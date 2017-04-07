/****************************************************************
 *                  J1939 Engine #1 CA (j1939en)
 ****************************************************************/
/*
 * Program
 *				J1939 Engine #1 CA (j1939en)
 * Purpose
 *				This object provides the Engine Status Support
 *              for the J1939 object. The CA associated with this
 *              object should insure that the internal Claimed
 *              Address is kept up to date.
 *
 *              To support these PGNs, the CA must call the
 *              HandleMessage() method fairly consistently.
 *              One message is expected every 50ms. Others are
 *              at larger intervals.
 *              
 *              The PGNs associated with the Engine Layer are:
 *                  (?)256* : spn 1852,1853,1854,1855
 *                  61443* : spn 91,92
 *                  61444* : spn 513
 *                  65262* : spn 110
 *                  65265* : spn 84
 *                  65270* : spn 102
 *
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



#ifndef J1939EN_H
#define J1939EN_H	1




#ifdef	__cplusplus
extern	"C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************
    
    //typedef struct j1939en_data_s	J1939EN_DATA;     // Inherits from OBJ.
    //          defined in j1939_defs.h
    
    typedef struct j1939en_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;                  // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lru_object.c.
        // Properties:
        // Methods:
    } J1939EN_VTBL;
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    // Warning - See J1939CAM, but this function may not change.
    J1939EN_DATA * j1939en_Alloc(
    );
    
        
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool			j1939en_setShiftExit(
        J1939EN_DATA	*this,
        P_VOIDEXIT12    pExit,
        void            *pData
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    // j1939en_AddData adds Data to the end of the buffer.
    bool			j1939en_AddData(
        J1939EN_DATA	*this,
        uint16_t        size,
        void            *data
    );
    
   
    // j1939en_Open calculates the needed buffer size, allocates an
    // area and sets up the control portion of the j1939en.
    // Warning - See J1939CAM, but this function may not change.
    J1939EN_DATA *	j1939en_Init(
        J1939EN_DATA	*this,
        J1939CAM_DATA   *pCAM,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    );
        

    bool            j1939en_HandleTimedTransmits(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn61443(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn61444(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65129(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65247(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65262(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65265(
        J1939EN_DATA	*this
    );
    
    

    
#ifdef	__cplusplus
};
#endif




#endif
