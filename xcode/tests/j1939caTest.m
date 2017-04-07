
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


#import     <XCTest/XCTest.h>
#import     <cmn_defs.h>
#include    <j1939.h>
#include    "j1939ca_internal.h"
#include    "common.h"              // Tests Common Routines
#include    "j1939Can.h"
#include    "j1939Sys.h"


// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      XCTAssert(expression, failure_description, ...)
//      XCTFail(failure_description, ...)
//      XCTAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      XCTAssertEquals(value_1, value_2, failure_description, ...)
//      XCTAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      XCTAssertNil(expression, failure_description, ...)
//      XCTAssertNotNil(expression, failure_description, ...)
//      XCTAssertTrue(expression, failure_description, ...)
//      XCTAssertFalse(expression, failure_description, ...)
//      XCTAssertThrows(expression, failure_description, ...)
//      XCTAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name,
//                                  failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name,
//                                  failure_description, ...)







static
J1939_MSG     lastMsg = { 0 };
static
J1939_MSG     testMsg = { 0 };





//---------------------------------------------------------------
//                      Transmit Message Methods
//---------------------------------------------------------------

// Loopback the xmt to the rcv for the J1939CA.

typedef enum loopback_state_e {
    LOOPBACK_STATE_HANDLEMESSAGE=0,
    LOOPBACK_STATE_HANDLEPGN60928,
} LOOPBACK_STATE;


static
LOOPBACK_STATE  state = LOOPBACK_STATE_HANDLEMESSAGE;


static
bool        xmtLoopback(
    void        *pObject,           // J1939CA_DATA ptr
    uint32_t    msDelay,            // Ignore delays for now
    J1939_MSG   *pMsg
)
{
    J1939CA_DATA    *cbp = pObject;
    J1939_PDU       pdu = {0};
    J1939_PGN       pgn = {0};
    bool            fRc = false;
    
    if (pMsg) {
        pgn = j1939msg_getJ1939_PGN(pMsg);
        pdu = j1939msg_getJ1939_PDU(pMsg);
    }
    
    switch (state) {
            
        case LOOPBACK_STATE_HANDLEMESSAGE:
            fRc = j1939ca_HandleMessages(cbp, pdu.eid, pMsg);
            break;
            
        case LOOPBACK_STATE_HANDLEPGN60928:
            fRc = j1939ca_HandlePgn60928(cbp, pdu.eid, pMsg);
            break;
            
        default:
            break;
    }
    
    
    //printj1939msg(pMessage);
    return fRc;
}



static
uint8_t     caNeeded = 0;
static
uint8_t     daNeeded = 255;


static
bool            xmtPGN60928(
    void            *pObject,           // J1939CA_DATA ptr
    uint32_t        msDelay,            // Ignore delays for now
    J1939_MSG         *pMsg
)
{
    J1939_PDU       pdu = {0};
    J1939_PGN       pgn = {0};
    char            data[80];
    bool            fRc = false;
    J1939_NAME      *pName;
    
    if (NULL == pMsg) {
        [[NSException exceptionWithName: @"NoMsgSent"
                                 reason: @"We were expecting a msg, but none was sent!"
                               userInfo:nil
          ] raise];
    }
    
    pgn = j1939msg_getJ1939_PGN(pMsg);
    pdu = j1939msg_getJ1939_PDU(pMsg);
    j1939msg_Copy(pMsg, &lastMsg);
    pName = (J1939_NAME *)&lastMsg.DATA.dw;
    ++pName->IDN;
    

    j1939msg_CreatePrintable( pMsg, data );
    fprintf(stderr, "accepted: %s\n", data);
    
    if (0x00EE00 == pgn.w)
        fRc = true;
    else {
        [[NSException exceptionWithName: @"NotSentPGN60928"
                                 reason: @"This message should have been PGN 60928!"
                               userInfo:nil
          ] raise];
    }
    if (caNeeded < 254) {
        if (caNeeded == pdu.SA)
            fRc = true;
        else {
            [[NSException exceptionWithName: @"NotCaNeeded"
                                     reason: @"Message does not have correct claimed address!"
                                   userInfo:nil
              ] raise];
        }        
    }
    if (daNeeded == pdu.PS)
        fRc = true;
    else {
        [[NSException exceptionWithName: @"NotCaNeeded"
                                 reason: @"Message does not have correct claimed address!"
                               userInfo:nil
          ] raise];
    }
    

    //printj1939msg(pMessage);
    return fRc;
}




