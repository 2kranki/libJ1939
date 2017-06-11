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
#include    <j1939en_internal.h>
#include    <j1939can.h>
#include    <j1939sys.h>


static
int             shiftsT = 0;
static
int             shiftsF = 0;

static
J1939CAN_DATA   *pCAN = OBJ_NIL;





void        shiftExit(void *ptr,bool fShifting)
{
    if (fShifting) {
        fprintf(stderr, "NOW SHIFTING    ======================================\n");
        ++shiftsT;
    }
    else {
        fprintf(stderr, "END OF SHIFTING ======================================\n");
        ++shiftsF;
    }
}






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








int         test_j1939en_OpenClose(
    const
    char        *test_name
)
{
    J1939EN_DATA    *pEng = NULL;
    //J1939_PDU       pdu;
    bool            fRc;

    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pEng = j1939en_Alloc();
    XCTAssertFalse( (NULL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (NULL == pEng) );
    if (pEng) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );

        obj_Release(pEng);
        pEng = NULL;
    }

    return 1;
}



// NOTE - Timing is not extremely accurate. So, it is possible for
//          the counts to vary some.
int         test_j1939en_TimedMessages(
    const
    char        *test_name
)
{
    J1939EN_DATA    *pEng = NULL;
    //J1939_PDU       pdu;
    bool            fRc;
    int             i;
    int             j;
        
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );

    pEng = j1939en_Alloc();
    XCTAssertFalse( (NULL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (NULL == pEng) );
    if (pEng) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );

        // We need to go long enough (1200ms) to get all timed messages to pop.
        // PGN 61443 - F003 - every 50ms        28ea
        // PGN 61444 - F004 - every 100ms       14ea
        // PGN 65265 - FEF1 - every 100ms       14ea
        // PGN 65247 - FEDF - every 250ms        6ea
        // PGN 65129 - FE69 - every 1000ms       1ea
        // PGN 65262 - FEEE - every 1000ms       1ea
        for (int i=0; i<120; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc =   (*j1939ca_getHandler((J1939CA_DATA *)pEng))(
                                            (J1939CA_DATA *)pEng,
                                            NULL
                    );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( ((56 < cCurMsg) && (cCurMsg < 65)) );
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 61443) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( ((23 < j) && (j < 29)) );
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 61444) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( ((11 < j) && (j < 15)) );
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 65265) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( ((11 < j) && (j < 15)) );
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 65247) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( ((4 < j) && (j < 7)) );
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 65129) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( (1 == j) );
        j = 0;
        for (i=0; i<cCurMsg; ++i) {
            if (j1939msg_getPGN(&curMsg[i]).pgn == 65262) {
                ++j;
            }
        }
        fprintf(stderr, "j = %d\n", j);
        XCTAssertTrue( (1 == j) );
       
        obj_Release(pEng);
        pEng = NULL;
    }
    
    return 1;
}



int         test_j1939en_TSC1_Direct_Clean(
    const
    char        *test_name
)
{
    J1939EN_DATA    *pEng = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    pEng = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (OBJ_NIL == pEng) );
    cCurMsg = 0;
    if (pEng) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up TSC1 msg from Transmission;
        j1939pdu_Construct(&pdu, 0, J1939_ENGINE_1, 3, J1939_TRANSMISSION_1);
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0xC1;
        data[1] = 240;
        data[2] = 0;
        for (int i=3; i<8; ++i) {
            data[i] = 0xFF;
        }
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, &msg );
        XCTAssertTrue( (true == pEng->fRetarding) );
        XCTAssertTrue( (3 == pEng->spn1480) );
        
        for (int i=0; i<50; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, NULL);
        }
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;                 // TSC1 PF
        pdu.PS = 0;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, &msg);
        XCTAssertTrue( (false == pEng->fRetarding) );
        XCTAssertTrue( (255 == pEng->spn1480) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (24 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        //XCTAssertTrue( (0x0CF00300 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        //XCTAssertTrue( (0x0C000003 == pdu.eid) );
        
        obj_Release(pEng);
        pEng = OBJ_NIL;
    }
    
    return 1;
}



int         test_j1939en_TSC1_Direct_Timeout(
    const
    char        *test_name
)
{
    J1939EN_DATA    *pEng = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );

    pEng = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (OBJ_NIL == pEng) );
    cCurMsg = 0;
    if (pEng) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = J1939_TRANSMISSION_1;
        pdu.P = 3;
        pdu.PF = 0;                 // TSC1 PF
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 1;                // Engine
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, &msg );
        XCTAssertTrue( (true == pEng->fRetarding) );
        XCTAssertTrue( (3 == pEng->spn1480) );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, NULL );
        }
        
