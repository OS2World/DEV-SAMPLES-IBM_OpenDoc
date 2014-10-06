/* @(#) 1.12 com/src/samples/utils/iodprint.cpp, odpagepart, od96os2, odos29712d 3/7/97 13:08:55 [3/21/97 17:48:15] */

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
	File:		IODPrint.cpp

	Contains:	Implementation of ODPrintExtension class.

	Owned by:	John Alcorn

	Copyright:	© 1996 by IBM, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	10/15/96	JWA		first checked in

	To Do:
	In Progress:
		
*/

#define _OD_DONT_IMPORT_CPP_
#define ODPrintExtension_Class_Source
#define VARIABLE_MACROS
#define METHOD_MACROS

#ifdef _PLATFORM_OS2_
#define INCL_PM
#define INCL_GPI
#define INCL_GPICIDS
#define INCL_GPIPRIMITIVES
#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_DEV
#define INCL_SPL
#define INCL_SPLDOSPRINT

#include <os2.h>

#define HDRAW HPS
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>

#define HDRAW HDC
#endif //_PLATFORM_WIN32_

#ifndef _ALTPOINT_
#include <AltPoint.h> //jwa - MUST be included BEFORE ODTypes.h (better ODPoint, ODRect)
#endif

#include <ODRes.h>
#include <ODTypes.h>
#include <ODUtils.h>
#include <ODDebug.h>
#include <ODExcept.h>

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

#ifndef SOM_ODContainer_xh
#include <ODCtr.xh>
#endif

#ifndef SOM_ODDocument_xh
#include <Document.xh>
#endif

#ifndef SOM_ODDraft_xh
#include <Draft.xh>
#endif

#ifndef SOM_ODStorageUnit_xh
#include <StorageU.xh>
#endif

#ifndef SOM_ODPart_xh
#include <Part.xh>
#endif

#ifndef SOM_ODHelp_xh
#include <ODHelp.xh>
#endif
//have to make following variables global, so that they can be used from within
//dialog window proc's (which don't have access to extension's instance data)
ODHelp *MyHelp = kODNULL;
HMODULE MyResources = kODNULL;
ODBoolean KeepPrinting = kODTrue;

#ifndef SOM_Module_xh5cStdProps_OpenDoc_StdProps_defined
#include <StdProps.xh>
#endif

#ifndef SOM_Module_xh5cStdTypes_OpenDoc_StdTypes_defined
#include <StdTypes.xh>
#endif

#include <stdio.h>
#include <iostream.h>
#include <IText.h>

#include "IODPrint.hpp"
#include "IODPrint.xih"


#ifdef _PLATFORM_OS2_
LONG CreatePrnList(HWND hwndListbox, char *currentQueueName );
void DestroyPrnList(HWND hwndListbox );
void ExtractPrnInfo(PPRQINFO3 ppiQueue,DEVOPENSTRUC *pdosPrinter );
void CenterWindow(HWND hwnd);

MRESULT EXPENTRY PrintingPageDlg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY PrintRangeProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY PrinterListDlg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
LRESULT CALLBACK PrintingPageDlg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

void WarningBox(HWND hwnd, int MSG, char *stg);
char* MRI(int id);
void ShowHelp(ODULong id);


//==============================================================================
// ODPrintExtension
//==============================================================================


//-------------------------------------------------------------------------
//  ODPrintExtension: PrinterSetup
//     Method to Allow user to choose a different Printer
//-------------------------------------------------------------------------

SOM_Scope ODBoolean  SOMLINK ODPrintExtensionPrinterSetup(ODPrintExtension *somSelf,
                                                    Environment *ev, HWND hwnd)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionPrinterSetup");

   ODBoolean PaperSizeChanged = kODFalse;

   //---------------------------------------------------------------------------
   // Present dialog listing all print queues
   // dialog returns the PRNLISTINFO (or NULL if Cancel was chosen)
   // of the chosen print queue
   //---------------------------------------------------------------------------

   char *oldQueueName = _GetCurrentPrinterQueuePhysicalName(ev);
   long oldPageWidth = _GetCurrentPrinterPageWidth(ev);
   long oldPageHeight = _GetCurrentPrinterPageHeight(ev);

#ifdef _PLATFORM_OS2_
   ULONG DialogValue = WinDlgBox(HWND_DESKTOP, hwnd, PrinterListDlg,
      MyResources, PrinterListBoxDlgRes, oldQueueName);

   if ((DialogValue!=kODNULL) && (DialogValue!=DID_ERROR)) {
//    if (_ppliInfo != kODNULL) free (_ppliInfo);
      _ppliInfo = (PPRNLISTINFO) DialogValue;
      _QuerySelectedPrinter(ev, kODNULL, kODTrue);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   PRINTDLG *dlgInfo = new PRINTDLG;
   memset(dlgInfo, 0, sizeof(PRINTDLG));

   dlgInfo->lStructSize = sizeof(PRINTDLG);
   dlgInfo->hwndOwner = hwnd;
   dlgInfo->Flags = PD_PRINTSETUP | PD_RETURNIC;

   ODBoolean rc = PrintDlg(dlgInfo);

   if (rc) {
//    _QuerySelectedPrinter(ev, kODNULL, kODTrue);
      _printDlg = dlgInfo;
#endif //_PLATFORM_WIN32_

//    draft->SetChangedFromPrev(ev);

      long newPageWidth = _GetCurrentPrinterPageWidth(ev);
      long newPageHeight = _GetCurrentPrinterPageHeight(ev);
      if ((newPageWidth!=oldPageWidth) || (newPageHeight!=oldPageHeight)) {
         PaperSizeChanged = kODTrue;
      } /* endif */

#ifdef _PLATFORM_OS2_
   } else {
      if (DialogValue==DID_ERROR) {
         short error = ERRORIDERROR(WinGetLastError(0));
         DosBeep(250,500);
      } /* endif */
#endif //_PLATFORM_OS2_
   } /* endif */

   return PaperSizeChanged;
}


//------------------------------------------------------------------------------
// ODPrintExtension: PrintDocument
//------------------------------------------------------------------------------

SOM_Scope ODBoolean  SOMLINK ODPrintExtensionPrintDocument
     	             (ODPrintExtension *somSelf, Environment *ev,
                     ODFrame* frame, ODEventData *event)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","PrintDocument");

    ODBoolean handled = kODTrue;

    handled = _HandlePrinting(ev, frame, kODNULL);

    if (!handled)
#ifdef _PLATFORM_OS2_
       WinMessageBox(HWND_DESKTOP, event->hwnd,
          (PSZ)"An error occurred in HandlePrinting()", (PSZ)"ODPrintExtension",
          0, MB_OK | MB_ERROR | MB_MOVEABLE);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
       MessageBox(event->hwnd, (PSZ)"An error occurred in HandlePrinting()",
          (PSZ)"ODPrintExtension", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
#endif //_PLATFORM_WIN32_

    return handled;
}



//-------------------------------------------------------------------------
//
//  Method to handle printing
//
//-------------------------------------------------------------------------

SOM_Scope ODBoolean  SOMLINK ODPrintExtensionHandlePrinting(ODPrintExtension *somSelf,
                                                       Environment *ev,
                                                      ODFrame* frame,
                                                      char *pszQueueName)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionHandlePrinting");

#ifdef _PLATFORM_OS2_
   ULONG           ul, cReturned, cTotal, cbNeeded, cForms;
   HAB             hab = WinQueryAnchorBlock(HWND_DESKTOP);
   DEVOPENSTRUC    dos; //=ppInfo->dosPrinter;
   PHCINFO         phcInfo, phc;
   LONG            i, rc;
   BOOL            fResult, bOK;
   CHAR            szWork[LEN_WORKSTRING], *pch, achQueueName[QUEUENAME_LENGTH], achDriverName[DRIVERNAME_LENGTH],
                   achSpoolerParams[40], achQueueProcParams[8];
   HPS             hpsPrinter;
   SIZEL           sizel;
#endif //_PLATFORM_OS2_

   CHAR            *pszTitle;
   HWND            hwndFrame = 0;
   ODRect          bounds;
   CHAR            *buf = new CHAR [80];
   HDC             hdcPrinter;
   PRNINFO         prnInfo;

   ODDocumentName title = ((ODPart *)somSelf->GetBase(ev))->GetStorageUnit(ev)->GetDraft(ev)   //[144299]
                                ->GetDocument(ev)->GetContainer(ev)->GetName(ev);

   if (title.text._length)
   {
      pszTitle = (char*)malloc(title.text._length + 1);
      pszTitle = GetITextCString((ODIText *)&title, pszTitle);        //[144299]
   }
   else
      pszTitle = strdup(MRI(UntitledDocumentMsg));

   ODWindow* window = frame->AcquireWindow(ev);
   if (window)
      hwndFrame = window->GetPlatformWindow(ev);

   ODReleaseObject(ev, window);

   ODBoolean response = _DisplayPrintDialog(ev, &prnInfo, hwndFrame, pszTitle);
   if (response==kODFalse) {
      return kODTrue; /* "Cancel" must have been chosen - this isn't an error */
   } /* endif */

#ifdef _PLATFORM_WIN32_
   _printDlg = prnInfo.printDlg;
#endif

#ifdef _PLATFORM_OS2_
   _QuerySelectedPrinter(ev, kODNULL, kODTrue);
#endif

   KeepPrinting = kODTrue;

