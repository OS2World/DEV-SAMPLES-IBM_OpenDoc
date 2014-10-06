/* @(#) 1.86 com/src/samples/basecntr/bcevent.cpp, odbasepart, od96os2, odos29712d 3/17/97 21:34:35 [3/21/97 17:37:47] */

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
//
// -------------------------------------------------------------------------
// -----                                                               -----
// -----                  BaseContainer Class                          -----
// -----                                                               -----
// -----                 Event Handling Methods                        -----
// -----                                                               -----
// -------------------------------------------------------------------------

#ifndef BaseContainerMethodDebug
   #define BaseContainerMethodDebug(c,m) SOMMethodDebug(c,m)
#endif
#define VARIABLE_MACROS
#define SOM_DONT_IMPORT_CLASS_ALink
#define SOM_DONT_IMPORT_CLASS_ALinkedList
#define SOM_DONT_IMPORT_CLASS_BaseContainer
#define SOM_DONT_IMPORT_CLASS_BCIterator
#define SOM_DONT_IMPORT_CLASS_ContentObject
#define SOM_DONT_IMPORT_CLASS_ContentFrame

// This MUST be the first include to override ODPoint and ODRect defs
#include <AltPoint.h>

#include <BArray.h>
#include <FocusLib.h>
#include <ODMath.h>
#ifdef _PLATFORM_AIX_
#include <odres.h>
#else
#include <ODRes.h>
#endif
#include <ODTypes.h>
#include <StorUtil.h>
#include <TempObj.h>
#include <WinUtils.h>


#ifndef  SOM_BCIterator_xh
#include <iodbcitr.xh>
#endif

#ifndef SOM_ODArbitrator_xh
#include <Arbitrat.xh>
#endif

#ifndef SOM_ODCanvas_xh
#include <Canvas.xh>
#endif

#ifndef SOM_ODClipboard_xh
#include <Clipbd.xh>
#endif

#ifndef SOM_ODDragItemIterator_xh
#include <DgItmIt.xh>
#endif

#ifndef SOM_ODDragAndDrop_xh
#include <DragDrp.xh>
#endif

#ifndef SOM_ODFacet_xh
#include <Facet.xh>
#endif

#ifndef SOM_ODFocus_xh
#include <Foci.xh>
#endif

#ifndef SOM_ODFocusSet_xh
#include <FocusSet.xh>
#endif

#ifndef SOM_ODFrame_xh
#include <Frame.xh>
#endif

#ifndef SOM_ODFrameFacetIterator_xh
#include <FrFaItr.xh>
#endif

#ifndef SOM_ODFacetIterator_xh
#include <FacetItr.xh>
#endif

#ifndef SOM_ODMenubar_xh
#include <MenuBar.xh>
#endif

#ifndef SOM_ODSession_xh
#include <ODSessn.xh>
#endif

#ifndef SOM_ODPlatformCanvas_xh
#include <PlatCanv.xh>
#endif

#ifndef SOM_ODShape_xh
#include <Shape.xh>
#endif

#ifndef SOM_Module_xh5cStdProps_OpenDoc_StdProps_defined
#include <StdProps.xh>
#endif

#ifndef SOM_Module_xh5cStdTypes_OpenDoc_StdTypes_defined
#include <StdTypes.xh>
#endif

#ifndef SOM_ODStorageUnit_xh
#include <StorageU.xh>
#endif

#ifndef SOM_ODTransform_xh
#include <Trnsform.xh>
#endif

#ifndef SOM_ODInfo_xh
#include <Info.xh>
#endif

#ifndef SOM_ODWindow_xh
#include <Window.xh>
#endif

#if defined(_PLATFORM_WIN32_)

#ifndef SOM_ODWin32Canvas_xh
#include <WinPCanv.xh>
#endif

#endif // defined win32


#if defined(_PLATFORM_OS2_)

#ifndef SOM_ODOS2Canvas_xh
#include <OS2PCanv.xh>
#endif

#endif // defined OS2

#ifdef _PLATFORM_UNIX_
#include <AIXPCanv.xh>
#include <AIXWCanv.xh>
#endif

#ifndef SOM_ODWindowState_xh
#include <WinStat.xh>
#endif

#ifndef _ODHELP_
#include <odhelp.xh>
#endif

#if defined(_PLATFORM_AIX_)
#   define QPRINTF printf
#   include <Xm/XmAll.h>
#   include <X11/cursorfont.h>

#elif defined(_PLATFORM_OS2_)
#   define QPRINTF qprintf

#   define INCL_DOS
#   define INCL_GPI
#   define INCL_GPIPOLYGON
#   define INCL_WIN
#   define INCL_WINFRAMEMGR
#   define INCL_WINPOINTERS
#   define INCL_WINWINDOWMGR
#   define INCL_WINHELP
#   include <os2.h>

#elif defined(_PLATFORM_WIN32_)
#   include <windows.h>
#   include <winuser.h>
#   include <wingdi.h>

#endif

#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include <ODRegApi.h>
#include <locale.h>
#include <wchar.h>
#include <ODDebug.h>


#include <iodbasec.xih>

#ifndef OD_PRINT //This isn't defined on WIN32 for some reason???
                 //Even though we now get the menu event directly for a
                 //DOC_PRINT, we should still get an OD_PRINT when a
                 //document is dragged to a printer.
#define OD_PRINT DOC_PRINT
#endif


/********************************************************************
  STRUCTURES FOR MOVE/RESIZE/LASSO
********************************************************************/

typedef struct bc_movedata {

   ODShape *shape;
   ODTransform *transform;
   CFocus *focus;
#if defined(_PLATFORM_WIN32_)
   HDC dc;
#elif defined(_PLATFORM_OS2_)
   HPS dc;
   ODTransform *contentXform;
#elif defined(_PLATFORM_UNIX_)
   GC dc;
   Window win;
   ODTransform *contentXform;
#endif
   ODPoint lastPoint;
   ODPoint firstPoint;

} BC_MoveData;


typedef struct bc_lassodata {

   CFocus *focus;
#if defined(_PLATFORM_WIN32_)
   HDC dc;
#elif defined(_PLATFORM_OS2_)
   HPS dc;
#elif defined(_PLATFORM_UNIX_)
   GC dc;
   Window win;
   ODTransform *contentXform;
#endif
   ODPoint lastPoint;
   ODPoint firstPoint;
   ODShape *shape;

} BC_LassoData;


typedef struct resizedata {

   CFocus *focus;
#if defined(_PLATFORM_WIN32_)
   HDC dc;
#elif defined(_PLATFORM_OS2_)
   HPS dc;
   ODTransform *contentXform;
#elif defined(_PLATFORM_UNIX_)
   GC dc;
   Window win;
   ODTransform *contentXform;
#endif
   ODRect bbox;
   ODPoint firstPoint;
   ODPoint lastPoint;
   ODPoint anchorPoint;
   ODShape *shape;
   ContentObject *cobj;
   ODULong resizeFlags;

} BC_ResizeData;


/********************************************************************
  HELPER FUNCTIONS
********************************************************************/
ContentFrame *GetContentObjectForFrame(ODFrame *frame, ALinkedList *l)
{

   ALink *itr;
   ContentFrame *cobj;
   Environment *ev = somGetGlobalEnvironment();
   for(itr = l->First(ev); itr->Content(ev); itr=itr->Next(ev)) {
       cobj = (ContentFrame *) itr->Content(ev);
       if ((cobj->_get_objType(ev) == COBJ_FRAMECLASS) && (cobj->_get_myFrame(ev) == frame))
          return cobj;
   }
   return kODNULL;
}

void WinPt2FramePt (Environment *ev, ODEventData *event, ODEventInfo *eventinfo,
                               ODPoint *cursorLocation, ODFacet *facet)
{

#if defined(_PLATFORM_WIN32_)
      cursorLocation->x = ODIntToFixed(LOWORD(event->lParam));
      cursorLocation->y = ODIntToFixed(HIWORD(event->lParam));
#elif defined(_PLATFORM_OS2_)
      cursorLocation->x = ODIntToFixed(SHORT1FROMMP(event->mp1));
      cursorLocation->y = ODIntToFixed(SHORT2FROMMP(event->mp1));
#elif defined(_PLATFORM_UNIX_)
      cursorLocation->x = eventinfo->where.x;
      cursorLocation->y = eventinfo->where.y;
#endif

      TempODTransform xform = facet->AcquireWindowContentTransform(ev, kODNULL);
      xform->InvertPoint (ev, cursorLocation);

}

#define x_between(val, left, right) ((val > left) && (val < right))

void dumpRect(char *str, ODRect r)
{
   PRINT("%s l:%d r:%d t:%d b:%d\n", str, r.left >> 16, r.right >> 16, r.top >> 16, r.bottom >> 16);
}

#if defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_)
   #define y_between(val, top, bottom) ((val > top) && (val < bottom))
#elif defined(_PLATFORM_OS2_)
   #define y_between(val, top, bottom) ((val > bottom) && (val < top))
#endif

#if defined(_PLATFORM_UNIX_)
#define min(a,b) (a)<(b) ? (a) : (b)
#define max(a,b) (a)>(b) ? (a) : (b)
#endif

extern ODFacet* FirstFacet (Environment *ev, ODFrame *frame);


#if defined(_PLATFORM_OS2_)

//---------------------------------------------------------------------------
// VK_SHIFT  VK_CTRL  VK_ALT  VK_CAPSLOCK  VK_NUMLOCK  VK_SCRLLOCK VK_ALTGRAF
//---------------------------------------------------------------------------
BOOL  key_shift( SHORT vk_key )
{
  SHORT key_state = WinGetKeyState( HWND_DESKTOP, vk_key );
  return (BOOL)( key_state & 0x8000 );
}

#endif // defined OS2


// -------------------------------------------------
// List of Methods
// -------------------------------------------------
// ODPart --> AdjustMenus
// ODPart --> HandleEvent
//
// BaseContainer --> CompleteMoveOperation
// BaseContainer --> CompleteResizeOperation
// BaseContainer --> HandleMouseUp
// BaseContainer --> HandleMenuEvent
// BaseContainer --> MoveSelectionToFront
// BaseContainer --> MoveSelectionToBack
// BaseContainer --> SelectEmbeddedPart



