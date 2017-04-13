// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   j1939cam_internal.h
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




#ifndef J1939CAM_INTERNAL_H
#define	J1939CAM_INTERNAL_H


#include        <j1939cam.h>
#include        "j1939ca_internal.h"


#ifdef	__cplusplus
extern "C" {
#endif

    
    typedef enum j1939cam_state_e {
        J1939CAM_STATE_START=0,
        J1939CAM_STATE_SEND_CLAIM_ADDRESS,
        J1939CAM_STATE_WAIT_FOR_CLAIM_ADDRESS,
        J1939CAM_STATE_SEND_CANNOT_CLAIM_ADDRESS,
        J1939CAM_STATE_NORMAL_OPERATION,
        J1939CAM_STATE_WAIT_FOR_COMMANDED_ADDRESS,
    } J1939CAM_STATE;

    typedef OBJ_ID (*OBJ_ALLOC)(void);
    typedef OBJ_ID (*OBJ_INIT)(OBJ_ID,OBJ_ID,uint16_t,P_XMTMSG_RTN,OBJ_ID);
    
    // Fixed Claimed Address (CA) Table
#pragma pack(push, 1)
    typedef struct j1939cam_ca_entry_s {
        uint8_t         ca;             // Fixed Claimed Address
        uint8_t         function;       // NAME - Function (SPN 2841) 8 bits
        uint8_t         funcInst;       // NAME - Function Instance (SPN 2839) 5 bits
        uint8_t         ecuInst;        // NAME - ECU Instance (SPN 2840) 3 bits
        OBJ_ALLOC       pAlloc;         // Allocation Routine
        OBJ_INIT        pInit;          // Initialization Routine
    } J1939CAM_CA_ENTRY;
#pragma pack(pop)
    
    
    

    
    //                  Main Control j1939cam
    /* This control j1939cam resides only in memory and is used to provide
     * the information necessary to access the j1939cam data.
     */
    
    
#pragma pack(push, 1)
    struct j1939cam_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA            super;
        OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

        OBJ_DATA            *pSYS;
        OBJ_DATA            *pCAN;
        
        bool                (*setWaitTime)( void *, uint32_t );
        void                *pSetTimeData;
        uint32_t            normalWaitTime;

        P_XMTMSG_RTN        pReflectMsg;
        OBJ_PTR             pReflectData;
        
        J1939CA_DATA        *pCAs[4];
        uint8_t             cCAs;
        uint8_t             fReflectMsg;
        uint8_t             reservered8[3];
        
    };
#pragma pack(pop)
    
    
    extern
    const
    J1939CAM_VTBL   j1939cam_Vtbl;
    


    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/
    
    void            j1939cam_Dealloc(
        OBJ_ID          objId
    );

    
    bool            j1939cam_HandlePgn59392(
        J1939CAM_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cam_HandlePgn59904(
        J1939CAM_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cam_HandlePgn60928(
        J1939CAM_DATA	*cbp,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    bool            j1939cam_TransmitPGN60928(
        J1939CAM_DATA	*cbp,
        uint8_t         sa,             // Source Address
                                        //      254 == Cannot Claim Address Msg
                                        //      otherwise supply claimed address
        uint8_t         da              // Destination Address
                                        //      255 == General Broadcast                                             
    );
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* J1939CAM_INTERNAL_H */

