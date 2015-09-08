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
// File       : verify
//
// Description: Defines a macro which is similar in operation to the assert
//              macro, however when the NDEBUG compiler flag is set the
//              expression in the verify statement is still inserted into the
//              code.
//
// -----------------------------------------------------------------------------

#ifndef VERIFY_H
#define VERIFY_H

#include <assert.h>

#ifndef verify
	#ifndef _DEBUG
		#define verify(expr) (expr)
	#else
		#define verify(expr) assert(expr)
	#endif
#endif

#endif
