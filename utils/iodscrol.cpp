//   @(#) 1.13 com/src/samples/utils/iodscrol.cpp, odpagepart, od96os2, odos29712d 3/7/97 13:08:48 [3/21/97 17:48:11]
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
/*
   File:       IODScrol.cpp

   Contains:   Implementation of ODScrollExtension class.

   Owned by:   John Alcorn

   Copyright:  © 1996 by IBM, Inc., all rights reserved.

   Change History (most recent first):

      <1>   9/29/96   JWA      first checked in

   To Do:
   In Progress:

*/

#define _OD_DONT_IMPORT_CPP_
#define ODScrollExtension_Class_Source
#define VARIABLE_MACROS
#define METHOD_MACROS

#ifdef _PLATFORM_OS2_
#include <ODos2.h>
#elif defined(_PLATFORM_WIN32_)
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#endif

#ifndef _ALTPOINT_
#include <AltPoint.h> //jwa - MUST be included BEFORE ODTypes.h (better ODPoint, ODRect)
#endif

#include <ODTypes.h>
#include <ODUtils.h>
#include <ODDebug.h>
#include <ODExcept.h>
#include <TempObj.h>
// define debugging message vehicle
#ifdef ODDebug
#include <ODDebug.h>
#endif

#ifndef SOM_ODShape_xh
#include <shape.xh>
#endif

#ifndef SOM_ODTransform_xh
#include <Trnsform.xh>
#endif

#ifndef SOM_ODFacet_xh
#include <Facet.xh>
#endif

#ifndef SOM_ODCanvas_xh
#include <Canvas.xh>
#endif

#ifndef SOM_ODFrame_xh
#include <Frame.xh>
#endif

#ifndef SOM_ODFrameFacetIterator_xh
#include <FrFaItr.xh>
#endif

#ifndef SOM_ODWindow_xh
#include <Window.xh>
#endif

#ifndef SOM_ODWindowState_xh
#include <WinStat.xh>
#endif

#ifndef SOM_ODSession_xh
#include <ODSessn.xh>
#endif

#ifndef SOM_ODDraft_xh
#include <Draft.xh>
#endif

#ifndef SOM_ODStorageUnit_xh
#include <StorageU.xh>
#endif

#ifndef SOM_Module_xh5cStdProps_OpenDoc_StdProps_defined
#include <StdProps.xh>
#endif

#ifndef SOM_Module_xh5cStdTypes_OpenDoc_StdTypes_defined
#include <StdTypes.xh>
#endif

#include <stdio.h>
#include <iostream.h>

#include "IODScrol.hpp"
#include "IODScrol.xih"


//------------------------------------------------------------------------
// HandleScrollEvent
//------------------------------------------------------------------------
SOM_Scope ODBoolean  SOMLINK ODScrollExtensionHandleScrollEvent(
                                   ODScrollExtension *somSelf,
                                   Environment *ev,
                                   ODFrame* frame,
                                   ODEventData* event)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionHandleScrollEvent");

    ODBoolean handled = kODTrue;

    ODBoolean adjust = kODTrue;
    short invalidArea = ENTIRE_FRAME;

#ifdef _PLATFORM_OS2_
    switch (event->msg)
#endif
#ifdef _PLATFORM_WIN32_
    switch (event->message)
