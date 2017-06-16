// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939tbl.c
 *	Generated 05/20/2015 11:48:08
 *
 * Created on December 30, 2014
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
#include "j1939tbl_internal.h"



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
        

    typedef struct preferred_address_s {
        uint8_t         address;
        const
        char            *pDescription;
        const
        char            *pExplanation;      // Optional
        
    } PREFERRED_ADDRESS;
    
    const
    PREFERRED_ADDRESS   group0_addresses[] = {
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
        {255, "GLOBAL (All-Any Node)",  NULL},
    };

    const
    uint16_t     cGroup0_addresses = (sizeof(group0_addresses)/sizeof(PREFERRED_ADDRESS));
    
    
    
    
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
            1               // Data Max
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
#endif
        
        
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
        NULL    /*&temp01*/,
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
        "Transmission Requested Range",
        NULL
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
        "Transmission Current Range",
        NULL
    };


    // SPN 166 - Engine Rated Power (kW)
    //                                      // actual_power = (ratedPower * 0.5) kW
    //                                      // range: 0 - 32127.5 kW
    static
    const
    J1939_SPN           spn166 = {
        166,
        0,
        NULL    /*&???*/,
        "Engine Rated Power (kW)",
        "Net brake power that the engine will deliver continuously, specified for a given application at a rated speed."
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
        NULL    /*&temp01*/,
        "Cab Interior Temperature"
    };
    
    
    // SPN 171 - Ambient Air Temperature
    static
    const
    J1939_SPN           spn171 = {
        171,
        0,
        NULL    /*&temp01*/,
        "Ambient Air Temperature"
    };
    
    
    // SPN 172 - Engine Air Inlet Temperature
    static
    const
    J1939_SPN           spn172 = {
        172,
        0,
        NULL    /*&temp01*/,
        "Engine Air Inlet Temperature"
    };
    
    
    // SPN 174 - Fuel Temperature - Temperature of fuel entering injectors.
    static
    const
    J1939_SPN           spn174 = {
        174,
        0,
        NULL    /*&temp01*/,
        "Fuel Temperature"
    };
    
    
    // SPN 175 - Engine Oil Temperature 1 - Temperature of the engine lubricant.
    static
    const
    J1939_SPN           spn175 = {
        175,
        0,
        NULL    /*&temp02*/,
        "Engine Oil Temperature 1"
    };
    
    
    // SPN 176 - Turbo Oil Temperature - Temperature of the turbocharger lubricant.
    static
    const
    J1939_SPN           spn176 = {
        176,
        0,
        NULL    /*&temp02*/,
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
        NULL    /*&velocityRotational01*/,
        "Engine Speed"
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
        0x0000FE99,
        1000,               // msFreq
        8,                  // dlc
        6,                  // priority
        4,                  // cSPNs
        0,                  // --reserved--
        NULL,               // SPN Table Pointer
        "Turbocharger Information 2 - TCI2"
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
        0,                  // msFreq
        8,                  // dlc
        6,                  // priority
        0,                  // cSPNs
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
        // PGN 65252  0x00FEE4 - Shutdown           - SHUTDOW
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
        pgn65265spns,       // SPN Table Pointer
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

    //---------------------------------------------------------------
    //                  F i n d  P G N  E n t r y
    //---------------------------------------------------------------
    
    const
    J1939_PGN_ENTRY * j1939tbl_Find_Pgn(
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
    J1939_PGNSPN *  j1939tbl_FindPgnSpn(
        J1939_PGN       pgn,
        uint32_t        spn
    )
    {
        const
        J1939_PGN_ENTRY *pPgnEntry = NULL;
        const
        J1939_PGNSPN    *pSpns;
        int             i;
        
        pPgnEntry = j1939tbl_Find_Pgn(pgn);
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
    
    

    /*!
     Create a byte bit mask.
     @param:    this    J1939TBL object pointer
     @param:    numBits number of bits in the mask (0 < numBits < 9)
     @param:    pos     number of bits to shift left
     @return:   If successful, the byte mask otherwise 0
     */
    uint8_t         j1939tbl_CreateBitMask(
        uint16_t        numBits,
        uint16_t        pos
    )
    {
        uint8_t         mask = 0;
        
        if ((0 < numBits) && (numBits < 9)) {
            mask = numBitsTable[numBits - 1];
            if ((pos < 8) && ((numBits + pos) < 9)) {
                mask <<= pos;
            }
            else {
                mask = 0;
            }
        }
        return mask;
    }

    
    
    static
    bool            print1of4(
        J1939TBL_DATA   *this,
        int             num,
        const
        char            *pDesc,
        const
        char            *pDesc0,
        const
        char            *pDesc1,
        const
        char            *pDesc2,
        const
        char            *pDesc3
    )
    {
        
        if (this->pFileOut) {
            switch (num) {
                case 0:
                    fprintf(this->pFileOut, "\t%s - %s\n", pDesc, pDesc0);
                    break;
                    
                case 1:
                    fprintf(this->pFileOut, "\t%s - %s\n", pDesc, pDesc1);
                    break;
                    
                case 2:
                    fprintf(this->pFileOut, "\t%s - %s\n", pDesc, pDesc2);
                    break;
                    
                case 3:
                    if (pDesc3) {
                        fprintf(this->pFileOut, "\t%s - %s\n", pDesc, pDesc3);
                    }
                    break;
                    
            }
        }
        
        return true;
    }
    
    
    
    static
    bool            printMsg(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg
                                )
    {
        char            data[64];
        
        if (this->pFileOut) {
            data[0] = 0;
            j1939msg_CreatePrintable(pMsg, data);
            fprintf(
                    this->pFileOut,
                    "\ntime: %5d  pgn: %08X  msg: %s",
                    pMsg->CMSGSID.CMSGTS,
                    j1939msg_getPGN(pMsg).w,
                    data
                    );
        }
        
        return true;
    }
    
    
    
    static
    bool            printMsgAdr(
        J1939TBL_DATA   *this,
        uint8_t         da
    )
    {
        
        if (this->pFileOut) {
            switch (da) {

                case 0:
                    fprintf(this->pFileOut, "Engine #1");
                    break;
                    
                case 1:
                    fprintf(this->pFileOut, "Engine #2");
                    break;
                    
                case 2:
                    fprintf(this->pFileOut, "Turbocharger");
                    break;
                    
                case 3:
                    fprintf(this->pFileOut, "Transmission #1");
                    break;
                    
                case 4:
                    fprintf(this->pFileOut, "Transmission #2");
                    break;
                    
                case 5:
                    fprintf(this->pFileOut, "Shift Console – Primary");
                    break;
                    
                case 6:
                    fprintf(this->pFileOut, "Shift Console – Secondary");
                    break;
                    
                case 7:
                    fprintf(this->pFileOut, "Axle - Steering");
                    break;
                    
                case 8:
                    fprintf(this->pFileOut, "Axle - Drive");
                    break;
                    
                case 9:
                    fprintf(this->pFileOut, "Brakes - System Controller");
                    break;
                    
                case 10:
                    fprintf(this->pFileOut, "Brakes - Steer Axle");
                    break;
                    
                case 11:
                    fprintf(this->pFileOut, "Brakes - Drive axle");
                    break;
                    
                case 12:
                    fprintf(this->pFileOut, "Retarder - Engine");
                    break;
                    
                case 13:
                    fprintf(this->pFileOut, "Retarder - Driveline");
                    break;
                    
                case 14:
                    fprintf(this->pFileOut, "Cruise Control");
                    break;
                    
                case 15:
                    fprintf(this->pFileOut, "Fuel System");
                    break;
                    
                case 16:
                    fprintf(this->pFileOut, "Steering Controller");
                    break;
                    
                case 17:
                    fprintf(this->pFileOut, "Suspension - Steer Axle");
                    break;
                    
                case 18:
                    fprintf(this->pFileOut, "Suspension - Drive Axle");
                    break;
                    
                case 19:
                    fprintf(this->pFileOut, "Instrument Cluster");
                    break;
                    
                case 20:
                    fprintf(this->pFileOut, "Trip Recorder");
                    break;
                    
                case 21:
                    fprintf(this->pFileOut, "Cab Climate Control");
                    break;
                    
                case 22:
                    fprintf(this->pFileOut, "Aerodynamic Control");
                    break;
                    
                case 23:
                    fprintf(this->pFileOut, "Vehicle Navigation");
                    break;
                    
                case 24:
                    fprintf(this->pFileOut, "Vehicle Security");
                    break;
                    
                case 25:
                    fprintf(this->pFileOut, "Network Interconnect ECU");
                    break;
                    
                case 26:
                    fprintf(this->pFileOut, "Body Controller");
                    break;
                    
                case 27:
                    fprintf(this->pFileOut, "Power TakeOff (Front or Secondary)");
                    break;
                    
                case 28:
                    fprintf(this->pFileOut, "Off Vehicle Gateway");
                    break;
                    
                case 29:
                    fprintf(this->pFileOut, "Virtual Terminal (in cab)");
                    break;
                    
                case 30:
                    fprintf(this->pFileOut, "Management Computer #1");
                    break;
                    
                case 31:
                    fprintf(this->pFileOut, "Propulsion Battery Charger");
                    break;
                    
                case 32:
                    fprintf(this->pFileOut, "Headway Controller");
                    break;
                    
                case 33:
                    fprintf(this->pFileOut, "System Monitor");
                    break;
                    
                case 34:
                    fprintf(this->pFileOut, "Hydraulic Pump Controller");
                    break;
                    
                case 35:
                    fprintf(this->pFileOut, "Suspension - System Controller");
                    break;
                    
                case 36:
                    fprintf(this->pFileOut, "Pneumatic - System Controller");
                    break;
                    
                case 37:
                    fprintf(this->pFileOut, "Cab Controller");
                    break;
                    
                case 38:
                    fprintf(this->pFileOut, "Tire Pressure Control");
                    break;
                    
                case 39:
                    fprintf(this->pFileOut, "Ignition Control Module");
                    break;
                    
                case 40:
                    fprintf(this->pFileOut, "Seat Controls");
                    break;
                    
                case 41:
                    fprintf(this->pFileOut, "Retarder, Exhaust, Engine #1");
                    break;
                    
                case 42:
                    fprintf(this->pFileOut, "Water Pump Control");
                    break;
                    
                case 43:
                    fprintf(this->pFileOut, "Transmission Display");
                    break;
                    
                case 44:
                    fprintf(this->pFileOut, "Retarder, Exhaust, Engine #2");
                    break;
                    
                case 45:
                    fprintf(this->pFileOut, "Vehicle Dynamic Stability Control");
                    break;
                    
                case 46:
                    fprintf(this->pFileOut, "Oil Sensor Unit");
                    break;
                    
                case 47:
                    fprintf(this->pFileOut, "Information System Controller #1");
                    break;
                    
                case 48:
                    fprintf(this->pFileOut, "Ramp Control");
                    break;
                    
                case 49:
                    fprintf(this->pFileOut, "Cab Controller - Primary");
                    break;
                    
                case 50:
                    fprintf(this->pFileOut, "Cab Controller - Secondary");
                    break;
                    
                case 51:
                    fprintf(this->pFileOut, "Tire Pressure Controller");
                    break;
                    
                case 52:
                    fprintf(this->pFileOut, "Ignition Control Module #1");
                    break;
                    
                case 255:
                    fprintf(this->pFileOut, "General Broadcast");
                    break;
                    
                default:
                    fprintf(this->pFileOut, "***Unknown***");
                    break;
            }
        }
        
        return true;
    }
    
    
    
    static
    bool            printMsgDesc(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        char            data[64];
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939msg_getPGN(pMsg);
        if (this->pFileOut) {
            data[0] = 0;
            j1939msg_CreatePrintable(pMsg, data);
            fprintf(
                    this->pFileOut,
                    "\ntime: %5d  pgn: %08X  msg: %s",
                    pMsg->CMSGSID.CMSGTS,
                    j1939msg_getPGN(pMsg).w,
                    data
            );
            fprintf(
                    this->pFileOut,
                    "\t%d - %s\n",
                    pgn.pgn,
                    pEntry->pDesc
            );
            fprintf(this->pFileOut, "\t");
            printMsgAdr(this, j1939pdu_getSA(pdu));
            fprintf(this->pFileOut, " -> ");
            printMsgAdr(this, j1939pdu_getDA(pdu));
            fprintf(this->pFileOut, "\n");
        }
        
        return true;
    }
        
        
        


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939TBL_DATA * j1939tbl_Alloc(
    )
    {
        J1939TBL_DATA   *this;
        uint32_t        cbSize = sizeof(J1939TBL_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                  SPN to Signed Value
    //---------------------------------------------------------------
    
    int32_t         j1939tbl_SpnToS32(
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
    //                      P r o p e r t i e s
    //===============================================================

    bool            j1939tbl_setFileOut(
        J1939TBL_DATA   *this,
        FILE            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        this->pFileOut = pValue;
        
        return true;
    }
    
    
    
    uint16_t        j1939tbl_getPriority(
        J1939TBL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    
    bool            j1939tbl_setPriority(
        J1939TBL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }



    uint32_t        j1939tbl_getSize(
        J1939TBL_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return 0;
    }



    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939tbl_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939TBL_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
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
        
        bool            j1939tbl_DumpPgn0(
            J1939TBL_DATA    *this,
            J1939_MSG       *pMsg,
            const
            J1939_PGN_ENTRY *pEntry
        )
        {
            J1939_PDU       pdu;
            J1939_PGN       pgn;
            uint8_t         spn518;         // Requested Torque / Torque Limit
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
            
            // Do initialization.
#ifdef NDEBUG
#else
            if( !j1939tbl_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
#endif
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            
            spn695 = pMsg->DATA.bytes[0] & 0x3;
            spn696 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
            spn897 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
            spn898 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
            spn518 = pMsg->DATA.bytes[3];
            
            print1of4(this,
                      spn695,
                      "Override Control Mode",
                      "Disable override by the source of msg",
                      "Override speed",
                      "Override torque",
                      "Limit Speed/Torque"
                      );
            print1of4(this,
                      spn696,
                      "Engine Requested Speed Control Conditions",
                      "Transient Optimized for driveline disengaged and non-lockup conditions",
                      "Stability Optimized for driveline disengaged and non-lockup conditions",
                      "Stability Optimized for driveline engaged and/or in lockup condition 1 (e.g., vehicle driveline)",
                      "Stability Optimized for driveline engaged and/or in lockup condition 2 (e.g., PTO driveline)"
                      );
            print1of4(this,
                      spn897,
                      "Override Control Mode Priority",
                      "Highest priority",
                      "High priority",
                      "Medium priority",
                      "Low priority"
                      );
            if (spn898 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tRequested Speed / Speed Limit = %d\n", spn898);
            }
            if (spn518 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tRequested Torque / Torque Limit = %d\n", spn518);
            }
            
            // Return to caller.
            return false;
        }
        
        
        
    //---------------------------------------------------------------
    //          PGN 57344  0x00E000 - Cab Message 1 - CM1
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn57344(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn986;
        uint16_t        spn1691;
        uint8_t         spn1684;
        uint8_t         spn1682;
        uint8_t         spn1714;
        uint8_t         spn1856;
        uint8_t         spn1655;
        uint8_t         spn1654;
        uint8_t         spn1653;
        uint8_t         spn1666;
        uint8_t         spn1656;
        uint8_t         spn1683;
        uint8_t         spn1685;
        uint8_t         spn1686;
        uint8_t         spn2596;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 986  1       8bits       Requested Percent Fan Speed
        spn986 = pMsg->DATA.bytes[0];
        // SPN 1691 2-3     16bits      Cab Interior Temperature Command
        spn1691 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        // SPN 1684 4.1     2bits       Auxiliary Heater Coolant Pump Request
        spn1684 = pMsg->DATA.bytes[3] & 0x3;
        // SPN 1682 4.3     2bits       Battery Main Switch Hold Request
        spn1682 = (pMsg->DATA.bytes[3] >> 2) & 0x3;
        // SPN 1717 4.5     2bits       Operator Seat Direction Switch
        spn1714 = (pMsg->DATA.bytes[3] >> 4) & 0x3;
        // SPN 1856 4.7     2bits       Seat Belt Switch
        spn1856 = (pMsg->DATA.bytes[3] >> 6) & 0x3;
        // SPN 1655 5.3     2bits       Vehicle Limiting Speed Governor Decrement Switch
        spn1655 = (pMsg->DATA.bytes[4] >> 2) & 0x3;
        // SPN 1654 5.5     2bits       Vehicle Limiting Speed Governor Increment Switch
        spn1654 = (pMsg->DATA.bytes[4] >> 4) & 0x3;
        // SPN 1653 5.7     2bits       Vehicle Limiting Speed Governor Enable Switch
        spn1653 = (pMsg->DATA.bytes[4] >> 6) & 0x3;
        // SPN 1666 6.5     2bits       Automatic Gear Shifting Enable Switch
        spn1666 = (pMsg->DATA.bytes[5] >> 4) & 0x3;
        // SPN 1656 6.7     2bits       Engine Automatic Start Enable Switch
        spn1656 = (pMsg->DATA.bytes[5] >> 6) & 0x3;
        // SPN 1683 7.1     4bits       Auxiliary Heater Mode Request
        spn1683 = pMsg->DATA.bytes[6] & 0x0F;
        // SPN 1685 7.5     2bits       Request Engine Zone Heating
        spn1685 = (pMsg->DATA.bytes[6] >> 4) & 0x3;
        // SPN 1686 7.7     2bits       Request Cab Zone Heating
        spn1686 = (pMsg->DATA.bytes[6] >> 6) & 0x3;
        // SPN 2596 8       8bits       Selected Maximum Vehicle Speed Limit
        spn2596 = pMsg->DATA.bytes[7];
        
        if (spn986 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tRequested Percent Fan Speed = %d\n", spn986);
        }
        if (spn1691 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tCab Interior Temperature Command = %d\n", spn1691);
        }
        print1of4(this,
                  spn1684,
                  "Auxiliary Heater Coolant Pump Request",
                  "Deactivate water pump",
                  "Activate water pump",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1682,
                  "Battery Main Switch Hold Request",
                  "Release Battery Main Switch",
                  "Hold Battery Main Switch",
                  "undefined",
                  NULL
                  );
        print1of4(this,
                  spn1714,
                  "Operator Seat Direction Switch",
                  "Operator seat not facing forward",
                  "Operator seat is facing forward",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1856,
                  "Seat Belt Switch",
                  "NOT Buckled",
                  "OK - Seat Belt is buckled",
                  "Error - Switch state cannot be determined",
                  NULL
                  );
        print1of4(this,
                  spn1655,
                  "Vehicle Limiting Speed Governor Decrement Switch",
                  "Switch in the off state",
                  "Switch in the on state - decrease",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1654,
                  "Vehicle Limiting Speed Governor Increment Switch",
                  "Switch in the off state",
                  "Switch in the on state - increase",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1653,
                  "Vehicle Limiting Speed Governor Enable Switch",
                  "Switch disabled",
                  "Switched enabled",
                  "Error",
                  NULL
                  );
        fprintf(this->pFileOut, "\tAutomatic Gear Shifting Enable Switch = %d\n", spn1666);
        print1of4(this,
                  spn1656,
                  "Engine Automatic Start Enable Switch",
                  "Switch in the off state",
                  "Switch in the on state",
                  "Error",
                  NULL
                  );
        switch (spn1683) {
            case 0:
                fprintf(this->pFileOut, "\tAuxiliary Heater Mode Request - De-activate auxiliary heater\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tAuxiliary Heater Mode Request - Off due to ADR per European Regulations for Transport of hazardous materials\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tAuxiliary Heater Mode Request - Economy mode\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tAuxiliary Heater Mode Request - Normal mode\n");
                break;
            case 14:
                fprintf(this->pFileOut, "\tAuxiliary Heater Mode Request - Reserved\n");
                break;
        }
        print1of4(this,
                  spn1685,
                  "Request Engine Zone Heating",
                  "Do not heat engine zone",
                  "Heat engine zone",
                  "Reserved",
                  NULL
                  );
        if (spn2596 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tSelected Maximum Vehicle Speed Limit = %d\n", spn2596);
        }

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 0 1 6 0
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn60160(
        J1939TBL_DATA    *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn2572;        // Sequence Number
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        spn2572 = pMsg->DATA.bytes[0];
        
        if (spn2572 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tSequence Number = %d\n", spn2572);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
        //---------------------------------------------------------------
        //                  D u m p  P G N 6 1 4 4 0
        //---------------------------------------------------------------
    
        bool            j1939tbl_DumpPgn61440(
            J1939TBL_DATA    *this,
            J1939_MSG       *pMsg,
            const
            J1939_PGN_ENTRY *pEntry
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
            if( !j1939tbl_Validate(this) ) {
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
            spn1085 = pMsg->DATA.bytes[2];
            // SPN 1082 4.1     2bits       Engine Coolant Load Increase
            spn1082 = pMsg->DATA.bytes[3] & 0x3;
            // SPN 1667 4.3     2bits       Retarder Requesting Brake Light
            spn1667 = (pMsg->DATA.bytes[3] >> 4) & 0x3;
            // SPN 1480 5       8bits       Source Address of Controlling Device for Retarder Control
            spn1480 = pMsg->DATA.bytes[4];
            // SPN 1715 6       8bits       Drivers Demand Retarder - Percent Torque
            spn1715 = pMsg->DATA.bytes[5];
            // SPN 1716 7       8bits       Retarder Selection, non-engine
            spn1716 = pMsg->DATA.bytes[6];
            // SPN 1717 8       8bits       Actual Maximum Available Retarder - Percent Torque
            spn1717 = pMsg->DATA.bytes[7];

            if (spn900) {
                fprintf(this->pFileOut, "\tRetarder Torque Mode = %d\n", spn900);
            }
            else {
                fprintf(this->pFileOut, "\tRetarder Torque Mode = no braking\n");
            }
            print1of4(this,
                      spn571,
                      "Retarder Enable - Brake Assist Switch",
                      "Retarder - brake assist disabled",
                      "Retarder - brake assist enabled",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn572,
                      "Retarder Enable - Shift Assist Switch",
                      "Retarder - shift assist disabled",
                      "Retarder - shift assist enabled",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn1082,
                      "Engine Coolant Load Increase",
                      "No coolant load increase",
                      "Coolant load increase possible",
                      "Error",
                      NULL
                      );
            if (spn520 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tActual Retarder - Percent Torque = %d\n", spn520);
            }
            if (spn1085 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tIntended Retarder Percent Torque = %d\n", spn1085);
            }
            fprintf(this->pFileOut, "\tRetarder Requesting Brake Light = %d\n", spn1667);
            if (spn1480 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tSource Address of Controlling Device for "
                        "Retarder Control = ");
                printMsgAdr(this, spn1480);
                fprintf(this->pFileOut, "\n");
            }
            if (spn1715 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tDrivers Demand Retarder - Percent Torque = %d\n", spn1715);
            }
            if (spn1716 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tRetarder Selection, non-engine = %d\n", spn1716);
            }
            if (spn1717 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tActual Maximum Available Retarder - Percent Torque = %d\n", spn1717);
            }

            // Return to caller.
            return false;
        }
        
        
        
        //---------------------------------------------------------------
        //                  D u m p  P G N 6 1 4 4 1
        //---------------------------------------------------------------
        
        bool            j1939tbl_DumpPgn61441(
            J1939TBL_DATA    *this,
            J1939_MSG       *pMsg,
            const
            J1939_PGN_ENTRY *pEntry
        )
        {
            J1939_PDU       pdu;
            J1939_PGN       pgn;
            uint8_t         spn561;
            uint8_t         spn562;
            uint8_t         spn563;
            uint8_t         spn1121;
            uint8_t         spn521;
            uint8_t         spn575;
            uint8_t         spn576;
            uint8_t         spn577;
            uint8_t         spn1238;
            uint8_t         spn972;
            uint8_t         spn971;
            uint8_t         spn970;
            uint8_t         spn969;
            uint8_t         spn973;
            uint8_t         spn1243;
            uint8_t         spn1439;
            uint8_t         spn1438;
            uint8_t         spn1793;
            uint8_t         spn1481;
            uint8_t         spn2911;
            uint8_t         spn1836;
            uint8_t         spn1792;
            
            // Do initialization.
#ifdef NDEBUG
#else
            if( !j1939tbl_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
#endif
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            
            // SPN 561  1.1     2bits       ASR Engine Control Active
            spn561 = pMsg->DATA.bytes[0] & 0x3;
            // SPN 562  1.3     2bits       ASR Brake Control Active
            spn562 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
            // SPN 563  1.5     2bits       Anti-Lock Braking (ABS) Active
            spn563 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
            // SPN 1121 1.7     2bits       EBS Brake Switch
            spn1121 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
            // SPN 521  2       8bits       Brake Pedal Position
            spn521 = pMsg->DATA.bytes[1];
            // SPN 575  3.1     2bits       ABS Off-road Switch
            spn575 = pMsg->DATA.bytes[2] & 0x3;
            // SPN 576  3.3     2bits       ASR Off-road Switch
            spn576 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
            // SPN 577  3.5     2bits       ASR 'Hill Holder' Switch
            spn577 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
            // SPN 1238 3.7     2bits       Traction Control Override Switch
            spn1238 = (pMsg->DATA.bytes[2] >> 6) & 0x3;
            // SPN 972  4.1     2bits       Accelerator Interlock Switch
            spn972 = pMsg->DATA.bytes[3] & 0x3;
            // SPN 971  4.3     2bits       Engine Derate Switch
            spn971 = (pMsg->DATA.bytes[3] >> 2) & 0x3;
            // SPN 970  4.5     2bits       Engine Auxiliary Shutdown Switch
            spn970 = (pMsg->DATA.bytes[3] >> 4) & 0x3;
            // SPN 969  4.7     2bits       Remote Accelerator Enable Switch
            spn969 = (pMsg->DATA.bytes[3] >> 6) & 0x3;
            // SPN 973  5       8bits       Engine Retarder Selection
            spn973 = pMsg->DATA.bytes[4];
            // SPN 1243 6.1     2bits       ABS Fully Operational
            spn1243 = pMsg->DATA.bytes[5] & 0x3;
            // SPN 1439 6.3     2bits       EBS Red Warning Signal
            spn1439 = (pMsg->DATA.bytes[5] >> 2) & 0x3;
            // SPN 1438 6.5     2bits       ABS/EBS Amber Warning Signal (Powered Vehicle)
            spn1438 = (pMsg->DATA.bytes[5] >> 4) & 0x3;
            // SPN 1793 6.7     2bits       ATC/ASR Information Signal
            spn1793 = (pMsg->DATA.bytes[5] >> 6) & 0x3;
            // SPN 1481 7       8bits       Source Address of Controlling Device for Brake Control
            spn1481 = pMsg->DATA.bytes[6];
            // SPN 2911 8.3     2bits       Halt brake switch
            spn2911 = (pMsg->DATA.bytes[7] >> 2) & 0x3;
            // SPN 1836 8.5     2bits       Trailer ABS Status
            spn1836 = (pMsg->DATA.bytes[7] >> 4) & 0x3;
            // SPN 1792 8.7     2bits       Tractor-Mounted Trailer ABS Warning Signal
            spn1792 = (pMsg->DATA.bytes[7] >> 6) & 0x3;
            
            print1of4(this,
                      spn561,
                      "ASR Engine Control Active",
                      "ASR engine control passive but installed",
                      "ASR engine control active",
                      "Reserved",
                      NULL
                      );
            print1of4(this,
                      spn562,
                      "ASR Brake Control Active",
                      "ASR brake control passive but installed",
                      "ASR brake control active",
                      "Reserved",
                      NULL
                      );
            print1of4(this,
                      spn563,
                      "Anti-Lock Braking (ABS) Active",
                      "ABS passive but installed",
                      "ABS active",
                      "Reserved",
                      NULL
                      );
            print1of4(this,
                      spn1121,
                      "EBS Brake Switch",
                      "Brake pedal is not being pressed",
                      "Brake pedal is being pressed",
                      "Error",
                      NULL
                      );
            if (spn521 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tBrake Pedal Position = %d\n", spn521);
            }
            print1of4(this,
                      spn575,
                      "ABS Off-road Switch",
                      "ABS off-road switch passive",
                      "ABS off-road switch active",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn576,
                      "ASR Off-road Switch",
                      "ASR off-road switch passive",
                      "ASR off-road switch active",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn577,
                      "ASR 'Hill Holder' Switch",
                      "ASR 'hill holder' switch passive",
                      "ASR 'hill holder' switch active",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn1238,
                      "Traction Control Override Switch",
                      "Off",
                      "On",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn972,
                      "Accelerator Interlock Switch",
                      "Off",
                      "On",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn971,
                      "Engine Derate Switch",
                      "Off",
                      "On",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn970,
                      "Engine Auxiliary Shutdown Switch",
                      "Off",
                      "On",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn969,
                      "Remote Accelerator Enable Switch",
                      "Off",
                      "On",
                      "Error",
                      NULL
                      );
            if (spn973 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Retarder Selection = %d\n", spn973);
            }
            print1of4(this,
                      spn1243,
                      "ABS Fully Operational",
                      "Not Fully Operational",
                      "Fully Operational",
                      "Reserved",
                      NULL
                      );
            print1of4(this,
                      spn1439,
                      "EBS Red Warning Signal",
                      "Off",
                      "On",
                      "Reserved",
                      NULL
                      );
            print1of4(this,
                      spn1438,
                      "ABS/EBS Amber Warning Signal (Powered Vehicle)",
                      "Off",
                      "On",
                      "Reserved",
                      NULL
                      );
            print1of4(this,
                      spn1793,
                      "ATC/ASR Information Signal",
                      "Off",
                      "On",
                      "Reserved",
                      NULL
                      );
            if (spn1481 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tSource Address of Controlling Device for "
                        "Brake Control = ");
                printMsgAdr(this, spn1481);
                fprintf(this->pFileOut, "\n");
            }
            print1of4(this,
                      spn2911,
                      "Halt brake switch",
                      "Halt brake switch passive",
                      "Halt brake switch active",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn1836,
                      "Trailer ABS Status",
                      "Trailer ABS Status Information Available But Not Active",
                      "Trailer ABS Active",
                      "Reserved",
                      NULL
                      );
            print1of4(this,
                      spn1792,
                      "Tractor-Mounted Trailer ABS Warning Signal",
                      "Off",
                      "On",
                      "Reserved",
                      NULL
                      );

            // Return to caller.
            return false;
        }
        
        
        
        //---------------------------------------------------------------
        //              D u m p   P G N 6 1 4 4 2   F002         ETC1
        //---------------------------------------------------------------
        
        /* This is "Electronic Transmission Controller 1". It is a status
         * msg generated by the transmission #3 or #4 every 10ms. It gives
         * us whether the transmission is shifting or not, input rpm and
         * output rpm most importantly.
         */
        
        bool            j1939tbl_DumpPgn61442(
            J1939TBL_DATA	*this,
            J1939_MSG       *pMsg,
            const
            J1939_PGN_ENTRY *pEntry
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
            if( !j1939tbl_Validate(this) ) {
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
            // SPN 1482 8       8bits       Source Address of Controlling Device for
            //                              Transmission Control
            spn1482 = pMsg->DATA.bytes[7];
            
            print1of4(this,
                      spn560,
                      "Transmission Driveline Engaged",
                      "Driveline disengaged",
                      "Driveline engaged",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn573,
                      "Transmission Torque Converter Lockup Engaged",
                      "Torque converter lockup disengaged",
                      "Torque converter lockup engaged",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn574,
                      "Transmission Shift In Process",
                      "Shift is not in process",
                      "Shift in process",
                      "Error",
                      NULL
                      );
            if (spn191 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tTransmission Output Shaft Speed = %d\n", spn191);
            }
            if (spn522 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tPercent Clutch Slip = %d\n", spn522);
            }
            print1of4(this,
                      spn606,
                      "Engine Momentary Overspeed Enable",
                      "Momentary engine overspeed is disabled",
                      "Momentary engine overspeed is enabled",
                      "Reserved",
                      NULL
                      );
            print1of4(this,
                      spn607,
                      "Progressive Shift Disable",
                      "Progressive shift is not disabled",
                      "Progressive shift is disabled",
                      "Reserved",
                      NULL
                      );
            if (spn161 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tTransmission Input Shaft Speed = %d\n", spn161);
            }
            if (spn1482 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tSource Address of Controlling Device for "
                        "Transmission Control = ");
                printMsgAdr(this, spn1482);
                fprintf(this->pFileOut, "\n");
            }
            
            // Return to caller.
            return true;
        }
        
        
        
        //---------------------------------------------------------------
        //             D u m p  P G N 6 1 4 4 3     F003         EEC2
        //---------------------------------------------------------------
        
        bool            j1939tbl_DumpPgn61443(
            J1939TBL_DATA	*this,
            J1939_MSG       *pMsg,
            const
            J1939_PGN_ENTRY *pEntry
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
            if( !j1939tbl_Validate(this) ) {
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
            
            print1of4(this,
                      spn558,
                      "Accelerator Pedal 1 Low Idle Switch",
                      "Accelerator pedal 1 not in low idle condition",
                      "Accelerator pedal 1 in low idle condition",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn559,
                      "Accelerator Pedal Kickdown Switch",
                      "Kickdown passive",
                      "Kickdown active",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn1437,
                      "Road Speed Limit Status",
                      "Active",
                      "Not Active",
                      "Error",
                      NULL
                      );
            print1of4(this,
                      spn2970,
                      "Accelerator Pedal 2 Low Idle Switch",
                      "Accelerator pedal 2 not in low idle condition",
                      "Accelerator pedal 2 in low idle condition",
                      "Error",
                      NULL
                      );
            if (spn91 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tAccelerator Pedal Position 1 = %d\n", spn91);
            }
            if (spn92 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Percent Load At Current Speed = %d\n", spn92);
            }
            if (spn974 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tRemote Accelerator Pedal Position = %d\n", spn974);
            }
            if (spn29 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tAccelerator Pedal Position 2 = %d\n", spn29);
            }
            print1of4(this,
                      spn2979,
                      "Vehicle Acceleration Rate Limit Status",
                      "Limit not active",
                      "Limit active",
                      "Reserved",
                      NULL
                      );
            if (spn3357 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tActual Maximum Available Engine - Percent Torque = %d\n", spn3357);
            }
            
            // Return to caller.
            return false;
        }
        
        
        
        //---------------------------------------------------------------
        //                  D u m p  P G N 6 1 4 4 4
        //---------------------------------------------------------------
        
        bool            j1939tbl_DumpPgn61444(
            J1939TBL_DATA    *this,
            J1939_MSG       *pMsg,
            const
            J1939_PGN_ENTRY *pEntry
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
            if( !j1939tbl_Validate(this) ) {
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
            
            if (spn899) {
                fprintf(this->pFileOut, "\tEngine Torque Mode = %d\n", spn899);
            }
            if (spn512 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tDriver's Demand Engine - Percent Torque = %d\n", spn512);
            }
            if (spn513 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tActual Engine - Percent Torque = %d\n", spn513);
            }
            if (spn190 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Speed (rpm) = %d\n", spn190);
            }
            if (spn1483 == 0xFF) {
            }
            else {
                fprintf(
                        this->pFileOut,
                        "\tSource Address of Controlling Device for Engine Control = "
                );
                printMsgAdr(this, spn1483);
                fprintf(this->pFileOut, "\n");
            }
            switch (spn1675) {
                case 0:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - start not requested\n");
                    break;
                case 1:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - starter active, gear not engaged\n");
                    break;
                case 2:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - starter active, gear engaged\n");
                    break;
                case 3:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - start finished; starter not active after having been actively engaged (after 50ms mode goes to 0000)\n");
                    break;
                case 4:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - starter inhibited - due to engine running already\n");
                    break;
                case 5:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - starter inhibited - due to engine not ready for starting (preheating)\n");
                    break;
                case 6:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - starter inhibited - due to driveline engaged or other transmission inhibit\n");
                    break;
                case 7:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - starter inhibited - due to active immobilizer\n");
                    break;
                case 8:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - starter inhibited - due to starter over-temp\n");
                    break;
                case 12:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - starter inhibited - reason unknown\n");
                    break;
                case 13:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - error\n");
                    break;
                case 14:
                    fprintf(this->pFileOut, "\tEngine Starter Mode - error\n");
                    break;
                default:
                    break;
            }
            if (spn2432 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Demand - Percent Torque = %d\n", spn2432);
            }

            // Return to caller.
            return false;
        }
        
        
        
        //---------------------------------------------------------------
        //                  D u m p  P G N 6 1 4 4 5
        //---------------------------------------------------------------
        
        bool            j1939tbl_DumpPgn61445(
            J1939TBL_DATA   *this,
            J1939_MSG       *pMsg,
            const
            J1939_PGN_ENTRY *pEntry
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
            if( !j1939tbl_Validate(this) ) {
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

            if (spn524 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tTransmission Selected Gear = %d\n", spn524);
            }
            if (spn526 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tTransmission Actual Gear Ratio = %d\n", spn526);
            }
            if (spn523 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tTransmission Current Gear = %d\n", spn523);
            }
            if (spn162 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tTransmission Requested Range = %4X\n", spn162);
            }
            if (spn163 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tTransmission Current Range = %4X\n", spn163);
            }

            // Return to caller.
            return false;
        }
        
        
        
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 1 4 5 2
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn61452(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn3030;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 3030 1-2     16bits      Transmission Torque Converter Ratio
        spn3030 = (pMsg->DATA.bytes[1] << 8) + pMsg->DATA.bytes[0];
        
        if (spn3030 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Torque Converter Ratio = %d\n", spn3030);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 4 8 9 2
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn64892(
        J1939TBL_DATA    *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        //TODO: Fill in
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 4 9 4 7
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn64947(
        J1939TBL_DATA    *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn3245;
        uint16_t        spn3246;
        uint8_t         spn3247;
        uint8_t         spn3248;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 3245 1-2     16bits      Aftertreatment 1 Exhaust Gas Temperature 3
        spn3245 = (pMsg->DATA.bytes[1] << 8) | pMsg->DATA.bytes[0];
        // SPN 3246 3-4     16bits      Aftertreatment 1 Particulate Trap Outlet Gas Temperature
        spn3246 = (pMsg->DATA.bytes[3] << 8) | pMsg->DATA.bytes[2];
        // SPN 3247 5.1     5bits       Aftertreatment 1 Exhaust Gas Temperature 3 Preliminary FMI
        spn3247 = (pMsg->DATA.bytes[4] >> 5) & 0x1F;
        // SPN 3248 6.1     5bits       Aftertreatment 1 Particulate Trap Outlet Exhaust Gas Temperature Preliminary FMI
        spn3248 = (pMsg->DATA.bytes[5] >> 0) & 0x1F;
        
        if (spn3245 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Exhaust Gas Temperature 3 = %d\n", spn3245);
        }
        if (spn3246 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Particulate Trap Outlet Gas Temperature = %d\n", spn3246);
        }
        if (spn3247 == 0x1F) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Exhaust Gas Temperature 3 Preliminary FMI = %d\n", spn3247);
        }
        if (spn3248 == 0x1F) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Particulate Trap Outlet Exhaust Gas Temperature Preliminary FMI = %d\n", spn3248);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 4 9 4 8
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn64948(
        J1939TBL_DATA    *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn3241;
        uint16_t        spn3242;
        uint8_t         spn3243;
        uint8_t         spn3244;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        //TODO:
        // SPN 3241 1-2     16bits      Aftertreatment 1 Exhaust Gas Temperature 1
        spn3241 = (pMsg->DATA.bytes[1] << 8) | pMsg->DATA.bytes[0];
        // SPN 3242 3-4     16bits      Aftertreatment 1 Particulate Trap Intake Gas Temperature
        spn3242 = (pMsg->DATA.bytes[3] << 8) | pMsg->DATA.bytes[2];
        // SPN 3243 5.1     5bits       Aftertreatment 1 Exhaust Gas Temperature 1 Preliminary FMI
        spn3243 = (pMsg->DATA.bytes[4] >> 5) & 0x1F;
        // SPN 3244 6.1     5bits       Aftertreatment 1 Particulate Trap Intake Exhaust Gas Temperature Preliminary FMI
        spn3244 = (pMsg->DATA.bytes[5] >> 0) & 0x1F;
        
        if (spn3241 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Exhaust Gas Temperature 3 = %d\n", spn3241);
        }
        if (spn3242 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Particulate Trap Intake Gas Temperature = %d\n", spn3242);
        }
        if (spn3243 == 0x1F) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Exhaust Gas Temperature 3 Preliminary FMI = %d\n", spn3243);
        }
        if (spn3244 == 0x1F) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Particulate Trap Intake Exhaust Gas Temperature Preliminary FMI = %d\n", spn3244);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 4 9 6 4
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn64964(
        J1939TBL_DATA    *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn2913;
        uint8_t         spn2912;
        uint8_t         spn2919;
        uint8_t         spn2917;
        uint8_t         spn2918;
        uint8_t         spn2921;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 2913 1.3     3bits       Halt brake mode
        spn2913 = (pMsg->DATA.bytes[0] >> 2) & 0x07;
        // SPN 2912 1.6     3bits       Hill holder mode
        spn2912 = (pMsg->DATA.bytes[0] >> 5) & 0x07;
        // SPN 2919 2.1     2bits       Foundation Brake Use
        spn2919 = (pMsg->DATA.bytes[1] >> 0) & 0x03;
        // SPN 2917 2.3     2bits       XBR System State
        spn2917 = (pMsg->DATA.bytes[1] >> 2) & 0x03;
        // SPN 2918 2.5     4bits       XBR Active Control Mode
        spn2918 = (pMsg->DATA.bytes[1] >> 4) & 0x0F;
        // SPN 2921 3       8bits       XBR Acceleration Limit
        spn2921 = pMsg->DATA.bytes[2];
        
        switch (spn2913) {
            case 0:
                fprintf(this->pFileOut, "\tHalt brake mode - Inactive\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tHalt brake mode - Active\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tHalt brake mode - Active, but not functioning properly. (This mode may be used to warn the driver)\n");
                break;
        }
        switch (spn2912) {
            case 0:
                fprintf(this->pFileOut, "\tHill holder mode - Inactive\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tHill holder mode - Active\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tHill holder mode - Active, but will change to inactive in a short time. (This mode may be used to warn the driver)\n");
                break;
        }
        print1of4(this,
                  spn2919,
                  "Foundation Brake Use",
                  "Foundation brakes not in use",
                  "Foundation brakes not in use",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2917,
                  "XBR System State",
                  "Any external brake demand will be accepted (brake system fully operational)",
                  "Only external brake demand of highest XBR Priority (00) will be accepted (e.g. because the temperature limit of the brake system is exceeded)",
                  "No external brake demand will be accepted (e.g. because of fault in brake system)",
                  NULL
                  );
        switch (spn2918) {
            case 0:
                fprintf(this->pFileOut, "\tXBR Active Control Mode - No brake demand being executed (default mode)\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tXBR Active Control Mode - Driver's brake demand being executed, no external brake demand\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tXBR Active Control Mode - Addition mode of XBR acceleration control being executed\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tXBR Active Control Mode - Maximum mode of XBR acceleration control being executed\n");
                break;
        }
        if (spn2921 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tXBR Acceleration Limit = %d\n", spn2921);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 0 9 8
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65098(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn1850;
        uint8_t         spn1849;
        uint8_t         spn3086;
        uint8_t         spn2945;
        uint8_t         spn2900;
        uint8_t         spn1851;
        uint8_t         spn2539;
        uint8_t         spn2538;
        uint8_t         spn2537;
        uint8_t         spn2536;
        uint8_t         spn3289;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 1850 1.5     2bits       Transmission Requested Range Display Blank State
        spn1850 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 1849 1.7     2bits       Transmission Requested Range Display Flash State
        spn1849 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 3086 2.1     2bits       Transmission Ready for Brake Release
        spn3086 = pMsg->DATA.bytes[1] & 0x3;
        // SPN 2945 2.3     2bits       Active Shift Console Indicator
        spn2945 = (pMsg->DATA.bytes[1] >> 2) & 0x3;
        // SPN 2900 2.5     2bits       Transmission Engine Crank Enable
        spn2900 = (pMsg->DATA.bytes[1] >> 4) & 0x3;
        // SPN 1851 2.7     2bits       Transmission Shift Inhibit Indicator
        spn1851 = (pMsg->DATA.bytes[1] >> 6) & 0x3;
        // SPN 2539 3.1     2bits       Transmission Mode 4 Indicator
        spn2539 = pMsg->DATA.bytes[2] & 0x3;
        // SPN 2538 3.3     2bits       Transmission Mode 3 Indicator
        spn2538 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
        // SPN 2537 3.5     2bits       Transmission Mode 2 Indicator
        spn2537 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
        // SPN 2536 3.7     2bits       Transmission Mode 1 Indicator
        spn2536 = (pMsg->DATA.bytes[2] >> 6) & 0x3;
        // SPN 3289 4       8bits       Transmission Requested Gear Feedback
        spn3289 = pMsg->DATA.bytes[3];
        
        print1of4(this,
                  spn1850,
                  "Transmission Requested Range Display Blank State",
                  "Inactive; Transmission Requested Range display should not be blanked",
                  "Active; Transmission Requested Range display should be blanked",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1849,
                  "Transmission Requested Range Display Flash State",
                  "Inactive; Transmission Requested Range display should not be flashing",
                  "Active; Transmission Requested Range display should be flashing",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn3086,
                  "Transmission Ready for Brake Release",
                  "Transmission Not Ready for Brake Release",
                  "Transmission Ready for Brake Release",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2945,
                  "Active Shift Console Indicator",
                  "Primary shift console is active",
                  "Secondary shift console is active",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2900,
                  "Transmission Engine Crank Enable",
                  "Cranking disabled; engine cranking is prohibited by the transmission",
                  "Cranking enabled; engine cranking is allowed by the transmission",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1851,
                  "Transmission Shift Inhibit Indicator",
                  "Inactive; shift is not inhibited",
                  "Active; shift is inhibited",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2539,
                  "Transmission Mode 4 Indicator",
                  "Transmission Mode 4 not active",
                  "Transmission Mode 4 Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2538,
                  "Transmission Mode 3 Indicator",
                  "Transmission Mode 3 not active",
                  "Transmission Mode 3 Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2537,
                  "Transmission Mode 2 Indicator",
                  "Transmission Mode 2 not active",
                  "Transmission Mode 2 Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2536,
                  "Transmission Mode 1 Indicator",
                  "Transmission Mode 1 not active",
                  "Transmission Mode 1 Active",
                  "Error",
                  NULL
                  );
        if (spn3289 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Requested Gear Feedback = %d\n", spn3289);
        }

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 1 3
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65213(
        J1939TBL_DATA    *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn975;
        uint8_t         spn977;
        uint16_t        spn1639;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 975  1       8bits       Estimated Percent Fan Speed
        spn975 = pMsg->DATA.bytes[0];
        // SPN 977  2.1     4bits       Fan Drive State
        spn977 = pMsg->DATA.bytes[1] & 0x0F;
        // SPN 1639 3-4     16bits      Fan Speed
        spn1639 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);
        
        if (spn975 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEstimated Percent Fan Speed = %d\n", spn975);
        }
        switch (spn977) {
            case 0:
                fprintf(this->pFileOut, "\tFan Drive State - Fan off\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tFan Drive State - Engine system–General\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tFan Drive State - Excessive engine air temperature\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tFan Drive State - Excessive engine oil temperature\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tFan Drive State - Excessive engine coolant temperature\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tFan Drive State - Excessive transmission oil temperature\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tFan Drive State - Excessive hydraulic oil temperature\n");
                break;
            case 7:
                fprintf(this->pFileOut, "\tFan Drive State - Default Operation\n");
                break;
            case 8:
                fprintf(this->pFileOut, "\tFan Drive State - Not defined\n");
                break;
            case 9:
                fprintf(this->pFileOut, "\tFan Drive State - Manual control\n");
                break;
            case 10:
                fprintf(this->pFileOut, "\tFan Drive State - Transmission retarder\n");
                break;
            case 11:
                fprintf(this->pFileOut, "\tFan Drive State - A/C system\n");
                break;
            case 12:
                fprintf(this->pFileOut, "\tFan Drive State - Timer\n");
                break;
            case 13:
                fprintf(this->pFileOut, "\tFan Drive State - Engine brake\n");
                break;
            case 14:
                fprintf(this->pFileOut, "\tFan Drive State - Other\n");
                break;
        }
        if (spn1639 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tFan Speed = %d\n", spn1639);
        }

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 1 5
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65215(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn904;
        uint8_t         spn905;
        uint8_t         spn906;
        uint8_t         spn907;
        uint8_t         spn908;
        uint8_t         spn909;
        uint8_t         spn910;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 904  1-2     16bits      Front Axle Speed
        spn904 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8);
        // SPN 905  3       8bits       Relative Speed; Front Axle, Left Wheel
        spn905 = pMsg->DATA.bytes[2];
        // SPN 906  4       8bits       Relative Speed; Front Axle, Right Wheel
        spn906 = pMsg->DATA.bytes[3];
        // SPN 907  5       8bits       Relative Speed; Rear Axle #1, Left Wheel
        spn907 = pMsg->DATA.bytes[4];
        // SPN 908  6       8bits       Relative Speed; Rear Axle #1, Right Wheel
        spn908 = pMsg->DATA.bytes[5];
        // SPN 909  7       8bits       Relative Speed; Rear Axle #2, Left Wheel
        spn909 = pMsg->DATA.bytes[6];
        // SPN 910  8       8bits       Relative Speed; Rear Axle #2, Right Wheel
        spn910 = pMsg->DATA.bytes[7];
        
        if (904 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tFront Axle Speed = %d\n", 904);
        }
        if (spn905 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tRelative Speed; Front Axle, Left Wheel = %d\n", spn905);
        }
        if (spn906 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tRelative Speed; Front Axle, Right Wheel = %d\n", spn906);
        }
        if (spn907 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tRelative Speed; Rear Axle #1, Left Wheel = %d\n", spn907);
        }
        if (spn908 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tRelative Speed; Rear Axle #1, Right Wheel = %d\n", spn908);
        }
        if (spn909 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tRelative Speed; Rear Axle #2, Left Wheel = %d\n", spn909);
        }
        if (spn910 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tRelative Speed; Rear Axle #2, Right Wheel = %d\n", spn910);
        }

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 1 7
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65217(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn917;
        uint32_t        spn918;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 917  1-4     32bits      High Resolution Total Vehicle Distance
        spn917 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
                | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 918  5-8     32bits      High Resolution Trip Distance
        spn918 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8)
                | (pMsg->DATA.bytes[6] << 16)  | (pMsg->DATA.bytes[7] << 24);
        
        if (spn917 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tHigh Resolution Total Vehicle Distance = %d\n", spn917);
        }
        if (spn918 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tHigh Resolution Trip Distance = %d\n", spn918);
        }

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 4 7
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65247(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
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
        if( !j1939tbl_Validate(this) ) {
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
        // SPN 519  4       8bits       Engine's Desired Operating Speed Asymmetry Adjustment
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
        
        if (spn514 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tNominal Friction - Percent Torque = %d\n", spn514);
        }
        if (spn515 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine's Desired Operating Speed = %d\n", spn515);
        }
        if (spn519 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine's Desired Operating Speed Asymmetry Adjustment = %d\n", spn519);
        }
        if (spn2978 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEstimated Engine Parasitic Losses - Percent Torque = %d\n", spn2978);
        }
        if (spn3236 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tAftertreatment 1 Exhaust Gas Mass Flow = %d\n", spn3236);
        }
        print1of4(this,
                  spn3237,
                  "Aftertreatment 1 Intake Dew Point",
                  "Not exceeded the dew point",
                  "Exceeded the dew point",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3238,
                  "Aftertreatment 1 Exhaust Dew Point",
                  "Not exceeded the dew point",
                  "Exceeded the dew point",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3239,
                  "Aftertreatment 2 Intake Dew Point",
                  "Not exceeded the dew point",
                  "Exceeded the dew point",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3240,
                  "Aftertreatment 2 Exhaust Dew Point",
                  "Not exceeded the dew point",
                  "Exceeded the dew point",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 4 8
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65248(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn244;
        uint32_t        spn245;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
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
        
        if (spn244 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTrip Distance = %d\n", spn244);
        }
        if (spn245 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTotal Vehicle Distance = %d\n", spn245);
        }

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 5 2
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65252(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn593;
        uint8_t         spn594;
        uint8_t         spn592;
        uint8_t         spn590;
        uint8_t         spn591;
        uint8_t         spn985;
        uint8_t         spn875;
        uint8_t         spn605;
        uint8_t         spn1081;
        uint8_t         spn1110;
        uint8_t         spn1109;
        uint8_t         spn1108;
        uint8_t         spn1107;
        uint8_t         spn1111;
        uint8_t         spn2815;
        uint8_t         spn2814;
        uint8_t         spn2813;
        uint8_t         spn2812;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 593  1.1     2bits       Engine Idle Shutdown has Shutdown Engine
        spn593 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 594  1.3     2bits       Engine Idle Shutdown Driver Alert Mode
        spn594 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        // SPN 592  1.5     2bits       Engine Idle Shutdown Timer Override
        spn592 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 590  1.7     2bits       Engine Idle Shutdown Timer State
        spn590 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 591  2.7     2bits       Engine Idle Shutdown Timer Function
        spn591 = (pMsg->DATA.bytes[1] >> 6) & 0x3;
        // SPN 985  3.1     2bits       A/C High Pressure Fan Switch
        spn985 = pMsg->DATA.bytes[2] & 0x3;
        // SPN 875  3.3     2bits       Refrigerant Low Pressure Switch
        spn875 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
        // SPN 605  3.5     2bits       Refrigerant High Pressure Switch
        spn605 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
        // SPN 1081 4.1     2bits       Engine Wait to Start Lamp
        spn1081 = pMsg->DATA.bytes[3] & 0x3;
        // SPN 1110 5.1     2bits       Engine Protection System has Shutdown Engine
        spn1110 = pMsg->DATA.bytes[4] & 0x3;
        // SPN 1109 5.3     2bits       Engine Protection System Approaching Shutdown
        spn1109 = (pMsg->DATA.bytes[4] >> 2) & 0x3;
        // SPN 1108 5.5     2bits       Engine Protection System Timer Override
        spn1108 = (pMsg->DATA.bytes[4] >> 4) & 0x3;
        // SPN 1107 5.7     2bits       Engine Protection System Timer State
        spn1107 = (pMsg->DATA.bytes[4] >> 6) & 0x3;
        // SPN 1111 6.7     2bits       Engine Protection System Configuration
        spn1111 = (pMsg->DATA.bytes[5] >> 6) & 0x3;
        // SPN 2815 7.1     2bits       Engine Alarm Acknowledge
        spn2815 = pMsg->DATA.bytes[6] & 0x3;
        // SPN 2814 7.3     2bits       Engine Alarm Output Command Status
        spn2814 = (pMsg->DATA.bytes[6] >> 2) & 0x3;
        // SPN 2813 7.5     2bits       Engine Air Shutoff Command Status
        spn2813 = (pMsg->DATA.bytes[6] >> 4) & 0x3;
        // SPN 2812 7.7     2bits       Engine Overspeed Test
        spn2812 = (pMsg->DATA.bytes[6] >> 6) & 0x3;
        
        print1of4(this,
                  spn593,
                  "Engine Idle Shutdown has Shutdown Engine",
                  "No",
                  "Yes",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn594,
                  "Engine Idle Shutdown Driver Alert Mode",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn592,
                  "Engine Idle Shutdown Timer Override",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn590,
                  "Engine Idle Shutdown Timer State",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn591,
                  "Engine Idle Shutdown Timer Function",
                  "Disabled in calibration",
                  "Enabled in calibration",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn985,
                  "A/C High Pressure Fan Switch",
                  "Pressure normal",
                  "Pressure too high, compressor clutch may be disengaged",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn875,
                  "Refrigerant Low Pressure Switch",
                  "Pressure normal",
                  "Pressure too high, compressor clutch may be disengaged",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn605,
                  "Refrigerant High Pressure Switch",
                  "Pressure normal",
                  "Pressure too high, compressor clutch may be disengaged",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1081,
                  "Engine Wait to Start Lamp",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1110,
                  "Engine Protection System has Shutdown Engine",
                  "No",
                  "Yes",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1109,
                  "Engine Protection System Approaching Shutdown",
                  "Not approaching",
                  "Approaching",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1108,
                  "Engine Protection System Timer Override",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1107,
                  "Engine Protection System Timer State",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1111,
                  "Engine Protection System Configuration",
                  "Disabled in calibration",
                  "Enabled in calibration",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2815,
                  "Engine Alarm Acknowledge",
                  "Not Active",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2814,
                  "Engine Alarm Command Status",
                  "Not Active",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2813,
                  "Engine Alarm Shutoff Command Status",
                  "Air Shutoff Disabled, not attempting to shutoff engine air supply",
                  "Air Shutoff Enabled, attempting to shutoff engine air supply",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2812,
                  "Engine Overspeed Test",
                  "Not Active",
                  "Active",
                  "Error",
                  NULL
                  );

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 5 7
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65257(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn182;
        uint32_t        spn250;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 182  1-4     32bits      Engine Trip Fuel
        spn182 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
        | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 250  5-8     32bits      Total Vehicle Distance
        spn250 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8)
        | (pMsg->DATA.bytes[6] << 16)  | (pMsg->DATA.bytes[7] << 24);
        
        if (spn182 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Trip Fuel = %d\n", spn182);
        }
        if (spn250 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Total Fuel Used = %d\n", spn250);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 2
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65262(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
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
        if( !j1939tbl_Validate(this) ) {
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
        
        if (spn110 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Coolant Temperature = %d\n", spn110);
        }
        if (spn174 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Fuel Temperature 1 = %d\n", spn174);
        }
        if (spn175 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Oil Temperature 1 = %d\n", spn175);
        }
        if (spn176 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Turbocharger Oil Temperature = %d\n", spn176);
        }
        if (spn52 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Intercooler Temperature = %d\n", spn52);
        }
        if (spn1134 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Intercooler Thermostat Opening = %d\n", spn1134);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 6 3
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65263(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
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
        if( !j1939tbl_Validate(this) ) {
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
        
        if (spn94 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Fuel Delivery Pressure = %d\n", spn94);
        }
        if (spn22 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Extended Crankcase Blow-by Pressure = %d\n", spn22);
        }
        if (spn98 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Oil Level = %d\n", spn98);
        }
        if (spn100 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Oil Pressure = %d\n", spn100);
        }
        if (spn101 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Crankcase Pressure = %d\n", spn101);
        }
        if (spn109 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Coolant Pressure = %d\n", spn109);
        }
        if (spn111 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Coolant Level = %d\n", spn111);
        }

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 4
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65264(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
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
        if( !j1939tbl_Validate(this) ) {
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
        
        if (spn90 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tPower Takeoff Oil Temperature = %d\n", spn90);
        }
        if (spn186 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tPower Takeoff Speed = %d\n", spn186);
        }
        if (spn187 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tPower Takeoff Set Speed = %d\n", spn186);
        }
        print1of4(this,
                  spn980,
                  "Engine PTO Enable Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn979,
                  "Engine Remote PTO Preprogrammed Speed Control Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn978,
                  "Engine Remote PTO Variable Speed Control Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn984,
                  "Engine PTO Set Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn983,
                  "Engine PTO Coast/Decelerate Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn982,
                  "Engine PTO Resume Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn981,
                  "Engine PTO Accelerate Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2897,
                  "Operator PTO Memory Select Switch",
                  "PTO set speed memory 1 selected",
                  "PTO set speed memory 2 selected",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3447,
                  "Remote PTO preprogrammed speed control switch #2",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3448,
                  "Auxiliary Input Ignore Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //      PGN 65265 FEF1 - Cruise Control/Vehicle Speed - CCVS
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65265(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn69;
        uint8_t         spn70;
        uint8_t         spn1633;
        uint16_t        spn84;
        uint8_t         spn595;
        uint8_t         spn596;
        uint8_t         spn597;
        uint8_t         spn598;
        uint8_t         spn599;
        uint8_t         spn600;
        uint8_t         spn601;
        uint8_t         spn602;
        uint8_t         spn86;
        uint8_t         spn976;
        uint8_t         spn527;
        uint8_t         spn968;
        uint8_t         spn967;
        uint8_t         spn966;
        uint8_t         spn1237;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN   69  1.1     2bits       Two Speed Axle Switch
        spn69 = pMsg->DATA.bytes[0] & 0x03;
        // SPN   70  1.3     2bits       Parking Brake Switch
        spn70 = (pMsg->DATA.bytes[0] >> 2) & 0x03;
        // SPN 1633  1.5     2bits       Cruise Control Pause Switch
        spn1633 = (pMsg->DATA.bytes[0] >> 2) & 0x03;
        // SPN   84  2-3     16bits      Wheel-Based Vehicle Speed
        spn84 = (pMsg->DATA.bytes[2] << 8) | pMsg->DATA.bytes[1];
        // SPN  595  4.1      2bits      Cruise Control Active
        spn595 = pMsg->DATA.bytes[3] & 0x03;
        // SPN  596  4.3     2bits       Cruise Control Enable Switch
        spn596 = (pMsg->DATA.bytes[3] >> 2) & 0x03;
        // SPN  597  4.5     2bits       Brake Switch
        spn597 = (pMsg->DATA.bytes[3] >> 2) & 0x03;
        // SPN  598  4.7     2bits       Clutch Switch
        spn598 = (pMsg->DATA.bytes[3] >> 2) & 0x03;
        // SPN  599  5.1     2bits       Cruise Control Set Switch
        spn599 = pMsg->DATA.bytes[4] & 0x03;
        // SPN  600  5.3     2bits       Cruise Control Coast (Decelerate) Switch
        spn600 = (pMsg->DATA.bytes[4] >> 2) & 0x03;
        // SPN  601  5.5     2bits       Cruise Control Resume Switch
        spn601 = (pMsg->DATA.bytes[4] >> 2) & 0x03;
        // SPN  602  5.7     2bits       Cruise Control Accelerate Switch
        spn602 = (pMsg->DATA.bytes[4] >> 2) & 0x03;
        // SPN   86  6       8bits       Cruise Control Set Speed
        spn86 = pMsg->DATA.bytes[5];
        // SPN  976  7.1     5bits       PTO State
        spn976 = pMsg->DATA.bytes[6] & 0x1F;
        // SPN  527  7.6     3bits       Cruise Control States
        spn527 = (pMsg->DATA.bytes[6] >> 5) & 0x07;
        // SPN  968  8.1     2bits       Engine Idle Increment Switch
        spn968 = pMsg->DATA.bytes[7] & 0x03;
        // SPN  967  8.3     2bits       Engine Idle Decrement Switch
        spn967 = (pMsg->DATA.bytes[7] >> 2) & 0x03;
        // SPN  966  8.5     2bits       Engine Test Mode Switch
        spn966 = (pMsg->DATA.bytes[7] >> 2) & 0x03;
        // SPN 1237  8.7     2bits       Engine Shutdown Override Switch
        spn1237 = (pMsg->DATA.bytes[7] >> 2) & 0x03;
        
        if (spn84 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\t   Vechicle Speed = %d\n", spn84);
        }
        if (spn86 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tCC Vechicle Speed = %d\n", spn84);
        }
        print1of4(this,
                  spn69,
                  "Two Speed Axle Switch",
                  "Low speed range",
                  "High speed range",
                  "Error",
                  NULL
        );
        print1of4(this,
                  spn70,
                  "Parking Brake Switch",
                  "Parking brake not set",
                  "Parking brake set",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1633,
                  "Cruise Control Pause Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn595,
                  "Cruise Control Active",
                  "Cruise control switched off",
                  "Cruise control switched on",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn596,
                  "Cruise Control Enable Switch",
                  "Cruise control disabled",
                  "Cruise control enabled",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn597,
                  "Brake Switch",
                  "Brake pedal released",
                  "Brake pedal depressed",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn598,
                  "Clutch Switch",
                  "Clutch pedal released",
                  "Clutch pedal depressed",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn599,
                  "Cruise Control Set Switch",
                  "Cruise control activator not in the position 'set'",
                  "Cruise control activator in position 'set'",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn600,
                  "Cruise Control Coast (Decelerate) Switch",
                  "Cruise control activator not in the position 'coast'",
                  "Cruise control activator in position 'coast'",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn601,
                  "Cruise Control Resume Switch",
                  "Cruise control activator not in the position 'resume'",
                  "Cruise control activator in position 'resume'",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn602,
                  "Cruise Control Accelerate Switch",
                  "Cruise control activator not in the position 'accelerate'",
                  "Cruise control activator in position 'accelerate'",
                  "Error",
                  NULL
                  );
        switch (spn976) {
            case 0:
                fprintf(this->pFileOut, "\tPTO State - Off/Disabled\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tPTO State - Hold\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tPTO State - Remote Hold\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tPTO State - Standby\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tPTO State - Remote Standby\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tPTO State - Set\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tPTO State - Decelerate/Coast\n");
                break;
            case 7:
                fprintf(this->pFileOut, "\tPTO State - Resume\n");
                break;
            case 8:
                fprintf(this->pFileOut, "\tPTO State - Accelerate\n");
                break;
            case 9:
                fprintf(this->pFileOut, "\tPTO State - Accelerator Override\n");
                break;
            case 10:
                fprintf(this->pFileOut, "\tPTO State - Preprogrammed set speed 1\n");
                break;
            case 11:
                fprintf(this->pFileOut, "\tPTO State - Preprogrammed set speed 2\n");
                break;
            case 12:
                fprintf(this->pFileOut, "\tPTO State - Preprogrammed set speed 3\n");
                break;
            case 13:
                fprintf(this->pFileOut, "\tPTO State - Preprogrammed set speed 4\n");
                break;
            case 14:
                fprintf(this->pFileOut, "\tPTO State - Preprogrammed set speed 5\n");
                break;
            case 15:
                fprintf(this->pFileOut, "\tPTO State - Preprogrammed set speed 6\n");
                break;
            case 16:
                fprintf(this->pFileOut, "\tPTO State - Preprogrammed set speed 7\n");
                break;
            case 17:
                fprintf(this->pFileOut, "\tPTO State - Preprogrammed set speed 8\n");
                break;
            case 18:
                fprintf(this->pFileOut, "\tPTO State - PTO set speed memory 1\n");
                break;
            case 19:
                fprintf(this->pFileOut, "\tPTO State - PTO set speed memory 2\n");
                break;
        }
        switch (spn527) {
            case 0:
                fprintf(this->pFileOut, "\tCruise Control States - Off/Disabled\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tCruise Control States - Hold\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tCruise Control States - Accelerate\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tCruise Control States - Decelerate\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tCruise Control States - Resume\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tCruise Control States - Set\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tCruise Control States - Accelerator Override\n");
                break;
        }
        print1of4(this,
                  spn968,
                  "Engine Idle Increment Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn967,
                  "Engine Idle Decrement Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn966,
                  "Engine Test Mode Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1237,
                  "Engine Shutdown Override Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               H a n d l e  P G N 6 5 2 6 6   FEF2         LFE
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65266(
        J1939TBL_DATA	*this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        uint16_t        spn183;
        uint16_t        spn184;
        uint16_t        spn185;
        uint8_t         spn51;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pMsg) {
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            
            // SPN 183  1-2     16bits       Engine Fuel Rate
            spn183 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8);
            // SPN 184  3-4     16bits       Engine Instantaneous Fuel Economy
            spn184 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);
            // SPN 185  5-6     16bits       Engine Average Fuel Economy
            spn185 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
            // SPN 51   7       8bits        Engine Throttle Position
            spn51 = pMsg->DATA.bytes[6];

            if (spn183 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Fuel Rate = %d\n", spn183);
            }
            if (spn184 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Instantaneous Fuel Economy = %d\n", spn184);
            }
            if (spn185 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Average Fuel Economy = %d\n", spn185);
            }
            if (spn51 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Throttle Position = %d\n", spn51);
            }
        
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 6 9
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65269(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn108;
        uint16_t        spn170;
        uint16_t        spn171;
        uint8_t         spn172;
        uint16_t        spn79;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 108  1       8bits       Barometric Pressure
        spn108 = pMsg->DATA.bytes[0];
        // SPN 170  2-3     16bits      Cab Interior Temperature
        spn170 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        // SPN 171  4-5     16bits      Ambient Air Temperature
        spn171 = pMsg->DATA.bytes[3] | (pMsg->DATA.bytes[4] << 8);
        // SPN 172  6       8bits       Engine Air Inlet Temperature
        spn172 = pMsg->DATA.bytes[0];
        // SPN 79   7-8     16bits      Road Surface Temperature
        spn79 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               H a n d l e  P G N 6 5 2 7 0   FEF6         IC1
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65270(
        J1939TBL_DATA	*this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        uint8_t         spn81;
        uint8_t         spn102;
        uint8_t         spn105;
        uint8_t         spn106;
        uint8_t         spn107;
        uint16_t        spn173;
        uint8_t         spn112;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pMsg) {
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            
            // SPN 81   1       8bits       Engine Particulate Trap Inlet Pressure
            spn81 = pMsg->DATA.bytes[0];
            // SPN 102  2       8bits       Engine Turbocharger Boost Pressure
            spn102 = pMsg->DATA.bytes[1];
            // SPN 105  3       8bits       Engine Intake Manifold 1 Temperature
            spn105 = pMsg->DATA.bytes[2];
            // SPN 106  4       8bits       Engine Air Inlet Pressure
            spn106 = pMsg->DATA.bytes[3];
            // SPN 107  5       8bits       Engine Air Filter 1 Differential Pressure
            spn107 = pMsg->DATA.bytes[4];
            // SPN 173  6-7     16bits      Engine Exhaust Gas Temperature
            spn173 = pMsg->DATA.bytes[5] | (pMsg->DATA.bytes[6] << 8);
            // SPN 112  8       8bits       Engine Coolant Filter Differential Pressure
            spn112 = pMsg->DATA.bytes[7];
            
            if (spn81 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Particulate Trap Inlet Pressure = %d\n", spn81);
            }
            if (spn102 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Turbocharger Boost Pressure = %d\n", spn102);
            }
            if (spn105 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Intake Manifold 1 Temperature = %d\n", spn105);
            }
            if (spn106 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Air Inlet Pressure = %d\n", spn106);
            }
            if (spn107 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Air Filter 1 Differential Pressure = %d\n", spn107);
            }
            if (spn173 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Exhaust Gas Temperature = %d\n", spn173);
            }
            if (spn112 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tEngine Coolant Filter Differential Pressure = %d\n", spn112);
            }
            
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 7 1
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65271(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn114;
        uint8_t         spn115;
        uint16_t        spn167;
        uint16_t        spn168;
        uint16_t        spn158;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 114  1       8bits       Net Battery Current
        spn114 = pMsg->DATA.bytes[0];
        // SPN 115  2       8bits       Alternator Current
        spn115 = pMsg->DATA.bytes[1];
        // SPN 167  3-4     16bits      Charging System Potential (Voltage)
        spn167 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);
        // SPN 168  5-6     16bits      Electrical Potential (Voltage)
        spn168 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 158  7-8     16bits      Battery Potential (Voltage), Switched
        spn158 = pMsg->DATA.bytes[6] | (pMsg->DATA.bytes[7] << 8);
        
        if (spn114 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tNet Battery Current = %d\n", spn114);
        }
        if (spn115 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tAlternator Current = %d\n", spn115);
        }
        if (spn167 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tCharging System Potential (Voltage) = %d\n", spn167);
        }
        if (spn168 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tElectrical Potential (Voltage) = %d\n", spn168);
        }
        if (spn158 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tBattery Potential (Voltage), Switched = %d\n", spn158);
        }
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               H a n d l e  P G N 6 5 2 7 2   EBC1        TRF1
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65272(
        J1939TBL_DATA	*this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        uint8_t         spn123;
        uint8_t         spn124;
        uint8_t         spn126;
        uint8_t         spn127;
        uint16_t        spn177;
        uint8_t         spn3027;
        uint8_t         spn3028;
        uint8_t         spn3026;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 123  1       8bits       Clutch Pressure
        spn123 = pMsg->DATA.bytes[0];
        // SPN 124  2       8bits       Transmission Oil Level
        spn124 = pMsg->DATA.bytes[1];
        // SPN 126  3       8bits       Transmission Filter Differential Pressure
        spn126 = pMsg->DATA.bytes[2];
        // SPN 127  4       8bits       Transmission Oil Pressure
        spn127 = pMsg->DATA.bytes[3];
        // SPN 177  5-6     16bits       Transmission Oil Temperature
        spn177 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 3027 7       8bits       Transmission Oil Level High / Low
        spn3027 = pMsg->DATA.bytes[6];
        // SPN 3028 8.1     4bits       Transmission Oil Level Countdown Timer
        spn3028 = pMsg->DATA.bytes[7] & 0xF;
        // SPN 3026 8.5     4bits       Transmission Oil Level Measurement Status
        spn3026 = (pMsg->DATA.bytes[7] >> 4) & 0xF;
        
        if (spn123 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tClutch Pressure = %d\n", spn123);
        }
        if (spn124 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Oil Level = %d\n", spn124);
        }
        if (spn126 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Filter Differential Pressure = %d\n", spn126);
        }
        if (spn127 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Oil Pressure = %d\n", spn127);
        }
        if (spn177 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Oil Temperature = %d\n", spn177);
        }
        if (spn3027 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Oil Level High / Low = %d\n", spn3027);
        }
        switch (spn3028) {
            case 0:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer -  less than 1 minute\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 1 minute\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 2 minutes\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 3 minutes\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 4 minutes\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 5 minutes\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 6 minutes\n");
                break;
            case 7:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 7 minutes\n");
                break;
            case 8:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 8 minutes\n");
                break;
            case 9:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 9 minutes\n");
                break;
            case 10:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 10 minutes\n");
                break;
            case 11:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 11 minutes\n");
                break;
            case 12:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 12 minutes\n");
                break;
            case 13:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - 13 minutes\n");
                break;
            case 14:
                fprintf(this->pFileOut, "\tTransmission Oil Level Countdown Timer - error\n");
        }
        switch (spn3026) {
            case 0:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status -  Conditions valid for transmission oil level measurement\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid – Settling timer still counting down\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid – Transmission in gear\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid – Transmission fluid temperature too low\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid – Transmission fluid temperature too high\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid – Vehicle moving; output shaft speed too high\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid – Vehicle not level\n");
                break;
            case 7:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid – Engine speed too low\n");
                break;
            case 8:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid – Engine speed too high\n");
                break;
            case 13:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Conditions not valid - Other\n");
                break;
            case 14:
                fprintf(this->pFileOut, "\tTransmission Oil Level Measurement Status - Error\n");
                break;
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 7 6
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65276(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn80;
        uint8_t         spn96;
        uint8_t         spn95;
        uint8_t         spn99;
        uint16_t        spn169;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 80   1       8bits       Washer Fluid Level
        spn80 = pMsg->DATA.bytes[0];
        // SPN 96   2       8bits       Fuel Level
        spn96 = pMsg->DATA.bytes[1];
        // SPN 95   3       8bits       Engine Fuel Filter Differential Pressure
        spn95 = pMsg->DATA.bytes[2];
        // SPN 99   4       8bits       Engine Oil Filter Differential Pressure
        spn99 = pMsg->DATA.bytes[3];
        // SPN 169  5-6     16bits      Cargo Ambient Temperature
        spn169 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] >> 8);
        
        if (spn80 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tWasher Fluid Level = %d\n", spn80);
        }
        if (spn96 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tFuel Level = %d\n", spn96);
        }
        if (spn95 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Fuel Filter Differential Pressure = %d\n", spn95);
        }
        if (spn99 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tEngine Oil Filter Differential Pressure = %d\n", spn99);
        }
        if (spn169 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tCargo Ambient Temperature = %d\n", spn169);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 7 9
    //---------------------------------------------------------------
    
    bool            j1939tbl_DumpPgn65279(
        J1939TBL_DATA   *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn97;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 97   1.1     2bits       Water In Fuel Indicator
        spn97 = pMsg->DATA.bytes[0] & 0x03;
        
        print1of4(this,
                  spn97,
                  "Water In Fuel Indicator",
                  "No",
                  "Yes",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
        //---------------------------------------------------------------
        //                  D u m p   M e s s a g e
        //---------------------------------------------------------------
        
        bool            j1939tbl_DumpMessage(
            J1939TBL_DATA	*this,
            J1939_MSG       *pMsg
        )
        {
            J1939_PDU       pdu;
            J1939_PGN       pgn;
            const
            J1939_PGN_ENTRY *pEntry = NULL;
            
            // Do initialization.
#ifdef NDEBUG
#else
            if( !j1939tbl_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
#endif
            if (this->pFileOut)
                ;
            else {
                return false;
            }
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);

            pEntry = j1939tbl_Find_Pgn(pgn);
            if (pEntry) {
                printMsgDesc(this, pMsg, pEntry);
            }
            else {
                if ((0xFF00 <= pgn.pgn) && (pgn.pgn <= 0xFFFF)) {
                    printMsgDesc(this, pMsg, &pgn65280_entry);
                }
                else {
                    printMsg(this, pMsg);
                    fprintf(this->pFileOut, "   **** Unknown Message ****\n");
                }
                return true;
            }
            
            
            switch (pgn.pgn) {
                
                case 0:
                    j1939tbl_DumpPgn0(this, pMsg, pEntry);
                    break;
                    
                case 57344:
                    j1939tbl_DumpPgn57344(this, pMsg, pEntry);
                    break;
                    
                case 60160:
                    j1939tbl_DumpPgn60160(this, pMsg, pEntry);
                    break;
                    
                case 61440:
                    j1939tbl_DumpPgn61440(this, pMsg, pEntry);
                    break;
                    
                case 61441:
                    j1939tbl_DumpPgn61441(this, pMsg, pEntry);
                    break;
                    
                case 61442:
                    j1939tbl_DumpPgn61442(this, pMsg, pEntry);
                    break;
                    
                case 61443:
                    j1939tbl_DumpPgn61443(this, pMsg, pEntry);
                    break;
                    
                case 61444:
                    j1939tbl_DumpPgn61444(this, pMsg, pEntry);
                    break;
                    
                case 61445:
                    j1939tbl_DumpPgn61445(this, pMsg, pEntry);
                    break;
                    
                case 61452:
                    j1939tbl_DumpPgn61452(this, pMsg, pEntry);
                    break;
                    
                case 64892:
                    j1939tbl_DumpPgn64892(this, pMsg, pEntry);
                    break;
                    
                case 64947:
                    j1939tbl_DumpPgn64947(this, pMsg, pEntry);
                    break;
                    
                case 64948:
                    j1939tbl_DumpPgn64948(this, pMsg, pEntry);
                    break;
                    
                case 64964:
                    j1939tbl_DumpPgn64964(this, pMsg, pEntry);
                    break;
                    
                case 65098:
                    j1939tbl_DumpPgn65098(this, pMsg, pEntry);
                    break;
                    
                case 65213:
                    j1939tbl_DumpPgn65213(this, pMsg, pEntry);
                    break;
                    
                case 65215:
                    j1939tbl_DumpPgn65215(this, pMsg, pEntry);
                    break;
                    
                case 65217:
                    j1939tbl_DumpPgn65217(this, pMsg, pEntry);
                    break;
                    
                case 65247:
                    j1939tbl_DumpPgn65247(this, pMsg, pEntry);
                    break;
                    
                case 65248:
                    j1939tbl_DumpPgn65248(this, pMsg, pEntry);
                    break;
                    
                case 65252:
                    j1939tbl_DumpPgn65252(this, pMsg, pEntry);
                    break;
                    
                case 65257:
                    j1939tbl_DumpPgn65257(this, pMsg, pEntry);
                    break;
                    
                case 65262:
                    j1939tbl_DumpPgn65262(this, pMsg, pEntry);
                    break;
                    
                case 65263:
                    j1939tbl_DumpPgn65263(this, pMsg, pEntry);
                    break;
                    
                case 65264:
                    j1939tbl_DumpPgn65264(this, pMsg, pEntry);
                    break;
                    
                case 65265:
                    j1939tbl_DumpPgn65265(this, pMsg, pEntry);
                    break;
                    
                case 65266:
                    j1939tbl_DumpPgn65266(this, pMsg, pEntry);
                    break;
                    
                case 65269:
                    j1939tbl_DumpPgn65269(this, pMsg, pEntry);
                    break;
                    
                case 65270:
                    j1939tbl_DumpPgn65270(this, pMsg, pEntry);
                    break;
                    
                case 65271:
                    j1939tbl_DumpPgn65271(this, pMsg, pEntry);
                    break;
                    
                case 65272:
                    j1939tbl_DumpPgn65272(this, pMsg, pEntry);
                    break;
                    
                case 65276:
                    j1939tbl_DumpPgn65276(this, pMsg, pEntry);
                    break;
                    
                case 65279:
                    j1939tbl_DumpPgn65279(this, pMsg, pEntry);
                    break;
                    
                default:
                    break;
            }
            
            // Return to caller.
            return false;
        }
        
        
        
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939TBL_DATA *   j1939tbl_Init(
        J1939TBL_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(J1939TBL_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_J1939TBL );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939tbl_Vtbl);
        
        this->pFileOut = stderr;

    #ifdef NDEBUG
    #else
        if( !j1939tbl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

        //---------------------------------------------------------------
        //                     E x t r a c t  S P N
        //---------------------------------------------------------------
        
        bool            j1939tbl_extractSPN512(
            J1939TBL_DATA   *this,
            J1939_MSG       *pMsg
        )
        {
            const
            J1939_PGN_ENTRY *pPgnEntry = &pgn61444_entry;
            const
            J1939_SPN       *pSpn = &spn512;
            J1939_PDU       pdu;
            J1939_PGN       pgn;
            int             i;
            
#ifdef NDEBUG
#else
            if( !j1939tbl_Validate( this ) ) {
                DEBUG_BREAK();
            }
#endif

            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);

            
            
            //this->priority = value;
            return true;
        }
        
        
        
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939tbl_Validate(
        J1939TBL_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_J1939TBL) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(J1939TBL_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


