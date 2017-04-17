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
 *              tions and forms the foundation for an ECU.
 *
 *              An ECU consists of one or more Controller Ap-
 *              plications. Each Controller Application normally
 *              goes through an address claim procedure before 
 *              they have an address that they can use for talking
 *              to other CAs.
 *
 *              These CAs may have predefined names and addresses
 *              which doesn't require them to go through the
 *              naming process.
 *
 *              Since all messages for the CA are funneled through
 *              this object, we handle the Data Link Support here
 *              as well including PGN Requests and Transport
 *              Protocol messages.
 *
 * Remarks
 *	**			Currently, this module only dispatches the in-
 *              coming messages to the appropriate CAs.
 *
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
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846,        // J1939 Industry Group (3 bits)
        bool            fIncludeER      // True == include a related Engine Retarder
    );
    
    
    J1939CAM_DATA * j1939cam_NewTransmission(
        OBJ_ID          pCAN,
        OBJ_ID          pSYS,
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
    
    
    J1939CA_DATA *  j1939cam_findCA(
        J1939CAM_DATA	*this,
        uint8_t         ca              // Claimed Address
    );
    
    
    OBJ_ID          j1939cam_getCAN(
        J1939CAM_DATA	*this
    );
    
    bool            j1939cam_setCAN(
        J1939CAM_DATA	*this,
        OBJ_ID          pValue
    );
    
    
    uint8_t         j1939cam_getNumCAs(
        J1939CAM_DATA	*this
    );
    
    
    OBJ_ID          j1939cam_getSYS(
        J1939CAM_DATA	*this
    );
    
    bool            j1939cam_setSYS(
        J1939CAM_DATA	*this,
        OBJ_ID          pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    bool            j1939cam_AddCA(
        J1939CAM_DATA	*this,
        OBJ_ID          pCA
    );
    
    
    J1939CA_DATA *  j1939cam_FindCA(
        J1939CAM_DATA	*this,
        uint8_t         ca              // Claimed Address
    );
    
    
    /*!
     Passed messages from a message source such as a CAN FIFO Receive
     Queue. This routine handles the message either internally or via
     its responder chain. It should be called about every 10ms even
     if a message is not available. A NULL message pointer and zero
     eid, tell the Handler to simply process any time transmitted
     messages.
     @param:    this    J1939CAM object pointer
     @param:    eid     Message EID
     @param:    pMsg    Message Pointer or NULL
     @return:   if successful, true otherwise, false
     @Warning:  This function must conform to P_SRVCMSG_RTN specs.
     */
    bool            j1939cam_HandleMessages(
        J1939CAM_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg
    );
    
    
    J1939CAM_DATA *	j1939cam_Init(
        J1939CAM_DATA	*this,
        OBJ_ID          pCAN,
        OBJ_ID          pSYS
    );
        
    
    /*!
     Transmist the given message reflecting it if necessary. Reflection
     is used primarily for debugging and is immediate.
     @param:    this    J1939CAM object pointer
     @param:    msDelay Message EID
     @param:    pMsg    Message Pointer or NULL
     @return:   if successful, true otherwise, false
     @Warning:  This function must conform to P_SRVCMSG_RTN specs.
     */
    bool            j1939cam_TransmitDelayedMsg(
        void            *pData,
        uint32_t        msDelay,
        J1939_MSG       *pMsg
    );
    
    
#ifdef	__cplusplus
};
#endif




#endif
