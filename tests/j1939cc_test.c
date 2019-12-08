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
#include    <j1939_defs.h>
#include    <j1939cc_internal.h>
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





int         test_j1939cc_OpenClose(
    const
    char        *test_name
)
{
    J1939CC_DATA	*pObj = OBJ_NIL;
   
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
   
    pObj = j1939cc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939cc_Init( 
                    pObj, 
                    (OBJ_ID)pCAN,
                    (OBJ_ID)pSYS,
                    1,             // J1939 Identity Number (21 bits)
                    8192,          // J1939 Manufacturer Code (11 bits)
                    4              // J1939 Industry Group (3 bits) (Marine)
            );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_j1939cc_Transmits(
    const
    char        *test_name
)
{
    J1939CC_DATA	*pCC = OBJ_NIL;
    J1939_PDU       pdu;
    bool            fRc;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pCC = j1939cc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pCC) );
    pCC = j1939cc_Init( pCC,
                       (OBJ_ID)pCAN,
                       (OBJ_ID)pSYS,
                       1,             // J1939 Identity Number (21 bits)
                       8192,          // J1939 Manufacturer Code (11 bits)
                       4              // J1939 Industry Group (3 bits) (Marine)
                       );
    XCTAssertFalse( (OBJ_NIL == pCC) );
    if (pCC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        fprintf(stderr, "\n\nTransmit 61443...\n");
        fRc = j1939cc_TransmitPgn61443(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x0CF00325 == pdu.eid) );
        
        fprintf(stderr, "\n\nTransmit 65217...\n");
        fRc = j1939cc_TransmitPgn65217(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEC125 == pdu.eid) );
        
        fprintf(stderr, "\n\nTransmit 65261...\n");
        fRc = j1939cc_TransmitPgn65261(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEED25 == pdu.eid) );
        
        fprintf(stderr, "\n\nTransmit 65265...\n");
        fRc = j1939cc_TransmitPgn65265(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (4 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF125 == pdu.eid) );
        
        fprintf(stderr, "\n\nTransmit 65269...\n");
        fRc = j1939cc_TransmitPgn65269(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF525 == pdu.eid) );
        
        fprintf(stderr, "\n\nTransmit 65271...\n");
        fRc = j1939cc_TransmitPgn65271(pCC);
        XCTAssertTrue( (fRc) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (6 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18FEF725 == pdu.eid) );
        
        obj_Release(pCC);
        pCC = OBJ_NIL;
    }
    
    return 1;
}




TINYTEST_START_SUITE(test_j1939cc);
  TINYTEST_ADD_TEST(test_j1939cc_Transmits,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939cc_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939cc);





