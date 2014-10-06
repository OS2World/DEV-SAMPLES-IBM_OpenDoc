// @(#) 1.26 com/src/samples/grafpart/iodgline.cpp, odgrafpart, od96os2, odos29712d 2/7/97 17:41:48 [3/21/97 17:45:36]
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odgrafpart
 *
 *   CLASSES: ContentGrafPartLine
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
//  File:      iodgline.cpp
//  Contains:  Class implementation for a Line Object in a 2D-Drawing Container Part
// ************************************************************************

#define ContentGrafPartLine_Class_Source

#ifndef SOM_Module_GrafLine_Source
    #define SOM_Module_GrafLine_Source
#endif  // SOM_Module_GrafLine_Source

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

#ifndef SOM_ContentGrafPartLine_xih
    #include "iodgline.xih"
#endif // SOM_ContentGrafPartLine_xih


// *************************************************************************
//
//  Class implementation:
//      ContentGrafPartLine : ContentGrafPartFigr
//
// *************************************************************************

// =========================================================================
//
//      Public Override methods: ContentGrafPartLine
//
// =========================================================================

// -------------------------------------------------------------------------
// ContentGrafPartLine --> somInit
//
//     Initialization used at registration time
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartLinesomInit(ContentGrafPartLine *somSelf )
{
    SQUAWK("> Invoked ContentGrafPartLine::somInit()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLinesomInit");

    // call parent method
    ContentGrafPartLine_parent_ContentGrafPartFigr_somInit(somSelf);

    // set the objtype
    somSelf->_set_objType(somGetGlobalEnvironment(), COBJ_GRAFPART_LINE);

    // set the initial values of the the points for a line to the origin (0,0;0,0)
    memset(&_fPt2, 0, sizeof(ODPoint) );            // set second point to 0,0

    SQUAWK("< Leaving ContentGrafPartLine::somInit()\n");

}   // somInit()


// -------------------------------------------------------------------------
// ContentGrafPartLine --> somUninit
//
//     Uninitialization used at registration time
//
//     -> public override method
//     -> calls parent only
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartLinesomUninit(ContentGrafPartLine *somSelf)
{
    SQUAWK("> Invoked ContentGrafPartLine::somUninit()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLinesomUninit");

    ContentGrafPartLine_parent_ContentGrafPartFigr_somUninit(somSelf);

    SQUAWK("< Leaving ContentGrafPartLine::somUninit()\n");

}   // somUninit()


// -------------------------------------------------------------------------
// ContentGrafPartLine --> MoveBy
//
//      Override ContentObject::MoveBy to update points
//
//      -> public override method
//      -> does not call parent
//      -> the 'offset' is a set of deltas from the origin of the
//          line's bounding rect, expressed as coordinates (not a point)
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartLineMoveBy(  ContentGrafPartLine*    somSelf,
                                                    Environment*            ev,
                                                    ODPoint*                offset )
{
    SQUAWK("> Invoked ContentGrafPartLine::MoveBy(ODPoint*)\n");
    SQUAWK("\tContentGrafPartLine::MoveBy(ODPoint*): received offset: %d, %d\n", ODFixedToInt(offset->x), ODFixedToInt(offset->y) );

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineMoveBy");

    // set local buffers from persistant data
    ODPoint pt1, pt2;   // buffers for the points
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure
    pt2 = _fPt2;                    // get endpoint from local instance data

/*
    // calculate deltas relative to origin point
    ODRect bbox = somSelf->_get_boundingRect(ev);               // get the current bounding box to a buffer
    SQUAWK("\tContentGrafPartLine::MoveBy(ODPoint*): boundingRect: %d, %d; %d, %d\n", ODFixedToInt(bbox.left), ODFixedToInt(bbox.top), ODFixedToInt(bbox.right), ODFixedToInt(bbox.bottom) );

    ODFixed deltaX = pt1.x - min(pt1.x, pt2.x) + offset->x;     // add the difference between the first
                                                                //   point and the bbox origin
#ifdef _PLATFORM_OS2_                                           // OS2 origin is LLC
    ODFixed deltaY = pt1.y - max(pt1.y, pt2.y) + offset->y;
#else                                                           // everyone else's origin is ULC
    ODFixed deltaY = pt1.y - min(pt1.x, pt2.x) + offset->y;
#endif  // _PLATFORM_OS2_
    SQUAWK("\tContentGrafPartLine::MoveBy(ODPoint*): calculated deltas are: %d, %d\n", ODFixedToInt(deltaX), ODFixedToInt(deltaY) );

    // apply the offset to the current points
    SQUAWK("\tContentGrafPartLine::MoveBy(ODPoint*): coordinates before move: %d, %d; %d, %d\n", ODFixedToInt(_fPt1.x), ODFixedToInt(_fPt1.y), ODFixedToInt(_fPt2.x), ODFixedToInt(_fPt2.y) );
    pt1.x += deltaX;
    pt1.y += deltaY;
    pt2.x += deltaX;
    pt2.y += deltaY;
*/
    SQUAWK("\tContentGrafPartLine::MoveBy(ODPoint*): coordinates before move: %d, %d; %d, %d\n", ODFixedToInt(pt1.x), ODFixedToInt(pt1.y), ODFixedToInt(pt2.x), ODFixedToInt(pt2.y) );

    // simple-minded move
    pt1.x += offset->x;
    pt1.y += offset->y;
    pt2.x += offset->x;
    pt2.y += offset->y;

    SQUAWK("\tContentGrafPartLine::MoveBy(ODPoint*): coordinates  after move: %d, %d; %d, %d\n", ODFixedToInt(pt1.x), ODFixedToInt(pt1.y), ODFixedToInt(pt2.x), ODFixedToInt(pt2.y) );

    // update the persistant data from the buffers
    somSelf->_set_fPt1(ev, &pt1);       // set origin in parent figure
    _fPt2.x = pt2.x; _fPt2.y = pt2.y;   // set endpoint in local instance data

    // adjust the bounding rect for the new points
    somSelf->AdjustBoundingRect(ev);

    SQUAWK("< Leaving ContentGrafPartLine::MoveBy(ODPoint*)\n");

}   // ContentGrafPartLine::MoveBy(ODPoint)