@interface j1939caTests : XCTestCase

@end



@implementation j1939caTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
    
    mem_Dump( );
}



- (void)testOpenClose_1_0
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939CA_DATA    *pJ1939ca = OBJ_NIL;
    uint32_t        a = 4;
    uint32_t        b = 2;

    //fprintf(stderr, "b-a = %u\n", (b-a));
    //fprintf(stderr, "b-a+max32 = %u\n", (uint32_t)(b - a + 4294967296));
    //FIXME: fprintf(stderr, "diff(b-a) = %u\n", timeDiff(NULL,a,b));
    
    j1939Sys_TimeReset(pSYS, 0);

    pJ1939ca = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    pJ1939ca =  j1939ca_Init(
                        pJ1939ca,
                        (P_XMTMSG_RTN)xmtHandler,
                        NULL,
                        1,              // J1939 Identity Number (21 bits)
                        10,             // J1939 Manufacturer Code (11 bits) (Cummins)
                        4               // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    if (pJ1939ca) {
        
        j1939ca_setCAN(pJ1939ca, pCAN);
        j1939ca_setSYS(pJ1939ca, pSYS);
        
        obj_Release(pJ1939ca);
        pJ1939ca = OBJ_NIL;
    }

    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
}



- (void)testCheck_EmptyChain
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939CA_DATA    *pJ1939ca = NULL;
    
    //FIXME: timeReset(NULL);
    pJ1939ca = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    pJ1939ca =  j1939ca_Init(
                             pJ1939ca,
                             (P_XMTMSG_RTN)xmtHandler,
                             NULL,
                             1,              // J1939 Identity Number (21 bits)
                             10,             // J1939 Manufacturer Code (11 bits) (Cummins)
                             4               // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    if (pJ1939ca) {

        j1939ca_setCAN(pJ1939ca, pCAN);
        j1939ca_setSYS(pJ1939ca, pSYS);
        
        j1939ca_setXmtMsg( pJ1939ca, xmtPGN60928, pJ1939ca );

        //fRc = pJ1939ca_CheckForTimeouts( pHnd, &msWait );
        //STAssertTrue( (fRc), @"Result was false!" );

        obj_Release(pJ1939ca);
        pJ1939ca = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
}



// Initiate an Address Claim, wait 250+ ms, then check that we have claimed
// the address.
- (void)testCheck_ClaimAddress_clean
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939CA_DATA    *pJ1939ca = NULL;
    //J1939_PDU       pdu = {0};
    //J1939_PGN       pgn = {0};
    bool            fRc;
    //uint32_t        msWait = 0;
    
    //FIXME: timeReset(NULL);
    pJ1939ca = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    pJ1939ca =  j1939ca_Init(
                             pJ1939ca,
                             (P_XMTMSG_RTN)xmtHandler,
                             NULL,
                             1,              // J1939 Identity Number (21 bits)
                             10,             // J1939 Manufacturer Code (11 bits) (Cummins)
                             4               // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    if (pJ1939ca) {

        j1939ca_setCAN(pJ1939ca, pCAN);
        j1939ca_setSYS(pJ1939ca, pSYS);
        
        j1939ca_setXmtMsg( pJ1939ca, xmtPGN60928, pJ1939ca );

        // The CA is in the Starting State. So, calling pgn 60928 will initiate
        // an Address Claim.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, 0, NULL);
        
        //TODO: Check that the claim address message was sent.

        // Send "Time Out" which should allow us to accept our claimed address
        // and go into normal operation.
        //FIXME: timeBump(NULL,255);
        fRc = j1939ca_HandlePgn60928(pJ1939ca, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939ca->cs), @"" );

        obj_Release(pJ1939ca);
        pJ1939ca = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
}


