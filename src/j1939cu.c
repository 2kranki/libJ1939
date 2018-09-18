// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939cu.c
 *	Generated 04/13/2017 20:44:32
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
#include    <j1939cu_internal.h>
#include    <j1939dg.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef NDEBUG
#else
    bool			j1939cu_Validate(
        J1939CU_DATA    *this
    );
#endif
    
    
    static
    void *          j1939cu_task_body(
        void            *pData,
        void            *pMsgData
    )
    {
        J1939CU_DATA    *this = pData;
        J1939_MSG       *pMsg = pMsgData;
        uint32_t        eid = 0;
        
        if (obj_Flag(this, OBJ_FLAG_ENABLED)) {
            if (pMsg) {
                eid = j1939msg_getEid(pMsg);
            }
            j1939cam_HandleMessages(this->pCam, pMsg);
        }
        return NULL;
    }




    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939CU_DATA *  j1939cu_Alloc(
    )
    {
        J1939CU_DATA    *this;
        uint32_t        cbSize = sizeof(J1939CU_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939CU_DATA *  j1939cu_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939CU_DATA       *this;
        
        this = j1939cu_Alloc( );
        if (this) {
            this = j1939cu_Init(this, pCAN, pSYS, spn2837, spn2838, spn2846);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    J1939CAM_DATA * j1939cu_getCam(
        J1939CU_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        j1939cu_setLastError(this, ERESULT_SUCCESS);
        return this->pCam;
    }
    
    
    bool            j1939cu_setCam(
        J1939CU_DATA    *this,
        J1939CAM_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pCam) {
            obj_Release(this->pCam);
        }
        this->pCam = pValue;
        
        j1939cu_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C A N
    //---------------------------------------------------------------
    
    OBJ_ID          j1939cu_getCAN(
        J1939CU_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pCAN;
    }
    
    
    bool            j1939cu_setCAN(
        J1939CU_DATA	*this,
        OBJ_ID          pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);         // This is our object.
        if (this->pCAN) {
            obj_Release(this->pCAN);
        }
        this->pCAN = pValue;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         j1939cu_getLastError(
        J1939CU_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939cu_setLastError(
        J1939CU_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    bool			j1939cu_setMsgFilter(
        J1939CU_DATA	*this,
        int             (*pMsgFilter)(void *, void *),
        void            *pMsgFilterData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pMsgFilter  = pMsgFilter;
        this->pMsgFilterData = pMsgFilterData;
        
        return true;
    }
    
    
    
    uint16_t        j1939cu_getPriority(
        J1939CU_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939cu_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            j1939cu_setPriority(
        J1939CU_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939cu_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t		j1939cu_getSpn2837(
        J1939CU_DATA	*this
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939cu_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->spn2837;
    }
    
    
    bool			j1939cu_setSpn2837(
        J1939CU_DATA	*this,
        uint32_t		value
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939cu_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->spn2837 = value;
        
        return true;
    }
    
    
    
    uint16_t		j1939cu_getSpn2838(
        J1939CU_DATA	*this
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939cu_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->spn2838;
    }
    
    
    bool			j1939cu_setSpn2838(
        J1939CU_DATA	*this,
        uint16_t		value
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939cu_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->spn2838 = value;
        
        return true;
    }
    
    
    
    uint8_t			j1939cu_getSpn2846(
        J1939CU_DATA	*this
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939cu_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->spn2846;
    }
    
    
    bool			j1939cu_setSpn2846(
        J1939CU_DATA	*this,
        uint8_t			value
    )
    {
        
#ifdef NDEBUG
#else
        if (j1939cu_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->spn2846 = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S Y S
    //---------------------------------------------------------------
    
    OBJ_ID          j1939cu_getSYS(
        J1939CU_DATA	*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        // Return to caller.
        return  this->pSYS;
    }
    
    
    bool            j1939cu_setSYS(
        J1939CU_DATA	*this,
        OBJ_ID          pValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);         // This is our object.
        if (this->pSYS) {
            obj_Release(this->pSYS);
        }
        this->pSYS = pValue;
        
        // Return to caller.
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
        ERESULT eRc = j1939cu__Assign(this,pOther);
     @endcode
     @param     this    J1939CU object pointer
     @param     pOther  a pointer to another J1939CU object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         j1939cu_Assign(
        J1939CU_DATA	*this,
        J1939CU_DATA    *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cu_getLastError(this);
        }
        if( !j1939cu_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939cu_getLastError(pOther);
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
        j1939cu_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939cu_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939cu_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        j1939cu      *pCopy = j1939cu_Copy(this);
     @endcode
     @param     this    J1939CU object pointer
     @return    If successful, a J1939CU object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the J1939CU object.
     */
    J1939CU_DATA *     j1939cu_Copy(
        J1939CU_DATA       *this
    )
    {
        J1939CU_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = j1939cu_New(obj_getSize(this));
        if (pOther) {
            eRc = j1939cu_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939cu_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939cu_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939CU_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        j1939cu_Disable(this);
        
        if (this->pConsumer) {
            obj_Release(this->pConsumer);
            this->pConsumer = OBJ_NIL;
        }
        
        j1939cu_setCam(this, OBJ_NIL);
        j1939cu_setCAN(this, OBJ_NIL);
        j1939cu_setSYS(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939cu_Disable(
        J1939CU_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939cu_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939cu_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cu_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939cu_setLastError(this, ERESULT_SUCCESS);
        return j1939cu_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939cu_Enable(
        J1939CU_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cu_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939cu_setLastError(this, ERESULT_SUCCESS);
        return j1939cu_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939CU_DATA *  j1939cu_Init(
        J1939CU_DATA    *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint32_t        cbSize = sizeof(J1939CU_DATA);
        J1939DG_DATA    *pDG;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939CU);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939CU);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939cu_Vtbl);
        
        j1939cu_setLastError(this, ERESULT_GENERAL_FAILURE);

        this->pConsumer = consumer_New(sizeof(J1939_MSG), 100, j1939cu_task_body, this);
        if( OBJ_NIL == this->pConsumer ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pCam = j1939cam_New(pCAN, pSYS);
        if( OBJ_NIL == this->pCam ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        // Create the Diagnostic Application.
        pDG = j1939dg_Alloc( );
        pDG = j1939dg_Init(pDG, pCAN, pSYS, spn2837, spn2838, spn2846);
        if( OBJ_NIL == pDG ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        j1939cam_AddCA(this->pCam, pDG);
        obj_Release(pDG);
        pDG = OBJ_NIL;
        
    #ifdef NDEBUG
    #else
        if( !j1939cu_Validate(this) ) {
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
    
    ERESULT         j1939cu_IsEnabled(
        J1939CU_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cu_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cu_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939cu_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939cu_getLastError(this);
        }
        
        // Return to caller.
        j1939cu_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939cu_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939cu_ToDebugString(this,4);
     @endcode
     @param     this    J1939CU object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939cu_ToDebugString(
        J1939CU_DATA      *this,
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
        if( !j1939cu_Validate(this) ) {
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
                     "{%p(j1939cu)\n",
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
        j = snprintf(str, sizeof(str), " %p(j1939cu)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939cu_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939cu_Validate(
        J1939CU_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939CU) )
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


        if( !(obj_getSize(this) >= sizeof(J1939CU_DATA)) ) {
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


