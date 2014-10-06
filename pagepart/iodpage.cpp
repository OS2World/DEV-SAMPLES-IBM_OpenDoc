//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odpagepart
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

//   @(#) 1.19 com/src/samples/pagepart/iodpage.cpp, odpagepart, od96os2, odos29712d 3/7/97 13:03:16 [3/21/97 17:48:53]


#ifndef SOM_Module_IODPage_Source
#define SOM_Module_IODPage_Source
#endif
#define VARIABLE_MACROS
#define METHOD_MACROS

#define PageLayout_Class_Source
#define M_PageLayout_Class_Source

#ifdef _PLATFORM_OS2_
#define INCL_PM
#define INCL_GPI
#define INCL_GPICIDS
#define INCL_GPIPRIMITIVES
#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_DEV

#include <os2.h>

#define HDRAW HPS

// #define SMART_DRAWING // enables _fVisiblePagesShape and _fBackgroundShape code
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <commdlg.h>
#include <commctrl.h>

#define HDRAW HDC
#endif //_PLATFORM_WIN32_

#ifndef _ALTPOINT_
#include <AltPoint.h> //jwa - MUST be included BEFORE ODTypes.h (better ODPoint, ODRect)
#endif

#include <barray.h>
#include <focuslib.h>
#include <ODDebug.h>
#include <ODRegApi.h>
#include <ODRes.h>
#include <ODTypes.h>
#include <ODUtils.h>
#include <StorUtil.h>

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

#ifndef SOM_ODMenuBar_xh
#include <MenuBar.xh>
#endif

#ifndef SOM_ODSession_xh
#include <ODSessn.xh>
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

#ifndef SOM_ODWindow_xh
#include <Window.xh>
#endif

#include <iostream.h>

#include <ODRegApi.h>
#include <ODDebug.h>

#ifndef SOM_PageLayoutPrintExtension_xh
#include <IODPrint.hpp>
#include <IODPgPrn.xh>
#endif

#ifndef SOM_ODScrollExtension_xh
#include <IODScrol.hpp>
#include <IODScrol.xh>
#endif

#ifndef _IODPAGE_RESOURCE_HEADER_
#include "IODPgRes.h"
#endif

#include <StdExts.xh>                    // for extension id strings

#include "IODPage.xih"
#include "IODPage.hpp"

HMODULE MyResources = 0;

char* MRI(int id);
extern void WarningBox(HWND hwnd, int MSG, char *stg);
extern void CenterWindow(HWND hwnd); /* One of the ODPrintExtension's helpers */

#ifdef _PLATFORM_OS2_
MRESULT EXPENTRY ChoosePageDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY GetTextDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
LRESULT CALLBACK ChoosePageDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GetTextDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif //_PLATFORM_WIN32_


/********************************************************************
  PageLayout's helper functions
********************************************************************/

inline void InitPropVal (Environment *ev, ODStorageUnit *su,
                         ODPropertyName propName, ODValueType valName)
{
    if (ODSUExistsThenFocus (ev, su, propName, valName))
         su->Remove (ev);

    ODSUAddPropValue (ev, su, propName, valName);

}


//--------------------------------------------------------------------------
//
// This retrieves a character string from the string table in our resources
//
//--------------------------------------------------------------------------

char* MRI(int id)
{
   char *ReturnValue = (char *) malloc(sizeof(char)*256);
   int rc = 0;

#ifdef _PLATFORM_OS2_
   rc = WinLoadString((HAB)0, MyResources, id, 255, ReturnValue); // read string table
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   rc = LoadString(MyResources, id, ReturnValue, 255);// read string table
#endif

   if (!rc) {
      strcpy(ReturnValue, StringNotFoundMsg);
   } /* endif */

   return ReturnValue;
}


#ifdef _PLATFORM_WIN32_
LRESULT CALLBACK ChoosePageDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   static short MaxPages;
   short PageNumber;
   BOOL error;

   switch (msg) {
   case WM_INITDIALOG:
      switch (HIWORD(lParam)) {
      case GoToPageDlgValue:
         SetWindowText(hwnd, MRI(GoToPageDlgTitle));
         break;
      case InsertPageDlgValue:
         SetWindowText(hwnd, MRI(InsertPageDlgTitle));
         break;
      case RemovePageDlgValue:
         SetWindowText(hwnd, MRI(RemovePageDlgTitle));
         break;
      } /* endswitch */

      SetDlgItemText(hwnd, ChoosePageEntryField, "1");
      MaxPages = LOWORD(lParam);

#if 0 //couldn't get the spin button to work if defined in rc file
      SendDlgItemMessage(hwnd, ChoosePageSpinButton, UDM_SETRANGE,
         (WPARAM) 0, (LPARAM) MAKELONG(MaxPages, 1));
#else
      CreateUpDownControl(WS_CHILD | WS_BORDER | WS_VISIBLE |
         UDS_SETBUDDYINT | UDS_ARROWKEYS | UDS_WRAP | UDS_ALIGNRIGHT,
         0, 0, 0, 0, hwnd, ChoosePageSpinButton, MyResources,
         GetDlgItem(hwnd, ChoosePageEntryField), MaxPages, 1, 1);
#endif
      break;

   case WM_COMMAND:
      switch (LOWORD(wParam)) {
      case IDOK:
         PageNumber = GetDlgItemInt(hwnd, ChoosePageEntryField, &error, kODFalse);
         if ((PageNumber<1) || (PageNumber>MaxPages)) {
            MessageBox(hwnd, (PSZ) MRI(GoToPageErrorMsg), (PSZ) NULL,
               MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            SetDlgItemInt(hwnd, ChoosePageEntryField, 1, kODFalse);
         } else {
            EndDialog(hwnd, PageNumber);
         } /* endif */
         break;
      case IDCANCEL:
         EndDialog(hwnd, kODNULL);
         break;
      } /* endswitch */
      break;
   default:
      return(kODFalse);
   } /* endswitch */
   return(kODTrue);
}


LRESULT CALLBACK GetTextDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   static char *entryFieldText;

   switch (msg) {
   case WM_INITDIALOG:
      switch (lParam) {
      case HeaderDlgValue:
         SetWindowText(hwnd, MRI(HeaderDlgTitle));
         break;
      case FooterDlgValue:
         SetWindowText(hwnd, MRI(FooterDlgTitle));
         break;
      } /* endswitch */

      entryFieldText = (char *) malloc(256*sizeof(char));
      break;

   case WM_COMMAND:
      switch (LOWORD(wParam)) {
      case IDOK:
         GetDlgItemText(hwnd, GetTextEntryField, entryFieldText, 255);
         EndDialog(hwnd, (int) entryFieldText);
         break;
      case IDCANCEL:
         free(entryFieldText);
         EndDialog(hwnd, kODNULL);
         break;
      } /* endswitch */
      break;
   default:
      return(kODFalse);
   } /* endswitch */
   return(kODTrue);
}
#endif //_PLATFORM_WIN32_


#ifdef _PLATFORM_OS2_
MRESULT EXPENTRY ChoosePageDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   MRESULT ReturnValue = FALSE;
   HWND hwndParent, hwndTitle;
   static MPARAM MaxPages;
   static MPARAM FirstPage;
   LONG PageNumber;

   switch (msg) {
   case WM_INITDLG:
      hwndParent = WinQueryWindow(hwnd, QW_PARENT);
      hwndTitle = WinWindowFromID(hwndParent, ChoosePageDlgValue);

      switch (SHORT1FROMMP(mp2)) {
      case GoToPageDlgValue:
         WinSetWindowText(hwndTitle, MRI(GoToPageDlgTitle));
         break;
      case InsertPageDlgValue:
         WinSetWindowText(hwndTitle, MRI(InsertPageDlgTitle));
         break;
      case RemovePageDlgValue:
         WinSetWindowText(hwndTitle, MRI(RemovePageDlgTitle));
         break;
      } /* endswitch */

      FirstPage = MPFROMLONG(1);
      MaxPages = MPFROMSHORT(SHORT2FROMMP(mp2));
      WinSendDlgItemMsg(hwnd, ChoosePageSpinButton, SPBM_SETLIMITS,
         MaxPages, FirstPage);
      WinSendDlgItemMsg(hwnd, ChoosePageSpinButton, SPBM_SETCURRENTVALUE,
         FirstPage, NULL);

      CenterWindow(hwnd);
      break;
   case WM_COMMAND:
      switch (SHORT1FROMMP(mp1)) {
      case DID_OK:
         WinSendDlgItemMsg(hwnd, ChoosePageSpinButton, SPBM_QUERYVALUE,
            &PageNumber, NULL);
         if ((PageNumber<1) || (PageNumber>LONGFROMMP(MaxPages))) {
            WinMessageBox(HWND_DESKTOP, hwnd, MRI(GoToPageErrorMsg),
               (PSZ)NULL, 0, MB_ENTER | MB_ERROR);
            WinSendDlgItemMsg(hwnd, ChoosePageSpinButton, SPBM_SETCURRENTVALUE,
               FirstPage, NULL);
         } else {
            WinDismissDlg(hwnd, PageNumber);
         } /* endif */
         break;
      case DID_CANCEL:
         WinDismissDlg(hwnd, kODNULL);
         break;
      } /* endswitch */
      break;
   default:
      return(WinDefDlgProc(hwnd, msg, mp1, mp2));
     break;
   } /* endswitch */
   return(ReturnValue);
}


MRESULT EXPENTRY GetTextDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   MRESULT ReturnValue = FALSE;
   HWND hwndParent, hwndTitle;
   static char *entryFieldText;

   switch (msg) {
   case WM_INITDLG:
      hwndParent = WinQueryWindow(hwnd, QW_PARENT);
      hwndTitle = WinWindowFromID(hwndParent, GetTextDlgValue);

      switch (LONGFROMMP(mp2)) {
      case HeaderDlgValue:
         WinSetWindowText(hwndTitle, MRI(HeaderDlgTitle));
         break;
      case FooterDlgValue:
         WinSetWindowText(hwndTitle, MRI(FooterDlgTitle));
         break;
      } /* endswitch */

      entryFieldText = (char *) malloc(256*sizeof(char));
      WinSendDlgItemMsg(hwnd, GetTextEntryField, EM_SETTEXTLIMIT,
         MPFROMLONG(255), (MPARAM) 0);

      CenterWindow(hwnd);
      break;
   case WM_COMMAND:
      switch (SHORT1FROMMP(mp1)) {
      case DID_OK:
         WinQueryDlgItemText(hwnd, GetTextEntryField, 255, entryFieldText);
         WinDismissDlg(hwnd, (ULONG) entryFieldText);
         break;
      case DID_CANCEL:
         free(entryFieldText);
         WinDismissDlg(hwnd, kODNULL);
         break;
      } /* endswitch */
      break;
   default:
      return(WinDefDlgProc(hwnd, msg, mp1, mp2));
     break;
   } /* endswitch */
   return(ReturnValue);
}
#endif //_PLATFORM_OS2_


/********************************************************************
  PageLayout Methods
********************************************************************/

SOM_Scope void  SOMLINK PageLayoutUpdateContentExtent(PageLayout  *somSelf,
                                                      Environment *ev,
                                                      ODFrame     *myFrame)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutUpdateContentExtent");

    ODPoint extent;
    extent.x = MAKEFIXED(_fTotalPageWidth, 0);
    extent.y = MAKEFIXED(_fTotalPageHeight * _fNumberOfPages, 0);
    myFrame->ChangeContentExtent(ev, &extent);
}

SOM_Scope ODExtension*  SOMLINK PageLayoutCreatePrintExtension(PageLayout *somSelf,
                                                                Environment *ev)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutCreatePrintExtension");

    _fPrintExt = new PageLayoutPrintExtension;

    return _fPrintExt;
}


SOM_Scope ODExtension*  SOMLINK PageLayoutEnablePrinting(PageLayout *somSelf,
                                                          Environment *ev,
                                                         ODBoolean enable,
                                                         char *QueueName)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutEnablePrinting");

    if (_fPrintExt!=kODNULL) {
       if (_fPrintExt->GetBase(ev)==kODNULL) { /* hasn't been initialized */
          _fPrintExt->InitializeForPageLayout(ev, _fPartWrapper, QueueName, _fLeftPageOffset,

#ifdef _PLATFORM_OS2_
             _fBottomPageOffset,
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
             _fTopPageOffset,
#endif //_PLATFORM_WIN32_

             _fTotalPageWidth, _fTotalPageHeight, _fNumberOfPages);
       } /* endif */
    } /* endif */

    PageLayout_parent_BaseContainer_EnablePrinting(somSelf, ev,
       enable, QueueName);

    return(_fPrintExt);
}


SOM_Scope ODBoolean  SOMLINK PageLayoutSetupPrinting(PageLayout *somSelf,
                                                      Environment *ev,
                                                     ODFrame* frame,
                                                     ODEventData* event)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutSetupPrinting");

    ODBoolean paperSizeChanged = PageLayout_parent_BaseContainer_SetupPrinting(
                                    somSelf, ev, frame, event);

    if (paperSizeChanged) {
       _ChangePaperSize(ev, frame);
    } /* endif */

    return(paperSizeChanged);
}


SOM_Scope ODBoolean  SOMLINK PageLayoutHandleScrollEvent(PageLayout *somSelf,
                                                          Environment *ev,
                                                         ODFrame* frame,
                                                         ODEventData* event)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutHandleScrollEvent");

    ODBoolean handled = PageLayout_parent_BaseContainer_HandleScrollEvent(
                           somSelf, ev, frame, event);

    if (handled) {
       _DetermineVisiblePages(ev, frame);
    } /* endif */

    return(handled);
}


SOM_Scope void  SOMLINK PageLayoutDetermineVisiblePages(PageLayout *somSelf,
                                                         Environment *ev,
                                                        ODFrame *frame)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutDetermineVisiblePages");

    if (_fScrollExt!=kODNULL) {
       short OldFirstVisiblePage = _fFirstVisiblePage;
       short OldLastVisiblePage = _fLastVisiblePage;

       long CurrentVertScrollPos = _fScrollExt->GetVerticalScrollPosition(ev);
       long VisibleHeight = _fScrollExt->GetVisibleHeight(ev);

#ifdef _PLATFORM_WIN32_
       _fFirstVisiblePage = CurrentVertScrollPos/_fTotalPageHeight;

       _fLastVisiblePage =
          (CurrentVertScrollPos+VisibleHeight-1)/_fTotalPageHeight;
#endif

#ifdef _PLATFORM_OS2_
       _fFirstVisiblePage = _fNumberOfPages-1-
          (CurrentVertScrollPos+VisibleHeight)/_fTotalPageHeight;

       _fLastVisiblePage = _fNumberOfPages-1-
          CurrentVertScrollPos/_fTotalPageHeight;
#endif

/* Just in case we came up with numbers that are out of bounds */
       if (_fFirstVisiblePage<0) {
          _fFirstVisiblePage = 0;
       } /* endif */

       if (_fLastVisiblePage>_fNumberOfPages-1) {
          _fLastVisiblePage = _fNumberOfPages-1;
       } /* endif */

#ifdef SMART_DRAWING
       if ((_fFirstVisiblePage!=OldFirstVisiblePage) ||
           (_fLastVisiblePage!=OldLastVisiblePage)) { /* Recalculate cached shapes */
          _fVisiblePagesShape->Reset(ev);

          RECTL pageRect;
          pageRect.xLeft = _fLeftPageOffset;
          pageRect.xRight = _fLeftPageOffset+_fPageWidth;

#ifdef _PLATFORM_OS2_
          pageRect.yBottom = _fBottomPageOffset;
          pageRect.yTop = _fBottomPageOffset+_fPageHeight;
#endif

#ifdef _PLATFORM_WIN32_
          pageRect.yTop = _fTopPageOffset;
          pageRect.yBottom = _fTopPageOffset+_fPageHeight;
#endif

          ODRect pageODRect(pageRect);

          ODShape *pageShape = _fVisiblePagesShape->NewShape(ev);
          pageShape->SetRectangle(ev, &pageODRect);
          ODPoint offset(0, MAKEFIXED(_fFirstVisiblePage*_fTotalPageHeight, 0));
          ODTransform *offsetXform = frame->CreateTransform(ev);

          for (int page=_fFirstVisiblePage; page<=_fLastVisiblePage; page++) {
             offsetXform->SetOffset(ev, &offset);
             ODShape *offsetPageShape = pageShape->Copy(ev);
             offsetPageShape->Transform(ev, offsetXform);
             _fVisiblePagesShape->Union(ev, offsetPageShape);
             offsetPageShape->Release(ev);
             offset.y += MAKEFIXED(_fTotalPageHeight, 0);
          } /* endfor */
          offsetXform->Release(ev);
          pageShape->Release(ev);
       } /* endif */

       ODShape *frameShape = frame->AcquireFrameShape(ev, kNoBias);
       _fBackgroundShape->CopyFrom(ev, frameShape);
       ODReleaseObject(ev, frameShape);

       ODTransform *internalXform = frame->AcquireInternalTransform(ev, kNoBias);
       _fBackgroundShape->InverseTransform(ev, internalXform);
       ODReleaseObject(ev, internalXform);

       _fBackgroundShape->Subtract(ev, _fVisiblePagesShape);
#endif

// jwa: We ought to create facets for parts on pages that just came into view
//     if ((_fFirstVisiblePage<OldFirstVisiblePage) ||
//         (_fLastVisiblePage>OldLastVisiblePage)),
//      and destroy facets for parts on pages that just went out of view
//     if ((_fFirstVisiblePage>OldFirstVisiblePage) ||
//         (_fLastVisiblePage<OldLastVisiblePage)).

    } /* endif */
}


