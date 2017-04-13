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
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */



#include    <j1939ecu.h>


#ifndef J1939ECU_INTERNAL_H
#define	J1939ECU_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct j1939ecu_data_s	{
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




#ifdef NDEBUG
#else
    bool			j1939ecu_Validate(
        J1939ECU_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* J1939ECU_INTERNAL_H */

