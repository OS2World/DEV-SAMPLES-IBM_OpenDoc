/* @(#)Z 1.4 com/src/samples/basecntr/iodbcset.cpp, odbasepart, od96os2, odos29714c 97/04/02 17:20:08 (97/03/25 13:49:30) */
//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odbasepart
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
        File:           BCSettng.cpp

        Contains:       code for the BCPartSettingsExt class
*/

#define BCPartSettingsExt_Class_Source
#define VARIABLE_MACROS

#include <ODTypes.h>

#if defined(_PLATFORM_OS2_)
#include <odos2.h>
#include <iodbcres.h>
#elif defined(_PLATFORM_WIN32_)
#include <windows.h>
#include <iodbcres.h>
#endif

#ifndef _ODRES_
#include <odres.h>
#endif

#ifndef SOM_ODSettingsExtension_xh
#include <Settings.xh>
#endif

#ifndef _TEMPOBJ_
#include <TempObj.h>
#endif

#ifndef SOM_ODFrame_xh
#include <Frame.xh>
#endif

#ifndef SOM_ODFacet_xh
#include <Facet.xh>
#endif

#ifndef SOM_ODPart_xh
#include <Part.xh>
#endif

#ifndef SOM_ODStorageUnit_xh
#include <StorageU.xh>
#endif

/*
 *  Settings Notebook headers...
 */
#if defined(_PLATFORM_UNIX_)
#include <Notebook.xh>
#include <iodbcpag.xh>
#endif
#include <iodbcset.xih>

#if defined(_PLATFORM_OS2_)
MRESULT EXPENTRY SettingsPageDlgProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2);
#elif defined(_PLATFORM_WIN32_)
SOMEXTERN BOOL SOMLINK CALLBACK SettingsPageDlgProc(HWND hdwnd,UINT message,
                                                  WPARAM wParam, LPARAM lParam);
#endif

HWND hwndParent = NULL;

//==============================================================================
// BCPartSettingsExt::InitSettingsExtension
//==============================================================================

SOM_Scope void  SOMLINK BCPartSettingsExtInitSettingsExtension
                        (BCPartSettingsExt *somSelf,
                         Environment *ev,
                         ODPart *parent)

{
    /* BCPartSettingsExtData *somThis =
                BCPartSettingsExtGetData(somSelf); */

    BCPartSettingsExtMethodDebug("BCPartSettingsExt",
                "BCPartSettingsExtInitSettingsExtension");

    BCPartSettingsExt_parent_ODSettingsExtension_InitSettingsExtension(
      somSelf, ev, parent);

}


#if defined(_PLATFORM_WIN32_)

//==============================================================================
// BCPartSettingsExt::ShowSettingsPages - Windows
//==============================================================================
SOM_Scope void  SOMLINK BCPartSettingsExtShowSettingsPages
                        (BCPartSettingsExt *somSelf, Environment *ev,
                         ODFacet *facet, HWND hPropSheetDlg)

{
    /* BCPartSettingsExtData *somThis =
                BCPartSettingsExtGetData(somSelf); */

    BCPartSettingsExtMethodDebug("BCPartSettingsExt",
                "BCPartSettingsExtShowSettingsPages");

// The settings page is not currently defined in the resource file for
// compilers other than Visual Age.
#if defined(__IBMCPP__) || defined(_IBMR2)

    // Save the parent into a global variable to be used within the dialog
    // funtion.
    hwndParent = hPropSheetDlg;

    HINSTANCE resInst = LoadLibrary("iodbasec");
    PROPSHEETPAGE page;

    page.dwSize      = sizeof(PROPSHEETPAGE);
    page.dwFlags     = PSP_HASHELP;
    page.hInstance   = resInst;
    page.pszTemplate = MAKEINTRESOURCE(ID_SETTINGSPAGEDLG);
    page.pfnDlgProc  = (FARPROC) SettingsPageDlgProc;
    page.lParam      = (LONG) facet;

    HPROPSHEETPAGE hPage = CreatePropertySheetPage (&page);

    PropSheet_AddPage (hPropSheetDlg, hPage);

#endif
}

//==============================================================================
// SettingsPageDlgProc - Windows
//==============================================================================
SOMEXTERN BOOL SOMLINK CALLBACK SettingsPageDlgProc(HWND hdwnd, UINT message,
                                                WPARAM wParam, LPARAM lParam)

