// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939ca_internal.h
 * Author: bob
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *
 * Created on September 26, 2014, 3:39 PM
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




#include        <j1939ca.h>
#include        <table.h>
#include        <j1939tp_internal.h>
//#include        <psxThread.h>
//#include        "j1939tbl.h"


#ifndef J1939CA_INTERNAL_H
#define	J1939CA_INTERNAL_H 1


#ifdef	__cplusplus
extern "C" {
#endif

    
    typedef enum j1939ca_state_e {
        J1939CA_STATE_START=0,
        J1939CA_STATE_SEND_CLAIM_ADDRESS,
        J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS,
        J1939CA_STATE_SEND_CANNOT_CLAIM_ADDRESS,
        J1939CA_STATE_NORMAL_OPERATION,
        J1939CA_STATE_WAIT_FOR_COMMANDED_ADDRESS,
    } J1939CA_STATE;
    

#pragma pack(push, 1)
    typedef struct j1939ca_msg_s {
        uint32_t        msDelay;            // Delay in ms
        uint32_t        msTime;             // Time when delay expires
        J1939_MSG       msg;
    } J1939CA_MSG;
#pragma pack(pop)
    
    
    // Packets consists of a 1 byte sequence number (1-255) and 7 bytes of data which
    // accounts for a total of 1875 bytes of message data.
#pragma pack(push, 1)
    typedef struct j1939ca_tp_s {
        uint8_t         activity;               // 0 == inactive
        //                                      // 1 == receive TP
        //                                      // 2 == transmit TP
        uint8_t         flags;
        uint8_t         state;
        uint8_t         adr;                    // For rcv,
        J1939_PDU       pdu;                    // PDU of Original Message
        uint32_t        msTime;                 // Time of Last Receipt/Transmit
        uint8_t         packets;                // Number of Packets
        uint8_t         seq;                    // Current Sequence Number (spn2562)
        uint8_t         limit;                  // CTS limit (spn2561)
        uint16_t        size;                   // amount of data (<= 1875)
        uint8_t         bitmap[32];             // Msg Received Bit Map
        uint8_t         data[1876];             // Max Msg Size Buffer
        //                                      // (Rounded up to 4-byte boundary)
    } J1939CA_TP;
#pragma pack(pop)
    
    enum J1939CA_TP_VALUES {
        J1939CA_TP_INACTIVE=0,
        J1939CA_TP_ACTIVE_RCV=1,
        J1939CA_TP_ACTIVE_XMT=2
    };
    enum J1939CA_TP_STATE {
        J1939CA_TP_STATE_UNKNOWN=0,
        J1939CA_TP_STATE_WAIT_FOR_DATA,
        J1939CA_TP_STATE_XMT_FULL,              // With inter-message delay
        J1939CA_TP_STATE_XMT_PARTIAL,           // With inter-message delay
        J1939CA_TP_STATE_WAIT_FOR_CTS,          // Wait for next TP.CM_CTS
    };
    
    
#pragma pack(push, 1)
    typedef struct j1939ca_msg_60416_s {
        uint8_t         spn2556;        // Control Byte (TP.CM)
        union {
            uint8_t         bytes[7];
            struct {    // TP.CM_RTS (16)
                struct {
                    uint8_t        spn2557L;   // Total Message Size (TP.CM_RTS)
                    uint8_t        spn2557H;   // Total Message Size (TP.CM_RTS)
                };
                uint8_t         spn2558;    // Total Number of Packets (TP.CM_RTS)
                uint8_t         spn2559;    // Maximum Number of Packets (TP.CM_RTS)
                J1939_PGN       spn2560;    // Parameter Group Number of packeted message (TP.CM_RTS)
            };
            struct {    // TP.CM_CTS (17)
                uint8_t         spn2561;    // Number of Packets that can be sent (TP.CM_CTS)
                uint8_t         spn2562;    // Next Packet Number to be sent (TP.CM_RTS)
                uint8_t         rsvd8a;
                uint8_t         rsvd8b;
                J1939_PGN       spn2563;    // Parameter Group Number of packeted message (TP.CM_CTS)
            };
            struct {    // End of Message TP.CM_ACK (19)
                struct {
                    uint8_t         spn2564L;   // Total Message Size (TP.CM_ACK)
                    uint8_t         spn2564H;   // Total Message Size (TP.CM_ACK)
                };
                uint8_t         spn2565;    // Total Number of Packets (TP.CM_ACK)
                uint8_t         rsvd8c;
                J1939_PGN       spn2566;    // Parameter Group Number of packeted message (TP.CM_ACK)
            };
            struct {    // TP.Conn_Abort (255)
                uint8_t         spn2570;    // Connection Abort Reason (TP.Conn_Abort)
                //                          // 1 == Already in one or more connection
                //                          //      managed sessions and cannot support
                //                          //      another.
                //                          // 2 == System resources were needed for
                //                          //      another task so this connection
                //                          //      managed session was terminated.
                //                          // 3 == A timeout occurred and this is the
                //                          //      connection abort to close the session.
                //                          // 4 == CTS messages received when data trans-
                //                          //      fer is in progress.
                //                          // 5 == Maximum retransmit request limit
                //                          //      reached
                uint8_t         rsvd8d;
                uint8_t         rsvd8e;
                uint8_t         rsvd8f;
                J1939_PGN       spn2571;    // Parameter Group Number of packeted message (TP.Conn_Abort)
            };
            struct {    // TP.CM_BAM (32)
                struct {
                    uint8_t         spn2567L;   // Total Message Size (TP.CM_BAM)
                    uint8_t         spn2567H;   // Total Message Size (TP.CM_BAM)
                };
                uint8_t         spn2568;    // Total Number of Packets (TP.CM_BAM)
                uint8_t         rsvd8g;
                J1939_PGN       spn2569;    // Parameter Group Number of packeted message (TP.CM_BAM)
            };
        };
    } J1939CA_MSG_60416;
#pragma pack(pop)
    
    
    

    
    
    
    //                  Main Control j1939ca
    /* This control j1939ca resides only in memory and is used to provide
     * the information necessary to access the j1939ca data.
     */
    
    
#pragma pack(push, 1)
    struct j1939ca_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA            super;
        OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

        // Common Data
        ERESULT             eRc;
        
        OBJ_DATA            *pSYS;
        OBJ_DATA            *pCAN;
        
        P_HANDLE_TIMED_TRANSMITS
                            pTimedTransmit;
        uint8_t             fTimedTransmit;

        uint8_t             fUseTask;
        uint8_t             rsvd8[2];
        
        P_SRVCMSG_RTN       pHandler;
        
        /* XmtMsg() is the routine called to transmit an 8-byte
         * message. All messages must be sent via this routine.
         */
        //P_XMTMSG_RTN        pXmtMsg;
        //OBJ_PTR             pXmtData;
        P_J1939_XMTRTN      pXmtMsgDL;
        OBJ_PTR             pXmtDataDL;
        
        uint32_t            startTime;
        
        uint8_t             ca;             // Claimed Address
        uint8_t             cs;             // CA Claimed State
        uint16_t            reserved16;
        const
        J1939CA_PGN_TABLE   *pRcvPgnTbl;
        const
        J1939CA_PGN_TABLE   *pXmtPgnTbl;
        
        // NAME Fields
        J1939_NAME          name;
        
        // Current Input Message Parameters
        // (All of the HandlePgnNNNNN()s and TransmitPgnNNNNN() assume
        // that these fields are set.)
        const
        J1939CA_PGN_ENTRY   *pCurEntry;
        J1939_PGN           curPgn;
        uint8_t             curDa;
        uint8_t             curSa;
        uint16_t            reserved16a;
        J1939CA_TP          TPs[j1989_CA_TP_SIZE];
        uint32_t            tpMsgDelay;
        uint32_t            tpTr;           // Timeout ??  (Default: 200ms)
        uint32_t            tpTh;           // Timeout ??  (Default: 500ms)
        uint32_t            tpT1;           // TP Timeout  (Default: 750ms)
        //                                  // Time out after receipt of last packet
        //                                  // when more are expected
        //                                  // Action: Close connection.
        uint32_t            tpT2;           // TP Timeout  (Default: 1250ms)
        //                                  // Time out after issuance of CTS without
        //                                  // a response.
        //                                  // Action: Close connection.
        uint32_t            tpT3;           // TP Timeout  (Default: 1250ms)
        //                                  // Time out for lack of CTS or ACK after last
        //                                  // packet was sent
        //                                  // Action: Close connection.
        uint32_t            tpT4;           // TP Timeout  (Default: 1050ms)
        //                                  // Time out for lack of CTS (0) message to
        //                                  // hold open the connection.
        //                                  // Action: Close connection.

        TABLE_DATA          *pDelayTable;   // If a message is delayed, it is in this chain.
        //                                  // This chain is sorted by expiration time
        //                                  // (Youngest to Oldest).

        uint8_t             spn2553;
        uint8_t             spn2555;
        J1939_PGN           spn2540;        // Parameter Group Number (RQST)
        J1939CA_MSG_60416   msg60416;
    };
