/*
 *	Generated 04/15/2017 08:51:40
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


#include    <j1939cc_internal.h>
#include    "common.h"              // Tests Common Routines
#include    <j1939can.h>
#include    <j1939sys.h>


static
J1939CAN_DATA   *pCAN = OBJ_NIL;




@interface j1939ccTests : XCTestCase

@end

@implementation j1939ccTests


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
    mem_Release( );

    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
}




- (void)testOpenClose
{
    J1939CC_DATA	*pCC = OBJ_NIL;
   
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pCC = j1939cc_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pCC) );
    pCC = j1939cc_Init( pCC,
                        (OBJ_ID)pCAN,
                        (OBJ_ID)pSYS,
                        1,             // J1939 Identity Number (21 bits)
                        8192,          // J1939 Manufacturer Code (11 bits)
                        1              // J1939 Industry Group (3 bits)
                        );
    XCTAssertFalse( (OBJ_NIL == pCC) );
    if (pCC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        obj_Release(pCC);
        pCC = OBJ_NIL;
    }

}



- (void)testTransmits
{
    J1939CC_DATA	*pCC = OBJ_NIL;
    //J1939_PDU       pdu;
    //bool            fRc;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pCC = j1939cc_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pCC) );
    pCC = j1939cc_Init( pCC,
                       (OBJ_ID)pCAN,
                       (OBJ_ID)pSYS,
                       1,               // J1939 Identity Number (21 bits)
                       8192,            // J1939 Manufacturer Code (11 bits)
                       1                // J1939 Industry Group (3 bits) (Marine)
                       );
    XCTAssertFalse( (OBJ_NIL == pCC) );
    if (pCC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);

#ifdef XYZZY
        fRc = j1939cc_TransmitPgn61443(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x0CF00325 == pdu.eid) );
        
        fRc = j1939cc_TransmitPgn65217(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEC125 == pdu.eid) );
        
        fRc = j1939cc_TransmitPgn65261(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEED25 == pdu.eid) );
        
        fRc = j1939cc_TransmitPgn65265(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (4 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF125 == pdu.eid) );
        
        fRc = j1939cc_TransmitPgn65269(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF525 == pdu.eid) );
        
        fRc = j1939cc_TransmitPgn65271(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (6 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF725 == pdu.eid) );
#endif
        
        obj_Release(pCC);
        pCC = OBJ_NIL;
    }
    
}



@end



