/****************************************************************
 *              J1939 Data Link (j1939tc) Support
 ****************************************************************/
/*
 * Program
 *              J1939 Data Link (j1939tc) Support
 * Purpose
 *              See j1939tc.h for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See j1939tc.h for the history.
 * References
 *              See j1939tc.h for the references.
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




#include "j1939tc_internal.h"



#ifdef	__cplusplus
extern	"C" {
#endif


    /****************************************************************
    * * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
    ****************************************************************/

#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn0_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        &pgn0_entry,
        NULL,
        (P_MSGDATA_RTN)j1939tc_Pgn0Setup
    };
#endif

#ifdef XYZZY
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn0_engine_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        &pgn0_entry,
        NULL,
        (P_MSGDATA_RTN)j1939tc_Pgn0Setup,
        offsetof(J1939TC_DATA, startTime0_10),
        0                   // Engine #1
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn0_retarder_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        &pgn0_entry,
        NULL,
        (P_MSGDATA_RTN)j1939tc_Pgn0Setup,
        offsetof(J1939TC_DATA, startTime0_50),
        41                  // Engine #1 Retarder
    };
#endif

#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn256_entry = {
        // PGN 256  0x000100 - Transmission Control 1 - TC1
        &pgn256_entry,
        (P_SRVCMSG_RTN)j1939tc_HandlePgn256,
        NULL,             // Message Data Constructor
        0
    };
#endif

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61184_entry = {
        // PGN 61184  0x00FE00 - Torque/Speed Control 1 - TSC1
        &pgn61184_entry,
        (P_SRVCMSG_RTN)j1939tc_HandlePgn61184,
        NULL,             // Message Data Constructor
        0
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61442_entry = {
        // PGN 61442  0x00F002 - Electronic Transmission Controller 1 - ETC1
        &pgn61442_entry,
        NULL,
        (P_MSGDATA_RTN)j1939tc_Pgn61442Setup,
        offsetof(J1939TC_DATA, startTime61442)
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61445_entry = {
        // PGN 61445  0x00F005 - Electronic Transmission Controller 1 - ETC1
        &pgn61445_entry,
        NULL,
        (P_MSGDATA_RTN)j1939tc_Pgn61445Setup,
        offsetof(J1939TC_DATA, startTime61445)
    };

#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65098_entry = {
        // PGN 65098  0x00FE4A - Electronic Transmission Controller 7 - ETC7
        &pgn65098_entry,
        NULL,
        (P_MSGDATA_RTN)j1939tc_Pgn65098Setup,
        offsetof(J1939TC_DATA, startTime65098)
    };
#endif

#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65226_entry = {
        // PGN 65226  0x00FECA - Active Diagnostic Trouble Codes - DM1
        &pgn65226_entry,
        NULL,
        (P_MSGDATA_RTN)j1939tc_Pgn65226Setup,
        offsetof(J1939TC_DATA, startTime65226)
    };
