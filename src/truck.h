// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          TRUCK Console Transmit Task (truck) Header
//****************************************************************
/*
 * Program
 *			Separate truck (truck)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate truck to run things without complications
 *          of interfering with the main truck. A truck may be 
 *          called a truck on other O/S's.
 *
 * Remarks
 *	1.      Things like Cylinder Heaters, Starter, Ignition and
 *          accelerator are hard wired to various truck components.
 *          For instance, the Starter is hard wired to the engine
 *          and the transmission. We provide direct access to this
 *          hard-wired entities in each of the CAs that need them
 *          in two ways. First, we provide direct methods and second,
 *          we provide Proprietary A messages that are generally
 *          issued by truck and handled in each of the components
 *          that would be normally hard-wired.
 *  2.      130,500 BTU per US gallon (36.4 MJ/L) for diesel
 *
 * History
 *	06/12/2017 Generated
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
#include        <AStr.h>


#ifndef         TRUCK_H
#define         TRUCK_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct truck_data_s	TRUCK_DATA;    // Inherits from OBJ.

    typedef struct truck_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in truck_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TRUCK_DATA *);
    } TRUCK_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return:   pointer to truck object if successful, otherwise OBJ_NIL.
     */
    TRUCK_DATA *     truck_Alloc(
        void
    );
    
    
    TRUCK_DATA *     truck_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        truck_getFuelAmount(
        TRUCK_DATA      *this
    );
    
    bool            truck_setFuelAmount(
        TRUCK_DATA      *this,
        uint32_t        value
    );
    
    
    uint32_t        truck_getFuelCapacity(
        TRUCK_DATA      *this
    );
    
    bool            truck_setFuelCapacity(
        TRUCK_DATA      *this,
        uint32_t        value
    );
    
    
    ERESULT     truck_getLastError(
        TRUCK_DATA		*this
    );


    uint32_t        truck_getWeightLoad(
        TRUCK_DATA      *this
    );
    
    bool            truck_setWeightLoad(
        TRUCK_DATA      *this,
        uint32_t        value
    );
    
    
    uint32_t        truck_getWeightTractor(
        TRUCK_DATA      *this
    );
    
    bool            truck_setWeightTractor(
        TRUCK_DATA      *this,
        uint32_t        value
    );
    
    
    uint32_t        truck_getWeightTrailer(
        TRUCK_DATA      *this
    );
    
    bool            truck_setWeightTrailer(
        TRUCK_DATA      *this,
        uint32_t        value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Accelerator pedal simulation by percentage.
     @param     this    TRUCK object pointer
     @param     percent a value of 0 - 99 representing the amount of downward
                        movement made on the accelerator pedal
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error code.
     */
    ERESULT         truck_Accelerator(
        TRUCK_DATA		*this,
        uint16_t        percent         // 0 - 99, 0 == idle
    );
    
    
    /*!
     This recreates the operator turning on/off the cylinder heaters.
     @param     this    TRUCK object pointer
     @param     fOn     true == Opertor turned on the cylinder heaters, false == Operator
                        turned off the cylinder heaters.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error code.
     */
    ERESULT     truck_Ignition(
                               TRUCK_DATA		*this,
                               bool            fOn
                               );
    
    
    ERESULT     truck_Disable(
        TRUCK_DATA		*this
    );


    ERESULT     truck_Enable(
        TRUCK_DATA		*this
    );

   
    /*!
     This recreates the operator turning on/off the ignition.
     @param     this    TRUCK object pointer
     @param     fOn     true == Opertor turned on ignition, false == Operator turned
                        off the ignition.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error code.
     */
    ERESULT     truck_Ignition(
        TRUCK_DATA		*this,
        bool            fOn
    );
    
    
    TRUCK_DATA *   truck_Init(
        TRUCK_DATA     *this
    );


    ERESULT     truck_IsEnabled(
        TRUCK_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     @param     this    TRUCK object pointer
     @param     fApplied true == Applied parking brake, false == Released parking brake
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error code.
     */
    ERESULT     truck_ParkingBrake(
        TRUCK_DATA		*this,
        bool            fApplied
    );
    
    
    /*!
     This recreates the operator turning on/off the starter.
     @param     this    TRUCK object pointer
     @param     fOn     true == Opertor turned on the starter, false == Operator turned
                        off the starter.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error code.
     */
    ERESULT     truck_Starter(
        TRUCK_DATA		*this,
        bool            fOn
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = truck_ToDebugString(this,4);
     @endcode
     @param     this    TRUCK object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    truck_ToDebugString(
        TRUCK_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TRUCK_H */

