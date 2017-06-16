/*
 *	Generated 06/05/2017 08:35:58
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
#include    <j1939_defs.h>
#include    <trace.h>
#include    <j1939misc_internal.h>
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

    
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_j1939misc_01(
    const
    char        *pTestName
)
{
    J1939MISC_DATA *pObj = OBJ_NIL;
    int         i;
    J1939_MSG   msg;
   
    pObj = j1939misc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init(pObj); 
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        j1939misc_setFileOut(pObj, stdout);

        for (i=0; i<cMsgs01; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs01[i].pdu, Msgs01[i].len, Msgs01[i].data);
            j1939misc_DumpMessage(pObj, &msg);
        }
        fprintf(stderr, "\n\n\n");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_j1939misc_01A(
    const
    char        *pTestName
)
{
    J1939MISC_DATA *pObj = OBJ_NIL;
    int         i;
    J1939_MSG   msg;
   
    pObj = j1939misc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init(pObj); 
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        j1939misc_setFileOut(pObj, stdout);

        for (i=0; i<cMsgs01A; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs01A[i].pdu, Msgs01A[i].len, Msgs01A[i].data);
            j1939misc_DumpMessage(pObj, &msg);
        }
        fprintf(stderr, "\n\n\n");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_j1939misc_02(
    const
    char        *pTestName
)
{
    J1939MISC_DATA *pObj = OBJ_NIL;
    int         i;
    J1939_MSG   msg;
   
    pObj = j1939misc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init(pObj); 
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        j1939misc_setFileOut(pObj, stdout);

        for (i=0; i<cMsgs02; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs02[i].pdu, Msgs02[i].len, Msgs02[i].data);
            j1939misc_DumpMessage(pObj, &msg);
        }
        fprintf(stderr, "\n\n\n");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_j1939misc_03(
    const
    char        *pTestName
)
{
    J1939MISC_DATA *pObj = OBJ_NIL;
    int         i;
    J1939_MSG   msg;
   
    pObj = j1939misc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init(pObj); 
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        j1939misc_setFileOut(pObj, stdout);

        for (i=0; i<cMsgs03; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs03[i].pdu, Msgs03[i].len, Msgs03[i].data);
            j1939misc_DumpMessage(pObj, &msg);
        }
        fprintf(stderr, "\n\n\n");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_j1939misc_04(
    const
    char        *pTestName
)
{
    J1939MISC_DATA *pObj = OBJ_NIL;
    int         i;
    J1939_MSG   msg;
   
    pObj = j1939misc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939misc_Init(pObj); 
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        j1939misc_setFileOut(pObj, stdout);

        for (i=0; i<cMsgs04; ++i) {
            j1939msg_ConstructMsg_E1(&msg, Msgs04[i].pdu, Msgs04[i].len, Msgs04[i].data);
            j1939misc_DumpMessage(pObj, &msg);
            if (i > 100)
                break;
        }
        fprintf(stderr, "\n\n\n");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(test_j1939misc);
  TINYTEST_ADD_TEST(test_j1939misc_04,setUp,tearDown);
  //TINYTEST_ADD_TEST(test_j1939misc_03,setUp,tearDown);
  //TINYTEST_ADD_TEST(test_j1939misc_02,setUp,tearDown);
  //TINYTEST_ADD_TEST(test_j1939misc_01A,setUp,tearDown);
  //TINYTEST_ADD_TEST(test_j1939misc_01,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939misc);