//--------------------------------------------------------------------------
// ODPart --> AdjustMenus
//
//      Should prepare this part's menus for display.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerAdjustMenus
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerAdjustMenus");

    ODBoolean gotCB;       // can we get clipboard focus from RequestFocus
    ODULong numSelected = _fSelectedObjects->Count(ev);
    ODULong numEmbedded = _fEmbeddedObjects->Count(ev);
    ODBoolean bEnable = kODFalse;

    try {

      ODBoolean isRoot = frame!=kODNULL ? frame->IsRoot(ev) : kODFalse;
      ODArbitrator *arbitrator = _fSession->GetArbitrator(ev);
      TempODFrame menuFocusOwner = arbitrator->
                                   AcquireFocusOwner(ev, _fSession->Tokenize(ev, kODMenuFocus));

      // Check if this frame owns the menu focus.
      if(menuFocusOwner == frame) {

        gotCB = arbitrator->RequestFocus(ev,_fClipboardFocus, frame);

        // access the menubar object for menuitem enablemment
        _fMenuBar->Acquire(ev);         // enable/disable specific entries

        bEnable = (!_fDraftReadOnly) && (numSelected == 1);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, CMD(Move), bEnable);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, CMD(MoveFront), (!_fDraftReadOnly) && numSelected);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, CMD(MoveBack), (!_fDraftReadOnly) && numSelected);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, CMD(Resize), bEnable);

        // or OPEN, DELETE or DESELECT them
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_SELECTALL, numSelected != numEmbedded);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_DESELECTALL, numSelected);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_OPENSEL, numSelected);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_DELETE, numSelected && (!_fDraftReadOnly));

        // if we have the CLIPBOARD and things are selected...
        bEnable = numSelected && gotCB;
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_CUT, bEnable && (!_fDraftReadOnly));
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_COPY, bEnable);

        // can we paste anything? Yes enable PASTE items and disable others
         bEnable = (_fSession->GetClipboard(ev)->CanEmbed(ev)) && (!_fDraftReadOnly);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTE, bEnable);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTEAS, kODFalse);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_SELPROPERTIES, numSelected == 1);

        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_INSERT,      kODFalse);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_CREATE,      kODFalse);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_UNDO,      kODFalse);
        _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_REDO,      kODFalse);
        _fMenuBar->EnableMenu(ev, kODCommandLinksMenu, kODFalse);

        //enable view properties item
        _fMenuBar->EnableMenuItem(ev, IDMS_VIEW, VIEW_PROPERTIES, kODTrue);

        //enable View->Show As items if this is not a root frame.
        if(!isRoot) {
           _fMenuBar->EnableMenuItem(ev, IDMS_VIEW, VIEW_SHOWAS, kODTrue);
        }

        //enable our own menu items
        _fMenuBar->EnableMenuItem(ev, kODOptionsMenuID, CMD(ColorCHANGE), !_fDraftReadOnly);

        _fMenuBar->EnableMenu(ev, kODEmbedMenuID, !_fDraftReadOnly);

        _fMenuBar->Release(ev);

        if (gotCB)
           arbitrator->RelinquishFocus(ev, _fClipboardFocus, frame);

      } // end if menu focus owner


      // With or without the menu focus, if this is a root frame it is
      // responsible to enable/disable the Print and PageSetup menu items.
      if (isRoot) {

        ODWindowState *winState = _fSession->GetWindowState(ev);
        TempODMenuBar currentMenu = winState->AcquireCurrentMenuBar(ev);

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
        currentMenu->EnableMenuItem(ev, IDMS_DOCUMENT, DOC_SETUP, _fPrintingEnabled);
        currentMenu->EnableMenuItem(ev, IDMS_DOCUMENT, DOC_PRINT, _fPrintingEnabled);
#else
        currentMenu->EnableMenuItem(ev, IDMS_DOCUMENT, DOC_SETUP, kODFalse);
        currentMenu->EnableMenuItem(ev, IDMS_DOCUMENT, DOC_PRINT, kODFalse);
#endif
      } // end if root

    } // end of try block
    catch (...) {}

}



//--------------------------------------------------------------------------
// ODPart --> HandleEvent
//
//      Should attempt to handle the specified user event.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleEvent
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // inout
                ODFrame         *frame,         // in
                ODFacet         *facet,         // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleEvent");


    ODBoolean eventHandled = kODFalse;

    try {

#if  defined(_PLATFORM_WIN32_)
    switch (event->message)
#elif defined(_PLATFORM_OS2_)
    switch (event->msg)
#elif defined(_PLATFORM_UNIX_)
    XButtonEvent* button_struct  = (XButtonEvent*) event;
    switch (event->type)
#endif
        {
        case kODEvtActivate:
                // If activating
#if  defined(_PLATFORM_WIN32_)
                if (LOWORD(event->wParam) != WA_INACTIVE)
#elif defined(_PLATFORM_OS2_)
                if (SHORT1FROMMP(event->mp1) != kODEvtInactive)
#elif defined(_PLATFORM_UNIX_)
                if (eventInfo->originalType == FocusIn)
#endif
                {
                    // Handle the window activation
                    somSelf->ActivatingWindow(ev, frame);
                }
                else
                {
                    // Handle the window deactivation
                    somSelf->DeactivatingWindow(ev, frame);
                }
                break;

        case kODEvtMouseUp:

                eventHandled = somSelf->HandleMouseUp
                                        (ev,event,frame,facet, eventInfo);
                break;

        case kODEvtMouseDown:

                eventHandled = somSelf->HandleMouseDown
                                        (ev, event, frame, facet, eventInfo);
                break;

        case kODEvtMouseDownBorder:
                // Mouse Down in Embedded facet border - select request

                somSelf->ActivateFrame(ev, frame);
                somSelf->SelectContentObject(ev,
                               (ContentObject*)GetContentObjectForFrame
                               (eventInfo->embeddedFrame, _fEmbeddedObjects));
                eventHandled = kODTrue;
                break;

        case kODEvtMouseUpEmbedded:

                {
                   ODTypeToken frameType = _fSession->Tokenize(ev,kODViewAsFrame);

                   ODBoolean isIcon = ((eventInfo->embeddedFrame) &&
                             (eventInfo->embeddedFrame->GetViewType(ev) != frameType));
                   somSelf->ActivateFrame(ev, frame);
#if  defined(_PLATFORM_WIN32_)
                   if(isIcon || (event->wParam & MK_SHIFT) || (event->wParam & MK_CONTROL))
#elif defined(_PLATFORM_OS2_)
                   if (isIcon || key_shift(VK_CTRL) || key_shift(VK_SHIFT))
#elif defined(_PLATFORM_UNIX_)
                   if (isIcon ||  (button_struct->state & ShiftMask) ||
                        (button_struct->state & ControlMask) )
#endif

                   {
                      somSelf->SelectContentObject(ev,
                                 (ContentObject*)GetContentObjectForFrame
                                 (eventInfo->embeddedFrame,_fEmbeddedObjects));
                   }
                   eventHandled = kODTrue;
                }
                break;

        case kODEvtMouseDownEmbedded:
                {
                   somSelf->ActivateFrame(ev, frame);

                   // Make sure the frame is selected. This prevents us from 
                   // attempting to drag unselected frames displaying as
                   // icon/thumbnail.
                   ContentObject *selectedObject = (ContentObject*)GetContentObjectForFrame(eventInfo->embeddedFrame, _fSelectedObjects);

#if  defined(_PLATFORM_WIN32_)
                   if (!((event->wParam & MK_SHIFT) ||
                         (event->wParam & MK_CONTROL)) &&
                       selectedObject)
#elif defined(_PLATFORM_OS2_)
                   if (!(key_shift(VK_CTRL) || key_shift(VK_SHIFT)) &&
                       (eventInfo->originalType == WM_BEGINDRAG) &&
                       selectedObject)
#elif defined(_PLATFORM_UNIX_)
                   if ( !((button_struct->state & ShiftMask) ||
                          (button_struct->state & ControlMask)) &&
                       selectedObject)
#endif
                      {
                         somSelf->StartDrag(ev, event, eventInfo->embeddedFrame,
                                   facet, eventInfo,
                                   (_fDraftReadOnly)?kODCloneCopy:kODCloneCut);
                      }
                   eventHandled = kODTrue;
                }
                break;


        case kODEvtMenu:

                eventHandled = somSelf->HandleMenuEvent(ev, frame, event);
                break;

#if (defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_))
        case WM_MOUSEMOVE:
#elif defined(_PLATFORM_UNIX_)
        case MotionNotify:
#endif
                eventHandled = somSelf->HandleMouseMove
                                          (ev, event, frame, facet, eventInfo);
                break;


        case kODEvtKeyUp:

                eventHandled = somSelf->HandleKeyEvent (ev, event, frame, facet, eventInfo);
                break;


        case OD_HELP:
        {
          ODHelp * help;
#if defined(_PLATFORM_WIN32_)
          if (LOWORD(event->wParam) == HLPM_ODMENU)
#elif defined(_PLATFORM_OS2_)
          if (SHORT1FROMMP(event->mp1) == HLPM_ODMENU)  // if F1 on Menu
#elif defined(_PLATFORM_UNIX_)
          if (event->type == HLPM_ODMENU)  // if F1 on Menu
#endif
          {
#if  defined(_PLATFORM_WIN32_)
            switch  (event->lParam)
#elif defined(_PLATFORM_OS2_)
            switch (SHORT1FROMMP(event->mp2))
#elif defined(_PLATFORM_UNIX_)
            switch (event->type)
#endif
            {
             case kODCommandMoveFront:
                help = _fSession->GetHelp(ev);
                help->DisplayHelp(ev,"iodbasec.hlp",200);
                eventHandled = kODTrue;
                break;
             case kODCommandMoveBack:
                help = _fSession->GetHelp(ev);
                help->DisplayHelp(ev,"iodbasec.hlp",201);
                eventHandled = kODTrue;
                break;
             case kODCommandMove:
                help = _fSession->GetHelp(ev);
                help->DisplayHelp(ev,"iodbasec.hlp",202);
                eventHandled = kODTrue;
                break;
             case kODCommandResize:
                help = _fSession->GetHelp(ev);
                help->DisplayHelp(ev,"iodbasec.hlp",203);
                eventHandled = kODTrue;
                break;
             case kODCommandColorCHANGE:
                help = _fSession->GetHelp(ev);
                help->DisplayHelp(ev,"iodbasec.hlp",205);
                eventHandled = kODTrue;
                break;
             case kODOptionsMenuID:
                help = _fSession->GetHelp(ev);
                help->DisplayHelp(ev,"iodbasec.hlp",206);
                eventHandled = kODTrue;
                break;
             case kODEmbedMenuID:
                help = _fSession->GetHelp(ev);
                help->DisplayHelp(ev,"iodbasec.hlp",204);
                eventHandled = kODTrue;
                break;
             default:
#if  defined(_PLATFORM_WIN32_)
                if ((event->lParam >= kODCommandParts) &&
                    (event->lParam < CMD_Offset_Subclass))
#elif defined(_PLATFORM_OS2_)
                if ((SHORT1FROMMP(event->mp2) >= kODCommandParts) &&
                    (SHORT1FROMMP(event->mp2) < CMD_Offset_Subclass))
#elif defined(_PLATFORM_UNIX_)
                break;  // no-op
#endif
                {
                help = _fSession->GetHelp(ev);
                help->DisplayHelp(ev,"iodbasec.hlp",204);
                eventHandled = kODTrue;
                break;
                }
                break;

           } // end switch stmt
        } // end if HLPM_ODWINDOW
        else  {}  // HLPM_ODWINDOW  not implemented      if F1 on Part
        } // end OD_HELP
        break;


#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
        case OD_PRINT:
                eventHandled = somSelf->HandlePrinting(ev, frame, event);
                break;

#ifdef _PLATFORM_OS2_
        case WM_CHAR: //below returns FALSE if non-scrolling key
#endif
#ifdef _PLATFORM_WIN32_
        case WM_KEYDOWN: //below returns FALSE if non-scrolling key
#endif
        case WM_HSCROLL:
        case WM_VSCROLL:
                eventHandled = somSelf->HandleScrollEvent(ev, frame, event);
                break;
#endif

#ifdef _PLATFORM_WIN32_
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDBLCLK:
                {
                   TempODFrame mouseOwner = _fSession->GetArbitrator(ev)->AcquireFocusOwner(ev, _fMouseFocus);
                   // Capture these messages if we are tracking our
                   // mouse events. This prevents an embedded part from
                   // taking over the mouse focus and eating up the
                   // kODEvtMouseUp event which we must process.
                   if((mouseOwner == frame) && (_usMouseMode != kMouseModeNull)){
                      eventHandled = kODTrue;
                   }
                }
                break;
#endif

        default:
                break;
        }                                                      /* endswitch*/


    } // end of try block
    catch (...) {}

    return eventHandled;
}


