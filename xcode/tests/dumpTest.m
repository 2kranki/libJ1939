/*
 *	Generated by Vogel 05/20/2015 11:48:08
 */


/*
 * COPYRIGHT  - (C) Copyright 2015  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
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


#include    <j1939_defs.h>
#include    <j1939misc_internal.h>
#include    <j1939Can.h>
#include    <j1939Sys.h>
#include	"common.h"



@interface dumpTests : XCTestCase

@end

@implementation dumpTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
}


- (void)tearDown
{
    mem_Dump( );

    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
    
}



- (void)test01
{
    J1939MISC_DATA	*pObj = OBJ_NIL;
    J1939_MSG       msg;
    uint32_t        i;
   
    pObj = j1939misc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<cMsgs01; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs01[i].pdu, Msgs01[i].len, Msgs01[i].data);
            //msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            j1939misc_DumpMessage(pObj, &msg);
            if (i > 250) {
                break;
            }
        }
        fprintf(stderr, "\n\n\n");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)test02
{
    J1939MISC_DATA	*pObj = OBJ_NIL;
    J1939_MSG       msg;
    uint32_t        i;
    
    pObj = j1939misc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<cMsgs03; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs02[i].pdu, Msgs02[i].len, Msgs02[i].data);
            //msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            j1939misc_DumpMessage(pObj, &msg);
            if (i > 250) {
                break;
            }
        }
        fprintf(stderr, "\n\n\n");
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)test03
{
    J1939MISC_DATA	*pObj = OBJ_NIL;
    J1939_MSG       msg;
    uint32_t        i;
    
    pObj = j1939misc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<cMsgs03; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs03[i].pdu, Msgs03[i].len, Msgs03[i].data);
            //msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            j1939misc_DumpMessage(pObj, &msg);
            if (i > 250) {
                break;
            }
        }
        fprintf(stderr, "\n\n\n");
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)test04
{
    J1939MISC_DATA	*pObj = OBJ_NIL;
    J1939_MSG       msg;
    uint32_t        i;
    
    pObj = j1939misc_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<cMsgs04; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs04[i].pdu, Msgs04[i].len, Msgs04[i].data);
            //msg.CMSGSID.CMSGTS = 0xFFFF;    // Denote transmitting;
            j1939misc_DumpMessage(pObj, &msg);
            if (i > 250) {
                break;
            }
        }
        fprintf(stderr, "\n\n\n");
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



