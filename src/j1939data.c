// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939data.c
 *	Generated 06/15/2017 10:10:23
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include <j1939data_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    // Number of Bits Conversion Table
    // (indexed by the number of bits minus one with (1 <= numBits <= 8))
    const
    uint16_t             numBitsTable[8] = {
        0x01,
        0x03,
        0x07,
        0x0F,
        0x1F,
        0x3F,
        0x7F,
        0xFF
    };
    
    
    const
    J1939_PREFERRED_ADDRESS   group0_addresses[78] = {
        {  0, "Engine #1",  NULL},
        {  1, "Engine #2",  NULL},
        {  2, "Turbocharger",  NULL},
        {  3, "Transmission #1",  NULL},
        {  4, "Transmission #2",  NULL},
        {  5, "Shift Console – Primary",  NULL},
        {  6, "Shift Console – Secondary",  NULL},
        {  7, "Power TakeOff - (Main or Rear)",  NULL},
        {  8, "Axle – Steering",  NULL},
        {  9, "Axle - Drive #1",  NULL},
        { 10, "Axle - Drive #2",  NULL},
        { 11, "Brakes - System Controller",  NULL},
        { 12, "Brakes - Steer Axle",  NULL},
        { 13, "Brakes - Drive axle #1",  NULL},
        { 14, "Brakes - Drive axle #2",  NULL},
        { 15, "Retarder – Engine",  "Engine Compression Braking"},
        { 16, "Retarder – Driveline",  NULL},
        { 17, "Cruise Control",  "Speed-based control"},
        { 18, "Fuel System",  NULL},
        { 19, "Steering Controller",  NULL},
        { 20, "Suspension – Steer Axle",  NULL},
        { 21, "Suspension – Drive Axle #1",  NULL},
        { 22, "Suspension – Drive Axle #2",  NULL},
        { 23, "Instrument Cluster",  NULL},
        { 24, "Trip Recorder",  NULL},
        { 25, "Passenger-Operator Climate Control",  NULL},
        { 26, "Electrical Charging System",  NULL},
        { 27, "Aerodynamic Control",  NULL},
        { 28, "Vehicle Navigation",  NULL},
        { 29, "Vehicle Security",  NULL},
        { 30, "Electrical System",  NULL},
        { 31, "Starter System",  NULL},
        { 32, "Tractor-Trailer Bridge #1",  "Tractor mounted bridge leading to trailer(s)"},
        { 33, "Body Controller",  NULL},
        { 34, "Auxiliary Valve Control",  NULL},
        { 35, "Hitch Control",  NULL},
        { 36, "Power TakeOff (Front or Secondary)",  NULL},
        { 37, "Off Vehicle Gateway",  NULL},
        { 38, "Virtual Terminal (in cab)",  NULL},
        { 39, "Management Computer #1",  "Manages vehicle systems, i.e. powertrain."},
        { 40, "Cab Display",  "Other than instruments or virtual terminal"},
        { 41, "Retarder, Exhaust, Engine #1",  NULL},
        { 42, "Headway Controller",  "Forward-looking collision warning, collision avoidance, speed controller, or speed matching"},
        { 43, "On-Board Diagnostic Unit",  NULL},
        { 44, "Retarder, Exhaust, Engine #2",  NULL},
        { 45, "Endurance Braking System",  NULL},
        { 46, "Hydraulic Pump Controller",  NULL},
        { 47, "Suspension - System Controller #1",  NULL},
        { 48, "Pneumatic - System Controller",  NULL},
        { 49, "Cab Controller - Primary",  NULL},
        { 50, "Cab Controller - Secondary",  NULL},
        { 51, "Tire Pressure Controller",  NULL},
        { 52, "Ignition Control Module #1",  NULL},
        { 53, "Ignition Control Module #2",  NULL},
        { 54, "Seat Controls",  NULL},
        { 55, "Lighting - Operator Controls",  NULL},
        { 56, "Rear Axle Steering Controller #1",  NULL},
        { 57, "Water Pump Controller",  NULL},
        { 58, "Passenger-Operator Climate Control #2",  NULL},
        { 59, "Transmission Display - Primary",  "Display to operate specifically in conjunction with the transmission control"},
        { 60, "Transmission Display - Secondary",  "Secondary display to operate specifically in conjunction with the transmission control"},
        { 61, "Exhaust Emission Controller",  NULL},
        { 62, "Vehicle Dynamic Stability Controller",  NULL},
        { 63, "Oil Sensor",  NULL},
        { 64, "Suspension - System Controller #2",  NULL},
        { 65, "Information System Controller #1",  "Information management system, for the vehicle’s application, such as transit passenger/fare monitoring, truck cargo management, etc."},
        { 66, "Ramp Control",  "Control of ramps, lifts, or tailgates"},
        { 67, "Clutch/Converter Controller",  "Control of either the clutch and/or hydraulic torque converter."},
        { 68, "Auxiliary Heater #1",  "Can be air, water, or other heater type and be using engine heat, electrical, or fuel fired heating source."},
        { 69, "Auxiliary Heater #2",  "Can be air, water, or other heater type and be using engine heat, electrical, or fuel fired heating source."},
        { 70, "Electronic Engine Valve Controller",  "Electronic control used to control actuation of engine intake and/or exhaust valves"},
        {249, "Off Board Diagnostic-Service Tool #1",  NULL},
        {250, "Off Board Diagnostic-Service Tool #2",  NULL},
        {251, "On-Board Data Logger",  NULL},
        {252, "Reserved for Experimental Use",  NULL},
        {253, "Reserved for OEM",  NULL},
        {254, "Null Address",  NULL},
        {255, "GLOBAL (All-Any Node)",  NULL}
    };
    
    const
    uint16_t     cGroup0_addresses = (sizeof(group0_addresses)/sizeof(J1939_PREFERRED_ADDRESS));
    
    
    
    
