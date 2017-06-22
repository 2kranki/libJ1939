/****************************************************************
 *              J1939 Transmission CA (j1939tc) Support
 ****************************************************************/
/*
 * Program
 *              J1939 Transmission CA (j1939tc) Support
 * Purpose
 *              See j1939tc.h for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          None
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

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn0_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        &pgn0_entry,
        NULL,
        NULL,
        (P_SETUP_MSG_RTN)j1939tc_SetupPgn0
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn0_engine_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        &pgn0_entry,
        NULL,
        NULL,
        (P_SETUP_MSG_RTN)j1939tc_SetupPgn0,
        offsetof(J1939TC_DATA, startTime0_10),
        0                   // Engine #1
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn0_retarder_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        &pgn0_entry,
        NULL,
        NULL,
        (P_SETUP_MSG_RTN)j1939tc_SetupPgn0,
        offsetof(J1939TC_DATA, startTime0_50),
        41,                 // Engine #1 Retarder
        0,
        50
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn256_entry = {
        // PGN 256  0x000100 - Transmission Control 1 - TC1
        &pgn256_entry,
        (P_SRVCMSG_RTN)j1939tc_HandlePgn256,
        NULL,
        NULL,             // Message Data Constructor
        0,
        0,
        50
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61184_entry = {
        // PGN 61184  0x00FE00 - Torque/Speed Control 1 - TSC1
        &pgn61184_entry,
        (P_SRVCMSG_RTN)j1939tc_HandlePgn61184,
        NULL,
        NULL,             // Message Data Constructor
        0,
        0,
        0
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61442_entry = {
        // PGN 61442  0x00F002 - Electronic Transmission Controller 1 - ETC1
        &pgn61442_entry,
        NULL,
        NULL,
        (P_SETUP_MSG_RTN)j1939tc_SetupPgn61442,
        offsetof(J1939TC_DATA, startTime61442)
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61445_entry = {
        // PGN 61445  0x00F005 - Electronic Transmission Controller 1 - ETC1
        &pgn61445_entry,
        NULL,
        NULL,
        (P_SETUP_MSG_RTN)j1939tc_SetupPgn61445,
        offsetof(J1939TC_DATA, startTime61445)
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65098_entry = {
        // PGN 65098  0x00FE4A - Electronic Transmission Controller 7 - ETC7
        &pgn65098_entry,
        NULL,
        NULL,
        (P_SETUP_MSG_RTN)j1939tc_SetupPgn65098,
        offsetof(J1939TC_DATA, startTime65098)
    };

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65226_entry = {
        // PGN 65226  0x00FECA - Active Diagnostic Trouble Codes - DM1
        &pgn65226_entry,
        NULL,
        NULL,
        (P_SETUP_MSG_RTN)j1939tc_SetupPgn65226,
        offsetof(J1939TC_DATA, startTime65226)
    };

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

#ifdef NDEBUG
#else
    static
    bool            j1939tc_Validate(
        J1939TC_DATA      *this
    );
#endif
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939TC_DATA * j1939tc_Alloc(
    )
    {
        J1939TC_DATA   *this;

        // Do initialization.

        this = obj_Alloc( sizeof(J1939TC_DATA) );

        // Return to caller.
        return this;
    }




    //===============================================================
    //                      *** Properties ***
    //===============================================================

    ERESULT         j1939tc_getLastError(
        J1939TC_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            j1939tc_setLastError(
        J1939TC_DATA    *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    uint32_t        j1939tc_getMask(
        J1939TC_DATA	*this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }


    bool			j1939tc_setMask(
        J1939TC_DATA	*this,
        uint32_t        value
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //FIXME: cbp->mask = value;

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
        J1939TC_DATA	*this = objId;

        // Do initialization.
        if( NULL == this ) {
            return;
        }

        j1939ca_Dealloc(this);
        this = NULL;

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
        J1939TC_DATA	*this,
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
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (pMsg) {
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
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
            if ( this->fActive && (this->timeOut <= j1939ca_MsTimeGet((J1939CA_DATA *)this)) ) {
                this->fActive = false;
                this->timeOut = 0;
                this->spn1480 = 255;
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
    //     H a n d l e  P G N 6 1 1 8 4    0x00EF00   Proprietary A
    //---------------------------------------------------------------


    bool            j1939tc_HandlePgn61184(
        J1939TC_DATA	*this,
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
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
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
                this->timeOut = j1939ca_MsTimeGet((J1939CA_DATA *)this) + 150;
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
            if ( this->fActive && (this->timeOut <= j1939ca_MsTimeGet((J1939CA_DATA *)this)) ) {
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
    //                  H a n d l e  P G N 6 1 4 4 0   ERC1
    //---------------------------------------------------------------

    bool            j1939tc_HandlePgn61440(
        J1939TC_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
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
    //                  H a n d l e  P G N 6 1 4 4 1   EBC1
    //---------------------------------------------------------------
    
    bool            j1939tc_HandlePgn61441(
        J1939TC_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn561;
        uint8_t         spn562;
        uint8_t         spn563;
        uint8_t         spn1121;
        uint8_t         spn521;
        uint8_t         spn575;
        uint8_t         spn576;
        uint8_t         spn577;
        uint8_t         spn1238;
        uint8_t         spn972;
        uint8_t         spn971;
        uint8_t         spn970;
        uint8_t         spn969;
        uint8_t         spn973;
        uint8_t         spn1243;
        uint8_t         spn1439;
        uint8_t         spn1438;
        uint8_t         spn1793;
        uint8_t         spn1481;
        uint8_t         spn2911;
        uint8_t         spn1836;
        uint8_t         spn1792;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 561  1.1     2bits       ASR Engine Control Active
        spn561 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 562  1.3     2bits       ASR Brake Control Active
        spn562 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        // SPN 563  1.5     2bits       Anti-Lock Braking (ABS) Active
        spn563 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 1121 1.7     2bits       EBS Brake Switch
        spn1121 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 521  2       8bits       Brake Pedal Position
        spn521 = pMsg->DATA.bytes[1];
        // SPN 575  3.1     2bits       ABS Off-road Switch
        spn575 = pMsg->DATA.bytes[2] & 0x3;
        // SPN 576  3.3     2bits       ASR Off-road Switch
        spn576 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
        // SPN 577  3.5     2bits       ASR 'Hill Holder' Switch
        spn577 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
        // SPN 1238 3.7     2bits       Traction Control Override Switch
        spn1238 = (pMsg->DATA.bytes[2] >> 6) & 0x3;
        // SPN 972  4.1     2bits       Accelerator Interlock Switch
        spn972 = pMsg->DATA.bytes[3] & 0x3;
        // SPN 971  4.3     2bits       Engine Derate Switch
        spn971 = (pMsg->DATA.bytes[3] >> 2) & 0x3;
        // SPN 970  4.5     2bits       Engine Auxiliary Shutdown Switch
        spn970 = (pMsg->DATA.bytes[3] >> 4) & 0x3;
        // SPN 969  4.7     2bits       Remote Accelerator Enable Switch
        spn969 = (pMsg->DATA.bytes[3] >> 6) & 0x3;
        // SPN 973  5       8bits       Engine Retarder Selection
        spn973 = pMsg->DATA.bytes[4];
        // SPN 1243 6.1     2bits       ABS Fully Operational
        spn1243 = pMsg->DATA.bytes[5] & 0x3;
        // SPN 1439 6.3     2bits       EBS Red Warning Signal
        spn1439 = (pMsg->DATA.bytes[5] >> 2) & 0x3;
        // SPN 1438 6.5     2bits       ABS/EBS Amber Warning Signal (Powered Vehicle)
        spn1438 = (pMsg->DATA.bytes[5] >> 4) & 0x3;
        // SPN 1793 6.7     2bits       ATC/ASR Information Signal
        spn1793 = (pMsg->DATA.bytes[5] >> 6) & 0x3;
        // SPN 1481 7       8bits       Source Address of Controlling Device for Brake Control
        spn1481 = pMsg->DATA.bytes[6];
        // SPN 2911 8.3     2bits       Halt brake switch
        spn2911 = (pMsg->DATA.bytes[7] >> 2) & 0x3;
        // SPN 1836 8.5     2bits       Trailer ABS Status
        spn1836 = (pMsg->DATA.bytes[7] >> 4) & 0x3;
        // SPN 1792 8.7     2bits       Tractor-Mounted Trailer ABS Warning Signal
        spn1792 = (pMsg->DATA.bytes[7] >> 6) & 0x3;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 0 9 8             ETC7
    //---------------------------------------------------------------
    
    bool            j1939tc_HandlePgn65098(
        J1939TC_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn1850;
        uint8_t         spn1849;
        uint8_t         spn3086;
        uint8_t         spn2945;
        uint8_t         spn2900;
        uint8_t         spn1851;
        uint8_t         spn2539;
        uint8_t         spn2538;
        uint8_t         spn2537;
        uint8_t         spn2536;
        uint8_t         spn3289;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 1850 1.5     2bits       Transmission Requested Range Display Blank State
        spn1850 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 1849 1.7     2bits       Transmission Requested Range Display Flash State
        spn1849 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 3086 2.1     2bits       Transmission Ready for Brake Release
        spn3086 = pMsg->DATA.bytes[1] & 0x3;
        // SPN 2945 2.3     2bits       Active Shift Console Indicator
        spn2945 = (pMsg->DATA.bytes[1] >> 2) & 0x3;
        // SPN 2900 2.5     2bits       Transmission Engine Crank Enable
        spn2900 = (pMsg->DATA.bytes[1] >> 4) & 0x3;
        // SPN 1851 2.7     2bits       Transmission Shift Inhibit Indicator
        spn1851 = (pMsg->DATA.bytes[1] >> 6) & 0x3;
        // SPN 2539 3.1     2bits       Transmission Mode 4 Indicator
        spn2539 = pMsg->DATA.bytes[2] & 0x3;
        // SPN 2538 3.3     2bits       Transmission Mode 3 Indicator
        spn2538 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
        // SPN 2537 3.5     2bits       Transmission Mode 2 Indicator
        spn2537 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
        // SPN 2536 3.7     2bits       Transmission Mode 1 Indicator
        spn2536 = (pMsg->DATA.bytes[2] >> 6) & 0x3;
        // SPN 3289 4       8bits       Transmission Requested Gear Feedback
        spn3289 = pMsg->DATA.bytes[3];
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               H a n d l e  P G N 6 5 2 7 2   EBC1        TRF1
    //---------------------------------------------------------------
    
    bool            j1939tc_HandlePgn65272(
        J1939TC_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        uint8_t         spn123;
        uint8_t         spn124;
        uint8_t         spn126;
        uint8_t         spn127;
        uint16_t        spn177;
        uint8_t         spn3027;
        uint8_t         spn3028;
        uint8_t         spn3026;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pMsg) {
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            
            // SPN 123  1       8bits       Clutch Pressure
            spn123 = pMsg->DATA.bytes[0];
            // SPN 124  2       8bits       Transmission Oil Level
            spn124 = pMsg->DATA.bytes[1];
            // SPN 126  3       8bits       Transmission Filter Differential Pressure
            spn126 = pMsg->DATA.bytes[2];
            // SPN 127  4       8bits       Transmission Oil Pressure
            spn127 = pMsg->DATA.bytes[3];
            // SPN 177  5-6     16bits       Transmission Oil Temperature
            spn177 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
            // SPN 3027 7       8bits       Transmission Oil Level High / Low
            spn3027 = pMsg->DATA.bytes[0];
            // SPN 3028 8.1     4bits       Transmission Oil Level Countdown Timer
            spn3028 = pMsg->DATA.bytes[0] & 0xF;
            // SPN 3026 8.5     4bits       Transmission Oil Level Measurement Status
            spn3026 = (pMsg->DATA.bytes[0] >> 4) & 0xF;
        }
       
        // Return to caller.
        return true;
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
        curTime = j1939ca_MsTimeGet((J1939CA_DATA *)this);

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
            j1939tc_HandlePgn61184(this, NULL);
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939TC_DATA *	j1939tc_Init(
        J1939TC_DATA    *this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
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

        this =   (J1939TC_DATA *)j1939ca_Init(
                        (J1939CA_DATA *)this,
                        pCAN,
                        pSYS,
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

        //this->super.name.ECU = 0;
        this->super.name.FU = 3;
        this->super.name.FUI = 0;

        this->super.pRcvPgnTbl = &rcvPgntbl;
        this->super.pXmtPgnTbl = &xmtPgntbl;
        this->super.pTimedTransmit =
                        (P_HANDLE_TIMED_TRANSMITS)&j1939tc_HandleTimedTransmits;

        // All of our tests that captured messages from startup in a real truck
        // did not show the engine or transmission claiming their name.  They
        // just assumed they had the names.
        j1939ca_Setup((J1939CA_DATA *)this, J1939_TRANSMISSION_1);
        this->super.cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we have our name.

        // Default all SPNs to unsupported values.
        memset(
                &this->spn123,
                0xFF,
                (
                    offsetof(J1939TC_DATA,spn898)
                    - offsetof(J1939TC_DATA,spn123)
                    + sizeof(this->spn898)
                )
        );

#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
        BREAK_NOT_BOUNDARY4(offsetof(J1939TC_DATA,eRc));
        BREAK_NOT_BOUNDARY4(offsetof(J1939TC_DATA,spn123));
        BREAK_NOT_BOUNDARY4(offsetof(J1939TC_DATA,spn161));
        BREAK_NOT_BOUNDARY4(offsetof(J1939TC_DATA,timeOut));
        BREAK_NOT_BOUNDARY4(sizeof(J1939TC_DATA));
#endif

        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 0   0x0000   TSC1
    //---------------------------------------------------------------

    // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
    int             j1939tc_SetupPgn0(
        J1939TC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn0_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn0_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn0_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0xC0;
            *pData |= this->spn695 & 0x03;
            *pData |= (this->spn696 & 0x03) << 2;
            *pData |= (this->spn897 & 0x03) << 4;
            ++pData;    // 1
            *pData  = this->spn898 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn898 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = this->spn518;
            ++pData;    // 4
            *pData  = 0xF0;
            *pData |= (this->spn3349 & 0x07);
            if (pPDU->PS == 41) {   // Retarder, Exhaust, Engine #1
                *pData |= 0x1F << 3;
            }
            else {
                *pData |= (this->spn3350 & 0x1F) << 3;
            }
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



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 2   0xF002   ETC1
    //---------------------------------------------------------------

    // Electronic Transmission Controller 1 - ETC1 -
    // Unused bits are set to 1.
    // The Transmission and the Cruise Controller are normally interested
    // in this message and try to control the Engine Retarder via the
    // TSC1 message.
    int             j1939tc_SetupPgn61442(
        J1939TC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        bool            fRc = true;

        if (pPDU) {
            pPDU->PF = (pgn61442_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn61442_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn61442_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return false;
            }
            *pData  = 0xC0;
            *pData |= this->spn560 & 0x3;
            *pData |= (this->spn573 & 0x3) << 4;
            *pData |= (this->spn574 & 0x3) << 6;
            ++pData;    // 1
            *pData  = this->spn191 & 0xFF;       // Transmission Output Shaft Speed
            ++pData;    // 2
            *pData  = (this->spn191 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = this->spn522;
            ++pData;    // 4
            *pData  = 0xF0;
            *pData |= (this->spn606 & 0x3);      // Engine Momentary Overspeed Enable
            *pData |= (this->spn607 & 0x3) << 2; // Progressive Shift Disable
            ++pData;    // 5
            *pData  = this->spn161 & 0xFF;       // Transmission Input Shaft Speed
            ++pData;    // 6
            *pData  = (this->spn161 >> 8) & 0xFF;
            ++pData;    // 7
            *pData  = this->spn1482;             // Source Address of Controlling Device
                                                // for Transmission Control
        }
        else {
            return false;
        }

        // Return to caller.
        return fRc;
    }


    bool            j1939tc_TransmitPgn61442(
        J1939TC_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        uint16_t        len = 0;
        
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
#endif
        
        len = j1939tc_SetupPgn61442(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->startTime61442 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }
    
    

    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 5   0xF005   ETC2
    //---------------------------------------------------------------

    int             j1939tc_SetupPgn61445(
        J1939TC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn61445_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn61445_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn61445_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn524;
            ++pData;    // 1
            *pData  = this->spn526 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn526 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = this->spn523;
            ++pData;    // 4
            *pData  = this->spn162 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn162 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = this->spn163 & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn163 >> 8) & 0xFF;
        }
        else {
            return 0;
        }

        // Return to caller.
        return 8;
    }
    
    
    bool            j1939tc_TransmitPgn61445(
        J1939TC_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        uint16_t        len = 0;
        
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
#endif
        
        len = j1939tc_SetupPgn61445(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->startTime61445 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 0 9 8   0xFE4A  ETC7
    //---------------------------------------------------------------

    int             j1939tc_SetupPgn65098(
        J1939TC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn65098_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65098_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65098_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0x0F;
            *pData  |= (this->spn1850 & 0x03) << 4;
            *pData  |= (this->spn1849 & 0x03) << 6;
            ++pData;    // 1
            *pData  = this->spn3086 & 0x03;
            *pData  |= (this->spn2945 & 0x03) << 2;
            *pData  |= (this->spn2900 & 0x03) << 4;
            *pData  |= (this->spn1851 & 0x03) << 6;
            ++pData;    // 2
            *pData  = this->spn2539 & 0x03;
            *pData  |= (this->spn2538 & 0x03) << 2;
            *pData  |= (this->spn2537 & 0x03) << 4;
            *pData  |= (this->spn2536 & 0x03) << 6;
            ++pData;    // 3
            *pData  = this->spn3289;
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
    
    
    bool            j1939tc_TransmitPgn65098(
        J1939TC_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        uint16_t        len = 0;
        
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
#endif
        
        len = j1939tc_SetupPgn65098(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->startTime65098 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 2 6   0xFECA  DM1
    //---------------------------------------------------------------

    int             j1939tc_SetupPgn65226(
        J1939TC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn65226_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65226_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65226_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn524;
            ++pData;    // 1
            *pData  = this->spn526 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn526 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = this->spn523;
            ++pData;    // 4
            *pData  = this->spn162 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn162 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = this->spn163 & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn163 >> 8) & 0xFF;
        }
        else {
            return 0;
        }

        // Return to caller.
        return 8;
    }
    
    
    bool            j1939tc_TransmitPgn65226(
        J1939TC_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        uint16_t        len = 0;
        
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
#endif
        
        len = j1939tc_SetupPgn65226(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->startTime65226 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 7 2   FEF8        TRF1
    //---------------------------------------------------------------

    int             j1939tc_SetupPgn65272(
        J1939TC_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn65272_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65272_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65272_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn123;
            ++pData;    // 1
            *pData  = this->spn124;
            ++pData;    // 2
            *pData  = this->spn126;
            ++pData;    // 3
            *pData  = this->spn127;
            ++pData;    // 4
            *pData  = this->spn177 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn177 >> 8) & 0xFF;
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
    
    
    bool            j1939tc_TransmitPgn65272(
        J1939TC_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        uint16_t        len = 0;
        
#ifdef NDEBUG
#else
        if( !j1939tc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
#endif
        
        len = j1939tc_SetupPgn65272(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->startTime65272 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
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
        J1939TC_DATA	*this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_J1939TC) )
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
