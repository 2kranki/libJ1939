// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//                J1939 Message (j1939msg) Support
//****************************************************************
/*
 * Program
 *				J1939 Message (j1939msg) Support
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to manipulate J1939 messages used by the
 *              J1939 system.
  *
 *
 * Remarks
 *	1.			XC32 allows 4 register variables per function call.
 *	            So, we will restrict most function calls to 4 or less.
 *  2.          We handle sid and eid as unique fields. However, you might
 *              want to handle them as one extended id as follows.
 *                  exid &= 0x1FFFFFFF;     // Mask off exid bits.
 *                  sid = (exid & 0x1FFC0000) >> 18;
 *                  eid = (exid & 0x0003FFFF);
 *                  sid = (sid & 0x07FF);
 * History
 *	12/09/2014	Created from canmsg sources.
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




#include        <stdint.h>
#include        <obj.h>



#ifndef j1939msg_H
#define	j1939msg_H 1






//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************

typedef struct j1939_msg_s  J1939_MSG;
typedef struct j1939_name_s J1939_NAME;
typedef struct j1939_pdu_s  J1939_PDU;
typedef struct j1939_pgn_s  J1939_PGN;


/* *** Common Message Routine Definitions ***
 */

/* Service() tries to handle the supplied message.
 * Returns:
 *      true == successful
 *      otherwise false
 */
typedef bool (*P_SRVCMSG_RTN) (
            OBJ_ID      ,                       // Object Ptr
            uint32_t    ,                       // EID
            J1939_MSG   *
        );

typedef bool (*P_XMTMSG_RTN) (
            OBJ_ID      ,                       // Object Ptr
            uint32_t    ,                       // msTime for Delay or Timeout
                                                // (-1(0xFFFFFFFF) == WAIT_INFINITE)
            J1939_MSG   *
        );

typedef int     (*P_VARMSG_RTN) (
    OBJ_ID      ,                       // Object Ptr
    uint32_t    ,                       // EID or PDU (j1939)
    uint16_t    ,                       // data area size
    void        *                       // Message Data Area
);

/*! Set up PDU and Msg using object data returning
 * amount of data used. 0 means an error.
 */
typedef int     (*P_SETUP_MSG_RTN) (
    OBJ_ID      ,                       // Object Ptr
    uint32_t    *,                      // EID or PDU (j1939) Ptr
    uint16_t    ,                       // data area size
    void        *                       // Message Data Area
);



//                  CAN Module Message Structure
// This defines the structure of messages that are sent or received
// through the CAN Module's FIFO queues. It supports CAN v2.0b with
// both standard and extended messages.

#ifndef J1939_MAKE_EXTENDED_ID
#define J1939_MAKE_EXTENDED_ID(sid,eid) (((sid & 0x7FF) << 18) | (eid & 0x7FFFF))
#endif
#ifndef J1939_EXTRACT_EID
#define J1939_EXTRACT_EID(eid) (eid & 0x7FFFF)
#endif
#ifndef J1939_EXTRACT_SID
#define J1939_EXTRACT_SID(eid) ((eid >> 18) & 0x7FF)
#endif


#pragma pack(push,1)
struct j1939_msg_s {
    union {
      struct {
        uint32_t SID:11;        // Standard Identifier
        uint32_t FILHIT:5;      // Filter Number that accepted msg (RX Only)
        uint32_t CMSGTS:16;     // CAN Message Timestamp - CANTMR if CANCAP == 1 (RX Only)
      };
      uint32_t  w:32;
      uint8_t   bytes[4];
    } CMSGSID;
    union {
      struct {
        uint32_t DLC:4;         // Data Length Code - (0-7 bytes) specific length
                                //                    0b1xxx == 8 bytes
        uint32_t RB0:1;         // Reserved bit 0 - must be set to '0'
        uint32_t :3;
        uint32_t RB1:1;         // Reserved bit 1 - must be set to '0'
        uint32_t RTR:1;         // Remote Transmission Request
        uint32_t EID:18;        // Extended Identifier
        uint32_t EXID:1;        // Extended Identifier Flag
                                //  1 == Msg will transmit Extended Identifier (XMT)
                                //  1 == Msg has Extended Identifier (RCV)
                                //  0 == Msg will transmit Standard Identifier (XMT)
                                //  0 == Msg has Standard Identifier (RCV)
        uint32_t SRR:1;         // Substitute Remote Request
                                //      In case of a standard message format (IDE = 0),
                                //      this bit is don?t care.
                                //      In case of an extended message format (IDE = 1),
                                //      this bit should always be set.
        uint32_t :2;
      };
      uint32_t  w:32;
      uint8_t   bytes[4];
    } CMSGEID;
    union {
        struct {
            uint32_t w0:32;
            uint32_t w1:32;
        };
        uint8_t     bytes[8];
        uint64_t    dw;
    } DATA;
};
#pragma pack(pop)




