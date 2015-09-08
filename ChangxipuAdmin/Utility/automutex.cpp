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
// Class			 : AutoMutex
//
// Description : Automatically locks a mutex on construction and releases
//               on destruction.
//
// SDI 03/13/01  Created
//
// -----------------------------------------------------------------------------
#include "automutex.h"
#include "verify.h"
#include "mutex.h"

#undef assert

#pragma warning(disable:4800)

#define ASSERT_PRINT(exp,file,line) OutputDebugStringW(TEXT("\r\n*** ASSERTION FAILED in ") TEXT(file) TEXT("(") TEXT(#line) TEXT("):\r\n") TEXT(#exp) TEXT("\r\n"))
#define ASSERT_AT(exp,file,line) (void)( (exp) || (ASSERT_PRINT(exp,file,line), DebugBreak(), 0 ) )
#define assert(exp) ASSERT_AT(exp,__FILE__,__LINE__)


AutoMutex::AutoMutex(Mutex& theMutex)
{
	m_bLocked = false;
	m_pcsSection = &theMutex.m_csGuard;
	m_hMutex = INVALID_HANDLE_VALUE;
	m_bCsType = true;
	if (m_pcsSection)
	{
		EnterCriticalSection(m_pcsSection);
		m_bLocked = true;
	}
}

AutoMutex::AutoMutex(Mutex* pMutex)
{
	m_bLocked = false;
	m_pcsSection = &pMutex->m_csGuard;
	m_hMutex = INVALID_HANDLE_VALUE;
	m_bCsType = true;
	if (m_pcsSection)
	{
		EnterCriticalSection(m_pcsSection);
		m_bLocked = true;
	}
}


AutoMutex::AutoMutex(CrossProcessMutex& theMutex) 
{
	m_bCsType = false;
	m_pcsSection = NULL;
	m_bLocked = false;
	m_hMutex = theMutex.m_hCrossProcessMutex;
	if (m_hMutex)
	{
		m_bLocked = (WaitForSingleObject(m_hMutex,INFINITE) == WAIT_OBJECT_0);
		assert(m_bLocked);
	}
}



AutoMutex::AutoMutex(CrossProcessMutex* pMutex) 
{
	m_bCsType = false;
	m_pcsSection = NULL;
	m_bLocked = false;
	m_hMutex = pMutex->m_hCrossProcessMutex;
	if (m_hMutex)
	{
		m_bLocked = (WaitForSingleObject(m_hMutex,INFINITE) == WAIT_OBJECT_0);
		assert(m_bLocked);
	}
}




AutoMutex::~AutoMutex() 
{
	if (m_bLocked)
	{
		if (m_bCsType)
		{
			if (m_pcsSection)
				LeaveCriticalSection(m_pcsSection);
		}
		else
		{
			m_bLocked = ReleaseMutex(m_hMutex);
			assert(m_bLocked);
		}
	}
}
