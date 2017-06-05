/*
 *	Generated 04/18/2017 12:48:07
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
#include    <j1939tp_internal.h>
#include    <j1939can.h>
#include    <j1939sys.h>


static
J1939CAN_DATA   *pCAN = OBJ_NIL;


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








int         test_j1939tp_OpenClose(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pObj = OBJ_NIL;
   
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pObj = j1939tp_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(  
                    pObj, 
                    (OBJ_ID)pCAN,
                    (OBJ_ID)pSYS,
                    'a'
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



int         test_j1939tp_TransmitPacket(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        pObj->rcv = 255;
        pObj->xmt = J1939_CAB_CONTROLLER_PRIMARY;
        pObj->packets = 2;
        pObj->size = 10;
        memmove(pObj->data, "1234567890", 10);
        
        eRc = j1939tp_TransmitPacket(pObj, 0);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 1) );
        
        eRc = j1939tp_TransmitPacket(pObj, 1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 2) );
        
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1; 
}



// Transmit BAM Message with everything working
int         test_j1939tp_TransmitBAM01(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    int             i;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        pdu.eid = 0x18EFFF31;
        eRc = j1939tp_MessageTransmit(pObj, pdu, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pObj->rcv == 255) );
        XCTAssertTrue( (pObj->xmt == J1939_CAB_CONTROLLER_PRIMARY) );
        
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CECFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 32) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        
        
        for (i=0; i<200; i+=20) {
            j1939sys_BumpMS(pSYS,40);
            eRc = j1939tp_ProcessPackets(pObj);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 2) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1; 
}



// Transmit BAM Message with everything working
int         test_j1939tp_TransmitBAM02(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    int             i;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        pdu.eid = 0x18EFFF31;
        eRc = j1939tp_MessageTransmit(pObj, pdu, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pObj->rcv == 255) );
        XCTAssertTrue( (pObj->xmt == J1939_CAB_CONTROLLER_PRIMARY) );
        
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CECFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 32) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        for (i=0; i<200; i+=20) {
            j1939sys_BumpMS(pSYS,40);
            eRc = j1939tp_HandleMessages(pObj, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 2) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1; 
}



// Transmit BAM Message and receive it with everything working
int         test_j1939tp_TransmitBAM03(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pRcv = OBJ_NIL;
    J1939TP_DATA	*pXmt = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    J1939_PDU       pduMsg;
    J1939_PGN       pgnMsg;
    int             i;
    //J1939_MSG       msg;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pRcv = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    pRcv = j1939tp_Init(pRcv, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    pXmt = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    pXmt = j1939tp_Init(pXmt, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_POWER_TAKEOFF_1);
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    if (pRcv && pXmt) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        j1939can_setRcvMsg(pCAN, (P_SRVCMSG_RTN)j1939tp_HandleMessages, pRcv);
        j1939can_setLoopBackXmt(pCAN, true);
        j1939tp_setRcvdMsg(pRcv, (void *)messageComplete, OBJ_NIL);
        
        j1939pdu_Construct(&pduMsg, 239, J1939_GENERAL_BROADCAST, 6, J1939_POWER_TAKEOFF_1);
        pgnMsg = j1939pdu_getPGN(pduMsg);
        eRc = j1939tp_MessageTransmit(pXmt, pduMsg, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pRcv->rcv == 255) );
        XCTAssertTrue( (pRcv->xmt == J1939_POWER_TAKEOFF_1) );
        XCTAssertTrue( (pXmt->rcv == 255) );
        XCTAssertTrue( (pXmt->xmt == J1939_POWER_TAKEOFF_1) );
        
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CECFF06 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 32) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        for (i=0; i<6; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939tp_HandleMessages(pXmt, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
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
        
        XCTAssertTrue( (fReceived) );
        XCTAssertTrue( (pRcv->activity == J1939TP_INACTIVE) );
        XCTAssertTrue( (pRcv->state == J1939TP_STATE_UNKNOWN) );
        XCTAssertTrue( (pRcv->stateProto == J1939TP_STATE_PROTO_WAITING_FOR_WORK) );
        
        obj_Release(pRcv);
        pRcv = OBJ_NIL;
        obj_Release(pXmt);
        pXmt = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tp_TransmitBAM04(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pRcv = OBJ_NIL;
    J1939TP_DATA	*pXmt = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    J1939_PDU       pduMsg;
    J1939_PGN       pgnMsg;
    int             i;
    //J1939_MSG       msg;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pRcv = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    pRcv = j1939tp_Init(pRcv, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    pXmt = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    pXmt = j1939tp_Init(pXmt, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_POWER_TAKEOFF_1);
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    if (pRcv && pXmt) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        j1939can_setRcvMsg(pCAN, (P_SRVCMSG_RTN)j1939tp_HandleMessages, pRcv);
        j1939can_setLoopBackXmt(pCAN, true);
        j1939tp_setRcvdMsg(pRcv, (void *)messageComplete, OBJ_NIL);
        
        j1939pdu_Construct(&pduMsg, 239, J1939_GENERAL_BROADCAST, 6, J1939_POWER_TAKEOFF_1);
        pgnMsg = j1939pdu_getPGN(pduMsg);
        eRc = j1939tp_MessageTransmit(pXmt, pduMsg, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pRcv->rcv == 255) );
        XCTAssertTrue( (pRcv->xmt == J1939_POWER_TAKEOFF_1) );
        XCTAssertTrue( (pXmt->rcv == 255) );
        XCTAssertTrue( (pXmt->xmt == J1939_POWER_TAKEOFF_1) );

        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CECFF06 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 32) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        j1939sys_BumpMS(pSYS,100);
        eRc = j1939tp_HandleMessages(pXmt, 0, NULL);

        for (i=0; i<10; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939tp_HandleMessages(pRcv, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (2 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEBFF06 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 1) );
        
        XCTAssertTrue( (!fReceived) );
        XCTAssertTrue( (pRcv->activity == J1939TP_INACTIVE) );
        XCTAssertTrue( (pRcv->state == J1939TP_STATE_UNKNOWN) );
        XCTAssertTrue( (pRcv->stateProto == J1939TP_STATE_PROTO_WAITING_FOR_WORK) );
        
        
        obj_Release(pRcv);
        pRcv = OBJ_NIL;
        obj_Release(pXmt);
        pXmt = OBJ_NIL;
    }
    
    return 1; 
}



// Transport Protocol - Transmit with everything working
int         test_j1939tp_TransmitRTS01(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    J1939_PDU       pduMsg;
    J1939_PGN       pgnMsg;
    int             i;
    J1939_MSG       msg;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        j1939pdu_Construct(&pduMsg, 239, J1939_POWER_TAKEOFF_1, 6, J1939_CAB_CONTROLLER_PRIMARY);
        pgnMsg = j1939pdu_getPGN(pduMsg);
        eRc = j1939tp_MessageTransmit(pObj, pduMsg, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pObj->rcv == J1939_POWER_TAKEOFF_1) );
        XCTAssertTrue( (pObj->xmt == J1939_CAB_CONTROLLER_PRIMARY) );

        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 16) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );

        composeTP_CTS(
                      &msg,
                      J1939_POWER_TAKEOFF_1,
                      J1939_CAB_CONTROLLER_PRIMARY,
                      pgnMsg.pgn,
                      2,
                      1
        );
        eRc = j1939tp_HandleMessages(pObj, j1939msg_getPDU(&msg).eid, &msg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        for (i=0; i<6; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939tp_HandleMessages(pObj, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        composeTP_EOM(
                      &msg,
                      J1939_POWER_TAKEOFF_1,
                      J1939_CAB_CONTROLLER_PRIMARY,
                      pgnMsg.pgn,
                      2,
                      10
        );
        eRc = j1939tp_HandleMessages(pObj, j1939msg_getPDU(&msg).eid, &msg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-3]);
        fprintf(stderr, "msg[-3] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEB0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-3].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-3].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEB0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 2) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tp_TransmitRTS02(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    J1939_PDU       pduMsg;
    J1939_PGN       pgnMsg;
    int             i;
    J1939_MSG       msg;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        j1939pdu_Construct(&pduMsg, 239, J1939_POWER_TAKEOFF_1, 6, J1939_CAB_CONTROLLER_PRIMARY);
        pgnMsg = j1939pdu_getPGN(pduMsg);
        eRc = j1939tp_MessageTransmit(pObj, pduMsg, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pObj->rcv == J1939_POWER_TAKEOFF_1) );
        XCTAssertTrue( (pObj->xmt == J1939_CAB_CONTROLLER_PRIMARY) );

        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 16) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        composeTP_CTS(
                      &msg,
                      J1939_POWER_TAKEOFF_1,
                      J1939_CAB_CONTROLLER_PRIMARY,
                      pgnMsg.pgn,
                      1,                // # of packets
                      1                 // Seq Number
                      );
        eRc = j1939tp_HandleMessages(pObj, j1939msg_getPDU(&msg).eid, &msg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Allow one message to be sent
        for (i=0; i<4; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939tp_HandleMessages(pObj, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        composeTP_CTS(
                      &msg,
                      J1939_POWER_TAKEOFF_1,
                      J1939_CAB_CONTROLLER_PRIMARY,
                      pgnMsg.pgn,
                      0,                // # of packets (0 == pause)
                      255               // Seq Number
        );
        eRc = j1939tp_HandleMessages(pObj, j1939msg_getPDU(&msg).eid, &msg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        for (i=0; i<5; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939tp_HandleMessages(pObj, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        composeTP_CTS(
                      &msg,
                      J1939_POWER_TAKEOFF_1,
                      J1939_CAB_CONTROLLER_PRIMARY,
                      pgnMsg.pgn,
                      1,                // # of packets
                      2                 // Seq Number
                      );
        eRc = j1939tp_HandleMessages(pObj, j1939msg_getPDU(&msg).eid, &msg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        for (i=0; i<6; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939tp_HandleMessages(pObj, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        j1939pdu_Construct(&pdu, 239, J1939_POWER_TAKEOFF_1, 6, J1939_CAB_CONTROLLER_PRIMARY);
        composeTP_EOM(
                      &msg,
                      J1939_POWER_TAKEOFF_1,
                      J1939_CAB_CONTROLLER_PRIMARY,
                      pgnMsg.pgn,
                      2,
                      10
                      );
        eRc = j1939tp_HandleMessages(pObj, j1939msg_getPDU(&msg).eid, &msg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (7 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-5]);
        fprintf(stderr, "msg[-5] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEB0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-5].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-5].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 255) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC3106 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 19) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1; 
}



int         test_j1939tp_TransmitRTS03(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    J1939_PDU       pduMsg;
    J1939_PGN       pgnMsg;
    int             i;
    J1939_MSG       msg;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        j1939pdu_Construct(&pduMsg, 239, J1939_POWER_TAKEOFF_1, 6, J1939_CAB_CONTROLLER_PRIMARY);
        pgnMsg = j1939pdu_getPGN(pduMsg);
        eRc = j1939tp_MessageTransmit(pObj, pduMsg, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pObj->rcv == J1939_POWER_TAKEOFF_1) );
        XCTAssertTrue( (pObj->xmt == J1939_CAB_CONTROLLER_PRIMARY) );

        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 16) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        composeTP_CTS(
                      &msg,
                      J1939_POWER_TAKEOFF_1,
                      J1939_CAB_CONTROLLER_PRIMARY,
                      pgnMsg.pgn,
                      2,
                      1
                      );
        eRc = j1939tp_HandleMessages(pObj, j1939msg_getPDU(&msg).eid, &msg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        for (i=0; i<13; ++i) {
            j1939sys_BumpMS(pSYS,100);
            eRc = j1939tp_HandleMessages(pObj, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        // Allow EOM_ACK to Time out;
#ifdef XYZZY
        j1939pdu_Construct(&pdu, 239, J1939_POWER_TAKEOFF_1, 6, J1939_CAB_CONTROLLER_PRIMARY);
        composeTP_EOM(
                      &msg,
                      J1939_POWER_TAKEOFF_1,
                      J1939_CAB_CONTROLLER_PRIMARY,
                      pgnMsg.pgn,
                      2,
                      10
                      );
        eRc = j1939tp_HandleMessages(pObj, j1939msg_getPDU(&msg).eid, &msg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
#endif
        
        for (i=0; i<20; ++i) {
            j1939sys_BumpMS(pSYS,200);
            eRc = j1939tp_HandleMessages(pObj, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-3]);
        fprintf(stderr, "msg[-3] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEB0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-3].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-3].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEB0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 2) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC0631 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 255) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1; 
}



// Transport Protocol - Transmit and Receive with everything working
int         test_j1939tp_TransmitRTS04(
    const
    char        *test_name
)
{
    J1939TP_DATA	*pRcv = OBJ_NIL;
    J1939TP_DATA	*pXmt = OBJ_NIL;
    J1939CAN_DATA   *pCAN_XMT = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    J1939_PDU       pduMsg;
    J1939_PGN       pgnMsg;
    int             i;
    //J1939_MSG       msg;
    
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    XCTAssertTrue( (0 == cCurMsg) );
    
    pRcv = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    pRcv = j1939tp_Init(pRcv, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pRcv) );
    obj_setMisc1(pCAN, J1939_CAB_CONTROLLER_PRIMARY);

    pCAN_XMT = j1939can_New();
    XCTAssertFalse( (OBJ_NIL == pCAN_XMT) );
    pXmt = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    pXmt = j1939tp_Init(pXmt, (OBJ_ID)pCAN_XMT, (OBJ_ID)pSYS, J1939_POWER_TAKEOFF_1);
    XCTAssertFalse( (OBJ_NIL == pXmt) );
    obj_setMisc1(pCAN_XMT, J1939_POWER_TAKEOFF_1);
    if (pRcv && pXmt) {
        
        
        j1939sys_TimeReset(pSYS, 0);
        // We need two J1939CAN objects, because we are doing bidirectional messaging
        // now. We assign pCAN to the Receiver and pCAN_XMT to the Transmitter.
        //j1939can_setRcvMsg(pCAN, (P_SRVCMSG_RTN)j1939tp_HandleMessages, pCAN);
        j1939can_setXmtReflectMsg(pCAN, xmtHandler, NULL);
        j1939can_setXmtMsg(pCAN, (P_XMTMSG_RTN)j1939tp_HandleMessages, pXmt);
        j1939tp_setRcvdMsg(pRcv, (void *)messageComplete, OBJ_NIL);

        //j1939can_setRcvMsg(pCAN_XMT, (P_SRVCMSG_RTN)j1939tp_HandleMessages, pRcv);
        j1939can_setXmtReflectMsg(pCAN_XMT, xmtHandler, NULL);
        j1939can_setXmtMsg(pCAN_XMT, (P_XMTMSG_RTN)j1939tp_HandleMessages, pRcv);
        
        j1939pdu_Construct(&pduMsg, 239, J1939_CAB_CONTROLLER_PRIMARY, 6, J1939_POWER_TAKEOFF_1);
        pgnMsg = j1939pdu_getPGN(pduMsg);
        eRc = j1939tp_MessageTransmit(pXmt, pduMsg, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pRcv->rcv == J1939_CAB_CONTROLLER_PRIMARY) );
        XCTAssertTrue( (pRcv->xmt == J1939_POWER_TAKEOFF_1) );
        XCTAssertTrue( (pXmt->rcv == J1939_CAB_CONTROLLER_PRIMARY) );
        XCTAssertTrue( (pXmt->xmt == J1939_POWER_TAKEOFF_1) );

        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x1CEC3106 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 16) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[1] == 10) );
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
            eRc = j1939tp_HandleMessages(pXmt, 0, NULL);
            eRc = j1939tp_HandleMessages(pRcv, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (5 == cCurMsg) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-3]);
        fprintf(stderr, "msg[-3] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (235 == pdu.PF) );
        XCTAssertTrue( (J1939_POWER_TAKEOFF_1 == pdu.SA) );
        XCTAssertTrue( (J1939_CAB_CONTROLLER_PRIMARY == pdu.PS) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-3].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-3].DATA.bytes[0] == 1) );
        pdu = j1939msg_getPDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (235 == pdu.PF) );
        XCTAssertTrue( (J1939_POWER_TAKEOFF_1 == pdu.SA) );
        XCTAssertTrue( (J1939_CAB_CONTROLLER_PRIMARY == pdu.PS) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 2) );
        
        XCTAssertTrue( (fReceived) );
        XCTAssertTrue( (pRcv->activity == J1939TP_INACTIVE) );
        XCTAssertTrue( (pRcv->state == J1939TP_STATE_UNKNOWN) );
        XCTAssertTrue( (pRcv->stateProto == J1939TP_STATE_PROTO_WAITING_FOR_WORK) );
        XCTAssertTrue( (pXmt->activity == J1939TP_INACTIVE) );
        XCTAssertTrue( (pXmt->state == J1939TP_STATE_UNKNOWN) );
        XCTAssertTrue( (pXmt->stateProto == J1939TP_STATE_PROTO_WAITING_FOR_WORK) );
        
        obj_Release(pRcv);
        pRcv = OBJ_NIL;
        obj_Release(pXmt);
        pXmt = OBJ_NIL;
        obj_Release(pCAN_XMT);
        pCAN_XMT = OBJ_NIL;
    }
    
    return 1; 
}







TINYTEST_START_SUITE(test_j1939tp);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitRTS04,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitRTS03,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitRTS02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitRTS01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitBAM04,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitBAM03,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitBAM02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitBAM01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_TransmitPacket,setUp,tearDown);
  TINYTEST_ADD_TEST(test_j1939tp_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939tp);