#endif

    {
       case WM_HSCROLL:
#ifdef _PLATFORM_OS2_
          switch (SHORT2FROMMP(event->mp2)) {
#endif
#ifdef _PLATFORM_WIN32_
          switch (LOWORD(event->wParam)) {
#endif
          case SB_LINELEFT:
             _fCurrentHorzScrollPos -= LINE_WIDTH;
             invalidArea = LEFT_COLUMN;
             break;
          case SB_LINERIGHT:
             _fCurrentHorzScrollPos += LINE_WIDTH;
             invalidArea = RIGHT_COLUMN;
             break;
          case SB_PAGELEFT:
             _fCurrentHorzScrollPos -= _fVisibleWidth;
             invalidArea = PAGE_LEFT;
             break;
          case SB_PAGERIGHT:
             _fCurrentHorzScrollPos += _fVisibleWidth;
             invalidArea = PAGE_RIGHT;
             break;
#ifdef _PLATFORM_OS2_
          case SB_SLIDERPOSITION:
             _fCurrentHorzScrollPos = SHORT1FROMMP(event->mp2);
#endif
#ifdef _PLATFORM_WIN32_
          case SB_THUMBPOSITION:
             _fCurrentHorzScrollPos = HIWORD(event->wParam);
#endif
             break;
          default:
             adjust = kODFalse;
          } /* endswitch */
          break;

       case WM_VSCROLL:
#ifdef _PLATFORM_OS2_
          switch (SHORT2FROMMP(event->mp2)) {
#endif
#ifdef _PLATFORM_WIN32_
          switch (LOWORD(event->wParam)) {
#endif
          case SB_LINEDOWN:
             _fCurrentVertScrollPos += LINE_HEIGHT;
             invalidArea = BOTTOM_ROW;
             break;
          case SB_LINEUP:
             _fCurrentVertScrollPos -= LINE_HEIGHT;
             invalidArea = TOP_ROW;
             break;
          case SB_PAGEDOWN:
             _fCurrentVertScrollPos += _fVisibleHeight;
             invalidArea = PAGE_DOWN;
             break;
          case SB_PAGEUP:
             _fCurrentVertScrollPos -= _fVisibleHeight;
             invalidArea = PAGE_UP;
             break;
#ifdef _PLATFORM_OS2_
          case SB_SLIDERPOSITION:
             _fCurrentVertScrollPos = SHORT1FROMMP(event->mp2);
#endif
#ifdef _PLATFORM_WIN32_
          case SB_THUMBPOSITION:
             _fCurrentVertScrollPos = HIWORD(event->wParam);
#endif
             break;
          default:
             adjust = kODFalse;
          } /* endswitch */
          break;

#ifdef _PLATFORM_OS2_
       case WM_CHAR:
          if ((SHORT1FROMMP(event->mp1) & KC_KEYUP) != 0) {
             handled = kODFalse;
             break;
          } /* endif */

          switch (SHORT2FROMMP(event->mp2)) {
          case VK_PAGEUP:
#endif //_PLATFORM_OS2_
#ifdef _PLATFORM_WIN32_
       case WM_KEYDOWN:
          switch (event->wParam) {
          case VK_PRIOR:
#endif //_PLATFORM_WIN32_
             _fCurrentVertScrollPos -= _fVisibleHeight;
             invalidArea = PAGE_UP;
             break;
#ifdef _PLATFORM_OS2_
          case VK_PAGEDOWN:
#endif
#ifdef _PLATFORM_WIN32_
          case VK_NEXT:
#endif
             _fCurrentVertScrollPos += _fVisibleHeight;
             invalidArea = PAGE_DOWN;
             break;
          case VK_UP:
             _fCurrentVertScrollPos -= LINE_HEIGHT;
             invalidArea = TOP_ROW;
             break;
          case VK_DOWN:
             _fCurrentVertScrollPos += LINE_HEIGHT;
             invalidArea = BOTTOM_ROW;
             break;
          case VK_LEFT:
             _fCurrentHorzScrollPos -= LINE_WIDTH;
             invalidArea = LEFT_COLUMN;
             break;
          case VK_RIGHT:
             _fCurrentHorzScrollPos += LINE_WIDTH;
             invalidArea = RIGHT_COLUMN;
             break;
          case VK_HOME:
             _fCurrentVertScrollPos = 0;
             break;
          case VK_END:
             _fCurrentVertScrollPos = _fTotalHeight-_fVisibleHeight-1;
             break;
          default:
             handled = kODFalse;
          } /* endswitch */
          break;

       default:
          handled = kODFalse;
    } /* endswitch */

    if (handled && adjust) {
#if 0
       _ProcessScrollAmount(ev, frame, invalidArea);
#else
       _ProcessScrollAmount(ev, frame, ENTIRE_FRAME);
#endif
    } /* endif */

    return(handled);
}


//------------------------------------------------------------------------
// ProcessScrollAmount
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionProcessScrollAmount(
                                     ODScrollExtension *somSelf,
                                     Environment *ev,
                                     ODFrame* frame,
                                     short invalidArea)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionProcessScrollAmount");

/* Too far right? */
    if (_fVisibleWidth<_fTotalWidth) {
       if (_fCurrentHorzScrollPos>_fTotalWidth-_fVisibleWidth) {
          _fCurrentHorzScrollPos = _fTotalWidth-_fVisibleWidth;
//        invalidArea = ENTIRE_FRAME; //jwa: Commented out due to [145182]
       } /* endif */
    } else {
       if (_fCurrentHorzScrollPos>0) {
          _fCurrentHorzScrollPos = 0;
//        invalidArea = ENTIRE_FRAME; //jwa: Commented out due to [145182]
       } /* endif */
    } /* endif */

/* Too far left? */
    if (_fCurrentHorzScrollPos<0) {
       _fCurrentHorzScrollPos = 0;
//     invalidArea = ENTIRE_FRAME; //jwa: Commented out due to [145182]
    } /* endif */

/* Too far down? */
    if (_fVisibleHeight<_fTotalHeight) {
       if (_fCurrentVertScrollPos>_fTotalHeight-_fVisibleHeight) {
          _fCurrentVertScrollPos = _fTotalHeight-_fVisibleHeight;
//        invalidArea = ENTIRE_FRAME; //jwa: Commented out due to [145182]
       } /* endif */
    } else {
       if (_fCurrentVertScrollPos>0) {
          _fCurrentVertScrollPos = 0;
//        invalidArea = ENTIRE_FRAME; //jwa: Commented out due to [145182]
       } /* endif */
    } /* endif */

/* Too far up? */
    if (_fCurrentVertScrollPos<0) {
       _fCurrentVertScrollPos = 0;
//     invalidArea = ENTIRE_FRAME; //jwa: Commented out due to [145182]
    } /* endif */

    if (!_fAllowEmbeddedControls || !frame->IsRoot(ev)) {
/* Smart scrolling only works if we are not rotated or scaled */
/* Also, if we're not the root part, then we might have a part on top of us, */
/* in which case we can't use WinScrollWindow, since it would not only shift */
/* our own image, but that of any obscuring parts also                       */
       invalidArea = ENTIRE_FRAME;
    } /* endif */

    _AdjustScrollBars(ev);

    ODTransform* xform = frame->AcquireInternalTransform(ev, kNoBias);   // [145182] - ced
    ODTransform* oldInternalTransform = xform->Copy(ev);                 // [145182] - ced
    xform->Release(ev);                                                  // [145182] - ced

    _ScrollFrameContents(ev, frame);
    _RedrawAfterScroll(ev, frame, invalidArea, oldInternalTransform);    // [145182] - ced
    oldInternalTransform->Release(ev);                                   // [145182] - ced
}


//------------------------------------------------------------------------
// ScrollFrameContents
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionScrollFrameContents(
                                         ODScrollExtension *somSelf,
                                         Environment *ev,
                                         ODFrame* frame)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionScrollFrameContents");

    ODTransform *internalXform = frame->AcquireInternalTransform(ev, kNoBias);
    ODTransform *oldXform = internalXform->Copy(ev);

    ODPoint newOffset(-_fCurrentHorzScrollPos*0x10000, 0);

    if (_fVisibleHeight<_fTotalHeight) { // jwa [142336]
#ifdef _PLATFORM_OS2_
       newOffset.y = -(_fTotalHeight-_fVisibleHeight-_fCurrentVertScrollPos);
#endif

#ifdef _PLATFORM_WIN32_
       newOffset.y = -_fCurrentVertScrollPos;
#endif
    } /* endif */

//  internalXform->SetOffset(ev, &newOffset); //wipes out any scaling, etc.
/* Preserve non-offset info from current internal transform matrix */
    ODPoint oldOffset;
    internalXform->GetOffset(ev, &oldOffset);

    newOffset.y *= 0x10000;
    ODPoint delta(newOffset.x-oldOffset.x, newOffset.y-oldOffset.y);
    internalXform->MoveBy(ev, &delta);

    //  ChangeInternalTransform causes GeometryChanged to get called, where we will
    // recompute our embedded control shape and then do a PerformClipping
    if (!internalXform->IsSameAs(ev,oldXform))
       frame->ChangeInternalTransform(ev, internalXform, kNoBias);
    else { // Invoke Geometry changed ourselves.
      ODFrameFacetIterator *iter  = frame->CreateFacetIterator(ev);
      ODFacet *facet = iter->First(ev);
      ODDeleteObject(iter);
      _GeometryChanged(ev, facet, kODFalse, kODTrue);  // In case scrolling is needed
    }

    internalXform->Release(ev);
    oldXform->Release(ev);
}