{
  Environment          *ev = somGetGlobalEnvironment();
  ODFacet              *facet;
  PROPSHEETPAGE        *page;
  ODBoolean            retCode = kODTrue;
  ODBoolean            dialogDismissed = kODFalse;

  try
  {
    switch (message)
    {
      //------------------------------------------------------
      //  Initialize the draft page.
      //------------------------------------------------------
      case WM_INITDIALOG:
      {
        // get necessary information from incoming lParam structure
        page = (PROPSHEETPAGE*) lParam;
        facet = (ODFacet*) page->lParam;

        // save handle to this object structure passed in as lParam
        SetWindowLong(hdwnd, GWL_USERDATA, lParam);

        // NOTE: Uncomment the following lines of code if you need to retrieve
        // information from the part's storage unit for initialization
        //
        // Need to acquire the frame before using it.
        // TempODFrame frame = facet->GetFrame(ev);
        // frame->Acquire(ev);

        // Need to acquire the part.
        // TempODPart part = frame->AcquirePart(ev);

        // Need to acquire the storage unit before using it.
        // TempODStorageUnit partSU = part->GetStorageUnit(ev);
        // partSU->Acquire(ev);

        // ---- Add part specific settings initialization here ----

        break;
      }

      case WM_HELP:
      {
        MessageBox(hdwnd, "Help is not implemented for this page.",
                   "Information", MB_OK);
        break;
      }

      case WM_COMMAND:
      {
        // Retrieve handle to facet.
        page = (PROPSHEETPAGE*) GetWindowLong(hdwnd, GWL_USERDATA);
        facet = (ODFacet*) page->lParam;

        switch (LOWORD(wParam))
        {
          case IDCANCEL:
            // Set indicator since this case will cause dialog to be dismissed.
            dialogDismissed = kODTrue;
            break;

          default:
            retCode = kODFalse;
            break;
        }
        break;
      } // WM_COMMAND

      case WM_NOTIFY:
      {
        // Retrieve handle to facet.
        page = (PROPSHEETPAGE*) GetWindowLong(hdwnd, GWL_USERDATA);
        facet = (ODFacet*) page->lParam;

        switch (((NMHDR FAR *) lParam)->code)
        {
          case PSN_SETACTIVE:
          {
            // Set return code.
            SetWindowLong(hdwnd, DWL_MSGRESULT, 0);

            break;
          }

          case PSN_APPLY:     // OK or APPLY was pressed.
          {
            // Set return code.
            SetWindowLong(hdwnd, DWL_MSGRESULT, PSNRET_NOERROR);

            break;
          }

          case PSN_KILLACTIVE:     // OK
          {
            // Allow window to lose activation.
            SetWindowLong(hdwnd, DWL_MSGRESULT, FALSE);

            break;
          }

          case PSN_RESET:     // Cancel pressed.  Need to cleanup.
          {
            // Set indicator since this case will cause dialog to be dismissed.
            dialogDismissed = kODTrue;

            break;
          }

          case PSN_HELP:
          {
            MessageBox(hdwnd, "Help is not implemented for this page.",
                    "Information", MB_OK);
            break;
          }

          default:
            retCode = kODFalse;
            break;

        } // switch
        break;

      } // WM_NOTIFY

      default:
          retCode = kODFalse;
          break;

    } // switch (message)

  }
  catch (ODException _exception)
  {
    // If dialog hasn't already been dismissed, dismiss it.
    if (!dialogDismissed)
      EndDialog(hdwnd,0);

    throw;
  }
  return retCode;
}


#elif defined(_PLATFORM_UNIX_)

//==============================================================================
// BCPartSettingsExt::ShowSettingsPages - AIX
//==============================================================================
SOM_Scope void  SOMLINK BCPartSettingsExtShowSettingsPages
                        (BCPartSettingsExt *somSelf, Environment *ev,
                         ODFacet *facet, ODNotebook *notebook)

{
    /* BCPartSettingsExtData *somThis =
                BCPartSettingsExtGetData(somSelf); */

    BCPartSettingsExtMethodDebug("BCPartSettingsExt",
                "BCPartSettingsExtShowSettingsPages");

    BaseContainerPage* bcpage = new BaseContainerPage;

    // ---- Add any part page initialization here before adding
    // ---- the page to the notebook, i.e.
    //
    //    bcpage->Initialize(ev, partSU,...)

    notebook->AddPage (ev, bcpage);
}

#elif defined(_PLATFORM_OS2_)