//--------------------------------------------------------------------------
// BaseContainer --> CompleteMoveOperation
//
//      Perform the actual movement of an embedded part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCompleteMoveOperation
                (
                BaseContainer   *somSelf,           // in
                Environment     *ev,                // in
                ODFrame          *containingFrame,   // in
                ODPoint           *offset              // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerCompleteMoveOperation");


    try {

        // get selected object to Move (we only move the 1st one)
        ALink* itr;
        for (itr = _fSelectedObjects->First(ev); itr->Content(ev); itr = itr->Next(ev))
        {
             ContentObject* selectedObject = (ContentObject*) itr->Content(ev);
             selectedObject->MoveBy(ev, offset);
        }

        containingFrame->Invalidate(ev, kODNULL, kODNULL);
        somSelf->CreateSelectionBorderShapes (ev, kODNULL);
        somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);

        somSelf->ChangeNotification (ev, BCC_MOVE, containingFrame, kODNULL, kODTrue, kODNULL);

    } // end of try block
    catch (...) {}


}

//--------------------------------------------------------------------------
// BaseContainer --> CompleteResizeOperation
//
//      Perform the actual resizing of the frame of an embbedded part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCompleteResizeOperation
                (
                BaseContainer   *somSelf,           // in
                Environment     *ev,                // in
                ContentObject   *contentObject,     // in
                ODULong         resizeFlags,        // in
                ODPoint         *winPoint,           // in
                ODFacet         *facet)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerCompleteResizeOperation");


    try {

        ContentObject *cobj = contentObject;
        if (!cobj)
           cobj = (ContentObject *)_fSelectedObjects->First(ev)->Content(ev);

        // get the old shape for invalidation
        ODRect rect = cobj->_get_boundingRect(ev);
        TempODShape oldShape = facet->CreateShape(ev);
        oldShape->SetRectangle (ev, &rect);
        oldShape->Union (ev, _fSelectShape);
        oldShape->Outset(ev, kODBorderWidth);

        cobj->Resize(ev, winPoint, resizeFlags);

        somSelf->CreateSelectionBorderShapes (ev, kODNULL);

        // invalidate the selection shape
        TempODShape tempShape = _fSelectShape->Copy(ev);
        tempShape->Outset(ev, kODBorderWidth);
        tempShape->Union(ev, oldShape);

        // get tempShape in frame coordinate from content coordinate
        ODFrame *myFrame = cobj->_get_containingFrame (ev);
        TempODTransform intXform = myFrame->AcquireInternalTransform (ev, kODNULL);
        tempShape->Transform (ev, intXform);

        facet->Invalidate(ev, tempShape, kODNULL);
        somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);

        somSelf->ChangeNotification (ev, BCC_RESIZE, facet->GetFrame (ev), cobj, kODTrue, kODNULL);

    } // end of try block
    catch (...) {}

}

//--------------------------------------------------------------------------
// BaseContainer --> HandleMouseUp
//
//      Handle a mouse up event from the user.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleMouseUp
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // in
                ODFrame         *frame,         // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleMouseUp");

    ODBoolean   eventHandled     = kODTrue;

    try {

    // let's relinquish mouse focus first
    _fSession->GetArbitrator(ev)->RelinquishFocus (ev, _fMouseFocus, frame);
    _fSession->GetArbitrator(ev)->RelinquishFocus (ev, _fMouseFocusOutside, frame);

    if (_bcMouseTrack.simEvent == kBCSingleClick)
       eventHandled = somSelf->HandleMouseClick (ev, event, frame, facet, eventInfo);

    else if (_bcMouseTrack.simEvent == kBCMouseDrag)
       eventHandled = somSelf->HandleMouseMotionEnd (ev, event, frame, facet, eventInfo);


    memset (&_bcMouseTrack, 0, sizeof (BC_MOUSETRACK));

    } // end of try block
    catch (...) {}

    return eventHandled;
}


//--------------------------------------------------------------------------
// BaseContainer --> HandleMouseDown
//
//      Handle a mouse down event from the user.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleMouseDown
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // in
                ODFrame         *frame,         // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleMouseDown");

    ODBoolean   eventHandled     = kODTrue;

    try {

    if ( !somSelf->ActivateFrame(ev, frame) )
    {
         // We were unable to acquire the necessary focus and activate.
         return kODFalse;
    }

        ODBoolean rc  = _fSession->GetArbitrator(ev)->RequestFocus (ev, _fMouseFocus, frame);
        ODBoolean rc1 = _fSession->GetArbitrator(ev)->RequestFocus (ev, _fMouseFocusOutside, frame);

    if (rc) {

       memset (&_bcMouseTrack, 0, sizeof (BC_MOUSETRACK));
       _bcMouseTrack.hotSpot.x = ODFixedRound(eventInfo->where.x);
       _bcMouseTrack.hotSpot.y = ODFixedRound(eventInfo->where.y);
       _bcMouseTrack.simEvent = kBCSingleClick;
       memcpy(&(_bcMouseTrack.event), event, sizeof(ODEventData));
       memcpy(&(_bcMouseTrack.eventInfo), eventInfo, sizeof(ODEventInfo));

       TempODShape fShape = frame->AcquireFrameShape (ev, kODNULL);
       TempODTransform intXform = frame->AcquireInternalTransform (ev, kODNULL);
       TempODShape tempShape = fShape->Copy(ev);
       tempShape->InverseTransform (ev, intXform);
       tempShape->GetBoundingBox (ev, &(_bcMouseTrack.frameRect));

#if   defined(_PLATFORM_UNIX_)
       _bcMouseTrack.maxDistance.x = MAX_PIXEL;
       _bcMouseTrack.maxDistance.y = MAX_PIXEL;
#elif defined(_PLATFORM_OS2_)
       _bcMouseTrack.maxDistance.x = WinQuerySysValue(HWND_DESKTOP,SV_CXDBLCLK);
       _bcMouseTrack.maxDistance.y = WinQuerySysValue(HWND_DESKTOP,SV_CYDBLCLK);
#elif defined(_PLATFORM_WIN32_)
       _bcMouseTrack.maxDistance.x = GetSystemMetrics(SM_CXDOUBLECLK);
       _bcMouseTrack.maxDistance.y = GetSystemMetrics(SM_CYDOUBLECLK);
#endif  // PLATFORM SPECIFIC

    }  // end of if rc to check for Focus
#ifdef ODDebug
    else
       PRINT("Mouse focus failed\n");
#endif

    } // end of try block
    catch (...) {}

    return eventHandled;
}


//--------------------------------------------------------------------------
// BaseContainer --> HandleMouseMove
//
//      Handle a mouse move event and set the cursor
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleMouseMove
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // in
                ODFrame         *frame,         // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleMouseMove");

    ODBoolean   eventHandled     = kODTrue;

    try {

    POINT  pt;

          pt.x = ODFixedRound(eventInfo->where.x);
          pt.y = ODFixedRound(eventInfo->where.y);

    if ((_bcMouseTrack.simEvent == kBCSingleClick) &&
       (abs(_bcMouseTrack.hotSpot.x - pt.x) > _bcMouseTrack.maxDistance.x ||
        abs(_bcMouseTrack.hotSpot.y - pt.y) > _bcMouseTrack.maxDistance.y ))
    {
        _bcMouseTrack.simEvent = kBCMouseDrag;
        eventHandled = somSelf->HandleMouseMotionStart (ev, &(_bcMouseTrack.event), frame, facet, &(_bcMouseTrack.eventInfo));
    }

    else if (_bcMouseTrack.simEvent == kBCMouseDrag)
        eventHandled = somSelf->HandleMouseMotionLBDown (ev, event, frame, facet, eventInfo);

    } // end of try block
    catch (...) {}

    return eventHandled;
}



//--------------------------------------------------------------------------
// BaseContainer --> HandleMouseClick
//
//      Handle a mouse click when mouse_up occurs
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleMouseClick
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // in
                ODFrame         *frame,         // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleMouseClick");

    ODBoolean   eventHandled     = kODTrue;

    try {

#ifdef ODDebug
    // PRINT("Mouse Click ..%d \n", somSelf);
#endif
    ODFacet* theFacet            = kODNULL;

    if ( facet != kODNULL )
    {

        ODPoint cursorLocation;
        WinPt2FramePt (ev, event, eventInfo, &cursorLocation, facet);

        if (_usMouseMode == kMouseModeEmbedFromMenu)
        {
             if (_fPartToEmbed) // are we placing a new part?
             {

                 ODTransform* newExternalTransform = frame->CreateTransform(ev);
                 newExternalTransform->SetOffset(ev, &cursorLocation);

                 // create and embed a new part

                 somSelf->Embed(ev, _fPartToEmbed, frame,
                                           newExternalTransform);
                 // reset _fPartToEmbed for next embed operation
                 _usMouseMode = kMouseModeNull;
                 _fPartToEmbed = kODNULL;
             }

        }

        else if (_usMouseMode == kMouseModeTrackMove) // this is the completion of a Move
        {
             ODRect bbox;
             _fSelectShape->GetBoundingBox (ev, &bbox);

             ODPoint offset(cursorLocation);
             offset.x -= bbox.left;
             offset.y -= bbox.top;

             somSelf->CompleteMoveOperation(ev, frame, &offset);
        }

        else if (_usMouseMode == kMouseModeTrackResize) // this is the completion of a Resize
        {

             ODULong resizeFlags = 0;
             resizeFlags = COBJ_RESIZE_BOTTOM | COBJ_RESIZE_RIGHT;
             somSelf->CompleteResizeOperation(ev, kODNULL, resizeFlags, &cursorLocation, facet);
        }

        else if (_usMouseMode == kMouseModeTrackPaste)
             somSelf->PasteSelection(ev, facet, &cursorLocation);

        else if (_usMouseMode == kMouseModeTrackPasteAs)
             somSelf->PasteSelectionAs (ev, facet, &cursorLocation);

        else if (_fSelectedObjects->Count(ev))
              somSelf->DeselectAll(ev);

        _usMouseMode = kMouseModeNull;

     } // if facet

    } // end of try block
    catch (ODException _exception) {
        _usMouseMode = kMouseModeNull;
        _fPartToEmbed = kODNULL;

    } // end of catch block

    return eventHandled;
}

