/****************************************************************
 *              J1939 Data Link (j1939dg) Support
 ****************************************************************/
/*
 * Program
 *              J1939 Data Link (j1939dg) Support
 * Purpose
 *              See j1939dg.h for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See j1939dg.h for the history.
 * References
 *              See j1939dg.h for the references.
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




#include "j1939dg_internal.h"



#ifdef	__cplusplus
extern	"C" {
#endif


    /****************************************************************
    * * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
    ****************************************************************/

    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        NULL
    };

    static
    const
    J1939CA_PGN_TABLE     rcvPgnTbl = {
        (sizeof(rcvPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &rcvPgnIndex
    };



    static
    const
    J1939CA_PGN_ENTRY     *xmtPgnIndex[] = {
        NULL
    };

    static
    const
    J1939CA_PGN_TABLE     xmtPgnTbl = {
        (sizeof(xmtPgnIndex)/sizeof(J1939_PGN_ENTRY *))-1,
        0,              // Reserved
        &xmtPgnIndex
    };





    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
    ****************************************************************/

#ifdef NDEBUG
#else
    static
    bool            j1939dg_Validate(
        J1939DG_DATA      *cbp
    );
#endif
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939DG_DATA * j1939dg_Alloc(
    )
    {
        J1939DG_DATA   *cbp;

        // Do initialization.

        cbp = obj_Alloc( sizeof(J1939DG_DATA) );

        // Return to caller.
        return( cbp );
    }




    //===============================================================
    //                      *** Properties ***
    //===============================================================

    uint32_t        j1939dg_getMask(
        J1939DG_DATA	*cbp
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dg_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }


    bool			j1939dg_setMask(
        J1939DG_DATA	*cbp,
        uint32_t        value
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dg_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //FIXME: cbp->mask = value;

        return true;
    }



    bool			j1939dg_setReceivePacket(
        J1939DG_DATA	*cbp,
        void            (*receivePacket)(void *, void *),
        void            *pData
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dg_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //FIXME: cbp->pRcvPacket = receivePacket;
        //FIXME: cbp->pRcvData  = pData;

        return true;
    }





    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------

    void            j1939dg_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939DG_DATA	*cbp = objId;

        // Do initialization.
        if( NULL == cbp ) {
            return;
        }

        j1939ca_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //          H a n d l e  PGN 59904    0x00EA00
    //---------------------------------------------------------------

    // Used to request a Parameter Group from a network device or devices.
    // This is called to handle requests for pgns that this object supports.
    // First 3 bytes of data are the PGN being requested.

    bool            j1939dg_HandlePgn59904(
        J1939DG_DATA	*cbp,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        J1939_PGN       requestPgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dg_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);

        if (NULL == pMsg) {
            return false;
        }

        // Get the PGN requested.
        requestPgn.w = 0;
        requestPgn.pgn0 = pMsg->DATA.bytes[0];
        requestPgn.pgn1 = pMsg->DATA.bytes[1];
        requestPgn.pgn2 = pMsg->DATA.bytes[2];

        // Handle the PGNs that we can.
        switch (pgn.w) {

            case 61440:
                j1939dg_TransmitPgn61440( cbp );
                return true;
                break;

           default:
                return false;
                break;
        }

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 0    0x000000
    //---------------------------------------------------------------

    /*
     * Start Retarding:
     *      When TSC1 is received with (spn695 == (1 or 3 for Engine) or
     *      (2 or 3 for Engine Retarder)).
     * Stop Retarding:
     *      When TSC1 is received with (spn695 == 0) or two update
     *      periods have expired since last TSC1. An update period
     *      for the Engine is 10ms, but 50ms for the Engine Retarder.
     */

    bool            j1939dg_HandlePgn0(
        J1939DG_DATA	*cbp,
        J1939_MSG       *pMsg           // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         sa;
        uint8_t         spn518;         // Requested Torque / Torque Limit
        uint8_t         spn695;         // Override Control Mode
                                        // 0 - Disable override by the source of msg
                                        // 1 - Override speed
                                        // 2 - Override torque
                                        // 3 - Limit Speed/Torque
        uint8_t         spn696;         // Requested Speed Control Conditions
        uint8_t         spn897;         // Override Control Mode Priority
                                        // 0 == Highest Priority
                                        // 3 == Lowest Priority
        uint16_t        spn898;         // Requested Speed / Speed Limit

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dg_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        sa = pdu.SA;
        spn695 = pMsg->DATA.bytes[0] & 0x3;
        spn696 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        spn897 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        spn898 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        spn518 = pMsg->DATA.bytes[3];

        if (0 == spn695) {      // *** Stop Retarding ***
            ;
        }


        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 1 4 4 0
    //---------------------------------------------------------------

    bool            j1939dg_HandlePgn61440(
        J1939DG_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dg_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //           H a n d l e  T i m e d  T r a n s m i t s
    //---------------------------------------------------------------

    bool            j1939dg_HandleTimedTransmits(
        J1939DG_DATA	*this
    )
    {
        uint32_t        curTime;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dg_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        curTime = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        this->curTime = curTime;

        if ((curTime - this->time61440.msTime) >= this->time61440.msDelay) {
            j1939dg_TransmitPgn61440(this);
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939DG_DATA *	j1939dg_Init(
        J1939DG_DATA    *this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint16_t		cbSize = sizeof(J1939DG_DATA);

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
#endif

        this =  (J1939DG_DATA *)j1939ca_Init(
                        (J1939CA_DATA *)this,
                        pCAN,
                        pSYS,
                        spn2837,
                        spn2838,
                        spn2846
                );
        if (NULL == this) {
            return NULL;
        }
        obj_setSize(  (OBJ_ID)this, cbSize );
        obj_setIdent( (OBJ_ID)this, OBJ_IDENT_J1939DG );
        this->pCaVtbl = (void *)obj_getVtbl(this);
        obj_setVtbl(  (OBJ_ID)this, (OBJ_IUNKNOWN *)&j1939dg_Vtbl );

        j1939ca_Setup((J1939CA_DATA *)this, J1939_OEM);
        //this->super.name.ECU = 0;
        this->super.name.FU = 12;
        //this->super.name.FUI = 0;
        this->super.pRcvPgnTbl = &rcvPgnTbl;
        this->super.pXmtPgnTbl = &xmtPgnTbl;
        this->super.pTimedTransmit =
        (P_HANDLE_TIMED_TRANSMITS)&j1939dg_HandleTimedTransmits;

        // Default all SPNs to unsupported values.
        memset(
               &this->spnFirst,
               0xFF,
               (offsetof(J1939DG_DATA,spnLast) - offsetof(J1939DG_DATA,spnFirst)
                + sizeof(uint32_t))
               );
        //this->spn1481 = J1939_BRAKE_SYSTEM_CONTROLLER;
        this->spn571 = 1;       // Enable Retarder Brake Assist
        this->spn572 = 1;       // Enable Retarder Shift Assist

        this->time61440.msDefault = pgn61440_entry.msFreq;
        this->time61440.msDelay = pgn61440_entry.msFreq;
        this->time61440.pgn = 61440;
        
#ifdef NDEBUG
#else
        if( !j1939dg_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
        BREAK_NOT_BOUNDARY4(&this->time61440);
        BREAK_NOT_BOUNDARY4(&this->spn84);
        BREAK_NOT_BOUNDARY4(&this->spn1637);
        BREAK_NOT_BOUNDARY4(sizeof(J1939DG_DATA));
#endif

        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 0   0xF000
    //---------------------------------------------------------------

    // Electronic Retarder Controller 1 - ERC1 -
    // Unused bits are set to 1.
    // The Transmission and the Cruise Controller are normally interested
    // in this message and try to control the Engine Retarder via the
    // TSC1 message.
    bool            j1939dg_TransmitPgn61440(
        J1939DG_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;

        data[0]  = 0x00;
        data[0] |= this->spn900 & 0xF;
        data[0] |= (this->spn571 & 0x3) << 4;
        data[0] |= (this->spn572 & 0x3) << 6;
        data[1]  = this->spn520;
        data[2]  = this->spn1085;
        data[3]  = 0xF0;
        data[3] |= (this->spn1082 & 0x3);
        data[3] |= (this->spn1667 & 0x3) << 2;
        data[4]  = this->spn1480;
        data[5]  = this->spn1715;
        data[6]  = this->spn1716;
        data[7]  = this->spn1717;

        pdu.PF = 240;
        pdu.PS = 0;
        pdu.SA = this->super.ca;
        pdu.P  = 6;             // Priority

        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time61440.msTime = this->curTime;

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 4 9   0xF000
    //---------------------------------------------------------------

    // Retarder Configuration - RC -
    // Unused bits are set to 1.
    bool            j1939dg_TransmitPgn65249(
        J1939DG_DATA	*this
    )
    {
        uint32_t        dlc = 19;
        uint8_t         data[19] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;

        data[0]  = 0x00;
        data[0] |= this->spn900 & 0xF;
        data[0] |= (this->spn571 & 0x3) << 4;
        data[0] |= (this->spn572 & 0x3) << 6;
        data[1]  = this->spn520;
        data[2]  = this->spn1085;
        data[3]  = 0xF0;
        data[3] |= (this->spn1082 & 0x3);
        data[3] |= (this->spn1667 & 0x3) << 2;
        data[4]  = this->spn1480;
        data[5]  = this->spn1715;
        data[6]  = this->spn1716;
        data[7]  = this->spn1717;

        pdu.PF = 254;
        pdu.PS = 225;
        pdu.SA = this->super.ca;
        pdu.P  = 6;             // Priority

        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        //this->nextTime61440 = j1939ca_MsTimeGet((J1939CA_DATA *)this) + 100;

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                      Validate
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool            j1939dg_Validate(
        J1939DG_DATA	*this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_J1939DG ) )
                ;
            else
                return false;
        }
        else
            return(false);
        return( true );
    }
    #endif



#ifdef	__cplusplus
};
#endif
