//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odsamples
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
// @(#) 1.8 com/src/samples/utils/ODMathW.cpp, odutilspart, od96os2, odos29712d 8/19/96 12:26:46 [ 3/21/97 17:41:23 ]
/*
	File:		ODMath.cpp

	Contains:	Math routines (fixed-point and wide) for OpenDoc.

	Owned by:	Jens Alfke
	Written by:	Cary Clark, Georgiann Delaney, Michael Fairman, Dave Good,
				Robert Johnson, Keith McGreggor, Oliver Steele, David Van Brink,
				Chris Yerga
				(Originally from QuickDraw GX source file "math.c")

	Copyright:	c 1987-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
		 <4>	10/24/94	jpa		Compiles w/unprecompiled public headers
									[1186850]
		 <3>	 9/29/94	RA		1189812: Mods for 68K build.
		 <2>	 6/17/94	jpa		Fixed a syntax error in PPC build
		 <1>	 6/15/94	jpa		first checked in
		 ---------------------------Moved to ODSOM project.
		 <1>	  5/9/94	jpa		first checked in
	Notes:
		The PowerPC definitions of many of these functions are already built
		into the Mac OS, so they are compiled here only for 68k. Likewise,
		the 68k definitions of some of these functions are coded in assembly
		language in ODMathM.a, and they are compiled here only for PowerPC.
	
	To Do:
*/

#define _OD_DONT_IMPORT_CPP_

#include <math.h>

#ifndef _ODMATH_
#include "ODMath.h"
#endif


//=============================================================================
// Constants
//=============================================================================


#define longSize		32
#define wideSize		64

#define highBit			((ODULong) 0x80000000)


//=============================================================================
// Wide Math For Non-PowerPC
//=============================================================================
/****************************************************************
ODWideCompare
Title:   Compare ODWide and ODWide => ODSShort
Return:  ODSShort
Notes:
*****************************************************************/
WIN32_DLLEXPORT ODSShort ODWideCompare(const ODWide *a, const ODWide *b)
{
	if (a->hi > b->hi) return 1;
	if (a->hi < b->hi) return -1;
	if (a->lo > b->lo) return 1;
	if (a->lo < b->lo) return -1;
	return 0;
}


/****************************************************************
ODWideNegate
Title:   -ODWide => ODWide
Return:  ODWide
Notes:
*****************************************************************/
WIN32_DLLEXPORT ODWide *
ODWideNegate(register ODWide *dst)
{
	if (dst->lo) {
		dst->lo = -dst->lo;
		dst->hi = ~dst->hi;
	} else
		dst->hi = -dst->hi;
	return dst;
}


/****************************************************************
ODWideShift
Title:   Shift ODWide by ODSShort => ODWide
Return:  ODWide
Notes:   Shift right (shift > 0) or left (shift < 0)
*****************************************************************/
WIN32_DLLEXPORT ODWide *
ODWideShift(register ODWide *src, register ODSShort shift)
{
	register long x = src->hi, y = src->lo;
	if (shift > 0)
		if (shift >= longSize)
		{	src->hi = -(x < 0);
			src->lo = x >> shift - longSize;
			if (shift == longSize && y < 0 || x << wideSize - shift < 0)
				++src->lo || ++src->hi;
		}
		else
		{	src->hi = x >> shift;
			src->lo = x << longSize - shift | (unsigned long)y >> shift;
			if (y << longSize - shift < 0)
				++src->lo || ++src->hi;
		}
	else if ( (shift = -shift) != 0 )
		if (shift >= longSize)
		{	src->hi = y << shift - longSize;
			src->lo = 0;
		}
		else
		{	src->hi = x << shift | (unsigned long)y >> longSize - shift;
			src->lo = y << shift;
		}
	return src;
}


