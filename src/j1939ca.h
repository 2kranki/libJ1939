/****************************************************************
 *          J1939 Controller Application (j1939ca)
 ****************************************************************/
/*
 * Program
 *				J1939 Controller Application (j1939ca)
 * Purpose
 *				This object provides the Controller Application
 *              Support for the J1939 object. It handles all its
 *              messages as well as other housekeeping functions.
 *
 *              It maintains a NAME and Claimed address.
 *
 *              Each Controller Application must go through an
 *              address claim procedure before they have an address
 *              that they can use for talking to other CAs.
 *
 *              Since all messages for the CA are funneled through
 *              this object, we handle the Data Link Support here
 *              as well including PGN Requests and Transport
 *              Protocol messages.
 *
 *              A CA has 3 main objectives:
 *                  1. Handle inbound requests
 *                  2. Transmit timed messages related to CA Functionality
 *                  3. Handle responses or timeouts generated by requests
 *                      and it is meant to be inherited.
 *
 * Remarks
 *	**			Certain external functions must be set up before this object
 *              is put into a running state:
 *                  MsClock - to get the current clock in milli-seconds
 *                            (tn_sys_time_get if TNEO) or sleep N milli-seconds
 *  **          The spn's for the Data Link Layer message can be found in
 *              Appendix D of J1939-21.
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


#define j1989_CA_TP_SIZE 1
// Max Transport Protocol's (TP) at once (both rcv and xmt)
#define j1989_CA_TIMED_XMT_QUEUE_SIZE 4   // Zero if you do not want


#include        <j1939_defs.h>
#include        <j1939data.h>


#ifndef J1939CA_H
#define J1939CA_H	1


//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************

#ifdef	__cplusplus
extern	"C" {
#endif

    typedef struct j1939ca_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939ca_object.c.
        // Properties:
        // Methods:
        //      PGN 59392  E800 - Responders (default is do nothing)
        void            (*pHandleACK)(
                                      OBJ_ID,
                                      uint8_t,      // Group Function
                                      uint8_t,      // Address
                                      J1939_PGN     // PGN being Responded to
                        );
        void            (*pHandleNAK)(
                                      OBJ_ID,
                                      uint8_t,      // Group Function
                                      uint8_t,      // Address
                                      J1939_PGN     // PGN being Responded to
                        );
        void            (*pHandleDenied)(
                                         OBJ_ID,
                                         uint8_t,      // Group Function
                                         uint8_t,      // Address
                                         J1939_PGN     // PGN being Responded to
                        );
        void            (*pHandleBusy)(
                                       OBJ_ID,
                                       uint8_t,     // Group Function
                                       uint8_t,      // Address
                                       J1939_PGN    // PGN being Responded to
                        );
    } J1939CA_VTBL;
    
    
    
    // J1939CA Message Setup Routine definition
    /*! 
     Set up PDU and Msg using object data.
     @param     this    object pointer
     @param     pPDU    input PDU pointer
     @param     cData   size of the supplied message data area
     @param     pData   Message Output Data Area Ptr
     @param     pLen    returned size actually used in the data area
     */
    typedef bool (*P_CA_MSGSETUP_RTN) (
        OBJ_ID          this,           // Object Ptr
        J1939_PDU       *pPDU,          // PDU (J1939) Ptr
        uint16_t        cData,          // data area size
        void            *pData,         // Message Output Data Area Ptr
        uint16_t        *pLen           // data output actually used size (returned)
    );

    
    // PGN Table Entry
