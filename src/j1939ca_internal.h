// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939ca_internal.h
 * Author: bob
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *
 * Created on September 26, 2014, 3:39 PM
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




#include        "j1939ca.h"
#include        "j1939tbl.h"


#ifndef J1939CA_INTERNAL_H
#define	J1939CA_INTERNAL_H 1


#ifdef	__cplusplus
extern "C" {
#endif

    
    typedef enum j1939ca_state_e {
        J1939CA_STATE_START=0,
        J1939CA_STATE_SEND_CLAIM_ADDRESS,
        J1939CA_STATE_WAIT_FOR_CLAIM_ADDRESS,
        J1939CA_STATE_SEND_CANNOT_CLAIM_ADDRESS,
        J1939CA_STATE_NORMAL_OPERATION,
        J1939CA_STATE_WAIT_FOR_COMMANDED_ADDRESS,
    } J1939CA_STATE;
    
    
    
    //                  Main Control j1939ca
    /* This control j1939ca resides only in memory and is used to provide
     * the information necessary to access the j1939ca data.
     */
    
    
#pragma pack(push, 1)
    struct j1939ca_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA            super;
        OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

        OBJ_DATA            *pSYS;
        OBJ_DATA            *pCAN;
        
        P_HANDLE_TIMED_TRANSMITS
                            pTimedTransmit;
        uint8_t             fTimedTransmit;
        uint8_t             rsvd8[3];
        
        P_SRVCMSG_RTN       pHandler;
        
        /* XmtMsg() is the routine called to transmit an 8-byte
         * message. All messages must be sent via this routine.
         */
        //P_XMTMSG_RTN        pXmtMsg;
        //OBJ_PTR             pXmtData;
        P_J1939_XMTRTN      pXmtMsgDL;
        OBJ_PTR             pXmtDataDL;
        
        uint32_t            startTime;
        
        uint8_t             ca;             // Claimed Address
        uint8_t             cs;             // CA Claimed State
        uint16_t            reserved16;
        const
        J1939CA_PGN_TABLE   *pRcvPgnTbl;
        const
        J1939CA_PGN_TABLE   *pXmtPgnTbl;
        
        // NAME Fields
        J1939_NAME          name;
        
        // Current Input Message Parameters
        // (All of the HandlePgnNNNNN()s and TransmitPgnNNNNN() assume
        // that these fields are set.)
        const
        J1939CA_PGN_ENTRY   *pCurEntry;
        J1939_PGN           curPgn;
        uint8_t             curDa;
        uint8_t             curSa;
        uint16_t            reserved16a;
        
    };
#pragma pack(pop)
    
    
    extern
    const
    J1939CA_VTBL    j1939ca_Vtbl;
    extern
    const
    struct j1939ca_class_data_s j1939ca_ClassObj;


    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/
    
    bool            j1939ca_setCAM(
        J1939CA_DATA	*cbp,
        J1939CAM_DATA   *pValue
    );
    
    
    bool			j1939ca_setClaimedAddress(
        J1939CA_DATA	*cbp,
        uint8_t         value
    );
  
    
    void            j1939ca_Dealloc(
        OBJ_ID          objId
    );

    
    bool            j1939ca_HandlePgn59392(
        J1939CA_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939ca_HandlePgn59904(
        J1939CA_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939ca_HandlePgn60928(
        J1939CA_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939ca_SetupPgn60928(
        J1939CA_DATA	*cbp,
        uint32_t        *pEid,
        uint16_t        cData,
        uint8_t         *pData
    );
    
    
    bool            j1939ca_TransmitPgn59392_NAK(
        J1939CA_DATA	*cbp,
        J1939_PGN       pgn                 // PGN being requested
    );
    
    
    bool            j1939ca_TransmitPgn60928(
        J1939CA_DATA	*cbp
    );
    
    
    bool            j1939ca_XmtMsgDL(
        J1939CA_DATA	*cbp,
        uint32_t        msDelay,
        J1939_PDU       pdu,
        uint16_t        cData,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    static
    bool            j1939ca_Validate(
        J1939CA_DATA      *cbp
    );
#endif
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* J1939CA_INTERNAL_H */