/****************************************************************
ODWideAdd
Title:   ODWide + ODWide => ODWide
Return:  ODWide
Notes:
*****************************************************************/
WIN32_DLLEXPORT ODWide *
ODWideAdd(register ODWide *dst, register const ODWide *src)
{
	dst->lo += src->lo;
	if (dst->lo < src->lo)
		dst->hi += src->hi + 1;
	else
		dst->hi += src->hi;
	return dst;
}


/****************************************************************
ODWideSubtract
Title:   ODWide - ODWide => ODWide
Return:  ODWide
Notes:
*****************************************************************/
WIN32_DLLEXPORT ODWide *
ODWideSubtract(register ODWide *dst, register const ODWide *src)
{
	if (dst->lo < src->lo)
		dst->hi -= src->hi + 1;
	else
		dst->hi -= src->hi;
	dst->lo -= src->lo;
	return dst;
}


/****************************************************************
ODWideMultiply
Title:   ODSLong * ODSLong => ODWide
Return:  ODWide
Notes:
*****************************************************************/
WIN32_DLLEXPORT ODWide* ODWideMultiply(ODSLong num1, ODSLong num2, ODWide *product)
{
	ODULong		ans, ans_int, ans_fract; 
	ODULong		ac, ad, bc, bc_fract;
	int			negative;
	
	negative = ODFALSE;
	
	if (num1 < 0)
	{
		num1 = -num1;
		negative = ODTRUE;
	}
	if (num2 < 0)
	{
		num2 = -num2;
		negative = !negative;
	}

	/*
	 *	Abs values are taken for 2 reasons: to make overflow/carry
	 *	checking simpler, and to avoid mixed mode 32 bit multiplies
	 *	of ODSLongs with ODULongs, which must be done in software
	 * 	subroutines on some (most? (all?)) machines.
	 *
	 * ODUHIWORD is used instead of ODFP_INTPART so that the integer part of
	 * the fixed number will be treated as unsigned.
	 */

	ac = (ODULong) ODUHIWORD(num1) 	* (ODULong) ODUHIWORD(num2);
	ad = (ODULong) ODUHIWORD(num1) 	* (ODULong) ODULOWORD(num2);
	bc = (ODULong) ODULOWORD(num1) * (ODULong) ODUHIWORD(num2);

	/*
	 * Start product with bd term rounded to 16 bits.
	 * IntPart set to zero, (32-bit) overflow not possible here
	 */
	bc_fract = ((ODULong)ODULOWORD(num1) * (ODULong)ODULOWORD(num2));
	ans = bc_fract;
	ans = ODUHIWORD(ans); 

	ans += ad;

	ans += bc;
	
	ans_int = ODFP_INTPART(ans) + ac;
	ans_fract = (ans << 16) + ODFP_FRACTPART(bc_fract);
	
	ODFPD_SET(product, (negative) ? - ((ODSLong) ans_int) : ans_int, ans_fract);
	return(product);

}

/****************************************************************
ODWideDivide
Title:   ODWide / ODFixed => ODFixed
Return:  ODWide	(quotient).
Out:     rem (remainder)
Notes:
*****************************************************************/
WIN32_DLLEXPORT ODSLong ODWideDivide(const ODWide *dividend, long divisor, long *rem)
{
	ODWide temp;
	long quotient;
	int negative = kODFalse, i;

	if (divisor == 0)
		return (kODFixedMinusInfinity);

	temp = *dividend;
	
	if (temp.hi < 0)
	{
		ODWideNegate(&temp);
		negative = kODTrue;
	}
	if (divisor < 0)
	{
		divisor = -divisor;
		negative = !negative;
	}

	if (temp.hi >= divisor)
		return (kODFixedMinusInfinity);

	temp.hi <<= 1;
	if ((ODSLong)temp.lo < 0)
		temp.hi |= 1;
	if ((ODULong) temp.hi >= divisor)
		return (kODFixedMinusInfinity);
	temp.lo <<= 1;

	quotient = 0;
	for (i = 0; i < 31; i++)
	{
		quotient <<= 1;
		temp.hi <<= 1;
		if ((ODSLong)temp.lo < 0)
			temp.hi |= 1;
		temp.lo <<= 1;

		if ((ODULong) temp.hi >= divisor)
		{
			quotient |= 1;
			temp.hi -= divisor;
		}
	}

	if (negative)
		quotient = -quotient;

	if (rem && rem != kODIgnoreRemainder)
		*rem = temp.hi;
	
	return quotient;
}


