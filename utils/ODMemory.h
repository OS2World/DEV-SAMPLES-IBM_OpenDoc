/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odsutils
 *
 *   CLASSES: none
 *
 *   ORIGINS: 82,27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1995,1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *   	
 *   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 *   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 *   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 *   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 *   OR PERFORMANCE OF THIS SOFTWARE.
 */
/*====END_GENERATED_PROLOG========================================
 */
/* @(#)Z 1.7 com/src/samples/utils/ODMemory.h, odutilspart, od96os2, odos29712d 97/03/21 17:42:17 (96/10/30 23:28:42) */
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   	
 *   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 *   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 *   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 *   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 *   OR PERFORMANCE OF THIS SOFTWARE.
 */
/*====END_GENERATED_PROLOG========================================
 */
//====START_GENERATED_PROLOG======================================
//
//
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
#ifndef _ODMEMORY_
#define _ODMEMORY_

#ifndef som_h
#include <som.h>
#endif

#ifndef _ODTYPES_
#include <ODTypes.h>
#endif

#include <ErrorDef.xh>

#ifndef _ODEXCEPT_
#include <ODExcept.h>
#endif


//========================================================================================
// Type definitions
//========================================================================================

typedef ODULong ODBlockSize;

//========================================================================================
// Operations on pointer based blocks
//========================================================================================

inline void* ODNewPtr(ODBlockSize blockSize)
{
	void *blockPtr = SOMMalloc(blockSize);
   if (!blockPtr)
      THROW(kODErrOutOfMemory);

	return blockPtr;
}

inline void* ODNewPtrClear(ODBlockSize blockSize)
{
	void *blockPtr = SOMMalloc(blockSize);
   if (!blockPtr)
      THROW(kODErrOutOfMemory);

	memset (blockPtr, '\0', blockSize);
	return blockPtr;
}

inline void ODDisposePtr(void *blockPtr)
{
	if (blockPtr)
		SOMFree(blockPtr);
}


//========================================================================================
// Utility functions
//========================================================================================

inline void		ODBlockMove(const void *from, void *to, ODBlockSize blockSize)
{
	memcpy (to, from, blockSize);
}

#endif /*_ODMEMORY_*/
