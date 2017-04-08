
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


#include    "j1939cam_internal.h"
#include    "j1939en_internal.h"
#include    "j1939er_internal.h"
#include    "j1939Can.h"
#include    "j1939Sys.h"


#include    "common.h"


static
J1939CAN_DATA   *pCAN = OBJ_NIL;




@interface j1939camTests : XCTestCase

@end

@implementation j1939camTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    pSYS = j1939Sys_New();
    pCAN = j1939can_New();
    cCurMsg = 0;
    
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
    
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    //j1939_SharedReset( );

    mem_Dump( );
}



// The CAM object is hard to test without having any CAs. Internally,
// it builds a table from the CAs that notify it of their existence.
// It is the central point for all incoming messages which it then
// dispatches to each of the CAs.




- (void)testOpenClose_1_0
{
    J1939CAM_DATA   *pCAM = NULL;

    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    pCAM = j1939cam_Alloc();
    XCTAssertFalse( (NULL == pCAM) );
    pCAM = j1939cam_Init( pCAM, pCAN, pSYS );
    XCTAssertFalse( (NULL == pCAM) );
    if (pCAM) {

        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        obj_Release(pCAM);
        pCAM = NULL;
    }

}



- (void)testTimedMessages
{
    J1939CAM_DATA   *pCAM = NULL;
    J1939EN_DATA    *pEN = NULL;
    J1939ER_DATA    *pER = NULL;
    J1939_PDU       pdu;
    bool            fRc;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    pCAM = j1939cam_Alloc();
    XCTAssertFalse( (NULL == pCAM) );
    pCAM = j1939cam_Init( pCAM, pCAN, pSYS );
    XCTAssertFalse( (NULL == pCAM) );
    if (pCAM) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        pEN = j1939en_Alloc();
        XCTAssertFalse( (NULL == pEN) );
        pEN = j1939en_Init( pEN, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 512, 4 );
        XCTAssertFalse( (NULL == pEN) );
        fRc = j1939cam_AddCA( pCAM, (J1939CA_DATA *)pEN );
        XCTAssertTrue( (fRc) );
        obj_Release(pEN);
        pEN = OBJ_NIL;
        
        pER = j1939er_Alloc();
        XCTAssertFalse( (NULL == pER) );
        pER = j1939er_Init( pER, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 512, 4 );
        XCTAssertFalse( (NULL == pER) );
        fRc = j1939cam_AddCA( pCAM, (J1939CA_DATA *)pER );
        XCTAssertTrue( (fRc) );
        obj_Release(pER);
        pER = OBJ_NIL;
        
        for (int i=0; i<2000; ++i) {
            fRc = j1939cam_HandleMessages( pCAM, 0, NULL );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (239 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        obj_Release(pCAM);
        pCAM = NULL;
    }
    
}



- (void)testTSC1_To_Engine_Clean
{
    J1939CAM_DATA   *pCAM = NULL;
    J1939EN_DATA    *pEN = NULL;
    J1939ER_DATA    *pER = NULL;
    J1939_PDU       pdu;
    J1939_MSG       msg;
    uint8_t         data[8];
    bool            fRc;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    pCAM = j1939cam_Alloc();
    XCTAssertFalse( (NULL == pCAM) );
    pCAM = j1939cam_Init( pCAM, pCAN, pSYS );
    XCTAssertFalse( (NULL == pCAM) );
    if (pCAM) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        pEN = j1939en_Alloc();
        XCTAssertFalse( (NULL == pEN) );
        pEN = j1939en_Init( pEN, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 512, 4 );
        XCTAssertFalse( (NULL == pEN) );
        fRc = j1939cam_AddCA( pCAM, (J1939CA_DATA *)pEN );
        XCTAssertTrue( (fRc) );
        obj_Release(pEN);
        //pEN = OBJ_NIL;
        
        pER = j1939er_Alloc();
        XCTAssertFalse( (NULL == pER) );
        pER = j1939er_Init( pER, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 512, 4 );
        XCTAssertFalse( (NULL == pER) );
        fRc = j1939cam_AddCA( pCAM, (J1939CA_DATA *)pER );
        XCTAssertTrue( (fRc) );
        obj_Release(pER);
        //pER = OBJ_NIL;
        
        for (int i=0; i<250; ++i) {
            fRc = j1939cam_HandleMessages( pCAM, 0, NULL );
        }
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 0;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 1;                // Engine
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939cam_HandleMessages( pCAM, j1939msg_getEid(&msg), &msg );
        XCTAssertTrue( (true == pEN->fActive) );
        XCTAssertTrue( (3 == pEN->spn1480) );
        
        for (int i=0; i<50; ++i) {
            fRc = j1939cam_HandleMessages( pCAM, 0, NULL );
        }
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939cam_HandleMessages( pCAM, j1939msg_getEid(&msg), &msg );
        for (int i=0; i<50; ++i) {
            fRc = j1939cam_HandleMessages( pCAM, 0, NULL );
        }

        msg.DATA.bytes[0] = 0;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939cam_HandleMessages( pCAM, j1939msg_getEid(&msg), &msg );
        XCTAssertTrue( (false == pEN->fActive) );
        XCTAssertTrue( (255 == pEN->spn1480) );
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (46 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0C000003 == pdu.eid) );
        
        obj_Release(pCAM);
        pCAM = NULL;
    }
    
}



- (void)testTSC1_To_Engine_Clean_2
{
    J1939CAM_DATA   *pCAM = NULL;
	//CANBASE_DATA    *pBase = NULL;
    J1939_PDU       pdu;
    J1939_MSG       msg;
    uint8_t         data[8];
    bool            fRc;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    pCAM = j1939cam_NewEngine((OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 512, 4);
    XCTAssertFalse( (NULL == pCAM) );
    if (pCAM) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        for (int i=0; i<250; ++i) {
            fRc = j1939cam_HandleMessages( pCAM, 0, NULL );
        }
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 0;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 1;                // Engine
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939cam_HandleMessages( pCAM, j1939msg_getEid(&msg), &msg );
        //STAssertTrue( (true == pEN->fActive), @"" );
        //STAssertTrue( (3 == pEN->spn1480), @"" );
        
        for (int i=0; i<50; ++i) {
            fRc = j1939cam_HandleMessages( pCAM, 0, NULL );
        }
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939cam_HandleMessages( pCAM, j1939msg_getEid(&msg), &msg );
        for (int i=0; i<50; ++i) {
            fRc = j1939cam_HandleMessages( pCAM, 0, NULL );
        }
        
        msg.DATA.bytes[0] = 0;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939cam_HandleMessages( pCAM, j1939msg_getEid(&msg), &msg );
        //STAssertTrue( (false == pEN->fActive), @"" );
        //STAssertTrue( (255 == pEN->spn1480), @"" );
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (21 == cCurMsg), @"Result was false!" );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x0C000003 == pdu.eid), @"Result was false!" );
        
        obj_Release(pCAM);
        pCAM = NULL;
    }
    
}



@end



