// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'truck'
//	Generated 06/12/2017 20:11:38


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



#define			TRUCK_OBJECT_C	    1
#include        <truck_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct truck_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct truck_class_data_s TRUCK_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        truck_Info;            // Forward Reference



OBJ_ID          truck_Class(
    OBJ_ID          objId
);



static
bool            truck_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TRUCK_CLASS == classID) {
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
    return OBJ_IDENT_TRUCK_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&truck_Info,
    truck_ClassIsKindOf,
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
TRUCK_CLASS_DATA  truck_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_TRUCK_CLASS, 0, 1},
	//0
};



static
bool            truck_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_TRUCK == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            truck_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          truck_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&truck_ClassObj;
}


static
uint16_t		truck_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_TRUCK;
}


const
TRUCK_VTBL     truck_Vtbl = {
    {
        &truck_Info,
        truck_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        truck_Dealloc,
        truck_Class,
        truck_WhoAmI,
        (P_OBJ_QUERYINFO)truck_QueryInfo,
        (P_OBJ_TOSTRING)truck_ToDebugString,
        NULL,			// truck_Enable,
        NULL,			// truck_Disable,
        NULL,			// (P_OBJ_ASSIGN)truck_Assign,
        NULL,			// (P_OBJ_COMPARE)truck_Compare,
        NULL, 			// (P_OBJ_PTR)truck_Copy,
        NULL 			// (P_OBJ_HASH)truck_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //truck_IsEnabled,
 
};



static
const
OBJ_INFO        truck_Info = {
    "truck",
    "J1939 Truck",
    (OBJ_DATA *)&truck_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&truck_Vtbl
};





