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
#include    <j1939ca_internal.h>
#include    <j1939can.h>
#include    <j1939sys.h>


static
J1939_MSG     lastMsg = { 0 };
static
J1939_MSG     testMsg = { 0 };
static
J1939CAN_DATA   *pCAN_RCV = OBJ_NIL;
static
J1939CAN_DATA   *pCAN_XMT = OBJ_NIL;
static
bool            fReceived = false;


static
void            messageComplete(
                                OBJ_ID          pObj,
                                uint32_t        eid,
                                uint16_t        cData,
                                uint8_t         *pData
                                )
{
    fReceived = true;
    fprintf(stderr, "Received: 0x%08X (%d)'%s'\n\n", eid, cData, pData);
}



//---------------------------------------------------------------
//                      Transmit Message Methods
//---------------------------------------------------------------

// Loopback the xmt to the rcv for the J1939CA.

typedef enum loopback_state_e {
    LOOPBACK_STATE_HANDLEMESSAGE=0,
    LOOPBACK_STATE_HANDLEPGN60928,
} LOOPBACK_STATE;


static
LOOPBACK_STATE  state = LOOPBACK_STATE_HANDLEMESSAGE;


static
bool        xmtLoopback(
    void        *pObject,           // J1939CA_DATA ptr
    uint32_t    msDelay,            // Ignore delays for now
    J1939_MSG   *pMsg
)
{
    J1939CA_DATA    *cbp = pObject;
    J1939_PDU       pdu = {0};
    J1939_PGN       pgn = {0};
    bool            fRc = false;
    
    if (pMsg) {
        pgn = j1939msg_getPGN(pMsg);
        pdu = j1939msg_getPDU(pMsg);
    }
    
    switch (state) {
            
        case LOOPBACK_STATE_HANDLEMESSAGE:
            fRc = j1939ca_HandleMessages(cbp, pdu.eid, pMsg);
            break;
            
        case LOOPBACK_STATE_HANDLEPGN60928:
            fRc = j1939ca_HandlePgn60928(cbp, pdu.eid, pMsg);
            break;
            
        default:
            break;
    }
    
    //printj1939msg(pMessage);
    return fRc;
}



static
uint8_t     caNeeded = 0;
static
uint8_t     daNeeded = 255;


static
bool            xmtPGN60928(
    void            *pObject,           // J1939CA_DATA ptr
    uint32_t        msDelay,            // Ignore delays for now
    J1939_MSG         *pMsg
)
{
    J1939_PDU       pdu = {0};
    J1939_PGN       pgn = {0};
    char            data[80];
    bool            fRc = false;
    J1939_NAME      *pName;
    
    if (NULL == pMsg) {
        fprintf(stderr, "ERROR: NoMsgSent - We were expecting a msg, but none was sent!");
        exit(8);
    }
    
    pgn = j1939msg_getPGN(pMsg);
    pdu = j1939msg_getPDU(pMsg);
    j1939msg_Copy(pMsg, &lastMsg);
    pName = (J1939_NAME *)&lastMsg.DATA.dw;
    ++pName->IDN;
    

    j1939msg_CreatePrintable( pMsg, data );
    fprintf(stderr, "accepted: %s\n", data);
    
    if (0x00EE00 == pgn.w)
        fRc = true;
    else {
        fprintf(stderr, "ERROR: NotSentPGN60928 - This message should have been PGN 60928!");
        exit(8);
    }
    if (caNeeded < 254) {
        if (caNeeded == pdu.SA)
            fRc = true;
        else {
            fprintf(stderr, "ERROR: NotCaNeeded - Message does not have correct claimed address!");
            exit(8);
        }        
    }
    if (daNeeded == pdu.PS)
        fRc = true;
    else {
        fprintf(stderr, "ERROR: NotCaNeeded - Message does not have correct claimed address!");
        exit(8);
    }
    

    //printj1939msg(pMessage);
    return fRc;
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
    pCAN_RCV = j1939can_New();
    pCAN_XMT = j1939can_New();
    cCurMsg = 0;
    fReceived = false;
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    obj_Release(pCAN_RCV);
    pCAN_RCV = OBJ_NIL;
    obj_Release(pCAN_XMT);
    pCAN_XMT = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    //j1939_SharedReset( );
    
    trace_SharedReset( );
    mem_Dump( );
    mem_Release( );
    return 1; 
}