// -------------------------------------------------------------------------
// ContentGrafPartLine --> Resize
//
//      Override ContentObject::Resize to update points
//
//     -> public override method
//     -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartLineResize(  ContentGrafPartLine*    somSelf,
                                                    Environment*            ev,
                                                    ODPoint*                point,
                                                    ODULong                 flags )
{
    SQUAWK("> Invoked ContentGrafPartLine::Resize()\n");
    SQUAWK("\tContentGrafPartLine::Resize(): received endpoint: %d, %d\n", ODFixedToInt(point->x), ODFixedToInt(point->y) );

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineResize");

#ifdef _PLATFORM_OS2_
    #define TOP(a,b) ( max(a,b) )
    #define BOT(a,b) ( min(a,b) )
#else
    #define TOP(a,b) ( min(a,b) )
    #define BOT(a,b) ( max(a,b) )
#endif  // _PLATFORM_OS2_

    // set local buffers from persistant data
    ODPoint pt1, pt2;   // buffers for the points
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure
    pt2 = _fPt2;                    // get endpoint from local instance data

    // reset last point to new endpoint (resize is relative to first point)
    SQUAWK("\tContentGrafPartLine::Resize(): coordinates before resize: %d, %d; %d, %d\n", ODFixedToInt(pt1.x), ODFixedToInt(pt1.y), ODFixedToInt(pt2.x), ODFixedToInt(pt2.y) );

    if (flags & COBJ_RESIZE_LEFT)
    {
        SQUAWK("\tContentGrafPartLine::Resize(): resizing from Left\n" );
        if (pt1.x < pt2.x)
        {
            SQUAWK("\tContentGrafPartLine::Resize(): resizing point 1\n" );
            pt1.x = point->x;
        }   // if: pt1 on left
        else
        {
            SQUAWK("\tContentGrafPartLine::Resize(): resizing point 2\n" );
            pt2.x = point->x;
        }   // else: pt2 on left
    }   // if: resize from left
    else if (flags & COBJ_RESIZE_RIGHT)
    {
        SQUAWK("\tContentGrafPartLine::Resize(): resizing from Right\n" );
        if (pt1.x > pt2.x)
        {
            SQUAWK("\tContentGrafPartLine::Resize(): resizing point 1\n" );
            pt1.x = point->x;
        }   // if: pt1 on right
        else
        {
            SQUAWK("\tContentGrafPartLine::Resize(): resizing point 2\n" );
            pt2.x = point->x;
        }   // else: pt2 on right
    }   // if: resize from right

    if (flags & COBJ_RESIZE_TOP)
    {
        SQUAWK("\tContentGrafPartLine::Resize(): resizing from Top\n" );
        if (pt1.y == TOP(pt1.y, pt2.y) )
        {
            SQUAWK("\tContentGrafPartLine::Resize(): resizing point 1\n" );
            pt1.y = point->y;
        }   // if: pt1 on top
        else
        {
            SQUAWK("\tContentGrafPartLine::Resize(): resizing point 2\n" );
            pt2.y = point->y;
        }   // else: pt2 on top
    }   // if: resize from top
    else if (flags & COBJ_RESIZE_BOTTOM)
    {
        SQUAWK("\tContentGrafPartLine::Resize(): resizing from Bottom\n" );
        if (pt1.y == BOT(pt1.y, pt2.y) )
        {
            SQUAWK("\tContentGrafPartLine::Resize(): resizing point 1\n" );
            pt1.y = point->y;
        }   // if: pt1 on right
        else
        {
            SQUAWK("\tContentGrafPartLine::Resize(): resizing point 2\n" );
            pt2.y = point->y;
        }   // else: pt2 on bottom
    }   // if: resize from bottom

    SQUAWK("\tContentGrafPartLine::Resize(): coordinates  after resize: %d, %d; %d, %d\n", ODFixedToInt(pt1.x), ODFixedToInt(pt1.y), ODFixedToInt(pt2.x), ODFixedToInt(pt2.y) );

    // update the persistant data from the buffers
    somSelf->_set_fPt1(ev, &pt1);       // set origin in parent figure data
    _fPt2.x = pt2.x; _fPt2.y = pt2.y;   // set endpoint in local instance data

    // adjust the bounding rect for the new points
    somSelf->AdjustBoundingRect(ev);

    SQUAWK("< Leaving ContentGrafPartLine::Resize()\n");

}   // ContentGrafPartLine::Resize()


