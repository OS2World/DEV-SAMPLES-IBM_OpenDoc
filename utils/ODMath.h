/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odsamples
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
// @(#) 1.9 com/src/samples/utils/ODMath.h, odutilspart, od96os2, odos29712d 10/10/96 16:10:01 [ 3/21/97 17:41:23 ]
/*
	File:		ODMath.h

	Contains:	Math routines (fixed-point and wide) for OpenDoc.

	Written by:	Jens Alfke

	Copyright:	c 1994 by Apple Computer, Inc., all rights reserved.

*/


#ifndef _ODMATH_
#define _ODMATH_

#ifndef _ODTYPES_
#include "ODTypes.h"
#endif

#ifndef _ODMVCLNK_
#include <ODMvcLnk.h>
#endif

typedef double double_t;

struct ODWide {       // 64-bit integer
	ODSLong hi;        // High order longword comes first
	ODULong lo;        // Then low-order (which has no sign bit!)
};

/*
** !! Use these ONLY FOR ASSIGNMENT, never for comparison !!
*/
#define ODFALSE  ((int)0)
#define ODTRUE   ((int)~ODFALSE)

#if defined(_PLATFORM_BIG_ENDIAN_)
#define ODUHIWORD(fixptVar)			(((ODUShort *)&(fixptVar))[0])		// get hi unsined word
#define ODULOWORD(fixptVar)			(((ODUShort *)&(fixptVar))[1])		// get lo unsined word
#define ODFP_INTPART(fixptVar)		(((ODSShort *)&(fixptVar))[0])		// get hi signed word
#define ODFP_FRACTPART(fixptVar)	(((ODUShort *)&(fixptVar))[1])		// get lo unsigned word	
#else // !defined(_PLATFORM_BIG_ENDIAN_)
#define ODUHIWORD(fixptVar)			(((ODUShort *)&(fixptVar))[1])		// get hi unsined word
#define ODULOWORD(fixptVar)			(((ODUShort *)&(fixptVar))[0])		// get lo unsined word
#define ODFP_INTPART(fixptVar)		(((ODSShort *)&(fixptVar))[1])		// get hi signed word
#define ODFP_FRACTPART(fixptVar)	(((ODUShort *)&(fixptVar))[0])		// get lo unsigned word	
#endif // defined(_PLATFORM_BIG_ENDIAN_)

#define	ODFPD_INTPART(wideVar)  	(((ODWide*)wideVar)->hi)
#define	ODFPD_FRACPART(wideVar)		(((ODWide*)wideVar)->lo)

#define	ODFRACT_MAX	((ODULong)0x3fffffff)	/* max value in a 30 bit quantity*/
 

#define	ODSWORD_MAX	((ODSShort)0x7fff)		/* (32767) max value in a       */
									  		/* signed 16 bit quantity       */
#define ODULONG_MAX	((ODULong)0xffffffffUL) /* max value in an unsigned 32  */
									    	/* bit quantity                 */
#define ODUDWORD_CARRY(Exp1 ,Exp2 )			\
				((ODULONG_MAX - (ODULong)(Exp1 )) < (ODULong)(Exp2 ))

/* COMMENTS *****************************************************************
 * Names:
 * 		ODFP_SET(fpVar, swordExp, uwordExp), 
 * 		ODFPD_SET(fpdVar, sdwordExp, udwordExp)
 * 
 *  Desc:
 *  	These macros take a signed integer and an unsigned integer (representing
 * 		the fraction of a fixed point number), and assign them to a fixed point 
 * 		(fixed point double) variable.
 * In:
 * 		s(d)wordExp	- an expression defining the integer part of the variable.
 * 		u(d)wordExp	- an expression defining the fractional part of the variable.
 * Out:
 * 	 	fp(d)Var - the single (double) fixed point variable to which the 2 parts 
 * 	 				are assigned.
 * Ret:
 * 		n/a
 * Notes:
 * 		These macros should only be used to set POSITIVE fixed point values.
 * 
 * END **********************************************************************
 */
#define ODFP_SET(fpVar,swordExp,uwordExp) 					\
		((ODFP_INTPART(fpVar) = (ODSShort)(swordExp)),  	\
		 (ODFP_FRACPART(fpVar) = (ODUShort)(uwordExp)))

#define ODFPD_SET(fpdVar,sdwordExp,udwordExp) 				\
		((ODFPD_INTPART(fpdVar) = (ODSLong)(sdwordExp)),  	\
		 (ODFPD_FRACPART(fpdVar) = (ODULong)(udwordExp)))


const ODFixed kODFixed1				= 0x00010000;
const ODFixed kODFixedHalf			= 0x00008000;
const ODFract kODFract1				= 0x40000000;
const ODFixed kODFixedInfinity		= 0x7FFFFFFF;	// Fract as well
const ODFixed kODFixedMinusInfinity	= 0x80000000;


// Some of these fns are coded in assembly on 68k, so make calling conventions C:
extern "C" {


#define ODFixedRound(a)		((ODSShort)((ODFixed)(a) + kODFixedHalf >> 16))
#define ODIntToFixed(a)		((ODFixed)(a) << 16)
#define ODFixedToFract(a)	((ODFract)(a) << 14)
#define ODFractToFixed(a)	((ODFixed)(a) + 8192L >> 14)
#define ODFixedToFloat(a)  ((double_t)((ODFixed)(a)) / 65536.0)
#define ODFloatToFixed(a)	((ODFixed)((double_t)(a) * 65536.0))


// These fixed-point math routines return infinity (see above) on overflow.

_DLLIMPORTEXPORT_ ODFixed	ODFixedMultiply( ODFixed num1, ODFixed num2 );
_DLLIMPORTEXPORT_ ODFixed	ODFixedDivide( ODFixed num1, ODFixed num2 );
_DLLIMPORTEXPORT_ ODFract	ODFractMultiply( ODFract a, ODFract b );
_DLLIMPORTEXPORT_ ODFract	ODFractDivide( ODFract a, ODFract b );
_DLLIMPORTEXPORT_ ODWide*	ODWideMultiply( ODSLong a, ODSLong b, ODWide *result );

_DLLIMPORTEXPORT_ ODSShort ODWideCompare( const ODWide*, const ODWide* );
_DLLIMPORTEXPORT_ ODWide*	ODWideNegate( ODWide* );
_DLLIMPORTEXPORT_ ODWide*	ODWideShift( ODWide*, ODSShort bits );	// Positive is toward MSB
_DLLIMPORTEXPORT_ ODWide*	ODWideAdd( ODWide*, const ODWide* );
_DLLIMPORTEXPORT_ ODWide*	ODWideSubtract( ODWide*, const ODWide* );

_DLLIMPORTEXPORT_ ODSLong	ODWideDivide( const ODWide *dividend,
							ODSLong divisor, ODSLong *remainder);
_DLLIMPORTEXPORT_ ODULong  ODWideSquareRoot( const ODWide *src );

#define kODIgnoreRemainder  ((ODSLong*)-1L)	// Use as remainder in ODWideDivide

#define ODWideIsLong(w) ((w)->hi ==  0 && (long)(w)->lo >= 0 || \
						  (w)->hi == -1 && (long)(w)->lo < 0)

_DLLIMPORTEXPORT_ ODFract	ODFractSinCos( ODFixed angle, ODFract *cos );

_DLLIMPORTEXPORT_ ODSShort	ODFirstBit( ODSLong );			// Returns index (0-32) of 1st bit


}	// End of extern "C" {

#endif /*_ODMATH_*/