/****************************************************************
ODWideSquareRoot
Title:   Square Root of ODWide => ODFixed
Return:  ODFixed
Notes:   If input negative, result set to kODFixedInfinity.
*****************************************************************/
WIN32_DLLEXPORT ODULong ODWideSquareRoot(const ODWide *src)
{
	if(src->hi == 0 && src->lo == 0)
		return 0;

	if(src->hi < 0)
		return kODFixedInfinity;

	double d = (double)src->hi + (double)src->lo / 4294967296.0;
	double s = sqrt(d);

	return ODFloatToFixed(s);
}

/****************************************************************
ODFractMultiply
Title:   ODFract * ODFract => ODFract
Return:  ODFract	(product).
Notes:
*****************************************************************/
WIN32_DLLEXPORT ODFract	ODFractMultiply( ODFract num1, ODFract num2 )
{
	ODULong		ans, ac, ad, bc;
	int			negative;
	ODFract		product;
	
	negative = ODFALSE;
	
	if (num1 < 0)
	{
		num1 = -num1;
		negative = ODTRUE;
	}
	if (num2 < 0)
	{
		num2 = -num2;
		negative = !negative;
	}



	ac = (ODULong) (num1 >> 30) 	* (ODULong) (num2 >> 30);
	ad = (ODULong) (num1 >> 30) 	* (ODULong) (num2 & ODFRACT_MAX);
	bc = (ODULong) (num1 & ODFRACT_MAX) * (ODULong) (num2 >> 30);


	/*
	 * Start product with bd term rounded to 30 bits.
	 * IntPart set to zero, (32-bit) overflow not possible here
	 */
	ans = 0;

	ans += bc;
	
	ans += ad;

	ac = ac << 30;
		
	ans += ac;

	product = (negative) ? - ((ODSLong) ans) : ans;
	
	return(product);
}

/****************************************************************
ODFractDivide
Title:   ODFract / ODFract => ODFract
Return:  ODFract	(quotient).
Notes:   If overflow, quotient set to kODFixedMinusInfinity or kODFixedInfinity.
*****************************************************************/
WIN32_DLLEXPORT ODFract	ODFractDivide( ODFract dividend, ODFract divisor )
{
 	ODFixed  quotient;
	register int i;				/* loop variable */
	int	negative;				/* flag as to whether result is negative */
	ODULong	int_part;			/* integer part of result */
	ODULong	frac_part;			/* fractional part of result */
	ODULong	remainder;
	ODULong	my_dividend;
	ODULong	my_divisor;
	ODULong	my_quotient;
	int	overflow;

	my_divisor = (divisor >= 0) ? divisor : -divisor;
	negative = divisor >> 30;

	if (dividend >= 0)
	{
		my_dividend = dividend;
	}
	else
	{
		negative = ~negative;
		my_dividend = -(dividend);
	}

	if (my_divisor == 0)			/* check for divide by 0 */
	{
		quotient = (negative < 0) ? kODFixedMinusInfinity : kODFixedInfinity;
		return (quotient);
	}

	int_part = my_dividend / my_divisor;
	remainder = my_dividend - (my_divisor * int_part);

	if ( (int_part > 0x8000) || (int_part == 0x8000 && negative > 0) )
	{
		quotient = (negative < 0) ? kODFixedMinusInfinity : kODFixedInfinity;
		return (quotient);
	}

	for (frac_part = i = 0; (remainder != 0) && (i < 30); i++)
	{
		frac_part <<= 1;
		remainder <<= 1;
		if (remainder >= my_divisor)
		{
			frac_part += 1;
			remainder -= my_divisor;
		}
	}

	frac_part <<= (30 - i);

	/* round up */
	if ((remainder << 1) >= my_divisor)
	{
		frac_part++;					/* this could cause overflow
										 * when added to my_quotient! 
										 */
	}

	/* note that the fractional part could contain more than 16 bits */

	my_quotient = 0;
	my_quotient = (ODSShort)int_part << 30;
	overflow = ODUDWORD_CARRY(my_quotient, frac_part);
	my_quotient += frac_part;
	overflow |= (my_quotient > 0x80000000)
				 || ((my_quotient == 0x80000000) && (negative >= 0));
	
	if (overflow)
	{
		quotient = (negative < 0) ? kODFixedMinusInfinity : kODFixedInfinity;
		return (quotient);
	}

	quotient = (negative >= 0) ? (ODFixed) my_quotient : -((ODFixed)my_quotient);
	
	return (quotient);

}