#ifdef _PLATFORM_OS2_
   if ((_cForms == 0) || (_pForms ==0)) //This means not vaild printer
   {
      WarningBox(hwndFrame, ERRm, MRI(PrintFailureMsg));
      return kODFalse;
   }

   _PrintHWND = WinLoadDlg(HWND_DESKTOP, hwndFrame, PrintingPageDlg,
                   MyResources, PrintingPage, NULL);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if ((prnInfo.printDlg==0) || (prnInfo.hdc==0)) //This means not valid printer
   {
      WarningBox(hwndFrame, ERRm, MRI(PrintFailureMsg));
      return kODFalse;
   }

// _PrintHWND = CreateDialog(MyResources, MAKEINTRESOURCE(PrintingPage),
//                 hwndFrame, (LPARAM) PrintingPageDlg);
#endif //_PLATFORM_WIN32_

   if (_PrintHWND != NULL)
   {
     ODBoolean rcc;
     strcpy(buf, MRI(InitializingMsg));

     char *QueueDisplayName = _GetCurrentPrinterQueueDisplayName(ev);
#ifdef _PLATFORM_OS2_
     rcc = WinSetDlgItemText(_PrintHWND, PrintQueueName, QueueDisplayName);
     rcc = WinSetDlgItemText(_PrintHWND, PrintPageNum, buf);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
     rcc = SetDlgItemText(_PrintHWND, PrintQueueName, QueueDisplayName);
     rcc = SetDlgItemText(_PrintHWND, PrintPageNum, buf);
#endif //_PLATFORM_WIN32_
   }

   long clipWidth = _GetCurrentPrinterClipWidth(ev);
   long clipHeight = _GetCurrentPrinterClipHeight(ev);

#ifdef _PLATFORM_OS2_
   phc = &_pForms[_GetCurrentPrinterForm(ev)];

   //---------------------------------------------------------------------------
   // Determine the bounds of the root facet in OD coords.
   //---------------------------------------------------------------------------

     bounds.left   = bounds.bottom = 0;
     bounds.right  = clipWidth*0x10000;
     bounds.top    = clipHeight*0x10000;

   //---------------------------------------------------------------------------
   // Build the Device Context for the DevOpenDC.
   //---------------------------------------------------------------------------

   short copies = 1;
   if (prnInfo.pRange!=kODNULL) {
      copies = prnInfo.pRange->usCopies;
   } /* endif */

   sprintf(achQueueProcParams, "COP=%d", copies);
   sprintf(achSpoolerParams, "FORM=%s", phc->szFormname);

   memset( &sizel, 0, sizeof(sizel));
   memcpy(&dos, &(_ppliInfo->dosPrinter), sizeof(DEVOPENSTRUC));

   dos.pszQueueProcParams = achQueueProcParams;
   dos.pszSpoolerParams = achSpoolerParams;

   //-----------------------------------------------------------------------
   //  Open Device Context and Associate a Presentation Space with it.
   //-----------------------------------------------------------------------

   hdcPrinter = DevOpenDC(  hab, OD_QUEUED, "*", 9, (PDEVOPENDATA)&dos, 0);
   hpsPrinter = GpiCreatePS( hab, hdcPrinter, &sizel, PU_PELS | GPIA_ASSOC);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if (prnInfo.printDlg && prnInfo.printDlg->hDC) {
      hdcPrinter = prnInfo.printDlg->hDC;
   } else {
      return kODFalse;
   } /* endif */

   //---------------------------------------------------------------------------
   // Determine the bounds of the root facet in OD coords.
   //---------------------------------------------------------------------------

     bounds.left   = bounds.top = 0;
     bounds.right  = clipWidth*0x10000;
     bounds.bottom = clipHeight*0x10000;
#endif //_PLATFORM_WIN32_

   //-----------------------------------------------------------------------
   //  Start the printing.
   //-----------------------------------------------------------------------

#ifdef _PLATFORM_OS2_
   DevEscape(hdcPrinter, DEVESC_STARTDOC, strlen(pszTitle), (PBYTE)pszTitle, 0, 0);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   DOCINFO info;
   info.cbSize = sizeof(DOCINFO);
   info.lpszDocName = pszTitle;
   info.lpszOutput = kODNULL;
   info.lpszDatatype = kODNULL;
   info.fwType = 0;

   StartDoc(hdcPrinter, &info);
#endif //_PLATFORM_WIN32_

   prnInfo.bounds = bounds;
   prnInfo.hdc = hdcPrinter;

#ifdef _PLATFORM_OS2_
   prnInfo.hps = hpsPrinter;
   prnInfo.phcInfo = phc;

   prnInfo.printDest.cb = sizeof(PRINTDEST);          // Size of struct
   prnInfo.printDest.lType = OD_QUEUED;               // Type of dev context
   prnInfo.printDest.pszToken = "*";                  // Dev-info token
   prnInfo.printDest.pdopData = (PDEVOPENDATA)&dos;   // Open dev context data
   prnInfo.printDest.fl = 0;                          // Flags
   prnInfo.printDest.pszPrinter = dos.pszLogAddress;  //pqi->pszPrinters;   // Name of printer
#endif //_PLATFORM_OS2_

   ODBoolean success = _PrintPages(ev, frame, &prnInfo); // Go print it!

   //-----------------------------------------------------------------------
   //  End the Printing and Cleanup everything.
   //-----------------------------------------------------------------------

#ifdef _PLATFORM_OS2_
   if (success) {
      DevEscape(hdcPrinter, DEVESC_ENDDOC, 0, 0, 0, 0);
   } else {
      DevEscape(hdcPrinter, DEVESC_ABORTDOC, 0, 0, 0, 0);
   } /* endif */

   GpiAssociate(hpsPrinter, 0);
   GpiDestroyPS(hpsPrinter);

   DevCloseDC(hdcPrinter);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if (success) {
      EndDoc(hdcPrinter);
   } else {
      AbortDoc(hdcPrinter);
   } /* endif */
#endif //_PLATFORM_WIN32_

   if (_PrintHWND != NULL)
   {
#ifdef _PLATFORM_OS2_
      WinDismissDlg(_PrintHWND, kODTrue);
      WinDestroyWindow(_PrintHWND);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
      EndDialog(_PrintHWND, kODTrue);
      DestroyWindow(_PrintHWND);
#endif //_PLATFORM_WIN32_

      _PrintHWND = NULL;
   }

   //-----------------------------------------------------------------------
   // Free the buffer allocated for SplEnumQueue call
   //-----------------------------------------------------------------------

// free(phcInfo);
// free(pqi);

   free(pszTitle);

   return kODTrue;
}


//-------------------------------------------------------------------------
//
//  This Method handles printing a Single Page
//
//-------------------------------------------------------------------------

SOM_Scope ODBoolean  SOMLINK ODPrintExtensionPrintPage(ODPrintExtension *somSelf,
                                             Environment *ev,
                                            ODFacet* prFacet,
                                            PRNINFO* pPI,
                                            ODBoolean lastPage)
{
   ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
   ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionPrintPage");

   if (!KeepPrinting) { /* If "Cancel" was chosen, this would be kODFalse */
      return kODFalse;
   } /* endif */

   ODPoint scale(0x10000, 0x10000);

#ifdef _PLATFORM_OS2_
   //-----------------------------------------------------------------------
   //
   // Calculate scaling factor for extenal transform of root facet.
   // Scale calculated using the following formula (for the x factor):
   //
   //                (pel)              xPels         (pel)   25.4 (mm/inch)
   // scaling factor ----- = ------------------------ ----- * ---- ---------
   //                (pt)    (xRightClip - xLeftClip) (mm)    72.0 (pt/inch)
   //
   // Note: This is so complicated because OS/2 returns clipping info in
   //       millimeters (which we have to then convert), and is much simpler
   //       on the WIN32 platform (see the _PLATFORM_WIN32_ section below),
   //       since Windows give you the number of pels per inch directly.
   //
   //-----------------------------------------------------------------------

   scale.x = (ODCoordinate)((float)pPI->phcInfo->xPels
                            / (float)(pPI->phcInfo->xRightClip -
                                      pPI->phcInfo->xLeftClip)
                            * 25.4 / 72.0 * 65536.0);

   scale.y = (ODCoordinate)((float)pPI->phcInfo->yPels
                            / (float)(pPI->phcInfo->yTopClip -
                                      pPI->phcInfo->yBottomClip)
                            * 25.4 / 72.0 * 65536.0);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   //-----------------------------------------------------------------------
   //
   // Calculate scaling factor for extenal transform of root facet.
   // Scale calculated using the following formula (for the x factor):
   //
   //                (pel)   xDPI (pel/inch)
   // scaling factor ----- = ---- ----------
   //                (pt)    72.0 (pt/inch)
   //
   //-----------------------------------------------------------------------

   float xDPI = GetDeviceCaps(pPI->hdc, LOGPIXELSX);
   float yDPI = GetDeviceCaps(pPI->hdc, LOGPIXELSY);

   scale.x = (ODCoordinate) (xDPI/72.0*65536.0);
   scale.y = (ODCoordinate) (yDPI/72.0*65536.0);
#endif //_PLATFORM_WIN32_

   ODFrame* prFrame    = prFacet->GetFrame(ev);
   ODShape* frameShape = prFrame->AcquireFrameShape(ev, kNoBias);

   ODRect bbox;
   frameShape->GetBoundingBox(ev, &bbox); //bbox is size of frame rect

   ODTransform* xtransform = prFacet->CreateTransform(ev);
   xtransform->SetOffset(ev, &pPI->offset);      //Offset points to page origin

   ODShape* clipshape = prFacet->CreateShape(ev);
   clipshape->SetRectangle(ev, &pPI->bounds);    //Clipshape = Page Size

   clipshape->Transform(ev, xtransform);
   clipshape->Intersect(ev, frameShape);
   ODReleaseObject(ev, frameShape);
   ODShape* invalshape = clipshape->Copy(ev);

   xtransform->Invert(ev);
   xtransform->ScaleBy(ev, &scale);             //see mess above for scaling factor

   prFacet->ChangeGeometry(ev, clipshape, xtransform, kNoBias);

   clipshape->Release(ev);
   xtransform->Release(ev);

#ifdef _PLATFORM_WIN32_
   StartPage(pPI->hdc);
#endif

   prFacet->Update(ev, invalshape, kNoBias); // calls Draw() on root part
                                             // and each of its embeds that
                                             // intersect the invalShape
   ODReleaseObject(ev, invalshape);

#ifdef _PLATFORM_WIN32_
   EndPage(pPI->hdc);
#endif

#ifdef _PLATFORM_OS2_
   if (!lastPage) {
/* Keep from ejecting a blank page after the last page of the document */
      DevEscape(pPI->hdc, DEVESC_NEWFRAME, 0, 0, 0, 0);
   } /* endif */
#endif

   return kODTrue;
}


