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
        NULL,
        NULL,                // Message Data Constructor
        0,
        0,
        10
    };

    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61440_entry = {
        // PGN 61440  0x00F000 - Electronic Retarder Controller 1 - ERC1
        &pgn61440_entry,
        (P_SRVCMSG_RTN)j1939er_HandlePgn61440,
        NULL,
        (P_SETUP_MSG_RTN)j1939er_SetupPgn61440,
        offsetof(J1939ER_DATA, time61440),
        0,
        0,
        100
    };

    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65249_entry = {
        // PGN 65249  0x00FEE1 - Retarder Configuration - RC -
        &pgn65249_entry,
        NULL,
        (P_VARMSG_RTN)j1939er_HandlePgn65249,
        (P_SETUP_MSG_RTN)j1939er_SetupPgn65249,
        offsetof(J1939ER_DATA, time65249),
        0,
        0,
        100
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        &ca_pgn0_entry,
        &ca_pgn61440_entry,
        &ca_pgn65249_entry,
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
        &ca_pgn65249_entry,
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
    bool            j1939er_Validate(
        J1939ER_DATA    *this
    );
#endif
    
    



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

    ERESULT         j1939er_getLastError(
        J1939ER_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939er_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            j1939er_setLastError(
        J1939ER_DATA    *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939er_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    // Wheel-Based Vehicle Speed
    uint16_t			j1939er_getSpn84(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn84;
    }


    bool			j1939er_setSpn84(
        J1939ER_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn84 = value;

        return true;
    }



    // Engine Oil Temperature 1
    uint16_t			j1939er_getSpn175(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn175;
    }


    bool			j1939er_setSpn175(
        J1939ER_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn175 = value;

        return true;
    }



    // Turbo Oil Temperature
    uint16_t			j1939er_getSpn176(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn176;
    }


    bool			j1939er_setSpn176(
        J1939ER_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn176 = value;

        return true;
    }



    // Engine Speed
    uint16_t			j1939er_getSpn190(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn190;
    }


    bool			j1939er_setSpn190(
        J1939ER_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn190 = value;

        return true;
    }



    // Engine's Desired Operating Speed
    uint16_t			j1939er_getSpn515(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn515;
    }


    bool			j1939er_setSpn515(
        J1939ER_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn515 = value;

        return true;
    }



    // Actual Retarder - Percent Torque
    uint8_t			j1939er_getSpn520(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn520;
    }


    bool			j1939er_setSpn520(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn520 = value;

        return true;
    }



    // Retarder Enable - Brake Assist Switch
    uint8_t			j1939er_getSpn571(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn571;
    }


    bool			j1939er_setSpn571(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn571 = value;

        return true;
    }



    // Retarder Enable - Brake Assist Switch
    uint8_t			j1939er_getSpn572(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn572;
    }


    bool			j1939er_setSpn572(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn572 = value;

        return true;
    }



    // Retarder Torque Mode
    uint8_t			j1939er_getSpn900(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn900;
    }


    bool			j1939er_setSpn900(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn900 = value;

        return true;
    }



    // Engine Coolant Load Increase
    uint8_t			j1939er_getSpn1082(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1082;
    }


    bool			j1939er_setSpn1082(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1082 = value;

        return true;
    }



    // Intended Retarder Percent Torque
    uint8_t			j1939er_getSpn1085(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1085;
    }


    bool			j1939er_setSpn1085(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1085 = value;

        return true;
    }



    // CA of Controlling Retarder Device
    uint8_t			j1939er_getSpn1480(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1480;
    }


    bool			j1939er_setSpn1480(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1480 = value;

        return true;
    }



    // Intake Manifold 1 Air Temperature
    uint16_t			j1939er_getSpn1636(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1636;
    }


    bool			j1939er_setSpn1636(
        J1939ER_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1636 = value;

        return true;
    }



    // Engine Coolant Temperature
    uint16_t			j1939er_getSpn1637(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1637;
    }


    bool			j1939er_setSpn1637(
        J1939ER_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1637 = value;

        return true;
    }



    // Retarder requesting Brake Light
    uint8_t			j1939er_getSpn1667(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1667;
    }


    bool			j1939er_setSpn1667(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1667 = value;

        return true;
    }



    // Drivers Demand Retarder - Percent Torque
    uint8_t			j1939er_getSpn1715(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1715;
    }


    bool			j1939er_setSpn1715(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1715 = value;

        return true;
    }



    // Retarder Selection - non-engine
    uint8_t			j1939er_getSpn1716(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1716;
    }


    bool			j1939er_setSpn1716(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1716 = value;

        return true;
    }



    // Actual Maximum Available Retarder
    uint8_t			j1939er_getSpn1717(
        J1939ER_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1717;
    }


    bool			j1939er_setSpn1717(
        J1939ER_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939er_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1717 = value;

        return true;
    }







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
    //                  H a n d l e  P G N 0    0x000000 (TSC1)
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
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
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
            //TODO: This might not account for clock rollover.
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
    // PGN 61440  0x00F000 - Electronic Retarder Controller 1 - ERC1
    //---------------------------------------------------------------

    bool            j1939er_HandlePgn61440(
        J1939ER_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn900;
        uint8_t         spn571;
        uint8_t         spn572;
        uint8_t         spn520;
        uint8_t         spn1085;
        uint8_t         spn1082;
        uint8_t         spn1667;
        uint8_t         spn1480;
        uint8_t         spn1715;
        uint8_t         spn1716;
        uint8_t         spn1717;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939er_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);

        // SPN 900  1.1     4bits       Retarder Torque Mode
        spn900 = pMsg->DATA.bytes[0] & 0xF;
        // SPN 571  1.5     2bits       Retarder Enable - Brake Assist Switch
        spn571 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 572  1.7     2bits       Retarder Enable - Shift Assist Switch
        spn572 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 520  2       8bits       Actual Retarder - Percent Torque
        spn520 = pMsg->DATA.bytes[1];
        // SPN 1085 3       8bits       Intended Retarder Percent Torque
        spn1085 = pMsg->DATA.bytes[1];
        // SPN 1082 4.1     2bits       Engine Coolant Load Increase
        spn1082 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 1667 4.3     2bits       Retarder Requesting Brake Light
        spn1667 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 1480 5       8bits       Source Address of Controlling Device for Retarder Control
        spn1480 = pMsg->DATA.bytes[1];
        // SPN 1715 6       8bits       Drivers Demand Retarder - Percent Torque
        spn1715 = pMsg->DATA.bytes[1];
        // SPN 1716 7       8bits       Retarder Selection, non-engine
        spn1716 = pMsg->DATA.bytes[1];
        // SPN 1717 8       8bits       Actual Maximum Available Retarder - Percent Torque
        spn1717 = pMsg->DATA.bytes[1];

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    // PGN 65249  0x00FEE1 - Retarder Configuration - RC -
    //---------------------------------------------------------------
    
    bool            j1939er_HandlePgn65249(
        J1939ER_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn901;
        uint8_t         spn902;
        uint8_t         spn557;
        uint16_t        spn546;
        uint8_t         spn551;
        uint16_t        spn548;
        uint8_t         spn552;
        uint16_t        spn549;
        uint8_t         spn553;
        uint16_t        spn550;
        uint8_t         spn554;
        uint16_t        spn547;
        uint16_t        spn556;
        uint8_t         spn555;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939er_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = *pPDU;
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 901  01.1     4bits      Retarder Type
        spn901 = pData[0] & 0x0F;
        // SPN 902  01.5     4bits      Retarder Location
        spn902 = (pData[0] >> 4) & 0x0F;
        // SPN 557  02       8bits      Retarder Control Method
        //                              (Retarder Configuration)
        spn557 = pData[1];
        // SPN 546  03-04    16bits     Retarder Speed At Idle, Point 1
        //                              (Retarder Configuration)
        spn546 = pData[2] | (pData[3] << 8);
        // SPN 551  05       8bits      Percent Torque At Idle, Point 1
        //                              (Retarder Configuration)
        spn551 = pData[4];
        // SPN 548  06-07    16bits     Maximum Retarder Speed, Point 2
        //                              (Retarder Configuration)
        spn548 = pData[5] | (pData[6] << 8);
        // SPN 552  08       8bits      Percent Torque At Maximum Speed, Point 2
        //                              (Retarder Configuration)
        spn552 = pData[7];
        // SPN 549  09-10    16bits     Retarder Speed At Point 3
        //                              (Retarder Configuration)
        spn549 = pData[8] | (pData[9] << 8);
        // SPN 553  11       8bits      Percent Torque At Point 3
        //                              (Retarder Configuration)
        spn553 = pData[10];
        // SPN 550  12-13    16bits     Retarder Speed At Point 4
        //                              (Retarder Configuration)
        spn550 = pData[11] | (pData[12] << 8);
        // SPN 554  14       8bits      Percent Torque At Point 4
        //                              (Retarder Configuration)
        spn554 = pData[13];
        // SPN 547  15-16    16bits     Retarder Speed At Peak Torque, Point 5
        //                              (Retarder Configuration)
        spn547 = pData[14] | (pData[15] << 8);
        // SPN 556  17-18    16bits     Reference Retarder Torque
        //                              (Retarder Configuration)
        spn556 = pData[16] | (pData[17] << 8);
        // SPN 555  19       8bits      Percent Torque At Peak Torque, Point 5
        //                              (Retarder Configuration)
        spn555 = pData[18];
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    // PGN 65275  0x00FEFB - Transmission Fluids 1 - TRF1
    //---------------------------------------------------------------
    
    bool            j1939er_HandlePgn65275(
        J1939ER_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn119;
        uint8_t         spn120;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939er_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 119  1       8bits       Hydraulic Retarder Pressure
        spn119 = pMsg->DATA.bytes[0];
        // SPN 120  2       8bits       Hydraulic Retarder Oil Temperature
        spn120 = pMsg->DATA.bytes[1];
        
        // Return to caller.
        return false;
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
        this->curTime = curTime;

        if ((curTime - this->time61440.msTime) >= this->time61440.msDelay) {
            j1939er_TransmitPgn61440(this);
        }
        if ((curTime - this->time65249.msTime) >= this->time65249.msDelay) {
            j1939er_TransmitPgn65249(this);
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

        //this->super.name.ECU = 0;
        this->super.name.FU = 12;
        this->super.name.FUI = 1;

        j1939ca_Setup((J1939CA_DATA *)this, J1939_ENGINE_RETARDER_EXHAUST_1);
        this->super.cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we have our name.
        this->super.pRcvPgnTbl = &rcvPgntbl;
        this->super.pXmtPgnTbl = &xmtPgntbl;
        this->super.pTimedTransmit =
                        (P_HANDLE_TIMED_TRANSMITS)&j1939er_HandleTimedTransmits;
        
        // Default all SPNs to unsupported values.
        memset(
               &this->spnFirst,
               0xFF,
               (offsetof(J1939ER_DATA,spnLast) - offsetof(J1939ER_DATA,spnFirst)
                + sizeof(uint32_t))
               );
        this->spn1480 = J1939_ENGINE_RETARDER_EXHAUST_1;
        this->spn520 = 125;     // Actual Retarder - Percent Torque
        this->spn571 = 1;       // Enable Retarder Brake Assist
        this->spn572 = 1;       // Enable Retarder Shift Assist
        this->spn1085 = 125;    // Intended Retarder Percent Torque
        this->spn1715 = 75;     // Maximum Torque that can be requested by the driver
        this->spn1717 = 0;      // Maximum Allowable Torque on request

        this->time61440.msDefault = pgn61440_entry.msFreq;
        this->time61440.msDelay = pgn61440_entry.msFreq;
        this->time61440.pgn = 61440;
        
        this->time65249.msDefault = pgn65249_entry.msFreq;
        this->time65249.msDelay = pgn65249_entry.msFreq;
        this->time65249.pgn = 65249;
        
        this->time65275.msDefault = pgn65275_entry.msFreq;
        this->time65275.msDelay = pgn65275_entry.msFreq;
        this->time65275.pgn = 65275;
        
#ifdef NDEBUG
#else
        if( !j1939er_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }
        BREAK_NOT_BOUNDARY4(offsetof(J1939ER_DATA,spn84));
        BREAK_NOT_BOUNDARY4(&this->spnFirst);
        BREAK_NOT_BOUNDARY4(&this->spnLast);
        BREAK_NOT_BOUNDARY4(offsetof(J1939ER_DATA,timeOut));
        BREAK_NOT_BOUNDARY4(sizeof(J1939ER_DATA));
#endif

        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    // PGN 61440  0x00F000 - Electronic Retarder Controller 1 - ERC1
    //---------------------------------------------------------------

    // Electronic Retarder Controller 1 - ERC1 -
    // Unused bits are set to 1.
    // The Transmission and the Cruise Controller are normally interested
    // in this message and try to control the Engine Retarder via the
    // TSC1 message.
    int             j1939er_SetupPgn61440(
        J1939ER_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn61440_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn61440_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn61440_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0x00;
            *pData |= this->spn900 & 0xF;
            *pData |= (this->spn571 & 0x3) << 4;
            *pData |= (this->spn572 & 0x3) << 6;
            ++pData;
            *pData  = this->spn520;
            ++pData;
            *pData  = this->spn1085;
            ++pData;
            *pData  = 0xF0;
            *pData |= (this->spn1082 & 0x3);
            *pData |= (this->spn1667 & 0x3) << 2;
            ++pData;
            *pData  = this->spn1480;
            ++pData;
            *pData  = this->spn1715;
            ++pData;
            *pData  = this->spn1716;
            ++pData;
            *pData  = this->spn1717;
        }
        else {
            return 0;
        }

        // Return to caller.
        return 8;
    }


    bool            j1939er_TransmitPgn61440(
        J1939ER_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;

        len = j1939er_SetupPgn61440(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }

        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time61440.msTime = this->curTime;

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    // PGN 65249  0x00FEE1 - Retarder Configuration - RC
    //---------------------------------------------------------------

    int             j1939er_SetupPgn65249(
        J1939ER_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65249_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65249_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65249_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 19) {
                return 0;
            }
            *pData  = 0x00;
            *pData |= this->spn900 & 0xF;
            *pData |= (this->spn571 & 0x3) << 4;
            *pData |= (this->spn572 & 0x3) << 6;
            ++pData;
            *pData  = this->spn520;
            ++pData;
            *pData  = this->spn1085;
            ++pData;
            *pData  = 0xF0;
            *pData |= (this->spn1082 & 0x3);
            *pData |= (this->spn1667 & 0x3) << 2;
            ++pData;
            *pData  = this->spn1480;
            ++pData;
            *pData  = this->spn1715;
            ++pData;
            *pData  = this->spn1716;
            ++pData;
            *pData  = this->spn1717;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
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
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65249.msTime = this->curTime;

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    // PGN 61440  0x00F000 - Electronic Retarder Controller 1 - ERC1
    //---------------------------------------------------------------
    
    int             j1939er_SetupPgn65275(
        J1939ER_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65275_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65275_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65275_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData |= this->spn119;
            ++pData;
            *pData  = this->spn120;
            ++pData;
            *pData  = 0xFF;
            ++pData;
            *pData  = 0xFF;
            ++pData;
            *pData  = 0xFF;
            ++pData;
            *pData  = 0xFF;
            ++pData;
            *pData  = 0xFF;
            ++pData;
            *pData  = 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939er_TransmitPgn65275(
        J1939ER_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;
        
        len = j1939er_SetupPgn65275(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65275.msTime = this->curTime;
        
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
        J1939ER_DATA	*this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_J1939ER) )
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
