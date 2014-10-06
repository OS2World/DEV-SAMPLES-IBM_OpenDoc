/* @(#)Z 1.37 com/src/docshell/DraftWn.cpp, odshell, od96os2, odos29712d 97/03/21 17:18:17 (97/01/20 16:48:26) */
//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odshell
//
//   CLASSES: none
//
//   ORIGINS: 27
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
//----------------------------------------------------------------------------
// DraftWn.cpp - This file contains the DraftWindow class implementation.
//               This class invokes and manages the draft history window.
//----------------------------------------------------------------------------
#include "DraftWn.h"
#include "DocShell.h"
#include "ShellUtl.h"

#undef LOGGING
#define LOGGING 1

//////////////////////////////////////////////////////////////////////////////
////                           MEMBER FUNCTIONS                           ////
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
DraftWindow::DraftWindow(DocumentManager* docmgr, 
                         WindowSystemData* wsdata,
                         ODPlatformWindow hwnd)

{
  Environment *ev = somGetGlobalEnvironment();

  fSelectedDraft         = kODNULL;

  // Have the document manager interalize all of the draft information.
  fActiveDocumentManager = docmgr;
  fActiveDocumentManager->InternalizeHistory(ev);

  // Save list of drafts associated with currently active document.
  fDraftInfoList = fActiveDocumentManager->GetDraftList(ev);

#if defined(_PLATFORM_WIN32_) || defined (_PLATFORM_OS2_)
  fWindow                = hwnd;
  fInstance              = wsdata->resInstance;
#elif defined(_PLATFORM_UNIX_)
  fInstance              = wsdata->appShell;
#endif

}

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
DraftWindow::~DraftWindow() 
{
  Environment *ev = somGetGlobalEnvironment();
  try
  {
    // Free the list of history records.
    fActiveDocumentManager->DeleteDraftList(ev);
  }
  catch (ODException _exception)
  {
     LOG("Exception occured in DraftWindow::~DraftWindow\n");
     throw;
  }
}

//----------------------------------------------------------------------------
// DraftHistory - invokes the drafthistory dialog.
//----------------------------------------------------------------------------
void DraftWindow::DraftHistory()
{
  Environment *ev = somGetGlobalEnvironment();
  DraftHistoryDlg(ev, this);
}

//----------------------------------------------------------------------------
//  FindDraftInList - Finds a particular draft info record based on a 
//                    position passed in.
//----------------------------------------------------------------------------
DraftInfoRec* DraftWindow::FindDraftInList (int ItemSelected)
{
  DraftInfoRec* draftptr = NULL;

  // Find selected draft in fDraftInfoList.  Note: this method is not used
  // for NT.

#if defined (_PLATFORM_UNIX_)
  // AIX: the ItemSelected paramter is the position in the list
  // of the selected draft.  Assumption is that list order reflects order 
  // of draftinfo records in dialog list.  Therefore position is equivalent.
  draftptr = fDraftInfoList;
  for (int position = 0;
       (draftptr != kODNULL) && (position < ItemSelected);
       position++, draftptr = draftptr->GetNext());
#elif defined(_PLATFORM_OS2_)
  // On Os2 the ItemSelected parameter is the actual draft number, not
  // the position in the list of the draft entry.  Therefore we search
  // the list for the DraftInfoRec that matches the draft number.
  for (draftptr=fDraftInfoList; 
       (draftptr != kODNULL) && (draftptr->GetDraftNum() != ItemSelected); 
       draftptr = draftptr->GetNext());
#endif

  return draftptr;
}

//----------------------------------------------------------------------------
//  OpenDraft - Opens the selected draft.
//----------------------------------------------------------------------------
ODBoolean DraftWindow::OpenDraft(int ItemSelected, DraftInfoRec* dInfoRec)
{
  Environment*  ev = somGetGlobalEnvironment();
  ODBoolean     retCode = kODFalse;
  DraftInfoRec* draftrec;
  
  try
  {
    fSelectedDraft = kODNULL;

    // If a pointer to the DraftInfoRec is passed in, use it.  Otherwise
    // an index was passed in and should be used to traverse the list to find
    // the current DraftInfoRec.
    if (dInfoRec)
      draftrec = dInfoRec;
    else
      // Find draft in list
      draftrec = this->FindDraftInList(ItemSelected);

    if (draftrec) 
    {      
      // save handle to locked draft.
      if (fSelectedDraft = draftrec->GetDraft())
      {
        // Acquire the draft to increment the ref count.
        fSelectedDraft->Acquire(ev);

        // Open it.
        retCode = fActiveDocumentManager->OpenDraft(ev,fSelectedDraft,kODTrue);
      }
    }
  
  }
  catch (ODException _exception)
  {
    LOG("Exception occured in DraftWn::OpenDraft\n");
    if (fSelectedDraft)
       SaveAndRestoreEv1(fSelectedDraft);
    throw;
  }

  return retCode;
}
//----------------------------------------------------------------------------
//  RemoveDraft - Deletes the selected draft and removes it from the 
//                list of draft info records.
//----------------------------------------------------------------------------
ODBoolean DraftWindow::RemoveDraft(int ItemSelected, DraftInfoRec* dInfoRec)
{
  Environment*  ev = somGetGlobalEnvironment();
  ODBoolean     retCode = kODFalse;
  DraftInfoRec* draftrec;
  
  try
  {
    fSelectedDraft = kODNULL;

    // If a pointer to the DraftInfoRec is passed in, use it.  Otherwise
    // an index was passed in and should be used to traverse the list to find
    // the current DraftInfoRec.
    if (dInfoRec)
      draftrec = dInfoRec;
    else
      // Find draft in list
      draftrec = this->FindDraftInList(ItemSelected);

    if (draftrec) 
    {
      // save handle to locked draft.
      if (fSelectedDraft = draftrec->GetDraft()) 
      {
        // Acquire the draft to increment the ref count.
        // Note: Delete Draft takes care of releasing the draft.
        fSelectedDraft->Acquire(ev);
  
        // Delete it.
        retCode = fActiveDocumentManager->DeleteDraft(ev,draftrec);
      }
    }

  }
  catch (ODException _exception)
  {
    LOG("Exception occured in DraftWn::RemoveDraft\n");
    throw;
  }

  return retCode;
}

