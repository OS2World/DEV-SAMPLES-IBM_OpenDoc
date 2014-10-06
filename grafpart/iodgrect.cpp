// @(#) 1.8 com/src/samples/grafpart/iodgrect.cpp, odgrafpart, od96nt 2/3/97 19:26:07 [2/5/97 20:44:57]
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odgrafpart
 *
 *   CLASSES: ContentGrafPartRect
 *
 *   ORIGINS: 27
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

// *********************************************************************
//  File:      iodgrect.cpp
//  Contains:  Class implementation for a Rect Object in a 2D-Drawing Container Part
// ************************************************************************

#define ContentGrafPartRect_Class_Source

#ifndef SOM_Module_GrafRect_Source
    #define SOM_Module_GrafRect_Source
#endif  // SOM_Module_GrafRect_Source

// GrafPart's includes
#ifndef _IODGCOMM_CPP_
   #include <iodgcomm.cpp>
#endif   // _IODGCOMM_CPP_

// GrafPart's constants & defines
#ifndef _GRAFPART_HPP_
   #include <iodgraph.hpp>
#endif   // _GRAFPART_HPP_

// support use of temporary objects (Initialize & Uninitialize)
#ifndef _TEMPOBJ_
    #include <TempObj.h>
#endif // _TEMPOBJ_

// support StorageUnit function
#ifndef _STORUTIL_
    #include <StorUtil.h>
#endif  // _STORUTIL_

// support math function (ContainsPoint)
#ifndef __math_h
    #include <math.h>
#endif  // __math_h

// includes for native drawing functions
#if defined(_PLATFORM_WIN32_)
    #include <windows.h>
    #include <winuser.h>
    #include <wingdi.h>
#elif defined(_PLATFORM_OS2_)
    #include <ODos2.h>
#endif // _PLATFORM_???_


// local function support includes
#ifndef SOM_GrafPart_xh
    #include "iodgraph.xh"
#endif // SOM_GrafPart_xh

#ifndef SOM_ContentGrafPartLine_xh
    #include "iodgline.xh"
#endif // SOM_ContentGrafPartLine_xh

#ifndef SOM_ContentGrafPartRect_xih
    #include "iodgrect.xih"
#endif // SOM_ContentGrafPartRect_xih


// *************************************************************************
//
//  Class implementation:
//      ContentGrafPartRect : ContentGrafPartLine
//
// *************************************************************************

// =========================================================================
//
//      Public Override methods: ContentGrafPartRect
//
// =========================================================================

// -------------------------------------------------------------------------
// ContentGrafPartRect --> somInit
//
//     Initialization used at registration time
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartRectsomInit(ContentGrafPartRect *somSelf )
{
    SQUAWK("> Invoked ContentGrafPartRect::somInit()\n");

    /* ContentGrafPartRectData *somThis = ContentGrafPartRectGetData(somSelf); */
    ContentGrafPartRectMethodDebug("ContentGrafPartRect","ContentGrafPartRectsomInit");

    // call parent method
    ContentGrafPartRect_parent_ContentGrafPartLine_somInit(somSelf);

    // set the objtype
    somSelf->_set_objType(somGetGlobalEnvironment(), COBJ_GRAFPART_RECT);

    // set the initial values of the the points for a rect to the origin (0,0;0,0)
    ODPoint pPt = {0,0};
    somSelf->_set_fPt2(somGetGlobalEnvironment(), &pPt);    // set second point to 0,0

    SQUAWK("< Leaving ContentGrafPartRect::somInit()\n");

}   // somInit()


// -------------------------------------------------------------------------
//  ContentGrafPartRect --> Draw
//
//      Render a rect on the screen
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartRectDraw(ContentGrafPartRect*    somSelf,
                                                        Environment*            ev,
                                                        HDraw                   hDraw )
{
    SQUAWK("> Invoked ContentGrafPartRect::Draw()\n");

#ifdef _PLATFORM_OS2_
    // Instance data for this class, in addition to that defined by ContentGrafPartFigr,
    //   only exists (and is used) on the OS/2 platform, so the following function is only
    //   defined in the iodgrect.xih file on the OS/2 platform.
    ContentGrafPartRectData *somThis = ContentGrafPartRectGetData(somSelf);
#endif  // _PLATFORM_OS2_
    ContentGrafPartRectMethodDebug("ContentGrafPartRect","ContentGrafPartRectDraw");

    // set local buffers from persistant data
    ODPoint pt1, pt2;               // buffers for the points
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure
    pt2 = somSelf->_get_fPt2(ev);   // get endpoint from local instance data

#if defined (_PLATFORM_OS2_)
    SQUAWK("\tContentGrafPartRect::Draw(): Drawing rect object for OS2\n");
    _pPt1.x = ODFixedToInt(pt1.x); _pPt1.y = ODFixedToInt(pt1.y);
    SQUAWK("\tContentGrafPartRect::Draw(): point 1: %lx, %lx\n", pt1.x, pt1.y );
    _pPt2.x = ODFixedToInt(pt2.x); _pPt2.y = ODFixedToInt(pt2.y);
    SQUAWK("\tContentGrafPartRect::Draw(): point 2: %lx, %lx\n", pt2.x, pt2.y );
    GpiSetColor(hDraw, somSelf->_get_fColor(ev));
    GpiMove(hDraw, &_pPt1);
    GpiBox(hDraw, DRO_OUTLINEFILL, &_pPt2, 0, 0);
#elif defined (_PLATFORM_WIN32_)
    SQUAWK("\tContentGrafPartRect::Draw(): Drawing rect object for WIN32\n");
    HBRUSH hbr = CreateSolidBrush( somSelf->_get_fColor(ev) );
    SelectObject( hDraw, hbr);
    HPEN pen = CreatePen(PS_SOLID, 0, somSelf->_get_fColor(ev)) ;
    SelectObject( hDraw, pen) ;
    Rectangle(  hDraw,
        ODFixedToInt(pt1.x), ODFixedToInt(pt1.y),
        ODFixedToInt(pt2.x), ODFixedToInt(pt2.y) );
    DeleteObject(hbr);
    DeleteObject(pen) ;
#endif // _PLATFORM_???_

    SQUAWK("< Leaving ContentGrafPartRect::Draw()\n");
    return(kODTrue);

}   // ContentGrafPartRect::Draw()


