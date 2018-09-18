/****************************************************************
 *              J1939 Diagnostic Support (j1939dg)
 ****************************************************************/
/*
 * Program
 *				J1939 Diagnostic Support (j1939dg)
 * Purpose
 *
 * Remarks
 *	1.			None
 * References
 *		"J1939-21 Data Link Layer", SAE, DEC 2006
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


#ifndef J1939DG_H
#define J1939DG_H	1


//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************

#ifdef	__cplusplus
extern	"C" {
#endif
    

    typedef struct j1939dg_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939ca_object.c.
        // Properties:
        // Methods:
    } J1939DG_VTBL;
    
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    // Warning - See J1939CAM, but this function may not change.
    J1939DG_DATA * j1939dg_Alloc(
        void
    );
    
        
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    // j1939dg_AddData adds Data to the end of the buffer.
    bool			j1939dg_AddData(
        J1939DG_DATA	*this,
        uint16_t        size,
        void            *data
    );
    
   
    bool            j1939dg_HandleTimedTransmits(
        J1939DG_DATA	*this
    );
    
    
    // j1939dg_Open calculates the needed buffer size, allocates an
    // area and sets up the control portion of the j1939dg.
    // Warning - See J1939CAM, but this function may not change.
    J1939DG_DATA *	j1939dg_Init(
        J1939DG_DATA	*this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
        

    bool            j1939dg_TransmitPgn61440(
        J1939DG_DATA	*this
    );
    
    
    bool            j1939dg_TransmitPgn65249(
        J1939DG_DATA	*this
    );
    
        
    

    
#ifdef	__cplusplus
};
#endif




#endif
