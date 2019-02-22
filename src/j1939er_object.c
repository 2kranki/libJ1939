// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'j1939er'
//	Generated 03/21/2017 22:27:14


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



#define			J1939ER_OBJECT_C	    1
#include        "j1939er_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct j1939er_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct j1939er_class_data_s J1939ER_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        j1939er_Info;            // Forward Reference



OBJ_ID          j1939er_Class(
    void
);



static
bool            j1939er_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939ER_CLASS == classID) {
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
uint16_t		j1939er_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_J1939ER_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&j1939er_Info,
    j1939er_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    j1939er_Class,
    j1939er_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
J1939ER_CLASS_DATA  j1939er_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(J1939ER_CLASS_DATA),         // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            j1939er_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939ER == classID) {
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
void            j1939er_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          j1939er_Class(
    void
)
{
    return (OBJ_ID)&j1939er_ClassObj;
}


static
uint16_t		j1939er_WhoAmI(
    void
)
{
    return OBJ_IDENT_J1939ER;
}


const
J1939ER_VTBL     j1939er_Vtbl = {
    {
        &j1939er_Info,
        j1939er_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        j1939er_Dealloc,
        j1939er_Class,
        j1939er_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        NULL,           // (P_OBJ_TOSTRING)j1939er_ToDebugString,
        NULL,			// j1939er_Enable,
        NULL,			// j1939er_Disable,
        NULL,			// (P_OBJ_ASSIGN)j1939er_Assign,
        NULL,			// (P_OBJ_COMPARE)j1939er_Compare,
        NULL, 			// (P_OBJ_PTR)j1939er_Copy,
        NULL 			// (P_OBJ_HASH)j1939er_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //j1939er_IsEnabled,
 
};



static
const
OBJ_INFO        j1939er_Info = {
    "j1939er",
    "j1939 Engine Retarder",
    (OBJ_DATA *)&j1939er_ClassObj,
    (OBJ_DATA *)&j1939ca_ClassObj,
    (OBJ_IUNKNOWN *)&j1939er_Vtbl
};