SOM_Scope ODBoolean  SOMLINK PageLayoutMaxPagesReached(PageLayout *somSelf,
                                                        Environment *ev)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutMaxPagesReached");

    ODBoolean ReturnValue = kODFalse;

    long height = _fTotalPageHeight*(_fNumberOfPages+1);

#ifdef _PLATFORM_OS2_
/* Due to 16-bit heritage of GPI (even though the GPI is now 32-bit, some of */
/* its functions still have 16-bit limitations - the transform code is such  */
/* an example), we can't let the numbers pass 32768 at any point in a series */
/* of transformations, even if later transformations bring them back down    */
/* within range.  The scaling factor on the root facet can end up pushing us */
/* over this limit, so we really can only go up to 32768/_fYScaleFactor on   */
/* the OS/2 platform.  NT doesn't have this problem.  For 8.5x11 paper, this */
/* means that we have a 22 page limit on OS/2, and a 37 page limit on NT.    */
/* Note - I tried scaling my internal transform (and scaling back during     */
/* drawing) to get around this limitation, and although makes my drawing     */
/* work OK beyond 22 pages, I then end up running into problems with the     */
/* external transforms on my embedded parts (since transforms use fixed      */
/* point representation, they live in a world with 16-bit limitations also), */
/* which leads to the kODErrTransformErr exception when parts are on pages   */
/* greater than 22.                                                          */
    if (_fYScaleFactor>1.0) {
       height *= _fYScaleFactor;
    } /* endif */
#endif

    if (height>32768) {
       ReturnValue = kODTrue;
    } /* endif */

    return ReturnValue;
}


SOM_Scope void  SOMLINK PageLayoutInsertPage(PageLayout *somSelf,
                                              Environment *ev,
                                             ODFrame* frame,
                                             short pageNumber)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutInsertPage");

    _fNumberOfPages++;
    if (_fPrintExt!=kODNULL) {
       _fPrintExt->SetNumberOfPages(ev, _fNumberOfPages);
    } /* endif */

#ifdef _PLATFORM_OS2_
    _MoveEmbedsByOnePage(ev, _fNumberOfPages-pageNumber-1, UP);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    if (pageNumber+1!=_fNumberOfPages) {
       _MoveEmbedsByOnePage(ev, pageNumber, UP);
    } /* endif */
#endif //_PLATFORM_WIN32_

    _CreateSelectionBorderShapes(ev, kODNULL);

    if (_fScrollExt!=kODNULL) {
       _UpdateContentExtent(ev, frame);
       _fScrollExt->SetScrollableDimensions(ev, frame, _fTotalPageWidth,
          _fTotalPageHeight*_fNumberOfPages);
       _DetermineVisiblePages(ev, frame);
    } /* endif */
}


SOM_Scope void  SOMLINK PageLayoutRemovePage(PageLayout *somSelf,
                                              Environment *ev,
                                             ODFrame* frame,
                                             short pageNumber)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutRemovePage");

    _fNumberOfPages--;
    if (_fPrintExt!=kODNULL) {
       _fPrintExt->SetNumberOfPages(ev, _fNumberOfPages);
    } /* endif */

/* Remove any parts that were on the page being removed */
    ALinkedList *itr = _GetEmbeddedObjects(ev);
    if (itr!=kODNULL) {
       ALink *item = itr->First(ev);
       if (item!=kODNULL) {
          ContentObject *cObj = (ContentObject *) item->Content(ev);
          while (cObj!=kODNULL) {
             short embedPageNumber = _DeterminePageNumberOfEmbed(ev, cObj);
#ifdef _PLATFORM_OS2_
             embedPageNumber = _fNumberOfPages-embedPageNumber;
#endif //_PLATFORM_OS2_
             if (embedPageNumber==pageNumber-1) {
                itr->Remove(ev, cObj);
                item = itr->First(ev); /* start over - old itr invalid */

                ALinkedList *selItr = _GetSelectedObjects(ev);
                if (selItr && selItr->Contains(ev, cObj)) {
                   selItr->Remove(ev, cObj);
                } /* endif */

                cObj->DeleteContents(ev, OBJECT_DELETED);
                delete cObj;
             } /* endif */

             item = item->Next(ev);
             if (item!=kODNULL) {
                cObj = (ContentObject *) item->Content(ev);
             } else {
                cObj = kODNULL;
             } /* endif */
          } /* endwhile */
       } /* endif */
    } /* endif */

#ifdef _PLATFORM_OS2_
    _MoveEmbedsByOnePage(ev, _fNumberOfPages-pageNumber+1, DOWN);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    if (pageNumber-1!=_fNumberOfPages) {
       _MoveEmbedsByOnePage(ev, pageNumber, DOWN);
    } /* endif */
#endif //_PLATFORM_WIN32_

    _CreateSelectionBorderShapes(ev, kODNULL);

    if (_fScrollExt!=kODNULL) {
       _UpdateContentExtent(ev, frame);
       _fScrollExt->SetScrollableDimensions(ev, frame, _fTotalPageWidth,
          _fTotalPageHeight*_fNumberOfPages);
       _DetermineVisiblePages(ev, frame);
    } /* endif */
}


SOM_Scope void  SOMLINK PageLayoutChangePaperSize(PageLayout *somSelf,
                                                   Environment *ev,
                                                  ODFrame* frame)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutChangePaperSize");

    if (_fPrintExt!=kODNULL) {
       _fPageWidth = _fPrintExt->GetCurrentPrinterPageWidth(ev);
       _fPageHeight = _fPrintExt->GetCurrentPrinterPageHeight(ev);

       _fTotalPageWidth = _fLeftPageOffset+_fPageWidth+_fRightPageOffset;
       _fTotalPageHeight = _fBottomPageOffset+_fPageHeight+_fTopPageOffset;

       _ChangeNotification(ev, BCC_EMBEDSHAPECHANGED, frame, kODNULL,
          kODTrue, kODNULL); /* keeps embeds within margins */

       if (_fPrintExt!=kODNULL) {
          _fPrintExt->SetPageDimensions(ev, _fTotalPageWidth, _fTotalPageHeight);
       } /* endif */

       if (_fScrollExt!=kODNULL) {
          _UpdateContentExtent(ev, frame);
          _fScrollExt->SetScrollableDimensions(ev, frame, _fTotalPageWidth,
             _fTotalPageHeight*_fNumberOfPages);
       } /* endif */
    } /* endif */
}


SOM_Scope short  SOMLINK PageLayoutDeterminePageNumberOfEmbed(PageLayout *somSelf,
                                                               Environment *ev,
                                                              ContentObject* object)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutDeterminePageNumberOfEmbed");

    short pageNumber = 0;

    if (object!=kODNULL) {
       ODTransform *xform = object->_get_extTransform(ev);
       if (xform!=kODNULL) {
          ODPoint offset;
          xform->GetOffset(ev, &offset);
          pageNumber = (offset.y/0x10000)/_fTotalPageHeight;
       } /* endif */
    } /* endif */

    return pageNumber;
}


SOM_Scope ODBoolean  SOMLINK PageLayoutKeepEmbedWithinMargins(PageLayout *somSelf,
                                                               Environment *ev,
                                                              ContentObject* object)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutKeepEmbedWithinMargins");

    ODBoolean adjusted = kODFalse;

    if (object!=kODNULL) {
       short pageNumber = _DeterminePageNumberOfEmbed(ev, object);
       if (pageNumber>_fNumberOfPages-1) {
          pageNumber = _fNumberOfPages-1;
       } /* endif */

       ODRect rect = object->_get_boundingRect(ev);
       ODTransform *xform = object->_get_extTransform(ev);

       if (xform==kODNULL) return kODFalse;

       long width = (rect.right-rect.left)/0x10000;

#ifdef _PLATFORM_OS2_
       long height = (rect.top-rect.bottom)/0x10000;
#endif

#ifdef _PLATFORM_WIN32_
       long height = (rect.bottom-rect.top)/0x10000;
#endif

       ODPoint offset;
       xform->GetOffset(ev, &offset);

       long Xlocation = offset.x/0x10000;
       long Ylocation = offset.y/0x10000;

       ODBoolean NeedsOffseting = kODFalse;
       ODBoolean NeedsResizing = kODFalse;

       long MinXPos = _fLeftPageOffset+_fLeftMargin+1;
       if (Xlocation<MinXPos) {
          NeedsOffseting = kODTrue;
          Xlocation += MinXPos-Xlocation;
       } /* endif */

#ifdef _PLATFORM_OS2_
       long MinYPos = _fBottomPageOffset+_fBottomMargin
#endif
#ifdef _PLATFORM_WIN32_
       long MinYPos = _fTopPageOffset+_fTopMargin
#endif
          +pageNumber*_fTotalPageHeight+1;

       if (Ylocation<MinYPos) {
          NeedsOffseting = kODTrue;
          Ylocation += MinYPos-Ylocation;
       } /* endif */

       long MaxWidth = _fPageWidth-_fLeftMargin-_fRightMargin-1;
       long MaxHeight = _fPageHeight-_fTopMargin-_fBottomMargin-1;

       long MaxXPos = _fLeftPageOffset+_fPageWidth-_fRightMargin;
       if (Xlocation+width>MaxXPos) {
          NeedsOffseting = kODTrue;
          if (width>MaxWidth) {
             Xlocation = MinXPos;
             NeedsResizing = kODTrue;
             width = MaxWidth;
          } else {
             Xlocation -= Xlocation+width-MaxXPos;
          } /* endif */
       } /* endif */

#ifdef _PLATFORM_OS2_
       long MaxYPos = _fBottomPageOffset+_fPageHeight-_fTopMargin
#endif
#ifdef _PLATFORM_WIN32_
       long MaxYPos = _fTopPageOffset+_fPageHeight-_fBottomMargin
#endif
          +pageNumber*_fTotalPageHeight;

       if (Ylocation+height>MaxYPos) {
          NeedsOffseting = kODTrue;
          if (height>MaxHeight) {
             Ylocation = MinYPos;
             NeedsResizing = kODTrue;
             height = MaxHeight;
          } else {
             Ylocation -= Ylocation+height-MaxYPos;
          } /* endif */
       } /* endif */

       if (NeedsOffseting) {
          ODPoint delta;
          delta.x = Xlocation*0x10000-offset.x;
          delta.y = Ylocation*0x10000-offset.y;

          object->MoveBy(ev, &delta);

          adjusted = kODTrue;
       } /* endif */

       if (NeedsResizing) {
#ifdef _PLATFORM_OS2_
          ODULong resizeFlags = COBJ_RESIZE_RIGHT | COBJ_RESIZE_TOP;
#endif
#ifdef _PLATFORM_WIN32_
          ODULong resizeFlags = COBJ_RESIZE_RIGHT | COBJ_RESIZE_BOTTOM;
#endif

          ODPoint newExtent;
          newExtent.x = (Xlocation+width)*0x10000;
          newExtent.y = (Ylocation+height)*0x10000;

          object->Resize(ev, &newExtent, resizeFlags);

          adjusted = kODTrue;
       } /* endif */
    } /* endif */

    return adjusted;
}


SOM_Scope void  SOMLINK PageLayoutSnapToGrid(PageLayout *somSelf,
                                              Environment *ev,
                                             ODFrame *frame)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutSnapToGrid");

    ALinkedList *itr = _GetSelectedObjects(ev);
    if (itr!=kODNULL) {
       ALink *item = itr->First(ev);
       if (item!=kODNULL) {
          ContentObject *cObj = (ContentObject *) item->Content(ev);
          while (cObj!=kODNULL) {
             short pageNumber = _DeterminePageNumberOfEmbed(ev, cObj);

             ODRect rect = cObj->_get_boundingRect(ev);

             long width = (rect.right-rect.left)/0x10000;

#ifdef _PLATFORM_OS2_
             long height = (rect.top-rect.bottom)/0x10000;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
             long height = (rect.bottom-rect.top)/0x10000;
#endif //_PLATFORM_WIN32_

             ODTransform *xform = cObj->_get_extTransform(ev);
             if (xform==kODNULL) break;

             ODPoint offset;
             xform->GetOffset(ev, &offset);

             long Xlocation = offset.x/0x10000;
             long Ylocation = offset.y/0x10000-pageNumber*_fTotalPageHeight;

             long leftGridLine = (Xlocation-_fLeftPageOffset-_fLeftMargin+
                _fGridSpacing/2)/_fGridSpacing;
             long rightGridLine = leftGridLine+(width+
                _fGridSpacing/2)/_fGridSpacing;

#ifdef _PLATFORM_OS2_
             long bottomGridLine = (Ylocation-_fBottomPageOffset-_fBottomMargin+
                _fGridSpacing/2)/_fGridSpacing;
             long topGridLine = bottomGridLine+(height+
                _fGridSpacing/2)/_fGridSpacing;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
             long topGridLine = (Ylocation-_fTopPageOffset-_fTopMargin+
                _fGridSpacing/2)/_fGridSpacing;
             long bottomGridLine = topGridLine+(height+
                _fGridSpacing/2)/_fGridSpacing;
#endif //_PLATFORM_WIN32_

/* Begin repositioning code */
             long newXPos = _fLeftPageOffset+_fLeftMargin+
                leftGridLine*_fGridSpacing+1;

#ifdef _PLATFORM_OS2_
             long newYPos = _fBottomPageOffset+_fBottomMargin+
                bottomGridLine*_fGridSpacing+pageNumber*_fTotalPageHeight+1;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
             long newYPos = _fTopPageOffset+_fTopMargin+
                topGridLine*_fGridSpacing+pageNumber*_fTotalPageHeight+1;
#endif //_PLATFORM_WIN32_

             ODPoint delta;
             delta.x = newXPos*0x10000-offset.x;
             delta.y = newYPos*0x10000-offset.y;

             cObj->MoveBy(ev, &delta);

/* Begin resizing code */
             long newWidth = (rightGridLine-leftGridLine)*_fGridSpacing-1;

#ifdef _PLATFORM_OS2_
             long newHeight = (topGridLine-bottomGridLine)*_fGridSpacing-1;
#endif
#ifdef _PLATFORM_WIN32_
             long newHeight = (bottomGridLine-topGridLine)*_fGridSpacing-1;
#endif

#ifdef _PLATFORM_OS2_
             ODULong resizeFlags = COBJ_RESIZE_RIGHT | COBJ_RESIZE_TOP;
#endif
#ifdef _PLATFORM_WIN32_
             ODULong resizeFlags = COBJ_RESIZE_RIGHT | COBJ_RESIZE_BOTTOM;
#endif

             ODPoint newExtent;
             newExtent.x = (newXPos+newWidth)*0x10000;
             newExtent.y = (newYPos+newHeight)*0x10000;

             cObj->Resize(ev, &newExtent, resizeFlags);
/* End resizing code */

             item = item->Next(ev);
             if (item!=kODNULL) {
                cObj = (ContentObject *) item->Content(ev);
             } else {
                cObj = kODNULL;
             } /* endif */
          } /* endwhile */
       } /* endif */
    } /* endif */

    _CreateSelectionBorderShapes(ev, kODNULL);
    frame->Invalidate(ev, kODNULL, kNoBias);
}


