// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939 Cab Controller CA (j1939cc) Header
//****************************************************************
/*
 * Program
 *			J1939 Cab Controller CA (j1939cc)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate j1939cc to run things without complications
 *          of interfering with the main j1939cc. A j1939cc may be 
 *          called a j1939cc on other O/S's.
 *          Transmitted Messages:
 *              AMB  FEF5 65269
 *              CCVS FEF1 65265
 *              CM1  E000 57344
 *              DM01 FECA 65226
 *              EEC2 F003 61443
 *              VDHR FEC1 65217
 *              VEP1 FEF7 65271
 *
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal j1939cc. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	04/15/2017 Generated
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





#include        <cmn_defs.h>
#include        <AStr.h>


#ifndef         J1939CC_H
#define         J1939CC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939cc_data_s	J1939CC_DATA;    // Inherits from OBJ.

    typedef struct j1939cc_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939cc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939CC_DATA *);
    } J1939CC_VTBL;



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
     @return:   pointer to j1939cc object if successful, otherwise OBJ_NIL.
     */
    J1939CC_DATA *     j1939cc_Alloc(
    );
    
    
    J1939CC_DATA *     j1939cc_New(
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            j1939cc_setCCU(
        J1939CC_DATA    *this,
        OBJ_ID          pValue
    );
    
    
    ERESULT     j1939cc_getLastError(
        J1939CC_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     j1939cc_Disable(
        J1939CC_DATA		*this
    );


    ERESULT     j1939cc_Enable(
        J1939CC_DATA		*this
    );

   
    J1939CC_DATA *   j1939cc_Init(
        J1939CC_DATA     *this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );


    ERESULT     j1939cc_IsEnabled(
        J1939CC_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939cc_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939CC object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    j1939cc_ToDebugString(
        J1939CC_DATA     *this,
        int             indent
    );
    
    
    bool            j1939cc_TransmitPgn57344(
        J1939CC_DATA	*this
    );
    
    
    bool            j1939cc_TransmitPgn61443(
        J1939CC_DATA	*this
    );
    
    
    bool            j1939cc_TransmitPgn65217(
        J1939CC_DATA	*this
    );
    
    
    bool            j1939cc_TransmitPgn65261(
        J1939CC_DATA	*this
    );
    
    
    bool            j1939cc_TransmitPgn65265(
        J1939CC_DATA	*this
    );
    
    
    bool            j1939cc_TransmitPgn65269(
        J1939CC_DATA	*this
    );

    
    bool            j1939cc_TransmitPgn65271(
        J1939CC_DATA	*this
    );
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* J1939CC_H */

