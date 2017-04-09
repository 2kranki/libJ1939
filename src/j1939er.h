/****************************************************************
 *              J1939 Engine Retarder CA (j1939er)
 ****************************************************************/
/*
 * Program
 *				J1939 Engine Retarder CA (j1939er)
 * Purpose
 *				This object provides the Engine Status Support
 *              for the J1939 object. The CA associated with this
 *              object should insure that the internal Claimed
 *              Address is kept up to date.
 *
 *              To support these PGNs, the CA must call the
 *              HandleMessage() method fairly consistently.
 *              One message is expected every 50ms. Others are
 *              at larger intervals.
 *              
 *              The PGNs associated with the Engine Retarder are:
 *                  0 TSC1 : spn 695, 897,518 (rcv from Transmission (SA == 3))
 *                  61440 ERC1 : spn 571,520  (xmt)
 *                  65249 RC :   spn  (xmt)
 *
 *              An engine retarder (compression or exhaust) is required on Eaton
 *              AutoShift 10 and 18-Speed and 13-Speed UltraShift transmissions. 
 *              It is recommended on the 10-Speed UltraShift transmission.
 *
 *              1. The transmission sends J-1939 Torque/Speed Control 1 (TSC1) 
 *                  torque control commands to the engine retarder (compression 
 *                  or exhaust) when deceleration assistance during a shift is 
 *                  required. The transmission automatically detects the retarder
 *                  source address (compression or exhaust) and addresses the 
 *                  TSC1 accordingly. If both compression and exhaust are present,
 *                  the transmission will address exhaust only.
 *              2. The engine retarder shall respond to TSC1 control commands as 
 *                  indicated by Actual Retarder Percent torque within 50 msec 
 *                  of the TSC1 command.
 *              3. The engine retarder shall respond to TSC1 commands regardless 
 *                  of the status of the engine brake control switches on the dash.
 *              4. The engine retarder shall affect the engine deceleration rate 
 *                  within 250 msec to 300 msec of the request. Longer response 
 *                  times will adversely affect the transmission’s upshift capa-
 *                  bilities on a grade and may limit applications to grades 8% 
 *                  and lower. Response times greater the 500 msec are not acceptable.
 *              5. The engine retarder shall respond to zero percent torque control 
 *                  command by turning off the engine brake within 250 msec. Longer 
 *                  delay times to turn off may cause harsh gear engagements and 
 *                  loss of vehicle speed.
 *              6. The engine shall have a minimum deceleration rate of 1000 rpm/sec
 *                  with the engine retarder at 100%. The engine is disengaged from
 *                  the driveline and is virtually unloaded.
 *              7. The recommended practice is for the exhaust brake on/off switches
 *                  to be wired in the engine ECM separately from the exhaust brake 
 *                  solenoid. Failure to comply with this recommended practice can 
 *                  cause Eaton AutoShift/UltraShift trans- missions to miss shifts 
 *                  when the exhaust brake is required. For more information contact 
 *                  Eaton Application Engineering and refer to the J-1939 Engine 
 *                  Requirements for Eaton Automated Transmissions.
 *
 * Remarks
 *	1.			None
 * References
 *		"J1939-21 Data Link Layer", SAE, DEC 2006
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


#ifndef J1939ER_H
#define J1939ER_H	1



#ifdef	__cplusplus
extern	"C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************
    
    typedef struct j1939er_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939ca_object.c.
        // Properties:
        // Methods:
    } J1939ER_VTBL;
    
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    // Warning - See J1939CAM, but this function may not change.
    J1939ER_DATA * j1939er_Alloc(
    );
    
        
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    // Wheel-Based Vehicle Speed
    uint16_t				j1939er_getSpn84(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn84(
        J1939ER_DATA	*this,
        uint16_t			value
    );


    // Engine Oil Temperature 1
    uint16_t				j1939er_getSpn175(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn175(
        J1939ER_DATA	*this,
        uint16_t			value
    );


    // Turbo Oil Temperature
    uint16_t				j1939er_getSpn176(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn176(
        J1939ER_DATA	*this,
        uint16_t			value
    );


    // Engine Speed
    uint16_t				j1939er_getSpn190(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn190(
        J1939ER_DATA	*this,
        uint16_t			value
    );


    // Engine's Desired Operating Speed
    uint16_t				j1939er_getSpn515(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn515(
        J1939ER_DATA	*this,
        uint16_t			value
    );


    // Actual Retarder - Percent Torque
    uint8_t				j1939er_getSpn520(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn520(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Retarder Enable - Brake Assist Switch
    uint8_t				j1939er_getSpn571(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn571(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Retarder Enable - Brake Assist Switch
    uint8_t				j1939er_getSpn572(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn572(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Retarder Torque Mode
    uint8_t				j1939er_getSpn900(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn900(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Engine Coolant Load Increase
    uint8_t				j1939er_getSpn1082(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1082(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Intended Retarder Percent Torque
    uint8_t				j1939er_getSpn1085(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1085(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // CA of Controlling Retarder Device
    uint8_t				j1939er_getSpn1480(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1480(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Intake Manifold 1 Air Temperature
    uint16_t				j1939er_getSpn1636(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1636(
        J1939ER_DATA	*this,
        uint16_t			value
    );


    // Engine Coolant Temperature
    uint16_t				j1939er_getSpn1637(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1637(
        J1939ER_DATA	*this,
        uint16_t			value
    );


    // Retarder requesting Brake Light
    uint8_t				j1939er_getSpn1667(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1667(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Drivers Demand Retarder - Percent Torque
    uint8_t				j1939er_getSpn1715(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1715(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Retarder Selection - non-engine
    uint8_t				j1939er_getSpn1716(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1716(
        J1939ER_DATA	*this,
        uint8_t			value
    );


    // Actual Maximum Available Retarder
    uint8_t				j1939er_getSpn1717(
        J1939ER_DATA	*this
    );

    bool				j1939er_setSpn1717(
        J1939ER_DATA	*this,
        uint8_t			value
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    // j1939er_AddData adds Data to the end of the buffer.
    bool			j1939er_AddData(
        J1939ER_DATA	*this,
        uint16_t        size,
        void            *data
    );
    
   
    bool            j1939er_HandleTimedTransmits(
        J1939ER_DATA	*this
    );
    
    
    // j1939er_Open calculates the needed buffer size, allocates an
    // area and sets up the control portion of the j1939er.
    // Warning - See J1939CAM, but this function may not change.
    J1939ER_DATA *	j1939er_Init(
        J1939ER_DATA	*this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint16_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint8_t         spn2846         // J1939 Industry Group (3 bits)
    );
        

    bool            j1939er_TransmitPgn61440(
        J1939ER_DATA	*this
    );
    
    
    bool            j1939er_TransmitPgn65249(
        J1939ER_DATA	*this
    );
    
        
    

    
#ifdef	__cplusplus
};
#endif




#endif
