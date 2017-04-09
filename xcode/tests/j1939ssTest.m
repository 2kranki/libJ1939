/*
 *	Generated 04/08/2017 00:51:45
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


#import     <cmn_defs.h>
#include    "j1939ss_internal.h"
#include    "common.h"              // Tests Common Routines
#include    "j1939Can.h"
#include    "j1939Sys.h"



static
J1939CAN_DATA   *pCAN = OBJ_NIL;



@interface j1939ssTests : XCTestCase

@end

@implementation j1939ssTests


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
    J1939SS_DATA	*pSS = OBJ_NIL;
    bool            fRc;
    J1939_PDU       pdu;
   
    pSS = j1939ss_Alloc();
    XCTAssertFalse( (OBJ_NIL == pSS) );
    pSS =   j1939ss_Init(
                pSS,
                (OBJ_ID)pCAN,
                (OBJ_ID)pSYS,
                1,             // J1939 Identity Number (21 bits)
                512,           // J1939 Manufacturer Code (11 bits)
                4              // J1939 Industry Group (3 bits) (Marine)
            );
    XCTAssertFalse( (OBJ_NIL == pSS) );
    if (pSS) {

        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
                
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pSS, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pSS->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x1CEEFF29 == pdu.eid) );
        
        // Send "Timed Out".
        j1939Sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pSS, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pSS->super.cs), @"" );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
        obj_Release(pSS);
        pSS = OBJ_NIL;
    }

}



@end