SOM_Scope void  SOMLINK PageLayoutFillEntirePage(PageLayout *somSelf,
                                              Environment *ev,
                                             ODFrame *frame)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutFillEntirePage");

    ALinkedList *itr = _GetSelectedObjects(ev);
    if (itr!=kODNULL) {
       ALink *item = itr->First(ev);
       if (item!=kODNULL) {
          ContentObject *cObj = (ContentObject *) item->Content(ev);
          while (cObj!=kODNULL) {
             short pageNumber = _DeterminePageNumberOfEmbed(ev, cObj);

             ODTransform *xform = cObj->_get_extTransform(ev);
             if (xform==kODNULL) break;

             ODPoint offset;
             xform->GetOffset(ev, &offset);

/* Begin repositioning code */
             long XPos = _fLeftPageOffset+_fLeftMargin+1;

#ifdef _PLATFORM_OS2_
             long YPos = _fBottomPageOffset+_fBottomMargin
#endif
#ifdef _PLATFORM_WIN32_
             long YPos = _fTopPageOffset+_fTopMargin
#endif
                +pageNumber*_fTotalPageHeight+1;

             ODPoint delta;
             delta.x = XPos*0x10000-offset.x;
             delta.y = YPos*0x10000-offset.y;

             cObj->MoveBy(ev, &delta);

/* Begin resizing code */
             long width = _fPageWidth-_fLeftMargin-_fRightMargin-1;
             long height = _fPageHeight-_fTopMargin-_fBottomMargin-1;

#ifdef _PLATFORM_OS2_
             ODULong resizeFlags = COBJ_RESIZE_RIGHT | COBJ_RESIZE_TOP;
#endif
#ifdef _PLATFORM_WIN32_
             ODULong resizeFlags = COBJ_RESIZE_RIGHT | COBJ_RESIZE_BOTTOM;
#endif

             ODPoint newExtent;
             newExtent.x = (XPos+width)*0x10000;
             newExtent.y = (YPos+height)*0x10000;

             cObj->Resize(ev, &newExtent, resizeFlags);
/* End resizing code */

             item = item->Next(ev);
             if (item!=kODNULL) {
                cObj = (ContentObject *) item->Content(ev);
             } else {
                cObj = kODNULL;
             } /* endif */
          } /* endwhile */
       } /* endif */
    } /* endif */

    _CreateSelectionBorderShapes(ev, kODNULL);
    frame->Invalidate(ev, kODNULL, kNoBias);
}


SOM_Scope void  SOMLINK PageLayoutMoveEmbedsByOnePage(PageLayout *somSelf,
                                                       Environment *ev,
                                                      short afterPage,
                                                      short direction)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutMoveEmbedByOnePage");

    ALinkedList *itr = _GetEmbeddedObjects(ev);
    if (itr!=kODNULL) {
       ALink *item = itr->First(ev);
       if (item!=kODNULL) {
          ODPoint pageHeight(0, _fTotalPageHeight*direction*0x10000);

          ContentObject *cObj = (ContentObject *) item->Content(ev);
          while (cObj!=kODNULL) {
             short pageNumber = _DeterminePageNumberOfEmbed(ev, cObj);
             if (pageNumber>=afterPage) {
                cObj->MoveBy(ev, &pageHeight);
             } /* endif */

             item = item->Next(ev);
             if (item!=kODNULL) {
                cObj = (ContentObject *) item->Content(ev);
             } else {
                cObj = kODNULL;
             } /* endif */
          } /* endwhile */
       } /* endif */
    } /* endif */
}


SOM_Scope void  SOMLINK PageLayoutResizeDocShell(PageLayout *somSelf,
                                                  Environment *ev,
                                                 ODFacet* facet)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutResizeDocShell");

    ODPoint frameCorner(MAKEFIXED(_fTotalPageWidth, 0),
                        MAKEFIXED(_fTotalPageHeight, 0));

    ODTransform *frameXform = facet->AcquireFrameTransform(ev, kNoBias);
    frameXform->TransformPoint(ev, &frameCorner);
    frameXform->Release(ev);

//  LONG width = frameCorner.x/0x10000;
//  LONG height = frameCorner.y/0x10000;
// jwa: above two lines could lead to rounding errors
    LONG width = (frameCorner.x+0x10000/2)/0x10000;
    LONG height = (frameCorner.y+0x10000/2)/0x10000;

    ODWindow *window = facet->GetWindow(ev);

    ODPlatformWindow hwnd = window->GetPlatformWindow(ev);

#ifdef _PLATFORM_OS2_
    RECTL rect = {0, 0, width, height};

    WinCalcFrameRect(hwnd, &rect, kODFalse);

    width = rect.xRight-rect.xLeft;
    height = rect.yTop-rect.yBottom;

    LONG ScreenWidth = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
    LONG ScreenHeight = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

    LONG xOffset = (ScreenWidth-width)/2;
    LONG yOffset = (ScreenHeight-height)/2;

    WinSetWindowPos(hwnd, NULL, xOffset>0 ? xOffset : 0,
       yOffset>0 ? yOffset : 0, width<ScreenWidth ? width : ScreenWidth,
       height<ScreenHeight ? height : ScreenHeight, SWP_SIZE | SWP_MOVE);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    Rect rect = {0, 0, width, height};

    AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), kODTrue);

    width = rect.right-rect.left;
    height = rect.bottom-rect.top;

//  LONG ScreenWidth = GetScreenWidth();
//  LONG ScreenHeight = GetScreenHeight();

    HDC screenDC = GetDC(hwnd);
    LONG ScreenWidth = GetDeviceCaps(screenDC, HORZRES);
    LONG ScreenHeight = GetDeviceCaps(screenDC, VERTRES);
    ReleaseDC(hwnd, screenDC);

    LONG xOffset = (ScreenWidth-width)/2;
    LONG yOffset = (ScreenHeight-height)/2;

    SetWindowPos(hwnd, NULL, xOffset>0 ? xOffset : 0,
       yOffset>0 ? yOffset : 0, width<ScreenWidth ? width : ScreenWidth,
       height<ScreenHeight ? height : ScreenHeight,
       SWP_NOZORDER | SWP_NOACTIVATE);
#endif //_PLATFORM_WIN32_
}


SOM_Scope void  SOMLINK PageLayoutCreateMenuBar(PageLayout *somSelf,
                                                 Environment *ev)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutCreateMenuBar");

    _fMenuBar = _GetMenuBar(ev);
    if (_fMenuBar!=kODNULL) {
       _fMenuBar->RemoveMenu(ev, kODOptionsMenuID);

       ODPlatformMenuItem *item = new ODPlatformMenuItem;

       // clear the memory
       memset (item, 0, sizeof(ODPlatformMenuItem));

       // add a menu separator line to EDIT menu
       item->id=MenuSeparator3;
       #if defined(_PLATFORM_WIN32_)
           item->afAttribute=MF_SEPARATOR;
       #elif defined(_PLATFORM_OS2_)
           item->afAttribute=CA_TITLESEPARATOR;
       #endif
       _fMenuBar->AddMenuItemLast(ev, IDMS_EDIT, item->id, item);

       item->afAttribute=0;           // use default attributes
       item->id=MenuFillPage;
       _fMenuBar->AddMenuItemLast(ev, IDMS_EDIT, item->id, item);
       _fMenuBar->SetMenuItemText(ev, IDMS_EDIT, item->id,
          MRI(FillPageString));

       item->id=MenuSnapToGrid;
       _fMenuBar->AddMenuItemLast(ev, IDMS_EDIT, item->id, item);
       _fMenuBar->SetMenuItemText(ev, IDMS_EDIT, item->id,
          MRI(SnapToGridString));

       // add a menu separator line to VIEW menu
       item->id=MenuSeparator4;
       #if defined(_PLATFORM_WIN32_)
           item->afAttribute=MF_SEPARATOR;
       #elif defined(_PLATFORM_OS2_)
           item->afAttribute=CA_TITLESEPARATOR;
       #endif
       _fMenuBar->AddMenuItemLast(ev, IDMS_VIEW, item->id, item);

       item->afAttribute=0;           // use default attributes
       item->id=MenuShowRulers;
       _fMenuBar->AddMenuItemLast(ev, IDMS_VIEW, item->id, item);
       _fMenuBar->SetMenuItemText(ev, IDMS_VIEW, item->id,
          MRI(ShowRulersString));

       item->id=MenuShowMargins;
       _fMenuBar->AddMenuItemLast(ev, IDMS_VIEW, item->id, item);
       _fMenuBar->SetMenuItemText(ev, IDMS_VIEW, item->id,
          MRI(ShowMarginsString));

       item->id=MenuShowGrid;
       _fMenuBar->AddMenuItemLast(ev, IDMS_VIEW, item->id, item);
       _fMenuBar->SetMenuItemText(ev, IDMS_VIEW, item->id,
          MRI(ShowGridString));

       // add another menu separator line to VIEW menu
       item->id=MenuSeparator5;
       #if defined(_PLATFORM_WIN32_)
           item->afAttribute=MF_SEPARATOR;
       #elif defined(_PLATFORM_OS2_)
           item->afAttribute=CA_TITLESEPARATOR;
       #endif
       _fMenuBar->AddMenuItemLast(ev, IDMS_VIEW, item->id, item);

       item->afAttribute=0;           // use default attributes
       item->id=MenuRefresh;
       _fMenuBar->AddMenuItemLast(ev, IDMS_VIEW, item->id, item);
       _fMenuBar->SetMenuItemText(ev, IDMS_VIEW, item->id,
          MRI(RefreshString));

       ODPlatformMenu PageMenu;

#ifdef _PLATFORM_OS2_
       PageMenu = WinLoadMenu(HWND_OBJECT, _fResources, PageMenuID);
#endif

#ifdef _PLATFORM_WIN32_
       PageMenu = LoadMenu(_fResources, MAKEINTRESOURCE(PageMenuID));
#endif

       if (PageMenu!=kODNULL) {
          _fMenuBar->AddMenuLast(ev, PageMenuID, PageMenu, _fPartWrapper);
//        _fMenuBar->SetMenuItemText(ev, PageMenuID, kODNULL,
          _fMenuBar->SetMenuItemText(ev, ID_BASEMENUBAR, PageMenuID,
             MRI(PageMenuString));
       } else {
#ifdef _PLATFORM_OS2_
          DosBeep(250,500);
#endif

#ifdef _PLATFORM_WIN32_
          Beep(250,500);
#endif
       } /* endif */

       ODPlatformMenu ColorMenu;

#ifdef _PLATFORM_OS2_
       ColorMenu = WinLoadMenu(HWND_OBJECT, _fResources, ColorMenuID);
#endif

#ifdef _PLATFORM_WIN32_
       ColorMenu = LoadMenu(_fResources, MAKEINTRESOURCE(ColorMenuID));
#endif

       if (ColorMenu!=kODNULL) {
          _fMenuBar->AddMenuLast(ev, ColorMenuID, ColorMenu, _fPartWrapper);
//        _fMenuBar->SetMenuItemText(ev, ColorMenuID, kODNULL,
          _fMenuBar->SetMenuItemText(ev, ID_BASEMENUBAR, ColorMenuID,
             MRI(ColorMenuString));
       } else {
#ifdef _PLATFORM_OS2_
          DosBeep(250,500);
#endif

#ifdef _PLATFORM_WIN32_
          Beep(250,500);
#endif
       } /* endif */
    } /* endif */
}


SOM_Scope void  SOMLINK PageLayoutDrawPage(PageLayout *somSelf,
                                            Environment *ev,
                                           HDRAW DrawingSurface, // HPS on OS/2, HDC on Win32
                                           short pageNumber,
                                           ODBoolean isPrinting,
                                           ODBoolean DrawAdornments)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutDrawPage");

#ifdef _PLATFORM_OS2_
    POINTL ptl;
    LONG PageYPos = _fBottomPageOffset+pageNumber*_fTotalPageHeight;

#ifndef SMART_DRAWING
    if (!_fIsTransparent &&
        (DrawAdornments || (isPrinting && _fPrintPageColor))) {

       ptl.x = _fLeftPageOffset;
       ptl.y = PageYPos;
       GpiMove(DrawingSurface, &ptl);

       ptl.x += _fPageWidth;
       ptl.y += _fPageHeight;

       GpiSetColor(DrawingSurface, _fPageColor);
       GpiBox(DrawingSurface, DRO_FILL, &ptl, 0, 0);
    } /* endif */
