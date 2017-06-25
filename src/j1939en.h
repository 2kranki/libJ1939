/****************************************************************
 *                  J1939 Engine #1 CA (j1939en)
 ****************************************************************/
/*
 * Program
 *				J1939 Engine #1 CA (j1939en)
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
 *              The PGNs associated with the Engine Layer are:
 *                  (?)256* : spn 1852,1853,1854,1855
 *                  61443* : spn 91,92
 *                  61444* : spn 513
 *                  65262* : spn 110
 *                  65265* : spn 84
 *                  65270* : spn 102
 *
 *
 * Remarks
 *	1.			This object does not claim its name. It just assumes that it
 *              has it.
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



#ifndef J1939EN_H
#define J1939EN_H	1




#ifdef	__cplusplus
extern	"C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************
    
    //typedef struct j1939en_data_s	J1939EN_DATA;     // Inherits from J1939CA.
    //          defined in j1939_defs.h
    
    typedef struct j1939en_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;                  // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lru_object.c.
        // Properties:
        // Methods:
    } J1939EN_VTBL;
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    // Warning - See J1939CAM, but this function may not change.
    J1939EN_DATA * j1939en_Alloc(
    );
    
        
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            j1939en_setRpmRoutine(
        J1939EN_DATA    *this,
        void            (*pRpmRoutine)(void *, uint16_t),
        void            *pRpmData
    );
    
    
    bool			j1939en_setShiftExit(
        J1939EN_DATA	*this,
        P_VOIDEXIT12    pExit,
        void            *pData
    );
    
    
    // Engine Intercooler Temperature
    uint8_t			j1939en_getSpn52(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn52(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Two Speed Axle Switch
    uint8_t			j1939en_getSpn69(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn69(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Parking Brake Switch
    uint8_t			j1939en_getSpn70(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn70(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Wheel-Based Vehicle Speed
    uint16_t        j1939en_getSpn84(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn84(
        J1939EN_DATA	*this,
        uint16_t		value
    );


    // Cruise Control Set Speed
    uint8_t			j1939en_getSpn86(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn86(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Accelerator Pedal Position 1
    uint8_t			j1939en_getSpn91(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn91(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Percent Load At Current Speed
    uint8_t				j1939en_getSpn92(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn92(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Engine Coolant Temperature
    uint8_t				j1939en_getSpn110(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn110(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // 03 - Transmission Input Shaft Speed
    uint16_t				j1939en_getSpn161(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn161(
        J1939EN_DATA	*this,
        uint16_t			value
    );


    // Fuel Temperature
    uint8_t				j1939en_getSpn174(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn174(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Engine Oil Temperature 1
    uint16_t				j1939en_getSpn175(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn175(
        J1939EN_DATA	*this,
        uint16_t			value
    );


    // Turbo Oil Temperature
    uint16_t				j1939en_getSpn176(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn176(
        J1939EN_DATA	*this,
        uint16_t			value
    );


    // Engine Speed
    uint16_t				j1939en_getSpn190(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn190(
        J1939EN_DATA	*this,
        uint16_t			value
    );


    // 03 - Transmission Output Shaft Speed
    uint16_t				j1939en_getSpn191(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn191(
        J1939EN_DATA	*this,
        uint16_t			value
    );


    // Driver's Demand Engine - Percent Torque
    uint8_t				j1939en_getSpn512(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn512(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Actual Engine - Percent Torque
    uint8_t				j1939en_getSpn513(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn513(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Nominal Friction - Percent Torque
    uint8_t				j1939en_getSpn514(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn514(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Engine's Desired Operating Speed
    uint16_t				j1939en_getSpn515(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn515(
        J1939EN_DATA	*this,
        uint16_t			value
    );


    // Engine's Desired Operating Speed Asymmetry Adjustment
    uint8_t				j1939en_getSpn519(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn519(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // 03 - Transmission Current Gear
    uint8_t				j1939en_getSpn523(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn523(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // 03 - Transmission Selected Gear
    uint8_t				j1939en_getSpn524(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn524(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Cruise Control States
    uint8_t				j1939en_getSpn527(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn527(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Accelerator Pedal 1 Low Idle Switch
    uint8_t				j1939en_getSpn558(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn558(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Accelerator Pedal Kickdown Switch
    uint8_t				j1939en_getSpn559(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn559(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Transmission Shift In Process
    uint8_t				j1939en_getSpn574(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn574(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Cruise Control Active
    uint8_t				j1939en_getSpn595(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn595(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Cruise Control Enable Switch
    uint8_t				j1939en_getSpn596(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn596(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Brake Switch
    uint8_t				j1939en_getSpn597(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn597(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Clutch Switch
    uint8_t				j1939en_getSpn598(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn598(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Cruise Control Set Switch
    uint8_t				j1939en_getSpn599(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn599(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Cruise Control Coast (Decelerate) Switch
    uint8_t				j1939en_getSpn600(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn600(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Cruise Control Resume Switch
    uint8_t				j1939en_getSpn601(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn601(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Cruise Control Accelerate Switch
    uint8_t				j1939en_getSpn602(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn602(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Engine Torque Mode
    uint8_t				j1939en_getSpn899(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn899(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Engine Test Mode Switch
    uint8_t				j1939en_getSpn966(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn966(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Idle Decrement Switch
    uint8_t				j1939en_getSpn967(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn967(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Idle Increment Switch
    uint8_t				j1939en_getSpn968(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn968(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Remote Accelerator Pedal Position
    uint8_t				j1939en_getSpn974(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn974(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // PTO State
    uint8_t				j1939en_getSpn976(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn976(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Engine Protection System Approaching Shutdown
    uint8_t				j1939en_getSpn1109(
        J1939EN_DATA	*this
    );
    
    bool				j1939en_setSpn1109(
        J1939EN_DATA	*this,
        uint8_t			value
    );
    
    
    // Engine Protection System has Shutdown Engine
    uint8_t				j1939en_getSpn1110(
        J1939EN_DATA	*this
    );
    
    bool				j1939en_setSpn1110(
        J1939EN_DATA	*this,
        uint8_t			value
    );
    
    
    // Engine Intercooler Thermostat Opening
    uint8_t				j1939en_getSpn1134(
        J1939EN_DATA	*this
    );

    bool				j1939en_setSpn1134(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Engine Shutdown Override Switch
    uint8_t			j1939en_getSpn1237(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn1237(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Road Speed Limit Status
    uint8_t			j1939en_getSpn1437(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn1437(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // CA of Controlling Retarder Device
    uint8_t			j1939en_getSpn1480(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn1480(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Source Address of Controlling Device
    uint8_t			j1939en_getSpn1483(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn1483(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Cruise Control Pause Switch
    uint8_t			j1939en_getSpn1633(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn1633(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Intake Manifold 1 Air Temperature
    uint16_t		j1939en_getSpn1636(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn1636(
        J1939EN_DATA	*this,
        uint16_t			value
    );


    // Engine Coolant Temperature
    uint16_t		j1939en_getSpn1637(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn1637(
        J1939EN_DATA	*this,
        uint16_t			value
    );


    // Engine Starter Mode
    uint8_t			j1939en_getSpn1675(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn1675(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Engine Demand - Percent Torque
    uint8_t			j1939en_getSpn2432(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn2432(
        J1939EN_DATA	*this,
        uint8_t			value
    );


    // Estimated Engine Parasitic Losses
    uint8_t			j1939en_getSpn2978(
        J1939EN_DATA	*this
    );

    bool			j1939en_setSpn2978(
        J1939EN_DATA	*this,
        uint8_t			value
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    // j1939en_AddData adds Data to the end of the buffer.
    bool			j1939en_AddData(
        J1939EN_DATA	*this,
        uint16_t        size,
        void            *data
    );
    
   
    bool            j1939en_CylinderHeaters(
        J1939EN_DATA	*this,
        bool            fOnOff
    );
    
    
    bool            j1939en_EngineIgnition(
        J1939EN_DATA	*this,
        bool            fOnOff
    );
    
    
    bool            j1939en_EngineShutdownEngage(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_EngineShutdownDisengage(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_EngineStarter(
        J1939EN_DATA	*this,
        bool            fOnOff
    );
    
    
    bool            j1939en_HandleTimedTransmits(
        J1939EN_DATA	*this
    );
    
    
    // j1939en_Open calculates the needed buffer size, allocates an
    // area and sets up the control portion of the j1939en.
    // Warning - See J1939CAM, but this function may not change.
    J1939EN_DATA *	j1939en_Init(
        J1939EN_DATA	*this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint32_t        spn2837,        // J1939 Identity Number (21 bits)
        uint32_t        spn2838,        // J1939 Manufacturer Code (11 bits)
        uint32_t        spn2846         // J1939 Industry Group (3 bits)
    );
        

    bool            j1939en_TransmitPgn61443(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn61444(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65129(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65247(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65252(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65262(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65265(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65266(
        J1939EN_DATA	*this
    );
    
    
    bool            j1939en_TransmitPgn65279(
        J1939EN_DATA	*this
    );
    
    

    
#ifdef	__cplusplus
};
#endif




#endif
