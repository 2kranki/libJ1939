// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939ss_internal.h
 *	Generated 04/08/2017 00:51:45
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




#include    <j1939ss.h>
#include    <j1939ca_internal.h>


#ifndef J1939SS_INTERNAL_H
#define	J1939SS_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct j1939ss_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    J1939CA_DATA        super;
    OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT             eRc;
    
    uint32_t            curTime;
    J1939CA_TIME_DELAY  time57344;

    uint8_t             spnFirst;
    uint8_t             spn518;             // Engine Requested Torque/Torque Limit
    // Parameter provided to the engine or retarder in the torque/speed control
    // message for controlling or limiting the output torque.
    // Requested torque to the engine is measured in indicated torque as a percentage
    // of reference engine torque (see the engine configuration message, PGN 65251).
    // This is the engine torque at which the engine is expected to operate if the
    // torque control mode is active or the engine torque which the engine is not
    // expected to exceed if the torque limit mode is active.
    // Zero torque can be requested which implies zero fuel and, according to Figures
    // SPN512_A and SPN512_B, the engine will not be allowed to stall. The actual
    // engine percent torque (SPN 513) should be zero and the engine should decelerate
    // until the low idle governor kicks in, at which time the actual engine percent
    // torque will be calculated as shown in Figures SPN512_A and SPN512_B and the
    // engine torque mode bits (SPN 899) should be equal to 0000b - Low Idle Governor.
    // Requested torque to the retarder is measured in indicated torque as a percen-
    // tage of reference retarder torque (see the retarder configuration message,
    // PGN 65249). The logic used in enabling or disabling the retarder is based on
    // the override control mode priority bits (SPN 897).
    // A zero torque request to the retarder is a disable request, and is used by a
    // J1939 node to prevent the retarder from being activated by other combinations
    // of inputs outside of J1939 commands. The Torque Limit Mode is commonly used
    // for this purpose.
    // mult: 1 % per bit  offset: -125 %
    // range: -125 to 125 %
    // operational: 0 to 125%  for engine torque requests,
    //              -125% to 0% for retarder torque requests
    uint8_t             spn695;             // Engine Override Control Mode
    // The override control mode defines which sort of command is used:
    // (2 bits)
    //  00 - Override disabled - Disable any existing control commanded by the
    //      source of this command.
    //  01 - Speed control - Govern speed to the included “desired speed” value.
    //  10 - Torque control - Control torque to the included “desired torque” value.
    //  11 - Speed/torque limit control - Limit speed and/or torque based on the
    //      included limit values. The speed limit governor is a droop governor
    //      where the speed limit value defines the speed at the maximum torque
    //      available during this operation.
    uint8_t             spn696;             // Engine Requested Speed Control Conditions
    // (2 bits)
    //  00 - Transient Optimized for driveline disengaged and non-lockup conditions
    //  01 - Stability Optimized for driveline disengaged and non-lockup conditions
    //  10 - Stability Optimized for driveline engaged and/or in lockup condition 1
    //      (e.g., vehicle driveline)
    //  11 - Stability Optimized for driveline engaged and/or in lockup condition 2
    //      (e.g., PTO driveline)
    uint8_t             spn897;             // Override Control Mode Priority
    // This field is used as an input to the engine or retarder to determine the
    // priority of the Override Control Mode received in the Torque/Speed Control
    // message (see PGN 0). The default is 11 (Low priority). It is not required
    // to use the same priority during the entire override function. For example,
    // the transmission can use priority 01 (High priority) during a shift, but can
    // set the priority to 11 (Low priority) at the end of the shift to allow trac-
    // tion control to also interact with the torque limit of the engine.
    // (2 bits)
    //  00 - Highest priority
    //  01 - High priority
    //  10 - Medium priority
    //  11 - Low priority
    uint8_t             spn1849;            // Transmission Requested Range Display
    // Flash State
    // State signal indicating a transmission request for the display of the Trans-
    // mission Requested Range parameter (SPN 162) to flash or not to flash. The
    // ‘Transmission Requested Range Display Flash State’ indicator can be utilized
    // by (but not limited to) the shift console, instrument cluster, or cab display.
    // Definition of the cause of this state is at the discretion of the transmission
    // manufacturer. The flash period shall be 700 ms @ 50% duty cycle.
    // Transmission manufacturers may want to flash the Transmission Requested Range
    // display depending on certain events. It could be because a gear could not be
    // attained, or because fluid is low, etc. Indicator should be on for 350 ms and
    // off for 350 ms.
    // Transmissions supporting both this parameter and the Transmission Requested
    // Range Display Blank State should treat the active states of these parameters
    // as mutually exclusive; both parameters should not indicate "active" at the
    // same time.
    // (2 bits)
    //  00 - Inactive; Transmission Requested Range display should not be flashing
    //  01 - Active; Transmission Requested Range display should be flashing
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn1850;            // Transmission Requested Range Display
    // Blank State
    // State signal indicating a transmission request for the display of the Trans-
    // mission Requested Range parameter (SPN162) to be blanked or not blanked. The
    // ‘Transmission Requested Range Display Blank State’ indicator can be utilized
    // by (but not limited to) the shift console, instrument cluster, or cab display.
    // Definition of the cause of this state is at the discretion of the transmission
    // manufacturer.
    // Transmission manufacturers may want to blank the Transmission Requested Range
    // display depending on certain events. Typically it is an indication of a shift
    // selector problem.
    // Transmissions supporting both this parameter and the Transmission Requested
    // Range Display Flash State should treat the active states of these parameters
    // as mutually exclusive; both parameters should not indicate "active" at the
    // same time.
    // (2 bits)
    //  00 - Inactive; Transmission Requested Range display should not be blanked
    //  01 - Active; Transmission Requested Range display should be blanked
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn1851;            // Transmission Shift Inhibit Indicator
    // State signal indicating a transmission request for the Shift Inhibit Indicator
    // to be active or inactive. The shift inhibit indicator can be of lamp or text
    // form, located on (but not limited to) the shift console, instrument cluster,
    // or cab display. Definition of the cause of the ‘range inhibit’ state is at
    // the discretion of the transmission manufacturer.
    // Transmission manufacturers may want to indicate that they currently cannot
    // make a requested shift. This could be due to inappropriate vehicle speed or
    // other restrictions.
    // (2 bits)
    //  00 - Inactive; shift is not inhibited
    //  01 - Active; shift is inhibited
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn2536;            // Transmission Mode 1 Indicator
    // This state signal is the transmission’s indication that it is operating under
    // transmission mode 1 (SPN 1852) as commanded via the TC1 message (PGN 256).
    // The definition of the transmission mode is left to the discretion of the
    // transmission manufacturer.
    // (2 bits)
    //  00 - Transmission Mode 1 not active
    //  01 - Transmission Mode 1 active
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn2537;            // Transmission Mode 2 Indicator
    // This state signal is the transmission’s indication that it is operating under
    // transmission mode 2 (SPN 1853) as commanded via the TC1 message (PGN 256).
    // The definition of the transmission mode is left to the discretion of the
    // transmission manufacturer.
    // (2 bits)
    //  00 - Transmission Mode 2 not active
    //  01 - Transmission Mode 2 active
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn2538;            // Transmission Mode 3 Indicator
    // This state signal is the transmission’s indication that it is operating under
    // transmission mode 3 (SPN 1854) as commanded via the TC1 message (PGN 256).
    // The definition of the transmission mode is left to the discretion of the
    // transmission manufacturer.
    // (2 bits)
    //  00 - Transmission Mode 3 not active
    //  01 - Transmission Mode 3 active
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn2539;            // Transmission Mode 4 Indicator
    // This state signal is the transmission’s indication that it is operating under
    // transmission mode 4 (SPN 1855) as commanded via the TC1 message (PGN 256).
    // The definition of the transmission mode is left to the discretion of the
    // transmission manufacturer.
    // (2 bits)
    //  00 - Transmission Mode 4 not active
    //  01 - Transmission Mode 4 active
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn2900;            // Transmission Engine Crank Enable
    // State signal from the transmission indicating if the transmission’s status is
    // such that engine cranking is allowed (i.e. at a minimum, transmission is in
    // neutral and the driveline is disengaged). As sender of this information, the
    // transmission is responsible for correct indication immediately upon first
    // broadcast of this parameter.
    // As with hard-wired neutral start implementations, those utilizing this para-
    // meter should consider the impact of the transmission or other controllers
    // ‘resetting’ due to voltage drops during the engine start sequence.
    // The vehicle system design should also consider the impact of timing latency
    // in the engine starting sequence. For example, the turn of an ignition key from
    // ‘off’ to ‘start’ may happen more quickly than the transmission controller can
    // boot up, determine its’ current state of being, and begin broadcasting informa-
    // tion over the J1939 datalink.
    // (2 bits)
    //  00 - Cranking disabled; engine cranking is prohibited by the transmission
    //  01 - Cranking enabled; engine cranking is allowed by the transmission
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn2945;            // Active Shift Console Indicator
    // Signal from transmission control unit indicating which shift console (primary
    // or secondary) it currently considers as the active shift selector input.
    // Note: In some applications such as refuse trucks, the transmission can be
    // operated from two positions in the vehicle. The transmission control unit
    // will accept changes in transmission requested gear (SPN 525) from the operator
    // only from the active shift console. The transmission control unit determines
    // which shift console is active based on a switch input controlled by the
    // operator and transmission system state criteria.
    // (2 bits)
    //  00 - Primary shift console is active
    //  01 - Secondary shift console is active
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn3086;            // Transmission Ready for Brake Release
    // This parameter indicates that enough torque / motive force is available at the
    // transmission output shaft to release all the brakes without a risk of unin-
    // tentional movement in the opposite direction.
    // (2 bits)
    //  00 - Transmission Not Ready for Brake Release
    //  01 - Transmission Ready for Brake Release
    //  10 - Reserved
    //  11 - Not available
    uint8_t             spn3289;            // Transmission Requested Gear Feedback
    // Feedback of the SPN 525 Transmission Requested Gear input as received from the
    // shift selector, ABS or engine via PGN 256, Transmission Control #1 (TC1).
    // Scaling, values and parameter specific indicators are identical to those
    // listed for SPN 525 Transmission Requested Gear.
    // This feedback from the transmission allows shift selectors and other TC1 input
    // devices to verify that their Transmission Requested Gear command has been
    // properly received by the transmission. (This parameter is not intended for
    // driver display purposes).
    // mult: 1 gear value per bit, offset: -125
    // range: -125 to 125
    uint8_t             spn3349;            // TSC1 Transmission Rate
    // This parameter indicates the transmission rate at which the sending device
    // will transmit the TSC1 message. The engine shall adjust its timeout for TSC1
    // messages accordingly. Variable TSC1 transmission rates shall only apply to
    // messages sent to the engine.
    // A value of all ones is to be used in TSC1 messages directed to retarders
    // because the TSC1 Transmission Rate parameter is not applicable for retarders.
    // All TSC1 messages sent to the retarder shall use the standard 50 ms rate.
    // Devices sending TSC1 messages to the engine should only invoke alternative
    // transmission rates which the engine has indicated it supports in SPN 3344 –
    // Support Variable Rate TSC1 Message.
    // (3 bits)
    //  000 = 1000 ms transmission rate
    //  001 = 750 ms transmission rate
    //  010 = 500 ms transmission rate
    //  011 = 250 ms transmission rate
    //  100 = 100 ms transmission rate
    //  101 = 50 ms transmission rate
    //  110 = 20 ms transmission rate
    //  111 = Use standard TSC1 transmission rates of 10 ms to engine
    uint8_t             spn3350;            // TSC1 Control Purpose
    // State signal which indicates which control mode the sending device is using to
    // generate the TSC1 command. Note that the modes are not in prioritized order.
    // Not all modes may be relevant for a given device. Some devices may not im-
    // plement all functions. For typical priorities refer to Figures SPN512_A,
    // SPN512_B for engine control and Figure SPN695_A. The TSC1 control purpose
    // shall only apply to messages sent to the engine.
    // A value of all ones is to be used in TSC1 messages directed to retarders
    // because the TSC1 Control Purpose parameter is not applicable for retarders.
    // (5 bits)
    //  00000 - P1 - Acelerator Pedal/Operator Selection
    //  00001 - P2 - Cruise Control
    //  00010 - P3 - PTO Governor
    //  00011 - P4 - Road Speed Governor
    //  00100 - P5 - Engine Protection
    //  00101 - P6 - Reserved
    //    |      |
    //  11110 - P31 - Reserved
    //  11111 - P32 - Temporary Power Train Control (Original use of TSC1 Command)
    uint8_t             rsvd8[2];

    uint16_t            spn898;         // Requested Speed / Speed Limit
    // Parameter provided to the engine from external sources in the torque/speed
    // control message. This is the engine speed which the engine is expected to
    // operate at if the speed control mode is active or the engine speed which
    // the engine is not expected to exceed if the speed limit mode is active.
    //                              // mult: 0.125 rpm per bit, offset: 0
    //                              // range: 0 to 8,031.875 rpm
    uint16_t            rsvd16[1];
    
    uint32_t            spnLast;

};
#pragma pack(pop)

    extern
    const
    struct j1939ss_class_data_s  j1939ss_ClassObj;

    extern
    const
    J1939SS_VTBL         j1939ss_Vtbl;


    // Internal Functions
    void            j1939ss_Dealloc(
        OBJ_ID          objId
    );

    bool            j1939ss_HandlePgn65098(
        J1939SS_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    bool            j1939ss_HandleTimedTransmits(
        J1939SS_DATA	*this
    );
    
    int             j1939ss_SetupPgn0(
        J1939SS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    bool            j1939ss_setLastError(
        J1939SS_DATA     *this,
        ERESULT         value
    );

    bool            j1939ss_TransmitPgn0(
        J1939SS_DATA	*this
    );



#ifdef NDEBUG
#else
    bool			j1939ss_Validate(
        J1939SS_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* J1939SS_INTERNAL_H */