#pragma pack(push, 1)
    typedef struct j1939ca_pgn_entry_s {
        const
        J1939_PGN_ENTRY *pDef;          // Definition
        // Handle a Standard 8-Byte Incoming Message
        const
        P_SRVCMSG_RTN   pService;   // First parameter is assumed to be the responder
                                    // object ptr who handles the incoming message.
        // Handle a Variable Length Incoming Message
        const
        P_VARMSG_RTN    pDataMsg;   // First parameter is assumed to be the responder
                                    // object ptr who handles the incoming message.
        const
        P_SETUP_MSG_RTN pDataSetup;
        const
        uint32_t        xmtTimeoutOff;  // Offset of Timeout repeat xmt
        const
        uint8_t         da;             // Destination Address if applicable
        const
        uint8_t         rsvd;
        const
        uint16_t        msXmtRepeat;
    } J1939CA_PGN_ENTRY;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
    typedef struct j1939ca_pgn_table_s {
        const
        uint16_t            cPGNs;
        const
        uint16_t            reserved16;
        const
        J1939CA_PGN_ENTRY   *(* const pPGNs)[];
                                        // PGN Index Ptr - It is assumed that they are
                                        //                  sorted by ascending PGN with
                                        //                  NULL terminator.
    } J1939CA_PGN_TABLE;
