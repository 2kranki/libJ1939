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


    typedef enum j1939en_state_e {
        J1939EN_STATE_STOPPED=0,
        J1939EN_STATE_HEATERS_ON,
        J1939EN_STATE_STARTER_ACTIVATE,
        J1939EN_STATE_STARTER_ACTIVE,
        J1939EN_STATE_STARTER_ENGAGED,
        J1939TC_STATE_RUNNING,
        J1939TC_STATE_RUNNING_RETARDED,
        J1939TC_STATE_SHUTDOWN_PHASE1,
        J1939TC_STATE_SHUTDOWN_PHASE2,
    } J1939EN_STATE;
    
    
    typedef struct engine_torque_power_s {
        uint16_t        rpm;            // 0 == idle
        uint16_t        hp;             //
        uint16_t        torque;         // foot-lbs ???
    } ENG_TRQ_HP;
    
    
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

        // Common Data
        ERESULT             eRc;
        OBJ_ID              pECU;
        uint16_t            ratedPower;
        uint16_t            state;              // Engine State (see J1939EN_STATE)
        //                                      // actual_power = (ratedPower * 0.5) kW
        //                                      // range: 0 - 32127.5 kW
        uint16_t            minTorque;
        uint16_t            maxTorque;
        uint32_t            timeOut;
        uint8_t             fRetarding;         // Retarding is Active
        uint8_t             fShifting;          // Shift in progress
        uint8_t             fShutdown;          // Shutdown is Active
        uint8_t             fAutomatic;         // True == Automatic Transmission,
        //                                      // False == Manual
        P_VOIDEXIT12        pShiftExit;
        void                *pShiftData;
        //uint8_t             reserved8b[1];
        
        // Engine parameters
        //                                      // actual_rpm = (rpm * 0.125) / 1000
        //                                      // range: 0 - 8031.875 rpm
        void                (*pRpmRoutine)(void *pRpmData, uint16_t rpm);
        void                *pRpmData;
        
        // Message Repeat Times
        uint32_t            curTime;
        uint32_t            startTimeOperation; // Varies
        J1939CA_TIME_DELAY  time61443;
        J1939CA_TIME_DELAY  time61444;
        J1939CA_TIME_DELAY  time65129;
        J1939CA_TIME_DELAY  time65247;
        J1939CA_TIME_DELAY  time65252;
        J1939CA_TIME_DELAY  time65262;
        J1939CA_TIME_DELAY  time65265;
        J1939CA_TIME_DELAY  time65266;
        J1939CA_TIME_DELAY  time65279;

        // The first spn is used in Init() to establish size of area to initialize.
        uint8_t             spnFirst;
        uint8_t             spn51;              // Engine Throttle Position
        // The position of the valve used to regulate the supply of a fluid, usually air
        // or fuel/air mixture, to an engine. 0% represents no supply and 100% is full
        // supply.
        // mult: 0.4 % per bit  offset: 0
        // range: 0 to 100 %
        uint8_t             spn52;              // Engine Intercooler Temperature
        // Temperature of liquid found in the intercooler located after the turbocharger.
        // mult: 1 degree C per bit  offset: -40 C
        // range: -40 C to 210 C
        uint8_t             spn69;              // Two Speed Axle Switch (2 bits)
        // Switch signal which indicates the current axle range.
        //  00 - Low speed range
        //  01 - High speed range
        //  10 - Error
        //  11 - Not available
        uint8_t             spn70;              // Parking Brake Switch (2 bits)
        // Switch signal which indicates when the parking brake is set. In general the
        // switch actuated by the operator's park brake control, whether a pedal, lever
        // or other control mechanism. (See also SPN 619)
        //  00 - Parking brake not set
        //  01 - Parking brake set
        //  10 - Error
        //  11 - Not available
        uint8_t             spn86;              // Cruise Control Set Speed
        // Value of set (chosen) velocity of velocity control system.
        // mult: 1 km/h per bit  offset: 0
        // range: 0 to 250 km/h
        uint8_t             spn91;              // Accelerator Pedal Position 1
        // The ratio of actual position of the analog engine speed/torque request input
        // device (such as an accelerator pedal or throttle lever) to the maximum position
        // of the input device. This parameter is intended for the primary accelerator
        // control in an application. If an application has only one accelerator control,
        // use SPN 91.
        // For on-highway vehicles, this will typically be the operator’s accelerator
        // pedal. Although it is used as an input to determine powertrain demand, it also
        // provides anticipatory information to transmission and ASR algorithms about
        // driver actions.
        // If a low idle validation switch is used in conjunction with accelerator pedal
        // position 1, use Accelerator Pedal Low Idle Switch 1, SPN 558.
        // mult: 0.4 % per bit  offset: 0
        // range: 0 to 100 %
        uint8_t             spn92;              // Percent Load At Current Speed
        // The ratio of actual engine percent torque (indicated) to maximum indicated
        // torque available at the current engine speed, clipped to zero torque during
        // engine braking.
        // mult: 1 % per bit  offset: 0 %
        // range: 0 to 250 %
        uint8_t             spn97;              // Water In Fuel Indicator
        //                                      // (2 bits)
        // Signal which indicates the presence of water in the fuel.
        //  00 - No
        //  01 - Yes
        //  10 - Error
        //  11 - Not available
        uint8_t             spn110;             // Engine Coolant Temperature
        // Temperature of liquid found in engine cooling system.
        // mult: 1 degree C per bit  offset: -40 C
        // range: -40 C to 210 C
        uint8_t             spn174;             // Fuel Temperature
        // Temperature of fuel (or gas) passing through the first fuel control system.
        // See SPN 3468 for the second control system
        // mult: 1 degree C per bit  offset: -40 C
        // range: -40 C to 210 C
        uint8_t             spn512;             // Driver's Demand Engine - Percent Torque
        // The requested torque output of the engine by the driver. It is based on input
        // from the following requestors external to the powertrain: operator (via the
        // accelerator pedal), cruise control and/or road speed limit governor. Dynamic
        // commands from internal powertrain functions such as smoke control, low- and
        // high-speed engine governing; ASR and shift control are excluded from this
        // calculation. The data is transmitted in indicated torque as a percent of the
        // reference engine torque. See PGN 65251 for the engine configuration message.
        // Several status bits are defined separately to indicate the request which is
        // currently being honored. This parameter may be used for shift scheduling.
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 %
        uint8_t             spn513;             // Actual Engine - Percent Torque
        // The calculated output torque of the engine. The data is transmitted in
        // indicated torque as a percent of reference engine torque (see the engine
        // configuration message, PGN 65251). The engine percent torque value will not
        // be less than zero and it includes the torque developed in the cylinders
        // required to overcome friction.
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 %
        uint8_t             spn514;             // Nominal Friction - Percent Torque
        // The calculated torque that indicates the amount of torque required by the basic
        // engine itself added by the loss torque of accessories. It contains the
        // frictional and thermodynamic loss of the engine itself, pumping torque loss
        // (SPN 5398), and the losses of fuel, oil and cooling pumps.  The data is trans-
        // mitted in indicated torque as a percent of reference engine torque (see the
        // engine configuration message, PGN 65251).
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 %
        uint8_t             spn519;             // Engine's Desired Operating Speed
                                                // Asymmetry Adjustment
        // This byte is utilized in transmission gear selection routines and indicates
        // the engine's preference of lower versus higher engine speeds should its desired
        // speed not be achievable. This is a scaled ratio such that 125 represents an
        // equal preference for a speed lower or higher that the engine's indicated
        // desired speed. The higher the asymmetry adjustment value is above 125, the
        // more the engine prefers to be operated at or above its indicated desired speed.
        // Conversely, the lower the asymmetry adjustment value is below 125, the more the
        // engine prefers to operate at or below its indicated desired speed. Typically,
        // the engine's asymmetry adjustment will be predicated on fuel consumption con-
        // siderations, and under these conditions, the method for computing the asym-
        // metry adjustment is indicated in Figure SPN519_A. The engine may include other
        // factors into its asymmetry adjustment calculation such as temperatures, pres-
        // sures, and other operating parameters.
        // mult: 1 per bit  offset: 0
        // range: 0 to 250
        uint8_t             spn523;             // Transmission Current Gear
        // The gear currently engaged in the transmission or the last gear engaged while
        // the transmission is in the process of shifting to the new or selected gear.
        // Transitions toward a destination gear will not be indicated. Once the selected
        // gear has been engaged then Transmission Current Gear (SPN 525) will reflect
        // that gear.
        // mult: 1 gear value per bit  offset: -125
        // range: -125 to 125   Operational range: -125 to +125, negative values are
        //                                          reverse gears, positive values are
        //                                          forward gears, zero is neutral.
        //                                          251 (0xFB) is park.
        uint8_t             spn524;             // Transmission Selected Gear
        // The gear that the transmission will attempt to achieve during the current shift
        // if a shift is in progress, or the next shift if one is pending (i.e., waiting
        // for torque reduction to initiate the shift).
        // mult: 1 gear value per bit  offset: -125
        // range: -125 to 125   Operational range: -125 to +125, negative values are
        //                                          reverse gears, positive values are
        //                                          forward gears, zero is neutral.
        //                                          251 (0xFB) is park.
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
        uint8_t             spn899;             // Engine Torque Mode
        //                                      // (4 bits)
        // State signal which indicates which engine torque mode is currently generating,
        // limiting, or controlling the torque. Note that the modes are not in prioritized
        // order. Not all modes may be relevant for a given device. Some devices may not
        // implement all functions. For typical priorities refer to Figures SPN512_A and
        // SPN512_B for engine control. The data type of this parameter is measured.
        //  0000 - “No request”: engine torque may range from 0 to full load only due to
        //          low idle governor output.
        //  0001 - indicate that there is either a torque request or the identified
        //    |     function is currently controlling the engine: engine torque may
        //  1110    range from 0 (no fueling) to the upper limit.
        //  1111 - Not available
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
        uint8_t             spn1109;            // Engine Protection System
        //                                      // Approaching Shutdown
        //                                      // (2 bits)
        // Status signal which indicates that engine shutdown is imminent. This engine
        // protection signal can be a result of different systems failing, i.e., engine
        // overheating. See Figure SPN1107_A.
        //  00 - Not approaching
        //  01 - Approaching
        //  10 - Error
        //  11 - Not available
        uint8_t             spn1110;            // Engine Protection System has
        //                                      // Shutdown Engine
        //                                      // (2 bits)
        // Status signal which indicates whether or not the engine protection system has
        // shutdown the engine. See Figure SPN1107_A.
        //  00 - No
        //  01 - Yes
        //  10 - Error
        //  11 - Not available
        uint8_t             spn1134;            // Engine Intercooler Thermostat Opening
        // The current position of the thermostat used to regulate the temperature of
        // the engine intercooler. A value of 0% represents the thermostat being com-
        // pletely closed and 100% represents the thermostat being completely open.
        // mult: 0.4 % per bit  offset: 0
        // range: 0 to 100 %
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
        uint8_t             spn1483;            // Source Address of Controlling Device
                                                // for Engine Control
        // The source address of the SAE J1939 device currently controlling the engine.
        // It is used to expand the torque mode parameter (see SPN 899) in cases where
        // control is in response to an ECU that is not listed in Table SPN899_A. Its
        // value may be the source address of the ECU transmitting the message (which
        // means that no external SAE J1939 message is providing the active command) or
        // the source address of the SAE J1939 ECU that is currently providing the active
        // command in a TSC1 (see PGN 0) or similar message. Note that if this parameter
        // value is the same as the source address of the device transmitting it, the
        // control may be due to a message on a non-J1939 data link such as SAE J1922 or
        // a proprietary link.
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
        uint8_t             spn2432;            // Engine Demand - Percent Torque
        // The requested torque output of the engine by all dynamic internal inputs,
        // including smoke control, noise control and low and high speed governing.
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 %
        uint8_t             spn2978;            // Estimated Engine Parasitic Losses -
                                                // Percent Torque
        // The calculated torque that indicates the estimated amount of torque loss due
        // to engine parasitics, such as cooling fan, air compressor, air conditioning,
        // etc. It is expressed as a percent of Engine Reference Torque.  When the data
        // value of this parameter is equal to FB it means that all parasitic losses
        // calculated by the engine are included in the Engine's Nominal Friction Per-
        // cent Torque (SPN 514).
        // mult: 1 % per bit  offset: -125 %
        // range: -125 to 125 %
        uint8_t             reserved8b[2];

        // Engine Fields - 2 bytes
        uint16_t            spn84;              // Wheel-Based Vehicle Speed
        // Speed of the vehicle as calculated from wheel or tailshaft speed.
        // mult: 1/256 km/h per bit  offset: 0
        // range: 0 to 250.996 km/h
        uint16_t            spn161;             // 03 - Transmission Input Shaft Speed
        // Rotational velocity of the primary shaft transferring power into the trans-
        // mission. When a torque converter is present, it is the output of the torque
        // converter.
        // mult: 0.125 rpm per bit  offset: 0
        // range: 0 to 8,031.875 rpm
        uint16_t            spn175;             // Engine Oil Temperature 1
        // Temperature of the engine lubricant.
        // mult: 0.03125 deg C per bit  offset: -273 C
        // range: -273 C to 1735 C
        uint16_t            spn176;             // Turbo Oil Temperature
        // Temperature of the turbocharger lubricant.
        // mult: 0.03125 deg C per bit  offset: -273 C
        // range: -273 C to 1735 C
        uint16_t            spn183;             // Engine Instantaneous Fuel Economy
        // Amount of fuel consumed by engine per unit of time.
        // mult: 0.05 L/h per bit  offset: 0
        // range: 0 to 3,212.75 L/h
        uint16_t            spn184;             // Engine Average Fuel Economy
        // Current fuel economy at current vehicle velocity.
        // mult: 1/512 km/L per bit  offset: 0
        // range: 0 to 125.5 km/L
        uint16_t            spn185;             // Engine Average Fuel Economy
        // Average of instantaneous fuel economy for that segment of vehicle operation
        // of interest.
        // mult: 1/512 km/L per bit  offset: 0
        // range: 0 to 125.5 km/L
        uint16_t            spn190;             // Engine Speed (rpm)
        // Actual engine speed which is calculated over a minimum crankshaft angle of 720
        // degrees divided by the number of cylinders.
        // mult: 0.125 rpm per bit, offset: 0
        // range: 0 to 8,031.875 rpm
        uint16_t            spn191;             // Transmission Output Shaft Speed
        // Calculated speed of the transmission output shaft.
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

        //uint16_t            reserved16;

        // The last spn is used in Init() to establish size of area to initialize.
        uint32_t            spnLast;

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


    bool            j1939en_setLastError(
        J1939EN_DATA    *this,
        ERESULT         value
    );
    
    
    bool            j1939en_HandlePgn0(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61184(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61442(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61443(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61444(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn61445(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65129(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65247(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65252(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );
    
    
    bool            j1939en_HandlePgn65262(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65265(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );


    bool            j1939en_HandlePgn65266(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );
    
    
    bool            j1939en_HandlePgn65279(
        J1939EN_DATA	*this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );
    
    
    ERESULT         j1939en_Operation(
        J1939EN_DATA	*this
    );
    
    
    int             j1939en_SetupPgn61443(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );


    int             j1939en_SetupPgn61444(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );


    int             j1939en_SetupPgn65129(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );


    int             j1939en_SetupPgn65247(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );


    int             j1939en_SetupPgn65252(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939en_SetupPgn65262(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );


    int             j1939en_SetupPgn65265(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );


    int             j1939en_SetupPgn65266(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939en_SetupPgn65279(
        J1939EN_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    



#ifdef	__cplusplus
}
#endif

#endif	/* J1939EN_INTERNAL_H */
