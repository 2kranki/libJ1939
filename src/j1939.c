/****************************************************************
 *          Data j1939 (j1939) Support Subroutines           *
 ****************************************************************/
/*
 * Program
 *              Data j1939 (j1939) Subroutines
 * Purpose
 *              See j1939.H for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See j1939.H for the history.
 * References
 *              See j1939.H for the references.
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




/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include        <j1939_internal.h>
#include        <j1939cam.h>



#ifdef	__cplusplus
extern	"C" {
#endif
   

#ifdef XYZZY
    
    static
    const
    J1939_SPN_TYPE      SAEbs01 = {  // Bits/States
        86,             // SAE Type
        1,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        1,              // Operating Max
        0,              // Data Min
        1               // Data Max
    };
    
    static
    const
    J1939_SPN_TYPE      SAEbs02 = {  // Bits/States
        87,             // SAE Type
        2,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        3,              // Operating Max
        0,              // Data Min
        3               // Data Max
    };
    
    static
    const
    J1939_SPN_TYPE      SAEbs03 = {  // Bits/States
        88,             // SAE Type
        3,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        7,              // Operating Max
        0,              // Data Min
        7               // Data Max
    };
    
    static
    const
    J1939_SPN_TYPE      SAEbs04 = {  // Bits/States
        89,             // SAE Type
        4,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        15,             // Operating Max
        0,              // Data Min
        15              // Data Max
    };
    
    static
    const
    J1939_SPN_TYPE      SAEbs05 = {  // Bits/States
        90,             // SAE Type
        5,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        31,             // Operating Max
        0,              // Data Min
        31              // Data Max
    };
    
    static
    const
    J1939_SPN_TYPE      SAEbs06 = {  // Bits/States
        91,             // SAE Type
        6,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        63,             // Operating Max
        0,              // Data Min
        63              // Data Max
    };
    
    static
    const
    J1939_SPN_TYPE      SAEbs07 = {  // Bits/States
        92,             // SAE Type
        7,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        127,            // Operating Max
        0,              // Data Min
        127             // Data Max
    };
    
    static
    const
    J1939_SPN_TYPE      SAEbs08 = {  // Bits/States
        93,             // SAE Type
        8,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        255,            // Operating Max
        0,              // Data Min
        255             // Data Max
    };
    
    
    static
    const
    J1939_SPN_TYPE      SAEpc05 = {  // Percent %
        45,             // SAE Type
        8,              // Length in Bits
        0,              // Decimal places
        1,              // Mult
        1,              // Div
        -125,           // Offset
        0,              // Round
        -125,           // Operating Min
        125,            // Operating Max
        0,              // Data Min
        250             // Data Max
    };

    
    static
    const
    J1939_SPN_TYPE      SAEpr07 = { // Pressure in Kpa
        53,             // SAE Type
        8,              // Length in Bits
        0,              // Decimal places
        2,              // Mult
        1,              // Div
        0,              // Offset
        0,              // Round
        0,              // Operating Min
        500,            // Operating Max
        0,              // Data Min
        250             // Data Max
    };
    
    
    static
    const
    J1939_SPN_TYPE      bits64 = {
        //  Len   Mult    Div  offset  round    min    max     min    max
             64,     1,     1,      0,     0,     0,     0,      0,     0
    };

    
    static
    const
    J1939_SPN_TYPE      percent01 = {
        //  Len   Mult    Div  offset  round    min    max     min    max
              8,     4,    10,      0,     2,     0,   100,      0,   250
    };
    
    static
    const
    J1939_SPN_TYPE      percent03 = {
        //  Len   Mult    Div  offset  round    min    max     min    max
              8,     1,     1,      0,     0,     0,   125,      0,   250
    };
    
    
    static
    const
    J1939_SPN_TYPE      pressure01 = {
        //  Len   Mult    Div  offset  round    min    max     min    max
              8,     5,    10,      0,     2,     0,   125,      0,   250
    };
    

    // Source Address (SA) for a device
    static
    const
    J1939_SPN_TYPE      sourceAddress = {
    //  Len   Mult    Div  offset  round    min    max     min    max
          8,     1,     1,      0,     0,     0,   253,      0,   255
    };


    static
    const
    J1939_SPN_TYPE      temp01 = {
        //  Len   Mult    Div  offset  round    min    max     min    max
              8,     1,     1,    -40,     2,   -40,   210,      0,   250
    };
    
    static
    const
    J1939_SPN_TYPE      temp02 = {
        //  Len   Mult    Div  offset  round    min    max     min    max
             16,  3125, 10000,   -273,  5000,  -273,  1735,      0, 55520
    };
    
    
    static
    const
    J1939_SPN_TYPE      velocityRotational01 = {
        //  Len   Mult    Div  offset  round    min    max     min    max
             16,   125,  1000,      0,   500,     0,  8031,      0, 64255
    };
    
    
    // SPN 51 - Throttle Position - The position of the valve used to regulate
    // the supply of a fluid, usually air or fuel/air mixture, to an engine.
    // 0% represents no supply and 100% is full supply.
    static
    const
    J1939_SPN           spn51 = { 51,  &percent01 };
    
    
    // SPN 52 - Engine Intercooler Temperature - Temperature of liquid found in the
    // intercooler located after the turbocharger.
    static
    const
    J1939_SPN           spn52 = { 52, &temp01 };
    
    
    // SPN 91 - Accelerator Pedal Position 1 - The ratio of actual position of the
    // analog engine speed/torque request input device (such as an accelerator pedal
    // or throttle lever) to the maximum position of the input device. This parameter
    // is intended for the primary accelerator control in an application. If an appli-
    // cation has only one accelerator control, use SPN 91. For on-highway vehicles,
    // this will typically be the operator's accelerator pedal. Although it is used
    // as an input to determine powertrain demand, it also provides anticipatory
    // information to transmission and ASR algorithms about driver actions. In marine
    // applications, this will typically be the operator's throttle lever. If a low
    // idle validation switch is used in conjunction with accelerator pedal position
    // 1, use Accelerator Pedal Low Idle Switch 1, SPN 558.
    static
    const
    J1939_SPN           spn91 = { 91,  &percent01 };
    
    
    // SPN 92 - Percent Load At Current Speed - The ratio of actual engine percent
    // torque (indicated) to maximum indicated torque available at the current en-
    // gine speed, clipped to zero torque during engine braking.
    static
    const
    J1939_SPN           spn92 = { 92, &percent03 };
    
    
    // SPN 98 - Engine Oil Level - Ratio of current volume of engine sump oil
    // to maximum required volume.
    static
    const
    J1939_SPN           spn98 = { 98, &percent01 };
    
    
    // SPN 99 - Engine Oil Filter Differential Pressure - Change in engine oil
    // pressure, measured across the filter, due to the filter and any accumulation
    // of solid or semisolid material on or in the filter.
    static
    const
    J1939_SPN           spn99 = { 99, &pressure01 };
    
    
    // SPN 102 - Boost Pressure - Gage pressure of air measured downstream on the
    // compressor discharge side of the turbocharger. See also SPNs 1127-1130 for
    // alternate range and resolution. If there is one boost pressure to report
    // and this range and resolution is adequate, this parameter should be used.
    static
    const
    J1939_SPN           spn102 = { 102, &pressure02 };
    
    
    // SPN 110 - Engine Coolant Temperature - Temperature of liquid found in engine
    // cooling system.
    static
    const
    J1939_SPN           spn110 = { 110, &temp01 };
    
    
   // SPN 174 - Fuel Temperature - Temperature of fuel entering injectors.
    static
    const
    J1939_SPN           spn174 = { 174, &temp01 };
    
    
    // SPN 175 - Engine Oil Temperature 1 - Temperature of the engine lubricant.
    static
    const
    J1939_SPN           spn175 = { 175, &temp02 };

    
    // SPN 176 - Turbo Oil Temperature - Temperature of the turbocharger lubricant.
    static
    const
    J1939_SPN           spn176 = { 176, &temp02 };


    // SPN 190 - Engine Speed - Actual engine speed which is calculated over a
    // minimum crankshaft angle of 720 degrees divided by the number of cylinders.
    static
    const
    J1939_SPN           spn190 = { 190, &velocityRotational01 };

    
    // SPN 512 - Driver's Demand Engine - Percent Torque - The requested torque
    // output of the engine by the driver. It is based on input from the following
    // requestors external to the powertrain: operator (via the accelerator pedal),
    // cruise control and/or road speed limit governor. Dynamic commands from inter-
    // nal powertrain functions such as smoke control, low- and high-speed engine
    // governing; ASR and shift control are excluded from this calculation. The
    // data is transmitted in indicated torque as a percent of the reference engine
    // torque. See PGN 65251 for the engine configuration message. Several status
    // bits are defined separately to indicate the request which is currently being
    // honored. This parameter may be used for shift scheduling.
    static
    const
    J1939_SPN           spn512 = { 512, &percent02 };

    
    // SPN 513 - spn513 - Actual Engine - Percent Torque - The calculated output
    // torque of the engine. The data is transmitted in indicated torque as a
    // percent of reference engine torque (see the engine configuration message,
    // PGN 65251). The engine percent torque value will not be less than zero and
    // it includes the torque developed in the cylinders required to overcome
    // friction.
    static
    const
    J1939_SPN           spn513 = { 513, &percent02 };

    
    // SPN 558 - spn558 - Accelerator Pedal 1 Low Idle Switch - Switch signal
    // which indicates the state of the accelerator pedal 1 low idle switch.
    // The low idle switch is defined in SAE J1843.
    // 00 Accelerator pedal 1 not in low idle condition
    // 01 Accelerator pedal 1 in low idle condition
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn558 = { 558, &bits02 };
    
    
    // SPN 559 - Accelerator Pedal Kickdown Switch - Switch signal which
    // indicates whether the accelerator pedal kickdown switch is opened
    // or closed. The kickdown switch is defined in SAE J1843.
    // 00 Kickdown passive
    // 01 Kickdown active
    static
    const
    J1939_SPN           spn559 = { 559, &bits01 };
    
    
    // SPN 899 - Engine Torque Mode - State signal which indicates which
    // engine torque mode is currently generating, limiting, or controlling
    // the torque. Note that the modes are not in prioritized order. Not all
    // modes may be relevant for a given device. Some devices may not implement
    // all functions. For typical priorities refer to Figures SPN512_A and
    // SPN512_B for engine control and Tables SPN518_A to SPN518_B for retarder
    // control. The data type of this parameter is measured.
    // Mode 0000b means 'No request': engine torque may range from 0 to full load
    //             only due to low idle governor output; retarder torque == 0
    //              (no braking).
    // Modes 0001b to 1110b indicate that there is either a torque request or
    //              the identified function is currently controlling the engine/
    //              retarder: engine/retarder torque may range from 0 (no fueling/
    //              no braking) to the upper limit.
    static
    const
    J1939_SPN           spn899 = { 899, &bits03 };
    
    
    // SPN 974 - Remote Accelerator Pedal Position - The ratio of actual position
    // of the remote analog engine speed/torque request input device (such as an
    // accelerator pedal or throttle lever) to the maximum position of the input
    // device. For example, in on-highway vehicles this could be an accelerator
    // control device that is external to the drivers cab or an accelerator that
    // is controlled by a hand lever from the operators seat. The Remote Accelerator
    // Enable Switch is SPN 969. This parameter enables the remote accelerator
    // operation. NOTE: See SPNs 28, 29, and 91 for additional accelerator position
    // parameters. If only one accelerator position exists on a vehicle, SPN 91
    // shall be used.
    static
    const
    J1939_SPN           spn974 = { 974, &percent01 };
    
    
    // SPN 1134 - Engine Intercooler Thermostat Opening - The current position
    // of the thermostat used to regulate the temperature of the engine intercooler.
    // A value of 0% represents the thermostat being completely closed and 100%
    // represents the thermostat being completely open.
    static
    const
    J1939_SPN           spn1134 = { 1134, &percent01 };
    
    
    // SPN 1437 - Road Speed Limit Status - Status (active or not active) of the
    // system used to limit maximum vehicle velocity.
    // 00 - Active
    // 01 - Not Active
    // NOTE - While somewhat inconsistent with other J1939 status parameters, the
    // states defining 00 = active and 01 = inactive for Road Speed Limit Status
    // are NOT typographical errors, and should be implemented as stated.
    static
    const
    J1939_SPN           spn1437 = { 1437, &bits01 };
    
    
    // SPN 1483 - Source Address of Controlling Device for Engine Control - The
    // source address of the SAE J1939 device currently controlling the engine.
    // It is used to expand the torque mode parameter (see SPN 899) in cases where
    // control is in response to an ECU that is not listed in Table SPN899_A. Its
    // value may be the source address of the ECU transmitting the message (which
    // means that no external SAE J1939 message is providing the active command)
    // or the source address of the SAE J1939 ECU that is currently providing the
    // active command in a TSC1 (see PGN 0) or similar message. Note that if this
    // parameter value is the same as the source address of the device transmitting
    // it, the control may be due to a message on a non-J1939 data link such as SAE
    // J1922 or a proprietary link.
    static
    const
    J1939_SPN           spn1483 = { 1483, &sourceAddress };

    
    // SPN 1636 - Intake Manifold 1 Air Temperature (High Resolution) - Temperature
    // of pre-combustion air found in intake manifold of engine air supply system.
    // The higher resolution is required for control purposes.
    static
    const
    J1939_SPN           spn1636 = { 1636, &temp02 };
    
    
    // SPN 1637 - Engine Coolant Temperature (High Resolution) - Temperature of
    // liquid found in engine cooling system. The higher resolution is required
    // for control purposes.
    static
    const
    J1939_SPN           spn1637 = { 1637, &temp02 };
    
    
    // SPN 1675 - spn1675 - Engine Starter Mode - There are several phases in a
    // starting action and different reasons why a start cannot take place.
    // 0000 start not requested
    // 0001 starter active, gear not engaged
    // 0010 starter active, gear engaged
    // 0011 start finished; starter not active after having been actively engaged
    //      (after 50ms mode goes to 0000) 0100 starter inhibited due to engine
    //       already running)
    // 0101 starter inhibited due to engine not ready for start (preheating)
    // 0110 starter inhibited due to driveline engaged or other transmission inhibit
    // 0111 starter inhibited due to active immobilizer
    // 1000 starter inhibited due to starter over-temp
    // 1001-1011 Reserved
    // 1100 starter inhibited - reason unknown
    // 1101 error (legacy implementations only; use 1110)
    // 1110 error
    // 1111 not available
    static
    const
    J1939_SPN           spn1675 = { 1675, &bits03 };
    
    
    // SPN 2432 - Engine Demand - Percent Torque - The requested torque output of
    // the engine by all dynamic internal inputs, including smoke control, noise
    // control and low and high speed governing.
    static
    const
    J1939_SPN           spn2432 = { 2432, &percent02 };

    
    // SPN 2848 - Engine Demand - Percent Torque - The requested torque output of
    static
    const
    J1939_SPN           spn2848 = { 2848, &bits64 };
    
    
    static
    const
    J1939_PGNSPN        pgn37632spns[1] = {
        { 37632, 2848, 0, 0, &spn2848 }
    };
    
    static
    const
    J1939_PGNSPN        pgn60928spns[1] = {
        { 60928, 2848, 0, 0, &spn2848 }
    };
    
    static
    const
    J1939_PGNSPN        pgn61443spns[6] = {
        { 61443,  558, 0, 0, &spn558 },
        { 61443,  559, 0, 0, &spn559 },
        { 61443, 1437, 0, 0, &spn1437 },
        { 61443,   91, 1, 0, &spn91 },
        { 61443,   92, 2, 0, &spn92 },
        { 61443,  974, 3, 0, &spn974 }
    };
    
    static
    const
    J1939_PGNSPN        pgn61444spns[7] = {
        { 61444,  899, 0, 0, &spn899 },
        { 61444,  512, 1, 0, &spn512 },
        { 61444,  513, 2, 0, &spn513 },
        { 61444,  190, 3, 0, &spn190 },
        { 61444, 1483, 5, 0, &spn1483 },
        { 61444, 1675, 6, 0, &spn1675 },
        { 61444, 2432, 7, 0, &spn2432 }
    };
        
    static
    const
    J1939_PGNSPN        pgn65129spns[2] = {
        { 65129, 1636, 0, 0, &spn1636 },
        { 65129, 1637, 2, 0, &spn1637 }
    };
    
    static
    const
    J1939_PGNSPN        pgn65262spns[6] = {
        { 65262,  110, 0, 0, &spn110 },
        { 65262,  174, 1, 0, &spn174 },
        { 65262,  175, 2, 0, &spn175 },
        { 65262,  176, 3, 0, &spn176 },
        { 65262,   52, 6, 0, &spn52 },
        { 65262, 1134, 7, 0, &spn1134 }
    };
    
    
    static
    const
    J1939_PGNTBL        pgn37632 = { 37632,    0, 6, 1, pgn37632spns };
    
    static
    const
    J1939_PGNTBL        pgn60928 = { 60928,    0, 6, 1, pgn60928spns };
    
    static
    const
    J1939_PGNTBL        pgn61443 = { 61443,   50, 3, 6, pgn61443spns };
        
    static
    const
    J1939_PGNTBL        pgn61444 = { 61444,   50, 3, 7, pgn61444spns };
    
    static
    const
    J1939_PGNTBL        pgn65129 = { 65129, 1000, 6, 2, pgn65129spns };

    static
    const
    J1939_PGNTBL        pgn65262 = { 65262, 1000, 6, 6, pgn65262spns };
    

    
    
    const
    J1939_PGN_ENTRY     pgn0_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        0x00000000,
        50,                 // msFreq (to Retarder)(10ms to Engine)
        8,                  // dlc
        3,                  // priority
        7,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn256_entry = {
        // PGN 0  0x000100 - Transmission Control 1 - TC1
        0x00000100,
        50,                 // msFreq (only when active)
        8,                  // dlc
        3,                  // priority
        17,                 // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn59392_entry = {
        // PGN 59392  0x00E800 - ACK/NAK
        0x0000E800,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn59904_entry = {
        // PGN 59904  0x00EA00 (PDU1) - Request for PGN
        0x0000EA00,
        0,                  // msFreq
        3,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn60416_entry = {
        // PGN 60416  0x00EC00 - 
        0x0000EE00,
        0,                  // msFreq
        8,                  // dlc
        7,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn60928_entry = {
        // PGN 60928  0x00EE00 - Claim Address/Cannot Claim Address
        0x0000EE00,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61184_entry = {
        // PGN 61184  0x00EF00 - Proprietary A
        0x0000EF00,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61440_entry = {
        // PGN 61440  0x00F000 - Electronic Retarder Controller 1 - ERC1
        0x0000F000,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };

    
    const
    J1939_PGN_ENTRY     pgn61442_entry = {
        // PGN 61442  0x00F002 - Electronic Transmission Controller 1 - ETC1
        0x0000F002,
        10,                 // msFreq
        8,                  // dlc
        3,                  // priority
        9,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61443_entry = {
    // PGN 61443  0x00F003 - Electronic Engine Controller 2 - EEC2
        0x0000F003,
        50,                 // msFreq
        8,                  // dlc
        3,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61444_entry = {
    // PGN 61444  0x00F004 - Electronic Engine Controller 1 - EEC1
        0x0000F004,
        100,                // msFreq
        8,                  // dlc
        3,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61445_entry = {
        // PGN 61445  0x00F005 - Electronic Transmission Controller 1 - ETC2
        0x0000F005,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        5,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65098_entry = {
        // PGN 65098  0x00FE4A - Electronic Transmission Controller 7 - ETC7
        0x0000FE4A,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        11,                 // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65129_entry = {
    // PGN 65129  0x00FE69 - Engine Temperature 3 - ET3
        0x0000FE69,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65226_entry = {
        // PGN 65226  0x00FECA - Active Diagnostic Trouble Codes - DM1
        0x0000FECA,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65247_entry = {
    // PGN 65247  0x00FEDF - Electronic Engine Controller 3 - EEC3
        0x0000FEDF,
        250,                // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65249_entry = {
        // PGN 65249  0x00FEE1 - Retarder Configuration - RC -
        0x00FEE1,
        5000,               // msFreq
        19,                 // dlc
        6,                  // priority
        14,                 // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65262_entry = {
    // PGN 65262  0x00FEEE - Engine Temperature 1 - ET1
        0x0000FEEE,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65265_entry = {
    // PGN 65265  0x00FEF1 - Cruise Control/Vehicle Speed - CCVS
        0x0000FEF1,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL                // SPN Table Pointer
    };
    
    
    const
    J1939_PGN_ENTRY     *pgn_index[] = {
        &pgn0_entry,
        &pgn256_entry,
        &pgn59392_entry,
        &pgn59904_entry,
        &pgn60416_entry,
        &pgn60928_entry,
        &pgn61184_entry,
        &pgn61440_entry,
        &pgn61442_entry,
        &pgn61443_entry,
        &pgn61444_entry,
        &pgn61445_entry,
        &pgn65098_entry,
        &pgn65129_entry,
        &pgn65226_entry,
        &pgn65247_entry,
        &pgn65249_entry,
        &pgn65262_entry,
        &pgn65265_entry,
        NULL
    };
    
    
    const
    J1939_PGN_TABLE     pgn_table = {
        (sizeof(pgn_index)/sizeof(J1939_PGN_ENTRY *)) - 1,
        0,
        &pgn_index
    };
#endif
    
    
    
    
    static
    J1939_DATA      *j1939_index[J1939_MAX_CAN_PORTS] = {0};
    
#ifdef TOOD_DO_WE_STILL_NEED_THIS
    static
    const
    uint16_t        defaultNumResponders = 16;
#endif
    
    
    
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
    ****************************************************************/


    // Park and Miller's psuedo-random number generator.
    // To get a random number within a range [a..b] use:
    //      rannum = a + (pm_random(0) / ((RANDMAX / (b - a + 1)) + 1)) 
