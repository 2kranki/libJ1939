// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'j1939bs'
//	Generated 06/21/2017 16:25:20


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



#define			J1939BS_OBJECT_C	    1
#include        <j1939bs_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct j1939bs_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct j1939bs_class_data_s J1939BS_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        j1939bs_Info;            // Forward Reference



OBJ_ID          j1939bs_Class(
    void
);



static
bool            j1939bs_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939BS_CLASS == classID) {
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
uint16_t		j1939bs_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_J1939BS_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&j1939bs_Info,
    j1939bs_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    j1939bs_Class,
    j1939bs_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
J1939BS_CLASS_DATA  j1939bs_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(J1939BS_CLASS_DATA),         // cbSize
        0,                                  // cbFlags
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            j1939bs_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939BS == classID) {
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
void            j1939bs_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          j1939bs_Class(
    void
)
{
    return (OBJ_ID)&j1939bs_ClassObj;
}


static
uint16_t		j1939bs_WhoAmI(
    void
)
{
    return OBJ_IDENT_J1939BS;
}


const
J1939BS_VTBL     j1939bs_Vtbl = {
    {
        &j1939bs_Info,
        j1939bs_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        j1939bs_Dealloc,
        j1939bs_Class,
        j1939bs_WhoAmI,
        (P_OBJ_QUERYINFO)j1939bs_QueryInfo,
        (P_OBJ_TOSTRING)j1939bs_ToDebugString,
        NULL,			// j1939bs_Enable,
        NULL,			// j1939bs_Disable,
        NULL,			// (P_OBJ_ASSIGN)j1939bs_Assign,
        NULL,			// (P_OBJ_COMPARE)j1939bs_Compare,
        NULL, 			// (P_OBJ_PTR)j1939bs_Copy,
        NULL 			// (P_OBJ_HASH)j1939bs_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //j1939bs_IsEnabled,
 
};



static
const
OBJ_INFO        j1939bs_Info = {
    "j1939bs",
    "J1939 Brake System CA",
    (OBJ_DATA *)&j1939bs_ClassObj,
    (OBJ_DATA *)&j1939ca_ClassObj,
    (OBJ_IUNKNOWN *)&j1939bs_Vtbl
};





