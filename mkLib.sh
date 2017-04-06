#!/bin/bash
# add -xv above to debug.

# vi:nu:et:sts=4 ts=4 sw=4

#   This is for use with git.sh




    fDebug=
    fQuiet=
    fNoVerify=
    fVerbose=

    project=libJ1939
    osType="macosx"
    srcDir="./src"
    cmnIncDir="${HOME}/Support/lib/${osType}/libCmn/include"
    destDir="${HOME}/Support/lib/${osType}/${project}"
    tmpDir="/tmp/${project}"

    fRelease=
    CC="gcc"
    CFLAGS="-std=c99 -Wall -I${srcDir}"




#################################################################
#                       Functions
#################################################################

#-----------------------------------------------------------------
#								doCmd
#-----------------------------------------------------------------
doCmd( ) {

	if [ $# -eq 0 ]; then
		:
	else
		if [ -z "$fQ"  ]; then
		    echo "Now we do - ${@}..."
		fi
		if [ -n "$fDebug" -a -n "$fSimulate" ]; then
				echo	"    Debug Mode - simulating ${@}"
				$?=0
		else
			if ${@}
			then
				:
			else
				echo "ERROR - ${@} FAILED!"
                exit 4
			fi
		fi
		#echo "Just completed - ${@}"
	fi

}



#-----------------------------------------------------------------
#								doCompile
#-----------------------------------------------------------------
doCompile( ) {
    local   rel=""
    local   libCmn="-I${cmnIncDir}"

	if [ -n "$release" ]; then
        rel="-DNDEBUG=1"
		echo	"    Release Mode"
				$?=0
    fi
	if [ $# -eq 0 ]; then
		:
	else
        doCmd "${CC} ${CFLAGS} ${libCmn} ${rel}  -c ${srcDir}/${1}.c -o ${tmpDir}/${1}.o"
	fi

}


doCompileSpcl( ) {
    local   relse=""
    local   libCmn="-I${cmnIncDir}"

	if [ -n "$release" ]; then
        relse="-DNDEBUG=1"
    fi
	if [ $# -eq 0 ]; then
		:
	else
        doCmd "${CC} ${CFLAGS} ${libCmn} ${relse}  -c ${srcDir}/${2}/${1}.c -o ${tmpDir}/${1}.o"
	fi

}




#----------------------------------------------------------------
#                     Get the Date and Time
#----------------------------------------------------------------

getDateTime () { 
    DateTime="$(date +%G%m%d)_$(date +%H%M%S)";
    return 0
}



#-----------------------------------------------------------------
#							getReplyYN
#-----------------------------------------------------------------

# Returns:
#			0 == yes
#			1 == no
#			exit 8 == q for quit

getReplyYN( ) {

	szMsg="$1"
	if [ -z "$2" ]; then
		szDefault="y"
	else
		szDefault="$2"
	fi

	while [ 0 ]; do
        if [ "y" = "${szDefault}" ]; then
            szYN="Yn"
        else
            szYN="Ny"
        fi
        echo "${szMsg} ${szYN}<enter> or q<enter> to quit:"
        read ANS
        if [ "q" = "${ANS}" ]; then
            exit 8
        fi
        if [ "" = "${ANS}" ]; then
            ANS="${szDefault}"
        fi
        if [ "y" = "${ANS}" ] || [ "Y" = "${ANS}" ]; then
            return 0
        fi
        if [ "n" = "${ANS}" ]  || [ "N" = "${ANS}" ]; then
            return 1
        fi
        echo "ERROR - invalid response, please enter y | n | q."
    done
}



#----------------------------------------------------------------
#                     Do Main Processing
#----------------------------------------------------------------

main( ) {

    # Parse off the command arguments.
    if [ $# = 0 ]; then             # Handle no arguments given.
        :
    else
        # Parse off the flags.
        while [ $# != 0 ]; do
            flag="$1"
            case "$flag" in
                -d | --debug) 
                    fDebug=y
                    if test -z "$fQuiet"; then
                        echo "In Debug Mode"
                    fi
                    set -xv
                    ;;
                --dest) 
                    destDir="$2"
                    shift
                    ;;
                -h | --help) 
                    displayUsage
                    return 4
                    ;;
                -q) 
                    fQuiet=y
                    ;;
                --release) 
                    release=y
                    shift
                    ;;
                -*)
                    if test -z "$fQuiet"; then
                        echo "FATAL: Found invalid flag: $flag"
                    fi
                    displayUsage
                    ;;
                *)
                    break                       # Leave while loop.
                    ;;
            esac
            shift
        done
        # Handle the fixed arguments.
        while [ $# != 0 ]; do
            opt="$1"
            case "$opt" in
                all) 
                    fBash=y
                    fDesktopservices=y
                    fFinder=y
                    fGitInstall=y
                    fSafari=y
                    fTerminal=y
                    fXcode=y
                    ;;
                bash) 
                    fBash=y
                    ;;
                desktopservices) 
                    fDesktopservices=y
                    ;;
                finder) 
                    fFinder=y
                    ;;
                git) 
                    fGitInstall=y
                    ;;
                safari) 
                    fSafari=y
                    ;;
                terminal) 
                    fTerminal=y
                    ;;
                xcode) 
                    fXcode=y
                    ;;
                *)
                    if test -z "$fQuiet"; then
                        echo "FATAL: Found invalid option: $opt"
                    fi
                    displayUsage
                    ;;
            esac
            shift
        done
    fi

    doCmd "rm -fr ${tmpDir}"
    doCmd "mkdir -p ${tmpDir}"

    doCompile   j1939
    doCompile   j1939_object
    doCompile   j1939ca
    doCompile   j1939ca_object
    doCompile   j1939cam
    doCompile   j1939cam_object
    doCompile   j1939dg
    doCompile   j1939dg_object
    doCompile   j1939dl
    doCompile   j1939dl_object
    doCompile   j1939en
    doCompile   j1939en_object
    doCompile   j1939er
    doCompile   j1939er_object
    doCompile   j1939msg
    doCompile   j1939tbl
    doCompile   j1939tbl_object
    doCompile   j1939tc
    doCompile   j1939tc_object
   
    doCmd "rm -fr ${destDir}"
    doCmd "mkdir -p ${destDir}/include"
    doCmd "ar -r -v  ${destDir}/${project}.a ${tmpDir}/*.o"
    doCmd "cp -v ${srcDir}/*.h ${destDir}/include/"

    return $?
}





#################################################################
#                       Main Function
#################################################################

    # Do initialization.
    szScriptPath="$0"
    szScriptDir=$(dirname "$0")
    szScriptName=$(basename "$0")
	getDateTime
	TimeStart="${DateTime}"
	#setColors

    # Scan off options and verify.
    
    # Perform the main processing.
	main  $@
	mainReturn=$?

	getDateTime
	TimeEnd="${DateTime}"
    if test -z "$fQuiet"; then
        if [ 0 -eq $mainReturn ]; then
            echo		   "Successful completion..."
        else
            echo		   "${RED}Unsuccessful completion of ${mainReturn}${CANCEL}"
        fi
        echo			"   Started: ${TimeStart}"
        echo			"   Ended:   ${TimeEnd}"
	fi

	exit	$mainReturn


 