- (void)testCheck_ClaimAddress_contested1
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939CA_DATA    *pJ1939ca = NULL;
    J1939_PDU       pdu = {0};
    //J1939_PGN       pgn = {0};
    bool            fRc;
    //uint32_t        msWait = 0;
    
    //FIXME: timeReset(NULL);
    pJ1939ca = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939ca), @"Could not alloc J1939CA" );
    pJ1939ca =  j1939ca_Init(
                             pJ1939ca,
                             (P_XMTMSG_RTN)xmtHandler,
                             NULL,
                             1,              // J1939 Identity Number (21 bits)
                             10,             // J1939 Manufacturer Code (11 bits) (Cummins)
                             4               // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pJ1939ca), @"Could not init J1939CA" );
    j1939ca_setXmtMsg( pJ1939ca, xmtPGN60928, pJ1939ca );
    if (pJ1939ca) {

        j1939ca_setCAN(pJ1939ca, pCAN);
        j1939ca_setSYS(pJ1939ca, pSYS);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, 0, NULL);
        j1939msg_Copy( &lastMsg, &testMsg );

        // This will have a larger NAME so it should insist on the claimed address.
        pdu = j1939msg_getJ1939_PDU(&testMsg);

        // Send conflict.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs), @"" );

        // Send conflict.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs), @"" );

        obj_Release(pJ1939ca);
        pJ1939ca = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
}



- (void)testCheck_ClaimAddress_contested2
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939CA_DATA    *pJ1939ca = NULL;
    J1939_PDU       pdu = {0};
    //J1939_PGN       pgn = {0};
    bool            fRc;
    //uint32_t        msWait = 0;
    J1939_NAME      *pName = (J1939_NAME *)&testMsg.DATA.dw;
    
    //FIXME: timeReset(NULL);
    pJ1939ca = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939ca), @"Could not alloc J1939CA" );
    pJ1939ca =  j1939ca_Init(
                             pJ1939ca,
                             (P_XMTMSG_RTN)xmtHandler,
                             NULL,
                             1,              // J1939 Identity Number (21 bits)
                             10,             // J1939 Manufacturer Code (11 bits) (Cummins)
                             4               // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pJ1939ca), @"Could not init J1939CA" );
    j1939ca_setXmtMsg( pJ1939ca, xmtPGN60928, pJ1939ca );
    if (pJ1939ca) {

        j1939ca_setCAN(pJ1939ca, pCAN);
        j1939ca_setSYS(pJ1939ca, pSYS);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, 0, NULL);
        j1939msg_Copy( &lastMsg, &testMsg );
        // This will have the same NAME so ca should try a new address.
        --pName->IDN;
        pdu = j1939msg_getJ1939_PDU(&testMsg);
        // Send conflict.
        caNeeded = 1;
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs), @"" );
        // Send conflict.
        pdu.SA = caNeeded;
        j1939msg_setJ1939_PDU(&testMsg,pdu.eid);
        caNeeded = 128;
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs), @"" );
        // Send lots of conflicts.
        for ( ; caNeeded<248; ++caNeeded) {
            pdu.SA = caNeeded - 1;
            j1939msg_setJ1939_PDU(&testMsg,pdu.eid);
            fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
            XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs), @"" );
        }
        // Send one more for we done!.
        pdu.SA = caNeeded - 1;
        j1939msg_setJ1939_PDU(&testMsg,pdu.eid);
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_COMMANDED_ADDRESS == pJ1939ca->cs), @"" );
        obj_Release(pJ1939ca);
        pJ1939ca = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
}



- (void)testCheck_RequestNameDirect
{
    J1939SYS_DATA   *pSYS = j1939Sys_New();
    J1939CAN_DATA   *pCAN = j1939Can_New(1);
    J1939CA_DATA    *pJ1939ca = NULL;
    bool            fRc;
    J1939_MSG         msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    //FIXME: timeReset(NULL);
    pJ1939ca = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939ca), @"Could not alloc J1939CA" );
    pJ1939ca =  j1939ca_Init(
                             pJ1939ca,
                             (P_XMTMSG_RTN)xmtHandler,
                             NULL,
                             1,              // J1939 Identity Number (21 bits)
                             10,             // J1939 Manufacturer Code (11 bits) (Cummins)
                             4               // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pJ1939ca), @"Could not init J1939CA" );
    cCurMsg = 0;
    if (pJ1939ca) {
        
        j1939ca_setCAN(pJ1939ca, pCAN);
        j1939ca_setSYS(pJ1939ca, pSYS);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, 0, NULL);

        // Send "Timed Out".
        //FIXME: timeBump(NULL,250);
        fRc = j1939ca_HandlePgn60928(pJ1939ca, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pJ1939ca->cs), @"" );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0xEE;
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( pJ1939ca, pdu.eid, &msg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF00 == pdu.eid) );
        
        obj_Release(pJ1939ca);
        pJ1939ca = OBJ_NIL;
    }
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
}



@end