//--------------------------------------------------------------------------
// BaseContainer --> HandleMouseMotionStart
//
//      Handle a mouse_motion_start event when mouse starts moving with MB1 down
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleMouseMotionStart
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // in
                ODFrame         *frame,         // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleMouseMotionStart");

    ODBoolean   eventHandled     = kODTrue;

    try {

       // Get the mouse point in frame coordinates
       ODPoint cursorLocation(ODIntToFixed(_bcMouseTrack.hotSpot.x),
                                 ODIntToFixed(_bcMouseTrack.hotSpot.y));
       ODFacet *myFacet = facet;
       if (!facet)
          myFacet = FirstFacet (ev, frame);

       TempODTransform xform = myFacet->AcquireWindowContentTransform (ev, kODNULL);
       xform->InvertPoint (ev, &cursorLocation);

       // check for resize
       ODBoolean cornerResize = _fCornerHandleShape->ContainsPoint (ev, &cursorLocation);
       ODBoolean edgeResize = _fEdgeHandleShape->ContainsPoint (ev, &cursorLocation);

       if ((!_fDraftReadOnly) && (cornerResize || edgeResize))
       {
          ContentObject *objToResize = kODNULL;
          ODULong resizeFlags = 0x0000;
          ALink *itr;

          // find the contentobject and type of resize
          for (itr = _fSelectedObjects->First(ev); itr->Content(ev); itr = itr->Next(ev))
          {
             ContentObject *cobj = (ContentObject *) itr->Content(ev);
             ODRect bbox = cobj->_get_boundingRect (ev);

             if (edgeResize)
             {
                if ((abs(bbox.left - cursorLocation.x) <= kODBorderWidth)
                    && y_between (cursorLocation.y, bbox.top, bbox.bottom))
                   objToResize=cobj, resizeFlags = COBJ_RESIZE_LEFT;

                else if ((abs(bbox.right - cursorLocation.x) <= kODBorderWidth)
                         && y_between (cursorLocation.y, bbox.top, bbox.bottom))
                        objToResize=cobj, resizeFlags = COBJ_RESIZE_RIGHT;

                else if ((abs(bbox.top - cursorLocation.y) <= kODBorderWidth)
                         && x_between (cursorLocation.x, bbox.left, bbox.right))
                        objToResize=cobj, resizeFlags = COBJ_RESIZE_TOP;

                else if ((abs(bbox.bottom - cursorLocation.y) <= kODBorderWidth)
                         && x_between (cursorLocation.x, bbox.left, bbox.right))
                   objToResize=cobj, resizeFlags = COBJ_RESIZE_BOTTOM;
              }
              else
              {
                if ((abs(bbox.left - cursorLocation.x) <= kODBorderWidth)
                    && (abs(bbox.top - cursorLocation.y) <= kODBorderWidth))
                   objToResize=cobj, resizeFlags = COBJ_RESIZE_LEFT | COBJ_RESIZE_TOP;

                else if ((abs(bbox.left - cursorLocation.x) <= kODBorderWidth)
                    && (abs(bbox.bottom - cursorLocation.y) <= kODBorderWidth))
                   objToResize=cobj, resizeFlags = COBJ_RESIZE_LEFT | COBJ_RESIZE_BOTTOM;

                else if ((abs(bbox.right - cursorLocation.x) <= kODBorderWidth)
                    && (abs(bbox.top - cursorLocation.y) <= kODBorderWidth))
                   objToResize=cobj, resizeFlags = COBJ_RESIZE_RIGHT | COBJ_RESIZE_TOP;

                else if ((abs(bbox.right - cursorLocation.x) <= kODBorderWidth)
                    && (abs(bbox.bottom - cursorLocation.y) <= kODBorderWidth))
                   objToResize=cobj, resizeFlags = COBJ_RESIZE_RIGHT | COBJ_RESIZE_BOTTOM;

              }

             if (objToResize)
                break;

          } // end for


          if (objToResize)
          {
             // fill data struct for resize
             _usMouseMode = kMouseModeTrackMouseResize;
             BC_ResizeData *sd = (BC_ResizeData *) SOMMalloc (sizeof (BC_ResizeData));
#if defined(_PLATFORM_UNIX_)
             ODAIXWindowCanvas *aixwincanvas = (ODAIXWindowCanvas *)
                       (facet->GetCanvas(ev)->GetPlatformCanvas(ev, kODAIX));
             sd->win = aixwincanvas->GetWindow(ev);
#endif

             TempODShape frameShape = frame->AcquireFrameShape (ev, kODNULL);
             sd->focus = new CFocus (myFacet, frameShape, &(sd->dc));

             sd->bbox = objToResize->_get_boundingRect(ev);
             sd->firstPoint = sd->lastPoint = cursorLocation;
             sd->anchorPoint.x = sd->anchorPoint.y = 0;

             if (resizeFlags & COBJ_RESIZE_LEFT)
                sd->anchorPoint.x = sd->bbox.right + kODBorderWidth;
             if (resizeFlags & COBJ_RESIZE_RIGHT)
                sd->anchorPoint.x = sd->bbox.left - kODBorderWidth;
             if (resizeFlags & COBJ_RESIZE_TOP)
#if defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_)
                sd->anchorPoint.y = sd->bbox.bottom + kODBorderWidth;
#elif defined(_PLATFORM_OS2_)
                sd->anchorPoint.y = sd->bbox.bottom - kODBorderWidth;
#endif
             if (resizeFlags & COBJ_RESIZE_BOTTOM)
#if defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_)
                sd->anchorPoint.y = sd->bbox.top - kODBorderWidth;
#elif defined(_PLATFORM_OS2_)
                sd->anchorPoint.y = sd->bbox.top + kODBorderWidth;
#endif
             sd->shape = frame->CreateShape(ev);
#if defined(_PLATFORM_OS2_)
             sd->contentXform = myFacet->AcquireContentTransform (ev, kODNULL);
#elif defined(_PLATFORM_UNIX_)
             sd->contentXform = myFacet->AcquireContentTransform (ev, kODNULL);
#endif
             sd->cobj = objToResize;
             sd->resizeFlags = resizeFlags;

             _resizeData = (void*)sd;

          } // end if .. objToResize
       } // end if .. resize

       // check for move
       else if ((!_fDraftReadOnly) && (_fSelectShape->ContainsPoint (ev, &cursorLocation)))
       {
          // fill data struct for move
          _usMouseMode = kMouseModeTrackMouseMove;
          BC_MoveData *md = (BC_MoveData *) SOMMalloc (sizeof (BC_MoveData));

#if defined(_PLATFORM_UNIX_)
             ODAIXWindowCanvas *aixwincanvas = (ODAIXWindowCanvas *)
                       (facet->GetCanvas(ev)->GetPlatformCanvas(ev, kODAIX));
             md->win = aixwincanvas->GetWindow(ev);
#endif
          TempODShape frameShape = frame->AcquireFrameShape (ev, kODNULL);
          md->focus = new CFocus (myFacet, frameShape, &(md->dc));

          md->lastPoint = md->firstPoint = cursorLocation;
          md->shape = _fSelectShape->Copy (ev);
#if defined(_PLATFORM_OS2_)
          md->contentXform = myFacet->AcquireContentTransform (ev, kODNULL);
#elif defined(_PLATFORM_UNIX_)
          md->contentXform = myFacet->AcquireContentTransform (ev, kODNULL);
#endif
          md->transform = myFacet->CreateTransform (ev);

          _moveData = (void*)md;

       } // end if move
       else
       {
          // perform lasso selection
          _usMouseMode = kMouseModeTrackLassoSelect;
          BC_LassoData *ld = (BC_LassoData *) SOMMalloc (sizeof (BC_LassoData));
          TempODShape frameShape = frame->AcquireFrameShape (ev, kODNULL);
          ld->focus = new CFocus (myFacet, frameShape, &(ld->dc));
          ld->lastPoint = ld->firstPoint = cursorLocation;
#if defined(_PLATFORM_UNIX_)
          ld->contentXform = myFacet->AcquireContentTransform (ev, kODNULL);
          ODAIXWindowCanvas *aixwincanvas = (ODAIXWindowCanvas *)
                       (facet->GetCanvas(ev)->GetPlatformCanvas(ev, kODAIX));
          ld->win = aixwincanvas->GetWindow(ev);
#endif
          ld->shape = myFacet->CreateShape(ev);

          _lassoData = (void*)ld;
       }

    } // end of try block
    catch (...) {}

    return eventHandled;
}


//--------------------------------------------------------------------------
// BaseContainer --> HandleMouseMotionEnd
//
//      Handle a mouse_motion_End event when mouse stops moving with MB1 down
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleMouseMotionEnd
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // in
                ODFrame         *frame,         // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleMouseMotionEnd");

    ODBoolean   eventHandled     = kODTrue;

    try {

       // Get the mouse point in frame coordinates
       ODPoint cursorLocation;
       ODFacet *myFacet = facet;
       if (!facet)
          myFacet = FirstFacet (ev, frame);

       // check for end of resize operation
       if (_usMouseMode == kMouseModeTrackMouseResize)
       {
          WinPt2FramePt (ev, event, eventInfo, &cursorLocation, myFacet);
          BC_ResizeData *sd = (BC_ResizeData *) _resizeData;

          // Erase the last resize rectangle drawn
          somSelf->DrawResizeRectangle(ev, &cursorLocation, BCR_ERASE);

          delete sd->focus;

          // if mouse up is outside frame then use last point
          if (_bcMouseTrack.frameRect.Contains (cursorLocation) == kODFalse)
             cursorLocation = sd->lastPoint;

          // call resize
          somSelf->CompleteResizeOperation (ev, sd->cobj, sd->resizeFlags,
                                          &cursorLocation, myFacet);

          sd->shape->Release(ev);
#if  defined(_PLATFORM_OS2_)
          sd->contentXform->Release (ev);
#elif  defined(_PLATFORM_UNIX_)
          sd->contentXform->Release (ev);
#endif
          SOMFree(sd);
          _resizeData = kODNULL;
       }

       // check for end of move operation
       else if (_usMouseMode == kMouseModeTrackMouseMove)
       {
          WinPt2FramePt (ev, event, eventInfo, &cursorLocation, myFacet);
          BC_MoveData *md = (BC_MoveData *) _moveData;

          // if mouse up was outside the frame then use last point
          if (_bcMouseTrack.frameRect.Contains (cursorLocation) == kODFalse)
             cursorLocation = md->lastPoint;

          delete md->focus;
          md->shape->Release(ev);
          md->transform->Release(ev);
#if  defined(_PLATFORM_OS2_)
          md->contentXform->Release (ev);
#elif  defined(_PLATFORM_UNIX_)
          md->contentXform->Release (ev);
#endif

          // move the selection
          ODPoint delta(cursorLocation);
          delta -= md->firstPoint;

          somSelf->CompleteMoveOperation (ev, frame, &delta);
          SOMFree(md);
          _moveData = kODNULL;

       } // end if move

       // check for end of lasso select
       else if (_usMouseMode == kMouseModeTrackLassoSelect)
       {
          BC_LassoData *ld = (BC_LassoData *)_lassoData;
          delete ld->focus;

          ODRect lassoRect(ld->firstPoint , ld->lastPoint);

          // select objects
          ALink *itr;
          for (itr= _fEmbeddedObjects->First(ev); itr->Content(ev); itr = itr->Next(ev))
          {
             ContentObject *cobj = (ContentObject *) itr->Content(ev);
             if (cobj->_get_selectionState(ev) == kODFalse)
             {
                ODRect bbox = cobj->_get_boundingRect(ev);
                if (lassoRect.Contains(bbox))
                {
                   cobj->_set_selectionState(ev, kODTrue);
                   _fSelectedObjects->AddLast (ev, cobj);
                   somSelf->CreateSelectionBorderShapes (ev, cobj);

                } // end if .. bbox fits in lasso
             } // end if .. not selected
          } // end for

          ld->shape->SetRectangle (ev, &lassoRect);
          ld->shape->Outset (ev,kODBorderWidth);

          // get tempShape in frame coordinate from content coordinate
          TempODTransform intXform = frame->AcquireInternalTransform (ev, kODNULL);
          ld->shape->Transform (ev, intXform);

          frame->Invalidate (ev, ld->shape, kODNULL);

          ld->shape->Release(ev);
#if  defined(_PLATFORM_UNIX_)
          ld->contentXform->Release (ev);
#endif
          SOMFree(ld);
          _lassoData = kODNULL;

       } // end if lasso select

    } // end of try block
    catch (...) {}

    _usMouseMode = kMouseModeNull;

    return eventHandled;
}


