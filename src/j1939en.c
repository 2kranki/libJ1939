/****************************************************************
 *              J1939 Data Link (j1939en) Support
 ****************************************************************/
/*
 * Program
 *              J1939 Data Link (j1939en) Support
 * Purpose
 *              See j1939en.h for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See j1939en.h for the history.
 * References
 *              See j1939en.h for the references.
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




#include "j1939en_internal.h"



#ifdef	__cplusplus
extern	"C" {
#endif


    /****************************************************************
    * * * * * * * * * * * *  data definitions   * * * * * * * * * * *
    ****************************************************************/

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn0_entry = {
        // PGN 0  0x000000 - Torque/SpeedControl1 - TSC1
        &pgn0_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn0,
        NULL,                // Message Data Constructor
        0
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61442_entry = {
        // PGN 61442  0x00F002 - Electronic Transmission Controller 1 - ETC1
        &pgn61442_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn61442,
        NULL,
        0
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61443_entry = {
        // PGN 61443  0x00F003 - Electronic Engine Controller 2 - EEC2
        &pgn61443_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn61443,
        (P_MSGDATA_RTN)j1939en_SetupPgn61443,
        offsetof(J1939EN_DATA, startTime61443)
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61444_entry = {
        // PGN 61444  0x00F004 - Electronic Engine Controller 1 - EEC1
        &pgn61444_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn61444,
        (P_MSGDATA_RTN)j1939en_SetupPgn61444,
        offsetof(J1939EN_DATA, startTime61444)
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61445_entry = {
        // PGN 61445  0x00F005 - Electronic Transmission Controller 2 - ETC2
        &pgn61445_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn61445,
        NULL,
        0
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65129_entry = {
        // PGN 65129  0x00FE69 - Engine Temperature 3 - ET3
        &pgn65129_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65129,
        (P_MSGDATA_RTN)j1939en_SetupPgn65129,
        offsetof(J1939EN_DATA, startTime65129)
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65247_entry = {
        // PGN 65247  0x00FEDF - Electronic Engine Controller 3 - EEC3
        &pgn65247_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65247,
        (P_MSGDATA_RTN)j1939en_SetupPgn65247,
        offsetof(J1939EN_DATA, startTime65247)
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65262_entry = {
        // PGN 65262  0x00FEEE - Engine Temperature 1 - ET1
        &pgn65262_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65262,
        (P_MSGDATA_RTN)j1939en_SetupPgn65262,
        offsetof(J1939EN_DATA, startTime65262)
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65265_entry = {
        // PGN 65265  0x00FEF1 - Cruise Control/Vehicle Speed - CCVS
        &pgn65265_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65265,
        (P_MSGDATA_RTN)j1939en_SetupPgn65265,
        offsetof(J1939EN_DATA, startTime65265)
    };


    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        &ca_pgn0_entry,
        &ca_pgn61442_entry,
        &ca_pgn61445_entry,
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
        &ca_pgn61443_entry,
        &ca_pgn61444_entry,
        &ca_pgn65129_entry,
        &ca_pgn65247_entry,
        &ca_pgn65262_entry,
        &ca_pgn65265_entry,
        NULL
    };

    static
    const
    J1939CA_PGN_TABLE   xmtPgnTbl = {
        (sizeof(xmtPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &xmtPgnIndex
    };




    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939EN_DATA * j1939en_Alloc(
    )
    {
        J1939EN_DATA   *cbp;

        // Do initialization.

        cbp = obj_Alloc( sizeof(J1939EN_DATA) );

        // Return to caller.
        return( cbp );
    }




    //===============================================================
    //                      *** Properties ***
    //===============================================================

    bool			j1939en_setShiftExit(
        J1939EN_DATA	*this,
        P_VOIDEXIT12    pExit,
        void            *pData
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pShiftExit = pExit;
        this->pShiftData = pData;

        return true;
    }



    bool			j1939en_setSystemTimeGet(
        J1939EN_DATA	*this,
        uint32_t        (*pSystemTimeGet)()
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pSystemTimeGet = pSystemTimeGet;
        
        return true;
    }
    
    
    


    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------

    void            j1939en_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939EN_DATA	*cbp = objId;

        // Do initialization.
        if( NULL == cbp ) {
            return;
        }

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
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

    bool            j1939en_HandlePgn0(
        J1939EN_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg           // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         sa;
        uint8_t         spn518;         // Requested Torque / Torque Limit
        // offset: -125%, -125 to 125 (0 - 250)
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
        bool            fRc = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (pMsg) {
            pdu.eid = eid;
            pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);
            sa = pdu.SA;
            spn695 = pMsg->DATA.bytes[0] & 0x3;
            spn696 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
            spn897 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
            spn898 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
            spn518 = pMsg->DATA.bytes[3];

            if (this->fActive && (0 == spn695)) {      // *** Stop Retarding ***
                this->fActive = false;
                this->timeOut = 0;
                this->spn1480 = 0xFF;
                // Turn off retarder.
                fRc = true;
                goto exit00;
            }
            if ((1 == spn695) || (3 == spn695)) {
                this->timeOut = this->pSystemTimeGet() + 150;
                if (this->fActive) {
                    // Just update time
                }
                else {
                    this->fActive = true;
                    this->spn1480 = sa;
                    // Turn on retarder.
                    fRc = true;
                    goto exit00;
                }
            }
        }
        else {
            if ( this->fActive && (this->timeOut <= this->pSystemTimeGet()) ) {
                this->fActive = false;
                this->timeOut = 0;
                this->spn1480 = 255;
                // Turn off retarder.
                fRc = true;
                goto exit00;
            }
        }

        // Return to caller.
    exit00:
        return fRc;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 1 4 4 2  0xF002
    //---------------------------------------------------------------

    /* This is "Electronic Transmission Controller 1". It is a status
     * msg generated by the transmission #3 or #4 every 10ms. It gives
     * us whether the transmission is shifting or not, input rpm and
     * output rpm most importantly.
     */

    bool            j1939en_HandlePgn61442(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn522;
        uint8_t         spn560;     // Transmission Driveline Engaged
        uint8_t         spn573;     // Transmission Torque Converter Lockup Engaged
        uint8_t         spn574;     // Transmission Shift In Process
        uint8_t         spn606;
        uint8_t         spn607;
        uint8_t         spn1482;
        uint16_t        spn161;     // Transmission Input Shaft Speed
        uint16_t        spn191;     // Transmission Output Shaft Speed

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);
        // SPN 560  1.1     2bits       Transmission Driveline Engaged
        spn560 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 573  1.3     2bits       Transmission Torque Converter Lockup Engaged
        spn573 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        // SPN 574  1.5     2bits       Transmission Shift In Process
        spn574 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 191  2-3     16bits      Transmission Output Shaft Speed
        spn191 = (pMsg->DATA.bytes[2] << 8) | pMsg->DATA.bytes[1];
        // SPN 522  4       8bits       Percent Clutch Slip
        spn522 = pMsg->DATA.bytes[3];
        // SPN 606  5.1     2bits       Engine Momentary Overspeed Enable
        spn606 = pMsg->DATA.bytes[4] & 0x3;
        // SPN 607  5.3     2bits       Progressive Shift Disable
        spn607 = (pMsg->DATA.bytes[4] >> 2) & 0x3;
        // SPN 161  6-7     16bits      Transmission Input Shaft Speed
        spn161 = (pMsg->DATA.bytes[6] << 8) | pMsg->DATA.bytes[5];
        cbp->spn161 = spn161;
        cbp->spn190 = spn161;           // Make it engine speed too.
        // SPN 1482 8       8bits       Source Address of Controlling Device for
        //                              Transmission Control
        spn1482 = pMsg->DATA.bytes[7];

        switch (spn574 & 0x03) {
            case 0x00:                  // Shift is not in progress
                cbp->spn574 = 0x00;
                break;

            case 0x01:                  // Shift is in progress
#ifdef XYZZY
                if (cbp->spn574 == 0x01)
                    ;
                else {
                    cbp->fShifting = true;
                    if (cbp->pShiftExit) {
                        (*cbp->pShiftExit)(cbp->pShiftData,true);
                    }
                }
#endif
                cbp->spn574 = 0x01;
                break;

            case 0x02:                  // Error
                cbp->spn574 = 0x02;
                break;

            case 0x03:                  // Data Not Available
                cbp->spn574 = 0x03;
                break;
        }

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 1 4 4 3
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn61443(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 1 4 4 4
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn61444(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 1 4 4 5  0xF005
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn61445(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        // SPN 524  1       8bits       Transmission Selected Gear
        cbp->spn524 = pMsg->DATA.bytes[0];
        // SPN 526  2-3     16bits      Transmission Actual Gear Ratio
        // SPN 523  4       8bits       Transmission Current Gear
        cbp->spn523 = pMsg->DATA.bytes[3];
        // SPN 162  5-6     16bits      Transmission Requested Range
        // SPN 163  7-8     16bits      Transmission Current Range

        if (cbp->fShifting) {
            if (cbp->spn523 == cbp->spn524) {
                cbp->fShifting = false;
                if (cbp->pShiftExit) {
                    (*cbp->pShiftExit)(cbp->pShiftData,false);
                }
            }
        }
        else {
            // Check for Up Shift within Shift sequence
            if (cbp->spn523 < cbp->spn524) {
                cbp->fShifting = true;
                if (cbp->pShiftExit) {
                    (*cbp->pShiftExit)(cbp->pShiftData,true);
                }
            }
        }


        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 1 2 9
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn65129(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 4 7
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn65247(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 2
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn65262(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 5
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn65265(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //           H a n d l e  T i m e d  T r a n s m i t s
    //---------------------------------------------------------------

    bool            j1939en_HandleTimedTransmits(
        J1939EN_DATA	*this
    )
    {
        uint32_t        curTime;
        const
        J1939_PGN_ENTRY *pEntry = &pgn61443_entry;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        curTime = this->pSystemTimeGet();

        if (j1939ca_getTimedTransmits((J1939CA_DATA *)this)) {
            if ((curTime - this->startTime61443) >= 50) {
                pEntry = &pgn61443_entry;
                j1939en_TransmitPgn61443(this);
            }
            if ((curTime - this->startTime61444) >= 100) {
                pEntry = &pgn61444_entry;
                j1939en_TransmitPgn61444(this);
            }
            if ((curTime - this->startTime65129) >= 1000) {
                pEntry = &pgn65129_entry;
                j1939en_TransmitPgn65129(this);
            }
            if ((curTime - this->startTime65247) >= 250) {
                pEntry = &pgn65247_entry;
                j1939en_TransmitPgn65247(this);
            }
            if ((curTime - this->startTime65262) >= 1000) {
                pEntry = &pgn65262_entry;
                j1939en_TransmitPgn65262(this);
            }
            if ((curTime - this->startTime65265) >= 100) {
                pEntry = &pgn65265_entry;
                j1939en_TransmitPgn65265(this);
            }
        }
        if (this->fActive) {
            j1939en_HandlePgn0( this, 0, NULL );
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939EN_DATA *	j1939en_Init(
        J1939EN_DATA    *this,
        J1939CAM_DATA   *pCAM,
        P_XMTMSG_RTN    pXmtMsg,
        void            *pXmtData,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint16_t		cbSize = sizeof(J1939EN_DATA);

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
#endif
        BREAK_NULL(pXmtMsg);

        this =   (J1939EN_DATA *)j1939ca_Init(
                        (J1939CA_DATA *)this,
                        pXmtMsg,
                        pXmtData,
                        spn2837,        // J1939 Identity Number (21 bits)
                        spn2838,        // J1939 Manufacturer Code (11 bits)
                        spn2846         // J1939 Industry Group (3 bits)
                );
        if (NULL == this) {
            return NULL;
        }
        obj_setSize(  (OBJ_ID)this, cbSize );
        obj_setIdent( (OBJ_ID)this, OBJ_IDENT_J1939EN );
        this->pCaVtbl = (void *)obj_getVtbl(this);
        obj_setVtbl(  (OBJ_ID)this, (OBJ_IUNKNOWN *)&j1939en_Vtbl );

        this->super.cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we are the engine.
        this->super.pRcvPgnTbl = &rcvPgnTbl;
        this->super.pXmtPgnTbl = &xmtPgnTbl;
        this->super.pTimedTransmit =
                    (P_HANDLE_TIMED_TRANSMITS)&j1939en_HandleTimedTransmits;

        // Default all SPNs to unsupported values.
        memset(
               &this->spn52,
               0xFF,
               (offsetof(J1939EN_DATA,spn1637) - offsetof(J1939EN_DATA,spn52) + 2)
        );
        this->spn110  = 0x67;       // spn110 - Engine Coolant Temp - 63 C
        this->spn514  = 0x8D;       // spn514 - Nominal Friction - Percent Torque - 16%


#ifdef NDEBUG
#else
        BREAK_NOT_BOUNDARY4(offsetof(J1939EN_DATA,spn84));
        BREAK_NOT_BOUNDARY4(offsetof(J1939EN_DATA,timeOut));
        BREAK_NOT_BOUNDARY4(offsetof(J1939EN_DATA,pShiftExit));
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
#endif

        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 3   0xF003
    //---------------------------------------------------------------

    // Electronic Engine Controller 2 - EEC2 -
    // Unused bits are set to 1.
    bool            j1939en_SetupPgn61443(
        J1939EN_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pData) {
            *pData  = 0xC0;
            *pData |= cbp->spn558 & 0x3;
            *pData |= (cbp->spn559 & 0x3) << 2;
            *pData |= (cbp->spn1437 & 0x3) << 4;
            ++pData;    // 1
            *pData  = cbp->spn91;                   // Accelerator Pedal Position 1
            ++pData;    // 2
            *pData  = cbp->spn92;
            ++pData;    // 3
            *pData  = cbp->spn974;
            ++pData;    // 4
            *pData  = 0xFF;
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
        }

        // Return to caller.
        return true;
    }


    bool            j1939en_TransmitPgn61443(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        uint32_t        i;
        bool            fRc = false;

        data[0]  = 0xC0;
        data[0] |= this->spn558 & 0x3;
        data[0] |= (this->spn559 & 0x3) << 2;
        data[0] |= (this->spn1437 & 0x3) << 4;
        data[1]  = this->spn91;
        data[2]  = this->spn92;
        data[3]  = this->spn974;
        for (i=4; i<8; ++i) {
            data[i] = 0xFF;
        }

        pdu.PF = 240;
        pdu.PS = 3;
        pdu.SA = this->super.ca;
        pdu.P  = 3;             // Priority

        BREAK_NULL(this->super.pXmtMsgDL);
        fRc = (*this->super.pXmtMsgDL)(this->super.pXmtDataDL, 0, pdu, dlc, &data );
        this->startTime61443 = this->pSystemTimeGet();

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 4   0xF004
    //---------------------------------------------------------------

    // Electronic Engine Controller 1 - EEC1 -
    // Unused bits are set to 1.
    bool            j1939en_SetupPgn61444(
        J1939EN_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        // Fake the engine stuff.

        if (pData) {
            *pData  = 0xF0;
            *pData |= cbp->spn899 & 0xF;
            ++pData;    // 1
            *pData  = cbp->spn512;
            ++pData;    // 2
            *pData  = cbp->spn513;
            ++pData;    // 3
            *pData  = cbp->spn190 & 0xFF;
            ++pData;    // 4
            *pData  = (cbp->spn190 >> 8) & 0xFF;
            ++pData;    // 5
            *pData  = cbp->spn1483;
            ++pData;    // 6
            *pData  = 0xF0;
            *pData |= cbp->spn1675 & 0xF;
            ++pData;    // 7
            *pData  = cbp->spn2432;
        }

        // Return to caller.
        return true;
    }


    bool            j1939en_TransmitPgn61444(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;

        data[0]  = 0xF0;
        data[0] |= this->spn899 & 0xF;
        data[1]  = this->spn512;
        data[2]  = this->spn513;
        data[3]  = this->spn190 & 0xFF;
        data[4]  = (this->spn190 >> 8) & 0xFF;
        data[5]  = this->spn1483;
        data[6]  = 0xF0;
        data[6] |= this->spn1675 & 0xF;
        data[7]  = this->spn2432;

        pdu.PF = 240;
        pdu.PS = 4;
        pdu.SA = this->super.ca;
        pdu.P  = 3;             // Priority

        BREAK_NULL(this->super.pXmtMsgDL);
        fRc = (*this->super.pXmtMsgDL)( this->super.pXmtDataDL, 0, pdu, dlc, &data );
        this->startTime61444 = this->pSystemTimeGet();

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 1 2 9   0xFE69
    //---------------------------------------------------------------

    /* Engine Temperature 3 - ET3 -
     * Freq: 1000 ms
     * Priority: 6
     */
    bool            j1939en_SetupPgn65129(
        J1939EN_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pData) {
            *pData  = cbp->spn1636 & 0xFF;
            ++pData;    // 1
            *pData  = (cbp->spn1636 >> 8) & 0xFF;
            ++pData;    // 2
            *pData  = cbp->spn1637 & 0xFF;
            ++pData;    // 3
            *pData  = (cbp->spn1637 >> 8) & 0xFF;
            ++pData;    // 4
            *pData  = 0xFF;
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
        }

        // Return to caller.
        return true;
    }


    bool            j1939en_TransmitPgn65129(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        uint32_t        i;
        bool            fRc = false;

        data[0] = this->spn1636 & 0xFF;
        data[1] = (this->spn1636 >> 8) & 0xFF;
        data[2] = this->spn1637 & 0xFF;
        data[3] = (this->spn1637 >> 8) & 0xFF;
        for (i=4; i<8; ++i) {
            data[i] = 0xFF;
        }

        pdu.PF = 254;
        pdu.PS = 105;
        pdu.SA = this->super.ca;
        pdu.P  = 6;         // Priority

        BREAK_NULL(this->super.pXmtMsgDL);
        fRc = (*this->super.pXmtMsgDL)( this->super.pXmtDataDL, 0, pdu, dlc, &data );
        this->startTime65129 = this->pSystemTimeGet();

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 4 7   0x00FEDF
    //---------------------------------------------------------------

    /* Electronic Engine Controller 3 - EEC3 -
     * Freq: 250 ms
     * Priority: 6
     */
    bool            j1939en_SetupPgn65247(
        J1939EN_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pData) {
            // Range seems to be 15% (0x8C) to 18% (0x8F) for spn514
            *pData = 0x8D;
            //*pData  = cbp->spn514 & 0xFF;
            ++pData;    // 1
            *pData  = cbp->spn515 & 0xFF;
            ++pData;    // 2
            *pData  = (cbp->spn515 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = cbp->spn519 & 0xFF;
            ++pData;    // 4
            *pData  = cbp->spn2978;
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
        }

        // Return to caller.
        return true;
    }


    bool            j1939en_TransmitPgn65247(
        J1939EN_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        uint32_t        i;
        bool            fRc = false;

        data[0] = this->spn514 & 0xFF;
        data[1] = this->spn515 & 0xFF;
        data[2] = (this->spn515 >> 8) & 0xFF;
        data[3] = this->spn519 & 0xFF;
        data[4] = this->spn2978 & 0xFF;
        for (i=5; i<8; ++i) {
            data[i] = 0xFF;
        }

        pdu.PF = 254;
        pdu.PS = 223;
        pdu.SA = this->super.ca;
        pdu.P  = 6;         // Priority

        BREAK_NULL(this->super.pXmtMsgDL);
        fRc = (*this->super.pXmtMsgDL)(this->super.pXmtDataDL, 0, pdu, dlc, &data);
        this->startTime65247 = this->pSystemTimeGet();

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 2   0x00FEEE
    //---------------------------------------------------------------

    /* Engine Temperature 1 - ET1 -
     * Freq: 1000 ms
     * Priority: 6
     */
    bool            j1939en_SetupPgn65262(
        J1939EN_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pData) {
            *pData  = cbp->spn110 & 0xFF;
            ++pData;    // 1
            *pData  = cbp->spn174 & 0xFF;
            ++pData;    // 2
            *pData  = cbp->spn175 & 0xFF;
            ++pData;    // 3
            *pData  = (cbp->spn175 >> 8) & 0xFF;
            ++pData;    // 4
            *pData  = cbp->spn176 & 0xFF;
            ++pData;    // 5
            *pData  = (cbp->spn176 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = cbp->spn52 & 0xFF;
            ++pData;    // 7
            *pData  = cbp->spn1134 & 0xFF;
        }

        // Return to caller.
        return true;
    }


    bool            j1939en_TransmitPgn65262(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;

        data[0] = this->spn110 & 0xFF;
        data[1] = this->spn174 & 0xFF;
        data[2] = this->spn175 & 0xFF;
        data[3] = (this->spn175 >> 8) & 0xFF;
        data[4] = this->spn176 & 0xFF;
        data[5] = (this->spn176 >> 8) & 0xFF;
        data[6] = this->spn52 & 0xFF;
        data[7] = this->spn1134 & 0xFF;

        pdu.PF = 254;
        pdu.PS = 238;
        pdu.SA = this->super.ca;
        pdu.P  = 6;         // Priority

        BREAK_NULL(this->super.pXmtMsgDL);
        fRc = (*this->super.pXmtMsgDL)(this->super.pXmtDataDL, 0, pdu, dlc, &data);
        this->startTime65262 = this->pSystemTimeGet();

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 5   0xFEF1
    //---------------------------------------------------------------

    /* Engine Temperature 3 - ET3 -
     * Freq: 1000 ms
     * Priority: 6
     */
    bool            j1939en_SetupPgn65265(
        J1939EN_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pData) {
            *pData  = 0xC0;
            *pData |= (cbp->spn69 & 0x3);
            *pData |= (cbp->spn70 & 0x3) << 2;
            *pData |= (cbp->spn1633 & 0x3) << 4;
            ++pData;    // 1
            *pData  = cbp->spn84 & 0xFF;
            ++pData;    // 2
            *pData  = (cbp->spn84 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = 0;
            *pData |= (cbp->spn595 & 0x3);
            *pData |= (cbp->spn596 & 0x3) << 2;
            *pData |= (cbp->spn597 & 0x3) << 4;
            *pData |= (cbp->spn598 & 0x3) << 6;
            ++pData;    // 4
            *pData  = 0;
            *pData |= (cbp->spn599 & 0x3);
            *pData |= (cbp->spn600 & 0x3) << 2;
            *pData |= (cbp->spn601 & 0x3) << 4;
            *pData |= (cbp->spn602 & 0x3) << 6;
            ++pData;    // 5
            *pData  = (cbp->spn86 & 0xFF);
            ++pData;    // 6
            *pData  = 0;
            *pData |= (cbp->spn976 & 0x1F);
            *pData |= (cbp->spn527 & 0x7) << 5;
            ++pData;    // 7
            *pData  = 0;
            *pData |= (cbp->spn968 & 0x3);
            *pData |= (cbp->spn967 & 0x3) << 2;
            *pData |= (cbp->spn966 & 0x3) << 4;
            *pData |= (cbp->spn1237 & 0x3) << 6;
        }

        // Return to caller.
        return true;
    }


    bool            j1939en_TransmitPgn65265(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;

        data[0]  = 0xC0;
        data[0] |= (this->spn69 & 0x3);
        data[0] |= (this->spn70 & 0x3) << 2;
        data[0] |= (this->spn1633 & 0x3) << 4;
        data[1]  = this->spn84 & 0xFF;
        data[2]  = (this->spn84 >> 8) & 0xFF;
        data[3]  = 0;
        data[3] |= (this->spn595 & 0x3);
        data[3] |= (this->spn596 & 0x3) << 2;
        data[3] |= (this->spn597 & 0x3) << 4;
        data[3] |= (this->spn598 & 0x3) << 6;
        data[4]  = 0;
        data[4] |= (this->spn599 & 0x3);
        data[4] |= (this->spn600 & 0x3) << 2;
        data[4] |= (this->spn601 & 0x3) << 4;
        data[4] |= (this->spn602 & 0x3) << 6;
        data[5]  = (this->spn86 & 0xFF);
        data[6]  = 0;
        data[6] |= (this->spn976 & 0x1F);
        data[6] |= (this->spn527 & 0x7) << 5;
        data[7]  = 0;
        data[7] |= (this->spn968 & 0x3);
        data[7] |= (this->spn967 & 0x3) << 2;
        data[7] |= (this->spn966 & 0x3) << 4;
        data[7] |= (this->spn1237 & 0x3) << 6;

        pdu.PF = 254;
        pdu.PS = 241;
        pdu.SA = this->super.ca;
        pdu.P  = 6;         // Priority

        BREAK_NULL(this->super.pXmtMsgDL);
        fRc = (*this->super.pXmtMsgDL)(this->super.pXmtDataDL, 0, pdu, dlc, &data);
        this->startTime65265 = this->pSystemTimeGet();

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                      Validate
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool            j1939en_Validate(
        J1939EN_DATA	*cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf( cbp, OBJ_IDENT_J1939EN ) )
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
