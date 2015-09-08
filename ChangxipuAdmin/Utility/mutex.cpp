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
// Note			:	Lock/Unlock has to be called in pair because of the nature
//					of the underlining counting semaphore.
//
// History		: 
//
// RLX  05/19/00	Adapt to Nucleus.
//  AT  23/06/06    Calypso. Alexey Troshin - Adapt to Windows/Windows CE
// -----------------------------------------------------------------------------

#include <Windows.h>
#include "mutex.h"
#include <memory.h>					// memset()
//#include "system.h"
//#include "vjstring.h"
#include <string> 
using namespace std;

#ifdef NUCLEUS
// Nucleus platform

// ----------------------------------------------------------------------------
//
//	Ctors & Dtor
//
// ----------------------------------------------------------------------------

Mutex_Nucleus::Mutex_Nucleus(char* name)
{
	// Initialize the control data.
	memset(&m_mutexCtrl, 0, sizeof(m_mutexCtrl));

	// Create Nucleus Semaphore
  if(NU_Create_Semaphore(&m_mutexCtrl, name, 1, NU_PRIORITY) != NU_SUCCESS)
		sysErr(RTOS_FAIL);
}

Mutex_Nucleus::~Mutex_Nucleus()
{
	if(NU_Delete_Semaphore(&m_mutexCtrl) != NU_SUCCESS)
		sysErr(RTOS_FAIL);
}

// ----------------------------------------------------------------------------
//
//	lock
//
//	Description: Lock the mutex; Suspend if mutex already reserved.
//
// ----------------------------------------------------------------------------

bool Mutex_Nucleus::lock()
{
	return(NU_Obtain_Semaphore(&m_mutexCtrl, NU_SUSPEND) == NU_SUCCESS);
}

// ----------------------------------------------------------------------------
//
//	trylock
//
//	Description: Lock the mutex; Don't suspend even if mutex already reserved.
//
// ----------------------------------------------------------------------------

bool Mutex_Nucleus::trylock()
{
	return(NU_Obtain_Semaphore(&m_mutexCtrl, NU_NO_SUSPEND) == NU_SUCCESS);
}

// ----------------------------------------------------------------------------
//
//	unlock
//
//	Description: Release the mutex.
//
// ----------------------------------------------------------------------------

bool Mutex_Nucleus::unlock()
{
	return(NU_Release_Semaphore(&m_mutexCtrl) == NU_SUCCESS);
}

bool Mutex_Nucleus::reset()
{
	return(NU_Reset_Semaphore(&m_mutexCtrl, 1) == NU_SUCCESS);
}

#endif //NUCLEUS


#ifdef _WIN32

#include <tchar.h>


CrossProcessMutex::CrossProcessMutex(const WCHAR* name)
{
	// create Windows mutex
	if (name)
	{
		wstring		wname; // convert ASCII string to unicode VJString

		wname = _T("ChangxipuSQLMutex");
		
		m_hCrossProcessMutex = CreateMutex(NULL,FALSE,wname.c_str());
		//m_hCrossProcessMutex = CreateMutex(NULL,FALSE,wname.getBuffer());
	}
	else m_hCrossProcessMutex = CreateMutex(NULL,FALSE,NULL);
		
	
	if (!m_hCrossProcessMutex)
	{
		//sysErr(RTOS_FAIL);
		return;
	}
}

CrossProcessMutex::~CrossProcessMutex()
{
	if (m_hCrossProcessMutex)
		CloseHandle(m_hCrossProcessMutex);
}




bool CrossProcessMutex::lock()
{
	DWORD	dwRetCode;

	dwRetCode = WaitForSingleObject(m_hCrossProcessMutex,INFINITE);
	return (WAIT_OBJECT_0 == dwRetCode);
}



bool CrossProcessMutex::trylock()
{
	DWORD	dwRetCode;
	
	dwRetCode = WaitForSingleObject(m_hCrossProcessMutex,0);
	return (WAIT_OBJECT_0 == dwRetCode);
}



bool CrossProcessMutex::unlock()
{
	BOOL bRetCode;

	bRetCode = ReleaseMutex(m_hCrossProcessMutex);
	return (bRetCode == TRUE);
}


Mutex::Mutex()
{
	InitializeCriticalSection(&m_csGuard);
	m_lInitialLockCount = m_csGuard.LockCount;
}

Mutex::~Mutex()
{
//	assert(m_csGuard.LockCount == m_lInitialLockCount);
	DeleteCriticalSection(&m_csGuard);
}




bool Mutex::lock()
{
	EnterCriticalSection(&m_csGuard);
	return true;
}



bool Mutex::trylock()
{
	return (TryEnterCriticalSection(&m_csGuard) != 0);
}



bool Mutex::unlock()
{
	LeaveCriticalSection(&m_csGuard);
	return true;
}

#endif //_WIN32