//--------------------------------------------------------------------------
// BaseContainer --> HandleMouseMotionLBDown
//
//      Handle a mouse_motion_LBDown event when a mouse moves with MB1 down
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleMouseMotionLBDown
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // in
                ODFrame         *frame,         // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleMouseMotionLBDown");

    ODBoolean   eventHandled     = kODTrue;

#if defined(_PLATFORM_UNIX_)
     XRectangle rgnBox;
#endif

    try {

       // Get the mouse point in frame coordinates
       ODPoint cursorLocation;
       ODFacet *myFacet = facet;
       if (!facet)
          myFacet = FirstFacet (ev, frame);

       WinPt2FramePt (ev, event, eventInfo, &cursorLocation, myFacet);

       // if the mouse is outside my frame then return
       if (_bcMouseTrack.frameRect.Contains (cursorLocation) == kODFalse)
          return eventHandled;

       // check for move
       if (_usMouseMode == kMouseModeTrackMouseMove)
       {
          BC_MoveData *md = (BC_MoveData *) _moveData;

          ODPoint delta(cursorLocation);
          delta -= md->lastPoint;
          md->transform->SetOffset (ev, &delta);
          md->lastPoint = cursorLocation;

          // delete the old shapes and draw new ones
#if defined(_PLATFORM_WIN32_)

          HBRUSH  hairBrush = CreateSolidBrush(RGB(255, 255, 255));
          HBRUSH  hbrOld = SelectObject(md->dc, hairBrush);
          int oldROP2 = SetROP2(md->dc, R2_XORPEN);

          ODRgnHandle borderRgn  = md->shape->GetRegion(ev);
          FillRgn(md->dc, borderRgn, hairBrush);
          md->shape->Transform (ev, md->transform);
          borderRgn  = md->shape->GetRegion(ev);
          FillRgn(md->dc, borderRgn, hairBrush);

          SelectObject(md->dc, hbrOld);
          DeleteObject(hairBrush);
          SetROP2 (md->dc, oldROP2);

#elif defined (_PLATFORM_UNIX_)
         XSetForeground(_fDisplay, md->dc, 1);
         XSetLineAttributes(_fDisplay,md->dc,6, LineSolid, CapButt, JoinRound);
         XSetFunction(_fDisplay, md->dc, GXxor);

          md->shape->Transform (ev, md->contentXform);
          Region borderRgn  = md->shape->GetRegion(ev);
          XSetRegion(_fDisplay, md->dc, borderRgn);
          XClipBox(borderRgn, &rgnBox);
          XDrawRectangle(_fDisplay, md->win, md->dc,
                         rgnBox.x-1, rgnBox.y-1, rgnBox.width, rgnBox.height);
          md->shape->InverseTransform (ev, md->contentXform);

          md->shape->Transform (ev, md->transform);
          md->shape->Transform (ev, md->contentXform);
          borderRgn  = md->shape->GetRegion(ev);
          XSetRegion(_fDisplay, md->dc, borderRgn);
          XClipBox(borderRgn, &rgnBox);
          XDrawRectangle(_fDisplay, md->win, md->dc,
                         rgnBox.x-1, rgnBox.y-1, rgnBox.width, rgnBox.height);
          md->shape->InverseTransform (ev, md->contentXform);

         XSetLineAttributes(_fDisplay,md->dc,1, LineSolid, CapButt, JoinRound);
         XSetFunction(_fDisplay, md->dc, GXcopy);
         XFlush(_fDisplay);

#elif defined (_PLATFORM_OS2_)

          LONG mixOld = GpiQueryMix( md->dc);
          GpiSetMix (md->dc, FM_INVERT);

          md->shape->Transform (ev, md->contentXform);
          ODRgnHandle borderRgn  = md->shape->GetRegion(ev);
          GpiPaintRegion(md->dc, borderRgn);
          md->shape->InverseTransform (ev, md->contentXform);
          md->shape->Transform (ev, md->transform);
          md->shape->Transform (ev, md->contentXform);
          borderRgn  = md->shape->GetRegion(ev);
          GpiPaintRegion(md->dc, borderRgn);
          md->shape->InverseTransform (ev, md->contentXform);

           GpiSetMix (md->dc, mixOld);
#endif

       }
       else if (_usMouseMode == kMouseModeTrackLassoSelect)
       {
          BC_LassoData *ld = (BC_LassoData *) _lassoData;

          // delete the old rect and draw new one
#if defined(_PLATFORM_WIN32_)

          HBRUSH  hairBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255,255,255));
          HBRUSH  hbrOld = SelectObject(ld->dc, hairBrush);
          int oldROP2 = SetROP2(ld->dc, R2_XORPEN);

          for (int i = 0; i < 2; i++)
          {
             ODRect rect(ld->firstPoint, ld->lastPoint);
             ld->shape->SetRectangle (ev, &rect);
             ODRgnHandle hrgn = ld->shape->GetRegion(ev);

             FrameRgn(ld->dc, hrgn, hairBrush, 1, 1);
             ld->lastPoint = cursorLocation;

          } // end for

          SelectObject(ld->dc, hbrOld);
          DeleteObject(hairBrush);
          SetROP2 (ld->dc, oldROP2);

#elif defined (_PLATFORM_UNIX_)

          XSetForeground(_fDisplay, ld->dc, 1);
          XSetLineAttributes(_fDisplay,ld->dc,6,LineSolid, CapButt, JoinRound);
          XSetFunction(_fDisplay, ld->dc, GXxor);

          for (int i = 0; i < 2; i++)
          {
             ODRect rect(ld->firstPoint, ld->lastPoint);
             ld->shape->SetRectangle (ev, &rect);

             ld->shape->Transform (ev, ld->contentXform);
             Region hrgn = ld->shape->GetRegion(ev);
             XSetRegion(_fDisplay, ld->dc, hrgn);
             XClipBox(hrgn, &rgnBox);
             XDrawRectangle(_fDisplay, ld->win, ld->dc,
                          rgnBox.x-1, rgnBox.y-1, rgnBox.width, rgnBox.height);
             ld->lastPoint = cursorLocation;

          } // end for

          XSetLineAttributes(_fDisplay,ld->dc,1,LineSolid, CapButt, JoinRound);
          XSetFunction(_fDisplay, ld->dc, GXcopy);
          XFlush(_fDisplay);

#elif defined (_PLATFORM_OS2_)

          LONG mixOld = GpiQueryMix( ld->dc);
          GpiSetMix (ld->dc, FM_INVERT);

          for (int i = 0; i < 2; i++)
          {
             ODRect rect(ld->firstPoint, ld->lastPoint);
             ld->shape->SetRectangle (ev, &rect);

             POINTL orig = {FixedToInt (rect.left),  FixedToInt (rect.bottom)};
             GpiMove (ld->dc, &orig);
             POINTL ptl =  {FixedToInt (rect.right), FixedToInt (rect.top)};
             GpiBox(ld->dc, DRO_OUTLINE, &ptl, 0, 0);
             ld->lastPoint = cursorLocation;

          } // end for

          GpiSetMix (ld->dc, mixOld);
#endif

       } // end if lasso

       // check for resize
       else if (_usMouseMode == kMouseModeTrackMouseResize)
       {

          // delete the old shape and draw new one
          somSelf->DrawResizeRectangle(ev, &cursorLocation, BCR_REDRAW);
       } // end if ..  resize

    } // end of try block

    catch (...) {}

    return eventHandled;
}


