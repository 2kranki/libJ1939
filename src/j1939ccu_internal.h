// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939ccu_internal.h
 *	Generated 06/05/2017 08:35:58
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




#include    <j1939ccu.h>
#include    <j1939cu_internal.h>
#include    <j1939bs.h>
#include    <j1939cab.h>
#include    <j1939cc.h>
#include    <j1939ss.h>




#ifndef J1939CCU_INTERNAL_H
#define	J1939CCU_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct j1939ccu_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    J1939CU_DATA    super;
    OBJ_IUNKNOWN    *pSuperVtbl;        // Needed for Inheritance

    // Common Data
    J1939BS_DATA    *pBrake;
    J1939CAB_DATA   *pCab;
    J1939CC_DATA    *pCruise;
    J1939SS_DATA    *pShift;
    uint32_t        rpm;
    void            (*pRpmRoutine)(void *, uint32_t);
    void            *pRpmData;

};
#pragma pack(pop)

    extern
    const
    struct j1939ccu_class_data_s  j1939ccu_ClassObj;

    extern
    const
    J1939CCU_VTBL         j1939ccu_Vtbl;


    // Internal Functions
    void            j1939ccu_Dealloc(
        OBJ_ID          objId
    );


    ERESULT         j1939ccu_NewRpm(
        J1939CCU_DATA	*this,
        uint32_t        rpm
    );
    
    
    void *          j1939ccu_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );


    bool            j1939ccu_setLastError(
        J1939CCU_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			j1939ccu_Validate(
        J1939CCU_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* J1939CCU_INTERNAL_H */

