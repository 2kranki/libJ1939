//
//
//  main.m
//  genGetterSetter
//
//  Created by bob on 4/8/17.
//


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


#include    <cmn_defs.h>
#include    <AStr.h>
#include    <dbCsv.h>
#include    <path.h>
#include    <trace.h>


//===============================================================
//                          D a t a
//===============================================================

typedef struct options_s {
    int             fDebug;
    int             fQuiet;
    int             verbose;
    int             genType;
    int             fSPN;
    const
    char            *pFunc;
    const
    char            *pName;
    const
    char            *pNameUpper;
    const
    char            *pArg1;
    const
    char            *pArg2;
    const
    char            *pArg3;
    const
    char            *pArg4;
} OPTIONS;


static
OPTIONS         options = {0};
static
ASTR_DATA       *pObjName = OBJ_NIL;
static
ASTR_DATA       *pObjData = OBJ_NIL;        // Upper case of ObjName
static
PATH_DATA		*pProgramName = OBJ_NIL;
static
OBJARRAY_DATA   *pRecords = OBJ_NIL;





//===============================================================
//                      F u n c t i o n s
//===============================================================

bool            genBody(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc
);

bool            genHeader(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc
);

bool            parseArgs(
    int             argc,
    const
    char            *argv[],
    OPTIONS         *pOptions
);

bool            readCSV(
    const
    char            *pFilePath
);

void			show_usage(
    const
    char            *pMsg
);



//---------------------------------------------------------------
//                  c r e a t e  M a s k
//---------------------------------------------------------------

char *          createMask(
    ASTR_DATA       *pStrSize
)
{
    const
    char            *pSize = AStr_getData(pStrSize);
    int             i;
    int             size;
    char            wrkstr[64];
    
    size = atoi(pSize);
    wrkstr[0] = '0';
    wrkstr[1] = 'b';
    wrkstr[2] = '\0';
    
    for (i=0; i<size; ++i) {
        strcat(wrkstr, "1");
    }
    
    return str_DupA(wrkstr);
}


char *          createMaskReg(
    ASTR_DATA       *pStrSize,
    ASTR_DATA       *pStrShift
)
{
    const
    char            *pSize = AStr_getData(pStrSize);
    const
    char            *pShift = AStr_getData(pStrShift);
    int             i;
    int             cSize;
    int             cShift;
    char            wrkstr[64];
    
    cSize = atoi(pSize);
    cShift = atoi(pShift);
    wrkstr[0] = '0';
    wrkstr[1] = 'b';
    wrkstr[2] = '\0';
    
    for (i=0; i<cSize; ++i) {
        strcat(wrkstr, "1");
    }
    for (i=0; i<cShift; ++i) {
        strcat(wrkstr, "0");
    }
    
    return str_DupA(wrkstr);
}



//---------------------------------------------------------------
//                     g e n  B o d y
//---------------------------------------------------------------