#ifdef XYZZY
    
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
        1,              // Data Max
        NULL,
        NULL
    };
    
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
        8,    4,      10,    0,     2,      0,    100,     0,    250
    };
    
    static
    const
    J1939_SPN_TYPE      percent03 = {
        //  Len   Mult    Div  offset  round    min    max     min    max
        8,    1,      1,     0,     0,      0,    125,     0,    250
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
#endif
    
    
    static
    const
    J1939_SPN_TYPE      temp01 = {
        J1939_SPN_TYPE_TEMPERATURE01,
        8,                      // Len in bits
        0,                      // Number of Decimal Places
        1,                      // Multiplier
        1,                      // Divisor
        -40,                    // Offset
        2,                      // Round
        -40,                    // Min Data Range
        210,                    // Max Data Range
        0,                      // Min Operational Range
        250,                    // Max Operational Range
        "Temperature",
        "deg C"
    };
    
    static
    const
    J1939_SPN_TYPE      temp02 = {
        J1939_SPN_TYPE_TEMPERATURE02,
        16,                     // Len in bits
        5,                      // Number of Decimal Places
        3125,                   // Multiplier
        10000,                  // Divisor
        -273,                   // Offset
        5000,                   // Round
        -273,                   // Min Data Range
        1735,                   // Max Data Range
        0,                      // Min Operational Range
        55520,                  // Max Operational Range
        "Temperature",
        "deg C"
    };
    
    
    static
    const
    J1939_SPN_TYPE      velocityRotational01 = {
        //  Len   Mult    Div  offset  round    min     max     min    max
        J1939_SPN_TYPE_VELOCITY01,
        16,                     // Len in bits
        3,                      // Number of Decimal Places
        125,                    // Multiplier
        1000,                   // Divisor
        0,                      // Offset
        500,                    // Round
        0,                      // Min Data Range
        8031875,                // Max Data Range - 8,031.875rpm
        0,                      // Min Operational Range
        64255,                  // Max Operational Range - 8,031.875rpm
        "speed",
        "rpm"
    };
    
    
    
    
    
    
    
    // SPN 51 - Throttle Position - The position of the valve used to regulate
    // the supply of a fluid, usually air or fuel/air mixture, to an engine.
    // 0% represents no supply and 100% is full supply.
    static
    const
    J1939_SPN           spn51 = {
        51,
        0,
        NULL    /*&percent01*/,
        "Throttle Position"
    };
    
    
    // SPN 52 - Engine Intercooler Temperature - Temperature of liquid found in the
    // intercooler located after the turbocharger.
    static
    const
    J1939_SPN           spn52 = {
        52,
        0,
        &temp01,
        "Engine Intercooler Temperature"
    };
    
    
    // SPN 69 - Two Speed Axle Switch -
    // 00 Low speed range
    // 01 High speed range
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn69 = {
        69,
        0,
        NULL    /*&???*/,
        "Two Speed Axle Switch"
    };
    
    
    // SPN 70 - Parking Brake Switch -
    // 00 Parking brake not set
    // 01 Parking brake set
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn70 = {
        70,
        0,
        NULL    /*&???*/,
        "Parking Brake Switch"
    };
    
    
    // SPN 72 - Engine Blower Bypass Valve Position - Relative position of the
    // blower bypass valve
    static
    const
    J1939_SPN           spn72 = {
        72,
        0,
        NULL    /*&percent01*/,
        "Engine Blower Bypass Valve Position"
    };
    
    
    // SPN 74 - Maximum Vehicle Speed Limit -
    static
    const
    J1939_SPN           spn74 = {
        74,
        0,
        NULL    /*&???*/,
        "Maximum Vehicle Speed Limit"
    };
    
    
    // SPN 79 - Road Surface Temperature
    static
    const
    J1939_SPN           spn79 = {
        79,
        0,
        NULL    /*&???*/,
        "Road Surface Temperature"
    };
    
    
    // SPN 84 - Wheel-Based Vehicle Speed -
    static
    const
    J1939_SPN           spn84 = {
        84,
        0,
        NULL    /*&???*/,
        "Wheel-Based Vehicle Speed"
    };
    
    
    // SPN 86 - Cruise Control Set Speed -
    static
    const
    J1939_SPN           spn86 = {
        86,
        0,
        NULL    /*&???*/,
        "Cruise Control Set Speed"
    };
    
    
    static
    const
    J1939_SPN           spn87 = {
        87,
        0,
        NULL    /*&???*/,
        "Cruise Control High Set Limit Speed"
    };
    
    
    static
    const
    J1939_SPN           spn88 = {
        88,
        0,
        NULL    /*&???*/,
        "Cruise Control Low Set Limit Speed"
    };
    
    
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
    J1939_SPN           spn91 = {
        91,
        0,
        NULL    /*&percent01*/,
        "Accelerator Pedal Position 1"
    };
    
    
    // SPN 92 - Percent Load At Current Speed - The ratio of actual engine percent
    // torque (indicated) to maximum indicated torque available at the current en-
    // gine speed, clipped to zero torque during engine braking.
    static
    const
    J1939_SPN           spn92 = {
        92,
        0,
        NULL    /*&percent03*/,
        "Percent Load At Current Speed"
    };
    
    
    // SPN 98 - Engine Oil Level - Ratio of current volume of engine sump oil
    // to maximum required volume.
    static
    const
    J1939_SPN           spn98 = {
        98,
        0,
        NULL    /*&percent01*/,
        "Engine Oil Level"
    };
    
    
    // SPN 99 - Engine Oil Filter Differential Pressure - Change in engine oil
    // pressure, measured across the filter, due to the filter and any accumulation
    // of solid or semisolid material on or in the filter.
    static
    const
    J1939_SPN           spn99 = {
        99,
        0,
        NULL    /*&pressure01*/,
        "Engine Oil Filter Differential Pressure"
    };
    
    
    // SPN 102 - Boost Pressure - Gage pressure of air measured downstream on the
    // compressor discharge side of the turbocharger. See also SPNs 1127-1130 for
    // alternate range and resolution. If there is one boost pressure to report
    // and this range and resolution is adequate, this parameter should be used.
    static
    const
    J1939_SPN           spn102 = {
        102,
        0,
        NULL    /*&pressure02*/,
        "Boost Pressure"
    };
    
    
    // SPN 108 - Barometric Pressure
    static
    const
    J1939_SPN           spn108 = {
        108,
        0,
        NULL    /*&???*/,
        "Barometric Pressure"
    };
    
    
    // SPN 110 - Engine Coolant Temperature - Temperature of liquid found in engine
    // cooling system.
    static
    const
    J1939_SPN           spn110 = {
        110,
        0,
        NULL    /*&temp01*/,
        "Engine Coolant Temperature"
    };
    
    
    // SPN 114 - Net Battery Current
    static
    const
    J1939_SPN           spn114 = {
        114,
        0,
        NULL    /*&???*/,
        "Net Battery Current"
    };
    
    
    // SPN 115 - Alternator Current
    static
    const
    J1939_SPN           spn115 = {
        115,
        0,
        NULL    /*&???*/,
        "Alternator Current"
    };
    
    
    // SPN 123 - Clutch Pressure
    static
    const
    J1939_SPN           spn123 = {
        123,
        0,
        NULL    /*&???*/,
        "Clutch Pressure"
    };
    
    
    // SPN 124 - Transmission Oil Level
    static
    const
    J1939_SPN           spn124 = {
        124,
        0,
        NULL    /*&???*/,
        "Transmission Oil Level"
    };
    
    
    // SPN 126 - Transmission Filter Differential Pressure
    static
    const
    J1939_SPN           spn126 = {
        126,
        0,
        NULL    /*&???*/,
        "Transmission Filter Differential Pressure"
    };
    
    
    // SPN 127 - Transmission Oil Pressure
    static
    const
    J1939_SPN           spn127 = {
        127,
        0,
        NULL    /*&???*/,
        "Transmission Oil Pressure"
    };
    
    
    // SPN 158 - Battery Potential (Voltage), Switched
    static
    const
    J1939_SPN           spn158 = {
        158,
        0,
        NULL    /*&???*/,
        "Battery Potential (Voltage), Switched"
    };
    
    
    // SPN 159 - Transmission Oil Pressure - Gage pressure of gas supply to fuel
    // metering device.
    // x = spn159 * 0.5 kPa;   range: 0 - 32,127.5 kPa
    static
    const
    J1939_SPN           spn159 = {
        159,
        0,
        NULL    /*&???*/,
        "Engine Gas Supply Pressure"
    };
    
    
    // SPN 162 - Transmission Requested Range
    // Range selected by the operator. Characters may include P, Rx, Rx-1...R2,
    // R1, R, Nx, Nx-1...N2, N1, N, D, D1, D2..., Dx, L, L1, L2..., Lx-1, 1, 2,
    // 3,... If only one displayed character is required, the second character
    // shall be used and the first character shall be a space (ASCII 32) or a
    // control character (ASCII 0 to 31). If the first character is a control
    // character, refer to the manufacturer’s application document for definition.
    static
    const
    J1939_SPN           spn162 = {
        162,
        0,
        NULL    /*&???*/,
        "Transmission Requested Range"
    };
    
    
    // SPN 163 - Transmission Current Range
    // Range selected by the operator. Characters may include P, Rx, Rx-1...R2,
    // R1, R, Nx, Nx-1...N2, N1, N, D, D1, D2..., Dx, L, L1, L2..., Lx-1, 1, 2,
    // 3,... If only one displayed character is required, the second character
    // shall be used and the first character shall be a space (ASCII 32) or a
    // control character (ASCII 0 to 31). If the first character is a control
    // character, refer to the manufacturer’s application document for definition.
    static
    const
    J1939_SPN           spn163 = {
        163,
        0,
        NULL    /*&???*/,
        "Transmission Current Range"
    };
    
    
    // SPN 166 - Engine Rated Power (kW)
    // Net brake power that the engine will deliver continuously,
    // specified for a given application at a rated speed.
    //                                      // actual_power = (ratedPower * 0.5) kW
    //                                      // range: 0 - 32127.5 kW
    static
    const
    J1939_SPN           spn166 = {
        166,
        0,
        NULL    /*&???*/,
        "Engine Rated Power (kW)"
    };
    
    
    // SPN 167 - Charging System Potential (Voltage)
    static
    const
    J1939_SPN           spn167 = {
        167,
        0,
        NULL    /*&???*/,
        "Charging System Potential (Voltage)"
    };
    
    
    // SPN 168 - Electrical Potential (Voltage)
    static
    const
    J1939_SPN           spn168 = {
        168,
        0,
        NULL    /*&???*/,
        "Electrical Potential (Voltage)"
    };
    
    
    // SPN 170 - Cab Interior Temperature
    static
    const
    J1939_SPN           spn170 = {
        170,
        0,
        &temp01,
        "Cab Interior Temperature"
    };
    
    
    // SPN 171 - Ambient Air Temperature
    static
    const
    J1939_SPN           spn171 = {
        171,
        0,
        &temp01,
        "Ambient Air Temperature"
    };
    
    
    // SPN 172 - Engine Air Inlet Temperature
    static
    const
    J1939_SPN           spn172 = {
        172,
        0,
        &temp01,
        "Engine Air Inlet Temperature"
    };
    
    
    // SPN 174 - Fuel Temperature - Temperature of fuel entering injectors.
    static
    const
    J1939_SPN           spn174 = {
        174,
        0,
        &temp01,
        "Fuel Temperature"
    };
    
    
    // SPN 175 - Engine Oil Temperature 1 - Temperature of the engine lubricant.
    static
    const
    J1939_SPN           spn175 = {
        175,
        0,
        &temp02,
        "Engine Oil Temperature 1"
    };
    
    
    // SPN 176 - Turbo Oil Temperature - Temperature of the turbocharger lubricant.
    static
    const
    J1939_SPN           spn176 = {
        176,
        0,
        &temp02,
        "Turbo Oil Temperature"
    };
    
    
    // SPN 177 - Transmission Oil Temperature
    static
    const
    J1939_SPN           spn177 = {
        177,
        0,
        NULL    /*&???*/,
        "Transmission Oil Temperature"
    };
    
    
    // SPN 190 - Engine Speed - Actual engine speed which is calculated over a
    // minimum crankshaft angle of 720 degrees divided by the number of cylinders.
    static
    const
    J1939_SPN           spn190 = {
        190,
        0,
        &velocityRotational01,
        "Engine Speed"
    };
    
    
    // SPN 191 - Transmission Output Shaft Speed - Calculated speed of the transmission output shaft.
    static
    const
    J1939_SPN           spn191 = {
        191,
        0,
        &velocityRotational01,
        "Transmission Output Shaft Speed"
    };
    
    
    // SPN 234 - Software Identification Field
    // Delimited by '*'
    static
    const
    J1939_SPN           spn234 = {
        234,
        0,
        NULL    /*&????*/,
        "Software Identification Field"
    };
    
    
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
    J1939_SPN           spn512 = {
        512,
        0,
        NULL    /*&percent02*/,
        "Driver's Demand Engine - Percent Torque"
    };
    
    
    // SPN 513 - Actual Engine - Percent Torque - The calculated output
    // torque of the engine. The data is transmitted in indicated torque as a
    // percent of reference engine torque (see the engine configuration message,
    // PGN 65251). The engine percent torque value will not be less than zero and
    // it includes the torque developed in the cylinders required to overcome
    // friction.
    static
    const
    J1939_SPN           spn513 = {
        513,
        0,
        NULL    /*&percent02*/,
        "Actual Engine - Percent Torque"
    };
    
    
    // SPN 518 - Engine Requested Torque/Torque Limit
    static
    const
    J1939_SPN           spn518 = {
        518,
        0,
        NULL    /*&????*/,
        "Engine Requested Torque/Torque Limit"
    };
    
    
    // SPN 523 - Transmission Current Gear
    // Offset: -125   Data Range: -125 - 125 (Negative values == reverse)
    // Operational Range: -125 to +125, negative values are reverse gears,
    //                                  positive values are forward gears,
    //                                  zero is neutral. 251 (0xFB) is park.
    // PGN: 61445
    // The gear currently engaged in the transmission or the last gear engaged
    // while the transmission is in the process of shifting to the new or
    // selected gear. Transitions toward a destination gear will not be indicated.
    // Once the selected gear has been engaged then Transmission Current Gear
    // (SPN 525) will reflect that gear.
    static
    const
    J1939_SPN           spn523 = {
        523,
        0,
        NULL    /*&????*/,
        "Transmission Current Gear"
    };
    
    
    // SPN 524 - Transmission Selected Gear
    // Offset: -125   Data Range: -125 - 125 (Negative values == reverse)
    // Operational Range: -125 to +125, negative values are reverse gears,
    //                                  positive values are forward gears,
    //                                  zero is neutral. 251 (0xFB) is park.
    // PGN: 61445
    // The gear that the transmission will attempt to achieve during the current
    // shift if a shift is in progress, or the next shift if one is pending
    // (i.e., waiting for torque reduction to initiate the shift).
    static
    const
    J1939_SPN           spn524 = {
        524,
        0,
        NULL    /*&????*/,
        "Transmission Selected Gear"
    };
    
    
    // SPN 527 - Cruise Control States
    // 000 Off/Disabled
    // 001 Hold
    // 010 Accelerate
    // 011 Decelerate
    // 100 Resume
    // 101 Set
    // 110 Accelerator Override
    // 111 Not available
    static
    const
    J1939_SPN           spn527 = {
        527,
        0,
        NULL    /*&????*/,
        "Cruise Control States"
    };
    
    
    // SPN 558 - Accelerator Pedal 1 Low Idle Switch - Switch signal
    // which indicates the state of the accelerator pedal 1 low idle switch.
    // The low idle switch is defined in SAE J1843.
    // 00 Accelerator pedal 1 not in low idle condition
    // 01 Accelerator pedal 1 in low idle condition
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn558 = {
        558,
        0,
        NULL    /*&bits02*/,
        "Accelerator Pedal 1 Low Idle Switch"
    };
    
    
    // SPN 559 - Accelerator Pedal Kickdown Switch - Switch signal which
    // indicates whether the accelerator pedal kickdown switch is opened
    // or closed. The kickdown switch is defined in SAE J1843.
    // 00 Kickdown passive
    // 01 Kickdown active
    static
    const
    J1939_SPN           spn559 = {
        559,
        0,
        NULL    /*&bits01*/,
        "Accelerator Pedal Kickdown Switch"
    };
    
    
    // SPN 590 - Engine Idle Shutdown Timer State
    // 00 Inactive
    // 01 Active
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn590 = {
        590,
        0,
        NULL    /*&????*/,
        "Engine Idle Shutdown Timer State"
    };
    
    
    // SPN 591 - Engine Idle Shutdown Timer Function
    // 00  Disabled in calibration
    // 01  Enabled in calibration
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn591 = {
        591,
        0,
        NULL    /*&????*/,
        "Engine Idle Shutdown Timer Function"
    };
    
    
    // SPN 592 - Engine Idle Shutdown Timer Override
    // 00 Inactive
    // 01 Active
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn592 = {
        592,
        0,
        NULL    /*&????*/,
        "Engine Idle Shutdown Timer Override"
    };
    
    
    // SPN 593 - Engine Idle Shutdown has Shutdown Engine
    // 00 No
    // 01 Yes
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn593 = {
        593,
        0,
        NULL    /*&????*/,
        "Engine Idle Shutdown has Shutdown Engine"
    };
    
    
    // SPN 594 - Engine Idle Shutdown Driver Alert Mode
    // Status signal which indicates the status of the driver alert mode
    // of the idle shutdown timer system. While the driver alert mode is
    // active, the idle shutdown timer may be overridden.
    // 00 Inactive
    // 01 Active
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn594 = {
        594,
        0,
        NULL    /*&????*/,
        "Engine Idle Shutdown Driver Alert Mode"
    };
    
    
    // SPN 595 - Engine Idle Shutdown has Shutdown Engine
    // 00 Cruise control switched off
    // 01 Cruise control switched on
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn595 = {
        595,
        0,
        NULL    /*&????*/,
        "Cruise Control Active"
    };
    
    
    // SPN 596 - Cruise Control Enable Switch
    // 00 Cruise control disabled
    // 01 Cruise control enabled
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn596 = {
        596,
        0,
        NULL    /*&????*/,
        "Cruise Control Enable Switch"
    };
    
    
    // SPN 597 - Brake Switch
    // 00 Brake pedal released
    // 01 Brake pedal depressed
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn597 = {
        597,
        0,
        NULL    /*&????*/,
        "Brake Switch"
    };
    
    
    // SPN 598 - Clutch Switch
    // 00 Clutch pedal released
    // 01 Clutch pedal depressed
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn598 = {
        598,
        0,
        NULL    /*&????*/,
        "Clutch Switch"
    };
    
    
    // SPN 599 - Cruise Control Set Switch
    // 00 Cruise control activator not in the position “set”
    // 01 Cruise control activator in position “set”
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn599 = {
        599,
        0,
        NULL    /*&????*/,
        "Cruise Control Set Switch"
    };
    
    
    // SPN 600 - Cruise Control Coast (Decelerate) Switch
    // 00 Cruise control activator not in the position “coast”
    // 01 Cruise control activator in position “coast”
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn600 = {
        600,
        0,
        NULL    /*&????*/,
        "Cruise Control Coast (Decelerate) Switch"
    };
    
    
    // SPN 601 - Cruise Control Resume Switch
    // 00 Cruise control activator not in the position “resume”
    // 01 Cruise control activator in position “resume”
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn601 = {
        601,
        0,
        NULL    /*&????*/,
        "Cruise Control Resume Switch"
    };
    
    
    // SPN 602 - Cruise Control Accelerate Switch
    // 00 Cruise control activator not in the position “accelerate”
    // 01 Cruise control activator in position “accelerate”
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn602 = {
        602,
        0,
        NULL    /*&????*/,
        "Cruise Control Accelerate Switch"
    };
    
    
    // SPN 605 - Refrigerant High Pressure Switch
    // 00 Pressure normal
    // 01 Pressure too high, compressor clutch may be disengaged
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn605 = {
        605,
        0,
        NULL    /*&????*/,
        "Refrigerant High Pressure Switch"
    };
    
    
    // SPN 695 - Engine Override Control Mode
    // 00 Override disabled - Disable any existing control commanded by the
    //      source of this command.
    // 01 Speed control - Govern speed to the included “desired speed” value.
    // 10 Torque control - Control torque to the included “desired torque” value.
    // 11 Speed/torque limit control - Limit speed and/or torque based on the
    //      included limit values. The speed limit governor is a droop governor
    //      where the speed limit value defines the speed at the maximum torque
    //      available during this operation.
    static
    const
    J1939_SPN           spn695 = {
        695,
        0,
        NULL    /*&????*/,
        "Engine Override Control Mode"
    };
    
    
    // SPN 696 - Engine Requested Speed Control Conditions
    // 00 Transient Optimized for driveline disengaged and non-lockup conditions
    // 01 Stability Optimized for driveline disengaged and non-lockup conditions
    // 10 Stability Optimized for driveline engaged and/or in lockup condition
    //      1 (e.g., vehicle driveline)
    // 11 Stability Optimized for driveline engaged and/or in lockup condition
    //      2 (e.g., PTO driveline)
    static
    const
    J1939_SPN           spn696 = {
        696,
        0,
        NULL    /*&????*/,
        "Engine Requested Speed Control Conditions"
    };
    
    
    // SPN 875 - Refrigerant Low Pressure Switch
    // 00 Pressure normal
    // 01 Pressure too low, compressor clutch may be disengaged
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn875 = {
        875,
        0,
        NULL    /*&????*/,
        "Refrigerant Low Pressure Switch"
    };
    
    
    // SPN 897 - Override Control Mode Priority
    static
    const
    J1939_SPN           spn897 = {
        897,
        0,
        NULL    /*&????*/,
        "Override Control Mode Priority"
    };
    
    
    // SPN 898 - Engine Requested Speed/Speed Limit
    // Parameter provided to the engine from external sources in the torque/
    // speed control message. This is the engine speed which the engine is
    // expected to operate at if the speed control mode is active or the
    // engine speed which the engine is not expected to exceed if the speed
    // limit mode is active.
    // Resolution: 0.125 rpm/bit   range: 0 - 8,031.875 rpm
    static
    const
    J1939_SPN           spn898 = {
        898,
        0,
        NULL    /*&????*/,
        "Engine Requested Speed/Speed Limit"
    };
    
    
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
    J1939_SPN           spn899 = {
        899,
        0,
        NULL    /*&bits03*/,
        "Engine Torque Mode"
    };
    
    
    // SPN 917 - High Resolution Total Vehicle Distance
    static
    const
    J1939_SPN           spn917 = {
        917,
        0,
        NULL    /*&????*/,
        "High Resolution Total Vehicle Distance"
    };
    
    
    // SPN 918 - High Resolution Trip Distance
    static
    const
    J1939_SPN           spn918 = {
        918,
        0,
        NULL    /*&????*/,
        "High Resolution Trip Distance"
    };
    
    
    // SPN 965 - Number of Software Identification Fields
    static
    const
    J1939_SPN           spn965 = {
        965,
        0,
        NULL    /*&????*/,
        "Number of Software Identification Fields"
    };
    
    
    // SPN 966 - Engine Test Mode Switch
    // 00 Off
    // 01 On
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn966 = {
        966,
        0,
        NULL    /*&????*/,
        "Engine Test Mode Switch"
    };
    
    
    // SPN 967 - Engine Idle Decrement Switch
    // 00 Off
    // 01 On
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn967 = {
        967,
        0,
        NULL    /*&????*/,
        "Engine Idle Decrement Switch"
    };
    
    
    // SPN 968 - Engine Idle Increment Switch
    // 00 Off
    // 01 On
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn968 = {
        968,
        0,
        NULL    /*&????*/,
        "Engine Idle Increment Switch"
    };
    
    
    // SPN 969 - Remote Accelerator Enable Switch
    // 00 Off
    // 01 On
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn969 = {
        969,
        0,
        NULL    /*&????*/,
        "Remote Accelerator Enable Switch"
    };
    
    
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
    J1939_SPN           spn974 = {
        974,
        0,
        NULL    /*&percent01*/,
        "Remote Accelerator Pedal Position"
    };
    
    
    // SPN 976 - PTO State
    // 00000 Off/Disabled
    // 00001 Hold
    // 00010 Remote Hold
    // 00011 Standby
    // 00100 Remote Standby
    // 00101 Set
    // 00110 Decelerate/Coast
    // 00111 Resume
    // 01000 Accelerate
    // 01001 Accelerator Override
    // 01010 Preprogrammed set speed 1
    // 01011 Preprogrammed set speed 2
    // 01100 Preprogrammed set speed 3
    // 01101 Preprogrammed set speed 4
    // 01110 Preprogrammed set speed 5
    // 01111 Preprogrammed set speed 6
    // 10000 Preprogrammed set speed 7
    // 10001 Preprogrammed set speed 8
    // 10010 PTO set speed memory 1
    // 10011 PTO set speed memory 2
    // 10100 Not defined
    // 10101 Not defined
    // 10110 Not defined
    // 10111 Not defined
    // 11110 Not defined
    // 11111 Not available
    static
    const
    J1939_SPN           spn976 = {
        976,
        0,
        NULL    /*&????*/,
        "PTO State"
    };
    
    
    // SPN 985 - A/C High Pressure Fan Switch
    // 00 Pressure normal
    // 01 Pressure too high, fan may be engaged
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn985 = {
        985,
        0,
        NULL    /*&????*/,
        "A/C High Pressure Fan Switch"
    };
    
    
    // SPN 986 - Requested Percent Fan Speed
    static
    const
    J1939_SPN           spn986 = {
        986,
        0,
        NULL    /*&????*/,
        "Requested Percent Fan Speed"
    };
    
    
    // SPN 1081 - Engine Wait to Start Lamp
    // Lamp signal which indicates that the engine is too cold to start
    // and the operator should wait until the signal becomes inactive
    // (turns off).
    // 00 Off
    // 01 On
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1081 = {
        1081,
        0,
        NULL    /*&????*/,
        "Engine Wait to Start Lamp"
    };
    
    
    // SPN 1107 - Engine Protection System Timer State
    // 00 Inactive
    // 01 Active
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1107 = {
        1107,
        0,
        NULL    /*&????*/,
        "Engine Protection System Timer State"
    };
    
    
    // SPN 1108 - Engine Protection System Timer Override
    // 00 Inactive
    // 01 Active
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1108 = {
        1107,
        0,
        NULL    /*&????*/,
        "Engine Protection System Timer Override"
    };
    
    
    // SPN 1109 - Engine Protection System Approaching Shutdown
    // 00 Not Approaching
    // 01 Approaching
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1109 = {
        1109,
        0,
        NULL    /*&????*/,
        "Engine Protection System Approaching Shutdown"
    };
    
    
    // SPN 1110 - Engine Protection System has Shutdown Engine
    // 00 No
    // 01 Yes
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1110 = {
        1110,
        0,
        NULL    /*&????*/,
        "Engine Protection System Timer State"
    };
    
    
    // SPN 1111 - Engine Protection System Configuration
    // 00 Disabled in calibration
    // 01 Enabled in calibration
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1111 = {
        1111,
        0,
        NULL    /*&????*/,
        "Engine Protection System Configuration"
    };
    
    
    // SPN 1134 - Engine Intercooler Thermostat Opening - The current position
    // of the thermostat used to regulate the temperature of the engine intercooler.
    // A value of 0% represents the thermostat being completely closed and 100%
    // represents the thermostat being completely open.
    static
    const
    J1939_SPN           spn1134 = {
        1134,
        0,
        NULL    /*&percent01*/,
        "Engine Intercooler Thermostat Opening"
    };
    
    
    // SPN 1237 - Engine Shutdown Override Switch
    // 00 Off
    // 01 On
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1237 = {
        1237,
        0,
        NULL    /*&????*/,
        "Engine Shutdown Override Switch"
    };
    
    
    // SPN 1437 - Road Speed Limit Status - Status (active or not active) of the
    // system used to limit maximum vehicle velocity.
    // 00 - Active
    // 01 - Not Active
    // NOTE - While somewhat inconsistent with other J1939 status parameters, the
    // states defining 00 = active and 01 = inactive for Road Speed Limit Status
    // are NOT typographical errors, and should be implemented as stated.
    static
    const
    J1939_SPN           spn1437 = {
        1437,
        0,
        NULL    /*&bits01*/,
        "Road Speed Limit Status"
    };
    
    
    // SPN 1480 - Source Address of Controlling Device for Retarder Control -
    // The source address of the SAE J1939 device currently controlling the
    // retarder. It is used to expand the torque mode parameter (see SPN 899)
    // in cases where control is in response to an ECU that is not listed in
    // Table SPN899_A. Its value may be the source address of the ECU trans-
    // mitting the message (which means that no external SAE J1939 message is
    // providing the active command) or the source address of the SAE J1939
    // ECU that is currently providing the active command in a TSC1 (see PGN 0)
    // or similar message. Note that if this parameter value is the same as
    // the source address of the device transmitting it, the control may be
    // due to a message on a non-SAE J1939 data link such as SAE J1922 or a
    // proprietary link.
    static
    const
    J1939_SPN           spn1480 = {
        1480,
        0,
        NULL    /*&sourceAddress*/,
        "Source Address of Controlling Device for Retarder Control"
    };
    
    
    // SPN 1481 - Source Address of Controlling Device for Brake Control -
    // The source address of the SAE J1939 device currently controlling the
    // brake system. Its value may be the source address of the ECU trans-
    // mitting the message (which means that no external SAE J1939 message
    // is providing the active command) or the source address of the SAE
    // J1939 ECU that is currently providing the active command in a TSC1
    // (see PGN 0) or similar message.
    // Note that if this parameter value is the same as the source address
    // of the device transmitting it, the control may be due to a message
    // on a non-SAE J1939 data link such as SAE J1922 or a proprietary link.
    static
    const
    J1939_SPN           spn1481 = {
        1481,
        0,
        NULL    /*&sourceAddress*/,
        "Source Address of Controlling Device for Brake Control"
    };
    
    
    // SPN 1482 - Source Address of Controlling Device for Transmission Control -
    // The source address of the SAE J1939 device currently controlling the
    // transmission. Its value may be the source address of the ECU transmitting
    // the message (which means that no external SAE J1939 message is providing
    // the active command) or the source address of the SAE J1939 ECU that is
    // currently providing the active command in a TSC1 (see PGN 0) or similar
    // message.
    // Note that if this parameter value is the same as the source address of the
    // device transmitting it, the control may be due to a message on a non-SAE
    // J1939 data link such as SAE J1922 or a proprietary link.
    static
    const
    J1939_SPN           spn1482 = {
        1482,
        0,
        NULL    /*&sourceAddress*/,
        "Source Address of Controlling Device for Transmission Control"
    };
    
    
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
    J1939_SPN           spn1483 = {
        1483,
        0,
        NULL    /*&sourceAddress*/,
        "Source Address of Controlling Device for Engine Control"
    };
    
    
    // SPN 1633 - Cruise Control Pause Switch -
    // 00 Off
    // 01 On
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1633 = {
        1633,
        0,
        NULL    /*&????*/,
        "Cruise Control Pause Switch"
    };
    
    
    // SPN 1636 - Intake Manifold 1 Air Temperature (High Resolution) - Temperature
    // of pre-combustion air found in intake manifold of engine air supply system.
    // The higher resolution is required for control purposes.
    static
    const
    J1939_SPN           spn1636 = {
        1636,
        0,
        NULL    /*&temp02*/,
        "Intake Manifold 1 Air Temperature (High Resolution)"
    };
    
    
    // SPN 1637 - Engine Coolant Temperature (High Resolution) - Temperature of
    // liquid found in engine cooling system. The higher resolution is required
    // for control purposes.
    static
    const
    J1939_SPN           spn1637 = {
        1637,
        0,
        NULL    /*&temp02*/,
        "Engine Coolant Temperature (High Resolution)"
    };
    
    
    // SPN 1653 - Vehicle Limiting Speed Governor Enable Switch
    // 00 Switch disabled
    // 01 Switch enabled
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1653 = {
        1653,
        0,
        NULL    /*&????*/,
        "Vehicle Limiting Speed Governor Enable Switch"
    };
    
    
    // SPN 1654 - Vehicle Limiting Speed Governor Increment Switch
    // 00 Switch in the off state
    // 01 Switch in the on state
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1654 = {
        1654,
        0,
        NULL    /*&????*/,
        "Vehicle Limiting Speed Governor Increment Switch"
    };
    
    
    // SPN 1655 - Vehicle Limiting Speed Governor Decrement Switch
    // Switch signal which decreases the Vehicle Limiting Speed Governor (VLSG).
    // 00 Switch in the off state
    // 01 Switch in the on state
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1655 = {
        1655,
        0,
        NULL    /*&????*/,
        "Vehicle Limiting Speed Governor Decrement Switch"
    };
    
    
    // SPN 1656 - Engine Automatic Start Enable Switch
    // Switch signal which enables the idle management system to be enabled. When
    // this system is enabled with the engine in an idle mode and safe operating
    // conditions existing, then the engine may be started or stopped automatically.
    // 00 Switch in the off state
    // 01 Switch in the on state
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1656 = {
        1656,
        0,
        NULL    /*&????*/,
        "Engine Automatic Start Enable Switch"
    };
    
    
    // SPN 1666 - Automatic Gear Shifting Enable Switch
    static
    const
    J1939_SPN           spn1666 = {
        1666,
        0,
        NULL    /*&????*/,
        "Automatic Gear Shifting Enable Switch"
    };
    
    
    // SPN 1675 - Engine Starter Mode - There are several phases in a
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
    J1939_SPN           spn1675 = {
        1675,
        0,
        NULL    /*&bits03*/,
        "Engine Starter Mode"
    };
    
    
    // SPN 1682 - Battery Main Switch Hold Request
    // 00 Release Battery Main Switch
    // 01 Hold Battery Main Switch
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1682 = {
        1682,
        0,
        NULL    /*&????*/,
        "Battery Main Switch Hold Request"
    };
    
    
    // SPN 1683 - Auxiliary Heater Mode Request
    // 0000 De-activate auxiliary heater
    // 0001 Off due to ADR per European Regulations for Transport of hazardous materials
    // 0010 Economy mode
    // 0011 Normal mode
    // 0100-1101 Not defined
    // 1110 Reserved
    // 1111 Don't care/take no action
    static
    const
    J1939_SPN           spn1683 = {
        1683,
        0,
        NULL    /*&????*/,
        "Auxiliary Heater Mode Request"
    };
    
    
    // SPN 1684 - Auxiliary Heater Coolant Pump Request
    // 00 Deactivate water pump
    // 01 Activate water pump
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1684 = {
        1684,
        0,
        NULL    /*&????*/,
        "Auxiliary Heater Coolant Pump Request"
    };
    
    
    // SPN 1685 - Request Engine Zone Heating
    // 00 Do not heat engine zone
    // 01 Heat engine zone
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1685 = {
        1685,
        0,
        NULL    /*&????*/,
        "Auxiliary Heater Coolant Pump Request"
    };
    
    
    // SPN 1686 - Request Cab Zone Heating
    // 00 Do not cab engine zone
    // 01 Heat cab zone
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1686 = {
        1686,
        0,
        NULL    /*&????*/,
        "Request Cab Zone Heating"
    };
    
    
    // SPN 1691 - Cab Interior Temperature Command
    static
    const
    J1939_SPN           spn1691 = {
        1691,
        0,
        NULL    /*&????*/,
        "Cab Interior Temperature Command"
    };
    
    
    // SPN 1714 - Operator Seat Direction Switch
    // 00 Operator seat not facing forward
    // 01 Operator seat is facing forward
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1714 = {
        1714,
        0,
        NULL    /*&????*/,
        "Operator Seat Direction Switch"
    };
    
    
    // SPN 1856 - Seat Belt Switch
    // 00 NOT Buckled
    // 01 OK - Seat Belt is buckled
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn1856 = {
        1856,
        0,
        NULL    /*&????*/,
        "Seat Belt Switch"
    };
    
    
    // SPN 2432 - Engine Demand - Percent Torque - The requested torque output of
    // the engine by all dynamic internal inputs, including smoke control, noise
    // control and low and high speed governing.
    static
    const
    J1939_SPN           spn2432 = {
        2432,
        0,
        NULL    /*&percent02*/,
        "Engine Demand - Percent Torque"
    };
    
    
    // SPN 2540 - Parameter Group Number (RQST)
    static
    const
    J1939_SPN           spn2540 = {
        2540,
        0,
        NULL    /*&????*/,
        "Parameter Group Number (RQST)"
    };
    
    
    // SPN 2550 - Manufacturer Specific Information (PropA_PDU1)
    //  Variable length data specified by manufacturer (0 to 1785 bytes)
    static
    const
    J1939_SPN           spn2550 = {
        2540,
        0,
        NULL    /*&????*/,
        "Manufacturer Specific Information (PropA_PDU1)"
    };
    
    
    // SPN 2574 - Parameter Group Number (RQST2)
    static
    const
    J1939_SPN           spn2574 = {
        2574,
        0,
        NULL    /*&????*/,
        "Parameter Group Number (RQST2)"
    };
    
    
    // SPN 2575 - Use Transfer Mode
    // 00 No
    // 01 Yes
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn2575 = {
        2575,
        0,
        NULL    /*&????*/,
        "Use Transfer Mode"
    };
    
    
    // SPN 2596 - Selected Maximum Vehicle Speed Limit
    static
    const
    J1939_SPN           spn2596 = {
        2596,
        0,
        NULL    /*&????*/,
        "Selected Maximum Vehicle Speed Limit"
    };
    
    
    // SPN 2812 - Engine Overspeed Test
    // 00 Engine Overspeed Test Not Active
    // 01 Engine Overspeed Test Active
    // 10 Reserved
    // 11 Not available
    static
    const
    J1939_SPN           spn2812 = {
        2812,
        0,
        NULL    /*&????*/,
        "Engine Overspeed Test"
    };
    
    
    // SPN 2813 - Engine Air Shutoff Command Status
    // 00 No
    // 01 Yes
    // 10 Error
    // 11 Not available
    static
    const
    J1939_SPN           spn2813 = {
        2813,
        0,
        NULL    /*&????*/,
        "Engine Air Shutoff Command Status"
    };
    
    
    // SPN 2814 - Engine Overspeed Test
    // 00 Disabled
    // 01 Enabled
    // 10 Reserved
    // 11 Not available
    static
    const
    J1939_SPN           spn2814 = {
        2814,
        0,
        NULL    /*&????*/,
        "Engine Overspeed Test"
    };
    
    
    // SPN 2815 - Engine Alarm Output Command Status
    // 00 Engine Alarm Output Command Not Active
    // 01 Engine Alarm Output Command Active
    // 10 Reserved
    // 11 Not available
    static
    const
    J1939_SPN           spn2815 = {
        2815,
        0,
        NULL    /*&????*/,
        "Engine Alarm Output Command Status"
    };
    
    
    // SPN 2848 - Engine Demand - Percent Torque - The requested torque output of
    static
    const
    J1939_SPN           spn2848 = {
        2848,
        0,
        NULL    /*&bits64*/,
        ""
    };
    
    
    // SPN 3026 - Transmission Oil Level Measurement Status
    static
    const
    J1939_SPN           spn3026 = {
        3026,
        0,
        NULL    /*&???*/,
        "Transmission Oil Level Measurement Status"
    };
    
    
    // SPN 3027 - Transmission Oil Level High / Low
    static
    const
    J1939_SPN           spn3027 = {
        3027,
        0,
        NULL    /*&???*/,
        "Transmission Oil Level High / Low"
    };
    
    
    // SPN 3028 - Transmission Oil Level Countdown Timer
    static
    const
    J1939_SPN           spn3028 = {
        3028,
        0,
        NULL    /*&???*/,
        "Transmission Oil Level Countdown Timer"
    };
    
    
    // SPN 3349 - TSC1 Transmission Rate
    static
    const
    J1939_SPN           spn3349 = {
        3349,
        0,
        NULL    /*&????*/,
        "TSC1 Transmission Rate"
    };
    
    
    // SPN 3350 - TSC1 Control Purpose
    static
    const
    J1939_SPN           spn3350 = {
        3350,
        0,
        NULL    /*&????*/,
        "TSC1 Control Purpose"
    };
    
    
    

    
    
    
    
    
    static
    const
    J1939_PGNSPN        pgn0spns[7] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        {     0,  695,   2,    0,     0,    0,  &spn695 },
        {     0,  696,   2,    2,     0,    0,  &spn696 },
        {     0,  897,   2,    4,     0,    0,  &spn897 },
        {     0,  898,  16,    0,     1,    0,  &spn898 },
        {     0,  518,   8,    0,     3,    0,  &spn518 },
        {     0, 3349,   3,    0,     4,    0,  &spn3349 },
        {     0, 3350,   5,    3,     4,    0,  &spn3350 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn51456spns[2] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 51456, 2574,  24,    0,     0,    0,  &spn2574 },
        { 51456, 2575,   2,    0,     3,    0,  &spn2575 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn57344spns[15] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 57344,  986,   8,    0,     0,    0,  &spn986 },
        { 57344, 1691,  16,    0,     2,    0,  &spn1691 },
        { 57344, 1684,   2,    0,     3,    0,  &spn1684 },
        { 57344, 1682,   2,    2,     3,    0,  &spn1682 },
        { 57344, 1714,   2,    4,     3,    0,  &spn1714 },
        { 57344, 1856,   2,    6,     3,    0,  &spn1856 },
        { 57344, 1655,   2,    2,     4,    0,  &spn1655 },
        { 57344, 1654,   2,    4,     4,    0,  &spn1654 },
        { 57344, 1653,   2,    6,     4,    0,  &spn1653 },
        { 57344, 1666,   2,    4,     5,    0,  &spn1666 },
        { 57344, 1656,   2,    6,     5,    0,  &spn1656 },
        { 57344, 1683,   2,    0,     6,    0,  &spn1683 },
        { 57344, 1685,   2,    4,     6,    0,  &spn1685 },
        { 57344, 1686,   2,    6,     6,    0,  &spn1686 },
        { 57344, 2596,   8,    0,     7,    0,  &spn2596 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn60928spns[1] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 60928, 2848,   0,    0,     0,     0, &spn2848 }
    };
    
    static
    const
    J1939_PGNSPN        pgn61184spns[1] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 61184, 2550,   0,    0,     0,     0, &spn2550 }
    };
    
    static
    const
    J1939_PGNSPN        pgn61443spns[6] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 61443,  558,   0,    0,     0,     0, &spn558 },
        { 61443,  559,   0,    0,     0,     0, &spn559 },
        { 61443, 1437,   0,    0,     0,     0, &spn1437 },
        { 61443,   91,   1,    0,     0,     0, &spn91 },
        { 61443,   92,   2,    0,     0,     0, &spn92 },
        { 61443,  974,   3,    0,     0,     0, &spn974 }
    };
    
    static
    const
    J1939_PGNSPN        pgn61444spns[7] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 61444,  899,   0,    0,     0,    0,  &spn899 },
        { 61444,  512,   1,    0,     0,    0,  &spn512 },
        { 61444,  513,   2,    0,     0,    0,  &spn513 },
        { 61444,  190,   3,    0,     0,    0,  &spn190 },
        { 61444, 1483,   5,    0,     0,    0,  &spn1483 },
        { 61444, 1675,   6,    0,     0,    0,  &spn1675 },
        { 61444, 2432,   7,    0,     0,    0,  &spn2432 }
    };
    
    static
    const
    J1939_PGNSPN        pgn65129spns[2] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65129, 1636,   0,    0,     0,    0,  &spn1636 },
        { 65129, 1637,   2,    0,     0,    0,  &spn1637 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65217spns[2] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65217,  917,  32,    0,     0,    0,  &spn917 },
        { 65217,  918,  32,    0,     4,    0,  &spn918 }
    };
    
    static
    const
    J1939_PGNSPN        pgn65242spns[2] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65242,  965,   8,    0,     0,    0,  &spn965 },
        { 65242,  234,   0,    0,     0,    0,  &spn234 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65252spns[18] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65252,  593,   2,    0,     0,    0,  &spn593 },
        { 65252,  594,   2,    2,     0,    0,  &spn594 },
        { 65252,  592,   2,    4,     0,    0,  &spn592 },
        { 65252,  590,   2,    6,     0,    0,  &spn590 },
        { 65252,  591,   2,    6,     1,    0,  &spn591 },
        { 65252,  985,   2,    0,     2,    0,  &spn985 },
        { 65252,  875,   2,    2,     2,    0,  &spn875 },
        { 65252,  605,   2,    4,     2,    0,  &spn605 },
        { 65252, 1081,   2,    0,     3,    0,  &spn1081 },
        { 65252, 1110,   2,    0,     4,    0,  &spn1110 },
        { 65252, 1109,   2,    2,     4,    0,  &spn1109 },
        { 65252, 1108,   2,    4,     4,    0,  &spn1108 },
        { 65252, 1107,   2,    6,     4,    0,  &spn1107 },
        { 65252, 1111,   2,    6,     5,    0,  &spn1111 },
        { 65252, 2815,   2,    0,     6,    0,  &spn2815 },
        { 65252, 2814,   2,    2,     6,    0,  &spn2814 },
        { 65252, 2813,   2,    4,     6,    0,  &spn2813 },
        { 65252, 2812,   2,    6,     6,    0,  &spn2812 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65261spns[3] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65261,  110,   8,    0,     0,    0,  &spn74 },
        { 65261,  174,   8,    0,     1,    0,  &spn87 },
        { 65261,  175,   8,    0,     2,    0,  &spn88 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65262spns[6] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65262,  110,   0,    0,     0,    0,  &spn110 },
        { 65262,  174,   1,    0,     0,    0,  &spn174 },
        { 65262,  175,   2,    0,     0,    0,  &spn175 },
        { 65262,  176,   3,    0,     0,    0,  &spn176 },
        { 65262,   52,   6,    0,     0,    0,  &spn52 },
        { 65262, 1134,   7,    0,     0,    0,  &spn1134 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65265spns[19] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65265,   69,   2,    0,     0,    0,  &spn69 },
        { 65265,   70,   2,    2,     0,    0,  &spn70 },
        { 65265, 1633,   2,    4,     0,    0,  &spn1633 },
        { 65265,   84,  16,    0,     2,    0,  &spn84 },
        { 65265,  595,   2,    0,     3,    0,  &spn595 },
        { 65265,  596,   2,    2,     3,    0,  &spn596 },
        { 65265,  597,   2,    4,     3,    0,  &spn597 },
        { 65265,  598,   2,    6,     3,    0,  &spn598 },
        { 65265,  599,   2,    0,     4,    0,  &spn599 },
        { 65265,  600,   2,    2,     4,    0,  &spn600 },
        { 65265,  601,   2,    4,     4,    0,  &spn601 },
        { 65265,  602,   2,    6,     4,    0,  &spn602 },
        { 65265,   86,   8,    6,     5,    0,  &spn86 },
        { 65265,  976,   5,    0,     6,    0,  &spn976 },
        { 65265,  527,   3,    5,     6,    0,  &spn527 },
        { 65265,  968,   2,    0,     7,    0,  &spn968 },
        { 65265,  967,   2,    2,     7,    0,  &spn967 },
        { 65265,  966,   2,    4,     7,    0,  &spn966 },
        { 65265, 1237,   2,    6,     7,    0,  &spn1237 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65269spns[5] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65269,  108,   0,    0,     0,    0,  &spn108 },
        { 65269,  170,   1,    0,     0,    0,  &spn170 },
        { 65269,  171,   2,    0,     0,    0,  &spn171 },
        { 65269,  172,   3,    0,     0,    0,  &spn172 },
        { 65269,   79,   6,    0,     0,    0,  &spn79 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65271spns[5] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65271,  114,   8,    0,     0,    0,  &spn114 },
        { 65271,  115,   8,    0,     1,    0,  &spn115 },
        { 65271,  167,  16,    0,     3,    0,  &spn167 },
        { 65271,  168,  16,    0,     5,    0,  &spn168 },
        { 65271,  158,  16,    0,     7,    0,  &spn158 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65272spns[8] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65272,  123,   8,    0,     0,    0,  &spn123 },
        { 65272,  124,   8,    0,     1,    0,  &spn124 },
        { 65272,  126,   8,    0,     2,    0,  &spn126 },
        { 65272,  127,   8,    0,     3,    0,  &spn127 },
        { 65272,  177,  16,    0,     5,    0,  &spn177 },
        { 65272, 3027,   8,    0,     6,    0,  &spn3027 },
        { 65272, 3028,   4,    0,     7,    0,  &spn3028 },
        { 65272, 3026,   4,    4,     7,    0,  &spn3026 }
    };
    
    
    static
    const
    J1939_PGNSPN        pgn65277spns[2] = {
        //                    Bit    Byte
        // PGN    SPN  cBits Offset Offset rsvd spnDef
        { 65277,   72,   8,    0,     0,    0,  &spn72 },
        { 65277,  159,  16,    0,     1,    0,  &spn159 }
    };
    
    
    
    
    

    
    
    
    const
    J1939_PGN_ENTRY     pgn0_entry = {
        // PGN 0  0x000100 - Transmission Control 1 - TSC1
        0x00000000,
        50,                 // msFreq (only when active)
        8,                  // dlc
        3,                  // priority
        7,                  // cSPNs
        0,                  // --reserved--
        pgn0spns,           // SPN Table Pointer
        "Torque/Speed Control 1 - TSC1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn256_entry = {
        // PGN 256  0x000100 - Transmission Control 1 - TC1
        0x00000100,
        50,                 // msFreq (only when active)
        8,                  // dlc
        3,                  // priority
        17,                 // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Transmission Control 1 - TC1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn51456_entry = {
        // PGN 51456  0x00C900 - Request2
        0x0000C900,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        pgn51456spns,       // SPN Table Pointer
        "Request2"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn51712_entry = {
        // PGN 51712  0x00CA00 - Transfer
        0x0000CA00,
        0,                  // msFreq (only when active)
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Transfer"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn57344_entry = {
        // PGN 57344  0x00E000 - Cab Message 1 - CM1
        0x0000E000,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        15,                  // cSPNs
        0,                  // --reserved--
        pgn57344spns,       // SPN Table Pointer
        "Cab Message 1 - CM1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn58112_entry = {
        // PGN 58112  0x00E300 - Command Non-Continuously Monitored Systems Test - DM7
        0x0000E300,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Command Non-Continuously Monitored Systems Test - DM7"
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
        NULL,               // SPN Table Pointer
        "ACK/NAK"
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
        NULL,               // SPN Table Pointer
        "Request for PGN"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn60160_entry = {
        // PGN 60160  0x00EB00 - Transport Protocol - Data Transfer - TP.DT
        0x0000EB00,
        0,                  // msFreq
        8,                  // dlc
        7,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Transport Protocol - Data Transfer - TP.DT"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn60416_entry = {
        // PGN 60416  0x00EC00 - Transport Protocol - Connection Management
        0x0000EC00,
        0,                  // msFreq
        8,                  // dlc
        7,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Transport Protocol - Connection Management"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn60712_entry = {
        // PGN 60712  0x00ED00 - Network Message
        0x0000ED00,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Network Message"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn60928_entry = {
        // PGN 60928  0x00EE00 - Claim Address/Cannot Claim Address
        0x0000EE00,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        1,                  // cSPNs
        0,                  // --reserved--
        pgn60928spns,       // SPN Table Pointer
        "Claim Address/Cannot Claim Address"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61184_entry = {
        // PGN 61184  0x00EF00 - Proprietary A
        0x0000EF00,
        0,                  // msFreq
        0,                  // dlc  - variable up to 1785
        6,                  // priority
        0,                  // cSPNs                (No SAE defined SPNs)
        0,                  // --reserved--
        NULL,               // SPN Table Pointer    (No SAE defined SPNs)
        "Proprietary A"
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
        NULL,               // SPN Table Pointer
        "Electronic Retarder Controller 1 - ERC1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61441_entry = {
        // PGN 61441  0x00F001 - Electronic Brake Controller 1 - EBC1
        0x0000F001,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        22,                 // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Electronic Brake Controller 1 - EBC1"
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
        NULL,               // SPN Table Pointer
        "Electronic Transmission Controller 1 - ETC1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61443_entry = {
        // PGN 61443  0x00F003 - Electronic Engine Controller 2 - EEC2
        0x0000F003,
        50,                 // msFreq
        8,                  // dlc
        3,                  // priority
        6,                  // cSPNs
        0,                  // --reserved--
        pgn61443spns,       // SPN Table Pointer
        "Electronic Engine Controller 2 - EEC2"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61444_entry = {
        // PGN 61444  0x00F004 - Electronic Engine Controller 1 - EEC1
        0x0000F004,
        100,                // msFreq (engine speed dependent)
        8,                  // dlc
        3,                  // priority
        7,                  // cSPNs
        0,                  // --reserved--
        pgn61444spns,       // SPN Table Pointer
        "Electronic Engine Controller 1 - EEC1"
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
        NULL,               // SPN Table Pointer
        "Electronic Transmission Controller 1 - ETC2"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61450_entry = {
        // PGN 61450  0x00F00A - Engine Gas Flow Rate - EGF1
        0x0000F00A,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Engine Gas Flow Rate - EGF1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61452_entry = {
        // PGN 61452  0x00F00C - Electronic Transmission Controller #8 - ETC8
        0x0000F00C,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Electronic Transmission Controller #8 - ETC8"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61454_entry = {
        // PGN 61454  0x00F00E - Aftertreatment 1 Intake Gas 1 - AT1I1
        0x0000F00E,
        50,                 // msFreq
        8,                  // dlc
        6,                  // priority
        10,                 // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Aftertreatment 1 Intake Gas 1 - AT1O1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn61455_entry = {
        // PGN 61455  0x00F00F - Aftertreatment 1 Outlet Gas 1 - AT1O1
        0x0000F00F,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        5,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Aftertreatment 1 Outlet Gas 1 - AT1O1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn64892_entry = {
        // PGN 64892  0x00FD7C - Diesel Particulate Filter Control 1 - DPFC1
        0x0000FD7C,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Diesel Particulate Filter Control 1 - DPFC1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn64947_entry = {
        // PGN 64947  0x00FDB3 - Aftertreatment 1 Outlet Gas 2 - AT1I2
        0x0000FDB3,
        500,                // msFreq
        8,                  // dlc
        6,                  // priority
        4,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Aftertreatment 1 Intake Gas 2 - AT1I2"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn64948_entry = {
        // PGN 64948  0x00FDB4 - Aftertreatment 1 Intake Gas 2 - AT1I2
        0x0000FDB4,
        500,                // msFreq
        8,                  // dlc
        6,                  // priority
        4,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Aftertreatment 1 Intake Gas 2 - AT1I2"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn64964_entry = {
        // PGN 64964  0x00FDC4 - Electronic Brake Controller 5 - EBC5
        0x0000FDC4,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        6,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Electronic Brake Controller 5 - EBC5"
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
        NULL,               // SPN Table Pointer
        "Electronic Transmission Controller 7 - ETC7"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65110_entry = {
        // PGN 65110  0x00FE56 - Tank Information 1 - TI1
        0x0000FE56,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        4,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Tank Information 1 - TI1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65129_entry = {
        // PGN 65129  0x00FE69 - Engine Temperature 3 - ET3
        0x0000FE69,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        pgn65129spns,       // SPN Table Pointer
        "Engine Temperature 3 - ET3"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65177_entry = {
        // PGN 65177  0x00FE99 - Turbocharger Information 3 - TCI3
        0x0000FE99,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        4,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Turbocharger Information 3 - TCI3"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65178_entry = {
        // PGN 65178  0x00FE9A - Turbocharger Information 2 - TCI2
        0x0000FE9A,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        4,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Turbocharger Information 2 - TCI2"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65198_entry = {
        // PGN 65198  0x00FEAE - Air Supply Pressure - AIR1
        0x0000FEAE,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        7,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Air Supply Pressure - AIR1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65202_entry = {
        // PGN 65202  0x00FEB3 - Fuel Information 1 (Gaseous) - GFI1
        0x0000FEB3,
        0,                  // msFreq (on demand)
        8,                  // dlc
        6,                  // priority
        3,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Fuel Information 1 (Gaseous) - GFI1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65213_entry = {
        // PGN 65213  0x00FEBD - Fan Drive - FD
        0x0000FEBD,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        3,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Fan Drive - FD"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65215_entry = {
        // PGN 65215  0x00FEBF - WheelSpeedInformation - EBC2
        0x0000FEBF,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        7,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Wheel Speed Information - EBC2"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65217_entry = {
        // PGN 65217  0x00FEC1 - High Resolution Vehicle Distance - VDHR
        0x0000FEC1,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        pgn65217spns,       // SPN Table Pointer
        "High Resolution Vehicle Distance - VDHR"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65226_entry = {
        // PGN 65226  0x00FECA - Active Diagnostic Trouble Codes - DM1
        0x0000FECA,
        0,                  // msFreq   (on demand)
        8,                  // dlc
        6,                  // priority
        12,                 // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Active Diagnostic Trouble Codes - DM1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65227_entry = {
        // PGN 65227  0x00FECB - Previously Active Diagnostic Trouble Codes - DM2
        0x0000FECB,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Previously Active Diagnostic Trouble Codes - DM2"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65228_entry = {
        // PGN 65228  0x00FECC - Diagnostic Data Clear/Reset of Previously Active DTCs - DM3
        0x0000FECC,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Diagnostic Data Clear/Reset of Previously Active DTCs - DM3"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65229_entry = {
        // PGN 65229  0x00FECD - Freeze Frame Parameters - DM4
        0x0000FECD,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Freeze Frame Parameters - DM4"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65230_entry = {
        // PGN 65230  0x00FECE - Diagnostic Readiness - DM5
        0x0000FECE,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Diagnostic Readiness - DM5"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65231_entry = {
        // PGN 65231  0x00FECF - Continuously Monitored Systems Test Results - DM6
        0x0000FECF,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Continuously Monitored Systems Test Results - DM6"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65232_entry = {
        // PGN 65232  0x00FED0 - Test Results For Non-Continuously Monitored Systems - DM8
        0x0000FED0,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Test Results For Non-Continuously Monitored Systems - DM8"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65234_entry = {
        // PGN 65234  0x00FED2 - Non-Continuously Monitored Systems Test Identifiers Support - DM10
        0x0000FED2,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Non-Continuously Monitored Systems Test Identifiers Support - DM10"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65235_entry = {
        // PGN 65235  0x00FED3 - Diagnostic Data Clear/Reset For Active DTCs - DM11
        0x0000FED3,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Diagnostic Data Clear/Reset For Active DTCs - DM11"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65236_entry = {
        // PGN 65236  0x00FED4 - Emissions-Related Active Diagnostic Trouble Codes - DM12
        0x0000FED4,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Emissions-Related Active Diagnostic Trouble Codes - DM12"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65242_entry = {
        // PGN 65242  0x00FEDA - Software Identification - SOFT
        0x0000FEDA,
        0,                  // msFreq - on demand
        0,                  // dlc - variable up to 201
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        pgn65242spns,       // SPN Table Pointer
        "Software Identification - SOFT"
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
        NULL,               // SPN Table Pointer
        "Electronic Engine Controller 3 - EEC3"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65248_entry = {
        // PGN 65247  0x00FEE0 - VehicleDistance - VD
        0x0000FEE0,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "VehicleDistance - VD"
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
        NULL,               // SPN Table Pointer
        "Retarder Configuration - RC"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65251_entry = {
        // PGN 65251  0x00FEE3 - Engine Configuration 1 - EC1 -
        0x00FEE3,
        5000,               // msFreq
        39,                 // dlc
        6,                  // priority
        14,                 // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Engine Configuration 1 - EC1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65252_entry = {
        // PGN 65252  0x00FEE4 - Shutdown - SHUTDOW
        0x00FEE4,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        18,                 // cSPNs
        0,                  // --reserved--
        pgn65252spns,       // SPN Table Pointer
        "Shutdown - SHUTDOW"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65253_entry = {
        // PGN 65253  0x00FEE5 - Engine Hours,Revolutions - HOURS
        0x00FEE5,
        0,                  // msFreq (on demand)
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Engine Hours,Revolutions - HOURS"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65254_entry = {
        // PGN 65254  0x00FEE6 - Time/Date - TD
        0x00FEE6,
        0,                  // msFreq (on demand)
        8,                  // dlc
        6,                  // priority
        8,                  // cSPNs
        0,                  // --reserved--
        NULL, //pgn65254spns,       // SPN Table Pointer
        "Time/Date - TD"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65255_entry = {
        // PGN 65255  0x00FEE7 - Vehicle Hours - VH
        0x00FEE7,
        0,                  // msFreq (on demand)
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        NULL, //pgn65254spns,       // SPN Table Pointer
        "Vehicle Hours - VH"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65257_entry = {
        // PGN 65257  0x00FEE9 - Fuel Consumption (Liquid) - LFC
        0x00FEE9,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Fuel Consumption (Liquid) - LFC"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65261_entry = {
        // PGN 65261  0x00FEED - Cruise Control/Vehicle Speed Setup - CCSS
        0x0000FEED,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        3,                  // cSPNs
        0,                  // --reserved--
        pgn65265spns,       // SPN Table Pointer
        "Cruise Control/Vehicle Speed Setup - CCSS"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65262_entry = {
        // PGN 65262  0x00FEEE - Engine Temperature 1 - ET1
        0x0000FEEE,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        6,                  // cSPNs
        0,                  // --reserved--
        pgn65262spns,       // SPN Table Pointer
        "Engine Temperature 1 - ET1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65263_entry = {
        // PGN 65264  0x00FEEF - Engine Fluid Level / Pressure 1 - EFL/P1
        0x0000FEEF,
        500,                // msFreq
        8,                  // dlc
        6,                  // priority
        7,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Engine Fluid Level / Pressure 1 - EFL/P1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65264_entry = {
        // PGN 65264  0x00FEF0 - Power Takeoff Information - PTO
        0x0000FEF0,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        13,                 // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Power Takeoff Information - PTO"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65265_entry = {
        // PGN 65265  0x00FEF1 - Cruise Control/Vehicle Speed - CCVS
        0x0000FEF1,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        19,                 // cSPNs
        0,                  // --reserved--
        pgn65265spns,       // SPN Table Pointer
        "Cruise Control/Vehicle Speed - CCVS"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65266_entry = {
        // PGN 65266  0x00FEF2 - Fuel Economy (Liquid) - LFE
        0x0000FEF2,
        100,                // msFreq
        8,                  // dlc
        6,                  // priority
        4,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Fuel Economy (Liquid) - LFE"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65269_entry = {
        // PGN 65269  0x00FEF5 - Ambient Conditions - AMB
        0x0000FEF5,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        5,                  // cSPNs
        0,                  // --reserved--
        pgn65269spns,       // SPN Table Pointer
        "Ambient Conditions - AMB"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65270_entry = {
        // PGN 65270  0x00FEF6 - Inlet / Exhaust Conditions 1 - IC1
        0x0000FEF6,
        500,                // msFreq
        8,                  // dlc
        6,                  // priority
        7,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Inlet / Exhaust Conditions 1 - IC1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65271_entry = {
        // PGN 65271  0x00FEF7 - Vehicle Electrical Power #1 - VEP1
        0x0000FEF7,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        5,                  // cSPNs
        0,                  // --reserved--
        pgn65271spns,       // SPN Table Pointer
        "Vehicle Electrical Power #1 - VEP1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65272_entry = {
        // PGN 65272  0x00FEF8 - Transmission Fluids 1 - TRF1
        0x0000FEF8,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        8,                  // cSPNs
        0,                  // --reserved--
        pgn65272spns,       // SPN Table Pointer
        "Transmission Fluids 1 - TRF1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65275_entry = {
        // PGN 65275  0x00FEFB - Transmission Fluids 1 - TRF1
        0x0000FEFB,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Retarder Fluids - RF"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65276_entry = {
        // PGN 65276  0x00FEFC - Dash Display - DD
        0x0000FEFC,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        5,                  // cSPNs
        0,                  // --reserved--
        pgn65272spns,       // SPN Table Pointer
        "Dash Display - DD"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65277_entry = {
        // PGN 65277  0x00FEFD - Alternate Fuel 1 - A1
        0x0000FEFD,
        500,                // msFreq
        8,                  // dlc
        6,                  // priority
        2,                  // cSPNs
        0,                  // --reserved--
        pgn65277spns,       // SPN Table Pointer
        "Alternate Fuel 1 - A1"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65279_entry = {
        // PGN 65279  0x00FEFF - Water in Fuel Indicator - WFI
        0x0000FEFF,
        10000,              // msFreq
        8,                  // dlc
        6,                  // priority
        1,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Water in Fuel Indicator - WFI"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65280_entry = {
        // PGN 65280  0x00FF00 - Proprietary B
        0x0000FF00,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65281_entry = {
        // PGN 65280  0x00FF01 - Proprietary B
        0x0000FF01,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65282_entry = {
        // PGN 65282  0x00FF02 - Proprietary B
        0x0000FF02,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65283_entry = {
        // PGN 65283  0x00FF03 - Proprietary B
        0x0000FF03,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65284_entry = {
        // PGN 65284  0x00FF04 - Proprietary B
        0x0000FF04,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65285_entry = {
        // PGN 65285  0x00FF05 - Proprietary B
        0x0000FF05,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65286_entry = {
        // PGN 65286  0x00FF06 - Proprietary B
        0x0000FF06,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65287_entry = {
        // PGN 65287  0x00FF07 - Proprietary B
        0x0000FF07,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65288_entry = {
        // PGN 65288  0x00FF08 - Proprietary B
        0x0000FF08,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65289_entry = {
        // PGN 65289  0x00FF09 - Proprietary B
        0x0000FF09,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65290_entry = {
        // PGN 65290  0x00FF0A - Proprietary B
        0x0000FF0A,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65291_entry = {
        // PGN 65291  0x00FF0B - Proprietary B
        0x0000FF0B,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65292_entry = {
        // PGN 65292  0x00FF0C - Proprietary B
        0x0000FF0C,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65293_entry = {
        // PGN 65293  0x00FF0D - Proprietary B
        0x0000FF0D,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65294_entry = {
        // PGN 65294  0x00FF0E - Proprietary B
        0x0000FF0E,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65295_entry = {
        // PGN 65295  0x00FF0F - Proprietary B
        0x0000FF0F,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65296_entry = {
        // PGN 65296  0x00FF10 - Proprietary B
        0x0000FF10,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65297_entry = {
        // PGN 65297  0x00FF11 - Proprietary B
        0x0000FF11,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    const
    J1939_PGN_ENTRY     pgn65298_entry = {
        // PGN 65298  0x00FF12 - Proprietary B
        0x0000FF12,
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Proprietary B"
    };
    
    
    
    
    const
    J1939_PGN_ENTRY     *pgn_index[] = {
        &pgn0_entry,
        &pgn256_entry,
        &pgn51456_entry,
        &pgn51712_entry,
        &pgn57344_entry,
        &pgn58112_entry,
        &pgn59392_entry,
        &pgn59904_entry,
        &pgn60160_entry,
        &pgn60416_entry,
        &pgn60712_entry,
        &pgn60928_entry,
        &pgn61184_entry,
        &pgn61440_entry,
        &pgn61441_entry,
        &pgn61442_entry,
        &pgn61443_entry,
        &pgn61444_entry,
        &pgn61445_entry,
        &pgn61450_entry,
        &pgn61452_entry,
        &pgn61454_entry,
        &pgn61455_entry,
        &pgn64892_entry,
        &pgn64947_entry,
        &pgn64948_entry,
        &pgn64964_entry,
        &pgn65098_entry,
        &pgn65110_entry,
        &pgn65129_entry,
        &pgn65177_entry,
        &pgn65178_entry,
        &pgn65198_entry,
        &pgn65202_entry,
        &pgn65213_entry,
        &pgn65215_entry,
        &pgn65217_entry,
        &pgn65226_entry,
        &pgn65227_entry,
        &pgn65228_entry,
        &pgn65229_entry,
        &pgn65230_entry,
        &pgn65231_entry,
        &pgn65232_entry,
        &pgn65234_entry,
        &pgn65235_entry,
        &pgn65236_entry,
        &pgn65247_entry,
        &pgn65248_entry,
        &pgn65249_entry,
        &pgn65251_entry,
        &pgn65252_entry,
        &pgn65253_entry,
        &pgn65254_entry,
        &pgn65255_entry,
        &pgn65257_entry,
        &pgn65261_entry,
        &pgn65262_entry,
        &pgn65263_entry,
        &pgn65264_entry,
        &pgn65265_entry,
        &pgn65266_entry,
        &pgn65269_entry,
        &pgn65270_entry,
        &pgn65271_entry,
        &pgn65272_entry,
        &pgn65275_entry,
        &pgn65276_entry,
        &pgn65277_entry,
        &pgn65279_entry,
        &pgn65280_entry,
        &pgn65281_entry,
        &pgn65282_entry,
        &pgn65283_entry,
        &pgn65284_entry,
        &pgn65285_entry,
        &pgn65286_entry,
        &pgn65287_entry,
        &pgn65288_entry,
        &pgn65289_entry,
        &pgn65290_entry,
        &pgn65291_entry,
        &pgn65292_entry,
        &pgn65293_entry,
        &pgn65294_entry,
        &pgn65295_entry,
        &pgn65296_entry,
        &pgn65297_entry,
        &pgn65298_entry,
        NULL
    };
    
    const
    J1939_PGN_TABLE     pgn_table = {
        (sizeof(pgn_index)/sizeof(J1939_PGN_ENTRY *)),
        0,
        pgn_index
    };
    
    
    
    
    
    
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            j1939data_task_body(
        void            *pData
    )
    {
        //J1939DATA_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939DATA_DATA *     j1939data_Alloc(
    )
    {
        J1939DATA_DATA       *this;
        uint32_t        cbSize = sizeof(J1939DATA_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939DATA_DATA *     j1939data_New(
    )
    {
        J1939DATA_DATA       *this;
        
        this = j1939data_Alloc( );
        if (this) {
            this = j1939data_Init(this);
        } 
        return this;
    }



    const
    J1939_PREFERRED_ADDRESS * j1939data_Find_Adr(
        uint8_t         adr
    )
    {
        const
        J1939_PREFERRED_ADDRESS
                        *pEntry;
        int             i;
        
        for( i=0; i<cGroup0_addresses; ++i) {
            pEntry = &group0_addresses[i];
            if (adr == pEntry->address) {
                return pEntry;
            }
        }
        
        return NULL;
    }
    
    
    
    const
    J1939_PGN_ENTRY * j1939data_Find_Pgn(
        J1939_PGN       pgn
    )
    {
        const
        J1939_PGN_TABLE *pTable = &pgn_table;
        const
        J1939_PGN_ENTRY **ppPgnEntry = NULL;
        const
        J1939_PGN_ENTRY *pPgnEntry = NULL;
        int             i;
        
        ppPgnEntry = pTable->pPGNs;
        for( i=0; i<pTable->cPGNs; ++i) {
            pPgnEntry = ppPgnEntry[i];
            if (NULL == pPgnEntry) {
                break;
            }
            if (pgn.w == pPgnEntry->pgn) {
                return pPgnEntry;
            }
        }
        
        return NULL;
    }
    
    
    
    const
    J1939_PGNSPN *  j1939data_FindPgnSpn(
        J1939_PGN       pgn,
        uint32_t        spn
    )
    {
        const
        J1939_PGN_ENTRY *pPgnEntry = NULL;
        const
        J1939_PGNSPN    *pSpns;
        int             i;
        
        pPgnEntry = j1939data_Find_Pgn(pgn);
        if (pPgnEntry) {
            pSpns = pPgnEntry->pSpns;
            for( i=0; i<pPgnEntry->cSpns; ++i) {
                if (spn == pSpns[i].spn) {
                    return &pSpns[i];
                }
            }
        }
        
        return NULL;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         j1939data_getLastError(
        J1939DATA_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939data_setLastError(
        J1939DATA_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        j1939data_getPriority(
        J1939DATA_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939data_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            j1939data_setPriority(
        J1939DATA_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939data_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        j1939data_getSize(
        J1939DATA_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939data_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    ASTR_DATA * j1939data_getStr(
        J1939DATA_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        j1939data_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        j1939data_setStr(
        J1939DATA_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        j1939data_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = j1939data__Assign(this,pOther);
     @endcode
     @param     this    J1939DATA object pointer
     @param     pOther  a pointer to another J1939DATA object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         j1939data_Assign(
        J1939DATA_DATA		*this,
        J1939DATA_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !j1939data_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        j1939data_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939data_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939data_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        j1939data      *pCopy = j1939data_Copy(this);
     @endcode
     @param     this    J1939DATA object pointer
     @return    If successful, a J1939DATA object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the J1939DATA object.
     */
    J1939DATA_DATA *     j1939data_Copy(
        J1939DATA_DATA       *this
    )
    {
        J1939DATA_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = j1939data_New( );
        if (pOther) {
            eRc = j1939data_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939data_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939data_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939DATA_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939DATA_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        j1939data_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939data_Disable(
        J1939DATA_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939data_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return j1939data_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939data_setLastError(this, ERESULT_SUCCESS);
        return j1939data_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939data_Enable(
        J1939DATA_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939data_setLastError(this, ERESULT_SUCCESS);
        return j1939data_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939DATA_DATA *   j1939data_Init(
        J1939DATA_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(J1939DATA_DATA);
        
        if (OBJ_NIL == this) {
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939DATA);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939DATA);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939data_Vtbl);
        
        j1939data_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "offsetof(eRc) = %lu\n", offsetof(J1939DATA_DATA,eRc));
        fprintf(stderr, "sizeof(J1939DATA_DATA) = %lu\n", sizeof(J1939DATA_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(J1939DATA_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939data_IsEnabled(
        J1939DATA_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939data_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939data_getLastError(this);
        }
        
        // Return to caller.
        j1939data_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939data_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          j1939data_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        J1939DATA_DATA  *this = objId;
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return j1939data_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return j1939data_Enable;
                        }
                        break;

                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939data_ToDebugString(this,4);
     @endcode
     @param     this    J1939DATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939data_ToDebugString(
        J1939DATA_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939data_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(j1939data) size=%d\n",
                     this,
                     j1939data_getSize(this)
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(j1939data)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939data_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939data_Validate(
        J1939DATA_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939DATA) )
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(J1939DATA_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


