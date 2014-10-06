
/* @(#)Z 1.2 com/src/samples/shpin/iodshpin.cpp, odplugin, od96os2, odos29712d 97/03/21 17:51:30 (97/02/27 16:11:55) */

//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odplugin
//
//   CLASSES: none
//
//   ORIGINS: 27
//
//
//   (C) COPYRIGHT International Business Machines Corp. 1997
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

#ifdef _PLATFORM_OS2_
#include <ODos2.h>
#endif
#include <ODTypes.h>

#ifndef _SHPLUGIN_
#include <shplugin.h>
#endif

#include "ioddspm.xh"
#include "ODStor.xh"
#include "ODCtr.xh"
#include "Document.xh"
#include "Draft.xh"
#include "ODSessn.xh"
#include "disptch.xh"
#include "dispmod.xh"

/* Define event types handled by Standard Dispatch Module */
static const ODEventType StdEventTypes[] = {
#ifdef _PLATFORM_OS2_
	WM_BUTTON1DOWN,
	WM_BUTTON2DOWN,
	WM_BUTTON3DOWN,
	WM_BUTTON1UP,
	WM_BUTTON2UP,
	WM_BUTTON3UP,
	WM_MOUSEMOVE,
	WM_CHORD,
	WM_BUTTON1MOTIONSTART,
	WM_BUTTON1MOTIONEND,
	WM_BUTTON2MOTIONSTART,
	WM_BUTTON2MOTIONEND,
	WM_BUTTON3MOTIONSTART,
	WM_BUTTON3MOTIONEND,
	WM_CONTEXTHELP,
	WM_BUTTON1CLICK,
	WM_BUTTON2CLICK,
	WM_BUTTON3CLICK,
	WM_BUTTON1DBLCLK,
	WM_BUTTON2DBLCLK,
	WM_BUTTON3DBLCLK,
	WM_BEGINDRAG,
	WM_ENDDRAG,
	WM_SINGLESELECT,
	WM_CONTEXTMENU,
	WM_BEGINSELECT,
	WM_ENDSELECT,
	WM_OPEN,
	WM_TEXTEDIT,
	WM_CHAR,
	kODEvtKeyUp,
	kODEvtKeyDown,
	WM_PAINT,
	WM_ACTIVATE,
	WM_COMMAND,
	WM_INITMENU,
	WM_TIMER,
	WM_SIZE,
	WM_RENDERFMT,
	DM_DRAGOVER,
	DM_DRAGLEAVE,
	DM_DROP,
	DM_RENDER,
	DM_RENDERCOMPLETE,
	DM_ENDCONVERSATION,
	WM_MENUSELECT,
	WM_DRAWITEM,
	WM_MEASUREITEM,
	OD_HELP,
	WM_QUERYCONVERTPOS,
	WM_REALIZEPALETTE,
	WM_PRESPARAMCHANGED,
	WM_HSCROLL,
	WM_VSCROLL,          
	WM_MOVE
#else
        WM_RBUTTONDOWN,
        WM_MBUTTONDOWN,
        WM_LBUTTONDOWN,
        WM_RBUTTONUP,
        WM_MBUTTONUP,
        WM_LBUTTONUP,
        WM_RBUTTONDBLCLK,
        WM_MBUTTONDBLCLK,
        WM_LBUTTONDBLCLK,
        WM_KEYDOWN,
        WM_KEYUP,
        WM_MOUSEMOVE,
        WM_VSCROLL,
        WM_HSCROLL,
        WM_PAINT,
        WM_ACTIVATE,
        WM_COMMAND,
        WM_ERASEBKGND,
        WM_NCCREATE,
        WM_SETFOCUS,
        WM_SIZE,
        WM_MOVE,
        kODEvtMouseDownEmbedded,
        kODEvtMouseDownBorder,
        kODEvtMouseUpEmbedded
#endif
};

const ODULong NumStdEventTypes = sizeof(StdEventTypes) / sizeof(ODEventType);

extern "C" {
OSErr ODShellPlugInInstall( Environment*, ODDraft*, ODShellPlugInActionCodes*);
}

// Shell plug-in entry point
OSErr ODShellPlugInInstall( Environment* ev1,
    ODDraft* draft, ODShellPlugInActionCodes* action)
{
    // Somehow the environment passed in is incorrect. Need to get the correct
    // environment.
    Environment *ev = somGetGlobalEnvironment();

    // Get the dispatcher
    ODSession* session = draft->GetDocument(ev)->GetContainer(ev)->
				GetStorageSystem(ev)->GetSession(ev);
    ODDispatcher* dispatcher = session->GetDispatcher(ev);

    // Create a new dispatch module
    SampleDispatchMonitor* dspmod = new SampleDispatchMonitor;

    // Initialize the dispatch module object
    dspmod->InitDispatchModule(ev, session);

    // Save window state data to be used by the new dispatch module
    dspmod->SetWindowState(ev, session->GetWindowState(ev));

    // Add the new dispatch module to the dispatch module dictionary
    // to handler specified events
    for (int i = 0; i < NumStdEventTypes; i++)
    {
       dispatcher->AddMonitor(ev, StdEventTypes[i], dspmod);
    }
    return noErr;
}