int         test_j1939ca_OpenClose(
    const
    char        *test_name
)
{
    J1939CA_DATA	*pObj = OBJ_NIL;
   
    XCTAssertFalse( (OBJ_NIL == pCAN_RCV) );
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    
    pObj = j1939ca_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939ca_Init(
                    pObj, 
                    (OBJ_ID)pCAN_RCV,
                    (OBJ_ID)pSYS,
                    1,             // J1939 Identity Number (21 bits)
                    8192,          // J1939 Manufacturer Code (11 bits)
                    4              // J1939 Industry Group (3 bits) (Marine)
            );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN_RCV, xmtHandler, NULL);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



// Initiate an Address Claim, wait 250+ ms, then check that we have claimed
// the address.
int         test_j1939ca_ClaimAddress_clean(
    const
    char        *test_name
)
{
    J1939CA_DATA    *pCA = NULL;
    J1939_PDU       pdu = {0};
    //J1939_PGN       pgn = {0};
    bool            fRc;
    //uint32_t        msWait = 0;
    
    XCTAssertFalse( (OBJ_NIL == pCAN_RCV) );
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    
    pCA = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pCA) );
    pCA =  j1939ca_Init(
                             pCA,
                             (OBJ_ID)pCAN_RCV,
                             (OBJ_ID)pSYS,
                             1,              // J1939 Identity Number (21 bits)
                             8192,           // J1939 Manufacturer Code (11 bits)
                             4               // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pCA) );
    if (pCA) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN_RCV, xmtHandler, NULL);
        
        // The CA is in the Starting State. So, calling pgn 60928 will initiate
        // an Address Claim.
        fRc = j1939ca_HandleMessages(pCA, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pCA->cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF00 == pdu.eid) );
        
        // Send "Time Out" which should allow us to accept our claimed address
        // and go into normal operation.
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages(pCA, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pCA->cs) );

        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );

        obj_Release(pCA);
        pCA = OBJ_NIL;
    }
    
    return 1;
}



int         test_j1939ca_ClaimAddress_contested1(
    const
    char        *test_name
)
{
    J1939CA_DATA    *pJ1939ca = NULL;
    J1939_PDU       pdu = {0};
    //J1939_PGN       pgn = {0};
    bool            fRc;
    //uint32_t        msWait = 0;
    
    XCTAssertFalse( (OBJ_NIL == pCAN_RCV) );
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    
    pJ1939ca = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    pJ1939ca =  j1939ca_Init(
                             pJ1939ca,
                             (OBJ_ID)pCAN_RCV,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             4              // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    if (pJ1939ca) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN_RCV, xmtPGN60928, pJ1939ca);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, 0, NULL);
        j1939msg_Copy( &lastMsg, &testMsg );

        // This will have a larger NAME so it should insist on the claimed address.
        pdu = j1939msg_getPDU(&testMsg);

        // Send conflict.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs) );

        // Send conflict.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs) );

        obj_Release(pJ1939ca);
        pJ1939ca = OBJ_NIL;
    }
    
    return 1;
}



