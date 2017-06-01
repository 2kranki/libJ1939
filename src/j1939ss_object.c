// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'j1939ss'
//	Generated 04/08/2017 00:51:45


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



#define			J1939SS_OBJECT_C	    1
#include        "j1939ss_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct j1939ss_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct j1939ss_class_data_s J1939SS_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        j1939ss_Info;            // Forward Reference



OBJ_ID          j1939ss_Class(
    OBJ_ID          objId
);



static
bool            j1939ss_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939SS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_J1939CA_CLASS == classID) {
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
    return OBJ_IDENT_J1939SS_CLASS;
}


static
const
OBJ_IUNKNOWN    obj_Vtbl = {
	&j1939ss_Info,
    j1939ss_ClassIsKindOf,
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
J1939SS_CLASS_DATA  j1939ss_ClassObj = {
    {&obj_Vtbl, sizeof(OBJ_DATA), OBJ_IDENT_J1939SS_CLASS, 0, 1},
	//0
};



static
bool            j1939ss_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939SS == classID) {
       return true;
    }
    if (OBJ_IDENT_J1939CA == classID) {
        return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            j1939ss_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          j1939ss_Class(
    OBJ_ID          objId
)
{
    return (OBJ_ID)&j1939ss_ClassObj;
}


static
uint16_t		j1939ss_WhoAmI(
    OBJ_ID          objId
)
{
    return OBJ_IDENT_J1939SS;
}


const
J1939SS_VTBL     j1939ss_Vtbl = {
    {
        &j1939ss_Info,
        j1939ss_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        j1939ss_Dealloc,
        j1939ss_Class,
        j1939ss_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)j1939ss_ToDebugString,
        NULL,			// j1939ss_Enable,
        NULL,			// j1939ss_Disable,
        NULL,			// (P_OBJ_ASSIGN)j1939ss_Assign,
        NULL,			// (P_OBJ_COMPARE)j1939ss_Compare,
        NULL, 			// (P_OBJ_PTR)j1939ss_Copy,
        NULL 			// (P_OBJ_HASH)j1939ss_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //j1939ss_IsEnabled,
 
};



static
const
OBJ_INFO        j1939ss_Info = {
    "j1939ss",
    "j1939 Shift Selector CA",
    (OBJ_DATA *)&j1939ss_ClassObj,
    (OBJ_DATA *)&j1939ca_ClassObj,
    (OBJ_IUNKNOWN *)&j1939ss_Vtbl
};





