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
    uint8_t             spn69;              // Two Speed Axle Switch
    uint8_t             spn70;              // Parking Brake Switch
    uint8_t             spn74;              // Maximum Vehicle Speed Limit
    uint8_t             spn86;              // Cruise Control Set Speed
    uint8_t             spn87;              // Cruise Control High Set Limit Speed
    uint8_t             spn88;              // Cruise Control Low Set Limit Speed
    uint8_t             spn91;              // Accelerator Pedal Position 1
    uint8_t             spn92;              // Percent Load At Current Speed
    uint8_t             spn108;             // Barometric Pressure
    uint8_t             spn114;             // Net Battery Current
    uint8_t             spn115;             // Alternator Current
    uint8_t             spn172;             // Engine Air Inlet Temperature
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
    uint8_t             spn966;             // Engine Test Mode Switch
    uint8_t             spn967;             // Idle Decrement Switch
    uint8_t             spn968;             // Idle Increment Switch
    uint8_t             spn974;             // Remote Accelerator Pedal Position
    uint8_t             spn976;             // PTO State
    uint8_t             spn1237;            // Engine Shutdown Override Switch
    uint8_t             spn1437;            // Road Speed Limit Status
    uint8_t             spn1633;            // Cruise Control Pause Switch
    uint8_t             spn1675;            // Engine Starter Mode
    
    uint16_t            spn79;              // Road Surface Temperature
    uint16_t            spn84;              // Wheel-Based Vehicle Speed
    uint16_t            spn158;             // Battery Potential (Voltage), Switched
    uint16_t            spn167;             // Charging System Potential (Voltage)
    uint16_t            spn168;             // Electrical Potential (Voltage)
    uint16_t            spn170;             // Cab Interior Temperature
    uint16_t            spn171;             // Ambient Air Temperature
    
    uint32_t            spn917;             // High Resolution Total Vehicle Distance
    uint32_t            spn918;             // High Resolution Trip Distance
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