#endif

    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        &ca_pgn61184_entry,
        NULL
    };

    static
    const
    J1939CA_PGN_TABLE     rcvPgntbl = {
        (sizeof(rcvPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &rcvPgnIndex
    };



    static
    const
    J1939CA_PGN_ENTRY     *xmtPgnIndex[] = {
#ifdef XYZZY
        &ca_pgn0_engine_entry,
        &ca_pgn0_retarder_entry,
#endif
        &ca_pgn61442_entry,
        &ca_pgn61445_entry,
        NULL
    };

    static
    const
    J1939CA_PGN_TABLE     xmtPgntbl = {
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

    J1939TC_DATA * j1939tc_Alloc(
    )
    {
        J1939TC_DATA   *cbp;

        // Do initialization.

        cbp = obj_Alloc( sizeof(J1939TC_DATA) );

        // Return to caller.
        return( cbp );
    }




    //===============================================================
    //                      *** Properties ***
    //===============================================================

    uint32_t        j1939tc_getMask(
        J1939TC_DATA	*cbp
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }


    bool			j1939tc_setMask(
        J1939TC_DATA	*cbp,
        uint32_t        value
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //FIXME: cbp->mask = value;

        return true;
    }



    bool			j1939tc_setSystemTimeGet(
        J1939TC_DATA	*this,
        uint32_t        (*pSystemTimeGet)()
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
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

    void            j1939tc_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939TC_DATA	*cbp = objId;

        // Do initialization.
        if( NULL == cbp ) {
            return;
        }

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 2 5 6    0x000100
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

    bool            j1939tc_HandlePgn256(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg           // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         sa;
        uint8_t         spn681;         // Transmission Gear Shift Inhibit Request
        uint8_t         spn682;         // Transmission Torque Converter Lockup
                                        // Disable Request
        uint8_t         spn683;         // Disengage Driveline Request
        uint8_t         spn684;         // Requested Percent Clutch Slip
        uint8_t         spn525;         // Transmission Requested Gear
        uint8_t         spn685;         // Disengage Differential Lock Request
                                        // - Front Axle 1
        uint8_t         spn686;         // Disengage Differential Lock Request
                                        // - Front Axle 2
        uint8_t         spn687;         // Disengage Differential Lock Request
                                        // - Rear Axle 1
        uint8_t         spn688;         // Disengage Differential Lock Request
                                        // - Rear Axle 2
        uint8_t         spn689;         // Disengage Differential Lock Request
                                        // - Central
        uint8_t         spn690;         // Disengage Differential Lock Request
                                        // - Central Front
        uint8_t         spn691;         // Disengage Differential Lock Request
                                        // - Central Rear
        uint8_t         spn1852;        // Transmission Mode 1
        uint8_t         spn1853;        // Transmission Mode 2
        uint16_t        spn1854;        // Transmission Mode 3
        uint16_t        spn1855;        // Transmission Mode 4
        uint16_t        spn2985;        // Transmission Shift Selector Display Mode Switch
        bool            fRc = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (pMsg) {
            pdu.eid = eid;
            pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);
            sa = pdu.SA;
            spn681 = pMsg->DATA.bytes[0] & 0x3;
            spn682 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
            spn683 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
            spn684 = pMsg->DATA.bytes[1];
            spn525 = pMsg->DATA.bytes[2];
            spn685 = pMsg->DATA.bytes[3] & 0x3;
            spn686 = (pMsg->DATA.bytes[3] >> 2) & 0x3;
            spn687 = (pMsg->DATA.bytes[3] >> 4) & 0x3;
            spn688 = (pMsg->DATA.bytes[3] >> 6) & 0x3;
            spn689 = pMsg->DATA.bytes[4] & 0x3;
            spn690 = (pMsg->DATA.bytes[4] >> 2) & 0x3;
            spn691 = (pMsg->DATA.bytes[4] >> 4) & 0x3;
            spn1852 = pMsg->DATA.bytes[5] & 0x3;
            spn1853 = (pMsg->DATA.bytes[5] >> 2) & 0x3;
            spn1854 = (pMsg->DATA.bytes[5] >> 4) & 0x3;
            spn1855 = (pMsg->DATA.bytes[5] >> 6) & 0x3;
            spn2985 = (pMsg->DATA.bytes[6] >> 6) & 0x3;

#ifdef XYZZY
            if (cbp->fActive && (0 == spn695)) {      // *** Stop Retarding ***
                cbp->fActive = false;
                cbp->timeOut = 0;
                cbp->spn1480 = 0xFF;
                // Turn off retarder.
                fRc = true;
                goto exit00;
            }
            if ((2 == spn695) || (3 == spn695)) {
                cbp->timeOut = tn_sys_time_get() + 150;
                if (cbp->fActive) {
                    // Just update time
                }
                else {
                    cbp->fActive = true;
                    cbp->spn1480 = sa;
                    // Turn on retarder.
                    fRc = true;
                    goto exit00;
                }
            }
        }
        else {
            if ( cbp->fActive && (cbp->timeOut <= tn_sys_time_get()) ) {
                cbp->fActive = false;
                cbp->timeOut = 0;
                cbp->spn1480 = 255;
                // Turn off retarder.
                fRc = true;
                goto exit00;
            }
#endif
        }

        // Return to caller.
    exit00:
        return fRc;
    }



    //---------------------------------------------------------------
    //             H a n d l e  P G N 6 1 1 8 4    0x00EF00
    //---------------------------------------------------------------


    bool            j1939tc_HandlePgn61184(
        J1939TC_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg           // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         sa;
        uint8_t         type;           // Request Type
        uint8_t         data1;          // Misc 1 byte Data
        uint16_t        data2;          // Misc 2 byte Data
        bool            fRc = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (pMsg) {
            pdu.eid = eid;
            pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);
            sa = pdu.SA;
            type = pMsg->DATA.bytes[0];
            data1 = pMsg->DATA.bytes[1];
            data2 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);

            if (this->fActive && (0 == type)) {      // *** Stop Retarding ***
                this->fActive = false;
                this->timeOut = 0;
                this->spn1482 = 0xFF;
                // Turn off retarder.
                fRc = true;
                goto exit00;
            }
            if ((2 == type) || (3 == type)) {
                this->timeOut = this->pSystemTimeGet() + 150;
                if (this->fActive) {
                    // Just update time
                }
                else {
                    this->fActive = true;
                    this->spn1482 = sa;
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
                this->spn1482 = 255;
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
    //                  H a n d l e  P G N 6 1 4 4 0
    //---------------------------------------------------------------

    bool            j1939tc_HandlePgn61440(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate( cbp ) ) {
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

    bool            j1939tc_HandleTimedTransmits(
        J1939TC_DATA	*this
    )
    {
        uint32_t        curTime;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        curTime = this->pSystemTimeGet();

        if (j1939ca_getTimedTransmits((J1939CA_DATA *)this)) {
            if ((curTime - this->startTime61442) >= 10) {
                j1939ca_TransmitPgn(
                                (J1939CA_DATA *)this,
                                &ca_pgn61442_entry
                );
            }
            if ((curTime - this->startTime61445) >= 100) {
                j1939ca_TransmitPgn(
                                    (J1939CA_DATA *)this,
                                    &ca_pgn61445_entry
                                    );
            }
        }
        if (this->fActive) {
            j1939tc_HandlePgn61184( this, 0, NULL );
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939TC_DATA *	j1939tc_Init(
        J1939TC_DATA    *this,
        J1939CAM_DATA   *pCAM,
        P_XMTMSG_RTN    pXmtMsg,
        void            *pXmtData,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint16_t		cbSize = sizeof(J1939TC_DATA);

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
#endif
        BREAK_NULL(pXmtMsg);

        this =   (J1939TC_DATA *)j1939ca_Init(
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
        obj_setIdent( (OBJ_ID)this, OBJ_IDENT_J1939TC );
        this->pCaVtbl = (void *)obj_getVtbl(this);
        obj_setVtbl(  (OBJ_ID)this, (OBJ_IUNKNOWN *)&j1939tc_Vtbl );

        this->super.ca = 3;                  // Transmission #1
        //this->super.name.ECU = 0;
        this->super.name.FU = 3;
        this->super.name.FUI = 0;
        this->super.pRcvPgnTbl = &rcvPgntbl;
        this->super.pXmtPgnTbl = &xmtPgntbl;
        this->super.pTimedTransmit =
                        (P_HANDLE_TIMED_TRANSMITS)&j1939tc_HandleTimedTransmits;

        // Default all SPNs to unsupported values.
        memset(
               &this->spn522,
               0xFF,
               (offsetof(J1939TC_DATA,spn526) - offsetof(J1939TC_DATA,spn522) + 2)
        );

#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
        BREAK_NOT_BOUNDARY4(offsetof(J1939TC_DATA,spn161));
        BREAK_NOT_BOUNDARY4(offsetof(J1939TC_DATA,timeOut));
#endif

        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 0   0x0000
    //---------------------------------------------------------------

    // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
    bool            j1939tc_Pgn0Setup(
        J1939TC_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        bool            fRc = true;
        J1939_PDU       pdu;

        if (pData) {
            pdu.eid = *pEid;
            *pData  = 0xC0;
            *pData |= cbp->spn695 & 0x03;
            *pData |= (cbp->spn696 & 0x03) << 2;
            *pData |= (cbp->spn897 & 0x03) << 4;
            ++pData;    // 1
            *pData  = cbp->spn898 & 0xFF;
            ++pData;    // 2
            *pData  = (cbp->spn898 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = cbp->spn518;
            ++pData;    // 4
            *pData  = 0xF0;
            *pData |= (cbp->spn3349 & 0x07);
            if (pdu.PS == 41) {
                *pData |= 0x1F << 3;
            }
            else {
                *pData |= (cbp->spn3350 & 0x1F) << 3;
            }
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
        }

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 2   0xF002
    //---------------------------------------------------------------

    // Electronic Transmission Controller 1 - ETC1 -
    // Unused bits are set to 1.
    // The Transmission and the Cruise Controller are normally interested
    // in this message and try to control the Engine Retarder via the
    // TSC1 message.
    bool            j1939tc_Pgn61442Setup(
        J1939TC_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        bool            fRc = true;

        if (pData) {
            *pData  = 0xC0;
            *pData |= cbp->spn560 & 0x3;
            *pData |= (cbp->spn573 & 0x3) << 4;
            *pData |= (cbp->spn574 & 0x3) << 6;
            ++pData;    // 1
            *pData  = cbp->spn191 & 0xFF;       // Transmission Output Shaft Speed
            ++pData;    // 2
            *pData  = (cbp->spn191 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = cbp->spn522;
            ++pData;    // 4
            *pData  = 0xF0;
            *pData |= (cbp->spn606 & 0x3);      // Engine Momentary Overspeed Enable
            *pData |= (cbp->spn607 & 0x3) << 2; // Progressive Shift Disable
            ++pData;    // 5
            *pData  = cbp->spn161 & 0xFF;       // Transmission Input Shaft Speed
            ++pData;    // 6
            *pData  = (cbp->spn161 >> 8) & 0xFF;
            ++pData;    // 7
            *pData  = cbp->spn1482;             // Source Address of Controlling Device
                                                // for Transmission Control
        }

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 5   0xF005
    //---------------------------------------------------------------

    bool            j1939tc_Pgn61445Setup(
        J1939TC_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        bool            fRc = true;

        if (pData) {
            *pData  = cbp->spn524;
            ++pData;    // 1
            *pData  = cbp->spn526 & 0xFF;
            ++pData;    // 2
            *pData  = (cbp->spn526 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = cbp->spn523;
            ++pData;    // 4
            *pData  = cbp->spn162 & 0xFF;
            ++pData;    // 5
            *pData  = (cbp->spn162 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = cbp->spn163 & 0xFF;
            ++pData;    // 7
            *pData  = (cbp->spn163 >> 8) & 0xFF;
        }

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 0 9 8   0xFE4A
    //---------------------------------------------------------------

    bool            j1939tc_Pgn65098Setup(
        J1939TC_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        bool            fRc = true;

        if (pData) {
            *pData  = cbp->spn524;
            ++pData;    // 1
            *pData  = cbp->spn526 & 0xFF;
            ++pData;    // 2
            *pData  = (cbp->spn526 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = cbp->spn523;
            ++pData;    // 4
            *pData  = cbp->spn162 & 0xFF;
            ++pData;    // 5
            *pData  = (cbp->spn162 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = cbp->spn163 & 0xFF;
            ++pData;    // 7
            *pData  = (cbp->spn163 >> 8) & 0xFF;
        }

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 2 6   0xFECA
    //---------------------------------------------------------------

    bool            j1939tc_Pgn65226Setup(
        J1939TC_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        bool            fRc = true;

        if (pData) {
            *pData  = cbp->spn524;
            ++pData;    // 1
            *pData  = cbp->spn526 & 0xFF;
            ++pData;    // 2
            *pData  = (cbp->spn526 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = cbp->spn523;
            ++pData;    // 4
            *pData  = cbp->spn162 & 0xFF;
            ++pData;    // 5
            *pData  = (cbp->spn162 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = cbp->spn163 & 0xFF;
            ++pData;    // 7
            *pData  = (cbp->spn163 >> 8) & 0xFF;
        }

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 4 5   0xF005
    //---------------------------------------------------------------

    bool            j1939tc_Pgn65245Setup(
        J1939TC_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        bool            fRc = true;

        if (pData) {
            *pData  = cbp->spn524;
            ++pData;    // 1
            *pData  = cbp->spn526 & 0xFF;
            ++pData;    // 2
            *pData  = (cbp->spn526 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = cbp->spn523;
            ++pData;    // 4
            *pData  = cbp->spn162 & 0xFF;
            ++pData;    // 5
            *pData  = (cbp->spn162 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = cbp->spn163 & 0xFF;
            ++pData;    // 7
            *pData  = (cbp->spn163 >> 8) & 0xFF;
        }

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //                      Validate
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool            j1939tc_Validate(
        J1939TC_DATA	*cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf( cbp, OBJ_IDENT_J1939TC ) )
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
