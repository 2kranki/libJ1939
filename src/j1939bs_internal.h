// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939bs_internal.h
 *	Generated 06/21/2017 16:25:20
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




#include    <j1939bs.h>
#include    <j1939ca_internal.h>


#ifndef J1939BS_INTERNAL_H
#define	J1939BS_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct j1939bs_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    J1939CA_DATA        super;
    OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT             eRc;

    uint32_t            curTime;
    J1939CA_TIME_DELAY  time61441;
    J1939CA_TIME_DELAY  time64964;
    J1939CA_TIME_DELAY  time65215;

    uint8_t         spnFirst;
    uint8_t         spn518;         // Requested Torque / Torque Limit
    //                              // offset: -125%, -125 to 125
    //                              // 0 - +125% == engine torque requests
    //                              // -125% - 0 == for retarder torque requests
    uint8_t         spn521;         // Brake Pedal Position
    // Ratio of brake pedal position to maximum pedal position. Used for electric brake
    // applications. 0% means no braking. Also when there are two brake pedals on the
    // machine (Left Brake Pedal Position SPN 3033 and Right Brake Pedal Position SPN
    // 3032) the maximum of the two should be transmitted for Brake Pedal Position.
    //                              // mult: 0.4% per bit  offset: 0
    //                              // range: 0 to 100 %
    uint8_t         spn561;         // ASR Engine Control Active (2 bits)
    // State signal which indicates that ASR engine control has been commanded to be
    // active. Active means that ASR actually tries to control the engine. This state
    // signal is independent of other control commands to the engine (e.g., from the
    // transmission) which may have higher priority.
    //                              // 00 - ASR engine control passive but installed
    //                              // 01 - ASR engine control active
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn562;         // ASR Brake Control Active
    // State signal which indicates that ASR brake control is active. Active means that
    // ASR actually controls wheel brake pressure at one or more wheels of the driven
    // axle(s).
    //                              // 00 - ASR brake control passive but installed
    //                              // 01 - ASR brake control active
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn563;         // Anti-Lock Braking (ABS) Active (2 bits)
    // State signal which indicates that the ABS is active. The signal is set active when
    // wheel brake pressure actually starts to be modulated by ABS and is reset to passive
    // when all wheels are in a stable condition for a certain time. The signal can also
    // be set active when driven wheels are in high slip (e.g., caused by retarder).
    // Whenever the ABS system is not fully operational (due to a defect or during off-
    // road ABS operation) , this signal is only valid for that part of the system that
    // is still working. When ABS is switched off completely, the flag is set to passive
    // regardless of the current wheel slip conditions.
    //                              // 00 - ABS passive but installed
    //                              // 01 - ABS active
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn575;         // ABS Off-road Switch (2 bits)
    // Switch signal which indicates the position of the ABS off-road switch.
    //                              // 00 - ABS off-road switch passive
    //                              // 01 - ABS off-road switch active
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn576;         // ASR Off-road Switch (2 bits)
    // Switch signal which indicates the position of the ASR off-road switch.
    //                              // 00 - ASR off-road switch passive
    //                              // 01 - ASR off-road switch active
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn577;         // ASR 'Hill Holder' Switch (2 bits)
    // Switch signal which indicates the position of the ASR “hill holder” switch.
    //                              // 00 - ASR “hill holder” switch passive
    //                              // 01 - ASR “hill holder” switch active
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn695;         // Override Control Mode
    //                              // 0 - Disable override by the source of msg
    //                              // 1 - Override speed
    //                              // 2 - Override torque
    //                              // 3 - Limit Speed/Torque
    uint8_t         spn696;         // Requested Speed Control Conditions
    // This mode tells the engine control system the governor characteristics that
    // are desired during speed control. The four characteristics defined are:
    // (2 bits)
    //  00 - This speed governor gain selection is adjusted to provide rapid transition
    //          between speed setpoints. RPM overshoot and undershoot may be greater
    //          than what is seen when the “speed control characteristic” is set to be
    //          stability optimized.
    //  01 - This control condition has been optimized to minimize rpm overshoot and
    //          undershoot given an expected plant consisting of the engine and its ac-
    //          cessory loads. This gain adjustment is not intended to compensate for
    //          driveline characteristics. This characteristic is most appropriate when
    //          no driveline is connected.
    //  10 - This control condition has been optimized to minimize rpm overshoot and
    //          undershoot given a more complex plant. For instance, the more complex
    //          plant would contain the engine, its accessory loads and the driveline
    //          characteristics. As an example, the driveline characteristics might
    //          include the effective spring mass relationship of pumps, tires, clutches,
    //          axles, driveshafts, and multiple gear ratios. This characteristic is
    //          most appropriate when a driveline is engaged.
    //  11 - This speed control characteristic is available for applications requiring
    //          compensation for more than one driveline characteristic. It has been
    //          optimized to minimize rpm overshoot and undershoot given a more complex
    //          plant of the second variety. This more complex plant would again contain
    //          the engine, its accessory loads and a second driveline characteristic
    //          unique from the one described in speed control characteristic 10b.
    uint8_t         spn897;         // Override Control Mode Priority
    // This field is used as an input to the engine or retarder to determine the priority
    // of the Override Control Mode received in the Torque/Speed Control message (see PGN
    // 0). The default is 11 (Low priority). It is not required to use the same priority
    // during the entire override function. For example, the transmission can use priority
    // 01 (High priority) during a shift, but can set the priority to 11 (Low priority)
    // at the end of the shift to allow traction control to also interact with the torque
    // limit of the engine.
    // (2 bits)
    //  00 - Highest priority
    //  01 - High priority
    //  10 - Medium priority
    //  11 - Low priority
    uint8_t         spn905;         // Relative Speed; Front Axle, Left Wheel
    // The speed of the front axle, left wheel relative to the front axle speed, SPN 904.
    // mult: 1/16 km/h per bit, offset:  -7.8125 km/h
    // range: -7.8125 km/h to 7.8125 km/h
    uint8_t         spn906;         // Relative Speed; Front Axle, Right Wheel
    // The speed of the front axle, right wheel relative to the front axle speed, SPN 904.
    // mult: 1/16 km/h per bit, offset:  -7.8125 km/h
    // range: -7.8125 km/h to 7.8125 km/h
    uint8_t         spn907;         // Relative Speed;  Rear Axle #1, Left Wheel
    // The speed of the  Rear Axle #1, left wheel relative to the front axle speed, SPN 904.
    // mult: 1/16 km/h per bit, offset:  -7.8125 km/h
    // range: -7.8125 km/h to 7.8125 km/h
    uint8_t         spn908;         // Relative Speed;  Rear Axle #1, Right Wheel
    // The speed of the  Rear Axle #1, right wheel relative to the front axle speed, SPN 904.
    // mult: 1/16 km/h per bit, offset:  -7.8125 km/h
    // range: -7.8125 km/h to 7.8125 km/h
    uint8_t         spn909;         // Relative Speed;  Rear Axle #2, Left Wheel
    // The speed of the  Rear Axle #2, left wheel relative to the front axle speed, SPN 904.
    // mult: 1/16 km/h per bit, offset:  -7.8125 km/h
    // range: -7.8125 km/h to 7.8125 km/h
    uint8_t         spn910;         // Relative Speed;  Rear Axle #2, Right Wheel
    // The speed of the  Rear Axle #2, right wheel relative to the front axle speed, SPN 904.
    // mult: 1/16 km/h per bit, offset:  -7.8125 km/h
    // range: -7.8125 km/h to 7.8125 km/h
    uint8_t         spn969;         // Remote Accelerator Enable Switch (2 bits)
    // Switch signal which indicates that the remote accelerator has been enabled and
    // controls the engine.  NOTE — The accelerator interlock switch (see SPN 972) must
    // be disabled in order for the remote accelerator to perform engine control.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Error
    //                              // 11 - Not available
    uint8_t         spn970;         // Engine Auxiliary Shutdown Switch (2 bits)
    // Switch signal which requests that all engine fueling stop.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Error
    //                              // 11 - Not available
    uint8_t         spn971;         // Engine Derate Switch (2 bits)
    // Switch signal used to activate the torque limiting feature of the engine. The
    // specific nature of torque limiting should be verified with the manufacturer.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Error
    //                              // 11 - Not available
    uint8_t         spn972;         // Accelerator Interlock Switch (2 bits)
    // Switch signal used to disable the accelerator and remote accelerator inputs,
    // causing the engine to return to idle.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Error
    //                              // 11 - Not available
    uint8_t         spn973;         // Engine Retarder Selection
    // The position of the operator controlled selector, expressed as a percentage and
    // determined by the ratio of the current position of the selector to its maximum
    // possible position. Zero percent means no braking torque is requested by the
    // operator from the engine while 100% means maximum braking.
    //                              // mult: 0.4% per bit  offset: 0
    //                              // range: 0 to 100 %
    uint8_t         spn1121;        // EBS Brake Switch (2 bits)
    // Switch signal which indicates that the brake pedal is being pressed. The EBS brake
    // switch is independent of the brake light switch and has no provisions for external
    // connections.
    //                              // 00 - Brake pedal is not being pressed
    //                              // 01 - Brake pedal is being pressed
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn1238;        // Traction Control Override Switch (2 bits)
    // Switch signal which indicates the position of the traction control override switch.
    // The traction control override signal disables the automatic traction control func-
    // tion allowing the wheels to spin.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Error
    //                              // 11 - Not available
    uint8_t         spn1438;        // ABS/EBS Amber Warning Signal (Powered Vehicle)
    // This parameter commands the ABS/EBS amber/yellow optical warning signal.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn1439;        // EBS Red Warning Signal (2 bits)
    // This parameter commands the EBS red optical warning signal.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn1243;        // ABS Fully Operational (2 bits)
    // Signal which indicates whether an ABS system is fully operational or whether its
    // functionality is reduced by a defect or by an intended action (e.g., by activation
    // of an ABS-off-road switch or during special diagnostic procedures). There are cases
    // where the signal is necessary to fulfill legal regulations for special applications
    // (e.g., switching off integrated retarders).
    //                              // 00 - Not Fully Operational
    //                              // 01 - Fully Operational
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn1481;        // Source Address of Controlling Device for Brake
    //                              // Control
    uint8_t         spn1792;        // Tractor-Mounted Trailer ABS Warning Signal
    // This parameter commands the tractor-mounted trailer ABS optical warning signal.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn1793;        // ATC/ASR Information Signal
    // This parameter commands the ATC/ASR driver information signal, for example a dash
    // lamp.
    //                              // 00 - Off
    //                              // 01 - On
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn1836;        // Trailer ABS Status (2 bits)
    // State signal which indicates that ABS in the trailer is actively controlling the
    // brakes. A message is sent to the tractor from the trailer (i.e. by PLC). The
    // receiving device in the tractor transfers this information to the J1939 network.
    // At the beginning of power on the message is sent by the trailer to indicate if
    // this status information is supported. Timeout of the trailer ABS active can be
    // done by monitoring of the Trailer warning light information.
    //                              // 00 - Trailer ABS Status Information Available But Not Active
    //                              // 01 - Trailer ABS Active
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn2911;        // Halt brake switch (2 bits)
    // Switch signal which indicates the position of the halt brake switch.
    //                              // 00 - Halt brake switch passive
    //                              // 01 - Halt brake switch active
    //                              // 10 - Error
    //                              // 11 - Not available
    uint8_t         spn2912;        // Hill holder mode (3 bits)
    // Signal which indicates the current mode of the hill holder function.
    //                              // 000 - Inactive
    //                              // 001 - Active
    //                              // 010 - Active, but will change to inactive in a
    //                              //      short time. (This mode may be used to warn
    //                              //      the driver)
    //                              // 011 - Active, but will change to inactive in a
    //                              //      short time. (This mode may be used to warn
    //                              //      the driver)
    //                              // 101 - 101 Not defined
    //                              // 110 - Reserved
    //                              // 111 - Not available
    uint8_t         spn2913;        // Halt brake mode (3 bits)
    // Signal which indicates the current mode of the halt brake function.
    //                              // 000 - Inactive
    //                              // 001 - Active
    //                              // 010 - Active, but not functioning properly
    //                              //       (This mode may be used to warn the driver)
    //                              // 011 - 101 Not Defined
    //                              // 110 - Reserved
    //                              // 111 - Not available
    uint8_t         spn2917;        // XBR System State (2 bits)
    // This parameter indicates which external brake control is allowed.
    //                              // 00 - Any external brake demand will be accepted
    //                              //      (brake system fully operational)
    //                              // 01 - Only external brake demand of highest XBR
    //                              //      Priority (00) will be accepted (e.g. because
    //                              //      the temperature limit of the brake system is
    //                              //      exceeded)
    //                              // 10 - No external brake demand will be accepted
    //                              //      (e.g. because of fault in brake system)
    //                              // 11 - Not Available
    uint8_t         spn2918;        // XBR Active Control Mode (4 bits)
    // This parameter indicates which XBR Control Mode is executed by the brake system.
    //                              // 0000 - No brake demand being executed (default mode)
    //                              // 0001 - Driver's brake demand being executed,
    //                              //          no external brake demand
    //                              // 0010 - Addition mode of XBR acceleration control
    //                              //          being executed
    //                              // 0011 - Maximum mode of XBR acceleration control
    //                              //          being executed
    //                              // 0100 - 1110 - Reserved for SAE Assignment
    //                              // 1111 - Not available
    uint8_t         spn2919;        // Foundation Brake Use (2 bits)
    // This parameter indicates if the brake system presently uses the foundation brakes.
    //                              // 00 - Foundation brakes not in use
    //                              // 01 - Foundation brakes in use
    //                              // 10 - Reserved
    //                              // 11 - Not available
    uint8_t         spn2921;        // XBR Acceleration Limit
    // The brake system may temporarily or generally limit the maximum brake performance
    // available for external systems. A temporary limit may be nessary due to high brake
    // temperature; a general limit may be defined by the vehicle manufacturer, e.g. a
    // value of -2.5 m/s2 due to liability reasons. The actual limit is communicated to
    // the external systems that request braking. The limit is only effective in the XBR
    // Priorities 01 to 11. It is specified as an absolute acceleration in reference to
    // the road.
    //                              // 8 bits, mult: 0.1 m/s2 per bit  offset: -12.5 m/s2
    //                              // data range: -12.5 m/s2 to +12.5 m/s2
    //                              // operational range: -10.0 to +10.0 m/s2
    uint8_t         spn3349;        // TSC1 Transmission Rate
    //                              // 000 - 1000 ms transmission rate
    //                              // 001 -  750 ms transmission rate
    //                              // 010 -  500 ms transmission rate
    //                              // 011 -  250 ms transmission rate
    //                              // 100 -  100 ms transmission rate
    //                              // 101 -   50 ms transmission rate
    //                              // 110 -   20 ms transmission rate
    //                              // 111 -   10 ms transmission rate (default)
    uint8_t         spn3350;        // TSC1 Control Purpose
    //                              // 00000 - Accelerator Pedal/Operator Selection
    //                              // 00001 - Cruise Control
    //                              // 00010 - PTO Governor
    //                              // 00011 - Road Speed Governor
    //                              // 00100 - Engine Protector
    //                              // 00101 - Reserved by SAE
    //                              //   |
    //                              // 11110
    //                              // 11111 - Temporary Power Train Control
    uint8_t         rsvd8[1];

    uint16_t        spn898;         // Requested Speed / Speed Limit
    // Parameter provided to the engine from external sources in the torque/speed control
    // message. This is the engine speed which the engine is expected to operate at if
    // the speed control mode is active or the engine speed which the engine is not
    // expected to exceed if the speed limit mode is active.
    //                              // mult: 0.125 rpm per bit, offset: 0
    //                              // range: 0 to 8,031.875 rpm
    uint16_t        spn904;         // Front Axle Speed
    // The average speed of the two front wheels.
    //                              // mult: 1/256 km/h per bit, offset: 0
    //                              // range: 0 to 250.996 km/h
    uint16_t        rsvd16;
    
    uint32_t        spnLast;

};
#pragma pack(pop)

    extern
    const
    struct j1939bs_class_data_s  j1939bs_ClassObj;

    extern
    const
    J1939BS_VTBL         j1939bs_Vtbl;


    // Internal Functions
    void            j1939bs_Dealloc(
        OBJ_ID          objId
    );

    
    bool            j1939bs_HandlePgn61441(
        J1939BS_DATA    *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );
    
    
    bool            j1939bs_HandlePgn64964(
        J1939BS_DATA    *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );
    
    
    bool            j1939bs_HandlePgn65215(
        J1939BS_DATA    *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    );
    
    
    void *          j1939bs_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    bool            j1939bs_setLastError(
        J1939BS_DATA     *this,
        ERESULT         value
    );


    int             j1939bs_SetupPgn0(
        J1939BS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );

    
    int             j1939bs_SetupPgn61441(
        J1939BS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939bs_SetupPgn64964(
        J1939BS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939bs_SetupPgn65215(
        J1939BS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    bool            j1939bs_TransmitPgn0(
        J1939BS_DATA	*this
    );


    bool            j1939bs_TransmitPgn61441(
        J1939BS_DATA	*this
    );
    
    
    bool            j1939bs_TransmitPgn64964(
        J1939BS_DATA	*this
    );
    
    
    bool            j1939bs_TransmitPgn65215(
        J1939BS_DATA	*this
    );
    
    
#ifdef NDEBUG
#else
    bool			j1939bs_Validate(
        J1939BS_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* J1939BS_INTERNAL_H */