/****************************************************************
ODFixedMultiply
Title:   ODFixed * ODFixed => ODFixed
Return:  ODFixed	(product).
Notes:   Since there is limited precision, accuracy may be lost in the
         fractional part.  If overflow, product set to
         kODFixedMinusInfinity or kODFixedInfinity.
*****************************************************************/
WIN32_DLLEXPORT ODFixed ODFixedMultiply(ODFixed num1, ODFixed num2)
{
	ODULong		ans, ac, ad, bc;
	int			negative, overflow;
	ODFixed		product;
	
	negative = ODFALSE;
	
	if (num1 < 0)
	{
		num1 = -num1;
		negative = ODTRUE;
	}
	if (num2 < 0)
	{
		num2 = -num2;
		negative = !negative;
	}


	/*
	 *	num1 = a*2^16 + b; num2 = c*2^16 + d
	 *	product = (ax+b)*(cx + d) = acx^2+(ad+bc)x + bd, 
	 *	shifted right 16 bits to realign radix point.
	 *
	 *	Abs values are taken for 2 reasons: to make overflow/carry
	 *	checking simpler, and to avoid mixed mode 32 bit multiplies
	 *	of ODSLongs with ODULongs, which must be done in software
	 * 	subroutines on some (most? (all?)) machines.
	 *
	 * ODUHIWORD is used instead of ODFP_INTPART so that the integer part of
	 * the fixed number will be treated as unsigned.
	 */


	ac = (ODULong) ODUHIWORD(num1) 	* (ODULong) ODUHIWORD(num2);
	ad = (ODULong) ODUHIWORD(num1) 	* (ODULong) ODULOWORD(num2);
	bc = (ODULong) ODULOWORD(num1) * (ODULong) ODUHIWORD(num2);


	/*
	 * Start product with bd term rounded to 16 bits.
	 * IntPart set to zero, (32-bit) overflow not possible here
	 */
	ans = ((ODULong)ODULOWORD(num1) * (ODULong)ODULOWORD(num2));
	ans = ODUHIWORD(ans); 

	overflow = ODUDWORD_CARRY(ans, ad); 
	ans += ad;

	overflow |= ODUDWORD_CARRY(ans, bc);
	ans += bc;
	
	/* First overflow check is for kODFixedMinusInfinity * 1 */
	if ( (ac == 0x00008000) && (ans == 0L) && negative )
	{
		product = kODFixedMinusInfinity;
		return(product);
	}

	if (ac > ODSWORD_MAX)	/* does ac occupy high order word? */
	{
		goto OverFlow1;
	}


//	ODUHIWORD(ac) = ODULOWORD(ac);
//	ODULOWORD(ac) = 0;
	ac = ac << 16;
		
	overflow |= ODUDWORD_CARRY(ans, ac);
	ans += ac;

	if (overflow || (ans > (ODULong)ODULONG_MAX))
	{
		goto OverFlow1;
	}

	product = (negative) ? - ((ODSLong) ans) : ans;
	
	return(product);

OverFlow1:
	
	product = (negative) ? kODFixedMinusInfinity : kODFixedInfinity;
	return (product);

}

