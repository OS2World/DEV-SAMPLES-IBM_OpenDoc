// @(#) 1.7 com/src/samples/grafpart/iodgfigr.cpp, odgrafpart, od96os2, odos29712d 2/7/97 17:41:39 [3/21/97 17:47:48]
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odgrafpart
 *
 *   CLASSES: ContentGrafPartFigr
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
//  File:      iodgfigr.cpp
//  Contains:  Class implementation for a Figr Object in a 2D-Drawing Container Part
// ************************************************************************

#define ContentGrafPartFigr_Class_Source

#ifndef SOM_Module_GrafFigr_Source
    #define SOM_Module_GrafFigr_Source
#endif  // SOM_Module_GrafFigr_Source

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

#ifndef SOM_ContentGrafPartFigr_xih
    #include "iodgfigr.xih"
#endif // SOM_ContentGrafPartFigr_xih


// *************************************************************************
//
//  Class implementation:
//      ContentGrafPartFigr : ContentObject (from BaseContainer)
//
// *************************************************************************

// =========================================================================
//
//      Public Override methods: ContentGrafPartFigr
//
// =========================================================================

// -------------------------------------------------------------------------
// ContentGrafPartFigr --> somInit
//
//     Initialization used at registration time
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartFigrsomInit(ContentGrafPartFigr *somSelf )
{
    SQUAWK("> Invoked ContentGrafPartFigr::somInit()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrsomInit");

    // call parent method
    ContentGrafPartFigr_parent_ContentObject_somInit(somSelf);

    // set the objtype
    somSelf->_set_objType(somGetGlobalEnvironment(), COBJ_GRAFPART_FIGR);

    // set the initial values of the the points for a figr to the origin (0,0)
    memset(&_fPt1, 0, sizeof(ODPoint) );            // set origin point to 0,0
    _fColor = 0 ;                                   // default color - black

    SQUAWK("< Leaving ContentGrafPartFigr::somInit()\n");
    return;
}   // somInit()


// -------------------------------------------------------------------------
// ContentGrafPartFigr --> somUninit
//
//     Uninitialization used at registration time
//
//     -> public override method
//     -> calls parent only
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartFigrsomUninit(ContentGrafPartFigr *somSelf)
{
    SQUAWK("> Invoked ContentGrafPartFigr::somUninit()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrsomUninit");

    ContentGrafPartFigr_parent_ContentObject_somUninit(somSelf);

    SQUAWK("< Leaving ContentGrafPartFigr::somUninit()\n");
    return;
}   // somUninit()


// -------------------------------------------------------------------------
// ContentGrafPartFigr --> MoveBy
//
//      Override ContentObject::MoveBy to update points
//
//      -> public override method
//      -> does not call parent
//      -> the 'offset' is a set of deltas from the origin of the
//          figr's bounding rect, expressed as coordinates (not a point)
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartFigrMoveBy(  ContentGrafPartFigr*    somSelf,
                                                    Environment*            ev,
                                                    ODPoint*                offset )
{
    SQUAWK("> Invoked ContentGrafPartFigr::MoveBy()\n");
    SQUAWK("\tContentGrafPartFigr::MoveBy(): received offset: %d, %d\n", ODFixedToInt(offset->x), ODFixedToInt(offset->y) );

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrMoveBy");

    // apply the offset to each of the coordinates
    _fPt1.x += offset->x;
    _fPt1.y += offset->y;

    SQUAWK("\tContentGrafPartFigr::MoveBy(): coordinates   after move: %d, %d; %d, %d\n", ODFixedToInt(_fPt1.x), ODFixedToInt(_fPt1.y) );

    SQUAWK("< Leaving ContentGrafPartFigr::MoveBy()\n");
    return;
}   // ContentGrafPartFigr::MoveBy()