// -------------------------------------------------------------------------
// ContentGrafPartLine --> WriteContents
//
//      Override ContentObject::WriteContents to write local data to a StorageUnit
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartLineWriteContents(   ContentGrafPartLine*    somSelf,
                                                            Environment*            ev,
                                                            ODStorageUnit*          toSU,
                                                            BCTransferKind          writeKind,
                                                            BCCloneInfo*            cloneInfo )
{
    SQUAWK("> Invoked ContentGrafPartLine::WriteContents()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineWriteContents");

    // call parent first
    ContentGrafPartLine_parent_ContentGrafPartFigr_WriteContents( somSelf,
                                                            ev,
                                                            toSU,
                                                            writeKind,
                                                            cloneInfo);

    // adjust point for containment
    ODPoint fPt;                            // temporary buffer
    if (cloneInfo->refPoint)                // if a reference point was by defined by BC parent
    {
        fPt.x = _fPt2.x - cloneInfo->refPoint->x;
        fPt.y = _fPt2.y - cloneInfo->refPoint->y;
    }   // if: refPoint defined
    else
    {
        fPt.x = _fPt2.x;
        fPt.y = _fPt2.y;
    }   // else: refPoint not defined

    // Write the local data
    StorageUnitSetValue(toSU, ev, sizeof(ODPoint), &fPt);       // write the end point

    SQUAWK("< Leaving ContentGrafPartLine::WriteContents()\n");

}   // ContentGrafPartLine::WriteContents()


// -------------------------------------------------------------------------
// ContentGrafPartLine --> ReadContents
//
//      Override ContentObject::ReadContents to read local data from a StorageUnit
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartLineReadContents(    ContentGrafPartLine*    somSelf,
                                                            Environment*            ev,
                                                            ODStorageUnit*          fromSU,
                                                            BCTransferKind          readKind,
                                                            BCCloneInfo*            cloneInfo )
{
    SQUAWK("> Invoked ContentGrafPartLine::ReadContents()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineReadContents");

    // call parent first
    ContentGrafPartLine_parent_ContentGrafPartFigr_ReadContents(  somSelf,
                                                            ev,
                                                            fromSU,
                                                            readKind,
                                                            cloneInfo);
    // Read the local data
    StorageUnitGetValue(fromSU, ev, sizeof(ODPoint), &_fPt2);   // read the end point
    if (cloneInfo->refPoint)                                    // adjust point for containment
    {
        _fPt2.x += cloneInfo->refPoint->x;
        _fPt2.y += cloneInfo->refPoint->y;
    }   // if: refPoint defined

    SQUAWK("< Leaving ContentGrafPartLine::ReadContents()\n");

}   // ContentGrafPartLine::ReadContents()