bool            genBody(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc
)
{
    const
    char            *pFieldType = AStr_getData(pStrType);
    const
    char            *pFieldName = AStr_getData(pStrName);
    const
    char            *pDescription = AStr_getData(pStrDesc);
    bool            fObj = false;
    
    if (AStr_CompareRightA(pStrType, "_DATA *") == ERESULT_SUCCESS_EQUAL) {
        fObj = true;
    }
    if (strlen(pDescription)) {
        fprintf(stdout, "\t// %s\n", pDescription);
    }
    if (options.fSPN) {
        fprintf(stdout, "\t%s\t\t\t%s_getSpn%s(\n",
                pFieldType,
                options.pName,
                pFieldName
                );
    }
    else {
        fprintf(stdout, "\t%s\t\t\t%s_get%s(\n",
                pFieldType,
                options.pName,
                pFieldName
                );
    }
    fprintf(stdout, "\t\t%s_DATA\t*this\n", options.pNameUpper);
    fprintf(stdout, "\t)\n{\n\n");
    fprintf(stdout, "\t#ifdef NDEBUG\n");
    fprintf(stdout, "\t#else\n");
    fprintf(stdout, "\t\tif (%s_Validate(this)) {\n", options.pName);
    fprintf(stdout, "\t\tDEBUG_BREAK();\n");
    if (fObj) {
        fprintf(stdout, "\t\treturn OBJ_NIL;\n");
    }
    else {
        fprintf(stdout, "\t\treturn 0;\n");
    }
    fprintf(stdout, "\t}\n\t#endif\n\n");
    if (options.fSPN) {
        fprintf(stdout, "\t\treturn this->spn%s;\n", pFieldName);
    }
    else {
        fprintf(stdout, "\t\treturn this->%s;\n", pFieldName);
    }
    fprintf(stdout, "\t}\n\n\n");
    
    if (options.fSPN) {
        fprintf(stdout, "\tbool\t\t\t%s_setSpn%s(\n",
                options.pName,
                pFieldName
                );
    }
    else {
        fprintf(stdout, "\tbool\t\t\t%s_set%s(\n",
                options.pName,
                pFieldName
                );
    }
    fprintf(stdout, "\t\t%s_DATA\t*this,\n", options.pNameUpper);
    fprintf(stdout, "\t\t%s\t\t\tvalue\n", pFieldType);
    fprintf(stdout, "\t)\n{\n\n");
    fprintf(stdout, "\t#ifdef NDEBUG\n");
    fprintf(stdout, "\t#else\n");
    fprintf(stdout, "\t\tif (%s_Validate(this)) {\n", options.pName);
    fprintf(stdout, "\t\tDEBUG_BREAK();\n");
    if (fObj) {
        fprintf(stdout, "\t\t\treturn OBJ_NIL;\n");
    }
    else {
        fprintf(stdout, "\t\t\treturn 0;\n");
    }
    fprintf(stdout, "\t\t}\n\t#endif\n\n");
    if (fObj) {
        fprintf(stdout, "\t\tobj_Retain(value);\n");
        if (options.fSPN) {
            fprintf(stdout, "\t\tif (this->spn%s) {\n", pFieldName);
            fprintf(stdout, "\t\t\tobj_Release(this->spn%s);\n", pFieldName);
            fprintf(stdout, "\t\t\t//this->spn%s = OBJ_NIL;\n\t\t}\n", pFieldName);
        }
        else {
            fprintf(stdout, "\t\tif (this->%s) {\n", pFieldName);
            fprintf(stdout, "\t\t\tobj_Release(this->%s);\n", pFieldName);
            fprintf(stdout, "\t\t\t//this->%s = OBJ_NIL;\n\t\t}\n", pFieldName);
        }
    }
    if (options.fSPN) {
        fprintf(stdout, "\t\tthis->spn%s = value;\n", pFieldName);
    }
    else {
        fprintf(stdout, "\t\tthis->%s = value;\n", pFieldName);
    }
    fprintf(stdout, "\n\t\treturn true;\n\t}\n\n\n\n");
    
    return true;
}



//---------------------------------------------------------------
//                     g e n  F u n c  E x t r a c t
//---------------------------------------------------------------

bool            genFuncExtract(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc,
    ASTR_DATA       *pStrOffset,
    ASTR_DATA       *pStrSize,
    ASTR_DATA       *pStrShift
)
{
    char            *pMask;
    int32_t         iOffset = (int32_t)AStr_ToInt64(pStrOffset);
    int32_t         iShift = (int32_t)AStr_ToInt64(pStrShift);
    //int32_t         iSize = (int32_t)AStr_ToInt64(pStrSize);
    
    pMask = createMask(pStrSize);
    
    if (iShift) {
        fprintf(stdout, "\tthis->%s = (data[%d] >> %d) & %s;\n",
                AStr_getData(pStrName),
                iOffset,
                iShift,
                pMask
        );
    }
    else {
        fprintf(stdout, "\tthis->%s = data[%d] & %s;\n",
                AStr_getData(pStrName),
                iOffset,
                pMask
        );
    }
    
    if (pMask) {
        mem_Free(pMask);
        pMask = NULL;
    }
    return true;
}



//---------------------------------------------------------------
//                     g e n  F u n c  S e t u p
//---------------------------------------------------------------

