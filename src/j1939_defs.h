/****************************************************************
 *                Protocol Layer (j1939) Support  Header
 ****************************************************************/
/*
 * Program
 *				Protocol Layer (j1939) Support Subroutines
 * Purpose
 *				J1939 protocol lives on top of the CAN system. It
 *              consists of ECUs which may have one or more Con-
 *              troller Applications within it. Each Controller
 *              Application has a NAME and will claim an address.
 *
 *				J1939 supports messages of up to 1875 bytes. However,
 *              most messages are 8 bytes in length or less. Requests
 *              for a specific PGN are supported.
 *
 *              Each Controller Application must go through an
 *              address claim procedure before they have an address
 *              that they can use for talking to other CAs.
 *
 *              Bus loads: 8 bytes of data with stuff bits seems
 *                  to be about 155 bits. 250 Kbps gives about
 *                  620 us per msg. 10,000/620 = 16 msgs per 10 ms
 *                  or max of about 1600 msgs per sec
 *
 * Remarks
 *	1.			When we first start up, we set up our CAN Port to
 *              support our protocol.
 *  2.          The combined size of the control, header and data
 *              portions of the j1939 is limited to 64k.
 * History
 *	12/01/14	Adapted for cmnLib.
 *	09/26/14	Created.
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
 */


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




#include        <cmn_defs.h>
#include        <AStr.h>
#include        <j1939msg.h>



#ifndef J1939_DEFS_H
#define J1939_DEFS_H	1





//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************


