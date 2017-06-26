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
        
        uint32_t            curTime;
        uint32_t            timeOut;
        J1939CA_TIME_DELAY  time61440;
        J1939CA_TIME_DELAY  time65249;
        J1939CA_TIME_DELAY  time65275;

        // The first spn is used in Init() to establish size of area to initialize.
        uint8_t             spnFirst;
        uint8_t             spn119;             // Hydraulic Retarder Pressure
        // Gage pressure of oil in hydraulic retarder system
        // mult: 16 kPa per bit, offset: 0
        // range: 0 to 1000 kPa
        uint8_t             spn120;             // Hydraulic Retarder Oil Temperature
        // Temperature of oil found in a hydraulic retarder.
        // mult: 1 degree C per bit, offset: -40 C
        // range: -40 C to 210 C
        uint8_t             spn520;             // Actual Retarder - Percent Torque
        // Actual braking torque of the retarder as a percent of retarder configuration
        // reference torque SPN 556.
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 (0 - 250)
        uint8_t             spn571;             // Retarder Enable - Brake Assist Switch
        //                                      // (2 bits)
        // Switch signal which indicates whether the operator wishes the retarder to be
        // enabled for vehicle braking assist. The retarder does not check this switch,
        // nor does the enabling of this switch engage the retarder. When this switch is
        // “enabled,” the devices constructing TSC1 – destination retarder messages may
        // command retarder torque for braking. For example, the cruise control should
        // not request retarder torque if this switch is not “enabled.” The switch exists
        // to prevent the engine retarder from being asked to be engaged via TSC1 in a
        // noise sensitive area. See also SPN 572
        //  00 - Retarder Brake Assist disabled
        //  01 - Retarder Brake Assist enabled
        //  10 - Error
        //  11 - Not available
        uint8_t             spn572;             // Retarder Enable - Brake Assist Switch
        //                                      // (2 bits)
        // Switch signal which indicates whether the operator wishes the retarder to be
        // enabled for transmission shift assist. The retarder does not check this switch,
        // nor does the enabling of this switch engage the retarder. When this switch is
        // “enabled,” the transmission may activate the retarder (via the TSC1 message)
        // to increase the rate of engine deceleration to assist in shift control. The
        // switch exists to prevent the engine retarder from being asked to be engaged
        // via TSC1 in a noise sensitive area. See SPN 571.
        //  00 - Retarder Shift Assist disabled
        //  01 - Retarder Shift Assist enabled
        //  10 - Error
        //  11 - Not available
        uint8_t             spn900;             // Retarder Torque Mode (4 bits)
        // State signal which indicates which retarder torque mode is currently
        // generating, limiting, or controlling the torque. Note that the modes are
        // not in prioritized order. Not all modes may be relevant for a given device.
        // Some devices may not implement all functions. For typical priorities refer
        // to Tables SPN518_A to SPN518_B for retarder control. The data type of this
        // parameter is measured.
        //   0 == No Braking
        //   1 == Accelerator pedal/operator selection
        //   2 == Cruise control
        //   3 == PTO governor
        //   4 == Road speed governor
        //   5 == ASR control
        //   6 == Transmission control
        //   7 == ABS control
        //   8 == Torque limiting
        //   9 == High speed governor
        //  10 == Braking system
        //  11 == Remote accelerator
        //  12 == Service procedure
        //  13 == not defined
        //  14 == Other
        //  15 == Not available
        uint8_t             spn1082;            // Engine Coolant Load Increase
        //                                      // (2 bits)
        // Status of an event, external to the engine, that may increase the nominal
        // temperature of the engine coolant liquid.
        //  00 - No coolant load increase
        //  01 - Coolant load increase possible
        //  10 - Error
        //  11 - Not available
        uint8_t             spn1085;            // Intended Retarder Percent Torque
        // Braking torque of retarder that the retarder is currently trying to achieve.
        // This value takes into account all static limitations, but not the limitations
        // due to the dynamic behavior of the retarder. This value, if unchanged over a
        // certain time, can and will be reached by the actual retarder - percent torque
        // (See SPN 520).
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 (0 - 250)
        uint8_t             spn1480;            // CA of Controlling Retarder Device
        // The source address of the SAE J1939 device currently controlling the retarder.
        // It is used to expand the torque mode parameter (see SPN 899) in cases where
        // control is in response to an ECU that is not listed in Table SPN899_A. Its
        // value may be the source address of the ECU transmitting the message (which
        // means that no external SAE J1939 message is providing the active command) or
        // the source address of the SAE J1939 ECU that is currently providing the active
        // command in a TSC1 (see PGN 0) or similar message. Note that if this parameter
        // value is the same as the source address of the device transmitting it, the
        // control may be due to a message on a non-SAE J1939 data link such as SAE J1922
        // or a proprietary link.
        uint8_t             spn1667;            // Retarder requesting Brake Light
        //                                      // (2 bits)
        //  0 - 3
        uint8_t             spn1715;            // Drivers Demand Retarder - Percent Torque
        // The Drivers demand retarder – percent torque is the maximum torque selected by
        // the driver when one or more modes are selected by the driver, such as hand
        // lever, switch, constant torque, constant velocity, etc.
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 (0 - 250)
        uint8_t             spn1716;            // Retarder Selection - non-engine
        // The “Retarder Selection, non-engine” is the position of the driver’s selector
        // for retarders that are not part of the engine system, expressed as percent and
        // determined by the ratio of current position to the maximum possible position.
        // The physical device may be a lever, rotary dial, combination of switches, or
        // other device that the driver can use to select the type or amount of
        // retardation needed.
        // 0.4 % per bit, offset: 0
        // range: 0 - 100 %
        uint8_t             spn1717;            // Actual Maximum Available Retarder
                                                // - Percent Torque
        // This is the maximum amount of torque that the retarder can immediately deliver.
        // It is the same as the maximum torque shown in the Retarder’s Configuration
        // message, but allows for a much faster rate of change than could be communicated
        // by reissuing the configuration message.
        // Application Note: The purpose for this parameter is to allow a “Master”
        // retarder controller to more accurately allocate the vehicle’s retarder
        // requirements among multiple retarders. Its value should be the same as the
        // value in the Configuration message at the time that message is assembled for
        // broadcast, but may vary between those broadcasts.
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 (0 - 250)
        uint8_t             reserved8b[1];

        // Engine Fields - 2 bytes
        uint16_t            spn84;              // Wheel-Based Vehicle Speed
        // Speed of the vehicle as calculated from wheel or tailshaft speed.
        // mult: 1/256 km/h per bit  offset: 0
        // range: 0 to 250.996 km/h
        uint16_t            spn175;             // Engine Oil Temperature 1
        // Temperature of the engine lubricant.
        // mult: 0.03125 deg C per bit  offset: -273 C
        // range: -273 C to 1735 C
        uint16_t            spn176;             // Turbo Oil Temperature
        // Temperature of the turbocharger lubricant.
        // mult: 0.03125 deg C per bit  offset: -273 C
        // range: -273 C to 1735 C
        uint16_t            spn190;             // Engine Speed (rpm)
        // Actual engine speed which is calculated over a minimum crankshaft angle of 720
        // degrees divided by the number of cylinders.
        // mult: 0.125 rpm per bit, offset: 0
        // range: 0 to 8,031.875 rpm
        uint16_t            spn515;             // Engine's Desired Operating Speed
        // An indication by the engine of the optimal operating speed of the engine for
        // the current existing conditions. These conditions may include the torque
        // generated to accommodate powertrain demands from the operator (via the
        // accelerator pedal), cruise control, road speed limit governors, or ASR.
        // Dynamic commands from functions such as smoke control or shift control are
        // excluded from this calculation.
        // mult: 0.125 rpm per bit, offset: 0
        // range: 0 to 8,031.875 rpm
        uint16_t            spn1636;            // Intake Manifold 1 Air Temperature
        // Temperature of pre-combustion air found in intake manifold of engine air
        // supply system. The higher resolution is required for control purposes.
        // mult: 0.03125 deg C per bit  offset: -273 C
        // range: -273 C to 1735 C
        uint16_t            spn1637;            // Engine Coolant Temperature
        // Temperature of liquid found in engine cooling system. The higher resolution
        // is required for control purposes.
        // mult: 0.03125 deg C per bit  offset: -273 C
        // range: -273 C to 1735 C
        uint16_t            reserved16;
        // The last spn is used in Init() to establish size of area to initialize.

        uint32_t            spnLast;
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


    bool            j1939er_HandlePgn65249(
        J1939ER_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
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


    int             j1939er_SetupPgn65249(
        J1939ER_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );

    
    int             j1939er_SetupPgn65275(
        J1939ER_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* J1939ER_INTERNAL_H */
