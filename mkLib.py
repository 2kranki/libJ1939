#!/usr/bin/env python3
# vi:nu:et:sts=4 ts=4 sw=4

''' Build the Library
'''


#   This is free and unencumbered software released into the public domain.
#
#   Anyone is free to copy, modify, publish, use, compile, sell, or
#   distribute this software, either in source code form or as a compiled
#   binary, for any purpose, commercial or non-commercial, and by any
#   means.
#
#   In jurisdictions that recognize copyright laws, the author or authors
#   of this software dedicate any and all copyright interest in the
#   software to the public domain. We make this dedication for the benefit
#   of the public at large and to the detriment of our heirs and
#   successors. We intend this dedication to be an overt act of
#   relinquishment in perpetuity of all present and future rights to this
#   software under copyright law.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
#   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
#   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
#   OR OTHER DEALINGS IN THE SOFTWARE.
#
#   For more information, please refer to <http://unlicense.org/>


import      argparse
import      contextlib
import      os
import      re
import      subprocess
import      sys
import      time


args = None                                         # pylint: disable=C0103
szGoDir = '${HOME}/go'                              # pylint: disable=C0103



################################################################################
#                           Object Classes and Functions
################################################################################

#---------------------------------------------------------------------
#       absolute_path -- Convert a Path to an absolute path
#---------------------------------------------------------------------

def absolute_path(path, create_dirs=False, trace_flag=False):
    """ Convert Path to an absolute path creating subdirectories if needed

    Returns:
        path string for successful completion or None for error
    """
    if trace_flag:
        print("absolutePath(%s)" % path)

    # Convert the path.
    work_path = os.path.normpath(path)
    work_path = os.path.expanduser(work_path)
    work_path = os.path.expandvars(work_path)
    work_path = os.path.abspath(work_path)

    if create_dirs:
        dir_path = os.path.dirname(work_path)
        if len(dir_path) > 0:
            if not os.path.exists(dir_path):
                if trace_flag:
                    print("\tCreating directories:", dir_path)
                os.makedirs(dir_path)

    # Return to caller.
    if trace_flag:
        print("...end of absolutePath:", work_path)
    return work_path


#---------------------------------------------------------------------
#                           OS Execute
#---------------------------------------------------------------------

def do_cmd(cmd_line, cwd='.'):
    """ Execute an O/S command without capturing input or output.

        Returns:
            command return code
    """
    print('Executing:', cmd_line)
    result = subprocess.run(cmd_line, cwd=cwd, shell=True, check=False)
    return result.returncode

def do_sys(cmd_line, cwd='.'):
    """ Execute an O/S command capturing both, stdout and stderr.

        Returns:
            result.returncode
            result.stdout
            result.stderr
    """
    result = subprocess.run(cmd_line, cwd=cwd, stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE, shell=True, check=True)
    return result


#---------------------------------------------------------------------
#                       Main Command Class
#---------------------------------------------------------------------

class MainBase:
    """ Base Command Line Program Class.
    """

    def __init__(self):
        self.args = None
        self.arg_prs = argparse.ArgumentParser()
        self.result_code = 0

    def arg_parse_exec(self):
        """ Execute the argument parsing.
            Warning - Main should override this method if additional cli
            arguments are needed or argparse needs some form of modification
            before execution.
        """
        self.arg_parse_setup()
        # You can insert other logic here if you need to when you override.
        self.arg_parse_parse()

    def arg_parse_parse(self):
        """ Parse the command line arguments.
        """
        self.args = self.arg_prs.parse_args(sys.argv[1:])
        if self.args.flg_debug:
            print("In DEBUG Mode...")
            print('Args:', self.args)

    def arg_parse_setup(self):
        """ Set up to parse the command line arguments
        """
        self.arg_prs.add_argument('-d', '--debug', action='store_true', dest='flg_debug',
                                  default=False, help='Set debug mode'
                                 )
        self.arg_prs.add_argument('--noexc', action='store_false', dest='flg_exec',
                                  default=True, help='Dont execute O/S routines'
                                 )
        self.arg_prs.add_argument('-f', '--force', action='store_true', dest='flg_force',
                                  default=False, help='Set force mode'
                                 )
        self.arg_prs.add_argument('--exec', action='store_false', dest='flg_exec',
                                  default=True, help='Reset execute mode'
                                 )
        self.arg_prs.add_argument('-v', '--verbose', action='count', default=1,
                                  dest='verbose', help='increase output verbosity'
                                 )
        self.arg_prs.add_argument('args', nargs=argparse.REMAINDER, default=[])

    def do_cmd(self, cmd_line, cwd='.'):
        """ Execute an O/S command without capturing input or output.

            Returns:
                command return code
        """
        result = subprocess.run(cmd_line, cwd=cwd, shell=True, check=True)
        self.result_code = result.returncode
        return self.result_code

    def exec_pgm(self):                                 #pylint: disable=no-self-use
        """ Program Execution
            Warning - Main should override this method and make certain that
            it returns an exit code in self.result_code.
        """
        self.result_code = 24
        print("ERROR: exec_pgm is NOT implemented!")

    def run(self):
        """ Run the program keeping track of how long that it takes.
        """
        start_time = time.time()
        self.arg_parse_exec()
        # arguments and options are in self.args.
        if self.result_code == 0:
            try:
                self.exec_pgm()
            except Exception as excp:  # pylint: disable=broad-except
                print("Execption:", excp)
                self.result_code = 20
        end_time = time.time()
        if self.args.verbose > 0 or self.args.flg_debug:
            if int(self.result_code) == 0:
                print("...Successful completion.")
            else:
                print("...Completion Failure of %d" % self.result_code)
            print("Start Time: %s" % time.ctime(start_time))
            print("End   Time: %s" % time.ctime(end_time))
            diff_time = end_time - start_time      # float Time in seconds
            secs = int(diff_time % 60.0)
            mins = int((diff_time / 60.0) % 60.0)
            hrs = int(diff_time / 3600.0)
            print("run   Time: %d:%02d:%02d" % (hrs, mins, secs))
        sys.exit(int(self.result_code) or 0)


