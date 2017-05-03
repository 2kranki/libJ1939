// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   j1939ss.c
 *	Generated 04/08/2017 00:51:45
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
#include "j1939ss_internal.h"



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
        (P_SETUP_MSG_RTN)j1939ss_SetupPgn0,
        offsetof(J1939SS_DATA, startTime0),
        0,
        0,
        0
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     ca_pgn65098_entry = {
        // PGN 0  0x000000 - Torque/Speed Control 1 - TSC1
        &pgn0_entry,
        (P_SRVCMSG_RTN)j1939ss_HandlePgn65098,
        NULL,
        NULL,                // Message Data Constructor
        0,
        0,
        0
    };
    
    
    static
    const
    J1939CA_PGN_ENTRY     *rcvPgnIndex[] = {
        &ca_pgn65098_entry,
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
        &ca_pgn0_entry,
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
    void            j1939ss_task_body(
        void            *pData
    )
    {
        //J1939SS_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    J1939SS_DATA *     j1939ss_Alloc(
    )
    {
        J1939SS_DATA    *this;
        uint32_t        cbSize = sizeof(J1939SS_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    J1939SS_DATA *     j1939ss_New(
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        J1939SS_DATA       *this;
        
        this = j1939ss_Alloc( );
        if (this) {
            this = (OBJ_ID)j1939ss_Init(
                                        this,
                                        pCAN,
                                        pSYS,
                                        spn2837,
                                        spn2838,
                                        spn2846
                    );
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         j1939ss_getLastError(
        J1939SS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            j1939ss_setLastError(
        J1939SS_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

// Requested Torque / Torque Limit
uint8_t			j1939ss_getSpn518(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn518;
}


bool			j1939ss_setSpn518(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn518 = value;

	return true;
}



// Override Control Mode
uint8_t			j1939ss_getSpn695(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn695;
}


bool			j1939ss_setSpn695(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn695 = value;

	return true;
}



// Requested Speed Control Conditions
uint8_t			j1939ss_getSpn696(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn696;
}


bool			j1939ss_setSpn696(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn696 = value;

	return true;
}



// Override Control Mode Priority
uint8_t			j1939ss_getSpn897(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn897;
}


bool			j1939ss_setSpn897(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn897 = value;

	return true;
}



// Requested Speed / Speed Limit
uint16_t			j1939ss_getSpn898(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn898;
}


bool			j1939ss_setSpn898(
	J1939SS_DATA	*this,
	uint16_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn898 = value;

	return true;
}



// Transmission Requested Range Display
uint8_t			j1939ss_getSpn1849(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn1849;
}


bool			j1939ss_setSpn1849(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn1849 = value;

	return true;
}



// Transmission Requested Range Display
uint8_t			j1939ss_getSpn1850(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn1850;
}


bool			j1939ss_setSpn1850(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn1850 = value;

	return true;
}



// Transmission Shift Inhibit Indicator
uint8_t			j1939ss_getSpn1851(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn1851;
}


bool			j1939ss_setSpn1851(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn1851 = value;

	return true;
}



// Transmission Mode 1 Indicator
uint8_t			j1939ss_getSpn2536(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn2536;
}


bool			j1939ss_setSpn2536(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn2536 = value;

	return true;
}



// Transmission Mode 2 Indicator
uint8_t			j1939ss_getSpn2537(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn2537;
}


bool			j1939ss_setSpn2537(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn2537 = value;

	return true;
}



// Transmission Mode 3 Indicator
uint8_t			j1939ss_getSpn2538(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn2538;
}


bool			j1939ss_setSpn2538(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn2538 = value;

	return true;
}



// Transmission Mode 4 Indicator
uint8_t			j1939ss_getSpn2539(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn2539;
}


bool			j1939ss_setSpn2539(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn2539 = value;

	return true;
}



// Transmission Engine Crank Enable
uint8_t			j1939ss_getSpn2900(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn2900;
}


bool			j1939ss_setSpn2900(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn2900 = value;

	return true;
}



// Active Shift Console Indicator
uint8_t			j1939ss_getSpn2945(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn2945;
}


bool			j1939ss_setSpn2945(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn2945 = value;

	return true;
}



// Transmission Ready for Brake Release
uint8_t			j1939ss_getSpn3086(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn3086;
}


bool			j1939ss_setSpn3086(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn3086 = value;

	return true;
}



// Transmission Requested Gear Feedback
uint8_t			j1939ss_getSpn3289(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn3289;
}


bool			j1939ss_setSpn3289(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn3289 = value;

	return true;
}



// TSC1 Transmission Rate
uint8_t			j1939ss_getSpn3349(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn3349;
}


bool			j1939ss_setSpn3349(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn3349 = value;

	return true;
}



// TSC1 Control Purpose
uint8_t			j1939ss_getSpn3350(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->spn3350;
}


bool			j1939ss_setSpn3350(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->spn3350 = value;

	return true;
}



    uint16_t        j1939ss_getPriority(
        J1939SS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        j1939ss_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            j1939ss_setPriority(
        J1939SS_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        j1939ss_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = j1939ss__Assign(this,pOther);
     @endcode:
     @param:    this    J1939SS object pointer
     @param:    pOther  a pointer to another J1939SS object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         j1939ss_Assign(
        J1939SS_DATA		*this,
        J1939SS_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return j1939ss_getLastError(this);
        }
        if( !j1939ss_Validate(pOther) ) {
            DEBUG_BREAK();
            return j1939ss_getLastError(pOther);
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
        j1939ss_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        j1939ss_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return j1939ss_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        j1939ss      *pCopy = j1939ss_Copy(this);
     @endcode:
     @param:    this    J1939SS object pointer
     @return:   If successful, a J1939SS object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the J1939SS object.
     */
    J1939SS_DATA *     j1939ss_Copy(
        J1939SS_DATA       *this
    )
    {
        J1939SS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther =    j1939ss_New(
                        this->super.pCAN,
                        this->super.pSYS,
                        this->super.name.IDN,
                        this->super.name.MFG,
                        this->super.name.IG
                    );
        if (pOther) {
            eRc = j1939ss_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        j1939ss_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            j1939ss_Dealloc(
        OBJ_ID          objId
    )
    {
        J1939SS_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((J1939SS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        j1939ca_Dealloc(this);          // Needed for inheritance
        //obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         j1939ss_Disable(
        J1939SS_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            j1939ss_setLastError(this, ERESULT_INVALID_OBJECT);
            return j1939ss_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return j1939ss_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        j1939ss_setLastError(this, ERESULT_SUCCESS);
        return j1939ss_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         j1939ss_Enable(
        J1939SS_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return j1939ss_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        j1939ss_setLastError(this, ERESULT_SUCCESS);
        return j1939ss_getLastError(this);
    }



    //---------------------------------------------------------------
    //                  H a n d l e  P G N 0    0x000000    TSC1
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
    
    bool            j1939ss_HandlePgn0(
        J1939SS_DATA	*this,
        uint32_t        eid,
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
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (pMsg) {
            pdu.eid = eid;
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
            if ((1 == spn695) || (3 == spn695)) {
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
    //           H a n d l e  P G N 6 5 0 9 8   0xFE4A  ETC7
    //---------------------------------------------------------------
    
    // Electronic Transmission Controller 7
    // Transmission status information from the transmission controller
    // to network.
    
    bool            j1939ss_HandlePgn65098(
        J1939SS_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    )
    {
        J1939_PDU       pdu;
        J1939_PGN       pgn;
        uint8_t         spn1849;            // Transmission Requested Range Display
        //                                  // Flash State
        uint8_t         spn1850;            // Transmission Requested Range Display
        //                                  // Blank State
        uint8_t         spn1851;            // Transmission Shift Inhibit Indicator
        uint8_t         spn2536;            // Transmission Mode 1 Indicator
        uint8_t         spn2537;            // Transmission Mode 2 Indicator
        uint8_t         spn2538;            // Transmission Mode 3 Indicator
        uint8_t         spn2539;            // Transmission Mode 4 Indicator
        uint8_t         spn2900;            // Transmission Engine Crank Enable
        uint8_t         spn2945;            // Active Shift Console Indicator
        uint8_t         spn3086;            // Transmission Ready for Brake Release
        uint8_t         spn3289;            // Transmission Requested Gear Feedback
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (pMsg) {
            pdu.eid = eid;
            pgn = j1939pdu_getPGN(pdu);
            spn1850 = (pMsg->DATA.bytes[0] >> 4) & 0x3;
            spn1849 = (pMsg->DATA.bytes[0] >> 6) & 0x3;
            spn3086 = pMsg->DATA.bytes[1] & 0x3;
            spn2945 = (pMsg->DATA.bytes[1] >> 2) & 0x3;
            spn2900 = (pMsg->DATA.bytes[1] >> 4) & 0x3;
            spn1851 = (pMsg->DATA.bytes[1] >> 6) & 0x3;
            spn2539 = pMsg->DATA.bytes[2] & 0x3;
            spn2538 = (pMsg->DATA.bytes[2] >> 2) & 0x3;
            spn2537 = (pMsg->DATA.bytes[2] >> 4) & 0x3;
            spn2536 = (pMsg->DATA.bytes[2] >> 6) & 0x3;
            spn3289 = pMsg->DATA.bytes[3] & 0xFF;
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //           H a n d l e  T i m e d  T r a n s m i t s
    //---------------------------------------------------------------
    
    bool            j1939ss_HandleTimedTransmits(
        J1939SS_DATA	*this
    )
    {
        uint32_t        curTime;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ss_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        curTime = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        //TODO: maybe doesn't consider clock rollover
        if ((curTime - this->startTime0) >= this->tsc1Time) {
            j1939ss_TransmitPgn0(this);
        }
        //if (this->fActive) {
            //j1939ss_HandlePgn0( this, 0, NULL );
        //}
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    J1939SS_DATA *   j1939ss_Init(
        J1939SS_DATA    *this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    )
    {
        uint32_t        cbSize = sizeof(J1939SS_DATA);
        
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

        this = (OBJ_ID)j1939ca_Init(
                                (J1939CA_DATA *)this,
                                pCAN,
                                pSYS,
                                spn2837,
                                spn2838,
                                spn2846
                );    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_J1939SS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_J1939SS);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&j1939ss_Vtbl);
        
        j1939ss_setLastError(this, ERESULT_GENERAL_FAILURE);

        j1939ca_Setup((J1939CA_DATA *)this, J1939_SHIFT_CONSOLE_PRIMARY);
        //this->super.name.ECU = 0;
        this->super.name.FU = 12;
        this->super.name.FUI = 1;
        this->super.pRcvPgnTbl = &rcvPgntbl;
        this->super.pXmtPgnTbl = &xmtPgntbl;
        this->super.pTimedTransmit =
        (P_HANDLE_TIMED_TRANSMITS)&j1939ss_HandleTimedTransmits;
        
        this->tsc1Time = 10;
        
    #ifdef NDEBUG
    #else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "offsetof(eRc) = %lu\n", offsetof(J1939SS_DATA,eRc));
        //fprintf(stderr, "offsetof(spn84) = %lu\n", offsetof(J1939SS_DATA,spn84));
        fprintf(stderr, "offsetof(spn1637) = %lu\n", offsetof(J1939SS_DATA,tsc1Time));
        fprintf(stderr, "sizeof(J1939SS_DATA) = %lu\n", sizeof(J1939SS_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(&this->tsc1Time);
        BREAK_NOT_BOUNDARY4(sizeof(J1939SS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         j1939ss_IsEnabled(
        J1939SS_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !j1939ss_Validate(this) ) {
            DEBUG_BREAK();
            return j1939ss_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            j1939ss_setLastError(this, ERESULT_SUCCESS_TRUE);
            return j1939ss_getLastError(this);
        }
        
        // Return to caller.
        j1939ss_setLastError(this, ERESULT_SUCCESS_FALSE);
        return j1939ss_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939ss_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939SS object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     j1939ss_ToDebugString(
        J1939SS_DATA      *this,
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
        if( !j1939ss_Validate(this) ) {
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
                     "{%p(j1939ss)\n",
                     this
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
        j = snprintf(str, sizeof(str), " %p(j1939ss)}\n", this);
        AStr_AppendA(pStr, str);
        
        j1939ss_setLastError(this, ERESULT_SUCCESS);
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
    int             j1939ss_SetupPgn0(
        J1939SS_DATA	*this,
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
    
    
    bool            j1939ss_TransmitPgn0(
        J1939SS_DATA	*this
    )
    {
        uint32_t        dlc = 8;
        uint8_t         data[8] = {0};
        J1939_PDU       pdu = {0};
        bool            fRc = false;
        int             len;
        
        len = j1939ss_SetupPgn0(this, &pdu, dlc, data);
        if (len == 8) {
        }
        else {
            return false;
        }
        
        fRc = j1939ca_XmtMsgDL((J1939CA_DATA *)this, 0, pdu, dlc, &data);
        this->startTime0 = j1939ca_MsTimeGet((J1939CA_DATA *)this);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            j1939ss_Validate(
        J1939SS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_J1939SS) )
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


        if( !(obj_getSize(this) >= sizeof(J1939SS_DATA)) ) {
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


