// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939Can.c
 *	Generated 04/06/2017 16:09:16
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include "j1939Can_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            j1939Can_task_body(
        void            *pData
    )
    {
        //J1939CAN_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939CAN_DATA * j1939Can_Alloc(
    )
    {
        J1939CAN_DATA   *this;
        uint32_t        cbSize = sizeof(J1939CAN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939CAN_DATA *     j1939Can_New(
    )
    {
        J1939CAN_DATA       *this;
        
        this = j1939Can_Alloc( );
        if (this) {
            this = j1939Can_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         j1939Can_getLastError(
        J1939CAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939Can_setLastError(
        J1939CAN_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        j1939Can_getPriority(
        J1939CAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939Can_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            j1939Can_setPriority(
        J1939CAN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939Can_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        j1939Can_getSize(
        J1939CAN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939Can_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }




    ASTR_DATA * j1939Can_getStr(
        J1939CAN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        j1939Can_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        j1939Can_setStr(
        J1939CAN_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        j1939Can_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    bool                j1939Can_setXmtMsg(
        J1939CAN_DATA		*this,
        P_XMTMSG_RTN        pRoutine,
        void                *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pXmtMsg  = pRoutine;
        this->pXmtData = pData;
        
        return true;
    }
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = j1939Can__Assign(this,pOther);
     @endcode:
     @param:    this    J1939CAN object pointer
     @param:    pOther  a pointer to another J1939CAN object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         j1939Can_Assign(
        J1939CAN_DATA		*this,
        J1939CAN_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return j1939Can_getLastError(this);
        }
        if( !j1939Can_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939Can_getLastError(pOther);
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        j1939Can_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939Can_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939Can_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        j1939Can      *pCopy = j1939Can_Copy(this);
     @endcode:
     @param:    this    J1939CAN object pointer
     @return:   If successful, a J1939CAN object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the J1939CAN object.
     */
    J1939CAN_DATA *     j1939Can_Copy(
        J1939CAN_DATA       *this
    )
    {
        J1939CAN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = j1939Can_New( );
        if (pOther) {
            eRc = j1939Can_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939Can_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939Can_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939CAN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939CAN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        j1939Can_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939Can_Disable(
        J1939CAN_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939Can_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939Can_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return j1939Can_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939Can_setLastError(this, ERESULT_SUCCESS);
        return j1939Can_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939Can_Enable(
        J1939CAN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return j1939Can_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939Can_setLastError(this, ERESULT_SUCCESS);
        return j1939Can_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939CAN_DATA *   j1939Can_Init(
        J1939CAN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(J1939CAN_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939CAN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939CAN);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939Can_Vtbl);
        
        j1939Can_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939Can_IsEnabled(
        J1939CAN_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return j1939Can_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939Can_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939Can_getLastError(this);
        }
        
        // Return to caller.
        j1939Can_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939Can_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939Can_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939CAN object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939Can_ToDebugString(
        J1939CAN_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(j1939Can) size=%d\n",
                     this,
                     j1939Can_getSize(this)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(j1939Can)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939Can_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939Can_Validate(
        J1939CAN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939CAN) )
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(J1939CAN_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //              T r a n s m i t  M e s s a g e
    //---------------------------------------------------------------
    
    void            j1939Can_XmtMsg(
        void            *pObject,
        uint32_t        msDelay,
        J1939_MSG       *pMsg
    )
    {
        J1939CAN_DATA	*this = pObject;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939Can_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
        if( msDelay ) {                 // *** Temporary ***
            DEBUG_BREAK();
        }
#endif
        if (this->pXmtMsg) {
            (*this->pXmtMsg)(this->pXmtData, msDelay, pMsg);
        }
        
        // Return to caller.
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


