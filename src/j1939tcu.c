// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939tcu.c
 *	Generated 04/13/2017 19:42:48
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
#include    <j1939tcu_internal.h>
#include    <j1939tc.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef NDEBUG
#else
    bool			j1939tcu_Validate(
        J1939TCU_DATA       *this
    );
#endif
    
    
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939TCU_DATA * j1939tcu_Alloc(
    )
    {
        J1939TCU_DATA   *this;
        uint32_t        cbSize = sizeof(J1939TCU_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939TCU_DATA * j1939tcu_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939TCU_DATA       *this;
        
        this = j1939tcu_Alloc( );
        if (this) {
            this = j1939tcu_Init(this, pCAN, pSYS, spn2837, spn2838, spn2846);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         j1939tcu_getLastError(
        J1939TCU_DATA     *this
    )
    {
        ERESULT         eRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = j1939cu_getLastError((J1939CU_DATA *)this);
        
        return eRc;
    }


    bool            j1939tcu_setLastError(
        J1939TCU_DATA     *this,
        ERESULT         value
    )
    {
        bool            fRc;
        
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = j1939cu_setLastError((J1939CU_DATA *)this, value);
        
        return fRc;
    }
    
    

    uint16_t        j1939tcu_getPriority(
        J1939TCU_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939tcu_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            j1939tcu_setPriority(
        J1939TCU_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939tcu_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        j1939tcu_getSize(
        J1939TCU_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939tcu_setLastError(this, ERESULT_SUCCESS);
        return 0;
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
        ERESULT eRc = j1939tcu__Assign(this,pOther);
     @endcode:
     @param:    this    J1939TCU object pointer
     @param:    pOther  a pointer to another J1939TCU object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         j1939tcu_Assign(
        J1939TCU_DATA		*this,
        J1939TCU_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tcu_getLastError(this);
        }
        if( !j1939tcu_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939tcu_getLastError(pOther);
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
        j1939tcu_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939tcu_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939tcu_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        j1939tcu      *pCopy = j1939tcu_Copy(this);
     @endcode:
     @param:    this    J1939TCU object pointer
     @return:   If successful, a J1939TCU object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the J1939TCU object.
     */
    J1939TCU_DATA *     j1939tcu_Copy(
        J1939TCU_DATA       *this
    )
    {
        J1939TCU_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = j1939tcu_New(obj_getSize(this));
        if (pOther) {
            eRc = j1939tcu_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939tcu_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939tcu_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939TCU_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        j1939cu_Dealloc(this);          // Needed for inheritance
        //obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939tcu_Disable(
        J1939TCU_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939tcu_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939tcu_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tcu_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939tcu_setLastError(this, ERESULT_SUCCESS);
        return j1939tcu_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939tcu_Enable(
        J1939TCU_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tcu_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939tcu_setLastError(this, ERESULT_SUCCESS);
        return j1939tcu_getLastError(this);
    }



    //---------------------------------------------------------------
    //                  H a n d l e  M e s s a g e s
    //---------------------------------------------------------------
    
    /* HandleMessages() is passed messages from a message source such
     * as a CAN FIFO Receive Queue. This routine handles the message
     * either internally or via its responder chain.
     * Warning: This function must conform to P_SRVCMSG_RTN specs.
     */
    
    bool            j1939tcu_HandleMessages(
        J1939TCU_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg           // if NULL, receive timed out
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = j1939cam_HandleMessages(j1939cu_getCam((J1939CU_DATA *)this), pMsg);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939TCU_DATA * j1939tcu_Init(
        J1939TCU_DATA   *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint32_t        cbSize = sizeof(J1939TCU_DATA);
        J1939TC_DATA    *pTC;
        
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

        this = (OBJ_ID)j1939cu_Init(        // Needed for Inheritance
                        (J1939CU_DATA *)this,
                                    pCAN,
                                    pSYS,
                                    spn2837,
                                    spn2838,
                                    spn2846
                );
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939TCU);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939TCU);     // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939tcu_Vtbl);
        
        j1939tcu_setLastError(this, ERESULT_GENERAL_FAILURE);

        // Create the Transmission #1.
        pTC = j1939tc_Alloc();
        pTC = j1939tc_Init(pTC, pCAN, pSYS, spn2837, spn2838, spn2846);
        if( OBJ_NIL == pTC ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        j1939cam_AddCA(j1939cu_getCam((J1939CU_DATA *)this), pTC);
        obj_Release(pTC);
        pTC = OBJ_NIL;
        
    #ifdef NDEBUG
    #else
        if( !j1939tcu_Validate(this) ) {
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
    
    ERESULT         j1939tcu_IsEnabled(
        J1939TCU_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939tcu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939tcu_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939tcu_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939tcu_getLastError(this);
        }
        
        // Return to caller.
        j1939tcu_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939tcu_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939tcu_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939TCU object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939tcu_ToDebugString(
        J1939TCU_DATA      *this,
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
        if( !j1939tcu_Validate(this) ) {
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
                     "{%p(j1939tcu)\n",
                     this
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
        j = snprintf(str, sizeof(str), " %p(j1939tcu)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939tcu_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939tcu_Validate(
        J1939TCU_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939TCU) )
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


        if( !(obj_getSize(this) >= sizeof(J1939TCU_DATA)) ) {
            j1939cu_setLastError((J1939CU_DATA *)this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        j1939cu_setLastError((J1939CU_DATA *)this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


