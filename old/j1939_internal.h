// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/* 
 * File:   j1939_internal.h
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




#ifndef J1939_INTERNAL_H
#define	J1939_INTERNAL_H


#include        "j1939.h"
#include        "j1939cam.h"


#ifdef	__cplusplus
extern "C" {
#endif

    
    // Fixed Claimed Address (CA) Table
#pragma pack(push, 1)
    typedef struct j1939_ca_entry_s {
        uint8_t         ca;             // Fixed Claimed Address
        uint8_t         function;       // NAME - Function (SPN 2841) 8 bits
        uint8_t         funcInst;       // NAME - Function Instance (SPN 2839) 5 bits
        uint8_t         ecuInst;        // NAME - ECU Instance (SPN 2840) 3 bits
        OBJ_DATA        *pObj;
    } J1939_CA_ENTRY;
#pragma pack(pop)
    
    
    
    typedef enum j1939_spn_data_type_e {
        J1939_SPN_DATA_TYPE_BIT1_0=1,
        J1939_SPN_DATA_TYPE_BIT1_1,
        J1939_SPN_DATA_TYPE_BIT1_2,
        J1939_SPN_DATA_TYPE_BIT1_3,
        J1939_SPN_DATA_TYPE_BIT1_4,
        J1939_SPN_DATA_TYPE_BIT1_5,
        J1939_SPN_DATA_TYPE_BIT1_6,
        J1939_SPN_DATA_TYPE_BIT1_7,
        J1939_SPN_DATA_TYPE_BIT2_0,
        J1939_SPN_DATA_TYPE_BIT2_1,
        J1939_SPN_DATA_TYPE_BIT2_2,
        J1939_SPN_DATA_TYPE_BIT2_3,
        J1939_SPN_DATA_TYPE_BIT2_4,
        J1939_SPN_DATA_TYPE_BIT2_5,
        J1939_SPN_DATA_TYPE_BIT2_6,
        J1939_SPN_DATA_TYPE_BIT3_0,
        J1939_SPN_DATA_TYPE_BIT3_1,
        J1939_SPN_DATA_TYPE_BIT3_2,
        J1939_SPN_DATA_TYPE_BIT3_3,
        J1939_SPN_DATA_TYPE_BIT3_4,
        J1939_SPN_DATA_TYPE_BIT3_5,
        J1939_SPN_DATA_TYPE_BIT4_0,
        J1939_SPN_DATA_TYPE_BIT4_1,
        J1939_SPN_DATA_TYPE_BIT4_2,
        J1939_SPN_DATA_TYPE_BIT4_3,
        J1939_SPN_DATA_TYPE_BIT4_4,
        J1939_SPN_DATA_TYPE_BIT5_0,
        J1939_SPN_DATA_TYPE_BIT5_1,
        J1939_SPN_DATA_TYPE_BIT5_2,
        J1939_SPN_DATA_TYPE_BIT5_3,
        J1939_SPN_DATA_TYPE_BIT6_0,
        J1939_SPN_DATA_TYPE_BIT6_1,
        J1939_SPN_DATA_TYPE_BIT6_2,
        J1939_SPN_DATA_TYPE_BIT7_0,
        J1939_SPN_DATA_TYPE_BIT7_1,
    } J1939_SPN_DATA_TYPE;

    
    
    
    //                  Main Control j1939
    /* This control j1939 resides only in memory and is used to provide
     * the information necessary to access the j1939 data.
     */
    
    
#pragma pack(push, 1)
    struct j1939_data_s {
        /* Warning - 'super' must be first in this object!
         */
        OBJ_DATA            super;
        OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

        // Common Data
        J1939_CAN_VTBL      *pCAN;
        J1939_SYS_VTBL      *pSYS;

        J1939CAM_DATA       *pCAM;
        
        // Message Handlers/Responders
        uint32_t            cResponders;
        P_SRVCMSG_RTN       pResponders[4];
        OBJ_PTR             pRespondersData[4];
        
        // Message Transmission (Xmt)
        P_XMTMSG_RTN        pXmtMsg;
        OBJ_PTR             pXmtData;
        P_J1939_XMTRTN      pXmtMsgDL;
        OBJ_PTR             pXmtDataDL;
        
        // NAME related SPNs
        uint32_t            spn2837;            // Identity Number (21 bits)
        uint16_t            spn2838;            // Manufacturer Code (11 bits)
        uint8_t             spn2844;            // Arbitrary Address Capable (1 bit)
        uint8_t             spn2846;            // Industry Group (3 bits)
        
        // Engine related Temps
        uint8_t             spn110;             // Engine Coolant Temperature
        uint8_t             spn174;             // Fuel Temperature
        
        // Other
        uint8_t             port;
    };
#pragma pack(pop)
    
    
    
    extern
    const
    J1939_VTBL      j1939_Vtbl;

    


    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/
    
    bool            j1939_setCAM(
        J1939_DATA		*cbp,
        OBJ_ID          pValue
    );
    
    
    void            j1939_Dealloc(
        OBJ_ID          objId
    );
    
    
    bool            j1939_SetupDefaultFifos(
        J1939_DATA      *cbp
    );
    

    bool            j1939_SetupDefaultFilters(
        J1939_DATA      *cbp
    );


    bool            j1939_SetupDefaultMasks(
        J1939_DATA      *cbp
    );
    
    
    bool            j1939_SetupHandler(
        J1939_DATA      *cbp,
        uint16_t        cMaxResponders
    );
#ifdef NDEBUG
#else
    static
    bool            j1939_Validate(
        J1939_DATA      *cbp
    );
#endif
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* J1939_INTERNAL_H */