//--------------------------------------------------------------------------
// BaseContainer --> HandleMenuEvent
//
//      Handle a menubar or pulldown menu selection event.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleMenuEvent
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,         // in
                ODEventData     *event          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleMenuEvent");

    ODBoolean   eventHandled     = kODFalse;

    try {

        ALink* itr                   = kODNULL;

#if   defined(_PLATFORM_UNIX_)
        ODMenuEventData* menu_event = (ODMenuEventData*) event;
        switch(menu_event->item)
#elif defined(_PLATFORM_WIN32_)
        switch(LOWORD(event->wParam)) // determine which menu pulldown it was
#elif defined(_PLATFORM_OS2_)
        switch(LONGFROMMP(event->mp1))
#endif
        {
            case CMD(PageSetup):
                 // SetupPrinting returns whether the setup changed,
                 // not whether the event was handled (we assume it was)
                 somSelf->SetupPrinting(ev, frame, event);
                 eventHandled=kODTrue;
                 break;

            case CMD(Print):
                 eventHandled=somSelf->HandlePrinting(ev, frame, event);
                 break;

            case CMD(Open):
                 // Open all selected frames into their own window(s)
                 // We need to copy selected list into a temp list since when
                 // a new window is opened, it grabs focus which makes us
                 // deselect everything and delete selected objects list
                 {
                    ALinkedList *tempList = new ALinkedList;
                    for (itr = _fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
                       tempList->AddLast (ev, itr->Content(ev));

                    for (itr = tempList->First(ev); itr->Content(ev); itr=itr->Next(ev))
                    {
                        ContentFrame *selectedObject =
                             (ContentFrame *) itr->Content(ev);
                        if (selectedObject->_get_objType(ev) == COBJ_FRAMECLASS) {
                           ODFrame *selectedFrame = selectedObject->_get_myFrame(ev);
                           TempODPart tempprt = selectedFrame->AcquirePart(ev);
                           tempprt->Open(ev, selectedFrame);
                        }
                    }

                    delete tempList;
                 }
                 eventHandled=kODTrue;
                 break;

            case CMD(Undo):
                 eventHandled=kODTrue;
                 break;

            case CMD(Redo):
                 eventHandled=kODTrue;
                 break;

            case CMD(Cut):
                 somSelf->CutSelection(ev);
                 eventHandled=kODTrue;
                 break;

            case CMD(Copy):
                 somSelf->CopySelection(ev, kODCloneCopy);
                 eventHandled=kODTrue;
                 break;

            case CMD(Paste):
                 _usMouseMode = kMouseModeTrackPaste;
                 eventHandled=kODTrue;
                 break;

            case CMD(PasteAs):
                 _usMouseMode = kMouseModeTrackPasteAs;
                 eventHandled=kODTrue;
                 break;

            case CMD(Delete):
                 somSelf->DeleteSelection(ev, OBJECT_DELETED);
                 eventHandled=kODTrue;
                 break;

            case CMD(DeselectAll):
                 somSelf->DeselectAll (ev);
                 eventHandled=kODTrue;
                 break;

            case CMD(SelectAll):
                 somSelf->SelectAll(ev);
                 eventHandled=kODTrue;
                 break;

            case CMD(Move):
                 _usMouseMode = kMouseModeTrackMove;
                 _fDirty = kODTrue;
                 eventHandled=kODTrue;
                 break;

            case CMD(Resize):
                 _usMouseMode = kMouseModeTrackResize;
                 _fDirty = kODTrue;
                 eventHandled=kODTrue;
                 break;

            case CMD(MoveBack):
                 somSelf->MoveSelectionToBack(ev);
                 eventHandled=kODTrue;
                 break;

            case CMD(MoveFront):
                 somSelf->MoveSelectionToFront(ev);
                 eventHandled=kODTrue;
                 break;

            case CMD(Help):
                 {
               ODHelp *help = _fSession->GetHelp(ev);
               help->DisplayHelp(ev, "iodbasec.hlp", 100);
               eventHandled = kODTrue;
               break;
                 }

            case CMD(ColorCHANGE):
                 {
                 eventHandled = somSelf->HandleColorChange (ev, frame);
                 break;
                 }

            case CMD(PartInfo):
                 {
                     if (_fSelectedObjects->Count(ev) == 1) {
                         eventHandled = kODTrue;
                         ODBoolean hasWriteAccess = kODTrue;
                         ODInfo* info = _fSession->GetInfo(ev);
                         ContentFrame *cFrame = (ContentFrame *) _fSelectedObjects->First(ev)->Content(ev);
                         if (cFrame->_get_objType(ev) == COBJ_FRAMECLASS) {
                             ODFrame *selFrame = cFrame->_get_myFrame(ev);
                             ODFacet *selFacet = FirstFacet(ev, selFrame);
                             info->ShowPartFrameInfo(ev, selFacet, hasWriteAccess);
                         }
                     }
                 break;
                 }

            case CMD(ViewProperties):
                 {
                 _fSession->GetInfo(ev)->ShowPartFrameInfo(ev,FirstFacet(ev,frame), kODTrue);
                 eventHandled = kODTrue;
                 break;
                 }

            case CMD(ViewSmallIcon):
                 {
                 frame->SetViewType(ev, _fSession->Tokenize(ev, kODViewAsSmallIcon));
                 somSelf->ViewTypeChanged(ev, frame);
                 eventHandled = kODTrue;
                 break;
                 }

            case CMD(ViewLargeIcon):
                 {
                 frame->SetViewType(ev, _fSession->Tokenize(ev, kODViewAsLargeIcon));
                 somSelf->ViewTypeChanged(ev, frame);
                 eventHandled = kODTrue;
                 break;
                 }

            case CMD(ViewThumbNail):
                 {
                 frame->SetViewType(ev, _fSession->Tokenize(ev, kODViewAsThumbnail));
                 somSelf->ViewTypeChanged(ev, frame);
                 eventHandled = kODTrue;
                 break;
                 }

            case CMD(ViewFrame):
                 {
                 frame->SetViewType(ev, _fSession->Tokenize(ev, kODViewAsFrame));
                 somSelf->ViewTypeChanged(ev, frame);
                 eventHandled = kODTrue;
                 break;
                 }

            default:
#if defined(_PLATFORM_UNIX_)
                 int iPart = (menu_event->item)-CMD(Parts);
                 int mi    = menu_event->item;
#elif defined(_PLATFORM_WIN32_)
                 int iPart = LOWORD(event->wParam)-CMD(Parts);
                 int mi    = LOWORD(event->wParam);
#elif defined(_PLATFORM_OS2_)
                 int iPart = SHORT1FROMMP(event->mp1)-CMD(Parts);
                 int mi    = SHORT1FROMMP(event->mp1);
#endif

                 if ( (iPart >=0) &&
                      (iPart < (CMD_Offset_Subclass - kODCommandParts)) ) {

                     // store the part to be embedded (for use when the user picks
                     // the location to place the new embedded part
                     _fPartToEmbed = _fEmbedTable[iPart];
                     _usMouseMode = kMouseModeEmbedFromMenu;
                     eventHandled = kODTrue;
                     _fDirty = kODTrue;

                     break;
                 }

                 // if menuitem is within the valid range of part ids
                 // then we flag it as unused, otherwise we assume the
                 // DocShell will handle it.
                 else if(((mi>=MENUID_ROOTPART_FIRST) && (mi<=MENUID_ROOTPART_LAST))
                         || ((mi>=MENUID_ACTIVEPART_FIRST) && (mi<=MENUID_ACTIVEPART_LAST))) {
#if defined(__IBMCPP__) || defined(_IBMR2)
                     char *bcText;
                     nl_catd bcNlsCatalog;
           setlocale(LC_MESSAGES, NULL);
           bcNlsCatalog=catopen("iodbasec.cat",0);
           if (bcNlsCatalog == CATD_ERR)
           {
              PRINT("Could not open BaseContainer Message catalog!\n");
           }
                     bcText=catgets(bcNlsCatalog,
                                    BCMSG_SET,
                                    BC_MENUBAR_WARNING,
                                    "Don't know how to handle this menu choice: %d!\n");
#else
                     char bcText[256];
                     strcpy(bcText, "Don't know how to handle this menu choice: %d!\n");
#endif

                     char *msgText = new char[strlen(bcText)+20];

#if defined(_PLATFORM_UNIX_)
                     sprintf(msgText,bcText,event->type);
                     cout << msgText << endl;
#elif  defined(_PLATFORM_WIN32_)
                     sprintf(msgText,bcText,LOWORD(event->wParam));
                     MessageBox(NULL,msgText,"BaseContainer",MB_OK|MB_ICONWARNING);
#elif defined(_PLATFORM_OS2_)
                     sprintf(msgText,bcText,(event->mp2));
                     WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,msgText,bcText,0,MB_OK|MB_WARNING);
#endif

                     delete msgText;
#if defined(__IBMCPP__) || defined(_IBMR2)
                     catclose(bcNlsCatalog);
#endif
                 }
                 break;

        } // endswitch which menu pulldown?




    } // end of try block
    catch (...) {}


    return eventHandled;
}


//--------------------------------------------------------------------------
// BaseContainer --> HandleKeyEvent
//
//      Handle keyboard input -- base container handles only ESC key
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleKeyEvent
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODEventData     *event,         // in
                ODFrame         *frame,         // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo      // inout
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleKeyEvent");

    ODBoolean   eventHandled     = kODFalse;

    try {

#if  defined(_PLATFORM_WIN32_)
       if (event->wParam == VK_ESCAPE)
#elif  defined(_PLATFORM_OS2_)
      if (CHAR1FROMMP(event->mp2) == 0x1B) //Esc key
#endif
       {
          somSelf->AbortMouseTracking (ev, frame);
          eventHandled = kODTrue;
       }

    } // end of try block
    catch (...) {}


    return eventHandled;
}


//--------------------------------------------------------------------------
// BaseContainer --> MoveSelectionToFront
//
//      Move selected frames to the foreground.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerMoveSelectionToFront
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerMoveSelectionToFront");

    try {

       ALink *itr = kODNULL;
       for (itr = _fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
       {
           ContentObject *selectedObject = (ContentObject *) itr->Content(ev);
           selectedObject->MoveToFront(ev);
           _fEmbeddedObjects->Remove (ev, selectedObject);
           _fEmbeddedObjects->AddLast (ev, selectedObject);
       }
       somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);

    } // end of try block

    catch (...) {}



}




//--------------------------------------------------------------------------
// BaseContainer --> MoveSelectionToBack
//
//      Move the selected frames to the background.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerMoveSelectionToBack
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerMoveSelectionToBack");


    try {

       ALink *itr = kODNULL;
       for (itr = _fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
       {
           ContentObject *selectedObject = (ContentObject *) itr->Content(ev);
           selectedObject->MoveToBack(ev);
           _fEmbeddedObjects->Remove (ev, selectedObject);
           _fEmbeddedObjects->AddFirst (ev, selectedObject);
       }
       somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);

    } // end of try block

    catch (...) {}


}



//--------------------------------------------------------------------------
// BaseContainer --> SelectEmbeddedPart
//
//      Select a specific embedded part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerSelectContentObject
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ContentObject   *contentObject         // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerSelectContentObject");


    try {

        TempODShape tempShape = kODNULL;

        if (contentObject->_get_selectionState(ev)) {

            // compute shape for invalidation
            tempShape = _fSelectShape->Copy(ev);
            tempShape->Union (ev, _fCornerHandleShape);
            tempShape->Union (ev, _fEdgeHandleShape);

            // Deselect this
            if (_fSelectedObjects->Count(ev) == 1)
               somSelf->DeselectAll(ev);
            else {
               contentObject->_set_selectionState(ev, kODFalse);
               _fSelectedObjects->Remove(ev, contentObject);
               somSelf->CreateSelectionBorderShapes(ev, kODNULL);
            }
        }
        else  {

            // Select this one
            contentObject->_set_selectionState(ev, kODTrue);
            _fSelectedObjects->AddLast(ev, contentObject);
            somSelf->CreateSelectionBorderShapes(ev, contentObject);

            // compute shape for invalidation
            tempShape = _fSelectShape->Copy(ev);
            tempShape->Union (ev, _fCornerHandleShape);
            tempShape->Union (ev, _fEdgeHandleShape);

        }

        // get tempShape in frame coordinate from content coordinate
        ODFrame *myFrame = contentObject->_get_containingFrame (ev);
        TempODTransform intXform = myFrame->AcquireInternalTransform (ev, kODNULL);
        tempShape->Transform (ev, intXform);

        myFrame->Invalidate(ev, tempShape, kODNULL);

    } // end of try block
    catch (...) {}


}


//--------------------------------------------------------------------------
// ODPart --> DragEnter
//
//      Should begin tracking a drag operation.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODDragResult
SOMLINK         BaseContainerDragEnter
                (
                BaseContainer       *somSelf,   // in
                Environment         *ev,        // in
                ODDragItemIterator  *dragInfo,  // in
                ODFacet             *facet,     // in
                ODPoint             *where      // in
                )
{
    BaseContainerData *somThis       = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDragEnter");


    ODDragAndDrop     *dad;
    ODStorageUnit     *dragSU;
    ODULong           dragAttributes;

    try {

    _fDropAccepted = kODTrue;
    dad            = _fSession->GetDragAndDrop(ev);

    if (dad)
      dragAttributes = dad->GetDragAttributes(ev);

    if((_fDropAccepted) && !(dragAttributes & kODDragIsInSourceFrame)) {
       somSelf->InvertDragHilite( ev, facet );
    }


    } // end of try block
    catch (...) {}


    return(_fDropAccepted);

}



//--------------------------------------------------------------------------
// ODPart --> DragWithin
//
//      Should track a drag operation and provide graphical feedback
//      regarding possible drag targets.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODDragResult
SOMLINK         BaseContainerDragWithin
                (
                BaseContainer       *somSelf,   // in
                Environment         *ev,        // in
                ODDragItemIterator  *dragInfo,  // in
                ODFacet             *facet,     // in
                ODPoint             *where      // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDragWithin");


    return(_fDropAccepted);;
}



//--------------------------------------------------------------------------
// ODPart --> DragLeave
//
//      Should finish tracking a drag operation and deactivate this part
//      from drag tracking.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDragLeave
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet,         // in
                ODPoint         *where          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDragLeave");



  try {

  if (_fDropAccepted) {
    somSelf->InvertDragHilite( ev, facet );
  }

  } // end of try block
  catch (...) {}

}


//--------------------------------------------------------------------------
// BaseContainer --> InvertDragHilite( ev, facet );
//
//      Inverts the border around the facet
//
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerInvertDragHilite
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet          // in
                )