// -------------------------------------------------------------------------
// ContentGrafPartLine --> DeleteContents
//
//      Override ContentObject::DeleteContents to wipe out local data
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartLineDeleteContents(  ContentGrafPartLine *somSelf,
                                                            Environment         *ev,
                                                            ODULong             type )
{
    SQUAWK("> Invoked ContentGrafPartLine::DeleteContents()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineDeleteContents");

    // call parent first
    ContentGrafPartLine_parent_ContentGrafPartFigr_DeleteContents(somSelf,
                                                                  ev,
                                                                  type);

    // Wipe the local data
    memset(&_fPt2, 0, sizeof(ODPoint));                          // wipe the end point

    SQUAWK("< Leaving ContentGrafPartLine::DeleteContents()\n");

}   // ContentGrafPartLine::DeleteContents()


// -------------------------------------------------------------------------
//  ContentGrafPartLine --> Initialize
//
//      Surrogate constructor for line object, calls all necessary initializations
//          because SOM doesn't allow parms to the real constructor (somInit).
//
//      -> public override method
//      -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope   GrafPart*
SOMLINK     ContentGrafPartLineInitialize(  ContentGrafPartLine*    somSelf,
                                            Environment*            ev,
                                            ODFrame*                frame,
                                            ODPoint*                point )
{
    SQUAWK("> Invoked ContentGrafPartLine::Initialize()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineInitialize");

    TempODPart      tPart = frame->AcquirePart(ev);     // get a temporary wrapper object
    GrafPart*       tGP;                                // declare a buffer for the calling GrafPart

    // call parent with first (origin) point
    SQUAWK("\tContentGrafPartLine::Initialize(): calling parent\n");
    tGP = ContentGrafPartLine_parent_ContentGrafPartFigr_Initialize(   somSelf,
                                                                        ev,
                                                                        frame,
                                                                        point );

    // set local value for endpoint (second point)
    _fPt2.x = point->x; _fPt2.y = point->y;         // set the end point
    somSelf->AdjustBoundingRect(ev);                // adjust the bounding rectangle to new points

    SQUAWK("< Leaving ContentGrafPartLine::Initialize()\n");
    return(tGP);                                    // return the pointer to the calling GrafPart

}   // ContentGrafPartLine::Initialize()


// -------------------------------------------------------------------------
//  ContentGrafPartLine --> Uninitialize
//
//      Surrogate destructor for line object, calls all necessary uninitializations
//          just to encapsulate them, and balance the Initialize.
//
//      -> public override method
//      -> calls parent only
// -------------------------------------------------------------------------
SOM_Scope   void
SOMLINK     ContentGrafPartLineUninitialize(  ContentGrafPartLine*    somSelf,
                                            Environment*            ev)
{
    SQUAWK("> Invoked ContentGrafPartLine::Uninitialize()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineUninitialize");

    // call parent
    ContentGrafPartLine_parent_ContentGrafPartFigr_Uninitialize( somSelf,
                                                               ev );

    SQUAWK("< Leaving ContentGrafPartLine::Uninitialize()\n");

}   // ContentGrafPartLine::Uninitialize()


// -------------------------------------------------------------------------
//  ContentGrafPartLine --> Update
//
//      Surrogate constructor for figr object, calls all necessary initializations
//          because SOM generates the real constructor.
//
//      -> public local method
// -------------------------------------------------------------------------
SOM_Scope   void
SOMLINK     ContentGrafPartLineUpdate(  ContentGrafPartLine*    somSelf,
                                        Environment*            ev,
                                        ODPoint*                point)
{
    SQUAWK("> Invoked ContentGrafPartLine::Update()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineUpdate");

    // reset the endpoint to the passed point
    somSelf->_set_fPt2(ev, point);                  // set the endpoint

    SQUAWK("< Leaving ContentGrafPartLine::Update()\n");
    return;
}   // ContentGrafPartLine::Update()


