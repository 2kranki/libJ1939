// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939TCU Console Transmit Task (j1939tcu) Header
//****************************************************************
/*
 * Program
 *			Separate j1939tcu (j1939tcu)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate j1939tcu to run things without complications
 *          of interfering with the main j1939tcu. A j1939tcu may be 
 *          called a j1939tcu on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal j1939tcu. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
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


#ifndef         J1939TCU_H
#define         J1939TCU_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939tcu_data_s	J1939TCU_DATA;    // Inherits from J1939CU

    typedef struct j1939tcu_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939tcu_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939TCU_DATA *);
    } J1939TCU_VTBL;



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
     @return:   pointer to j1939tcu object if successful, otherwise OBJ_NIL.
     */
    J1939TCU_DATA * j1939tcu_Alloc(
    );
    
    
    J1939TCU_DATA * j1939tcu_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     j1939tcu_getLastError(
        J1939TCU_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         j1939tcu_Disable(
        J1939TCU_DATA	*this
    );


    ERESULT         j1939tcu_Enable(
        J1939TCU_DATA	*this
    );

   
    /*!
     Passed messages from a message source such as a CAN FIFO Receive
     Queue. This routine handles the message either internally or via
     its responder chain. It should be called about every 10ms even
     if a message is not available. A NULL message pointer and zero
     eid, tell the Handler to simply process any time transmitted
     messages.
     @param:    this    J1939ECU object pointer
     @param:    eid     Message EID
     @param:    pMsg    Message Pointer or NULL
     @return:   if successful, true otherwise, false
     @Warning:  This function must conform to P_SRVCMSG_RTN specs.
     */
    bool            j1939tcu_HandleMessages(
        J1939TCU_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    J1939TCU_DATA * j1939tcu_Init(
        J1939TCU_DATA   *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );


    ERESULT         j1939tcu_IsEnabled(
        J1939TCU_DATA	*this
    );
    
 
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
    ASTR_DATA *    j1939tcu_ToDebugString(
        J1939TCU_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939TCU_H */

