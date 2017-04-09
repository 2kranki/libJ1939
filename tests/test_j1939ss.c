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
#include    <cmn_defs.h>
#include    <j1939ss_internal.h>





int         test_j1939ss_OpenClose(
    const
    char        *test_name
)
{
    J1939SS_DATA	*pObj = OBJ_NIL;
   
    pObj = j1939ss_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = j1939ss_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}




TINYTEST_START_SUITE(test_j1939ss);
  TINYTEST_ADD_TEST(test_j1939ss_OpenClose);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_j1939ss);