//-------------------------------------------------------------------------
//
//  This Method displays the Print Dialog and returns its info in pPi
//
//-------------------------------------------------------------------------

SOM_Scope ODBoolean  SOMLINK ODPrintExtensionDisplayPrintDialog(ODPrintExtension *somSelf,
                                             Environment *ev,
                                            PRNINFO* pPI,
                                            HWND hwnd,
                                            char *pszTitle)
{
   ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
   ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionDisplayPrintDialog");

   ODBoolean rc = kODFalse;

#ifdef _PLATFORM_WIN32_
   PRINTDLG *dlgInfo = new PRINTDLG;
   memset(dlgInfo, 0, sizeof(PRINTDLG));

   dlgInfo->lStructSize = sizeof(PRINTDLG);
   dlgInfo->hwndOwner = hwnd;
   dlgInfo->Flags = PD_ALLPAGES | PD_RETURNDC | PD_USEDEVMODECOPIESANDCOLLATE;
   dlgInfo->nCopies = 1;

   rc = PrintDlg(dlgInfo);

   pPI->printDlg = dlgInfo;
   pPI->hdc = dlgInfo->hDC;
#endif //_PLATFORM_WIN32_

#ifdef _PLATFORM_OS2_
   char *pszPrinter = _GetCurrentPrinterQueueDisplayName(ev);
   if (pszPrinter!=kODNULL) {
      PPRNRANGE pRange = new PRNRANGE;

      pRange->pszPrinter     = pszPrinter;
      pRange->pszDocument    = pszTitle;
      pRange->usCopies       = 1;
      pRange->usPrintFrom    = 1;
      pRange->usPrintTo      = 1;
      pRange->fPrintAllPages = kODTrue;
      pRange->fAllowChoiceOfPages = kODFalse;

      rc = WinDlgBox (HWND_DESKTOP, hwnd, PrintRangeProc, MyResources,
              PrintRangeDlgRes, (PVOID)pRange);

      pPI->pRange = pRange;
   } else {
      WarningBox(hwnd, ERRm, MRI(CantQueryPrinterMsg));
   } /* endif */
#endif //_PLATFORM_OS2_

   return rc;
}


//-------------------------------------------------------------------------
//
//  This Method handles printing Multiple Pages
//
//-------------------------------------------------------------------------

SOM_Scope ODBoolean  SOMLINK ODPrintExtensionPrintPages(ODPrintExtension *somSelf,
                                              Environment *ev,
                                             ODFrame* frame,
                                             PRNINFO* pPI)
{
   ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
   ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionPrintPages");

   ODFacet*   prFacet;
   CHAR *buf = new CHAR[50];
   short pageNumber = 1;

// TRY
      prFacet = _BeginPrinting(ev, frame, pPI);

//    THROW_IF_NULL(prFacet);
      if (prFacet==kODNULL) {
         return(kODFalse);
      } /* endif */

      ODFrame* prFrame    = prFacet->GetFrame(ev);
      ODShape* frameShape = prFrame->AcquireFrameShape(ev, kNoBias);

      ODRect bbox;
      frameShape->GetBoundingBox(ev, &bbox); //bbox is size of frame rect
      frameShape->Release(ev);

      long frameWidth = (bbox.right-bbox.left)/0x10000;

#ifdef _PLATFORM_OS2_
      long frameHeight = (bbox.top-bbox.bottom)/0x10000;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
      long frameHeight = (bbox.bottom-bbox.top)/0x10000;
#endif //_PLATFORM_WIN32_

//    long pageWidth = _GetCurrentPrinterPageWidth(ev);
//    long pageHeight = _GetCurrentPrinterPageHeight(ev);
      long pageWidth = _GetCurrentPrinterClipWidth(ev);
      long pageHeight = _GetCurrentPrinterClipHeight(ev);

      short lastPage = (frameHeight/pageHeight+1)*(frameWidth/pageWidth+1);
      for (short row=1; (row-1)*pageHeight<frameHeight; row++) {
         for (short column=1; (column-1)*pageWidth<frameWidth; column++) {
            ODBoolean rc = 0;
            if (_PrintHWND != NULL)
            {
               sprintf(buf, MRI(PrintingPageXString), pageNumber);

#ifdef _PLATFORM_OS2_
               rc = WinSetDlgItemText(_PrintHWND, PrintPageNum, buf);
#endif

#ifdef _PLATFORM_WIN32_
               rc = SetDlgItemText(_PrintHWND, PrintPageNum, buf);
#endif
            } /* endif */

            pPI->offset.x = bbox.left+(column-1)*pageWidth*0x10000;

#ifdef _PLATFORM_OS2_
            pPI->offset.y = bbox.bottom+(row-1)*pageHeight*0x10000;
/* We adjust the offset so that the top of the frame comes out aligned with  */
/* the top of the page.  This happens for free on WIN32, due to the top-down */
/* coordinate system there - we'll simulate that here on OS/2                */
            if (frameHeight<pageHeight) {
               pPI->offset.y -= (pageHeight-frameHeight)*0x10000;
            } /* endif */
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
            pPI->offset.y = bbox.top+(row-1)*pageHeight*0x10000;
#endif //_PLATFORM_WIN32_

            rc = _PrintPage(ev, prFacet, pPI, pageNumber==lastPage);

            if (rc==kODFalse) {
               return kODFalse;
            } /* endif */

            pageNumber++;
         } /* endfor */
      } /* endfor */

      _EndPrinting(ev, prFacet);

// CATCH_ALL
      // garbage collection needs to be improved
// ENDTRY

   return kODTrue; // no error
}


//-------------------------------------------------------------------------
//
//  This Method Creates a printing canvas and returns a print facet
//
//-------------------------------------------------------------------------

SOM_Scope ODFacet*  SOMLINK ODPrintExtensionBeginPrinting(ODPrintExtension *somSelf,
                                                     Environment *ev,
                                                    ODFrame* rootFrame,
                                                    PRNINFO* pPI)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionBeginPrinting");

    CHAR *buf = new CHAR[80];

    if (_PrintHWND != NULL)
    {
       strcpy(buf, MRI(PreparingJobMsg));
#ifdef _PLATFORM_OS2_
       ODBoolean rcc = WinSetDlgItemText(_PrintHWND, PrintPageNum, buf);
#endif

#ifdef _PLATFORM_WIN32_
       ODBoolean rcc = SetDlgItemText(_PrintHWND, PrintPageNum, buf);
#endif
    }

    if (rootFrame==kODNULL) {
       return kODNULL;
    } /* endif */

    ODStorageUnit *su = rootFrame->GetStorageUnit(ev);

    ODShape* frameShape = _SetPrintingFrameShape(ev, rootFrame);
    if (frameShape==kODNULL) {
       return kODNULL;
    } /* endif */

    if (somSelf->GetBase(ev) ==kODNULL) {
       return kODNULL;
    } /* endif */

    ODFrame* prFrame = su->GetDraft(ev)->CreateFrame(ev,
                            kODNonPersistentFrameObject,
                            kODNULL,
                            frameShape,
                            kODNULL,
                            (ODPart *)somSelf->GetBase(ev),
                            rootFrame->GetViewType(ev),
                            rootFrame->GetPresentation(ev),
                            kODTrue,
                            kODFalse);
    frameShape->Release(ev);

    if (prFrame==kODNULL) {
       return kODNULL;
    } /* endif */

    prFrame->Acquire(ev);

    ODPart *prPart = prFrame->AcquirePart(ev);
    prPart->AttachSourceFrame(ev, prFrame, rootFrame);
    prPart->Release(ev);

    ODTransform* xtransform = rootFrame->CreateTransform(ev);
    ODShape* clipshape = rootFrame->CreateShape(ev);

    clipshape->SetRectangle(ev, &pPI->bounds);

    ODFacet* prFacet = kODNULL;
    ODWindowState* windowState = su->GetSession(ev)->GetWindowState(ev);
    if (windowState) {
       prFacet = windowState->CreateFacet(ev, prFrame, clipshape, xtransform,
          kODNULL /* canvas */, kNoBias);
    } /* endif */

    if (prFacet==kODNULL) {
       return kODNULL;
    } /* endif */

#ifdef _PLATFORM_OS2_
    ODPlatformCanvas* platformCanvas = (ODPlatformCanvas *)
       prFacet->CreatePlatformCanvas(ev, pPI->hps);

    ODCanvas* prCanvas = prFacet->CreateCanvas(ev, kODPM,
       platformCanvas, kODFalse, kODFalse);

    prCanvas->SetPlatformPrintJob(ev, kODPM, &pPI->printDest);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    ODPlatformCanvas* platformCanvas = (ODPlatformCanvas *)
       prFacet->CreatePlatformCanvas(ev, pPI->hdc);

    ODCanvas* prCanvas = prFacet->CreateCanvas(ev, kODWin32,
       platformCanvas, kODFalse, kODFalse);

    prCanvas->SetPlatformPrintJob(ev, kODWin32, &pPI->printDlg);
