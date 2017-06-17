//
//
//  main.c
//  dumpFile
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


#include    <j1939_defs.h>
#include    <AStr.h>
#include    <dbCsv.h>
#include    <hex.h>
#include    <j1939misc.h>
#include    <j1939msg.h>
#include    <path.h>
#include    <trace.h>


//===============================================================
//                          D a t a
//===============================================================

typedef struct options_s {
    int             fDebug;
    int             fQuiet;
    int             verbose;
    uint32_t        lowerLimit;
    uint32_t        upperLimit;
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
//                     Construct Message
//---------------------------------------------------------------

bool            constructMessage(
    J1939_MSG       *pMsg,              // Updated msg
    ASTR_DATA       *pStrTime,
    ASTR_DATA       *pStrMsgID,
    ASTR_DATA       *pStrLength,
    ASTR_DATA       *pStrData
)
{
    const
    char            *pTime = AStr_getData(pStrTime);
    uint32_t        time = 0;
    const
    char            *pMsgID = AStr_getData(pStrMsgID);
    uint32_t        msgID = 0;
    const
    char            *pLength = AStr_getData(pStrLength);
    uint32_t        length = 0;
    const
    char            *pData = AStr_getData(pStrData);
    uint32_t        data = 0;
    uint8_t         bytes[8];
    int             i;
    bool            fRc;

    BREAK_NULL(pMsg);
    j1939msg_Clear(pMsg);

    fRc = hex_ScanUint32A(AStr_getLength(pStrTime), pTime, &time);
    BREAK_FALSE(fRc);
    //pMsg->CMSGSID.CMSGTS = time;
    
    fRc = hex_ScanUint32A(AStr_getLength(pStrMsgID), pMsgID, &msgID);
    BREAK_FALSE(fRc);
    //pMsg->CMSGSID.w = msgID;
    
    fRc = hex_ScanUint32A(AStr_getLength(pStrLength), pLength, &length);
    BREAK_FALSE(fRc);
    BREAK_FALSE((length == 8));
    
    BREAK_FALSE((AStr_getLength(pStrData) == 16));
    for (i=0; i<length; ++i) {
        data = 0;
        fRc = hex_ScanUint32A(2, pData, &data);
        BREAK_FALSE(fRc);
        bytes[i] = data & 0xFF;
        pData += 2;
    }

    fRc = j1939msg_ConstructMsg_E1( pMsg, msgID, length, bytes);
    BREAK_FALSE(fRc);
    pMsg->CMSGSID.CMSGTS = time;
    
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
        else if (0 == strncmp(*argv, "--lower", 9)) {
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
                    fprintf(stderr, "WARNING - Lower Limit is too long!\n");
                }
                strncat(wrkstr, (*argv + offset), len);
                x = atoi(wrkstr);
                if (x > 1) {
                    pOptions->lowerLimit = x;
                }
                else {
                    show_usage("Invalid Lower Limit");
                }
            }
        }
        else if (0 == strncmp(*argv, "--upper", 9)) {
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
                    fprintf(stderr, "WARNING - Upper Limit is too long!\n");
                }
                strncat(wrkstr, (*argv + offset), len);
                x = atoi(wrkstr);
                if (x > 1) {
                    pOptions->upperLimit = x;
                }
                else {
                    show_usage("Invalid Upper Limit");
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
    if (options.lowerLimit && options.upperLimit) {
        if (options.lowerLimit < options.upperLimit) {
        }
        else {
            fprintf( stderr, "Fatal - Lower Limit must be less than Upper Limit!\n" );
            show_usage(NULL);
        }
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
//                      p r i n t  M e s s a g es
//---------------------------------------------------------------

bool            printMessages(
)
{
    uint32_t        i;
    uint32_t        iMax;
    //uint32_t        j;
    uint32_t        jMax;
    OBJARRAY_DATA   *pEntry;
    ASTR_DATA       *pStrTime;
    ASTR_DATA       *pStrMsgID;
    ASTR_DATA       *pStrLength;
    ASTR_DATA       *pStrData;
    bool            fRc;
    J1939_MSG       msg;
    J1939MISC_DATA  *pMisc;
    uint32_t        numMsgs = 0;
    
    if (pRecords) {
    }
    else {
        fprintf(stderr, "FATAL ERROR - Input pasred array!");
        exit(99);
    }
    pMisc = j1939misc_New( );
    BREAK_NULL(pMisc);
    j1939misc_setFileOut(pMisc, stderr);
    
    iMax = objArray_getSize(pRecords);
    if (options.fDebug) {
        fprintf(stderr, "%d possible Messages\n\n", iMax);
    }
    for (i=0; i<iMax; ++i) {
        if (options.lowerLimit && (i < options.lowerLimit)) {
            continue;
        }
        if (options.upperLimit && (i > options.upperLimit)) {
            continue;
        }
       pEntry = objArray_Get(pRecords, i+1);
        if (pEntry) {
            if (obj_getIdent(pEntry) == OBJ_IDENT_OBJARRAY) {
                jMax = objArray_getSize(pEntry);
                if (jMax >= 3) {
                    pStrTime = objArray_Get(pEntry, 1);
                    pStrMsgID = objArray_Get(pEntry, 2);
                    pStrLength = objArray_Get(pEntry, 3);
                    pStrData = objArray_Get(pEntry, 4);
                    fRc = constructMessage(&msg, pStrTime, pStrMsgID, pStrLength, pStrData);
                    j1939misc_DumpMessage(pMisc, &msg);
                    ++numMsgs;
                }
            }
            else {
                DEBUG_BREAK();
            }
        }
    }
    fprintf(stderr, "\n%d Messages\n\n", iMax);
    
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
    fprintf(stderr, "%s [-d][-v]* input_path\n", path_getData(pPath) );
    fprintf(stderr, "Options:\n" );
    fprintf(stderr, "\t-d\t--debug\tDebug Mode\n" );
    fprintf(stderr, "\t-h\t--help\tDisplay this help\n" );
    fprintf(stderr, "\t-q\t--quiet\tMinimize message ouput\n" );
    fprintf(
            stderr,
            "\t-v\t--Verbose\tmay be entered more than once for even more verbosity\n\n"
            );
    fprintf(stderr, "\t\t--lower=NNN\tSkip first NNN message in file\n" );
    fprintf(stderr, "\t\t--upper=NNN\tSkip from NNNth message to end of file\n" );
    fprintf(stderr, "input_path is expected to be a J1939 Message file in csv/hex format.\n" );
    fprintf(stderr, "#time,#pdu,#data_length(08),#data_bytes\n" );
    fprintf(stderr, "All fields are in hexadecimal format with comma separators.\n" );
    fprintf(stderr, "Example:  0000CEF3,18F00503,08,7D00007D204E204E\n" );
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
        fprintf(stderr, "FATAL ERROR - Could not parse input file!");
        exit(99);
    }

    fRc = printMessages( );
    if (!fRc) {
        fprintf(stderr, "FATAL ERROR - Could not print input file!");
        exit(99);
    }
    
    return 0;
}