// -------------------------------------------------------------------------
// ContentGrafPartFigr --> Resize
//
//      Override ContentObject::Resize to update points
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartFigrResize(  ContentGrafPartFigr*    somSelf,
                                                    Environment*            ev,
                                                    ODPoint*                point,
                                                    ODULong                 flags)
{
    SQUAWK("> Invoked ContentGrafPartFigr::Resize()\n");
    SQUAWK("\tContentGrafPartFigr::Resize(): received endpoint: %d, %d\n", ODFixedToInt(point->x), ODFixedToInt(point->y) );
    SQUAWK("\tContentGrafPartFigr::Resize():    received flags: %lX\n", flags);

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrResize");

    // call parent method first
    ContentGrafPartFigr_parent_ContentObject_Resize(somSelf, ev, point, flags);

    // reset the point to new point
    SQUAWK("\tContentGrafPartFigr::Resize(): coordinates before resize: %d, %d\n", ODFixedToInt(_fPt1.x), ODFixedToInt(_fPt1.y) );

    _fPt1.x = point->x;
    _fPt1.y = point->y;

    SQUAWK("\tContentGrafPartFigr::Resize(): coordinates  after resize: %d, %d\n", ODFixedToInt(_fPt1.x), ODFixedToInt(_fPt1.y) );

    SQUAWK("< Leaving ContentGrafPartFigr::Resize()\n");
    return;
}   // ContentGrafPartFigr::Resize()


// -------------------------------------------------------------------------
// ContentGrafPartFigr --> WriteContents
//
//      Override ContentObject::WriteContents to write local data to a StorageUnit
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartFigrWriteContents(   ContentGrafPartFigr*    somSelf,
                                                            Environment*            ev,
                                                            ODStorageUnit*          toSU,
                                                            BCTransferKind          writeKind,
                                                            BCCloneInfo*            cloneInfo )
{
    SQUAWK("> Invoked ContentGrafPartFigr::WriteContents()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrWriteContents");

    // call parent first
    ContentGrafPartFigr_parent_ContentObject_WriteContents( somSelf,
                                                            ev,
                                                            toSU,
                                                            writeKind,
                                                            cloneInfo);

    // adjust point for containment
    ODPoint fPt;                            // temporary buffer
    if (cloneInfo->refPoint)                // if a reference point was by defined by BC parent
    {
        fPt.x = _fPt1.x - cloneInfo->refPoint->x;
        fPt.y = _fPt1.y - cloneInfo->refPoint->y;
    }   // if: refPoint defined
    else
    {
        fPt.x = _fPt1.x;
        fPt.y = _fPt1.y;
    }   // else: refPoint not defined

    // Write the local data
    StorageUnitSetValue(toSU, ev, sizeof(ODPoint), &fPt);       // write the origin point
    StorageUnitSetValue(toSU, ev, sizeof(long   ), &_fColor);   // write the Color value

    SQUAWK("< Leaving ContentGrafPartFigr::WriteContents()\n");
    return;
}   // ContentGrafPartFigr::WriteContents()


// -------------------------------------------------------------------------
// ContentGrafPartFigr --> ReadContents
//
//      Override ContentObject::ReadContents to read local data from a StorageUnit
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartFigrReadContents(    ContentGrafPartFigr*    somSelf,
                                                            Environment*            ev,
                                                            ODStorageUnit*          fromSU,
                                                            BCTransferKind          readKind,
                                                            BCCloneInfo*            cloneInfo )
{
    SQUAWK("> Invoked ContentGrafPartFigr::ReadContents()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrReadContents");

    // call parent first
    ContentGrafPartFigr_parent_ContentObject_ReadContents(  somSelf,
                                                            ev,
                                                            fromSU,
                                                            readKind,
                                                            cloneInfo);
    // Read the local data
    StorageUnitGetValue(fromSU, ev, sizeof(ODPoint), &_fPt1);   // read the origin point
    StorageUnitGetValue(fromSU, ev, sizeof(long   ), &_fColor); // read the Color Value
    if (cloneInfo->refPoint)                                    // adjust point for containment
    {
        _fPt1.x += cloneInfo->refPoint->x;
        _fPt1.y += cloneInfo->refPoint->y;
    }   // if: refPoint defined

    SQUAWK("< Leaving ContentGrafPartFigr::ReadContents()\n");
    return;
}   // ContentGrafPartFigr::ReadContents()


// -------------------------------------------------------------------------
// ContentGrafPartFigr --> DeleteContents
//
//      Override ContentObject::DeleteContents to wipe out local data
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartFigrDeleteContents(  ContentGrafPartFigr *somSelf,
                                                            Environment         *ev,
                                                            ODULong             type )
{
    SQUAWK("> Invoked ContentGrafPartFigr::DeleteContents()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrDeleteContents");

    // call parent first
    ContentGrafPartFigr_parent_ContentObject_DeleteContents(somSelf,
                                                            ev,
                                                            type);

    // Wipe the local data
    memset(&_fPt1, 0, sizeof(ODPoint));                          // wipe the origin point

    SQUAWK("< Leaving ContentGrafPartFigr::DeleteContents()\n");
    return;
}   // ContentGrafPartFigr::DeleteContents()


