// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939ecu_internal.h
 *	Generated 04/13/2017 15:27:23
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




#include    <j1939ecu.h>
#include    <j1939cu_internal.h>




#ifndef J1939ECU_INTERNAL_H
#define	J1939ECU_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif

    
    typedef struct eng_trq_hp_s {
        uint16_t        rpm;            // 0 == idle
        uint16_t        hp;             //
        uint16_t        torque;         // foot-lbs ???
    } ENG_TRQ_HP;


    
#pragma pack(push, 1)
struct j1939ecu_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    J1939CU_DATA    super;
    OBJ_IUNKNOWN    *pSuperVtbl;        // Needed for Inheritance

    // Current Criteria
    uint16_t        rpm;
    uint16_t        torque;
    uint16_t        hp;

};
#pragma pack(pop)

    extern
    const
    struct j1939ecu_class_data_s  j1939ecu_ClassObj;

    extern
    const
    J1939ECU_VTBL         j1939ecu_Vtbl;


    // Internal Functions
    void            j1939ecu_Dealloc(
        OBJ_ID          objId
    );

    bool            j1939ecu_setLastError(
        J1939ECU_DATA     *this,
        ERESULT         value
    );





#ifdef	__cplusplus
}
#endif

#endif	/* J1939ECU_INTERNAL_H */