// -------------------------------------------------------------------------
//  ContentGrafPartRect --> ContainsPoint
//
//      Determines whether a given point is on or near a rect
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartRectContainsPoint(   ContentGrafPartRect*    somSelf,
                                                                    Environment*            ev,
                                                                    ODPoint*                point )
{
    SQUAWK("> Invoked ContentGrafPartRect::ContainsPoint()\n");

    /* ContentGrafPartRectData *somThis = ContentGrafPartRectGetData(somSelf); */
    ContentGrafPartRectMethodDebug("ContentGrafPartRect","ContentGrafPartRectContainsPoint");

    // set local buffers from persistant data
    ODPoint pt1, pt2;               // buffers for the points
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure
    pt2 = somSelf->_get_fPt2(ev);   // get endpoint from local instance data

    SQUAWK("\tContentGrafPartRect::ContainsPoint(): received Point: %d,%d\n", ODFixedToInt(point->x), ODFixedToInt(point->y));
    SQUAWK("\tContentGrafPartRect::ContainsPoint(): rectangle extents: %d, %d; %d, %d\n", ODFixedToInt(pt1.x), ODFixedToInt(pt1.y), ODFixedToInt(pt2.x), ODFixedToInt(pt2.y) );
    SQUAWK("\tContentGrafPartRect::ContainsPoint(): X, Y SelectionThresholds: %d, %d\n", kODXSelectionThreshold, kODYSelectionThreshold );

    // do all math in double precision
    struct POINTFL
    {
        double x;
        double y;
    }   Dpt1 =  { (double)pt1.x/65536.,     (double)pt1.y/65536.   },
        Dpt2 =  { (double)pt2.x/65536.,     (double)pt2.y/65536.   },
        Dpt3 =  { (double)point->x/65536.,  (double)point->y/65536.};

    double Dtx = (double)kODXSelectionThreshold/65536.; // the x selection threshold
    double Dty = (double)kODXSelectionThreshold/65536.; // the y selection threshold
    double Dd;                                          // distance between point and rect
    double dx = (Dpt2.x - Dpt1.x);                      // delta x
    double dy = (Dpt2.y - Dpt1.y);                      // delta y
    double m, intercept_1, intercept_2, x_intersect, y_intersect;

#ifdef _PLATFORM_OS2_
    #define TOP(a,b,t) ( max(a,b) + t )
    #define BOT(a,b,t) ( min(a,b) - t )
#else
    #define TOP(a,b,t) ( min(a,b) - t )
    #define BOT(a,b,t) ( max(a,b) + t )
#endif  // _PLATFORM_OS2_

    // examine threshold ranges around each line of the rectangle
    if ( ( ( Dpt3.x >= Dpt1.x - Dtx )                   &&  // point in x range of left vertical
           ( Dpt3.x <= Dpt1.x + Dtx )                   &&  //   and
           ( Dpt3.y >= TOP( Dpt1.y, Dpt2.y,   Dty ) )   &&  // point in y range of left vertical
           ( Dpt3.y <= BOT( Dpt1.y, Dpt2.y,   Dty ) ) ) ||  //     or
         ( ( Dpt3.x >= Dpt2.x - Dtx )                   &&  // point in x range of right vertical
           ( Dpt3.x <= Dpt2.x + Dtx )                   &&  //   and
           ( Dpt3.y >= TOP( Dpt1.y, Dpt2.y,   Dty ) )   &&  // point in y range of right vertical
           ( Dpt3.y <= BOT( Dpt1.y, Dpt2.y,   Dty ) ) ) ||  //     or
         ( ( Dpt3.x >= min( Dpt1.x, Dpt2.x) - Dtx )     &&  // point in x range of top horizontal
           ( Dpt3.x <= max( Dpt1.x, Dpt2.x) + Dtx )     &&  //   and
           ( Dpt3.y >= min( Dpt1.y, Dpt2.y) - Dty )     &&  // point in y range of top horizontal
           ( Dpt3.y <= max( Dpt1.y, Dpt2.y) + Dty ) )   ||  //     or
         ( ( Dpt3.x >= min( Dpt1.x, Dpt2.x) - Dtx )     &&  // point in x range of bottom horizontal
           ( Dpt3.x <= max( Dpt1.x, Dpt2.x) + Dtx )     &&  //   and
           ( Dpt3.y >= max( Dpt1.y, Dpt2.y) + Dty )     &&  // point in y range of bottom horizontal
           ( Dpt3.y <= min( Dpt1.y, Dpt2.y) - Dty ) ) )
    {
        SQUAWK("< Leaving ContentGrafPartRect::ContainsPoint(), returning True (edges)\n");
        return(kODTrue);
    }   // if: edges
    else                                                // determine distance of point from rect
    {
        SQUAWK("< Leaving ContentGrafPartRect::ContainsPoint(), returning False\n");
        return(kODFalse);
    }   // else: edges

}   // ContentGrafPartRect::ContainsPoint()


// =========================================================================
// End of file: GrafRect.cpp
// =========================================================================
