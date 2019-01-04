// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'j1939can'
//	Generated 04/06/2017 16:09:16


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


#define			J1939CAN_OBJECT_C	    1
#include        "j1939can_internal.h"



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct j1939can_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct j1939can_class_data_s J1939CAN_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        j1939can_Info;            // Forward Reference



OBJ_ID          j1939can_Class(
    void
);



static
bool            j1939can_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939CAN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		j1939can_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_J1939CAN_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&j1939can_Info,
    j1939can_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    j1939can_Class,
    j1939can_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

const
J1939CAN_CLASS_DATA  j1939can_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(J1939CAN_CLASS_DATA),        // cbSize
        OBJ_IDENT_J1939CAN_CLASS,           // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            j1939can_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_J1939CAN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            j1939can_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          j1939can_Class(
    void
)
{
    return (OBJ_ID)&j1939can_ClassObj;
}


static
uint16_t		j1939can_WhoAmI(
    void
)
{
    return OBJ_IDENT_J1939CAN;
}


const
J1939CAN_VTBL     j1939can_Vtbl = {
    {
        &j1939can_Info,
        j1939can_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        j1939can_Dealloc,
        j1939can_Class,
        j1939can_WhoAmI,
        NULL,           // (P_OBJ_QUERYINFO)
        (P_OBJ_TOSTRING)j1939can_ToDebugString,
        NULL,			// j1939can_Enable,
        NULL,			// j1939can_Disable,
        NULL,			// (P_OBJ_ASSIGN)j1939can_Assign,
        NULL,			// (P_OBJ_COMPARE)j1939can_Compare,
        NULL, 			// (P_OBJ_PTR)j1939can_Copy,
        NULL 			// (P_OBJ_HASH)j1939can_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    j1939can_RcvMsg,
    NULL,
    j1939can_XmtMsg
 
};



static
const
OBJ_INFO        j1939Can_Info = {
    "j1939can",
    "j1939 CAN Substitute Object",
    (OBJ_DATA *)&j1939can_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&j1939can_Vtbl
};





