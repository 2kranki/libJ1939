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
                j1939msg_getJ1939_PGN(pMessage).w,
                data
    );
    return true;
}



J1939_MSG   curMsg[300];
uint16_t    cCurMsg = 0;
uint8_t     fSkipMsg = false;


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
        if (cCurMsg < 300) {
            memmove( &curMsg[cCurMsg], pMsg, sizeof(J1939_MSG) );
            ++cCurMsg;
        }
        printCanMsg(pMsg);
    }
    else {
        fprintf(stderr, "delay: %5d  msg: Time Out\n", msDelay);
    }
    return true;
}






