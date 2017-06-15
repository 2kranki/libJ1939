/*
 *	Generated 06/12/2017 17:43:12
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
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)


#include    <j1939cab_internal.h>
#include    "common.h"              // Tests Common Routines
#include    <j1939can.h>
#include    "j1939sys.h"


static
J1939CAN_DATA   *pCAN = OBJ_NIL;




@interface j1939cabTests : XCTestCase

@end

@implementation j1939cabTests


- (void)setUp
{
    [super setUp];
    
    mem_Init( );
    
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
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
    
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    mem_Dump( );
    mem_Release( );

    [super tearDown];
}




- (void)testOpenClose
{
    J1939CAB_DATA	*pCAB = OBJ_NIL;
   
    pCAB = j1939cab_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pCAB) );
    XCTAssertFalse( (OBJ_NIL == pCAB) );
    pCAB =  j1939cab_Init(
                    pCAB,
                    (OBJ_ID)pCAN,
                    (OBJ_ID)pSYS,
                    1,             // J1939 Identity Number (21 bits)
                    8192,          // J1939 Manufacturer Code (11 bits)
                    4              // J1939 Industry Group (3 bits) (Marine)
            );
    XCTAssertFalse( (OBJ_NIL == pCAB) );
    if (pCAB) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        obj_Release(pCAB);
        pCAB = OBJ_NIL;
    }

}



- (void)testTransmits
{
    J1939CAB_DATA	*pCAB = OBJ_NIL;
    J1939_PDU       pdu;
    bool            fRc;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pCAB = j1939cab_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pCAB) );
    pCAB = j1939cab_Init(
                    pCAB,
                    (OBJ_ID)pCAN,
                    (OBJ_ID)pSYS,
                    1,             // J1939 Identity Number (21 bits)
                    8192,          // J1939 Manufacturer Code (11 bits)
                    4              // J1939 Industry Group (3 bits) (Marine)
            );
    XCTAssertFalse( (OBJ_NIL == pCAB) );
    if (pCAB) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        fRc = j1939cab_TransmitPgn61443(pCAB);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x0CF00325 == pdu.eid) );

        fRc = j1939cab_TransmitPgn65217(pCAB);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEC125 == pdu.eid) );
        
        fRc = j1939cab_TransmitPgn65261(pCAB);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEED25 == pdu.eid) );
        
        fRc = j1939cab_TransmitPgn65265(pCAB);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (4 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF125 == pdu.eid) );
        
        fRc = j1939cab_TransmitPgn65269(pCAB);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF525 == pdu.eid) );
        
        fRc = j1939cab_TransmitPgn65271(pCAB);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (6 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF725 == pdu.eid) );
        
        obj_Release(pCAB);
        pCAB = OBJ_NIL;
    }
    
}



@end



