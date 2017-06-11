/*
 *	Generated 04/15/2017 08:51:40
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
#include    <msgBus.h>
#include    <j1939_defs.h>
#include    <j1939ccu_internal.h>
#include    <j1939ecu_internal.h>
#include    <j1939tcu_internal.h>
#include    <j1939can.h>
#include    <j1939sys.h>


static
MSGBUS_DATA     *pMsgBus  = OBJ_NIL;
static
J1939CAN_DATA   *pCAN_CCU = OBJ_NIL;
static
J1939CAN_DATA   *pCAN_ECU = OBJ_NIL;
static
J1939CAN_DATA   *pCAN_TCU = OBJ_NIL;







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
    pMsgBus = msgBus_New(sizeof(J1939_MSG), 500);
    pCAN_CCU = j1939can_New();
    pCAN_ECU = j1939can_New();
    pCAN_TCU = j1939can_New();
    cCurMsg = 0;
    j1939sys_TimeReset(pSYS, 0);
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    obj_Release(pCAN_TCU);
    pCAN_TCU = OBJ_NIL;
    obj_Release(pCAN_ECU);
    pCAN_ECU = OBJ_NIL;
    obj_Release(pCAN_CCU);
    pCAN_CCU = OBJ_NIL;
    obj_Release(pMsgBus);
    pMsgBus = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    //j1939_SharedReset( );
    
    trace_SharedReset( );
    mem_Dump( );
    mem_Release( );
    return 1; 
}





int         test_truck_01(
    const
    char        *test_name
)
{
    J1939CCU_DATA	*pCCU = OBJ_NIL;
   
    XCTAssertFalse( (OBJ_NIL == pCAN_CCU) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
   
    pCCU = j1939ccu_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pCCU) );
    pCCU = j1939ccu_Init( 
                    pCCU, 
                    (OBJ_ID)pCAN_CCU,
                    (OBJ_ID)pSYS,
                    1,             // J1939 Identity Number (21 bits)
                    8192,          // J1939 Manufacturer Code (11 bits)
                    4              // J1939 Industry Group (3 bits) (Marine)
            );
    XCTAssertFalse( (OBJ_NIL == pCCU) );
    if (pCCU) {
        j1939can_setXmtMsg(pCAN_CCU, xmtHandler, NULL);
    }
        

    obj_Release(pCCU);
    pCCU = OBJ_NIL;
    return 1;
}





TINYTEST_START_SUITE(test_truck);
  TINYTEST_ADD_TEST(test_truck_01,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_truck);





