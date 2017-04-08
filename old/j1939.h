/****************************************************************
 *                Protocol Layer (j1939) Support  Header
 ****************************************************************/
/*
 * Program
 *				Protocol Layer (j1939) Support Subroutines
 * Purpose
 *				J1939 protocol lives on top of the CAN system. It
 *              consists of ECUs which may have one or more Con-
 *              troller Applications within it. Each Controller
 *              Application has a NAME and will claim an address.
 *
 *				J1939 supports messages of up to 1875 bytes. However,
 *              most messages are 8 bytes in length or less. Requests
 *              for a specific PGN are supported.
 *
 *              Each Controller Application must go through an
 *              address claim procedure before they have an address
 *              that they can use for talking to other CAs.
 *
 *              Bus loads: 8 bytes of data with stuff bits seems
 *                  to be about 155 bits. 250 Kbps gives about
 *                  620 us per msg. 10,000/620 = 16 msgs per 10 ms
 *                  or max of about 1600 msgs per sec
 *
 * Remarks
 *	1.			When we first start up, we set up our CAN Port to
 *              support our protocol.
 *  2.          The combined size of the control, header and data
 *              portions of the j1939 is limited to 64k.
 * History
 *	12/01/14	Adapted for cmnLib.
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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


#ifndef J1939_H
#define J1939_H	1




#ifdef	__cplusplus
extern	"C" {
#endif
    
    
    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************
    
    //typedef struct j1939_data_s	J1939_DATA;     // Inherits from OBJ.
    //          defined in j1939_defs.h
    
    typedef struct j1939_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;                  // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lru_object.c.
        // Properties:
        // Methods:
    } J1939_VTBL;
    
    
    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    J1939_DATA *    j1939_Alloc(
    );
    
        
    J1939_DATA *    j1939_NewEngine(
        uint8_t         port,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    );
    
    
    J1939_DATA *    j1939_NewTransmission(
        uint8_t         port,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    );
    
    
    J1939_DATA *    j1939_Shared(
        uint8_t         port
    );
    
    void            j1939_SharedReset(
    );
    
    void            j1939_SharedSet(
        uint8_t         port,
        J1939_DATA      *this
    );

    
    int32_t     j1939_SpnToS32(
        J1939_SPN_TYPE  *pType,
        uint16_t        data            // Data In
    );
    
    
   
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJ_ID          j1939_getCAM(
        J1939_DATA		*this
    );
    
    
    J1939_CAN_VTBL * j1939_getCAN(
        J1939_DATA		*this
    );
    
    bool            j1939_setCAN(
        J1939_DATA		*this,
        J1939_CAN_VTBL  *pValue
    );
    
    
    // Claimed Address
    uint8_t         j1939_getClaimed(
        J1939_DATA		*this
    );

    
    // NAME Field - Identity Number
    uint32_t        j1939_getSPN2837(
        J1939_DATA		*this
    );
    
    bool            j1939_setSPN2837(
        J1939_DATA		*this,
        uint32_t        value
    );
    
    
    // NAME Field - Manufacturer Code
    uint16_t        j1939_getSPN2838(
        J1939_DATA		*this
    );
    
    bool            j1939_setSPN2838(
        J1939_DATA		*this,
        uint16_t        value
    );
    

    // NAME Field - Industry Group
    uint8_t         j1939_getSPN2846(
        J1939_DATA		*this
    );
    
    bool            j1939_setSPN2846(
        J1939_DATA		*this,
        uint8_t         value
    );
    
    
    J1939_SYS_VTBL * j1939_getSYS(
        J1939_DATA		*this
    );
    
    bool            j1939_setSYS(
        J1939_DATA		*this,
        J1939_SYS_VTBL  *pValue
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    /* AddMessageResponder() adds message responders to the Message
     * Handler queue. As each message is received, it will be dispatched
     * to each responder in the queue.
     */
    bool            j1939_AddMessageResponder(
        J1939_DATA      *this,
        P_SRVCMSG_RTN   pSrvcMsg,
        OBJ_PTR         pSrvcData
    );
    
    
    bool            j1939_Disable(
        OBJ_ID          objId
    );
    
    
    bool            j1939_Enable(
        OBJ_ID          objId
    );
    
    
    /* HandleMessages() is passed messages from a message source such
     * as a CAN FIFO Receive Queue. This routine sends the message
     * to each responder previously defined with addResponder().
     * Warning: This function and all responders must conform to 
     * P_SRVCMSG_RTN specs.
     */    
    bool            j1939_HandleMessages(
        J1939_DATA      *this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    J1939_DATA *	j1939_Init(
        J1939_DATA		*this,
        uint8_t         port
    );
        

    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = j1939_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939 object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939_ToDebugString(
        J1939_DATA      *this,
        int             indent
    );
    
    
    void            j1939_XmtMsg(
        J1939_DATA		*this,
        uint32_t        msDelay,
        J1939_MSG       *pMsg
    );
    
    
    void            j1939_XmtMsgDL(
        J1939_DATA		*this,
        uint32_t        msDelay,
        J1939_PDU       pdu,
        uint16_t        cData,          // Data Length (1..1785)
        uint8_t         *pData
    );


    
    
    //---------------------------------------------------------------
    //                      *** SPN Types Table ***
    //---------------------------------------------------------------
    
#ifdef XYZZY
    extern
    const
    J1939_SPN_TYPE      SAEpc05;
    extern
    const
    J1939_SPN_TYPE      SAEpr07;
#endif
    
    
    
    //---------------------------------------------------------------
    //                      *** PGN Table ***
    //---------------------------------------------------------------
    
#ifdef XYZZY
    extern
    const
    J1939_PGN_ENTRY     pgn0_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn256_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn59392_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn59904_entry;
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
    J1939_PGN_ENTRY     pgn61442_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61443_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn61444_entry;
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
    J1939_PGN_ENTRY     pgn65226_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65247_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65249_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65262_entry;
    extern
    const
    J1939_PGN_ENTRY     pgn65265_entry;
#endif
    
    
#ifdef	__cplusplus
};
#endif




#endif