#pragma pack(pop)
    
    extern
    const
    J1939CA_PGN_ENTRY   ca_pgn59392_entry;
    extern
    const
    J1939CA_PGN_ENTRY   ca_pgn59904_entry;
    extern
    const
    J1939CA_PGN_ENTRY   ca_pgn60928_entry;
    
    extern
    const
    J1939CA_VTBL    j1939ca_Vtbl;
    extern
    const
    struct j1939ca_class_data_s j1939ca_ClassObj;


    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/
    
    bool            j1939ca_setCAM(
        J1939CA_DATA	*this,
        J1939CAM_DATA   *pValue
    );
    
    
    bool			j1939ca_setClaimedAddress(
        J1939CA_DATA	*this,
        uint8_t         value
    );
  
    
    bool            j1939ca_setLastError(
        J1939CA_DATA    *this,
        ERESULT         value
    );
    
    
    void            j1939ca_Dealloc(
        OBJ_ID          objId
    );

    
    bool            j1939ca_HandlePgn51456(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939ca_HandlePgn59392(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939ca_HandlePgn59904(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939ca_HandlePgn60416(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939ca_HandlePgn60928(
        J1939CA_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    int             j1939ca_SetupPgn60928(
        J1939CA_DATA	*this,
        J1939_PDU       *pEid,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    int             j1939ca_SetupPgn60416(
        J1939CA_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    bool            j1939ca_TransmitPgn60160(
        J1939CA_DATA	*this,
        J1939CA_TP      *pTP
    );
    
    
    bool            j1939ca_TransmitPgn60928(
        J1939CA_DATA	*this
    );
    
    
    void            j1939ca_XmtDelayedMsgs(
        J1939CA_DATA	*this
    );
    
    bool            j1939ca_XmtMsgDL(
        J1939CA_DATA	*this,
        uint32_t        msDelay,
        J1939_PDU       pdu,
        uint16_t        cData,
        void            *pData
    );
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* J1939CA_INTERNAL_H */