#endif //SMART_DRAWING

    if (_fShowGrid && DrawAdornments) {
       GpiSetLineType(DrawingSurface, _fGridLine);
       GpiSetColor(DrawingSurface, _fGridColor);

       LONG MaxGridWidth = _fPageWidth-_fLeftMargin-_fRightMargin;
       LONG MaxGridHeight = _fPageHeight-_fBottomMargin-_fTopMargin;

    /* Draw Horizontal grid lines */
       for (short index2=0; index2*_fGridSpacing<=MaxGridHeight; index2++) {
          ptl.y = PageYPos+_fBottomMargin+index2*_fGridSpacing;
          ptl.x = _fLeftPageOffset+_fLeftMargin;
          GpiMove(DrawingSurface, &ptl);

          ptl.x += MaxGridWidth;
          GpiLine(DrawingSurface, &ptl);
       } /* endfor */

    /* Draw Vertical grid lines */
       for (index2=0; index2*_fGridSpacing<=MaxGridWidth; index2++) {
          ptl.x = _fLeftPageOffset+_fLeftMargin+index2*_fGridSpacing;
          ptl.y = PageYPos+_fBottomMargin;
          GpiMove(DrawingSurface, &ptl);

          ptl.y += MaxGridHeight;
          GpiLine(DrawingSurface, &ptl);
       } /* endfor */
    } /* endif */

    if (DrawAdornments) {
       GpiSetLineType(DrawingSurface, _fMarginLine);

       GpiSetColor(DrawingSurface, _fVertMarginColor);
       if (_fShowVertMargins) {
       /* Draw Left Margin */
          ptl.x = _fLeftPageOffset+_fLeftMargin;
          ptl.y = PageYPos;
          GpiMove(DrawingSurface, &ptl);

          ptl.y += _fPageHeight;
          GpiLine(DrawingSurface, &ptl);

       /* Draw Right Margin */
          ptl.x = _fLeftPageOffset+_fPageWidth-_fRightMargin;
          ptl.y = PageYPos;
          GpiMove(DrawingSurface, &ptl);

          ptl.y += _fPageHeight;
          GpiLine(DrawingSurface, &ptl);
       } /* endif */

       if (_fShowHorzMargins) {
          GpiSetLineType(DrawingSurface, _fMarginLine);
          GpiSetColor(DrawingSurface, _fHorzMarginColor);
       /* Draw Bottom Margin */
          ptl.y = PageYPos+_fBottomMargin;
          ptl.x = _fLeftPageOffset;
          GpiMove(DrawingSurface, &ptl);

          ptl.x += _fPageWidth;
          GpiLine(DrawingSurface, &ptl);

       /* Draw Top Margin */
          ptl.y = PageYPos+_fPageHeight-_fTopMargin;
          ptl.x = _fLeftPageOffset;
          GpiMove(DrawingSurface, &ptl);

          ptl.x += _fPageWidth;
          GpiLine(DrawingSurface, &ptl);
       } /* endif */
    } /* endif */

    if (_fShowHorzRuler && DrawAdornments) {
    /* Begin Horizontal Ruler stuff */
       float UnitLength;
       float distance;
       GpiSetLineType(DrawingSurface, LINETYPE_SOLID);

    /* Draw "tick" marks for margins */
       GpiSetColor(DrawingSurface, _fVertMarginColor);
       LONG HorzRulerPos = _fPageHeight+_fTopPageOffset-HORZ_RULER_OFFSET;

    /* Left Margin tick mark */
       ptl.x = _fLeftPageOffset+_fLeftMargin-TICK_MARK_SIZE/2+1;
       ptl.y = PageYPos+HorzRulerPos+1;
       GpiMove(DrawingSurface, &ptl);

       GpiBeginPath(DrawingSurface, 1L); /* Draw triangle */
          ptl.x += TICK_MARK_SIZE;
          GpiLine(DrawingSurface, &ptl);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          GpiLine(DrawingSurface, &ptl);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y += TICK_MARK_SIZE/2;
          GpiLine(DrawingSurface, &ptl);
       GpiEndPath(DrawingSurface);
       GpiFillPath(DrawingSurface, 1L, FPATH_ALTERNATE);

    /* Right Margin tick mark */
       ptl.x = _fLeftPageOffset+_fPageWidth-_fRightMargin-TICK_MARK_SIZE/2;
       ptl.y = PageYPos+HorzRulerPos+1;
       GpiMove(DrawingSurface, &ptl);

       GpiBeginPath(DrawingSurface, 1L); /* Draw triangle */
          ptl.x += TICK_MARK_SIZE;
          GpiLine(DrawingSurface, &ptl);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          GpiLine(DrawingSurface, &ptl);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y += TICK_MARK_SIZE/2;
          GpiLine(DrawingSurface, &ptl);
       GpiEndPath(DrawingSurface);
       GpiFillPath(DrawingSurface, 1L, FPATH_ALTERNATE);

    /* Draw Horizontal ruler */
       GpiSetColor(DrawingSurface, _fRulerColor);

       ptl.y = PageYPos+HorzRulerPos+1;
       ptl.x = _fLeftPageOffset;
       GpiMove(DrawingSurface, &ptl);

       ptl.x += _fPageWidth;
       GpiLine(DrawingSurface, &ptl);

    /* Draw numbers next to each inch/centimeter mark */
       UnitLength = _fRulerUnits==INCHES ? INCH_LENGTH : CENTIMETER_LENGTH;

       ptl.y = PageYPos+HorzRulerPos+RULER_UNIT_OFFSET;
       char UnitString[5];
       LONG HalfStringSize;
       for (short unit=0; unit*UnitLength<=_fPageWidth; unit++) {
          sprintf(UnitString, "%d", unit);
          HalfStringSize = HALF_CHAR_SIZE*strlen(UnitString);
          ptl.x = _fLeftPageOffset+unit*UnitLength-HalfStringSize;
          GpiCharStringAt(DrawingSurface, &ptl, strlen(UnitString), UnitString);
       } /* endfor */

       if (_fRulerUnits==INCHES) {
    /* Draw Inch marks */
          ptl.x = _fLeftPageOffset;
          for (short index2=0; index2*INCH_LENGTH<=_fPageWidth; index2++) {
             ptl.y = PageYPos+HorzRulerPos+1;
             GpiMove(DrawingSurface, &ptl);

             ptl.y -= EIGHTH_INCH_MARK*4+1;
             GpiLine(DrawingSurface, &ptl);

             ptl.x += INCH_LENGTH;
          } /* endfor */

/* Rather than drawing half of the half-inch marks on top of the inch marks, */
/* (and 3/4 of the quarter-inch marks on top of the inch or half-inch marks, */
/* and so on), we instead only draw the marks where needed, avoiding drawing */
/* a smaller mark back over a larger mark wherever possible [141586]         */
    /* Draw Half-Inch, Quarter-Inch, and Eighth-Inch marks */
          for (short index3=1; index3<=3; index3++) {
             distance = INCH_LENGTH/PowerOf2(index3-1);
             ptl.x = _fLeftPageOffset+distance/2;
             for (float index4=0.5; index4*distance<=_fPageWidth; index4++) {
                ptl.y = PageYPos+HorzRulerPos+1;
                GpiMove(DrawingSurface, &ptl);

                ptl.y -= EIGHTH_INCH_MARK*(4-index3)+1;
                GpiLine(DrawingSurface, &ptl);

                ptl.x += distance;
             } /* endfor */
          } /* endfor */
       } else {
    /* Draw Centimeter marks */
/* jwa - Note: I tried putting in code for drawing millimeter marks, but they */
/* came out looking terrible, because, after the conversion from frame coords */
/* to pels, some of them ended up 2 pels apart, whereas others were 3 pels    */
/* apart, and at such small values it is real obvious (some were 50% further  */
/* from the next than others)                                                 */
          distance = CENTIMETER_LENGTH;
          for (short index3=0; index3*distance<=_fPageWidth; index3++) {
             ptl.x = _fLeftPageOffset+index3*distance;
             ptl.y = PageYPos+HorzRulerPos+1;
             GpiMove(DrawingSurface, &ptl);

             ptl.y -= CENTIMETER_MARK+1;
             GpiLine(DrawingSurface, &ptl);
          } /* endfor */
       } /* endif */
    } /* endif */

    if (_fShowVertRuler && DrawAdornments) {
    /* Begin Vertical Ruler stuff */
       float UnitLength;
       float distance;
       GpiSetLineType(DrawingSurface, LINETYPE_SOLID);

    /* Draw "tick" marks for margins */
       GpiSetColor(DrawingSurface, _fHorzMarginColor);

    /* Bottom Margin tick mark */
       ptl.x = VERT_RULER_OFFSET;
       ptl.y = PageYPos+_fBottomMargin-TICK_MARK_SIZE/2;
       GpiMove(DrawingSurface, &ptl);

       GpiBeginPath(DrawingSurface, 1L); /* Draw triangle */
          ptl.y += TICK_MARK_SIZE;
          GpiLine(DrawingSurface, &ptl);

          ptl.x += TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          GpiLine(DrawingSurface, &ptl);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          GpiLine(DrawingSurface, &ptl);
       GpiEndPath(DrawingSurface);
       GpiFillPath(DrawingSurface, 1L, FPATH_ALTERNATE);

    /* Top Margin tick mark */
       ptl.x = VERT_RULER_OFFSET;
       ptl.y = PageYPos+_fPageHeight-_fTopMargin-TICK_MARK_SIZE/2;
       GpiMove(DrawingSurface, &ptl);

       GpiBeginPath(DrawingSurface, 1L); /* Draw triangle */
          ptl.y += TICK_MARK_SIZE;
          GpiLine(DrawingSurface, &ptl);

          ptl.x += TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          GpiLine(DrawingSurface, &ptl);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          GpiLine(DrawingSurface, &ptl);
       GpiEndPath(DrawingSurface);
       GpiFillPath(DrawingSurface, 1L, FPATH_ALTERNATE);

    /* Draw Vertical ruler */
       GpiSetColor(DrawingSurface, _fRulerColor);

       ptl.x = VERT_RULER_OFFSET-1;
       ptl.y = PageYPos;
       GpiMove(DrawingSurface, &ptl);

       ptl.y += _fPageHeight;
       GpiLine(DrawingSurface, &ptl);

    /* Draw numbers next to each inch/centimeter mark */
       UnitLength = _fRulerUnits==INCHES ? INCH_LENGTH : CENTIMETER_LENGTH;

       ptl.x = 0;
       char UnitString[5];
       for (short unit=0; unit*UnitLength<=_fPageHeight; unit++) {
          ptl.y = PageYPos+_fPageHeight-unit*UnitLength-HALF_CHAR_SIZE;
          if (unit<100) {
             if (unit<10) {
                sprintf(UnitString, "  %d", unit);
             } else {
                sprintf(UnitString, " %d", unit);
             } /* endif */
          } else {
             sprintf(UnitString, "%d", unit);
          } /* endif */
          GpiCharStringAt(DrawingSurface, &ptl, strlen(UnitString), UnitString);
       } /* endfor */

       if (_fRulerUnits==INCHES) {
    /* Draw Inch marks */
          ptl.y = PageYPos+_fPageHeight;
          for (short index2=0; index2*INCH_LENGTH<=_fPageHeight; index2++) {
             ptl.x = VERT_RULER_OFFSET-1;
             GpiMove(DrawingSurface, &ptl);

             ptl.x += EIGHTH_INCH_MARK*4+1;
             GpiLine(DrawingSurface, &ptl);

             ptl.y -= INCH_LENGTH;
          } /* endfor */

/* Rather than drawing half of the half-inch marks on top of the inch marks, */
/* (and 3/4 of the quarter-inch marks on top of the inch or half-inch marks, */
/* and so on), we instead only draw the marks where needed, avoiding drawing */
/* a smaller mark back over a larger mark wherever possible [141586]         */
    /* Draw Half-Inch, Quarter-Inch, and Eighth-Inch marks */
          for (short index3=1; index3<=3; index3++) {
             distance = INCH_LENGTH/PowerOf2(index3-1);
             ptl.y = PageYPos+_fPageHeight-distance/2;
             for (float index4=0.5; index4*distance<=_fPageHeight; index4++) {
                ptl.x = VERT_RULER_OFFSET-1;
                GpiMove(DrawingSurface, &ptl);

                ptl.x += EIGHTH_INCH_MARK*(4-index3)+1;
                GpiLine(DrawingSurface, &ptl);

                ptl.y -= distance;
             } /* endfor */
          } /* endfor */
       } else {
       /* Draw Centimeter marks */
/* jwa - Note: I tried putting in code for drawing millimeter marks, but they */
/* came out looking terrible, because, after the conversion from frame coords */
/* to pels, some of them ended up 2 pels apart, whereas others were 3 pels    */
/* apart, and at such small values it is real obvious (some were 50% further  */
/* from the next than others)                                                 */
          distance = CENTIMETER_LENGTH;
          for (short index3=0; index3*distance<=_fPageHeight; index3++) {
             ptl.y = PageYPos+_fPageHeight-index3*distance;
             ptl.x = VERT_RULER_OFFSET-1;
             GpiMove(DrawingSurface, &ptl);

             ptl.x += CENTIMETER_MARK+1;
             GpiLine(DrawingSurface, &ptl);
          } /* endfor */
       } /* endif */
    } /* endif */

   GpiSetColor(DrawingSurface, _fPageStringColor);

#if 0 /* begin font setting code from Merlin's text part */
   FATTRS fat;

   fat.usRecordLength = sizeof(FATTRS);
   fat.fsSelection = 0;
   fat.lMatch = 0L;
   fat.idRegistry = 0;
   fat.usCodePage = 0;
   fat.lMaxBaselineExt = 10L;
   fat.lAveCharWidth = 10L;
   fat.fsType = 0;
   fat.fsFontUse = FATTR_FONTUSE_TRANSFORMABLE;

   strcpy(fat.szFacename, _fCurrentFont);

   GpiCreateLogFont(DrawingSurface,(PSTR8)0,1L,&fat);

   GpiSetCharSet(DrawingSurface, 1L);
