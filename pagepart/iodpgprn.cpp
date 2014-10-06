//   @(#) 1.5 com/src/samples/pagepart/iodpgprn.cpp, odpagepart, od96os2, odos29712d 3/4/97 18:17:58 [3/21/97 17:49:00]
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
/*
	File:		IODPgPrn.cpp

	Contains:	Implementation of PageLayoutPrintExtension class.

	Owned by:	John Alcorn

	Copyright:	© 1996 by IBM, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 10/23/96	JWA		first checked in

	To Do:
	In Progress:
		
*/

#define PageLayoutPrintExtension_Class_Source
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

#ifndef SOM_ODFacet_xh
#include <Facet.xh>
#endif

#ifndef SOM_ODFrame_xh
#include <Frame.xh>
#endif

#ifndef SOM_Module_xh5cStdProps_OpenDoc_StdProps_defined
#include <StdProps.xh>
#endif

#ifndef SOM_Module_xh5cStdTypes_OpenDoc_StdTypes_defined
#include <StdTypes.xh>
#endif

#include <stdio.h>
#include <iostream.h>

#include <IODPrint.hpp>
#include "IODPgPrn.xih"

HMODULE IODPgPrn_Resources;


#ifdef _PLATFORM_OS2_
extern MRESULT EXPENTRY PrintRangeProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#endif //_PLATFORM_OS2_


char* IODPgPrn_MRI(int id)
{
   char *ReturnValue = (char *) malloc(sizeof(char)*256);
#ifdef _PLATFORM_OS2_
// read string from string table in resource file
   USHORT rc = WinLoadString((HAB)0, IODPgPrn_Resources, id, 255, ReturnValue);
   if (!rc) {
      strcpy(ReturnValue, StringNotFoundMsg);
   } /* endif */
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   strcpy(ReturnValue, StringNotFoundMsg);
#endif

   return ReturnValue;
}


//==============================================================================
// PageLayoutPrintExtension
//==============================================================================


//-------------------------------------------------------------------------
//
//  This Method displays the Print Dialog and returns its info in pPi
//
//-------------------------------------------------------------------------

SOM_Scope ODBoolean  SOMLINK PageLayoutPrintExtensionDisplayPrintDialog(PageLayoutPrintExtension *somSelf,
                                             Environment *ev,
                                            PRNINFO* pPI,
                                            HWND hwnd,
                                            char *pszTitle)
{
   PageLayoutPrintExtensionData *somThis = PageLayoutPrintExtensionGetData(somSelf);
   PageLayoutPrintExtensionMethodDebug("PageLayoutPrintExtension","PageLayoutPrintExtensionDisplayPrintDialog");

   ODBoolean rc = kODFalse;

#ifdef _PLATFORM_WIN32_
   PRINTDLG *dlgInfo = new PRINTDLG;
   memset(dlgInfo, 0, sizeof(PRINTDLG));

   dlgInfo->lStructSize = sizeof(PRINTDLG);
   dlgInfo->hwndOwner = hwnd;
   dlgInfo->Flags = PD_PAGENUMS | PD_NOSELECTION | PD_RETURNDC |
                    PD_USEDEVMODECOPIESANDCOLLATE;
   dlgInfo->nCopies = 1;
   dlgInfo->nFromPage = 1;
   dlgInfo->nToPage = _NumberOfPages;
   dlgInfo->nMinPage = 1;
   dlgInfo->nMaxPage = _NumberOfPages;

   rc = PrintDlg(dlgInfo);

   pPI->printDlg = dlgInfo;
   pPI->hdc = dlgInfo->hDC;
#endif //_PLATFORM_WIN32_

#ifdef _PLATFORM_OS2_
   PPRNRANGE pRange = new PRNRANGE;

   pRange->pszPrinter     = _GetCurrentPrinterQueueDisplayName(ev);
   pRange->pszDocument    = pszTitle;
   pRange->usCopies       = 1;
   pRange->usPrintFrom    = 1;
   pRange->usPrintTo      = _NumberOfPages;
   pRange->fPrintAllPages = kODTrue;
   pRange->fAllowChoiceOfPages = kODTrue;

   rc = WinDlgBox (HWND_DESKTOP, hwnd, PrintRangeProc, IODPgPrn_Resources,
           PrintRangeDlgRes, (PVOID)pRange);

   pPI->pRange = pRange;
#endif //_PLATFORM_OS2_

   return rc;
}


//-------------------------------------------------------------------------
//
//  This Method handles printing Multiple Pages
//
//-------------------------------------------------------------------------