//==============================================================================
// BCPartSettingsExt::ShowSettingsPages - OS2
//==============================================================================
SOM_Scope void  SOMLINK BCPartSettingsExtShowSettingsPages
                        (BCPartSettingsExt *somSelf, Environment *ev,
                         ODFacet* facet, HWND parent, ULONG notebookID)
{
    /* BCPartSettingsExtData *somThis =
                BCPartSettingsExtGetData(somSelf); */

    BCPartSettingsExtMethodDebug("BCPartSettingsExt",
                "BCPartSettingsExtShowSettingsPages");

    // Save the parent into a global variable to be used within the dialog
    // funtion.
    hwndParent = parent;

    // Get handle to our load module which contains the resource file.
    HMODULE hmod;
    CHAR Error[256] = "";
    DosLoadModule( Error, sizeof(Error), "iodbasec", &hmod );

    // Tell notebook to insert a page and save the id to it.
    ULONG pageId = (LONG)WinSendDlgItemMsg(parent, notebookID,
                BKM_INSERTPAGE, NULL,
                MPFROM2SHORT((BKA_STATUSTEXTON | BKA_AUTOPAGESIZE | BKA_MAJOR),
                BKA_LAST));

    // Set the text of the new page's tab.
    WinSendDlgItemMsg(parent, notebookID, BKM_SETTABTEXT, MPFROMLONG(pageId),
                      MPFROMP("Part"));

    // Create a page based on the ID_SETTINGSPAGEDLG resource and save the
    // handle.
    HWND pageHwnd = WinLoadDlg(parent,parent,(PFNWP)SettingsPageDlgProc,
                               (HMODULE)hmod, ID_SETTINGSPAGEDLG, facet);

    // Associate the handle of the new page dialog to the notebook.
    WinSendDlgItemMsg(parent, notebookID, BKM_SETPAGEWINDOWHWND,
                      MPFROMLONG(pageId), MPFROMHWND(pageHwnd));

    // Save the new page handle and id in an internal data structure for
    // the ODInfo class to be able to reference it.
    somSelf->AddNotebookSheet( ev, pageHwnd, pageId );
}

//==============================================================================
// SettingsPageDlgProc - OS2
//==============================================================================
/*-------------------------------------------------------------------*/
/* Dialog procedure for the settings page.                           */
/*-------------------------------------------------------------------*/
MRESULT EXPENTRY SettingsPageDlgProc( HWND hdwnd, ULONG msg,
                                      MPARAM mp1, MPARAM mp2 )
{
  ODFacet* facet = kODNULL;
  Environment *ev = somGetGlobalEnvironment();

  switch ( msg )
  {
    case WM_INITDLG:
    {
      facet = (ODFacet *) MPFROMP(mp2);

      // save handle to facet passed in as lParam
      WinSetWindowULong(hdwnd, QWL_USER, LONGFROMMP(mp2));

      // NOTE: Uncomment the following lines of code if you need to retrieve
      // information from the part's storage unit for initialization
      //
      // Need to acquire the frame before using it.
      // TempODFrame frame = facet->GetFrame(ev);
      // frame->Acquire(ev);

      // Need to acquire the part.
      // TempODPart part = frame->AcquirePart(ev);

      // Need to acquire the storage unit before using it.
      // TempODStorageUnit partSU = part->GetStorageUnit(ev);
      // partSU->Acquire(ev);

      // ----- Add part specific settings initialization here -----

      return MRESULT(TRUE);
      break;
    }

/*---------------------------------------------------------------------*/
/* This is code in response to a user defined message which is sent    */
/* when the notebook page is about to come to the top as the active    */
/* page.  This corresponds to the PSN_SETACTIVE case in Windows.       */
/*---------------------------------------------------------------------*/
    case WM_SET_ACTIVE:
      break;

/*---------------------------------------------------------------------*/
/* This is code in response to a user defined message which is sent    */
/* when the user hit the OK button and this page was on top.  This     */
/* corresponds to the PSN_SETACTIVE case in Windows.                   */
/*---------------------------------------------------------------------*/
    case WM_DID_OK:
    {
      facet = (ODFacet *) WinQueryWindowULong(hdwnd, QWL_USER);

      // NOTE: Uncomment the following lines of code if you need to retrieve
      // information from the part's storage unit for initialization
      //
      // Need to acquire the frame before using it.
      // TempODFrame frame = facet->GetFrame(ev);
      // frame->Acquire(ev);

      // Need to acquire the part.
      // TempODPart part = frame->AcquirePart(ev);

      // Need to acquire the storage unit before using it.
      // TempODStorageUnit partSU = part->GetStorageUnit(ev);
      // partSU->Acquire(ev);

      // ---- Do any part updating here ----
      break;
    }

    case WM_COMMAND:
      if (SHORT1FROMMP( mp1 ) == DID_CANCEL)
      {
        /* This occured as a result of the Escape key being pressed while this
         * page was active.  Want to intercept this so it doesn't go onto
         * WinDefDlgProc.  Eventually, need to pass event back up to parent to
         * handle.
         */
        WinSendMsg(hwndParent, WM_COMMAND, MPFROMSHORT(DID_CANCEL), MPARAM(0));
        break;
      }

    case WM_HELP:
    {
       WinMessageBox(HWND_DESKTOP,hdwnd,
                     "Help is not implemented for this page.",
                     "Information",
                     0, MB_INFORMATION | MB_OK);
       break;
    }

    default:
      /*
       * Any event messages that the dialog procedure has not processed
       * come here and are processed by WinDefDlgProc.
       * This call MUST exist in your dialog procedure.
       */
      return WinDefDlgProc( hdwnd, msg, mp1, mp2 );
  }
  return (MRESULT) FALSE;
}

#endif

