/****************************************************************
 *              J1939 Transmission CA (j1939tc)
 ****************************************************************/
/*
 * Program
 *				J1939 Transmission CA (j1939tc)
 * Purpose
 *				This object provides the Transmission Support
 *              for the J1939 object. The CA associated with this
 *              object should insure that the internal Claimed
 *              Address is kept up to date.
 *
 *              To support these PGNs, the CA must call the
 *              HandleMessage() method fairly consistently.
 *              One message is expected every 50ms. Others are
 *              at larger intervals.
 *              
 *              The PGNs associated with the Transmission are:
 *                  0 TSC1 : spn 695, 897,518 (rcv from Transmission (SA == 3))
 *                  61440 ERC1 : spn 571,520  (xmt)
 *                  65249 RC :   spn  (xmt)
 *
 *
 * Remarks
 *	1.			This object does not claim its name. It just assumes that it
 *              has it.
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
#include        <j1939ca.h>



#ifndef J1939TC_H
#define J1939TC_H	1





#ifdef	__cplusplus
extern	"C" {
#endif
    
    
    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************
    
    //typedef struct j1939tc_data_s	J1939TC_DATA;     // Inherits from OBJ.
    //          defined in j1939_defs.h
    
    typedef struct j1939tc_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;                  // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lru_object.c.
        // Properties:
        // Methods:
    } J1939TC_VTBL;
    
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    // Warning - See J1939CAM, but this function may not change.
    J1939TC_DATA * j1939tc_Alloc(
        void
    );
    
        
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    bool            j1939tc_HandleTimedTransmits(
        J1939TC_DATA	*this
    );
    
    
    J1939TC_DATA *	j1939tc_Init(
        J1939TC_DATA	*this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
        

    bool            j1939tc_TransmitPgn61440(
        J1939TC_DATA	*this
    );
    
    
    bool            j1939tc_TransmitPgn65249(
        J1939TC_DATA	*this
    );
    
        
    

    
#ifdef	__cplusplus
};
#endif




#endif
