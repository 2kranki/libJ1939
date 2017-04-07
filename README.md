
libJ1939
===============

**libJ1939** is one approach to providing simple C objects for
various environments such as Mac, PIC32MX7xx, and iOS that
support J1939 Message Reception and Transmission.

It is intended that each object be self documenting and consistent
in its usage from other objects within this library.

However, this is a work in-progress, constantly evolving and some
objects/environments may be incomplete, duplicated, buggy or all
of those. lol

All of this library is committed to the Public Domain.  See 'j1939_defs.h'
for a list of the objects in the library.

My primary development environment is MacOSX with Xcode. The C code
is ANSI C and should be compilable with any ANSI C compiler. Use
'mkLib.sh' after adjusting it to create the library. If you are
using Xcode, you will find a test program for almost every object.
Some tests are pretty complete, but they are always a work in-progress.


*** Use at your own risk. ***



J1939 Objects
===============

J1939       -   Central Object which must be used in all cases

J1939cam    -   Controller Application Manager
                --  Receives all messages and dispatches them to the
                    appropriate Controller Application(s)

J1939ca     -   Controller Application
                --  Handles appropriate messages
                --  Transmits Timed Messages when due

J1939en     -   Engine Application which inherits from J1939ca

J1939er     -   Engine Retarder Application which inherits from J1939ca

J1939tc     -   Transmission Application which inherits from 1939ca



The normal operation would be to have an Engine Application and an Engine Retarder
Application running under a task or a Transmission Application. If you use J1939
to start either the Engine Application or the Transmission Application, it will
take care of the underlying linkages. This system was originally designed to run
in a multi-tasking operating system.