#endif /* end font setting code from text part */

   int HeaderStringLen = strlen(_fHeaderText);
   int FooterStringLen = strlen(_fFooterText);

   POINTL aptl[TXTBOX_COUNT];

   GpiQueryTextBox(DrawingSurface, HeaderStringLen, _fHeaderText, TXTBOX_COUNT,aptl);
   int HeaderStringSize = (aptl[2].x - aptl[1].x) /2;
   int HeaderStringHeight = (aptl[2].y - aptl[4].y)+2;

   GpiQueryTextBox(DrawingSurface, FooterStringLen, _fFooterText, TXTBOX_COUNT,aptl);
   int FooterStringSize = (aptl[2].x - aptl[1].x) /2;
   int FooterStringHeight = (aptl[2].y - aptl[4].y)+2;

   short pageNumberDisplayed = _fNumberOfPages-pageNumber;
   if (pageNumberDisplayed >= _fPageNumberStartOn) {
      char PageString[14];
      sprintf(PageString, "%d", pageNumberDisplayed-_fPageNumberStartOn+_fPageNumberStartWith);
      int PageStringLen = strlen(PageString);
      GpiQueryTextBox(DrawingSurface, PageStringLen, PageString,
                               TXTBOX_COUNT,aptl);
      int PageStringSize = (aptl[2].x - aptl[1].x) /2;
      int PageStringHeight = (aptl[2].y - aptl[4].y)+2;

      switch (_fPageNumberPosition) {
      case TOP_LEFT:
         ptl.x = _fLeftPageOffset+_fLeftMargin;
         ptl.y = PageYPos+_fPageHeight-_fTopMargin+2;
         if (HeaderStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y += HeaderStringHeight;
         break;
      case TOP_CENTER:
         ptl.x = _fLeftPageOffset+_fLeftMargin+((_fPageWidth-_fRightMargin)-_fLeftMargin)/2-PageStringSize;
         ptl.y = PageYPos+_fPageHeight-_fTopMargin+2;
         if (HeaderStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y += HeaderStringHeight;
         break;
      case TOP_RIGHT:
         ptl.x = _fPageWidth+_fLeftPageOffset-_fRightMargin-2*PageStringSize;
         ptl.y = PageYPos+_fPageHeight-_fTopMargin+2;
         if (HeaderStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y += HeaderStringHeight;
         break;
      case BOTTOM_LEFT:
         ptl.x = _fLeftPageOffset+_fLeftMargin;
         ptl.y = PageYPos+_fBottomMargin-PageStringHeight;
         if (FooterStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y -= FooterStringHeight;
         break;
      case BOTTOM_CENTER:
         ptl.x = _fLeftPageOffset+_fLeftMargin+((_fPageWidth-_fRightMargin)-_fLeftMargin)/2-PageStringSize;
         ptl.y = PageYPos+_fBottomMargin-PageStringHeight;
         if (FooterStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y -= FooterStringHeight;
         break;
      case BOTTOM_RIGHT:
         ptl.x = _fPageWidth+_fLeftPageOffset-_fRightMargin-2*PageStringSize;
         ptl.y = PageYPos+_fBottomMargin-PageStringHeight;
         if (FooterStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y -= FooterStringHeight;
         break;
      } /* endswitch */

      if (_fPageNumberPosition != NONE) {
         GpiCharStringAt(DrawingSurface, &ptl, PageStringLen, PageString);
      } /* endif */
   } /* endif */

   if (HeaderStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn)) {
      ptl.x = _fLeftPageOffset+_fLeftMargin+(_fPageWidth-_fRightMargin-_fLeftMargin)/2-HeaderStringSize;
      ptl.y = PageYPos+_fPageHeight-_fTopMargin+2;
      GpiCharStringAt(DrawingSurface, &ptl, HeaderStringLen, _fHeaderText);
   } /* endif */

   if (FooterStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn)) {
      ptl.x = _fLeftPageOffset+_fLeftMargin+(_fPageWidth-_fRightMargin-_fLeftMargin)/2-FooterStringSize;
      ptl.y = PageYPos+_fBottomMargin-FooterStringHeight+2;
      GpiCharStringAt(DrawingSurface, &ptl, FooterStringLen, _fFooterText);
   } /* endif */
#endif //_PLATFORM_OS2_


#ifdef _PLATFORM_WIN32_
    POINTL ptl;
    LONG PageYPos = _fTopPageOffset+pageNumber*_fTotalPageHeight;

#ifndef SMART_DRAWING
    if (!_fIsTransparent &&
        (DrawAdornments || (isPrinting && _fPrintPageColor))) {

       // Create a solid brush
       HBRUSH pageBrush = CreateSolidBrush (_fPageColor);

       Rect pageRect;

       SetRect(&pageRect, _fLeftPageOffset,             /* left */
                          PageYPos,                     /* top */
                          _fLeftPageOffset+_fPageWidth, /* right */
                          PageYPos+_fPageHeight);       /* bottom */

       // Fill the rectangle with the brush
       FillRect (DrawingSurface, &pageRect, pageBrush);

       // Get rid of the brush
       DeleteObject(pageBrush);
    } /* endif */
#endif

    if (_fShowGrid && DrawAdornments) {
       HPEN gridPen = CreatePen(_fGridLine, 0, _fGridColor);
       HPEN oldPen = SelectObject(DrawingSurface, gridPen);

       LONG MaxGridWidth = _fPageWidth-_fLeftMargin-_fRightMargin;
       LONG MaxGridHeight = _fPageHeight-_fBottomMargin-_fTopMargin;

    /* Draw Horizontal grid lines */
       for (short index2=0; index2*_fGridSpacing<=MaxGridHeight; index2++) {
          ptl.x = _fLeftPageOffset+_fLeftMargin;
          ptl.y = PageYPos+_fBottomMargin+index2*_fGridSpacing;
          MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

          ptl.x += MaxGridWidth;
          LineTo(DrawingSurface, ptl.x, ptl.y);
       } /* endfor */

    /* Draw Vertical grid lines */
       for (index2=0; index2*_fGridSpacing<=MaxGridWidth; index2++) {
          ptl.x = _fLeftPageOffset+_fLeftMargin+index2*_fGridSpacing;
          ptl.y = PageYPos+_fTopMargin;
          MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

          ptl.y += MaxGridHeight;
          LineTo(DrawingSurface, ptl.x, ptl.y);
       } /* endfor */

       SelectObject(DrawingSurface, oldPen);
       DeleteObject(gridPen);
    } /* endif */

    if (DrawAdornments) {
       if (_fShowVertMargins) {
          HPEN vertMarginPen = CreatePen(_fMarginLine, 0, _fVertMarginColor);
          HPEN oldPen = SelectObject(DrawingSurface, vertMarginPen);

       /* Draw Left Margin */
          ptl.x = _fLeftPageOffset+_fLeftMargin;
          ptl.y = PageYPos;
          MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

          ptl.y += _fPageHeight;
          LineTo(DrawingSurface, ptl.x, ptl.y);

       /* Draw Right Margin */
          ptl.x = _fLeftPageOffset+_fPageWidth-_fRightMargin;
          ptl.y = PageYPos;
          MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

          ptl.y += _fPageHeight;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          SelectObject(DrawingSurface, oldPen);
          DeleteObject(vertMarginPen);
       } /* endif */

       if (_fShowHorzMargins) {
          HPEN horzMarginPen = CreatePen(_fMarginLine, 0, _fHorzMarginColor);
          HPEN oldPen = SelectObject(DrawingSurface, horzMarginPen);

       /* Draw Top Margin */
          ptl.x = _fLeftPageOffset;
          ptl.y = PageYPos+_fTopMargin;
          MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

          ptl.x += _fPageWidth;
          LineTo(DrawingSurface, _fLeftPageOffset+_fPageWidth,
             PageYPos+_fTopMargin);

       /* Draw Bottom Margin */
          ptl.x = _fLeftPageOffset;
          ptl.y = PageYPos+_fPageHeight-_fBottomMargin;
          MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

          ptl.x += _fPageWidth;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          SelectObject(DrawingSurface, oldPen);
          DeleteObject(horzMarginPen);
       } /* endif */
    } /* endif */

    if (_fShowHorzRuler && DrawAdornments) {
    /* Begin Horizontal Ruler stuff */
       float UnitLength;
       float distance;

       HPEN horzRulerPen = CreatePen(PS_SOLID, 0, _fRulerColor);
       HPEN oldPen = SelectObject(DrawingSurface, horzRulerPen);

       LONG HorzRulerPos = _fTopPageOffset-HORZ_RULER_OFFSET;

    /* Draw "tick" marks for margins */
       HBRUSH tickMarkBrush = CreateSolidBrush(_fVertMarginColor);
       HBRUSH oldBrush = SelectObject(DrawingSurface, tickMarkBrush);

    /* Left Margin tick mark */
       ptl.x = _fLeftPageOffset+_fLeftMargin-TICK_MARK_SIZE/2+1;
       ptl.y = PageYPos-HorzRulerPos-1;
       MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

       BeginPath(DrawingSurface); /* Draw triangle */
          ptl.x += TICK_MARK_SIZE;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y += TICK_MARK_SIZE/2;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          LineTo(DrawingSurface, ptl.x, ptl.y);
       EndPath(DrawingSurface);
       FillPath(DrawingSurface);

    /* Right Margin tick mark */
       ptl.x = _fLeftPageOffset+_fPageWidth-_fRightMargin-TICK_MARK_SIZE/2;
       ptl.y = PageYPos-HorzRulerPos-1;
       MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

       BeginPath(DrawingSurface); /* Draw triangle */
          ptl.x += TICK_MARK_SIZE;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y += TICK_MARK_SIZE/2;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          LineTo(DrawingSurface, ptl.x, ptl.y);
       EndPath(DrawingSurface);
       FillPath(DrawingSurface);

       SelectObject(DrawingSurface, oldBrush);
       DeleteObject(tickMarkBrush);

    /* Draw Horizontal ruler */
       ptl.x = _fLeftPageOffset;
       ptl.y = PageYPos-HorzRulerPos-1;
       MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

       ptl.x += _fPageWidth;
       LineTo(DrawingSurface, ptl.x, ptl.y);

    /* Draw numbers next to each inch/centimeter mark */
       UnitLength = _fRulerUnits==INCHES ? INCH_LENGTH : CENTIMETER_LENGTH;

       char UnitString[5];
       LONG HalfStringSize;
       LONG StringHeight = 10;

       ptl.y = PageYPos-HorzRulerPos-RULER_UNIT_OFFSET-StringHeight;
       for (short unit=0; unit*UnitLength<=_fPageWidth; unit++) {
          sprintf(UnitString, "%d", unit);
          HalfStringSize = HALF_CHAR_SIZE*strlen(UnitString);

//        ptl.x = _fLeftPageOffset+unit*UnitLength-HalfStringSize;
          ptl.x = _fLeftPageOffset+unit*UnitLength-HalfStringSize/2;
          TextOut(DrawingSurface, ptl.x, ptl.y, UnitString, strlen(UnitString));
       } /* endfor */

       if (_fRulerUnits==INCHES) {
    /* Draw Inch marks */
          ptl.x = _fLeftPageOffset;
          for (short index2=0; index2*INCH_LENGTH<=_fPageWidth; index2++) {
             ptl.y = PageYPos-HorzRulerPos-1;
             MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

             ptl.y += EIGHTH_INCH_MARK*4+1;
             LineTo(DrawingSurface, ptl.x, ptl.y);

             ptl.x += INCH_LENGTH;
          } /* endfor */

/* Rather than drawing half of the half-inch marks on top of the inch marks, */
/* (and 3/4 of the quarter-inch marks on top of the inch or half-inch marks, */
/* and so on), we instead only draw the marks where needed, avoiding drawing */
/* a smaller mark back over a larger mark wherever possible [141586]         */
    /* Draw Half-Inch, Quarter-Inch, and Eighth-Inch marks */
          for (short index3=1; index3<=3; index3++) {
             distance = INCH_LENGTH/PowerOf2(index3-1);
             ptl.x = _fLeftPageOffset+distance/2;
             for (float index4=0.5; index4*distance<=_fPageWidth; index4++) {
                ptl.y = PageYPos-HorzRulerPos-1;
                MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

                ptl.y += EIGHTH_INCH_MARK*(4-index3)+1;
                LineTo(DrawingSurface, ptl.x, ptl.y);

                ptl.x += distance;
             } /* endfor */
          } /* endfor */
       } else {
    /* Draw Centimeter marks */
/* jwa - Note: I tried putting in code for drawing millimeter marks, but they */
/* came out looking terrible, because, after the conversion from frame coords */
/* to pels, some of them ended up 2 pels apart, whereas others were 3 pels    */
/* apart, and at such small values it is real obvious (some were 50% further  */
/* from the next than others)                                                 */
          distance = CENTIMETER_LENGTH;
          for (short index3=0; index3*distance<=_fPageWidth; index3++) {
             ptl.x = _fLeftPageOffset+index3*distance;
             ptl.y = PageYPos-HorzRulerPos-1;
             MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

             ptl.y += CENTIMETER_MARK+1;
             LineTo(DrawingSurface, ptl.x, ptl.y);
          } /* endfor */
       } /* endif */

       SelectObject(DrawingSurface, oldPen);
       DeleteObject(horzRulerPen);
    } /* endif */

    if (_fShowVertRuler && DrawAdornments) {
    /* Begin Vertical Ruler stuff */
       float UnitLength;
       float distance;

       HPEN vertRulerPen = CreatePen(PS_SOLID, 0, _fRulerColor);
       HPEN oldPen = SelectObject(DrawingSurface, vertRulerPen);

    /* Draw "tick" marks for margins */
       HBRUSH tickMarkBrush = CreateSolidBrush(_fHorzMarginColor);
       HBRUSH oldBrush = SelectObject(DrawingSurface, tickMarkBrush);

    /* Top Margin tick mark */
       ptl.x = VERT_RULER_OFFSET-1;
       ptl.y = PageYPos+_fTopMargin-TICK_MARK_SIZE/2;
       MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

       BeginPath(DrawingSurface); /* Draw triangle */
          ptl.y += TICK_MARK_SIZE;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          ptl.x += TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          LineTo(DrawingSurface, ptl.x, ptl.y);
       EndPath(DrawingSurface);
       FillPath(DrawingSurface);

    /* Bottom Margin tick mark */
       ptl.x = VERT_RULER_OFFSET-1;
       ptl.y = PageYPos+_fPageHeight-_fBottomMargin-TICK_MARK_SIZE/2;
       MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

       BeginPath(DrawingSurface); /* Draw triangle */
          ptl.y += TICK_MARK_SIZE;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          ptl.x += TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          LineTo(DrawingSurface, ptl.x, ptl.y);

          ptl.x -= TICK_MARK_SIZE/2;
          ptl.y -= TICK_MARK_SIZE/2;
          LineTo(DrawingSurface, ptl.x, ptl.y);
       EndPath(DrawingSurface);
       FillPath(DrawingSurface);

       SelectObject(DrawingSurface, oldBrush);
       DeleteObject(tickMarkBrush);

    /* Draw Vertical ruler */
       ptl.x = VERT_RULER_OFFSET-1;
       ptl.y = PageYPos;
       MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

       ptl.y += _fPageHeight;
       LineTo(DrawingSurface, ptl.x, ptl.y);

    /* Draw numbers next to each inch/centimeter mark */
       UnitLength = _fRulerUnits==INCHES ? INCH_LENGTH : CENTIMETER_LENGTH;

       ptl.x = 0;
       char UnitString[5];
       for (short unit=0; unit*UnitLength<=_fPageHeight; unit++) {
          ptl.y = PageYPos+unit*UnitLength-HALF_CHAR_SIZE-1;
          if (unit<100) {
             if (unit<10) {
                sprintf(UnitString, "  %d", unit);
             } else {
                sprintf(UnitString, " %d", unit);
             } /* endif */
          } else {
             sprintf(UnitString, "%d", unit);
          } /* endif */
          TextOut(DrawingSurface, ptl.x, ptl.y, UnitString, strlen(UnitString));
       } /* endfor */

       if (_fRulerUnits==INCHES) {
    /* Draw Inch marks */
          ptl.y = PageYPos;
          for (short index2=0; index2*INCH_LENGTH<=_fPageHeight; index2++) {
             ptl.x = VERT_RULER_OFFSET-1;
             MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

             ptl.x += EIGHTH_INCH_MARK*4+1;
             LineTo(DrawingSurface, ptl.x, ptl.y);

             ptl.y += INCH_LENGTH;
          } /* endfor */

/* Rather than drawing half of the half-inch marks on top of the inch marks, */
/* (and 3/4 of the quarter-inch marks on top of the inch or half-inch marks, */
/* and so on), we instead only draw the marks where needed, avoiding drawing */
/* a smaller mark back over a larger mark wherever possible [141586]         */
    /* Draw Half-Inch, Quarter-Inch, and Eighth-Inch marks */
          for (short index3=1; index3<=3; index3++) {
             distance = INCH_LENGTH/PowerOf2(index3-1);
             ptl.y = PageYPos+distance/2;
             for (float index4=0.5; index4*distance<=_fPageHeight; index4++) {
                ptl.x = VERT_RULER_OFFSET-1;
                MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

                ptl.x += EIGHTH_INCH_MARK*(4-index3)+1;
                LineTo(DrawingSurface, ptl.x, ptl.y);

                ptl.y += distance;
             } /* endfor */
          } /* endfor */
       } else {
       /* Draw Centimeter marks */
/* jwa - Note: I tried putting in code for drawing millimeter marks, but they */
/* came out looking terrible, because, after the conversion from frame coords */
/* to pels, some of them ended up 2 pels apart, whereas others were 3 pels    */
/* apart, and at such small values it is real obvious (some were 50% further  */
/* from the next than others)                                                 */
          distance = CENTIMETER_LENGTH;
          for (short index3=0; index3*distance<=_fPageHeight; index3++) {
             ptl.y = PageYPos+index3*distance;
             ptl.x = VERT_RULER_OFFSET-1;
             MoveToEx(DrawingSurface, ptl.x, ptl.y, kODNULL);

             ptl.x += CENTIMETER_MARK+1;
             LineTo(DrawingSurface, ptl.x, ptl.y);
          } /* endfor */
       } /* endif */

       SelectObject(DrawingSurface, oldPen);
       DeleteObject(vertRulerPen);
    } /* endif */

   int HeaderStringLen = strlen(_fHeaderText);
   int FooterStringLen = strlen(_fFooterText);

   SIZE size;
   GetTextExtentPoint32(DrawingSurface, _fHeaderText, HeaderStringLen, &size);
   int HeaderStringSize = size.cx/2;
   int HeaderStringHeight = size.cy+2;

   GetTextExtentPoint32(DrawingSurface, _fFooterText, FooterStringLen, &size);
   int FooterStringSize = size.cx/2;
   int FooterStringHeight = size.cy+2;

   short pageNumberDisplayed = pageNumber+1;
   if (pageNumberDisplayed >= _fPageNumberStartOn) {
      char PageString[14];
      sprintf(PageString, "%d", pageNumberDisplayed-_fPageNumberStartOn+_fPageNumberStartWith);
      int PageStringLen = strlen(PageString);
      GetTextExtentPoint32(DrawingSurface, PageString, PageStringLen, &size);
      int PageStringSize = size.cx/2;
      int PageStringHeight = size.cy+2;

      switch (_fPageNumberPosition) {
      case TOP_LEFT:
         ptl.x = _fLeftPageOffset+_fLeftMargin;
         ptl.y = PageYPos+_fTopMargin-PageStringHeight;
         if (HeaderStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y -= HeaderStringHeight;
         break;
      case TOP_CENTER:
         ptl.x = _fLeftPageOffset+_fLeftMargin+((_fPageWidth-_fRightMargin)-_fLeftMargin)/2-PageStringSize;
         ptl.y = PageYPos+_fTopMargin-PageStringHeight;
         if (HeaderStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y -= HeaderStringHeight;
         break;
      case TOP_RIGHT:
         ptl.x = _fPageWidth+_fLeftPageOffset-_fRightMargin-2*PageStringSize;
         ptl.y = PageYPos+_fTopMargin-PageStringHeight;
         if (HeaderStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y -= HeaderStringHeight;
         break;
      case BOTTOM_LEFT:
         ptl.x = _fLeftPageOffset+_fLeftMargin;
         ptl.y = PageYPos+_fPageHeight-_fBottomMargin+2;
         if (FooterStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y -= FooterStringHeight;
         break;
      case BOTTOM_CENTER:
         ptl.x = _fLeftPageOffset+_fLeftMargin+((_fPageWidth-_fRightMargin)-_fLeftMargin)/2-PageStringSize;
         ptl.y = PageYPos+_fPageHeight-_fBottomMargin+2;
         if (FooterStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y += FooterStringHeight;
         break;
      case BOTTOM_RIGHT:
         ptl.x = _fPageWidth+_fLeftPageOffset-_fRightMargin-2*PageStringSize;
         ptl.y = PageYPos+_fPageHeight-_fBottomMargin+2;
         if (FooterStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn))
            ptl.y += FooterStringHeight;
         break;
      } /* endswitch */

      if (_fPageNumberPosition != NONE) {
         TextOut(DrawingSurface, ptl.x, ptl.y, PageString, PageStringLen);
      } /* endif */
   } /* endif */

   if (HeaderStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn)) {
      ptl.x = _fLeftPageOffset+_fLeftMargin+(_fPageWidth-_fRightMargin-_fLeftMargin)/2-HeaderStringSize;
      ptl.y = PageYPos+_fTopMargin-HeaderStringHeight-2;
      TextOut(DrawingSurface, ptl.x, ptl.y, _fHeaderText, HeaderStringLen);
   } /* endif */

   if (FooterStringLen && (pageNumberDisplayed >= _fHeaderFooterStartOn)) {
      ptl.x = _fLeftPageOffset+_fLeftMargin+(_fPageWidth-_fRightMargin-_fLeftMargin)/2-FooterStringSize;
      ptl.y = PageYPos+_fPageHeight-_fBottomMargin+2;
      TextOut(DrawingSurface, ptl.x, ptl.y, _fFooterText, FooterStringLen);
   } /* endif */
#endif //_PLATFORM_WIN32_
}


SOM_Scope ODBoolean  SOMLINK PageLayoutHandleMenuEvent(PageLayout *somSelf,
                                                        Environment *ev,
                                                       ODFrame* frame,
                                                       ODEventData* event)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutHandleMenuEvent");

    ODBoolean handled = kODTrue;
    char *newText;
    short NewPage;
    ODBoolean contentChanged = kODTrue;

#ifdef _PLATFORM_OS2_
    long menuItem = LONGFROMMP(event->mp1);
#endif

#ifdef _PLATFORM_WIN32_
    short menuItem = LOWORD(event->wParam);
#endif

    switch (menuItem) {
    case MenuFillPage:
       _FillEntirePage(ev, frame);
       break;
    case MenuSnapToGrid:
       _SnapToGrid(ev, frame);
       break;
    case MenuShowMargins:
       _fShowHorzMargins = !_fShowHorzMargins;
       _fShowVertMargins = !_fShowVertMargins;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuShowRulers:
       _fShowHorzRuler = !_fShowHorzRuler;
       _fShowVertRuler = !_fShowVertRuler;
       frame->Invalidate(ev, _fBackgroundShape, kNoBias);
       break;
    case MenuShowGrid:
       _fShowGrid = !_fShowGrid;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuRefresh:
       frame->Invalidate(ev, kODNULL, kNoBias);
       break;
    case MenuInsertPage:
       if (_MaxPagesReached(ev)) {
          WarningBox(event->hwnd, ERRm, MRI(MaxPageString));
          contentChanged = kODFalse;
       } else {
#ifdef _PLATFORM_OS2_
          NewPage = WinDlgBox(HWND_DESKTOP, event->hwnd, ChoosePageDlgProc,
            _fResources, ChoosePageDlgValue,
            (PVOID) MPFROM2SHORT(InsertPageDlgValue, _fNumberOfPages));
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
          NewPage = DialogBoxParam(_fResources,
             MAKEINTRESOURCE(ChoosePageDlgValue), event->hwnd,
             (DLGPROC) ChoosePageDlgProc,
             (LPARAM) MAKELONG(_fNumberOfPages, InsertPageDlgValue));
#endif //_PLATFORM_WIN32_

          if (NewPage>0) { /* Cancel wasn't chosen */
             _InsertPage(ev, frame, NewPage);
          } else contentChanged = kODFalse;
       } /* endif */
       break;
    case MenuInsertPageLast:
       if (_MaxPagesReached(ev)) {
          WarningBox(event->hwnd, ERRm, MRI(MaxPageString));
          contentChanged = kODFalse;
       } else {
          _InsertPage(ev, frame, _fNumberOfPages);
       } /* endif */
       break;
    case MenuRemovePage:
#ifdef _PLATFORM_OS2_
       NewPage = WinDlgBox(HWND_DESKTOP, event->hwnd, ChoosePageDlgProc,
         _fResources, ChoosePageDlgValue,
         (PVOID) MPFROM2SHORT(RemovePageDlgValue, _fNumberOfPages));
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
          NewPage = DialogBoxParam(_fResources,
             MAKEINTRESOURCE(ChoosePageDlgValue), event->hwnd,
             (DLGPROC) ChoosePageDlgProc,
             (LPARAM) MAKELONG(_fNumberOfPages, RemovePageDlgValue));
#endif //_PLATFORM_WIN32_

       if (NewPage>0) { /* Cancel wasn't chosen */
          _RemovePage(ev, frame, NewPage);
       } else contentChanged = kODFalse;
       break;
    case MenuGoToPage:
#ifdef _PLATFORM_OS2_
       NewPage = WinDlgBox(HWND_DESKTOP, event->hwnd, ChoosePageDlgProc,
          _fResources, ChoosePageDlgValue,
          (PVOID) MPFROM2SHORT(GoToPageDlgValue, _fNumberOfPages));
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
       NewPage = DialogBoxParam(_fResources,
          MAKEINTRESOURCE(ChoosePageDlgValue), event->hwnd,
          (DLGPROC) ChoosePageDlgProc,
          (LPARAM) MAKELONG(_fNumberOfPages, GoToPageDlgValue));
#endif //_PLATFORM_WIN32_

       if ((NewPage>0) && (_fScrollExt!=kODNULL)) { /* Cancel wasn't chosen */
          _fScrollExt->SetScrollPosition(ev, frame, 0,
             (NewPage-1)*_fTotalPageHeight);
          _DetermineVisiblePages(ev, frame);
       } /* endif */
       contentChanged = kODFalse;
       break;
    case MenuPageNumberTopLeft:
       _fPageNumberPosition = TOP_LEFT;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuPageNumberTopCenter:
       _fPageNumberPosition = TOP_CENTER;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuPageNumberTopRight:
       _fPageNumberPosition = TOP_RIGHT;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuPageNumberBottomLeft:
       _fPageNumberPosition = BOTTOM_LEFT;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuPageNumberBottomCenter:
       _fPageNumberPosition = BOTTOM_CENTER;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuPageNumberBottomRight:
       _fPageNumberPosition = BOTTOM_RIGHT;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuPageNumberNone:
       _fPageNumberPosition = NONE;
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuRulerInches:
       _fRulerUnits = INCHES;
       frame->Invalidate(ev, _fBackgroundShape, kNoBias);
       break;
    case MenuRulerCentimeters:
       _fRulerUnits = METRIC;
       frame->Invalidate(ev, _fBackgroundShape, kNoBias);
       break;
    case MenuMarginDots:
#ifdef _PLATFORM_OS2_
       _fMarginLine = LINETYPE_DOT;
#endif
#ifdef _PLATFORM_WIN32_
       _fMarginLine = PS_DOT;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuMarginDash:
#ifdef _PLATFORM_OS2_
       _fMarginLine = LINETYPE_LONGDASH;
#endif
#ifdef _PLATFORM_WIN32_
       _fMarginLine = PS_DASH;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuMarginDashDot:
#ifdef _PLATFORM_OS2_
       _fMarginLine = LINETYPE_DASHDOT;
#endif
#ifdef _PLATFORM_WIN32_
       _fMarginLine = PS_DASHDOT;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuMarginDashDoubleDot:
#ifdef _PLATFORM_OS2_
       _fMarginLine = LINETYPE_DASHDOUBLEDOT;
#endif
#ifdef _PLATFORM_WIN32_
       _fMarginLine = PS_DASHDOTDOT;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuMarginSolid:
#ifdef _PLATFORM_OS2_
       _fMarginLine = LINETYPE_SOLID;
#endif
#ifdef _PLATFORM_WIN32_
       _fMarginLine = PS_SOLID;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuGridDots:
#ifdef _PLATFORM_OS2_
       _fGridLine = LINETYPE_DOT;
#endif
#ifdef _PLATFORM_WIN32_
       _fGridLine = PS_DOT;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuGridDash:
#ifdef _PLATFORM_OS2_
       _fGridLine = LINETYPE_LONGDASH;
#endif
#ifdef _PLATFORM_WIN32_
       _fGridLine = PS_DASH;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuGridDashDot:
#ifdef _PLATFORM_OS2_
       _fGridLine = LINETYPE_DASHDOT;
#endif
#ifdef _PLATFORM_WIN32_
       _fGridLine = PS_DASHDOT;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuGridDashDoubleDot:
#ifdef _PLATFORM_OS2_
       _fGridLine = LINETYPE_DASHDOUBLEDOT;
#endif
#ifdef _PLATFORM_WIN32_
       _fGridLine = PS_DASHDOTDOT;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuGridSolid:
#ifdef _PLATFORM_OS2_
       _fGridLine = LINETYPE_SOLID;
#endif
#ifdef _PLATFORM_WIN32_
       _fGridLine = PS_SOLID;
#endif
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuHeader:
#ifdef _PLATFORM_OS2_
       newText = (char *) WinDlgBox(HWND_DESKTOP, event->hwnd, GetTextDlgProc,
          _fResources, GetTextDlgValue, (PVOID) HeaderDlgValue);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
       newText = (char *) DialogBoxParam(_fResources,
          MAKEINTRESOURCE(GetTextDlgValue), event->hwnd,
          (DLGPROC) GetTextDlgProc, (LPARAM) HeaderDlgValue);
#endif //_PLATFORM_WIN32_

       if (newText!=kODNULL) {
          strcpy(_fHeaderText, newText);
          free(newText);
          frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       } else contentChanged = kODFalse;
       break;
    case MenuFooter:
#ifdef _PLATFORM_OS2_
       newText = (char *) WinDlgBox(HWND_DESKTOP, event->hwnd, GetTextDlgProc,
          _fResources, GetTextDlgValue, (PVOID) FooterDlgValue);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
       newText = (char *) DialogBoxParam(_fResources,
          MAKEINTRESOURCE(GetTextDlgValue), event->hwnd,
          (DLGPROC) GetTextDlgProc, (LPARAM) FooterDlgValue);
#endif //_PLATFORM_WIN32_

       if (newText!=kODNULL) {
          strcpy(_fFooterText, newText);
          free(newText);
          frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       } else contentChanged = kODFalse;
       break;
    case MenuBackgroundColor:
       _fBackgroundColor = _ColorSelection(ev, _fBackgroundColor, 1);
       frame->Invalidate(ev, _fBackgroundShape, kNoBias);
       break;
    case MenuPageColor:
       _fPageColor = _ColorSelection(ev, _fPageColor, 1);
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuTextColor:
       _fPageStringColor = _ColorSelection(ev, _fPageStringColor, 1);
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    case MenuRulersColor:
       _fRulerColor = _ColorSelection(ev, _fRulerColor, 1);
       frame->Invalidate(ev, _fBackgroundShape, kNoBias);
       break;
    case MenuMarginsColor:
       _fHorzMarginColor = _fVertMarginColor =
          _ColorSelection(ev, _fVertMarginColor, 1);
       frame->Invalidate(ev, kODNULL, kNoBias);
       break;
    case MenuGridColor:
       _fGridColor = _ColorSelection(ev, _fGridColor, 1);
       frame->Invalidate(ev, _fVisiblePagesShape, kNoBias);
       break;
    default:
       handled = kODFalse;
       contentChanged=kODFalse;
       break;
    } /* endswitch */

    if (contentChanged)
    {
      somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);
      PageLayout_parent_BaseContainer_ChangeNotification(somSelf, ev,
           BCC_INTRINSIC, kODNULL, kODNULL, kODTrue, kODNULL);
    }

    if (!handled) {
       handled = PageLayout_parent_BaseContainer_HandleMenuEvent(somSelf, ev,
          frame, event);
    } /* endif */

    return(handled);
}


SOM_Scope void  SOMLINK PageLayoutAdjustMenus(PageLayout *somSelf,
                                               Environment *ev,
                                              ODFrame* frame)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutAdjustMenus");

    PageLayout_parent_BaseContainer_AdjustMenus(somSelf, ev, frame);

    if (frame->GetLinkStatus(ev) == kODInLinkDestination)
    {
      _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, MenuFillPage, kODFalse);
      _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, MenuSnapToGrid, kODFalse);
      _fMenuBar->EnableMenuItem(ev, IDMS_VIEW, MenuShowRulers, kODFalse);
      _fMenuBar->EnableMenuItem(ev, IDMS_VIEW, MenuShowMargins, kODFalse);
      _fMenuBar->EnableMenuItem(ev, IDMS_VIEW, MenuShowGrid, kODFalse);
      _fMenuBar->EnableMenu(ev, PageMenuID, kODFalse);
      _fMenuBar->EnableMenu(ev, ColorMenuID, kODFalse);
    }
    else
    {
      ODBoolean HasSelection = kODFalse;
      ALinkedList *itr = _GetSelectedObjects(ev);
      if (itr) {
         ALink *item = itr->First(ev);
         if (item) {
            HasSelection = (item->Content(ev)!=kODNULL);
         } /* endif */
      } /* endif */

      _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, MenuFillPage, HasSelection);
      _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, MenuSnapToGrid, HasSelection);

      _fMenuBar->CheckMenuItem(ev, IDMS_VIEW, MenuShowRulers,
          _fShowVertRuler || _fShowHorzRuler);
      _fMenuBar->CheckMenuItem(ev, IDMS_VIEW, MenuShowMargins,
          _fShowVertMargins || _fShowHorzMargins);
      _fMenuBar->CheckMenuItem(ev, IDMS_VIEW, MenuShowGrid, _fShowGrid);

      _fMenuBar->EnableMenuItem(ev, PageMenuID, MenuRemovePage,
         _fNumberOfPages>1);

      _fMenuBar->CheckMenuItem(ev, MenuPageNumberPosition, MenuPageNumberTopLeft,
         _fPageNumberPosition==TOP_LEFT);
      _fMenuBar->CheckMenuItem(ev, MenuPageNumberPosition, MenuPageNumberTopCenter,
         _fPageNumberPosition==TOP_CENTER);
      _fMenuBar->CheckMenuItem(ev, MenuPageNumberPosition, MenuPageNumberTopRight,
         _fPageNumberPosition==TOP_RIGHT);
      _fMenuBar->CheckMenuItem(ev, MenuPageNumberPosition, MenuPageNumberBottomLeft,
         _fPageNumberPosition==BOTTOM_LEFT);
      _fMenuBar->CheckMenuItem(ev, MenuPageNumberPosition, MenuPageNumberBottomCenter,
         _fPageNumberPosition==BOTTOM_CENTER);
      _fMenuBar->CheckMenuItem(ev, MenuPageNumberPosition, MenuPageNumberBottomRight,
         _fPageNumberPosition==BOTTOM_RIGHT);
      _fMenuBar->CheckMenuItem(ev, MenuPageNumberPosition, MenuPageNumberNone,
         _fPageNumberPosition==NONE);

      _fMenuBar->CheckMenuItem(ev, MenuRulerUnits, MenuRulerInches,
         _fRulerUnits==INCHES);
      _fMenuBar->CheckMenuItem(ev, MenuRulerUnits, MenuRulerCentimeters,
         _fRulerUnits==METRIC);

      _fMenuBar->CheckMenuItem(ev, MenuMarginLineType, MenuMarginDots,
#ifdef _PLATFORM_OS2_
         _fMarginLine==LINETYPE_DOT);
#endif
#ifdef _PLATFORM_WIN32_
         _fMarginLine==PS_DOT);
