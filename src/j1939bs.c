// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939bs.c
 *	Generated 06/21/2017 16:25:20
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
#include <j1939bs_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn0_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        &pgn0_entry,
        NULL,
        NULL,
        (P_SETUP_MSG_RTN)j1939bs_SetupPgn0,
        0,
        0,
        0,
        0
    };
    
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61441_entry = {
        //  PGN 61441  0x00F001 - Electronic Engine Controller 1 - EBC1
        &pgn61441_entry,
        (P_SRVCMSG_RTN)j1939bs_HandlePgn61441,
        NULL,
        (P_SETUP_MSG_RTN)j1939bs_SetupPgn61441,
        offsetof(J1939BS_DATA, time61441),
        0,
        0,
        0
    };
    
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn64964_entry = {
        //  PGN 61441  0x00F001 - Electronic Engine Controller 1 - EBC1
        &pgn64964_entry,
        (P_SRVCMSG_RTN)j1939bs_HandlePgn64964,
        NULL,
        (P_SETUP_MSG_RTN)j1939bs_SetupPgn64964,
        offsetof(J1939BS_DATA, time64964),
        0,
        0,
        0
    };
    
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65215_entry = {
        //  PGN 65215  0x00FEBF - Wheel Speed Information - EBC2
        &pgn65215_entry,
        (P_SRVCMSG_RTN)j1939bs_HandlePgn65215,
        NULL,
        (P_SETUP_MSG_RTN)j1939bs_SetupPgn65215,
        offsetof(J1939BS_DATA, time65215),
        0,
        0,
        0
    };
    
    
    
    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        &ca_pgn0_entry,
        &ca_pgn61441_entry,
        &ca_pgn64964_entry,
        &ca_pgn65215_entry,
        NULL
    };
    
    
    static
    const
    J1939CA_PGN_TABLE     rcvPgntbl = {
        (sizeof(rcvPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &rcvPgnIndex
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     *xmtPgnIndex[] = {
        &ca_pgn61441_entry,
        &ca_pgn64964_entry,
        &ca_pgn65215_entry,
        NULL
    };
    
    static
    const
    J1939CA_PGN_TABLE     xmtPgntbl = {
        (sizeof(xmtPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &xmtPgnIndex
    };
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            j1939bs_task_body(
        void            *pData
    )
    {
        //J1939BS_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939BS_DATA *  j1939bs_Alloc(
    )
    {
        J1939BS_DATA    *this;
        uint32_t        cbSize = sizeof(J1939BS_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939BS_DATA *  j1939bs_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939BS_DATA       *this;
        
        this = j1939bs_Alloc( );
        if (this) {
            this = j1939bs_Init(this, pCAN, pSYS, spn2837, spn2838, spn2846);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         j1939bs_getLastError(
        J1939BS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939bs_setLastError(
        J1939BS_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        j1939bs_getPriority(
        J1939BS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939bs_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            j1939bs_setPriority(
        J1939BS_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939bs_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        j1939bs_getSize(
        J1939BS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939bs_setLastError(this, ERESULT_SUCCESS);
        return 0;
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
     @code
        ERESULT eRc = j1939bs__Assign(this,pOther);
     @endcode
     @param     this    J1939BS object pointer
     @param     pOther  a pointer to another J1939BS object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         j1939bs_Assign(
        J1939BS_DATA		*this,
        J1939BS_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !j1939bs_Validate(pOther) ) {
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
        j1939bs_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939bs_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939bs_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        j1939bs      *pCopy = j1939bs_Copy(this);
     @endcode
     @param     this    J1939BS object pointer
     @return    If successful, a J1939BS object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the J1939BS object.
     */
    J1939BS_DATA *     j1939bs_Copy(
        J1939BS_DATA       *this
    )
    {
        J1939BS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = j1939bs_New(obj_getSize(this));
        if (pOther) {
            eRc = j1939bs_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939bs_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939bs_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939BS_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939BS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        //j1939bs_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        j1939ca_Dealloc(this);          // Needed for inheritance
        //obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939bs_Disable(
        J1939BS_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939bs_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return j1939bs_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939bs_setLastError(this, ERESULT_SUCCESS);
        return j1939bs_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939bs_Enable(
        J1939BS_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939bs_setLastError(this, ERESULT_SUCCESS);
        return j1939bs_getLastError(this);
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 0    0x000000 (TSC1)
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
    
    bool            j1939bs_HandlePgn0(
        J1939BS_DATA	*this,
        J1939_MSG       *pMsg           // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         sa;
        uint8_t         spn518;         // Requested Torque / Torque Limit
                                            // offset: -125%, -125 to 125 (0 - 250)
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
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939bs_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pMsg) {
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            sa = pdu.SA;
            
            spn695 = pMsg->DATA.bytes[0] & 0x3;
            spn696 = (pMsg->DATA.bytes[0] >> 2) & 0x3;
            spn897 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
            spn898 = pMsg->DATA.bytes[1] | (pMsg->DATA.bytes[2] << 8);
            spn518 = pMsg->DATA.bytes[3];
            
#ifdef XYZZY
            if (this->fActive && (0 == spn695)) {      // *** Stop Retarding ***
                this->fActive = false;
                this->timeOut = 0;
                this->spn1480 = 0xFF;
                // Turn off retarder.
                fRc = true;
                goto exit00;
            }
            if ((2 == spn695) || (3 == spn695)) {
                this->timeOut = j1939ca_MsTimeGet((J1939CA_DATA *)this) + 150;
                if (this->fActive) {
                    // Just update time
                }
                else {
                    this->fActive = true;
                    this->spn1480 = sa;
                    // Turn on retarder.
                    fRc = true;
                    goto exit00;
                }
            }
        }
        else {
            //TODO: This might not account for clock rollover.
            if ( this->fActive && (this->timeOut <= j1939ca_MsTimeGet((J1939CA_DATA *)this)) ) {
                this->fActive = false;
                this->timeOut = 0;
                this->spn1480 = 255;
                // Turn off retarder.
                fRc = true;
                goto exit00;
            }
#endif

        }
        
        // Return to caller.
    exit00:
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 61441  0x00F001 - Electronic Engine Controller 1 - EBC1
    //---------------------------------------------------------------
    
    bool            j1939bs_HandlePgn61441(
        J1939BS_DATA    *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn561;             // ASR Engine Control Active
        uint8_t         spn562;             // ASR Brake Control Active
        uint8_t         spn563;             // Anti-Lock Braking (ABS) Active
        uint8_t         spn1121;            // EBS Brake Switch
        uint8_t         spn521;             // Brake Pedal Position
        uint8_t         spn575;             // ABS Off-road Switch
        uint8_t         spn576;             // ASR Off-road Switch
        uint8_t         spn577;             // ASR 'Hill Holder' Switch
        uint8_t         spn1238;            // Traction Control Override Switch
        uint8_t         spn972;             // Accelerator Interlock Switch
        uint8_t         spn971;             // Engine Derate Switch
        uint8_t         spn970;             // Engine Auxiliary Shutdown Switch
        uint8_t         spn969;             // Remote Accelerator Enable Switch
        uint8_t         spn973;             // Engine Retarder Selection
        uint8_t         spn1243;            // ABS Fully Operational
        uint8_t         spn1439;            // EBS Red Warning Signal
        uint8_t         spn1438;            // ABS/EBS Amber Warning Signal (Powered Vehicle)
        uint8_t         spn1793;            // ATC/ASR Information Signal
        uint8_t         spn1481;            // Source Address of Controlling Device for Brake Control
        uint8_t         spn2911;            // Halt brake switch
        uint8_t         spn1836;            // Trailer ABS Status
        uint8_t         spn1792;            // Tractor-Mounted Trailer ABS Warning Signal
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
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
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 64964  0x00FDC4 - Electronic Brake Controller 5 - EBC5
    //---------------------------------------------------------------
    
    bool            j1939bs_HandlePgn64964(
        J1939BS_DATA    *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
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
        if( !j1939bs_Validate(this) ) {
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
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 65215  0x00FEBF - Wheel Speed Information - EBC2
    //---------------------------------------------------------------
    
    bool            j1939bs_HandlePgn65215(
        J1939BS_DATA    *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
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
        if( !j1939bs_Validate(this) ) {
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
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //           H a n d l e  T i m e d  T r a n s m i t s
    //---------------------------------------------------------------
    
    bool            j1939bs_HandleTimedTransmits(
        J1939BS_DATA	*this
    )
    {
        uint32_t        curTime;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        curTime = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        this->curTime = curTime;

        if ((curTime - this->time61441.msTime) >= this->time61441.msDelay) {
            j1939bs_TransmitPgn61441(this);
        }
        if ((curTime - this->time64964.msTime) >= this->time64964.msDelay) {
            j1939bs_TransmitPgn64964(this);
        }
        if ((curTime - this->time65215.msTime) >= this->time65215.msDelay) {
            j1939bs_TransmitPgn65215(this);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939BS_DATA *  j1939bs_Init(
        J1939BS_DATA    *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint32_t        cbSize = sizeof(J1939BS_DATA);
        
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

        this =  (OBJ_ID)j1939ca_Init(                       // Needed for Inheritance
                        (J1939CA_DATA *)this,
                        pCAN,
                        pSYS,
                        spn2837,
                        spn2838,
                        spn2846
                );
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939BS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939BS);      // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939bs_Vtbl);
        
        //this->super.name.ECU = 0;
        this->super.name.FU = 12;
        this->super.name.FUI = 1;

        j1939ca_Setup((J1939CA_DATA *)this, J1939_BRAKE_SYSTEM_CONTROLLER);
        this->super.cs = J1939CA_STATE_NORMAL_OPERATION; // Assume that we have our name.
        this->super.pRcvPgnTbl = &rcvPgntbl;
        this->super.pXmtPgnTbl = &xmtPgntbl;
        this->super.pTimedTransmit =
                            (P_HANDLE_TIMED_TRANSMITS)&j1939bs_HandleTimedTransmits;
        
        // Default all SPNs to unsupported values.
        memset(
               &this->spnFirst,
               0xFF,
               (offsetof(J1939BS_DATA,spnLast) - offsetof(J1939BS_DATA,spnFirst)
                + sizeof(uint32_t))
        );
        this->spn1481 = J1939_BRAKE_SYSTEM_CONTROLLER;

        this->time61441.msDefault = pgn61441_entry.msFreq;
        this->time61441.msDelay = pgn61441_entry.msFreq;
        this->time61441.pgn = 61441;
        
        this->time64964.msDefault = pgn64964_entry.msFreq;
        this->time64964.msDelay = pgn64964_entry.msFreq;
        this->time64964.pgn = 64964;
        
        this->time65215.msDefault = pgn65215_entry.msFreq;
        this->time65215.msDelay = pgn65215_entry.msFreq;
        this->time65215.pgn = 65215;
        
    #ifdef NDEBUG
    #else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(&this->spnFirst);
        BREAK_NOT_BOUNDARY4(&this->spnLast);
        BREAK_NOT_BOUNDARY4(sizeof(J1939BS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939bs_IsEnabled(
        J1939BS_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939bs_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939bs_getLastError(this);
        }
        
        // Return to caller.
        j1939bs_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939bs_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          j1939bs_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        J1939BS_DATA   *this = objId;
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !j1939bs_Validate(this) ) {
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
                            return j1939bs_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return j1939bs_Enable;
                        }
                        break;

                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939bs_ToDebugString(this,4);
     @endcode
     @param     this    J1939BS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939bs_ToDebugString(
        J1939BS_DATA      *this,
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
        if( !j1939bs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(j1939bs) size=%d\n",
                     this,
                     j1939bs_getSize(this)
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(j1939bs)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939bs_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 0   0x0000          TSC1
    //---------------------------------------------------------------
    
    // Torque/Speed Control 1 - TSC1 -
    // Unused bits are set to 1.
    // The Transmission and the Cruise Controller are normally interested
    // in this message and try to control the Engine Retarder via the
    // TSC1 message.
    int             j1939bs_SetupPgn0(
        J1939BS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn0_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn0_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn0_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            *pData  = 0xC0;
            *pData |= this->spn695 & 0x03;
            *pData |= (this->spn696 & 0x03) << 2;
            *pData |= (this->spn897 & 0x03) << 4;
            ++pData;    // 1
            *pData  = this->spn898 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn898 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = this->spn518;
            ++pData;    // 4
            *pData  = 0xF0;
            *pData |= (this->spn3349 & 0x07);
            if (pPDU->PS == 41) {       // Retarder, Exhaust, Engine #1
                *pData |= 0x1F << 3;
            }
            else {
                *pData |= (this->spn3350 & 0x1F) << 3;
            }
            ++pData;    // 5
            *pData  = 0xFF;
            ++pData;    // 6
            *pData  = 0xFF;
            ++pData;    // 7
            *pData  = 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939bs_TransmitPgn0(
        J1939BS_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;
        
        len = j1939bs_SetupPgn0(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 61441  0x00F001 - Electronic Engine Controller 1 - EBC1
    //---------------------------------------------------------------
    
    int             j1939bs_SetupPgn61441(
        J1939BS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn61441_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn61441_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn61441_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            *pData  = 0x00;
            *pData |= this->spn561 & 0x03;
            *pData |= (this->spn562 & 0x03) << 2;
            *pData |= (this->spn563 & 0x03) << 4;
            *pData |= (this->spn1121 & 0x03) << 6;
            ++pData;    // 1
            *pData  = this->spn521 & 0xFF;
            ++pData;    // 2
            *pData  = 0x00;
            *pData |= this->spn575 & 0x03;
            *pData |= (this->spn576 & 0x03) << 2;
            *pData |= (this->spn577 & 0x03) << 4;
            *pData |= (this->spn1238 & 0x03) << 6;
            ++pData;    // 3
            *pData  = 0x00;
            *pData |= this->spn972 & 0x03;
            *pData |= (this->spn971 & 0x03) << 2;
            *pData |= (this->spn970 & 0x03) << 4;
            *pData |= (this->spn969 & 0x03) << 6;
            ++pData;    // 4
            *pData  = this->spn973 & 0xFF;
            ++pData;    // 5
            *pData  = 0x00;
            *pData |= this->spn1243 & 0x03;
            *pData |= (this->spn1439 & 0x03) << 2;
            *pData |= (this->spn1438 & 0x03) << 4;
            *pData |= (this->spn1793 & 0x03) << 6;
            ++pData;    // 6
            *pData  = this->spn1481 & 0xFF;
            ++pData;    // 7
            *pData  = 0x03;
            *pData |= (this->spn2911 & 0x03) << 2;
            *pData |= (this->spn1836 & 0x03) << 4;
            *pData |= (this->spn1792 & 0x03) << 6;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939bs_TransmitPgn61441(
        J1939BS_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;
        
        len = j1939bs_SetupPgn61441(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time61441.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 64964  0x00FDC4 - Electronic Brake Controller 5 - EBC5
    //---------------------------------------------------------------
    
    int             j1939bs_SetupPgn64964(
        J1939BS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn64964_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn64964_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn64964_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            *pData  = 0x03;
            *pData |= (this->spn2913 & 0x07) << 2;
            *pData |= (this->spn2912 & 0x07) << 5;
            ++pData;    // 1
            *pData  = 0xC0;
            *pData |= this->spn2919 & 0x03;
            *pData |= (this->spn2917 & 0x03) << 2;
            *pData |= (this->spn2918 & 0x03) << 4;
            ++pData;    // 2
            *pData = this->spn2921 & 0xFF;
            ++pData;    // 3
            *pData = 0xFF;
            ++pData;    // 4
            *pData = 0xFF;
            ++pData;    // 5
            *pData  = 0x00;
            *pData = 0xFF;
            ++pData;    // 6
            *pData = 0xFF;
            ++pData;    // 7
            *pData = 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939bs_TransmitPgn64964(
        J1939BS_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;
        
        len = j1939bs_SetupPgn64964(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time64964.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 65215  0x00FEBF - Wheel Speed Information - EBC2
    //---------------------------------------------------------------
    
    int             j1939bs_SetupPgn65215(
        J1939BS_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65215_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65215_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65215_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            *pData  = this->spn904 & 0xFF;
            ++pData;    // 1
            *pData  = (this->spn904 >> 8) & 0xFF;
            ++pData;    // 2
            *pData  = this->spn905 & 0xFF;
            ++pData;    // 3
            *pData  = this->spn906 & 0xFF;
            ++pData;    // 4
            *pData  = this->spn907 & 0xFF;
            ++pData;    // 5
            *pData  = this->spn908 & 0xFF;
            ++pData;    // 6
            *pData  = this->spn909 & 0xFF;
            ++pData;    // 7
            *pData  = this->spn910 & 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939bs_TransmitPgn65215(
        J1939BS_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;
        
        len = j1939bs_SetupPgn65215(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65215.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939bs_Validate(
        J1939BS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939BS) )
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


        if( !(obj_getSize(this) >= sizeof(J1939BS_DATA)) ) {
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


