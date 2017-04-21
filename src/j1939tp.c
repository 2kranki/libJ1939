// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939tp.c
 *	Generated 04/18/2017 12:48:07
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include <j1939tp_internal.h>
#include <j1939ca_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  M s  T i m e  G e t
    //---------------------------------------------------------------
    
    static
    uint32_t        j1939tp_MsTimeGet(
        J1939TP_DATA	*this
        )
    {
        uint32_t        msTime = 0;
        
        // Do initialization.
        
        if (this->pSYS && ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS) {
            msTime = ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS(this->pSYS);
        }
        
        // Return to caller.
        return msTime;
    }
    
    
    
    static
    bool            j1939tp_XmtMsg(
        J1939TP_DATA    *this,
        J1939_MSG       *pMsg,
        uint32_t        *pTime
    )
    {
        bool            fRc = false;
        J1939CAN_VTBL   *pVtbl;
        
        if (pMsg && this->pCAN) {
            pVtbl = (J1939CAN_VTBL *)obj_getVtbl(this->pCAN);
            if (pVtbl) {
                fRc = pVtbl->pXmt(this->pCAN, 0, pMsg);
            }
        }
        if (pTime) {
            if (this->pSYS && ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS) {
                *pTime = ((J1939_SYS_VTBL *)this->pSYS->pVtbl)->pGetTimeMS(this->pSYS);
            }
        }
        
        return fRc;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939TP_DATA *     j1939tp_Alloc(
    )
    {
        J1939TP_DATA       *this;
        uint32_t        cbSize = sizeof(J1939TP_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939TP_DATA *     j1939tp_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint8_t         ca
    )
    {
        J1939TP_DATA       *this;
        
        this = j1939tp_Alloc( );
        if (this) {
            this = j1939tp_Init(this, pCAN, pSYS, ca);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          C A N
    //---------------------------------------------------------------
    
    OBJ_ID          j1939tp_getCAN(
        J1939TP_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pCAN;
    }
    
    
    bool            j1939tp_setCAN(
        J1939TP_DATA	*this,
        OBJ_ID          pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
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
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_getLastError(
        J1939TP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939tp_setLastError(
        J1939TP_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    bool                j1939tp_setRcvdMsg(
        J1939TP_DATA		*this,
        P_SRVCMSG_RTN       pRoutine,
        void                *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pMessageReceived  = (void *)pRoutine;
        this->pMsgRcvObj = pData;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S Y S
    //---------------------------------------------------------------
    
    OBJ_ID          j1939tp_getSYS(
        J1939TP_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pSYS;
    }
    
    
    bool            j1939tp_setSYS(
        J1939TP_DATA	*this,
        OBJ_ID          pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
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
    
    
    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = j1939tp__Assign(this,pOther);
     @endcode:
     @param:    this    J1939TP object pointer
     @param:    pOther  a pointer to another J1939TP object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         j1939tp_Assign(
        J1939TP_DATA		*this,
        J1939TP_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
        if( !j1939tp_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(pOther);
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939tp_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939tp_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        j1939tp      *pCopy = j1939tp_Copy(this);
     @endcode:
     @param:    this    J1939TP object pointer
     @return:   If successful, a J1939TP object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the J1939TP object.
     */
    J1939TP_DATA *     j1939tp_Copy(
        J1939TP_DATA       *this
    )
    {
        J1939TP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = j1939tp_New((OBJ_ID)this->pCAN, (OBJ_ID)this->pSYS, this->ca);
        if (pOther) {
            eRc = j1939tp_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939tp_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939TP_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939TP_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        j1939tp_setCAN(this, OBJ_NIL);
        j1939tp_setSYS(this, OBJ_NIL);
        
        if (this->pMutex) {
            obj_Release(this->pMutex);
            this->pMutex = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939tp_Disable(
        J1939TP_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939tp_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939tp_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return j1939tp_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939tp_Enable(
        J1939TP_DATA	*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return j1939tp_getLastError(this);
    }



    //---------------------------------------------------------------
    //                  H a n d l e  M e s s a g e s
    //---------------------------------------------------------------
    
    /* HandleMessages() is passed messages from a message source such
     * as a CAN FIFO Receive Queue. This routine handles the message
     * either internally or via its responder chain.
     * Warning: This function must conform to P_SRVCMSG_RTN specs.
     */
    
    bool            j1939tp_HandleMessages(
        J1939TP_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg           // if NULL, receive timed out
    )
    {
        J1939_PGN       pgn;
        J1939_PDU       pdu;
        uint8_t         da;
        uint8_t         sa;
        bool            fRc = false;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Get the PGN requested.
        if (pMsg) {
            pdu.eid = eid;
            pgn = j1939pdu_getPGN(pdu);
            da = j1939pdu_getDA(pdu);
            sa = pdu.SA;
        }
        else {
            pdu.eid = 0;
            pgn.w = 0;
            da = 255;
            sa = pdu.SA;
        }

        if (pgn.w == 60416) {
            fRc = j1939tp_HandlePgn60416(this, eid, pMsg);
        }
        
        if ((this->activity == J1939TP_ACTIVE_RCV) && (pgn.w == 60160)) {
            fRc = j1939tp_HandlePgn60160(this, eid, pMsg);
        }
        
        eRc = j1939tp_ProcessProtocol(this);
        eRc = j1939tp_ProcessPackets(this);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 60160    0x00EB00              TP.DT
    //---------------------------------------------------------------
    
    // Transport Protocal - Data Transfer - TP.DT
    
    bool            j1939tp_HandlePgn60160(
        J1939TP_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         sa;
        //bool            fRc;
        uint8_t         spn2572;    // Sequence Number (TP.DT)
        uint8_t         *pSpn2573;
        uint16_t        offset;
        uint16_t        len;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939pdu_getPGN(pdu);
        sa = j1939pdu_getSA(pdu);
        if (sa == this->adr) {
            spn2572 = pMsg->DATA.bytes[0];
            pSpn2573 = &pMsg->DATA.bytes[1];
            if (spn2572 == this->seq) {
                offset = (spn2572 - 1) * 7;
                len = (this->size - offset) > 7 ? 7 : (this->size - offset);
                memmove(this->data+offset, pSpn2573, len);
                if (this->seq == this->packets) {
                    j1939tp_ProtocolComplete(this);
                }
                ++this->seq;
            }
            else {
                j1939tp_ProtocolCancel(this, 0);     // Cancel w/o error message
            }
            this->msTime = j1939tp_MsTimeGet(this);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //          H a n d l e  PGN 60416    0x00EC00              TP.CM
    //---------------------------------------------------------------
    
    // Transport Protocol/Connection Management (TP.CM)
    bool            j1939tp_HandlePgn60416(
        J1939TP_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        ERESULT         eRc;
        J1939_PDU       pdu;
        uint8_t         da;
        uint8_t         sa;
        uint8_t         spn2556;    // Control Byte (TP.CM)
        
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
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        da = j1939pdu_getDA(pdu);
        sa = j1939pdu_getSA(pdu);
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
                if (this->activity == J1939TP_ACTIVE_XMT) {
                    if (this->state == J1939TP_STATE_WAIT_FOR_CTS) {
                        if ((spn2563.w == this->pgn.w) && (sa == this->adr)) {
                            if (spn2561) {
                                this->seq   = spn2562 - 1;
                                this->limit = spn2561;
                                this->state = J1939TP_STATE_XMT_PARTIAL;
                                this->stateProto = J1939TP_STATE_PROTO_WAIT_FOR_CTS_T3;
                                this->msTime = j1939tp_MsTimeGet(this);
                                this->msTimeProto = j1939tp_MsTimeGet(this);
                            }
                            else {   // Responder is requesting a pause.
                                this->stateProto = J1939TP_STATE_PROTO_WAIT_FOR_CTS_T4;
                                this->msTimeProto = j1939tp_MsTimeGet(this);
                            }
                        }
                    }
                }
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
                spn2567  = pMsg->DATA.bytes[1];         // Message Size
                spn2567 |= pMsg->DATA.bytes[2] << 8;
                spn2568  = pMsg->DATA.bytes[3];         // Number of Packets
                spn2569.w = 0;                          // PGN
                spn2569.pgn0 = pMsg->DATA.bytes[5];
                spn2569.pgn1 = pMsg->DATA.bytes[6];
                spn2569.pgn2 = pMsg->DATA.bytes[7];
                eRc = j1939tp_MessageReceiveBAM(this, sa, spn2569, spn2567, spn2568);
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
    //                          I n i t
    //---------------------------------------------------------------

    J1939TP_DATA *  j1939tp_Init(
        J1939TP_DATA    *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint8_t         ca
    )
    {
        uint32_t        cbSize = sizeof(J1939TP_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939TP);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939TP);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939tp_Vtbl);
        
        j1939tp_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

        j1939tp_setCAN(this, pCAN);
        j1939tp_setSYS(this, pSYS);
        this->pMutex = psxMutex_New();
        this->ca = ca;
        
        this->activity = J1939TP_INACTIVE;
        this->stateProto = J1939TP_STATE_PROTO_WAITING_FOR_WORK;
        this->state = J1939TP_STATE_UNKNOWN;
        
        this->tpMsgDelay = 100;
        this->tpTh = 500;
        this->tpTr = 200;
        this->tpT1 = 750;
        this->tpT2 = 1250;
        this->tpT3 = 1250;
        this->tpT4 = 1050;
        
    #ifdef NDEBUG
    #else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s B u s y
    //---------------------------------------------------------------
    
    bool            j1939tp_IsBusy(
        J1939TP_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->stateProto == J1939TP_STATE_PROTO_WAITING_FOR_WORK) {
            return false;
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_IsEnabled(
        J1939TP_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939tp_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939tp_getLastError(this);
        }
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939tp_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                M e s s a g e  R e c e i v e
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_MessageReceiveBAM(
        J1939TP_DATA	*this,
        uint8_t         sa,
        J1939_PGN       pgn,
        uint16_t        msgSize,
        uint8_t         cPackets
    )
    {
        //int             i;
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        if (this->stateProto == J1939TP_STATE_PROTO_WAITING_FOR_WORK) {
        }
        else {
            j1939tp_setLastError(this, ERESULT_BUSY);
            return ERESULT_BUSY;
        }
        
        this->activity = J1939TP_ACTIVE_RCV;
        
        this->pgn = pgn;
        this->adr = sa;
        this->size = msgSize;
        //memmove(this->data, pData, cData);
        this->packets = cPackets;
        this->limit = this->packets;
        this->seq = 1;
        
        this->stateProto = J1939TP_STATE_PROTO_RCV_BAM;
        //this->msTimeProto = j1939tp_MsTimeGet(this);
        this->state = J1939TP_STATE_RCV_BAM;
        this->msTime = j1939tp_MsTimeGet(this);
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                M e s s a g e  T r a n s m i t
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_MessageTransmit(
        J1939TP_DATA	*this,
        J1939_PDU       pdu,
        uint16_t        cData,
        void            *pData
    )
    {
        //int             i;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        if (this->stateProto == J1939TP_STATE_PROTO_WAITING_FOR_WORK) {
        }
        else {
            j1939tp_setLastError(this, ERESULT_BUSY);
            return ERESULT_BUSY;
        }
        
        this->activity = J1939TP_ACTIVE_XMT;
        
        this->pdu = pdu;
        this->pgn = j1939pdu_getPGN(pdu);
        this->adr = j1939pdu_getDA(pdu);
        this->size = cData;
        memmove(this->data, pData, cData);
        this->packets = (cData + 7 - 1) / 7;
        this->limit = this->packets;
        this->seq = 0;
        
        if (255 == this->adr) {
            eRc = j1939tp_TransmitBAM(this);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            this->stateProto = J1939TP_STATE_PROTO_XMT_BAM;
            this->msTimeProto = j1939tp_MsTimeGet(this);
            this->state = J1939TP_STATE_XMT_BAM;
        }
        else {
            eRc = j1939tp_TransmitRTS(this);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            this->stateProto = J1939TP_STATE_PROTO_WAIT_FOR_CTS_T3;
            this->msTimeProto = j1939tp_MsTimeGet(this);
            this->state = J1939TP_STATE_WAIT_FOR_CTS;
        }
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                 P r o c e s s  P a c k e t s
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_ProcessPackets(
        J1939TP_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        switch (this->state) {
            case J1939TP_STATE_UNKNOWN:
                break;
                
            case J1939TP_STATE_RCV_BAM:
                // Packets must be received in sequence order starting with 1
                // within the T1 time out limits until the full message is
                // received. If any error occurs, we simply give up and reset
                // this object making it available for other work.
                // Handle60160() handles each message as it is received.
                if ((j1939tp_MsTimeGet(this) - this->msTime) > this->tpT1) {
                    j1939tp_ProtocolCancel(this, 0);    // Cancel w/o error message.
                }
                break;
                
            case J1939TP_STATE_XMT_CANCEL:
                this->seq = 255;
                break;
                
            case J1939TP_STATE_WAIT_FOR_CTS:
                break;
                
            case J1939TP_STATE_XMT_BAM:
                // Time Delay for XMT allowed is 50ms to 200ms for Broadcast
                // Messages and up to 200ms for specific destinations.
                if ((this->seq >= this->packets) || (this->limit == 0)) {
                    this->state = J1939TP_STATE_XMT_PAUSE;
                    break;
                }
                if ((j1939tp_MsTimeGet(this) - this->msTime) > this->tpMsgDelay) {
                    j1939tp_TransmitPacket(this, this->seq++);
                    --this->limit;
                    if (this->seq < this->packets) {
                        this->msTime = j1939tp_MsTimeGet(this);
                    }
                    else {
                        this->state = J1939TP_STATE_UNKNOWN;
                        this->stateProto = J1939TP_STATE_PROTO_WAITING_FOR_WORK;
                    }
                }
                break;
                
            case J1939TP_STATE_XMT_PARTIAL:
                // Time Delay for XMT allowed is 50ms to 200ms for Broadcast
                // Messages and up to 200ms for specific destinations.
                if ((j1939tp_MsTimeGet(this) - this->msTime) > this->tpMsgDelay) {
                    if (this->limit && (this->seq < this->packets)) {
                        j1939tp_TransmitPacket(this, this->seq++);
                        this->msTime = j1939tp_MsTimeGet(this);
                        this->msTimeProto = j1939tp_MsTimeGet(this);
                        --this->limit;
                        if (this->limit) {
                        }
                        else {
                            this->state = J1939TP_STATE_WAIT_FOR_CTS;
                        }
                    }
                }
                break;
                
            case J1939TP_STATE_XMT_PAUSE:
                break;
                
        }
    
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                 P r o c e s s  P r o t o c o l
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_ProcessProtocol(
        J1939TP_DATA	*this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        switch (this->state) {
            case J1939TP_STATE_PROTO_UNKNOWN:
                break;
                
            case J1939TP_STATE_PROTO_RCV_BAM:
                // Do nothing. All actions will be controlled by
                // ProcessPackets.
                // BAM receipt of messages is simple. You must receive all multi-part
                // segments in order and in full for a complete message.
                break;
                
            case J1939TP_STATE_PROTO_RCV_CANCEL:
                break;
                
            case J1939TP_STATE_PROTO_RCV_COMPLETED:
                break;
                
            case J1939TP_STATE_PROTO_WAITING_FOR_WORK:
                // Do nothing for now.
                break;
                
            case J1939TP_STATE_PROTO_XMT_BAM:
                // ProcessPackets() should set this to "Waiting for work" when
                // it has completed transmitting all messages.
                // So, we do not need to do anything at this point.
                break;
                
            case J1939TP_STATE_PROTO_WAIT_FOR_CTS_T3:
                // Waiting for a CTS or End of Msg ACK
                if ((j1939tp_MsTimeGet(this) - this->msTimeProto) > this->tpT3) {
                    // OOPS, we timed out.
                    eRc = j1939tp_ProtocolCancel(this, 3);
                }
                break;
                
            case J1939TP_STATE_PROTO_WAIT_FOR_CTS_T4:
                // CTS Pause in effect
                if ((j1939tp_MsTimeGet(this) - this->msTimeProto) > this->tpT4) {
                    // OOPS, we timed out.
                    eRc = j1939tp_ProtocolCancel(this, 3);
                }
                break;
                
        }
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                 P r o t o c o l  C a n c e l
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_ProtocolCancel(
        J1939TP_DATA	*this,
        uint8_t         abortReason
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        // Send Connection Abort message.
        if (abortReason) {
            eRc = j1939tp_TransmitAbort(this, abortReason);
        }
        
        // Reset the Connection states.
        this->activity = J1939TP_INACTIVE;
        this->stateProto = J1939TP_STATE_PROTO_WAITING_FOR_WORK;
        this->state = J1939TP_STATE_UNKNOWN;
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                 P r o t o c o l  C o m p l e t e
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_ProtocolComplete(
        J1939TP_DATA	*this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        // Handle the message.
        if (this->pMessageReceived) {
            eRc = this->pMessageReceived(this->pMsgRcvObj, this->pgn.pgn, this->size, this->data);
        }
        
        // Reset the Connection states.
        this->activity = J1939TP_INACTIVE;
        this->stateProto = J1939TP_STATE_PROTO_WAITING_FOR_WORK;
        this->state = J1939TP_STATE_UNKNOWN;
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          P r o t o c o l  E n d  of  M e s s a g e
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_ProtocolEndOfMessage(
        J1939TP_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          P r o t o c o l  H a n d l e  X M T  -  C T S
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_ProcessHandleXmtCTS(
        J1939TP_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                T r a n s m i t  A b o r t
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_TransmitAbort(
        J1939TP_DATA	*this,
        uint8_t         reason
    )
    {
        J1939_PDU       pdu;
        uint8_t         *pData;
        uint8_t         data[8];
        J1939_MSG       msg;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        j1939pdu_Construct(&pdu, 236, this->adr, 7, this->ca);
        
        pData = data;
        *pData  = 255;
        ++pData;    // 1
        *pData  = reason;
        ++pData;    // 2
        *pData  = 0xFF;
        ++pData;    // 3
        *pData  = 0xFF;
        ++pData;    // 4
        *pData  = 0xFF;
        ++pData;    // 5
        *pData  = this->pgn.pgn0;
        ++pData;    // 6
        *pData  = this->pgn.pgn1;
        ++pData;    // 7
        *pData  = this->pgn.pgn2;
        
        fRc = j1939msg_ConstructMsg_E(&msg, pdu.eid, 8, data);
        if (fRc) {
            fRc = j1939tp_XmtMsg(this, &msg, &this->msTimeProto);
            if (!fRc) {
                j1939tp_setLastError(this, ERESULT_IO_ERROR);
                return ERESULT_IO_ERROR;
            }
        }
        else {
            j1939tp_setLastError(this, ERESULT_DATA_ERROR);
            return ERESULT_DATA_ERROR;
        }
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                T r a n s m i t  B A M
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_TransmitBAM(
        J1939TP_DATA	*this
    )
    {
        J1939_PDU       pdu;
        uint8_t         *pData;
        uint8_t         data[8];
        J1939_MSG       msg;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        j1939pdu_Construct(&pdu, 236, this->adr, 7, this->ca);
        
        pData = data;
        *pData  = 32;
        ++pData;    // 1
        *pData  = this->size & 0xFF;
        ++pData;    // 2
        *pData  = (this->size >> 8) & 0xFF;
        ++pData;    // 3
        *pData  = this->packets;
        ++pData;    // 4
        *pData  = 0xFF;
        ++pData;    // 5
        *pData  = this->pgn.pgn0;
        ++pData;    // 6
        *pData  = this->pgn.pgn1;
        ++pData;    // 7
        *pData  = this->pgn.pgn2;
        
        fRc = j1939msg_ConstructMsg_E(&msg, pdu.eid, 8, data);
        if (fRc) {
            fRc = j1939tp_XmtMsg(this, &msg, &this->msTimeProto);
            if (!fRc) {
                j1939tp_setLastError(this, ERESULT_IO_ERROR);
                return ERESULT_IO_ERROR;
            }
        }
        else {
            j1939tp_setLastError(this, ERESULT_DATA_ERROR);
            return ERESULT_DATA_ERROR;
        }
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                T r a n s m i t  P a c k e t
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_TransmitPacket(
        J1939TP_DATA	*this,
        uint8_t         n               // Relative to 0
    )
    {
        int             i;
        J1939_PDU       pdu;
        uint8_t         *pData;
        uint8_t         *pDataSrc;
        int             offset;
        int             len;
        uint8_t         data[8];
        J1939_MSG       msg;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
        if (n < this->packets) {
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        j1939pdu_Construct(&pdu, 235, this->adr, 7, this->ca);
        
        offset = n * 7;
        pDataSrc = this->data + offset;
        len = (this->size - offset) > 7 ? 7 : (this->size - offset);
        if (len) {
        }
        else {
            j1939tp_setLastError(this, ERESULT_DATA_MISSING);
            return ERESULT_DATA_MISSING;
        }
        
        pData = data;
        *pData++ = n + 1;
        for (i=0; i<len; ++i) {
            *pData++ = *pDataSrc++;
        }
        for (i=0; i<(7 - len); ++i) {
            *pData++ = 0xFF;
        }
        
        fRc = j1939msg_ConstructMsg_E(&msg, pdu.eid, 8, data);
        if (fRc) {
            fRc = j1939tp_XmtMsg(this, &msg, &this->msTime);
            if (!fRc) {
                j1939tp_setLastError(this, ERESULT_IO_ERROR);
                return ERESULT_IO_ERROR;
            }
        }
        else {
            j1939tp_setLastError(this, ERESULT_DATA_ERROR);
            return ERESULT_DATA_ERROR;
        }
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                T r a n s m i t  R T S
    //---------------------------------------------------------------
    
    ERESULT         j1939tp_TransmitRTS(
        J1939TP_DATA	*this
    )
    {
        J1939_PDU       pdu;
        uint8_t         *pData;
        uint8_t         data[8];
        J1939_MSG       msg;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tp_getLastError(this);
        }
#endif
        
        j1939pdu_Construct(&pdu, 236, this->adr, 7, this->ca);
        
        pData = data;
        *pData  = 16;
        ++pData;    // 1
        *pData  = this->size & 0xFF;
        ++pData;    // 2
        *pData  = (this->size >> 8) & 0xFF;
        ++pData;    // 3
        *pData  = this->packets;
        ++pData;    // 4
        *pData  = this->packets;
        ++pData;    // 5
        *pData  = this->pgn.pgn0;
        ++pData;    // 6
        *pData  = this->pgn.pgn1;
        ++pData;    // 7
        *pData  = this->pgn.pgn2;
        
        fRc = j1939msg_ConstructMsg_E(&msg, pdu.eid, 8, data);
        if (fRc) {
            fRc = j1939tp_XmtMsg(this, &msg, &this->msTimeProto);
            if (!fRc) {
                j1939tp_setLastError(this, ERESULT_IO_ERROR);
                return ERESULT_IO_ERROR;
            }
        }
        else {
            j1939tp_setLastError(this, ERESULT_DATA_ERROR);
            return ERESULT_DATA_ERROR;
        }
        
        // Return to caller.
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939tp_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939TP object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939tp_ToDebugString(
        J1939TP_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tp_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(j1939tp) stateProto=%d\n",
                     this,
                     this->stateProto
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(j1939tp)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939tp_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939tp_Validate(
        J1939TP_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939TP) )
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(J1939TP_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


