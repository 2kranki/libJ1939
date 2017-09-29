// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   truck_internal.h
 *	Generated 06/12/2017 20:11:38
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




#include    <truck.h>
#include    <msgBus.h>

#include    <j1939cam.h>

#include    <j1939cu.h>
#include    <j1939ccu.h>
#include    <j1939ecu.h>
#include    <j1939tcu.h>

#include    <j1939can.h>
#include    <j1939sys.h>


#ifndef TRUCK_INTERNAL_H
#define	TRUCK_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif

    
    // When we create a new CU, we must supply it with a CAN object
    // which is tied to the BUS.
    typedef struct cu_group_s {
        J1939CU_DATA        *pCU;
        J1939CAN_DATA       *pCAN;
    } CU_GROUP;
    
    
    


#pragma pack(push, 1)
struct truck_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;        // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    
    // Remember that each of these are separate tasks.
    CU_GROUP        cab;
    CU_GROUP        eng;
    CU_GROUP        xms;
    
    uint8_t         fParkingBrake;      // true == Parking Brake is applied
    uint8_t         fDriverPresent;     // true == Driver seat sensor detects driver
    uint8_t         rsvd8[2];
    uint16_t        accelPedal;         // Accelerator Pedal Percentage (0 - 99)
    uint16_t        reserved;
    uint32_t        fuelCapacity;       // Weight of tractor (l)
    uint32_t        fuelAmount;         // Weight of tractor (l)
    uint32_t        weightLoad;         // Weight of load (kg)
    uint32_t        weightTractor;      // Weight of tractor (kg)
    uint32_t        weightTrailer;      // Weight of trailer (kg)

    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    const
    struct truck_class_data_s  truck_ClassObj;

    extern
    const
    TRUCK_VTBL         truck_Vtbl;


    // Internal Functions
    void            truck_Dealloc(
        OBJ_ID          objId
    );

    void *          truck_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );


    bool            truck_setLastError(
        TRUCK_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			truck_Validate(
        TRUCK_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TRUCK_INTERNAL_H */