#pragma pack(push, 1)
typedef struct j1939msg_eid_entry_s {
    const
    uint32_t            eid;        // If J1939, PGN instead of EID.
    const
    P_SRVCMSG_RTN       pService;   // First parameter is assumed to be the responder
                                    // who handles the message.
} J939MSG_EID_ENTRY;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct j1939msg_eid_table_s {
    const
    uint16_t            cEids;
    const
    uint16_t            reserved;
    const
    J939MSG_EID_ENTRY   *pEids;
} J1939MSG_EID_TABLE;
#pragma pack(pop)




#pragma pack(push,1)
// J1939 defines the data as LSB first. So, it is in reverse order
// of what we would think. "J1939-81 Network Management" contains
// extensive documentation of these fields.
struct j1939_name_s {
    union {
        struct {
            // J1939_NAME0 is the first word of the NAME (ie data bytes 0-3 or w0).
            struct {
                union {
                    struct {
                        uint32_t IDN:21;        // Identity Number (SPN 2837)
                        uint32_t MFG:11;        // Manufacturer Code (SPN 2838)
                    };
                    struct {
                        uint32_t w0:32;
                    };
                };
            };
            // J1939_NAME1 is the second word of the NAME (ie data bytes 4-7 or w1).
            struct {
                union {
                    struct {
                        uint32_t ECU:3;         // ECU Instance (SPN 2840)
                        uint32_t FUI:5;         // Function Instance (SPN 2839)
                        uint32_t FU:8;          // Function (SPN 2841)
                        uint32_t RVSD:1;        // Reserved
                        uint32_t VS:7;          // Vehicle System (SPN 2842)
                        uint32_t VSI:4;         // Vehicle System Instance (SPN 2843)
                        uint32_t IG:3;          // Industry Group (SPN 2846)
                        uint32_t AAC:1;         // Arbitrary Address Capable (SPN 2844)
                    };
                    struct {
                        uint32_t w1:32;
                    };
                };
            };
        };
        uint64_t    dw;
    };
};
#pragma pack(pop)




// J1939_PDU is the same format as CAN's eid extended to 32 bits.
// There are two PDU formats, PDU1 Format (PS == Destination Address)
// and PDU2 Format (PS == Group Extension).

// The PDU1 Format provides the means to send messages to specific
// destination addresses. However, this limits the number of PGNs
// that can be used for this purpose since PS is used as the
// destination address and not part of the PGN. Proprietary PGNs
// for PDU1 messages are 61184 and 126720.

// The PDU2 format is only used for messages that are for general
// broadcast (globally addressed). In this format, PS is the Group
// Extension (GE) which is part of the PGN. Proprietaty PGNs for
// this format are 65280 through 65536.

#pragma pack(push,1)
struct j1939_pdu_s {
    union {
        struct {
            uint32_t SA:8;          // Source Address
                                    // 0..253 Device specific address
                                    // 254 == NULL Address
                                    // 255 == General Broadcast Address
            uint32_t PS:8;          // Destination Address
                                    //      0..253 Device specific address
                                    //      255 == General Broadcast Address
                                    //  or
                                    // Group Extension (if PF => 240(0xF0))
            uint32_t PF:8;          // PDU Format - determines the PDU format and
            //                      // is one of the fields used to determine the
            //                      // Parameter Group Number assigned to the data
            //                      // field.
            uint32_t DP:1;          // Data Page
            uint32_t EDP:1;         // Extended Data Page
            uint32_t P:3;           // Priority 0(Highest) - 7(Lowest)
            uint32_t :3;            // Reserved
        };
        struct {
            uint32_t eid:32;
        };
    };
};
#pragma pack(pop)


// A PGN is defined to be 24 bits which leaves 8 bits on a 32 bit machine.
// So, we may hide other data in the upper 8 bits. Remember to ignore those
// bits if doing a comparison. Always, use just the pgn.
// See SAE J1939-21 for further information.
#pragma pack(push,1)
struct j1939_pgn_s {
    union {
        // 24 Bit PGN Structures
        struct { 
            uint32_t GE:8;          // Group Extension if PF >= 240 (0xF0), otherwise 0
            uint32_t PF:8;          // PDU Format
            uint32_t DP:1;          // Data Page
            uint32_t EDP:1;         // Extended Data Page
            uint32_t reserved1:6;   // Reserved - 0's
            uint32_t reserved2:8;   // Reserved - 0's
        };
        struct {
            uint32_t pgn:24;
            uint32_t reserved3:8;   // Reserved - 0's
        };
        // 32 Bit PGN Structures (for use when computer word is 32 bits)
        struct {
            uint32_t pgn0:8;        // LSB
            uint32_t pgn1:8;
            uint32_t pgn2:8;        // MSB
            uint32_t pgn3:8;        // Not part of official pgn, can be used if you are
                                    // careful for other things.
        };
        struct {
            uint32_t w:32;
        };
    };
};
#pragma pack(pop)





