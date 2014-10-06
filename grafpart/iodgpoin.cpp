// @(#) 1.11 com/src/samples/grafpart/iodgpoin.cpp, odgrafpart, od96nt 2/3/97 19:26:04 [2/5/97 20:45:00]
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odgrafpart
 *
 *   CLASSES: ContentGrafPartPoin
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
//  File:      iodgpoin.cpp
//  Contains:  Class implementation for a Point Object in a 2D-Drawing Container Part
// ************************************************************************

#define ContentGrafPartPoin_Class_Source

#ifndef SOM_Module_GrafPoin_Source
    #define SOM_Module_GrafPoin_Source
#endif  // SOM_Module_GrafPoin_Source

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

#ifndef SOM_ContentGrafPartFigr_xh
    #include "iodgfigr.xh"
#endif // SOM_ContentGrafPartFigr_xh

#ifndef SOM_ContentGrafPartPoin_xih
    #include "iodgpoin.xih"
#endif // SOM_ContentGrafPartPoin_xih


// *************************************************************************
//
//  Class implementation:
//      ContentGrafPartPoin : ContentGrafPartFigr
//
// *************************************************************************

// =========================================================================
//
//      Public Override methods: ContentGrafPartPoin
//
// =========================================================================

// -------------------------------------------------------------------------
// ContentGrafPartPoin --> somInit
//
//     Initialization used at registration time
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartPoinsomInit(ContentGrafPartPoin *somSelf )
{
    SQUAWK("> Invoked ContentGrafPartPoin::somInit()\n");

    /* ContentGrafPartPoinData *somThis = ContentGrafPartPoinGetData(somSelf); */
    ContentGrafPartPoinMethodDebug("ContentGrafPartPoin","ContentGrafPartPoinsomInit");

    // call parent method
    ContentGrafPartPoin_parent_ContentGrafPartFigr_somInit(somSelf);

    // set the objtype
    somSelf->_set_objType(somGetGlobalEnvironment(), COBJ_GRAFPART_POIN);

    SQUAWK("< Leaving ContentGrafPartPoin::somInit()\n");

}   // somInit()


// -------------------------------------------------------------------------
// ContentGrafPartPoin --> MoveBy
//
//      Override ContentObject::MoveBy to update points
//
//      -> public override method
//      -> calls parent first
//      -> the 'offset' is a set of deltas from the origin of the
//          point's bounding rect, expressed as coordinates (not a point)
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartPoinMoveBy(  ContentGrafPartPoin*    somSelf,
                                                    Environment*            ev,
                                                    ODPoint*                offset )
{
    SQUAWK("> Invoked ContentGrafPartPoin::MoveBy(ODPoint*)\n");
    SQUAWK("\tContentGrafPartPoin::MoveBy(ODPoint*): received offset: %d, %d\n", ODFixedToInt(offset->x), ODFixedToInt(offset->y) );

    /* ContentGrafPartPoinData *somThis = ContentGrafPartPoinGetData(somSelf); */
    ContentGrafPartPoinMethodDebug("ContentGrafPartPoin","ContentGrafPartPoinMoveBy");

    // call parent method
    ContentGrafPartPoin_parent_ContentGrafPartFigr_MoveBy(  somSelf,
                                                            ev,
                                                            offset );

    // adjust the bounding rect for the new points
    somSelf->AdjustBoundingRect(ev);

    SQUAWK("< Leaving ContentGrafPartPoin::MoveBy(ODPoint*)\n");

}   // ContentGrafPartPoin::MoveBy(ODPoint)


// -------------------------------------------------------------------------
// ContentGrafPartPoin --> Resize
//
//      Override ContentObject::Resize to update points
//
//     -> public override method
//     -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartPoinResize(  ContentGrafPartPoin*    somSelf,
                                                    Environment*            ev,
                                                    ODPoint*                point,
                                                    ODULong                 flags )
{
    SQUAWK("> Invoked ContentGrafPartPoin::Resize()\n");
    SQUAWK("\tContentGrafPartPoin::Resize(): received endpoint: %d, %d\n",
        ODFixedToInt(point->x), ODFixedToInt(point->y) );

    /* ContentGrafPartPoinData *somThis = ContentGrafPartPoinGetData(somSelf); */
    ContentGrafPartPoinMethodDebug("ContentGrafPartPoin","ContentGrafPartPoinResize");

    // call parent method
    ContentGrafPartPoin_parent_ContentGrafPartFigr_Resize(  somSelf,
                                                            ev,
                                                            point,
                                                            flags );

    // adjust the bounding rect for the new points
    somSelf->AdjustBoundingRect(ev);

    SQUAWK("< Leaving ContentGrafPartPoin::Resize()\n");

}   // ContentGrafPartPoin::Resize()


// -------------------------------------------------------------------------
//  ContentGrafPartPoin --> AdjustBoundingRect
//
//      Adjust a Point's bounding rect to fit it's representation, which is
//          possibly larger than a single pixel
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK ContentGrafPartPoinAdjustBoundingRect(  ContentGrafPartPoin*    somSelf,
                                                                    Environment*            ev )
{
    SQUAWK("> Invoked ContentGrafPartPoin::AdjustBoundingRect()\n");

    /* ContentGrafPartPoinData *somThis = ContentGrafPartPoinGetData(somSelf); */
    ContentGrafPartPoinMethodDebug("ContentGrafPartPoin","ContentGrafPartPoinAdjustBoundingRect");

    // set local buffer from persistant data
    ODPoint pt1;                    // buffers for the point
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure

    // reset the bounding box from the new points, keeping orientation
    ODRect bbox;                                    // declare a buffer for bounding rectangle

    // set the buffer points to the new extents
#ifdef _PLATFORM_OS2_                               // OS2 origin is LLC
    bbox.top    = pt1.y + 1;
    bbox.bottom = pt1.y - 1;
#else                                               // everyone else's origin in ULC
    bbox.top    = pt1.y - 1;
    bbox.bottom = pt1.y + 1;
#endif  // _PLATFORM_OS2_
    bbox.left   = pt1.x - 1;
    bbox.right  = pt1.x + 1;

    somSelf->_set_boundingRect(ev, &bbox);          // set the bounding rectangle from the buffer

    SQUAWK("< Leaving ContentGrafPartPoin::AdjustBoundingRect()\n");

}   // ContentGrafPartPoin::AdjustBoundingRect()


