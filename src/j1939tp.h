// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          J1939 Transport Protocol (j1939tp) Header
//****************************************************************
/*
 * Program
 *			J1939 Transport Protocol (j1939tp)
 * Purpose
 *			This object provides support for the transport Protocol
 *          in conjunction with a Controller Application (CA).
 *
 *          It consists of two tasks that are going on concurrently.
 *          First, the protocol task handles the required communi-
 *          cations with the destination CA. The second task is
 *          processing the individual packets of data.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/18/2017 Generated
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


#ifndef         J1939TP_H
#define         J1939TP_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct j1939tp_data_s	J1939TP_DATA;    // Inherits from OBJ.

    typedef struct j1939tp_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in j1939tp_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(J1939TP_DATA *);
    } J1939TP_VTBL;



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
     @return:   pointer to j1939tp object if successful, otherwise OBJ_NIL.
     */
    J1939TP_DATA *  j1939tp_Alloc(
    );
    
    
    J1939TP_DATA *  j1939tp_New(
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint8_t         ca
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJ_ID          j1939tp_getCAN(
        J1939TP_DATA	*this
    );
    
    bool            j1939tp_setCAN(
        J1939TP_DATA	*this,
        OBJ_ID          pValue
    );
    
    
    ERESULT     j1939tp_getLastError(
        J1939TP_DATA		*this
    );


    OBJ_ID          j1939tp_getSYS(
        J1939TP_DATA	*this
    );
    
    bool            j1939tp_setSYS(
        J1939TP_DATA	*this,
        OBJ_ID          pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         j1939tp_Disable(
        J1939TP_DATA	*this
    );


    ERESULT         j1939tp_Enable(
        J1939TP_DATA	*this
    );

   
    bool            j1939tp_HandleMessages(
        J1939TP_DATA	*this,
        uint32_t        eid,
        J1939_MSG       *pMsg           // if NULL, receive timed out
    );
    
    
    J1939TP_DATA *  j1939tp_Init(
        J1939TP_DATA    *this,
        OBJ_ID          *pCAN,
        OBJ_ID          *pSYS,
        uint8_t         ca
    );


    bool            j1939tp_IsBusy(
        J1939TP_DATA	*this
    );
    
    
    ERESULT         j1939tp_IsEnabled(
        J1939TP_DATA		*this
    );
    
 
    /*!
     If this object is waiting for work, set up the message to be
     transmitted in packets and start the protocol.
     @param:    this    J1939TP object pointer
     @return:   If successful, ERROR_SUCCESS, otherwise an ERESULT_* error code.
     */
    ERESULT         j1939tp_MessageTransmit(
        J1939TP_DATA	*this,
        J1939_PDU       pdu,
        uint16_t        cData,
        void            *pData
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = j1939tp_ToDebugString(this,4);
     @endcode:
     @param:    this    J1939TP object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    j1939tp_ToDebugString(
        J1939TP_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* J1939TP_H */