//------------------------------------------------------------------------
// RedrawAfterScroll
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionRedrawAfterScroll(
                                         ODScrollExtension *somSelf,
                                         Environment *ev,
                                         ODFrame* frame,
                                         short invalidArea,
                                         ODTransform* oldInternalTransform)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionRedrawAfterScroll");

   ODShape *scrollShape;
   POINTL scrollBy;

// [145182] long HorzScrollAmount = ((double) LINE_WIDTH)*_XScaleFactor+.5;
// [145182] long VertScrollAmount = ((double) LINE_HEIGHT)*_YScaleFactor+.5;

   switch (invalidArea) {
   case LEFT_COLUMN:
      scrollShape = _fLeftScrollShape;
// [145182]      scrollBy.x = HorzScrollAmount;
// [145182]      scrollBy.y = 0;
      break;
   case RIGHT_COLUMN:
      scrollShape = _fRightScrollShape;
// [145182]      scrollBy.x = -HorzScrollAmount;
// [145182]      scrollBy.y = 0;
      break;
   case BOTTOM_ROW:
      scrollShape = _fBottomScrollShape;
// [145182]      scrollBy.x = 0;
// [145182]      scrollBy.y = VertScrollAmount;
      break;
   case TOP_ROW:
      scrollShape = _fTopScrollShape;
// [145182]      scrollBy.x = 0;
// [145182]      scrollBy.y = -VertScrollAmount;
      break;
   default:
      scrollShape = kODNULL;
   } /* endswitch */

   if (scrollShape!=kODNULL) {
#if 0 //jwa: code disabled since some parts (especially parts with embedded
      //     controls) don't redraw properly when scrolled this way

      ODFrameFacetIterator *iter  = frame->CreateFacetIterator(ev);
      ODFacet *facet = iter->First(ev); // jwa - single facet hack!
      ODDeleteObject(iter);
      ODCanvas *canvas = facet->GetCanvas(ev);

/* ced - [145182]                                                           */
/* Determine the amount to scroll by.  So that we know exactly how much     */
/* to scroll the window, we use GPI to determine the scroll amount by       */
/* using the default viewing transform to transform the same point using    */
/* the old window content transform, and the new window content transform.  */
/* The scroll amount is the difference between these two transformed points.*/

      POINTL ptl1 = {0, 0}, ptl2 = {0, 0};
      MATRIXLF mtx;
      HPS hps = canvas->GetPlatformCanvas(ev, kODPM)->GetPS(ev, facet);

      ODTransform* xform = oldInternalTransform->Copy(ev);
      ODTransform* frameTransform = facet->AcquireWindowFrameTransform(ev, kODNULL);
      xform->PostCompose(ev, frameTransform);
      frameTransform->Release(ev);
      xform->GetMATRIXLF(ev, &mtx);
      GpiSetDefaultViewMatrix(hps, 9, &mtx, TRANSFORM_REPLACE);
      GpiConvert(hps, CVTC_DEFAULTPAGE, CVTC_PAGE, 1, &ptl1);
      xform->Release(ev);

      ODTransform* contentTransform = facet->AcquireWindowContentTransform(ev, canvas);
      contentTransform->GetMATRIXLF(ev, &mtx);
      GpiSetDefaultViewMatrix(hps, 9, &mtx, TRANSFORM_REPLACE);
      GpiConvert(hps, CVTC_DEFAULTPAGE, CVTC_PAGE, 1, &ptl2);
      contentTransform->Release(ev);

      scrollBy.x = ptl2.x - ptl1.x;
      scrollBy.y = ptl2.y - ptl1.y;

/* ced - [145182]                                                                */
/* Scroll the window.  Because parts of the window have already been invalidated */
/* (the old active border for example), and because WinScrollWindow does not     */
/* properly handle update regions when the window is scrolled, we need to        */
/* save the update region, validate the entire window, scroll the window and     */
/* then invalidate the window using saved update region after offsetting it by   */
/* the scroll amount.                                                            */

      HRGN hrgnUpdate = GpiCreateRegion(hps, 0, NULL);
      HWND hwnd = WinWindowFromID(facet->GetWindow(ev)->GetPlatformWindow(ev), FID_CLIENT);
      WinQueryUpdateRegion(hwnd, hrgnUpdate);
      WinValidateRect(hwnd, _fScrollableRECTL, FALSE);
      WinScrollWindow(hwnd, scrollBy.x, scrollBy.y,
         _fScrollableRECTL, _fScrollableRECTL, NULLHANDLE, NULL, NULL);
      GpiOffsetRegion(hps, hrgnUpdate, &scrollBy);
      WinInvalidateRegion(hwnd, hrgnUpdate, FALSE);
      GpiDestroyRegion(hps, hrgnUpdate);
      canvas->GetPlatformCanvas(ev, kODPM)->ReleasePS(ev, facet);

/* jwa - Begin fix for defect 141659 */
/* Now, we make sure all redrawing related to the scroll event has finished */
/* before we return to process the next event.  This way, we won't get the  */
/* next scroll event until we are ready for it.  Before we used to have a   */
/* boolean flag, called HasRedrawnSinceScroll, which, if false, would cause */
/* us to invalidate the entire frame.  That caused too much flicker.        */
      facet->Update(ev, scrollShape, canvas);
/* jwa - End fix for defect 141659 */

      ODArbitrator *arbitrator = _MySession->GetArbitrator(ev);
      ODFrame *activeFrame = arbitrator->AcquireFocusOwner(ev, _fSelectionFocus);
      if (activeFrame!=kODNULL) {
         if (activeFrame!=frame) {
/* We are forcing the active border of the embed to have  */
/* finished drawing before the next scroll event comes in */
            activeFrame->InvalidateActiveBorder(ev);
            activeFrame->DrawActiveBorder(ev);
         } /* endif */
         activeFrame->Release(ev);
      } /* endif */
#endif //0
   } else {
      frame->Invalidate(ev, kODNULL, kNoBias);
   } /* endif */
}


