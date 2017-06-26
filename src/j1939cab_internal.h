// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939cab_internal.h
 *	Generated 06/12/2017 17:43:12
 *
 * Notes:
 *  --	N/A
 *
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




#include        <j1939cab.h>
#include        <j1939ca_internal.h>



#ifndef J1939CAB_INTERNAL_H
#define	J1939CAB_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct j1939cab_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    J1939CA_DATA        super;
    OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT             eRc;
    
    uint32_t            curTime;
    J1939CA_TIME_DELAY  time57344;
    J1939CA_TIME_DELAY  time61443;
    J1939CA_TIME_DELAY  time65217;
    J1939CA_TIME_DELAY  time65261;
    J1939CA_TIME_DELAY  time65265;
    J1939CA_TIME_DELAY  time65269;
    J1939CA_TIME_DELAY  time65271;
    
    // The first spn is used in Init() to establish size of area to initialize.
    uint8_t             spnFirst;
    uint8_t             spn52;              // Engine Intercooler Temperature
    // Temperature of liquid found in the intercooler located after the turbocharger.
    // mult: 1 degree C per bit  offset: -40 C
    // range: -40 C to 210 C
    uint8_t             spn69;              // Two Speed Axle Switch
    // Switch signal which indicates the current axle range.
    //                                      // (2 bits)
    //  00 - Low speed range
    //  01 - High speed range
    //  10 - Error
    //  11 - Not available
    uint8_t             spn70;              // Parking Brake Switch
    // Switch signal which indicates when the parking brake is set. In general the switch
    // actuated by the operator's park brake control, whether a pedal, lever or other
    // control mechanism. (See also SPN 619)
    //                                      // (2 bits)
    //  00 - Parking brake not set
    //  01 - Parking brake set
    //  10 - Error
    //  11 - Not available
    uint8_t             spn74;              // Maximum Vehicle Speed Limit
    // Maximum vehicle velocity allowed.
    // mult: 1 km/h per bit  offset: 0
    // range: 0 to 250 km/h
    uint8_t             spn86;              // Cruise Control Set Speed
    // Value of set (chosen) velocity of velocity control system.
    // mult: 1 km/h per bit  offset: 0
    // range: 0 to 250 km/h
    uint8_t             spn87;              // Cruise Control High Set Limit Speed
    // Maximum vehicle velocity at which cruise can be set.
    // mult: 1 km/h per bit  offset: 0
    // range: 0 to 250 km/h
    uint8_t             spn88;              // Cruise Control Low Set Limit Speed
    // Minimum vehicle velocity at which cruise can be set or minimum vehicle velocity
    // for cruise operation before it will exit cruise control operation.
    // mult: 1 km/h per bit  offset: 0
    // range: 0 to 250 km/h
    uint8_t             spn91;              // Accelerator Pedal Position 1
    // The ratio of actual position of the analog engine speed/torque request input
    // device (such as an accelerator pedal or throttle lever) to the maximum position
    // of the input device. This parameter is intended for the primary accelerator
    // control in an application. If an application has only one accelerator control,
    // use SPN 91.
    // For on-highway vehicles, this will typically be the operator’s accelerator pedal.
    // Although it is used as an input to determine powertrain demand, it also provides
    // anticipatory information to transmission and ASR algorithms about driver actions.
    // In marine applications, this will typically be the operator’s throttle lever.
    // If a low idle validation switch is used in conjunction with accelerator pedal
    // position 1, use Accelerator Pedal Low Idle Switch 1, SPN 558.
    // mult: 1 % per bit  offset: 0
    // range: 0 to 250 %        operational range: 0 to 125 %
    uint8_t             spn92;              // Percent Load At Current Speed
    // The ratio of actual engine percent torque (indicated) to maximum indicated torque
    // available at the current engine speed, clipped to zero torque during engine
    // braking.
    // mult: 0.4 % per bit  offset: 0
    // range: 0 to 100 %
    uint8_t             spn108;             // Barometric Pressure
    // Absolute air pressure of the atmosphere. See Figures SPN16_A & SPN16_B.
    // mult: 0.5 kPa per bit, offset: 0
    // range: 0 to 125 kPa
    uint8_t             spn114;             // Net Battery Current
    // Net flow of electrical current into/out of the battery or batteries.
    // mult: 1 A per bit, offset: -125 A
    // range: -125 to 125 A
    uint8_t             spn115;             // Alternator Current
    // Measure of electrical current flow from the alternator. Alternator Current
    // (High Range/Resolution) parameter SPN 1795 has a higher range and resolution
    // of the same parameter.
    // mult: 1 A per bit, offset: 0
    // range: 0 to 250 A
    uint8_t             spn172;             // Engine Air Inlet Temperature
    // Temperature of air entering vehicle air induction system.
    // mult: 1 degree C per bit  offset: -40 C
    // range: -40 C to 210 C
    uint8_t             spn527;             // Cruise Control States (3 bits)
    // This parameter is used to indicate the current state, or mode, of operation by
    // the cruise control device. This is a status parameter.
    //  000 - Off/Disabled
    //  001 - Hold
    //  010 - Accelerate
    //  011 - Decelerate
    //  100 - Resume
    //  101 - Set
    //  110 - Accelerator Override
    //  111 - Not available
    uint8_t             spn558;             // Accelerator Pedal 1 Low Idle Switch
    //                                      // (2 bits)
    // Switch signal which indicates the state of the accelerator pedal 1 low idle
    // switch. The low idle switch is defined in SAE Recommended Practice J1843.
    //  00 - Accelerator pedal 1 not in low idle condition
    //  01 - Accelerator pedal 1 in low idle condition
    //  10 - Error
    //  11 - Not available
    uint8_t             spn559;             // Accelerator Pedal Kickdown Switch
    //                                      // (2 bits)
    // Switch signal which indicates whether the accelerator pedal kickdown switch is
    // opened or closed. The kickdown switch is defined in SAE J1843.
    uint8_t             spn574;             // Transmission Shift In Process
    //                                      // (2 bits)
    //  00 - Kickdown passive
    //  01 - Kickdown active
    //  10 - Error
    //  11 - Not available
    uint8_t             spn595;             // Cruise Control Active
    //                                      // (2 bits)
    // Cruise control is switched on. It is not ensured that the engine is controlled
    // by cruise control, as in the case of a large driver's demand the engine is
    // controlled by the driver while cruise control is active (maximum selection of
    // cruise control and driver’s demand). The cruise control is set to 0 if a
    // switch off condition occurs.
    //  00 - Cruise control switched off
    //  01 - Cruise control switched on
    //  10 - Error
    //  11 - Not available
    uint8_t             spn596;             // Cruise Control Enable Switch
    //                                      // (2 bits)
    // Switch signal which indicates that it is possible to manage the cruise control
    // function.
    //  00 - Cruise control disabled
    //  01 - Cruise control enabled
    //  10 - Error
    //  11 - Not available
    uint8_t             spn597;             // Brake Switch
    //                                      // (2 bits)
    // Switch signal which indicates that the driver operated brake foot pedal is
    // being pressed. This brake foot pedal is controlling the vehicles’ service
    // brake (total vehicle braking application, not park brakes). It is necessary
    // for safe drivetrain behavior that the switch activates before the physical
    // braking components are activated (i.e. Disengage the cruise control function
    // prior to the activation of friction brakes).
    //  00 - Brake pedal released
    //  01 - Brake pedal depressed
    //  10 - Error
    //  11 - Not available
    uint8_t             spn598;             // Clutch Switch
    //                                      // (2 bits)
    // Switch signal which indicates that the clutch pedal is being pressed. It is
    // necessary for a safe drivetrain behavior that the clutch switch is set before
    // the clutch is opened (cruise control function).
    //  00 - Clutch pedal released
    //  01 - Clutch pedal depressed
    //  10 - Error
    //  11 - Not available
    uint8_t             spn599;             // Cruise Control Set Switch
    //                                      // (2 bits)
    // Switch signal of the cruise control activator which indicates that the
    // activator is in the position “set.”
    //  00 - Cruise control activator not in the position “set”
    //  01 - Cruise control activator in position “set”
    //  10 - Error
    //  11 - Not available
    uint8_t             spn600;             // Cruise Control Coast (Decelerate) Switch
    //                                      // (2 bits)
    // Switch signal of the cruise control activator which indicates that the
    // activator is in the position “resume.”
    //  00 - Cruise control activator not in the position “coast”
    //  01 - Cruise control activator in the position “coast”
    //  10 - Error
    //  11 - Not available
    uint8_t             spn601;             // Cruise Control Resume Switch
    //                                      // (2 bits)
    // Switch signal of the cruise control activator which indicates that the
    // activator is in the position “resume.”
    //  00 - Cruise control activator not in the position “resume”
    //  01 - Cruise control activator in the position “resume”
    //  10 - Error
    //  11 - Not available
    uint8_t             spn602;             // Cruise Control Accelerate Switch
    //                                      // (2 bits)
    // Switch signal of the cruise control activator which indicates that the
    // activator is in the position “accelerate.”
    //  00 - Cruise control activator not in the position “accelerate”
    //  01 - Cruise control activator in the position “accelerate”
    //  10 - Error
    //  11 - Not available
    uint8_t             spn966;             // Engine Test Mode Switch
    //                                      // (2 bits)
    // Switch signal which indicates the position of the engine test mode switch.
    //  00 - Off
    //  01 - On
    //  10 - Error
    //  11 - Not available
    uint8_t             spn967;             // Idle Decrement Switch
    //                                      // (2 bits)
    // Switch signal which indicates the position of the idle decrement switch.
    //  00 - Off
    //  01 - On
    //  10 - Error
    //  11 - Not available
    uint8_t             spn968;             // Idle Increment Switch
    //                                      // (2 bits)
    // Switch signal which indicates the position of the idle increment switch.
    //  00 - Off
    //  01 - On
    //  10 - Error
    //  11 - Not available
    uint8_t             spn974;             // Remote Accelerator Pedal Position
    // The ratio of actual position of the remote analog engine speed/torque request
    // input device (such as an accelerator pedal or throttle lever) to the maximum
    // position of the input device.
    // For example, in on-highway vehicles this could be an accelerator control
    // device that is external to the drivers cab or an accelerator that is control-
    // led by a hand lever from the operators seat.
    // The Remote Accelerator Enable Switch is SPN 969. This parameter enables the
    // remote accelerator operation.
    // NOTE—See SPNs 28, 29, and 91 for additional accelerator position parameters.
    // If only one accelerator position exists on a vehicle, SPN 91 shall be used.
    // mult: 0.4 % per bit  offset: 0
    // range: 0 to 100 %
    uint8_t             spn976;             // PTO State
    //                                      // (5 bits)
    // This parameter is used to indicate the current state or mode of operation
    // by the power takeoff (PTO) device. It needs to be ensured that each achieved
    // state information be set up to be conveyed in at least one datalink message
    // before a transition to another state is allowed.
    //  00000 - Off/Disabled
    //  00001 - Hold
    //  00010 - Remote Hold
    //  00011 - Standby
    //  00100 - Remote Standby
    //  00101 - Set
    //  00110 - Decelerate/Coast
    //  00111 - Resume
    //  01000 - Accelerate
    //  01001 - Accelerator Override
    //  01010 - Preprogrammed set speed 1
    //  01011 - Preprogrammed set speed 2
    //  01100 - Preprogrammed set speed 3
    //  01101 - Preprogrammed set speed 4
    //  01110 - Preprogrammed set speed 5
    //  01111 - Preprogrammed set speed 6
    //  10000 - Preprogrammed set speed 7
    //  10001 - Preprogrammed set speed 8
    //  10010 - PTO set speed memory 1
    //  10011 - PTO set speed memory 2
    //  10100 - Not defined
    //    |
    //  11110
    //  11111 - Not available
    uint8_t             spn1237;            // Engine Shutdown Override Switch
    //                                      // (2 bits)
    // Switch signal which indicates the position of the engine shutdown override
    // switch. This switch function allows the operator to override an impending
    // engine shutdown.
    //  00 - No
    //  01 - Yes
    //  10 - Error
    //  11 - Not available
    uint8_t             spn1437;            // Road Speed Limit Status
    //                                      // (2 bits)
    // Status (active or not active) of the system used to limit maximum vehicle
    // velocity.
    //  00 - Active
    //  01 - Not active
    //  10 - Error
    //  11 - Not available
    uint8_t             spn1633;            // Cruise Control Pause Switch
    //                                      // (2 bits)
    // Switch signal which indicates the position of the Cruise Control Pause Switch
    // used on Remote Cruise Control applications. The Cruise Control Pause Switch
    // signal temporarily disables the Cruise Control function.
    //  00 - Off
    //  01 - On
    //  10 - Error
    //  11 - Not available
    uint8_t             spn1675;            // Engine Starter Mode
    //                                      // (4 bits)
    // There are several phases in a starting action and different reasons why a
    // start cannot take place.
    //  0000 - start not requested
    //  0001 - starter active, gear not engaged
    //  0010 - starter active, gear engaged
    //  0011 - start finished; starter not active after having been actively engaged
    //          (after 50ms mode goes to 0000)
    //  0100 - starter inhibited
    //  0101 - starter inhibited
    //  0110 - starter inhibited
    //  0111 - starter inhibited
    //  1000 - starter inhibited
    //  1001 - Reserved
    //    |
    //  1011
    //  1100 - starter inhibited
    //  1101 - error (legacy implementation only, use 1110)
    //  1110 - Error
    //  1111 - Not available
    
    uint16_t            spn79;              // Road Surface Temperature
    // Indicated temperature of road surface over which vehicle is operating.
    // mult: 0.03125 deg C per bit  offset: -273 C
    // range: -273 C to 1735 C
    uint16_t            spn84;              // Wheel-Based Vehicle Speed
    // Speed of the vehicle as calculated from wheel or tailshaft speed.
    // mult: 1/256 km/h per bit  offset: 0
    // range: 0 to 250.996 km/h
    uint16_t            spn158;             // Battery Potential (Voltage), Switched
    // Electrical potential measured at the input of the electronic control unit supplied
    // through a switching device.
    // mult: 0.05 V per bit  offset: 0
    // range: 0 to 3212.75 V
    uint16_t            spn167;             // Charging System Potential (Voltage)
    // Electrical potential measured at the charging system output. The charging system
    // may be any device charging the batteries. This includes alternators, generators,
    // solid state charger and other charging devices.
    // mult: 0.05 V per bit  offset: 0
    // range: 0 to 3212.75 V
    uint16_t            spn168;             // Electrical Potential (Voltage)
    // Measured electrical potential of the battery.
    // mult: 0.05 V per bit  offset: 0
    // range: 0 to 3212.75 V
    uint16_t            spn170;             // Cab Interior Temperature
    // Temperature of air inside the part of the vehicle that encloses the driver and
    // vehicle operating controls. Note: See SPN 1662 and SPN 1691.
    // mult: 0.03125 deg C per bit  offset: -273 C
    // range: -273 C to 1735 C
    uint16_t            spn171;             // Ambient Air Temperature
    // Temperature of air surrounding vehicle.
    // mult: 0.03125 deg C per bit  offset: -273 C
    // range: -273 C to 1735 C
    
    uint32_t            spn917;             // High Resolution Total Vehicle Distance
    // Accumulated distance traveled by the vehicle during its operation. NOTE - See
    // SPN 245 for alternate resolution.
    // mult: 5 m per bit, offset: 0
    // range: 0 to 21,055,406 km
    uint32_t            spn918;             // High Resolution Trip Distance
    // Distance traveled during all or part of a journey.
    // mult: 5 m per bit, offset: 0
    // range: 0 to 21,055,406 km
    uint32_t            spnLast;
    
    
};
#pragma pack(pop)

    extern
    const
    struct j1939cab_class_data_s  j1939cab_ClassObj;

    extern
    const
    J1939CAB_VTBL         j1939cab_Vtbl;


    // Internal Functions
    void            j1939cab_Dealloc(
        OBJ_ID          objId
    );

    
    bool            j1939cab_HandlePgn57344(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cab_HandlePgn61184(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cab_HandlePgn61443(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cab_HandlePgn61444(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cab_HandlePgn65217(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cab_HandlePgn65226(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cab_HandlePgn65265(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cab_HandlePgn65269(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cab_HandlePgn65271(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    void *          j1939cab_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
                    );
    
    
    int             j1939cab_SetupPgn57344(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939cab_SetupPgn61443(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939cab_SetupPgn65217(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939cab_SetupPgn65226(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939cab_SetupPgn65265(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939cab_SetupPgn65269(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939cab_SetupPgn65271(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    bool            j1939cab_setLastError(
        J1939CAB_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			j1939cab_Validate(
        J1939CAB_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* J1939CAB_INTERNAL_H */

