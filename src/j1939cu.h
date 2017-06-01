// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              J1939 Control Unit (j1939cu) Header
//****************************************************************
/*
 * Program
 *			J1939 Control Unit (j1939cu)
 * Purpose
 *			This object provides J1939 Control Unit base object to
 *          be built upon.
 *
 *          Notes to self. The Control Units need to be able to
 *          change spn's within its CAs and force msgs to be sent
 *          at specific times.  For instance, the Engine Shutdown
 *          procedure is two phases apparently given the msg,
 *          SHUTDOW. The first phase is "shutdown is approaching".
 *          So, clean up all the CAs and get them ready to stop. 
 *          After an appropriate pause, the second phase is to
 *          tell everyone that they need to actually shutdown.
 *          Currently, this would be at least the following:
 *                 Set spn1109 value to approaching shutdown.
 *                 Set spn1110 value to approaching shutdown.
 *                 Issue "SHUTDOW"
 *                 wait for appropriate period.
 *                 Set spn1109 value to final shutdown.
 *                 Set spn1110 value to final shutdown.
 *                 Issue "SHUTDOW"
 *
            Maybe we run the CAM and all CAs for the CU under
            one task and run the CU under another posting control/
            response type messages (not J1939) between the two.
            Another approach would be to spawn a separate task
            for each special task and have it handle the request
            and post back when it is done.
 *
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/13/2017 Generated
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


#ifndef         J1939CU_H
#define         J1939CU_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939cu_data_s	J1939CU_DATA;    // Inherits from OBJ.

    typedef struct j1939cu_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939cu_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939CU_DATA *);
    } J1939CU_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    J1939CU_DATA *     j1939cu_Alloc(
    );
    
    
    J1939CU_DATA *     j1939cu_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    J1939CAM_DATA * j1939cu_getCam(
        J1939CU_DATA    *this
    );
    
    bool            j1939cu_setCam(
        J1939CU_DATA    *this,
        J1939CAM_DATA   *pValue
    );
    
    
    ERESULT     j1939cu_getLastError(
        J1939CU_DATA		*this
    );


    uint32_t		j1939cu_getSpn2837(
        J1939CU_DATA	*this
    );
    
    bool			j1939cu_setSpn2837(
        J1939CU_DATA	*this,
        uint32_t		value
    );
    
    
    uint16_t		j1939cu_getSpn2838(
        J1939CU_DATA	*this
    );
    
    bool			j1939cu_setSpn2838(
        J1939CU_DATA	*this,
        uint16_t		value
    );
    
    
    uint8_t			j1939cu_getSpn2846(
        J1939CU_DATA	*this
    );
    
    bool			j1939cu_setSpn2846(
        J1939CU_DATA	*this,
        uint8_t			value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     j1939cu_Disable(
        J1939CU_DATA		*this
    );


    ERESULT     j1939cu_Enable(
        J1939CU_DATA		*this
    );

   
    J1939CU_DATA *   j1939cu_Init(
        J1939CU_DATA     *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );


    ERESULT     j1939cu_IsEnabled(
        J1939CU_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939cu_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939CU object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    j1939cu_ToDebugString(
        J1939CU_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939CU_H */