// -------------------------------------------------------------------------
//  ContentGrafPartPoin --> Draw
//
//      Render a poin on the screen
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartPoinDraw(ContentGrafPartPoin*    somSelf,
                                                        Environment*            ev,
                                                        HDraw                   hDraw )
{
    SQUAWK("> Invoked ContentGrafPartPoin::Draw()\n");

#ifdef _PLATFORM_OS2_
    // Instance data for this class, in addition to that defined by ContentGrafPartFigr,
    //   only exists (and is used) on the OS/2 platform, so the following function is only
    //   defined in the iodgpoin.xih file on the OS/2 platform.
    ContentGrafPartPoinData *somThis = ContentGrafPartPoinGetData(somSelf);
#endif  // _PLATFORM_OS2_
    ContentGrafPartPoinMethodDebug("ContentGrafPartPoin","ContentGrafPartPoinDraw");

    // set local buffers from persistant data
    ODPoint pt1;                    // buffers for the points
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure

#if defined (_PLATFORM_OS2_)
    SQUAWK("\tContentGrafPartPoin::Draw(): Drawing poin object for OS2\n");
    _pPt1.x = ODFixedToInt(pt1.x); _pPt1.y = ODFixedToInt(pt1.y);
    SQUAWK("\tContentGrafPartPoin::Draw(): point 1: %lx, %lx\n", pt1.x, pt1.y );
    _pPt1.x = (_pPt1.x)-1; _pPt1.y = (_pPt1.y)-1;
    GpiMove(hDraw, &_pPt1);
    _pPt1.x = (_pPt1.x)+2; _pPt1.y = (_pPt1.y)+2;
    GpiSetColor(hDraw, somSelf->_get_fColor(ev));
    GpiBox(hDraw, DRO_OUTLINEFILL, &_pPt1, 2, 2);
#elif defined (_PLATFORM_WIN32_)
    SQUAWK("\tContentGrafPartPoin::Draw(): Drawing poin object for WIN32\n");
    HBRUSH hbr = CreateSolidBrush(somSelf->_get_fColor(ev));
    SelectObject( hDraw, hbr);
    Rectangle(  hDraw,
        ODFixedToInt(pt1.x)-1, ODFixedToInt(pt1.y)-1,
        ODFixedToInt(pt1.x)+1, ODFixedToInt(pt1.y)+1 );
    DeleteObject(hbr);
#endif // _PLATFORM_???_

    SQUAWK("< Leaving ContentGrafPartPoin::Draw()\n");
    return(kODTrue);

}   // ContentGrafPartPoin::Draw()


// -------------------------------------------------------------------------
//  ContentGrafPartPoin --> ContainsPoint
//
//      Determines whether a given point is on or near an intrinsic point object
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartPoinContainsPoint(   ContentGrafPartPoin*    somSelf,
                                                                    Environment*            ev,
                                                                    ODPoint*                point )
{
    SQUAWK("> Invoked ContentGrafPartPoin::ContainsPoint()\n");

    /* ContentGrafPartPoinData *somThis = ContentGrafPartPoinGetData(somSelf); */
    ContentGrafPartPoinMethodDebug("ContentGrafPartPoin","ContentGrafPartPoinContainsPoint");

    // set local buffers from persistant data
    ODPoint pt1;                    // buffer for the origin point
    pt1 = somSelf->_get_fPt1(ev);   // get copy of origin point from parent figure

    SQUAWK("\tContentGrafPartPoin::ContainsPoint(): received Point: %d, %d\n", ODFixedToInt(point->x), ODFixedToInt(point->y) );
    SQUAWK("\tContentGrafPartPoin::ContainsPoint():   point origin: %d, %d\n", ODFixedToInt(pt1.x), ODFixedToInt(pt1.y) );
    SQUAWK("\tContentGrafPartPoin::ContainsPoint(): X, Y SelectionThresholds: %d, %d\n", kODXSelectionThreshold, kODYSelectionThreshold );

    // do all math in double precision
    struct POINTFL
    {
        double x;
        double y;
    }   Dpt1 =  { (double)pt1.x/65536.,    (double)pt1.y/65536.    },
        Dpt2 =  { (double)point->x/65536., (double)point->y/65536. };

    // examine threshold ranges around origin point
    if ( (Dpt2.x >= Dpt1.x - kODXSelectionThreshold ) &&    // point in x range of origin point
         (Dpt2.x <= Dpt1.x + kODXSelectionThreshold ) &&    //   and
         (Dpt2.y >= Dpt1.y - kODYSelectionThreshold ) &&    // point in y range of origin point
         (Dpt2.y <= Dpt1.y + kODYSelectionThreshold ) )
    {
        SQUAWK("< Leaving ContentGrafPartPoin::ContainsPoint(), returning True (origin)\n");
        return(kODTrue);
    }   // if: origin
    else
    {
        SQUAWK("< Leaving ContentGrafPartPoin::ContainsPoint(), returning False\n");
        return(kODFalse);
    }   // else: origin

}   // ContentGrafPartPoin::ContainsPoint()


// =========================================================================
// End of file: iodgpoin.cpp
// =========================================================================