// -------------------------------------------------------------------------
//  ContentGrafPartLine --> AdjustBoundingRect
//
//      Adjust a line's bounding rect to fit it's endpoints
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK ContentGrafPartLineAdjustBoundingRect(  ContentGrafPartLine*    somSelf,
                                                                    Environment*            ev )
{
    SQUAWK("> Invoked ContentGrafPartLine::AdjustBoundingRect()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineAdjustBoundingRect");

    // set local buffers from persistant data
    ODPoint pt1, pt2;               // buffers for the points
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure
    pt2 = _fPt2;                    // get endpoint from local instance data

    // reset the bounding box from the new points, keeping orientation
    ODRect bbox;                                    // declare a buffer for bounding rectangle

    // set the buffer points to the new extents
#ifdef _PLATFORM_OS2_                               // OS2 origin is LLC
    bbox.top    = max( pt1.y, pt2.y);
    bbox.bottom = min( pt1.y, pt2.y);
#else                                               // every one else's origin in ULC
    bbox.top    = min( pt1.y, pt2.y);
    bbox.bottom = max( pt1.y, pt2.y);
#endif  // _PLATFORM_OS2_
    bbox.left   = min( pt1.x, pt2.x);
    bbox.right  = max( pt1.x, pt2.x);

    somSelf->_set_boundingRect(ev, &bbox);          // set the bounding rectangle from the buffer

    SQUAWK("< Leaving ContentGrafPartLine::AdjustBoundingRect()\n");

}   // ContentGrafPartLine::AdjustBoundingRect()


// -------------------------------------------------------------------------
//  ContentGrafPartLine --> Draw
//
//      Render a line on the screen
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartLineDraw(ContentGrafPartLine*    somSelf,
                                                        Environment*            ev,
                                                        HDraw                   hDraw )
{
    SQUAWK("> Invoked ContentGrafPartLine::Draw()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineDraw");

    // set local buffers from persistant data
    ODPoint pt1, pt2;               // buffers for the points
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure
    pt2 = _fPt2;                    // get endpoint from local instance data

#if defined (_PLATFORM_OS2_)
    SQUAWK("\tContentGrafPartLine::Draw(): Drawing line object for OS2\n");
    _pPt1.x = ODFixedToInt(pt1.x); _pPt1.y = ODFixedToInt(pt1.y);
    SQUAWK("\tContentGrafPartLine::Draw(): point 1: %lx, %lx\n", pt1.x, pt1.y );
    _pPt2.x = ODFixedToInt(pt2.x); _pPt2.y = ODFixedToInt(pt2.y);
    SQUAWK("\tContentGrafPartLine::Draw(): point 2: %lx, %lx\n", pt2.x, pt2.y );
    GpiSetColor(hDraw, somSelf->_get_fColor(ev));
    GpiMove(hDraw, &_pPt1);
    GpiLine(hDraw, &_pPt2);
#elif defined (_PLATFORM_WIN32_)
    SQUAWK("\tContentGrafPartLine::Draw(): Drawing line object for WIN32\n");
    HPEN pen = CreatePen(PS_SOLID, 0, somSelf->_get_fColor(ev)) ;
    SelectObject(hDraw, pen) ;
    MoveToEx(hDraw, ODFixedToInt(pt1.x), ODFixedToInt(pt1.y), NULL);
    LineTo(  hDraw, ODFixedToInt(pt2.x), ODFixedToInt(pt2.y) );
    DeleteObject(pen) ;
#endif // _PLATFORM_???_

    SQUAWK("< Leaving ContentGrafPartLine::Draw()\n");
    return(kODTrue);

}   // ContentGrafPartLine::Draw()