/****************************************************************
* * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
****************************************************************/

#ifdef	__cplusplus
extern "C" {
#endif

//---------------------------------------------------------------
//                      *** Properties ***
//---------------------------------------------------------------

    uint32_t        j1939msg_getEid(
        J1939_MSG       *pMsg
    );
    
    bool            j1939msg_setEid(
        J1939_MSG       *pMsg,
        uint32_t        value
    );
    
    
    uint32_t        j1939msg_getDataLength(
        J1939_MSG       *pMsg
    );
    
    bool            j1939msg_setDataLength(
        J1939_MSG       *pMsg,
        uint32_t        value
    );
    
    
    bool            j1939msg_IsEXID(
        J1939_MSG       *pMsg
    );
    
    
    J1939_PDU       j1939msg_getPDU(
        J1939_MSG       *pMsg
    );
    
    bool            j1939msg_setPDU(
        J1939_MSG       *pMsg,
        uint32_t        value
    );
    
    
    J1939_PGN       j1939msg_getPGN(
        J1939_MSG       *pMsg
    );
    
    
    uint32_t        j1939msg_getSid(
        J1939_MSG       *pMsg
    );
    
    bool            j1939msg_setSid(
        J1939_MSG       *pMsg,
        uint32_t        value
    );
    
    
    uint8_t         j1939pdu_getDA(
        J1939_PDU       pdu
    );
    
    J1939_PGN       j1939pdu_getPGN(
        J1939_PDU       pdu
    );
    
    uint8_t         j1939pdu_getSA(
        J1939_PDU       pdu
    );
    
    
    

//---------------------------------------------------------------
//                      *** Methods ***
//---------------------------------------------------------------

    void            j1939msg_Clear(
        J1939_MSG       *pMsg
    );
    
    void            j1939name_Clear(
        J1939_NAME      *pName
    );
    
    
    
    // Create a standard message with up to 8 bytes of data.
    bool            j1939msg_ConstructMsg(
        J1939_MSG       *pMsg,
        uint32_t        sid,
        uint32_t        dlc,
        uint8_t         *pData
    );

    
    // Create a extended message with up to 8 bytes of data
    // and 0x00 fill bytes.
    bool            j1939msg_ConstructMsg_E(
        J1939_MSG       *pMsg,
        uint32_t        eid,
        uint32_t        dlc,
        uint8_t         *pData
    );


    // Create a extended message with up to 8 bytes of data
    // and 0xFF fill bytes.
    bool            j1939msg_ConstructMsg_E1(
        J1939_MSG       *pMsg,
        uint32_t        eid,
        uint32_t        dlc,
        uint8_t         *pData
    );
    
    
    // Create a standard RTR message.
    bool            j1939msg_ConstructRTR(
        J1939_MSG       *pMsg,
        uint32_t        sid
    );

    // Create a extended RTR message.
    bool            j1939msg_ConstructRTR_E(
        J1939_MSG       *pMsg,
        uint32_t        eid
    );


    bool            j1939name_Construct(
        J1939_NAME      *pName,
        uint32_t        spn2837,        // J1939 NAME Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 NAME Manufacturer Code (11 bits)
        uint8_t         spn2846,        // J1939 NAME Industry Group (3 bits)
        uint8_t         spn2841,        // J1939 NAME Function (8 bits)
        uint8_t         spn2839         // J1939 NAME Function Instance (5 bits)
    );
    
    
    bool            j1939pdu_Construct(
       J1939_PDU        *pPDU,
       uint8_t          format,         // PDU Format
       uint8_t          specific,       // PDU Specific or Destination address
       uint8_t          priority,
       uint8_t          source          // Source Address
    );
    
    
    void            j1939msg_Copy(
        J1939_MSG       *pMsgIn,
        J1939_MSG       *pMsgOut
    );
    
    
    void            j1939msg_CreatePrintable(
        J1939_MSG       *pMsg,
        char            *pData          // Ptr to 64 character buffer
    );


    void            j1939msg_ExtractData(
        J1939_MSG       *pMsg,
        uint32_t        *pLength,       // Ptr to output length
        uint8_t         *pData          // Ptr to 8 byte buffer
    );
    

    bool            j1939msg_InsertData(
        J1939_MSG       *pMsg,
        uint8_t         length,         // input length (0..8)
        uint8_t         *pData          // Ptr to 8 byte buffer
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* j1939msg_H */