int         test_j1939ca_ClaimAddress_contested2(
    const
    char        *test_name
)
{
    J1939CA_DATA    *pJ1939ca = NULL;
    J1939_PDU       pdu = {0};
    //J1939_PGN       pgn = {0};
    bool            fRc;
    //uint32_t        msWait = 0;
    J1939_NAME      *pName = (J1939_NAME *)&testMsg.DATA.dw;
    
    XCTAssertFalse( (OBJ_NIL == pCAN_RCV) );
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    
    pJ1939ca = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    pJ1939ca =  j1939ca_Init(
                             pJ1939ca,
                             (OBJ_ID)pCAN_RCV,
                             (OBJ_ID)pSYS,
                             1,             // J1939 Identity Number (21 bits)
                             8192,          // J1939 Manufacturer Code (11 bits)
                             4              // J1939 Industry Group (3 bits) (Marine)
                );
    XCTAssertFalse( (OBJ_NIL == pJ1939ca) );
    if (pJ1939ca) {

        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN_RCV, xmtPGN60928, pJ1939ca);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandlePgn60928(pJ1939ca, 0, NULL);
        j1939msg_Copy( &lastMsg, &testMsg );
        // This will have the same NAME so ca should try a new address.
        --pName->IDN;
        pdu = j1939msg_getPDU(&testMsg);
        // Send conflict.
        caNeeded = 1;
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs) );
        // Send conflict.
        pdu.SA = caNeeded;
        j1939msg_setPDU(&testMsg,pdu.eid);
        caNeeded = 128;
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs) );
        // Send lots of conflicts.
        for ( ; caNeeded<248; ++caNeeded) {
            pdu.SA = caNeeded - 1;
            j1939msg_setPDU(&testMsg,pdu.eid);
            fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
            XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pJ1939ca->cs) );
        }
        // Send one more for we done!.
        pdu.SA = caNeeded - 1;
        j1939msg_setPDU(&testMsg,pdu.eid);
        fRc = j1939ca_HandlePgn60928(pJ1939ca, pdu.eid, &testMsg);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_COMMANDED_ADDRESS == pJ1939ca->cs) );
        obj_Release(pJ1939ca);
        pJ1939ca = OBJ_NIL;
    }
    
    return 1;
}



// Test to insure Transmit Delayed Messages works.
int         test_j1939ca_DelayedMessages(
    const
    char        *test_name
)
{
    J1939CA_DATA    *pCA = NULL;
    J1939_PDU       pdu = {0};
    //J1939_PGN       pgn = {0};
    bool            fRc;
    //uint32_t        msWait = 0;
    
    XCTAssertFalse( (OBJ_NIL == pCAN_RCV) );
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    
    pCA = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pCA) );
    pCA =  j1939ca_Init(
                        pCA,
                        (OBJ_ID)pCAN_RCV,
                        (OBJ_ID)pSYS,
                        1,              // J1939 Identity Number (21 bits)
                        8192,           // J1939 Manufacturer Code (11 bits)
                        4               // J1939 Industry Group (3 bits) (Marine)
                        );
    XCTAssertFalse( (OBJ_NIL == pCA) );
    if (pCA) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN_RCV, xmtHandler, NULL);
        
        // The CA is in the Starting State. So, calling pgn 60928 will initiate
        // an Address Claim.
        fRc = j1939ca_HandleMessages(pCA, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pCA->cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF00 == pdu.eid) );
        
        // Send "Time Out" which should allow us to accept our claimed address
        // and go into normal operation.
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages(pCA, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pCA->cs) );
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (1 == cCurMsg) );
        
        obj_Release(pCA);
        pCA = OBJ_NIL;
    }
    
    return 1;
}



