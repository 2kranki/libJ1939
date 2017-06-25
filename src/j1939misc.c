// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939misc.c
 *	Generated 06/15/2017 11:49:27
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include <j1939misc_internal.h>
#include <dec.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    // size: resolution: 0.4 % per bit, offset 0, range: 0 - 100 %
    static
    bool            printPCT03(
        J1939MISC_DATA  *this,
        const
        char            *pDesc,
        uint8_t         num
    )
    {
        char            numstr[32] = {0};
        uint32_t        cNum = 32;
        char            *pStr = numstr;
        int64_t         total;
        bool            fRc;
        
        total = (int64_t)num * 4;
        fRc =   dec_putInt64DecA(
                                 total,          // Input Number
                                 -1,             // Sign: -1 == leading, 0 == none, 1 == trailing
                                 true,           // Align: false == left, true == right
                                 false,          // Fill: false == space fill, true == zero fill
                                 6,              // Field Width
                                 1,              // Decimal Point Position
                                 &cNum,          // Buffer Length
                                 &pStr                       // Buffer Ptr
                                 );
        pStr = numstr;
        fprintf(this->pFileOut, "%s = %s %%\n", pDesc, pStr);
        
        
        return true;
    }
    
    
    
    // resolution: 1 % per bit, offset: -125, range: -125 - 125 %
    static
    bool            printPCT05(
        J1939MISC_DATA  *this,
        const
        char            *pDesc,
        uint16_t         num
    )
    {
        char            numstr[32] = {0};
        uint32_t        cNum = 32;
        char            *pStr = numstr;
        int64_t         total;
        bool            fRc;
        
        total = (((int16_t)num) - 125);
        fRc =   dec_putInt64DecA(
                                 total,          // Input Number
                                 -1,             // Sign: -1 == leading, 0 == none, 1 == trailing
                                 true,           // Align: false == left, true == right
                                 false,          // Fill: false == space fill, true == zero fill
                                 4,              // Field Width
                                 0,              // Decimal Point Position
                                 &cNum,          // Buffer Length
                                 &pStr                       // Buffer Ptr
                                 );
        pStr = numstr;
        fprintf(this->pFileOut, "%s = %s %%\n", pDesc, pStr);
        
        
        return true;
    }
    
    
    
    // resolution: 0.125 rpm per bit, offset 0, range: 0 to 8,031.875 rpm
    static
    bool            printRPM01(
        J1939MISC_DATA  *this,
        const
        char            *pDesc,
        uint16_t         num
    )
    {
        char            numstr[32] = {0};
        uint32_t        cNum = 32;
        char            *pStr = numstr;
        int64_t         total;
        bool            fRc;
        
        total = num * 125;
        fRc =   dec_putInt64DecA(
                        total,          // Input Number
                        0,              // Sign: -1 == leading, 0 == none, 1 == trailing
                        true,           // Align: false == left, true == right
                        false,          // Fill: false == space fill, true == zero fill
                        10,             // Field Width
                        3,                          // Decimal Point Position
                        &cNum,                      // Buffer Length
                        &pStr                       // Buffer Ptr
                );
        pStr = numstr;
        fprintf(this->pFileOut, "%s = %s rpm\n", pDesc, pStr);

        
        return true;
    }

    
    
    // resolution: 1/256 km/h per bit, offset 0, range: 0 to 250.996 km/h
    static
    bool            printSpeed02(
        J1939MISC_DATA  *this,
        const
        char            *pDesc,
        uint16_t         num
    )
    {
        char            numstr[32] = {0};
        uint32_t        cNum = 32;
        char            *pStr = numstr;
        int64_t         total;
        bool            fRc;
        
        total = (((int16_t)num) * 1000) >> 8;
        fRc =   dec_putInt64DecA(
                                 total,          // Input Number
                                 -1,             // Sign: -1 == leading, 0 == none, 1 == trailing
                                 true,           // Align: false == left, true == right
                                 false,          // Fill: false == space fill, true == zero fill
                                 9,              // Field Width
                                 3,              // Decimal Point Position
                                 &cNum,          // Buffer Length
                                 &pStr                       // Buffer Ptr
                                 );
        pStr = numstr;
        fprintf(this->pFileOut, "%s = %s km/h\n", pDesc, pStr);
        
        
        return true;
    }
    
    
    
    // size: 8 bits, resolution: 1/16 km/h per bit, offset -7.8125
    // range: -7.8125 - 7.8125 km/h
    static
    bool            printSpeed04(
        J1939MISC_DATA  *this,
        const
        char            *pDesc,
        uint8_t         num
    )
    {
        char            numstr[32] = {0};
        uint32_t        cNum = 32;
        char            *pStr = numstr;
        int64_t         total;
        bool            fRc;
        
        total = ((((int16_t)num) * 10000) >> 4) - 78125;
        fRc =   dec_putInt64DecA(
                                 total,          // Input Number
                                 -1,             // Sign: -1 == leading, 0 == none, 1 == trailing
                                 true,           // Align: false == left, true == right
                                 false,          // Fill: false == space fill, true == zero fill
                                 8,              // Field Width
                                 4,              // Decimal Point Position
                                 &cNum,          // Buffer Length
                                 &pStr                       // Buffer Ptr
                                 );
        pStr = numstr;
        fprintf(this->pFileOut, "%s = %s km/h\n", pDesc, pStr);
        
        
        return true;
    }
    
    
    
    static
    bool            print1of4(
                              J1939MISC_DATA  *this,
                              int             num,
                              const
                              char            *pDesc,
                              const
                              char            *pDesc0,
                              const
                              char            *pDesc1,
                              const
                              char            *pDesc2,
                              const
                              char            *pDesc3
                              )
    {
        
        if (this->pFileOut) {
            switch (num) {
                case 0:
                    fprintf(this->pFileOut, "\t%s - %s\n", pDesc, pDesc0);
                    break;
                    
                case 1:
                    fprintf(this->pFileOut, "\t%s - %s\n", pDesc, pDesc1);
                    break;
                    
                case 2:
                    fprintf(this->pFileOut, "\t%s - %s\n", pDesc, pDesc2);
                    break;
                    
                case 3:
                    if (pDesc3) {
                        fprintf(this->pFileOut, "\t%s - %s\n", pDesc, pDesc3);
                    }
                    break;
                    
            }
        }
        
        return true;
    }
    
    
    
    static
    bool            printMsg(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        char            data[64];
        const
        J1939_PREFERRED_ADDRESS
        *pEntryDA;
        const
        J1939_PREFERRED_ADDRESS
        *pEntrySA;
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939msg_getPGN(pMsg);
        pEntryDA = j1939data_Find_Adr(j1939pdu_getDA(pdu));
        pEntrySA = j1939data_Find_Adr(j1939pdu_getSA(pdu));

        if (this->pFileOut) {
            data[0] = 0;
            j1939msg_CreatePrintable(pMsg, data);
            fprintf(
                    this->pFileOut,
                    "\ntime: %5d  pgn: %08X  msg: %s",
                    pMsg->CMSGSID.CMSGTS,
                    j1939msg_getPGN(pMsg).w,
                    data
                    );
            if (pEntrySA) {
                fprintf(
                        this->pFileOut,
                        "\t%s -> ",
                        pEntrySA->pDescription
                        );
            }
            else {
                fprintf(this->pFileOut, "\t***???*** -> ");
            }
            if (pEntryDA) {
                fprintf(
                        this->pFileOut,
                        "%s\n",
                        pEntryDA->pDescription
                        );
            }
            else {
                fprintf(this->pFileOut, "***???***\n");
            }
        }
        
        return true;
    }
    
    
    
    static
    bool            printMsgDesc(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        char            data[64];
        const
        J1939_PREFERRED_ADDRESS
                        *pEntryDA;
        const
        J1939_PREFERRED_ADDRESS
                        *pEntrySA;
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939msg_getPGN(pMsg);
        pEntryDA = j1939data_Find_Adr(j1939pdu_getDA(pdu));
        pEntrySA = j1939data_Find_Adr(j1939pdu_getSA(pdu));
        if (this->pFileOut) {
            data[0] = 0;
            j1939msg_CreatePrintable(pMsg, data);
            fprintf(
                    this->pFileOut,
                    "\ntime: %5d  pgn: %08X  msg: %s",
                    pMsg->CMSGSID.CMSGTS,
                    j1939msg_getPGN(pMsg).w,
                    data
                    );
            fprintf(
                    this->pFileOut,
                    "\t%d - %s\n",
                    pgn.pgn,
                    pEntry->pDesc
                    );
            if (pEntrySA) {
                fprintf(
                        this->pFileOut,
                        "\t%s -> ",
                        pEntrySA->pDescription
                );
            }
            else {
                fprintf(this->pFileOut, "\t***???*** -> ");
            }
            if (pEntryDA) {
                fprintf(
                        this->pFileOut,
                        "%s\n",
                        pEntryDA->pDescription
                        );
            }
            else {
                fprintf(this->pFileOut, "***???***\n");
            }
        }
        
        return true;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939MISC_DATA *     j1939misc_Alloc(
    )
    {
        J1939MISC_DATA  *this;
        uint32_t        cbSize = sizeof(J1939MISC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939MISC_DATA *     j1939misc_New(
    )
    {
        J1939MISC_DATA       *this;
        
        this = j1939misc_Alloc( );
        if (this) {
            this = j1939misc_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            j1939misc_setFileOut(
        J1939MISC_DATA  *this,
        FILE            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pFileOut = pValue;
        
        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         j1939misc_getLastError(
        J1939MISC_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939misc_setLastError(
        J1939MISC_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        j1939misc_getPriority(
        J1939MISC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939misc_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            j1939misc_setPriority(
        J1939MISC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        j1939misc_getSize(
        J1939MISC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    ASTR_DATA * j1939misc_getStr(
        J1939MISC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        j1939misc_setStr(
        J1939MISC_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = j1939misc__Assign(this,pOther);
     @endcode:
     @param:    this    J1939MISC object pointer
     @param:    pOther  a pointer to another J1939MISC object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         j1939misc_Assign(
        J1939MISC_DATA		*this,
        J1939MISC_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !j1939misc_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        j1939misc_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939misc_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939misc_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        j1939misc      *pCopy = j1939misc_Copy(this);
     @endcode:
     @param:    this    J1939MISC object pointer
     @return:   If successful, a J1939MISC object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the J1939MISC object.
     */
    J1939MISC_DATA *     j1939misc_Copy(
        J1939MISC_DATA       *this
    )
    {
        J1939MISC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = j1939misc_New( );
        if (pOther) {
            eRc = j1939misc_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939misc_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939MISC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939MISC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        j1939misc_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939misc_Disable(
        J1939MISC_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939misc_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return j1939misc_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return j1939misc_getLastError(this);
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 0    0x000000
    //---------------------------------------------------------------
    
    /*
     * Start Retarding:
     *      When TSC1 is received with (spn695 == (1 or 3 for Engine) or
     *      (2 or 3 for Engine Retarder)).
     * Stop Retarding:
     *      When TSC1 is received with (spn695 == 0) or two update
     *      periods have expired since last TSC1. An update period
     *      for the Engine is 10ms, but 50ms for the Engine Retarder.
     */
    
    bool            j1939misc_DumpPgn0(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn518;         // Requested Torque / Torque Limit
        uint8_t         spn695;         // Override Control Mode
        // 0 - Disable override by the source of msg
        // 1 - Override speed
        // 2 - Override torque
        // 3 - Limit Speed/Torque
        uint8_t         spn696;         // Requested Speed Control Conditions
        uint8_t         spn897;         // Override Control Mode Priority
        // 0 == Highest Priority
        // 3 == Lowest Priority
        uint16_t        spn898;         // Requested Speed / Speed Limit
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        spn695 = pMsg->DATA.bytes[0] & 0x3;
        spn696 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        spn897 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        spn898 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        spn518 = pMsg->DATA.bytes[3];
        
        print1of4(this,
                  spn695,
                  "spn695 Override Control Mode",
                  "Disable override by the source of msg",
                  "Override speed",
                  "Override torque",
                  "Limit Speed/Torque"
                  );
        print1of4(this,
                  spn696,
                  "spn696 Engine Requested Speed Control Conditions",
                  "Transient Optimized for driveline disengaged and non-lockup conditions",
                  "Stability Optimized for driveline disengaged and non-lockup conditions",
                  "Stability Optimized for driveline engaged and/or in lockup condition 1 (e.g., vehicle driveline)",
                  "Stability Optimized for driveline engaged and/or in lockup condition 2 (e.g., PTO driveline)"
                  );
        print1of4(this,
                  spn897,
                  "spn897 Override Control Mode Priority",
                  "Highest priority",
                  "High priority",
                  "Medium priority",
                  "Low priority"
                  );
        if (spn898 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn898 Requested Speed / Speed Limit = %d\n", spn898);
        }
        if (spn518 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn518 Requested Torque / Torque Limit = %d\n", spn518);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //          PGN 57344  0x00E000 - Cab Message 1 - CM1
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn57344(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn986;
        uint16_t        spn1691;
        uint8_t         spn1684;
        uint8_t         spn1682;
        uint8_t         spn1714;
        uint8_t         spn1856;
        uint8_t         spn1655;
        uint8_t         spn1654;
        uint8_t         spn1653;
        uint8_t         spn1666;
        uint8_t         spn1656;
        uint8_t         spn1683;
        uint8_t         spn1685;
        uint8_t         spn1686;
        uint8_t         spn2596;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 986  1       8bits       Requested Percent Fan Speed
        spn986 = pMsg->DATA.bytes[0];
        // SPN 1691 2-3     16bits      Cab Interior Temperature Command
        spn1691 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        // SPN 1684 4.1     2bits       Auxiliary Heater Coolant Pump Request
        spn1684 = pMsg->DATA.bytes[3] & 0x3;
        // SPN 1682 4.3     2bits       Battery Main Switch Hold Request
        spn1682 = (pMsg->DATA.bytes[3] >> 2) & 0x3;
        // SPN 1717 4.5     2bits       Operator Seat Direction Switch
        spn1714 = (pMsg->DATA.bytes[3] >> 4) & 0x3;
        // SPN 1856 4.7     2bits       Seat Belt Switch
        spn1856 = (pMsg->DATA.bytes[3] >> 6) & 0x3;
        // SPN 1655 5.3     2bits       Vehicle Limiting Speed Governor Decrement Switch
        spn1655 = (pMsg->DATA.bytes[4] >> 2) & 0x3;
        // SPN 1654 5.5     2bits       Vehicle Limiting Speed Governor Increment Switch
        spn1654 = (pMsg->DATA.bytes[4] >> 4) & 0x3;
        // SPN 1653 5.7     2bits       Vehicle Limiting Speed Governor Enable Switch
        spn1653 = (pMsg->DATA.bytes[4] >> 6) & 0x3;
        // SPN 1666 6.5     2bits       Automatic Gear Shifting Enable Switch
        spn1666 = (pMsg->DATA.bytes[5] >> 4) & 0x3;
        // SPN 1656 6.7     2bits       Engine Automatic Start Enable Switch
        spn1656 = (pMsg->DATA.bytes[5] >> 6) & 0x3;
        // SPN 1683 7.1     4bits       Auxiliary Heater Mode Request
        spn1683 = pMsg->DATA.bytes[6] & 0x0F;
        // SPN 1685 7.5     2bits       Request Engine Zone Heating
        spn1685 = (pMsg->DATA.bytes[6] >> 4) & 0x3;
        // SPN 1686 7.7     2bits       Request Cab Zone Heating
        spn1686 = (pMsg->DATA.bytes[6] >> 6) & 0x3;
        // SPN 2596 8       8bits       Selected Maximum Vehicle Speed Limit
        spn2596 = pMsg->DATA.bytes[7];
        
        if (spn986 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn986 Requested Percent Fan Speed = %d\n", spn986);
        }
        if (spn1691 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1691 Cab Interior Temperature Command = %d\n", spn1691);
        }
        print1of4(this,
                  spn1684,
                  "spn1684 Auxiliary Heater Coolant Pump Request",
                  "Deactivate water pump",
                  "Activate water pump",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1682,
                  "spn1682 Battery Main Switch Hold Request",
                  "Release Battery Main Switch",
                  "Hold Battery Main Switch",
                  "undefined",
                  NULL
                  );
        print1of4(this,
                  spn1714,
                  "spn1714 Operator Seat Direction Switch",
                  "Operator seat not facing forward",
                  "Operator seat is facing forward",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1856,
                  "spn1856 Seat Belt Switch",
                  "NOT Buckled",
                  "OK - Seat Belt is buckled",
                  "Error - Switch state cannot be determined",
                  NULL
                  );
        print1of4(this,
                  spn1655,
                  "spn1655 Vehicle Limiting Speed Governor Decrement Switch",
                  "Switch in the off state",
                  "Switch in the on state - decrease",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1654,
                  "spn1654 Vehicle Limiting Speed Governor Increment Switch",
                  "Switch in the off state",
                  "Switch in the on state - increase",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1653,
                  "spn1653 Vehicle Limiting Speed Governor Enable Switch",
                  "Switch disabled",
                  "Switched enabled",
                  "Error",
                  NULL
                  );
        fprintf(this->pFileOut, "\tspn1666 Automatic Gear Shifting Enable Switch = %d\n", spn1666);
        print1of4(this,
                  spn1656,
                  "spn1656 Engine Automatic Start Enable Switch",
                  "Switch in the off state",
                  "Switch in the on state",
                  "Error",
                  NULL
                  );
        switch (spn1683) {
            case 0:
                fprintf(this->pFileOut, "\tspn1683 Auxiliary Heater Mode Request - De-activate auxiliary heater\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tspn1683 Auxiliary Heater Mode Request - Off due to ADR per European Regulations for Transport of hazardous materials\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tspn1683 Auxiliary Heater Mode Request - Economy mode\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tspn1683 Auxiliary Heater Mode Request - Normal mode\n");
                break;
            case 14:
                fprintf(this->pFileOut, "\tspn1683 Auxiliary Heater Mode Request - Reserved\n");
                break;
        }
        print1of4(this,
                  spn1685,
                  "spn1685 Request Engine Zone Heating",
                  "Do not heat engine zone",
                  "Heat engine zone",
                  "Reserved",
                  NULL
                  );
        if (spn2596 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn2596 Selected Maximum Vehicle Speed Limit = %d\n", spn2596);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 0 1 6 0
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn60160(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn2572;        // Sequence Number
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        spn2572 = pMsg->DATA.bytes[0];
        
        if (spn2572 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn2572 Sequence Number = %d\n", spn2572);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 1 4 4 0
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn61440(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn900;
        uint8_t         spn571;
        uint8_t         spn572;
        uint8_t         spn520;
        uint8_t         spn1085;
        uint8_t         spn1082;
        uint8_t         spn1667;
        uint8_t         spn1480;
        uint8_t         spn1715;
        uint8_t         spn1716;
        uint8_t         spn1717;
        const
        J1939_PREFERRED_ADDRESS
                        *pEntryA;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 900  1.1     4bits       Retarder Torque Mode
        spn900 = pMsg->DATA.bytes[0] & 0xF;
        // SPN 571  1.5     2bits       Retarder Enable - Brake Assist Switch
        spn571 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 572  1.7     2bits       Retarder Enable - Shift Assist Switch
        spn572 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 520  2       8bits       Actual Retarder - Percent Torque
        spn520 = pMsg->DATA.bytes[1];
        // SPN 1085 3       8bits       Intended Retarder Percent Torque
        spn1085 = pMsg->DATA.bytes[2];
        // SPN 1082 4.1     2bits       Engine Coolant Load Increase
        spn1082 = pMsg->DATA.bytes[3] & 0x3;
        // SPN 1667 4.3     2bits       Retarder Requesting Brake Light
        spn1667 = (pMsg->DATA.bytes[3] >> 4) & 0x3;
        // SPN 1480 5       8bits       Source Address of Controlling Device for Retarder Control
        spn1480 = pMsg->DATA.bytes[4];
        // SPN 1715 6       8bits       Drivers Demand Retarder - Percent Torque
        spn1715 = pMsg->DATA.bytes[5];
        // SPN 1716 7       8bits       Retarder Selection, non-engine
        spn1716 = pMsg->DATA.bytes[6];
        // SPN 1717 8       8bits       Actual Maximum Available Retarder - Percent Torque
        spn1717 = pMsg->DATA.bytes[7];
        
        if (spn900) {
            fprintf(this->pFileOut, "\tspn900 Retarder Torque Mode = %d\n", spn900);
        }
        else {
            fprintf(this->pFileOut, "\tspn900 Retarder Torque Mode = no braking\n");
        }
        print1of4(this,
                  spn571,
                  "spn571 Retarder Enable - Brake Assist Switch",
                  "Retarder - brake assist disabled",
                  "Retarder - brake assist enabled",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn572,
                  "spn572 Retarder Enable - Shift Assist Switch",
                  "Retarder - shift assist disabled",
                  "Retarder - shift assist enabled",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1082,
                  "spn1082 Engine Coolant Load Increase",
                  "No coolant load increase",
                  "Coolant load increase possible",
                  "Error",
                  NULL
                  );
        if (spn520 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn520 Actual Retarder - Percent Torque = %d\n", spn520);
        }
        if (spn1085 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1085 Intended Retarder Percent Torque = %d\n", spn1085);
        }
        fprintf(this->pFileOut, "\tspn1667 Retarder Requesting Brake Light = %d\n", spn1667);
        if (spn1480 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1480 Source Address of Controlling Device for "
                    "Retarder Control = ");
            pEntryA = j1939data_Find_Adr(spn1480);
            if (pEntryA) {
                fprintf(this->pFileOut, "%s\n", pEntryA->pDescription);
            }
            else {
                fprintf(this->pFileOut, "***???***\n");
            }
        }
        if (spn1715 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1715 Drivers Demand Retarder - Percent Torque = %d\n", spn1715);
        }
        if (spn1716 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1716 Retarder Selection, non-engine = %d\n", spn1716);
        }
        if (spn1717 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1717 Actual Maximum Available Retarder - Percent Torque = %d\n", spn1717);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 1 4 4 1
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn61441(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn561;
        uint8_t         spn562;
        uint8_t         spn563;
        uint8_t         spn1121;
        uint8_t         spn521;
        uint8_t         spn575;
        uint8_t         spn576;
        uint8_t         spn577;
        uint8_t         spn1238;
        uint8_t         spn972;
        uint8_t         spn971;
        uint8_t         spn970;
        uint8_t         spn969;
        uint8_t         spn973;
        uint8_t         spn1243;
        uint8_t         spn1439;
        uint8_t         spn1438;
        uint8_t         spn1793;
        uint8_t         spn1481;
        uint8_t         spn2911;
        uint8_t         spn1836;
        uint8_t         spn1792;
        const
        J1939_PREFERRED_ADDRESS
                        *pEntryA;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 561  1.1     2bits       ASR Engine Control Active
        spn561 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 562  1.3     2bits       ASR Brake Control Active
        spn562 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        // SPN 563  1.5     2bits       Anti-Lock Braking (ABS) Active
        spn563 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 1121 1.7     2bits       EBS Brake Switch
        spn1121 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 521  2       8bits       Brake Pedal Position
        spn521 = pMsg->DATA.bytes[1];
        // SPN 575  3.1     2bits       ABS Off-road Switch
        spn575 = pMsg->DATA.bytes[2] & 0x3;
        // SPN 576  3.3     2bits       ASR Off-road Switch
        spn576 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
        // SPN 577  3.5     2bits       ASR 'Hill Holder' Switch
        spn577 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
        // SPN 1238 3.7     2bits       Traction Control Override Switch
        spn1238 = (pMsg->DATA.bytes[2] >> 6) & 0x3;
        // SPN 972  4.1     2bits       Accelerator Interlock Switch
        spn972 = pMsg->DATA.bytes[3] & 0x3;
        // SPN 971  4.3     2bits       Engine Derate Switch
        spn971 = (pMsg->DATA.bytes[3] >> 2) & 0x3;
        // SPN 970  4.5     2bits       Engine Auxiliary Shutdown Switch
        spn970 = (pMsg->DATA.bytes[3] >> 4) & 0x3;
        // SPN 969  4.7     2bits       Remote Accelerator Enable Switch
        spn969 = (pMsg->DATA.bytes[3] >> 6) & 0x3;
        // SPN 973  5       8bits       Engine Retarder Selection
        spn973 = pMsg->DATA.bytes[4];
        // SPN 1243 6.1     2bits       ABS Fully Operational
        spn1243 = pMsg->DATA.bytes[5] & 0x3;
        // SPN 1439 6.3     2bits       EBS Red Warning Signal
        spn1439 = (pMsg->DATA.bytes[5] >> 2) & 0x3;
        // SPN 1438 6.5     2bits       ABS/EBS Amber Warning Signal (Powered Vehicle)
        spn1438 = (pMsg->DATA.bytes[5] >> 4) & 0x3;
        // SPN 1793 6.7     2bits       ATC/ASR Information Signal
        spn1793 = (pMsg->DATA.bytes[5] >> 6) & 0x3;
        // SPN 1481 7       8bits       Source Address of Controlling Device for Brake Control
        spn1481 = pMsg->DATA.bytes[6];
        // SPN 2911 8.3     2bits       Halt brake switch
        spn2911 = (pMsg->DATA.bytes[7] >> 2) & 0x3;
        // SPN 1836 8.5     2bits       Trailer ABS Status
        spn1836 = (pMsg->DATA.bytes[7] >> 4) & 0x3;
        // SPN 1792 8.7     2bits       Tractor-Mounted Trailer ABS Warning Signal
        spn1792 = (pMsg->DATA.bytes[7] >> 6) & 0x3;
        
        print1of4(this,
                  spn561,
                  "spn561 ASR Engine Control Active",
                  "Passive but installed",
                  "Active",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn562,
                  "spn562 ASR Brake Control Active",
                  "Passive but installed",
                  "Active",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn563,
                  "spn563 Anti-Lock Braking (ABS) Active",
                  "Passive but installed",
                  "Active",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1121,
                  "spn1121 EBS Brake Switch",
                  "Brake pedal is not being pressed",
                  "Brake pedal is being pressed",
                  "Error",
                  NULL
                  );
        if (spn521 == 0xFF) {
        }
        else {
            printPCT03(this, "\tspn521 Brake Pedal Position", spn521);
        }
        print1of4(this,
                  spn575,
                  "spn575 ABS Off-road Switch",
                  "ABS off-road switch passive",
                  "ABS off-road switch active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn576,
                  "spn576 ASR Off-road Switch",
                  "ASR off-road switch passive",
                  "ASR off-road switch active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn577,
                  "spn577 ASR 'Hill Holder' Switch",
                  "ASR 'hill holder' switch passive",
                  "ASR 'hill holder' switch active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1238,
                  "spn1238 Traction Control Override Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn972,
                  "spn972 Accelerator Interlock Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn971,
                  "spn971 Engine Derate Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn970,
                  "spn970 Engine Auxiliary Shutdown Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn969,
                  "spn969 Remote Accelerator Enable Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        if (spn973 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn973 Engine Retarder Selection = %d\n", spn973);
        }
        print1of4(this,
                  spn1243,
                  "spn1243 ABS Fully Operational",
                  "Not Fully Operational",
                  "Fully Operational",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1439,
                  "spn1439 EBS Red Warning Signal",
                  "Off",
                  "On",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1438,
                  "spn1438 ABS/EBS Amber Warning Signal (Powered Vehicle)",
                  "Off",
                  "On",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1793,
                  "spn1793 ATC/ASR Information Signal",
                  "Off",
                  "On",
                  "Reserved",
                  NULL
                  );
        if (spn1481 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1481 Source Address of Controlling Device for "
                    "Brake Control = ");
            pEntryA = j1939data_Find_Adr(spn1481);
            if (pEntryA) {
                fprintf(this->pFileOut, "%s\n", pEntryA->pDescription);
            }
            else {
                fprintf(this->pFileOut, "***???***\n");
            }
        }
        print1of4(this,
                  spn2911,
                  "spn2911 Halt brake switch",
                  "Halt brake switch passive",
                  "Halt brake switch active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1836,
                  "spn1836 Trailer ABS Status",
                  "Trailer ABS Status Information Available But Not Active",
                  "Trailer ABS Active",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1792,
                  "spn1792 Tractor-Mounted Trailer ABS Warning Signal",
                  "Off",
                  "On",
                  "Reserved",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //              D u m p   P G N 6 1 4 4 2   F002         ETC1
    //---------------------------------------------------------------
    
    /* This is "Electronic Transmission Controller 1". It is a status
     * msg generated by the transmission #3 or #4 every 10ms. It gives
     * us whether the transmission is shifting or not, input rpm and
     * output rpm most importantly.
     */
    
    bool            j1939misc_DumpPgn61442(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn522;
        uint8_t         spn560;     // Transmission Driveline Engaged
        uint8_t         spn573;     // Transmission Torque Converter Lockup Engaged
        uint8_t         spn574;     // Transmission Shift In Process
        uint8_t         spn606;
        uint8_t         spn607;
        uint8_t         spn1482;
        uint16_t        spn161;     // Transmission Input Shaft Speed
        uint16_t        spn191;     // Transmission Output Shaft Speed
        const
        J1939_PREFERRED_ADDRESS
                        *pEntryA;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        // SPN 560  1.1     2bits       Transmission Driveline Engaged
        spn560 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 573  1.3     2bits       Transmission Torque Converter Lockup Engaged
        spn573 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        // SPN 574  1.5     2bits       Transmission Shift In Process
        spn574 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 191  2-3     16bits      Transmission Output Shaft Speed
        spn191 = (pMsg->DATA.bytes[2] << 8) | pMsg->DATA.bytes[1];
        // SPN 522  4       8bits       Percent Clutch Slip
        spn522 = pMsg->DATA.bytes[3];
        // SPN 606  5.1     2bits       Engine Momentary Overspeed Enable
        spn606 = pMsg->DATA.bytes[4] & 0x3;
        // SPN 607  5.3     2bits       Progressive Shift Disable
        spn607 = (pMsg->DATA.bytes[4] >> 2) & 0x3;
        // SPN 161  6-7     16bits      Transmission Input Shaft Speed
        spn161 = (pMsg->DATA.bytes[6] << 8) | pMsg->DATA.bytes[5];
        // SPN 1482 8       8bits       Source Address of Controlling Device for
        //                              Transmission Control
        spn1482 = pMsg->DATA.bytes[7];
        
        print1of4(this,
                  spn560,
                  "spn560 Transmission Driveline Engaged",
                  "Driveline disengaged",
                  "Driveline engaged",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn573,
                  "spn573 Transmission Torque Converter Lockup Engaged",
                  "Torque converter lockup disengaged",
                  "Torque converter lockup engaged",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn574,
                  "spn574 Transmission Shift In Process",
                  "Shift is not in process",
                  "Shift in process",
                  "Error",
                  NULL
                  );
        if (spn191 == 0xFFFF) {
        }
        else {
            
            printRPM01(this, "\tspn191 Transmission Output Shaft Speed", spn191);
        }
        if (spn522 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tPercent Clutch Slip = %d\n", spn522);
        }
        print1of4(this,
                  spn606,
                  "spn606 Engine Momentary Overspeed Enable",
                  "Momentary engine overspeed is disabled",
                  "Momentary engine overspeed is enabled",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn607,
                  "spn607 Progressive Shift Disable",
                  "Progressive shift is not disabled",
                  "Progressive shift is disabled",
                  "Reserved",
                  NULL
                  );
        if (spn161 == 0xFFFF) {
        }
        else {
            printRPM01(this, "\tspn161 Transmission Input Shaft Speed", spn161);
        }
        if (spn1482 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1482 Source Address of Controlling Device for "
                    "Transmission Control = ");
            pEntryA = j1939data_Find_Adr(spn1482);
            if (pEntryA) {
                fprintf(this->pFileOut, "%s\n", pEntryA->pDescription);
            }
            else {
                fprintf(this->pFileOut, "***???***\n");
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //             D u m p  P G N 6 1 4 4 3     F003         EEC2
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn61443(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn29;
        uint8_t         spn91;
        uint8_t         spn92;
        uint8_t         spn558;
        uint8_t         spn559;
        uint8_t         spn974;
        uint8_t         spn1437;
        uint8_t         spn2970;
        uint8_t         spn2979;
        uint8_t         spn3357;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 558  1.1     2bits       Accelerator Pedal 1 Low Idle Switch
        spn558 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 559  1.3     2bits       Accelerator Pedal Kickdown Switch
        spn559 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        // SPN 1437 1.5     2bits       Road Speed Limit Status
        spn1437 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 2970 1.7     2bits       Accelerator Pedal 2 Low Idle Switch
        spn2970 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 91   2       8bits       Accelerator Pedal Position 1
        spn91 = pMsg->DATA.bytes[1];
        // SPN 92   3       8bits       Engine Percent Load At Current Speed
        spn92 = pMsg->DATA.bytes[2];
        // SPN 974  4       8bits       Remote Accelerator Pedal Position
        spn974 = pMsg->DATA.bytes[3];
        // SPN 29   5       8bits       Accelerator Pedal Position 2
        spn29 = pMsg->DATA.bytes[4];
        // SPN 2979 6.1     2bits       Vehicle Acceleration Rate Limit Status
        spn2979 = pMsg->DATA.bytes[5] & 0x3;
        // SPN 3357 7       8bits       Actual Maximum Available Engine - Percent Torque
        spn3357 = pMsg->DATA.bytes[6];
        
        print1of4(this,
                  spn558,
                  "spn558 Accelerator Pedal 1 Low Idle Switch",
                  "Accelerator pedal 1 not in low idle condition",
                  "Accelerator pedal 1 in low idle condition",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn559,
                  "spn559 Accelerator Pedal Kickdown Switch",
                  "Kickdown passive",
                  "Kickdown active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1437,
                  "spn1437 Road Speed Limit Status",
                  "Active",
                  "Not Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2970,
                  "spn2970 Accelerator Pedal 2 Low Idle Switch",
                  "Accelerator pedal 2 not in low idle condition",
                  "Accelerator pedal 2 in low idle condition",
                  "Error",
                  NULL
                  );
        if (spn91 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn91 Accelerator Pedal Position 1 = %d\n", spn91);
        }
        if (spn92 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn92 Engine Percent Load At Current Speed = %d\n", spn92);
        }
        if (spn974 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn974 Remote Accelerator Pedal Position = %d\n", spn974);
        }
        if (spn29 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn29 Accelerator Pedal Position 2 = %d\n", spn29);
        }
        print1of4(this,
                  spn2979,
                  "spn2979 Vehicle Acceleration Rate Limit Status",
                  "Limit not active",
                  "Limit active",
                  "Reserved",
                  NULL
                  );
        if (spn3357 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3357 Actual Maximum Available Engine - Percent Torque = %d\n", spn3357);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 1 4 4 4
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn61444(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn190;         // Engine Speed
        uint8_t         spn512;         // Driver's Demand Engine - Percent Torque
        uint8_t         spn513;         // Actual Engine - Percent Torque
        uint8_t         spn899;         // Engine Torque Mode
        uint8_t         spn1483;        // Source Address of Controlling Device for Engine Control
        uint8_t         spn1675;        // Engine Starter Mode
        uint8_t         spn2432;        // Engine Demand - Percent Torque
        const
        J1939_PREFERRED_ADDRESS
                        *pEntryA;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 899  1.1     4bits       Engine Torque Mode
        spn899 = pMsg->DATA.bytes[0] & 0x0F;
        // SPN 512  2       8bits       Driver's Demand Engine - Percent Torque
        spn512 = pMsg->DATA.bytes[1];
        // SPN 513  3       8bits       Actual Engine - Percent Torque
        spn513 = pMsg->DATA.bytes[2];
        // SPN 190  4-5     16bits      Engine Speed (rpm)
        spn190 = (pMsg->DATA.bytes[4] << 8) | pMsg->DATA.bytes[3];
        // SPN 1483 6       8bits       Source Address of Controlling Device for Engine Control
        spn1483 = pMsg->DATA.bytes[5];
        // SPN 1675 7.1     4bits       Engine Starter Mode
        spn1675 = pMsg->DATA.bytes[0] & 0x0F;
        // SPN 2432 8       8bits       Engine Demand - Percent Torque
        spn2432 = pMsg->DATA.bytes[2];
        
        if (spn899 == 0x0F) {
        }
        else {
            fprintf(this->pFileOut, "\tspn899 Engine Torque Mode = %d\n", spn899);
        }
        if (spn512 == 0xFF) {
        }
        else {
            printPCT05(this, "\tspn512 Driver's Demand Engine - Percent Torque", spn512);
        }
        if (spn513 == 0xFF) {
        }
        else {
            printPCT05(this, "\tspn513 Actual Engine - Percent Torque", spn513);
        }
        if (spn190 == 0xFFFF) {
        }
        else {
            printRPM01(this, "\tspn190 Engine Speed", spn190);
        }
        if (spn1483 == 0xFF) {
        }
        else {
            fprintf(
                    this->pFileOut,
                    "\tspn1483 Source Address of Controlling Device for Engine Control = "
                    );
            pEntryA = j1939data_Find_Adr(spn1483);
            if (pEntryA) {
                fprintf(this->pFileOut, "%s\n", pEntryA->pDescription);
            }
            else {
                fprintf(this->pFileOut, "***???***\n");
            }
        }
        switch (spn1675) {
            case 0:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - start not requested\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - starter active, gear not engaged\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - starter active, gear engaged\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - start finished; starter not active after having been actively engaged (after 50ms mode goes to 0000)\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - starter inhibited - due to engine running already\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - starter inhibited - due to engine not ready for starting (preheating)\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - starter inhibited - due to driveline engaged or other transmission inhibit\n");
                break;
            case 7:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - starter inhibited - due to active immobilizer\n");
                break;
            case 8:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - starter inhibited - due to starter over-temp\n");
                break;
            case 12:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - starter inhibited - reason unknown\n");
                break;
            case 13:
                fprintf(this->pFileOut, "\tspn1675 Engine Starter Mode - error\n");
                break;
        }
        if (spn2432 == 0xFF) {
        }
        else {
            printPCT05(this, "\tspn2432 Engine Demand - Percent Torque", spn2432);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 1 4 4 5
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn61445(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn524;         // Transmission Selected Gear
        uint16_t        spn526;         // Transmission Actual Gear Ratio
        uint8_t         spn523;         // Transmission Current Gear
        uint16_t        spn162;         // Transmission Requested Range
        uint16_t        spn163;         // Transmission Current Range
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 524  1       8bits       Transmission Selected Gear
        spn524 = pMsg->DATA.bytes[0];
        // SPN 526  2-3     16bits      Transmission Actual Gear Ratio
        spn526 = (pMsg->DATA.bytes[2] << 8) + pMsg->DATA.bytes[1];
        // SPN 523  4       8bits       Transmission Current Gear
        spn523 = pMsg->DATA.bytes[3];
        // SPN 162  5-6     16bits      Transmission Requested Range
        // Range selected by the operator. Characters may include P, Rx, Rx-1...R2,
        // R1, R, Nx, Nx-1...N2, N1, N, D, D1, D2..., Dx, L, L1, L2..., Lx-1, 1, 2,
        // 3,... If only one displayed character is required, the second character
        // shall be used and the first character shall be a space (ASCII 32) or a
        // control character (ASCII 0 to 31). If the first character is a control
        // character, refer to the manufacturer’s application document for definition.
        spn162 = (pMsg->DATA.bytes[5] << 8) + pMsg->DATA.bytes[4];
        // SPN 163  7-8     16bits      Transmission Current Range
        // Range selected by the operator. Characters may include P, Rx, Rx-1...R2,
        // R1, R, Nx, Nx-1...N2, N1, N, D, D1, D2..., Dx, L, L1, L2..., Lx-1, 1, 2,
        // 3,... If only one displayed character is required, the second character
        // shall be used and the first character shall be a space (ASCII 32) or a
        // control character (ASCII 0 to 31). If the first character is a control
        // character, refer to the manufacturer’s application document for definition.
        spn163 = (pMsg->DATA.bytes[7] << 8) + pMsg->DATA.bytes[6];
        
        if (spn524 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn524 Transmission Selected Gear = %d\n", spn524);
        }
        if (spn526 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn526 Transmission Actual Gear Ratio = %d\n", spn526);
        }
        if (spn523 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn523 Transmission Current Gear = %d\n", spn523);
        }
        if (spn162 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn162 Transmission Requested Range = %4X\n", spn162);
        }
        if (spn163 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn163 Transmission Current Range = %4X\n", spn163);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 1 4 5 2
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn61452(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn3030;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 3030 1-2     16bits      Transmission Torque Converter Ratio
        spn3030 = (pMsg->DATA.bytes[1] << 8) + pMsg->DATA.bytes[0];
        
        if (spn3030 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3030 Transmission Torque Converter Ratio = %d\n", spn3030);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 4 8 9 2
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn64892(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        //TODO: Fill in
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 4 9 4 7
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn64947(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn3245;
        uint16_t        spn3246;
        uint8_t         spn3247;
        uint8_t         spn3248;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 3245 1-2     16bits      Aftertreatment 1 Exhaust Gas Temperature 3
        spn3245 = (pMsg->DATA.bytes[1] << 8) | pMsg->DATA.bytes[0];
        // SPN 3246 3-4     16bits      Aftertreatment 1 Particulate Trap Outlet Gas Temperature
        spn3246 = (pMsg->DATA.bytes[3] << 8) | pMsg->DATA.bytes[2];
        // SPN 3247 5.1     5bits       Aftertreatment 1 Exhaust Gas Temperature 3 Preliminary FMI
        spn3247 = (pMsg->DATA.bytes[4] >> 5) & 0x1F;
        // SPN 3248 6.1     5bits       Aftertreatment 1 Particulate Trap Outlet Exhaust Gas Temperature Preliminary FMI
        spn3248 = (pMsg->DATA.bytes[5] >> 0) & 0x1F;
        
        if (spn3245 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3245 Aftertreatment 1 Exhaust Gas Temperature 3 = %d\n", spn3245);
        }
        if (spn3246 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3246 Aftertreatment 1 Particulate Trap Outlet Gas Temperature = %d\n", spn3246);
        }
        if (spn3247 == 0x1F) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3247 Aftertreatment 1 Exhaust Gas Temperature 3 Preliminary FMI = %d\n", spn3247);
        }
        if (spn3248 == 0x1F) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3248 Aftertreatment 1 Particulate Trap Outlet Exhaust Gas Temperature Preliminary FMI = %d\n", spn3248);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 4 9 4 8
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn64948(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn3241;
        uint16_t        spn3242;
        uint8_t         spn3243;
        uint8_t         spn3244;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        //TODO:
        // SPN 3241 1-2     16bits      Aftertreatment 1 Exhaust Gas Temperature 1
        spn3241 = (pMsg->DATA.bytes[1] << 8) | pMsg->DATA.bytes[0];
        // SPN 3242 3-4     16bits      Aftertreatment 1 Particulate Trap Intake Gas Temperature
        spn3242 = (pMsg->DATA.bytes[3] << 8) | pMsg->DATA.bytes[2];
        // SPN 3243 5.1     5bits       Aftertreatment 1 Exhaust Gas Temperature 1 Preliminary FMI
        spn3243 = (pMsg->DATA.bytes[4] >> 5) & 0x1F;
        // SPN 3244 6.1     5bits       Aftertreatment 1 Particulate Trap Intake Exhaust Gas Temperature Preliminary FMI
        spn3244 = (pMsg->DATA.bytes[5] >> 0) & 0x1F;
        
        if (spn3241 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3241 Aftertreatment 1 Exhaust Gas Temperature 3 = %d\n", spn3241);
        }
        if (spn3242 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3242 Aftertreatment 1 Particulate Trap Intake Gas Temperature = %d\n", spn3242);
        }
        if (spn3243 == 0x1F) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3243 Aftertreatment 1 Exhaust Gas Temperature 3 Preliminary FMI = %d\n", spn3243);
        }
        if (spn3244 == 0x1F) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3244 Aftertreatment 1 Particulate Trap Intake Exhaust Gas Temperature Preliminary FMI = %d\n", spn3244);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 4 9 6 4
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn64964(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn2913;            // Halt brake mode
        uint8_t         spn2912;            // Hill holder mode
        uint8_t         spn2919;            // Foundation Brake Use
        uint8_t         spn2917;            // XBR System State
        uint8_t         spn2918;            // XBR Active Control Mode
        uint8_t         spn2921;            // XBR Acceleration Limit
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 2913 1.3     3bits       Halt brake mode
        spn2913 = (pMsg->DATA.bytes[0] >> 2) & 0x07;
        // SPN 2912 1.6     3bits       Hill holder mode
        spn2912 = (pMsg->DATA.bytes[0] >> 5) & 0x07;
        // SPN 2919 2.1     2bits       Foundation Brake Use
        spn2919 = (pMsg->DATA.bytes[1] >> 0) & 0x03;
        // SPN 2917 2.3     2bits       XBR System State
        spn2917 = (pMsg->DATA.bytes[1] >> 2) & 0x03;
        // SPN 2918 2.5     4bits       XBR Active Control Mode
        spn2918 = (pMsg->DATA.bytes[1] >> 4) & 0x0F;
        // SPN 2921 3       8bits       XBR Acceleration Limit
        spn2921 = pMsg->DATA.bytes[2];
        
        switch (spn2913) {
            case 0:
                fprintf(this->pFileOut, "\tspn2913 Halt brake mode - Inactive\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tspn2913 Halt brake mode - Active\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tspn2913 Halt brake mode - Active, but not functioning properly. (This mode may be used to warn the driver)\n");
                break;
        }
        switch (spn2912) {
            case 0:
                fprintf(this->pFileOut, "\tspn2912 Hill holder mode - Inactive\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tspn2912 Hill holder mode - Active\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tspn2912 Hill holder mode - Active, but will change to inactive in a short time. (This mode may be used to warn the driver)\n");
                break;
        }
        print1of4(this,
                  spn2919,
                  "spn2919 Foundation Brake Use",
                  "Foundation brakes not in use",
                  "Foundation brakes not in use",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2917,
                  "spn2917 XBR System State",
                  "Any external brake demand will be accepted (brake system fully operational)",
                  "Only external brake demand of highest XBR Priority (00) will be accepted (e.g. because the temperature limit of the brake system is exceeded)",
                  "No external brake demand will be accepted (e.g. because of fault in brake system)",
                  NULL
                  );
        switch (spn2918) {
            case 0:
                fprintf(this->pFileOut, "\tspn2918 XBR Active Control Mode - No brake demand being executed (default mode)\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tspn2918 XBR Active Control Mode - Driver's brake demand being executed, no external brake demand\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tspn2918 XBR Active Control Mode - Addition mode of XBR acceleration control being executed\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tspn2918 XBR Active Control Mode - Maximum mode of XBR acceleration control being executed\n");
                break;
        }
        if (spn2921 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn2921 XBR Acceleration Limit = %d\n", spn2921);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 0 9 8
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65098(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn1850;
        uint8_t         spn1849;
        uint8_t         spn3086;
        uint8_t         spn2945;
        uint8_t         spn2900;
        uint8_t         spn1851;
        uint8_t         spn2539;
        uint8_t         spn2538;
        uint8_t         spn2537;
        uint8_t         spn2536;
        uint8_t         spn3289;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 1850 1.5     2bits       Transmission Requested Range Display Blank State
        spn1850 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 1849 1.7     2bits       Transmission Requested Range Display Flash State
        spn1849 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 3086 2.1     2bits       Transmission Ready for Brake Release
        spn3086 = pMsg->DATA.bytes[1] & 0x3;
        // SPN 2945 2.3     2bits       Active Shift Console Indicator
        spn2945 = (pMsg->DATA.bytes[1] >> 2) & 0x3;
        // SPN 2900 2.5     2bits       Transmission Engine Crank Enable
        spn2900 = (pMsg->DATA.bytes[1] >> 4) & 0x3;
        // SPN 1851 2.7     2bits       Transmission Shift Inhibit Indicator
        spn1851 = (pMsg->DATA.bytes[1] >> 6) & 0x3;
        // SPN 2539 3.1     2bits       Transmission Mode 4 Indicator
        spn2539 = pMsg->DATA.bytes[2] & 0x3;
        // SPN 2538 3.3     2bits       Transmission Mode 3 Indicator
        spn2538 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
        // SPN 2537 3.5     2bits       Transmission Mode 2 Indicator
        spn2537 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
        // SPN 2536 3.7     2bits       Transmission Mode 1 Indicator
        spn2536 = (pMsg->DATA.bytes[2] >> 6) & 0x3;
        // SPN 3289 4       8bits       Transmission Requested Gear Feedback
        spn3289 = pMsg->DATA.bytes[3];
        
        print1of4(this,
                  spn1850,
                  "spn1850 Transmission Requested Range Display Blank State",
                  "Inactive; Transmission Requested Range display should not be blanked",
                  "Active; Transmission Requested Range display should be blanked",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn1849,
                  "spn1849 Transmission Requested Range Display Flash State",
                  "Inactive; Transmission Requested Range display should not be flashing",
                  "Active; Transmission Requested Range display should be flashing",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn3086,
                  "spn3086 Transmission Ready for Brake Release",
                  "Transmission Not Ready for Brake Release",
                  "Transmission Ready for Brake Release",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2945,
                  "spn2945 Active Shift Console Indicator",
                  "Primary shift console is active",
                  "Secondary shift console is active",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2900,
                  "spn1851 Transmission Engine Crank Enable",
                  "Cranking disabled; engine cranking is prohibited by the transmission",
                  "Cranking enabled; engine cranking is allowed by the transmission",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1851,
                  "spn1851 Transmission Shift Inhibit Indicator",
                  "Inactive; shift is not inhibited",
                  "Active; shift is inhibited",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2539,
                  "spn2539 Transmission Mode 4 Indicator",
                  "Transmission Mode 4 not active",
                  "Transmission Mode 4 Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2538,
                  "spn2538 Transmission Mode 3 Indicator",
                  "Transmission Mode 3 not active",
                  "Transmission Mode 3 Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2537,
                  "spn2537 Transmission Mode 2 Indicator",
                  "Transmission Mode 2 not active",
                  "Transmission Mode 2 Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2536,
                  "spn2536 Transmission Mode 1 Indicator",
                  "Transmission Mode 1 not active",
                  "Transmission Mode 1 Active",
                  "Error",
                  NULL
                  );
        if (spn3289 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3289 Transmission Requested Gear Feedback = %d\n", spn3289);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 1 9 8
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65198(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn46;
        uint8_t         spn1086;
        uint8_t         spn1087;
        uint8_t         spn1088;
        uint8_t         spn1089;
        uint8_t         spn1090;
        uint8_t         spn1351;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN   46 1       8bits       Pneumatic Supply Pressure
        spn46 = pMsg->DATA.bytes[0];
        // SPN 1086 2       8bits       Parking and/or Trailer Air Pressure
        spn1086 = pMsg->DATA.bytes[1];
        // SPN 1087 3       8bits       Service Brake Air Pressure Circuit #1
        spn1087 = pMsg->DATA.bytes[2];
        // SPN 1088 4       8bits       Service Brake Air Pressure Circuit #2
        spn1088 = pMsg->DATA.bytes[3];
        // SPN 1089 5       8bits       Auxiliary Equipment Supply Pressure
        spn1089 = pMsg->DATA.bytes[4];
        // SPN 1090 6       8bits       Air Suspension Supply Pressure
        spn1090 = pMsg->DATA.bytes[5];
        // SPN 1351 7.1     2bits       Air Compressor Status
        spn1351 = pMsg->DATA.bytes[6] & 0x3;
        
        if (spn46 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn46 Pneumatic Supply Pressure = %d\n", spn46);
        }
        if (spn1086 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1086 Parking and/or Trailer Air Pressure = %d\n", spn1086);
        }
        if (spn1087 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1087 Service Brake Air Pressure Circuit #1 = %d\n", spn1087);
        }
        if (spn1088 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1088 Service Brake Air Pressure Circuit #2 = %d\n", spn1088);
        }
        if (spn1089 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1089 Auxiliary Equipment Supply Pressure = %d\n", spn1089);
        }
        if (spn1090 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1090 Air Suspension Supply Pressure = %d\n", spn1090);
        }
        print1of4(this,
                  spn1351,
                  "spn1351 Air Compressor Status",
                  "Not active",
                  "Active",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 0 2
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65202(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn1030;        // Total Engine PTO Fuel Used (Gaseous)
        uint16_t        spn1031;        // Trip Average Fuel Rate (Gaseous)
        uint16_t        spn1389;        // Engine Fuel Specific Gravity
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 1030 1-4     32bits      Total Engine PTO Fuel Used (Gaseous)
        spn1030 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
                    | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 1031 5-6     16bits      Trip Average Fuel Rate (Gaseous)
        spn1031 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 1389 7-8     16bits      Engine Fuel Specific Gravity
        spn1389 = pMsg->DATA.bytes[6] | (pMsg->DATA.bytes[7] << 8);
        
        if (spn1030 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1030 Total Engine PTO Fuel Used (Gaseous) = %d\n", spn1030);
        }
        if (spn1031 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1031 Trip Average Fuel Rate (Gaseous) = %d\n", spn1031);
        }
        if (spn1389 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1389 Engine Fuel Specific Gravity = %d\n", spn1389);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 1 3
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65213(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn975;
        uint8_t         spn977;
        uint16_t        spn1639;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 975  1       8bits       Estimated Percent Fan Speed
        spn975 = pMsg->DATA.bytes[0];
        // SPN 977  2.1     4bits       Fan Drive State
        spn977 = pMsg->DATA.bytes[1] & 0x0F;
        // SPN 1639 3-4     16bits      Fan Speed
        spn1639 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);
        
        if (spn975 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn975 Estimated Percent Fan Speed = %d\n", spn975);
        }
        switch (spn977) {
            case 0:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Fan off\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Engine system–General\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Excessive engine air temperature\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Excessive engine oil temperature\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Excessive engine coolant temperature\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Excessive transmission oil temperature\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Excessive hydraulic oil temperature\n");
                break;
            case 7:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Default Operation\n");
                break;
            case 8:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Not defined\n");
                break;
            case 9:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Manual control\n");
                break;
            case 10:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Transmission retarder\n");
                break;
            case 11:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - A/C system\n");
                break;
            case 12:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Timer\n");
                break;
            case 13:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Engine brake\n");
                break;
            case 14:
                fprintf(this->pFileOut, "\tspn977 Fan Drive State - Other\n");
                break;
        }
        if (spn1639 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1639 Fan Speed = %d\n", spn1639);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 1 5
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65215(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spn904;         // Front Axle Speed
        uint8_t         spn905;         // Relative Speed; Front Axle, Left Wheel
        uint8_t         spn906;         // Relative Speed; Front Axle, Right Wheel
        uint8_t         spn907;         // Relative Speed; Rear Axle #1, Left Wheel
        uint8_t         spn908;         // Relative Speed; Rear Axle #1, Right Wheel
        uint8_t         spn909;         // Relative Speed; Rear Axle #2, Left Wheel
        uint8_t         spn910;         // Relative Speed; Rear Axle #2, Right Wheel
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 904  1-2     16bits      Front Axle Speed
        spn904 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8);
        // SPN 905  3       8bits       Relative Speed; Front Axle, Left Wheel
        spn905 = pMsg->DATA.bytes[2];
        // SPN 906  4       8bits       Relative Speed; Front Axle, Right Wheel
        spn906 = pMsg->DATA.bytes[3];
        // SPN 907  5       8bits       Relative Speed; Rear Axle #1, Left Wheel
        spn907 = pMsg->DATA.bytes[4];
        // SPN 908  6       8bits       Relative Speed; Rear Axle #1, Right Wheel
        spn908 = pMsg->DATA.bytes[5];
        // SPN 909  7       8bits       Relative Speed; Rear Axle #2, Left Wheel
        spn909 = pMsg->DATA.bytes[6];
        // SPN 910  8       8bits       Relative Speed; Rear Axle #2, Right Wheel
        spn910 = pMsg->DATA.bytes[7];
        
        if (spn904 == 0xFFFF) {
        }
        else {
            printSpeed02(this, "\tspn904 Front Axle Speed", spn904);
        }
        if (spn905 == 0xFF) {
        }
        else {
            printSpeed04(this, "\tspn905 Relative Speed; Front Axle, Left Wheel", spn905);
        }
        if (spn906 == 0xFF) {
        }
        else {
            printSpeed04(this, "\tspn906 Relative Speed; Front Axle, Right Wheel", spn906);
        }
        if (spn907 == 0xFF) {
        }
        else {
            printSpeed04(this, "\tspn907 Relative Speed; Rear Axle #1, Left Wheel", spn907);
        }
        if (spn908 == 0xFF) {
        }
        else {
            printSpeed04(this, "\tspn908 Relative Speed; Rear Axle #1, Right Wheel", spn908);
        }
        if (spn909 == 0xFF) {
        }
        else {
            printSpeed04(this, "\tspn909 Relative Speed; Rear Axle #2, Left Wheel", spn909);
        }
        if (spn910 == 0xFF) {
        }
        else {
            printSpeed04(this, "\tspn910 Relative Speed; Rear Axle #2, Right Wheel", spn910);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 1 7
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65217(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn917;
        uint32_t        spn918;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 917  1-4     32bits      High Resolution Total Vehicle Distance
        spn917 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
        | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 918  5-8     32bits      High Resolution Trip Distance
        spn918 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8)
        | (pMsg->DATA.bytes[6] << 16)  | (pMsg->DATA.bytes[7] << 24);
        
        if (spn917 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn917 High Resolution Total Vehicle Distance = %d\n", spn917);
        }
        if (spn918 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn918 High Resolution Trip Distance = %d\n", spn918);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 4 7
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65247(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn514;
        uint16_t        spn515;
        uint8_t         spn519;
        uint8_t         spn2978;
        uint16_t        spn3236;
        uint8_t         spn3237;
        uint8_t         spn3238;
        uint8_t         spn3239;
        uint8_t         spn3240;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 514  1       8bits       Nominal Friction - Percent Torque
        spn514 = pMsg->DATA.bytes[0];
        // SPN 515  2-3     16bits      Engine's Desired Operating Speed
        spn515 = (pMsg->DATA.bytes[2] << 8) + pMsg->DATA.bytes[1];
        // SPN 519  4       8bits       Engine's Desired Operating Speed Asymmetry Adjustment
        spn519 = pMsg->DATA.bytes[3];
        // SPN 2978 5       8bits       Estimated Engine Parasitic Losses - Percent Torque
        spn2978 = pMsg->DATA.bytes[4];
        // SPN 3236 6-7     16bits      Aftertreatment 1 Exhaust Gas Mass Flow
        spn3236 = (pMsg->DATA.bytes[6] << 8) + pMsg->DATA.bytes[5];
        // SPN 3237 8.1     2bits       Aftertreatment 1 Intake Dew Point
        spn3237 = pMsg->DATA.bytes[7] & 0x3;
        // SPN 3238 8.3     2bits       Aftertreatment 1 Exhaust Dew Point
        spn3238 = (pMsg->DATA.bytes[7] >> 2) & 0x3;
        // SPN 3239 8.5     2bits       Aftertreatment 2 Intake Dew Point
        spn3239 = (pMsg->DATA.bytes[7] >> 4) & 0x3;
        // SPN 3240 8.7     2bits       Aftertreatment 2 Exhaust Dew Point
        spn3240 = (pMsg->DATA.bytes[7] >> 6) & 0x3;
        
        if (spn514 == 0xFF) {
        }
        else {
            printPCT05(this, "\tspn514 Nominal Friction - Percent Torque", spn514);
        }
        if (spn515 == 0xFFFF) {
        }
        else {
            printRPM01(this, "\tspn515 Engine's Desired Operating Speed", spn515);
        }
        if (spn519 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn519 Engine's Desired Operating Speed Asymmetry Adjustment = %d\n", spn519);
        }
        if (spn2978 == 0xFF) {
        }
        else {
            printPCT05(this, "\tspn2978 Estimated Engine Parasitic Losses - Percent Torque", spn2978);
        }
        if (spn3236 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3236 Aftertreatment 1 Exhaust Gas Mass Flow = %d\n", spn3236);
        }
        print1of4(this,
                  spn3237,
                  "spn3237 Aftertreatment 1 Intake Dew Point",
                  "Not exceeded the dew point",
                  "Exceeded the dew point",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3238,
                  "spn3238 Aftertreatment 1 Exhaust Dew Point",
                  "Not exceeded the dew point",
                  "Exceeded the dew point",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3239,
                  "spn3239 Aftertreatment 2 Intake Dew Point",
                  "Not exceeded the dew point",
                  "Exceeded the dew point",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3240,
                  "spn3240 Aftertreatment 2 Exhaust Dew Point",
                  "Not exceeded the dew point",
                  "Exceeded the dew point",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 4 8
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65248(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn244;
        uint32_t        spn245;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 244  1-4     32bits      Trip Distance
        spn244 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
        | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 245  5-8     32bits      Total Vehicle Distance
        spn245 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8)
        | (pMsg->DATA.bytes[6] << 16)  | (pMsg->DATA.bytes[7] << 24);
        
        if (spn244 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn244 Trip Distance = %d\n", spn244);
        }
        if (spn245 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn245 Total Vehicle Distance = %d\n", spn245);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 5 2
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65252(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn593;
        uint8_t         spn594;
        uint8_t         spn592;
        uint8_t         spn590;
        uint8_t         spn591;
        uint8_t         spn985;
        uint8_t         spn875;
        uint8_t         spn605;
        uint8_t         spn1081;
        uint8_t         spn1110;
        uint8_t         spn1109;
        uint8_t         spn1108;
        uint8_t         spn1107;
        uint8_t         spn1111;
        uint8_t         spn2815;
        uint8_t         spn2814;
        uint8_t         spn2813;
        uint8_t         spn2812;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 593  1.1     2bits       Engine Idle Shutdown has Shutdown Engine
        spn593 = pMsg->DATA.bytes[0] & 0x3;
        // SPN 594  1.3     2bits       Engine Idle Shutdown Driver Alert Mode
        spn594 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
        // SPN 592  1.5     2bits       Engine Idle Shutdown Timer Override
        spn592 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
        // SPN 590  1.7     2bits       Engine Idle Shutdown Timer State
        spn590 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
        // SPN 591  2.7     2bits       Engine Idle Shutdown Timer Function
        spn591 = (pMsg->DATA.bytes[1] >> 6) & 0x3;
        // SPN 985  3.1     2bits       A/C High Pressure Fan Switch
        spn985 = pMsg->DATA.bytes[2] & 0x3;
        // SPN 875  3.3     2bits       Refrigerant Low Pressure Switch
        spn875 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
        // SPN 605  3.5     2bits       Refrigerant High Pressure Switch
        spn605 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
        // SPN 1081 4.1     2bits       Engine Wait to Start Lamp
        spn1081 = pMsg->DATA.bytes[3] & 0x3;
        // SPN 1110 5.1     2bits       Engine Protection System has Shutdown Engine
        spn1110 = pMsg->DATA.bytes[4] & 0x3;
        // SPN 1109 5.3     2bits       Engine Protection System Approaching Shutdown
        spn1109 = (pMsg->DATA.bytes[4] >> 2) & 0x3;
        // SPN 1108 5.5     2bits       Engine Protection System Timer Override
        spn1108 = (pMsg->DATA.bytes[4] >> 4) & 0x3;
        // SPN 1107 5.7     2bits       Engine Protection System Timer State
        spn1107 = (pMsg->DATA.bytes[4] >> 6) & 0x3;
        // SPN 1111 6.7     2bits       Engine Protection System Configuration
        spn1111 = (pMsg->DATA.bytes[5] >> 6) & 0x3;
        // SPN 2815 7.1     2bits       Engine Alarm Acknowledge
        spn2815 = pMsg->DATA.bytes[6] & 0x3;
        // SPN 2814 7.3     2bits       Engine Alarm Output Command Status
        spn2814 = (pMsg->DATA.bytes[6] >> 2) & 0x3;
        // SPN 2813 7.5     2bits       Engine Air Shutoff Command Status
        spn2813 = (pMsg->DATA.bytes[6] >> 4) & 0x3;
        // SPN 2812 7.7     2bits       Engine Overspeed Test
        spn2812 = (pMsg->DATA.bytes[6] >> 6) & 0x3;
        
        print1of4(this,
                  spn593,
                  "spn593 Engine Idle Shutdown has Shutdown Engine",
                  "No",
                  "Yes",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn594,
                  "spn594 Engine Idle Shutdown Driver Alert Mode",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn592,
                  "spn592 Engine Idle Shutdown Timer Override",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn590,
                  "spn590 Engine Idle Shutdown Timer State",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn591,
                  "spn591 Engine Idle Shutdown Timer Function",
                  "Disabled in calibration",
                  "Enabled in calibration",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn985,
                  "spn985 A/C High Pressure Fan Switch",
                  "Pressure normal",
                  "Pressure too high, compressor clutch may be disengaged",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn875,
                  "spn875 Refrigerant Low Pressure Switch",
                  "Pressure normal",
                  "Pressure too high, compressor clutch may be disengaged",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn605,
                  "spn605 Refrigerant High Pressure Switch",
                  "Pressure normal",
                  "Pressure too high, compressor clutch may be disengaged",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1081,
                  "spn1081 Engine Wait to Start Lamp",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1110,
                  "spn1110 Engine Protection System has Shutdown Engine",
                  "No",
                  "Yes",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1109,
                  "spn1109 Engine Protection System Approaching Shutdown",
                  "Not approaching",
                  "Approaching",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1108,
                  "spn1108 Engine Protection System Timer Override",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1107,
                  "spn1107 Engine Protection System Timer State",
                  "Inactive",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1111,
                  "spn1111 Engine Protection System Configuration",
                  "Disabled in calibration",
                  "Enabled in calibration",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2815,
                  "spn2815 Engine Alarm Acknowledge",
                  "Not Active",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2814,
                  "spn2814 Engine Alarm Command Status",
                  "Not Active",
                  "Active",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2813,
                  "spn2813 Engine Alarm Shutoff Command Status",
                  "Air Shutoff Disabled, not attempting to shutoff engine air supply",
                  "Air Shutoff Enabled, attempting to shutoff engine air supply",
                  "Reserved",
                  NULL
                  );
        print1of4(this,
                  spn2812,
                  "spn2812 Engine Overspeed Test",
                  "Not Active",
                  "Active",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 5 3
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65253(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn247;         // Engine Total Hours of Operation
        uint32_t        spn249;         // Engine Total Revolutions
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 247  1-4     32bits      Engine Total Hours of Operation
        spn247 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
        | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 249  5-8     32bits      Engine Total Revolutions
        spn249 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8)
        | (pMsg->DATA.bytes[6] << 16)  | (pMsg->DATA.bytes[7] << 24);
        
        if (spn247 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn247 Engine Total Hours of Operation = %d\n", spn247);
        }
        if (spn249 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn249 Engine Total Revolutions = %d\n", spn249);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 5 4
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65254(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn959;
        uint32_t        spn960;
        uint32_t        spn961;
        uint32_t        spn963;
        uint32_t        spn962;
        uint32_t        spn964;
        uint32_t        spn1601;
        uint32_t        spn1602;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 959  1       8bits       Seconds
        spn959 = pMsg->DATA.bytes[0];
        // SPN 960  1       8bits       Minutes
        spn960 = pMsg->DATA.bytes[1];
        // SPN 961  1       8bits       Hours
        spn961 = pMsg->DATA.bytes[1];
        // SPN 963  1       8bits       Month
        spn963 = pMsg->DATA.bytes[1];
        // SPN 962  1       8bits       Day
        spn962 = pMsg->DATA.bytes[1];
        // SPN 964  1       8bits       Year
        spn964 = pMsg->DATA.bytes[1];
        // SPN 1601 1       8bits       Local minute offset
        spn1601 = pMsg->DATA.bytes[1];
        // SPN 1602 1       8bits       Local hour offset
        spn1602 = pMsg->DATA.bytes[1];
        
        if (spn959 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn959 Seconds = %d\n", spn959);
        }
        if (spn960 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn960 Minutes = %d\n", spn960);
        }
        if (spn961 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn961 Hours = %d\n", spn961);
        }
        if (spn963 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn963 Month = %d\n", spn963);
        }
        if (spn962 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn962 Day = %d\n", spn962);
        }
        if (spn964 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn964 Year = %d\n", spn964);
        }
        if (spn1601 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1601 Local minute offset = %d\n", spn1601);
        }
        if (spn1602 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1602 Local hour offset = %d\n", spn1602);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 5 5
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65255(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn246;         // Total Vehicle Hours
        uint32_t        spn248;         // Total Power Takeoff Hours
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 246  1-4     32bits      Total Vehicle Hours
        spn246 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
        | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 248  5-8     32bits      Total Power Takeoff Hours
        spn248 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8)
        | (pMsg->DATA.bytes[6] << 16)  | (pMsg->DATA.bytes[7] << 24);
        
        if (spn246 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn246 Total Vehicle Hours = %d\n", spn246);
        }
        if (spn248 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn248 Total Power Takeoff Hours = %d\n", spn248);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 5 7
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65257(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint32_t        spn182;
        uint32_t        spn250;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 182  1-4     32bits      Engine Trip Fuel
        spn182 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8)
        | (pMsg->DATA.bytes[2] << 16)  | (pMsg->DATA.bytes[3] << 24);
        // SPN 250  5-8     32bits      Total Vehicle Distance
        spn250 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8)
        | (pMsg->DATA.bytes[6] << 16)  | (pMsg->DATA.bytes[7] << 24);
        
        if (spn182 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn182 Engine Trip Fuel = %d\n", spn182);
        }
        if (spn250 == 0xFFFFFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn250 Engine Total Fuel Used = %d\n", spn250);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 2
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65262(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn110;
        uint8_t         spn174;
        uint16_t        spn175;
        uint16_t        spn176;
        uint8_t         spn52;
        uint8_t         spn1134;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 110  1       8bits       Engine Coolant Temperature
        spn110 = pMsg->DATA.bytes[0];
        // SPN 174  2       8bits       Engine Fuel Temperature 1
        spn174 = pMsg->DATA.bytes[1];
        // SPN 175  3-4     16bits      Engine Oil Temperature 1
        spn175 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);
        // SPN 176  5-6     16bits      Engine Turbocharger Oil Temperature
        spn176 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 52   7       8bits       Engine Intercooler Temperature
        spn52 = pMsg->DATA.bytes[6];
        // SPN 1134 8       8bits       Engine Intercooler Thermostat Opening
        spn1134 = pMsg->DATA.bytes[7];
        
        if (spn110 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn110 Engine Coolant Temperature = %d\n", spn110);
        }
        if (spn174 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn174 Engine Fuel Temperature 1 = %d\n", spn174);
        }
        if (spn175 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn175 Engine Oil Temperature 1 = %d\n", spn175);
        }
        if (spn176 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn176 Engine Turbocharger Oil Temperature = %d\n", spn176);
        }
        if (spn52 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn52 Engine Intercooler Temperature = %d\n", spn52);
        }
        if (spn1134 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn1134 Engine Intercooler Thermostat Opening = %d\n", spn1134);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 6 3
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65263(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn94;
        uint8_t         spn22;
        uint8_t         spn98;
        uint8_t         spn100;
        uint16_t        spn101;
        uint8_t         spn109;
        uint8_t         spn111;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 94   1       8bits       Engine Fuel Delivery Pressure
        spn94 = pMsg->DATA.bytes[0];
        // SPN 22   2       8bits       Engine Extended Crankcase Blow-by Pressure
        spn22 = pMsg->DATA.bytes[1];
        // SPN 98   3       8bits       Engine Oil Level
        spn98 = pMsg->DATA.bytes[2];
        // SPN 100  4       8bits       Engine Oil Pressure
        spn100 = pMsg->DATA.bytes[3];
        // SPN 101  5-6     16bits      Engine Crankcase Pressure
        spn101 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 109  4       8bits       Engine Coolant Pressure
        spn109 = pMsg->DATA.bytes[6];
        // SPN 111  4       8bits       Engine Coolant Level
        spn111 = pMsg->DATA.bytes[7];
        
        if (spn94 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn94 Engine Fuel Delivery Pressure = %d\n", spn94);
        }
        if (spn22 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn22 Engine Extended Crankcase Blow-by Pressure = %d\n", spn22);
        }
        if (spn98 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn98 Engine Oil Level = %d\n", spn98);
        }
        if (spn100 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn100 Engine Oil Pressure = %d\n", spn100);
        }
        if (spn101 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn101 Engine Crankcase Pressure = %d\n", spn101);
        }
        if (spn109 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn109 Engine Coolant Pressure = %d\n", spn109);
        }
        if (spn111 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn111 Engine Coolant Level = %d\n", spn111);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  H a n d l e  P G N 6 5 2 6 4
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65264(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn90;
        uint16_t        spn186;
        uint16_t        spn187;
        uint8_t         spn980;
        uint8_t         spn979;
        uint8_t         spn978;
        uint8_t         spn984;
        uint8_t         spn983;
        uint8_t         spn982;
        uint8_t         spn981;
        uint8_t         spn2897;
        uint8_t         spn3447;
        uint8_t         spn3448;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 90   1       8bits       Power Takeoff Oil Temperature
        spn90 = pMsg->DATA.bytes[0];
        // SPN 186  2-3     16bits      Power Takeoff Speed
        spn186 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        // SPN 187  4-5     16bits      Power Takeoff Set Speed
        spn187 = pMsg->DATA.bytes[3] | (pMsg->DATA.bytes[4] << 8);
        // SPN 980  6.1     2bits       Engine PTO Enable Switch
        spn980 = pMsg->DATA.bytes[5] & 0x3;
        // SPN 979  6.3     2bits       Engine Remote PTO Preprogrammed Speed Control Switch
        spn979 = (pMsg->DATA.bytes[5] >> 2) & 0x3;
        // SPN 978  6.5     2bits       Engine Remote PTO Variable Speed Control Switch
        spn978 = (pMsg->DATA.bytes[5] >> 4) & 0x3;
        // SPN 984  7.1     2bits       Engine PTO Set Switch
        spn984 = pMsg->DATA.bytes[6] & 0x3;
        // SPN 983  7.3     2bits       Engine PTO Coast/Decelerate Switch
        spn983 = (pMsg->DATA.bytes[6] >> 2) & 0x3;
        // SPN 982  7.5     2bits       Engine PTO Resume Switch
        spn982 = (pMsg->DATA.bytes[6] >> 4) & 0x3;
        // SPN 981  7.7     2bits       Engine PTO Accelerate Switch
        spn981 = (pMsg->DATA.bytes[6] >> 6) & 0x3;
        // SPN 2897 8.1     2bits       Operator PTO Memory Select Switch
        spn2897 = pMsg->DATA.bytes[7] & 0x3;
        // SPN 3447 8.3     2bits       Remote PTO preprogrammed speed control switch #2
        spn3447 = (pMsg->DATA.bytes[7] >> 2) & 0x3;
        // SPN 3448 8.5     2bits       Auxiliary Input Ignore Switch
        spn3448 = (pMsg->DATA.bytes[7] >> 4) & 0x3;
        
        if (spn90 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn90 Power Takeoff Oil Temperature = %d\n", spn90);
        }
        if (spn186 == 0xFFFF) {
        }
        else {
            printRPM01(this, "\tspn186 Power Takeoff Speed", spn186);
        }
        if (spn187 == 0xFFFF) {
        }
        else {
            printRPM01(this, "\tspn187 Power Takeoff Set Speed", spn187);
        }
        print1of4(this,
                  spn980,
                  "spn980 Engine PTO Enable Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn979,
                  "spn979 Engine Remote PTO Preprogrammed Speed Control Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn978,
                  "spn978 Engine Remote PTO Variable Speed Control Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn984,
                  "spn984 Engine PTO Set Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn983,
                  "spn983 Engine PTO Coast/Decelerate Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn982,
                  "spn982 Engine PTO Resume Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn981,
                  "spn981 Engine PTO Accelerate Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn2897,
                  "spn2897 Operator PTO Memory Select Switch",
                  "PTO set speed memory 1 selected",
                  "PTO set speed memory 2 selected",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3447,
                  "spn3447 Remote PTO preprogrammed speed control switch #2",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn3448,
                  "spn3448 Auxiliary Input Ignore Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //      PGN 65265 FEF1 - Cruise Control/Vehicle Speed - CCVS
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65265(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn69;
        uint8_t         spn70;
        uint8_t         spn1633;
        uint16_t        spn84;
        uint8_t         spn595;
        uint8_t         spn596;
        uint8_t         spn597;
        uint8_t         spn598;
        uint8_t         spn599;
        uint8_t         spn600;
        uint8_t         spn601;
        uint8_t         spn602;
        uint8_t         spn86;
        uint8_t         spn976;
        uint8_t         spn527;
        uint8_t         spn968;
        uint8_t         spn967;
        uint8_t         spn966;
        uint8_t         spn1237;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN   69  1.1     2bits       Two Speed Axle Switch
        spn69 = pMsg->DATA.bytes[0] & 0x03;
        // SPN   70  1.3     2bits       Parking Brake Switch
        spn70 = (pMsg->DATA.bytes[0] >> 2) & 0x03;
        // SPN 1633  1.5     2bits       Cruise Control Pause Switch
        spn1633 = (pMsg->DATA.bytes[0] >> 2) & 0x03;
        // SPN   84  2-3     16bits      Wheel-Based Vehicle Speed
        spn84 = (pMsg->DATA.bytes[2] << 8) | pMsg->DATA.bytes[1];
        // SPN  595  4.1      2bits      Cruise Control Active
        spn595 = pMsg->DATA.bytes[3] & 0x03;
        // SPN  596  4.3     2bits       Cruise Control Enable Switch
        spn596 = (pMsg->DATA.bytes[3] >> 2) & 0x03;
        // SPN  597  4.5     2bits       Brake Switch
        spn597 = (pMsg->DATA.bytes[3] >> 2) & 0x03;
        // SPN  598  4.7     2bits       Clutch Switch
        spn598 = (pMsg->DATA.bytes[3] >> 2) & 0x03;
        // SPN  599  5.1     2bits       Cruise Control Set Switch
        spn599 = pMsg->DATA.bytes[4] & 0x03;
        // SPN  600  5.3     2bits       Cruise Control Coast (Decelerate) Switch
        spn600 = (pMsg->DATA.bytes[4] >> 2) & 0x03;
        // SPN  601  5.5     2bits       Cruise Control Resume Switch
        spn601 = (pMsg->DATA.bytes[4] >> 2) & 0x03;
        // SPN  602  5.7     2bits       Cruise Control Accelerate Switch
        spn602 = (pMsg->DATA.bytes[4] >> 2) & 0x03;
        // SPN   86  6       8bits       Cruise Control Set Speed
        spn86 = pMsg->DATA.bytes[5];
        // SPN  976  7.1     5bits       PTO State
        spn976 = pMsg->DATA.bytes[6] & 0x1F;
        // SPN  527  7.6     3bits       Cruise Control States
        spn527 = (pMsg->DATA.bytes[6] >> 5) & 0x07;
        // SPN  968  8.1     2bits       Engine Idle Increment Switch
        spn968 = pMsg->DATA.bytes[7] & 0x03;
        // SPN  967  8.3     2bits       Engine Idle Decrement Switch
        spn967 = (pMsg->DATA.bytes[7] >> 2) & 0x03;
        // SPN  966  8.5     2bits       Engine Test Mode Switch
        spn966 = (pMsg->DATA.bytes[7] >> 2) & 0x03;
        // SPN 1237  8.7     2bits       Engine Shutdown Override Switch
        spn1237 = (pMsg->DATA.bytes[7] >> 2) & 0x03;
        
        if (spn84 == 0xFFFF) {
        }
        else {
            printSpeed02(this, "\tspn84 Vehicle Speed", spn84);
        }
        if (spn86 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn86 CC Vehicle Speed = %d km/h\n", spn86);
        }
        print1of4(this,
                  spn69,
                  "spn69 Two Speed Axle Switch",
                  "Low speed range",
                  "High speed range",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn70,
                  "spn70 Parking Brake Switch",
                  "Parking brake not set",
                  "Parking brake set",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1633,
                  "spn1633 Cruise Control Pause Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn595,
                  "spn595 Cruise Control Active",
                  "Cruise control switched off",
                  "Cruise control switched on",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn596,
                  "spn596 Cruise Control Enable Switch",
                  "Cruise control disabled",
                  "Cruise control enabled",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn597,
                  "spn597 Brake Switch",
                  "Brake pedal released",
                  "Brake pedal depressed",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn598,
                  "spn598 Clutch Switch",
                  "Clutch pedal released",
                  "Clutch pedal depressed",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn599,
                  "spn599 Cruise Control Set Switch",
                  "Cruise control activator not in the position 'set'",
                  "Cruise control activator in position 'set'",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn600,
                  "spn600 Cruise Control Coast (Decelerate) Switch",
                  "Cruise control activator not in the position 'coast'",
                  "Cruise control activator in position 'coast'",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn601,
                  "spn601 Cruise Control Resume Switch",
                  "Cruise control activator not in the position 'resume'",
                  "Cruise control activator in position 'resume'",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn602,
                  "spn602 Cruise Control Accelerate Switch",
                  "Cruise control activator not in the position 'accelerate'",
                  "Cruise control activator in position 'accelerate'",
                  "Error",
                  NULL
                  );
        switch (spn976) {
            case 0:
                fprintf(this->pFileOut, "\tspn976 PTO State - Off/Disabled\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tspn976 PTO State - Hold\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tspn976 PTO State - Remote Hold\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tspn976 PTO State - Standby\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tspn976 PTO State - Remote Standby\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tspn976 PTO State - Set\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tspn976 PTO State - Decelerate/Coast\n");
                break;
            case 7:
                fprintf(this->pFileOut, "\tspn976 PTO State - Resume\n");
                break;
            case 8:
                fprintf(this->pFileOut, "\tspn976 PTO State - Accelerate\n");
                break;
            case 9:
                fprintf(this->pFileOut, "\tspn976 PTO State - Accelerator Override\n");
                break;
            case 10:
                fprintf(this->pFileOut, "\tspn976 PTO State - Preprogrammed set speed 1\n");
                break;
            case 11:
                fprintf(this->pFileOut, "\tspn976 PTO State - Preprogrammed set speed 2\n");
                break;
            case 12:
                fprintf(this->pFileOut, "\tspn976 PTO State - Preprogrammed set speed 3\n");
                break;
            case 13:
                fprintf(this->pFileOut, "\tspn976 PTO State - Preprogrammed set speed 4\n");
                break;
            case 14:
                fprintf(this->pFileOut, "\tspn976 PTO State - Preprogrammed set speed 5\n");
                break;
            case 15:
                fprintf(this->pFileOut, "\tspn976 PTO State - Preprogrammed set speed 6\n");
                break;
            case 16:
                fprintf(this->pFileOut, "\tspn976 PTO State - Preprogrammed set speed 7\n");
                break;
            case 17:
                fprintf(this->pFileOut, "\tspn976 PTO State - Preprogrammed set speed 8\n");
                break;
            case 18:
                fprintf(this->pFileOut, "\tspn976 PTO State - PTO set speed memory 1\n");
                break;
            case 19:
                fprintf(this->pFileOut, "\tspn976 PTO State - PTO set speed memory 2\n");
                break;
        }
        switch (spn527) {
            case 0:
                fprintf(this->pFileOut, "\tspn527 Cruise Control States - Off/Disabled\n");
                break;
            case 1:
                fprintf(this->pFileOut, "\tspn527 Cruise Control States - Hold\n");
                break;
            case 2:
                fprintf(this->pFileOut, "\tspn527 Cruise Control States - Accelerate\n");
                break;
            case 3:
                fprintf(this->pFileOut, "\tspn527 Cruise Control States - Decelerate\n");
                break;
            case 4:
                fprintf(this->pFileOut, "\tspn527 Cruise Control States - Resume\n");
                break;
            case 5:
                fprintf(this->pFileOut, "\tspn527 Cruise Control States - Set\n");
                break;
            case 6:
                fprintf(this->pFileOut, "\tspn527 Cruise Control States - Accelerator Override\n");
                break;
        }
        print1of4(this,
                  spn968,
                  "spn968 Engine Idle Increment Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn967,
                  "spn967 Engine Idle Decrement Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn966,
                  "spn966 Engine Test Mode Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        print1of4(this,
                  spn1237,
                  "spn1237 Engine Shutdown Override Switch",
                  "Off",
                  "On",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               H a n d l e  P G N 6 5 2 6 6   FEF2         LFE
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65266(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        uint16_t        spn183;
        uint16_t        spn184;
        uint16_t        spn185;
        uint8_t         spn51;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pMsg) {
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            
            // SPN 183  1-2     16bits       Engine Fuel Rate
            spn183 = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8);
            // SPN 184  3-4     16bits       Engine Instantaneous Fuel Economy
            spn184 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);
            // SPN 185  5-6     16bits       Engine Average Fuel Economy
            spn185 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
            // SPN 51   7       8bits        Engine Throttle Position
            spn51 = pMsg->DATA.bytes[6];
            
            if (spn183 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn183 Engine Fuel Rate = %d\n", spn183);
            }
            if (spn184 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn184 Engine Instantaneous Fuel Economy = %d\n", spn184);
            }
            if (spn185 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn185 Engine Average Fuel Economy = %d\n", spn185);
            }
            if (spn51 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn51 Engine Throttle Position = %d\n", spn51);
            }
            
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 6 9
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65269(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn108;
        uint16_t        spn170;
        uint16_t        spn171;
        uint8_t         spn172;
        uint16_t        spn79;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 108  1       8bits       Barometric Pressure
        spn108 = pMsg->DATA.bytes[0];
        // SPN 170  2-3     16bits      Cab Interior Temperature
        spn170 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        // SPN 171  4-5     16bits      Ambient Air Temperature
        spn171 = pMsg->DATA.bytes[3] | (pMsg->DATA.bytes[4] << 8);
        // SPN 172  6       8bits       Engine Air Inlet Temperature
        spn172 = pMsg->DATA.bytes[0];
        // SPN 79   7-8     16bits      Road Surface Temperature
        spn79 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
        
        if (spn108 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn108 Barometric Pressure = %d\n", spn108);
        }
        if (spn170 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn170 Cab Interior Temperature = %d\n", spn170);
        }
        if (spn171 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn171 Ambient Air Temperature = %d\n", spn171);
        }
        if (spn172 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn172 Engine Air Inlet Temperature = %d\n", spn172);
        }
        if (spn79 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn79 Road Surface Temperature = %d\n", spn79);
        }

        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               H a n d l e  P G N 6 5 2 7 0   FEF6         IC1
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65270(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        uint8_t         spn81;
        uint8_t         spn102;
        uint8_t         spn105;
        uint8_t         spn106;
        uint8_t         spn107;
        uint16_t        spn173;
        uint8_t         spn112;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pMsg) {
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            
            // SPN 81   1       8bits       Engine Particulate Trap Inlet Pressure
            spn81 = pMsg->DATA.bytes[0];
            // SPN 102  2       8bits       Engine Turbocharger Boost Pressure
            spn102 = pMsg->DATA.bytes[1];
            // SPN 105  3       8bits       Engine Intake Manifold 1 Temperature
            spn105 = pMsg->DATA.bytes[2];
            // SPN 106  4       8bits       Engine Air Inlet Pressure
            spn106 = pMsg->DATA.bytes[3];
            // SPN 107  5       8bits       Engine Air Filter 1 Differential Pressure
            spn107 = pMsg->DATA.bytes[4];
            // SPN 173  6-7     16bits      Engine Exhaust Gas Temperature
            spn173 = pMsg->DATA.bytes[5] | (pMsg->DATA.bytes[6] << 8);
            // SPN 112  8       8bits       Engine Coolant Filter Differential Pressure
            spn112 = pMsg->DATA.bytes[7];
            
            if (spn81 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn81 Engine Particulate Trap Inlet Pressure = %d\n", spn81);
            }
            if (spn102 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn102 Engine Turbocharger Boost Pressure = %d\n", spn102);
            }
            if (spn105 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn105 Engine Intake Manifold 1 Temperature = %d\n", spn105);
            }
            if (spn106 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn106 Engine Air Inlet Pressure = %d\n", spn106);
            }
            if (spn107 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn107 Engine Air Filter 1 Differential Pressure = %d\n", spn107);
            }
            if (spn173 == 0xFFFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn173 Engine Exhaust Gas Temperature = %d\n", spn173);
            }
            if (spn112 == 0xFF) {
            }
            else {
                fprintf(this->pFileOut, "\tspn112 Engine Coolant Filter Differential Pressure = %d\n", spn112);
            }
            
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 7 1
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65271(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn114;
        uint8_t         spn115;
        uint16_t        spn167;
        uint16_t        spn168;
        uint16_t        spn158;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 114  1       8bits       Net Battery Current
        spn114 = pMsg->DATA.bytes[0];
        // SPN 115  2       8bits       Alternator Current
        spn115 = pMsg->DATA.bytes[1];
        // SPN 167  3-4     16bits      Charging System Potential (Voltage)
        spn167 = pMsg->DATA.bytes[2] | (pMsg->DATA.bytes[3] << 8);
        // SPN 168  5-6     16bits      Electrical Potential (Voltage)
        spn168 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 158  7-8     16bits      Battery Potential (Voltage), Switched
        spn158 = pMsg->DATA.bytes[6] | (pMsg->DATA.bytes[7] << 8);
        
        if (spn114 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn114 Net Battery Current = %d\n", spn114);
        }
        if (spn115 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn115 Alternator Current = %d\n", spn115);
        }
        if (spn167 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn167 Charging System Potential (Voltage) = %d\n", spn167);
        }
        if (spn168 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn168 Electrical Potential (Voltage) = %d\n", spn168);
        }
        if (spn158 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn158 Battery Potential (Voltage), Switched = %d\n", spn158);
        }
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               H a n d l e  P G N 6 5 2 7 2   EBC1        TRF1
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65272(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu = {0};
        J1939_PGN       pgn = {0};
        uint8_t         spn123;
        uint8_t         spn124;
        uint8_t         spn126;
        uint8_t         spn127;
        uint16_t        spn177;
        uint8_t         spn3027;
        uint8_t         spn3028;
        uint8_t         spn3026;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 123  1       8bits       Clutch Pressure
        spn123 = pMsg->DATA.bytes[0];
        // SPN 124  2       8bits       Transmission Oil Level
        spn124 = pMsg->DATA.bytes[1];
        // SPN 126  3       8bits       Transmission Filter Differential Pressure
        spn126 = pMsg->DATA.bytes[2];
        // SPN 127  4       8bits       Transmission Oil Pressure
        spn127 = pMsg->DATA.bytes[3];
        // SPN 177  5-6     16bits       Transmission Oil Temperature
        spn177 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] << 8);
        // SPN 3027 7       8bits       Transmission Oil Level High / Low
        spn3027 = pMsg->DATA.bytes[6];
        // SPN 3028 8.1     4bits       Transmission Oil Level Countdown Timer
        spn3028 = pMsg->DATA.bytes[7] & 0xF;
        // SPN 3026 8.5     4bits       Transmission Oil Level Measurement Status
        spn3026 = (pMsg->DATA.bytes[7] >> 4) & 0xF;
        
        if (spn123 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tClutch Pressure = %d\n", spn123);
        }
        if (spn124 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Oil Level = %d\n", spn124);
        }
        if (spn126 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Filter Differential Pressure = %d\n", spn126);
        }
        if (spn127 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Oil Pressure = %d\n", spn127);
        }
        if (spn177 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Oil Temperature = %d\n", spn177);
        }
        if (spn3027 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tTransmission Oil Level High / Low = %d\n", spn3027);
        }
        if (spn3028 == 0x0F) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3028 Transmission Oil Level Countdown Timer -  ");
            switch (spn3028) {
                case 0:
                    fprintf(this->pFileOut, "less than 1 minute\n");
                    break;
                case 1:
                    fprintf(this->pFileOut, "1 minute\n");
                    break;
                case 2:
                    fprintf(this->pFileOut, "2 minutes\n");
                    break;
                case 3:
                    fprintf(this->pFileOut, "3 minutes\n");
                    break;
                case 4:
                    fprintf(this->pFileOut, "4 minutes\n");
                    break;
                case 5:
                    fprintf(this->pFileOut, "5 minutes\n");
                    break;
                case 6:
                    fprintf(this->pFileOut, "6 minutes\n");
                    break;
                case 7:
                    fprintf(this->pFileOut, "7 minutes\n");
                    break;
                case 8:
                    fprintf(this->pFileOut, "8 minutes\n");
                    break;
                case 9:
                    fprintf(this->pFileOut, "9 minutes\n");
                    break;
                case 10:
                    fprintf(this->pFileOut, "10 minutes\n");
                    break;
                case 11:
                    fprintf(this->pFileOut, "11 minutes\n");
                    break;
                case 12:
                    fprintf(this->pFileOut, "12 minutes\n");
                    break;
                case 13:
                    fprintf(this->pFileOut, "13 minutes\n");
                    break;
                case 14:
                    fprintf(this->pFileOut, "error\n");
            }
        }
        if (spn3026 == 0x0F) {
        }
        else {
            fprintf(this->pFileOut, "\tspn3026 Transmission Oil Level Measurement Status -  ");
            switch (spn3026) {
                case 0:
                    fprintf(this->pFileOut, "Conditions valid for transmission oil level measurement\n");
                    break;
                case 1:
                    fprintf(this->pFileOut, "Conditions not valid – Settling timer still counting down\n");
                    break;
                case 2:
                    fprintf(this->pFileOut, "Conditions not valid – Transmission in gear\n");
                    break;
                case 3:
                    fprintf(this->pFileOut, "Conditions not valid – Transmission fluid temperature too low\n");
                    break;
                case 4:
                    fprintf(this->pFileOut, "Conditions not valid – Transmission fluid temperature too high\n");
                    break;
                case 5:
                    fprintf(this->pFileOut, "Conditions not valid – Vehicle moving; output shaft speed too high\n");
                    break;
                case 6:
                    fprintf(this->pFileOut, "Conditions not valid – Vehicle not level\n");
                    break;
                case 7:
                    fprintf(this->pFileOut, "Conditions not valid – Engine speed too low\n");
                    break;
                case 8:
                    fprintf(this->pFileOut, "Conditions not valid – Engine speed too high\n");
                    break;
                case 13:
                    fprintf(this->pFileOut, "Conditions not valid - Other\n");
                    break;
                case 14:
                    fprintf(this->pFileOut, "Error\n");
                    break;
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 7 6
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65276(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn80;
        uint8_t         spn96;
        uint8_t         spn95;
        uint8_t         spn99;
        uint16_t        spn169;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 80   1       8bits       Washer Fluid Level
        spn80 = pMsg->DATA.bytes[0];
        // SPN 96   2       8bits       Fuel Level
        spn96 = pMsg->DATA.bytes[1];
        // SPN 95   3       8bits       Engine Fuel Filter Differential Pressure
        spn95 = pMsg->DATA.bytes[2];
        // SPN 99   4       8bits       Engine Oil Filter Differential Pressure
        spn99 = pMsg->DATA.bytes[3];
        // SPN 169  5-6     16bits      Cargo Ambient Temperature
        spn169 = pMsg->DATA.bytes[4] | (pMsg->DATA.bytes[5] >> 8);
        
        if (spn80 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn80 Washer Fluid Level = %d\n", spn80);
        }
        if (spn96 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn96 Fuel Level = %d\n", spn96);
        }
        if (spn95 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn95 Engine Fuel Filter Differential Pressure = %d\n", spn95);
        }
        if (spn99 == 0xFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn99 Engine Oil Filter Differential Pressure = %d\n", spn99);
        }
        if (spn169 == 0xFFFF) {
        }
        else {
            fprintf(this->pFileOut, "\tspn169 Cargo Ambient Temperature = %d\n", spn169);
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p  P G N 6 5 2 7 9
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpPgn65279(
        J1939MISC_DATA  *this,
        J1939_MSG       *pMsg,
        const
        J1939_PGN_ENTRY *pEntry
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn97;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // SPN 97   1.1     2bits       Water In Fuel Indicator
        spn97 = pMsg->DATA.bytes[0] & 0x03;
        
        print1of4(this,
                  spn97,
                  "spn97 Water In Fuel Indicator",
                  "No",
                  "Yes",
                  "Error",
                  NULL
                  );
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D u m p   M e s s a g e
    //---------------------------------------------------------------
    
    bool            j1939misc_DumpMessage(
        J1939MISC_DATA	*this,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        const
        J1939_PGN_ENTRY *pEntry = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pFileOut)
            ;
        else {
            return false;
        }
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        pEntry = j1939data_Find_Pgn(pgn);
        if (pEntry) {
            printMsgDesc(this, pMsg, pEntry);
        }
        else {
            if ((0xFF00 <= pgn.pgn) && (pgn.pgn <= 0xFFFF)) {
                printMsgDesc(this, pMsg, &pgn65280_entry);
            }
            else {
                printMsg(this, pMsg);
                fprintf(this->pFileOut, "   **** Unknown Message ****\n");
            }
            return true;
        }
        
        
        switch (pgn.pgn) {
                
            case 0:
                j1939misc_DumpPgn0(this, pMsg, pEntry);
                break;
                
            case 57344:
                j1939misc_DumpPgn57344(this, pMsg, pEntry);
                break;
                
            case 60160:
                j1939misc_DumpPgn60160(this, pMsg, pEntry);
                break;
                
            case 61440:
                j1939misc_DumpPgn61440(this, pMsg, pEntry);
                break;
                
            case 61441:
                j1939misc_DumpPgn61441(this, pMsg, pEntry);
                break;
                
            case 61442:
                j1939misc_DumpPgn61442(this, pMsg, pEntry);
                break;
                
            case 61443:
                j1939misc_DumpPgn61443(this, pMsg, pEntry);
                break;
                
            case 61444:
                j1939misc_DumpPgn61444(this, pMsg, pEntry);
                break;
                
            case 61445:
                j1939misc_DumpPgn61445(this, pMsg, pEntry);
                break;
                
            case 61452:
                j1939misc_DumpPgn61452(this, pMsg, pEntry);
                break;
                
            case 64892:
                j1939misc_DumpPgn64892(this, pMsg, pEntry);
                break;
                
            case 64947:
                j1939misc_DumpPgn64947(this, pMsg, pEntry);
                break;
                
            case 64948:
                j1939misc_DumpPgn64948(this, pMsg, pEntry);
                break;
                
            case 64964:
                j1939misc_DumpPgn64964(this, pMsg, pEntry);
                break;
                
            case 65098:
                j1939misc_DumpPgn65098(this, pMsg, pEntry);
                break;
                
            case 65198:
                j1939misc_DumpPgn65198(this, pMsg, pEntry);
                break;
                
            case 65202:
                j1939misc_DumpPgn65202(this, pMsg, pEntry);
                break;
                
            case 65213:
                j1939misc_DumpPgn65213(this, pMsg, pEntry);
                break;
                
            case 65215:
                j1939misc_DumpPgn65215(this, pMsg, pEntry);
                break;
                
            case 65217:
                j1939misc_DumpPgn65217(this, pMsg, pEntry);
                break;
                
            case 65247:
                j1939misc_DumpPgn65247(this, pMsg, pEntry);
                break;
                
            case 65248:
                j1939misc_DumpPgn65248(this, pMsg, pEntry);
                break;
                
            case 65252:
                j1939misc_DumpPgn65252(this, pMsg, pEntry);
                break;
                
            case 65253:
                j1939misc_DumpPgn65253(this, pMsg, pEntry);
                break;
                
            case 65254:
                j1939misc_DumpPgn65254(this, pMsg, pEntry);
                break;
                
            case 65255:
                j1939misc_DumpPgn65255(this, pMsg, pEntry);
                break;
                
            case 65257:
                j1939misc_DumpPgn65257(this, pMsg, pEntry);
                break;
                
            case 65262:
                j1939misc_DumpPgn65262(this, pMsg, pEntry);
                break;
                
            case 65263:
                j1939misc_DumpPgn65263(this, pMsg, pEntry);
                break;
                
            case 65264:
                j1939misc_DumpPgn65264(this, pMsg, pEntry);
                break;
                
            case 65265:
                j1939misc_DumpPgn65265(this, pMsg, pEntry);
                break;
                
            case 65266:
                j1939misc_DumpPgn65266(this, pMsg, pEntry);
                break;
                
            case 65269:
                j1939misc_DumpPgn65269(this, pMsg, pEntry);
                break;
                
            case 65270:
                j1939misc_DumpPgn65270(this, pMsg, pEntry);
                break;
                
            case 65271:
                j1939misc_DumpPgn65271(this, pMsg, pEntry);
                break;
                
            case 65272:
                j1939misc_DumpPgn65272(this, pMsg, pEntry);
                break;
                
            case 65276:
                j1939misc_DumpPgn65276(this, pMsg, pEntry);
                break;
                
            case 65279:
                j1939misc_DumpPgn65279(this, pMsg, pEntry);
                break;
                
            default:
                break;
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939misc_Enable(
        J1939MISC_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return j1939misc_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939MISC_DATA *   j1939misc_Init(
        J1939MISC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(J1939MISC_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939MISC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939MISC);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939misc_Vtbl);
        
        j1939misc_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pFileOut = stderr;

    #ifdef NDEBUG
    #else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(J1939MISC_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939misc_IsEnabled(
        J1939MISC_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939misc_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939misc_getLastError(this);
        }
        
        // Return to caller.
        j1939misc_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939misc_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          j1939misc_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        J1939MISC_DATA   *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return j1939misc_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return j1939misc_Enable;
                        }
                        break;

                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939misc_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939MISC object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939misc_ToDebugString(
        J1939MISC_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939misc_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(j1939misc) size=%d\n",
                     this,
                     j1939misc_getSize(this)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(j1939misc)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939misc_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939misc_Validate(
        J1939MISC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939MISC) )
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(J1939MISC_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


