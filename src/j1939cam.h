/****************************************************************
 *    J1939 Controller Application Manager (j1939cam) Support
 ****************************************************************/
/*
 * Program
 *				J1939 Controller Application Manager (j1939cam)
 * Purpose
 *				This object provides the Controller Application
 *              Management for the J1939 object. It handles all 
 *              its messages as well as other housekeeping func-
 *              tions and forms the foundation for the ECU.
 *
 *              It maintains a NAME and Claimed address.
 *
 *              Each Controller Application must go through an
 *              address claim procedure before they have an address
 *              that they can use for talking to other CAs.
 *
 *              Since all messages for the CA are funneled through
 *              this object, we handle the Data Link Support here
 *              as well including PGN Requests and Transport
 *              Protocol messages.
 *
 * Remarks
 *	**			None
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




#include        <j1939_defs.h>


#ifndef J1939CAM_H
#define J1939CAM_H	1


#ifdef	__cplusplus
extern	"C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************
    
    //typedef struct j1939cam_data_s	J1939CAM_DATA;     // Inherits from OBJ.
    //          defined in j1939_defs.h
    
    typedef struct j1939cam_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;                  // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lru_object.c.
        // Properties:
        // Methods:
    } J1939CAM_VTBL;
    
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    J1939CAM_DATA * j1939cam_Alloc(
    );
    
        
    J1939CAM_DATA * j1939cam_NewEngine(
        J1939_DATA      *pJ1939,
        P_XMTMSG_RTN    pReflectMsg,
        OBJ_ID          *pReflectData,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_ID          *pXmtData,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    );
    
    
    J1939CAM_DATA * j1939cam_NewTransmission(
        J1939_DATA      *pJ1939,
        P_XMTMSG_RTN    pReflectMsg,
        OBJ_ID          *pReflectData,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_ID          *pXmtData,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    );
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    J1939CA_DATA *  j1939cam_getCA(
        J1939CAM_DATA	*this,
        uint8_t         index           // Relative to zero
    );
    
    
    J1939_DATA *    j1939cam_getJ1939(
        J1939CAM_DATA	*this
    );
    
    
    uint8_t         j1939cam_getNumCAs(
        J1939CAM_DATA	*this
    );
    
    
    bool			j1939cam_setReflectMsg(
        J1939CAM_DATA	*this,
        P_XMTMSG_RTN    pXmtMsg,
        void            *pData
    );
    
    
    bool			j1939cam_setReflectMsgFlag(
        J1939CAM_DATA	*this,
        bool            value
    );
    
    
    bool			j1939cam_setXmtMsg(
        J1939CAM_DATA	*this,
        P_XMTMSG_RTN    pXmtMsg,
        void            *pData
    );

    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    bool            j1939cam_AddCA(
        J1939CAM_DATA	*this,
        OBJ_ID          pCA
    );
    
    
    bool            j1939cam_HandleMessages(
        J1939CAM_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    // j1939cam_Open calculates the needed buffer size, allocates an
    // area and sets up the control portion of the j1939cam.
    J1939CAM_DATA *	j1939cam_Init(
        J1939CAM_DATA	*this,
        J1939_DATA      *pJ1939,
        P_XMTMSG_RTN    pXmtMsg,
        OBJ_ID          pData
    );
        
    
    bool            j1939cam_TransmitDelayedMsg(
        void            *pData,
        uint32_t        msDelay,
        J1939_MSG       *pMsg
    );
    
    
#ifdef	__cplusplus
};
#endif




#endif
