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




#include    <j1939en_internal.h>
#include    <j1939ecu_internal.h>



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
        NULL,
        NULL,                // Message Data Constructor
        0,
        0,
        50
    };


    static
    const
    J1939CA_PGN_ENTRY   ca_pgn61184_entry = {
        // PGN 61184  0x00EF00 - Proprietary A - PROPA
        &pgn61184_entry,
        NULL,
        (P_VARMSG_RTN)j1939ca_HandlePgn61184,
        (P_SETUP_MSG_RTN)j1939ca_SetupPgn61184,
        0,                              // Offset of Timeout
        0,                              // da
        0                               // rsvd
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61442_entry = {
        // PGN 61442  0x00F002 - Electronic Transmission Controller 1 - ETC1
        &pgn61442_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn61442,
        NULL,
        NULL,
        0,
        0,
        10
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61443_entry = {
        // PGN 61443  0x00F003 - Electronic Engine Controller 2 - EEC2
        &pgn61443_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn61443,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn61443,
        offsetof(J1939EN_DATA, time61443),
        0,
        0,
        50
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61444_entry = {
        // PGN 61444  0x00F004 - Electronic Engine Controller 1 - EEC1
        &pgn61444_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn61444,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn61444,
        offsetof(J1939EN_DATA, time61444),
        0,
        0,
        0                   // Engine Speed Dependent
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61445_entry = {
        // PGN 61445  0x00F005 - Electronic Transmission Controller 2 - ETC2
        &pgn61445_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn61445,
        NULL,
        NULL,
        0,
        0,
        100
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65129_entry = {
        // PGN 65129  0x00FE69 - Engine Temperature 3 - ET3
        &pgn65129_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65129,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn65129,
        offsetof(J1939EN_DATA, time65129),
        0,
        0,
        1000
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65247_entry = {
        // PGN 65247  0x00FEDF - Electronic Engine Controller 3 - EEC3
        &pgn65247_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65247,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn65247,
        offsetof(J1939EN_DATA, time65247),
        0,
        0,
        250
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65252_entry = {
        // PGN 65252  0x00FEE4 - Shutdown - SHUTDOW
        &pgn65252_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65262,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn65252,
        offsetof(J1939EN_DATA, time65252),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65262_entry = {
        // PGN 65262  0x00FEEE - Engine Temperature 1 - ET1
        &pgn65262_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65262,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn65262,
        offsetof(J1939EN_DATA, time65262),
        0,
        0,
        1000
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65265_entry = {
        // PGN 65265  0x00FEF1 - Cruise Control/Vehicle Speed - CCVS
        &pgn65265_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65265,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn65265,
        offsetof(J1939EN_DATA, time65265),
        0,
        0,
        100
    };


    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65266_entry = {
        // PGN 65266  0x00FEF2 - Fuel Economy (Liquid) - LFE
        &pgn65266_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65266,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn65266,
        offsetof(J1939EN_DATA, time65266),
        0,
        0,
        100
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65279_entry = {
        // PGN 65279  0x00FEFF - Water in Fuel Indicator - WFI
        &pgn65279_entry,
        (P_SRVCMSG_RTN)j1939en_HandlePgn65279,
        NULL,
        (P_SETUP_MSG_RTN)j1939en_SetupPgn65279,
        offsetof(J1939EN_DATA, time65279),
        0,
        0,
        100
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        &ca_pgn0_entry,
        &ca_pgn61442_entry,
        &ca_pgn61445_entry,
        &ca_pgn65252_entry,
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
        &ca_pgn65252_entry,
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

#ifdef NDEBUG
#else
    static
    bool            j1939en_Validate(
        J1939EN_DATA      *cbp
    );
#endif
    
    


    

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

    OBJ_ID          j1939en_getECU(
        J1939EN_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        j1939en_setLastError(this, ERESULT_SUCCESS);
        return this->pECU;
    }

    
    bool            j1939en_setECU(
        J1939EN_DATA    *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pECU = pValue;        // NOT owned
        
        j1939en_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    ERESULT         j1939en_getLastError(
        J1939EN_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            j1939en_setLastError(
        J1939EN_DATA    *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    bool            j1939en_setRpmRoutine(
        J1939EN_DATA    *this,
        void            (*pRpmRoutine)(void *, uint16_t),
        void            *pRpmData
    )
    {
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pRpmRoutine = pRpmRoutine;
        this->pRpmData = pRpmData;
        
        j1939en_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    bool			j1939en_setShiftExit(
        J1939EN_DATA	*this,
        P_VOID_EXIT12   pExit,
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



    // Engine Intercooler Temperature
    uint8_t			j1939en_getSpn52(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn52;
    }


    bool			j1939en_setSpn52(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn52 = value;

        return true;
    }



    // Two Speed Axle Switch
    uint8_t			j1939en_getSpn69(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn69;
    }


    bool			j1939en_setSpn69(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn69 = value;

        return true;
    }



    // Parking Brake Switch
    uint8_t			j1939en_getSpn70(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn70;
    }


    bool			j1939en_setSpn70(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn70 = value;

        return true;
    }



    // Wheel-Based Vehicle Speed
    uint16_t			j1939en_getSpn84(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn84;
    }


    bool			j1939en_setSpn84(
        J1939EN_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn84 = value;

        return true;
    }



    // Cruise Control Set Speed
    uint8_t			j1939en_getSpn86(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn86;
    }


    bool			j1939en_setSpn86(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn86 = value;

        return true;
    }



    // Accelerator Pedal Position 1
    uint8_t			j1939en_getSpn91(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn91;
    }


    bool			j1939en_setSpn91(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn91 = value;

        return true;
    }



    // Percent Load At Current Speed
    uint8_t			j1939en_getSpn92(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn92;
    }


    bool			j1939en_setSpn92(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn92 = value;

        return true;
    }



    // Engine Coolant Temperature
    uint8_t			j1939en_getSpn110(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn110;
    }


    bool			j1939en_setSpn110(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn110 = value;

        return true;
    }



    // 03 - Transmission Input Shaft Speed
    uint16_t			j1939en_getSpn161(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn161;
    }


    bool			j1939en_setSpn161(
        J1939EN_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn161 = value;

        return true;
    }



    // Fuel Temperature
    uint8_t			j1939en_getSpn174(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn174;
    }


    bool			j1939en_setSpn174(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn174 = value;

        return true;
    }



    // Engine Oil Temperature 1
    uint16_t			j1939en_getSpn175(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn175;
    }


    bool			j1939en_setSpn175(
        J1939EN_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn175 = value;

        return true;
    }



    // Turbo Oil Temperature
    uint16_t			j1939en_getSpn176(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn176;
    }


    bool			j1939en_setSpn176(
        J1939EN_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn176 = value;

        return true;
    }



    // Engine Speed
    uint16_t			j1939en_getSpn190(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn190;
    }


    bool			j1939en_setSpn190(
        J1939EN_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn190 = value;

        return true;
    }



    // 03 - Transmission Output Shaft Speed
    uint16_t			j1939en_getSpn191(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn191;
    }


    bool			j1939en_setSpn191(
        J1939EN_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn191 = value;

        return true;
    }



    // Driver's Demand Engine - Percent Torque
    uint8_t			j1939en_getSpn512(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn512;
    }


    bool			j1939en_setSpn512(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn512 = value;

        return true;
    }



    // Actual Engine - Percent Torque
    uint8_t			j1939en_getSpn513(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn513;
    }


    bool			j1939en_setSpn513(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn513 = value;

        return true;
    }



    // Nominal Friction - Percent Torque
    uint8_t			j1939en_getSpn514(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn514;
    }


    bool			j1939en_setSpn514(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn514 = value;

        return true;
    }



    // Engine's Desired Operating Speed
    uint16_t			j1939en_getSpn515(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn515;
    }


    bool			j1939en_setSpn515(
        J1939EN_DATA	*this,
        uint16_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn515 = value;

        return true;
    }



    // Engine's Desired Operating Speed Asymmetry Adjustment
    uint8_t			j1939en_getSpn519(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn519;
    }


    bool			j1939en_setSpn519(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn519 = value;

        return true;
    }



    // 03 - Transmission Current Gear
    uint8_t			j1939en_getSpn523(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn523;
    }


    bool			j1939en_setSpn523(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn523 = value;

        return true;
    }



    // 03 - Transmission Selected Gear
    uint8_t			j1939en_getSpn524(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn524;
    }


    bool			j1939en_setSpn524(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn524 = value;

        return true;
    }



    // Cruise Control States
    uint8_t			j1939en_getSpn527(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn527;
    }


    bool			j1939en_setSpn527(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn527 = value;

        return true;
    }



    // Accelerator Pedal 1 Low Idle Switch
    uint8_t			j1939en_getSpn558(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn558;
    }


    bool			j1939en_setSpn558(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn558 = value;

        return true;
    }



    // Accelerator Pedal Kickdown Switch
    uint8_t			j1939en_getSpn559(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn559;
    }


    bool			j1939en_setSpn559(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn559 = value;

        return true;
    }



    // Transmission Shift In Process
    uint8_t			j1939en_getSpn574(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn574;
    }


    bool			j1939en_setSpn574(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn574 = value;

        return true;
    }



    // Cruise Control Active
    uint8_t			j1939en_getSpn595(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn595;
    }


    bool			j1939en_setSpn595(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn595 = value;

        return true;
    }



    // Cruise Control Enable Switch
    uint8_t			j1939en_getSpn596(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn596;
    }


    bool			j1939en_setSpn596(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn596 = value;

        return true;
    }



    // Brake Switch
    uint8_t			j1939en_getSpn597(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn597;
    }


    bool			j1939en_setSpn597(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn597 = value;

        return true;
    }



    // Clutch Switch
    uint8_t			j1939en_getSpn598(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn598;
    }


    bool			j1939en_setSpn598(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn598 = value;

        return true;
    }



    // Cruise Control Set Switch
    uint8_t			j1939en_getSpn599(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn599;
    }


    bool			j1939en_setSpn599(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn599 = value;

        return true;
    }



    // Cruise Control Coast (Decelerate) Switch
    uint8_t			j1939en_getSpn600(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn600;
    }


    bool			j1939en_setSpn600(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn600 = value;

        return true;
    }



    // Cruise Control Resume Switch
    uint8_t			j1939en_getSpn601(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn601;
    }


    bool			j1939en_setSpn601(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn601 = value;

        return true;
    }



    // Cruise Control Accelerate Switch
    uint8_t			j1939en_getSpn602(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn602;
    }


    bool			j1939en_setSpn602(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn602 = value;

        return true;
    }



    // Engine Torque Mode
    uint8_t			j1939en_getSpn899(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn899;
    }


    bool			j1939en_setSpn899(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn899 = value;

        return true;
    }



    // Engine Test Mode Switch
    uint8_t			j1939en_getSpn966(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn966;
    }


    bool			j1939en_setSpn966(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn966 = value;

        return true;
    }



    // Idle Decrement Switch
    uint8_t			j1939en_getSpn967(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn967;
    }


    bool			j1939en_setSpn967(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn967 = value;

        return true;
    }



    // Idle Increment Switch
    uint8_t			j1939en_getSpn968(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn968;
    }


    bool			j1939en_setSpn968(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn968 = value;

        return true;
    }



    // Remote Accelerator Pedal Position
    uint8_t			j1939en_getSpn974(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn974;
    }


    bool			j1939en_setSpn974(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn974 = value;

        return true;
    }



    // PTO State
    uint8_t			j1939en_getSpn976(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn976;
    }


    bool			j1939en_setSpn976(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn976 = value;

        return true;
    }



    // Engine Protection System Approaching Shutdown
    uint8_t			j1939en_getSpn1109(
        J1939EN_DATA	*this
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939en_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->spn1109;
    }

    
    bool			j1939en_setSpn1109(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939en_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->spn1109 = value;
        
        return true;
    }
    

    
    // Engine Protection System has Shutdown Engine
    uint8_t			j1939en_getSpn1110(
        J1939EN_DATA	*this
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939en_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->spn1110;
    }

    
    bool			j1939en_setSpn1110(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939en_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->spn1110 = value;
        
        return true;
    }
    

    
    // Engine Intercooler Thermostat Opening
    uint8_t			j1939en_getSpn1134(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1134;
    }


    bool			j1939en_setSpn1134(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1134 = value;

        return true;
    }



    // Engine Shutdown Override Switch
    uint8_t			j1939en_getSpn1237(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1237;
    }


    bool			j1939en_setSpn1237(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1237 = value;

        return true;
    }



    // Road Speed Limit Status
    uint8_t			j1939en_getSpn1437(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1437;
    }


    bool			j1939en_setSpn1437(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1437 = value;

        return true;
    }



    // CA of Controlling Retarder Device
    uint8_t			j1939en_getSpn1480(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1480;
    }


    bool			j1939en_setSpn1480(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1480 = value;

        return true;
    }



    // Source Address of Controlling Device
    uint8_t			j1939en_getSpn1483(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1483;
    }


    bool			j1939en_setSpn1483(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1483 = value;

        return true;
    }



    // Cruise Control Pause Switch
    uint8_t			j1939en_getSpn1633(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1633;
    }


    bool			j1939en_setSpn1633(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1633 = value;

        return true;
    }



    // Intake Manifold 1 Air Temperature
    uint16_t		j1939en_getSpn1636(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1636;
    }


    bool			j1939en_setSpn1636(
        J1939EN_DATA	*this,
        uint16_t		value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1636 = value;

        return true;
    }



    // Engine Coolant Temperature
    uint16_t			j1939en_getSpn1637(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1637;
    }


    bool			j1939en_setSpn1637(
        J1939EN_DATA	*this,
        uint16_t		value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1637 = value;

        return true;
    }



    // Engine Starter Mode
    uint8_t			j1939en_getSpn1675(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn1675;
    }


    bool			j1939en_setSpn1675(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn1675 = value;

        return true;
    }



    // Engine Demand - Percent Torque
    uint8_t			j1939en_getSpn2432(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn2432;
    }


    bool			j1939en_setSpn2432(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn2432 = value;

        return true;
    }



    // Estimated Engine Parasitic Losses
    uint8_t			j1939en_getSpn2978(
        J1939EN_DATA	*this
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
        return 0;
    }
    #endif

        return this->spn2978;
    }


    bool			j1939en_setSpn2978(
        J1939EN_DATA	*this,
        uint8_t			value
    )
    {

    #ifdef NDEBUG
    #else
        if (j1939en_Validate(this)) {
        DEBUG_BREAK();
            return 0;
        }
    #endif

        this->spn2978 = value;

        return true;
    }






    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //                  C y l i n d e r  H e a t e r s
    //---------------------------------------------------------------
    
    bool            j1939en_CylinderHeatersEngage(
        J1939EN_DATA	*this
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
        
        return true;
    }
    
    
    bool            j1939en_CylinderHeatersDisengage(
        J1939EN_DATA	*this
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
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------

    void            j1939en_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939EN_DATA	*this = objId;

        // Do initialization.
        if( NULL == this ) {
            return;
        }

        j1939ca_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //               E n g i n e  S h u t d o w n
    //---------------------------------------------------------------
    
    bool            j1939en_EngineShutdownEngage(
        J1939EN_DATA	*this
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
        
        return true;
    }
    
    
    bool            j1939en_EngineShutdownDisengage(
        J1939EN_DATA	*this
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
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //               E n g i n e  S t a r t e r
    //---------------------------------------------------------------
    
    bool            j1939en_EngineStarterEngage(
        J1939EN_DATA	*this
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
        
        this->spn1675 = 0b001;          // starter active, gear not engaged
        this->state = J1939EN_STATE_STARTER_ACTIVE;
        
        return true;
    }
    
    
    bool            j1939en_EngineStarterDisengage(
        J1939EN_DATA	*this
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
        
        return true;
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
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            sa = pdu.SA;
            spn695 = pMsg->DATA.bytes[0] & 0x3;
            spn696 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
            spn897 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
            spn898 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
            spn518 = pMsg->DATA.bytes[3];

            if (this->fRetarding && (0 == spn695)) {      // *** Stop Retarding ***
                this->fRetarding = false;
                this->timeOut = 0;
                this->spn1480 = 0xFF;
                // Turn off retarder.
                fRc = true;
                goto exit00;
            }
            if ((1 == spn695) || (3 == spn695)) {
                this->timeOut = j1939ca_MsTimeGet((J1939CA_DATA *)this) + 150;
                if (this->fRetarding) {
                    // Just update time
                }
                else {
                    this->fRetarding = true;
                    this->spn1480 = sa;
                    // Turn on retarder.
                    fRc = true;
                    goto exit00;
                }
            }
        }
        else {
            if ( this->fRetarding && (this->timeOut <= j1939ca_MsTimeGet((J1939CA_DATA *)this)) ) {
                this->fRetarding = false;
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
    //              H a n d l e  P G N 6 1 4 4 2   F002         ETC1
    //---------------------------------------------------------------

    /* This is "Electronic Transmission Controller 1". It is a status
     * msg generated by the transmission #3 or #4 every 10ms. It gives
     * us whether the transmission is shifting or not, input rpm and
     * output rpm most importantly.
     */

    bool            j1939en_HandlePgn61442(
        J1939EN_DATA	*this,
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
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
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
        this->spn161 = spn161;
        this->spn190 = spn161;           // Make it engine speed too.
        // SPN 1482 8       8bits       Source Address of Controlling Device for
        //                              Transmission Control
        spn1482 = pMsg->DATA.bytes[7];

        switch (spn574 & 0x03) {
            case 0x00:                  // Shift is not in progress
                this->spn574 = 0x00;
                break;

            case 0x01:                  // Shift is in progress
#ifdef XYZZY
                if (this->spn574 == 0x01)
                    ;
                else {
                    this->fShifting = true;
                    if (this->pShiftExit) {
                        (*this->pShiftExit)(this->pShiftData,true);
                    }
                }
#endif
                this->spn574 = 0x01;
                break;

            case 0x02:                  // Error
                this->spn574 = 0x02;
                break;

            case 0x03:                  // Data Not Available
                this->spn574 = 0x03;
                break;
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //             H a n d l e  P G N 6 1 4 4 3     F003         EEC2
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn61443(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn29;
        uint8_t         spn91;
        uint8_t         spn92;
        uint8_t         spn558;
        uint8_t         spn559;
        uint8_t         spn974;
        uint8_t         spn1437;
        uint8_t         spn2970;
        uint8_t         spn2979;
        uint8_t         spn3357;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);

        // SPN 558  1.1     2bits       Accelerator Pedal 1 Low Idle Switch
        spn558 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 559  1.3     2bits       Accelerator Pedal Kickdown Switch
        spn559 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        // SPN 1437 1.5     2bits       Road Speed Limit Status
        spn1437 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 2970 1.7     2bits       Accelerator Pedal 2 Low Idle Switch
        spn2970 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 91   2       8bits       Accelerator Pedal Position 1
        spn91 = pMsg->DATA.bytes[1];
        // SPN 92   3       8bits       Engine Percent Load At Current Speed
        spn92 = pMsg->DATA.bytes[2];
        // SPN 974  4       8bits       Remote Accelerator Pedal Position
        spn974 = pMsg->DATA.bytes[3];
        // SPN 29   5       8bits       Accelerator Pedal Position 2
        spn29 = pMsg->DATA.bytes[4];
        // SPN 2979 6.1     2bits       Vehicle Acceleration Rate Limit Status
        spn2979 = pMsg->DATA.bytes[5] & 0x3;
        // SPN 3357 7       8bits       Actual Maximum Available Engine - Percent Torque
        spn3357 = pMsg->DATA.bytes[6];

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 1 4 4 4
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn61444(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn190;         // Engine Speed
        uint8_t         spn512;         // Driver's Demand Engine - Percent Torque
        uint8_t         spn513;         // Actual Engine - Percent Torque
        uint8_t         spn899;         // Engine Torque Mode
        uint8_t         spn1483;        // Source Address of Controlling Device for Engine Control
        uint8_t         spn1675;        // Engine Starter Mode
        uint8_t         spn2432;        // Engine Demand - Percent Torque

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);

        // SPN 899  1.1     4bits       Engine Torque Mode
        spn899 = pMsg->DATA.bytes[0] & 0x0F;
        // SPN 512  2       8bits       Driver's Demand Engine - Percent Torque
        spn512 = pMsg->DATA.bytes[1];
        // SPN 513  3       8bits       Actual Engine - Percent Torque
        spn513 = pMsg->DATA.bytes[2];
        // SPN 190  4-5     16bits      Engine Speed (rpm)
        spn190 = (pMsg->DATA.bytes[4] << 8) | pMsg->DATA.bytes[3];
        // SPN 1483 6       8bits       Source Address of Controlling Device for Engine Control
        spn1483 = pMsg->DATA.bytes[5];
        // SPN 1675 7.1     4bits       Engine Starter Mode
        spn1675 = pMsg->DATA.bytes[0] & 0x0F;
        // SPN 2432 8       8bits       Engine Demand - Percent Torque
        spn2432 = pMsg->DATA.bytes[2];
        
        if (spn190 == 0xFFFF) {
        }
        else {
            if (this->pRpmRoutine) {
                this->pRpmRoutine(this->pRpmData, spn190);
            }
        }

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 1 4 4 5  0xF005
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn61445(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn524;         // Transmission Selected Gear
        uint16_t        spn526;         // Transmission Actual Gear Ratio
        uint8_t         spn523;         // Transmission Current Gear
        uint16_t        spn162;         // Transmission Requested Range
        uint16_t        spn163;         // Transmission Current Range

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);

        // SPN 524  1       8bits       Transmission Selected Gear
        spn524 = pMsg->DATA.bytes[0];
        // SPN 526  2-3     16bits      Transmission Actual Gear Ratio
        spn526 = (pMsg->DATA.bytes[2] << 8) + pMsg->DATA.bytes[1];
        // SPN 523  4       8bits       Transmission Current Gear
        spn523 = pMsg->DATA.bytes[3];
        // SPN 162  5-6     16bits      Transmission Requested Range
        // Range selected by the operator. Characters may include P, Rx, Rx-1...R2,
        // R1, R, Nx, Nx-1...N2, N1, N, D, D1, D2..., Dx, L, L1, L2..., Lx-1, 1, 2,
        // 3,... If only one displayed character is required, the second character
        // shall be used and the first character shall be a space (ASCII 32) or a
        // control character (ASCII 0 to 31). If the first character is a control
        // character, refer to the manufacturer’s application document for definition.
        spn162 = (pMsg->DATA.bytes[5] << 8) + pMsg->DATA.bytes[4];
        // SPN 163  7-8     16bits      Transmission Current Range
        // Range selected by the operator. Characters may include P, Rx, Rx-1...R2,
        // R1, R, Nx, Nx-1...N2, N1, N, D, D1, D2..., Dx, L, L1, L2..., Lx-1, 1, 2,
        // 3,... If only one displayed character is required, the second character
        // shall be used and the first character shall be a space (ASCII 32) or a
        // control character (ASCII 0 to 31). If the first character is a control
        // character, refer to the manufacturer’s application document for definition.
        spn163 = (pMsg->DATA.bytes[7] << 8) + pMsg->DATA.bytes[6];

        if (this->fShifting) {
            if (spn523 == spn524) {
                this->fShifting = false;
                if (this->pShiftExit) {
                    (*this->pShiftExit)(this->pShiftData, false);
                }
            }
        }
        else {
            // Check for Up Shift within Shift sequence
            if (spn523 < spn524) {
                this->fShifting = true;
                if (this->pShiftExit) {
                    (*this->pShiftExit)(this->pShiftData, true);
                }
            }
        }


        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 1 2 9
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn65129(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
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
    //                  H a n d l e  P G N 6 5 2 4 7
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn65247(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn514;
        uint16_t        spn515;
        uint8_t         spn519;
        uint8_t         spn2978;
        uint16_t        spn3236;
        uint8_t         spn3237;
        uint8_t         spn3238;
        uint8_t         spn3239;
        uint8_t         spn3240;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);

        // SPN 514  1       8bits       Nominal Friction - Percent Torque
        spn514 = pMsg->DATA.bytes[0];
        // SPN 515  2-3     16bits      Engine's Desired Operating Speed
        spn515 = (pMsg->DATA.bytes[2] << 8) + pMsg->DATA.bytes[1];
        // SPN 514  4       8bits       Engine's Desired Operating Speed Asymmetry Adjustment
        spn519 = pMsg->DATA.bytes[3];
        // SPN 2978 5       8bits       Estimated Engine Parasitic Losses - Percent Torque
        spn2978 = pMsg->DATA.bytes[4];
        // SPN 3236 6-7     16bits      Aftertreatment 1 Exhaust Gas Mass Flow
        spn3236 = (pMsg->DATA.bytes[6] << 8) + pMsg->DATA.bytes[5];
        // SPN 3237 8.1     2bits       Aftertreatment 1 Intake Dew Point
        spn3237 = pMsg->DATA.bytes[7] & 0x3;
        // SPN 3238 8.3     2bits       Aftertreatment 1 Exhaust Dew Point
        spn3238 = (pMsg->DATA.bytes[7] >> 2) & 0x3;
        // SPN 3239 8.5     2bits       Aftertreatment 2 Intake Dew Point
        spn3239 = (pMsg->DATA.bytes[7] >> 4) & 0x3;
        // SPN 3240 8.7     2bits       Aftertreatment 2 Exhaust Dew Point
        spn3240 = (pMsg->DATA.bytes[7] >> 6) & 0x3;

        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 4 8
    //---------------------------------------------------------------
    
    bool            j1939en_HandlePgn65248(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn244;
        uint32_t        spn245;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 244  1-4     32bits      Trip Distance
        spn244 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
                | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 245  5-8     32bits      Total Vehicle Distance
        spn245 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8)
        | (pMsg->DATA.bytes[6] << 16)  | (pMsg->DATA.bytes[7] << 24);
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 5 2
    //---------------------------------------------------------------
    
    bool            j1939en_HandlePgn65252(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
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
    //                  H a n d l e  P G N 6 5 2 6 2
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn65262(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn110;
        uint8_t         spn174;
        uint16_t        spn175;
        uint16_t        spn176;
        uint8_t         spn52;
        uint8_t         spn1134;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);

        // SPN 110  1       8bits       Engine Coolant Temperature
        spn110 = pMsg->DATA.bytes[0];
        // SPN 174  2       8bits       Engine Fuel Temperature 1
        spn174 = pMsg->DATA.bytes[1];
        // SPN 175  3-4     16bits      Engine Oil Temperature 1
        spn175 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);
        // SPN 176  5-6     16bits      Engine Turbocharger Oil Temperature
        spn176 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 52   7       8bits       Engine Intercooler Temperature
        spn52 = pMsg->DATA.bytes[6];
        // SPN 1134 8       8bits       Engine Intercooler Thermostat Opening
        spn1134 = pMsg->DATA.bytes[7];
        
        
        
        
        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 3
    //---------------------------------------------------------------
    
    bool            j1939en_HandlePgn65263(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn94;
        uint8_t         spn22;
        uint8_t         spn98;
        uint8_t         spn100;
        uint16_t        spn101;
        uint8_t         spn109;
        uint8_t         spn111;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 94   1       8bits       Engine Fuel Delivery Pressure
        spn94 = pMsg->DATA.bytes[0];
        // SPN 22   2       8bits       Engine Extended Crankcase Blow-by Pressure
        spn22 = pMsg->DATA.bytes[1];
        // SPN 98   3       8bits       Engine Oil Level
        spn98 = pMsg->DATA.bytes[2];
        // SPN 100  4       8bits       Engine Oil Pressure
        spn100 = pMsg->DATA.bytes[3];
        // SPN 101  5-6     16bits      Engine Crankcase Pressure
        spn101 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 109  4       8bits       Engine Coolant Pressure
        spn109 = pMsg->DATA.bytes[6];
        // SPN 111  4       8bits       Engine Coolant Level
        spn111 = pMsg->DATA.bytes[7];
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 4
    //---------------------------------------------------------------
    
    bool            j1939en_HandlePgn65264(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn90;
        uint16_t        spn186;
        uint16_t        spn187;
        uint8_t         spn980;
        uint8_t         spn979;
        uint8_t         spn978;
        uint8_t         spn984;
        uint8_t         spn983;
        uint8_t         spn982;
        uint8_t         spn981;
        uint8_t         spn2897;
        uint8_t         spn3447;
        uint8_t         spn3448;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 90   1       8bits       Power Takeoff Oil Temperature
        spn90 = pMsg->DATA.bytes[0];
        // SPN 186  2-3     16bits      Power Takeoff Speed
        spn186 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        // SPN 187  4-5     16bits      Power Takeoff Set Speed
        spn187 = pMsg->DATA.bytes[3] | (pMsg->DATA.bytes[4] << 8);
        // SPN 980  6.1     2bits       Engine PTO Enable Switch
        spn980 = pMsg->DATA.bytes[5] & 0x3;
        // SPN 979  6.3     2bits       Engine Remote PTO Preprogrammed Speed Control Switch
        spn979 = (pMsg->DATA.bytes[5] >> 2) & 0x3;
        // SPN 978  6.5     2bits       Engine Remote PTO Variable Speed Control Switch
        spn978 = (pMsg->DATA.bytes[5] >> 4) & 0x3;
        // SPN 984  7.1     2bits       Engine PTO Set Switch
        spn984 = pMsg->DATA.bytes[6] & 0x3;
        // SPN 983  7.3     2bits       Engine PTO Coast/Decelerate Switch
        spn983 = (pMsg->DATA.bytes[6] >> 2) & 0x3;
        // SPN 982  7.5     2bits       Engine PTO Resume Switch
        spn982 = (pMsg->DATA.bytes[6] >> 4) & 0x3;
        // SPN 981  7.7     2bits       Engine PTO Accelerate Switch
        spn981 = (pMsg->DATA.bytes[6] >> 6) & 0x3;
        // SPN 2897 8.1     2bits       Operator PTO Memory Select Switch
        spn2897 = pMsg->DATA.bytes[7] & 0x3;
        // SPN 3447 8.3     2bits       Remote PTO preprogrammed speed control switch #2
        spn3447 = (pMsg->DATA.bytes[7] >> 2) & 0x3;
        // SPN 3448 8.5     2bits       Auxiliary Input Ignore Switch
        spn3448 = (pMsg->DATA.bytes[7] >> 4) & 0x3;
        
        
        
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 5
    //---------------------------------------------------------------

    bool            j1939en_HandlePgn65265(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
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
    //               H a n d l e  P G N 6 5 2 7 2   EBC1        TRF1
    //---------------------------------------------------------------
    
    bool            j1939en_HandlePgn65272(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn123;
        uint8_t         spn124;
        uint8_t         spn126;
        uint8_t         spn127;
        uint16_t        spn177;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        if (pMsg) {
            spn123 = pMsg->DATA.bytes[0];
            spn124 = pMsg->DATA.bytes[1];
            spn126 = pMsg->DATA.bytes[2];
            spn127 = pMsg->DATA.bytes[3];
            spn177 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //           H a n d l e  T i m e d  T r a n s m i t s
    //---------------------------------------------------------------

    bool            j1939en_HandleTimedTransmits(
        J1939EN_DATA	*this
    )
    {
        uint32_t        curTime;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        curTime = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        this->curTime = curTime;

        if (curTime  >= this->startTimeOperation) {
            j1939en_Operation(this);
        }

        if (j1939ca_getTimedTransmits((J1939CA_DATA *)this)) {
            if ((curTime - this->time61443.msTime) >= this->time61443.msDelay) {
                j1939en_TransmitPgn61443(this);
            }
            if ((curTime - this->time61444.msTime) >= this->time61444.msDelay) {
                j1939en_TransmitPgn61444(this);
            }
            if ((curTime - this->time65129.msTime) >= this->time65129.msDelay) {
                j1939en_TransmitPgn65129(this);
            }
            if ((curTime - this->time65247.msTime) >= this->time65247.msDelay) {
                j1939en_TransmitPgn65247(this);
            }
            if (this->fShutdown
                && ((curTime - this->time65252.msTime) >= this->time65252.msDelay)) {
                j1939en_TransmitPgn65252(this);
            }
            if ((curTime - this->time65262.msTime) >= this->time65262.msDelay) {
                j1939en_TransmitPgn65262(this);
            }
            if ((curTime - this->time65265.msTime) >= this->time65265.msDelay) {
                j1939en_TransmitPgn65265(this);
            }
            if ((curTime - this->time65266.msTime) >= this->time65266.msDelay) {
                j1939en_TransmitPgn65266(this);
            }
            if ((curTime - this->time65279.msTime) >= this->time65279.msDelay) {
                j1939en_TransmitPgn65279(this);
            }
        }
        if (this->fRetarding) {
            j1939en_HandlePgn0(this, NULL);
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                        I n i t
    //---------------------------------------------------------------

    J1939EN_DATA *	j1939en_Init(
        J1939EN_DATA    *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint16_t		cbSize = sizeof(J1939EN_DATA);
        uint32_t        curTime;

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
#endif

        this =   (J1939EN_DATA *)j1939ca_Init(
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
        obj_setIdent( (OBJ_ID)this, OBJ_IDENT_J1939EN );
        this->pCaVtbl = (void *)obj_getVtbl(this);
        obj_setVtbl(  (OBJ_ID)this, (OBJ_IUNKNOWN *)&j1939en_Vtbl );

        j1939ca_Setup((J1939CA_DATA *)this, J1939_ENGINE_1);
        //this->super.name.ECU = 0;
        this->super.name.FU = 12;
        this->super.name.FUI = 1;
        
        // All of our tests that captured messages from startup in a real truck
        // did not show the engine or transmission claiming their name.  They
        // just assumed they had the names.
        j1939ca_Setup((J1939CA_DATA *)this, J1939_ENGINE_1);
        this->super.cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we have our name.
        this->super.pRcvPgnTbl = &rcvPgnTbl;
        this->super.pXmtPgnTbl = &xmtPgnTbl;
        this->super.pTimedTransmit =
                    (P_HANDLE_TIMED_TRANSMITS)&j1939en_HandleTimedTransmits;

        // Default all SPNs to unsupported values.
        memset(
               &this->spnFirst,
               0xFF,
               (offsetof(J1939EN_DATA,spnLast) - offsetof(J1939EN_DATA,spnFirst)
                + sizeof(uint32_t))
               );
        this->spn1483 = J1939_ENGINE_1;
        this->spn110  = 0x67;       // spn110 - Engine Coolant Temp - 63 C
        this->spn514  = 0x8D;       // spn514 - Nominal Friction - Percent Torque - 16%

        this->time61443.msDefault = pgn61443_entry.msFreq;
        this->time61443.msDelay = pgn61443_entry.msFreq;
        this->time61443.pgn = 61443;
        
        this->time61444.msDefault = pgn61444_entry.msFreq;
        this->time61444.msDelay = pgn61444_entry.msFreq;
        this->time61444.pgn = 61444;
        
        this->time65129.msDefault = pgn65129_entry.msFreq;
        this->time65129.msDelay = pgn65129_entry.msFreq;
        this->time65129.pgn = 65129;
        
        this->time65247.msDefault = pgn65247_entry.msFreq;
        this->time65247.msDelay = pgn65247_entry.msFreq;
        this->time65247.pgn = 65247;
        
        this->time65252.msDefault = pgn65252_entry.msFreq;
        this->time65252.msDelay = pgn65252_entry.msFreq;
        this->time65252.pgn = 65252;
        
        this->time65262.msDefault = pgn65262_entry.msFreq;
        this->time65262.msDelay = pgn65262_entry.msFreq;
        this->time65262.pgn = 65262;
        
        this->time65265.msDefault = pgn65265_entry.msFreq;
        this->time65265.msDelay = pgn65265_entry.msFreq;
        this->time65265.pgn = 65265;
        
        this->time65266.msDefault = pgn65266_entry.msFreq;
        this->time65266.msDelay = pgn65266_entry.msFreq;
        this->time65266.pgn = 65266;
        
        this->time65279.msDefault = pgn65279_entry.msFreq;
        this->time65279.msDelay = pgn65279_entry.msFreq;
        this->time65279.pgn = 65279;
        
#ifdef NDEBUG
#else
        BREAK_NOT_BOUNDARY4(offsetof(J1939EN_DATA,timeOut));
        BREAK_NOT_BOUNDARY4(offsetof(J1939EN_DATA,spnFirst));
        BREAK_NOT_BOUNDARY4(offsetof(J1939EN_DATA,spn84));
        BREAK_NOT_BOUNDARY4(offsetof(J1939EN_DATA,spnLast));
        BREAK_NOT_BOUNDARY4(offsetof(J1939EN_DATA,pShiftExit));
        BREAK_NOT_BOUNDARY4(sizeof(J1939EN_DATA));
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
    //                        N e w  R p m
    //---------------------------------------------------------------
    
    ERESULT         j1939en_NewRpm(
        J1939EN_DATA	*this,
        uint16_t        rpm
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        switch (this->state) {

            case J1939EN_STATE_STOPPED:
                break;
                
            case J1939EN_STATE_HEATERS_ON:
                break;
                
            case J1939EN_STATE_STARTER_ENGAGED:
                break;
                
            case J1939TC_STATE_RUNNING:
                break;
                
            case J1939TC_STATE_RUNNING_RETARDED:
                break;
                
        }
        
        // Return to caller.
        j1939en_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O p e r a t i o n
    //---------------------------------------------------------------
    
    ERESULT         j1939en_Operation(
        J1939EN_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        switch (this->state) {

            case J1939EN_STATE_STOPPED:
                break;
                
            case J1939EN_STATE_HEATERS_ON:
                if (this->spn1675 == 0b001) {
                    this->startTimeOperation = this->curTime + 250; // ms
                    break;
                }
                break;
                
            case J1939EN_STATE_STARTER_ACTIVATE:
                this->startTimeOperation = this->curTime + 250; // ms
                if (this->spn1675 == 0b000) {
                    this->spn1675 = 0b001;
                    this->startTimeOperation = this->curTime + 250; // ms
                    break;
                }
               break;
                
            case J1939EN_STATE_STARTER_ACTIVE:
                this->startTimeOperation = this->curTime + 250; // ms
                break;
                
            case J1939EN_STATE_STARTER_ENGAGED:
                break;
                
            case J1939TC_STATE_RUNNING:
                break;
                
            case J1939TC_STATE_RUNNING_RETARDED:
                break;
                
            case J1939TC_STATE_SHUTDOWN_PHASE1:
                break;
                
            case J1939TC_STATE_SHUTDOWN_PHASE2:
                break;
                
        }
        
        // Return to caller.
        j1939en_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S h u t d o w n
    //---------------------------------------------------------------
    
    ERESULT         j1939en_Shutdown(
        J1939EN_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return j1939en_getLastError(this);
        }
#endif
        
        // Put code here...
        
        // Return to caller.
        j1939en_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S t a r t
    //---------------------------------------------------------------
    
    ERESULT         j1939en_Start(
        J1939EN_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939en_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Put code here...
        
        // Return to caller.
        j1939en_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_NOT_IMPLEMENTED;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 3   0xF003
    //---------------------------------------------------------------

    // Electronic Engine Controller 2 - EEC2 -
    // Unused bits are set to 1.
    int             j1939en_SetupPgn61443(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        
        if (pPDU) {
            pPDU->PF = (pgn61443_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn61443_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn61443_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return false;
            }
            *pData  = 0xC0;
            *pData |= this->spn558 & 0x3;           // Accelerator Pedal 1 Low Idle Switch
            *pData |= (this->spn559 & 0x3) << 2;    // Accelerator Pedal Kickdown Switch
            *pData |= (this->spn1437 & 0x3) << 4;   // Road Speed Limit Status
            ++pData;    // 1
            *pData  = this->spn91;                  // Accelerator Pedal Position 1
            ++pData;    // 2
            *pData  = this->spn92;                  // Percent Load At Current Speed
            ++pData;    // 3
            *pData  = this->spn974;                 // Remote Accelerator Pedal Position
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


    bool            j1939en_TransmitPgn61443(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;

        len = j1939en_SetupPgn61443(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time61443.msTime = this->curTime;

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 4              0xF004
    //---------------------------------------------------------------

    // Electronic Engine Controller 1 - EEC1 -
    // Unused bits are set to 1.
    int             j1939en_SetupPgn61444(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        // Fake the engine stuff.

        if (pPDU) {
            pPDU->PF = (pgn61444_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn61444_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn61444_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0xF0;
            *pData |= this->spn899 & 0xF;   // Engine Torque Mode
            ++pData;    // 1
            *pData  = this->spn512;         // Driver's Demand Engine - Percent Torque
            ++pData;    // 2
            *pData  = this->spn513;         // Actual Engine - Percent Torque
            ++pData;    // 3
            *pData  = this->spn190 & 0xFF;  // Engine Speed
            ++pData;    // 4
            *pData  = (this->spn190 >> 8) & 0xFF;
            ++pData;    // 5
            *pData  = this->spn1483;        // Source Address of Controlling Device
            ++pData;    // 6
            *pData  = 0xF0;
            *pData |= this->spn1675 & 0xF;  // Engine Starter Mode
            ++pData;    // 7
            *pData  = this->spn2432;        // Engine Demand - Percent Torque
        }
        else {
            return 0;
        }

        // Return to caller.
        return 8;
    }


    bool            j1939en_TransmitPgn61444(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;

        len = j1939en_SetupPgn61444(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time61444.msTime = this->curTime;

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 1 2 9   0xFE69
    //---------------------------------------------------------------

    /* Engine Temperature 3 - ET3 -
     * Freq: 1000 ms
     * Priority: 6
     */
    int             j1939en_SetupPgn65129(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn65129_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65129_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65129_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn1636 & 0xFF;
            ++pData;    // 1
            *pData  = (this->spn1636 >> 8) & 0xFF;
            ++pData;    // 2
            *pData  = this->spn1637 & 0xFF;
            ++pData;    // 3
            *pData  = (this->spn1637 >> 8) & 0xFF;
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


    bool            j1939en_TransmitPgn65129(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;

        len = j1939en_SetupPgn65129(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65129.msTime = this->curTime;

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 4 7   0x00FEDF
    //---------------------------------------------------------------

    /* Electronic Engine Controller 3 - EEC3 -
     * Freq: 250 ms
     * Priority: 6
     */
    int             j1939en_SetupPgn65247(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn65247_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65247_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65247_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn514;
            ++pData;    // 1
            *pData  = this->spn515 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn515 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = this->spn519;
            ++pData;    // 4
            *pData  = this->spn2978;
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


    bool            j1939en_TransmitPgn65247(
        J1939EN_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;

        len = j1939en_SetupPgn65247(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }

        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65247.msTime = this->curTime;

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 5 2   0x00FEE4  SHUTDOW
    //---------------------------------------------------------------
    
    /* Shutdown - SHUTDOW -
     * Freq: 1000 ms
     * Priority: 6
     */
    int             j1939en_SetupPgn65252(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65252_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65252_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65252_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData = 0xFF;
            ++pData;    // 1
            *pData  = 0xFF;
            ++pData;    // 2
            *pData  = 0xFF;
            ++pData;    // 3
            *pData  = 0xFF;
            ++pData;    // 4
            *pData  = 0xF0;
            *pData  |= (this->spn1110 & 0b11);
            *pData  |= (this->spn1109 & 0b11) << 2;
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
    
    
    bool            j1939en_TransmitPgn65252(
        J1939EN_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu;
        bool            fRc = false;
        int             len;
        
        len = j1939en_SetupPgn65252(this, &pdu, 8, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65252.msTime = this->curTime;
        
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
    int             j1939en_SetupPgn65262(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn65262_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65262_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65262_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn110 & 0xFF;
            ++pData;    // 1
            *pData  = this->spn174 & 0xFF;
            ++pData;    // 2
            *pData  = this->spn175 & 0xFF;
            ++pData;    // 3
            *pData  = (this->spn175 >> 8) & 0xFF;
            ++pData;    // 4
            *pData  = this->spn176 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn176 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = this->spn52 & 0xFF;
            ++pData;    // 7
            *pData  = this->spn1134 & 0xFF;
        }
        else {
            return 0;
        }

        // Return to caller.
        return 8;
    }


    bool            j1939en_TransmitPgn65262(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;

        len = j1939en_SetupPgn65262(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }

        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65262.msTime = this->curTime;

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 5   0xFEF1       CCVS
    //---------------------------------------------------------------

    /* Cruise Control/Vehicle Speed - CCVS -
     * Freq: 100 ms
     * Priority: 6
     */
    int             j1939en_SetupPgn65265(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {

        if (pPDU) {
            pPDU->PF = (pgn65265_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65265_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65265_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0xC0;
            *pData |= (this->spn69 & 0x3);
            *pData |= (this->spn70 & 0x3) << 2;
            *pData |= (this->spn1633 & 0x3) << 4;
            ++pData;    // 1
            *pData  = this->spn84 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn84 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = 0;
            *pData |= (this->spn595 & 0x3);
            *pData |= (this->spn596 & 0x3) << 2;
            *pData |= (this->spn597 & 0x3) << 4;
            *pData |= (this->spn598 & 0x3) << 6;
            ++pData;    // 4
            *pData  = 0;
            *pData |= (this->spn599 & 0x3);
            *pData |= (this->spn600 & 0x3) << 2;
            *pData |= (this->spn601 & 0x3) << 4;
            *pData |= (this->spn602 & 0x3) << 6;
            ++pData;    // 5
            *pData  = (this->spn86 & 0xFF);
            ++pData;    // 6
            *pData  = 0;
            *pData |= (this->spn976 & 0x1F);
            *pData |= (this->spn527 & 0x7) << 5;
            ++pData;    // 7
            *pData  = 0;
            *pData |= (this->spn968 & 0x3);
            *pData |= (this->spn967 & 0x3) << 2;
            *pData |= (this->spn966 & 0x3) << 4;
            *pData |= (this->spn1237 & 0x3) << 6;
        }
        else {
            return 0;
        }

        // Return to caller.
        return 8;
    }


    bool            j1939en_TransmitPgn65265(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;

        len = j1939en_SetupPgn65265(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }

        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65265.msTime = this->curTime;

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 6   0xFEF2        LFE
    //---------------------------------------------------------------
    
    // PGN 65266  0x00FEF2 - Fuel Economy (Liquid) - LFE
    // Freq: 100 ms
    // Priority: 6
    
    int             j1939en_SetupPgn65266(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65266_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65266_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65266_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn183 & 0xFF;
            ++pData;    // 1
            *pData  = (this->spn183 >> 8) & 0xFF;
            ++pData;    // 2
            *pData  = this->spn184 & 0xFF;
            ++pData;    // 3
            *pData  = (this->spn184 >> 8) & 0xFF;
            ++pData;    // 4
            *pData  = (this->spn185 & 0xFF);
            ++pData;    // 5
            *pData  = (this->spn185 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = this->spn51;
            ++pData;    // 7
            *pData  = 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939en_TransmitPgn65266(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;
        
        len = j1939en_SetupPgn65266(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65266.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 7 9   0xFEFF        WFI
    //---------------------------------------------------------------
    
    // PGN 65279  0x00FEFF - Water in Fuel Indicator - WFI
    // Freq: 100 ms
    // Priority: 6
    
    int             j1939en_SetupPgn65279(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        int             i;
        
        if (pPDU) {
            pPDU->PF = (pgn65279_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65279_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65279_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0xF8;
            *pData |= (this->spn97 & 0x3);
            for (i=1; i<8; ++i) {
                ++pData;
                *pData  = 0xFF;
            }
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939en_TransmitPgn65279(
        J1939EN_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;
        
        len = j1939en_SetupPgn65279(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65279.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      Validate
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool            j1939en_Validate(
        J1939EN_DATA	*this
    )
    {
        if(this) {
            if ( obj_IsKindOf( this, OBJ_IDENT_J1939EN ) )
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
