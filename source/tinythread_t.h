/*
Copyright (c) 2012 Jared Duke

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
*/

//NOTE : This thread support different signature of functions.
//However retrieving the result is not hte point of a thread.
//To do so, futures need to be implemented

#ifndef _TINYTHREAD_T_H_
#define _TINYTHREAD_T_H_

#include "tinythread.h"

#if defined(_TTHREAD_POSIX_)
#include <unistd.h>
#include <map>
#elif defined(_TTHREAD_WIN32_)
#include <process.h>
#endif

#include <memory>

/// @file
namespace tthread {

/// Thread class with template argument support.
class threadt : public thread {
public:

	threadt() : thread() { }

#if defined(_TTHREAD_RVALUES_)
	threadt(threadt&& other) : thread(std::move(other)) { }

	threadt& operator=(threadt&& other) { 
		thread::swap(std::move(other)); 
		return *this;
	}
#endif

	template< typename thread_func_t >
	threadt(thread_func_t func, void * aArg) : thread() {
		init(func, aArg);
	}

//be careful of move semantics
#if defined(_TTHREAD_RVALUES_)
#if defined(_TTHREAD_VARIADIC_)
	template< typename thread_func_t, typename Args... >
	threadt(thread_func_t func, Args... args) : thread() {
		init(std::bind(std::move(func), std::move(args)...));
	}
#endif
#endif

protected:

	_TTHREAD_DISABLE_ASSIGNMENT(threadt);

	template< typename thread_func_t >
	void init(thread_func_t func, void * aArg);

	/// Information shared between the thread wrapper and the thread object.
	template< typename thread_func_t >
	class _thread_wrapper_t {
	  public:
		_thread_wrapper_t(thread_func_t aFunction, void * aArg) :
		  mFunction(aFunction),
		  mArg(aArg),
		  mRefCount(2)      // Upon creation the object is referenced by two
							// instances: the thread object and the thread wrapper
		{
		}

		inline void run()
		{
		  mFunction(mArg);
		}

		inline bool joinable() const
		{
		  return mRefCount > 1;
		}

		inline bool release()
		{
		  return !(--mRefCount);
		}

	  private:
		thread_func_t mFunction;	// Pointer to the function to be executed
		void * mArg;                // Function argument for the thread function
		atomic_int mRefCount;       // Reference count
	};

template< class thread_func_t >
#if defined(_TTHREAD_WIN32_)
	static unsigned WINAPI wrapper_function(void* aArg);
#elif defined(_TTHREAD_POSIX_)
	static void* wrapper_function(void* aArg);
#endif

};

template< typename thread_func_t >
void threadt::init(thread_func_t aFunction, void * aArg) {

	// Fill out the thread startup information (passed to the thread wrapper)
	_thread_wrapper_t<thread_func_t> * tw = new _thread_wrapper_t<thread_func_t>(aFunction, aArg);

	// Create the thread
#if defined(_TTHREAD_WIN32_)
	mHandle = (HANDLE) _beginthreadex(0, 0, wrapper_function<thread_func_t>, (void *) tw, 0, &mWin32ThreadID);
#elif defined(_TTHREAD_POSIX_)
	if(pthread_create(&mHandle, NULL, wrapper_function<thread_func_t>, (void *) tw) != 0)
		mHandle = 0;
#endif

	// Did we fail to create the thread?
	if(!mHandle)
	{
	delete tw;
	tw = 0;
	}

	mWrapper = (void *) tw;
}

// Thread wrapper function.
template< class thread_func_t >
#if defined(_TTHREAD_WIN32_)
unsigned WINAPI threadt::wrapper_function(void * aArg)
#elif defined(_TTHREAD_POSIX_)
void * threadt::wrapper_function(void * aArg)
#endif
{
  // Get thread wrapper information
  _thread_wrapper_t<thread_func_t> * tw = (_thread_wrapper_t<thread_func_t> *) aArg;

  try
  {
    // Call the actual client thread function
    tw->run();
  }
  catch(...)
  {
    // Uncaught exceptions will terminate the application (default behavior
    // according to C++11)
    std::terminate();
  }

  // The thread is no longer executing
  if(tw->release())
  {
    delete tw;
  }

  return 0;
}

} //namespace tthread

#endif // _TINYTHREAD_T_H_