{

    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerInvertDragHilite");

   try {

#if defined(_PLATFORM_OS2_)
     HPS hdc;

     ODFrame         *frame = facet->GetFrame(ev);
     TempODShape clip_shape = facet->AcquireAggregateClipShape(ev, kODNULL);
     TempODShape shape = clip_shape->Copy(ev);
     TempODTransform tf = facet->AcquireWindowFrameTransform(ev,kODNULL);

     // transform the clip shape to the Container's coords
     shape->Transform(ev,tf);
     ODRgnHandle rgn = shape->GetRegion(ev);
     ODPoint offset(0,0);
     tf->TransformPoint(ev, &offset);

     // get drag drop PS and set it in invert mode
     HWND hwndFacet = facet->GetFacetHWND(ev);
     hdc = DrgGetPS(hwndFacet);
     LONG mixOld = GpiQueryMix( hdc);
     GpiSetMix (hdc, FM_INVERT);

     POINTL winPt;
     winPt.x = -FixedToInt(offset.x);
     winPt.y = -FixedToInt(offset.y);
     GpiOffsetRegion(hdc, rgn, &winPt);

     SIZEL sizlThickness = {5,5} ;
     GpiFrameRegion (hdc, rgn, &sizlThickness);

     GpiSetMix( hdc, mixOld );
     DrgReleasePS(hdc);

#elif defined(_PLATFORM_WIN32_)
     HDC hdc;

     RECT rc;
     UINT dd = 5;
     HWND hwndFacet = facet->GetFacetHWND(ev);
     //hdc = GetWindowDC(hwndFacet);
     hdc = GetDCEx(hwndFacet, NULL,DCX_CACHE | DCX_LOCKWINDOWUPDATE | DCX_CLIPSIBLINGS);
     GetClientRect (hwndFacet, &rc);

     // draw the feedback
     PatBlt ( hdc, rc.left, rc.top, rc.right-rc.left, dd, DSTINVERT);
     PatBlt ( hdc, rc.left, rc.top+dd, dd, rc.bottom-rc.top-(2*dd), DSTINVERT);
     PatBlt ( hdc, rc.left, rc.bottom-dd, rc.right-rc.left, dd, DSTINVERT);
     PatBlt ( hdc, rc.right-dd, rc.top+dd, dd, rc.bottom-rc.top-(2*dd), DSTINVERT);

     ReleaseDC (hwndFacet, hdc);

#elif defined(_PLATFORM_UNIX_)

     XPoint point;
     unsigned long valmask;
     XGCValues vals;
     unsigned long backgrnd;
     unsigned long foregrnd;
     XRectangle rgnBox;

     ODAIXWindowCanvas *aixwincanvas = (ODAIXWindowCanvas *)
                       (facet->GetCanvas(ev)->GetPlatformCanvas(ev, kODAIX));

     Widget widget = aixwincanvas->GetWidget(ev);
     Window window = aixwincanvas->GetWindow(ev);

// save off the background and foreground colors and reverse them
     GC gc = aixwincanvas->GetGC(ev);
     XGetGCValues(_fDisplay, gc, (GCForeground | GCBackground), &vals);
     foregrnd = vals.foreground;
     backgrnd = vals.background;
     XSetForeground(_fDisplay, gc, backgrnd);
     XSetBackground(_fDisplay, gc, foregrnd);

// get region from OpenDoc
     ODFrame         *frame = facet->GetFrame(ev);
     TempODShape clip_shape = facet->AcquireAggregateClipShape(ev, kODNULL);
     TempODShape shape = clip_shape->Copy(ev);
     TempODTransform tf = facet->AcquireWindowFrameTransform(ev,kODNULL);

// transform the clip shape to the Container's coords
     shape->Transform(ev,tf);
     ODRgnHandle shapeRgn;

     shapeRgn = shape->GetRegion(ev);
     XSetRegion(_fDisplay, gc, shapeRgn);

     ODPoint offset(0,0);
     tf->TransformPoint(ev, &offset);
     point.x = -FixedToInt(offset.x);
     point.y = -FixedToInt(offset.y);

     XOffsetRegion(shapeRgn, point.x, point.y);
     XClipBox(shapeRgn, &rgnBox);

     XDrawRectangle(_fDisplay, window, gc, rgnBox.x, rgnBox.y, rgnBox.width, rgnBox.height);

#endif

   } // end of try block
   catch (...) {}
}



//--------------------------------------------------------------------------
// BaseContainer --> CopySelection
//
//      Start of Copy/Paste operation
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCopySelection
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODCloneKind      cloneKind      // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCopySelection");

    // nothing to copy .. leave
    ODULong num = _fSelectedObjects->Count(ev);
    if (!num)
       return;

    try {

    // Acquire clipboard focus
    TempODFrame clipboardOwner = _fSession->GetArbitrator(ev)->AcquireFocusOwner(ev, _fClipboardFocus);
    ContentFrame *cobj = (ContentFrame *) _fSelectedObjects->First(ev)->Content(ev);
    ODFrame *frame = cobj->_get_containingFrame (ev);
    ODBoolean gotCB = kODFalse;

    if (_fDisplayFrames->Contains (ev, clipboardOwner) == kODFalse) {
       gotCB=_fSession->GetArbitrator(ev)->RequestFocus(ev,_fClipboardFocus, frame);
       if (!gotCB) {
          WARNMSG (WARN_INDEX(-1), "Could not get clipboard focus");
          return;
       }
    }
    else
       PRINT("** One of my frames has clipboard focus");

    // start of a new clip operation so we clear the clipboard

    ODClipboard*  clipboard = _fSession->GetClipboard(ev);
    clipboard->Clear(ev);
    ODStorageUnit* clipSU = clipboard->GetContentStorageUnit(ev);

    if ((num == 1) && (cobj->_get_objType(ev) == COBJ_FRAMECLASS)) {

         // special case: copy single embedded frame to clipboard
         ODFrame *embeddedFrame = cobj->_get_myFrame(ev);
         somSelf->WriteSingleFrame (ev, embeddedFrame, clipSU, cloneKind);

    }
    else {

         somSelf->WriteKindInfo (ev, clipSU);
         BCCloneInfo cloneInfo;
         memset (&cloneInfo, 0, sizeof(BCCloneInfo));

         ODDraft *fromDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
         ODDraft *toDraft = clipSU->GetDraft(ev);
         ODDraftKey key = 0;
         key = fromDraft->BeginClone (ev, toDraft, kODNULL, cloneKind);
         cloneInfo.key = key;

         somSelf->WriteContents (ev, clipSU, &cloneInfo, CLONE_SELECTED);

         fromDraft->EndClone (ev, key);
    }

    // Export data to clipboard
    clipboard->ExportClipboard(ev);

    // Relinquish clipboard focus
    if (gotCB)
        _fSession->GetArbitrator(ev)->RelinquishFocus(ev, _fClipboardFocus, frame);

    } // end of try block
    catch (...) {}
}



//--------------------------------------------------------------------------
// BaseContainer --> PasteSelection
//
//      Completion of Cut/Copy/Paste operation
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerPasteSelection
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODFacet         *facet,          // in
                ODPoint         *toWhere
                )
{

    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerPasteSelection");

    try {

      // Acquire clipboard focus
      TempODFrame clipboardOwner = _fSession->GetArbitrator(ev)->AcquireFocusOwner(ev, _fClipboardFocus);
      ODBoolean gotCB = kODFalse;

      if (clipboardOwner != facet->GetFrame(ev)) {
         gotCB=_fSession->GetArbitrator(ev)->RequestFocus(ev,_fClipboardFocus, facet->GetFrame(ev));
         if (!gotCB) {
            WARNMSG (WARN_INDEX(-1), "Could not get clipboard focus");
            return;
         }
      }
      else
         PRINT("** One of my frames has clipboard focus");


      ODClipboard*  clipboard = _fSession->GetClipboard(ev);
      ODStorageUnit* clipSU = clipboard->GetContentStorageUnit(ev);

      // If a ContentFrame property exists then get single frame
      if ((clipSU->Exists(ev, kODPropContentFrame, kODWeakStorageUnitRef, 0))
          || (somSelf->ReadKindInfo(ev, clipSU) == kODFalse))
      {
         ODFrame *embeddedFrame = somSelf->ReadSingleFrame (ev, facet,
                                         clipSU, kODClonePaste, toWhere);
         ContentFrame *contFrame = new ContentFrame();
         contFrame->_set_myFrame (ev, embeddedFrame);
        _fEmbeddedObjects->AddLast(ev, contFrame);
      }
      else if (somSelf->ReadKindInfo(ev, clipSU)) {

         BCCloneInfo cloneInfo;
         memset (&cloneInfo, 0, sizeof(BCCloneInfo));

         ODDraft *toDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
         ODDraft *fromDraft = clipSU->GetDraft(ev);
         ODDraftKey key = 0;
         key = fromDraft->BeginClone (ev, toDraft, kODNULL, kODClonePaste);
         cloneInfo.key = key;
         cloneInfo.refPoint = toWhere;
         cloneInfo.myFrame = facet->GetFrame (ev);

         somSelf->ReadContents(ev, clipSU, &cloneInfo, CLONE_ALL);

         fromDraft->EndClone (ev, key);

      }

      // Relinquish clipboard focus
      if (gotCB)
          _fSession->GetArbitrator(ev)->RelinquishFocus(ev, _fClipboardFocus, facet->GetFrame(ev));

      somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);
      somSelf->ChangeNotification (ev, BCC_PASTE, facet->GetFrame(ev), kODNULL, kODTrue, kODNULL);

    } // end of try block
    catch (...) {}
}




//--------------------------------------------------------------------------
// BaseContainer --> PasteSelectionAs
//
//      Completion of Cut/Copy/Paste operation
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerPasteSelectionAs
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODFacet         *facet,          // in
                ODPoint         *toWhere
                )
{

    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerPasteSelectionAs");

    try {

       somSelf->PasteSelection (ev, facet, toWhere);

    } // end of try block
    catch (...) {}

}


//--------------------------------------------------------------------------
// BaseContainer --> DeleteSelection
//
//      Deletes all user selection from the document.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDeleteSelection
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODULong         type
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDeleteSelection");


    try {
        ALink* itr                   = kODNULL;
        ContentObject *selectedObject = kODNULL;
        ALinkedList *tempList = new ALinkedList;

        // We first store the selection in a temp list for deletion
        // If you don't use a temp list then we run into a strange
        // problem where if any of the selected parts are opened in
        // their own windows then while closing those windows I lose
        // focus and as a result I clear selection when I am in the
        // middle of iterating over it. So I should copy the selection
        // in another list and iterate over that list.

        for (itr = _fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
            tempList->AddLast (ev, (ContentObject*) itr->Content(ev));

        // get rid of the selected objects list
        delete _fSelectedObjects;
        _fSelectedObjects=new ALinkedList();


        for (itr = tempList->First(ev); itr->Content(ev); itr=itr->Next(ev))
        {

           selectedObject = (ContentObject *) itr->Content(ev);
           selectedObject->DeleteContents(ev, type);
           _fEmbeddedObjects->Remove(ev, selectedObject);
           delete selectedObject;
        }

        delete tempList;

        // Reset all the selection border shapes

        _fSelectShape->Reset (ev);
        _fCornerHandleShape->Reset (ev);
        _fEdgeHandleShape->Reset (ev);

        for (itr = _fDisplayFrames->First(ev); itr->Content(ev); itr=itr->Next(ev))
        {
            ODFrame *myFrame = (ODFrame *) itr->Content(ev);
            myFrame->Invalidate(ev, kODNULL, kODNULL);
        }

        somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);

        somSelf->ChangeNotification (ev, BCC_DELETE, kODNULL, kODNULL, kODTrue, kODNULL);

    } // end of try block
    catch (...) {}


}


//--------------------------------------------------------------------------
// BaseContainer --> CutSelection(Environment *)
//
//      Performs the cut operation (weak comment TBD)
//
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCutSelection(BaseContainer *somSelf,
                                   Environment *ev)

{
    somSelf->CopySelection(ev, kODCloneCopy);
    somSelf->DeleteSelection(ev, OBJECT_DELETED);
}