#endif//_PLATFORM_WIN32_

    prCanvas->SetOwner(ev, (ODPart *)somSelf->GetBase(ev));
    prFacet->ChangeCanvas(ev, prCanvas);

    clipshape->Release(ev); clipshape = kODNULL;
    xtransform->Release(ev); xtransform = kODNULL;
    prFrame->FacetAdded(ev, prFacet);

    return prFacet;
}


SOM_Scope void  SOMLINK ODPrintExtensionEndPrinting(ODPrintExtension *somSelf,
                                               Environment *ev,
                                              ODFacet* prFacet)
{
   ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
   ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionEndPrinting");

   CHAR *buf = new CHAR[80];

   if (_PrintHWND != NULL)
   {
      strcpy(buf, MRI(CompletingJobMsg));

#ifdef _PLATFORM_OS2_
      ODBoolean rcc = WinSetDlgItemText(_PrintHWND, PrintPageNum, buf);
#endif

#ifdef _PLATFORM_WIN32_
      ODBoolean rcc = SetDlgItemText(_PrintHWND, PrintPageNum, buf);
#endif
   } /* endif */

// ODCanvas* prCanvas = prFacet->GetCanvas(ev);
   ODFrame*  prFrame =  prFacet->GetFrame(ev);

   prFrame->FacetRemoved(ev, prFacet);
   delete prFacet;

// delete prCanvas; //jwa: the "delete prFacet" above takes care of this
                    //     (we'll trap if we try doing it again, since we've
                    //      got a pointer to memory that has been deallocated)

   prFrame->Close(ev);
}


//-------------------------------------------------------------------------
//
//  This Method Creates the frameShape to be used in BeginPrinting()
//
//-------------------------------------------------------------------------

SOM_Scope ODShape*  SOMLINK ODPrintExtensionSetPrintingFrameShape(ODPrintExtension *somSelf,
                                                     Environment *ev,
                                                    ODFrame* rootFrame)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionSetPrintingFrameShape");

/* A Part with a content area different from its frameShape (such as a part */
/* utilizing the ODScrollExtension) would create a shape here and then put  */
/* together an appropriate ODRect and call shape->SetRectangle(), and then  */
/* return that shape, for BeginPrinting() to use in the CreateFrame() call. */

    return(ODCopyAndRelease(ev, rootFrame->AcquireFrameShape(ev, kNoBias)));
}


//-------------------------------------------------------------------------
//
//  Method to Query the selected printer
//
//-------------------------------------------------------------------------

SOM_Scope void  SOMLINK ODPrintExtensionQuerySelectedPrinter(ODPrintExtension *somSelf,
                                                        Environment *ev,
                                                       char *QueueName,
                                                       ODBoolean displayErrors)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionQuerySelectedPrinter");

#ifdef _PLATFORM_OS2_
   ULONG           rc, cForms, slen, cbNeeded;
   CHAR            szWork[LEN_WORKSTRING], *pch, achQueueName[255];
   CHAR            pszPrint[256];
   CHAR            achDriverName[DRIVERNAME_LENGTH];
   HAB             hab = WinQueryAnchorBlock(HWND_DESKTOP);
   HDC             hdcPrinterInfo;
   HPS             hpsPrinterInfo;
   PHCINFO         phcInfo;
   PPRQINFO3       pqi;
   DEVOPENSTRUC    dos;
   SIZEL           sizel;

   //---------------------------------------------------------------------------
   //  Get system default queue.
   //---------------------------------------------------------------------------

   if (_ppliInfo == kODNULL)
   {
      _ppliInfo = (PPRNLISTINFO) malloc(sizeof(PRNLISTINFO));
      _ppliInfo->dosPrinter.pszLogAddress = NULL;
   }
   if (_ppliInfo->dosPrinter.pszLogAddress != NULL)
   {
      strcpy(achQueueName, _ppliInfo->dosPrinter.pszLogAddress);
   }
   else
   {
      if (QueueName==kODNULL) { //  Get System Default Queue if Nothing has been selected
         rc = PrfQueryProfileString(HINI_PROFILE, "PM_SPOOLER", "QUEUE", NULL, szWork, LEN_WORKSTRING);
         if (rc)
         {
            /* truncate queuename at terminating semicolon */
            achQueueName[0] = '\0';

            pch = strchr(szWork, ';');
            if (pch)
            {
               *pch = 0;
               strcpy(achQueueName, szWork);
               _ppliInfo->dosPrinter.pszLogAddress = achQueueName;
            }
         }
         else              // defect 134005. If no INI file then
         {                 // PrfQueryProfileString may fail. If
            _cForms = 0;   // so then just return so default page
            _pForms = 0;   // size will be used.
            return;
         } /* endif */

         if (!achQueueName[0])
         {
            if (displayErrors) {
               WarningBox(HWND_DESKTOP, WARNm, MRI(NoDefaultQueueMsg));
            } /* endif */
            _ppliInfo->dosPrinter.pszLogAddress = NULL;
            _ppliInfo->dosPrinter.pszComment = NULL;
            _cForms = 0;
            _pForms = 0;
            return;
            // return kODFalse;
         } /* endif */
      } else {
         strcpy(achQueueName, QueueName);
      } /* endif */

      //---------------------------------------------------------------------------
      //   Get queue settings including the driver data info.
      //---------------------------------------------------------------------------

      SplQueryQueue("", achQueueName, 3, NULL, 0, &cbNeeded);
      pqi = (PPRQINFO3) malloc(cbNeeded);
      rc = SplQueryQueue("", achQueueName, 3, pqi, cbNeeded, &cbNeeded);

      if (rc != 0)
      {
         if (displayErrors) {
            sprintf(szWork, MRI(ErrorQueueXString), achQueueName);
            WarningBox(HWND_DESKTOP, ERRm, szWork);
         } /* endif */
              // 146485 JFH
         free(pqi);
         return;
      }

      //---------------------------------------------------------------------------
      //   Initialize _ppliInfo struct to the default values.
      //---------------------------------------------------------------------------

      ExtractPrnInfo(pqi, &_ppliInfo->dosPrinter);
   }

   memset(&sizel, 0, sizeof(sizel));
   memcpy(&dos, &(_ppliInfo->dosPrinter), sizeof(DEVOPENSTRUC));

   hdcPrinterInfo = DevOpenDC(hab, OD_INFO, "*", 3, (PDEVOPENDATA)&dos, 0);
   hpsPrinterInfo = GpiCreatePS(hab, hdcPrinterInfo, (PSIZEL)&sizel,  PU_PELS | GPIA_ASSOC);

   //---------------------------------------------------------------------------
   // Query available forms and use the currently selected one.
   //---------------------------------------------------------------------------

   if (_pForms != 0)
   {
      free(_pForms);
      _pForms = 0;
   }

   _cForms  =  DevQueryHardcopyCaps( hdcPrinterInfo, 0, 0, 0); // count of forms
   _pForms  = (PHCINFO)malloc(sizeof(HCINFO) * _cForms);       // ptr to forms
   rc       = DevQueryHardcopyCaps( hdcPrinterInfo, 0, _cForms, _pForms);

   GpiAssociate(hpsPrinterInfo, 0);
   GpiDestroyPS(hpsPrinterInfo);
   DevCloseDC(hdcPrinterInfo);
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if (_printDlg==kODNULL) {
      if (QueueName==kODNULL) {
         _printDlg = new PRINTDLG;
         memset(_printDlg, 0, sizeof(PRINTDLG));

         _printDlg->lStructSize = sizeof(PRINTDLG);
         _printDlg->Flags = PD_RETURNDEFAULT | PD_RETURNIC;

         if (displayErrors==kODFalse) {
            _printDlg->Flags |= PD_NOWARNING;
         } /* endif */

         PrintDlg(_printDlg);
      } /* endif */
   } /* endif */
#endif //_PLATFORM_WIN32_
}


//-------------------------------------------------------------------------
//  Method to Return a handle to the print progress dialog
//-------------------------------------------------------------------------

SOM_Scope HWND  SOMLINK ODPrintExtensionGetPrintProgressHWND(ODPrintExtension *somSelf,
                                                         Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetPrintProgressHWND");

    return _PrintHWND;
}


//-------------------------------------------------------------------------
//  Method to Return the index of Current Printer Form Selected
//-------------------------------------------------------------------------

SOM_Scope short  SOMLINK ODPrintExtensionGetCurrentPrinterForm(ODPrintExtension *somSelf,
                                                         Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetCurrentPrinterForm");

    short i = 0;

#ifdef _PLATFORM_OS2_
   //---------------------------------------------------------------------------
   // Query available forms and use the currently selected one.
   //---------------------------------------------------------------------------

   for (i=0; i< _cForms; i++)
      if (_pForms[i].flAttributes & HCAPS_CURRENT) break;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if (_printDlg!=kODNULL) {
      HGLOBAL devInfo = _printDlg->hDevMode;
      if (devInfo!=kODNULL) {
         DEVMODE* devMode = (DEVMODE *) GlobalLock(devInfo);
         if (devMode!=kODNULL) {
            i = devMode->dmPaperSize;
            GlobalUnlock(devInfo);
         } /* endif */
      } /* endif */
   } /* endif */
#endif

   return i;
}


