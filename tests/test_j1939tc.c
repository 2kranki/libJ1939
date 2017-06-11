/*
 *	Generated 04/08/2017 00:51:45
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
#include    <j1939tc_internal.h>
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








int         test_j1939tc_OpenClose(
    const
    char        *test_name
)
{
    J1939TC_DATA    *pTC = NULL;

    j1939sys_TimeReset(pSYS, 0);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        obj_Release(pTC);
        pTC = NULL;
    }

    return 1;
}



int         test_j1939tc_RequestNameDirect(
    const
    char        *test_name
)
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );

        // Setup up msg from ER #1 (41) to TC #1 (3) requesting NAME;
        pdu.eid = 0;
        pdu.SA = 41;                // Source Address
        pdu.P = 3;                  // Priority
        pdu.PF = 0xEA;              // PDU Format - PGN
        pdu.PS = 3;                 // Destination Address
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0xEE;
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0CEA0329 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18EEFF03 == pdu.eid) );

        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tc_RequestBadNameDirect(
    const
    char        *test_name
)
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from ER #1 (41) to TC #1 (3) requesting NAME;
        pdu.eid = 0;
        pdu.SA = 41;                // Source Address
        pdu.P = 3;                  // Priority
        pdu.PF = 0xEA;              // PDU Format - PGN
        pdu.PS = 3;                 // Destination Address
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0x23;         // Not Sure what this is if anything! lol
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0CEA0329 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18E82903 == pdu.eid) );       // Respond with NAK
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tc_RequestBadNameGlobal(
    const
    char        *test_name
)
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 255;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0x23;         // Not Sure what this is! lol
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        // It will not nak since we asked globablly.
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tc_RequestIRC1Direct(
    const
    char        *test_name
)
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // IRC1 PGN
        data[1] = 240;
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (4 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        //XCTAssertTrue( (0x18F00029 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tc_TimedIRC1(
    const
    char        *test_name
)
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_PDU       pdu;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, NULL );
        }        

        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tc_TSC1_Direct_Clean(
    const
    char        *test_name
)
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 2;                // Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        //FIXME: XCTAssertTrue( (true == pTC->fActive) );
        //FIXME: XCTAssertTrue( (3 == pTC->spn1482) );

        for (int i=0; i<100; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, NULL );
        }
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        XCTAssertTrue( (false == pTC->fActive) );
        XCTAssertTrue( (255 == pTC->spn1482) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        //FIXME: XCTAssertTrue( (0x18F00029 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //FIXME: XCTAssertTrue( (0x0C002903 == pdu.eid) );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tc_TSC1_Direct_Timeout(
    const
    char        *test_name
)
{
    J1939TC_DATA    *pTC = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pTC = j1939tc_Alloc();
    XCTAssertFalse( (NULL == pTC) );
    pTC = j1939tc_Init(pTC, pCAN, pSYS, 1, 8192, 4);
    XCTAssertFalse( (NULL == pTC) );
    if (pTC) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pTC, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pTC->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 2;                // Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
        //FIXME: XCTAssertTrue( (true == pTC->fActive) );
        //FIXME: XCTAssertTrue( (3 == pTC->spn1482) );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, NULL );
        }
        
#ifdef XYZZY
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pTC, &msg );
#endif
        XCTAssertTrue( (false == pTC->fActive) );
        XCTAssertTrue( (255 == pTC->spn1482) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        //FIXME: XCTAssertTrue( (0x18F00029 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        //FIXME: XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        obj_Release(pTC);
        pTC = OBJ_NIL;
    }
    
    return 1; 
}







TINYTEST_START_SUITE(test_j1939tc);
  TINYTEST_ADD_TEST(test_j1939tc_TSC1_Direct_Timeout,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tc_TSC1_Direct_Clean,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tc_TimedIRC1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tc_RequestIRC1Direct,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tc_RequestBadNameGlobal,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tc_RequestBadNameDirect,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tc_RequestNameDirect,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tc_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939tc);





