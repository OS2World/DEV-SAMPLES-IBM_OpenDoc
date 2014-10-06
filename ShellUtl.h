/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odshell
 *
 *   CLASSES: none
 *
 *   ORIGINS: 82,27
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
/* @(#)Z 1.10 com/src/docshell/ShellUtl.h, odshell, od96os2, odos29712d 97/03/21 17:48:25 (97/03/05 14:36:18) */

/*

	File:		ShellUtl.h

	Contains:	Prototypes for shell utility functions

*/

#ifndef _SHELLUTL_
#define _SHELLUTL_

#include "DraftWn.h"

SOMEXTERN ODULong SOMLINK       SelectKindDlg(Environment *ev, char* selText);
SOMEXTERN ODULong SOMLINK       ConfirmCloseDlg(Environment *ev);
SOMEXTERN ODULong SOMLINK       ConfirmExitDlg(Environment *ev);
SOMEXTERN ODBoolean SOMLINK     ConfirmRevertDlg(Environment *ev);
SOMEXTERN void SOMLINK CreateDraftDlg(Environment *ev, ODULong draftNum);
SOMEXTERN void SOMLINK DraftHistoryDlg(Environment *ev, DraftWindow* DWThis);
SOMEXTERN void SOMLINK AboutDlg(Environment *ev);
SOMEXTERN void SOMLINK OpenFileDlg(ODPlatformWindow window, char* docName);
SOMEXTERN PlatformFile* SOMLINK SaveFileDlg(Environment *ev);
SOMEXTERN ODBoolean SOMLINK ReadOnlyDlg(Environment *ev);


#ifdef _PLATFORM_WIN32_

#include <windows.h>
#include <WinShell.xh>

SOMEXTERN void SOMLINK SetShell(WinShell *somSelf);
SOMEXTERN BOOL SOMLINK CALLBACK CreateDialogFunc(HWND hdwnd, UINT message,
                                                  WPARAM wParam, LPARAM lParam);
SOMEXTERN BOOL SOMLINK CALLBACK SelectKindDialogFunc(HWND hdwnd, UINT message,
                                                  WPARAM wParam, LPARAM lParam);
SOMEXTERN BOOL SOMLINK CALLBACK DraftDialogFunc(HWND hdwnd, UINT message, 
                                                  WPARAM wParam, LPARAM lParam);
SOMEXTERN LRESULT SOMLINK CALLBACK ODDocumentWindowProc(HWND window, UINT message,
                                                  WPARAM wParam, LPARAM lParam);
SOMEXTERN void SOMLINK EnableApplModal(Environment *ev, HWND hwnd, 
                                                  BOOL enable);
#endif

#ifdef _PLATFORM_OS2_
#include <OS2Shell.xh>
SOMEXTERN void SOMLINK SetShell(OS2Shell *somSelf);
SOMEXTERN MRESULT SOMLINK SelectKindDialogFunc(HWND hwnd, ULONG msg, 
				      MPARAM mp1, MPARAM mp2);
SOMEXTERN MRESULT SOMLINK CreateDialogFunc(HWND hwnd, ULONG msg, 
                                  MPARAM mp1, MPARAM mp2);
SOMEXTERN MRESULT SOMLINK ODDocumentWindowProc( HWND hwnd, ULONG msg, 
                                       MPARAM mp1, MPARAM mp2 );
SOMEXTERN MRESULT SOMLINK DraftDialogFunc(HWND hdwnd, ULONG message, 
                                 MPARAM mp1, MPARAM mp2);
SOMEXTERN void SOMLINK EnableApplModal(Environment *ev, HWND hwnd, BOOL enable);

#endif

#ifdef _PLATFORM_UNIX_
#include <AIXShell.xh>
// button values from dialog callback routines
#define NONE   0
#define YES    1
#define NO     2
#define OK     3
#define CANCEL 4
#define HELP   5
#define SAVE   6

SOMEXTERN void SOMLINK SetShell(AIXShell *somSelf);
SOMEXTERN ODULong SOMLINK ConfirmDeleteDraftDlg(Environment *ev, 
                                Widget parentWidget);
SOMEXTERN ODBoolean SOMLINK ConfirmDeleteDlg(Environment *ev, 
                                Widget parentWidget, char *fileName);
SOMEXTERN PlatformFile* SOMLINK SaveFileDlg(Environment *ev);
SOMEXTERN void SOMLINK helpCallBack(Widget widget, XtPointer client_data, 
				XtPointer call_data);
SOMEXTERN void SOMLINK confirmCallBack(Widget widget, XtPointer client_data, 
				XtPointer call_data);
SOMEXTERN void SOMLINK fileCallBack(Widget widget, XtPointer client_data, 
				XtPointer call_data);
SOMEXTERN void SOMLINK selectPartKindCallBack(Widget widget, 
				XtPointer client_data, XtPointer call_data);
SOMEXTERN void SOMLINK draftCallBack(Widget widget, XtPointer client_data, 
				XtPointer call_data);
SOMEXTERN void SOMLINK draftHistoryCallBack(Widget widget, 
				XtPointer client_data, XtPointer call_data);
SOMEXTERN void SOMLINK DialogPopupCallBack(Widget widget, 
				XtPointer client_data, XtPointer call_data);
SOMEXTERN void SOMLINK DialogPopdownCallBack(Widget widget, 
				XtPointer client_data, XtPointer call_data);
SOMEXTERN void SOMLINK CreateDraftControlArea(Widget parent, Widget *name, 
				Widget *comment, char *draftNum);
SOMEXTERN void SOMLINK CloseCallBack(Widget widget, XtPointer client_data, 
				XtPointer call_data);
SOMEXTERN void SOMLINK SaveDtSession(Widget widget, XtPointer client_data, 
				XtPointer call_data);
SOMEXTERN char* SOMLINK BuildEntry(DraftInfoRec* draftptr);
SOMEXTERN void SOMLINK CreateDraftListLabel(char* label, int* label_len);
SOMEXTERN char* SOMLINK CreateDraftListEntry(char* entry, int* label_len);
SOMEXTERN int  SOMLINK ShellXErrorHandler(Display* display, XErrorEvent* err);
SOMEXTERN void SOMLINK ProcessEventLoop(int *result, int cancelReturn);
SOMEXTERN Widget SOMLINK GetActiveWindowTopLevelWidget(Environment *ev);
SOMEXTERN void SOMLINK SetDispatchModal(ODBoolean setModality);
#endif

#endif  // _SHELLUTL_