#endif
      _fMenuBar->CheckMenuItem(ev, MenuMarginLineType, MenuMarginDash,
#ifdef _PLATFORM_OS2_
         _fMarginLine==LINETYPE_LONGDASH);
#endif
#ifdef _PLATFORM_WIN32_
         _fMarginLine==PS_DASH);
#endif
      _fMenuBar->CheckMenuItem(ev, MenuMarginLineType, MenuMarginDashDot,
#ifdef _PLATFORM_OS2_
         _fMarginLine==LINETYPE_DASHDOT);
#endif
#ifdef _PLATFORM_WIN32_
         _fMarginLine==PS_DASHDOT);
#endif
      _fMenuBar->CheckMenuItem(ev, MenuMarginLineType, MenuMarginDashDoubleDot,
#ifdef _PLATFORM_OS2_
         _fMarginLine==LINETYPE_DASHDOUBLEDOT);
#endif
#ifdef _PLATFORM_WIN32_
         _fMarginLine==PS_DASHDOTDOT);
#endif
      _fMenuBar->CheckMenuItem(ev, MenuMarginLineType, MenuMarginSolid,
#ifdef _PLATFORM_OS2_
         _fMarginLine==LINETYPE_SOLID);
#endif
#ifdef _PLATFORM_WIN32_
         _fMarginLine==PS_SOLID);