// =========================================================================
//
//      Public local methods: ContentGrafPartFigr
//
// =========================================================================

// -------------------------------------------------------------------------
//  ContentGrafPartFigr --> Initialize
//
//      Surrogate constructor for figr object, calls all necessary initializations
//          because SOM generates the real constructor.
//
//      -> public local method
// -------------------------------------------------------------------------
SOM_Scope   GrafPart*
SOMLINK     ContentGrafPartFigrInitialize(  ContentGrafPartFigr*    somSelf,
                                            Environment*            ev,
                                            ODFrame*                frame,
                                            ODPoint*                point)
{
    SQUAWK("> Invoked ContentGrafPartFigr::Initialize()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrInitialize");

    TempODPart      tPart = frame->AcquirePart(ev);     // get a temporary wrapper object
    GrafPart*       tGP;                                // declare a buffer for the calling GrafPart

    try
    {
        // get a reference to the embedding part from the frame passed in
        if (tPart->IsRealPart(ev) )
            tGP = (GrafPart *) &tPart;                  // unwrap the reference to a GrafPart
        else
        {
            tGP = (GrafPart *) tPart->GetRealPart(ev);  // unwrap the reference to a GrafPart
            tPart->ReleaseRealPart(ev);                 // release the reference to the real part
        }
    }   // try
    catch(...)
    {
        SQUAWK("\tContentGrafPartFigr::Initialize(): CAUGHT EXCEPTION\n");
    }

    // add myself to editor embed list
    ALinkedList*    eList = tGP->GetEmbeddedObjects(ev);        // get the list of embedded objects
    eList->AddLast(ev, somSelf);

/*
    // add myself to editor select list, and be selected
    ALinkedList*    sList = tGP->GetSelectedObjects(ev);        // get the list of selected objects
    sList->AddLast(ev, somSelf);                    // add the figr object to the selected list
    somSelf->_set_selectionState(ev, kODTrue);      // tell the figr it is selected
*/

    // set internal values
    somSelf->_set_containingFrame(ev, frame);       // give the figr the current frame
    somSelf->_set_fPt1(ev, point);                  // set the origin point

    SQUAWK("< Leaving ContentGrafPartFigr::Initialize()\n");
    return(tGP);                                    // return the pointer to the calling GrafPart
}   // ContentGrafPartFigr::Initialize()


// -------------------------------------------------------------------------
//  ContentGrafPartFigr --> Uninitialize
//
//      Surrogate destructor for figr object, calls all necessary uninitializations
//          just to encapsulate them, and balance the Initialize() method.
//
//      -> public local method
// -------------------------------------------------------------------------
SOM_Scope   void
SOMLINK     ContentGrafPartFigrUninitialize(    ContentGrafPartFigr*    somSelf,
                                                Environment*            ev)
{
    SQUAWK("> Invoked ContentGrafPartFigr::Uninitialize()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrUninitialize");

    TempODPart  tPart = somSelf->_get_containingFrame(ev)->AcquirePart(ev);     // get a temp wrapper
    GrafPart*   tGP;

    try {

    // get a reference to the embedding part from the current containing frame
    if (tPart->IsRealPart(ev) )
        tGP = (GrafPart *) &tPart;                  // get the reference to a GrafPart
    else
    {
        tGP = (GrafPart *) tPart->GetRealPart(ev);  // unwrap the reference to a GrafPart
        tPart->ReleaseRealPart(ev);                 // release the reference to the real part
    }

    }   // try
    catch(...)
    {
        SQUAWK("\tContentGrafPartFigr::Uninitialize(): CAUGHT EXCEPTION\n");
    }


    // remove myself from editor's lists
    ALinkedList*    eList = tGP->GetEmbeddedObjects(ev);    // get the list of embedded objects
    ALinkedList*    sList = tGP->GetSelectedObjects(ev);    // get the list of selected objects
    sList->Remove(ev, somSelf);                             // remove the figr from the selected list
    eList->Remove(ev, somSelf);                             // remove the figr from the embedded list
    somSelf->_set_selectionState(ev, kODFalse);             // tell the figr it is not selected

    SQUAWK("< Leaving ContentGrafPartFigr::Uninitialize()\n");
    return;
}   // ContentGrafPartFigr::Uninitialize()