#pragma pack(pop)
    
    

    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    J1939CA_DATA * j1939ca_Alloc(
        void
    );
    
        
    OBJ_ID          j1939ca_Class(
        void
    );


    J1939CA_DATA *	j1939ca_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJ_ID          j1939ca_getCAN(
        J1939CA_DATA	*this
    );
    
    bool            j1939ca_setCAN(
        J1939CA_DATA	*this,
        OBJ_ID          pValue
    );
    
    
    uint8_t         j1939ca_getClaimedAddress(
        J1939CA_DATA	*this
    );
    
    
    P_SRVCMSG_RTN   j1939ca_getHandler(
        J1939CA_DATA	*this
    );

    
    ERESULT         j1939ca_getLastError(
        J1939CA_DATA    *this
    );
    
    
    J1939_NAME *    j1939ca_getName(
        J1939CA_DATA	*this
    );
    
    
    // Engine Intercooler Temperature
    uint32_t		j1939ca_getSoftwareLevel(
        J1939CA_DATA	*this
    );
    
    bool			j1939en_setSoftwareLevel(
        J1939CA_DATA	*this,
        uint32_t		value
    );
    
    
    OBJ_ID          j1939ca_getSYS(
        J1939CA_DATA	*this
    );
    
    bool            j1939ca_setSYS(
        J1939CA_DATA	*this,
        OBJ_ID          pValue
    );
    
    
    bool            j1939ca_getTimedTransmits(
        J1939CA_DATA	*this
    );
    
    bool            j1939ca_setTimedTransmits(
        J1939CA_DATA	*this,
        bool            value
    );
    
    
    bool			j1939ca_setXmtMsgDL(
        J1939CA_DATA	*this,
        P_J1939_XMTRTN  pXmtMsg,
        void            *pData
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* HandleMessages() serves two purposes. The first is to try to
     * handle any received messages. The second is to perform func-
     * tions such as transmitting messages on a timed basis. This
     * function assumes that it will be called consistantly enough
     * (ie 10ms - 20ms) so that it can perform its functions.
     * It returns true if it handled the message given otherwise false.
     */
    bool            j1939ca_HandleMessages(
        J1939CA_DATA	*this,
        J1939_MSG       *pMsg           // NULL == Time-out
    );
    
    
    // j1939ca_Open calculates the needed buffer size, allocates an
    // area and sets up the control portion of the j1939ca.
    J1939CA_DATA *	j1939ca_Init(
        J1939CA_DATA	*this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 NAME Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 NAME Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 NAME Industry Group (3 bits)
    );
        
    
    uint32_t        j1939ca_MsTimeGet(
        J1939CA_DATA	*this
    );
    
    
    bool            j1939ca_SendAccessDenied(
        J1939CA_DATA	*this,
        uint8_t         spn2546,    // Group Function Value (NACK_AD - 8 bits)
        uint8_t         spn3292,    // Address Negative Acknowlegement (ADD_AD - 8 bits)
        J1939_PGN       spn2547     // PGN (NACK_AD - 24 bits)
    );
    
    
    bool            j1939ca_SendACK(
        J1939CA_DATA	*this,
        uint8_t         spn2542,    // Group Function Value (ACK - 8 bits)
        uint8_t         spn3290,    // Address Acknowledged (ADD_ACK - 8 bits)
        J1939_PGN       spn2543     // PGN (ACK - 24 bits)
    );
    
    
    bool            j1939ca_SendBusy(
        J1939CA_DATA	*this,
        uint8_t         spn2548,    // Group Function Value (NACK_BUSY - 8 bits)
        uint8_t         spn3293,    // Address Negative Acknowlegement (ADD_BUSY - 8 bits)
        J1939_PGN       spn2549     // PGN (NACK_BUSY - 24 bits)
    );
    
    
    bool            j1939ca_SendNACK(
        J1939CA_DATA	*this,
        uint8_t         spn2561,    // Number of Packets that can be sent (TP.CM_CTS)
        uint8_t         spn2562,    // Next Packet Number to be sent (TP.CM_RTS)
        J1939_PGN       spn2563     // Parameter Group Number of packeted message (TP.CM_CTS)
    );
    
    
    bool            j1939ca_SendTP_CTS(
        J1939CA_DATA	*this,
        uint8_t         spn2558,    // Total Number of Packets (TP.CM_RTS)
        uint8_t         spn2559,    // Maximum Number of Packets (TP.CM_RTS)
        J1939_PGN       spn2560     // Parameter Group Number of packeted message (TP.CM_RTS)
    );
    
    
    bool            j1939ca_SendTP_RTS(
        J1939CA_DATA	*this,
        uint16_t        spn2557,    // Total Message Size (TP.CM_RTS)
        uint8_t         spn2558,    // Total Number of Packets (TP.CM_RTS)
        uint8_t         spn2559,    // Maximum Number of Packets (TP.CM_RTS)
        J1939_PGN       spn2560     // Parameter Group Number of packeted message (TP.CM_RTS)
    );
    
    
    // Delayed messages could be handled by a separate task. This
    // function is designed to work in a psxThread to handle the
    // delayed messages.
    void            j1939ca_TaskBody(
        void            *pData
    );
    
    
    bool            j1939ca_TransmitPgn(
        J1939CA_DATA	*this,
        const
        J1939CA_PGN_ENTRY
                        *pPgnEntry
    );
    

    bool            j1939ca_TransmitPgnDa(
        J1939CA_DATA	*this,
        const
        J1939CA_PGN_ENTRY
                        *pPgnEntry,
        uint8_t         da
        );
    
    
    //              Acknowledgment Message
    bool            j1939ca_TransmitPgn59392(
         J1939CA_DATA	*this,
         uint8_t         type,               // (0-ACK, 1-NAK, 2-Access Denied, 3-Busy)
         uint8_t         grpFunc,            // Group Function (Use 0xFF if not needed)
         uint8_t         addr,
         J1939_PGN       pgn                 // PGN being requested
    );
    
    
    // "Request for PGN" to be transmitted.
    bool            j1939ca_TransmitPgn59904(
        J1939CA_DATA	*this,
        J1939_PGN       pgn,                // PGN being requested
        uint8_t         da                  // Destination Address
    );
    

    // PGN 61184 0xEF00 Proprietary A
    bool            j1939ca_TransmitPgn61184(
        J1939CA_DATA	*this,
        uint8_t         da,                 // Destination Address
        uint8_t         cData,
        uint8_t         *pData
    );
    
    
    // PGN 65242  0x00FEDA - Software Identification - SOFT
    bool            j1939ca_TransmitPgn65242(
        J1939CA_DATA	*this
    );
    
    
    bool            j1939ca_XmtMsgDL(
        J1939CA_DATA	*this,
        J1939_PDU       pdu,
        uint16_t        cData,
        void            *pData
    );
    
    
    
#ifdef	__cplusplus
};
#endif




#endif
