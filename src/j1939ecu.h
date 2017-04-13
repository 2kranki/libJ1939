// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939 ECU (j1939ecu) Header
//****************************************************************
/*
 * Program
 *			J1939 ECU (j1939ecu)
 * Purpose
 *			This object provides an ECU which is made up of a CAM
 *          and multiple CAs.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/13/2017 Generated
 */


/*
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */





#include        <j1939_defs.h>
#include        <AStr.h>


#ifndef         J1939ECU_H
#define         J1939ECU_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939ecu_data_s	J1939ECU_DATA;    // Inherits from OBJ.

    typedef struct j1939ecu_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939ecu_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939ECU_DATA *);
    } J1939ECU_VTBL;



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
     @return:   pointer to j1939ecu object if successful, otherwise OBJ_NIL.
     */
    J1939ECU_DATA *     j1939ecu_Alloc(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    
    J1939ECU_DATA *     j1939ecu_New(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     j1939ecu_getLastError(
        J1939ECU_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     j1939ecu_Disable(
        J1939ECU_DATA		*this
    );


    ERESULT     j1939ecu_Enable(
        J1939ECU_DATA		*this
    );

   
    J1939ECU_DATA *   j1939ecu_Init(
        J1939ECU_DATA     *this
    );


    ERESULT     j1939ecu_IsEnabled(
        J1939ECU_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939ecu_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939ECU object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    j1939ecu_ToDebugString(
        J1939ECU_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939ECU_H */