#define RANDMAX 2147483646 // RANDMAX = M - 1
    static
    int         pm_random(
        int         seed
    )
    {
        static
        int         next = 1;
        static
        int         A = 16807;
        static
        int         M = 2147483647;   // 2^31 - 1
        static
        int         q = 127773;       // M / A
        static
        int         r = 2836;         // M % A
        
        if (seed) {
            next = seed;
        }
        next = A * (next % q) - r * (next / q);
        if (next < 0) {
            next += M;
        }
        
        return next;
    }
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    
    //---------------------------------------------------------------
    //         Create New J1939 set up as an Engine ECU
    //---------------------------------------------------------------
    
    J1939_DATA *    j1939_NewEngine(
        uint8_t         port,
        P_SRVCMSG_RTN   pSrvcMsg,
        void            *pSrvcData
    )
    {
        J1939_DATA      *pJ1939;
        J1939CAM_DATA   *pCAM;
        bool            fRc;
        
#ifdef NDEBUG
#else
        if (j1939_index[port-1]) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pJ1939 = j1939_Alloc();
        pJ1939 = j1939_Init( pJ1939, port );
        if( OBJ_NIL == pJ1939 ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (pSrvcMsg) {
            fRc = j1939_AddMessageResponder( pJ1939, pSrvcMsg, pSrvcData );
            if(!fRc) {
                DEBUG_BREAK();
                obj_Release(pJ1939);
                pJ1939 = OBJ_NIL;
                return OBJ_NIL;
            }
        }
        
        // Create the ECU.
        // Note: Setup() establishes the pXmtMsg from the Xmt Fifo.
        pCAM =  j1939cam_NewEngine(
                            pJ1939,
                            NULL,
                            NULL,
                            pJ1939->pXmtMsg,
                            pJ1939->pXmtData,
                            pJ1939->spn2837,
                            pJ1939->spn2838,
                            pJ1939->spn2846
                );
        if( OBJ_NIL == pCAM ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        j1939_setCAM(pJ1939, pCAM);
        fRc =   j1939_AddMessageResponder(
                            pJ1939,
                            (P_SRVCMSG_RTN)&j1939cam_HandleMessages,
                            pCAM
                );
        obj_Release(pCAM);
        pCAM = OBJ_NIL;
        
        return pJ1939;
    }

    
    
    //---------------------------------------------------------------
    //         Create New J1939 set up as a Transmissio ECU
    //---------------------------------------------------------------
    
    J1939_DATA *    j1939_NewTransmission(
        uint8_t         port,
        P_SRVCMSG_RTN   pSrvcMsg,
        void            *pSrvcData
    )
    {
        J1939_DATA      *pJ1939;
        J1939CAM_DATA   *pCAM;
        bool            fRc;
        
#ifdef NDEBUG
#else
        if (j1939_index[port-1]) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pJ1939 = j1939_Alloc();
        pJ1939 = j1939_Init( pJ1939, port );
        if( OBJ_NIL == pJ1939 ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (pSrvcMsg) {
            fRc = j1939_AddMessageResponder( pJ1939, pSrvcMsg, pSrvcData );
            if(!fRc) {
                DEBUG_BREAK();
                obj_Release(pJ1939);
                pJ1939 = OBJ_NIL;
                return OBJ_NIL;
            }
        }
        
        // Create the TCU.
        pCAM =  j1939cam_NewTransmission(
                                    pJ1939,
                                    NULL,
                                    NULL,
                                    pJ1939->pXmtMsg,
                                    pJ1939->pXmtData,
                                    pJ1939->spn2837,
                                    pJ1939->spn2838,
                                    pJ1939->spn2846
                );
        if( OBJ_NIL == pCAM ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        j1939_setCAM(pJ1939, pCAM);
        fRc =   j1939_AddMessageResponder(
                                pJ1939,
                                (P_SRVCMSG_RTN)&j1939cam_HandleMessages,
                                pCAM
                );
        obj_Release(pCAM);
        pCAM = OBJ_NIL;
        
        return pJ1939;
    }

    
    
    J1939_DATA *    j1939_Shared(
        uint8_t         port
    )
    {
        if (port < J1939_MAX_CAN_PORTS) {
            if (NULL == j1939_index[port-1]) {
                j1939_index[port-1] =  j1939_Alloc();
                j1939_index[port-1] =  j1939_Init(
                                                  j1939_index[port-1],
                                                  port
                                        );
            }
            return j1939_index[port-1];
        }
        return OBJ_NIL;
    }
    
    
    void            j1939_SharedSet(
        uint8_t         port,
        J1939_DATA      *this
    )
    {
        
        if (j1939_index[port-1]) {
            obj_Release(j1939_index[port-1]);
        }
        obj_Retain(this);
        j1939_index[port-1] = this;
    }

    
    
    void            j1939_SharedReset(
    )
    {
        if (j1939_index[0]) {
            obj_Release(j1939_index[0]);
            j1939_index[0] = OBJ_NIL;
        }
        if (j1939_index[1]) {
            obj_Release(j1939_index[1]);
            j1939_index[1] = OBJ_NIL;
        }
    }
    
    
    J1939_DATA *    j1939_Alloc(
    )
    {
        J1939_DATA      *cbp;
        
        // Do initialization.
        
        cbp = obj_Alloc( sizeof(J1939_DATA) );
        
        // Return to caller.
        return( cbp );
    }
    
    
        
    //---------------------------------------------------------------
    //                  SPN to Signed Value
    //---------------------------------------------------------------
    
    int32_t     j1939_SpnToS32(
        J1939_SPN_TYPE  *pType,
        uint16_t        data
    )
    {
        int32_t         value = 0;
        
        if (pType) {
            // The order of operations is important since we are
            // working with integers.
            // We expand some of the more common multiplications
            // and divisions to save time.
            if (1 == pType->mult) {
                value = data;
            }
            else if (2 == pType->mult) {
                value = (data << 1);
            }
            else if (4 == pType->mult) {
                value = (data << 2);
            }
            else {
                value = (data * pType->mult);
            }
            value += pType->round;
            if (1 == pType->div)
                ;
            else if (2 == pType->div) {
                value >>= 1;
            }
            else if (4 == pType->div) {
                value >>= 2;
            }
            else {
                value /= pType->div;
            }
            value += pType->offset;
        }
        
        // Return to caller.
        return value;
    }
    
    
    
    
    //===============================================================
    //                      *** Properties ***
    //===============================================================

    //---------------------------------------------------------------
    //                          C A M
    //---------------------------------------------------------------
    
    OBJ_ID          j1939_getCAM(
        J1939_DATA		*cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return( cbp->pCAM );
    }
    
    
    bool            j1939_setCAM(
        J1939_DATA		*cbp,
        OBJ_ID          pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
        if (pValue && obj_IsKindOf(pValue, OBJ_IDENT_J1939CAM)) {
        }
        else {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (cbp->pCAM) {
            obj_Release(cbp->pCAM);
        }
        obj_Retain(pValue);         // This is our object.
        cbp->pCAM = pValue;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C A N
    //---------------------------------------------------------------
    
    J1939_CAN_VTBL * j1939_getCAN(
        J1939_DATA		*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pCAN;
    }
    
    
    bool            j1939_setCAN(
        J1939_DATA		*this,
        J1939_CAN_VTBL  *pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);         // This is our object.
        if (this->pCAN) {
            obj_Release(this->pCAN);
        }
        this->pCAN = pValue;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //            SPN 2837 - NAME Field - Identity Number
    //---------------------------------------------------------------
    
    uint32_t        j1939_getSPN2837(
        J1939_DATA		*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return this->spn2837;
    }
    
    
    bool            j1939_setSPN2837(
        J1939_DATA		*this,
        uint32_t        value
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->spn2837 = value;
        
        // Return to caller.
        return  true;
    }

    
    
    //---------------------------------------------------------------
    //            SPN 2838 - NAME Field - Manufacturer Code
    //---------------------------------------------------------------
    
    uint16_t        j1939_getSPN2838(
        J1939_DATA		*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return( this->spn2838 );
    }
    
    
    bool            j1939_setSPN2838(
        J1939_DATA		*this,
        uint16_t        value
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->spn2838 = value;
        
        // Return to caller.
        return  true;
    }
    
    
    
    //---------------------------------------------------------------
    //             SPN 2846 - NAME Field - Industry Group
    //---------------------------------------------------------------
    
    uint8_t         j1939_getSPN2846(
        J1939_DATA		*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return( this->spn2846 );
    }
    
    
    bool            j1939_setSPN2846(
        J1939_DATA		*this,
        uint8_t         value
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->spn2846 = value;
        
        // Return to caller.
        return  true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          X m t  M s g
    //---------------------------------------------------------------
    
    bool			j1939_setXmtMsg(
        J1939_DATA		*this,
        P_XMTMSG_RTN    pXmtMsg,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pXmtMsg   = pXmtMsg;
        this->pXmtData  = pData;
        
        return true;
    }


    bool			j1939_setXmtMsgDL(
        J1939_DATA		*this,
        P_J1939_XMTRTN  pXmtMsg,
        OBJ_PTR         pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pXmtMsgDL  = pXmtMsg;
        this->pXmtDataDL = pData;
        
        return true;
    }
    
    
    //---------------------------------------------------------------
    //                          S Y S
    //---------------------------------------------------------------
    
    J1939_SYS_VTBL * j1939_getSYS(
        J1939_DATA		*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pSYS;
    }
    
    
    bool            j1939_setSYS(
        J1939_DATA		*this,
        J1939_SYS_VTBL  *pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);         // This is our object.
        if (this->pSYS) {
            obj_Release(this->pSYS);
        }
        this->pSYS = pValue;
        
        // Return to caller.
        return true;
    }
    
    
    



    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //           A d d  M e s s a g e  R e s p o n d e r
    //---------------------------------------------------------------

    bool            j1939_AddMessageResponder(
        J1939_DATA      *this,
        P_SRVCMSG_RTN   pSrvcMsg,
        OBJ_PTR         pSrvcData
    )
    {
        INTERRUPT_STATUS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->cResponders >= 4) {
            // Too many already
            DEBUG_BREAK();
            return false;
        }

        DISABLE_INTERRUPTS();
        this->pResponders[this->cResponders] = pSrvcMsg;
        this->pRespondersData[this->cResponders] = pSrvcData;
        ++this->cResponders;
        RESTORE_INTERRUPTS;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------

    void            j1939_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939_DATA		*this = objId;
        bool            fRc;
        
        // Do initialization.
        if( NULL == this ) {
            return;
        }
        
        if (obj_IsEnabled(this)) {
            fRc = j1939_Disable(this);
            // Do the best that we can...
        }
        
        if (this->pCAM) {
            obj_Release(this->pCAM);
            this->pCAM = OBJ_NIL;
        }
        
        if (this->pCAN) {
            obj_Release(this->pCAN);
            this->pCAN = OBJ_NIL;
        }
        
        if (j1939_index[0] == this) {
            j1939_index[0] = OBJ_NIL;
        }
        
        if (j1939_index[1] == this) {
            j1939_index[1] = OBJ_NIL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc( this );
        this = OBJ_NIL;
        
        // Return to caller.
    }



    //---------------------------------------------------------------
    //                       D i s a b l e
    //---------------------------------------------------------------
    
    // Terminate the CAN Service Task and reset the associated
    // variables.
    
    bool            j1939_Disable(
        OBJ_ID          objId
    )
    {
        J1939_DATA      *this = objId;
        bool            fRc;
        
        if (obj_IsEnabled(this))
            ;
        else {
            return true;
        }
        
        obj_Disable(this);
        if (this->pCAN && this->pCAN->iVtbl.pDisable) {
            fRc = this->pCAN->iVtbl.pDisable(this->pCAN);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                       E n a b l e
    //---------------------------------------------------------------
    
    bool            j1939_Enable(
        OBJ_ID          objId
    )
    {
        J1939_DATA      *this = objId;
        bool            fRc = false;
        
        if (obj_IsEnabled(this)) {
            return true;
        }
        
#ifdef XYZZY
        if (this->pBase) {
            fRc = canbase_Enable(this->pBase);
            canbase_setTimestamp(this->pBase, true);
        }
#endif
        obj_Enable(this);
        
        this->pCAM = j1939cam_Alloc();
        this->pCAM = j1939cam_Init( this->pCAM, this, this->pXmtMsg, this->pXmtData );
        if (OBJ_NIL == this->pCAM) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        // Return to caller.
        return( fRc );
    }
    
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  M e s s a g e s
    //---------------------------------------------------------------
    
    bool            j1939_HandleMessages(
        J1939_DATA      *cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg           // if NULL, receive timed out
    )
    {
        P_SRVCMSG_RTN   pResponder;
        uint32_t        i;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Broadcast the message to everyone.
        for (i=0; i<cbp->cResponders; ++i) {
            pResponder = cbp->pResponders[i];
            if (pResponder) {
                fRc = (*pResponder)( cbp->pRespondersData[i], eid, pMsg );
            }
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939_DATA *	j1939_Init(
        J1939_DATA		*this,
        uint8_t         port
    )
    {
        uint16_t		cbSize = sizeof(J1939_DATA);

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
        if (port && (port <= J1939_MAX_CAN_PORTS)) {
        }
        else {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = obj_Init( this, cbSize, OBJ_IDENT_J1939 );
        if (NULL == this) {
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_LRU);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl( this, (OBJ_IUNKNOWN *)&j1939_Vtbl );
        

#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pXmtMsg);
        BREAK_NOT_BOUNDARY4(&this->spn2837);
#endif
        
        // Return to caller.
        j1939_SharedSet(port, this);
        obj_Release(this);
        return this;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = j1939_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939 object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939_ToDebugString(
        J1939_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(j1939)\n",
                     this
                     );
        AStr_AppendA(pStr, str);
        
#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                                               this->pData,
                                                                               indent+3
                                                                               );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(j1939)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //              T r a n s m i t  M e s s a g e
    //---------------------------------------------------------------
    
    void            j1939_XmtMsg(
        J1939_DATA		*this,
        uint32_t        msDelay,
        J1939_MSG       *pMsg
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        DEBUG_BREAK();      // FIXME: Remove this!
        if (this->pXmtMsg) {
            (*this->pXmtMsg)(this->pXmtData, msDelay, pMsg);
        }
        
        // Return to caller.
    }
    
    
    
    void            j1939_XmtMsgDL(
        J1939_DATA		*this,
        uint32_t        msDelay,
        J1939_PDU       pdu,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        DEBUG_BREAK();      // FIXME: Remove this!
        if (this->pXmtMsgDL) {
            (*this->pXmtMsgDL)(this->pXmtDataDL, msDelay, pdu, cData, pData);
        }
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                          Validate
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool            j1939_Validate(
        J1939_DATA		*cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_J1939) )
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




