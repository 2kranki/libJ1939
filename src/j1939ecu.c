// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939ecu.c
 *	Generated 04/13/2017 15:27:22
 *
 */

 
/*
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include "j1939ecu_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            j1939ecu_task_body(
        void            *pData
    )
    {
        //J1939ECU_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939ECU_DATA *     j1939ecu_Alloc(
        uint16_t        stackSize
    )
    {
        J1939ECU_DATA       *this;
        uint32_t        cbSize = sizeof(J1939ECU_DATA);
        
        // Do initialization.
        
        if (0 == stackSize) {
            stackSize = 256;
        }
        cbSize += stackSize << 2;
        this = obj_Alloc( cbSize );
        obj_setMisc1(this, stackSize);
        
        // Return to caller.
        return this;
    }



    J1939ECU_DATA *     j1939ecu_New(
        uint16_t        stackSize
    )
    {
        J1939ECU_DATA       *this;
        
        this = j1939ecu_Alloc(stackSize);
        if (this) {
            this = j1939ecu_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         j1939ecu_getLastError(
        J1939ECU_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939ecu_setLastError(
        J1939ECU_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        j1939ecu_getPriority(
        J1939ECU_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939ecu_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            j1939ecu_setPriority(
        J1939ECU_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939ecu_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        j1939ecu_getSize(
        J1939ECU_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939ecu_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }




    ASTR_DATA * j1939ecu_getStr(
        J1939ECU_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        j1939ecu_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        j1939ecu_setStr(
        J1939ECU_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        j1939ecu_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = j1939ecu__Assign(this,pOther);
     @endcode:
     @param:    this    J1939ECU object pointer
     @param:    pOther  a pointer to another J1939ECU object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         j1939ecu_Assign(
        J1939ECU_DATA		*this,
        J1939ECU_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939ecu_getLastError(this);
        }
        if( !j1939ecu_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939ecu_getLastError(pOther);
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
        j1939ecu_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939ecu_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939ecu_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        j1939ecu      *pCopy = j1939ecu_Copy(this);
     @endcode:
     @param:    this    J1939ECU object pointer
     @return:   If successful, a J1939ECU object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the J1939ECU object.
     */
    J1939ECU_DATA *     j1939ecu_Copy(
        J1939ECU_DATA       *this
    )
    {
        J1939ECU_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = j1939ecu_New(obj_getSize(this));
        if (pOther) {
            eRc = j1939ecu_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939ecu_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939ecu_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939ECU_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939ECU_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        j1939ecu_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939ecu_Disable(
        J1939ECU_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939ecu_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939ecu_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939ecu_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939ecu_setLastError(this, ERESULT_SUCCESS);
        return j1939ecu_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939ecu_Enable(
        J1939ECU_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939ecu_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939ecu_setLastError(this, ERESULT_SUCCESS);
        return j1939ecu_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939ECU_DATA *   j1939ecu_Init(
        J1939ECU_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(J1939ECU_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939ECU);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939ECU);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939ecu_Vtbl);
        
        j1939ecu_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !j1939ecu_Validate(this) ) {
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
    
    ERESULT         j1939ecu_IsEnabled(
        J1939ECU_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ecu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939ecu_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939ecu_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939ecu_getLastError(this);
        }
        
        // Return to caller.
        j1939ecu_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939ecu_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939ecu_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939ECU object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939ecu_ToDebugString(
        J1939ECU_DATA      *this,
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
        if( !j1939ecu_Validate(this) ) {
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
                     "{%p(j1939ecu) size=%d\n",
                     this,
                     j1939ecu_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(j1939ecu)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939ecu_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939ecu_Validate(
        J1939ECU_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939ECU) )
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


        if( !(obj_getSize(this) >= sizeof(J1939ECU_DATA)) ) {
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


