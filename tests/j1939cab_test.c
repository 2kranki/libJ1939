/*
 *	Generated 06/12/2017 17:43:12
 */





// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      TINYTEST_ASSERT(condition)
//      TINYTEST_ASSERT_MSG(condition,msg)
//      TINYTEST_EQUAL(expected, actual)
//      TINYTEST_EQUAL_MSG(expected, actual, msg)
//      TINYTEST_FALSE_MSG(condition,msg)
//      TINYTEST_FALSE(condition)
//      TINYTEST_TRUE_MSG(pointer,msg)
//      TINYTEST_TRUE(condition)





#include    <tinytest.h>
#include    <common.h>
#include    <trace.h>
#include    <j1939_defs.h>
#include    <j1939cab_internal.h>
#include    <j1939can.h>
#include    <j1939sys.h>


static
J1939CAN_DATA   *pCAN = OBJ_NIL;







int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    pSYS = j1939sys_New();
    pCAN = j1939can_New();
    cCurMsg = 0;
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
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
    
    return 1; 
}






int         test_j1939cab_OpenClose(
    const
    char        *pTestName
)
{
    J1939CAB_DATA	*pCab = OBJ_NIL;
   
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
 
    pCab = j1939cab_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pCab) );
    pCab = j1939cab_Init(pCab, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4);
    TINYTEST_FALSE( (OBJ_NIL == pCab) );
    if (pCab) {

        // Test something.

        obj_Release(pCab);
        pCab = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(test_j1939cab);
  TINYTEST_ADD_TEST(test_j1939cab_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939cab);





