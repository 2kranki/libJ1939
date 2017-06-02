// Common Routines and Data that can be used by all
// Tests
//

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



#include    "common.h"
#include    <string.h>







//===============================================================
//              *** CAN/J1939 Message Mock ***
//===============================================================


J1939SYS_DATA   *pSYS = OBJ_NIL;




void            composeTP_EOM(
    J1939_MSG       *pMsg,
    uint8_t         sa,
    uint8_t         da,
    uint32_t        eid,
    uint8_t         cPackets,
    uint16_t        size
)
{
    J1939_PDU       pdu;
    J1939_PDU       pduCTS;
    uint8_t         data[8];
    bool            fRc;
    
    pdu.eid = eid;
    
    j1939pdu_Construct(&pduCTS, 236, da, 7, sa);
    
    data[0] = 19;
    data[1] = size & 0xFF;
    data[2] = (size >> 8) & 0xFF;
    data[3] = cPackets;
    data[4] = 0xFF;
    data[5] = eid & 0xFF;
    data[6] = (eid >> 8) & 0xFF;
    data[7] = (eid >> 16) & 0xFF;
    
    j1939msg_ConstructMsg_E1(pMsg, pduCTS.eid, 8, data);
    pMsg->CMSGSID.CMSGTS = 0xFFFF;          // Denote transmitting;
    fRc = xmtHandler(NULL, 0, pMsg);
    
}



void            composeRQ_PGN(
    J1939_MSG       *pMsg,
    uint8_t         sa,
    uint8_t         da,
    uint32_t        pgn
)
{
    J1939_PDU       pdu;
    uint8_t         data[8];
    bool            fRc;
    
    j1939pdu_Construct(&pdu, 0xEA, da, 3, sa);
    
    data[0] = pgn & 0xFF;
    data[1] = (pgn >> 8) & 0xFF;
    data[2] = (pgn >> 16) & 0xFF;
    for (int i=3; i<8; ++i) {
        data[i] = 0xFF;
    }
    
    j1939msg_ConstructMsg_E1(pMsg, pdu.eid, 8, data);
    pMsg->CMSGSID.CMSGTS = 0xFFFF;          // Denote transmitting;
    fRc = xmtHandler(NULL, 0, pMsg);
    
}



void            composeTP_CTS(
    J1939_MSG       *pMsg,
    uint8_t         sa,
    uint8_t         da,
    uint32_t        eid,
    uint8_t         cPackets,
    uint8_t         nextPacket
)
{
    J1939_PDU       pdu;
    J1939_PDU       pduCTS;
    uint8_t         data[8];
    bool            fRc;
    
    pdu.eid = eid;
    
    j1939pdu_Construct(&pduCTS, 236, da, 7, sa);
    
    data[0] = 17;
    data[1] = cPackets;
    data[2] = nextPacket;
    data[3] = 0xFF;
    data[4] = 0xFF;
    data[5] = eid & 0xFF;
    data[6] = (eid >> 8) & 0xFF;
    data[7] = (eid >> 16) & 0xFF;
    
    j1939msg_ConstructMsg_E1(pMsg, pduCTS.eid, 8, data);
    pMsg->CMSGSID.CMSGTS = 0xFFFF;          // Denote transmitting;
    fRc = xmtHandler(NULL, 0, pMsg);
    
}



bool            printCanMsg(
    J1939_MSG       *pMessage
)
{
    char            data[64];
    
    data[0] = 0;
    j1939msg_CreatePrintable( pMessage, data );
    fprintf(    stderr,
                "time: %5d  pgn: %08X  msg: %s",
                pMessage->CMSGSID.CMSGTS,
                j1939msg_getPGN(pMessage).w,
                data
    );
    return true;
}


#define CMN_MAX_MSGS    50000


J1939_MSG   curMsg[CMN_MAX_MSGS];
uint16_t    cCurMsg = 0;
uint8_t     fSkipMsg = false;



// This must conform to P_SRVCMSG_RTN!
bool        rcvHandler(
    OBJ_PTR     pObj,
    uint32_t    eid,
    J1939_MSG   *pMsg
)
{

    if (pMsg) {
        if (cCurMsg < CMN_MAX_MSGS) {
            memmove( &curMsg[cCurMsg], pMsg, sizeof(J1939_MSG) );
            ++cCurMsg;
        }
        else {
            DEBUG_BREAK();
            // Too Many Messages
        }
        printCanMsg(pMsg);
    }

    return true;
}



// This must conform to P_XMTMSG_RTN!
bool        xmtHandler(
    OBJ_PTR     pObj,
    uint32_t    msDelay,
    J1939_MSG   *pMsg
)
{
    if (pMsg) {
        if (msDelay == -1) {        // *** Transmit ***
        }
        else {
            if (pSYS && ((J1939SYS_VTBL *)obj_getVtbl(pSYS))->pTimeMS) {
                pMsg->CMSGSID.CMSGTS = ((J1939SYS_VTBL *)obj_getVtbl(pSYS))->pTimeMS(pSYS);
            }
        }
        if (cCurMsg < CMN_MAX_MSGS) {
            memmove( &curMsg[cCurMsg], pMsg, sizeof(J1939_MSG) );
            ++cCurMsg;
        }
        else {
            DEBUG_BREAK();
            // Too Many Messages
        }
        printCanMsg(pMsg);
    }
    else {
        fprintf(stderr, "delay: %5d  msg: Time Out\n", msDelay);
    }
    return true;
}






