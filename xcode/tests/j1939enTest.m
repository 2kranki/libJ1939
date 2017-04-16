
/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
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
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name,
//                                  failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name,
//                                  failure_description, ...)


#include    "j1939en_internal.h"



#include	"common.h"
#include    "j1939Can.h"
#include    "j1939Sys.h"




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




@interface j1939enTests : XCTestCase

@end

@implementation j1939enTests


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

    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
    
}



- (void)testOpenClose_1_0
{
    J1939EN_DATA    *pEng = NULL;
    //J1939_PDU       pdu;
    bool            fRc;

    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    pEng = j1939en_Alloc();
    XCTAssertFalse( (NULL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (NULL == pEng) );
    if (pEng) {

        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );

        obj_Release(pEng);
        pEng = NULL;
    }

}



- (void)testTimedMessages
{
    J1939EN_DATA    *pEng = NULL;
    J1939_PDU       pdu;
    bool            fRc;
        
    XCTAssertFalse( (OBJ_NIL == pCAN) );
    XCTAssertFalse( (OBJ_NIL == pSYS) );
    pEng = j1939en_Alloc();
    XCTAssertFalse( (NULL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (NULL == pEng) );
    if (pEng) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );

        // We need to go long enough (1200ms) to get all timed messages to pop.
        // PGN 61443 - F003 - every 50ms        24ea
        // PGN 61444 - F004 - every 100ms       13ea
        // PGN 65265 - FEF1 - every 100ms       13ea
        // PGN 65247 - FEDF - every 250ms        5ea
        // PGN 65129 - FE69 - every 1000ms       1ea
        // PGN 65262 - FEEE - every 1000ms       1ea
        for (int i=0; i<120; ++i) {
            j1939Sys_BumpMS(pSYS, 10);
            fRc =   (*j1939ca_getHandler((J1939CA_DATA *)pEng))(
                                            (J1939CA_DATA *)pEng,
                                            0,
                                            NULL
                    );
        }
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME:  Message Count is too hard to track for the moment.
        //XCTAssertTrue( (57 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        //XCTAssertTrue( (0x0CF00300 == pdu.eid) );
        
        obj_Release(pEng);
        pEng = NULL;
    }
    
}



- (void)testCheck_TSC1_Direct_Clean
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
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
        pdu.P = 3;
        pdu.PF = 0;                 // TSC1 PF
        pdu.PS = 0;
        for (int i=0; i<8; ++i) {
            data[i] = 0xFF;
        }
        data[0] = 1;                // Engine
        //data[1] = 240;
        //data[2] = 0x00;
        j1939msg_ConstructMsg_E1(&msg, pdu.eid, 8, data);
        msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, pdu.eid, &msg );
        XCTAssertTrue( (true == pEng->fActive) );
        XCTAssertTrue( (3 == pEng->spn1480) );
        
        for (int i=0; i<50; ++i) {
            j1939Sys_BumpMS(pSYS, 10);
            fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, 0, NULL);
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
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, pdu.eid, &msg);
        XCTAssertTrue( (false == pEng->fActive) );
        XCTAssertTrue( (255 == pEng->spn1480) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (24 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        //XCTAssertTrue( (0x0CF00300 == pdu.eid) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        //XCTAssertTrue( (0x0C000003 == pdu.eid) );
        
        obj_Release(pEng);
        pEng = OBJ_NIL;
    }
    
}



- (void)testCheck_TSC1_Direct_Timeout
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
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Setup up msg from #3 Transmission to TSC1;
        pdu.eid = 0;
        pdu.SA = 3;
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
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, pdu.eid, &msg );
        XCTAssertTrue( (true == pEng->fActive) );
        XCTAssertTrue( (3 == pEng->spn1480) );
        
        for (int i=0; i<200; ++i) {
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, 0, NULL );
        }
        
#ifdef XYZZY
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
        fRc = xmtHandler(NULL, 0, &msg);
        fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, pdu.eid, &msg );
#endif
        XCTAssertTrue( (false == pEng->fActive) );
        XCTAssertTrue( (255 == pEng->spn1480) );
        
        
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        //FIXME: Message Count is too hard to track for the moment.
        //XCTAssertTrue( (11 == cCurMsg) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-2]);
        fprintf(stderr, "msg[-2] pdu.eid = 0x%8X\n", pdu.eid);
        //FIXME: XCTAssertTrue( (0x18FEDF00 == pdu.eid) );
        pdu = j1939msg_getJ1939_PDU(&curMsg[cCurMsg-1]);
        fprintf(stderr, "msg[-1] pdu.eid = 0x%8X\n", pdu.eid);
        XCTAssertTrue( (0x0CF00300 == pdu.eid) );
        
        obj_Release(pEng);
        pEng = OBJ_NIL;
    }
    
}



- (void)testCheck_MSG02_Clean
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
    pEng = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (OBJ_NIL == pEng) );
    cCurMsg = 0;
    if (pEng) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        fRc = j1939en_setShiftExit(pEng, shiftExit, NULL);
        XCTAssertTrue( (fRc) );
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        XCTAssertTrue( (false == pEng->fActive) ); // Should not be retarded
        
        // Send all msg02 msgs.
        for (i=0; i<cMsgs02; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs02[i].pdu, Msgs02[i].len, Msgs02[i].data);
            msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            printCanMsg(&msg);
            fRc = xmtHandler(NULL, 0, &msg);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, Msgs02[i].pdu, &msg );
            //FIXME: why did we think that this is constantly retarded ???
            //FIXME: XCTAssertTrue( (true == pEng->fActive) );
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
    
}



- (void)testCheck_MSG03_Clean
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
    pEng = j1939en_Alloc();
    XCTAssertFalse( (OBJ_NIL == pEng) );
    pEng = j1939en_Init( pEng, (OBJ_ID)pCAN, (OBJ_ID)pSYS, 1, 8192, 4 );
    XCTAssertFalse( (OBJ_NIL == pEng) );
    cCurMsg = 0;
    if (pEng) {
        
        j1939Sys_TimeReset(pSYS, 0);
        j1939can_setXmtMsg(pCAN, xmtHandler, NULL);
        
        fRc = j1939en_setShiftExit(pEng, shiftExit, NULL);
        XCTAssertTrue( (fRc) );
        
        // Initiate Address Claim, but not necessary.
        fRc = j1939ca_HandleMessages((J1939CA_DATA *)pEng, 0, NULL);
        XCTAssertTrue( (J1939CA_STATE_NORMAL_OPERATION == pEng->super.cs) );
        fprintf( stderr, "cCurMsg = %d\n", cCurMsg );
        XCTAssertTrue( (0 == cCurMsg) );
        
        // Send all msg03 msgs.
        for (i=0; i<cMsgs03; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs03[i].pdu, Msgs03[i].len, Msgs03[i].data);
            msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            printCanMsg(&msg);
            fRc = xmtHandler(NULL, 0, &msg);
            fRc = j1939ca_HandleMessages( (J1939CA_DATA *)pEng, Msgs03[i].pdu, &msg );
            //FIXME: why did we think that this is constantly retarded ???
            //FIXME: XCTAssertTrue( (true == pEng->fActive) );
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
    
}



@end



