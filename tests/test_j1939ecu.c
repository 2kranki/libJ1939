/*
 *	Generated 04/13/2017 15:27:23
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
#include    <j1939_defs.h>
#include    <j1939ecu_internal.h>
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
    
    mem_Dump( );
    mem_Release( );
    return 1; 
}







int         test_j1939ecu_OpenClose(
    const
    char        *test_name
)
{
    J1939ECU_DATA	*pObj = OBJ_NIL;
   
    pObj = j1939ecu_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939ecu_Init(
                    pObj, 
                    (OBJ_ID)pCAN,
                    (OBJ_ID)pSYS,
                    1,             // J1939 Identity Number (21 bits)
                    8192,          // J1939 Manufacturer Code (11 bits)
                    4              // J1939 Industry Group (3 bits) (Marine)
            );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(test_j1939ecu);
  TINYTEST_ADD_TEST(test_j1939ecu_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939ecu);





