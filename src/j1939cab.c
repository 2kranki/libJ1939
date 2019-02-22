// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939cab.c
 *	Generated 06/12/2017 17:43:12
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
#include <j1939cab_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    const
    J1939CA_PGN_ENTRY     ca_pgn57344_entry = {
        // PGN 57344  0x00E000 - Cab Message 1 - CM1
        &pgn57344_entry,
        (P_SRVCMSG_RTN)j1939cab_HandlePgn57344,
        NULL,
        (P_SETUP_MSG_RTN)j1939cab_SetupPgn57344,
        offsetof(J1939CAB_DATA, time57344),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61184_entry = {
        // PGN 61184  0x00EF00 - Proprietary A - PROPA
        &pgn61184_entry,
        (P_SRVCMSG_RTN)j1939cab_HandlePgn61184,
        NULL,
        NULL,
        0,                  // Offset of Timeout repeat xmt
        0,                  // Destination Address if applicable
        0,                  // Reserved
        0                   // ms Transmit Repeat
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61443_entry = {
        // PGN 61443  0x00F003 - Electronic Engine Controller 2 - EEC2
        &pgn61443_entry,
        (P_SRVCMSG_RTN)j1939cab_HandlePgn61443,
        NULL,
        (P_SETUP_MSG_RTN)j1939cab_SetupPgn61443,
        offsetof(J1939CAB_DATA, time61443),
        0,
        0,
        50
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn61444_entry = {
        // PGN 61444  0x00F004 - Electronic Engine Controller 1 - EEC1
        &pgn61444_entry,
        (P_SRVCMSG_RTN)j1939cab_HandlePgn61444,
        NULL,
        NULL,
        0,                  // Offset of Timeout repeat xmt
        0,                  // Destination Address if applicable
        0,                  // Reserved
        0                   // ms Transmit Repeat
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65217_entry = {
        // PGN 65217  0x00FEC1 - High Resolution Vehicle Distance - VDHR
        &pgn65217_entry,
        (P_SRVCMSG_RTN)j1939cab_HandlePgn65217,
        NULL,
        (P_SETUP_MSG_RTN)j1939cab_SetupPgn65217,
        offsetof(J1939CAB_DATA, time65217),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65261_entry = {
        // PGN 65261 FEED - Cruise Control/Vehicle Speed Setup - CCSS
        &pgn65261_entry,
        NULL, //FIXME: ??? (P_SRVCMSG_RTN)j1939cc_HandlePgn65261,
        NULL,
        NULL, //FIXME: ??? (P_MSGDATA_RTN)j1939cc_SetupPgn65261,
        0,
        0,
        0,
        0                       // On Request
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65265_entry = {
        // PGN 65265  0x00FEF1 - Cruise Control/Vehicle Speed - CCVS
        &pgn65265_entry,
        (P_SRVCMSG_RTN)j1939cab_HandlePgn65265,
        NULL,
        (P_SETUP_MSG_RTN)j1939cab_SetupPgn65265,
        offsetof(J1939CAB_DATA, time65265),
        0,
        0,
        100
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65269_entry = {
        // PGN 65269  0x00FEF5 - Ambient Conditions - AMB
        &pgn65269_entry,
        (P_SRVCMSG_RTN)j1939cab_HandlePgn65269,
        NULL,
        (P_SETUP_MSG_RTN)j1939cab_SetupPgn65269,
        offsetof(J1939CAB_DATA, time65269),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65271_entry = {
        // PGN 65271  0x00FEF7 - Vehicle Electrical Power #1 - VEP1
        &pgn65271_entry,
        (P_SRVCMSG_RTN)j1939cab_HandlePgn65271,
        NULL,
        (P_SETUP_MSG_RTN)j1939cab_SetupPgn65271,
        offsetof(J1939CAB_DATA, time65271),
        0,
        0,
        1000
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        //&ca_pgn0_entry,
        //&ca_pgn61442_entry,
        //&ca_pgn61445_entry,
        //&ca_pgn65252_entry,
        NULL
    };
    
    static
    const
    J1939CA_PGN_TABLE   rcvPgnTbl = {
        (sizeof(rcvPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &rcvPgnIndex
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY   *xmtPgnIndex[] = {
        &ca_pgn57344_entry,
        &ca_pgn61443_entry,
        &ca_pgn65217_entry,
        &ca_pgn65265_entry,
        &ca_pgn65261_entry,
        &ca_pgn65269_entry,
        &ca_pgn65271_entry,
        NULL
    };
    
    static
    const
    J1939CA_PGN_TABLE   xmtPgnTbl = {
        (sizeof(xmtPgnIndex)/sizeof(J1939CA_PGN_ENTRY *))-1,
        0,              // Reserved
        &xmtPgnIndex
    };
    
    
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            j1939cab_task_body(
        void            *pData
    )
    {
        //J1939CAB_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939CAB_DATA *     j1939cab_Alloc(
    )
    {
        J1939CAB_DATA   *this;
        uint32_t        cbSize = sizeof(J1939CAB_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939CAB_DATA *     j1939cab_New(
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939CAB_DATA       *this;
        
        this = j1939cab_Alloc( );
        if (this) {
            this = j1939cab_Init(this, pCAN, pSYS, spn2837, spn2838, spn2846);
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         j1939cab_getLastError(
        J1939CAB_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939cab_setLastError(
        J1939CAB_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        j1939cab_getPriority(
        J1939CAB_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939cab_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            j1939cab_setPriority(
        J1939CAB_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939cab_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        j1939cab_getSize(
        J1939CAB_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939cab_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = j1939cab__Assign(this,pOther);
     @endcode
     @param     this    J1939CAB object pointer
     @param     pOther  a pointer to another J1939CAB object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         j1939cab_Assign(
        J1939CAB_DATA		*this,
        J1939CAB_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !j1939cab_Validate(pOther) ) {
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
        j1939cab_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939cab_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939cab_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        j1939cab      *pCopy = j1939cab_Copy(this);
     @endcode
     @param     this    J1939CAB object pointer
     @return    If successful, a J1939CAB object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the J1939CAB object.
     */
    J1939CAB_DATA *     j1939cab_Copy(
        J1939CAB_DATA       *this
    )
    {
        J1939CAB_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = j1939cab_New(obj_getSize(this));
        if (pOther) {
            eRc = j1939cab_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939cab_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939cab_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939CAB_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939CAB_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        //j1939cab_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        j1939ca_Dealloc(this);          // Needed for inheritance
        //obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939cab_Disable(
        J1939CAB_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939cab_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return j1939cab_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939cab_setLastError(this, ERESULT_SUCCESS);
        return j1939cab_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939cab_Enable(
        J1939CAB_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939cab_setLastError(this, ERESULT_SUCCESS);
        return j1939cab_getLastError(this);
    }



    //---------------------------------------------------------------
    //          PGN 57344  0x00E000 - Cab Message 1 - CM1
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn57344(
        J1939CAB_DATA   *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
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
        if( !j1939cab_Validate(this) ) {
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
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 61184  0x00EF00 - Proprietary A - PROPA
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn61184(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint16_t        spnCmd;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pMsg) {
            pdu = j1939msg_getPDU(pMsg);
            pgn = j1939pdu_getPGN(pdu);
            
            spnCmd = pMsg->DATA.bytes[0] | (pMsg->DATA.bytes[1] << 8);
            switch (spnCmd) {
                case PROPA_CMD_SET_PARKING_BRAKE:
                    j1939cab_ParkingBrake(this, pMsg->DATA.bytes[2]);
                    break;
                    
                default:
                    break;
            }
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 61443  0x00F003 - Electronic Engine Controller 2 - EEC2
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn61443(
        J1939CAB_DATA   *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
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
        if( !j1939cab_Validate(this) ) {
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
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //  PGN 61444  0x00F004 - Electronic Engine Controller 1 - EEC1
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn61444(
        J1939CAB_DATA	*this,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    // PGN 65217  0x00FEC1 - High Resolution Vehicle Distance - VDHR
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn65217(
        J1939CAB_DATA   *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        
        
        
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //    PGN 65261 FEED - Cruise Control/Vehicle Speed Setup - CCSS
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn65261(
        J1939CAB_DATA   *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        
        
        
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //      PGN 65265 FEF1 - Cruise Control/Vehicle Speed - CCVS
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn65265(
        J1939CAB_DATA   *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        
        
        
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //         PGN 65269  0x00FEF5 - Ambient Conditions - AMB
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn65269(
        J1939CAB_DATA   *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        
        
        
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    // PGN 65271  0x00FEF7 - Vehicle Electrical Power #1 - VEP1
    //---------------------------------------------------------------
    
    bool            j1939cab_HandlePgn65271(
        J1939CAB_DATA   *this,
        J1939_MSG       *pMsg               // NULL == Timed Out
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pdu = j1939msg_getPDU(pMsg);
        pgn = j1939pdu_getPGN(pdu);
        
        
        
        
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //           H a n d l e  T i m e d  T r a n s m i t s
    //---------------------------------------------------------------
    
    bool            j1939cab_HandleTimedTransmits(
        J1939CAB_DATA	*this
    )
    {
        uint32_t        curTime;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        curTime = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        this->curTime = curTime;
       
        if ((curTime - this->time57344.msTime) >= this->time57344.msDelay) {
            j1939cab_TransmitPgn57344(this);
        }
        if ((curTime - this->time65265.msTime) >= this->time65265.msDelay) {
            j1939cab_TransmitPgn65265(this);
        }
#ifdef XYZZY
        if (this->fActive) {
            j1939er_HandlePgn0( this, NULL );
        }
#endif
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939CAB_DATA * j1939cab_Init(
        J1939CAB_DATA   *this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint32_t        cbSize = sizeof(J1939CAB_DATA);
        
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

        this = (OBJ_ID)j1939ca_Init(                        // Needed for Inheritance
                                    (J1939CA_DATA *)this,
                                    pCAN,
                                    pSYS,
                                    spn2837,
                                    spn2838,
                                    spn2846
                );
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939CAB);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance

        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939cab_Vtbl);
        
        j1939cab_setLastError(this, ERESULT_GENERAL_FAILURE);

        j1939ca_Setup((J1939CA_DATA *)this, J1939_CAB_CONTROLLER);
        //this->super.name.ECU = 0;
        this->super.name.FU = 12;
        this->super.name.FUI = 0;
        //FIXME: this->super.pRcvPgnTbl = &rcvPgntbl;
        //FIXME: this->super.pXmtPgnTbl = &xmtPgntbl;
        //FIXME: this->super.pTimedTransmit = (P_HANDLE_TIMED_TRANSMITS)&j1939cc_HandleTimedTransmits;
        
        // Default all SPNs to unsupported values.
        memset(
               &this->spnFirst,
               0xFF,
               (offsetof(J1939CAB_DATA,spnLast) - offsetof(J1939CAB_DATA,spnFirst)
                + sizeof(uint32_t))
               );
        //this->spn1481 = J1939_BRAKE_SYSTEM_CONTROLLER;
        
        this->time57344.msDefault = pgn57344_entry.msFreq;
        this->time57344.msDelay = pgn57344_entry.msFreq;
        this->time57344.pgn = 57344;
        
        this->time61443.msDefault = pgn61443_entry.msFreq;
        this->time61443.msDelay = pgn61443_entry.msFreq;
        this->time61443.pgn = 61443;
        
        this->time65217.msDefault = pgn65217_entry.msFreq;
        this->time65217.msDelay = pgn65217_entry.msFreq;
        this->time65217.pgn = 65217;
        
        this->time65265.msDefault = pgn65265_entry.msFreq;
        this->time65265.msDelay = pgn65265_entry.msFreq;
        this->time65265.pgn = 65265;
        
        this->time65269.msDefault = pgn65269_entry.msFreq;
        this->time65269.msDelay = pgn65269_entry.msFreq;
        this->time65269.pgn = 65269;
        
        this->time65271.msDefault = pgn65271_entry.msFreq;
        this->time65271.msDelay = pgn65271_entry.msFreq;
        this->time65271.pgn = 65271;
        
    #ifdef NDEBUG
    #else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(&this->spnFirst);
        BREAK_NOT_BOUNDARY4(&this->spn79);
        BREAK_NOT_BOUNDARY4(&this->spn917);
        BREAK_NOT_BOUNDARY4(&this->spnLast);
        BREAK_NOT_BOUNDARY4(sizeof(J1939CAB_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939cab_IsEnabled(
        J1939CAB_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939cab_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939cab_getLastError(this);
        }
        
        // Return to caller.
        j1939cab_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939cab_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r k i n g  B r a k e
    //---------------------------------------------------------------
    
    ERESULT     j1939cab_ParkingBrake(
        J1939CAB_DATA	*this,
        bool            fApplied
    )
    {
        uint8_t         spn70 = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (fApplied) {
            spn70 = 0b01;
        }
        if (spn70 == this->spn70) {
        }
        else {
            this->spn70 = spn70;
            j1939cab_TransmitPgn65265(this);
        }
        
        // Return to caller.
        j1939cab_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          j1939cab_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        J1939CAB_DATA   *this = objId;
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !j1939cab_Validate(this) ) {
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
                            return j1939cab_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return j1939cab_Enable;
                        }
                        break;

                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = j1939cab_ToDebugString(this,4);
     @endcode
     @param     this    J1939CAB object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939cab_ToDebugString(
        J1939CAB_DATA   *this,
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
        if( !j1939cab_Validate(this) ) {
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
                     "{%p(j1939cab) size=%d\n",
                     this,
                     j1939cab_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(j1939cab)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939cab_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 5 7 3 4 4   0xE000        CM1
    //---------------------------------------------------------------
    
    /* PGN 57344  0x00E000 - Cab Message 1 - CM1
     * Freq: 1000 ms
     * Priority: 6
     */
    int             j1939cab_SetupPgn57344(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = 254;
            pPDU->PS = 247;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn57344_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            //FIXME: NOT 57344
            //          // 0
            *pData  = this->spn114;
            ++pData;    // 1
            *pData  = this->spn115;
            ++pData;    // 2
            *pData  = this->spn167 & 0xFF;
            ++pData;    // 3
            *pData  = (this->spn167 >> 8) & 0xFF;
            ++pData;    // 4
            *pData  = this->spn168 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn168 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = this->spn158 & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn158 >> 8) & 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cab_TransmitPgn57344(
        J1939CAB_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cab_SetupPgn57344(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time57344.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 1 4 4 3   0xF003       EEC2
    //---------------------------------------------------------------
    
    // Electronic Engine Controller 2 - EEC2 -
    // Unused bits are set to 1.
    
    int             j1939cab_SetupPgn61443(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn61443_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn61443_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn61443_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0xC0;
            *pData |= this->spn558 & 0x3;
            *pData |= (this->spn559 & 0x3) << 2;
            *pData |= (this->spn1437 & 0x3) << 4;
            ++pData;    // 1
            *pData  = this->spn91;                   // Accelerator Pedal Position 1
            ++pData;    // 2
            *pData  = this->spn92;
            ++pData;    // 3
            *pData  = this->spn974;
            ++pData;    // 4
            *pData  = 0xFF;
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
    
    
    bool            j1939cab_TransmitPgn61443(
        J1939CAB_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cab_SetupPgn61443(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time61443.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 1 7   0xFEC1      VDHR
    //---------------------------------------------------------------
    
    /* High Resolution Vehicle Distance - VDHR -
     * Freq: 1000 ms
     * Priority: 6
     */
    int             j1939cab_SetupPgn65217(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65217_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65217_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65217_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn917 & 0xFF;
            ++pData;    // 1
            *pData  = (this->spn917 >> 8) & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn917 >> 16) & 0xFF;
            ++pData;    // 3
            *pData  = (this->spn917 >> 24) & 0xFF;
            ++pData;    // 4
            *pData  = this->spn918 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn918 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = (this->spn918 >> 16) & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn918 >> 24) & 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cab_TransmitPgn65217(
        J1939CAB_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cab_SetupPgn65217(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65217.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 1   0xFEED      CCSS
    //---------------------------------------------------------------
    
    /* CruiseControl/VehicleSpeedSetup - CCSS -
     * Freq: 0 ms
     * Priority: 6
     */
    int             j1939cab_SetupPgn65261(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65261_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65261_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65261_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn74;
            ++pData;    // 1
            *pData  = this->spn87;
            ++pData;    // 2
            *pData  = this->spn88;
            ++pData;    // 3
            *pData  = 0xFF;
            ++pData;    // 4
            *pData  = 0xFF;
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
    
    
    bool            j1939cab_TransmitPgn65261(
        J1939CAB_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cab_SetupPgn65261(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65261.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 5   0xFEF1      CCVS
    //---------------------------------------------------------------
    
    /* Cruise Control/Vehicle Speed - CCVS -
     * Freq: 100 ms
     * Priority: 6
     */
    int             j1939cab_SetupPgn65265(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65265_entry.pgn >> 8) & 0xFF;
            pPDU->PS = pgn65265_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65265_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = 0xC0;
            *pData |= (this->spn69 & 0x3);
            *pData |= (this->spn70 & 0x3) << 2;
            *pData |= (this->spn1633 & 0x3) << 4;
            ++pData;    // 1
            *pData  = this->spn84 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn84 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = 0;
            *pData |= (this->spn595 & 0x3);
            *pData |= (this->spn596 & 0x3) << 2;
            *pData |= (this->spn597 & 0x3) << 4;
            *pData |= (this->spn598 & 0x3) << 6;
            ++pData;    // 4
            *pData  = 0;
            *pData |= (this->spn599 & 0x3);
            *pData |= (this->spn600 & 0x3) << 2;
            *pData |= (this->spn601 & 0x3) << 4;
            *pData |= (this->spn602 & 0x3) << 6;
            ++pData;    // 5
            *pData  = (this->spn86 & 0xFF);
            ++pData;    // 6
            *pData  = 0;
            *pData |= (this->spn976 & 0x1F);
            *pData |= (this->spn527 & 0x7) << 5;
            ++pData;    // 7
            *pData  = 0;
            *pData |= (this->spn968 & 0x3);
            *pData |= (this->spn967 & 0x3) << 2;
            *pData |= (this->spn966 & 0x3) << 4;
            *pData |= (this->spn1237 & 0x3) << 6;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cab_TransmitPgn65265(
        J1939CAB_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cab_SetupPgn65265(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65265.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 6 9   0xFEF5        AMB
    //---------------------------------------------------------------
    
    /* Ambient Conditions - AMB -
     * Freq: 0 ms
     * Priority: 6
     */
    int             j1939cab_SetupPgn65269(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = (pgn65269_entry.pgn >> 8) & 0xFF ;
            pPDU->PS = pgn65269_entry.pgn & 0xFF;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65269_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            *pData  = this->spn108;
            ++pData;    // 1
            *pData  = this->spn170 & 0xFF;
            ++pData;    // 2
            *pData  = (this->spn170 >> 8) & 0xFF;
            ++pData;    // 3
            *pData  = this->spn171 & 0xFF;
            ++pData;    // 4
            *pData  = (this->spn171 >> 8) & 0xFF;
            ++pData;    // 5
            *pData  = this->spn172;
            ++pData;    // 6
            *pData  = this->spn79 & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn79 >> 8) & 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cab_TransmitPgn65269(
        J1939CAB_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cab_SetupPgn65269(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65269.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s m i t  P G N 6 5 2 7 1   0xFEF7       VEP1
    //---------------------------------------------------------------
    
    /* VehicleElectricalPower#1 - VEP1 -
     * Freq: 1000 ms
     * Priority: 6
     */
    int             j1939cab_SetupPgn65271(
        J1939CAB_DATA	*this,
        J1939_PDU       *pPDU,
        uint16_t        cData,
        uint8_t         *pData
    )
    {
        
        if (pPDU) {
            pPDU->PF = 254;
            pPDU->PS = 247;
            pPDU->SA = this->super.ca;
            pPDU->P  = pgn65271_entry.priority;
        }
        else {
            return 0;
        }
        
        if (pData) {
            if (cData < 8) {
                return 0;
            }
            //          // 0
            *pData  = this->spn114;
            ++pData;    // 1
            *pData  = this->spn115;
            ++pData;    // 2
            *pData  = this->spn167 & 0xFF;
            ++pData;    // 3
            *pData  = (this->spn167 >> 8) & 0xFF;
            ++pData;    // 4
            *pData  = this->spn168 & 0xFF;
            ++pData;    // 5
            *pData  = (this->spn168 >> 8) & 0xFF;
            ++pData;    // 6
            *pData  = this->spn158 & 0xFF;
            ++pData;    // 7
            *pData  = (this->spn158 >> 8) & 0xFF;
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return 8;
    }
    
    
    bool            j1939cab_TransmitPgn65271(
        J1939CAB_DATA	*this
    )
    {
        uint16_t        dlc = 8;
        uint8_t         data[8];
        J1939_PDU       pdu = {0};
        int             iRc;
        bool            fRc;
        
        iRc = j1939cab_SetupPgn65271(this, &pdu, dlc, data);
        if (iRc == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, pdu, dlc, &data);
        this->time65271.msTime = this->curTime;
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939cab_Validate(
        J1939CAB_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939CAB) )
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


        if( !(obj_getSize(this) >= sizeof(J1939CAB_DATA)) ) {
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


