// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939sys.c
 *	Generated 04/06/2017 16:09:23
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
#include <j1939sys_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939SYS_DATA * j1939sys_Alloc(
    )
    {
        J1939SYS_DATA   *this;
        uint32_t        cbSize = sizeof(J1939SYS_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939SYS_DATA *     j1939sys_New(
    )
    {
        J1939SYS_DATA       *this;
        
        this = j1939sys_Alloc( );
        if (this) {
            this = j1939sys_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         j1939sys_getLastError(
        J1939SYS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939sys_setLastError(
        J1939SYS_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
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
        ERESULT eRc = j1939sys__Assign(this,pOther);
     @endcode:
     @param:    this    J1939SYS object pointer
     @param:    pOther  a pointer to another J1939SYS object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         j1939sys_Assign(
        J1939SYS_DATA		*this,
        J1939SYS_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return j1939sys_getLastError(this);
        }
        if( !j1939sys_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939sys_getLastError(pOther);
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
        j1939sys_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939sys_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939sys_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       B u m p  M S
    //---------------------------------------------------------------
    
    uint32_t        j1939sys_BumpMS(
        J1939SYS_DATA	*this,
        uint32_t        ms
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return j1939sys_getLastError(this);
        }
#endif
        
        this->time += ms;
        
        // Return to caller.
        j1939sys_setLastError(this, ERESULT_SUCCESS);
        return this->time;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        j1939Sys      *pCopy = j1939sys_Copy(this);
     @endcode:
     @param:    this    J1939SYS object pointer
     @return:   If successful, a J1939SYS object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the J1939SYS object.
     */
    J1939SYS_DATA *     j1939sys_Copy(
        J1939SYS_DATA       *this
    )
    {
        J1939SYS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = j1939sys_New( );
        if (pOther) {
            eRc = j1939sys_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939sys_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939sys_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939SYS_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939SYS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        //j1939sys_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939sys_Disable(
        J1939SYS_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939sys_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939sys_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return j1939sys_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939sys_setLastError(this, ERESULT_SUCCESS);
        return j1939sys_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939sys_Enable(
        J1939SYS_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return j1939sys_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939sys_setLastError(this, ERESULT_SUCCESS);
        return j1939sys_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939SYS_DATA *   j1939sys_Init(
        J1939SYS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(J1939SYS_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939SYS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939SYS);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939sys_Vtbl);
        
        j1939sys_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          j1939sys_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        J1939SYS_DATA   *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                    case 'B':
                        if (str_Compare("BumpMS", (char *)pStr) == 0) {
                            return j1939sys_BumpMS;
                        }
                        break;
                        
                    case 'S':
                        if (str_Compare("SleepMS", (char *)pStr) == 0) {
                            return j1939sys_SleepMS;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("TimeMS", (char *)pStr) == 0) {
                            return j1939sys_TimeMS;
                        }
                        if (str_Compare("TimeReset", (char *)pStr) == 0) {
                            return j1939sys_TimeReset;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                       S l e e p  M S
    //---------------------------------------------------------------
    
    uint32_t        j1939sys_SleepMS(
        J1939SYS_DATA	*this,
        uint32_t        ms
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return j1939sys_getLastError(this);
        }
#endif
        
        // Simulate by just bumping time.
        this->time += ms;
        
        // Return to caller.
        j1939sys_setLastError(this, ERESULT_SUCCESS);
        return this->time;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T i m e  M S
    //---------------------------------------------------------------
    
    uint32_t        j1939sys_TimeMS(
        J1939SYS_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return j1939sys_getLastError(this);
        }
#endif
        
        ++this->time;       // Bump to simulate real clock
        
        // Return to caller.
        j1939sys_setLastError(this, ERESULT_SUCCESS);
        return this->time;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T i m e  R e s e t
    //---------------------------------------------------------------
    
    uint32_t        j1939sys_TimeReset(
        J1939SYS_DATA	*this,
        uint32_t        ms
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939sys_Validate(this) ) {
            DEBUG_BREAK();
            return j1939sys_getLastError(this);
        }
#endif
        
        // Simulate by just setting time.
        this->time = ms;
        
        // Return to caller.
        j1939sys_setLastError(this, ERESULT_SUCCESS);
        return this->time;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939Sys_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939SYS object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939sys_ToDebugString(
        J1939SYS_DATA      *this,
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
        if( !j1939sys_Validate(this) ) {
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
                     "{%p(j1939Sys) time=%d\n",
                     this,
                     this->time
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
        j = snprintf(str, sizeof(str), " %p(j1939Sys)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939sys_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939sys_Validate(
        J1939SYS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_J1939SYS) )
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


        if( !(obj_getSize(this) >= sizeof(J1939SYS_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