#ifdef	__cplusplus
extern	"C" {
#endif
    

#ifndef DEBUG_BREAK
#   ifdef NDEBUG
#       define DEBUG_BREAK( )  /**/
#   else
#       define DEBUG_BREAK( )  __asm__ volatile ("sdbbp 0")
#   endif
#endif
    
    
#ifndef CHECK_FOR_VALID_DCR
#   ifdef NDEBUG
#       define CHECK_FOR_VALID_DCR(dcr) /**/
#   else
#       define CHECK_FOR_VALID_DCR(dcr) \
            if( !( ((uint32_t)dcr >= 0xBFC02FF0) && ((uint32_t)dcr <= 0xBFC02FFF) ) ) \
                DEBUG_BREAK()
#   endif
#endif
    
    
#ifndef CHECK_FOR_VALID_SFR
#   ifdef NDEBUG
#       define CHECK_FOR_VALID_SFR(sfr) /**/
#   else
#       define CHECK_FOR_VALID_SFR(sfr) \
            if( !( ((uint32_t)sfr >= 0xBF800000) && ((uint32_t)sfr <= 0xBF8FFFFF) ) ) \
            DEBUG_BREAK()
#   endif
#endif
    
    
#ifndef BREAK_NOT_BOUNDARY2
#   ifdef NDEBUG
#       define BREAK_NOT_BOUNDARY2(n) /**/
#   else
#       define BREAK_NOT_BOUNDARY2(n) \
            if( !(0 == (((uint32_t)n) & 0x1)) ) \
                DEBUG_BREAK();
#   endif
#endif
    
    
#ifndef BREAK_NOT_BOUNDARY4
#   ifdef NDEBUG
#       define BREAK_NOT_BOUNDARY4(n) /**/
#   else
#       define BREAK_NOT_BOUNDARY4(n) \
            if( !(0 == (((uint32_t)n) & 0x3)) ) \
                DEBUG_BREAK();
#   endif
#endif
    
    
#ifndef BREAK_NOT_BOUNDARY8
#   ifdef NDEBUG
#       define BREAK_NOT_BOUNDARY8(n) /**/
#   else
#       define BREAK_NOT_BOUNDARY8(n) \
            if( !(0 == (((uint32_t)n) & 0x7)) ) \
                DEBUG_BREAK();
#   endif
#endif
    
    
#ifndef BREAK_NULL
#   ifdef NDEBUG
#       define BREAK_NULL(n) /**/
#   else
#       define BREAK_NULL(n) \
            if( NULL == n ) \
                DEBUG_BREAK();
#   endif
#endif
    
    
#ifndef BREAK_ZERO
#   ifdef NDEBUG
#       define BREAK_ZERO(n) /**/
#   else
#       define BREAK_ZERO(n) \
            if( 0 == n ) \
                DEBUG_BREAK();
#   endif
#endif
    
    
#ifndef BREAK_NOT_ZERO
#   ifdef NDEBUG
#       define BREAK_NOT_ZERO(n) /**/
#   else
#       define BREAK_NOT_ZERO(n) \
            if( !(0 == n) ) \
                DEBUG_BREAK();
#   endif
#endif
    
    
#ifndef INTERRUPT_STATUS
#   ifdef  __APPLE__
#       define INTERRUPT_STATUS
#   else
#       define INTERRUPT_STATUS    uint32_t    cp0_12_status;
#   endif
#endif
    
#ifndef DISABLE_INTERRUPTS
#   ifdef  __APPLE__
#       define DISABLE_INTERRUPTS()
#   else
#       define DISABLE_INTERRUPTS()                                             \
            do {                                                                \
                asm volatile( "di %0" : "=r"(cp0_12_status) );                  \
                asm volatile( "ehb" );                                          \
            } while(0)
#   endif
#endif
    
#ifndef ENABLE_INTERRUPTS
#   ifdef  __APPLE__
#       define ENABLE_INTERRUPTS
#   else
    // ENABLE_INTERRUPTS enables interrupts unconditionally.
#       define ENABLE_INTERRUPTS                                                \
            do {                                                                \
                cp0_12_status |= 1;                                             \
                asm volatile("mtc0  %0, $12, 0" : : "r" (cp0_12_status));       \
            } while(0)
#   endif
#endif
    
#ifndef RESTORE_INTERRUPTS
#   ifdef  __APPLE__
#       define RESTORE_INTERRUPTS
#   else
    // RESTORE_INTERRUPTS re-enables interrupts only if they were enabled
    // at the time that DISABLE_INTERRUPTS was performed. Otherwise, it is
    // effectively a nop.
#       define RESTORE_INTERRUPTS                                           \
            do {                                                            \
                asm volatile("mtc0  %0, $12, 0" : : "r" (cp0_12_status));   \
            } while(0)
#   endif
#endif


#define J1939_MAX_CA        4       // Maximum Number of Controller Applications
#define J1939_MAX_CAN_PORTS 2       // Maximum Number of CAN Ports
    
    
#if J1939_MAX_CAN_PORTS >= 3
    #warning "Currently, we only support 2 CAN Ports, see J1939.c to increase"
#endif
    
    
    
    
    //---------------------------------------------------------------
    //                *** System Virtual Object Methods ***
    //---------------------------------------------------------------
    
    // This vtbl must be supplied to the j1939 object prior to execution
    // of anything in the j1939 system that requires interfacing to the
    // system routines.
    
    typedef struct j1939_sys_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;                  // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lru_object.c.
        // Properties:
        // Methods:
        uint32_t        (*pGetTimeMS)(OBJ_ID);          // Return the system time
        //                                              // in milliseconds.
        uint32_t        (*pSleepMS)(OBJ_ID, uint32_t);  // Sleep for N ms and return
        //                                              // amount of time slept (ms)
    } J1939_SYS_VTBL;
    
    
    
    
    //---------------------------------------------------------------
    //                *** CAN Virtual Object Methods ***
    //---------------------------------------------------------------

    // This vtbl must be supplied to the j1939 object prior to execution
    // of anything in the j1939 system that requires interfacing to the
    // CAN Routines.
    
    typedef struct j1939_can_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;                  // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lru_object.c.
        // Properties:
        // Methods:
        P_XMTMSG_RTN    pXmt;
    } J1939_CAN_VTBL;
    

    
    
    //---------------------------------------------------------------
    //                *** J1939 OBJECT CONSTANTS ***
    //---------------------------------------------------------------
    
    typedef enum obj_j1939_idents_e {
        OBJ_IDENT_J1939_BASE=OBJ_IDENT_J1939_ENTRIES,
        OBJ_IDENT_J1939CA,              // J1939 Control Application Base CA
        OBJ_IDENT_J1939CA_CLASS,
        OBJ_IDENT_J1939CAM,
        OBJ_IDENT_J1939CAM_CLASS,
        OBJ_IDENT_J1939CAN,             // CAN Test Module
        OBJ_IDENT_J1939CAN_CLASS,
        OBJ_IDENT_J1939CU,              // J1939 Control Unit Base CU
        OBJ_IDENT_J1939CU_CLASS,
        OBJ_IDENT_J1939DG,              // J1939 Diagnostic/Test CA
        OBJ_IDENT_J1939DG_CLASS,
        OBJ_IDENT_J1939DL,              // J1939 Data Link Layer
        OBJ_IDENT_J1939DL_CLASS,
        OBJ_IDENT_J1939ECU,             // J1939 Engine Control Unit ECU
        OBJ_IDENT_J1939ECU_CLASS,
        OBJ_IDENT_J1939EN,              // J1939 Engine #1 CA
        OBJ_IDENT_J1939EN_CLASS,
        OBJ_IDENT_J1939ER,              // J1939 Engine Retarder CA
        OBJ_IDENT_J1939ER_CLASS,
        OBJ_IDENT_J1939MSG,
        OBJ_IDENT_J1939MSG_CLASS,
        OBJ_IDENT_J1939RQ,
        OBJ_IDENT_J1939RQ_CLASS,
        OBJ_IDENT_J1939SS,              // J1939 Shift Selector CA
        OBJ_IDENT_J1939SS_CLASS,
        OBJ_IDENT_J1939SYS,             // SYS Test Module
        OBJ_IDENT_J1939SYS_CLASS,
        OBJ_IDENT_J1939TBL,             // J1939 SPN & PGN Tables
        OBJ_IDENT_J1939TBL_CLASS,
        OBJ_IDENT_J1939TC,              // J1939 Transmission #1 CA
        OBJ_IDENT_J1939TC_CLASS,
        OBJ_IDENT_J1939TCU,             // J1939 Transmission Control Unit TCU
        OBJ_IDENT_J1939TCU_CLASS,
    } OBJ_J1939_IDENTS;

    
        // J1939 Object Types
    typedef struct j1939ca_data_s	J1939CA_DATA;   // Base CA Class
    typedef struct j1939cam_data_s	J1939CAM_DATA;  // CA Manager (ECU)
    typedef struct j1939dg_data_s	J1939DG_DATA;   // Diagnostic CA
                                                    // (inherits from J1939CA_DATA)
    typedef struct j1939en_data_s	J1939EN_DATA;   // Engine #1 CA
                                                    // (inherits from J1939CA_DATA)
    typedef struct j1939er_data_s	J1939ER_DATA;   // Engine Retarder #41 CA
                                                    // (inherits from J1939CA_DATA)
    typedef struct j1939tc_data_s	J1939TC_DATA;   // Transmission #1 CA
                                                    // (inherits from J1939CA_DATA)
    

    typedef struct j1939_data_s		J1939_DATA;
    
    typedef bool (*P_J1939_XMTRTN)(
                        OBJ_PTR,
                        uint32_t,       // msDelay 
                        J1939_PDU,
                        uint16_t,       // Data Length (1..1785)
                        void *          // Data Ptr
                 );
    
    typedef bool (*P_HANDLE_TIMED_TRANSMITS)(OBJ_PTR);
    
        
    

    typedef enum j1939_names_e {
        J1939_ENGINE_1=0,
        J1939_TRANSMISSION_1=3,
        J1939_SHIFT_CONSOLE_PRIMARY=5,
        J1939_POWER_TAKEOFF_1=6,
        J1939_BRAKE_SYSTEM_CONTROLLER=11,
        J1939_ENGINE_RETARDER_COMPRESSION_1=41,
        J1939_CRUISE_CONTROL=17,
        J1939_INSTRUMENT_CLUSTER_1=23,
        J1939_POWER_TAKEOFF_2=27,
        J1939_BODY_CONTROLLER=33,
        J1939_MANAGEMENT_COMPUTER=39,
        J1939_ENGINE_RETARDER_EXHAUST_1=41,
        J1939_CAB_CONTROLLER_PRIMARY=49,
   } J1939_NAMES;
    

    // SPN Table
