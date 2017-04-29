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
#include        <j1939ca_internal.h>
#include        <dec.h>


#ifdef	__cplusplus
extern	"C" {
#endif


    const
    J1939CA_PGN_ENTRY   ca_pgn51456_entry = {
        // PGN 51456  0x00C900 - RQST2
        &pgn51456_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn51456,
        NULL,
        NULL,                // Message Data Constructor
        0,
        0,
        0
    };
    
    
    const
    J1939CA_PGN_ENTRY   ca_pgn59392_entry = {
        // PGN 59392  0x00E800 - ACK/NAK
        &pgn59392_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn59392,
        NULL,
        NULL,                // Message Data Constructor
        0
    };
    
    
    const
    J1939CA_PGN_ENTRY   ca_pgn59904_entry = {
        // PGN 59904  0x00EA00 (PDU1) - Request for PGN
        &pgn59904_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn59904,
        NULL,
        NULL,                // Message Data Constructor
        0
    };
    
    
    const
    J1939CA_PGN_ENTRY   ca_pgn60160_entry = {
        // PGN 60416  0x00EC00 - Transport ProtocolConnection Management (TP.CM)
        &pgn60160_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn60160,
        NULL,
        NULL,                // Message Data Constructor
        0
    };
    
    
    const
    J1939CA_PGN_ENTRY   ca_pgn60416_entry = {
        // PGN 60416  0x00EC00 - Transport ProtocolConnection Management (TP.CM)
        &pgn60416_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn60416,
        NULL,
        NULL,                // Message Data Constructor
        0
    };
    
    
    const
    J1939CA_PGN_ENTRY   ca_pgn60928_entry = {
        // PGN 60928  0x00EE00 - Claim Address/Cannot Claim Address
        &pgn60928_entry,
        (P_SRVCMSG_RTN)j1939ca_HandlePgn60928,
        NULL,
        (P_SETUP_MSG_RTN)j1939ca_SetupPgn60928,
        0
    };

    
    const
    J1939CA_PGN_ENTRY   ca_pgn65242_entry = {
        // PGN 65242  0x00FEDA - Software Identification - SOFT
        &pgn65242_entry,
        NULL,
        (P_VARMSG_RTN)j1939ca_HandlePgn65242,
        (P_SETUP_MSG_RTN)j1939ca_SetupPgn65242,
        0,                              // Offset of Timeout
        0,                              // da
        0,                              // rsvd
        0                               // ms Xmt Repeat
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY   *rcvPgnIndex[] = {
        &ca_pgn51456_entry,
        &ca_pgn59392_entry,
        &ca_pgn59904_entry,
        &ca_pgn60416_entry,
        &ca_pgn60928_entry,
        &ca_pgn65242_entry,
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

#ifdef NDEBUG
#else
    static
    bool            j1939ca_Validate(
        J1939CA_DATA      *this
    );
#endif
    
    
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

    
    
    //---------------------------------------------------------------
    //                  T a s k  B o d y
    //---------------------------------------------------------------
    
    // Delayed messages could be handled by a separate task. This
    // function is designed to work in a psxThread to handle the
    // delayed messages.
    void            j1939ca_TaskBody(
        void            *pData
    )
    {
        J1939CA_DATA    *this = pData;
        
        j1939ca_XmtDelayedMsgs(this);
        if (this->pSYS && ((J1939_SYS_VTBL *)this->pSYS)->pSleepMS) {
            ((J1939_SYS_VTBL *)this->pSYS)->pSleepMS(this->pSYS, 10);
        }
    }
    
    
    J1939TP_DATA *    tp_Find(
        J1939CA_DATA	*this,
        uint8_t         activity,
        uint8_t         adr             // rcv/xmt address 
    )
    {
        int             i;
        
        for (i=0; i<j1989_CA_TP_SIZE; ++i) {
            if (this->TPs[i].activity == activity) {
                if (this->TPs[i].adr == adr) {
                    return &this->TPs[i];
                }
            }
        }
        
        return NULL;
    }
    
    

    ERESULT             tp_MessageReceived(
        J1939CA_DATA	*this,
        uint32_t        eid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        bool            fRc;
        uint8_t         da;
        uint8_t         sa;
        const
        J1939CA_PGN_ENTRY *pCurEntry;
        const
        J1939CA_PGN_ENTRY *(*pCurIndex);
        
        if ((NULL == pData) || (0 == cData)) {
            return ERESULT_INVALID_PARAMETER;
        }
        
        // Break down the PDU.
        pdu.eid = eid;
        da = j1939pdu_getDA(pdu);
        sa = pdu.SA;
        pgn = j1939pdu_getPGN(pdu);
        //this->curPgn = j1939pdu_getPGN(pdu);
        //this->curDa = j1939pdu_getDA(pdu);
        //this->curSa = pdu.SA;
        
        // Search the dynamic pgn list.
        if( this->pRcvPgnTbl ) {
            pCurIndex = (const J1939CA_PGN_ENTRY *(*))this->pRcvPgnTbl->pPGNs;
            while ( (pCurEntry = *pCurIndex++) ) {
                if (pgn.w == pCurEntry->pDef->pgn ) {
                    fRc = (pCurEntry->pDataMsg)( this, pdu.eid, cData, pData);
                    return ERESULT_SUCCESS;
                }
            }
        }
        
        // Search our static pgn list.
        pCurIndex = (const J1939CA_PGN_ENTRY *(*))rcvPgnTbl.pPGNs;
        while ( (pCurEntry = *pCurIndex++) ) {
            if (pgn.w == pCurEntry->pDef->pgn ) {
                fRc = (pCurEntry->pDataMsg)( this, pdu.eid, cData, pData);
                return ERESULT_SUCCESS;
            }
        }
        
        // Find an entry for the appropriate msg.
        
        return ERESULT_GENERAL_FAILURE;
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
        J1939CA_DATA   *this;
        
        // Do initialization.
        
        this = obj_Alloc( sizeof(J1939CA_DATA) );
        
        // Return to caller.
        return this;
    }
    
    
        
    J1939CA_DATA *	j1939ca_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939CA_DATA   *this;
        
        // Do initialization.
        
        this = j1939ca_Alloc( );
        if (this) {
            this = j1939ca_New(pCAN, pSYS, spn2837, spn2838, spn2846);
        }
        
        // Return to caller.
        return this;
    }

    
    
    
    
    
    //===============================================================
    //                      *** Properties ***
    //===============================================================

    //---------------------------------------------------------------
    //                          C A N
    //---------------------------------------------------------------
    
    OBJ_ID          j1939ca_getCAN(
        J1939CA_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pCAN;
    }
    
    
    bool            j1939ca_setCAN(
        J1939CA_DATA	*this,
        OBJ_ID          pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);         // This is our object.
        if (this->pCAN) {
            obj_Release(this->pCAN);
        }
        this->pCAN = pValue;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  C l a i m e d  A d d r e s s
    //---------------------------------------------------------------
    
    uint8_t         j1939ca_getClaimedAddress(
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
      
        return this->ca;
    }

    
    bool			j1939ca_setClaimedAddress(
        J1939CA_DATA	*this,
        uint8_t         value
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
        
        this->ca = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H a n d l e r
    //---------------------------------------------------------------
    
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
    
    
    
    ERESULT         j1939ca_getLastError(
        J1939CA_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            j1939ca_setLastError(
        J1939CA_DATA    *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                            N a m e
    //---------------------------------------------------------------
    
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
    //                  S o f t w a r e  L e v e l
    //---------------------------------------------------------------
    
    uint32_t        j1939ca_getSoftwareLevel(
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
        
        return this->softwareLevel;
    }
    
    
    bool			j1939ca_setSoftwareLevel(
        J1939CA_DATA	*this,
        uint32_t        value
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
        
        this->softwareLevel = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S Y S
    //---------------------------------------------------------------
    
    OBJ_ID          j1939ca_getSYS(
        J1939CA_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pSYS;
    }
    
    
    bool            j1939ca_setSYS(
        J1939CA_DATA	*this,
        OBJ_ID          pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);         // This is our object.
        if (this->pSYS) {
            obj_Release(this->pSYS);
        }
        this->pSYS = pValue;
        
        // Return to caller.
        return true;
    }
    
    
    
    bool            j1939ca_getTimedTransmits(
        J1939CA_DATA	*this
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
    
        return this->fTimedTransmit ? true : false;
    }

    
    bool            j1939ca_setTimedTransmits(
        J1939CA_DATA	*this,
        bool            value
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
        
        if (value) {
            this->fTimedTransmit = true;
        }
        else {
            this->fTimedTransmit = false;
        }
        
        return true;
    }
    
    
    bool			j1939ca_setXmtMsgDL(
        J1939CA_DATA	*this,
        P_J1939_XMTRTN  pXmtMsg,
        void            *pData
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
        
        this->pXmtMsgDL  = pXmtMsg;
        this->pXmtDataDL = pData;
        
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
        J1939CA_DATA	*this = objId;
        int             i;
        
        // Do initialization.
        if( NULL == this ) {
            return;
        }
        
        for (i=0; i<j1989_CA_TP_SIZE; ++i) {
            obj_Release(&this->TPs[i]);
            memset(&this->TPs[i], '\0', sizeof(J1939TP_DATA));
        }
        
        if (this->pDelayTable) {
            obj_Release(this->pDelayTable);
            this->pDelayTable = OBJ_NIL;
        }
        
        if (this->pCAN) {
            obj_Release(this->pCAN);
            this->pCAN = OBJ_NIL;
        }
        
        if (this->pSYS) {
            obj_Release(this->pSYS);
            this->pSYS = OBJ_NIL;
        }
        
        obj_Dealloc(this);
        this = NULL;
        
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

        // Search our static pgn list.
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
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Search the dynamic pgn list.
        if( this->pXmtPgnTbl ) {
            pCurIndex = (const J1939CA_PGN_ENTRY *(*))this->pXmtPgnTbl->pPGNs;
            while ( (pCurEntry = *pCurIndex++) ) {
                if (pgn.w == pCurEntry->pDef->pgn ) {
                    this->pCurEntry = pCurEntry;
                    return true;
                }
            }
        }
        
        // Search our static pgn list.
        pCurIndex = (const J1939CA_PGN_ENTRY *(*))xmtPgnTbl.pPGNs;
        while ( (pCurEntry = *pCurIndex++) ) {
            if (pgn.w == pCurEntry->pDef->pgn ) {
                this->pCurEntry = pCurEntry;
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
        int             i;
        
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
            pdu = j1939msg_getPDU(pMsg);
            this->curPgn = j1939pdu_getPGN(pdu);
            this->curDa = j1939pdu_getDA(pdu);
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
            // Address claim procedure is necessary.
            fRc = j1939ca_HandlePgn60928( this, pdu.eid, pMsg );
        }
        
        if (!this->fUseTask) {
            j1939ca_XmtDelayedMsgs(this);
        }
        
        for (i=0; i<j1989_CA_TP_SIZE; ++i) {
            if (this->TPs[i].activity == J1939TP_INACTIVE) {
            }
            else {
                j1939tp_HandleMessages(&this->TPs[i], 0, NULL);
            }
        }
        
        // Return to caller.
        return fRc;
    }

    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 51456    0x00C900              RQST2
    //---------------------------------------------------------------
    
    // Used to request a Parameter Group from a network device or devices.
    // First 3 bytes of data are the PGN being requested.
    
    bool            j1939ca_HandlePgn51456(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       spn2574;    // Requested PGN
        uint8_t         spn2575;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        
        // Get the PGN requested.
        spn2574.w = 0;
        spn2574.pgn0 = pMsg->DATA.bytes[0];
        spn2574.pgn1 = pMsg->DATA.bytes[1];
        spn2574.pgn2 = pMsg->DATA.bytes[2];
        spn2575 = pMsg->DATA.bytes[3] & 0b11;
        
        if (0x0000EA00 == spn2574.w) {
            // We should never be requesting a request!
            return false;
        }
        
        fRc = j1939ca_FindXmtPgnEntry(this, spn2574);
        if (fRc) {
            fRc = j1939ca_TransmitPgn(this, this->pCurEntry);
        }
        else {
            if ((spn2574.PF < 240) && !(255 == this->curDa)) {
                fRc = j1939ca_TransmitPgn59392(this, 1, 0, 0xFF, spn2574);
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 59392    0x00E800
    //---------------------------------------------------------------
    
    // ACK/NAK Message
    
    bool            j1939ca_HandlePgn59392(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        uint8_t         spn2541;    // Control Byte (ACKM - 8 bits)
        
        // ACK
        uint8_t         spn2542;    // Group Function Value (ACK - 8 bits)
        uint8_t         spn3290;    // Address Acknowledged (ADD_ACK - 8 bits)
        uint32_t        spn2543;    // PGN (ACK - 24 bits)

#ifdef FOR_INFORMATION_PURPOSES
        // NACK
        uint8_t         spn2544;    // Group Function Value (NACK - 8 bits)
        uint8_t         spn3291;    // Address Negative Acknowlegement (ADD_NAK - 8 bits)
        uint32_t        spn2545;    // PGN (NACK - 24 bits)
        
        // Access Denied
        uint8_t         spn2546;    // Group Function Value (NACK_AD - 8 bits)
        uint8_t         spn3292;    // Address Negative Acknowlegement (ADD_AD - 8 bits)
        uint32_t        spn2547;    // PGN (NACK_AD - 24 bits)
        
        // Busy
        uint8_t         spn2548;    // Group Function Value (NACK_BUSY - 8 bits)
        uint8_t         spn3293;    // Address Negative Acknowlegement (ADD_BUSY - 8 bits)
        uint32_t        spn2549;    // PGN (NACK_BUSY - 24 bits)
#endif
        
        
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
     
        spn2541 = pMsg->DATA.bytes[0];
        spn2542 = pMsg->DATA.bytes[1];
        spn3290 = pMsg->DATA.bytes[4];
        spn2543 = pMsg->DATA.bytes[5];
        spn2543 |= pMsg->DATA.bytes[6] << 8;
        spn2543 |= pMsg->DATA.bytes[7] << 16;
        pgn.w = spn2543;
        
        switch (spn2541) {
            case 0:                 // ACK
                if (((J1939CA_VTBL *)obj_getVtbl(this))->pHandleACK) {
                    ((J1939CA_VTBL *)obj_getVtbl(this))->pHandleACK(
                                                                    this,
                                                                    spn2542,
                                                                    spn3290,
                                                                    pgn
                    );
                }
                break;
                
            case 1:                 // NAK
                if (((J1939CA_VTBL *)obj_getVtbl(this))->pHandleNAK) {
                    ((J1939CA_VTBL *)obj_getVtbl(this))->pHandleNAK(
                                                                    this,
                                                                    spn2542,
                                                                    spn3290,
                                                                    pgn
                    );
                }
                break;
                
            case 2:                 // Access Denied (PGN supported but security
                //                  //                  denied access)
                if (((J1939CA_VTBL *)obj_getVtbl(this))->pHandleDenied) {
                    ((J1939CA_VTBL *)obj_getVtbl(this))->pHandleDenied(
                                                                       this,
                                                                       spn2542,
                                                                       spn3290,
                                                                       pgn
                    );
                }
                break;
                
            case 3:                 // Can not Respond (PGN supported but ECU is
                //                  //               busy and cannot respond now.
                //                  //              Re-request the data at a later time.)
                if (((J1939CA_VTBL *)obj_getVtbl(this))->pHandleBusy) {
                    ((J1939CA_VTBL *)obj_getVtbl(this))->pHandleBusy(
                                                                     this,
                                                                     spn2542,
                                                                     spn3290,
                                                                     pgn
                    );
                }
                break;
                
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 59904    0x00EA00              RQST
    //---------------------------------------------------------------
    
    // Used to request a Parameter Group from a network device or devices.
    // First 3 bytes of data are the PGN being requested.
    
    bool            j1939ca_HandlePgn59904(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       spn2540;    // Requested PGN
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        
        // Get the PGN requested.
        spn2540.w = 0;
        spn2540.pgn0 = pMsg->DATA.bytes[0];
        spn2540.pgn1 = pMsg->DATA.bytes[1];
        spn2540.pgn2 = pMsg->DATA.bytes[2];
        
        if (0x0000EA00 == spn2540.w) {
            // We should never be requesting a request!
            return false;
        }
        
        fRc = j1939ca_FindXmtPgnEntry(this, spn2540);
        if (fRc) {
            fRc = j1939ca_TransmitPgn(this, this->pCurEntry);
        }
        else {
            if ((spn2540.PF < 240) && !(255 == this->curDa)) {
                fRc = j1939ca_TransmitPgn59392(this, 1, 0, 0xFF, spn2540);
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 60160    0x00EB00              TP.DT
    //---------------------------------------------------------------
    
    // Transport Protocal - Data Transfer - TP.DT
    
    bool            j1939ca_HandlePgn60160(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        //bool            fRc;
        uint8_t         spn2572;    // Sequence Number (TP.DT)
        uint8_t         *pSpn2573;
        J1939TP_DATA    *pTP;
        uint8_t         da;         // Msg dest adr
        uint8_t         sa;         // Msg src adr
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        sa = j1939pdu_getSA(pdu);
        da = j1939pdu_getDA(pdu);
        
        spn2572 = pMsg->DATA.bytes[0];
        pSpn2573 = &pMsg->DATA.bytes[1];
        
        pTP = tp_Find(this, J1939TP_ACTIVE_RCV_BAM, sa);
        if (pTP) {
            ;
        }
        else {
            // Ignore the message.
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 60416    0x00EC00              TP.CM
    //---------------------------------------------------------------
    
    // Transport Protocol/Connection Management (TP.CM)
    bool            j1939ca_HandlePgn60416(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        bool            fRc;
        uint8_t         spn2556;    // Control Byte (TP.CM)
        ERESULT         eRc;
        J1939TP_DATA    *pTP;
        uint8_t         da;         // Msg dest adr
        uint8_t         sa;         // Msg src adr

        // RTS (16)
        uint16_t        spn2557;    // Total Message Size (TP.CM_RTS)
        uint8_t         spn2558;    // Total Number of Packets (TP.CM_RTS)
        uint8_t         spn2559;    // Maximum Number of Packets (TP.CM_RTS)
        J1939_PGN       spn2560;    // Parameter Group Number of packeted message (TP.CM_RTS)
        
        // CTS (17)
        uint8_t         spn2561;    // Number of Packets that can be sent (TP.CM_CTS)
        uint8_t         spn2562;    // Next Packet Number to be sent (TP.CM_RTS)
        J1939_PGN       spn2563;    // Parameter Group Number of packeted message (TP.CM_CTS)
        
        // End of Message ACK
        uint16_t        spn2564;    // Total Message Size (TP.CM_ACK)
        uint8_t         spn2565;    // Total Number of Packets (TP.CM_ACK)
        J1939_PGN       spn2566;    // Parameter Group Number of packeted message (TP.CM_ACK)
        
        // Connection Abort
        uint8_t         spn2570;    // Connection Abort Reason (TP.Conn_Abort)
        J1939_PGN       spn2571;    // Parameter Group Number of packeted message (TP.Conn_Abort)
        
        // BAM
        uint16_t        spn2567;    // Total Message Size (TP.CM_BAM)
        uint8_t         spn2568;    // Total Number of Packets (TP.CM_BAM)
        J1939_PGN       spn2569;    // Parameter Group Number of packeted message (TP.CM_BAM)
        
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        sa = j1939pdu_getSA(pdu);
        da = j1939pdu_getDA(pdu);
        spn2556 = pMsg->DATA.bytes[0];
        
        // Handle the message.
        switch (spn2556) {
            case 16:                    // TP.CM_RTS
                spn2557  = pMsg->DATA.bytes[1];
                spn2557 |= pMsg->DATA.bytes[2] << 8;
                spn2558  = pMsg->DATA.bytes[3];
                spn2559  = pMsg->DATA.bytes[4];
                spn2560.w = 0;
                spn2560.pgn0 = pMsg->DATA.bytes[5];
                spn2560.pgn1 = pMsg->DATA.bytes[6];
                spn2560.pgn2 = pMsg->DATA.bytes[7];
                break;
                
            case 17:                    // TP.CM_CTS
                spn2561  = pMsg->DATA.bytes[1];
                spn2562  = pMsg->DATA.bytes[2];
                spn2563.w = 0;
                spn2563.pgn0 = pMsg->DATA.bytes[5];
                spn2563.pgn1 = pMsg->DATA.bytes[6];
                spn2563.pgn2 = pMsg->DATA.bytes[7];
                break;
                
            case 19:                    // TP.CM_EndOfMsgACK
                spn2564  = pMsg->DATA.bytes[1];
                spn2564 |= pMsg->DATA.bytes[2] << 8;
                spn2565  = pMsg->DATA.bytes[3];
                spn2566.w = 0;
                spn2566.pgn0 = pMsg->DATA.bytes[5];
                spn2566.pgn1 = pMsg->DATA.bytes[6];
                spn2566.pgn2 = pMsg->DATA.bytes[7];
                break;
                
            case 32:                    // TP.CM_BAM
                spn2567  = pMsg->DATA.bytes[1];
                spn2567 |= pMsg->DATA.bytes[2] << 8;
                spn2568  = pMsg->DATA.bytes[3];
                spn2569.w = 0;
                spn2569.pgn0 = pMsg->DATA.bytes[5];
                spn2569.pgn1 = pMsg->DATA.bytes[6];
                spn2569.pgn2 = pMsg->DATA.bytes[7];
                //FIXME: ??da = j1939pdu_getDA(pdu);
                pTP = tp_Find(this, J1939TP_INACTIVE, 0);
                if (pTP) {
                    eRc =j1939tp_MessageReceiveBAM(pTP, da, spn2569, spn2567, spn2568);
                    if (ERESULT_FAILED(eRc)) {
                        fRc = false;
                    }
                    else {
                        fRc = true;
                    }
                }
                else {
                    DEBUG_BREAK();
                    return false;
                }
                break;
                
            case 255:                   // TP.Conn_Abort
                spn2570 = pMsg->DATA.bytes[1];
                spn2571.w = 0;
                spn2571.pgn0 = pMsg->DATA.bytes[5];
                spn2571.pgn1 = pMsg->DATA.bytes[6];
                spn2571.pgn2 = pMsg->DATA.bytes[7];
                break;
                
            default:
                break;
        }

/***
        fRc = j1939ca_FindXmtPgnEntry(this, spn2540);
        if (fRc) {
            fRc = j1939ca_TransmitPgn(this, this->pCurEntry);
        }
        else {
            if ((spn2540.PF < 240) && !(255 == this->curDa)) {
                fRc = j1939ca_TransmitPgn59392(this, 1, 0, 0xFF, spn2540);
            }
        }
 ***/
        
        // Return to caller.
        return true;
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
            pgn = j1939msg_getPGN(pMsg);
            pdu = j1939msg_getPDU(pMsg);
        }
        
        switch (this->cs) {
                
            case J1939CA_STATE_START:
                goto claimAddress;
                break;
                
            case J1939CA_STATE_SEND_CLAIM_ADDRESS:
    claimAddress:
                // Send Claim Address msg.
                fRc = j1939ca_TransmitPgn60928(this);
                if (this->pSYS && ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS) {
                    this->startTime = ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS(this->pSYS);
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
                    if (this->pSYS && ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS) {
                        msTime = ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS(this->pSYS);
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
                            if (this->pSYS && ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS) {
                                msTime = ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS(this->pSYS);
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
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 65242    0x00FEDA               SOFT
    //---------------------------------------------------------------
    
    // Software Identification
    
    bool            j1939ca_HandlePgn65242(
        J1939CA_DATA	*this,
        uint32_t        eid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       spn2540;    // Requested PGN
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        
        // Get the PGN requested.
        spn2540.w = 0;
        //FIXME: spn2540.pgn0 = pMsg->DATA.bytes[0];
        //FIXME: spn2540.pgn1 = pMsg->DATA.bytes[1];
        //FIXME: spn2540.pgn2 = pMsg->DATA.bytes[2];
        
        if (0x0000EA00 == spn2540.w) {
            // We should never be requesting a request!
            return false;
        }
        
        fRc = j1939ca_FindXmtPgnEntry(this, spn2540);
        if (fRc) {
            fRc = j1939ca_TransmitPgn(this, this->pCurEntry);
        }
        else {
            if ((spn2540.PF < 240) && !(255 == this->curDa)) {
                fRc = j1939ca_TransmitPgn59392(this, 1, 0, 0xFF, spn2540);
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939CA_DATA *	j1939ca_Init(
        J1939CA_DATA    *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint16_t		cbSize = sizeof(J1939CA_DATA);
        int             i;
        J1939TP_DATA    *pTP;

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_J1939CA );
        if (NULL == this) {
            return NULL;
        }
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939ca_Vtbl);
        
        this->cs = J1939CA_STATE_START;
        this->pHandler = (P_SRVCMSG_RTN)j1939ca_HandleMessages;
        this->fTimedTransmit = true;
        j1939ca_setCAN(this, pCAN);
        j1939ca_setSYS(this, pSYS);
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
        
        this->tpMsgDelay = 100;
        this->tpTh = 500;
        this->tpTr = 200;
        this->tpT1 = 750;
        this->tpT2 = 1250;
        this->tpT3 = 1250;
        this->tpT4 = 1050;
        
        for (i=0; i<j1989_CA_TP_SIZE; ++i) {
            pTP = j1939tp_Init(&this->TPs[i], pCAN, pSYS, 0);
            j1939tp_setRcvdMsg(pTP, (void *)tp_MessageReceived, this);
        }
        
        uint32_t            blkNum = 64;
        blkNum = table_FindBlockSize(4096, sizeof(struct j1939_msg_s));
        this->pDelayTable = table_Alloc( );
        this->pDelayTable = table_Init(
                                this->pDelayTable,
                                blkNum,
                                sizeof(struct j1939_msg_s),
                                true
                            );
        if (OBJ_NIL == this->pDelayTable) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
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
        
        if (this->pSYS && ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS) {
            msTime = ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS(this->pSYS);
        }
        
        // Return to caller.
        return msTime;
    }
    
    
    
    //---------------------------------------------------------------
    //               S e n d  A c c e s s  D e n i e d
    //---------------------------------------------------------------
    
    bool            j1939ca_SendAccessDenied(
        J1939CA_DATA	*this,
        uint8_t         spn2546,    // Group Function Value (NACK_AD - 8 bits)
        uint8_t         spn3292,    // Address Negative Acknowlegement (ADD_AD - 8 bits)
        J1939_PGN       spn2547     // PGN (NACK_AD - 24 bits)
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = j1939ca_TransmitPgn59392(this, 2, spn2546, spn3292, spn2547);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e n d  A C K
    //---------------------------------------------------------------
    
    bool            j1939ca_SendACK(
        J1939CA_DATA	*this,
        uint8_t         spn2542,    // Group Function Value (ACK - 8 bits)
        uint8_t         spn3290,    // Address Acknowledged (ADD_ACK - 8 bits)
        J1939_PGN       spn2543     // PGN (ACK - 24 bits)
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = j1939ca_TransmitPgn59392(this, 0, spn2542, spn3290, spn2543);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e n d  B u s y
    //---------------------------------------------------------------
    
    bool            j1939ca_SendBusy(
        J1939CA_DATA	*this,
        uint8_t         spn2548,    // Group Function Value (NACK_BUSY - 8 bits)
        uint8_t         spn3293,    // Address Negative Acknowlegement (ADD_BUSY - 8 bits)
        J1939_PGN       spn2549     // PGN (NACK_BUSY - 24 bits)
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = j1939ca_TransmitPgn59392(this, 3, spn2548, spn3293, spn2549);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e n d  N A C K
    //---------------------------------------------------------------
    
    bool            j1939ca_SendNACK(
        J1939CA_DATA	*this,
        uint8_t         spn2544,    // Group Function Value (NACK - 8 bits)
        uint8_t         spn3291,    // Address Negative Acknowlegement (ADD_NAK - 8 bits)
        J1939_PGN       spn2545     // PGN (NACK - 24 bits)
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = j1939ca_TransmitPgn59392(this, 1, spn2544, spn3291, spn2545);
        
        // Return to caller.
        return fRc;
    }
    

    
    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------
    
    bool            j1939ca_Setup(
        J1939CA_DATA	*this,
        uint8_t         ca          // Claimed Address
    )
    {
        bool            fRc;
        int             i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ca_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        j1939ca_setClaimedAddress(this, ca);
        
        for (i=0; i<j1989_CA_TP_SIZE; ++i) {
            j1939tp_setClaimedAddress(&this->TPs[i], ca);
        }
        
        // Return to caller.
        return fRc;
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
        int             lenUsed = 0;
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
            lenUsed = (*pPgnEntry->pDataSetup)(this, (uint32_t *)&pdu, dlc, pData);
        }
        
        if (this->pXmtMsgDL) {
            fRc = (*this->pXmtMsgDL)(this->pXmtDataDL, 0, pdu, lenUsed, &data);
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
            if (this->pSYS && ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS) {
                msTime = ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS(this->pSYS);
            }
            *((uint32_t *)((uint8_t *)this)+pPgnEntry->xmtTimeoutOff) = msTime;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //            T r a n s m i t  P G N 5 9 3 9 2  0x00E800
    //---------------------------------------------------------------
    
    // ACK/NAK PGN
    
    bool            j1939en_SetupPgn59392(
        J1939CA_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    )
    {
        
        if (pLen) {
            *pLen = 8;
        }
        if (pData) {
            if (cData < 8) {
                return false;
            }
            *pData  = 1;
            ++pData;    // 1
            *pData  = 0xFF;
            ++pData;    // 2
            *pData  = 0xFF;
            ++pData;    // 3
            *pData  = 0xFF;
            ++pData;    // 4
            *pData  = this->ca & 0xFF;
            ++pData;    // 5
            *pData  = pPDU->PF & 0xFF;  //FIXME:
            ++pData;    // 6
            *pData  = pPDU->PF & 0xFF;  //FIXME:
            ++pData;    // 7
            *pData  = pPDU->PF & 0xFF;  //FIXME:
        }
        else {
            return false;
        }
        
        // Return to caller.
        return true;
    }
    
    
    bool            j1939ca_TransmitPgn59392(
        J1939CA_DATA	*this,
        uint8_t         type,               // (0-ACK, 1-NAK, 2-Access Denied, 3-Busy)
        uint8_t         grpFunc,            // Group Function (Use 0xFF if not needed)
        uint8_t         addr,
        J1939_PGN       pgn                 // PGN being requested
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        uint8_t         *pData = data;
        bool            fRc = false;
        
        *pData  = type;
        ++pData;    // 1
        *pData  = grpFunc;
        ++pData;    // 2
        *pData  = 0xFF;
        ++pData;    // 3
        *pData  = 0xFF;
        ++pData;    // 4
        *pData  = this->ca & 0xFF;
        ++pData;    // 5
        *pData  = pgn.pgn0;
        ++pData;    // 6
        *pData  = pgn.pgn1;
        ++pData;    // 7
        *pData  = pgn.pgn2;
        
        pdu.PF = 232;
        if (255 == this->curDa) {
            pdu.PS = 255;
        }
        else {
            pdu.PS = this->curSa;
        }
        pdu.SA = this->ca;
        pdu.P  = 6;         // Priority
        
        if (this->pXmtMsgDL) {
            fRc = (*this->pXmtMsgDL)(this->pXmtDataDL, 0, pdu, dlc, &data);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //        T r a n s m i t  P G N 5 9 9 0 4  0x00EA00          REQ
    //---------------------------------------------------------------
    
    // Request for PGN - The message data contains the PGN being
    // requested.
    
    int             j1939ca_SetupPgn59904(
        J1939CA_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->eid = 0;
            pPDU->PF = 234;
            pPDU->PS = this->curDa;
            pPDU->SA = this->ca;
            pPDU->P  = 6;             // Priority
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn2540.pgn0;
            ++pData;    // 1
            *pData  = this->spn2540.pgn1;
            ++pData;    // 2
            *pData  = this->spn2540.pgn2;
            ++pData;    // 3
            *pData  = 0xFF;
            ++pData;    // 4
            *pData  = 0xFF;
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
            
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939ca_TransmitPgn59904(
        J1939CA_DATA	*this,
        J1939_PGN       pgn,                // PGN being requested
        uint8_t         da                  // Destination Address
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        uint32_t        i;
        bool            fRc = false;
        
        this->spn2540.w = pgn.w;
        this->curDa = da;
        i = j1939ca_SetupPgn59904(this, &pdu, dlc, data);
        
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
    //            T r a n s m i t  P G N 6 0 1 6 0  0x00EB00    TP.DT
    //---------------------------------------------------------------
    
    // Transport Protocal - Data Transfer - TP.DT
    
    int             j1939ca_SetupPgn60160(
        J1939CA_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = 234;
            pPDU->PS = this->curDa;
            pPDU->SA = this->ca;
            pPDU->P  = 6;             // Priority
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn2540.pgn0;
            ++pData;    // 1
            *pData  = this->spn2540.pgn1;
            ++pData;    // 2
            *pData  = this->spn2540.pgn2;
            ++pData;    // 3
            *pData  = 0xFF;
            ++pData;    // 4
            *pData  = 0xFF;
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
            
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939ca_TransmitPgn60160(
        J1939CA_DATA	*this,
        J1939CA_TP      *pTP
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        uint32_t        i;
        bool            fRc = false;
        int             offset;
        int             len;
        uint8_t         *pData = data;
        uint8_t         *pDataSrc;
        
        pdu.PF = 235;
        pdu.PS = pTP->adr;
        pdu.SA = this->ca;
        pdu.P  = 6;             // Priority
        
        if (pTP->seq < pTP->packets) {
        }
        else {
            return false;
        }
        
        *pData++ = pTP->seq + 1;

        offset = pTP->seq * 7;
        len = (pTP->size - offset) > 7 ? 7 : (pTP->size - offset);
        pDataSrc = &pTP->data[offset];
        if (len) {
        }
        else {
            return false;
        }
        
        for (i=0; i<len; ++i) {
            *pData++ = *pDataSrc++;
        }
        for (i=0; i<(7 - len); ++i) {
            *pData++ = 0xFF;
        }
        
        fRc = j1939ca_XmtMsgDL(this, 0, pdu, dlc, &data);
        pTP->msTime = j1939ca_MsTimeGet(this);
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 0 4 1 6  0x00EC00     TP.CM
    //---------------------------------------------------------------
    
    // Transport Protocol/Connection Management (TP.CM)
    
    int             j1939ca_SetupPgn60416(
        J1939CA_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        //J1939TP_DATA    *pTP;
        
        if (pPDU) {
            pPDU->eid = 0;
            pPDU->PF = 236;
            pPDU->PS = this->curDa;
            pPDU->SA = this->ca;
            pPDU->P  = 7;             // Priority
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            switch (this->msg60416.spn2556) {
                case 16:                    // TP.CM_RTS
                    *pData  = this->msg60416.spn2556;
                    ++pData;    // 1
                    *pData  = this->msg60416.spn2557L;
                    ++pData;    // 2
                    *pData  = this->msg60416.spn2557H;
                    ++pData;    // 3
                    *pData  = this->msg60416.spn2558;
                    ++pData;    // 4
                    *pData  = this->msg60416.spn2559;
                    ++pData;    // 5
                    *pData  = this->msg60416.spn2560.pgn0;
                    ++pData;    // 6
                    *pData  = this->msg60416.spn2560.pgn1;
                    ++pData;    // 7
                    *pData  = this->msg60416.spn2560.pgn2;
                    break;
                    
                case 17:                    // TP.CM_CTS
                    *pData  = this->msg60416.spn2556;
                    ++pData;    // 1
                    *pData  = this->msg60416.spn2561;
                    ++pData;    // 2
                    *pData  = this->msg60416.spn2562;
                    ++pData;    // 3
                    *pData  = 0xFF;
                    ++pData;    // 4
                    *pData  = 0xFF;
                    ++pData;    // 5
                    *pData  = this->msg60416.spn2563.pgn0;
                    ++pData;    // 6
                    *pData  = this->msg60416.spn2563.pgn1;
                    ++pData;    // 7
                    *pData  = this->msg60416.spn2563.pgn2;
                    break;
                    
                case 19:                    // TP.CM_EndOfMsgACK
                    *pData  = this->msg60416.spn2556;
                    ++pData;    // 1
                    *pData  = this->msg60416.spn2564L;
                    ++pData;    // 2
                    *pData  = this->msg60416.spn2564H;
                    ++pData;    // 3
                    *pData  = this->msg60416.spn2565;
                    ++pData;    // 4
                    *pData  = 0xFF;
                    ++pData;    // 5
                    *pData  = this->msg60416.spn2566.pgn0;
                    ++pData;    // 6
                    *pData  = this->msg60416.spn2566.pgn1;
                    ++pData;    // 7
                    *pData  = this->msg60416.spn2566.pgn2;
                    break;
                    
                case 32:                    // TP.CM_BAM
                    *pData  = this->msg60416.spn2556;
                    ++pData;    // 1
                    *pData  = this->msg60416.spn2567L;
                    ++pData;    // 2
                    *pData  = this->msg60416.spn2567H;
                    ++pData;    // 3
                    *pData  = this->msg60416.spn2568;
                    ++pData;    // 4
                    *pData  = 0xFF;
                    ++pData;    // 5
                    *pData  = this->msg60416.spn2569.pgn0;
                    ++pData;    // 6
                    *pData  = this->msg60416.spn2569.pgn1;
                    ++pData;    // 7
                    *pData  = this->msg60416.spn2569.pgn2;
                    break;
                    
                case 255:                   // TP.Conn_Abort
                    *pData  = this->msg60416.spn2556;
                    ++pData;    // 1
                    *pData  = this->msg60416.spn2570;
                    ++pData;    // 2
                    *pData  = 0xFF;
                    ++pData;    // 3
                    *pData  = 0xFF;
                    ++pData;    // 4
                    *pData  = 0xFF;
                    ++pData;    // 5
                    *pData  = this->msg60416.spn2571.pgn0;
                    ++pData;    // 6
                    *pData  = this->msg60416.spn2571.pgn1;
                    ++pData;    // 7
                    *pData  = this->msg60416.spn2571.pgn2;
                    break;
                    
                default:
                    return 0;
                    break;
            }
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939ca_TransmitPgn60416(
        J1939CA_DATA	*this,
        J1939_PGN       pgn,        // PGN
        uint8_t         control,    //16=RTS,17=CTS,19=ACK,32=BAM,255=ABORT
        uint16_t        size,       // Data Size
        uint8_t         opt1,       // 
        uint8_t         opt2,
        uint32_t        da
    )
    {
        uint16_t        dlc = 8;
        J1939_PDU       pdu = {0};
        uint8_t         data[8];
        bool            fRc = false;
        int             len;
        
        this->curDa = da;
        len = j1939ca_SetupPgn60416(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        if (this->pXmtMsgDL) {
            fRc = (*this->pXmtMsgDL)(this->pXmtDataDL, 0, pdu, dlc, &this->name);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 0 9 2 8  0x00EE00
    //---------------------------------------------------------------
    
    // Claim Address/Cannot Claim Address

    int             j1939ca_SetupPgn60928(
        J1939CA_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        J1939_NAME      *pName = (J1939_NAME *)pData;
        
        if (pPDU) {
            pPDU->eid = 0;
            pPDU->PF = 238;
            pPDU->PS = 255;
            pPDU->SA = this->ca;
            pPDU->P  = 7;             // Priority
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            pName->w0 = this->name.w0;
            pName->w1 = this->name.w1;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    
    bool            j1939ca_TransmitPgn60928(
        J1939CA_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        J1939_PDU       pdu = {0};
        uint8_t         data[8];
        bool            fRc = false;
        int             len;
        
        len = j1939ca_SetupPgn60928(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        if (this->pXmtMsgDL) {
            fRc = (*this->pXmtMsgDL)(this->pXmtDataDL, 0, pdu, dlc, &this->name);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //            T r a n s m i t  P G N 6 1 1 6 4  0x00EF00
    //---------------------------------------------------------------
    
    //  Proprietary A
    //  Data is manufacturer specified and is variable length
    //  (0 - 1785 bytes)
    
    bool            j1939ca_TransmitPgn61164(
        J1939CA_DATA	*this,
        uint8_t         da,                 // Destination Address
        uint16_t        cData,
        void            *pData
    )
    {
        uint16_t        dlc = 8;
        J1939_PDU       pdu = {0};
        bool            fRc;
        
        pdu.PF = 239;
        pdu.PS = da;
        pdu.SA = this->ca;
        pdu.P  = 6;             // Priority
        
        fRc = j1939ca_XmtMsgDL(this, 0, pdu, dlc, pData);
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 4 2  0x00FEDA
    //---------------------------------------------------------------
    
    // Software Identification -SOFT
    
    int             j1939ca_SetupPgn65242(
        J1939CA_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        char            *pData2 = (char *)pData + 1;
        uint32_t        len = 32;
        
        if (pPDU) {
            pPDU->eid = 0;
            pPDU->PF = 254;
            pPDU->PS = 218;
            pPDU->SA = this->ca;
            pPDU->P  = 6;             // Priority
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            dec_putInt32A(this->softwareLevel, &len, &pData2);
            *pData2++ = '*';
            *pData2++ = '\0';
            len = (uint32_t)strlen((char *)pData);
            *pData = (uint8_t)len;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return len + 1;
    }
    
    
    
    bool            j1939ca_TransmitPgn65242(
        J1939CA_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        J1939_PDU       pdu = {0};
        uint8_t         data[8];
        bool            fRc = false;
        int             len;
        
        len = j1939ca_SetupPgn65242(this, &pdu, dlc, data);
        if ((len > 0) && (len < 201)) {
        }
        else {
            return false;
        }
        
        if (this->pXmtMsgDL) {
            fRc = (*this->pXmtMsgDL)(this->pXmtDataDL, 0, pdu, dlc, &this->name);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                T r a n s m i t  M e s s a g e
    //---------------------------------------------------------------
    
    void            j1939ca_XmtDelayedMsgs(
        J1939CA_DATA	*this
    )
    {
        J1939CA_MSG     *pCurrent;
        J1939CA_MSG     *pNext;
        uint32_t        curTime = j1939ca_MsTimeGet(this);
        bool            fRc = false;
        
        table_Lock(this->pDelayTable);
        pCurrent = table_Head(this->pDelayTable);
        while (pCurrent) {
            pNext = table_Next(this->pDelayTable, pCurrent);
            if (pCurrent->msTime <= curTime) {
                if (this->pCAN && ((J1939_CAN_VTBL *)this->pCAN->pVtbl)->pXmt) {
                    fRc = (*((J1939_CAN_VTBL *)this->pCAN->pVtbl)->pXmt)(
                                                                         this->pCAN,
                                                                         0,
                                                                         &pCurrent->msg
                                                                         );
                }
                table_Delete(this->pDelayTable, pCurrent);
            }
            if (pCurrent->msTime > curTime) {
                break;
            }
            pCurrent = pNext;
        }
        table_Unlock(this->pDelayTable);
        
    }
    
    
    
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
        J1939CA_MSG     *pCurrent;
        J1939CA_MSG     *pInsert;
        J1939TP_DATA    *pTP;
        uint8_t         da;
        
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
        if( cData > 1875 ) {
            DEBUG_BREAK();
            return false;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            return false;
        }
        if (this->pCAN && (obj_getIdent(this->pCAN) == OBJ_IDENT_J1939CAN)) {
        }
        else {
            DEBUG_BREAK();
        }
#endif
        
        if (cData < 9) {
            fRc = j1939msg_ConstructMsg_E(&msg, pdu.eid, cData, pData);
            if (msDelay) {
                table_Lock(this->pDelayTable);
                
                pCurrent = table_Add(this->pDelayTable);
                if (NULL == pCurrent) {
                    table_Unlock(this->pDelayTable);
                    return false;
                }
                memmove(&pCurrent->msg, pData, sizeof(J1939_MSG));
                pCurrent->msDelay = msDelay;
                pCurrent->msTime  = j1939ca_MsTimeGet(this);
                pCurrent->msTime += msDelay;
                
                // Move the msg to the appropriate place in the queue.
                pInsert = table_Head(this->pDelayTable);
                while (!(NULL == pInsert)) {
                    if (pInsert->msTime > pCurrent->msTime) {
                        fRc = table_MoveBefore(this->pDelayTable, pInsert, pCurrent);
                        break;
                    }
                    pInsert = table_Next(this->pDelayTable, pInsert);
                }
                
                table_Unlock(this->pDelayTable);
            }
            else {
                if (this->pCAN && ((J1939_CAN_VTBL *)this->pCAN->pVtbl)->pXmt) {
                    fRc = (*((J1939_CAN_VTBL *)this->pCAN->pVtbl)->pXmt)(
                                                                this->pCAN,
                                                                msDelay,
                                                                &msg
                                                );
                }
            }
            //if (this->pXmtMsg) {
                //fRc = (*this->pXmtMsg)(this->pXmtData, msDelay, &msg);
            //}
        }
        else {
            ERESULT         eRc;
            da = j1939pdu_getDA(pdu);
            pTP = tp_Find(this, J1939TP_INACTIVE, 0);
            if (pTP) {
                eRc =j1939tp_MessageTransmit(pTP, pdu, cData, pData);
                if (ERESULT_FAILED(eRc)) {
                    fRc = false;
                }
                else {
                    fRc = true;
                }
            }
            else {
                DEBUG_BREAK();
                return false;
            }
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




