// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939can.c
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
#include "j1939can_internal.h"



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

    J1939CAN_DATA * j1939can_Alloc(
    )
    {
        J1939CAN_DATA   *this;
        uint32_t        cbSize = sizeof(J1939CAN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939CAN_DATA *     j1939can_New(
    )
    {
        J1939CAN_DATA       *this;
        
        this = j1939can_Alloc( );
        if (this) {
            this = j1939can_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         j1939can_getLastError(
        J1939CAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939can_setLastError(
        J1939CAN_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    bool            j1939can_getLoopBackRcv(
        J1939CAN_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        j1939can_setLastError(this, ERESULT_SUCCESS);
        return this->fLoopRcv;
    }
    
    
    bool            j1939can_setLoopBackRcv(
        J1939CAN_DATA   *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fLoopRcv = value;
        
        j1939can_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    bool            j1939can_getLoopBackXmt(
        J1939CAN_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        j1939can_setLastError(this, ERESULT_SUCCESS);
        return this->fLoopXmt;
    }
    
    
    bool            j1939can_setLoopBackXmt(
        J1939CAN_DATA   *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fLoopXmt = value;
        
        j1939can_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    bool                j1939can_setRcvMsg(
        J1939CAN_DATA		*this,
        P_SRVCMSG_RTN       pRoutine,
        void                *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pRcvMsg  = pRoutine;
        this->pRcvObj = pData;
        
        return true;
    }
    
    
    
    bool                j1939can_setXmtMsg(
        J1939CAN_DATA		*this,
        P_XMTMSG_RTN        pRoutine,
        void                *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->cXmts == J1939CAN_MAX_XMT) {
            return false;
        }
        
        this->pXmtMsg[this->cXmts]  = pRoutine;
        this->pXmtObj[this->cXmts] = pData;
        ++this->cXmts;
        
        return true;
    }
    
    

    bool                j1939can_setXmtReflectMsg(
        J1939CAN_DATA		*this,
        P_XMTMSG_RTN        pRoutine,
        void                *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pXmtReflectMsg  = pRoutine;
        this->pXmtReflectObj = pData;
        
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
     @code
        ERESULT eRc = j1939can__Assign(this,pOther);
     @endcode
     @param     this    J1939CAN object pointer
     @param     pOther  a pointer to another J1939CAN object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         j1939can_Assign(
        J1939CAN_DATA		*this,
        J1939CAN_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return j1939can_getLastError(this);
        }
        if( !j1939can_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939can_getLastError(pOther);
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
        j1939can_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939can_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939can_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        j1939Can      *pCopy = j1939can_Copy(this);
     @endcode
     @param     this    J1939CAN object pointer
     @return    If successful, a J1939CAN object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the J1939CAN object.
     */
    J1939CAN_DATA *     j1939can_Copy(
        J1939CAN_DATA       *this
    )
    {
        J1939CAN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = j1939can_New( );
        if (pOther) {
            eRc = j1939can_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939can_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939can_Dealloc(
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
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939CAN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pLock) {
            obj_Release(this->pLock);
            this->pLock = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939can_Disable(
        J1939CAN_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939can_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939can_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return j1939can_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939can_setLastError(this, ERESULT_SUCCESS);
        return j1939can_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939can_Enable(
        J1939CAN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return j1939can_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939can_setLastError(this, ERESULT_SUCCESS);
        return j1939can_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939CAN_DATA *   j1939can_Init(
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
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939can_Vtbl);
        
        j1939can_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pLock = psxLock_New();

    #ifdef NDEBUG
    #else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(&this->pRcvMsg);
        BREAK_NOT_BOUNDARY4(&this->pXmtReflectMsg);
        BREAK_NOT_BOUNDARY4(sizeof(J1939CAN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939can_IsEnabled(
        J1939CAN_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return j1939can_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939can_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939can_getLastError(this);
        }
        
        // Return to caller.
        j1939can_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939can_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //              R e c e i v e  M e s s a g e
    //---------------------------------------------------------------
    
    bool            j1939can_RcvMsg(
        OBJ_ID          pObject,
        J1939_MSG       *pMsg
    )
    {
        J1939CAN_DATA	*this = pObject;
        int             i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pRcvMsg) {
            (*this->pRcvMsg)(this->pRcvObj, pMsg);
        }
        else {
            fprintf(stderr, "ERROR - j1939can_RcvMsg is missing pRcvMsg Handler!\n");
            DEBUG_BREAK();
        }
        if (this->fLoopRcv) {
            for (i=0; i<this->cXmts; ++i) {
                if (this->pXmtMsg[i]) {
                    (*this->pXmtMsg[i])(this->pXmtObj[i], pMsg);
                }
                else {
                    fprintf(stderr, "ERROR - j1939can_XmtMsg is missing pXmtMsg Handler!\n");
                    DEBUG_BREAK();
                }
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939can_ToDebugString(this,4);
     @endcode
     @param     this    J1939CAN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939can_ToDebugString(
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
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(j1939Can)\n",
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(j1939Can)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939can_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939can_Validate(
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
    
    bool            j1939can_XmtMsg(
        OBJ_ID          pObject,
        J1939_MSG       *pMsg
    )
    {
        J1939CAN_DATA	*this = pObject;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939can_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pXmtReflectMsg) {
            (*this->pXmtReflectMsg)(this->pXmtReflectObj, pMsg);
        }
        for (i=0; i<this->cXmts; ++i) {
            if (this->pXmtMsg[i]) {
                (*this->pXmtMsg[i])(this->pXmtObj[i], pMsg);
            }
        }
        if (this->fLoopXmt) {
            if (this->pRcvMsg) {
                (*this->pRcvMsg)(this->pRcvObj, pMsg);
            }
            else {
                fprintf(stderr, "ERROR - j1939can_RcvMsg is missing pRcvMsg Handler!\n");
                DEBUG_BREAK();
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


