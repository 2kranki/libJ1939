/****************************************************************
 *          Data j1939cam (j1939cam) Support Subroutines           *
 ****************************************************************/
/*
 * Program
 *              Data j1939cam (j1939cam) Subroutines
 * Purpose
 *              See j1939cam.H for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See j1939cam.H for the history.
 * References
 *              See j1939cam.H for the references.
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
#include "j1939cam_internal.h"
#include "j1939ca_internal.h"
#include "j1939en_internal.h"
#include "j1939er_internal.h"
#include "j1939dg_internal.h"
#include "j1939tc_internal.h"


#ifdef	__cplusplus
extern	"C" {
#endif


#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    J1939CAM_CA_ENTRY      ca_tbl[] = {
        {   0,                          // Engine #1
            0,
            0,
            0,
            (OBJ_ALLOC)&j1939en_Alloc,
            (OBJ_INIT)&j1939en_Init
        },
        {  3,  3, 0, 0, NULL, NULL },   // Transmission #1
        { 11,  9, 0, 0, NULL, NULL },   // Brake System Controller
        { 15, 12, 0, 0, NULL, NULL },   // Engine Retarder #1
                                        // (Compression Braking)
        { 17, 14, 0, 0, NULL, NULL },   // Cruise Control
        { 23, 19, 0, 0, NULL, NULL },   // Instrument Cluster #1
        { 33, 26, 0, 0, NULL, NULL },   // Body Controller
        {   41,                         // Engine #1 Exhaust Retarder
            12,
             0,
             0,
             (OBJ_ALLOC)&j1939er_Alloc,
             (OBJ_INIT)&j1939er_Init
        },
        { 49, 37, 0, 0, NULL, NULL },    // Cab Controller (Primary)
        {   253,                         // OEM - Diagnostic CA
            12,
             0,
             0,
             (OBJ_ALLOC)&j1939dg_Alloc,
             (OBJ_INIT)&j1939dg_Init
        },
    };
#endif
#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    uint16_t            ca_tbl_num = sizeof(ca_tbl)/sizeof(J1939CAM_CA_ENTRY);
#endif
    
    
#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    CANMSG_EID_ENTRY     pgnEntries[] = {
        // PGN 59392  0x00E800 - ACK/NAK
        { 0x0000E800, (P_SRVCMSG_RTN)j1939cam_HandlePgn59392 },
        // PGN 59904  0x00EA00 - Request for PGN
        { 0x0000EA00, (P_SRVCMSG_RTN)j1939cam_HandlePgn59904 },
        // PGN 60928  0x00EE00 - Claim Address/Cannot Claim Address
        { 0x0000EE00, (P_SRVCMSG_RTN)j1939cam_HandlePgn60928 }
    };
#endif
    
#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    CANMSG_EID_TABLE     pgntbl = {
        sizeof(pgnEntries)/sizeof(CANMSG_EID_ENTRY),
        0,              // Reserved
        pgnEntries
    };
#endif

    
#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    uint32_t        defaultWaitTime = 10;       // 10ms
#endif
    
    
#ifdef NDEBUG
#else
    static
    bool            j1939cam_Validate(
        J1939CAM_DATA   *this
    );
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
    
    J1939CAM_DATA * j1939cam_Alloc(
    )
    {
        J1939CAM_DATA   *this;
        
        // Do initialization.
        
        this = obj_Alloc( sizeof(J1939CAM_DATA) );
        
        // Return to caller.
        return this;
    }
    
    
        
    J1939CAM_DATA * j1939cam_NewEngine(
        J1939_DATA      *pJ1939,
        P_XMTMSG_RTN    pReflectMsg,
        OBJ_ID          *pReflectData,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_ID          *pXmtData,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939CAM_DATA   *pCAM;
        J1939EN_DATA    *pEN;
#ifdef XYZZY
        J1939ER_DATA    *pER;
#endif
        
#ifdef NDEBUG
#else
        if( pJ1939 ) {
            if ( obj_IsKindOf(pJ1939, OBJ_IDENT_J1939) ) {
            }
            else {
                DEBUG_BREAK();
                return OBJ_NIL;
            }
        }
        BREAK_NULL(pXmtMsg);
#endif
        
        pCAM = j1939cam_Alloc();
        pCAM = j1939cam_Init( pCAM, pJ1939, pXmtMsg, pXmtData );
        if( OBJ_NIL == pCAM ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        j1939cam_setReflectMsg(pCAM, pReflectMsg, pReflectData);
        
        // Create the Engine #1.
        pEN = j1939en_Alloc();
        pEN =   j1939en_Init(
                           pEN,
                           pCAM,
                           j1939cam_TransmitDelayedMsg,
                           pCAM,
                           spn2837,
                           spn2838,
                           spn2846
                );
        if( OBJ_NIL == pEN ) {
            DEBUG_BREAK();
            obj_Release(pCAM);
            return OBJ_NIL;
        }
        j1939cam_AddCA(pCAM, pEN);
        obj_Release(pEN);
        pEN = OBJ_NIL;

#ifdef XYZZY
        // Create the Engine #1 Retarder.
        pER = j1939er_Alloc();
        pER = j1939er_Init( pER, pCAM, j1939cam_TransmitDelayedMsg, pCAM );
        if( OBJ_NIL == pER ) {
            DEBUG_BREAK();
            obj_Release(pCAM);
            return OBJ_NIL;
        }
        j1939cam_AddCA(pCAM, pER);
        obj_Release(pER);
        pER = OBJ_NIL;
#endif
        
        return pCAM;
    }
    
    
    
    J1939CAM_DATA * j1939cam_NewTransmission(
        J1939_DATA      *pJ1939,
        P_XMTMSG_RTN    pReflectMsg,
        OBJ_ID          *pReflectData,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_ID          *pXmtData,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939CAM_DATA   *pCAM;
        J1939TC_DATA    *pTC;
        
#ifdef NDEBUG
#else
        if( pJ1939 && (obj_IsKindOf(pJ1939, OBJ_IDENT_J1939)) ) {
        }
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NULL(pXmtMsg);
#endif
        
        pCAM = j1939cam_Alloc();
        pCAM = j1939cam_Init( pCAM, pJ1939, pXmtMsg, pXmtData );
        if( OBJ_NIL == pCAM ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        j1939cam_setReflectMsg(pCAM, pReflectMsg, pReflectData);
        
        // Create the Transmission #1.
        pTC = j1939tc_Alloc();
        pTC =   j1939tc_Init(
                             pTC,
                             pCAM,
                             j1939cam_TransmitDelayedMsg,
                             pCAM,
                             spn2837,
                             spn2838,
                             spn2846
                );
        if( OBJ_NIL == pTC ) {
            DEBUG_BREAK();
            obj_Release(pCAM);
            return OBJ_NIL;
        }
        j1939cam_AddCA(pCAM, pTC);
        obj_Release(pTC);
        pTC = OBJ_NIL;
        
        return pCAM;
    }
    
    
    
    //===============================================================
    //                      *** Properties ***
    //===============================================================

    //---------------------------------------------------------------
    //                          J 1 9 3 9
    //---------------------------------------------------------------
    
    J1939CA_DATA *  j1939cam_getCA(
        J1939CAM_DATA	*this,
        uint8_t         index
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (index < this->cCAs)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        // Return to caller.
        return( this->pCAs[index] );
    }
    
    
    
    //---------------------------------------------------------------
    //                          C A N
    //---------------------------------------------------------------
    
    J1939_CAN_VTBL * j1939cam_getCAN(
        J1939CAM_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pCAN;
    }
    
    
    bool            j1939cam_setCAN(
        J1939CAM_DATA	*this,
        J1939_CAN_VTBL  *pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
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
    
    
    
    J1939_DATA *    j1939cam_getJ1939(
        J1939CAM_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return( this->pJ1939 );
    }
    
    
    bool            j1939cam_setJ1939(
        J1939CAM_DATA	*this,
        J1939_DATA      *pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        //obj_Retain(pValue);         // We dont own this.
        this->pJ1939 = pValue;
        
        // Return to caller.
        return true;
    }
    
    
    
    uint8_t         j1939cam_getNumCAs(
        J1939CAM_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Return to caller.
        return this->cCAs;
    }
    

    
    bool			j1939cam_setReflectMsg(
        J1939CAM_DATA	*this,
        P_XMTMSG_RTN    pRoutine,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pReflectMsg  = pRoutine;
        this->pReflectData = pData;
        
        return true;
    }
    
    
    
    bool			j1939cam_setReflectMsgFlag(
        J1939CAM_DATA	*this,
        bool            value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fReflectMsg  = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S Y S
    //---------------------------------------------------------------
    
    J1939_SYS_VTBL * j1939cam_getSYS(
        J1939CAM_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pSYS;
    }
    
    
    bool            j1939cam_setSYS(
        J1939CAM_DATA	*this,
        J1939_SYS_VTBL  *pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
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
    
    
    
    bool			j1939cam_setXmtMsg(
        J1939CAM_DATA	*this,
        P_XMTMSG_RTN    pRoutine,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pXmtMsg  = pRoutine;
        this->pXmtData = pData;
        
        return true;
    }





    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //                      A d d  C A
    //---------------------------------------------------------------
    
    bool            j1939cam_AddCA(
        J1939CAM_DATA	*this,
        OBJ_ID          pCA
    )
    {
        J1939CA_DATA    *pTblCA;
        uint8_t         ca;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        ca = j1939ca_getClaimedAddress(pCA);
        
        // See if we have one already.
        for (i=0; i<this->cCAs; ++i) {
            pTblCA = this->pCAs[i];
            if (pTblCA) {
                if (pCA == pTblCA) {
                    return false;
                }
                if (j1939ca_getClaimedAddress(pTblCA) == ca) {
                    return false;
                }
            }
        }

        // Add it to the table.
        obj_Retain(pCA);
        this->pCAs[this->cCAs] = pCA;
        ++this->cCAs;

        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------

    void            j1939cam_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939CAM_DATA	*this = objId;
        uint32_t        i;
        
        // Do initialization.
        if( NULL == this ) {
            return;
        }
        
        for (i=0; i<this->cCAs; ++i) {
            if (this->pCAs[i]) {
                obj_Release(this->pCAs[i]);
                this->pCAs[i] = OBJ_NIL;
            }
        }
        this->cCAs = 0;
        
        obj_Dealloc(this);
        this = NULL;
        
        // Return to caller.
    }



    //---------------------------------------------------------------
    //                       D i s a b l e
    //---------------------------------------------------------------
    
    bool            j1939cam_Disable(
        OBJ_ID          objId
    )
    {
        J1939CAM_DATA   *this = objId;
        //bool            fRc;
        
        if (obj_IsEnabled(this))
            ;
        else {
            return true;
        }
        
        obj_Disable(this);
        
        // Return to caller.
        return true;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                       E n a b l e
    //---------------------------------------------------------------
    
    bool            j1939cam_Enable(
        OBJ_ID          objId
    )
    {
        J1939CAM_DATA   *this = objId;
        bool            fRc = false;
        
        if (obj_IsEnabled(this)) {
            return true;
        }
        
        obj_Enable(this);
        
        // Return to caller.
        return( fRc );
    }
    
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  M e s s a g e s
    //---------------------------------------------------------------

    /* HandleMessages() is passed messages from a message source such
     * as a CAN FIFO Receive Queue. This routine handles the message
     * either internally or via its responder chain.
     * Warning: This function must conform to P_SRVCMSG_RTN specs.
     */
    
    bool            j1939cam_HandleMessages(
        J1939CAM_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg           // if NULL, receive timed out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn = {0};
        uint8_t         da = 255;      // Destination Address - default general broadcast
        J1939CA_DATA    *pCA;
        uint32_t        i;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        
        // Get the PGN requested.
        if (pMsg) {
            pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);
            if (pdu.PF < 240) {
                da = pdu.PS;
            }
        }
        
        if (pMsg) {
            if (254 == da) {            /*** NULL Address ***/
                ;
            }
            else if (255 == da) {       /*** General Broadcast ***/
                for (i=0; i<this->cCAs; ++i) {
                    pCA = this->pCAs[i];
                    if (pCA) {
                        fRc = (*j1939ca_getHandler(pCA))( pCA, pdu.eid, pMsg);
                    }
                }
            }
            else {
                for (i=0; i<this->cCAs; ++i) {
                    pCA = this->pCAs[i];
                    if (pCA && (da == j1939ca_getClaimedAddress(pCA))) {
                        fRc = (*j1939ca_getHandler(pCA))( pCA, pdu.eid, pMsg);
                        return true;
                    }
                }
            }
        }
        else {
            // Broadcast the time-out to everyone.
            for (i=0; i<this->cCAs; ++i) {
                pCA = this->pCAs[i];
                if (pCA) {
                    fRc = (*j1939ca_getHandler(pCA))( pCA, 0, NULL);
                }
            }
        }
        
        // Return to caller.
        return false;
    }

    
    
    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939CAM_DATA *	j1939cam_Init(
        J1939CAM_DATA   *this,
        J1939_DATA      *pJ1939,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_ID          pXmtData
    )
    {
        uint16_t		cbSize = sizeof(J1939CAM_DATA);

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_J1939CAM );
        if (NULL == this) {
            return NULL;
        }
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939cam_Vtbl);
        
        j1939cam_setXmtMsg(this, pXmtMsg, pXmtData);
        
        this->pJ1939   = pJ1939;
        this->fReflectMsg = true;

#ifdef NDEBUG
#else
        if( !j1939cam_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        // Return to caller.
        return this;
    }



    bool            j1939cam_TransmitDelayedMsg(
        void            *pData,
        uint32_t        msDelay,
        J1939_MSG       *pMsg
    )
    {
        J1939CAM_DATA   *this = pData;
        bool            fRc = false;
        
        if( this->pReflectMsg && this->fReflectMsg) {
            fRc = (*this->pReflectMsg)(this->pReflectData,msDelay,pMsg);
            fRc = true;
        }
        if( this->pXmtMsg ) {
            fRc = (*this->pXmtMsg)(this->pXmtData,msDelay,pMsg);
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
    bool            j1939cam_Validate(
        J1939CAM_DATA	*this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_J1939CAM) )
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