//------------------------------------------------------------------------
// AdjustScrollBars
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionAdjustScrollBars(
                                         ODScrollExtension *somSelf,
                                         Environment *ev)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionAdjustScrollBars");

#ifdef _PLATFORM_OS2_
/* Adjust the Horizontal Scroll Bar */
    WinSendMsg(_fHorzScrollBarHWND, SBM_SETSCROLLBAR,
       MPFROMSHORT(_fCurrentHorzScrollPos),
       MPFROM2SHORT(0, _fTotalWidth-_fVisibleWidth-1));
    WinSendMsg(_fHorzScrollBarHWND, SBM_SETTHUMBSIZE,
       MPFROM2SHORT(_fVisibleWidth, _fTotalWidth), (MPARAM) 0);

/* Adjust the Vertical Scroll Bar */
    WinSendMsg(_fVertScrollBarHWND, SBM_SETSCROLLBAR,
       MPFROMSHORT(_fCurrentVertScrollPos),
       MPFROM2SHORT(0, _fTotalHeight-_fVisibleHeight-1));
    WinSendMsg(_fVertScrollBarHWND, SBM_SETTHUMBSIZE,
       MPFROM2SHORT(_fVisibleHeight, _fTotalHeight), (MPARAM) 0);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   SCROLLINFO ScrollInfo;
   ScrollInfo.cbSize = sizeof(SCROLLINFO);
   ScrollInfo.fMask = SIF_RANGE | SIF_PAGE | SIF_POS | SIF_DISABLENOSCROLL;
   ScrollInfo.nMin = 0;
   ScrollInfo.nMax = _fTotalWidth-1;
   ScrollInfo.nPage = _fVisibleWidth;
   ScrollInfo.nPos = _fCurrentHorzScrollPos;

   SetScrollInfo(_fHorzScrollBarHWND, SB_CTL, &ScrollInfo, kODTrue);

   ScrollInfo.nMax = _fTotalHeight-1;
   ScrollInfo.nPage = _fVisibleHeight;
   ScrollInfo.nPos = _fCurrentVertScrollPos;
   SetScrollInfo(_fVertScrollBarHWND, SB_CTL, &ScrollInfo, kODTrue);
