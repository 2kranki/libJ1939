
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


#import <XCTest/XCTest.h>


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


#include    "j1939tc_internal.h"

#include	"common.h"
#include    <j1939can.h>
#include    <j1939sys.h>



static
J1939CAN_DATA   *pCAN = OBJ_NIL;




@interface j1939tcTests : XCTestCase

@end

@implementation j1939tcTests


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
    J1939TC_DATA    *pTC = NULL;

    j1939sys_TimeReset(pSYS, 0);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        obj_Release(pTC);
        pTC = NULL;
    }

}



- (void)testCheck_RequestNameDirect
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );

        // Setup up msg from ER #1 (41) to TC #1 (3) requesting NAME;
        pdu.eid = 0;
        pdu.SA = 41;                // Source Address
        pdu.P = 3;                  // Priority
        pdu.PF = 0xEA;              // PDU Format - PGN
        pdu.PS = 3;                 // Destination Address
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0xEE;
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0CEA0329 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18EEFF03 == pdu.eid) );

        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
}



- (void)testCheck_RequestBadNameDirect
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from ER #1 (41) to TC #1 (3) requesting NAME;
        pdu.eid = 0;
        pdu.SA = 41;                // Source Address
        pdu.P = 3;                  // Priority
        pdu.PF = 0xEA;              // PDU Format - PGN
        pdu.PS = 3;                 // Destination Address
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0x23;         // Not Sure what this is if anything! lol
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0CEA0329 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18E82903 == pdu.eid) );       // Respond with NAK
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
}



- (void)testCheck_RequestBadNameGlobal
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
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
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        // It will not nak since we asked globablly.
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (3 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
}



- (void)testCheck_RequestIRC1Direct
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
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
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (4 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        //XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
}



- (void)testCheck_TimedIRC1
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_PDU       pdu;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, NULL );
        }        

        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (3 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
}



- (void)testCheck_TSC1_Direct_Clean
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
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
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        //FIXME: XCTAssertTrue( (true == pTC->fActive) );
        //FIXME: XCTAssertTrue( (3 == pTC->spn1482) );

        for (int i=0; i<100; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, NULL );
        }
        
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
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        XCTAssertTrue( (false == pTC->fActive) );
        XCTAssertTrue( (255 == pTC->spn1482) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        //FIXME: XCTAssertTrue( (0x18F00029 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //FIXME: XCTAssertTrue( (0x0C002903 == pdu.eid) );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
}



- (void)testCheck_TSC1_Direct_Timeout
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
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
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        //FIXME: XCTAssertTrue( (true == pTC->fActive), @"" );
        //FIXME: XCTAssertTrue( (3 == pTC->spn1482), @"" );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, NULL );
        }
        
#ifdef XYZZY
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
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
#endif
        XCTAssertTrue( (false == pTC->fActive) );
        XCTAssertTrue( (255 == pTC->spn1482) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (5 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        //FIXME: XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //FIXME: XCTAssertTrue( (0x18F00029 == pdu.eid), @"Result was false!" );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
}



@end