//-----------------------------------------------------------------------------
//  Method to Return the physical name of the Printer Queue Currently Selected
//-----------------------------------------------------------------------------

SOM_Scope char*  SOMLINK ODPrintExtensionGetCurrentPrinterQueuePhysicalName(ODPrintExtension *somSelf,
                                                           Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetCurrentPrinterQueuePhysicalName");

   char *pszQueueName = kODNULL;

#ifdef _PLATFORM_OS2_
   //---------------------------------------------------------------------------
   // Return the physical name (not the comment!) of the queue we're
   // currently setup for (so parts can externalize it, and then, when
   // coming back up from storage, send it back to us in
   // _Initialize(ev, base, pszQueueName), if they want)
   //---------------------------------------------------------------------------

   if ((_ppliInfo!=kODNULL) && (_ppliInfo->dosPrinter.pszLogAddress!=kODNULL)) {
      pszQueueName = strdup(_ppliInfo->dosPrinter.pszLogAddress);
   } /* endif */
#endif

#ifdef _PLATFORM_WIN32_
   if (_printDlg!=kODNULL) {
      HGLOBAL devInfo = _printDlg->hDevMode;
      if (devInfo!=kODNULL) {
         DEVMODE* devMode = (DEVMODE *) GlobalLock(devInfo);
         if (devMode!=kODNULL) {
            pszQueueName = strdup((char *)devMode->dmDeviceName);
            GlobalUnlock(devInfo);
         } /* endif */
      } /* endif */
   } /* endif */
#endif

   return pszQueueName;
}


//-------------------------------------------------------------------------------------
//  Method to Return the display name (comment) of the Printer Queue Currently Selected
//-------------------------------------------------------------------------------------

SOM_Scope char*  SOMLINK ODPrintExtensionGetCurrentPrinterQueueDisplayName(ODPrintExtension *somSelf,
                                                           Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetCurrentPrinterQueueDisplayName");

   char *pszQueueName = kODNULL;

#ifdef _PLATFORM_OS2_
   if ((_ppliInfo!=kODNULL) && (_ppliInfo->dosPrinter.pszComment!=kODNULL)) {
      pszQueueName = strdup(_ppliInfo->dosPrinter.pszComment);
   } /* endif */
#endif

#ifdef _PLATFORM_WIN32_
   if (_printDlg!=kODNULL) {
      HGLOBAL devInfo = _printDlg->hDevMode;
      if (devInfo!=kODNULL) {
         DEVMODE* devMode = (DEVMODE *) GlobalLock(devInfo);
         if (devMode!=kODNULL) {
/* Apparently the "real name" and "user-friendly name" are the same on WIN32? */
            pszQueueName = strdup((char *)devMode->dmDeviceName);
            GlobalUnlock(devInfo);
         } /* endif */
      } /* endif */
   } /* endif */
#endif

   return pszQueueName;
}


//-------------------------------------------------------------------------
//  Method to Return the width of Current Printer Form Selected
//-------------------------------------------------------------------------

SOM_Scope long  SOMLINK ODPrintExtensionGetCurrentPrinterPageWidth(ODPrintExtension *somSelf,
                                                         Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetCurrentPrinterPageWidth");

   long PageWidth = 8.5*72; // Give it a reasonable default, in case below fails

#ifdef _PLATFORM_OS2_
   if (_pForms!=kODNULL) {
      PHCINFO phc = &_pForms[_GetCurrentPrinterForm(ev)];
      if (phc!=kODNULL) {
         float mmWidth = phc->cx; /* page width in millimeters */
         PageWidth = (long) (((mmWidth * 72.0) / 25.4) + .5);
      } /* endif */
   } /* endif */
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if (_printDlg!=kODNULL) {
      HDC hDC = _printDlg->hDC;
      float xDPI = GetDeviceCaps(hDC, LOGPIXELSX);    /* pixels per inch */
      float xRES = GetDeviceCaps(hDC, PHYSICALWIDTH); /* page width in pixels */

      PageWidth = (long) (((xRES * 72.0) / xDPI) +.5);
   } /* endif */
#endif //_PLATFORM_WIN32_

   return PageWidth;
}


//-------------------------------------------------------------------------
//  Method to Return the height of Current Printer Form Selected
//-------------------------------------------------------------------------

SOM_Scope long  SOMLINK ODPrintExtensionGetCurrentPrinterPageHeight(ODPrintExtension *somSelf,
                                                         Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetCurrentPrinterPageHeight");

   long PageHeight = 11*72; // Give it a reasonable default, in case below fails

#ifdef _PLATFORM_OS2_
   if (_pForms!=kODNULL) {
      PHCINFO phc = &_pForms[_GetCurrentPrinterForm(ev)];
      if (phc!=kODNULL) {
         float mmHeight = phc->cy; /* page height in millimeters */
         PageHeight = (long) (((mmHeight * 72.0) / 25.4) + .5);
      } /* endif */
   } /* endif */
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if (_printDlg!=kODNULL) {
      HDC hDC = _printDlg->hDC;
      float yDPI = GetDeviceCaps(hDC, LOGPIXELSY);     /* pixels per inch */
      float yRES = GetDeviceCaps(hDC, PHYSICALHEIGHT); /* page height in pixels */

      PageHeight = (long) (((yRES * 72.0) / yDPI) +.5);
   } /* endif */
#endif //_PLATFORM_WIN32_

   return PageHeight;
}


//-------------------------------------------------------------------------
//  Method to Return the clip width of Current Printer Form Selected
//-------------------------------------------------------------------------

SOM_Scope long  SOMLINK ODPrintExtensionGetCurrentPrinterClipWidth(ODPrintExtension *somSelf,
                                                         Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetCurrentPrinterClipWidth");

   long PageWidth = 8.5*72; // Give it a reasonable default, in case below fails

#ifdef _PLATFORM_OS2_
   if (_pForms!=kODNULL) {
      PHCINFO phc = &_pForms[_GetCurrentPrinterForm(ev)];
      if (phc!=kODNULL) {
         float mmWidth = (phc->xRightClip-phc->xLeftClip); /* clip width in millimeters */
         PageWidth = (long) (((mmWidth * 72.0) / 25.4) + .5);
      } /* endif */
   } /* endif */
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if (_printDlg!=kODNULL) {
      HDC hDC = _printDlg->hDC;
      float xDPI = GetDeviceCaps(hDC, LOGPIXELSX); /* pixels per inch */
      float xRES = GetDeviceCaps(hDC, HORZRES);    /* clip width in pixels */

      PageWidth = (long) (((xRES * 72.0) / xDPI) +.5);
   } /* endif */
#endif //_PLATFORM_WIN32_

   return PageWidth;
}


//-------------------------------------------------------------------------
//  Method to Return the clip height of Current Printer Form Selected
//-------------------------------------------------------------------------

SOM_Scope long  SOMLINK ODPrintExtensionGetCurrentPrinterClipHeight(ODPrintExtension *somSelf,
                                                         Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetCurrentPrinterClipHeight");

   long PageHeight = 11*72; // Give it a reasonable default, in case below fails

#ifdef _PLATFORM_OS2_
   if (_pForms!=kODNULL) {
      PHCINFO phc = &_pForms[_GetCurrentPrinterForm(ev)];
      if (phc!=kODNULL) {
         float mmHeight = (phc->yTopClip-phc->yBottomClip); /* clip height in millimeters */
         PageHeight = (long) (((mmHeight * 72.0) / 25.4) + .5);
      } /* endif */
   } /* endif */
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   if (_printDlg!=kODNULL) {
      HDC hDC = _printDlg->hDC;
      float yDPI = GetDeviceCaps(hDC, LOGPIXELSY); /* pixels per inch */
      float yRES = GetDeviceCaps(hDC, VERTRES);    /* clip height in pixels */

      PageHeight = (long) (((yRES * 72.0) / yDPI) +.5);
   } /* endif */
#endif //_PLATFORM_WIN32_

   return PageHeight;
}


//-------------------------------------------------------------------------
//  Method to Return the HMODULE associate with the ODPrintExtension
//-------------------------------------------------------------------------

SOM_Scope HMODULE  SOMLINK ODPrintExtensionGetResourceHandle(ODPrintExtension *somSelf,
                                                         Environment *ev)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","ODPrintExtensionGetResourceHandle");

    return MyResources;
}


//------------------------------------------------------------------------------
// ODPrintExtension: Initialize
//------------------------------------------------------------------------------

SOM_Scope void SOMLINK ODPrintExtensionInitialize
    (ODPrintExtension *somSelf, Environment *ev,
     ODPart* base, char *pszQueueName)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","Initialize");

    _InitExtension(ev, (ODObject *) base);

    MyHelp = base->GetStorageUnit(ev)->GetSession(ev)->GetHelp(ev);

#ifdef _PLATFORM_OS2_
    DosQueryModuleHandle(kMRIFileName, &MyResources);
#endif

#ifdef _PLATFORM_WIN32_
    MyResources = GetModuleHandle(kMRIFileName);
#endif

    if (MyResources==kODNULL) {
       WarningBox(HWND_DESKTOP, WARNm, ResourceErrorMsg);
    } /* endif */

   _QuerySelectedPrinter(ev, pszQueueName, kODFalse);
}


SOM_Scope void  SOMLINK ODPrintExtensionsomInit(ODPrintExtension *somSelf)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","somInit");

    ODPrintExtension_parent_ODExtension_somInit(somSelf);

    _PrintHWND = kODNULL;

#ifdef _PLATFORM_OS2_
    _ppliInfo = kODNULL;
    _pForms = kODNULL;
    _cForms = kODNULL;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    _printDlg = kODNULL;
