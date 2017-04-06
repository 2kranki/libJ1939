// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/* 
 * File:   j1939dl_internal.h
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




#include        "j1939dl.h"


#ifndef J1939DL_INTERNAL_H
#define	J1939DL_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif

    
    //                  Main Control j1939dl
    /* This control j1939dl resides only in memory and is used to provide
     * the information necessary to access the j1939dl data.
     */
    
    
#pragma pack(push, 1)
    struct j1939dl_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA            super;
        OBJ_IUNKNOWN        *pSuperVtbl;      // Needed for Inheritance

        uint16_t            maxLayers;
        uint16_t            curLayers;
        //RECEIVE_HANDLER     *pHandlers;

        P_XMTMSG_RTN        pXmtMsg;
        OBJ_PTR             pXmtData;
        
        uint8_t             ca;     // Claimed Address
        uint8_t             reserved8;
        
        // NAME Fields
        uint8_t             fu;     //  8 bits - Function
        uint8_t             fi;     //  5 bits - Function Instance
        uint8_t             ecu;    //  3 bits - ECU Instance
        uint8_t             ig;     //  3 bits - Industry Group
        uint8_t             vs;     //  7 bits - Vehicle System
        uint8_t             vsi;    //  4 bits - Vehicle System Instance
        uint16_t            mc;     // 11 bits - Manufacturer Code
        uint16_t            reserved16;
        uint32_t            idn;    // 21 bits - Identity Number
        
    };
#pragma pack(pop)
    
    
    extern
    const
    J1939DL_VTBL    j1939dl_Vtbl;
    


    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/
    
    void            j1939dl_Dealloc(
        OBJ_ID          objId
    );
    
    bool            j1939dl_TransmitPGN60928(
        J1939DL_DATA	*cbp,
        uint8_t         da                      // Destination Address
   );
    
    
    void *			j1939dl_UnusedDataPtr(
        J1939DL_DATA		*
    );
    
#ifdef NDEBUG
#else
    static
    bool            j1939dl_Validate(
        J1939DL_DATA      *cbp
    );
#endif
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* J1939DL_INTERNAL_H */

