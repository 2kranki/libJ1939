// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   j1939en_internal.h
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




#ifndef J1939EN_INTERNAL_H
#define	J1939EN_INTERNAL_H


#include        <j1939en.h>
#include        <j1939ca_internal.h>
//#include        "canrsp.h"


#ifdef	__cplusplus
extern "C" {
#endif


    //                  Main Control j1939en
    /* This control j1939en resides only in memory and is used to provide
     * the information necessary to access the j1939en data.
     */


#pragma pack(push, 1)
    struct j1939en_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        J1939CA_DATA        super;
        J1939CA_VTBL        *pCaVtbl;

        uint32_t            startTime61443;     // Repeat every 50ms
        uint32_t            startTime61444;     // Repeat engine speed dependent
                                                // (100ms for now)
        uint32_t            startTime65129;     // Repeat every 1000ms
        uint32_t            startTime65247;     // Repeat every 250ms
        uint32_t            startTime65262;     // Repeat every 1000ms
        uint32_t            startTime65265;     // Repeat every 100ms

        // The first spn is used in Init() to establish size of area to initialize.
        uint8_t             spn52;              // Engine Intercooler Temperature
        uint8_t             spn69;              // Two Speed Axle Switch
        uint8_t             spn70;              // Parking Brake Switch
        uint8_t             spn86;              // Cruise Control Set Speed

        uint8_t             spn91;              // Accelerator Pedal Position 1
        uint8_t             spn92;              // Percent Load At Current Speed
        uint8_t             spn110;             // Engine Coolant Temperature
        uint8_t             spn174;             // Fuel Temperature

        uint8_t             spn512;             // Driver's Demand Engine - Percent Torque
        uint8_t             spn513;             // Actual Engine - Percent Torque
        uint8_t             spn514;             // Nominal Friction - Percent Torque
        uint8_t             spn519;             // Engine's Desired Operating Speed
                                                // Asymmetry Adjustment

        uint8_t             spn523;             // 03 - Transmission Current Gear
        uint8_t             spn524;             // 03 - Transmission Selected Gear
        uint8_t             spn527;             // Cruise Control States
        uint8_t             spn558;             // Accelerator Pedal 1 Low Idle Switch

        uint8_t             spn559;             // Accelerator Pedal Kickdown Switch
        uint8_t             spn574;             // Transmission Shift In Process
        uint8_t             spn595;             // Cruise Control Active
        uint8_t             spn596;             // Cruise Control Enable Switch

        uint8_t             spn597;             // Brake Switch
        uint8_t             spn598;             // Clutch Switch
        uint8_t             spn599;             // Cruise Control Set Switch
        uint8_t             spn600;             // Cruise Control Coast (Decelerate) Switch

        uint8_t             spn601;             // Cruise Control Resume Switch
        uint8_t             spn602;             // Cruise Control Accelerate Switch
        uint8_t             spn899;             // Engine Torque Mode
        uint8_t             spn966;             // Engine Test Mode Switch

        uint8_t             spn967;             // Idle Decrement Switch
        uint8_t             spn968;             // Idle Increment Switch
        uint8_t             spn974;             // Remote Accelerator Pedal Position
        uint8_t             spn976;             // PTO State

        uint8_t             spn1134;            // Engine Intercooler Thermostat Opening
        uint8_t             spn1237;            // Engine Shutdown Override Switch
        uint8_t             spn1437;            // Road Speed Limit Status
        uint8_t             spn1480;            // CA of Controlling Retarder Device

        uint8_t             spn1483;            // Source Address of Controlling Device
                                                // for Engine Control
        uint8_t             spn1633;            // Cruise Control Pause Switch
        uint8_t             spn1675;            // Engine Starter Mode
        uint8_t             spn2432;            // Engine Demand - Percent Torque

        uint8_t             spn2978;            // Estimated Engine Parasitic Losses -
                                                // Percent Torque
        uint8_t             reserved8b[3];

        // Engine Fields - 2 bytes
        uint16_t            spn84;              // Wheel-Based Vehicle Speed
        uint16_t            spn161;             // 03 - Transmission Input Shaft Speed
        uint16_t            spn175;             // Engine Oil Temperature 1
        uint16_t            spn176;             // Turbo Oil Temperature
        uint16_t            spn190;             // Engine Speed
        uint16_t            spn191;             // 03 - Transmission Output Shaft Speed
        uint16_t            spn515;             // Engine's Desired Operating Speed
        uint16_t            spn1636;            // Intake Manifold 1 Air Temperature
        uint16_t            spn1637;            // Engine Coolant Temperature
        uint16_t            reserved16;
        // The last spn is used in Init() to establish size of area to initialize.

        uint32_t            timeOut;
        uint8_t             fActive;            // Retarding is Active
        uint8_t             fShifting;          // Shift in progress
        uint8_t             reserved8c[2];
        P_VOIDEXIT12        pShiftExit;
        void                *pShiftData;

    };
#pragma pack(pop)


    extern
    const
    J1939EN_VTBL    j1939en_Vtbl;



    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/

    void            j1939en_Dealloc(
        OBJ_ID          objId
    );


    bool            j1939en_HandlePgn0(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61184(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61442(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61443(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61444(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61445(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65129(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65247(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65262(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65265(
        J1939EN_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_SetupPgn61443(
        J1939EN_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939en_SetupPgn61444(
        J1939EN_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939en_SetupPgn65129(
        J1939EN_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939en_SetupPgn65247(
        J1939EN_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939en_SetupPgn65262(
        J1939EN_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939en_SetupPgn65265(
        J1939EN_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );



#ifdef NDEBUG
#else
    static
    bool            j1939en_Validate(
        J1939EN_DATA      *cbp
    );
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* J1939EN_INTERNAL_H */
