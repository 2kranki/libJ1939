/*
 *	Generated 04/18/2017 12:48:07
 */


#import <XCTest/XCTest.h>



// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      XCTAssert(expression, failure_description, ...)
//      XCTFail(failure_description, ...)
//      XCTAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      XCTAssertEquals(value_1, value_2, failure_description, ...)
//      XCTAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      XCTAssertNil(expression, failure_description, ...)
//      XCTAssertNotNil(expression, failure_description, ...)
//      XCTAssertTrue(expression, failure_description, ...)
//      XCTAssertFalse(expression, failure_description, ...)
//      XCTAssertThrows(expression, failure_description, ...)
//      XCTAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)


#include    <j1939tp_internal.h>
#include	"common.h"
#include    "j1939Can.h"
#include    "j1939Sys.h"



static
J1939CAN_DATA   *pCAN = OBJ_NIL;


void            composeTP_CTS(
    J1939_MSG       *pMsg,
    uint8_t         da,
    uint8_t         sa,
    uint32_t        eid,
    uint8_t         cPackets,
    uint8_t         nextPacket
)
{
    J1939_PDU       pdu;
    J1939_PDU       pduCTS;
    uint8_t         data[8];
    bool            fRc;
    
    pdu.eid = eid;
    
    pduCTS.eid = 0;
    pduCTS.SA = sa;
    pduCTS.P = 7;
    pduCTS.PF = 236;
    pduCTS.PS = da;
    
    data[0] = 17;
    data[1] = cPackets;
    data[2] = nextPacket;
    data[3] = 0xFF;
    data[4] = 0xFF;
    data[5] = eid & 0xFF;
    data[6] = (eid >> 8) & 0xFF;
    data[7] = (eid >> 16) & 0xFF;
    
    j1939msg_ConstructMsg_E1(pMsg, pduCTS.eid, 8, data);
    pMsg->CMSGSID.CMSGTS = 0xFFFF;          // Denote transmitting;
    fRc = xmtHandler(NULL, 0, pMsg);
    
}



void            composeTP_EOM(
    J1939_MSG       *pMsg,
    uint8_t         da,
    uint8_t         sa,
    uint32_t        eid,
    uint8_t         cPackets,
    uint16_t        size
)
{
    J1939_PDU       pdu;
    J1939_PDU       pduCTS;
    uint8_t         data[8];
    bool            fRc;
    
    pdu.eid = eid;
    
    pduCTS.eid = 0;
    pduCTS.SA = sa;
    pduCTS.P = 7;
    pduCTS.PF = 236;
    pduCTS.PS = da;
    
    data[0] = 19;
    data[1] = size & 0xFF;
    data[2] = (size >> 8) & 0xFF;
    data[3] = cPackets;
    data[4] = 0xFF;
    data[5] = eid & 0xFF;
    data[6] = (eid >> 8) & 0xFF;
    data[7] = (eid >> 16) & 0xFF;
    
    j1939msg_ConstructMsg_E1(pMsg, pduCTS.eid, 8, data);
    pMsg->CMSGSID.CMSGTS = 0xFFFF;          // Denote transmitting;
    fRc = xmtHandler(NULL, 0, pMsg);
    
}






@interface j1939tpTests : XCTestCase

@end

@implementation j1939tpTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
    pSYS = j1939Sys_New();
    pCAN = j1939can_New();
    cCurMsg = 0;
    
}


- (void)tearDown
{
    obj_Release(pCAN);
    pCAN = OBJ_NIL;
    obj_Release(pSYS);
    pSYS = OBJ_NIL;
    //j1939_SharedReset( );
    
    mem_Dump( );
    mem_Release( );

    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
}




- (void)testOpenClose
{
    J1939TP_DATA	*pObj = OBJ_NIL;
   
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testTransmitPacket
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        pObj->adr = 255;
        pObj->packets = 2;
        pObj->size = 10;
        memmove(pObj->data, "1234567890", 10);
        
        eRc = j1939tp_TransmitPacket(pObj, 0);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18EBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 1) );
        
        eRc = j1939tp_TransmitPacket(pObj, 1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18EBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 2) );
        
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testMessageTransmitBAM01
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    int             i;
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        pdu.eid = 0x18EFFF31;
        eRc = j1939tp_MessageTransmit(pObj, pdu, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18ECFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 32) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        for (i=0; i<200; i+=20) {
            j1939Sys_BumpMS(pSYS,40);
            eRc = j1939tp_ProcessPackets(pObj);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18EBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18EBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 2) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testMessageTransmitBAM02
{
    J1939TP_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    J1939_PDU       pdu;
    int             i;
    
    pObj = j1939tp_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939tp_Init(pObj, (OBJ_ID)pCAN, (OBJ_ID)pSYS, J1939_CAB_CONTROLLER_PRIMARY);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        pdu.eid = 0x18EFFF31;
        eRc = j1939tp_MessageTransmit(pObj, pdu, 10, "1234567890");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18ECFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 32) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[1]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[1] == 10) );
        fprintf(stderr, "byte[1]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[2]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[2] == 0) );
        
        for (i=0; i<200; i+=20) {
            j1939Sys_BumpMS(pSYS,40);
            eRc = j1939tp_HandleMessages(pObj, 0, NULL);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (3 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18EBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-2].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-2].DATA.bytes[0] == 1) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x18EBFF31 == pdu.eid) );
        fprintf(stderr, "byte[0]=0x%0X\n", curMsg[cCurMsg-1].DATA.bytes[0]);
        XCTAssertTrue( (curMsg[cCurMsg-1].DATA.bytes[0] == 2) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