#endif //_PLATFORM_WIN32_
}


SOM_Scope void  SOMLINK ODPrintExtensionsomUninit(ODPrintExtension *somSelf)
{
    ODPrintExtensionData *somThis = ODPrintExtensionGetData(somSelf);
    ODPrintExtensionMethodDebug("ODPrintExtension","somUninit");

    ODPrintExtension_parent_ODExtension_somUninit(somSelf);

#ifdef _PLATFORM_OS2_
    if (_pForms!=kODNULL) {
       free _pForms;
    } /* endif */

    if (_ppliInfo!=kODNULL) {
       free _ppliInfo;
    } /* endif */
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    if (_printDlg!=kODNULL) {
       free _printDlg;
    } /* endif */
#endif //_PLATFORM_WIN32_
}


//==============================================================================
// Helper functions used by ODPrintExtension's dialogs
//==============================================================================

#ifdef _PLATFORM_OS2_
LONG  CreatePrnList(HWND hwndListbox, char *currentQueueName)
{
//-----------------------------------------------------------------
// This function enumerates the printers available and inserts them
// into the specified listbox.
//
// Input:  hwndListbox - handle to the listbox to contain the list
// Returns:  an CPL_* constant
//-----------------------------------------------------------------

   SPLERR            seError;
   ULONG             ulSzBuf;
   ULONG             ulNumQueues;
   ULONG             ulNumReturned;
   ULONG             ulSzNeeded;
   ULONG             ulIndex;
   LONG              CurrentQueueIndex = CPL_NODEFAULT;
   PPRQINFO3         ppiQueue;
   PCHAR             pchPos;
   PPRNLISTINFO      ppliInfo;
   SHORT             sInsert;

   //--------------------------------------------------------------
   // Get the size of the buffer needed
   //--------------------------------------------------------------
   seError = SplEnumQueue(NULL,
                          3,
                          NULL,
                          0,
                          &ulNumReturned,
                          &ulNumQueues,
                          &ulSzNeeded,
                          NULL);
   if (seError == kODNULL)
   {
      return CPL_NOPRINTERS;
   }

   if (seError != ERROR_MORE_DATA )
   {
      return CPL_ERROR;
   }

   ppiQueue = (PPRQINFO3) malloc (ulSzNeeded);

   if (ppiQueue == NULL)
   {
      return CPL_ERROR;
   }

   ulSzBuf = ulSzNeeded;

   //--------------------------------------------------------------
   // Get the information
   //--------------------------------------------------------------

   SplEnumQueue(NULL,
                3,
                ppiQueue,
                ulSzBuf,
                &ulNumReturned,
                &ulNumQueues,
                &ulSzNeeded,
                NULL);

   //--------------------------------------------------------------
   // ulNumReturned has the count of the number of PRQINFO3
   // structures.
   //--------------------------------------------------------------

   for (ulIndex = 0; ulIndex < ulNumReturned; ulIndex++)
   {
      if ((ppiQueue[ulIndex].pszName!=kODNULL) && (currentQueueName!=kODNULL)) {
         if (strcmp(ppiQueue[ulIndex].pszName, currentQueueName)==0) {
            CurrentQueueIndex = ulIndex;
         } /* endif */
      } /* endif */

      //-----------------------------------------------------------
      // Since the "comment" can have newlines in it, replace them
      // with spaces
      //-----------------------------------------------------------

      pchPos = strchr(ppiQueue[ulIndex].pszComment, '\n');
      while (pchPos != NULL)
      {
         *pchPos = ' ';
         pchPos = strchr(ppiQueue[ulIndex].pszComment, '\n');
      }

      ppliInfo = (PPRNLISTINFO) malloc(sizeof(PRNLISTINFO));
      if (ppliInfo == NULL)
      {
         continue;
      }

      //-----------------------------------------------------------
      // Extract the device name before initializing the
      // DEVOPENSTRUC structure
      //-----------------------------------------------------------

      ppliInfo->selected = kODFalse;
      ppliInfo->pdrv = NULL;

      pchPos = strchr(ppiQueue[ulIndex].pszDriverName, '.');
      if (pchPos != NULL)
      {
         *pchPos = 0;
         strcpy (ppliInfo->achDevice, pchPos + 1);
      }
      if (ppiQueue[ulIndex].pszPrinters[0] != NULL)
      {
         strcpy(ppliInfo->pszPrinters,ppiQueue [ulIndex].pszPrinters);
      }

      ExtractPrnInfo(&ppiQueue [ulIndex], &ppliInfo -> dosPrinter);

      sInsert=SHORT1FROMMR(WinSendDlgItemMsg(hwndListbox,
                                            PrintListBox,
                                            LM_INSERTITEM,
                                            MPFROMSHORT(LIT_END),
                                            ppiQueue [ulIndex] .pszComment));

      WinSendDlgItemMsg(hwndListbox,
                        PrintListBox,
                        LM_SETITEMHANDLE,
                        MPFROMSHORT(sInsert),
                        MPFROMP(ppliInfo));
   }

   free(ppiQueue);
   return CurrentQueueIndex;
}


void DestroyPrnList(HWND hwndListbox)
{
//-----------------------------------------------------------------
// This function destroys the printer list and returns the memory
// to the system.
//
// Input:  hwndListbox - handle of the listbox containing the
//                       printer list
//-----------------------------------------------------------------
   USHORT            usNumItems;
   USHORT            usIndex;
   PPRNLISTINFO      ppliInfo;

   usNumItems = SHORT1FROMMR(WinSendDlgItemMsg(hwndListbox,
                                               PrintListBox,
                                               LM_QUERYITEMCOUNT,
                                               0,
                                               0));

   for (usIndex = 0; usIndex < usNumItems; usIndex ++)
   {
      ppliInfo = (PPRNLISTINFO) PVOIDFROMMR(
                 WinSendDlgItemMsg(hwndListbox,
                                   PrintListBox,
                                   LM_QUERYITEMHANDLE,
                                   MPFROMSHORT(usIndex),
                                   0));

      if ((ppliInfo != NULL) && (ppliInfo->selected != kODTrue))
      {
         if (ppliInfo->dosPrinter.pszLogAddress != NULL)
            free(ppliInfo->dosPrinter.pszLogAddress);

         if (ppliInfo->dosPrinter.pszDriverName != NULL)
            free(ppliInfo->dosPrinter.pszDriverName);

         if (ppliInfo->dosPrinter.pdriv != NULL)
            free(ppliInfo->dosPrinter.pdriv);

         if (ppliInfo->dosPrinter.pszComment != NULL)
            free(ppliInfo->dosPrinter.pszComment);

         if (ppliInfo->dosPrinter.pszQueueProcName != NULL)
            free(ppliInfo->dosPrinter.pszQueueProcName);

         if (ppliInfo->dosPrinter.pszQueueProcParams != NULL)
            free(ppliInfo->dosPrinter.pszQueueProcParams);

         free(ppliInfo);
      }
   }

   WinSendDlgItemMsg(hwndListbox, PrintListBox, LM_DELETEALL, 0, 0);
   return;
}


void ExtractPrnInfo(PPRQINFO3 ppiQueue,DEVOPENSTRUC* pdosPrinter)
{
//-----------------------------------------------------------------
// This function extracts the needed information from the specified
// PRQINFO3 structure and places it into the specifies DEVOPENSTRUC
// structure.
//
// Input:  ppiQueue - points to the PRQINFO3 structure
// Output:  pdosPrinter - points to the initialized DEVOPENSTRUC
//                        structure
//-----------------------------------------------------------------

   PCHAR       pchPos;

//   pdosPrinter -> pszLogAddress = ppiQueue -> pszName;
   pdosPrinter -> pszLogAddress = (CHAR*) malloc (strlen(ppiQueue->pszName)+1);
   strcpy(pdosPrinter->pszLogAddress, ppiQueue->pszName);

   pdosPrinter -> pszDriverName = (CHAR*) malloc (strlen(ppiQueue->pszDriverName)+1);
   strcpy(pdosPrinter->pszDriverName, ppiQueue->pszDriverName);
   pchPos = strchr(pdosPrinter->pszDriverName, '.');

   if (pchPos != NULL)
      *pchPos = 0;

//   pdosPrinter->pdriv = ppiQueue->pDriverData;
   pdosPrinter->pdriv = (PDRIVDATA) malloc (ppiQueue->pDriverData->cb);
   memcpy (pdosPrinter->pdriv, ppiQueue->pDriverData, ppiQueue->pDriverData->cb);

//   pdosPrinter->pszDataType = "PM_Q_STD";
   pdosPrinter->pszDataType = (CHAR*) malloc(9);
   strcpy(pdosPrinter->pszDataType, "PM_Q_STD");

//   pdosPrinter->pszComment = ppiQueue->pszComment;
   pdosPrinter->pszComment = (CHAR*) malloc(strlen(ppiQueue->pszComment)+1);
   strcpy(pdosPrinter->pszComment, ppiQueue->pszComment);

   if (strlen(ppiQueue->pszPrProc) != 0) {
//      pdosPrinter->pszQueueProcName = ppiQueue->pszPrProc;
      pdosPrinter->pszQueueProcName = (CHAR*) malloc(strlen(ppiQueue->pszPrProc)+1);
      strcpy(pdosPrinter->pszQueueProcName, ppiQueue->pszPrProc);
   } else {
      pdosPrinter->pszQueueProcName = NULL;
   }

   if (strlen(ppiQueue->pszParms) != 0) {
//      pdosPrinter->pszQueueProcParams = ppiQueue->pszParms;
      pdosPrinter->pszQueueProcParams = (CHAR*) malloc(strlen(ppiQueue->pszParms)+1);
      strcpy(pdosPrinter->pszQueueProcParams, ppiQueue->pszParms);
   } else {
      pdosPrinter->pszQueueProcParams = NULL;
   }

   pdosPrinter -> pszSpoolerParams = NULL;
   pdosPrinter -> pszNetworkParams = NULL;

   return;
}


