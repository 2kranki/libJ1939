// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939can_internal.h
 *	Generated 04/06/2017 16:09:16
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



#include    "j1939can.h"


#ifndef J1939CAN_INTERNAL_H
#define	J1939CAN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct j1939can_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA            super;
    OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT             eRc;
    uint16_t            size;		/* maximum number of elements           */
    uint16_t            reserved;
    ASTR_DATA           *pStr;

    /* ReflectMsg() is the routine called to transmit an 8-byte
     * message. All messages must be sent via this routine.
     */
    bool                fReflect;
    P_XMTMSG_RTN        pReflectMsg;
    OBJ_PTR             pReflectData;
    
    /* XmtMsg() is the routine called to transmit an 8-byte
     * message. All messages must be sent via this routine.
     */
    P_XMTMSG_RTN        pXmtMsg;
    OBJ_PTR             pXmtData;
    
};
#pragma pack(pop)

    extern
    const
    struct j1939can_class_data_s  j1939can_ClassObj;

    extern
    const
    J1939CAN_VTBL         j1939can_Vtbl;


    // Internal Functions
    void            j1939can_Dealloc(
        OBJ_ID          objId
    );

    bool            j1939can_setLastError(
        J1939CAN_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			j1939can_Validate(
        J1939CAN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* J1939CAN_INTERNAL_H */