//--------------------------------------------------------------------------
// BaseContainer --> DeselectAll
//
//      Clear all user selection (turn off hilighting...)
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDeselectAll
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDeselectAll");


    try {
        ALink* itr                   = kODNULL;

        // Iterate over SelectedFrames and turn off selection highlight
        for (itr = _fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
        {
            ContentObject *selectedObject = (ContentObject *) itr->Content(ev);
            selectedObject->_set_selectionState(ev, kODFalse);
        }

        // delete selected frames array and reset pointer to a new ALinkedList
        delete _fSelectedObjects;
        _fSelectedObjects=new ALinkedList();

        // compute the shape for invalidation
        TempODShape tempShape = _fSelectShape->Copy(ev);
        tempShape->Union (ev, _fCornerHandleShape);
        tempShape->Union (ev, _fEdgeHandleShape);

        // Reset all the selection border shapes
        _fSelectShape->Reset (ev);
        _fCornerHandleShape->Reset (ev);
        _fEdgeHandleShape->Reset (ev);


        for (itr = _fDisplayFrames->First(ev); itr->Content(ev); itr=itr->Next(ev))
        {
            ODFrame *myFrame = (ODFrame *) itr->Content(ev);

            // get tempShape in frame coordinate from content coordinate
            TempODTransform intXform = myFrame->AcquireInternalTransform (ev, kODNULL);
            tempShape->Transform (ev, intXform);

            myFrame->Invalidate(ev, tempShape, kODNULL);
            tempShape->InverseTransform (ev, intXform);
        }


    } // end of try block
    catch (...) {}


}



//--------------------------------------------------------------------------
// BaseContainer --> SelectAll
//
//      Select all embedded parts.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerSelectAll
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerSelectAll");


    try {
        ALink* itr                   = kODNULL;

        // Iterate over all EmbeddedFrames and select each

        for (itr=_fEmbeddedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
        {
            ContentObject *embedObject = (ContentObject *) itr->Content(ev);
            if (!embedObject->_get_selectionState(ev)) {
               embedObject->_set_selectionState(ev, kODTrue);
               _fSelectedObjects->AddLast(ev, embedObject);
               somSelf->CreateSelectionBorderShapes (ev, embedObject);
            }
        }

        // compute the shape for invalidation
        TempODShape tempShape = _fSelectShape->Copy(ev);
        tempShape->Union (ev, _fCornerHandleShape);
        tempShape->Union (ev, _fEdgeHandleShape);

        for (itr = _fDisplayFrames->First(ev); itr->Content(ev); itr=itr->Next(ev))
        {
            ODFrame *myFrame = (ODFrame *) itr->Content(ev);

            // get tempShape in frame coordinate from content coordinate
            TempODTransform intXform = myFrame->AcquireInternalTransform (ev, kODNULL);
            tempShape->Transform (ev, intXform);

            myFrame->Invalidate(ev, tempShape, kODNULL);
            tempShape->InverseTransform (ev, intXform);
        }

    } // end of try block
    catch (...) {}


}



//--------------------------------------------------------------------------
// BaseContainer --> HandleColorChange
//
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleColorChange
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame         // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleColorChange");


    try {

       FramePartInfo *pInfo =(FramePartInfo *)frame->GetPartInfo(ev);
       pInfo->NeedsActivating = (frame->IsRoot(ev)) ? kODTrue : kODFalse;
       somSelf->SetBackgroundColor(ev,somSelf->ColorSelection(ev,_fBackgroundColor, 1));

       ALink *itr;
       for (itr = _fDisplayFrames->First(ev); itr->Content(ev); itr=itr->Next(ev))
       {
             ODFrame *myFrame = (ODFrame *) itr->Content(ev);
             myFrame->Invalidate(ev, kODNULL, kODNULL);

       }

       somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);

       somSelf->ChangeNotification (ev, BCC_INTRINSIC, kODNULL, kODNULL, kODTrue, kODNULL);

    } // end of try block
    catch (...) {}

    return kODTrue;
}


//--------------------------------------------------------------------------
// BaseContainer --> HandleKeyEvent
//
//      Handle keyboard input -- base container handles only ESC key
//
//      ->
//--------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         BaseContainerAbortMouseTracking
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerAbortMouseTracking");


    try {

          switch (_usMouseMode)
          {
             case kMouseModeTrackLassoSelect:
                {
                   BC_LassoData *ld = (BC_LassoData *)_lassoData;
                   delete ld->focus;

                   TempODShape tempShape = ld->shape->Copy(ev);
                   tempShape->Outset (ev, kODBorderWidth);

                   // get tempShape in frame coordinate from content coordinate
                   TempODTransform intXform = frame->AcquireInternalTransform (ev, kODNULL);
                   tempShape->Transform (ev, intXform);
                   frame->Invalidate (ev, tempShape, kODNULL);

                   ld->shape->Release(ev);
                   SOMFree(ld);
                   _lassoData = kODNULL;
                }
                break;
             case kMouseModeTrackMouseMove:
                {
                   BC_MoveData *md = (BC_MoveData *) _moveData;
                   delete md->focus;

                   TempODShape tempShape = md->shape->Copy(ev);
#if  defined(_PLATFORM_OS2_)
                    md->contentXform->Release(ev);
#endif
                   tempShape->Union (ev, _fSelectShape);
                   tempShape->Outset (ev, kODBorderWidth);

                   // get tempShape in frame coordinate from content coordinate
                   TempODTransform intXform = frame->AcquireInternalTransform (ev, kODNULL);
                   tempShape->Transform (ev, intXform);

                   frame->Invalidate (ev, tempShape, kODNULL);
                   md->shape->Release(ev);
                   md->transform->Release(ev);
                   SOMFree(md);
                   _moveData = kODNULL;
                }
                break;
             case kMouseModeTrackMouseResize:
                {
                   BC_ResizeData *rd = (BC_ResizeData *) _resizeData;
                   delete rd->focus;

                   TempODShape tempShape = rd->shape->Copy(ev);
#if  defined(_PLATFORM_OS2_)
                   tempShape->InverseTransform( ev, rd->contentXform);
                   rd->contentXform->Release(ev);
#endif
                   tempShape->Union (ev, _fSelectShape);
                   tempShape->Outset (ev, kODBorderWidth);

                   // get tempShape in frame coordinate from content coordinate
                   TempODTransform intXform = frame->AcquireInternalTransform (ev, kODNULL);
                   tempShape->Transform (ev, intXform);

                   frame->Invalidate (ev, tempShape, kODNULL);
                   rd->shape->Release(ev);
                   SOMFree(rd);
                   _resizeData = kODNULL;
                }
                break;
          } // end switch

          _usMouseMode = kMouseModeNull;
          _fPartToEmbed = kODNULL;

    }
    catch (...) {}

}


//--------------------------------------------------------------------------
// BaseContainer --> DrawResizeRectangle
//
//      Erases the last rectangle drawn if drawType is BCR_EERASE. If the
//      the drawType is BCR_REDRAW, it will draw a new resize rectangle after
//      erasing the old one.
//
//      -> This method is called in HandleMouseMotionLBDown and in
//         HandleMouseMotionEnd.
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDrawResizeRectangle
                (
                BaseContainer   *somSelf,        // in
                Environment     *ev,             // in
                ODPoint         *cursorLocation, // in
                BC_RECTDRAWTYPE drawType         // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDrawResizeRectangle");

    BC_ResizeData *sd = (BC_ResizeData *) _resizeData;

    // Store the current drawing attributes.

#if defined(_PLATFORM_WIN32_)

    HBRUSH  hairBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255,255,255));
    HBRUSH  hbrOld = SelectObject(sd->dc, hairBrush);
    int oldROP2 = SetROP2(sd->dc, R2_XORPEN);

#elif defined(_PLATFORM_UNIX_)

    XSetForeground(_fDisplay, sd->dc, 1);
    XSetLineAttributes(_fDisplay,sd->dc,6,LineSolid, CapButt, JoinRound);
    XSetFunction(_fDisplay, sd->dc, GXxor);

#elif defined(_PLATFORM_OS2_)

    LONG mixOld = GpiQueryMix( sd->dc);
    GpiSetMix (sd->dc, FM_INVERT);
#endif

    ODRect rect;

    // If redrawing, we must draw twice: once to erase the last rectangle,
    // and a second time to draw the new rectangle. Otherwise, just draw
    // once in XOR mode over the last rectangle to erase it.
    int drawMax = (drawType == BCR_REDRAW) ? 2: 1;

    for (int i = 0; i < drawMax; i++)
    {

       if (sd->anchorPoint.x == 0)
       {
          rect.left = sd->bbox.left - kODBorderWidth;
          rect.right = sd->bbox.right + kODBorderWidth;
       }
       else
       {
          rect.left = min (sd->anchorPoint.x, sd->lastPoint.x);
          rect.right = max (sd->anchorPoint.x, sd->lastPoint.x);
       }
       if (sd->anchorPoint.y == 0)
       {
#if defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_)
          rect.top = sd->bbox.top - kODBorderWidth;
          rect.bottom = sd->bbox.bottom + kODBorderWidth;
#elif defined(_PLATFORM_OS2_)
          rect.top = sd->bbox.top + kODBorderWidth;
          rect.bottom = sd->bbox.bottom - kODBorderWidth;
#endif
       }
       else
       {
#if defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_)
          rect.top = min (sd->anchorPoint.y, sd->lastPoint.y);
          rect.bottom = max (sd->anchorPoint.y, sd->lastPoint.y);
#elif defined(_PLATFORM_OS2_)
          rect.top = max (sd->anchorPoint.y, sd->lastPoint.y);
          rect.bottom = min (sd->anchorPoint.y, sd->lastPoint.y);
#endif
       }

       sd->shape->SetRectangle (ev, &rect);

#if defined(_PLATFORM_WIN32_)
       ODRgnHandle hrgn = sd->shape->GetRegion(ev);
       FrameRgn(sd->dc, hrgn, hairBrush, kODBorderWidth >> 16 , kODBorderWidth >> 16);
#elif defined(_PLATFORM_UNIX_)

       sd->shape->Transform (ev, sd->contentXform);
       Region hrgn = sd->shape->GetRegion(ev);
       XSetRegion(_fDisplay, sd->dc, hrgn);
       XRectangle rgnBox;
       XClipBox(hrgn, &rgnBox);
       XDrawRectangle(_fDisplay, sd->win, sd->dc,
                      rgnBox.x, rgnBox.y, rgnBox.width, rgnBox.height);

#elif defined(_PLATFORM_OS2_)
       sd->shape->Transform (ev, sd->contentXform);
       ODRgnHandle hrgn = sd->shape->GetRegion(ev);
       SIZEL thickness = {kODBorderWidth >> 16 , kODBorderWidth >> 16};
       GpiFrameRegion(sd->dc, hrgn, &thickness);
#endif

       sd->lastPoint = *cursorLocation;

    } // end for


    // Restore the old drawing attributes
#if defined(_PLATFORM_WIN32_)
    SelectObject(sd->dc, hbrOld);
    DeleteObject(hairBrush);
    SetROP2 (sd->dc, oldROP2);

#elif defined (_PLATFORM_UNIX_)
    XSetLineAttributes(_fDisplay,sd->dc,1,LineSolid, CapButt, JoinRound);
    XSetFunction(_fDisplay, sd->dc, GXcopy);
    XFlush(_fDisplay);

#elif defined (_PLATFORM_OS2_)
    GpiSetMix (sd->dc, mixOld);

#endif
}
