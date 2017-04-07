/****************************************************************
 *              J1939 Data Link (j1939dl) Support
 ****************************************************************/
/*
 * Program
 *				J1939 Data Link (j1939dl) Support
 * Purpose
 *				This object provides the Data Link Support
 *              for the J1939 object.
 *              
 *              The PGNs associated with the Data Link Layer are:
 *                  59904 (Request PG) Used to request a PGN from network device(s)
 *                  59392 (Acknowledgement) is used to provide a handshake mechanism
 *                          between transmitting and receiving devices
 *                  51456 (Request2) Used to request a PGN from network device or
 *                          devices and to specify whether the response should use
 *                          the Transfer PGN () or not.
 *                  51712 (Transfer) Used for transfer of data in response to a
 *                          Request2 (51456) PGN when the "Use Transfer PGN for
 *                          response" is set to "Yes"
 *                  60416 (Transport Protocol - Connection Management)
 *                  60160 (Transport Protocol - Data Transfer)
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
//#include        "j1939tbl.h"


#ifndef J1939DL_H
#define J1939DL_H	1


//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************

#ifdef	__cplusplus
extern	"C" {
#endif
    

    typedef struct j1939dl_data_s		J1939DL_DATA;

    typedef struct j1939dl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939ca_object.c.
        // Properties:
        // Methods:
    } J1939DL_VTBL;
    
    
    
    
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    J1939DL_DATA * j1939dl_Alloc(
    );
    
        
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    J1939_CAN_VTBL * j1939dl_getCAN(
        J1939DL_DATA	*this
    );
    
    bool            j1939dl_setCAN(
        J1939DL_DATA	*this,
        J1939_CAN_VTBL  *pValue
    );
    
    
    uint8_t         j1939dl_getClaimedAddress(
        J1939DL_DATA	*this
    );
    
    bool			j1939dl_putClaimedAddress(
        J1939DL_DATA	*this,
        uint8_t         value
    );
    
    
    uint32_t        j1939dl_getEid(
        J1939DL_DATA	*this
    );
    
    bool			j1939dl_putEid(
        J1939DL_DATA	*this,
        uint32_t        value
    );
    
    
    uint32_t        j1939dl_getMask(
        J1939DL_DATA	*this
    );

    bool			j1939dl_putMask(
        J1939DL_DATA	*this,
        uint32_t        value
    );
    
   
    bool			j1939dl_setReceivePacket(
        J1939DL_DATA	*this,
        void            (*receivePacket)(void *, void *),
        void            *pData
    );
    
    
    J1939_SYS_VTBL * j1939dl_getSYS(
        J1939DL_DATA	*this
    );
    
    bool            j1939dl_setSYS(
        J1939DL_DATA	*this,
        J1939_SYS_VTBL  *pValue
    );
    
    
    bool			j1939dl_setXmtMsg(
        J1939DL_DATA    *this,
        P_XMTMSG_RTN    pXmtMsg,
        void            *pData
    );

    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    // j1939dl_AddData adds Data to the end of the buffer.
    bool			j1939dl_AddData(
        J1939DL_DATA	*this,
        uint16_t        size,
        void            *data
    );
    
   
    // j1939dl_Open calculates the needed buffer size, allocates an
    // area and sets up the control portion of the j1939dl.
    J1939DL_DATA *	j1939dl_Init(
        J1939DL_DATA	*this,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_PTR         pData
    );
        

    bool            j1939dl_HandlePacket(
        J1939DL_DATA	*this,
        uint32_t        pgn,
        void            *pPacket
    );
    
    
    bool            j1939dl_XmtMsgDL(
        J1939DL_DATA	*this,
        uint32_t        msDelay,
        J1939_PDU       pdu,
        uint16_t        cData,
        void            *pData
    );
    
    
    
#ifdef	__cplusplus
};
#endif




#endif
