// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939msg.c
 * Author: bob
 *
 * Created on October 5, 2014
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




#include    <j1939msg.h>
#include    <hex.h>



#ifdef	__cplusplus
extern "C" {
#endif
    
    
    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    
    

    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/


    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    //===============================================================
    //                    P r o p e r t i e s
    //===============================================================

    uint32_t        j1939msg_getEid(
        J1939_MSG       *pMsg
    )
        
    {
        uint32_t        value = 0;

        if(pMsg) {
            value  = (pMsg->CMSGSID.SID & 0x07FF);
            if (pMsg->CMSGEID.EXID) {
                value  = (pMsg->CMSGSID.SID & 0x07FF) << 18;
                value |= (pMsg->CMSGEID.EID & 0x03FFFF);
            }
        }
       
        // Return to caller.
        return( value & 0x1FFFFFFF );
    }

    bool            j1939msg_setEid(
        J1939_MSG       *pMsg,
        uint32_t        value
    )
    {

        if(pMsg) {
            pMsg->CMSGSID.SID = (value >> 18) & 0x07FF;
            pMsg->CMSGEID.EID = (value & 0x03FFFF);
            pMsg->CMSGEID.EXID = 1;
        }

        // Return to caller.
        return true;
    }

        

    uint32_t        j1939msg_getDataLength(
        J1939_MSG       *pMsg
    )
    {
        if( pMsg ) {
            return( pMsg->CMSGEID.DLC );
        }
        else {
            return 0;
        }
    }

    bool            j1939msg_setDataLength(
        J1939_MSG       *pMsg,
        uint32_t        value
    )
    {

        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if( value > 8 ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        if (pMsg) {
            pMsg->CMSGEID.DLC = value;
        }

        // Return to caller.
        return( true );
    }



    bool            j1939msg_IsEXID(
        J1939_MSG       *pMsg
    )
    {

        // Validate the input parameters.
        if( pMsg && pMsg->CMSGEID.EXID )
            return true;

        // Return to caller.
        return( false );
    }

        

    //----------------------------------------------------------
    //                      J1939_PDU
    //----------------------------------------------------------
    
    J1939_PDU       j1939msg_getJ1939_PDU(
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu = {0};

        if (pMsg) {
            pdu.eid = j1939msg_getEid(pMsg);
        }
        
        return pdu;
    }
    
    bool            j1939msg_setJ1939_PDU(
        J1939_MSG       *pMsg,
        uint32_t        value
    )
    {
        
        j1939msg_setEid(pMsg, value);
        
        // Return to caller.
        return( true );
    }
    
        
    uint8_t         j1939msg_getJ1939_DA_From_PDU(
        J1939_PDU       pdu
    )
    {
        uint8_t         da;
        
        if (pdu.PF < 240) {     // PDU1
            da = pdu.PS;
        }
        else {                  // PDU2
            da = 255;               // General Broadcast
        }
        
        return da;
    }
    
    
    
    
    //----------------------------------------------------------
    //                      J1939_PGN
    //----------------------------------------------------------
    
    J1939_PGN       j1939msg_getJ1939_PGN_From_PDU(
        J1939_PDU       pdu
    )
    {
        J1939_PGN       pgn;
        
        pgn.w = 0;
        // PDU_CONTROL fits within the eid.
        if (pdu.EDP) {
            pgn.EDP = 1;
        }
        if (pdu.DP) {
            pgn.DP = 1;
        }
        pgn.PF = pdu.PF;
        if (pdu.PF >= 240) {
            pgn.GE = pdu.PS;
        }
        
        return pgn;
    }
    
    
    
    J1939_PGN       j1939msg_getJ1939_PGN(
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        
        pdu.eid = j1939msg_getEid(pMsg);
        return j1939msg_getJ1939_PGN_From_PDU(pdu);
    }
    
    
    
    uint32_t        j1939msg_getSid(
        J1939_MSG       *pMsg
    )
    {
        uint32_t        value = 0;

        if (pMsg) {
            value  = (pMsg->CMSGSID.SID & 0x07FF);
            if (pMsg->CMSGEID.EXID) {
                value  = (pMsg->CMSGSID.SID & 0x07FF) << 18;
                value |= (pMsg->CMSGEID.EID & 0x03FFFF);
            }
        }
        
        // Return to caller.
        return( value );
    }

    bool            j1939msg_setSid(
        J1939_MSG       *pMsg,
        uint32_t        value
    )
    {

        if (pMsg) {
            pMsg->CMSGSID.SID = value & 0x07FF;
            pMsg->CMSGEID.EID = 0;
            pMsg->CMSGEID.EXID = 0;
        }
        
        // Return to caller.
        return true;
    }
    
    
    


    //===============================================================
    //                    M e t h o d s
    //===============================================================


    //----------------------------------------------------------
    //                       C l e a r
    //----------------------------------------------------------

    void            j1939msg_Clear(
        J1939_MSG         *pMsg
    )
    {
#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        pMsg->CMSGSID.w   = 0;
        pMsg->CMSGEID.w   = 0;
        pMsg->DATA.w0 = 0;
        pMsg->DATA.w1 = 0;
    }


    void            j1939name_Clear(
        J1939_NAME      *pName
    )
    {
#ifdef NDEBUG
#else
        if (NULL == pName) {
            DEBUG_BREAK();
        }
        if( !(((int)pName & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        pName->w0 = 0;
        pName->w1 = 0;
    }
    
    

    //----------------------------------------------------------
    //                  C o n s t r u c t
    //----------------------------------------------------------

    bool            j1939msg_ConstructMsg(
        J1939_MSG       *pMsg,
        uint32_t        sid,
        uint32_t        dlc,
        uint8_t         *pData
    )
    {
        uint32_t        i;

#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        if (dlc > 8) {
            return false;
        }

        j1939msg_Clear(pMsg);
        j1939msg_setSid(pMsg, sid);
        pMsg->CMSGEID.DLC = dlc;
        if (pData && dlc) {
            for (i=0; i<dlc; ++i) {
                pMsg->DATA.bytes[i] = *pData++;
            }
            for ( ; i<8; ++i) {
                pMsg->DATA.bytes[i] = 0x00;
            }
        }
        else {
            for ( i=0; i<8; ++i) {
                pMsg->DATA.bytes[i] = 0x00;
            }
        }

        return true;
    }


    bool            j1939msg_ConstructMsg_E(
        J1939_MSG       *pMsg,
        uint32_t        eid,
        uint32_t        dlc,
        uint8_t         *pData
    )
    {
        uint32_t        i;

#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        if (dlc > 8) {
            return false;
        }

        j1939msg_Clear(pMsg);
        j1939msg_setEid(pMsg, eid);
        pMsg->CMSGEID.DLC = dlc;
        if (pData && dlc) {
            for (i=0; i<dlc; ++i) {
                pMsg->DATA.bytes[i] = *pData++;
            }
            for ( ; i<8; ++i) {
                pMsg->DATA.bytes[i] = 0x00;
            }
        }
        else {
            for ( i=0; i<8; ++i) {
                pMsg->DATA.bytes[i] = 0x00;
            }
        }

        return true;
    }

    
    bool            j1939msg_ConstructMsg_E1(
        J1939_MSG       *pMsg,
        uint32_t        eid,
        uint32_t        dlc,
        uint8_t         *pData
    )
    {
        uint32_t        i;
        
#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        if (dlc > 8) {
            return false;
        }
        
        j1939msg_Clear(pMsg);
        j1939msg_setEid(pMsg, eid);
        pMsg->CMSGEID.DLC = dlc;
        if (pData && dlc) {
            for (i=0; i<dlc; ++i) {
                pMsg->DATA.bytes[i] = *pData++;
            }
            for ( ; i<8; ++i) {
                pMsg->DATA.bytes[i] = 0xFF;
            }
        }
        else {
            for ( i=0; i<8; ++i) {
                pMsg->DATA.bytes[i] = 0xFF;
            }
        }
        
        return true;
    }
    
    

    //----------------------------------------------------------
    //                C o n s t r u c t  R T R
    //----------------------------------------------------------

    bool            j1939msg_ConstructRTR(
        J1939_MSG       *pMsg,
        uint32_t        sid
    )
    {
#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        j1939msg_Clear(pMsg);
        j1939msg_setSid(pMsg, sid);
        pMsg->CMSGEID.RTR   = 1;
        return true;
    }


    bool            j1939msg_ConstructRTR_E(
        J1939_MSG       *pMsg,
        uint32_t        eid
    )
    {
#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        j1939msg_Clear(pMsg);
        j1939msg_setEid(pMsg, eid);
        pMsg->CMSGEID.RTR   = 1;
        return true;
    }



    bool            j1939name_Construct(
        J1939_NAME      *pName,
        uint32_t        spn2837,        // J1939 NAME Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 NAME Manufacturer Code (11 bits)
        uint8_t         spn2846,        // J1939 NAME Industry Group (3 bits)
        uint8_t         spn2841,        // J1939 NAME Function (8 bits)
        uint8_t         spn2839         // J1939 NAME Function Instance (5 bits)
    )
    {
#ifdef NDEBUG
#else
        if (NULL == pName) {
            DEBUG_BREAK();
            return false;
        }
        if( !(((int)pName & 0x3) == 0) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        j1939name_Clear(pName);
        pName->IDN = spn2837;
        pName->MFG = spn2838;
        
        //this->name.ECU = 0;         // Supplied by object
        pName->FU  = spn2841;
        pName->FUI = spn2839;
        pName->VS  = 1;             // SPN
        //pName->VSI = 0;
        pName->IG  = spn2846;
        //pName->AAC = 0;

        return true;
    }
    
    
    
    //----------------------------------------------------------
    //                       C o p y
    //----------------------------------------------------------
    
    void            j1939msg_Copy(
        J1939_MSG         *pMsgIn,
        J1939_MSG         *pMsgOut
    )
    {
#ifdef NDEBUG
#else
#ifndef __APPLE__
        if (NULL == pMsgIn) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsgIn & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
        if (NULL == pMsgOut) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsgOut & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
#endif
        pMsgOut->CMSGSID.w  = pMsgIn->CMSGSID.w;
        pMsgOut->CMSGEID.w  = pMsgIn->CMSGEID.w;
        pMsgOut->DATA.w0    = pMsgIn->DATA.w0;
        pMsgOut->DATA.w1    = pMsgIn->DATA.w1;
    }
    

    
    //----------------------------------------------------------
    //               C r e a t e  P r i n t a b l e
    //----------------------------------------------------------

    void            j1939msg_CreatePrintable(
        J1939_MSG       *pMsg,
        char            *pData          // Ptr to 64 character buffer
    )
    {
        uint32_t        sid;
        uint32_t        len = 64;
        char            *pOut = pData;
        uint32_t        i;
        HEX_DATA        *pHex = OBJ_NIL;

#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        pHex = hex_New();
        i = pMsg->CMSGSID.CMSGTS & 0xFFFF;
        hex_putU16( pHex, i, &len, (char **)&pOut );
        *pOut++ = ' ';
        
        sid = j1939msg_getSid(pMsg);
        hex_putU32( pHex, sid, &len, (char **)&pOut );

        *pOut++ = ' ';
        if( pMsg->CMSGEID.RTR ) {
            *pOut++ = 'r';
            *pOut++ = 't';
            *pOut++ = 'r';
        }
        else {
            hex_putU8( pHex, pMsg->CMSGEID.DLC, &len, (char **)&pOut );
            if( pMsg->CMSGEID.DLC ) {
                *pOut++ = ' ';
                //for( i=0; i<pMsg->CMSGEID.DLC; ++i ) {
                for( i=0; i<8; ++i ) {
                    hex_putU8( pHex, pMsg->DATA.bytes[i], &len, (char **)&pOut );
                }
            }
        }
        *pOut++ = '\n';

        while ( len-- ) {
            *pOut++ = '\0';
        }

        if (pHex) {
            obj_Release(pHex);
            pHex = OBJ_NIL;
        }
    }



    //----------------------------------------------------------
    //                 E x t r a c t  D a t a
    //----------------------------------------------------------

    void            j1939msg_ExtractData(
        J1939_MSG       *pMsg,
        uint32_t        *pLengthOut,
        uint8_t         *pDataOut
    )
    {
        uint32_t        cLen;
        uint32_t        i;
        uint8_t         *pData;

#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        cLen = pMsg->CMSGEID.DLC;
        if (pLengthOut) {
            *pLengthOut = cLen;
        }
        if (pDataOut) {
            pData = pDataOut;
            for (i=0; i<cLen; ++i) {
                *pData++ = pMsg->DATA.bytes[i];
            }
            if (cLen && (cLen < 8)) {
                pDataOut[cLen] = '\0';
            }
        }
        
    }



    //----------------------------------------------------------
    //                 I n s e r t  D a t a
    //----------------------------------------------------------

    bool            j1939msg_InsertData(
        J1939_MSG       *pMsg,
        uint8_t         length,
        uint8_t         *pData
    )
    {
        uint32_t        i;

#ifdef NDEBUG
#else
        if (NULL == pMsg) {
            DEBUG_BREAK();
        }
        if( !(((int)pMsg & 0x3) == 0) ) {
            DEBUG_BREAK();
        }
#endif
        if (length > 8) {
            return false;
        }
        pMsg->CMSGEID.DLC = length;
        if (NULL == pData) {
            if (0 == length) {
                return true;
            }
            else
                return false;
        }

        for (i=0; i<length; ++i) {
            pMsg->DATA.bytes[i] = *pData++;
        }
        for ( ; i<8; ++i) {
            pMsg->DATA.bytes[i] = '\0';
        }

        return true;
    }




#ifdef	__cplusplus
}
#endif




