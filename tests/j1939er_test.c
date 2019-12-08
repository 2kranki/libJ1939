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
#include    <j1939er_internal.h>
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








int         test_j1939er_OpenClose(
    const
    char        *pTestName
)
{
    J1939ER_DATA	*pER = OBJ_NIL;
    bool            fRc;
    J1939_PDU       pdu;    
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pER = j1939er_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pER) );
    pER = j1939er_Init(
                    pER, 
                    (OBJ_ID)pCAN,
                    (OBJ_ID)pSYS,
                    1,             // J1939 Identity Number (21 bits)
                    8192,          // J1939 Manufacturer Code (11 bits)
                    4              // J1939 Industry Group (3 bits) (Marine)
            );
    TINYTEST_FALSE( (OBJ_NIL == pER) );
    if (pER) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        XCTAssertTrue( (0 == cCurMsg) );

        obj_Release(pER);
        pER = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_j1939er_Transmits(
    const
    char        *pTestName
)
{
    J1939ER_DATA    *pER = NULL;
    J1939_PDU       pdu;
    bool            fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (NULL == pER) );
    pER = j1939er_Init(
                       pER,
                       (OBJ_ID)pCAN,
                       (OBJ_ID)pSYS,
                       1,               // J1939 Identity Number (21 bits)
                       8192,            // J1939 Manufacturer Code (11 bits)
                       4                // J1939 Industry Group (3 bits) (Marine)
                       );
    XCTAssertFalse( (NULL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        fRc = j1939er_TransmitPgn61440(pER);
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
        //FIXME: msg size is 19, so we need large msg xmt!
#ifdef XYZZY
        fRc = j1939er_TransmitPgn65249(pER);
        // Initiate Address Claim.
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
#endif
        
        obj_Release(pER);
        pER = NULL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_j1939er_RequestNameDirect(
    const
    char        *pTestName
)
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                        pER,
                        (OBJ_ID)pCAN,
                        (OBJ_ID)pSYS,
                        1,              // J1939 Identity Number (21 bits)
                        8192,            // J1939 Manufacturer Code (11 bits)
                        4               // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );

        // Send msg from #3 Transmission to ER requesting NAME;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;              // Request PGN PF
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0xEE;             // Address Claim PF
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        
        // Now handle the response
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf( stderr, "eid[-2] = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x0CEA2903 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf( stderr, "eid[-1] = 0x%08X\n", pdu.eid );
        XCTAssertTrue( (0x18EEFF29 == pdu.eid) );

        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_j1939er_RequestBadNameDirect(
    const
    char        *pTestName
)
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             4              // J1939 Industry Group (3 bits) (Marine)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );

        // Setup up msg from #3 Transmission to ER requesting an unknown EID;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0x00;
        data[1] = 0x23;         // Not Sure what this is! lol
        data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);
        
        // Now handle the response.
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0CEA2903 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18E80329 == pdu.eid) );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_j1939er_RequestBadNameGlobal(
    const
    char        *pTestName
)
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             4              // J1939 Industry Group (3 bits) (Marine)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to ER requesting unknown EID;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0xEA;          // Request PGN PF
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
        
        // Now handle the message.
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        // It will not nak since we asked globablly.
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0xCEAFF03 == pdu.eid) );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_j1939er_RequestIRC1Direct(
    const
    char        *pTestName
)
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             4              // J1939 Industry Group (3 bits) (Marine)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
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
        
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0CEA2903 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_j1939er_TimedIRC1(
    const
    char        *pTestName
)
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_PDU       pdu;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             4              // J1939 Industry Group (3 bits) (Marine)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Let's go 1000 ms in the future.
        // We should see 10 ERC1s because they are
        // issued every 100ms.
        for (int i=0; i<100; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, NULL );
        }        

        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (11 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_j1939er_TSC1_Direct_Clean(
    const
    char        *pTestName
)
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             4              // J1939 Industry Group (3 bits) (Marine)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        XCTAssertTrue( (!pER->fActive) );

        // Tell Engine Retarder to Brake.
        // Setup up msg from #3 Transmission via TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;                 // TSC1 PF
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
        
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (pER->fActive) );
        XCTAssertTrue( (3 == pER->spn1480) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0X0C002903 == pdu.eid) );

        // Put us 1000ms into the future.
        // Should give us 10 ERC1s.
        for (int i=0; i<100; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, NULL );
        }
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (13 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        //      *** Tell Engine Retarder to Stop. ***
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;             // Torque/SpeedControl1 (TSC1) PF
        pdu.PS = 41;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 0;            // Disable Engine Retarder
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, &msg);    // Show that we are sending this.
        
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (!pER->fActive) );
        XCTAssertTrue( (255 == pER->spn1480) );
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (14 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0C002903 == pdu.eid) );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_j1939er_TSC1_Direct_Timeout(
    const
    char        *pTestName
)
{
    J1939ER_DATA    *pER = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    uint8_t         data[8];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pER = j1939er_Alloc();
    XCTAssertFalse( (OBJ_NIL == pER) );
    pER =  j1939er_Init(
                             pER,
                             (OBJ_ID)pCAN,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             4              // J1939 Industry Group (3 bits) (Marine)
                             );
    XCTAssertFalse( (OBJ_NIL == pER) );
    cCurMsg = 0;
    if (pER) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pER, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pER->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        //          *** Tell Engine Retarder to Brake. ***
        
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
        
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (pER->fActive) );
        XCTAssertTrue( (3 == pER->spn1480) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%08X\n", pdu.eid);
        XCTAssertTrue( (0X0C002903 == pdu.eid) );
        
        for (int i=0; i<100; ++i) {
            j1939sys_BumpMS(pSYS, 10);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, NULL );
        }
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (13 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        
        // Tell Engine Retarder to Stop.
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
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pER, &msg );
        XCTAssertTrue( (false == pER->fActive) );
        XCTAssertTrue( (255 == pER->spn1480) );
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (14 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18F00029 == pdu.eid) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0C002903 == pdu.eid) );
        
        obj_Release(pER);
        pER = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}





TINYTEST_START_SUITE(test_j1939er);
  TINYTEST_ADD_TEST(test_j1939er_TSC1_Direct_Timeout,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939er_TSC1_Direct_Clean,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939er_TimedIRC1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939er_RequestIRC1Direct,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939er_RequestBadNameGlobal,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939er_RequestBadNameDirect,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939er_RequestNameDirect,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939er_Transmits,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939er_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939er);





