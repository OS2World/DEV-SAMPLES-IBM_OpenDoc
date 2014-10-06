
/* @(#)Z 1.2 com/src/samples/shpin/ioddspm.cpp, odplugin, od96os2, odos29712d 97/03/21 17:51:30 (97/02/27 16:11:39) */

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

#ifndef SOM_Module_smpdspm_Source
#define SOM_Module_smpdspm_Source
#endif
#define SampleDispatchMonitor_Class_Source

#define VARIABLE_MACROS
#include <stdio.h>
#include "ioddspm.xih"
#include "frame.xh"
#include "draft.xh"
#include "winstat.xh"
#include "window.xh"
#include "storageU.xh"
#include "ioddspm.h"


// 
// Our sample dispatch logs each event passed through the dispatcher
// and sets the draft dirty if the event types is WM_MOVE on OS/2 and 
// Windows platform.
//
SOM_Scope ODBoolean  SOMLINK SampleDispatchMonitorDispatch(
					SampleDispatchMonitor *somSelf,
                                        Environment *ev,
                                        ODEventData* event,
					ODEventInfo *eventInfo)
{
    SampleDispatchMonitorData *somThis = SampleDispatchMonitorGetData(somSelf);
    SampleDispatchMonitorMethodDebug("SampleDispatchMonitor","SampleDispatchMonitorDispatch");

    const char *msg;
    char work[12];

    // Search the message table for the message id. If the message id
    // is found, get the message string from the message table to be
    // used for logging. If the message id is not found in the message
    // table, use the message id for logging. 
    const int array_size = sizeof(messages) / sizeof(message);
    for (int i=0; i<array_size; i++)
#ifdef _PLATFORM_WIN32_
       if (messages[i].id == event->message) break;
#endif
#ifdef _PLATFORM_OS2_
       if (messages[i].id == event->msg) break;
#endif

    if (i < array_size)
       msg = messages[i].text;
    else {
#ifdef _PLATFORM_WIN32_
       sprintf(work, "%08X", event->message);
#endif
#ifdef _PLATFORM_OS2_
       sprintf(work, "%08X", event->msg);
#endif
       msg = work;
    }

#ifdef _PLATFORM_OS2_
    somPrintf("hwnd=%08X, msg=%s, mp1=%08X, mp2=%08X\n",
             event->hwnd,
             msg,
             event->mp1,
             event->mp2);
#endif
#ifdef _PLATFORM_WIN32_
    somPrintf("hwnd=%08X, msg=%s, wParam=%08X, lParam=%08X\n",
             event->hwnd,
             msg,
             event->wParam,
             event->lParam);
#endif

    // If the event type is WM_MOVE, mark the draft dirty.
#ifdef _PLATFORM_WIN32_
    if (event->message == WM_MOVE)
#endif
#ifdef _PLATFORM_OS2
    if (event->msg == WM_MOVE)
#endif
    {
        // Get window state from dispatcher module
	ODWindowState *windowState = somSelf->GetWindowState(ev);
	 
	if (windowState)
	{
		// Acquire OD window from the platform window
		ODWindow *window = windowState->AcquireODWindow(ev, event->hwnd);
		if (window)
		{
			// Get root frame belonging to the OD window
			ODFrame *frame = window->GetRootFrame(ev);
			if (frame)
			{
				// Get draft belonging to the root frame
				ODDraft *draft = frame->GetStorageUnit(ev)->
							GetDraft(ev);

				// If draft has write permission, mark draft
				// dirty.
				if (draft && 
				  draft->GetPermissions(ev) >= kODDPSharedWrite)
					draft->SetChangedFromPrev(ev);
			}
			// Release OD window acquired above
			window->Release(ev);
		}
	}
   }
	
   // Return event not handled
   return kODFalse;
}

//
// Set window state data
//
SOM_Scope void SOMLINK SampleDispatchMonitorSetWindowState(
					SampleDispatchMonitor *somSelf,
                                        Environment *ev,
                                        ODWindowState *windowState)
{
    SampleDispatchMonitorData *somThis = SampleDispatchMonitorGetData(somSelf); 
    SampleDispatchMonitorMethodDebug("SampleDispatchMonitor","SampleDispatchMonitorSetWindowState");

    _fWindowState = windowState;
}

//
// Get window state data
//
SOM_Scope ODWindowState* SOMLINK SampleDispatchMonitorGetWindowState(
					SampleDispatchMonitor *somSelf,
                                        Environment *ev)
{
    SampleDispatchMonitorData *somThis = SampleDispatchMonitorGetData(somSelf); 
    SampleDispatchMonitorMethodDebug("SampleDispatchMonitor","SampleDispatchMonitorSetWindowState");

    return _fWindowState; 
}

