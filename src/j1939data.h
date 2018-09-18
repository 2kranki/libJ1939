// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939DATA Console Transmit Task (j1939data) Header
//****************************************************************
/*
 * Program
 *			Separate j1939data (j1939data)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate j1939data to run things without complications
 *          of interfering with the main j1939data. A j1939data may be 
 *          called a j1939data on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal j1939data. A testing unit simply calls
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


#ifndef         J1939DATA_H
#define         J1939DATA_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939data_data_s	J1939DATA_DATA;    // Inherits from OBJ.

    typedef struct j1939data_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939data_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939DATA_DATA *);
    } J1939DATA_VTBL;



    //---------------------------------------------------------------
    //                      *** PGN Table ***
    //---------------------------------------------------------------
    
    extern
    const
    J1939_PGN_ENTRY     pgn0_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn256_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn51456_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn57344_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn59392_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn59904_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn60160_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn60416_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn60928_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61184_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61440_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61441_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61442_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61443_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61444_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn64964_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61445_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65098_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65129_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65184_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65215_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65217_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65226_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65242_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65247_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65249_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65252_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65261_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65262_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65265_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65266_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65269_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65271_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65272_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65275_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65279_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65280_entry;
    
    
    
    
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
     @return:   pointer to j1939data object if successful, otherwise OBJ_NIL.
     */
    J1939DATA_DATA * j1939data_Alloc(
        void
    );
    
    
    J1939DATA_DATA * j1939data_New(
        void
    );
    
    
    const
    J1939_PREFERRED_ADDRESS * j1939data_Find_Adr(
        uint8_t         adr
    );
    
    
    const
    J1939_PGN_ENTRY * j1939data_Find_Pgn(
        J1939_PGN       pgn
    );
    
    
    const
    J1939_PGNSPN *  j1939data_FindPgnSpn(
        J1939_PGN       pgn,
        uint32_t        spn
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         j1939data_getLastError(
        J1939DATA_DATA	*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         j1939data_Disable(
        J1939DATA_DATA	*this
    );


    ERESULT         j1939data_Enable(
        J1939DATA_DATA	*this
    );

   
    J1939DATA_DATA * j1939data_Init(
        J1939DATA_DATA  *this
    );


    ERESULT         j1939data_IsEnabled(
        J1939DATA_DATA	*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939data_ToDebugString(this,4);
     @endcode
     @param     this    J1939DATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939data_ToDebugString(
        J1939DATA_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939DATA_H */

