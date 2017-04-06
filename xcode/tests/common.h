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


#include    <stdbool.h>
#include    <stdint.h>

#include    <j1939msg.h>
#include    <chario.h>




//===============================================================
//                    *** Char I/O Mock ***
//===============================================================

bool        chrInputAdd(
    char        *pMsg
);

bool        chrInputGet(
    void            *pObjectRx,
    uint16_t        *pData,         // Return Data ptr,
                                    // if NULL, return data is flushed.
    uint32_t        timeOut_ms      // Time Out in ms to wait
                                    // (0 == no wait, 0xFFFFFFFF == infinite)
);

void        chrInputReset(
);


bool        chrOutputPut(
    void            *pObjectTx,
    uint16_t        data,
    uint32_t        timeOut_ms      // Time Out in ms to wait
                                    // (0 == no wait, 0xFFFFFFFF == infinite)
);

char *      chrOutputData(
    int         *pLen
);

void        chrOutputReset(
);


extern
CHARIO_DATA chrIO;




//===============================================================
//                  *** CAN/J1939 Message Mock ***
//===============================================================

typedef struct j1939_msg_data_s {
	uint32_t	pdu;
	uint16_t	len;
	uint8_t		data[8];
} J1939_MSG_DATA;



bool            printCanMsg(
    J1939_MSG       *pMessage
);


extern
J1939_MSG   curMsg[];
extern
uint16_t    cCurMsg;


// This must conform to P_XMTMSG_RTN!
bool        xmtHandler(
    OBJ_PTR     pObj,
    uint32_t    msDelay,
    J1939_MSG   *pMsg
);




//----------------------------------------------------------------
//                  Messages found in common02.c
//----------------------------------------------------------------
extern
J1939_MSG_DATA	Msgs01[];

extern
uint32_t		cMsgs01;



/*          Msgs 01A is 10 messages
 *   PDU        PGN       Count
 * 0CF00300    F003         2
 * 0CF00400    F004         2
 * 18F00100    F001         1
 * 18F00E00    F00E         1
 * 18FEF000    FEF0         1
 * 18FEDF00    FEDF         3
 *
 */

extern
J1939_MSG_DATA	Msgs01A[];

extern
uint32_t		cMsgs01A;



/* Captured messages just from Transmission TCU
 * in Green Truck for two blocks
 */
extern
J1939_MSG_DATA	Msgs02[];

extern
uint32_t		cMsgs02;



/* Captured messages just from Transmission TCU
 * in Green Truck in building with Jay driving
 * and manual shifting
 */
extern
J1939_MSG_DATA	Msgs03[];

extern
uint32_t		cMsgs03;