/****************************************************************
ODFixedDivide
Title:   ODFixed / ODFixed => ODFixed
Return:  ODFixed	(quotient).
Notes:   If overflow, quotient set to kODFixedMinusInfinity or kODFixedInfinity.
*****************************************************************/
WIN32_DLLEXPORT ODFixed ODFixedDivide(ODFixed dividend, ODFixed divisor)
{
 	ODFixed  quotient;
	register int i;				/* loop variable */
	int	negative;				/* flag as to whether result is negative */
	ODULong	int_part;			/* integer part of result */
	ODULong	frac_part;			/* fractional part of result */
	ODULong	remainder;
	ODULong	my_dividend;
	ODULong	my_divisor;
	ODULong	my_quotient;
	int	overflow;

	my_divisor = (divisor >= 0) ? divisor : -divisor;
	negative = ODFP_INTPART(divisor);

	if (dividend >= 0)
	{
		my_dividend = dividend;
	}
	else
	{
		negative = ~negative;
		my_dividend = -(dividend);
	}

	if (my_divisor == 0)			/* check for divide by 0 */
	{
		quotient = (negative < 0) ? kODFixedMinusInfinity : kODFixedInfinity;
		return (quotient);
	}

	int_part = my_dividend / my_divisor;
	remainder = my_dividend - (my_divisor * int_part);

	/*	
	 *	If intpart (which is positive) is too big to fit in 16 bits signed,
	 *	then overflow.
	 *	Second clause is so 0x80000000 / 0x00010000 will not signal
	 *	overflow, but 0x80000000 / 0xffff0000 will signal overflow
	 */
	if ( (int_part > 0x8000) || (int_part == 0x8000 && negative > 0) )
	{
		quotient = (negative < 0) ? kODFixedMinusInfinity : kODFixedInfinity;
		return (quotient);
	}

	for (frac_part = i = 0; (remainder != 0) && (i < 16); i++)
	{
		frac_part <<= 1;
		remainder <<= 1;
		if (remainder >= my_divisor)
		{
			frac_part += 1;
			remainder -= my_divisor;
		}
	}

	frac_part <<= (16 - i);

	/* round up */
	if ((remainder << 1) >= my_divisor)
	{
		frac_part++;					/* this could cause overflow
										 * when added to my_quotient! 
										 */
	}

	/* note that the fractional part could contain more than 16 bits */

	my_quotient = 0;
	ODFP_INTPART(my_quotient) = (ODSShort)int_part;
	overflow = ODUDWORD_CARRY(my_quotient, frac_part);
	my_quotient += frac_part;
	overflow |= (my_quotient > 0x80000000)
				 || ((my_quotient == 0x80000000) && (negative >= 0));
	
	if (overflow)
	{
		quotient = (negative < 0) ? kODFixedMinusInfinity : kODFixedInfinity;
		return (quotient);
	}

	quotient = (negative >= 0) ? (ODFixed) my_quotient : -((ODFixed)my_quotient);
	
	return (quotient);

}


/****************************************************************
ODFirstBit
Title:   ODSLong
Return:  ODSShort
Notes:   Returns bit position of first non-zero bit, starting
         with the least significant bit.  Position of least
         significant bit is zero.  If all bits are zero,
         returns -1.
*****************************************************************/
WIN32_DLLEXPORT ODSShort
ODFirstBit( ODSLong x )
{
	ODSShort bit = 0;

	if (x == 0)
		return -1;

	if (x >= 1UL << 16)
		bit += 16, x >>= 16;
	if (x >= 1UL << 8)
		bit += 8, x >>= 8;
	if (x >= 1UL << 4)
		bit += 4, x >>= 4;
	if (x >= 1UL << 2)
		bit += 2, x >>= 2;
	if (x >= 1UL << 1)
		bit += 1;
	return bit;
}