#ifdef XYZZY
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = J1939_TRANSMISSION_1;
        pdu.P = 3;
        pdu.PF = 0;                 // TSC1 PF
        pdu.PS = 0;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;                // Disable Brake
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, &msg );
#endif
        XCTAssertTrue( (false == pEng->fRetarding) );
        XCTAssertTrue( (255 == pEng->spn1480) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (11 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        //FIXME: XCTAssertTrue( (0x18FEDF00 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0CF00300 == pdu.eid) );
        
        obj_Release(pEng);
        pEng = OBJ_NIL;
    }
    
    return 1;
}



int         test_j1939en_MSG02_Clean(
    const
    char        *test_name
)
{
    J1939EN_DATA    *pEng = NULL;
    bool            fRc;
    J1939_MSG       msg;
    uint32_t        i;
    int             count = 0;
    
    shiftsT = 0;
    shiftsF = 0;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pEng = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (OBJ_NIL == pEng) );
    cCurMsg = 0;
    if (pEng) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        fRc = j1939en_setShiftExit(pEng, shiftExit, NULL);
        XCTAssertTrue( (fRc) );
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        XCTAssertTrue( (false == pEng->fRetarding) ); // Should not be retarded
        
        // Send all msg02 msgs.
        for (i=0; i<cMsgs02; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs02[i].pdu, Msgs02[i].len, Msgs02[i].data);
            msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            //printCanMsg(&msg);
            fRc = xmtHandler(NULL, &msg);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, &msg );
            //FIXME: why did we think that this is constantly retarded ???
            //FIXME: XCTAssertTrue( (true == pEng->fRetarding) );
            if (pEng->fShifting) {
                fprintf(stderr, "\tShifting with detorque!\n");
                ++count;
            }
        }
        fprintf(stderr, "Number of messages in shift mode: %d\n",count);
        fprintf(stderr, "Number of true shifts: %d\n",shiftsT);
        fprintf(stderr, "Number of false shifts: %d\n",shiftsF);
        XCTAssertTrue( (shiftsT == shiftsF) );
        XCTAssertTrue( (shiftsT == 15) );
        
        obj_Release(pEng);
        pEng = OBJ_NIL;
    }
    
    return 1;
}



int         test_j1939en_MSG03_Clean(
    const
    char        *test_name
)
{
    J1939EN_DATA    *pEng = NULL;
    bool            fRc;
    J1939_MSG       msg;
    uint32_t        i;
    int             count = 0;
    
    shiftsT = 0;
    shiftsF = 0;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    fprintf(stderr, "Number of messages in 01: %d\n", cMsgs01);
    fprintf(stderr, "Number of messages in 02: %d\n", cMsgs02);
    fprintf(stderr, "Number of messages in 03: %d\n", cMsgs03);
   
    pEng = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (OBJ_NIL == pEng) );
    cCurMsg = 0;
    if (pEng) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        fRc = j1939en_setShiftExit(pEng, shiftExit, NULL);
        XCTAssertTrue( (fRc) );
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Send all msg03 msgs.
        for (i=0; i<cMsgs03; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs03[i].pdu, Msgs03[i].len, Msgs03[i].data);
            msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            //printCanMsg(&msg);
            fRc = xmtHandler(NULL, &msg);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, &msg );
            //FIXME: why did we think that this is constantly retarded ???
            //FIXME: XCTAssertTrue( (true == pEng->fRetarding) );
            if (pEng->fShifting) {
                fprintf(stderr, "\tShifting with detorque!\n");
                ++count;
            }
        }
        fprintf(stderr, "Number of messages in shift mode: %d\n",count);
        fprintf(stderr, "Number of true shifts: %d\n",shiftsT);
        fprintf(stderr, "Number of false shifts: %d\n",shiftsF);
        XCTAssertTrue( (shiftsT == shiftsF) );
        
        obj_Release(pEng);
        pEng = OBJ_NIL;
    }
    
    return 1;
}






TINYTEST_START_SUITE(test_j1939en);
  TINYTEST_ADD_TEST(test_j1939en_MSG03_Clean,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939en_MSG02_Clean,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939en_TSC1_Direct_Timeout,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939en_TSC1_Direct_Clean,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939en_TimedMessages,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939en_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939en);





