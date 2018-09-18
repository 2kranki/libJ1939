// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939 Cab Control Unit (j1939ccu) Header
//****************************************************************
/*
 * Program
 *			J1939 Cab Control Unit (j1939ccu)
 * Purpose
 *			This object provides support for the following Control
 *          Applications:
 *              j1939bs - Braking System CA
 *              j1939cab - Cab CA
 *              j1939cc - Cruise Control CA
 *              j1939ss - Shifter CA
 *          The CAs run under the CCU's Consumer Task.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/05/2017 Generated
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





#include        <j1939_defs.h>
#include        <AStr.h>


#ifndef         J1939CCU_H
#define         J1939CCU_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939ccu_data_s	J1939CCU_DATA;    // Inherits from OBJ.

    typedef struct j1939ccu_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939ccu_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939CCU_DATA *);
    } J1939CCU_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return:   pointer to j1939ccu object if successful, otherwise OBJ_NIL.
     */
    J1939CCU_DATA *     j1939ccu_Alloc(
        void
    );
    
    
    J1939CCU_DATA *     j1939ccu_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         j1939ccu_getLastError(
        J1939CCU_DATA	*this
    );

    
    bool            j1939ccu_setRPM(
        J1939CCU_DATA	*this,
        uint32_t        value
    );
    
    
    bool            j1939ccu_setRpmRoutine(
        J1939CCU_DATA	*this,
        void            (*pRpm)(void *, uint32_t),
        void            *pRpmData
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     j1939ccu_Disable(
        J1939CCU_DATA		*this
    );


    ERESULT     j1939ccu_Enable(
        J1939CCU_DATA		*this
    );

   
    J1939CCU_DATA *   j1939ccu_Init(
        J1939CCU_DATA   *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );


    ERESULT     j1939ccu_IsEnabled(
        J1939CCU_DATA		*this
    );
    
 
    /*!
     The driver just released the engine start.
     */
    ERESULT     j1939ccu_StartEnd(
        J1939CCU_DATA		*this
    );
    
    
    /*!
     The driver just pressed the engine start.
     */
    ERESULT     j1939ccu_StartInitiate(
        J1939CCU_DATA		*this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939ccu_ToDebugString(this,4);
     @endcode
     @param     this    J1939CCU object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    j1939ccu_ToDebugString(
        J1939CCU_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939CCU_H */