//--------------------------------------------------------------------------
//
// This function will center a Diaglog Window over it's parent window.
//
//--------------------------------------------------------------------------

void CenterWindow(HWND hwnd)
{
         HWND hwndParent;
         RECTL rectl;
         RECTL rectlParent;

         WinQueryWindowRect(hwnd,&rectl);

         hwndParent=WinQueryWindow(hwnd,QW_PARENT);
         WinQueryWindowRect(hwndParent,&rectlParent);

         rectl.xRight/=2;
         rectl.yTop/=2;
         rectlParent.xRight/=2;
         rectlParent.yTop/=2;

         WinSetWindowPos(hwnd,
                         (HWND)NULL,
                         (LONG)(rectlParent.xRight-rectl.xRight),
                         (LONG)(rectlParent.yTop-rectl.yTop),
                         0l,
                         0l,
                         (ULONG)SWP_MOVE );
}
#endif //_PLATFORM_OS2_


//--------------------------------------------------------------------------
//
// This puts up a dialog box with warning message.
//
//--------------------------------------------------------------------------

void WarningBox(HWND hwnd, int MSG, char *str)
{
#ifdef _PLATFORM_OS2_
   char *typeMsg;
   ULONG fFlag;
   switch (MSG)
   {
   case ERRm:
      typeMsg = MRI(ErrorMsgString);
      fFlag= MB_OK | MB_MOVEABLE | MB_ERROR;
      break;
   case WARNm:
      typeMsg = MRI(WarningMsgString);
      fFlag= MB_OK | MB_MOVEABLE | MB_WARNING;
      break;
   case INFOm:
      typeMsg = MRI(InfoMsgString);
      fFlag= MB_OK | MB_MOVEABLE | MB_INFORMATION;
      break;
   default:
      typeMsg = MRI(MessageMsgString);
      fFlag= MB_OK | MB_MOVEABLE | MB_ICONASTERISK;
     break;
   }
   WinMessageBox(HWND_DESKTOP,
                 hwnd,
                 str,
                 typeMsg,
                 0,
                 fFlag);
#endif

#ifdef _PLATFORM_WIN32_
   Beep(250,150);
#endif
}


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


void ShowHelp(ODULong id)
{
   if (MyHelp!=kODNULL) {
      Environment *ev = somGetGlobalEnvironment();
      MyHelp->DisplayHelp(ev, kHelpFileName, id);
   } /* endif */
}


//==============================================================================
// Window Procedures used by ODPrintExtension's dialogs
//==============================================================================

#ifdef _PLATFORM_WIN32_
LRESULT CALLBACK PrintingPageDlg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   UINT BetValue;
   BOOL error;

   switch (msg) {
   case WM_INITDIALOG:
//    CenterWindow(hwnd);
      break;

   case WM_COMMAND:
      {
         short button = LOWORD(wParam);
         if (button==StopPrinting) {
            KeepPrinting = kODFalse;
            EndDialog(hwnd, button);
         } /* endif */
      }
      break;
   default:
      return(kODFalse);
   } /* endswitch */
   return(kODTrue);
}
#endif //_PLATFORM_WIN32_

#ifdef _PLATFORM_OS2_
MRESULT EXPENTRY PrintingPageDlg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   MRESULT ReturnValue = FALSE;

   switch (msg) {
   case WM_INITDLG:
      CenterWindow(hwnd);
      break;
   case WM_COMMAND:
      {
         short button = SHORT1FROMMP(mp1);
         if (button==StopPrinting) {
            KeepPrinting = kODFalse;
            WinDismissDlg(hwnd, button);
         } /* endif */
      }
      break;
   default:
      return(WinDefDlgProc(hwnd, msg, mp1, mp2));
     break;
   } /* endswitch */

   return(ReturnValue);
}


MRESULT EXPENTRY PrintRangeProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   static PPRNRANGE pRng;
   PSZ         psz;
   ULONG       ulPanel,rc;
   static SHORT      usCopies, usFirstPage, usLastPage;
   CHAR        szEntryField[4];
   ODBoolean   flg;

   switch (msg)
   {
   case WM_INITDLG:
      CenterWindow(hwnd);    // Center Window over Parent

      /* Get pointer to application specific data */
      pRng = (PPRNRANGE) PVOIDFROMMP(mp2);

      /* Show the printer name */
      WinSetDlgItemText(hwnd, PrinterName, (PSZ)pRng->pszPrinter);

      /* Show the document name */
      if (pRng->pszDocument == kODNULL)
          WinSetDlgItemText(hwnd, DocumentName, MRI(UntitledDocumentMsg));
      else
          WinSetDlgItemText(hwnd, DocumentName, (PSZ)pRng->pszDocument);

      /* Initialize the number of copies */
      usCopies = pRng->usCopies;
      usFirstPage = pRng->usPrintFrom;
      usLastPage = pRng->usPrintTo;


            WinSendMsg( WinWindowFromID(hwnd, PrintFrom), SPBM_SETLIMITS,
                               MPFROMSHORT(pRng->usPrintTo), MPFROMLONG(1));
            WinSendMsg( WinWindowFromID(hwnd, PrintFrom),
                               SPBM_SETCURRENTVALUE,
                               MPFROMSHORT(pRng->usPrintFrom), NULL);
            WinSendMsg( WinWindowFromID(hwnd, PrintTo), SPBM_SETLIMITS,
                               MPFROMSHORT(pRng->usPrintTo), MPFROMSHORT(pRng->usPrintFrom));
            WinSendMsg( WinWindowFromID(hwnd, PrintTo),
                               SPBM_SETCURRENTVALUE,
                               MPFROMSHORT(pRng->usPrintTo), NULL);
            WinSendMsg( WinWindowFromID(hwnd, PrintCopies), SPBM_SETLIMITS,
                               MPFROMSHORT(10000), MPFROMLONG(1));
            WinSendMsg( WinWindowFromID(hwnd, PrintCopies),
                               SPBM_SETCURRENTVALUE,
                               MPFROMSHORT(pRng->usCopies), NULL);
         WinEnableControl(hwnd, PrintFrom, TRUE);
         WinEnableControl(hwnd, PrintTo, TRUE);

      /* Set the state of the page select pushbuttons */
      if (pRng->fPrintAllPages)
      {
         WinCheckButton( hwnd, PrintAllPages, 1);
         WinCheckButton( hwnd, PrintSelectivePages, 0);
         WinEnableControl(hwnd, PrintFrom, FALSE);
         WinEnableControl(hwnd, PrintTo, FALSE);
      } else {
         WinCheckButton( hwnd, PrintAllPages, 0);
         WinCheckButton( hwnd, PrintSelectivePages, 1);
      } /* endif */

      if (!pRng->fAllowChoiceOfPages) {
         WinEnableControl(hwnd, PrintSelectivePages, 0);
      } /* endif */

      return 0;

//--------------------END INIT------------------------------//
   case WM_CONTROL:
      switch(SHORT1FROMMP(mp1))
      {
      case PrintCopies:
            switch (SHORT2FROMMP(mp1))
              {
               case SPBN_KILLFOCUS:
                  {
                     char charString[11];
                     short i = 0;

                   WinSendMsg( WinWindowFromID(hwnd, PrintCopies), SPBM_QUERYVALUE,
                                      MPARAM(&charString), MPFROMSHORT(10));

                   while(charString[i] >= '0' && charString[i] <= '9')
                            i++;

                    if (strlen(charString) == i)
                      {
                       usCopies = atoi(charString);
                        if (usCopies < 1)
                          usCopies = 1;
                        if (usCopies > 10000)
                          usCopies = 10000;
                      }
                   WinSendMsg(  WinWindowFromID(hwnd, PrintCopies),
                                       SPBM_SETCURRENTVALUE, MPFROMSHORT(usCopies), NULL);
                  }
              }
      return (MPARAM)0;
      case PrintAllPages:
         // check buttons appropriately
         WinCheckButton( hwnd, PrintAllPages, 1);
         WinCheckButton( hwnd, PrintSelectivePages, 0);

         // disable first and last page entry fields
         WinEnableControl(hwnd, PrintFrom, FALSE);
         WinEnableControl(hwnd, PrintTo, FALSE);
         return 0;

      case PrintSelectivePages:
         // check buttons appropriately

         WinCheckButton( hwnd, PrintAllPages, 0);
         WinCheckButton( hwnd, PrintSelectivePages, 1);
         WinEnableControl(hwnd, PrintFrom, TRUE);
         WinEnableControl(hwnd, PrintTo, TRUE);

         return 0;

      case PrintFrom:
           switch (SHORT2FROMMP(mp1))
              {
               case SPBN_KILLFOCUS:
                  {
                     char charString[11];
                     short i = 0;

                   WinSendMsg( WinWindowFromID(hwnd, PrintFrom), SPBM_QUERYVALUE,
                                      MPARAM(&charString), MPFROMSHORT(10));

                    usFirstPage = (SHORT)atoi(charString);

                     if (usFirstPage < 1)
                       usFirstPage = 1;
                     if (usFirstPage > usLastPage)
                       usFirstPage = usLastPage;

                    WinSendMsg(  WinWindowFromID(hwnd, PrintFrom),
                                        SPBM_SETCURRENTVALUE, MPFROMSHORT(usFirstPage), NULL);
                    WinSendMsg( WinWindowFromID(hwnd, PrintTo), SPBM_SETLIMITS,
                                       MPFROMSHORT(pRng->usPrintTo), MPFROMLONG(usFirstPage));
                  }
              }
      return (MPARAM)0;
   case PrintTo:
           switch (SHORT2FROMMP(mp1))
              {
               case SPBN_KILLFOCUS:
                  {
                     char charString[11];
                     short i = 0;

                   WinSendMsg( WinWindowFromID(hwnd, PrintTo), SPBM_QUERYVALUE,
                                      MPARAM(&charString), MPFROMSHORT(10));

                    usLastPage = (SHORT)atoi(charString);
                     if (usFirstPage > usLastPage)
                       usLastPage = usFirstPage;
                     if (usLastPage > pRng->usPrintTo)
                       usLastPage = pRng->usPrintTo;

                     WinSendMsg(  WinWindowFromID(hwnd, PrintTo),
                                         SPBM_SETCURRENTVALUE, MPFROMSHORT(usLastPage), NULL);
                     WinSendMsg( WinWindowFromID(hwnd, PrintFrom), SPBM_SETLIMITS,
                                        MPFROMSHORT(usLastPage), MPFROMLONG(1));
                  }
              }
      return (MPARAM)0;
     }

//--------------------END CONTROL------------------------------//
   case WM_COMMAND:
      switch(SHORT1FROMMP(mp1))
      {
        case DID_OK:
        case PrintDoc:
         WinShowWindow(hwnd, FALSE);
         /* get number of copies and store in global data structure */
//       WinQueryDlgItemShort(hwnd, PrintCopies,
//                             (PSHORT)&pRng->usCopies, FALSE);
        WinSendMsg(WinWindowFromID(hwnd, PrintCopies),
                          SPBM_QUERYVALUE,
                          &pRng->usCopies, NULL);

         /* print all pages or selective pages */
         pRng->fPrintAllPages =
             (BOOL) WinSendDlgItemMsg(hwnd, PrintAllPages, BM_QUERYCHECK,
                                      (MPARAM)TRUE, (MPARAM)0L);
//         WinQueryDlgItemShort(hwnd, PrintFrom,
//                              (PSHORT)&pRng->usPrintFrom, FALSE);
//         WinQueryDlgItemShort(hwnd, PrintTo,
//                              (PSHORT)&pRng->usPrintTo, FALSE);
        WinSendMsg(WinWindowFromID(hwnd, PrintFrom),
                          SPBM_QUERYVALUE,
                          &pRng->usPrintFrom, NULL);
        WinSendMsg(WinWindowFromID(hwnd, PrintTo),
                          SPBM_QUERYVALUE,
                          &pRng->usPrintTo, NULL);

//
//       if (pRng->usPrintTo < pRng->usPrintFrom)
//       {
//          pRng->fPrintAllPages = TRUE;
//          pRng->usPrintFrom = 1;
//          pRng->usPrintTo = 1;
//       }
         WinDismissDlg(hwnd, TRUE);
         return 0;

      case DID_CANCEL:
      case PrintCancel:
         WinDismissDlg(hwnd, FALSE);
         return 0;

      case DID_HELP:
         ShowHelp(PRINT_DOCUMENT_HELP); //jwa - [158914]
         return 0;

      default:
//         DosBeep(500,500);
         break;
       }
       break;
//--------------------END COMMAND---------------------------//
    }
   return(WinDefDlgProc(hwnd, msg, mp1, mp2));
}


