
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
#include    <j1939er_internal.h>
#include    "common.h"              // Tests Common Routines
#include    <j1939can.h>
#include    <j1939sys.h>


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
J1939CAN_DATA   *pCAN = OBJ_NIL;



@interface j1939erTests : XCTestCase

@end

@implementation j1939erTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    pSYS = j1939sys_New();
    pCAN = j1939can_New();
    cCurMsg = 0;
    
}


- (void)tearDown
{
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    //j1939_SharedReset( );
    
    mem_Dump( );

    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
    
}



- (void)testOpenClose_1_0
{
    J1939ER_DATA    *pER = NULL;
    J1939_PDU       pdu;
    bool            fRc;

    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (NULL == pER), @"Could not alloc pER" );
    pER = j1939er_Init(
                       pER,
                       (OBJ_ID)pCAN,
                       (OBJ_ID)pSYS,
                       1,               // J1939 Identity Number (21 bits)
                       8192,            // J1939 Manufacturer Code (11 bits)
                       1                // J1939 Industry Group (3 bits)
            );
    XCTAssertFalse( (NULL == pER) );
    cCurMsg = 0;
    if (pER) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF29 == pdu.eid) );
        
        obj_Release(pER);
        pER = NULL;
    }
    
}



- (void)testTransmits
{
    J1939ER_DATA    *pER = NULL;
    J1939_PDU       pdu;
    bool            fRc;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (NULL == pER), @"Could not alloc pER" );
    pER = j1939er_Init(
                       pER,
                       (OBJ_ID)pCAN,
                       (OBJ_ID)pSYS,
                       1,               // J1939 Identity Number (21 bits)
                       8192,            // J1939 Manufacturer Code (11 bits)
                       1                // J1939 Industry Group (3 bits)
                       );
    XCTAssertFalse( (NULL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        fRc = j1939er_TransmitPgn61440(pER);
        // Initiate Address Claim.
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        //FIXME: msg size is 19, so we need large msg xmt!
#ifdef XYZZY
        fRc = j1939er_TransmitPgn65249(pER);
        // Initiate Address Claim.
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
#endif
        
        obj_Release(pER);
        pER = NULL;
    }
    
}



- (void)testCheck_RequestNameDirect
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                        pER,
                        (OBJ_ID)pCAN,
                        (OBJ_ID)pSYS,
                        1,              // J1939 Identity Number (21 bits)
                        8192,            // J1939 Manufacturer Code (11 bits)
                        1               // J1939 Industry Group (3 bits)
                );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF29 == pdu.eid) );

        // Send "Timed Out".
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs), @"" );

        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;              // Request PGN PF
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0xEE;             // Address Claim PF
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (4 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        XCTAssertTrue( (0x18EEFF29 == pdu.eid), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );

        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
}



- (void)testCheck_RequestBadNameDirect
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             1              // J1939 Industry Group (3 bits)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF29 == pdu.eid) );

        // Send "Timed Out".
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs), @"" );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
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
        data[1] = 0x23;         // Not Sure what this is! lol
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (4 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18E80329 == pdu.eid), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
}



- (void)testCheck_RequestBadNameGlobal
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             1              // J1939 Industry Group (3 bits)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF29 == pdu.eid) );

        // Send "Timed Out".
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs), @"" );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;          // Request PGN PF
        pdu.PS = 255;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0x23;         // Not Sure what this is! lol
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        // It will not nak since we asked globablly.
        XCTAssertTrue( (3 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
}



- (void)testCheck_RequestIRC1Direct
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             1              // J1939 Industry Group (3 bits)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF29 == pdu.eid) );

        // Send "Timed Out".
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs), @"" );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // IRC1 PGN
        data[1] = 240;
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (4 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
}



- (void)testCheck_TimedIRC1
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_PDU       pdu;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             1              // J1939 Industry Group (3 bits)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);

        // Send "Timed Out".
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs), @"" );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
        // Let's go 1000 ms in the future.
        // We should see 10 ERC1s because they are
        // issued every 100ms.
        for (int i=0; i<100; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, NULL );
        }        

        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (11 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
}



- (void)testCheck_TSC1_Direct_Clean
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             1              // J1939 Industry Group (3 bits)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);

        // Send "Timed Out".
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
        // Tell Engine Retarder to Brake.
        // Setup up msg from #3 Transmission via TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;                 // TSC1 PF
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 2;                // Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (true == pER->fActive) );
        XCTAssertTrue( (3 == pER->spn1480) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0X0C002903 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );

        // Put us 1000ms into the future.
        // Should give us 10 ERC1s.
        for (int i=0; i<100; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, NULL );
        }
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (13 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        // Tell Engine Retarder to Stop.
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;             // Torque/SpeedControl1 (TSC1) PF
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;            // Disable Engine Retarder
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);    // Show that we are sending this.
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (false == pER->fActive) );
        XCTAssertTrue( (255 == pER->spn1480) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (14 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0C002903 == pdu.eid) );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
}



- (void)testCheck_TSC1_Direct_Timeout
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             1              // J1939 Industry Group (3 bits) 
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);

        // Send "Timed Out".
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
        // Tell Engine Retarder to Brake.
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 2;                // Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (true == pER->fActive) );
        XCTAssertTrue( (3 == pER->spn1480) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%08X\n", pdu.eid);
        XCTAssertTrue( (0X0C002903 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%08X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        for (int i=0; i<100; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, NULL );
        }
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (13 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        // Tell Engine Retarder to Stop.
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (false == pER->fActive), @"" );
        XCTAssertTrue( (255 == pER->spn1480), @"" );
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (14 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0C002903 == pdu.eid), @"Result was false!" );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
}



@end