#endif //_PLATFORM_WIN32
}


//------------------------------------------------------------------------
// SetScrollableDimensions
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionSetScrollableDimensions(
                                         ODScrollExtension *somSelf,
                                         Environment *ev, ODFrame *frame,
                                         long width, long height)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionSetScrollableDimensions");

    _fTotalWidth = width;
    _fTotalHeight = height;

    if (frame!=kODNULL) {
       _ProcessScrollAmount(ev, frame, ENTIRE_FRAME);
    } /* endif */

#ifdef ODDebug
      PRINT ("SetScrDim: TotalH/W (%d,%d) VisH/W (%d,%d) V/HScrolPos (%d,%d)\n",
             _fTotalHeight, _fTotalWidth, _fVisibleHeight, _fVisibleWidth,
             _fCurrentVertScrollPos, _fCurrentHorzScrollPos);
#endif
}


//------------------------------------------------------------------------
// SetScrollPosition
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionSetScrollPosition(
                                         ODScrollExtension *somSelf,
                                         Environment *ev, ODFrame *frame,
                                         long horzScrollPos, long vertScrollPos)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionSetScrollPosition");

    _fCurrentHorzScrollPos = horzScrollPos;
    _fCurrentVertScrollPos = vertScrollPos;

    if (frame!=kODNULL) {
       _ProcessScrollAmount(ev, frame, ENTIRE_FRAME);
    } /* endif */
}


//------------------------------------------------------------------------
// GetHorizontalScrollPosition
//------------------------------------------------------------------------

SOM_Scope long  SOMLINK ODScrollExtensionGetHorizontalScrollPosition(
                                         ODScrollExtension *somSelf,
                                         Environment *ev)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionGetHorizontalScrollPosition");

    return _fCurrentHorzScrollPos;
}