SOM_Scope ODBoolean  SOMLINK PageLayoutPrintExtensionPrintPages(PageLayoutPrintExtension *somSelf,
                                              Environment *ev,
                                             ODFrame* frame,
                                             PRNINFO* pPI)
{
   PageLayoutPrintExtensionData *somThis = PageLayoutPrintExtensionGetData(somSelf);
   PageLayoutPrintExtensionMethodDebug("PageLayoutPrintExtension","PageLayoutPrintExtensionPrintPages");

   ODFacet*   prFacet;
   CHAR *buf = new CHAR[50];

// TRY
      prFacet = _BeginPrinting(ev, frame, pPI);

//    THROW_IF_NULL(prFacet);
      if (prFacet==kODNULL) {
         return(kODFalse);
      } /* endif */

      HWND PrintHWND = _GetPrintProgressHWND(ev);

      short firstPage = 1;
      short lastPage = _NumberOfPages;

#ifdef _PLATFORM_OS2_
      if (pPI->pRange && !pPI->pRange->fPrintAllPages) {
         firstPage = pPI->pRange->usPrintFrom;
         lastPage = pPI->pRange->usPrintTo;
      } /* endif */
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
      if (pPI->printDlg && !(pPI->printDlg->Flags & PD_ALLPAGES)) {
         firstPage = pPI->printDlg->nFromPage;
         lastPage = pPI->printDlg->nToPage;
      } /* endif */
#endif //_PLATFORM_WIN32_

      for (short pageNumber=firstPage; pageNumber<=lastPage; pageNumber++) {
         ODBoolean rc;
         if (PrintHWND != NULL)
         {
            sprintf(buf, IODPgPrn_MRI(PrintingPageXString), pageNumber);

#ifdef _PLATFORM_OS2_
            rc = WinSetDlgItemText(PrintHWND, PrintPageNum, buf);
#endif

#ifdef _PLATFORM_WIN32_
            rc = SetDlgItemText(PrintHWND, PrintPageNum, buf);
#endif
         } /* endif */

         ODFrame* prFrame    = prFacet->GetFrame(ev);
         ODShape* frameShape = prFrame->AcquireFrameShape(ev, kNoBias);

         ODRect bbox;
         frameShape->GetBoundingBox(ev, &bbox); //bbox is size of frame rect
         frameShape->Release(ev);

         pPI->offset.x = bbox.left+_HorzPageOffset*0x10000;

#ifdef _PLATFORM_OS2_
         pPI->offset.y = bbox.bottom+(_VertPageOffset+
            (_NumberOfPages-pageNumber)*_TotalPageHeight)*0x10000;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
         pPI->offset.y = bbox.top+(_VertPageOffset+
            (pageNumber-1)*_TotalPageHeight)*0x10000;
#endif //_PLATFORM_WIN32_

         rc = _PrintPage(ev, prFacet, pPI, pageNumber!=lastPage);

         if (rc==kODFalse) {
            return kODFalse;
         } /* endif */
      } /* endfor */

      _EndPrinting(ev, prFacet);

// CATCH_ALL
      // garbage collection needs to be improved
// ENDTRY

   return kODTrue; // no error
}


//-------------------------------------------------------------------------
//
//  This Method Creates the frameShape to be used in BeginPrinting()
//
//-------------------------------------------------------------------------

SOM_Scope ODShape*  SOMLINK PageLayoutPrintExtensionSetPrintingFrameShape(PageLayoutPrintExtension *somSelf,
                                                     Environment *ev,
                                                    ODFrame* rootFrame)
{
    PageLayoutPrintExtensionData *somThis = PageLayoutPrintExtensionGetData(somSelf);
    PageLayoutPrintExtensionMethodDebug("PageLayoutPrintExtension","PageLayoutPrintExtensionSetPrintingFrameShape");

/* Since our content area is generally different from our frame shape, we   */
/* override this method so that we can set the size of the printing frame   */
/* (to which the drawing during printing is clipped) to be our content area */

    ODShape *frameShape = rootFrame->CreateShape(ev);
    ODRect PageRect;
    PageRect.left   = 0;
    PageRect.right  = _TotalPageWidth*0x10000;

#ifdef _PLATFORM_OS2_
    PageRect.bottom = 0;
    PageRect.top    = _TotalPageHeight*_NumberOfPages*0x10000;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
    PageRect.top    = 0;
    PageRect.bottom = _TotalPageHeight*_NumberOfPages*0x10000;
#endif //_PLATFORM_WIN32_

    frameShape->SetRectangle(ev, &PageRect);

    return(frameShape);
}


//-------------------------------------------------------------------------
//
//  This Method updates the page width and height instance variables
//
//-------------------------------------------------------------------------

SOM_Scope void  SOMLINK PageLayoutPrintExtensionSetPageDimensions(PageLayoutPrintExtension *somSelf,
                                              Environment *ev,
                                              long width, long height)
{
   PageLayoutPrintExtensionData *somThis = PageLayoutPrintExtensionGetData(somSelf);
   PageLayoutPrintExtensionMethodDebug("PageLayoutPrintExtension","PageLayoutPrintExtensionSetTotalPageWidth");

   _TotalPageWidth = width;
   _TotalPageHeight = height;
}


//-------------------------------------------------------------------------
//
//  This Method updates the NumberOfPages instance variable
//
//-------------------------------------------------------------------------

SOM_Scope void  SOMLINK PageLayoutPrintExtensionSetNumberOfPages(PageLayoutPrintExtension *somSelf,
                                              Environment *ev,
                                              short count)
{
   PageLayoutPrintExtensionData *somThis = PageLayoutPrintExtensionGetData(somSelf);
   PageLayoutPrintExtensionMethodDebug("PageLayoutPrintExtension","PageLayoutPrintExtensionSetNumberOfPages");

   _NumberOfPages = count;
}


//------------------------------------------------------------------------------
// Initialize our instance variables
//------------------------------------------------------------------------------

SOM_Scope void SOMLINK PageLayoutPrintExtensionInitializeForPageLayout
    (PageLayoutPrintExtension *somSelf, Environment *ev,
        ODPart* base, char *pszQueueName, long HorzOffset, long VertOffset,
        long TotalPageWidth, long TotalPageHeight, short NumberOfPages)
{
    PageLayoutPrintExtensionData *somThis = PageLayoutPrintExtensionGetData(somSelf);
    PageLayoutPrintExtensionMethodDebug("PageLayoutPrintExtension","InitializeForPageLayout");

    _NumberOfPages = NumberOfPages;

    _HorzPageOffset = HorzOffset;
    _VertPageOffset = VertOffset;

    _TotalPageWidth = TotalPageWidth;
    _TotalPageHeight = TotalPageHeight;

    _Initialize(ev, base, pszQueueName);

    IODPgPrn_Resources = _GetResourceHandle(ev);
}

