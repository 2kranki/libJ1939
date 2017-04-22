
libJ1939
===============

**libJ1939** is one approach to providing simple C objects for
various environments such as Mac, PIC32MX7xx, and iOS that
support J1939 Message Reception and Transmission. They were
initially operational in MacOSX and a Microchip PIC32MX795
computer. I used a multi-tasking O/S in the Microchip computer
and ran a task for each service (ie, UART, CAN and J1939).
Within the UART and CAN routines, I buffered the data in circular
buffers. I used a consumer/producer object to communicate between
the CAN and J1939 objects. It seemed to keep up with the message
flow, because the PIC32MX795 is fairly powerful. I would use
a PIC32MZ today. 

It is intended that each object be self documenting and consistent
in its usage from other objects within this library.

To use this library, you must supply routines that will read and
write CAN messages on your own hardware. In addition, you will
need a 10ms timer that calls the CAM message handler with a NULL
for the message pointer. I have written the routines to work in
any environment that can supply these services. Also, after initial
startup, these objects and routines will not allocate or free
memory to meet safety standards.

However, this is a work in-progress, constantly evolving and some
objects/environments may be incomplete, duplicated, buggy or all
of those. lol

All of this library is committed to the Public Domain.  See 
'j1939_defs.h' for a list of the objects in the library.

My primary development environment is MacOSX with Xcode. The C code
is ANSI C and should be compilable with any ANSI C compiler. Use
'mkLib.sh' after adjusting it to create the library. If you are
using Xcode, you will find a test program for almost every object.
Some tests are pretty complete, but they are always a work in-progress.

This library relies on libCmn being available.

*** Use at your own risk. ***



J1939 Objects
===============

J1939cam    -   Controller Application Manager
                --  Receives all messages and dispatches them to the
                    appropriate Controller Application(s)
                --  This is the first place to look to learn how the
                    system works.

J1939can    -   Substitute CAN Object
                --  Can be used in leiu of creating another object if 
                    desired

J1939ca     -   Controller Application
                --  Handles appropriate messages
                --  Handles the Transport Protocol
                --  Transmits Timed Messages when due

J1939cc     -   Cab Controller Application which inherits from J1939ca
                --  Tells Engine and Transmission Contollers what to
                    do based on operator inputs
                --  Gathers information from Engine and Transmission
                    to display in the cab

J1939en     -   Engine Application which inherits from J1939ca

J1939er     -   Engine Retarder Application which inherits from J1939ca

J1939tc     -   Transmission Application which inherits from 1939ca
                (Currently Not Operational)



The normal operation would be to have an Engine Application and optionally an 
Engine Retarder Application running under a task or a Transmission Application. 
If you use J1939 to start either the Engine Application or the Transmission 
Application, it will take care of the underlying linkages. This system was
originally designed to run in a multi-tasking operating system.