bool            genFuncSetup(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc,
    ASTR_DATA       *pStrOffset,
    ASTR_DATA       *pStrSize,
    ASTR_DATA       *pStrShift
)
{
    char            *pMask;
    int32_t         iOffset = (int32_t)AStr_ToInt64(pStrOffset);
    int32_t         iShift = (int32_t)AStr_ToInt64(pStrShift);
    int32_t         iSize = (int32_t)AStr_ToInt64(pStrSize);
    int32_t         chrW;
    
    pMask = createMask(pStrSize);
    
    chrW = AStr_CharGetW(pStrName, 2);
    if ((chrW == 'b') || (chrW == 'x')) {
        if (iShift) {
            fprintf(stdout, "\t\t\tpData[%d] &=  0xFF - (%s << %d);\n",
                    iOffset,
                    pMask,
                    iShift
            );
            fprintf(stdout, "\t\t\tpData[%d] |= (%s & %s) << %d;\n",
                    iOffset,
                    AStr_getData(pStrName),
                    pMask,
                    iShift
            );
        }
        else {
            if (iSize < 8) {
                fprintf(stdout, "\t\t\tpData[%d] &=  0xFF - %s;\n",
                        iOffset,
                        pMask
                );
                fprintf(stdout, "\t\t\tpData[%d] |= %s & %s;\n",
                        iOffset,
                        AStr_getData(pStrName),
                        pMask
                        );
            }
            else {
                fprintf(stdout, "\t\t\tpData[%d] = %s;\n",
                        iOffset,
                        AStr_getData(pStrName)
                );
            }
        }
    }
    else {
        if (iShift) {
            fprintf(stdout, "\t\t\tpData[%d] &=  0xFF - (%s << %d);\n",
                    iOffset,
                    pMask,
                    iShift
            );
            fprintf(stdout, "\t\t\tpData[%d] |= (this->spn%s & %s) << %d;\n",
                    iOffset,
                    AStr_getData(pStrName),
                    pMask,
                    iShift
            );
        }
        else {
            if (iSize < 8) {
                fprintf(stdout, "\t\t\tpData[%d] &=  0xFF - %s;\n",
                        iOffset,
                        pMask
                );
                fprintf(stdout, "\t\t\tpData[%d] |= this->spn%s & %s;\n",
                        iOffset,
                        AStr_getData(pStrName),
                        pMask
                        );
            }
            else {
                fprintf(stdout, "\t\t\tpData[%d] = this->spn%s;\n",
                        iOffset,
                        AStr_getData(pStrName)
                        );
            }
        }
    }
    
    if (pMask) {
        mem_Free(pMask);
        pMask = NULL;
    }
    return true;
}



//---------------------------------------------------------------
//                     g e n  H e a d e r
//---------------------------------------------------------------

bool            genHeader(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc
)
{
    const
    char            *pFieldType = AStr_getData(pStrType);
    const
    char            *pFieldName = AStr_getData(pStrName);
    const
    char            *pDescription = pStrDesc ? AStr_getData(pStrDesc) : OBJ_NIL;
    
    if (strlen(pDescription)) {
        fprintf(stdout, "\t// %s\n", pDescription);
    }
    if (options.fSPN) {
        fprintf(stdout, "\t%s\t\t\t\t%s_getSpn%s(\n",
                pFieldType,
                options.pName,
                pFieldName
                );
    }
    else {
        fprintf(stdout, "\t%s\t\t\t\t%s_get%s(\n",
                pFieldType,
                options.pName,
                pFieldName
                );
    }
    fprintf(stdout, "\t\t%s_DATA\t*this\n", options.pNameUpper);
    fprintf(stdout, "\t);\n\n");
    if (options.fSPN) {
        fprintf(stdout, "\tbool\t\t\t\t%s_setSpn%s(\n",
                options.pName,
                pFieldName
                );
    }
    else {
        fprintf(stdout, "\tbool\t\t\t\t%s_set%s(\n",
                options.pName,
                pFieldName
                );
    }
    fprintf(stdout, "\t\t%s_DATA\t*this,\n", options.pNameUpper);
    fprintf(stdout, "\t\t%s\t\t\tvalue\n", pFieldType);
    fprintf(stdout, "\t);\n\n\n");
    
    return true;
}



//---------------------------------------------------------------
//                     p a r s e  A r g s
//---------------------------------------------------------------