int         test_j1939ca_RequestNameDirect(
    const
    char        *test_name
)
{
    J1939CA_DATA    *pCA = NULL;
    bool            fRc;
    J1939_MSG       msg;
    J1939_PDU       pdu;
    //uint8_t         data[8];
    
    XCTAssertFalse( (OBJ_NIL == pCAN_RCV) );
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    
    pCA = j1939ca_Alloc();
    XCTAssertFalse( (OBJ_NIL == pCA) );
    pCA =  j1939ca_Init(
                pCA,
                (OBJ_ID)pCAN_RCV,
                (OBJ_ID)pSYS,
                1,             // J1939 Identity Number (21 bits)
                8192,           // J1939 Manufacturer Code (11 bits)
                4              // J1939 Industry Group (3 bits) (Marine)
            );
    XCTAssertFalse( (OBJ_NIL == pCA) );
    cCurMsg = 0;
    if (pCA) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN_RCV, xmtHandler, NULL);
        
        // Initiate Address Claim.
        fRc = j1939ca_HandleMessages(pCA, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS == pCA->cs) );
        XCTAssertTrue( (1 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF00 == pdu.eid) );

        // Send "Timed Out".
        j1939sys_BumpMS(pSYS, 250);
        fRc = j1939ca_HandleMessages(pCA, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pCA->cs) );
        
        // Setup up msg from #3 Transmission to ER requesting NAME;
        composeRQ_PGN(&msg, 3, 41, 0x0000EE00);
        fRc = j1939ca_HandleMessages( pCA, 0, &msg );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        XCTAssertTrue( (0x18EEFF00 == pdu.eid) );
        
        obj_Release(pCA);
        pCA = OBJ_NIL;
    }
    
    return 1;
}



// Transmit BAM Message and receive it with everything working
int         test_j1939ca_MessageTransmitBAM01(
    const
    char        *test_name
)
{
    J1939CA_DATA	*pRcv = OBJ_NIL;
    J1939CA_DATA	*pXmt = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    //J1939_PDU       pduMsg;
    J1939_PGN       pgn;
    int             i;
    //J1939_MSG       msg;
    bool            fRc;
    uint32_t        softlvl;
    
    XCTAssertFalse( (OBJ_NIL == pCAN_RCV) );
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    
    pRcv = j1939ca_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    pRcv =  j1939ca_Init(
                        pRcv,
                        (OBJ_ID)pCAN_RCV,
                        (OBJ_ID)pSYS,
                        1,             // J1939 Identity Number (21 bits)
                        8192,          // J1939 Manufacturer Code (11 bits)
                        4              // J1939 Industry Group (3 bits) (Marine)
            );
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    j1939ca_Setup(pRcv, J1939_CAB_CONTROLLER_PRIMARY);
    pRcv->cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we have our name.

    pXmt = j1939ca_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    pXmt =  j1939ca_Init(
                        pXmt,
                        (OBJ_ID)pCAN_XMT,
                        (OBJ_ID)pSYS,
                        1,             // J1939 Identity Number (21 bits)
                        8192,          // J1939 Manufacturer Code (11 bits)
                        4              // J1939 Industry Group (3 bits) (Marine)
            );
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    j1939ca_Setup(pXmt, J1939_POWER_TAKEOFF_1);
    pXmt->cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we have our name.

    if (pRcv && pXmt) {
        
        j1939sys_TimeReset(pSYS, 0);

        // We need two J1939CAN objects, because we are doing bidirectional messaging
        // now. We assign pCAN_RCV to the Receiver and pCAN_XMT to the Transmitter.
        j1939can_setXmtMsg(pCAN_RCV, xmtHandler, NULL);
        j1939can_setRcvMsg(pCAN_RCV, (P_XMTMSG_RTN)j1939ca_HandleMessages, pXmt);
        j1939can_setLoopBackXmt(pCAN_RCV, true);
        j1939can_setXmtMsg(pCAN_XMT, xmtHandler, NULL);
        j1939can_setRcvMsg(pCAN_XMT, (P_XMTMSG_RTN)j1939ca_HandleMessages, pRcv);
        j1939can_setLoopBackXmt(pCAN_XMT, true);
        softlvl = pRcv->softwareLevel;
        
        pgn.pgn = 65242;
        fRc = j1939ca_TransmitPgn59904(pRcv, pgn, J1939_POWER_TAKEOFF_1);
        XCTAssertTrue( (fRc) );
        
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CECFF06 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 32) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 13) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        for (i=0; i<6; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939ca_HandleMessages(pXmt, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (4 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF06 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF06 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 2) );
        
        XCTAssertTrue( (!(softlvl == pRcv->softwareLevel)) );
        
        obj_Release(pRcv);
        pRcv = OBJ_NIL;
        obj_Release(pXmt);
        pXmt = OBJ_NIL;
    }
    
    return 1;
}



