TinyThread++
=============

TinyThread++ (tthread, http://tinythread.sourceforge.net/) is a lightweight and portable C++ threading library.
This is a simple fork of the project to keep doing maintenance on it for [WkCore](https://github.com/asmodehn/WkCore) needs.

As TinyThread++, this project should remain compatible with old compilers, namely VS 2010, for use of Thread Objects when the compiler does not have the C++11 conform std::bind function ( and cannot easily support passing a Functor as the Thread function ).

Also to keep it lightweight, a very cimple CMakeLists is used here ( and not the full fledged WkCMake ).
Unit Tests are made with simplified custom unit test code ( and not a full fledged unit test library ).

TinyThread++ shoud still be cross-platform as much as possible. Current targets are :

- Windows
- Linux
- OSX
- Android
- iOS

For more C++11 behavior ( with variadic templates, functional behavior, future, etc. ) [WkCore](https://github.com/asmodehn/WkCore) is there to provide them, with a minimum requirement of compiling with VS2012
