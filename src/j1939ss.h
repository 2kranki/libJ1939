// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//   J1939 Shift Selector Contoller Application (j1939ss) Header
//****************************************************************
/*
 * Program
 *			J1939 Shift Selector Contoller Application (j1939ss)
 * Purpose
 *			This object provides a Shift Selector Contoller for
 *          shifting gears.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/08/2017 Generated
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


#ifndef         J1939SS_H
#define         J1939SS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939ss_data_s	J1939SS_DATA;    // Inherits from OBJ.

    typedef struct j1939ss_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939ss_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939SS_DATA *);
    } J1939SS_VTBL;



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
     @return:   pointer to j1939ss object if successful, otherwise OBJ_NIL.
     */
    J1939SS_DATA *     j1939ss_Alloc(
        void
    );
    
    
    J1939SS_DATA *     j1939ss_New(
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         j1939ss_getLastError(
        J1939SS_DATA	*this
    );


    // Requested Torque / Torque Limit
    uint8_t         j1939ss_getSpn518(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn518(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Override Control Mode
    uint8_t			j1939ss_getSpn695(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn695(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Requested Speed Control Conditions
    uint8_t			j1939ss_getSpn696(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn696(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Override Control Mode Priority
    uint8_t			j1939ss_getSpn897(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn897(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Requested Speed / Speed Limit
    uint16_t		j1939ss_getSpn898(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn898(
        J1939SS_DATA	*this,
        uint16_t		value
    );
    
    
    // Transmission Requested Range Display
    uint8_t			j1939ss_getSpn1849(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn1849(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Requested Range Display
    uint8_t			j1939ss_getSpn1850(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn1850(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Shift Inhibit Indicator
    uint8_t			j1939ss_getSpn1851(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn1851(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Mode 1 Indicator
    uint8_t			j1939ss_getSpn2536(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn2536(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Mode 2 Indicator
    uint8_t			j1939ss_getSpn2537(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn2537(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Mode 3 Indicator
    uint8_t			j1939ss_getSpn2538(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn2538(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Mode 4 Indicator
    uint8_t			j1939ss_getSpn2539(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn2539(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Engine Crank Enable
    uint8_t			j1939ss_getSpn2900(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn2900(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Active Shift Console Indicator
    uint8_t			j1939ss_getSpn2945(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn2945(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Ready for Brake Release
    uint8_t			j1939ss_getSpn3086(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn3086(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // Transmission Requested Gear Feedback
    uint8_t			j1939ss_getSpn3289(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn3289(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // TSC1 Transmission Rate
    uint8_t			j1939ss_getSpn3349(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn3349(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    
    // TSC1 Control Purpose
    uint8_t			j1939ss_getSpn3350(
        J1939SS_DATA	*this
    );
    
    bool			j1939ss_setSpn3350(
        J1939SS_DATA	*this,
        uint8_t         value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    J1939SS_DATA *  j1939ss_Init(
        J1939SS_DATA    *this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939ss_ToDebugString(this,4);
     @endcode
     @param     this    J1939SS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    j1939ss_ToDebugString(
        J1939SS_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939SS_H */