//------------------------------------------------------------------------
// GetVerticalScrollPosition
//------------------------------------------------------------------------
SOM_Scope long  SOMLINK ODScrollExtensionGetVerticalScrollPosition(
                                         ODScrollExtension *somSelf,
                                         Environment *ev)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionGetVerticalScrollPosition");

    return _fCurrentVertScrollPos;
}


//------------------------------------------------------------------------
// GetVisibleWidth
//------------------------------------------------------------------------
SOM_Scope long  SOMLINK ODScrollExtensionGetVisibleWidth(
                                         ODScrollExtension *somSelf,
                                         Environment *ev)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionGetVisibleWidth");

    return _fVisibleWidth;
}


//------------------------------------------------------------------------
// GetVisibleHeight
//------------------------------------------------------------------------
SOM_Scope long  SOMLINK ODScrollExtensionGetVisibleHeight(
                                         ODScrollExtension *somSelf,
                                         Environment *ev)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionGetVisibleHeight");

    return _fVisibleHeight;
}


//------------------------------------------------------------------------
// FacetAdded
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionFacetAdded(
                                         ODScrollExtension *somSelf,
                                         Environment *ev,
                                         ODFacet* facet)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionFacetAdded");

    ODCanvas *canvas = facet->GetCanvas(ev);
    if (canvas->IsDynamic(ev)) {

       // Figure out the visible dimensions of the facet
       TempODShape frameShape = facet->GetFrame(ev)->AcquireFrameShape(ev,kNoBias);
       ODRect rect;
       Rect frameRect;
       frameShape->GetBoundingBox(ev, &rect);

#ifdef _PLATFORM_OS2_
       rect.AsRECTL(frameRect);
       _fVisibleWidth = frameRect.xRight-frameRect.xLeft;
       _fVisibleHeight = frameRect.yTop-frameRect.yBottom;

#elif defined(_PLATFORM_WIN32_)
       rect.AsWinRect(frameRect);
       _fVisibleWidth = frameRect.right-frameRect.left;
       _fVisibleHeight = frameRect.bottom-frameRect.top;

#endif

       // Create the scrollbars to have them ready to display if/when needed.
       HWND facetHWND = facet->GetFacetHWND(ev);

#ifdef _PLATFORM_OS2_
       _fHorzScrollBarHWND = WinCreateWindow(facetHWND, WC_SCROLLBAR, "",
          WS_VISIBLE | SBS_AUTOTRACK | SBS_HORZ, 0, 0, 0, 0, facetHWND,
          HWND_TOP, HORZ_SCROLL_ID, 0, 0);

       _fVertScrollBarHWND = WinCreateWindow(facetHWND, WC_SCROLLBAR, "",
          WS_VISIBLE | SBS_AUTOTRACK | SBS_VERT, 0, 0, 0, 0, facetHWND,
          HWND_TOP, VERT_SCROLL_ID, 0, 0);

       _fBlankCornerHWND = WinCreateWindow(facetHWND, WC_STATIC, "",
          WS_VISIBLE | SS_FGNDRECT, 0, 0, 0, 0, facetHWND,
          HWND_TOP, BLANK_CORNER_ID, 0, 0);

       long ForegroundColor = CLR_PALEGRAY;
       WinSetPresParam(_fBlankCornerHWND, PP_FOREGROUNDCOLORINDEX,
          (ULONG) sizeof(long), (PVOID) &ForegroundColor);

#elif defined(_PLATFORM_WIN32_)
       HINSTANCE hInst = (HINSTANCE) GetWindowLong(facetHWND, GWL_HINSTANCE);

       _fHorzScrollBarHWND = CreateWindow("SCROLLBAR", NULL,
//        WS_CHILD | WS_VISIBLE | SBS_SIZEBOX | SBS_HORZ, 0, 0, 0, 0, facetHWND,
          WS_CHILD | WS_VISIBLE | SBS_HORZ, 0, 0, 0, 0, facetHWND,
          (HMENU) HORZ_SCROLL_ID, hInst, 0);
       DWORD error = GetLastError();

       _fVertScrollBarHWND = CreateWindow("SCROLLBAR", NULL,
//        WS_CHILD | WS_VISIBLE | SBS_SIZEBOX | SBS_VERT, 0, 0, 0, 0, facetHWND,
          WS_CHILD | WS_VISIBLE | SBS_VERT, 0, 0, 0, 0, facetHWND,
          (HMENU) VERT_SCROLL_ID, hInst, 0);

       _fBlankCornerHWND = CreateWindow("STATIC", NULL,
         WS_CHILD | WS_VISIBLE | SS_GRAYRECT, 0, 0, 0, 0, facetHWND,
          (HMENU) BLANK_CORNER_ID, hInst, 0);
#endif
    } /* endif */
}


