// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   j1939er_internal.h
 * Author: bob
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *
 * Created on September 26, 2014, 3:39 PM
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




#include        <j1939er.h>
#include        <j1939ca_internal.h>


#ifndef J1939ER_INTERNAL_H
#define	J1939ER_INTERNAL_H 1


#ifdef	__cplusplus
extern "C" {
#endif


    //                  Main Control j1939er
    /* This control j1939er resides only in memory and is used to provide
     * the information necessary to access the j1939er data.
     */


#pragma pack(push, 1)
    struct j1939er_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        J1939CA_DATA        super;
        J1939CA_VTBL        *pCaVtbl;

        // Common Data
        ERESULT             eRc;
        
        uint32_t            startTime61440;     // Repeat every 100ms
        uint32_t            startTime65249;     // Repeat every 5s

        // The first spn is used in Init() to establish size of area to initialize.
        uint8_t             spn520;             // Actual Retarder - Percent Torque
                                                // offset: -125%, -125 to 125 (0 - 250)
        uint8_t             spn571;             // Retarder Enable - Brake Assist Switch
                                                // 00 == Retarder Brake Assist disabled
                                                // 01 == Retarder Brake Assist enabled
        uint8_t             spn572;             // Retarder Enable - Brake Assist Switch
                                                // 00 == Retarder Shift Assist disabled
                                                // 01 == Retarder Shift Assist enabled
        uint8_t             spn900;             // Retarder Torque Mode
                                                //  0 == No Braking
                                                //  1 == Accelerator pedal/operator selection
                                                //  2 == Cruise control
                                                //  3 == PTO governor
                                                //  4 == Road speed governor
                                                //  5 == ASR control
                                                //  6 == Transmission control
                                                //  7 == ABS control
                                                //  8 == Torque limiting
                                                //  9 == High speed governor
                                                // 10 == Braking system
                                                // 11 == Remote accelerator
                                                // 12 == Service procedure
                                                // 13 == not defined
                                                // 14 == Other
                                                // 15 == Not available
        uint8_t             spn1082;            // Engine Coolant Load Increase
        uint8_t             spn1085;            // Intended Retarder Percent Torque
                                                // offset: -125%, -125 to 125 (0 - 250)
        uint8_t             spn1480;            // CA of Controlling Retarder Device
        uint8_t             spn1667;            // Retarder requesting Brake Light
        uint8_t             spn1715;            // Drivers Demand Retarder - Percent Torque
                                                // offset: -125%, -125 to 0 (0 - 125)
        uint8_t             spn1716;            // Retarder Selection - non-engine
                                                // offset: 0, 0.4/bit (0 - 100)
        uint8_t             spn1717;            // Actual Maximum Available Retarder
                                                // - Percent Torque
                                                // offset: -125%, -125 to 0 (0 - 125)
        uint8_t             reserved8b[1];

        // Engine Fields - 2 bytes
        uint16_t            spn84;              // Wheel-Based Vehicle Speed
        uint16_t            spn175;             // Engine Oil Temperature 1
        uint16_t            spn176;             // Turbo Oil Temperature
        uint16_t            spn190;             // Engine Speed
        uint16_t            spn515;             // Engine's Desired Operating Speed
        uint16_t            spn1636;            // Intake Manifold 1 Air Temperature
        uint16_t            spn1637;            // Engine Coolant Temperature
        uint16_t            reserved16;
        // The last spn is used in Init() to establish size of area to initialize.

        uint32_t            timeOut;
        uint8_t             fActive;
        uint8_t             rsvd8[3];

    };
#pragma pack(pop)


    extern
    const
    J1939ER_VTBL    j1939er_Vtbl;



    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/

    void            j1939er_Dealloc(
        OBJ_ID          objId
    );


    bool            j1939er_HandlePgn0(
        J1939ER_DATA	*cbp,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939er_HandlePgn61440(
        J1939ER_DATA	*cbp,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939er_HandlePgn61444(
        J1939ER_DATA	*cbp,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939er_HandlePgn65129(
        J1939ER_DATA	*cbp,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939er_HandlePgn65247(
        J1939ER_DATA	*cbp,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939er_HandlePgn65262(
        J1939ER_DATA	*cbp,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939er_HandlePgn65265(
        J1939ER_DATA	*cbp,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    int             j1939er_SetupPgn61440(
        J1939ER_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );





#ifdef	__cplusplus
}
#endif

#endif	/* J1939ER_INTERNAL_H */
