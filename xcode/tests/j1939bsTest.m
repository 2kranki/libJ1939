/*
 *	Generated 06/21/2017 16:25:20
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


#include    <j1939bs_internal.h>
#include    "common.h"              // Tests Common Routines
#include    <j1939can.h>
#include    <j1939sys.h>


static
J1939CAN_DATA   *pCAN = OBJ_NIL;





@interface j1939bsTests : XCTestCase

@end

@implementation j1939bsTests


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
    J1939BS_DATA	*pObj = OBJ_NIL;
   
    pObj = j1939bs_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939bs_Init(
                        pObj,
                        (OBJ_ID)pCAN,
                        (OBJ_ID)pSYS,
                        1,             // J1939 Identity Number (21 bits)
                        8192,          // J1939 Manufacturer Code (11 bits)
                        1              // J1939 Industry Group (3 bits)
            );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



// NOTE - Timing is not extremely accurate. So, it is possible for
//          the counts to vary some.
- (void)test_j1939bs_TimedMessages
{
    J1939BS_DATA    *pBrake = NULL;
    //J1939_PDU       pdu;
    bool            fRc;
    int             i;
    int             j;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pBrake = j1939bs_Alloc();
    XCTAssertFalse( (NULL == pBrake) );
    pBrake = j1939bs_Init(pBrake, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 1);
    XCTAssertFalse( (NULL == pBrake) );
    if (pBrake) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pBrake, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pBrake->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // We need to go long enough (1200ms) to get all timed messages to pop.
        // PGN 61441 - F001 - every 100ms       12ea
        // PGN 64964 - FDC4 - every 100ms       12ea
        // PGN 65215 - FEBF - every 100ms       12ea
        for (int i=0; i<120; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc =   (*j1939ca_getHandler((J1939CA_DATA *)pBrake))(
                                                                  (J1939CA_DATA *)pBrake,
                                                                  NULL
                                                                  );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( ((33 < cCurMsg) && (cCurMsg < 40)) );
        
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 61441) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( ((10 < j) && (j < 15)) );
        
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 64964) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( ((10 < j) && (j < 15)) );
        
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 65215) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( ((11 < j) && (j < 15)) );
        
        
        obj_Release(pBrake);
        pBrake = NULL;
    }
    
}



@end



