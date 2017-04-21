// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939tp_internal.h
 *	Generated 04/18/2017 12:48:07
 *
 * Notes:
 *  --	N/A
 *
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




#include    <j1939tp.h>
#include    <j1939can.h>
#include    <psxMutex.h>


#ifndef J1939TP_INTERNAL_H
#define	J1939TP_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    enum J1939TP_VALUES {
        J1939TP_INACTIVE=0,
        J1939TP_ACTIVE_RCV=1,
        J1939TP_ACTIVE_XMT=2
    };
    enum J1939TP_STATE {
        J1939TP_STATE_UNKNOWN=0,
        J1939TP_STATE_RCV_BAM,
        J1939TP_STATE_XMT_BAM,              // With inter-message delay
        J1939TP_STATE_XMT_CANCEL,
        J1939TP_STATE_XMT_PARTIAL,          // With inter-message delay
        J1939TP_STATE_XMT_PAUSE,
        J1939TP_STATE_WAIT_FOR_CTS,
        J1939TP_STATE_WAIT_FOR_DATA
    };
    enum J1939TP_STATE_PROTOCOL {
        J1939TP_STATE_PROTO_UNKNOWN=0,
        J1939TP_STATE_PROTO_RCV_BAM,
        J1939TP_STATE_PROTO_RCV_CANCEL,
        J1939TP_STATE_PROTO_RCV_COMPLETED,
        J1939TP_STATE_PROTO_WAITING_FOR_WORK,
        J1939TP_STATE_PROTO_WAIT_FOR_CTS_T1,      // Wait for next TP.CM_CTS
        J1939TP_STATE_PROTO_WAIT_FOR_CTS_T2,      // Wait for next TP.CM_CTS
        J1939TP_STATE_PROTO_WAIT_FOR_CTS_T3,      // Wait for next TP.CM_CTS
        J1939TP_STATE_PROTO_WAIT_FOR_CTS_T4,      // Wait for next TP.CM_CTS
        J1939TP_STATE_PROTO_XMT_BAM,              // With inter-message delay
        J1939TP_STATE_PROTO_XMT_PARTIAL,          // With inter-message delay
    };
    
    


#pragma pack(push, 1)
struct j1939tp_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA            super;
    OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT             eRc;

    OBJ_DATA            *pSYS;
    OBJ_DATA            *pCAN;
    PSXMUTEX_DATA       *pMutex;
    
    // This exit is called whenever a TP.CM multi-part message has been received in full.
    ERESULT             (*pMessageReceived)(
                                            OBJ_ID,
                                            uint32_t,       // eid
                                            uint16_t,       // data length
                                            uint8_t *       // message data
                        );
    OBJ_ID              pMsgRcvObj;
    
    J1939_PGN           pgn;
    J1939_PDU           pdu;            // PDU of Original Message
    
    uint8_t             ca;
    uint8_t             adr;            // For rcv,
    uint8_t             state;
    uint8_t             stateProto;
    
    uint32_t            msTimeProto;    // Time of Last Protocol Action
    uint32_t            msTime;         // Time of Last Packet Receipt/Transmit
    
    uint32_t            tpMsgDelay;     // Intermessage Delay (Default: 100ms)
    //                                  // (Must be less than tpT3 or tpT4)
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
    
    uint8_t             activity;       // 0 == inactive
    //                                  // 1 == receive TP
    //                                  // 2 == transmit TP
    uint8_t             flags;
    uint8_t             packets;        // Number of Packets
    uint8_t             seq;            // Current Sequence Number (spn2562)
    uint8_t             limit;          // CTS limit (spn2561)
    uint16_t            size;           // amount of data (<= 1875)
    uint8_t             bitmap[32];     // Msg Received Bit Map
    uint8_t             data[1876];     // Max Msg Size Buffer
    //                                  // (Rounded up to 4-byte boundary)

};
#pragma pack(pop)

    extern
    const
    struct j1939tp_class_data_s  j1939tp_ClassObj;

    extern
    const
    J1939TP_VTBL         j1939tp_Vtbl;


    // Internal Functions
    void            j1939tp_Dealloc(
        OBJ_ID          objId
    );

    
    bool            j1939tp_setLastError(
        J1939TP_DATA     *this,
        ERESULT         value
    );


    bool            j1939tp_HandlePgn60160(
        J1939TP_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939tp_HandlePgn60416(
        J1939TP_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    ERESULT         j1939tp_ProcessPackets(
        J1939TP_DATA	*this
    );
    
    
    ERESULT         j1939tp_ProcessProtocol(
        J1939TP_DATA	*this
    );
    
    
    ERESULT         j1939tp_ProtocolCancel(
        J1939TP_DATA	*this,
        uint8_t         reason
    );
    
    
    ERESULT         j1939tp_ProtocolComplete(
        J1939TP_DATA	*this
    );
    
    
    ERESULT         j1939tp_ProtocolEndOfMessage(
        J1939TP_DATA	*this
    );
    
    
    ERESULT         j1939tp_TransmitAbort(
        J1939TP_DATA	*this,
        uint8_t         reason
    );
    
    
    ERESULT         j1939tp_TransmitBAM(
        J1939TP_DATA	*this
    );
    
    
    ERESULT         j1939tp_TransmitPacket(
        J1939TP_DATA	*this,
        uint8_t         n               // Relative to 0
    );
    
    
    ERESULT         j1939tp_TransmitRTS(
        J1939TP_DATA	*this
    );
    
    


#ifdef NDEBUG
#else
    bool			j1939tp_Validate(
        J1939TP_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* J1939TP_INTERNAL_H */