#pragma pack(push, 1)
    // actual_value(int32_t) = (((spn_value * mult) + round) / div) + offset;
    
    typedef struct j1939_spn_type_s {
        uint16_t        type;           // See J1939_SPN_TYPE
        uint8_t         len;            // Length in bits
        uint8_t         dec;            // Number of Decimal points
        int16_t         mult;           // multiplier
        int16_t         div;            // divisor
        int32_t         offset;         // SPN Calculation Offset
        int32_t         round;          // SPN Rounding Amount
        int32_t         minOp;          // Minimum Operating Range
        int32_t         maxOp;          // Maximum Operating Range
        int32_t         minData;        // Minimum Data Range
        int32_t         maxData;        // Maximum Data Range
        const
        char            *pDesc;
    } J1939_SPN_TYPE;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
    typedef struct j1939_spn_s {
        uint16_t        spn;            // SPN Identifier
        uint16_t        reservered16;
        const
        J1939_SPN_TYPE  *pType;
        const
        char            *pDesc;
    } J1939_SPN;
#pragma pack(pop)
    
    
    // PGN SPN Table
#pragma pack(push, 1)
    typedef struct j1939_pgnspn_s {
        uint16_t        pgn;            // PGN Identifier
        uint16_t        spn;            // SPN Identifier
        uint8_t         cBits;          // SPN Size in Bits
        uint8_t         bitOffset;
        int8_t          dataOffset;     // Offset in Data
        uint8_t         reserved8;
        const
        J1939_SPN       *pSpn;
    } J1939_PGNSPN;
#pragma pack(pop)
    
    
    // PGN Table Entry
#pragma pack(push, 1)
    typedef struct j1939_pgn_entry_s {
        uint32_t        pgn;            // PGN Identifier
        uint16_t        msFreq;         // Frequency (ms) (0 == As Required)
        uint16_t        dlc;            // dlc (0 == variable)
        uint8_t         priority;       // Priority (0-7) (0 == highest)
        uint8_t         cSpns;          // Number of SPNs
        uint16_t        reserved16;
        const
        J1939_PGNSPN    *pSpns;
        const
        char            *pDesc;
    } J1939_PGN_ENTRY;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
    typedef struct j1939_pgn_table_s {
        const
        uint16_t            cPGNs;
        const
        uint16_t            reserved16;
        const
        J1939_PGN_ENTRY     *(*pPGNs)[];// PGN Index Ptr - It is assumed that the PGNs
        //                  are sorted by ascending PGN
        //                  and that the index is NULL
        //                  terminated.
    } J1939_PGN_TABLE;
#pragma pack(pop)
    
    
    
#ifdef	__cplusplus
};
#endif


#include        <j1939tbl.h>


#endif      // J1939_DEFS_H