// -------------------------------------------------------------------------
//  ContentGrafPartFigr --> Update
//
//      Apply new point during creation drag
//
//      -> public local method
// -------------------------------------------------------------------------
SOM_Scope   void
SOMLINK     ContentGrafPartFigrUpdate(  ContentGrafPartFigr*    somSelf,
                                        Environment*            ev,
                                        ODPoint*                point)
{
    SQUAWK("> Invoked ContentGrafPartFigr::Update()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrUpdate");

    // reset the origin to the passed point
    somSelf->_set_fPt1(ev, point);                  // set the origin point

    SQUAWK("< Leaving ContentGrafPartFigr::Update()\n");
    return;
}   // ContentGrafPartFigr::Update()


// -------------------------------------------------------------------------
//  ContentGrafPartFigr --> AdjustBoundingRect
//
//      Adjust a figr's bounding rect to fit it's endpoints
//
//      -> public local method
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK ContentGrafPartFigrAdjustBoundingRect(  ContentGrafPartFigr*    somSelf,
                                                                    Environment*            ev )
{
    SQUAWK("> Invoked ContentGrafPartFigr::AdjustBoundingRect()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrAdjustBoundingRect");

    // reset the bounding box from the new points, keeping orientation
    ODRect bbox;                                    // declare a buffer for bounding rectangle

    // set the buffer points to the new extents
    bbox.left   = _fPt1.x;
    bbox.top    = _fPt1.y;
    bbox.right  = _fPt1.x;
    bbox.bottom = _fPt1.y;

    somSelf->_set_boundingRect(ev, &bbox);          // set the bounding rectangle from the buffer

    SQUAWK("< Leaving ContentGrafPartFigr::AdjustBoundingRect()\n");
    return;
}   // ContentGrafPartFigr::AdjustBoundingRect()


// -------------------------------------------------------------------------
//  ContentGrafPartFigr --> Draw
//
//      Render a figure on the screen
//
//      -> public local method
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartFigrDraw(ContentGrafPartFigr*    somSelf,
                                                        Environment*            ev,
                                                        HDraw                   hDraw )
{
    SQUAWK("> Invoked ContentGrafPartFigr::Draw()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrDraw");

    // "virtual" method: no implementation

    SQUAWK("< Leaving ContentGrafPartFigr::Draw()\n");
    return(kODFalse);
}   // ContentGrafPartFigr::Draw()


// -------------------------------------------------------------------------
//  ContentGrafPartFigr --> ContainsPoint
//
//      Determines whether a given point is on or near a figure
//
//      -> public local method
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartFigrContainsPoint(   ContentGrafPartFigr*    somSelf,
                                                                    Environment*            ev,
                                                                    ODPoint*                point )
{
    SQUAWK("> Invoked ContentGrafPartFigr::ContainsPoint()\n");

    ContentGrafPartFigrData *somThis = ContentGrafPartFigrGetData(somSelf);
    ContentGrafPartFigrMethodDebug("ContentGrafPartFigr","ContentGrafPartFigrContainsPoint");

    SQUAWK("\tContentGrafPartFigr::ContainsPoint(): received Point: %d,%d\n", ODFixedToInt(point->x), ODFixedToInt(point->y));
    SQUAWK("\tContentGrafPartFigr::ContainsPoint(): figr origin points: %d, %d\n", ODFixedToInt(_fPt1.x), ODFixedToInt(_fPt1.y) );

    // simplest case: are origin and passed point coincident?
    if ( (_fPt1.x==point->x) &&
         (_fPt1.y==point->y) )
    {
        SQUAWK("< Leaving ContentGrafPartFigr::ContainsPoint(), returning True\n");
        return(kODTrue);
    }   // if: points
    else                                                // determine distance of point from figr
    {
        SQUAWK("< Leaving ContentGrafPartFigr::ContainsPoint(), returning False\n");
        return(kODFalse);
    }   // else: points
}   // ContentGrafPartFigr::ContainsPoint()


// =========================================================================
// End of file: iodgfigr.cpp
// =========================================================================
