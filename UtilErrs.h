//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odutils
//
//   CLASSES: none
//
//   ORIGINS: 82,27
//
//
//   (C) COPYRIGHT International Business Machines Corp. 1995,1996
//   All Rights Reserved
//   Licensed Materials - Property of IBM
//   US Government Users Restricted Rights - Use, duplication or
//   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//   	
//   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
//   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
//   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
//   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
//   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
//   OR PERFORMANCE OF THIS SOFTWARE.
//
//====END_GENERATED_PROLOG========================================
//
// @(#) 1.5 com/src/utils/include/UtilErrs.h, odutils, od96os2, odos29712d 3/14/97 16:54:49 [ 3/21/97 17:21:37 ]
/*
	File:		UtilErrs.h

	Contains:	Error codes for various OpenDoc utilities. The error codes are
				gathered together here in order to avoid numbering conflicts
				and to allow for reuse.

	Owned by:	Nick Pilch

	Copyright:	(C) 1995 by Apple Computer, Inc., all rights reserved.

*/

#ifndef _UTILERRS_
#define _UTILERRS_

#ifndef _ODTYPES_
#include "ODTypes.h"
#endif

//=====================================================================================
// Error constants
//=====================================================================================

const ODError kODErrSOMException		= -29849; // Except

const ODError kODErrFileClosed			= -29848; // PlfmFile
const ODError kODErrFileOpened			= -29847; // PlfmFile

const ODError kODErrCantLoadSOMClass	= -29846; // ODNewObj

const ODError kODErrAssertionFailed		= -29845; // ODDebug

const ODError kODErrReadErr            	= -29844; // BndNSUtl
const ODError kODErrWriteErr           	= -29843; // BndNSUtl

const ODError kODErrHashValueSizeTooBig = -29842; // AEHshTbl, SIHshTbl

const ODError kODErrInvalidKey          = -29841; // StrHshTb

const ODError kODErrShapeTooComplex     = -29840; // AltPoly: Polygon shape is too huge for QuickDraw
#if defined(_PLATFORM_WIN32_) || defined(_PLATFORM_OS2_) || defined(_PLATFORM_UNIX_)
const ODError kODErrEndOfFile			= -29839; // PlfmFile
#endif // defined(_PLATFORM_WIN32_) || defined(_PLATFORM_OS2_) || defined(_PLATFORM_UNIX_)

// Error codes up to -29830 are available for future expansion.

#endif /* _UTILERRS_ */
