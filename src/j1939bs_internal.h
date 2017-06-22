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
    J1939CA_DATA    super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;

    uint32_t        curTime;
    uint32_t        tsc1Time;
    uint32_t        startTime0;
    uint32_t        ebc1Time;
    uint32_t        startTime61441;

    uint8_t         spnFirst;
    uint8_t         spn518;         // Requested Torque / Torque Limit
    //                              // offset: -125%, -125 to 125 (0 - 250)
    uint8_t         spn695;         // Override Control Mode
    //                              // 0 - Disable override by the source of msg
    //                              // 1 - Override speed
    //                              // 2 - Override torque
    //                              // 3 - Limit Speed/Torque
    uint8_t         spn696;         // Requested Speed Control Conditions
    uint8_t         spn897;         // Override Control Mode Priority
    //                              // 0 == Highest Priority
    //                              // 3 == Lowest Priority
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

    void *          j1939bs_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
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
    
    bool            j1939bs_TransmitPgn0(
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

