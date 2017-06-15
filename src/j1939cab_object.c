// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'j1939cab'
//	Generated 06/12/2017 17:43:12


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



#define			J1939CAB_OBJECT_C	    1
#include        <j1939cab_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct j1939cab_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct j1939cab_class_data_s J1939CAB_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        j1939cab_Info;            // Forward Reference



OBJ_ID          j1939cab_Class(
    OBJ_ID          objId
);



static
bool            j1939cab_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939CAB_CLASS == classID) {
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
    return OBJ_IDENT_J1939CAB_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&j1939cab_Info,
    j1939cab_ClassIsKindOf,
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
J1939CAB_CLASS_DATA  j1939cab_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_J1939CAB_CLASS, 0, 1},
	//0
};



static
bool            j1939cab_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939CAB == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            j1939cab_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          j1939cab_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&j1939cab_ClassObj;
}


static
uint16_t		j1939cab_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_J1939CAB;
}


const
J1939CAB_VTBL     j1939cab_Vtbl = {
    {
        &j1939cab_Info,
        j1939cab_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        j1939cab_Dealloc,
        j1939cab_Class,
        j1939cab_WhoAmI,
        (P_OBJ_QUERYINFO)j1939cab_QueryInfo,
        (P_OBJ_TOSTRING)j1939cab_ToDebugString,
        NULL,			// j1939cab_Enable,
        NULL,			// j1939cab_Disable,
        NULL,			// (P_OBJ_ASSIGN)j1939cab_Assign,
        NULL,			// (P_OBJ_COMPARE)j1939cab_Compare,
        NULL, 			// (P_OBJ_PTR)j1939cab_Copy,
        NULL 			// (P_OBJ_HASH)j1939cab_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //j1939cab_IsEnabled,
 
};



static
const
OBJ_INFO        j1939cab_Info = {
    "j1939cab",
    "j1939 Cab Controller",
    (OBJ_DATA *)&j1939cab_ClassObj,
    (OBJ_DATA *)&j1939ca_ClassObj,
    (OBJ_IUNKNOWN *)&j1939cab_Vtbl
};





