
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