//------------------------------------------------------------------------
// FacetRemoved
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionFacetRemoved(
                                         ODScrollExtension *somSelf,
                                         Environment *ev,
                                         ODFacet* facet)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionFacetRemoved");

    if (facet->GetCanvas(ev)->IsDynamic(ev)) {
#ifdef _PLATFORM_OS2_
       WinDestroyWindow(_fHorzScrollBarHWND);
       WinDestroyWindow(_fVertScrollBarHWND);
       WinDestroyWindow(_fBlankCornerHWND);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
       DestroyWindow(_fHorzScrollBarHWND);
       DestroyWindow(_fVertScrollBarHWND);
       DestroyWindow(_fBlankCornerHWND);
#endif //_PLATFORM_WIN32_

       _fHorzScrollBarHWND = kODNULL;
       _fVertScrollBarHWND = kODNULL;
       _fBlankCornerHWND = kODNULL;
    } /* endif */
}


//------------------------------------------------------------------------
// Geometry Changed
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionGeometryChanged(
                                         ODScrollExtension *somSelf,
                                         Environment *ev,
                                         ODFacet* facet,
                                         ODBoolean clipShapeChanged,
                                         ODBoolean externalTransformChanged)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionGeometryChanged");

/* Determine frameRect */
    ODCanvas *canvas = facet->GetCanvas(ev);
    ODTransform *frameXform = facet->AcquireFrameTransform(ev, canvas);

    ODFrame *frame = facet->GetFrame(ev);
    ODShape *frameShape = ODCopyAndRelease(ev, frame->AcquireFrameShape(ev,
                             canvas));
    frameShape->Transform(ev, frameXform);

    ODRect frameODRect;
    frameShape->GetBoundingBox(ev, &frameODRect);
    frameShape->Release(ev);

    Rect frameRect;

#ifdef _PLATFORM_OS2_
    frameODRect.AsRECTL(frameRect);

    LONG frameWidth = frameRect.xRight-frameRect.xLeft;
    LONG frameHeight = frameRect.yTop-frameRect.yBottom;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    frameODRect.AsWinRect(frameRect);

    LONG frameWidth = frameRect.right-frameRect.left;
    LONG frameHeight = frameRect.bottom-frameRect.top;
#endif //_PLATFORM_WIN32_

/* Determine facet's origin relative to DocShell's origin */
    ODPoint origin(0, 0);
    frameXform->TransformPoint(ev, &origin);
    frameXform->Release(ev);

    origin.x /= 0x10000; /* Conversion of 16:16 value to 32:0 value */
    origin.y /= 0x10000;

    ODBoolean HorzScrollBarNeeded = (_fVisibleWidth<_fTotalWidth);
    ODBoolean VertScrollBarNeeded = (_fVisibleHeight<_fTotalHeight);

    long HorzScrollHeight = HorzScrollBarNeeded ? HORZ_SCROLL_HEIGHT : 0;
    long VertScrollWidth = VertScrollBarNeeded ? VERT_SCROLL_WIDTH : 0;

    LONG VertXPos = origin.x+frameWidth-VertScrollWidth+1;
    LONG width = frameWidth-VertScrollWidth+1;
    LONG height = frameHeight-HorzScrollHeight;