#---------------------------------------------------------------------
#               parse_args -- Parse the CLI Arguments
#---------------------------------------------------------------------

def         parse_args(listArgV=None):
    '''
    '''
    global      args

    # Parse the command line.
    szUsage = "usage: %prog [options] sourceDirectoryPath [destinationDirectoryPath]"
    cmd_prs = argparse.ArgumentParser( )
    cmd_prs.add_argument('-d', '--debug', action='store_true', dest='debug',
                         default=False, help='Set debug mode'
                         )
    cmd_prs.add_argument('-f', '--force', action='store_true', dest='force',
                         default=False, help='Set force mode'
                         )
    cmd_prs.add_argument('-i', '--install', action='store_false', dest='install',
                         default=True, help='Skip Install mode'
                         )
    cmd_prs.add_argument('-m', '--make', action='store_false', dest='make',
                         default=True, help='Skip Make mode'
                         )
    cmd_prs.add_argument('-o', '--ostype', action='store', dest='ostype',
                         default='macos64', help='Makefile Type (macos64 | win64)'
                         )
    cmd_prs.add_argument('-t', '--test', action='store_false', dest='test',
                         default=True, help='Skip Test mode'
                         )
    cmd_prs.add_argument('-v', '--verbose', action='count', default=1,
                         dest='verbose', help='increase output verbosity'
                         )
    cmd_prs.add_argument('args', nargs=argparse.REMAINDER, default=[])
    args = cmd_prs.parse_args(listArgV)
    if args.debug:
        print("In DEBUG Mode...")
        print('Args:', args)

    return 0


#---------------------------------------------------------------------
#           perform_actions -- Perform the requested actions
#---------------------------------------------------------------------

def         perform_actions():
    ''' Perform the requested actions.
    '''
    global      args

    if args.verbose > 0:
        print('*****************************************')
        print('*       Building the Library            *')
        print('*****************************************')
        print()

    # Build the Makefile.
    if args.make:
       rc = do_cmd("genMake objects.json.txt")
       if rc != 0:
           print('ERROR - genMake failed!')
           return 4
       rc = do_cmd("cp Makefile.%s.txt Makefile" % args.ostype)
       if rc != 0:
           print('ERROR - cp failed!')
           return 4

    # Build the library.
    rc = do_cmd("make -f Makefile.%s.txt clean" % args.ostype)
    if rc != 0:
        print('ERROR - make clean failed!')
        return 4
    rc = do_cmd("make -f Makefile.%s.txt all" % args.ostype)
    if rc != 0:
        print('ERROR - make all failed!')
        return 4

    # Test the library.
    if args.test:
        rc = do_cmd("make -f Makefile.%s.txt test" % args.ostype)
        if rc != 0:
            print('ERROR - make test failed!')
            return 4

    # Install the library.
    if args.install:
        rc = do_cmd("make -f Makefile.%s.txt install" % args.ostype)
        if rc != 0:
            print('ERROR - make test failed!')
            return 4

    return 0


################################################################################
#                           Main Program Processing
################################################################################

def main_cli(listArgV=None):
    ''' Command-line interface.
    '''
    global      args
    
    # Parse the command line.
    parse_args(listArgV)

    # Perform the specified actions.
    rc = perform_actions()                              # pylint: disable=C0103

    return rc


################################################################################
#                           Command-line interface
################################################################################

if '__main__' == __name__:
    start_time = time.time()                            # pylint: disable=C0103
    rc = main_cli(sys.argv[1:])                         # pylint: disable=C0103
    if args.verbose > 0 or args.debug:
        if rc == 0:
            print("...Successful completion.")
        else:
            print("...Completion Failure of %d" % (rc))
    end_time = time.time()                              # pylint: disable=C0103
    if args.verbose > 0 or args.debug:
        print("Start Time: %s" % (time.ctime(start_time)))
        print("End   Time: %s" % (time.ctime(end_time)))
        # float time in seconds
        diffTime = end_time - start_time                # pylint: disable=C0103
        secs = int(diffTime % 60.0)                     # pylint: disable=C0103
        mins = int((diffTime / 60.0) % 60.0)            # pylint: disable=C0103
        hrs = int(diffTime / 3600.0)                    # pylint: disable=C0103
        print("Run   Time: %d:%02d:%02d" % (hrs, mins, secs))
    sys.exit(rc or 0)