// Transport Protocol - Transmit with everything working
int         test_j1939ca_MessageTransmitRTS01(
    const
    char        *test_name
)
{
    J1939CA_DATA	*pRcv = OBJ_NIL;
    J1939CA_DATA	*pXmt = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    J1939_PGN       pgn;
    int             i;
    uint32_t        softlvl;
    bool            fRc;
    
    XCTAssertFalse( (OBJ_NIL == pCAN_RCV) );
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    
    pRcv = j1939ca_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    pRcv =  j1939ca_Init(
                         pRcv,
                         (OBJ_ID)pCAN_RCV,
                         (OBJ_ID)pSYS,
                         1,             // J1939 Identity Number (21 bits)
                         8192,          // J1939 Manufacturer Code (11 bits)
                         4              // J1939 Industry Group (3 bits) (Marine)
                         );
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    j1939ca_Setup(pRcv, J1939_CAB_CONTROLLER_PRIMARY);
    pRcv->cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we have our name.
    
    pXmt = j1939ca_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    pXmt =  j1939ca_Init(
                         pXmt,
                         (OBJ_ID)pCAN_XMT,
                         (OBJ_ID)pSYS,
                         1,             // J1939 Identity Number (21 bits)
                         8192,          // J1939 Manufacturer Code (11 bits)
                         4              // J1939 Industry Group (3 bits) (Marine)
                         );
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    j1939ca_Setup(pXmt, J1939_POWER_TAKEOFF_1);
    pXmt->cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we have our name.
    
    if (pRcv && pXmt) {
        
        j1939sys_TimeReset(pSYS, 0);
        
        // We need two J1939CAN objects, because we are doing bidirectional messaging
        // now. We assign pCAN_RCV to the Receiver and pCAN_XMT to the Transmitter.
        j1939can_setXmtMsg(pCAN_RCV, xmtHandler, NULL);
        j1939can_setRcvMsg(pCAN_RCV, (P_XMTMSG_RTN)j1939ca_HandleMessages, pXmt);
        j1939can_setLoopBackXmt(pCAN_RCV, true);
        j1939can_setXmtMsg(pCAN_XMT, xmtHandler, NULL);
        j1939can_setRcvMsg(pCAN_XMT, (P_XMTMSG_RTN)j1939ca_HandleMessages, pRcv);
        j1939can_setLoopBackXmt(pCAN_XMT, true);
        softlvl = pRcv->softwareLevel;
        
        pgn.pgn = 61184;
        fRc = j1939ca_TransmitPgn59904(pRcv, pgn, J1939_POWER_TAKEOFF_1);
        XCTAssertTrue( (fRc) );
        
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC3106 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 16) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[1] == 13) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[2] == 0) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 17) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 2) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 1) );
        
        for (i=0; i<6; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939ca_HandleMessages(pXmt, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (6 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-3]);
        fprintf(stderr, "msg[-3] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEB3106 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-3].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-3].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEB3106 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 2) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 19) );
        
        XCTAssertTrue( (!(softlvl == pRcv->softwareLevel)) );
        
        obj_Release(pRcv);
        pRcv = OBJ_NIL;
        obj_Release(pXmt);
        pXmt = OBJ_NIL;
    }
    
    return 1;
}












TINYTEST_START_SUITE(test_j1939ca);
  TINYTEST_ADD_TEST(test_j1939ca_MessageTransmitRTS01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939ca_MessageTransmitBAM01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939ca_RequestNameDirect,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939ca_DelayedMessages,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939ca_ClaimAddress_contested2,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939ca_ClaimAddress_contested1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939ca_ClaimAddress_clean,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939ca_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939ca);