bool            parseArgs(
    int             argc,
    const
    char            *argv[],
    OPTIONS         *pOptions
)
{
    int             offset;
    int             len;
    char            wrkstr[64];
    
    pOptions->genType = 4;
    pOptions->pFunc = "Func";
    pOptions->pName = "Name";
    pOptions->pNameUpper = "NAME";
    
    pProgramName = path_NewA(argv[0]);
    if (OBJ_NIL == pProgramName) {
        return false;
    }
    
    /* Setup input parameters.
     */
    for( argc--,argv++; argc>0; argc--,argv++ ) {
        if (0 == strcmp(*argv, "--debug")) {
            ++pOptions->fDebug;
        }
        else if (0 == strncmp(*argv, "--gentype", 9)) {
            wrkstr[0] = '\0';
            len = (int)strlen(*argv) - 9;
            offset = 9;
            if ('=' == *(*argv + offset)) {
                ++offset;
                --len;
            }
            if (len) {
                int         x;
                if (len > 63) {
                    len =  63;
                    fprintf(stderr, "WARNING - gentype is too long!\n");
                }
                strncat(wrkstr, (*argv + offset), len);
                x = atoi(wrkstr);
                if ((x >= 1) && (x <=5)) {
                    pOptions->genType =x;
                }
                else {
                    show_usage("Invalid GenType");
                }
            }
        }
        else if (0 == strcmp(*argv, "--help")) {
        }
        else if (0 == strcmp(*argv, "--quiet")) {
            ++pOptions->fQuiet;
        }
        else if (0 == strcmp(*argv, "--verbose")) {
            ++pOptions->verbose;
        }
        else if (0 == strcmp(*argv, "--header")) {
            //++pOptions->fGenHeader;
        }
        else if (0 == strcmp(*argv, "--spn")) {
            ++pOptions->fSPN;
        }
        else if (0 == strncmp(*argv, "--name", 6)) {
            wrkstr[0] = '\0';
            len = (int)strlen(*argv) - 6;
            offset = 6;
            if ('=' == *(*argv + offset)) {
                ++offset;
                --len;
            }
            if ('"' == *(*argv + offset)) {
                ++offset;
                len -= 2;
            }
            if (len > 63) {
                len =  63;
                fprintf(stderr, "WARNING - name is too long! Limiting length to 63!\n");
            }
            strncat(wrkstr, (*argv + offset), len);
            if (len) {
                pOptions->pName = str_DupA(wrkstr);
                str_ToUpperA(wrkstr);
                pOptions->pNameUpper = str_DupA(wrkstr);
                if (pOptions->pName && pOptions->pNameUpper) {
                }
                else {
                    show_usage("invalid name");
                }
            }
        }
        else if( (**argv == '-') ) {
            while( *++(*argv) ) {
                switch( tolower( **argv	) ) {
                    case '-':
                        //FIXME: Parse "--xyzzy" style options
                        break;
                    case 'd':
                        ++pOptions->fDebug;
                        break;
                    case '?':
                    case 'h':
                        show_usage(NULL);
                        break;
                    case 'n':
                        ++(*argv);
                        if (*argv[0] == '=') {
                            ++(*argv);
                        }
                        pObjName = AStr_NewA(*argv);
                        if (OBJ_NIL == pObjName) {
                            show_usage("invalid name");
                        }
                        pObjData = AStr_ToUpper(pObjName);
                        if (pObjData) {
                        }
                        else {
                            show_usage("invalid data name");
                        }
                        ++argv;
                        --argc;
                        break;
                    case 'q':
                        ++pOptions->fDebug;
                        break;
                    case 's':
                        //++pOptions->fGenHeader;
                        break;
                    case 'v':
                        ++pOptions->verbose;
                        break;
                    default:
                        fprintf( stderr, "Fatal - illegal option - %c\n", **argv );
                        show_usage(NULL);
                }
            }
        }
        else
            break;
    }
    /* NOW THE ARGV[0] CONTAINS THE FIRST NON-OPTION ARGUMENT,
     * WHILE ARGC CONTAINS THE NUMBER OF ARGUMENTS LEFT.  SO
     * WE HAVE AVAILABLE ARGV[0] -- ARGV[ARGC-1].
     */
    if (argc > 0) {
        pOptions->pArg1 = argv[0];
        ++argv;
        --argc;
    }
    if (argc > 0) {
        pOptions->pArg2 = argv[0];
        ++argv;
        --argc;
    }
    if (argc > 0) {
        pOptions->pArg3 = argv[0];
        ++argv;
        --argc;
    }
    if (argc > 0) {
        pOptions->pArg4 = argv[0];
        ++argv;
        --argc;
    }
    
    
    return true;
}



//---------------------------------------------------------------
//                      p r i n t  C S V
//---------------------------------------------------------------

