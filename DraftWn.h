/* @(#)Z 1.20 com/src/docshell/DraftWn.h, odshell, od96os2, odos29714c 97/04/02 17:19:55 (97/03/24 12:40:24) */
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odshell
 *
 *   CLASSES:   DraftWindow
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

/*

	File:		DraftWn.h

	Contains:	definition of the DraftWn classes

*/

#ifndef _DRAFTWN_
#define _DRAFTWN_

#if defined (_PLATFORM_WIN32_)
#include <windows.h>
#elif defined (_PLATFORM_OS2_)
#include "ODos2.h"
#endif

#include <DocMgr.xh>
#include <AppShell.xh>
#include <Draft.xh>
#include <WinStat.xh>
#include <Window.xh>

#include <ISOStr.h>
#include <ODTypes.h>
#include <ODUtils.h>

#if defined(_PLATFORM_WIN32_) || defined(_PLATFORM_OS2_)
#include <ODRes.h>
#ifndef SOM_ODSession_xh
#include <ODSessn.xh>
#endif
#ifndef SOM_ODHelp_xh
#include <ODHelp.xh>
#endif
#ifndef _HLPPANELS_
#include <hlppanls.h>
#endif
#endif //defined(_PLATFORM_WIN32_) || defined(_PLATFORM_OS2_) 

#include <IText.h>
#include <DraftRec.h>

//moved these includes below the ones above 
//to avoid conflict with odnltyps.h
#include <time.h>
#include <langinfo.h>
#include <string.h>
#include <stdio.h>
#include <iostream.h>
#include <wchar.h>
#include <locale.h>


//==============================================================================
// constants used in functions
//==============================================================================
const ODULong kODNameLength = 15; // Length of name in draft history entry
const ODULong kODNumLength  = 5;  // Length of draft in draft history entry
const ODULong kODDateLength = 40; // Length of date in draft history entry
const ODULong kODCmntLength = 30; // Length of comment in draft history entry
const ODULong kODTotalTabs  = 3;  // Number of tab stops used in list box.

const ODULong kODMaxNameLength = 80;// Max length of creator name. 
const ODULong kODMaxLength  = 256;// Max length of text fields in draft info
const size_t  kODWcsLength  = sizeof(wchar_t);
//==============================================================================
// Classes defined in this interface
//==============================================================================

class DraftWindow;	

//==============================================================================
// DraftWindow definition
//==============================================================================

class DraftWindow
{	

  public:
        // Constructor
	DraftWindow(DocumentManager*, WindowSystemData*, ODPlatformWindow);

        // Destructor
	ODVMethod ~DraftWindow();

        // Produces and controls Draft History Dialog
        ODMethod  void          DraftHistory();

        // Opens selected draft
        ODMethod  ODBoolean     OpenDraft(int, DraftInfoRec*);
 
        // Deletes selected draft
        ODMethod  ODBoolean     RemoveDraft(int, DraftInfoRec*);

	// Accessors for fActiveDocumentManager
	ODMethod  void          SetActiveDocumentManager(DocumentManager* dmgr) 
                                               {fActiveDocumentManager = dmgr;}
	ODMethod  DocumentManager* GetActiveDocumentManager() 
                                               {return fActiveDocumentManager;}

	// Accessors for fDraftInfoList
	ODMethod  void          SetDraftInfoList(DraftInfoRec* dhInfo) 
                                                   {fDraftInfoList = dhInfo;}
        ODMethod  DraftInfoRec* GetDraftInfoList() {return fDraftInfoList;}

	// Accessors for fInstance
#if defined (_PLATFORM_WIN32_) 
	ODMethod void SetInstance(HINSTANCE instance) {fInstance = instance;}
        ODMethod HINSTANCE GetInstance()              {return fInstance;}
#elif defined (_PLATFORM_OS2_)
	ODMethod void SetInstance(HMODULE instance)   {fInstance = instance;}
        ODMethod HMODULE GetInstance()                {return fInstance;}
#elif defined (_PLATFORM_UNIX_)
	ODMethod void SetInstance(Widget instance)    {fInstance = instance;}
        ODMethod Widget GetInstance()                 {return fInstance;}
#endif

	// Accessors for fWindow
	ODMethod void           SetWindow(ODPlatformWindow window) 
                                                            {fWindow = window;}
        ODMethod ODPlatformWindow GetWindow() {return fWindow;}

  private:
        // Finds a specific info rec in DraftInfoList
        DraftInfoRec* FindDraftInList(int);

        // pointer to currently active document manager associated 
        // with this document.
	DocumentManager*	fActiveDocumentManager;

        // List of draft info records
	DraftInfoRec*		fDraftInfoList;
        
        // Resource file instance
#if defined (_PLATFORM_WIN32_) 
	HINSTANCE       	fInstance;
#elif defined (_PLATFORM_OS2_)
	HMODULE       	        fInstance;
#elif defined (_PLATFORM_UNIX_)
	Widget       	        fInstance;
#endif

        // Handle to document window.
	ODPlatformWindow        fWindow;

        // pointer to currently selected draft for purposes of incrementing 
        // and decrementing ref count.
	ODDraft*		fSelectedDraft;

};

#endif	// _DRAFTWIN_