MRESULT EXPENTRY PrinterListDlg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PPRNLISTINFO      ppliInfo; //  (PPRNLISTINFO) mp2;

   switch (msg) {
   case WM_INITDLG:
   {
      CenterWindow(hwnd);    // Center Window over Parent
      WinSendMsg(hwnd, WM_COMMAND, MPFROMSHORT(RefreshList), mp2);
   }
      break;
   case WM_DESTROY:
      //-----------------------------------------------------------
      // Return the resources to the system
      //-----------------------------------------------------------
      DestroyPrnList(hwnd);
      break;
   case WM_CONTROL:
      if (SHORT1FROMMP(mp1)==PrintListBox)
      {
         //----------------------------------------------------------------
         // If we get a LN_ENTER notification, process it
         // as though the user pressed "Load".
         //----------------------------------------------------------------
         if (SHORT2FROMMP(mp1)==LN_ENTER)
         {
            WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(DID_OK), 0L);
         }
         else
         {
            return WinDefDlgProc(hwnd, msg, mp1, mp2);
         }
      }
      break;
   case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
      {
      case DID_CANCEL:
         DestroyPrnList(hwnd);
         WinDismissDlg(hwnd, FALSE);
         break;
      case DID_HELP:
         ShowHelp(AVAILABLE_PRINTERS_HELP); //jwa - [158914]
         break;
      case PrinterProperties:
      {
         USHORT            usSelect;
         //-----------------------------------------------------
         // Query the selected printer
         //-----------------------------------------------------
         usSelect = SHORT1FROMMR(WinSendDlgItemMsg(hwnd,
                                                   PrintListBox,
                                                   LM_QUERYSELECTION,
                                                   MPFROMLONG(LIT_FIRST),
                                                   0));
         ppliInfo = (PPRNLISTINFO) PVOIDFROMMR(
                                 WinSendDlgItemMsg(hwnd,
                                                   PrintListBox,
                                                   LM_QUERYITEMHANDLE,
                                                   MPFROMSHORT(usSelect),
                                                   0));

         if (ppliInfo != NULL)
         {
            LONG cbuf,rc;
            cbuf = DevPostDeviceModes(WinQueryAnchorBlock(hwnd),
                                 NULL,
                                 ppliInfo->dosPrinter.pszDriverName,
                                 ppliInfo->achDevice,
                                 ppliInfo->pszPrinters,
                                 DPDM_POSTJOBPROP);
            if (cbuf <= 0)
            {
               WarningBox(hwnd, ERRm, MRI(PrintBufferErrorMsg));
            }

            if (cbuf != ppliInfo->dosPrinter.pdriv->cb)
            {
               ppliInfo->dosPrinter.pdriv = (PDRIVDATA) malloc(cbuf);
            }

            if (ppliInfo->pdrv != NULL)
            {
               free(ppliInfo->pdrv);
               ppliInfo->pdrv = NULL;
            }
            ppliInfo->pdrv = (PDRIVDATA) malloc(cbuf);
            memcpy(ppliInfo->pdrv, ppliInfo->dosPrinter.pdriv, ppliInfo->dosPrinter.pdriv->cb);

            rc = DevPostDeviceModes(WinQueryAnchorBlock(hwnd),
                                 ppliInfo -> pdrv,
                                 ppliInfo -> dosPrinter.pszDriverName,
                                 ppliInfo -> achDevice,
                                 ppliInfo -> pszPrinters,
                                 DPDM_POSTJOBPROP );
            if (rc==6)
               DosBeep(1000,1000);

            memcpy(ppliInfo->dosPrinter.pdriv,ppliInfo->pdrv,cbuf);
         }
         else
         {
            WarningBox(hwnd, ERRm, MRI(PrintersNotAvailMsg));
         }
      }
      break;
      case DID_OK:
      {
          USHORT            usSelect;
          PPRNLISTINFO      ppliInfo1=NULL;

         //-----------------------------------------------------
         // Query the selected printer
         //-----------------------------------------------------
         usSelect = SHORT1FROMMR(WinSendDlgItemMsg(hwnd,
                                                    PrintListBox,
                                                    LM_QUERYSELECTION,
                                                    MPFROMLONG(LIT_FIRST),
                                                    0));
         ppliInfo = (PPRNLISTINFO) PVOIDFROMMR(
                                  WinSendDlgItemMsg(hwnd,
                                                    PrintListBox,
                                                    LM_QUERYITEMHANDLE,
                                                    MPFROMSHORT(usSelect),
                                                    0));

         if (ppliInfo == NULL)
         {
            WarningBox(hwnd, INFOm, MRI(CantQueryPrinterMsg));
         }
//         else
//         {
//            ppliInfo1 = (PPRNLISTINFO) malloc(sizeof(PRNLISTINFO));
//            memcpy(ppliInfo1, ppliInfo, sizeof(PRNLISTINFO));
//         }
         ppliInfo->selected = kODTrue;
         WinDismissDlg(hwnd,(ULONG) ppliInfo);  // Return Printer to caller
         DestroyPrnList(hwnd);
      }
      break;

      case RefreshList:
      {
         LONG      Result;

         DestroyPrnList(hwnd);
         Result = CreatePrnList(hwnd, (char *)mp2);

         switch (Result)
         {
            case CPL_ERROR:
               WarningBox(hwnd, ERRm, MRI(PrintersNotAvailMsg));
               break;

            case CPL_NOPRINTERS:
               WarningBox(hwnd, WARNm, MRI(NoPrintersWarning));
               WinDismissDlg(hwnd, FALSE); // No need to display list box
               break;

            case CPL_NODEFAULT:
               /* Don't highlight any items in the listbox */
               break;

            default:
               WinSendDlgItemMsg(hwnd,
                                 PrintListBox,
                                 LM_SELECTITEM,
                                 MPFROMLONG(Result),
                                 MPFROMSHORT(TRUE));
               break;
         }
      }
         break;
      default:
         return WinDefDlgProc(hwnd, msg, mp1,  mp2);
      }
      break;

   default:
      return WinDefDlgProc(hwnd, msg, mp1, mp2);
   }
   return MRFROMSHORT(FALSE);
}
#endif //_PLATFORM_OS2_

