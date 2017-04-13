// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'j1939ecu'
//	Generated 04/13/2017 15:27:23


/*
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */


#define			J1939ECU_OBJECT_C	    1
#include        "j1939ecu_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct j1939ecu_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct j1939ecu_class_data_s J1939ECU_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        j1939ecu_Info;            // Forward Reference



OBJ_ID          j1939ecu_Class(
    OBJ_ID          objId
);



static
bool            j1939ecu_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939ECU_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		obj_ClassWhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_J1939ECU_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&j1939ecu_Info,
    j1939ecu_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    obj_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
J1939ECU_CLASS_DATA  j1939ecu_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_J1939ECU_CLASS, 0, 1},
	//0
};



static
bool            j1939ecu_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939ECU == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            j1939ecu_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          j1939ecu_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&j1939ecu_ClassObj;
}


static
uint16_t		j1939ecu_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_J1939ECU;
}


const
J1939ECU_VTBL     j1939ecu_Vtbl = {
    {
        &j1939ecu_Info,
        j1939ecu_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        j1939ecu_Dealloc,
        j1939ecu_Class,
        j1939ecu_WhoAmI,
        NULL,			// j1939ecu_Enable,
        NULL,			// j1939ecu_Disable,
        (P_OBJ_TOSTRING)j1939ecu_ToDebugString,
        NULL,			// (P_OBJ_ASSIGN)j1939ecu_Assign,
        NULL,			// (P_OBJ_COMPARE)j1939ecu_Compare,
        NULL, 			// (P_OBJ_PTR)j1939ecu_Copy,
        NULL 			// (P_OBJ_HASH)j1939ecu_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //j1939ecu_IsEnabled,
 
};



static
const
OBJ_INFO        j1939ecu_Info = {
    "j1939ecu",
    "j1939ecu",	// <-- Fill in description
    (OBJ_DATA *)&j1939ecu_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&j1939ecu_Vtbl
};
#warning -- adjust super class object in Info above 
//			if object inherits from another class





