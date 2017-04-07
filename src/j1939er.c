/****************************************************************
 *              J1939 Data Link (j1939er) Support
 ****************************************************************/
/*
 * Program
 *              J1939 Data Link (j1939er) Support
 * Purpose
 *              See j1939er.h for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See j1939er.h for the history.
 * References
 *              See j1939er.h for the references.
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




#include "j1939er_internal.h"



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
        (P_SRVCMSG_RTN)j1939er_HandlePgn0,
        NULL,                // Message Data Constructor
        0
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61440_entry = {
        // PGN 61440  0x00F000 - Electronic Retarder Controller 1 - ERC1
        &pgn61440_entry,
        (P_SRVCMSG_RTN)j1939er_HandlePgn61440,
        (P_MSGDATA_RTN)j1939er_Pgn61440Setup,
        offsetof(J1939ER_DATA, startTime61440)
    };

    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        &ca_pgn0_entry,
        &ca_pgn61440_entry,
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
        &ca_pgn61440_entry,
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

    J1939ER_DATA * j1939er_Alloc(
    )
    {
        J1939ER_DATA   *this;

        // Do initialization.

        this = obj_Alloc( sizeof(J1939ER_DATA) );

        // Return to caller.
        return this;
    }




    //===============================================================
    //                      *** Properties ***
    //===============================================================




    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------

    void            j1939er_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939ER_DATA	*this = objId;

        // Do initialization.
        if( NULL == this ) {
            return;
        }

        j1939ca_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //          H a n d l e  PGN 59904    0x00EA00
    //---------------------------------------------------------------

    // Used to request a Parameter Group from a network device or devices.
    // This is called to handle requests for pgns that this object supports.
    // First 3 bytes of data are the PGN being requested.

    bool            j1939er_HandlePgn59904(
        J1939ER_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        J1939_PGN       requestPgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939er_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

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
                j1939er_TransmitPgn61440(this);
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

    bool            j1939er_HandlePgn0(
        J1939ER_DATA	*this,
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
        if( !j1939er_Validate( this ) ) {
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
            if ((2 == spn695) || (3 == spn695)) {
                this->timeOut = j1939ca_MsTimeGet((J1939CA_DATA *)this) + 150;
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
            //TODO: This doesnt account for clock rollover.
            if ( this->fActive && (this->timeOut <= j1939ca_MsTimeGet((J1939CA_DATA *)this)) ) {
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
    //     H a n d l e  P G N 6 1 4 4 0 -
    //---------------------------------------------------------------

    bool            j1939er_HandlePgn61440(
        J1939ER_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939er_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu.eid = eid;
        pgn = j1939msg_getJ1939_PGN_From_PDU(pdu);

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //           H a n d l e  T i m e d  T r a n s m i t s
    //---------------------------------------------------------------

    bool            j1939er_HandleTimedTransmits(
        J1939ER_DATA	*this
    )
    {
        uint32_t        curTime;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939er_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        curTime = j1939ca_MsTimeGet((J1939CA_DATA *)this);

        //TODO: doesnt consider clock rollover
        if ((curTime - this->startTime61440) >= 100) {
            j1939er_TransmitPgn61440(this);
        }
        if (this->fActive) {
            j1939er_HandlePgn0( this, 0, NULL );
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939ER_DATA *	j1939er_Init(
        J1939ER_DATA   *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint16_t		cbSize = sizeof(J1939ER_DATA);

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
#endif

        this =  (J1939ER_DATA *)j1939ca_Init(
                        (J1939CA_DATA *)this,
                        pCAN,
                        pSYS,
                        spn2837,
                        spn2838,
                        spn2846
                );
        if (OBJ_NIL == this) {
            return NULL;
        }
        obj_setSize(  (OBJ_ID)this, cbSize );
        obj_setIdent( (OBJ_ID)this, OBJ_IDENT_J1939ER );
        this->pCaVtbl = (void *)obj_getVtbl(this);
        obj_setVtbl(  (OBJ_ID)this, (OBJ_IUNKNOWN *)&j1939er_Vtbl );

        this->super.ca = 41;                // Engine #1 Exhaust Retarder
        //this->super.name.ECU = 0;
        this->super.name.FU = 12;
        this->super.name.FUI = 1;
        this->super.pRcvPgnTbl = &rcvPgntbl;
        this->super.pXmtPgnTbl = &xmtPgntbl;
        this->super.pTimedTransmit =
                        (P_HANDLE_TIMED_TRANSMITS)&j1939er_HandleTimedTransmits;

        // Default all SPNs to unsupported values.
        memset(
               &this->spn520,
               0xFF,
               (offsetof(J1939ER_DATA,spn1637) - offsetof(J1939ER_DATA,spn520) + 2)
        );
        this->spn520 = 125;     // Actual Retarder - Percent Torque
        this->spn571 = 1;       // Enable Retarder Brake Assist
        this->spn572 = 1;       // Enable Retarder Shift Assist
        this->spn1085 = 125;    // Intended Retarder Percent Torque
        this->spn1715 = 75;     // Maximum Torque that can be requested by the driver
        this->spn1717 = 0;      // Maximum Allowable Torque on request

#ifdef NDEBUG
#else
        BREAK_NOT_BOUNDARY4(offsetof(J1939ER_DATA,spn84));
        BREAK_NOT_BOUNDARY4(offsetof(J1939ER_DATA,timeOut));
        if( !j1939er_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
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
    bool            j1939er_Pgn61440Setup(
        J1939ER_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        bool            fRc = true;

        if (pData) {
            *pData  = 0x00;
            *pData |= cbp->spn900 & 0xF;
            *pData |= (cbp->spn571 & 0x3) << 4;
            *pData |= (cbp->spn572 & 0x3) << 6;
            ++pData;
            *pData  = cbp->spn520;
            ++pData;
            *pData  = cbp->spn1085;
            ++pData;
            *pData  = 0xF0;
            *pData |= (cbp->spn1082 & 0x3);
            *pData |= (cbp->spn1667 & 0x3) << 2;
            ++pData;
            *pData  = cbp->spn1480;
            ++pData;
            *pData  = cbp->spn1715;
            ++pData;
            *pData  = cbp->spn1716;
            ++pData;
            *pData  = cbp->spn1717;
        }

        // Return to caller.
        return fRc;
    }


    bool            j1939er_TransmitPgn61440(
        J1939ER_DATA	*this
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

        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);
        this->startTime61440 = j1939ca_MsTimeGet((J1939CA_DATA *)this);

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 4 9   0xF000
    //---------------------------------------------------------------

    // Retarder Configuration - RC -
    // Unused bits are set to 1.
    bool            j1939er_TransmitPgn65249(
        J1939ER_DATA	*this
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

        //FIXME: We need to implement 21 Data Link Layer!
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);

        this->startTime65249 = j1939ca_MsTimeGet((J1939CA_DATA *)this);

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                      Validate
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool            j1939er_Validate(
        J1939ER_DATA	*cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf( cbp, OBJ_IDENT_J1939ER ) )
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
