// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939data_internal.h
 *	Generated 06/15/2017 10:10:23
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




#include    <j1939data.h>


#ifndef J1939DATA_INTERNAL_H
#define	J1939DATA_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct j1939data_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        size;		/* maximum number of elements           */
    uint16_t        reserved;
    ASTR_DATA       *pStr;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    struct j1939data_class_data_s  j1939data_ClassObj;

    extern
    const
    J1939DATA_VTBL         j1939data_Vtbl;


    // Internal Functions
    void            j1939data_Dealloc(
        OBJ_ID          objId
    );

    void *          j1939data_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );


    bool            j1939data_setLastError(
        J1939DATA_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			j1939data_Validate(
        J1939DATA_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* J1939DATA_INTERNAL_H */