#endif

      _fMenuBar->CheckMenuItem(ev, MenuGridLineType, MenuGridDots,
#ifdef _PLATFORM_OS2_
         _fGridLine==LINETYPE_DOT);
#endif
#ifdef _PLATFORM_WIN32_
         _fGridLine==PS_DOT);
#endif
      _fMenuBar->CheckMenuItem(ev, MenuGridLineType, MenuGridDash,
#ifdef _PLATFORM_OS2_
         _fGridLine==LINETYPE_LONGDASH);
#endif
#ifdef _PLATFORM_WIN32_
         _fGridLine==PS_DASH);
#endif
      _fMenuBar->CheckMenuItem(ev, MenuGridLineType, MenuGridDashDot,
#ifdef _PLATFORM_OS2_
         _fGridLine==LINETYPE_DASHDOT);
#endif
#ifdef _PLATFORM_WIN32_
         _fGridLine==PS_DASHDOT);
#endif
      _fMenuBar->CheckMenuItem(ev, MenuGridLineType, MenuGridDashDoubleDot,
#ifdef _PLATFORM_OS2_
         _fGridLine==LINETYPE_DASHDOUBLEDOT);
#endif
#ifdef _PLATFORM_WIN32_
         _fGridLine==PS_DASHDOTDOT);
#endif
      _fMenuBar->CheckMenuItem(ev, MenuGridLineType, MenuGridSolid,
#ifdef _PLATFORM_OS2_
         _fGridLine==LINETYPE_SOLID);
#endif
#ifdef _PLATFORM_WIN32_
         _fGridLine==PS_SOLID);
#endif
    }
}


SOM_Scope void  SOMLINK PageLayoutFacetAdded(PageLayout *somSelf,
                                              Environment *ev,
                                             ODFacet* facet)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutFacetAdded");

    PageLayout_parent_BaseContainer_FacetAdded(somSelf, ev, facet);

    ODCanvas *canvas = facet->GetCanvas(ev);
    if (canvas && canvas->IsDynamic(ev)) { /* don't do when printing */
#ifdef SMART_DRAWING
       if (_fBackgroundShape==kODNULL) {
          _fBackgroundShape = facet->CreateShape(ev);
       } /* endif */

       if (_fVisiblePagesShape==kODNULL) {
          _fVisiblePagesShape = facet->CreateShape(ev);
       } /* endif */
#endif

/* Determine scaling factor (used in MaxPagesReached()) */
       ODTransform *frameXform = facet->AcquireFrameTransform(ev, kNoBias);

       ODPoint scale;
       frameXform->GetScale(ev, &scale);
       _fXScaleFactor = ((double) scale.x)/((double) 0x10000);
       _fYScaleFactor = ((double) scale.y)/((double) 0x10000);

       frameXform->Release(ev);

       ODFrame *frame = facet->GetFrame(ev);
       if (_fNeedToResizeDocShell) {
          if (frame->IsRoot(ev)) {
             _ResizeDocShell(ev, facet);
          } else {
             _FrameShapeChanged(ev, frame);
          } /* endif */
          _fNeedToResizeDocShell = kODFalse;
       } /* endif */
    } /* endif */
}


SOM_Scope void  SOMLINK PageLayoutFrameShapeChanged(PageLayout *somSelf,
                                                     Environment *ev,
                                                    ODFrame* frame)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutFrameShapeChanged");

    PageLayout_parent_BaseContainer_FrameShapeChanged(somSelf, ev, frame);

    _DetermineVisiblePages(ev, frame);
}


// -------------------------------------------------------------------------
// PageLayout --> ChangeNotification
// This is a hook for subclasses of BaseContainer so that they can know
// when anything changes with respect to the embedded parts
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         PageLayoutChangeNotification
                (
                PageLayout     *somSelf,
                Environment    *ev,
                ODULong         reason,
                ODFrame        *frame,
                ContentObject  *content,
                ODBoolean       bPropagate,
                ODUpdateID      updateID
                )
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutChangeNotification");

    ODBoolean adjust=kODFalse;

    if (content!=kODNULL) {
       adjust = _KeepEmbedWithinMargins(ev, content);
    } else {
       ALinkedList *itr = _GetEmbeddedObjects(ev);
       if (itr!=kODNULL) {
          ALink *item = itr->First(ev);
          if (item!=kODNULL) {
             ContentObject *cObj = (ContentObject *) item->Content(ev);
             while (cObj!=kODNULL) {
                if (_KeepEmbedWithinMargins(ev, cObj)) {
                   adjust = kODTrue;
                } /* endif */

                item = item->Next(ev);
                if (item!=kODNULL) {
                   cObj = (ContentObject *) item->Content(ev);
                } else {
                   cObj = kODNULL;
                } /* endif */
             } /* endwhile */
          } /* endif */
       } /* endif */
    } /* endif */

    if (adjust) {
       _CreateSelectionBorderShapes(ev, kODNULL);
       if (frame!=kODNULL) {
          frame->Invalidate(ev, kODNULL, kNoBias);
       } /* endif */
    } /* endif */

    PageLayout_parent_BaseContainer_ChangeNotification(somSelf, ev,
       reason, frame, content, bPropagate, updateID);
}


// -------------------------------------------------------------------------
// PageLayout --> DrawContents
//
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         PageLayoutDrawContents
                (
                PageLayout      *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet,          // in
                ODShape         *invalidShape
                )
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutDrawContents");

    ODCanvas* canvas = facet->GetCanvas(ev);
    ODFrame* displayFrame = facet->GetFrame(ev);

#ifndef SMART_DRAWING
    ODShape *frameShape = ODCopyAndRelease(ev,
//     displayFrame->AcquireFrameShape(ev, canvas));
       displayFrame->AcquireUsedShape(ev, canvas));

    ODTransform *internalXform = displayFrame->AcquireInternalTransform(ev, canvas);
    frameShape->InverseTransform(ev, internalXform);
    ODReleaseObject(ev, internalXform);

    ODRect rect;
    frameShape->GetBoundingBox(ev, &rect);
    frameShape->Release(ev);
    Rect frameRect;

    // Convert to Window's rectangle
#ifdef _PLATFORM_WIN32_
       SetRect(&frameRect,
          FixedToInt(rect.left),
          FixedToInt(rect.top),
          FixedToInt(rect.right),
          FixedToInt(rect.bottom));
#endif //_PLATFORM_WIN32_

#ifdef _PLATFORM_OS2_
       WinSetRect((HAB) 0, &frameRect,
          FixedToInt(rect.left),
          FixedToInt(rect.bottom),
          FixedToInt(rect.right),
          FixedToInt(rect.top));
#endif //_PLATFORM_OS2_
#endif //SMART_SCROLLING

    HDRAW DrawingSurface;
    CFocus focus(facet, invalidShape, &DrawingSurface);

//  ODBoolean Printing = !(canvas->IsDynamic(ev));
    ODBoolean Printing = NULL;
#ifdef _PLATFORM_OS2_
    Printing = canvas->HasPlatformPrintJob(ev, kODPM);
#endif
#ifdef _PLATFORM_WIN32_
    if (canvas)
      Printing = canvas->HasPlatformPrintJob(ev, kODWin32);
#endif
    ODBoolean DrawAdornments = !(Printing && displayFrame->IsRoot(ev));

#if defined(_PLATFORM_OS2_)

    if (Printing) {  // Setup Font for printing
       HDC hDC = GpiQueryDevice(DrawingSurface);
       LONG resolution;
       DevQueryCaps( hDC, CAPS_HORIZONTAL_FONT_RES, 1L, &resolution);

       SIZEF sizfCharBox;
       //  sizfCharBox.cx = MAKEFIXED ((4)*resolution /72, 0);
       //  sizfCharBox.cy = MAKEFIXED ((4)*resolution /72, 0);
       sizfCharBox.cx = MAKEFIXED (8, 0);
       sizfCharBox.cy = MAKEFIXED (8, 0);
       GpiSetCharBox(DrawingSurface,&sizfCharBox);        // scaling
    } /* endif */

    // set hps to RGB mode!
    GpiCreateLogColorTable(DrawingSurface, 0, LCOLF_RGB, 0, 0, NULL);

    if (DrawAdornments && !_fIsTransparent) {
       GpiSetColor(DrawingSurface, _fBackgroundColor);

#ifdef SMART_DRAWING
       ODTransform *xform = facet->AcquireContentTransform(ev, kNoBias);
       ODShape *transformedShape = _fBackgroundShape->Copy(ev);
       transformedShape->Transform(ev, xform);

       HRGN BackgroundRegion = _fBackgroundShape->GetRegion(ev);
       GpiPaintRegion(DrawingSurface, BackgroundRegion);

       transformedShape->Release(ev);
       xform->Release(ev);
#else
       POINTL pos = {frameRect.xLeft, frameRect.yBottom};
       GpiMove(DrawingSurface, &pos);
       pos.x = frameRect.xRight; pos.y = frameRect.yTop;
       GpiBox(DrawingSurface, DRO_FILL, &pos, 0, 0);
#endif
    } /* endif */

#elif defined(_PLATFORM_WIN32_)
    if (Printing) {  // Setup Font for printing
       HFONT newFont = GetStockObject(ANSI_FIXED_FONT);
       SelectObject(DrawingSurface, newFont);
    } /* endif */

    if (DrawAdornments && !_fIsTransparent) {
       // Create a solid brush
       HBRUSH newBrush = CreateSolidBrush(_fBackgroundColor);

       // Fill the rectangle with the brush
       FillRect(DrawingSurface, &frameRect, newBrush);

       // Get rid of the brush
       DeleteObject(newBrush);
    } /* endif */

    SetTextColor(DrawingSurface, _fPageStringColor);
    SetBkMode(DrawingSurface, TRANSPARENT);
#endif  // end WIN32 specific

#ifdef SMART_DRAWING
    if (!_fIsTransparent &&
        (DrawAdornments || (Printing && _fPrintPageColor))) {
#ifdef _PLATFORM_OS2_
       ODTransform *xform = facet->AcquireContentTransform(ev, kNoBias);
       ODShape *transformedShape = _fVisiblePagesShape->Copy(ev);
       transformedShape->Transform(ev, xform);

       HRGN VisiblePagesRegion = _fVisiblePagesShape->GetRegion(ev);

       GpiPaintRegion(DrawingSurface, VisiblePagesRegion);

       transformedShape->Release(ev);
       xform->Release(ev);
#endif //_PLATFORM_OS2_
    } /* endif */
#endif //SMART_DRAWING

    short FirstPage = Printing ? 0 : _fFirstVisiblePage;
    short LastPage = Printing ? _fNumberOfPages-1 : _fLastVisiblePage;

//  for (short index=0; index<_fNumberOfPages; index++)
    for (short index=FirstPage; index<=LastPage; index++)
    {
       _DrawPage(ev, DrawingSurface, index, Printing, DrawAdornments);
    } /* endfor */

    return kODTrue;
}


// -------------------------------------------------------------------------
// PageLayout --> ReadContents
//
//      Read part's content from storage.
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         PageLayoutReadContents
                (
                PageLayout   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *fromSU,          // in
                BCCloneInfo     *cloneInfo,
                ODULong         readKind
                )

{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout", "PageLayoutReadContents");

    // Read in our parent's contents first
    PageLayout_parent_BaseContainer_ReadContents(somSelf, ev,
                                                 fromSU,
                                                 cloneInfo,
                                                 readKind);

    if (ODSUExistsThenFocus(ev, fromSU, kODPropContents, kPartKindName)) {
       StorageUnitGetValue(fromSU, ev, sizeof(short), &_fNumberOfPages);

       StorageUnitGetValue(fromSU, ev, sizeof(COLORREF), &_fBackgroundColor);
       StorageUnitGetValue(fromSU, ev, sizeof(COLORREF), &_fPageColor);
       StorageUnitGetValue(fromSU, ev, sizeof(COLORREF), &_fPageStringColor);
       StorageUnitGetValue(fromSU, ev, sizeof(COLORREF), &_fRulerColor);
       StorageUnitGetValue(fromSU, ev, sizeof(COLORREF), &_fHorzMarginColor);
       StorageUnitGetValue(fromSU, ev, sizeof(COLORREF), &_fVertMarginColor);
       StorageUnitGetValue(fromSU, ev, sizeof(COLORREF), &_fGridColor);

       StorageUnitGetValue(fromSU, ev, sizeof(ODBoolean), &_fShowHorzRuler);
       StorageUnitGetValue(fromSU, ev, sizeof(ODBoolean), &_fShowVertRuler);
       StorageUnitGetValue(fromSU, ev, sizeof(ODBoolean), &_fShowHorzMargins);
       StorageUnitGetValue(fromSU, ev, sizeof(ODBoolean), &_fShowVertMargins);
       StorageUnitGetValue(fromSU, ev, sizeof(ODBoolean), &_fShowGrid);

       StorageUnitGetValue(fromSU, ev, sizeof(long), &_fPageNumberPosition);
       StorageUnitGetValue(fromSU, ev, sizeof(short), &_fRulerUnits);
       StorageUnitGetValue(fromSU, ev, sizeof(short), &_fMarginLine);
       StorageUnitGetValue(fromSU, ev, sizeof(short), &_fGridLine);

       int len=0;
       StorageUnitGetValue(fromSU, ev, sizeof(int), &len);
       if (len>0) {
          StorageUnitGetValue(fromSU, ev, len, &_fHeaderText);
       } /* endif */

       StorageUnitGetValue(fromSU, ev, sizeof(int), &len);
       if (len>0) {
          StorageUnitGetValue(fromSU, ev, len, &_fFooterText);
       } /* endif */

       StorageUnitGetValue(fromSU, ev, sizeof(int), &len);
       if (len>0) {
          StorageUnitGetValue(fromSU, ev, len, &_fCurrentPrinterQueueName);
       } /* endif */

       if (_fPrintExt!=kODNULL) {
          if (len>0) {
             _fPrintExt->QuerySelectedPrinter(ev, _fCurrentPrinterQueueName,
                kODFalse);
          } /* endif */
          _fPrintExt->SetNumberOfPages(ev, _fNumberOfPages);
       } /* endif */

       if (_fScrollExt!=kODNULL) {
          _fScrollExt->SetScrollableDimensions(ev, kODNULL, _fTotalPageWidth,
             _fTotalPageHeight*_fNumberOfPages);
       } /* endif */
    } /* endif */
}


// -------------------------------------------------------------------------
// PageLayout --> WriteContents
//
//      Writes part's content to storage.
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         PageLayoutWriteContents
                (
                PageLayout    *somSelf,       // in
                Environment   *ev,            // in
                ODStorageUnit *toSU,          // in
                BCCloneInfo   *cloneInfo,
                ODULong       writeKind
                )

