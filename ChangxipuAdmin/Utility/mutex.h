// -----------------------------------------------------------------------------
//
// Copyright 2000 Marconi Data Systems, Inc. All Rights Reserved. 
//
// An unpublished work of Marconi Data Systems Inc. The software and 
// documentation contained herein are copyrighted works which include 
// confidential information and trade secrets proprietary to Marconi Data 
// Systems Inc. and shall not be copied, duplicated, disclosed or used, 
// in whole or in part, except pursuant to the License Agreement or as 
// otherwise expressly approved by Marconi Data Systems Inc.
//
// -----------------------------------------------------------------------------
//
// Class		:	Mutex
//
// Description	:	Operating System Abstraction Layer
//
// History		: 
//
//  RLX   05/19/00	Adapt to Nucleus.
//  AT  23/06/06    Calypso. Alexey Troshin - Adapt to Windows/Windows CE
// -----------------------------------------------------------------------------

#ifndef MUTEX_H
#define MUTEX_H


// Abstract interface to Mutex object
class _MutexInterface 
{
	
public:
	// Lock/Unlock: return true if the mutex has been obtained successfully.
	virtual bool lock() = 0;
	virtual bool trylock() = 0;
	virtual bool unlock() = 0;
	
	// Resets the mutex- any tasks waiting on the mutex are resumed
	// Calypso. AT - this method is illegal for classic mutex
	//virtual bool reset() = 0;
};


#ifdef NUCLEUS

#include "nucleus.h"

class Mutex_Nucleus : public _MutexInterface 
{

public:

	Mutex_Nucleus(char* name = "MUTEX");
	virtual ~Mutex_Nucleus();

	// Lock/Unlock: return true if the mutex has been obtained successfully.

	bool lock();
	bool trylock();
	bool unlock();

	// Resets the mutex- any tasks waiting on the mutex are resumed
	// Calypso. AT - this method is illegal for classic mutex
	//bool reset();

protected:

	NU_SEMAPHORE	m_mutexCtrl;		// mutex control data.
};

// define queue type for Nucleus platform
typedef Mutex_Nucleus Mutex;


#endif //NUCLEUS


// WIN32 platform version

#ifdef _WIN32

#include <windows.h>


class CrossProcessMutex : public _MutexInterface 
{
	friend class AutoMutex;
public:

	// AT - named Windows mutex is unique, thats why default is unnamed
	explicit CrossProcessMutex(const WCHAR* name);
	virtual ~CrossProcessMutex();

    // Lock/Unlock: return true if the mutex has been obtained successfully.
    bool lock();
	bool trylock();
	bool unlock();

protected:
	// Mutex handle
	HANDLE	m_hCrossProcessMutex;
};

class Mutex : public _MutexInterface 
{
	friend class AutoMutex;
public:

	explicit Mutex();
	virtual ~Mutex();

	// Lock/Unlock: return true if the mutex has been obtained successfully.
	bool lock();
	bool trylock();
	bool unlock();

protected:

	// Mutex handle
	CRITICAL_SECTION	m_csGuard;
	LONG				m_lInitialLockCount;
};


#endif //_WIN32

#endif //MUTEX_H
// AZ added cr-lf at the end of file

