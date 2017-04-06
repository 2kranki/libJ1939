/****************************************************************
 *              J1939 Data Link (j1939dl) Support
 ****************************************************************/
/*
 * Program
 *              J1939 Data Link (j1939dl) Support
 * Purpose
 *              See j1939dl.h for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See j1939dl.h for the history.
 * References
 *              See j1939dl.h for the references.
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




/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include "j1939dl_internal.h"



#ifdef	__cplusplus
extern	"C" {
#endif
    

    
    
    

    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
    ****************************************************************/

 

    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    
    J1939DL_DATA * j1939dl_Alloc(
    )
    {
        J1939DL_DATA   *cbp;
        
        // Do initialization.
        
        cbp = obj_Alloc( sizeof(J1939DL_DATA) );
        
        // Return to caller.
        return( cbp );
    }
    
    
        
    
    //===============================================================
    //                      *** Properties ***
    //===============================================================

    uint32_t        j1939dl_getEid(
        J1939DL_DATA	*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
      
        return 0;
    }

    
    bool			j1939dl_putEid(
        J1939DL_DATA	*cbp,
        uint32_t        value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        //FIXME: cbp->eid = value;
        
        return true;
    }
    
    
    
    uint32_t        j1939dl_getMask(
        J1939DL_DATA	*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return 0;
    }

    
    bool			j1939dl_putMask(
        J1939DL_DATA	*cbp,
        uint32_t        value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        //FIXME: cbp->mask = value;
        
        return true;
    }
    
    
    
    bool			j1939dl_setReceivePacket(
        J1939DL_DATA	*cbp,
        void            (*receivePacket)(void *, void *),
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        //FIXME: cbp->pRcvPacket = receivePacket;
        //FIXME: cbp->pRcvData  = pData;
        
        return true;
    }

    
    
    //---------------------------------------------------------------
    //                          X m t  M s g
    //---------------------------------------------------------------
    
    bool			j1939dl_setXmtMsg(
        J1939DL_DATA	*this,
        P_XMTMSG_RTN    pXmtMsg,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pXmtMsg   = pXmtMsg;
        this->pXmtData  = pData;
        
        return true;
    }
    
    




    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------

    void            j1939dl_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939DL_DATA	*cbp = objId;
        
        // Do initialization.
        if( NULL == cbp ) {
            return;
        }
        
        obj_Dealloc( cbp );
        cbp = NULL;
        
        // Return to caller.
    }



    //---------------------------------------------------------------
    //                 H a n d l e  P a c k e t
    //---------------------------------------------------------------
    
    bool            j1939dl_HandlePacket(
        J1939DL_DATA	*cbp,
        uint32_t        pgn,
        void            *pPacket
    )
    {
        //bool            fRc;
        //uint32_t        i;
        //RECEIVE_HANDLER *pHandler;
        //uint32_t        cmp;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  P G N 6 0 9 2 8  R e q u e s t
    //---------------------------------------------------------------
    
    bool            j1939dl_HandlePGN60928Request(
        J1939DL_DATA	*cbp,
        void            *pPacket
    )
    {
        J1939_MSG       *pMsg = pPacket;
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pgn = j1939msg_getJ1939_PGN(pMsg);
        pdu = j1939msg_getJ1939_PDU(pMsg);
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  R e q u e s t  P G N 5 9 9 0 4
    //---------------------------------------------------------------
    
    // Used to request a Parameter Group from a network device or devices.
    // First 3 bytes of data are the PGN being requested.
    
    bool            j1939dl_HandleRequest_PGN59904(
        J1939DL_DATA	*cbp,
        void            *pPacket
    )
    {
        //bool            fRc;
        //uint32_t        i;
        //RECEIVE_HANDLER *pHandler;
        //uint32_t        cmp;
        J1939_MSG       *pMsg = pPacket;
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Get the PGN requested.
        pMsg->DATA.bytes[3] = 0;
        pgn = j1939msg_getJ1939_PGN(pMsg);
        pdu = j1939msg_getJ1939_PDU(pMsg);
        
        // Handle the PGNs that we can.
        switch (pgn.w) {
            case 60928:
                j1939dl_TransmitPGN60928( cbp, pdu.PF );
                return true;
                break;
                
            default:
                break;
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939DL_DATA *	j1939dl_Init(
        J1939DL_DATA   *cbp,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_PTR         pData
    )
    {
        uint16_t		cbSize = sizeof(J1939DL_DATA);

        // Do initialization.
        if (NULL == cbp) {
            return NULL;
        }
        
        cbp = obj_Init( cbp, cbSize, OBJ_IDENT_J1939DL );
        if (NULL == cbp) {
            return NULL;
        }
        obj_setVtbl(cbp, (OBJ_IUNKNOWN *)&j1939dl_Vtbl);
        
        cbp->ca  = 0;
        cbp->fu  = 0;
        cbp->ecu = 0;
        cbp->ig  = 1;
        cbp->vs  = 1;
        cbp->vsi = 0;
        cbp->mc  = 0b00000001010;   // Cummins (lol)
        cbp->idn = 0b011110001110001110000;

#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return NULL;
        }
#endif
        
        // Return to caller.
        return cbp;
    }



    //---------------------------------------------------------------
    //                T r a n s m i t  P G N 6 0 9 2 8
    //---------------------------------------------------------------
    
    /* The Address Claimed PGN may be used in two ways:, to claim an address, and to
     * announce that a CA was unable to claim an address. The former case is referred
     * to as the Address Claimed message, and the latter as the Cannot Claim Address 
     * message. The Address Claimed message is used by any CA to either respond to a
     * received request message for the Address Claimed message or to simply claim a 
     * single address on the network. CAs shall issue it during initialization of a 
     * network or when attaching to a running network. If a CA receives an Address 
     * Claimed message claiming its own source address, it shall compare the NAME that 
     * was received in the Address Claimed message with its own NAME and determine which 
     * CA has a higher priority NAME.
     *
     * If the CA receiving the Address Claim determines that it has the higher priority 
     * NAME it may then transmit an Address Claimed message containing its NAME and 
     * address. However if it has the lower priority NAME it shall either attempt to 
     * claim a different address or send a Cannot Claim Address message. A CA that 
     * loses address arbitration in this manner and is in the process of sending a 
     * transport protocol message shall immediately cease sending the transport 
     * protocol message and shall not send a Transport Protocol Abort. Receivers of the
     * transport protocol message shall detect the interruption through the normal 
     * transport protocol timeout process as specified in J1939-21 Queued transport 
     * protocol frames shall cease within the timeout and constraints given in J1939-21, 
     * (50 ms).
     *
     * A CA may send the Cannot Claim Address message or a Request for Address Claim 
     * using the NULL address as a source address provided it has attempted the address
     * claim and without having successfully claimed an address. A network inter-
     * connection CA shall not use its own address in communications on the network 
     * until it has successfully claimed that address. Handling messages of other CAs 
     * is a special case for network interconnection devices. Network interconnection 
     * devices acting entirely as repeaters may pass messages bearing the originator’s 
     * Source Address before claiming their own addresses.
     */
    bool            j1939dl_TransmitPGN60928(
        J1939DL_DATA	*cbp,
        uint8_t         da                      // Destination Address
    )
    {
        J1939_MSG       msg;
        uint32_t        dlc = 8;
        J1939_NAME      name = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        
        // Example for ON-ROAD Vehicle - Cummins - 10 (mc), Identity - 1 (in)
        /*      vvvv
         *  iii ssss vvvv vvv            ffff feee mmmm mmmm mmmi iiii iiii iiii iiii iiii
         * aggg iiii ssss sssr ffff ffff iiii iiii cccc cccc cccn nnnn nnnn nnnn nnnn nnnn
         * 0001 0000 0000 0010 0000 0000 0000 0000 0000 0001 0100 0000 0000 0000 0000 0001
         *
         * Remember to reverse order:
         *                                                                       vvvv
         * iiii iiii iiii iiii iiii immm mmmm mmmm eeef ffff            vvv vvvv ssss iii
         * nnnn nnnn nnnn nnnn nnnn nccc cccc cccc iiii iiii ffff ffff rsss ssss iiii ggga
         * 1000 0000 0000 0000 0000 0010 1000 0000 0000 0000 0000 0000 0100 0000 0000 1000
         */
        name.IDN = cbp->idn;
        name.MFG = cbp->mc;
        name.ECU = cbp->ecu;
        name.FUI = cbp->fi;
        name.FU  = cbp->fu;
        name.VS  = cbp->vs;
        name.VSI = cbp->vsi;
        name.IG  = cbp->ig;
        name.AAC = 1;
        
        pdu.PF = 238;
        pdu.PS = da;
        pdu.SA = cbp->ca;
        pdu.P  = 7;         // Priority
        
        fRc = j1939msg_ConstructMsg_E( &msg, pdu.eid, dlc, (uint8_t *)&name );

        //FIXME: canbase_TransmitPacket( cbp, &msg );
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //              T r a n s m i t  M e s s a g e
    //---------------------------------------------------------------
    
    void            j1939dl_XmtMsg(
        J1939DL_DATA	*cbp,
        uint32_t        msDelay,
        J1939_MSG       *pMsg
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        if (cbp->pXmtMsg) {
            (*cbp->pXmtMsg)(cbp->pXmtData,msDelay,pMsg);
        }
        
        // Return to caller.
    }
    
    
    
    bool            j1939dl_XmtMsgDL(
        J1939DL_DATA	*this,
        uint32_t        msDelay,
        J1939_PDU       pdu,
        uint16_t        cData,
        void            *pData
    )
    {
        J1939_MSG       msg;
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939dl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if( 0 == cData ) {
            DEBUG_BREAK();
            return false;
        }
        if( cData > 1785 ) {
            DEBUG_BREAK();
            return false;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (cData < 9) {
            fRc = j1939msg_ConstructMsg_E( &msg, pdu.eid, cData, pData );
            if (this->pXmtMsg) {
                fRc = (*this->pXmtMsg)(this->pXmtData,msDelay,&msg);
            }
        }
        else {
            //TODO: Complete Transport Protocol Transmit side
        }
                
        // Return to caller.
        return fRc;
    }
    
    
    
    //**********************************************************
    //                      Validate
    //**********************************************************

    #ifdef NDEBUG
    #else
    static
    bool            j1939dl_Validate(
        J1939DL_DATA	*cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf( cbp, OBJ_IDENT_J1939DL ) )
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




