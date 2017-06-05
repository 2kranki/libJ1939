// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939 SYS Test Object (j1939sys) Header
//****************************************************************
/*
 * Program
 *			J1939 SYS Test Object (j1939sys)
 * Purpose
 *			This object provides a means of testing the operation
 *          of libJ1939 without actually having the library connected
 *          to a CAN Port and using an O/S. It requires j1939can as well.
 *
 * Remarks
 *	1.      J1939SYS_VTBL must be in sync with the J1939_SYS_VTBL in
 *          j1939_defs.h
 *  2.      This object is only used in a test environment and not
 *          needed in an operational environment.
 *
 * History
 *	04/06/2017 Generated
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
#include        <j1939_defs.h>


#ifndef         J1939SYS_H
#define         J1939SYS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939sys_data_s	J1939SYS_DATA;    // Inherits from OBJ.

    typedef struct j1939sys_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939Sys_object.c.
        // Properties:
        // Methods:
        uint32_t        (*pTimeMS)(OBJ_ID);             // Return the system time
        //                                              // in milliseconds.
        uint32_t        (*pSleepMS)(OBJ_ID, uint32_t);  // Sleep for N ms and return
        //                                              // amount of time slept (ms)
        uint32_t        (*pBumpMS)(OBJ_ID, uint32_t);   // Increase the system time
        //                                              // by the specified amount.
        uint32_t        (*pTimeReset)(OBJ_ID, uint32_t);// Set the system time
        //                                              // to the specified amount.
    } J1939SYS_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    J1939SYS_DATA *     j1939sys_Alloc(
    );
    
    
    J1939SYS_DATA *     j1939sys_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     j1939sys_getLastError(
        J1939SYS_DATA	*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint32_t    j1939sys_BumpMS(
        J1939SYS_DATA   *this,
        uint32_t        ms
    );
    
    
    ERESULT     j1939sys_Disable(
        J1939SYS_DATA	*this
    );


    ERESULT     j1939sys_Enable(
        J1939SYS_DATA	*this
    );

   
    J1939SYS_DATA * j1939sys_Init(
        J1939SYS_DATA   *this
    );


    /*!
     Simulate sleeping for ms milliseconds.
     @param:    this    J1939SYS object pointer
     @param:    ms      Time to sleep in ms
     @return:   returns the current test time
     */
    uint32_t    j1939sys_SleepMS(
        J1939SYS_DATA   *this,
        uint32_t        ms
    );
    
    
    /*!
     Return the current time in MS (milliseconds).
     @param:    this    J1939SYS object pointer
     @return:   returns the current test time
     */
    uint32_t    j1939sys_TimeMS(
        J1939SYS_DATA   *this
    );
    
    
    /*!
     Reset the time to the given value.
     @param:    this    J1939SYS object pointer
     @param:    ms      Time to sleep in ms
     @return:   returns the current test time
     */
    uint32_t    j1939sys_TimeReset(
        J1939SYS_DATA   *this,
        uint32_t        ms
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939Sys_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939SYS object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA * j1939sys_ToDebugString(
        J1939SYS_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939SYS_H */

