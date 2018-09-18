// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939MISC Console Transmit Task (j1939misc) Header
//****************************************************************
/*
 * Program
 *			Separate j1939misc (j1939misc)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate j1939misc to run things without complications
 *          of interfering with the main j1939misc. A j1939misc may be 
 *          called a j1939misc on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal j1939misc. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	06/15/2017 Generated
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


#ifndef         J1939MISC_H
#define         J1939MISC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939misc_data_s	J1939MISC_DATA;    // Inherits from OBJ.

    typedef struct j1939misc_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939misc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939MISC_DATA *);
    } J1939MISC_VTBL;



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
     @return:   pointer to j1939misc object if successful, otherwise OBJ_NIL.
     */
    J1939MISC_DATA *     j1939misc_Alloc(
        void
    );
    
    
    J1939MISC_DATA *     j1939misc_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            j1939misc_setFileOut(
        J1939MISC_DATA  *this,
        FILE            *pValue
    );
    
    
    ERESULT     j1939misc_getLastError(
        J1939MISC_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     j1939misc_Disable(
        J1939MISC_DATA		*this
    );


    bool            j1939misc_DumpMessage(
        J1939MISC_DATA	*this,
        J1939_MSG       *pMsg
    );
    
    
    ERESULT     j1939misc_Enable(
        J1939MISC_DATA		*this
    );

   
    J1939MISC_DATA *   j1939misc_Init(
        J1939MISC_DATA     *this
    );


    ERESULT     j1939misc_IsEnabled(
        J1939MISC_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939misc_ToDebugString(this,4);
     @endcode
     @param     this    J1939MISC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    j1939misc_ToDebugString(
        J1939MISC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939MISC_H */

