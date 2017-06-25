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
    uint8_t             spn518;         // Requested Torque / Torque Limit
    //                                  // offset: -125%, -125 to 125 (0 - 250)
    uint8_t             spn695;         // Override Control Mode
    //                                  // 0 - Disable override by the source of msg
    //                                  // 1 - Override speed
    //                                  // 2 - Override torque
    //                                  // 3 - Limit Speed/Torque
    uint8_t             spn696;         // Requested Speed Control Conditions
    uint8_t             spn897;         // Override Control Mode Priority
    //                              // 0 == Highest Priority
    //                              // 3 == Lowest Priority
    uint16_t            spn898;         // Requested Speed / Speed Limit
    uint8_t             spn1849;        // Transmission Requested Range Display
    //                              // Flash State
    uint8_t             spn1850;        // Transmission Requested Range Display
    //                              // Blank State
    uint8_t             spn1851;        // Transmission Shift Inhibit Indicator
    uint8_t             spn2536;        // Transmission Mode 1 Indicator
    uint8_t             spn2537;        // Transmission Mode 2 Indicator
    uint8_t             spn2538;        // Transmission Mode 3 Indicator
    uint8_t             spn2539;        // Transmission Mode 4 Indicator
    uint8_t             spn2900;        // Transmission Engine Crank Enable
    uint8_t             spn2945;        // Active Shift Console Indicator
    uint8_t             spn3086;        // Transmission Ready for Brake Release
    uint8_t             spn3289;        // Transmission Requested Gear Feedback
    uint8_t             spn3349;        // TSC1 Transmission Rate
    //  000 - 1000 ms transmission rate
    //  001 -  750 ms transmission rate
    //  010 -  500 ms transmission rate
    //  011 -  250 ms transmission rate
    //  100 -  100 ms transmission rate
    //  101 -   50 ms transmission rate
    //  110 -   20 ms transmission rate
    //  111 -   10 ms transmission rate (default)
    uint8_t             spn3350;        // TSC1 Control Purpose
    //  00000 - Accelerator Pedal/Operator Selection
    //  00001 - Cruise Control
    //  00010 - PTO Governor
    //  00011 - Road Speed Governor
    //  00100 - Engine Protector
    //  00101 - Reserved by SAE
    //    |
    //  11110
    //  11111 - Temporary Power Train Control
    uint8_t             rsvd8;
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

