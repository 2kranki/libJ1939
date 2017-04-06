/****************************************************************
 *          Data j1939ca (j1939ca) Support Subroutines           *
 ****************************************************************/
/*
 * Program
 *              Data j1939ca (j1939ca) Subroutines
 * Purpose
 *              See j1939ca.H for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See j1939ca.H for the history.
 * References
 *              See j1939ca.H for the references.
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
#include        "j1939ca_internal.h"


#ifdef	__cplusplus
extern	"C" {
#endif


    static
    const
    J1939CA_PGN_ENTRY   ca_pgn59392_entry = {
        // PGN 59392  0x00E800 - ACK/NAK
        &pgn59392_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn59392,
        NULL,                // Message Data Constructor
        0
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY   ca_pgn59904_entry = {
        // PGN 59904  0x00EA00 (PDU1) - Request for PGN
        &pgn59904_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn59904,
        NULL,                // Message Data Constructor
        0
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY   ca_pgn60928_entry = {
        // PGN 60928  0x00EE00 - Claim Address/Cannot Claim Address
        &pgn60928_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn60928,
        (P_MSGDATA_RTN)j1939ca_SetupPgn60928,
        0
    };

    
    static
    const
    J1939CA_PGN_ENTRY   *rcvPgnIndex[] = {
        &ca_pgn59392_entry,
        &ca_pgn59904_entry,
        &ca_pgn60928_entry,
        NULL
    };
    
    static
    const
    J1939CA_PGN_TABLE   rcvPgnTbl = {
        (sizeof(rcvPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &rcvPgnIndex
    };

    
    static
    const
    J1939CA_PGN_ENTRY   *xmtPgnIndex[] = {
        &ca_pgn60928_entry,
        NULL
    };
    
    static
    const
    J1939CA_PGN_TABLE   xmtPgnTbl = {
        (sizeof(xmtPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &xmtPgnIndex
    };
    

#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    uint32_t        defaultWaitTime = 15;       // 15ms
#endif
    
    

    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
    ****************************************************************/

    // Knuth's bit reversal algorithm
    // from http://www.hackersdelight.org/revisions.pdf
    uint32_t        bitReversal32_knuth(
        uint32_t        a
    )
    {
        uint32_t        t;
        
        a = (a << 15) | (a >> 17);
        t = (a ^ (a >> 10)) & 0x003f801f;
        a = (t + (t << 10)) ^ a;
        t = (a ^ (a >>  4)) & 0x0e038421;
        a = (t + (t <<  4)) ^ a;
        t = (a ^ (a >>  2)) & 0x22488842;
        a = (t + (t <<  2)) ^ a;
        
        return a;
    }
    
    
    // Knuth's bit reversal algorithm
    // from http://www.hackersdelight.org/revisions.pdf
    uint64_t        bitReversal64_knuth(
        uint64_t        x
    )
    {
        uint64_t        t;
        x = (x << 31) | (x >> 33);   // I.e., shlr(x, 31).
        t = (x ^ (x >> 20)) & 0x00000FFF800007FFLL;
        x = (t |(t << 20)) ^ x;
        t = (x ^ (x >> 8)) & 0x00F8000F80700807LL;
        x = (t |(t << 8)) ^ x;
        t = (x ^ (x >> 4)) & 0x0808708080807008LL;
        x = (t |(t << 4)) ^ x;
        t = (x ^ (x >> 2)) & 0x1111111111111111LL;
        x = (t |(t << 2)) ^ x;
        return x;
    }

    
    
    
    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    
    J1939CA_DATA * j1939ca_Alloc(
    )
    {
        J1939CA_DATA   *cbp;
        
        // Do initialization.
        
        cbp = obj_Alloc( sizeof(J1939CA_DATA) );
        
        // Return to caller.
        return( cbp );
    }
    
    
        
    
    //===============================================================
    //                      *** Properties ***
    //===============================================================

    //---------------------------------------------------------------
    //                  C l a i m e d  A d d r e s s
    //---------------------------------------------------------------
    
    uint8_t         j1939ca_getClaimedAddress(
        J1939CA_DATA	*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
      
        return cbp->ca;
    }

    
    bool			j1939ca_setClaimedAddress(
        J1939CA_DATA	*cbp,
        uint8_t         value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        cbp->ca = value;
        
        return true;
    }
    
    
    
    P_SRVCMSG_RTN   j1939ca_getHandler(
        J1939CA_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->pHandler;
    }
    
    

    J1939_NAME *    j1939ca_getName(
        J1939CA_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        return  &this->name;
    }
    
    
    
    //---------------------------------------------------------------
    //            S y s t e m  S u p p o r t  O b j e c t
    //---------------------------------------------------------------
    
    OBJ_ID          j1939ca_getSystemSupport(
        J1939CA_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pSys;
    }
    
    
    bool			j1939ca_setSystemSupport(
        J1939CA_DATA	*this,
        OBJ_ID          pValue
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pSys) {
            obj_Release(this->pSys);
            //this->pSys = OBJ_NIL;
        }
        this->pSys = pValue;
        
        return true;
    }
    
    
    
    bool            j1939ca_getTimedTransmits(
        J1939CA_DATA	*cbp
    )
    {
    
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
    
        return cbp->fTimedTransmit ? true : false;
    }
    
    bool            j1939ca_setTimedTransmits(
        J1939CA_DATA	*cbp,
        bool            value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (value) {
            cbp->fTimedTransmit = true;
        }
        else {
            cbp->fTimedTransmit = false;
        }
        
        return true;
    }
    
    
    bool			j1939ca_setXmtMsg(
        J1939CA_DATA	*cbp,
        P_XMTMSG_RTN    pRoutine,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        cbp->pXmtMsg  = pRoutine;
        cbp->pXmtData = pData;
        
        return true;
    }


    bool			j1939ca_setXmtMsgDL(
        J1939CA_DATA	*cbp,
        P_J1939_XMTRTN  pXmtMsg,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        cbp->pXmtMsgDL  = pXmtMsg;
        cbp->pXmtDataDL = pData;
        
        return true;
    }
    
    



    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------

    void            j1939ca_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939CA_DATA	*cbp = objId;
        
        // Do initialization.
        if( NULL == cbp ) {
            return;
        }
        
        obj_Dealloc( cbp );
        cbp = NULL;
        
        // Return to caller.
    }



    //---------------------------------------------------------------
    //                F i n d  P G N  E n t r y
    //---------------------------------------------------------------
    
    // Search the PGN tables starting with the inherited one first.
    // If the entry is found, set it in this->pCurEntry.
    
    bool            j1939ca_FindRcvPgnEntry(
        J1939CA_DATA	*this,
        J1939_PGN       pgn
    )
    {
        const
        J1939CA_PGN_ENTRY *pCurEntry;
        const
        J1939CA_PGN_ENTRY *(*pCurIndex);
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Search the dynamic pgn list.
        if( this->pRcvPgnTbl ) {
            pCurIndex = (const J1939CA_PGN_ENTRY *(*))this->pRcvPgnTbl->pPGNs;
            while ( (pCurEntry = *pCurIndex++) ) {
                if (pgn.w == pCurEntry->pDef->pgn ) {
                    this->pCurEntry = pCurEntry;
                    return true;
                }
            }
        }

        // Search the static pgn list.
        pCurIndex = (const J1939CA_PGN_ENTRY *(*))rcvPgnTbl.pPGNs;
        while ( (pCurEntry = *pCurIndex++) ) {
            if (pgn.w == pCurEntry->pDef->pgn ) {
                this->pCurEntry = pCurEntry;
                return true;
            }
        }
        
        // Return to caller.
        return false;
    }
    
    
    bool            j1939ca_FindXmtPgnEntry(
        J1939CA_DATA	*cbp,
        J1939_PGN       pgn
    )
    {
        const
        J1939CA_PGN_ENTRY *pCurEntry;
        const
        J1939CA_PGN_ENTRY *(*pCurIndex);
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if( cbp->pXmtPgnTbl ) {
            pCurIndex = (const J1939CA_PGN_ENTRY *(*))cbp->pXmtPgnTbl->pPGNs;
            while ( (pCurEntry = *pCurIndex++) ) {
                if (pgn.w == pCurEntry->pDef->pgn ) {
                    cbp->pCurEntry = pCurEntry;
                    return true;
                }
            }
        }
        
        pCurIndex = (const J1939CA_PGN_ENTRY *(*))xmtPgnTbl.pPGNs;
        while ( (pCurEntry = *pCurIndex++) ) {
            if (pgn.w == pCurEntry->pDef->pgn ) {
                cbp->pCurEntry = pCurEntry;
                return true;
            }
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  M e s s a g e s
    //---------------------------------------------------------------

    /* HandleMessages() is passed messages from a message source such
     * as a CAN FIFO Receive Queue. This routine handles the message
     * either internally or via its responder chain.
     * Warning: This function must conform to P_SRVCMSG_RTN specs.
     */
    
    bool            j1939ca_HandleMessages(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg           // if NULL, receive timed out
    )
    {
        J1939_PDU       pdu;
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Get the PGN requested.
        if (pMsg) {
            pdu.eid = eid;
            this->curPgn = j1939msg_getJ1939_PGN_From_PDU(pdu);
            this->curDa = j1939msg_getJ1939_DA_From_PDU(pdu);
            this->curSa = pdu.SA;
        }
        else {
            pdu.eid = 0;
            this->curPgn.w = 0;
            this->curDa = 255;
            this->curSa = 255;
        }
        
        if (J1939CA_STATE_NORMAL_OPERATION == this->cs) {
            if (pMsg) {
                if (this->curSa == this->ca) {    // *** Somebody is using our address! ***
                    // Warning - It might be necessary to go through the
                    // claiming procedure here. The doc is unclear. So, we will
                    // just resend our claim as it is.
                    fRc = j1939ca_TransmitPgn60928(this);
                }
                fRc = j1939ca_FindRcvPgnEntry(this, this->curPgn);
                if (fRc) {
                    fRc = (*this->pCurEntry->pService)( this, pdu.eid, pMsg);
                }
            }
            if (this->pTimedTransmit && this->fTimedTransmit) {
                fRc = (*this->pTimedTransmit)(this);
            }
        }
        else {
            fRc = j1939ca_HandlePgn60928( this, pdu.eid, pMsg );
        }
        
        
        // Return to caller.
        return fRc;
    }

    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 59392    0x00E800
    //---------------------------------------------------------------
    
    // ACK/NAK Message
    
    bool            j1939ca_HandlePgn59392(
        J1939CA_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        
        //TODO: Do something, not sure what yet.
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 59904    0x00EA00
    //---------------------------------------------------------------
    
    // Used to request a Parameter Group from a network device or devices.
    // First 3 bytes of data are the PGN being requested.
    
    bool            j1939ca_HandlePgn59904(
        J1939CA_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       requestedPgn;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        
        // Get the PGN requested.
        requestedPgn.w = 0;
        requestedPgn.pgn0 = pMsg->DATA.bytes[0];
        requestedPgn.pgn1 = pMsg->DATA.bytes[1];
        requestedPgn.pgn2 = pMsg->DATA.bytes[2];
        
        if (0x0000EA00 == requestedPgn.w) {
            // We should never be requesting a request!
            return false;
        }
        
        fRc = j1939ca_FindXmtPgnEntry(cbp, requestedPgn);
        if (fRc) {
            fRc = j1939ca_TransmitPgn(cbp, cbp->pCurEntry);
        }
        else {
            if ((requestedPgn.PF < 240) && !(255 == cbp->curDa)) {
                fRc = j1939ca_TransmitPgn59392_NAKPGN( cbp, requestedPgn );
            }
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //     H a n d l e  PGN 60928  0x00EE00 - Claim Address
    //---------------------------------------------------------------
    
    bool            j1939ca_HandlePgn60928(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        bool            fRc;
        uint32_t        msTime = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (pMsg) {
            pgn = j1939msg_getJ1939_PGN(pMsg);
            pdu = j1939msg_getJ1939_PDU(pMsg);
        }
        
        switch (this->cs) {
                
            case J1939CA_STATE_START:
                goto claimAddress;
                break;
                
            case J1939CA_STATE_SEND_CLAIM_ADDRESS:
    claimAddress:
                // Send Claim Address msg.
                fRc = j1939ca_TransmitPgn60928(this);
                if (this->pSys) {
                    this->startTime = this->pSys->pGetTimeMS(this->pSys);
                }
                this->cs = J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS;
                break;
                
            case J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS:
                if (pMsg) {
    checkAddressClaim:
                    // Ignore everything but PGN 60298 - Address Claim
                    if (60928 == pgn.pgn) {
                        if (pdu.SA == this->ca) {
                            if (pMsg->DATA.dw > this->name.dw) {
                                goto claimAddress;
                            }
                            else {
                                goto try_new_address;
                            }
                        }
                        if (pdu.SA == 254) {    // *** Claim was denied! ***
    try_new_address:
                            // Figure out a new address.
                            // (Arbitrary Addresses are 128..247.)
                            if (0 == this->ca) {
                                this->ca = 1;
                            }
                            else if (1 == this->ca) {
                                this->ca = 128;
                            }
                            else if (this->ca > 127) {
                                ++this->ca;
                            }
                            if (248 == this->ca) {
                                // Can not claim address (must not transmit)
                                this->cs = J1939CA_STATE_WAIT_FOR_COMMANDED_ADDRESS;
                                break;
                            }
                            goto claimAddress;
                        }
                    }
                    this->cs = J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS;
                }
                else {
                    // The clock wraps since it is in ms and only 32 bits.
                    // The following statement should still work.
                    if (this->pSys) {
                        msTime = this->pSys->pGetTimeMS(this->pSys);
                    }
                    if (msTime >= (this->startTime + 250)) {
                        // Timed out, so we should be able to use the address.
                        this->cs = J1939CA_STATE_NORMAL_OPERATION;
                    }
                }
                break;
                
            case J1939CA_STATE_NORMAL_OPERATION:
                if (pMsg) {
                    if (60928 == pgn.pgn) {
                        if (pdu.SA == this->ca) {
                            goto checkAddressClaim;
                        }
                    }
                    // Re-assert our address claim.
                    fRc = j1939ca_TransmitPgn60928(this);
                    this->cs = J1939CA_STATE_NORMAL_OPERATION;
                }
                else {
                    // Timed out, so we should be able to use the address.
                    this->cs = J1939CA_STATE_NORMAL_OPERATION;
                }
                break;
                
            case J1939CA_STATE_WAIT_FOR_COMMANDED_ADDRESS:
                if (pMsg) {
                    if (60298 == pgn.pgn) {
                        if (pdu.SA == this->ca) {
                            if (this->pSys) {
                                this->pSys->pSleepMS(this->pSys, 100);
                            }
                            this->ca = 254;
                            fRc = j1939ca_TransmitPgn60928(this);
                        }
                    }
                    this->cs = J1939CA_STATE_WAIT_FOR_COMMANDED_ADDRESS;
                }
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

    J1939CA_DATA *	j1939ca_Init(
        J1939CA_DATA    *this,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_PTR         pXmtData,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint16_t		cbSize = sizeof(J1939CA_DATA);

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
        BREAK_NULL(pXmtMsg);
        
        this = obj_Init( this, cbSize, OBJ_IDENT_J1939CA );
        if (NULL == this) {
            return NULL;
        }
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939ca_Vtbl);
        
        this->cs = J1939CA_STATE_START;
        this->pHandler = (P_SRVCMSG_RTN)j1939ca_HandleMessages;
        this->fTimedTransmit = true;
        j1939ca_setXmtMsg(this, pXmtMsg, pXmtData);
        j1939ca_setXmtMsgDL(this, (P_J1939_XMTRTN)j1939ca_XmtMsgDL, this);
        
        this->name.IDN = spn2837;
        this->name.MFG = spn2838;
            
        //this->name.ECU = 0;        // Supplied by object
        //this->name.FU  = 0;
        //this->name.FUI = 0;
        
        this->name.VS  = 1;
        this->name.VSI = 0;
        this->name.IG  = spn2846;
        this->name.AAC = 0;
        
#ifdef NDEBUG
#else
        if( !j1939ca_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(offsetof(J1939CA_DATA,curPgn));
#endif
        
        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                  M s  T i m e  G e t
    //---------------------------------------------------------------
    
    uint32_t        j1939ca_MsTimeGet(
        J1939CA_DATA	*this
    )
    {
        uint32_t        msTime = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pSys) {
            msTime = this->pSys->pGetTimeMS(this->pSys);
        }
        
        // Return to caller.
        return msTime;
    }
    
    
    
    //---------------------------------------------------------------
    //                  T r a n s m i t  P g n
    //---------------------------------------------------------------
    
    bool            j1939ca_TransmitPgn(
        J1939CA_DATA	*this,
        const
        J1939CA_PGN_ENTRY
                        *pPgnEntry
    )
    {
        bool            fRc = false;

        fRc = j1939ca_TransmitPgnDa(this, pPgnEntry, this->curSa);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  T r a n s m i t  P g n  D a
    //---------------------------------------------------------------
    
    bool            j1939ca_TransmitPgnDa(
        J1939CA_DATA	*this,
        const
        J1939CA_PGN_ENTRY
                        *pPgnEntry,
        uint8_t         da
    )
    {
        uint16_t        dlc = pPgnEntry->pDef->dlc;
        uint8_t         data[8];
        uint8_t         *pData = data;
        J1939_PGN       pgn;
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        
        pgn.w = pPgnEntry->pDef->pgn;
        pdu.PF = pgn.PF;
        if (pdu.PF < 240) {
            // Claim Name must always be global!
            if (0xEE == pgn.PF) {
                pdu.PS = 255;
            }
            else {
                pdu.PS = da;
            }
        }
        else {
            pdu.PS = pgn.GE;
        }
        pdu.SA = this->ca;
        pdu.P = pPgnEntry->pDef->priority;
        
        if (0 ==  dlc) {
            dlc = 1785;
        }
        if ((0 == dlc) || (dlc > 8)) {
            pData = mem_Malloc(dlc);
            if (NULL == pData) {
                return false;
            }
        }
        
        if (pPgnEntry->pDataSetup) {
            fRc = (*pPgnEntry->pDataSetup)(this,(uint32_t *)&pdu,dlc,pData);
        }
        
        if (this->pXmtMsgDL) {
            fRc = (*this->pXmtMsgDL)(this->pXmtDataDL, 0, pdu, dlc, &data);
        }
        
        if (pData == data) {
        }
        else {
            mem_Free(pData);
            pData = NULL;
        }
        
        // Set the Time-out Start time if there is a time-out needed.
        if ((pPgnEntry->pDef->msFreq) && pPgnEntry->xmtTimeoutOff) {
            uint32_t        msTime = 0;
            BREAK_NOT_BOUNDARY4(pPgnEntry->xmtTimeoutOff);
            if (this->pSys) {
                msTime = this->pSys->pGetTimeMS(this->pSys);
            }
            *((uint32_t *)((uint8_t *)this)+pPgnEntry->xmtTimeoutOff) = msTime;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //            T r a n s m i t  P G N 5 9 3 9 2  0x00E800
    //---------------------------------------------------------------
    
    bool            j1939ca_TransmitPgn59392_NAKPGN(
        J1939CA_DATA	*cbp,
        J1939_PGN       pgn                 // PGN being requested
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        uint32_t        i;
        bool            fRc = false;
        
        data[0] = 1;
        for (i=1; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[4] = cbp->ca;
        data[5] = pgn.pgn0;
        data[6] = pgn.pgn1;
        data[7] = pgn.pgn2;
        
        pdu.PF = 232;
        if (255 == cbp->curDa) {
            pdu.PS = 255;
        }
        else {
            pdu.PS = cbp->curSa;
        }
        pdu.SA = cbp->ca;
        pdu.P  = 6;         // Priority
        
        if (cbp->pXmtMsgDL) {
            fRc = (*cbp->pXmtMsgDL)(cbp->pXmtDataDL, 0, pdu, dlc, &data);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //            T r a n s m i t  P G N 5 9 9 0 4  0x00EA00
    //---------------------------------------------------------------
    
    // Request for PGN - The message data contains the PGN being
    // requested.
    
    bool            j1939ca_TransmitPgn59904(
        J1939CA_DATA	*this,
        J1939_PGN       pgn,                // PGN being requested
        uint8_t         da                  // Destination Address
    )
    {
        uint16_t        dlc = 3;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        uint32_t        i;
        bool            fRc = false;
        
        // Extract the PGN.
        data[0] = pgn.pgn0;
        data[1] = pgn.pgn1;
        data[2] = pgn.pgn2;
        for (i=3; i<8; ++i) {
            data[i] = 0xFF;
        }
        
        pdu.PF = 234;
        pdu.PS = da;
        pdu.SA = this->ca;
        pdu.P  = 6;         // Priority
        
        if (this->pXmtMsgDL) {
            fRc = (*this->pXmtMsgDL)(this->pXmtDataDL, 0, pdu, dlc, &data);
        }

        // We must respond to our own global request for Address Claimed.
        if ((0x0000EE00 == pgn.pgn) && (255 == da)) {
            fRc = j1939ca_TransmitPgn60928(this);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                T r a n s m i t  P G N 6 0 9 2 8  0x00EE00
    //---------------------------------------------------------------
    
    // Claim Address/Cannot Claim Address

    bool            j1939ca_SetupPgn60928(
        J1939CA_DATA	*this,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        J1939_NAME      *pName = (J1939_NAME *)pData;
        
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
        
        if (pData) {
            pName->w0 = this->name.w0;
            pName->w1 = this->name.w1;
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    bool            j1939ca_TransmitPgn60928(
        J1939CA_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        
        pdu.PF = 238;
        pdu.PS = 255;       // We must always make this global.
        pdu.SA = this->ca;
        pdu.P  = 7;         // Priority
        
        //fRc = j1939ca_SetupPgn60928(cbp,&pdu,dlc,&cbp->name);
        // Not needed since we just get the name from the same place.
        
        if (this->pXmtMsgDL) {
            fRc = (*this->pXmtMsgDL)(this->pXmtDataDL, 0, pdu, dlc, &this->name);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                T r a n s m i t  M e s s a g e
    //---------------------------------------------------------------
    
    bool            j1939ca_XmtMsgDL(
        J1939CA_DATA	*this,
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
        if( !j1939ca_Validate(this) ) {
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
            fRc = j1939msg_ConstructMsg_E(&msg, pdu.eid, cData, pData);
            if (this->pXmtMsg) {
                fRc = (*this->pXmtMsg)(this->pXmtData, msDelay, &msg);
            }
        }
        else {
            //TODO: Complete Transport Protocol Transmit side
            DEBUG_BREAK();
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          Validate
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool            j1939ca_Validate(
        J1939CA_DATA	*this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_J1939CA) )
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




