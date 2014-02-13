TinyThread++ Fork
=================

[TinyThread++](https://gitorious.org/tinythread) is a lightweight and portable C++ threading library.
This repository is a simple fork of the project to keep doing maintenance on it for [WkCore](https://github.com/asmodehn/WkCore) needs.

As TinyThread++, this project should remain compatible with old compilers, namely VS 2010, for use of Thread Objects when the compiler does not have the C++11 conform std::bind function ( and cannot easily support passing a Functor as the Thread function ).

Also to keep it lightweight, a very simple CMakeLists is used here ( and not the full fledged WkCMake ).
Original Makefile is still there if you need it.
Unit Tests are made with simplified custom unit test code ( and not a full fledged unit test library ).

TinyThread++ shoud still be cross-platform as much as possible. Current targets are :

- Windows
- Linux
- OSX
- Android
- iOS

To use this fork, you can :
- add it as a subdirectory in your cmake chain,
- add it as an Android Module in your NDK build chain,
- do it the old way (see below)

For more C++11 behavior ( with variadic templates, functional behavior, future, etc. ) [WkCore](https://github.com/asmodehn/WkCore) is there to provide them, with a minimum requirement of compiling with VS2012


[TinyThread++ v1.2](http://tinythreadpp.bitsnbites.eu)
===================


About
-----

TinyThread++ is a minimalist, portable, threading library for C++, intended to
make it easy to create multi threaded C++ applications.

The library is closesly modeled after the C++11 standard, but only a subset is
implemented at the moment.

See the documentation in the doc/html directory for more information.


Using TinyThread++
------------------

To use TinyThread++ in your own project, just add tinythread.cpp and
tinythread.h to your project. In your own code, do:

    #include <tinythread.h>
    using namespace tthread;

If you wish to use the fast_mutex class, inlude fast_mutex.h:

    #include <fast_mutex.h>


Building the test programs
--------------------------

From the test folder, issue one of the following commands:

Linux, Mac OS X, OpenSolaris etc:

    make (you may need to use gmake on some systems)

Windows/MinGW:

    mingw32-make

Windows/MS Visual Studio:

    nmake /f Makefile.msvc


License
-------

Copyright (c) 2010-2012 Marcus Geelnard

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.

  3. This notice may not be removed or altered from any source
  distribution.
