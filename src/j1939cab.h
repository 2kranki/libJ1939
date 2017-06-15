// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939CAB Console Transmit Task (j1939cab) Header
//****************************************************************
/*
 * Program
 *			Separate j1939cab (j1939cab)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate j1939cab to run things without complications
 *          of interfering with the main j1939cab. A j1939cab may be 
 *          called a j1939cab on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal j1939cab. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	06/12/2017 Generated
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


#ifndef         J1939CAB_H
#define         J1939CAB_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939cab_data_s	J1939CAB_DATA;    // Inherits from OBJ.

    typedef struct j1939cab_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939cab_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939CAB_DATA *);
    } J1939CAB_VTBL;



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
     @return:   pointer to j1939cab object if successful, otherwise OBJ_NIL.
     */
    J1939CAB_DATA * j1939cab_Alloc(
    );
    
    
    J1939CAB_DATA * j1939cab_New(
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         j1939cab_getLastError(
        J1939CAB_DATA   *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         j1939cab_Disable(
        J1939CAB_DATA	*this
    );


    ERESULT         j1939cab_Enable(
        J1939CAB_DATA	*this
    );

   
    J1939CAB_DATA * j1939cab_Init(
        J1939CAB_DATA   *this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );


    ERESULT         j1939cab_IsEnabled(
        J1939CAB_DATA	*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939cab_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939CAB object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939cab_ToDebugString(
        J1939CAB_DATA   *this,
        int             indent
    );
    
    
    bool            j1939cab_TransmitPgn61443(
        J1939CAB_DATA	*this
    );
    
    
    bool            j1939cab_TransmitPgn65217(
        J1939CAB_DATA	*this
    );
    
    
    bool            j1939cab_TransmitPgn65261(
        J1939CAB_DATA	*this
    );
    
    
    bool            j1939cab_TransmitPgn65265(
        J1939CAB_DATA	*this
    );
    
    
    bool            j1939cab_TransmitPgn65269(
        J1939CAB_DATA	*this
    );
    
    
    bool            j1939cab_TransmitPgn65271(
        J1939CAB_DATA	*this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939CAB_H */