{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout", "PageLayoutWriteContents");

    // Read in our parent's contents first
    PageLayout_parent_BaseContainer_WriteContents(somSelf, ev,
                                                  toSU,
                                                  cloneInfo,
                                                  writeKind);

    ODSUForceFocus(ev, toSU, kODPropContents, kPartKindName);
    StorageUnitSetValue(toSU, ev, sizeof(short), &_fNumberOfPages);

    StorageUnitSetValue(toSU, ev, sizeof(COLORREF), &_fBackgroundColor);
    StorageUnitSetValue(toSU, ev, sizeof(COLORREF), &_fPageColor);
    StorageUnitSetValue(toSU, ev, sizeof(COLORREF), &_fPageStringColor);
    StorageUnitSetValue(toSU, ev, sizeof(COLORREF), &_fRulerColor);
    StorageUnitSetValue(toSU, ev, sizeof(COLORREF), &_fHorzMarginColor);
    StorageUnitSetValue(toSU, ev, sizeof(COLORREF), &_fVertMarginColor);
    StorageUnitSetValue(toSU, ev, sizeof(COLORREF), &_fGridColor);

    StorageUnitSetValue(toSU, ev, sizeof(ODBoolean), &_fShowHorzRuler);
    StorageUnitSetValue(toSU, ev, sizeof(ODBoolean), &_fShowVertRuler);
    StorageUnitSetValue(toSU, ev, sizeof(ODBoolean), &_fShowHorzMargins);
    StorageUnitSetValue(toSU, ev, sizeof(ODBoolean), &_fShowVertMargins);
    StorageUnitSetValue(toSU, ev, sizeof(ODBoolean), &_fShowGrid);

    StorageUnitSetValue(toSU, ev, sizeof(long), &_fPageNumberPosition);
    StorageUnitSetValue(toSU, ev, sizeof(short), &_fRulerUnits);
    StorageUnitSetValue(toSU, ev, sizeof(short), &_fMarginLine);
    StorageUnitSetValue(toSU, ev, sizeof(short), &_fGridLine);

    int len=strlen(_fHeaderText);
    StorageUnitSetValue(toSU, ev, sizeof(int), &len);
    if (len>0) {
       StorageUnitSetValue(toSU, ev, len, &_fHeaderText);
    } /* endif */

    len=strlen(_fFooterText);
    StorageUnitSetValue(toSU, ev, sizeof(int), &len);
    if (len>0) {
       StorageUnitSetValue(toSU, ev, len, &_fFooterText);
    } /* endif */

    if (_fPrintExt!=kODNULL) {
       _fCurrentPrinterQueueName =
          _fPrintExt->GetCurrentPrinterQueuePhysicalName(ev);
    } /* endif */

    if (_fCurrentPrinterQueueName!=kODNULL) {
       len=strlen(_fCurrentPrinterQueueName);
    } else {
       len=0;
    } /* endif */
    StorageUnitSetValue(toSU, ev, sizeof(int), &len);
    if (len>0) {
       StorageUnitSetValue(toSU, ev, len, &_fCurrentPrinterQueueName);
    } /* endif */
}


// -------------------------------------------------------------------------
// PageLayout --> ReadKindInfo
//
//      Reads Base Container kind from the storage unit.
//
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         PageLayoutReadKindInfo
                (
                PageLayout    *somSelf,       // in
                Environment   *ev,            // in
                ODStorageUnit *fromSU         // in
                )
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout", "PageLayoutReadKindInfo");

    ODBoolean bExists = kODFalse;

    try {

    bExists = fromSU->Exists(ev, kODPropContents, kPartKindName, 0);

    } // end of try block
    catch (...) {}

    return bExists;
}


// -------------------------------------------------------------------------
// PageLayout --> WriteKindInfo
//
//      Writes Base Container kind into the storage unit.
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         PageLayoutWriteKindInfo
                (
                PageLayout    *somSelf,       // in
                Environment   *ev,            // in
                ODStorageUnit *toSU           // in
                )
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout", "PageLayoutWriteKindInfo");

    try {

         PageLayout_parent_BaseContainer_WriteKindInfo(somSelf, ev, toSU);
         InitPropVal(ev, toSU, kODPropContents, kPartKindName);
         InitPropVal(ev, toSU, kODPropPreferredKind, kPartKindName);

    } // end of try block
    catch (...) {}
}


// -------------------------------------------------------------------------
// PageLayout--> WriteIconToSU
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         PageLayoutWriteIconToSU
                (
                PageLayout       *somSelf, // in
                Environment      *ev,      // in
                ODStorageUnit    *toSU     // in
                )
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout", "PageLayoutWritePartInfo");

#ifdef _PLATFORM_OS2_
// Customized icon support for OS2.

     ULONG cbIconSize;
     PBYTE pIconData = NULL;

     if ( !DosQueryResourceSize(_fResources, RT_POINTER, PAGEICON, &cbIconSize) &&
         !DosGetResource(_fResources, RT_POINTER, PAGEICON, (PPVOID)&pIconData)  )
     {
        InitPropVal(ev, toSU, kODPropIconFamily, kODIconFamily);
        StorageUnitSetValue(toSU, ev, cbIconSize, (ODValue) pIconData);
        DosFreeResource(pIconData);
     } /* endif */

#endif // _PLATFORM_OS2_
}


// -------------------------------------------------------------------------
// PageLayout --> Initialize
//
//      Common code needed by the InitPart* methods.
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         PageLayoutInitialize
                (
                PageLayout      *somSelf,       // in
                Environment     *ev,             // in
                ODPart          *partWrapper    // in
                )
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout", "PageLayoutInitialize");

    _fPartWrapper = partWrapper;

#ifdef _PLATFORM_OS2_
    DosQueryModuleHandle(kPagePartMRIFileName, &_fResources);
#endif

#ifdef _PLATFORM_WIN32_
    _fResources = GetModuleHandle(kPagePartMRIFileName);
#endif

    MyResources = _fResources; /* for use by helper functions */

    if (_fResources==kODNULL) {
       WarningBox(HWND_DESKTOP, WARNm, ResourceErrorMsg);
    } /* endif */

    PageLayout_parent_BaseContainer_Initialize(somSelf, ev, partWrapper);

    if (_HasExtension(ev,kODPrintExtension)) {
       _fPrintExt = (PageLayoutPrintExtension *) _AcquireExtension(ev, kODPrintExtension) ;
       _EnablePrinting(ev, kODTrue, _fCurrentPrinterQueueName);
    }

    if (_HasExtension(ev, kODScrollExtension)) {
       _fScrollExt = (ODScrollExtension *) _AcquireExtension(ev, kODScrollExtension) ;
       _EnableScrolling(ev, kODTrue, _fTotalPageWidth, _fTotalPageHeight*_fNumberOfPages);
    }

    _CreateMenuBar(ev);
}

//--------------------------------------------------------------------------
// ReleaseAll
//
// This method is called prior to the object destructor being invoked.
// It must release all references to other objects.  If we are the Factory
// for the object we should also ensure the object is properly deleted
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         PageLayoutReleaseAll
                (
                PageLayout      *somSelf,       // in
                Environment     *ev             // in
                )
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutReleaseAll");

    //--------------------------------------------------------------------
    // Release the extensions we acquired in the initialize routine.
    // Put it in a try/catch block in case of failure, but ignore the
    // error since we're leaving.
    //--------------------------------------------------------------------
    if (_fScrollExt) {
       try {
         _fScrollExt->Release(ev);
         _fScrollExt = kODNULL ;
       }
       catch (ODException _exception) {
          PRINT("SOM exception occurred in TextPart::ReleaseAll\n");
          // Clear the exception, in case we got one
          SetErrorCodeEv(ev, kODNoError);
       }
    }

    if (_fPrintExt) {
       try {
         _fPrintExt->Release(ev);
         _fPrintExt = kODNULL ;
       }
       catch (ODException _exception) {
          PRINT("SOM exception occurred in TextPart::ReleaseAll\n");
          // Clear the exception, in case we got one
          SetErrorCodeEv(ev, kODNoError);
       }
    }

    PageLayout_parent_BaseContainer_ReleaseAll(somSelf, ev);

}


SOM_Scope void  SOMLINK PageLayoutsomInit(PageLayout *somSelf)
{
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutsomInit");

    PageLayout_parent_BaseContainer_somInit(somSelf);

    _fPrintExt = kODNULL;
    _fScrollExt = kODNULL;

    _fCurrentPrinterQueueName = kODNULL;

    _fShowHorzRuler = kODTrue;
    _fShowVertRuler = kODTrue;
    _fShowHorzMargins = kODFalse;
    _fShowVertMargins = kODFalse;
    _fShowGrid = kODFalse;

    _fPrintPageColor = kODFalse;

    _fPageNumberPosition = BOTTOM_CENTER;

#ifdef _PLATFORM_OS2_
    _fGridLine = LINETYPE_DOT;
    _fMarginLine = LINETYPE_LONGDASH;
#endif

#ifdef _PLATFORM_WIN32_
    _fGridLine = PS_DOT;
    _fMarginLine = PS_DASH;
#endif

    _fPageUnitMeasure = INCHES;
    _fMarginsUnitMeasure = INCHES;
    _fGridUnitMeasure = INCHES;

    _fHeaderFooterStartOn = 1;
    strcpy(_fHeaderText, "");
    strcpy(_fFooterText,"");

    _fPageNumberStartOn = 1;
    _fPageNumberStartWith = 1;

    _fNumberOfPages = 1;

    _fGridSpacing = GRID_SPACING;

    _fRulerUnits = INCHES;

    _fPageWidth = PAGE_WIDTH;
    _fPageHeight = PAGE_HEIGHT;

    _fLeftPageOffset = LEFT_PAGE_OFFSET;
    _fRightPageOffset = RIGHT_PAGE_OFFSET;
    _fBottomPageOffset = BOTTOM_PAGE_OFFSET;
    _fTopPageOffset = TOP_PAGE_OFFSET;

    _fLeftMargin = LEFT_MARGIN;
    _fRightMargin = RIGHT_MARGIN;
    _fBottomMargin = BOTTOM_MARGIN;
    _fTopMargin = TOP_MARGIN;

    _fPageColor = 0x00FFFFFF;              // WHITE
    _fPageStringColor = 0x00000000;        // Black
    _fRulerColor = 0x00000000;             // Black

#ifdef _PLATFORM_OS2_
    _fBackgroundColor = 0x00CCCCCC;        // PaleGray
    _fHorzMarginColor =  0x00FF0000;       // Red
    _fVertMarginColor =  0x00FF0000;       // Red
#endif

#ifdef _PLATFORM_WIN32_
    _fBackgroundColor = 0x00C0C0C0;        // PaleGray
    _fHorzMarginColor =  0x000000FF;       // Red
    _fVertMarginColor =  0x000000FF;       // Red
#endif

    _fGridColor = 0x00555555;              // DarkGray

    strcpy(_fCurrentFont, kPagePartDefaultFont);

    _fTotalPageWidth = _fLeftPageOffset+_fPageWidth+_fRightPageOffset;
    _fTotalPageHeight = _fBottomPageOffset+_fPageHeight+_fTopPageOffset;

    _fFirstVisiblePage = 0;
    _fLastVisiblePage = 0;

    _fXScaleFactor = 1.0;
    _fYScaleFactor = 1.0;

    _fNeedToResizeDocShell = kODTrue;

    _fSameColorAsContainer = kODTrue;

    _fBackgroundShape = kODNULL;
    _fVisiblePagesShape = kODNULL;
}


SOM_Scope void  SOMLINK PageLayoutsomUninit(PageLayout *somSelf)
{
    /* PageLayoutData *somThis = PageLayoutGetData(somSelf); */
    PageLayoutData *somThis = PageLayoutGetData(somSelf);
    PageLayoutMethodDebug("PageLayout","PageLayoutsomUninit");

    PageLayout_parent_BaseContainer_somUninit(somSelf);
}


/*****************************************************************************
 M_PageLayout clsGetODPartHandlerName( M_PageLayout *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope ISOString  SOMLINK M_PageLayoutclsGetODPartHandlerName
                 (M_PageLayout *somSelf,  Environment *ev)
{
    /* M_PageLayoutData *somThis = M_PageLayoutGetData(somSelf); */
    M_PageLayoutMethodDebug("M_PageLayout","M_PageLayoutclsGetODPartHandlerName");

    string handlerName = (string)SOMMalloc(strlen(kPartHandlerName)+1);
    strcpy(handlerName,kPartHandlerName);


    return (ISOString) handlerName;
}

/*****************************************************************************
 M_PageLayout --> clsGetODPartHandlerDisplayName( M_PageLayout *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope string  SOMLINK M_PageLayoutclsGetODPartHandlerDisplayName(M_PageLayout *somSelf,
                                                                         Environment *ev)
{
    /* M_PageLayoutData *somThis = M_PageLayoutGetData(somSelf); */
    M_PageLayoutMethodDebug("M_PageLayout","M_PageLayoutclsGetODPartHandlerDisplayName");

    string handlerName = (string)SOMMalloc(strlen(kPartHandlerDisplayName)+1);
    strcpy(handlerName,kPartHandlerDisplayName);


    return (ISOString) handlerName;
}

/*****************************************************************************
 M_PageLayout --> clsGetODPartKinds( M_PageLayout *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope _IDL_SEQUENCE_PartKindInfo  SOMLINK M_PageLayoutclsGetODPartKinds(M_PageLayout *somSelf,
                                                                                Environment *ev)
{
    /* M_PageLayoutData *somThis = M_PageLayoutGetData(somSelf); */
    M_PageLayoutMethodDebug("M_PageLayout","M_PageLayoutclsGetODPartKinds");

    _IDL_SEQUENCE_PartKindInfo partKindInfo;

    // Create structure PartKindInfo  and allocate memory for its fields
    PartKindInfo * info       =  (PartKindInfo *)SOMMalloc(sizeof(PartKindInfo));
    info->partKindName        =  (ISOString) SOMMalloc(strlen(kPartKindName) + 1);
    info->partKindDisplayName =  (string)SOMMalloc(strlen(kPartKindDisplayName)+1);
    info->filenameFilters     =  (string)SOMMalloc(strlen("")+1);
    info->filenameTypes       =  (string)SOMMalloc(strlen("")+1);
    info->categories          =  (string)SOMMalloc(strlen(kPartCategoryName)+1);
    info->categoryDisplayName =  (string)SOMMalloc(strlen(kPartCategoryDisplayName)+1);
    info->objectID            =  (string)SOMMalloc(strlen("")+1);

    // Copy the information into the structure
    strcpy(info->partKindName , kPartKindName);
    strcpy(info->partKindDisplayName, kPartKindDisplayName);
    strcpy(info->filenameFilters, "");
    strcpy(info->filenameTypes, "");
    strcpy(info->categories, kPartCategoryName);
    strcpy(info->categoryDisplayName, kPartCategoryDisplayName);
    strcpy(info->objectID, "");

    partKindInfo._maximum = 1;
    partKindInfo._length = 1;
    partKindInfo._buffer = info;

    return partKindInfo;
}

/*****************************************************************************
 M_PageLayout --> clsGetODPartGetOLE2ClassID( M_PageLayout *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope string  SOMLINK M_PageLayoutclsGetOLE2ClassId(M_PageLayout *somSelf,
                                                            Environment *ev)
{
    /* M_PageLayoutData *somThis = M_PageLayoutGetData(somSelf); */
    M_PageLayoutMethodDebug("M_PageLayout","M_PageLayoutclsGetOLE2ClassId");

    char *kID = "{f884b7a0-2de8-11d0-b6aa-08005aceddb4}";

    string OLE2ClassID = (string)SOMMalloc(strlen(kID)+1);
    strcpy(OLE2ClassID,kID);

    return OLE2ClassID;
}

/*****************************************************************************
 M_PageLayout --> clsGetODPartGetWindowsIconFileName ( M_PageLayout *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope string  SOMLINK M_PageLayoutclsGetWindowsIconFileName(M_PageLayout *somSelf,
                                                                    Environment *ev)
{
    /* M_PageLayoutData *somThis = M_PageLayoutGetData(somSelf); */
    M_PageLayoutMethodDebug("M_PageLayout","M_PageLayoutclsGetWindowsIconFileName");

    string windowsIcon = (string)SOMMalloc(strlen(kWindowsIcon)+1);
    strcpy(windowsIcon, kWindowsIcon);

    return windowsIcon;
}