bool            printCSV(
)
{
    uint32_t        i;
    uint32_t        iMax;
    //uint32_t        j;
    uint32_t        jMax;
    OBJARRAY_DATA   *pEntry;
    ASTR_DATA       *pStrType;
    ASTR_DATA       *pStrName;
    ASTR_DATA       *pStrDesc;
    ASTR_DATA       *pStrOffset;
    ASTR_DATA       *pStrSize;
    ASTR_DATA       *pStrShift;
    bool            fRc;
    
    if (pRecords) {
    }
    else {
        fprintf(stderr, "FATAL ERROR - Input pasred array!");
        exit(99);
    }
    
    switch (options.genType) {
        case 1:
            break;
            
        case 2:
            break;
            
        case 3:
            fprintf(stdout, "\tbool\t\t\t%s_%s(\n", options.pName, options.pFunc);
            break;
            
        case 4:
            fprintf(stdout, "\tbool\t\t\t%s_%s(\n", options.pName, options.pFunc);
            fprintf(stdout, "\t\t%s_DATA\t\t*this,\n", options.pNameUpper);
            fprintf(stdout, "\t\tJ1939_PDU\t\t*pPDU,\n");
            fprintf(stdout, "\t\tuint16_t\t\tcData,\n");
            fprintf(stdout, "\t\tuint8_t\t\t\t*pData,\n");
            fprintf(stdout, "\t\tuint16_t\t\t*pLen\n");
            fprintf(stdout, "\t)\n");
            fprintf(stdout, "\t{\n");
            fprintf(stdout, "\t\tint\t\t\ti;\n");
            fprintf(stdout, "\t\tif (pLen) {\n");
            fprintf(stdout, "\t\t\t*pLen = 8;\n");
            fprintf(stdout, "\t}\n");
            fprintf(stdout, "\t\tif (pData) {\n");
            fprintf(stdout, "\t\t\tif (cData < 8) {\n");
            fprintf(stdout, "\t\t\t\treturn false;\n");
            fprintf(stdout, "\t\t\t}\n");
            fprintf(stdout, "\t\t\tfor (i=0; i<cData; ++i) {\n");
            fprintf(stdout, "\t\t\t\tpData[i] = 0xFF;\n");
            fprintf(stdout, "\t\t\t}\n");
            break;
            
        case 5:
            break;
            
        default:
            break;
    }

    iMax = objArray_getSize(pRecords);
    for (i=0; i<iMax; ++i) {
        pEntry = objArray_Get(pRecords, i+1);
        if (pEntry) {
            if (obj_getIdent(pEntry) == OBJ_IDENT_OBJARRAY) {
                jMax = objArray_getSize(pEntry);
                if (jMax >= 2) {
                    pStrType = objArray_Get(pEntry, 1);
                    pStrName = objArray_Get(pEntry, 2);
                    if (jMax > 2) {
                        pStrDesc = objArray_Get(pEntry, 3);
                    }
                    else {
                        pStrDesc = OBJ_NIL;
                    }
                    if (jMax > 3) {
                        pStrOffset = objArray_Get(pEntry, 4);
                    }
                    else {
                        pStrOffset = OBJ_NIL;
                    }
                    if (jMax > 4) {
                        pStrSize = objArray_Get(pEntry, 5);
                    }
                    else {
                        pStrSize = OBJ_NIL;
                    }
                    if (jMax > 5) {
                        pStrShift = objArray_Get(pEntry, 6);
                    }
                    else {
                        pStrShift = OBJ_NIL;
                    }
                    switch (options.genType) {
                        case 1:
                            fRc =   genHeader(
                                              pStrType,
                                              pStrName,
                                              pStrDesc
                                              );
                            break;
                            
                        case 2:
                            fRc =   genBody(
                                              pStrType,
                                              pStrName,
                                              pStrDesc
                                              );
                            break;
                            
                        case 3:
                            fRc =   genFuncExtract(
                                            pStrType,
                                            pStrName,
                                            pStrDesc,
                                            pStrOffset,
                                            pStrSize,
                                            pStrShift
                                    );
                            break;
                            
                        case 4:
                            fRc =   genFuncSetup(
                                                   pStrType,
                                                   pStrName,
                                                   pStrDesc,
                                                   pStrOffset,
                                                   pStrSize,
                                                   pStrShift
                                    );
                            break;
                            
                        case 5:
                            break;
                            
                        default:
                            break;
                    }
                }
            }
            else {
                DEBUG_BREAK();
            }
        }
    }
    
    switch (options.genType) {
        case 1:
            break;
            
        case 2:
            break;
            
        case 3:
            fprintf(stdout, "\t}\n\n\n\n");
            break;
            
        case 4:
            fprintf(stdout, "\t\t}\n\n");
            fprintf(stdout, "\t\treturn true;\n");
            fprintf(stdout, "\t}\n\n\n\n");
            break;
            
        case 5:
            break;
            
        default:
            break;
    }
    
    return true;
}




