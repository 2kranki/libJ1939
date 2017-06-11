// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939cu_internal.h
 *	Generated 04/13/2017 20:44:32
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




#include    <j1939cu.h>
#include    <j1939cam.h>
#include    <trace.h>
#include    <consumer.h>



#ifndef J1939CU_INTERNAL_H
#define	J1939CU_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct j1939cu_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    J1939CAM_DATA   *pCam;
    OBJ_DATA        *pSYS;
    OBJ_DATA        *pCAN;
    CONSUMER_DATA   *pConsumer;     // Input Message Queue
    
    uint32_t        spn2837;        // J1939 Identity Number (21 bits)
    uint16_t        spn2838;        // J1939 Manufacturer Code (11 bits)
    uint8_t         spn2846;        // J1939 Industry Group (3 bits)
    uint8_t         rsvd8[1];
    
    int             (*pMsgFilter)(void *, void *);
    void            *pMsgFilterData;

};
#pragma pack(pop)

    extern
    const
    struct j1939cu_class_data_s  j1939cu_ClassObj;

    extern
    const
    J1939CU_VTBL         j1939cu_Vtbl;


    // Internal Functions
    void            j1939cu_Dealloc(
        OBJ_ID          objId
    );

    bool            j1939cu_setLastError(
        J1939CU_DATA     *this,
        ERESULT         value
    );





#ifdef	__cplusplus
}
#endif

#endif	/* J1939CU_INTERNAL_H */