// -------------------------------------------------------------------------
//  ContentGrafPartLine --> ContainsPoint
//
//      Determines whether a given point is on or near a line
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartLineContainsPoint(   ContentGrafPartLine*    somSelf,
                                                                    Environment*            ev,
                                                                    ODPoint*                point )
{
    long x1, y1, x2, y2, x3, y3, x4, y4 ;
    long dx, dy, dex, dey, dx2, dy2, dxdy, dt2 ;

    SQUAWK("> Invoked ContentGrafPartLine::ContainsPoint()\n");

    ContentGrafPartLineData *somThis = ContentGrafPartLineGetData(somSelf);
    ContentGrafPartLineMethodDebug("ContentGrafPartLine","ContentGrafPartLineContainsPoint");

    // set local buffers from persistant data
    ODPoint pt1, pt2;               // buffers for the points
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure
    pt2 = _fPt2;                    // get endpoint from local instance data

    SQUAWK("\tContentGrafPartLine::ContainsPoint(): received Point: %d,%d\n", ODFixedToInt(point->x), ODFixedToInt(point->y));
    SQUAWK("\tContentGrafPartLine::ContainsPoint(): line endpoints: %d, %d; %d, %d\n", ODFixedToInt(pt1.x), ODFixedToInt(pt1.y), ODFixedToInt(pt2.x), ODFixedToInt(pt2.y) );
    SQUAWK("\tContentGrafPartLine::ContainsPoint(): X, Y SelectionThresholds: %d, %d\n", kODXSelectionThreshold, kODYSelectionThreshold );

    x1 = FixedToInt(pt1.x)   ;  y1 = FixedToInt(pt1.y)    ;
    x2 = FixedToInt(pt2.x)   ;  y2 = FixedToInt(pt2.y)    ;
    x3 = FixedToInt(point->x);  y3 = FixedToInt(point->y) ;

    dt2 = kODXSelectionThreshold * kODYSelectionThreshold / 4 ;

    // First check if within delta of the end points, check square of distance
    // against square of the delta.

    // First End check.
    dex = x1 - x3 ;  dey = y1 - y3 ;
    if ( dex * dex + dey * dey < dt2 )
    {
        SQUAWK("< Leaving ContentGrafPartLine::ContainsPoint(), returning True (first point)\n");
        return kODTrue ;
    }

    // Second End Check.
    dex = x2 - x3 ;  dey = y2 - y3 ;
    if ( dex * dex + dey * dey < dt2 )
    {
        SQUAWK("< Leaving ContentGrafPartLine::ContainsPoint(), returning True (second point)\n");
        return kODTrue ;
    }

    // compute delta X and delta y for the line
    dx  = x1 - x2 ;  dy  = y1 - y2 ;

    // if line is vertical, quick answer
    if ( dx == 0 )
    {
        x4 = x1 ;  y4 = y3 ;
    }

    // if line is horizontal, quick answer
    if ( dy == 0 )
    {
        x4 = x3 ;  y4 = y1 ;
    }

    // Answer is a little more complex if line is oblique.
    // really just a bit of algrbra to find the common solution to the
    // two lines.
    // (x-x2)/(y-y2) = (x1-x2)/(y1.y2)   i.e. the real line

    // (x-xy)/(y-y3) = -(y1-y2)/(x1-x2)      and perpendicular line thru x3,y3

    if ( dx != 0 && dy != 0)
    {
        dx2 = dx * dx ;  dy2 = dy * dy ;
        dxdy = dx * dy ;
        y4 = ((x3 - x2)*dxdy + y2 * dx2 + y3 * dy2) / (dx2 + dy2) ;
        // using long arithmetic, we can get some truncation errors.  We choose
        // the expression for x4 that minimizes those errors.
        if (dy2 > dx2)
        {
            x4 = (y4 - y2) * dx / dy + x2 ;
        }
        else
        {
            x4 = (y3 - y4) * dy / dx + x3 ;
        }
    }

    // x4,y4 is the point where a perpendicular from the point to the line
    // would intercept the line (posibly extended).

    // First check if x4,y4 is within the bounding rectangle of the line
    if ((((x1 <= x2) && (x1 <= x4) && (x4 <= x2))  ||   // x1 <= x4 <= x2 OR
         ((x1 >= x2) && (x1 >= x4) && (x4 >= x2))) &&   // x1 >= x4 >= x2  AND
        (((y1 <= y2) && (y1 <= y4) && (y4 <= y2))  ||   // y1 <= y4 <= y2 OR
         ((y1 >= y2) && (y1 >= y4) && (y4 >= y2))))     // t1 >= y4 >= y2
    {
        // then compute length (squared) of line segment from point to x4,y4
        dex = x3 - x4 ;  dey = y3 - y4 ;
        if ( dex * dex + dey * dey < dt2 )
        {
            SQUAWK("< Leaving ContentGrafPartLine::ContainsPoint(), returning True (line proximity)\n");
            return kODTrue ;                // in box and close enough, so return true
        }
    }

    SQUAWK("< Leaving ContentGrafPartLine::ContainsPoint(), returning False\n");
    return kODFalse ;                   // not close enough, so return false.

}   // ContentGrafPartLine::ContainsPoint()


// =========================================================================
// End of file: iodgline.cpp
// =========================================================================
