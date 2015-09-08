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

#ifndef AUTOMUTEX_H
#define AUTOMUTEX_H

#include "Mutex.h"

class AutoMutex {

public:

	AutoMutex(Mutex& theMutex);
	AutoMutex(Mutex* pMutex);
	AutoMutex(CrossProcessMutex& theMutex);
	AutoMutex(CrossProcessMutex* pMutex);
	virtual ~AutoMutex();

protected:
	bool				m_bCsType;
	bool				m_bLocked;
	HANDLE				m_hMutex;
	CRITICAL_SECTION*	m_pcsSection;
	
};

#endif