#ifdef _PLATFORM_OS2_
    LONG VertYPos = origin.y+HorzScrollHeight;

    WinSetWindowPos(_fBlankCornerHWND, HWND_TOP, VertXPos, origin.y,
       VertScrollWidth, HorzScrollHeight, SWP_SIZE | SWP_MOVE | SWP_ZORDER);

    WinSetWindowPos(_fHorzScrollBarHWND, HWND_TOP, origin.x, origin.y,
       width, HorzScrollHeight, SWP_SIZE | SWP_MOVE | SWP_ZORDER);

    WinSetWindowPos(_fVertScrollBarHWND, HWND_TOP, VertXPos, VertYPos,
       VertScrollWidth, height, SWP_SIZE | SWP_MOVE | SWP_ZORDER);

    WinShowWindow(_fBlankCornerHWND, _fAllowEmbeddedControls &&
       HorzScrollBarNeeded && VertScrollBarNeeded);
    WinShowWindow(_fHorzScrollBarHWND, _fAllowEmbeddedControls &&
       HorzScrollBarNeeded);
    WinShowWindow(_fVertScrollBarHWND, _fAllowEmbeddedControls &&
       VertScrollBarNeeded);

    WinInvalidateRect(_fBlankCornerHWND, kODNULL, kODTrue);
    WinInvalidateRect(_fHorzScrollBarHWND, kODNULL, kODTrue);
    WinInvalidateRect(_fVertScrollBarHWND, kODNULL, kODTrue);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    LONG VertYPos = origin.y+frameHeight-HorzScrollHeight;

    SetWindowPos(_fBlankCornerHWND, HWND_TOP, VertXPos, VertYPos,
       VertScrollWidth, HorzScrollHeight, SWP_NOACTIVATE);

    SetWindowPos(_fHorzScrollBarHWND, HWND_TOP, origin.x, VertYPos,
       width, HorzScrollHeight, SWP_NOACTIVATE);

    SetWindowPos(_fVertScrollBarHWND, HWND_TOP, VertXPos, origin.y,
       VertScrollWidth, height, SWP_NOACTIVATE);

    ShowWindow(_fBlankCornerHWND, (_fAllowEmbeddedControls &&
       HorzScrollBarNeeded && VertScrollBarNeeded) ? SW_SHOW : SW_HIDE);
    ShowWindow(_fHorzScrollBarHWND, (_fAllowEmbeddedControls &&
       HorzScrollBarNeeded) ? SW_SHOW : SW_HIDE);
    ShowWindow(_fVertScrollBarHWND, (_fAllowEmbeddedControls &&
       VertScrollBarNeeded) ? SW_SHOW : SW_HIDE);

    InvalidateRect(_fBlankCornerHWND, kODNULL, kODTrue);
    InvalidateRect(_fHorzScrollBarHWND, kODNULL, kODTrue);
    InvalidateRect(_fVertScrollBarHWND, kODNULL, kODTrue);
#endif //_PLATFORM_WIN32_
}


//------------------------------------------------------------------------
// FrameShapeChanged
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionFrameShapeChanged(
                                         ODScrollExtension *somSelf,
                                         Environment *ev,
                                         ODFrame* frame)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","ODScrollExtensionFrameShapeChanged");

    ODShape *frameShape = frame->AcquireFrameShape(ev, kNoBias);

    ODRect rect;
    frameShape->GetBoundingBox(ev, &rect);

    Rect frameRect;

#ifdef _PLATFORM_OS2_
    rect.AsRECTL(frameRect);

    _fVisibleWidth = frameRect.xRight-frameRect.xLeft;
    _fVisibleHeight = frameRect.yTop-frameRect.yBottom;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    rect.AsWinRect(frameRect);

    _fVisibleWidth = frameRect.right-frameRect.left;
    _fVisibleHeight = frameRect.bottom-frameRect.top;
#endif //_PLATFORM_WIN32_

    _ProcessScrollAmount(ev, frame, ENTIRE_FRAME);
    /* Above call also calls _AdjustScrollBars() */
}


//------------------------------------------------------------------------------
// ODScrollExtension: Initialize
//------------------------------------------------------------------------------

SOM_Scope void SOMLINK ODScrollExtensionInitialize(
                                        ODScrollExtension *somSelf,
                                        Environment *ev,
                                        ODPart* base,
                                        long width,
                                        long height)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","Initialize");

    // Call ODExtension's InitExtension method, passing it a pointer
    // to the base container
    _InitExtension(ev, (ODObject *) base);

    _fTotalWidth = width;
    _fTotalHeight = height;
}


//------------------------------------------------------------------------
// somInit
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionsomInit(ODScrollExtension *somSelf)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","somInit");

    ODScrollExtension_parent_ODExtension_somInit(somSelf);

    _fHorzScrollBarHWND = kODNULL;
    _fVertScrollBarHWND = kODNULL;
    _fBlankCornerHWND = kODNULL;

    _fAllowEmbeddedControls = kODTrue;

    _fCurrentHorzScrollPos = 0;
    _fCurrentVertScrollPos = 0;

    _fEmbeddedControlShape = kODNULL;

    _fScrollableRECTL = kODNULL;
    _fLeftScrollShape = kODNULL;
    _fRightScrollShape = kODNULL;
    _fTopScrollShape = kODNULL;
    _fBottomScrollShape = kODNULL;
}


//------------------------------------------------------------------------
// somUninit
//------------------------------------------------------------------------
SOM_Scope void  SOMLINK ODScrollExtensionsomUninit(ODScrollExtension *somSelf)
{
    ODScrollExtensionData *somThis = ODScrollExtensionGetData(somSelf);
    ODScrollExtensionMethodDebug("ODScrollExtension","somUninit");

    ODScrollExtension_parent_ODExtension_somUninit(somSelf);
}

