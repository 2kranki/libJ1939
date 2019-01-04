// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'j1939cu'
//	Generated 04/13/2017 20:44:32


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



#define			J1939CU_OBJECT_C	    1
#include        <j1939cu_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct j1939cu_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct j1939cu_class_data_s J1939CU_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        j1939cu_Info;            // Forward Reference



OBJ_ID          j1939cu_Class(
    void
);



static
bool            j1939cu_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939CU_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		j1939cu_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_J1939CU_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&j1939cu_Info,
    j1939cu_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    j1939cu_Class,
    j1939cu_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
J1939CU_CLASS_DATA  j1939cu_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(J1939CU_CLASS_DATA),         // cbSize
        OBJ_IDENT_J1939CU_CLASS,            // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            j1939cu_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939CU == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            j1939cu_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          j1939cu_Class(
    void
)
{
    return (OBJ_ID)&j1939cu_ClassObj;
}


static
uint16_t		j1939cu_WhoAmI(
    void
)
{
    return OBJ_IDENT_J1939CU;
}


const
J1939CU_VTBL     j1939cu_Vtbl = {
    {
        &j1939cu_Info,
        j1939cu_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        j1939cu_Dealloc,
        j1939cu_Class,
        j1939cu_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)j1939cu_ToDebugString,
        NULL,			// j1939cu_Enable,
        NULL,			// j1939cu_Disable,
        NULL,			// (P_OBJ_ASSIGN)j1939cu_Assign,
        NULL,			// (P_OBJ_COMPARE)j1939cu_Compare,
        NULL, 			// (P_OBJ_PTR)j1939cu_Copy,
        NULL 			// (P_OBJ_HASH)j1939cu_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //j1939cu_IsEnabled,
 
};



static
const
OBJ_INFO        j1939cu_Info = {
    "j1939cu",
    "J1939 Control Unit",
    (OBJ_DATA *)&j1939cu_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&j1939cu_Vtbl
};





