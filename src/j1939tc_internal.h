// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939tc_internal.h
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




#ifndef J1939TC_INTERNAL_H
#define	J1939TC_INTERNAL_H


#include        "j1939tc.h"
#include        "j1939ca_internal.h"


#ifdef	__cplusplus
extern "C" {
#endif


    typedef enum j1939tc_state_e {
        J1939TC_STATE_START=0,
        J1939TC_STATE_TELLING_ENGINE_ABOUT_TO_SHIFT,
        J1939TC_STATE_TELLING_RETARDER_ABOUT_TO_SHIFT,
        J1939TC_STATE_WAITING_FOR_ENGINE,
        J1939TC_STATE_WAITING_FOR_RETARDER,
        J1939TC_STATE_SHIFTING,
        J1939TC_STATE_TELLING_RETARDER_SHIFTED,
        J1939TC_STATE_TELLING_ENGINE_SHIFTED,
        J1939TC_STATE_CHECKVALUE
    } J1939TC_STATE;




    //                  Main Control j1939tc
    /* This control j1939tc resides only in memory and is used to provide
     * the information necessary to access the j1939tc data.
     */


#pragma pack(push, 1)
    struct j1939tc_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        J1939CA_DATA        super;
        J1939CA_VTBL        *pCaVtbl;

        uint32_t            startTime0_10;      // Repeat every 10ms
        uint32_t            startTime0_50;      // Repeat every 50ms
        uint32_t            startTime61442;     // Repeat every 10ms
        uint32_t            startTime61445;     // Repeat every 100ms
        uint32_t            startTime65098;     // Repeat every 100ms
        uint32_t            startTime65226;     // Repeat every 1000ms
        uint32_t            startTime65272;     // Repeat every 1000ms

        // The first spn is used in Init() to establish size of area to initialize.
        uint8_t             spn123;             // Clutch Pressure
        uint8_t             spn124;             // Transmission Oil Level
        uint8_t             spn126;             // Transmission Filter Differential Pressure
        uint8_t             spn127;             // Transmission Oil Pressure
        uint8_t             spn518;             // Engine Requested Torque/Torque Limit
        uint8_t             spn522;             // Percent Clutch Slip
        uint8_t             spn523;             // Transmission Current Gear
        uint8_t             spn524;             // Transmission Selected Gear
        uint8_t             spn525;             // Transmission Requested Gear
        uint8_t             spn560;             // Transmission Driveline Engaged
                                                // 00 == Driveline disengaged
                                                // 01 == Driveline engaged
                                                // 10 == Error
        uint8_t             spn573;             // Transmission Torque Converter Lockup Engaged
                                                // 00 == Torque converter lockup disengaged
                                                // 01 == Torque converter lockup engaged
                                                // 10 == Error
        uint8_t             spn574;             // Transmission Shift In Process
                                                // 00 == Shift is not in process
                                                // 01 == Shift is in process
                                                // 10 == Error
        uint8_t             spn606;             // Engine Momentary Overspeed Enable
                                                // 00 == Momentary engine overspeed disabled
                                                // 01 == Momentary engine overspeed enabled
        uint8_t             spn607;             // Progressive Shift Disable
                                                // 00 == Progressive shift disabled
                                                // 01 == Progressive shift enabled
        uint8_t             spn695;             // Engine Override Control Mode
                                                // 00 Override disabled - Disable any
                                                //  existing control commanded by the
                                                //  source of this command.
                                                // 01 Speed control - Govern speed to
                                                //  the included “desired speed” value.
                                                // 10 Torque control - Control torque to
                                                //  the included “desired torque” value.
                                                // 11 Speed/torque limit control - Limit
                                                //  speed and/or torque based on the
                                                //  included limit values. The speed limit
                                                //  governor is a droop governor where the
                                                //  speed limit value defines the speed at
                                                //  the maximum torque available during
                                                //  this operation.
        uint8_t             spn696;             // Engine Requested Speed Control Conditions
                                                // 00 Transient Optimized for driveline
                                                //  disengaged and non-lockup conditions
                                                // 01 Stability Optimized for driveline
                                                //  disengaged and non-lockup conditions
                                                // 10 Stability Optimized for driveline
                                                //  engaged and/or in lockup condition 1
                                                //  (e.g., vehicle driveline)
                                                // 11 Stability Optimized for driveline
                                                //  engaged and/or in lockup condition 2
                                                //  (e.g., PTO driveline)
        uint8_t             spn897;             // Override Control Mode Priority
        uint8_t             spn1482;            // Source Address of Controlling Device
                                                // for Transmission Control
        uint8_t             spn1849;            // Transmission Requested Range Display
                                                // Flash State
        uint8_t             spn1850;            // Transmission Requested Range Display
                                                // Blank State
        uint8_t             spn1851;            // Transmission Shift Inhibit Indicator
        uint8_t             spn2536;            // Transmission Mode 1 Indicator
        uint8_t             spn2537;            // Transmission Mode 2 Indicator
        uint8_t             spn2538;            // Transmission Mode 3 Indicator
        uint8_t             spn2539;            // Transmission Mode 4 Indicator
        uint8_t             spn2900;            // Transmission Engine Crank Enable
        uint8_t             spn2945;            // Active Shift Console Indicator
        uint8_t             spn3086;            // Transmission Ready for Brake Release
        uint8_t             spn3289;            // Transmission Requested Gear Feedback
        uint8_t             spn3349;            // TSC1 Transmission Rate
        uint8_t             spn3350;            // TSC1 Control Purpose
        uint8_t             reserved8b[1];

        // Engine Fields - 2 bytes
        uint16_t            spn161;             // Transmission Input Shaft Speed
        uint16_t            spn162;             // Transmission Requested Range
        uint16_t            spn163;             // Transmission Current Range
        uint16_t            spn177;             // Transmission Oil Termperature
        uint16_t            spn191;             // Transmission Output Shaft Speed
        uint16_t            spn526;             // Transmission Actual Gear Ratio
        uint16_t            spn898;             // Engine Requested Speed/Speed Limit
        uint16_t            reserved16;
        // The last spn is used in Init() to establish size of area to initialize.

        uint32_t            timeOut;
        uint8_t             fActive;

    };
#pragma pack(pop)


    extern
    const
    J1939TC_VTBL    j1939tc_Vtbl;



    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/

    void            j1939tc_Dealloc(
        OBJ_ID          objId
    );


    bool            j1939tc_HandlePgn256(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939tc_HandlePgn61184(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939tc_HandlePgn61441(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );
    
    
    bool            j1939tc_HandlePgn61442(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939tc_HandlePgn61444(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939tc_HandlePgn65098(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939tc_HandlePgn65129(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939tc_HandlePgn65226(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939tc_HandlePgn65265(
        J1939TC_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939tc_SetupPgn0(
        J1939TC_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939tc_SetupPgn61442(
        J1939TC_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939tc_SetupPgn61445(
        J1939TC_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939tc_SetupPgn65098(
        J1939TC_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );


    bool            j1939tc_SetupPgn65226(
        J1939TC_DATA	*cbp,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData,
        uint16_t        *pLen
    );




#ifdef	__cplusplus
}
#endif

#endif	/* J1939TC_INTERNAL_H */