//---------------------------------------------------------------
//                      r e a d  C S V
//---------------------------------------------------------------

bool            readCSV(
                        const
                        char            *pFilePath
                        )
{
    DBCSV_DATA      *pCsv = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    
    if (pFilePath) {
        pPath = path_NewA(pFilePath);
        if (pPath) {
            pCsv = dbCsv_NewFile(pPath, 4);
            if (pCsv == OBJ_NIL) {
                fprintf(stderr, "FATAL ERROR - Missing input file path!");
                exit(99);
            }
        }
    }
    else {
        fprintf(stderr, "FATAL ERROR - Missing input file path!");
        exit(99);
    }
    
    //obj_setFlags(pCsv, (obj_getFlags(pCsv) | OBJ_FLAG_TRACE));
    pRecords = dbCsv_ParseFile(pCsv);
    if (pRecords == OBJ_NIL) {
        fprintf(stderr, "FATAL ERROR - dbCsv_ParseFile() failed!");
        exit(99);
    }
    
    if (options.fDebug) {
        ASTR_DATA           *pStr;
        pStr = objArray_ToDebugString(pRecords, 0);
        if (pStr) {
            fprintf(stderr, "%s\n",AStr_getData(pStr));
            obj_Release(pStr);
        }
    }
    
    return true;
}




//------------------------------------------------------------------
//             show_usage - Print program usage informatio.
//------------------------------------------------------------------

void			show_usage(
                           const
                           char            *pErrMsg
                           )
{
    PATH_DATA       *pPath = NULL;
    ERESULT         eRc;
    
    eRc = path_SplitPath(pProgramName, OBJ_NIL, OBJ_NIL, &pPath);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Could not get program name!\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(stderr, "usage: %s\n", path_getData(pPath));
    if (pErrMsg) {
        fprintf(stderr, "FATAL - %s!\n", pErrMsg);
    }
    fprintf(
            stderr,
            "%s(%s) - Generate Getters/Setters for inclusion into programs\n",
            path_getData(pPath),
            __DATE__
            );
    fprintf(stderr, "%s [-d][-v]* input_csv_path\n", path_getData(pPath) );
    fprintf(stderr, "Options:\n" );
    fprintf(stderr, "\t-d\t--debug\tDebug Mode\n" );
    fprintf(stderr, "\t-h\t--help\tDisplay this help\n" );
    fprintf(stderr, "\t-q\t--quiet\tMinimize message ouput\n" );
    fprintf(stderr, "\t-s\t--header\tGenerate .h inclusion instead of .c\n" );
    fprintf(
            stderr,
            "\t-v\t--Verbose\tmay be entered more than once for even more verbosity\n\n"
            );
    fprintf(stderr, "#field_type,field_name,[field_description][,field_offset,\n" );
    fprintf(stderr, "#field_size,field_shift]\n" );
    fprintf(stderr, "The input csv file has a minimum of 2 fields. The first is the\n" );
    fprintf(stderr, "field type such as 'uint8_t'. If it is a pointer, the '*' must\n" );
    fprintf(stderr, "be included. So, it would have to be quoted. The second field is\n" );
    fprintf(stderr, "field name. A third field being a description is optional.\n" );
    fprintf(stderr, "Field_offset is the offset of the field in some structure.\n" );
    fprintf(stderr, "Field_size is the size of the field in bits. field_shift.\n" );
    fprintf(stderr, "Field_shift is the amount to shift to put the field in bit 0.\n\n\n" );
    fprintf(stderr, "\n\n\n" );
    exit(EXIT_FAILURE);
}



//===============================================================
//                          M a i n
//===============================================================

int             main(
    int             argc,
    const
    char *          argv[]
)
{
    bool            fRc;
    
    fRc = parseArgs(argc, argv, &options);
    if (!fRc) {
        show_usage(NULL);
    }
    if (options.pArg1 == NULL) {
        show_usage("Missing Input File Path");
    }
    
    fRc = readCSV(options.pArg1);
    if (!fRc) {
        fprintf(stderr, "FATAL ERROR - Could not parse csv file!");
        exit(99);
    }
    fRc = printCSV();
    if (!fRc) {
        fprintf(stderr, "FATAL ERROR - Could not print csv file!");
        exit(99);
    }

    return 0;
}
