/*
 *	Generated 06/21/2017 16:25:20
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
#include    <cmn_defs.h>
#include    <trace.h>
#include    <j1939bs_internal.h>
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






int         test_j1939bs_OpenClose(
    const
    char        *pTestName
)
{
    J1939BS_DATA	*pObj = OBJ_NIL;
   
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );

    pObj = j1939bs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939bs_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



// NOTE - Timing is not extremely accurate. So, it is possible for
//          the counts to vary some.
int         test_j1939bs_TimedMessages(
    const
    char        *test_name
)
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
    
    return 1;
}





TINYTEST_START_SUITE(test_j1939bs);
  TINYTEST_ADD_TEST(test_j1939bs_TimedMessages,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939bs_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939bs);





