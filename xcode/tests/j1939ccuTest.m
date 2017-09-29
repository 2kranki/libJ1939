/*
 *	Generated 06/05/2017 08:35:58
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


#include    <j1939ccu_internal.h>
#include    <trace.h>
#include    <j1939can.h>
#include    <j1939sys.h>

#include    "common.h"


static
J1939CAN_DATA   *pCAN = OBJ_NIL;




@interface j1939ccuTests : XCTestCase

@end

@implementation j1939ccuTests


- (void)setUp
{
    [super setUp];
    
    mem_Init( );
    trace_Shared( );
    
    pSYS = j1939sys_New();
    pCAN = j1939can_New();
    cCurMsg = 0;
    
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    //j1939_SharedReset( );
    
    trace_SharedReset( );
    mem_Dump( );
    mem_Release( );

    [super tearDown];
}




- (void)testOpenClose
{
    J1939CCU_DATA	*pObj = OBJ_NIL;
   
    pObj =  j1939ccu_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj =  j1939ccu_Init(
                         pObj,
                         (OBJ_ID)pCAN,
                         (OBJ_ID)pSYS,
                         1,              // J1939 Identity Number (21 bits)
                         8192,           // J1939 Manufacturer Code (11 bits)
                         1               // J1939 Industry Group (3 bits)
            );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        
        // WARNING: Test in batch tests. OBJ-C doesnt like us doing tasking outside of it!
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



