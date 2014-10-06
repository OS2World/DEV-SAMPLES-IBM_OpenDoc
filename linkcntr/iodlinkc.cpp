//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odlinkcntr
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
/* @(#) 1.39 com/src/samples/linkcntr/iodlinkc.cpp, odlinkpart, od96os2, odos29714c 3/25/97 11:47:22 [4/2/97 17:19:55] */

#ifndef SOM_Module_linkcntr_Source
#define SOM_Module_linkcntr_Source
#endif
#define VARIABLE_MACROS
#define METHOD_MACROS

#define LinkContainer_Class_Source
#define M_LinkContainer_Class_Source

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
#include <time.h>
#include <string.h>
#include <StdTypIO.h>

#ifndef SOM_ODShape_xh
#include <Shape.xh>
#endif

#ifndef SOM_ODFacet_xh
#include <Facet.xh>
#endif

#ifndef SOM_ODFrame_xh
#include <Frame.xh>
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

#include <iostream.h>

#include <ODRegApi.h>
#include <ODDebug.h>


#ifndef SOM_ODLinkSpec_xh
#include <LinkSpec.xh>
#endif

#ifndef SOM_ODLink_xh
#include <Link.xh>
#endif

#ifndef SOM_ODMenubar_xh
#include <MenuBar.xh>
#endif

#ifndef SOM_ODLinkSource_xh
#include <LinkSrc.xh>
#endif

#ifndef SOM_ODClipboard_xh
#include <Clipbd.xh>
#endif

#include "iodlinkc.xih"

#ifndef SOM_ODFrameFacetIterator_xh
#include <FrFaItr.xh>
#endif

#ifndef SOM_ODDragAndDrop_xh
#include <DragDrp.xh>
#endif

#ifndef SOM_ODDragItemIterator_xh
#include <DgItmIt.xh>
#endif

#ifndef SOM_ODArbitrator_xh
#include <Arbitrat.xh>
#endif

#ifndef SOM_ODFocus_xh
#include <Foci.xh>
#endif

/**********************************************************************************
CONSTANTS AND TYPE DEFINITIONS
**********************************************************************************/

#define kPartHandlerName                   "LinkContainer"
#define kPartHandlerDisplayName            "Link Container"
#define kPartKindName                      "LinkContainer"
#define kPartKindDisplayName               "Link Container Kind"
#define kPartCategory                      "Linking"
#define kWindowsIcon                       "iodlinkc.ico"
#define kLinkContainerLinkInfo             "LinkContainer:LinkInfo"
#define kLinkContainerLinkSources          "LinkContainer:LinkSources"
#define kLinkContainerLinkDestinations     "LinkContainer:LinkDestinations"
#define kLinkContainerLinkCount            "LinkContainer:LinkCount"
//********************************************************************


#if defined (_PLATFORM_WIN32_)
#pragma linkage (SOMInitModule, system)
#endif

SOMEXTERN void SOMLINK SOMInitModule (long majorversion, long minorversion, string className)
{
    SOM_IgnoreWarning (majorversion);
    SOM_IgnoreWarning (minorversion);
    SOM_IgnoreWarning (className);
    LinkContainerNewClass(BaseContainer_MajorVersion,BaseContainer_MinorVersion);
}

#ifdef _PLATFORM_OS2_
#pragma export (SOMInitModule)
#endif



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


ODFacet* FirstFacet (Environment *ev, ODFrame *frame)
{

    ODFrameFacetIterator *ffitr  = frame->CreateFacetIterator(ev);
    ODFacet *facet = (ODFacet *)ffitr->First(ev);
    ODDeleteObject(ffitr);
    return facet;

}

inline ODULong GetIDForContentObject (ContentObject *cObj, ContentObject **tmpArray,
                                       ODULong num)
{
   int i;
   for (i = 0; i<num; i++)
      if (tmpArray[i] == cObj)
         return i;
   return num;

}


void UpdateLinkStatusofEmbeds (Environment *ev, LinkContainer *somSelf)
{
   ALink *itr;
   ALinkedList *embeds = somSelf->GetEmbeddedObjects (ev);

   for (itr = embeds->First (ev); itr->Content (ev); itr = itr->Next (ev))
   {
      ContentObject *cObj = (ContentObject *) itr->Content(ev);
      if (cObj->_get_containingFrame (ev)->GetLinkStatus (ev) == kODInLinkSource)
         cObj->_set_linkStatus (ev, kODInLinkSource);
   }
}


// The following routine throws a warning if the frame in which an editing
// opeartion is performed is a link destination

char warnDestMsg[] = "Editing is not allowed in this frame since it is marked \n"
;
char warnDestMsg1[] = "as a link destination.  Please break the link and retry.";
char warnDestMsg2[] = "Selection contains link sources or link destinations.  \n";
char warnDestMsg3[] = "Please press OK to break links and proceed, or Cancel to abort.";
char warnTitle[] = "Link Container Warning";

// UNIX specific code to display a modal dialog

#if defined (_PLATFORM_UNIX_)

#ifndef SOM_ODWindowState_xh
#include <WinStat.xh>
#endif

SOMEXTERN void SOMLINK okcancelCallBack(Widget widget, XtPointer client_data,
                                    XtPointer call_data)
{
   int *answer = (int *)client_data;
   XmAnyCallbackStruct *cbs = (XmAnyCallbackStruct *)call_data;

   switch (cbs->reason)
    {
        case XmCR_OK:
            *answer = 1;
            break;
        case XmCR_CANCEL:
            *answer = 2;
            break;
    }

}

ODBoolean ShowModalDialogOnX (ODFacet *facet, Environment *ev,
                   char *warnTitle, char *msgText, ODBoolean bShowCancel)
{
   ODBoolean result = kODFalse;

   Widget topLevelShellWidget = facet->GetFacetWidget (ev);
   if (!topLevelShellWidget)
     return result;

   Arg args[2];
   XtSetArg(args[0], XmNdeleteResponse, XmDO_NOTHING);
   XtSetArg(args[1], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL);

   Widget dialog = XmCreateInformationDialog(topLevelShellWidget,
                                              "showwarningDest", args, 2);
   XmString title = XmStringCreateLocalized(warnTitle);
   XmString myMsg = XmStringCreateLocalized(msgText);

   XtVaSetValues(dialog,
                  XmNdialogTitle, title,
                  XmNmessageString, myMsg,
                  NULL);
   XmStringFree(myMsg);
   XmStringFree(title);

   // remove cancel and help buttons from dialog.
   XtUnmanageChild (XmMessageBoxGetChild(dialog, XmDIALOG_HELP_BUTTON));
   if (bShowCancel == kODFalse)
      XtUnmanageChild (XmMessageBoxGetChild(dialog, XmDIALOG_CANCEL_BUTTON));

   // add callbacks for buttons
   int answer = 0;

   XtAddCallback(dialog, XmNokCallback,
                  (XtCallbackProc)okcancelCallBack, (XtPointer)&answer);
   if (bShowCancel)
      XtAddCallback(dialog, XmNcancelCallback,
                  (XtCallbackProc)okcancelCallBack, (XtPointer)&answer);

   // display dialog
   XtManageChild(dialog);

   // get app context
   XtAppContext app = facet->GetFrame(ev)->GetStorageUnit(ev)->
                GetSession(ev)->GetWindowState(ev)->GetAppContext(ev);

   while (answer == 0){
      XtAppProcessEvent (app, XtIMAll);
      XSync(XtDisplay(dialog), 0);
   }

   if (answer == 1)
      result = kODTrue;

   XtUnmanageChild (dialog);
   XSync(XtDisplay(dialog), 0);
   XmUpdateDisplay(dialog);

   return result;
};

#endif // Aix specific modal dialog function


// Warning dialog for non-explicit destination.. cannot break link from here

ODBoolean ShowWarningForDest (ODFacet *facet, Environment *ev)
{
   ODBoolean warnResult = kODFalse;
   char msgText[256] = "";
   strcat (msgText, warnDestMsg);
   strcat (msgText, warnDestMsg1);

#if defined (_PLATFORM_WIN32_)

    MessageBox (facet->GetWindow(ev)->GetPlatformWindow(ev), msgText, warnTitle,
                            MB_APPLMODAL | MB_OK);

#elif defined (_PLATFORM_OS2_)

   WinMessageBox (HWND_DESKTOP, facet->GetWindow(ev)->GetPlatformWindow(ev),
                            msgText, warnTitle, 0, MB_APPLMODAL | MB_OK | MB_MOVEABLE);

#elif defined (_PLATFORM_UNIX_)

   ShowModalDialogOnX (facet, ev, warnTitle, msgText, kODFalse);

#endif
   return warnResult;
}


// Warning dialog for explicit destination.. give user an option to break link or abort

ODBoolean ShowWarningForEmbed (ODFacet *facet, Environment *ev)
{
   ODBoolean warnResult = kODFalse;
   char msgText[256] = "";
   strcat (msgText, warnDestMsg2);
   strcat (msgText, warnDestMsg3);

#if defined (_PLATFORM_WIN32_)

    int result = MessageBox (facet->GetWindow(ev)->GetPlatformWindow(ev), msgText, warnTitle,
                            MB_APPLMODAL | MB_OKCANCEL);
    if (result == IDOK)
       warnResult = kODTrue;

#elif defined (_PLATFORM_OS2_)

   int result =  WinMessageBox (HWND_DESKTOP, facet->GetWindow(ev)->GetPlatformWindow(ev),
                            msgText, warnTitle, 0, MB_APPLMODAL | MB_OKCANCEL | MB_MOVEABLE);
    if (result == MBID_OK)
       warnResult = kODTrue;

#elif defined (_PLATFORM_UNIX_)

   warnResult = ShowModalDialogOnX (facet, ev, warnTitle, msgText, kODTrue);

#endif

   return warnResult;
}

// GetLinkSource does the following:
//   - Receives a pointer to a list of all the link sources (l) and a pointer to a list
//     of frames that we want tested.  
//   - If the entire list of frames comprises exactly one of the link sources in "l,"
//     then we return a pointer to the SourceOfLink structure for the link.

SourceOfLink *GetLinkSource (Environment *ev, ALinkedList *candidates,  ALinkedList *l)
{
    ALink *itr = kODNULL;
    ODBoolean foundOne = kODFalse;
    SourceOfLink *source = kODNULL;

    for(itr = l->First(ev); (itr->Content(ev) && !foundOne); itr=itr->Next(ev))
    {
         foundOne = kODTrue;
         source = (SourceOfLink *) itr->Content(ev);
         int i;
	 if (source->num == candidates->Count(ev)) {
	   for (i = 0; i < source->num; i++) {
	     if (!candidates->Contains(ev, source->sourceObjects[i])) {
	       foundOne = kODFalse;
               break;
	     }
	   }
	 }
	 else
	   foundOne = kODFalse;
    }
    return (foundOne ? source : kODNULL);
}

// GetLinkDestination does the following:
//   - Receives a pointer to a list of all the link destinations (l) and a pointer to a list
//     of frames that we want tested.  
//   - If the entire list of frames comprises exactly one of the link destinations in "l,"
//     then we return a pointer to the DestOfLink structure for the link.

DestOfLink *GetLinkDestination (Environment *ev, ALinkedList *candidates,  ALinkedList *l)
{
    ALink *itr = kODNULL;
    ODBoolean foundOne = kODFalse;
    DestOfLink *dest = kODNULL;

    for(itr = l->First(ev); (itr->Content(ev) && !foundOne); itr=itr->Next(ev))
    {
         foundOne = kODTrue;
         dest = (DestOfLink *) itr->Content(ev);
         int i;
	 if (dest->num == candidates->Count(ev)) {
	   for (i = 0; i < dest->num; i++) {
	     if (!candidates->Contains(ev, dest->destObjects[i])) {
	       foundOne = kODFalse;
               break;
	     }
	   }
	 }
	 else
	   foundOne = kODFalse;
    }
    return (foundOne ? dest : kODNULL);
}

ODBoolean IsInLinkSource (Environment *ev, ContentObject *cObj, ALinkedList *l)
{
    ALink *itr = kODNULL;

    for(itr = l->First(ev); itr->Content(ev); itr=itr->Next(ev))
    {
         SourceOfLink *source = (SourceOfLink *) itr->Content(ev);
         int i;
         for (i = 0; i < source->num; i++) {
            if (source->sourceObjects[i] == cObj) {
               return kODTrue;
            }
         }
    }
    return kODFalse;
}


ODBoolean IsInLinkDestination (Environment *ev, ContentObject *cObj, ALinkedList *l)
{
    ALink *itr = kODNULL;

    for(itr = l->First(ev); itr->Content(ev); itr=itr->Next(ev))
    {
         DestOfLink *dest = (DestOfLink *) itr->Content(ev);
         int i;
         for (i = 0; i < dest->num; i++) {
            if (dest->destObjects[i] == cObj) {
               return kODTrue;
            }
         }
    }
    return kODFalse;
}
//--------------------------------------------------------------------------
// ODPart --> LinkStatusChanged
//
//      Should notify this part that the link status of one of its display
//      frames has changed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerLinkStatusChanged
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerLinkStatusChanged");

    ODLinkStatus status = frame->GetLinkStatus (ev);

    ALink *itr;
    ALinkedList *list = somSelf->GetEmbeddedObjects (ev);

    for (itr = list->First(ev); itr->Content(ev); itr = itr->Next(ev))
    {
       ContentObject *cObj = (ContentObject *) itr->Content(ev);
       if (cObj->_get_containingFrame(ev) == frame)
          cObj->_set_linkStatus (ev, status);
    }

}



//--------------------------------------------------------------------------
// ODPart --> RevealLink
//
//      Should show the content at the source of a link.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerRevealLink
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODLinkSource    *linkSource     // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerRevealLink");


}


//--------------------------------------------------------------------------
// ODPart --> CreateLink
//
//      Should create a link-source object for this part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODLinkSource*
SOMLINK         LinkContainerCreateLink
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODByteArray     *data           // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerCreateLink");

    SourceOfLink *source = new SourceOfLink;
    memset(source, 0, sizeof(SourceOfLink));

    try {

       ODDraft* myDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
       ALinkedList *ObjectsToLink = kODNULL;
       memcpy(&ObjectsToLink, data->_buffer, sizeof (ALinkedList*));

       source->linkSource = myDraft->CreateLinkSource(ev, somSelf);
       source->num = ObjectsToLink->Count(ev);
       source->sourceObjects = (ContentObject**) SOMMalloc (source->num * sizeof(ContentObject*));
       ALink *itr = kODNULL;
       int i = 0;

       for(itr = ObjectsToLink->First(ev); itr->Content(ev); itr=itr->Next(ev))
       {
           source->sourceObjects[i++] = (ContentObject*) itr->Content(ev);
           if (((ContentObject*) itr->Content(ev))->_get_linkStatus(ev) != kODInLinkDestination)
              ((ContentObject*) itr->Content(ev))->_set_linkStatus (ev, kODInLinkSource);
       }

       _fAllLinkSources->AddLast (ev, source);

       source->change = _fSession->UniqueUpdateID(ev);
       somSelf->WriteSingleLink (ev, (void*)source, source->change);



   }
   catch (ODException _exception) {

     if (source->linkSource)
        source->linkSource->Release(ev);
     delete source;
   }

   //According to recipes, we need to acquire link source
   source->linkSource->Acquire(ev);
   return source->linkSource;

}

//--------------------------------------------------------------------------
//  LinkContainer->WriteLinkSpec
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerWriteLinkSpec
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *toSU           // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerWriteLinkSpec");

    try {


    ALinkedList *ObjectsToLink = new ALinkedList;
    PRINT("WriteLinkSpec:ObjectsToLink %lx\n", ObjectsToLink);
    ALinkedList *fSelectedObjects = somSelf->GetSelectedObjects(ev);
    ALink* itr = kODNULL;

    for(itr = fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
    {
         ContentObject *lObj = (ContentObject*) itr->Content(ev);
         ObjectsToLink->AddLast(ev, lObj);
    }

    ODByteArray *theLinkSpecData = CreateByteArray((void*)&ObjectsToLink, sizeof(ObjectsToLink));
    ODDraft* myDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
    toSU->AddProperty(ev, kODPropLinkSpec);
    ODLinkSpec* linkSpec = myDraft->CreateLinkSpec(ev, somSelf, theLinkSpecData);
    linkSpec->WriteLinkSpec(ev, toSU);

    _fLastSavedList = ObjectsToLink;

    }
    catch (...) {}


}


//--------------------------------------------------------------------------
//  LinkContainer->CompleteResizeOperation
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerCompleteResizeOperation
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ContentObject *contentObject,
                ODULong       resizeFlags,
                ODPoint       *winPoint,
                ODFacet       *facet
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerCompleteResizeOperation");

    try {

       ContentObject *cObj = contentObject;
       if (!cObj)
          cObj = (ContentObject *)somSelf->GetSelectedObjects (ev)->
                                                      First(ev)->Content(ev);

       if (cObj && (cObj->_get_linkStatus(ev) == kODInLinkDestination))
       {
          if (IsInLinkDestination (ev, cObj, _fAllLinkDestinations))
          {
             if (ShowWarningForEmbed (facet, ev))
             {
                // break link
                somSelf->BreakAllLinks (ev, cObj);
             }
             else
             {
                if (somSelf->GetMouseMode (ev) == kMouseModeTrackResize)
                   somSelf->AbortMouseTracking (ev, facet->GetFrame(ev));
                facet->Invalidate (ev, kODNULL, kODNULL);
                return;
             }
          }
          else
          {
             ShowWarningForDest (facet, ev);
             if (somSelf->GetMouseMode (ev) == kMouseModeTrackResize)
                somSelf->AbortMouseTracking (ev, facet->GetFrame(ev));
             facet->Invalidate (ev, kODNULL, kODNULL);
             return;
          }
       }

       LinkContainer_parent_BaseContainer_CompleteResizeOperation (somSelf, ev,
                                      contentObject, resizeFlags, winPoint, facet);
    }
    catch (...) {}


}


//--------------------------------------------------------------------------
//  LinkContainer->CompleteMoveOperation
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerCompleteMoveOperation
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODFrame      *containingFrame,
                ODPoint      *offset
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerCompleteMoveOperation");

    try {

       ODBoolean embedWarn = kODFalse, destWarn = kODFalse;
       ALink *itr;
       ALinkedList *objects = somSelf->GetSelectedObjects (ev);

       for (itr = objects->First(ev); itr->Content(ev); itr = itr->Next(ev))
       {
          ContentObject *cObj = (ContentObject *)(itr->Content(ev));
          ODLinkStatus ls = cObj->_get_linkStatus(ev);

          if (ls == kODInLinkDestination)
          {
             //chaeck if there are any explicit links here or link status is
             // just inherited from parent
	    
	    if (IsInLinkDestination (ev, cObj, _fAllLinkDestinations)) {

	      //  We check to see if the selection is one single entire destination.  If it is, then
	      //  we will allow the move.  We only disallow the move if the selection is part of a destination,
	      //  since such a move represents a change in that destination.  Destinations are considered to be
	      //  read-only, so changes are not allowed.
	      DestOfLink   *isEntireLinkDestination = GetLinkDestination(ev, objects, _fAllLinkDestinations);	     
	      if (isEntireLinkDestination)
		embedWarn = kODFalse;
	      else
                embedWarn = kODTrue;
	    }
             else
                destWarn = kODTrue;
          }

       }

       ODFacet  *facet = FirstFacet (ev, containingFrame);

       if (destWarn)
       {
          ShowWarningForDest (facet, ev);
          if (somSelf->GetMouseMode (ev) == kMouseModeTrackMove)
             somSelf->AbortMouseTracking (ev, containingFrame);
          facet->Invalidate (ev, kODNULL, kODNULL);
          return;
       }

       else if (embedWarn)
       {
             if (ShowWarningForEmbed (facet, ev))
             {
                // break link
                for (itr = objects->First(ev); itr->Content(ev); itr = itr->Next(ev))
                {
                   ContentObject *cObj = (ContentObject *)(itr->Content(ev));
                   somSelf->BreakAllLinks (ev, cObj);
                }
             }
             else
             {
                if (somSelf->GetMouseMode (ev) == kMouseModeTrackResize)
                   somSelf->AbortMouseTracking (ev, containingFrame);
                facet->Invalidate (ev, kODNULL, kODNULL);
                return;
             }
       }

       LinkContainer_parent_BaseContainer_CompleteMoveOperation (somSelf, ev,
                                      containingFrame, offset);
    }
    catch (...) {}


}

//--------------------------------------------------------------------------
//  LinkContainer->DeleteSelection
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerDeleteSelection
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODULong         type
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerDeleteSelection");

    try {

       ODBoolean embedWarn = kODFalse, destWarn = kODFalse;
       ALink *itr;
       ODFrame *cF = kODNULL;
       ALinkedList *objects = somSelf->GetSelectedObjects (ev);

       for (itr = objects->First(ev); itr->Content(ev); itr = itr->Next(ev))
       {
          ContentObject *cObj = (ContentObject *)(itr->Content(ev));
          ODLinkStatus ls = cObj->_get_linkStatus(ev);

          if (ls == kODInLinkDestination)
          {
             //chaeck if there are any explicit links here or link status is
             // just inherited from parent

             if (IsInLinkDestination (ev, cObj, _fAllLinkDestinations))
                embedWarn = kODTrue;
             else
                destWarn = kODTrue;
          }

          if (ls == kODInLinkSource)
             embedWarn = IsInLinkSource (ev, cObj, _fAllLinkSources);

          if (!cF)
             cF = cObj->_get_containingFrame (ev);
       }

       if (destWarn)
       {
          ShowWarningForDest (FirstFacet (ev, cF), ev);
           return;
       }

       if (embedWarn)
       {
          ODBoolean warnResult = ShowWarningForEmbed (FirstFacet (ev, cF), ev);
          if (warnResult)
          {
             // break links
             for (itr = objects->First(ev); itr->Content(ev); itr = itr->Next(ev))
             {
                ContentObject *cObj = (ContentObject *)(itr->Content(ev));
                somSelf->BreakAllLinks (ev, cObj);
             }
          }
          else
             return;
       }

       // Now that we have decided to delete selection, make sure
       // that the link spec kept on clipboard is up-to-date

       if (type != OBJECT_DRAGGED)
       {
          // Looks like I was the last one to update clipboard

          ODClipboard*  clipboard = _fSession->GetClipboard(ev);
          ODFrame *frame = (ODFrame *)somSelf->GetDisplayFrames(ev)->First(ev)->Content(ev);
          ODBoolean gotCB = _fSession->GetArbitrator(ev)->RequestFocus(ev,
                                    _fSession->Tokenize(ev,kODClipboardFocus), frame);
          ODStorageUnit* clipSU = clipboard->GetContentStorageUnit(ev);

          if (gotCB && _fLastSavedList && clipSU->Exists (ev, kODPropLinkSpec, kODNULL, 0))
          {
             //update savedList based on what's being deleted

             for (itr = objects->First(ev); itr->Content(ev); itr = itr->Next(ev))
             {
                ContentObject *cObj = (ContentObject *)(itr->Content(ev));
                if (_fLastSavedList->Contains (ev, cObj))
                   _fLastSavedList->Remove (ev, cObj);

             } // end for

             if (_fLastSavedList->Count(ev) == 0)
             {
                // remove the property and export clipboard and set updateID
                PRINT("Clearing link Spec\n");
                ODSURemoveProperty (ev, clipSU, kODPropLinkSpec);
                clipboard->ExportClipboard(ev);
                delete _fLastSavedList;
                _fLastSavedList = kODNULL;
             }
             else
                PRINT("Still keeping link spec\n");

          } // endif .. gotCB

          // relinquish focus now
          if (gotCB)
          {
             _fSession->GetArbitrator(ev)->RelinquishFocus(ev,
                            _fSession->Tokenize(ev,kODClipboardFocus), frame);
          }

       } // endif .. not OBJECT_DRAGGED

       LinkContainer_parent_BaseContainer_DeleteSelection (somSelf, ev, type);

    }
    catch (...) {}

}


//--------------------------------------------------------------------------
//  LinkContainer->StartDrag
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerStartDrag
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODEventData     *event,          // in
                ODFrame         *embeddedFrame,  // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo,
                ODCloneKind     cloneKind
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerStartDrag");

    try {

       ALinkedList *list = somSelf->GetSelectedObjects (ev);
       ALink *itr;
       ODCloneKind cKind = kODCloneCut;

       for (itr = list->First(ev); itr->Content(ev); itr = itr->Next (ev))
       {
          ContentObject *cObj = (ContentObject *) itr->Content(ev);
          if (cObj->_get_linkStatus (ev) != kODNotInLink)
          {
             cKind = kODCloneCopy;
             break;
          }
       } // end for

       LinkContainer_parent_BaseContainer_StartDrag (somSelf, ev,
                 event, embeddedFrame, facet, eventInfo, cKind);

    }
    catch (...) {}

}

//--------------------------------------------------------------------------
//  LinkContainer->PasteSelectionAs
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerPasteSelectionAs
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODFacet         *facet,          // in
                ODPoint         *toWhere
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerPasteSelectionAs");

    try {

      ODPasteAsResult result;
      ODClipboard*  clipboard = _fSession->GetClipboard(ev);
      ODStorageUnit* clipSU = clipboard->GetContentStorageUnit(ev);
      ODTypeToken viewType = _fSession->Tokenize(ev, kODViewAsFrame );

      // invoke the dialog; if it returns true, the user selected "OK"
      if(!_fSession->GetClipboard(ev)->ShowPasteAsDialog(ev, kODTrue,
                    kODPasteAsEmbedOnly, facet, viewType, &result))
         return;

      if( result.pasteLinkSetting == kODFalse) {
          somSelf->PasteSelection(ev, facet, toWhere);
         return;
      }

      ODDraft *myDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
      ODLinkSpec* linkSpec = myDraft->CreateLinkSpec(ev, kODNULL, kODNULL);

      clipSU->Focus(ev, kODPropLinkSpec, kODPosUndefined, kODNULL, 0, kODPosUndefined);
      linkSpec->ReadLinkSpec(ev, clipSU);

      ODLink *link = myDraft->AcquireLink(ev, kODNULLID, linkSpec);

      if (link == kODNULL) {
         WARNMSG (WARN_INDEX(-1), "Link Could not be acquired. Linking failed.");
         return;
      }
#ifndef _PLATFORM_AIX_
      if (result.selectedKind == kODNULL) {
         WARNMSG (WARN_INDEX(-1), "No kind selected. Linking failed.");
         return;
      }
#endif

      P_DestOfLink pDest = new DestOfLink;
      memset(pDest, 0, sizeof(DestOfLink));
      _floatingDest = (void*) pDest;

      pDest->link = link;
      pDest->containingFrame = facet->GetFrame(ev);
      pDest->info.change = pDest->link->GetUpdateID(ev);
      time(&pDest->info.creationTime);
#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
      pDest->info.kind = new char[strlen(result.selectedKind)+1];
      strcpy(pDest->info.kind,result.selectedKind);
#else
      pDest->info.kind = new char[strlen("Unknown")+1];
      strcpy(pDest->info.kind,"Unknown");
#endif
      //      pDest->info.autoUpdate = kODTrue; // revisit this LATER.
      pDest->info.autoUpdate = result.autoUpdateSetting;
      pDest->destinationPoint = *toWhere;

      pDest->link->RegisterDependent(ev, _fPartWrapper, kODUnknownUpdate);

      somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);


    }
    catch (...) {}

    return;
}


//--------------------------------------------------------------------------
// ODPart --> Drop
//
//      Should move or copy the dragged data into this part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODDropResult
SOMLINK         LinkContainerDrop
                (
                LinkContainer       *somSelf,   // in
                Environment         *ev,        // in
                ODDragItemIterator  *dropInfo,  // in
                ODFacet             *facet,     // in
                ODPoint             *where      // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerDrop");

    ODDropResult        dropResult = kODDropFail;
    ODBoolean readOnly = (somSelf->GetStorageUnit(ev)->GetDraft(ev)->GetPermissions(ev) == kODDPReadOnly);

    if (readOnly) {
       WARNMSG(WARN_INDEX(-1), "Document is read only. Drop is not accepted.");
       return dropResult;
    }

    if (facet->GetFrame (ev)->GetLinkStatus (ev) == kODInLinkDestination)
    {
       ODBoolean warnResult = ShowWarningForDest (facet, ev);
       return dropResult;
    }

  try {

    // Get proper attributes

    ODULong             attributes;
    attributes = _fSession->GetDragAndDrop(ev)->GetDragAttributes(ev);

    if (!(attributes & kODDropIsLink))
        return LinkContainer_parent_BaseContainer_Drop (somSelf, ev, dropInfo, facet, where);

    //show drop as dialog

    ODPasteAsResult result;
    ODTypeToken viewType = _fSession->Tokenize(ev, kODViewAsFrame);
    ODStorageUnit *dropSU = dropInfo->First(ev);

#if defined(_PLATFORM_OS2_)

          // some OS/2 specific stuff for drag-drop from WPShell
          if ( !dropSU->Exists(ev, kODPropContents, (ODValueType)kODDragitem, 0))
          {
             // nothing to process... (bug)
             return dropResult;
          } /* end if */

          // get the dragitem (actual pm structure)
          dropSU->Focus(ev, kODPropContents, kODPosUndefined, (ODValueType)kODDragitem, 0, kODPosUndefined);

          // create a view of our focused value for the drag manager
          ODStorageUnitView *dropView = dropSU->CreateView(ev);

          // ask the drag manager to get it for us
          if ( ! _fSession->GetDragAndDrop(ev)-> GetDataFromDragManager(ev,  dropView,
                                          &dropSU ) )
          {
             // error in transfer
             return dropResult;
          }
#endif

    if(!_fSession->GetDragAndDrop(ev)->ShowPasteAsDialog(ev, kODTrue,
                    kODPasteAsEmbedOnly, facet, viewType, dropSU, &result))
         return dropResult;

    if( result.pasteLinkSetting == kODFalse)
        return LinkContainer_parent_BaseContainer_Drop (somSelf, ev, dropInfo, facet, where);

    if (result.selectedKind == kODNULL) {
       WARNMSG (WARN_INDEX(-1), "No kind selected. Linking failed.");
       return dropResult;
    }

    // we need to drop-link

    ODDraft *myDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
    ODLinkSpec* linkSpec = myDraft->CreateLinkSpec(ev, kODNULL, kODNULL);

    dropSU->Focus(ev, kODPropLinkSpec, kODPosUndefined, kODNULL, 0, kODPosUndefined);
    linkSpec->ReadLinkSpec(ev, dropSU);

    ODLink *link = myDraft->AcquireLink(ev, kODNULLID, linkSpec);

    if (link == kODNULL) {
       WARNMSG (WARN_INDEX(-1), "Link Could not be acquired. Linking failed.");
       return dropResult;
    }

    // Create and fill DestinationOfLink structure

    P_DestOfLink pDest = new DestOfLink;
    memset(pDest, 0, sizeof(DestOfLink));
    _floatingDest = (void*) pDest;

    pDest->link = link;
    pDest->containingFrame = facet->GetFrame(ev);
    pDest->info.change = pDest->link->GetUpdateID(ev);
    time(&pDest->info.creationTime);
    pDest->info.kind = new char[strlen(result.selectedKind)+1];
    strcpy(pDest->info.kind,result.selectedKind);
    // pDest->info.autoUpdate = kODTrue; // revisit this LATER.
    pDest->info.autoUpdate = result.autoUpdateSetting;
    pDest->destinationPoint = *where;

    pDest->link->RegisterDependent(ev, _fPartWrapper, kODUnknownUpdate);

    somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);


    dropResult = kODDropCopy;

  }
  catch (...) {}

  return dropResult;

}


//--------------------------------------------------------------------------
//  LinkContainer->GetAllLinkSources
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerGetAllLinkSources
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ContentObject   *cObj,
                ALinkedList     *l
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerGetAllLinkSources");

    try {

    ALink *itr = kODNULL;

    for(itr = _fAllLinkSources->First(ev); itr->Content(ev); itr=itr->Next(ev))
    {
         SourceOfLink *source = (SourceOfLink *) itr->Content(ev);
         int i;
         for (i = 0; i < source->num; i++) {
            if (source->sourceObjects[i] == cObj) {
               l->AddLast(ev, source);
               break;
            }
         }
    }

    }
    catch (...) {}

}



//--------------------------------------------------------------------------
//  LinkContainer->GetAllLinkDestinations
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerGetAllLinkDestinations
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ContentObject   *cObj,
                ALinkedList     *l
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerGetAllLinkDestinations");

    try {

    ALink *itr = kODNULL;

    for(itr = _fAllLinkDestinations->First(ev); itr->Content(ev); itr=itr->Next(ev))
    {
         DestOfLink *dest = (DestOfLink *) itr->Content(ev);
         int i;
         for (i = 0; i < dest->num; i++) {
            if (dest->destObjects[i] == cObj) {
               l->AddLast(ev, dest);
               break;
            }
         }
    }

    }
    catch (...) {}

}


//--------------------------------------------------------------------------
//  LinkContainer->BreakAllLinks
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerBreakAllLinks
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ContentObject   *cObj
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerBreakAllLinks");

    try {

       ALinkedList *l = new ALinkedList;
       ALink *itr;

       // break all the link sources
       somSelf->GetAllLinkSources(ev, cObj, l);
       for (itr = l->First(ev); itr->Content(ev); itr = itr->Next(ev))
       {
          SourceOfLink *source = (SourceOfLink *)itr->Content(ev);
          _fAllLinkSources->Remove (ev, source);

          source->linkSource->SetSourcePart (ev, kODNULL);
          source->linkSource->Release(ev);

          for (int i = 0; i < source->num; i++)
             source->sourceObjects[i]->_set_linkStatus (ev, kODNotInLink);

          delete source;
       }

       l->RemoveAll(ev);

       // break all the link destinations
       somSelf->GetAllLinkDestinations(ev, cObj, l);
       for (itr = l->First(ev); itr->Content(ev); itr = itr->Next(ev))
       {
          DestOfLink *dest = (DestOfLink *)itr->Content(ev);
          _fAllLinkDestinations->Remove (ev, dest);

          dest->link->Release(ev);
          dest->link->UnregisterDependent (ev, _fPartWrapper);

          for (int i = 0; i < dest->num; i++)
          {
             if (IsInLinkSource (ev, cObj, _fAllLinkDestinations))
                dest->destObjects[i]->_set_linkStatus (ev, kODInLinkSource);
             else
                dest->destObjects[i]->_set_linkStatus (ev, kODNotInLink);
          }

          delete dest;
       }

       delete l;
    }
    catch (...) {}

}


//--------------------------------------------------------------------------
//  LinkContainer->PropagateChangesToLinks
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerChangeNotification
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODULong          reason,
                ODFrame         *frame,
                ContentObject  *content,        // in
                ODBoolean       bPropagate,     // in
                ODUpdateID      updateID
                )
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerChangeNotification");

    try {

       if ((reason == BCC_EMBED) || (reason == BCC_DROP) || (reason == BCC_PASTE))
       {
          // If my frame is a link source, then make sure that all my embeds are too
          // If my frame is a destination, this code should not be reached
          // if my frame is not in link then leave the embeds as they are
          UpdateLinkStatusofEmbeds (ev, somSelf);
       }

       ODUpdateID id = updateID;

       if (content) {

          ALinkedList *allSources = new ALinkedList;
          somSelf->GetAllLinkSources (ev, content, allSources);
          ALink *itr = kODNULL;

          if (allSources->Count(ev) && !id)
             id = _fSession->UniqueUpdateID (ev);

          for(itr = allSources->First(ev); itr->Content(ev); itr=itr->Next(ev))
          {
             SourceOfLink *source = (SourceOfLink *) itr->Content(ev);
	     source->change = id;
	     if (source->linkSource->IsAutoUpdate(ev))
	       somSelf->WriteSingleLink (ev, (void*)source, id);

          }
          delete allSources;

       } // if content

       LinkContainer_parent_BaseContainer_ChangeNotification (somSelf, ev, reason, frame,
                                            content, bPropagate, id);
    }
    catch (...) {}

}


//--------------------------------------------------------------------------
//  LinkContainer->WriteSingleLink
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerWriteSingleLink
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                void            *sourceoflink,  // in
                ODUpdateID     change)
{

    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerWriteSingleLink");

    ODLinkKey linkKey;
    SourceOfLink *source = (SourceOfLink*)sourceoflink;
    ODLinkSource *linkSource = source->linkSource;
    ODUpdateID previousID = linkSource->GetUpdateID(ev);

    try {

       if (linkSource->Lock(ev, 0, &linkKey) ) {

          //  Get and clear the linkSU
          linkSource->Clear(ev, change, linkKey);
          ODStorageUnit* toSU = linkSource->GetContentStorageUnit(ev, linkKey);

          // Write data
          if ((source->num == 1) && (source->sourceObjects[0]->_get_objType(ev) == COBJ_FRAMECLASS)) {

             ODFrame *frame = ((ContentFrame *)source->sourceObjects[0])->_get_myFrame(ev);
             somSelf->WriteSingleFrame (ev, frame, toSU, kODCloneToLink);
          }
          else {

             //Multiple selection case
             somSelf->WriteKindInfo (ev, toSU);

             BCCloneInfo cloneInfo;
             memset (&cloneInfo, 0, sizeof(BCCloneInfo));
             cloneInfo.refPoint = new ODPoint;

             // refPoint computation
             int i = 0;
             ODRect bbox = source->sourceObjects[0]->_get_boundingRect(ev);
             cloneInfo.refPoint->x = bbox.left;
             cloneInfo.refPoint->y = bbox.top;

             for (i=1; i<source->num; i++) {
                bbox = source->sourceObjects[i]->_get_boundingRect(ev);
                if (bbox.left < cloneInfo.refPoint->x)
                   cloneInfo.refPoint->x = bbox.left;
#if defined (_PLATFORM_WIN32_) || defined (_PLATFORM_UNIX_)
                if (bbox.top < cloneInfo.refPoint->y)
#elif defined(_PLATFORM_OS2_)
                if (bbox.top > cloneInfo.refPoint->y)
#endif
                   cloneInfo.refPoint->y = bbox.top;
             }

             // clone stuff
             ODDraft *fromDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
             ODDraftKey key = 0;
             key = fromDraft->BeginClone (ev, toSU->GetDraft(ev), kODNULL, kODCloneToLink);
             cloneInfo.key = key;

             ODSUAddPropValue (ev, toSU, kODPropEmbeddedFrames, kODStrongStorageUnitRef);

             ODSetULongProp (ev, toSU, kODNULL, kODNULL, source->num);


             for (i=0; i<source->num; i++) {

                // Store the object type.
                ODULong objType = source->sourceObjects[i]->_get_objType(ev);
                ODSetULongProp (ev, toSU, kODNULL, kODNULL, objType);

                // Write out the object.
                source->sourceObjects[i]->WriteContents (ev, toSU, CLONE_SELECTED, &cloneInfo);
             }

             fromDraft->EndClone (ev, key);


          }

          // Propagate to target
          linkSource->ContentUpdated(ev, change, linkKey);
          linkSource->Unlock(ev, linkKey);

       } // end if Lock

    }
    catch (ODException _exception) {

        linkSource->Clear(ev, previousID, linkKey);
    }


}


//--------------------------------------------------------------------------
// ODPart --> LinkUpdated
//
//      Should replace the content at each destination of a link
//      with new content from the updated link object.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerLinkUpdated
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODLink          *updatedLink,   // in
                ODUpdateID       id             // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerLinkUpdated");

    try {

    if (_floatingDest) {

       // This is the first link update
       if (updatedLink != ((DestOfLink*)_floatingDest)->link) {
          WARNMSG(WARN_INDEX(-1), "Unknown link passed in. Linking failed.");
          return;
       }

       ODLinkKey linkKey;
       ALinkedList *fEmbeddedObjects = somSelf->GetEmbeddedObjects(ev);
       DestOfLink *pDest = new DestOfLink;
       memcpy(pDest, _floatingDest, sizeof(DestOfLink));

       ODStorageUnit* fromSU = kODNULL;
       if (updatedLink->Lock(ev, 0, &linkKey) ) {

          try {
               fromSU = updatedLink->GetContentStorageUnit(ev, linkKey);
          }
          catch (ODException _exception) {
             int Error = ErrorCode();
             if (Error == kODErrNoLinkContent) {
                SetErrorCodeEv(ev, kODNoError);
                updatedLink->Unlock(ev, linkKey);
                delete pDest;
                return;
             }
             else
                ODSetSOMException(ev, _exception);
          }  // end catch

          if (fromSU->Exists(ev, kODPropContentFrame, kODWeakStorageUnitRef, 0))
          {
             ODFrame *embeddedFrame = somSelf->ReadSingleFrame (ev,
                            FirstFacet(ev, pDest->containingFrame),
                            fromSU, kODCloneFromLink, &(pDest->destinationPoint));

             ContentFrame *newObject = new ContentFrame();
             newObject->_set_myFrame(ev, embeddedFrame);
             fEmbeddedObjects->AddLast (ev, (ODPtr)newObject);
             pDest->num = 1;
             pDest->destObjects = (ContentObject**) SOMMalloc (sizeof(ContentObject*));
             pDest->destObjects[0] = newObject;
             newObject->_set_linkStatus (ev, kODInLinkDestination);
          }

          else if (somSelf->ReadKindInfo(ev, fromSU))
               {
                  BCCloneInfo cloneInfo;
                  memset (&cloneInfo, 0, sizeof(BCCloneInfo));

                  ODDraft *toDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
                  ODDraft *fromDraft = fromSU->GetDraft(ev);
                  ODDraftKey key = 0;
                  key = fromDraft->BeginClone (ev, toDraft, kODNULL, kODCloneFromLink);
                  cloneInfo.key = key;
                  cloneInfo.refPoint = &(pDest->destinationPoint);
                  cloneInfo.myFrame = pDest->containingFrame;

                  if ( ODSUExistsThenFocus (ev, fromSU, kODPropEmbeddedFrames, kODStrongStorageUnitRef))
                  {
                     ODULong num = 0;
                     pDest->num = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
                     pDest->destObjects =(ContentObject**)SOMMalloc(sizeof(ContentObject*)* (pDest->num));

                     for (int i = 0; i < pDest->num; i++) {

                        ODULong objType = 0;
                        objType = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);

                        ContentObject *contObj = 0;
                        somSelf->GetContentObjectFromObjType(ev, objType, &contObj);
                        if (contObj) {
                           contObj->ReadContents(ev, fromSU, CLONE_SELECTED, &cloneInfo);
                           fEmbeddedObjects->AddLast(ev, contObj);
                           pDest->destObjects[i] = contObj;
                           contObj->_set_linkStatus (ev, kODInLinkDestination);
                        }
                     } // end for

                  } // end if embeddedFrames

                  fromDraft->EndClone(ev, key);

               } // end if ReadKindInfo

          pDest->info.change     = updatedLink->GetUpdateID(ev);
          pDest->info.changeTime = updatedLink->GetChangeTime(ev);
          _fAllLinkDestinations->AddLast (ev, pDest);
          pDest->link->Unlock(ev, linkKey);

          pDest->containingFrame->ContentUpdated(ev, pDest->info.change);
          pDest->containingFrame->Invalidate (ev, kODNULL, kODNULL);

	  // If the user specified a manual update, we honor that here.  The recipe says
	  // that we should ignore it at first, to let the first update flow.  Now we
	  // start to honor that manual update.
	  if (!pDest->info.autoUpdate)
	    pDest->link->UnregisterDependent(ev, _fPartWrapper);

          delete _floatingDest;
          _floatingDest = kODNULL;

       } // if link->Lock

       else {
          delete pDest;
       }

    }  // end first time update

    else {

       // Update link from an established link
       ALink* itr = kODNULL;
       DestOfLink *pDest = kODNULL;

       for(itr = _fAllLinkDestinations->First(ev); itr->Content(ev); itr=itr->Next(ev))
       {
         if (((DestOfLink*) itr->Content(ev))->link == updatedLink)
            pDest = (DestOfLink*) itr->Content(ev);
       }
       if (!pDest) {
          WARNMSG (WARN_INDEX(-1), "Unknown Link. Linking Failed.");
          return;
       }

       ODLinkKey linkKey;
       if (updatedLink->Lock(ev, 0, &linkKey) ) {

          ODStorageUnit* fromSU = updatedLink->GetContentStorageUnit(ev, linkKey);

          if (fromSU->Exists(ev, kODPropContentFrame, kODWeakStorageUnitRef, 0))
          {
             if ((pDest->num != 1) || (pDest->destObjects[0]->_get_objType(ev) != COBJ_FRAMECLASS)) {
                WARNMSG (WARN_INDEX(-1), "Link does not match.");
                updatedLink->Unlock (ev, linkKey);
                return;
             }
             pDest->destObjects[0]->DeleteContents(ev, OBJECT_DELETED);
             ODFrame *embeddedFrame = somSelf->ReadSingleFrame (ev,
                             FirstFacet (ev, pDest->containingFrame),
                             fromSU, kODCloneFromLink, &(pDest->destinationPoint));
             ((ContentFrame*)(pDest->destObjects[0]))->_set_myFrame (ev, embeddedFrame);
             pDest->destObjects[0]->_set_linkStatus (ev, kODInLinkDestination);

          }  // end if SingleFrame

          else if (somSelf->ReadKindInfo(ev, fromSU))
               {
                  BCCloneInfo cloneInfo;
                  memset (&cloneInfo, 0, sizeof(BCCloneInfo));

                  ODDraft *toDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
                  ODDraft *fromDraft = fromSU->GetDraft(ev);
                  ODDraftKey key = 0;
                  key = fromDraft->BeginClone (ev, toDraft, kODNULL, kODCloneFromLink);
                  cloneInfo.key = key;
                  cloneInfo.refPoint = &(pDest->destinationPoint);
                  cloneInfo.myFrame = pDest->containingFrame;

                  if ( ODSUExistsThenFocus (ev, fromSU, kODPropEmbeddedFrames, kODStrongStorageUnitRef))
                  {
                     ODULong num = 0;
                     num = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
                     if (num != pDest->num) {
                        WARNMSG (WARN_INDEX(-1), "Links don't match. Linking failed.");
                        fromDraft->EndClone (ev, key);
                        pDest->link->Unlock (ev, linkKey);
                        return;
                     }

                     for (int i = 0; i < pDest->num; i++) {

                        ODULong objType = 0;
                        objType = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
                        pDest->destObjects[i]->DeleteContents(ev, OBJECT_DELETED);
                        pDest->destObjects[i]->ReadContents(ev, fromSU, CLONE_SELECTED, &cloneInfo);
                        pDest->destObjects[i]->_set_linkStatus (ev, kODInLinkDestination);

                     } // end for

                  } // end if embeddedFrames

                  fromDraft->EndClone (ev, key);

               } // end if ReadKindInfo

          pDest->info.change     = updatedLink->GetUpdateID(ev);
          pDest->info.changeTime = updatedLink->GetChangeTime(ev);
          pDest->link->Unlock(ev, linkKey);

          // notify the change but call parent only ONCE
          for (int i=0; i < pDest->num; i++)
             somSelf->ChangeNotification (ev, BCC_EMBEDUPDATED, kODNULL,
                   pDest->destObjects[i], ((pDest->num - i) == 1), pDest->info.change);

          pDest->containingFrame->Invalidate (ev, kODNULL, kODNULL);

       } // if link->Lock

    } // end if of linkUpdate

    }
    catch (...) {}
}




// -------------------------------------------------------------------------
// LinkContainer --> WriteContents
//
//      Writes part's content to storage.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         LinkContainerWriteContents
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *toSU,          // in
                BCCloneInfo     *cloneInfo,
                BCTransferKind  writeKind
                )

{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer", "LinkContainerWriteContents");

    LinkContainer_parent_BaseContainer_WriteContents(somSelf, ev, toSU, cloneInfo, writeKind);

    try {

       if (writeKind == CLONE_SELECTED) // copy or drag
          somSelf->WriteLinkSpec (ev, toSU);

       else if (writeKind == EXTERNALIZE) {

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)

          // Need to store links
          if (ODSUExistsThenFocus (ev, toSU, kLinkContainerLinkInfo, kODNULL))
             toSU->Remove (ev);

          ODULong numSources = _fAllLinkSources->Count(ev);
          ODULong numDestinations = _fAllLinkDestinations->Count(ev);
          if (!numSources && !numDestinations)
             return;



          // Store the number of sources and destinations

          ODSUAddPropValue (ev, toSU, kLinkContainerLinkInfo, kLinkContainerLinkCount);
          ODSetULongProp (ev, toSU, kODNULL, kODNULL, numSources);
          ODSetULongProp (ev, toSU, kODNULL, kODNULL, numDestinations);

          // Create the temp array for easy access to IDs
          ALinkedList *embeds = somSelf->GetEmbeddedObjects(ev);
          ALink *itr;
          ODULong numEmbeds = embeds->Count(ev);
          ContentObject **tmpArray = kODNULL;
          ODULong i=0;
          tmpArray = (ContentObject**) SOMMalloc (numEmbeds * sizeof (ContentObject*));

          for(itr = embeds->First(ev); itr->Content(ev); itr=itr->Next(ev))
             tmpArray[i++] = (ContentObject *)itr->Content(ev);


          // Store the source info

          ODSUAddPropValue (ev, toSU, kLinkContainerLinkInfo, kLinkContainerLinkSources);
          for(itr = _fAllLinkSources->First(ev); itr->Content(ev); itr=itr->Next(ev)) {

             SourceOfLink *source = (SourceOfLink *)itr->Content(ev);
             ODSetStrongSURefProp (ev, toSU, kODNULL, kODNULL, source->linkSource->GetID(ev));
             ODSetULongProp (ev, toSU, kODNULL, kODNULL, source->num);

             // Store the IDs for content objects
             for (i = 0; i< source->num; i++) {
                ODULong storID = GetIDForContentObject(source->sourceObjects[i], tmpArray, numEmbeds);
                ODSetULongProp (ev, toSU, kODNULL, kODNULL, storID);

             } // end for

          }  // end for

          // Store the destination info

          ODSUAddPropValue (ev, toSU, kLinkContainerLinkInfo, kLinkContainerLinkDestinations);
          for(itr = _fAllLinkDestinations->First(ev); itr->Content(ev); itr=itr->Next(ev)) {

             DestOfLink *dest = (DestOfLink *)itr->Content(ev);
             ODSetStrongSURefProp (ev, toSU, kODNULL, kODNULL, dest->link->GetID(ev));
             ODSetULongProp (ev, toSU, kODNULL, kODNULL, dest->num);

             // Store the IDs for content objects
             ODULong i;
             for (i = 0; i< dest->num; i++) {
                ODULong storID = GetIDForContentObject(dest->destObjects[i], tmpArray, numEmbeds);
                ODSetULongProp (ev, toSU, kODNULL, kODNULL, storID);

             } // end for

             ODSetStrongSURefProp (ev, toSU, kODNULL, kODNULL, dest->containingFrame->GetID(ev));
             ODSetPointProp (ev, toSU, kODNULL, kODNULL, &(dest->destinationPoint));
             StorageUnitSetValue(toSU, ev, sizeof(ODLinkInfo), (ODValue)&(dest->info));

          }  // end for

          SOMFree (tmpArray);

#endif
       } // end if EXTERNALIZE

    }   // end try
    catch (...) {}

}



// -------------------------------------------------------------------------
// LinkContainer --> ReadContents
//
//      Reads part's content to storage.
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         LinkContainerReadContents
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *fromSU,          // in
                BCCloneInfo     *cloneInfo,
                BCTransferKind  readKind
                )

{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer", "LinkContainerReadContents");

    LinkContainer_parent_BaseContainer_ReadContents(somSelf, ev, fromSU, cloneInfo, readKind);

    try {

       if (readKind == INTERNALIZE) {

          if (ODSUExistsThenFocus (ev, fromSU, kLinkContainerLinkInfo, kLinkContainerLinkCount)) {

             ODULong numSources = 0, numDestinations = 0;
             ODULong i=0;
             numSources = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
             numDestinations = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);

             // Create the tmpArray for easy access
             ALinkedList *embeds = somSelf->GetEmbeddedObjects(ev);
             ALink *itr;
             ODULong numEmbeds = embeds->Count(ev);
             ContentObject **tmpArray = kODNULL;
             tmpArray = (ContentObject**) SOMMalloc (numEmbeds * sizeof (ContentObject*));

             for(itr = embeds->First(ev); itr->Content(ev); itr=itr->Next(ev))
                tmpArray[i++] = (ContentObject *)itr->Content(ev);

             // Restore the link sources

             if (ODSUExistsThenFocus (ev, fromSU, kLinkContainerLinkInfo, kLinkContainerLinkSources)) {

                for (i = 0; i< numSources; i++) {

                   ODID linkSourceID = ODGetStrongSURefProp (ev, fromSU, kODNULL, kODNULL);
                   SourceOfLink *source = new SourceOfLink;

                   if (linkSourceID != kODNULLID) {
                      source->linkSource = fromSU->GetDraft(ev)->AcquireLinkSource(ev, linkSourceID);
                      source->linkSource->SetSourcePart(ev, somSelf->GetStorageUnit(ev));
                   }
                   else
                      WARNMSG(WARN_INDEX(-1), "Invalid SU reference.");

                   source->num = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
                   int numObj = 0;
                   source->sourceObjects = (ContentObject**) SOMMalloc (source->num *
                                                         sizeof (ContentObject*) );
                   for (numObj = 0; numObj < source->num; numObj++) {
                      ODULong id = 0;
                      id = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
                      source->sourceObjects[numObj] = tmpArray[id];
                      tmpArray[id]->_set_linkStatus (ev, kODInLinkSource);
                   } // end for

                   _fAllLinkSources->AddLast (ev, source);

                }// end for of link sources
             } // end if sources present

             // Restore the link dests

             if (ODSUExistsThenFocus(ev,fromSU, kLinkContainerLinkInfo, kLinkContainerLinkDestinations)) {

                for (i = 0; i< numDestinations; i++) {

                   ODID linkID = ODGetStrongSURefProp (ev, fromSU, kODNULL, kODNULL);
                   DestOfLink *dest = new DestOfLink;

                   if (linkID != kODNULLID) {
                      dest->link = fromSU->GetDraft(ev)->AcquireLink(ev, linkID, kODNULL);
                   }
                   else
                      WARNMSG(WARN_INDEX(-1), "Invalid destination SU reference.");

                   dest->num = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
                   int numObj = 0;
                   dest->destObjects = (ContentObject**) SOMMalloc (dest->num *
                                                         sizeof (ContentObject*) );
                   for (numObj = 0; numObj < dest->num; numObj++) {
                      ODULong id = 0;
                      id = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
                      dest->destObjects[numObj] = tmpArray[id];
                      tmpArray[id]->_set_linkStatus (ev, kODInLinkDestination);
                   } // end for

                   // Read in the frame, point, info etc..
                   ODID frameID = ODGetStrongSURefProp (ev, fromSU, kODNULL, kODNULL);
                   dest->containingFrame =
                      somSelf->GetStorageUnit(ev)->GetDraft(ev)->AcquireFrame(ev, frameID);

                   ODGetPointProp (ev, fromSU, kODNULL, kODNULL, &(dest->destinationPoint));
                   StorageUnitGetValue(fromSU, ev, sizeof(ODLinkInfo), &(dest->info));

                   _fAllLinkDestinations->AddLast (ev, dest);
                   // defect 25316: Need to add dest to _fAllLinkDests before registering
                   // it as a dependent (since LinkUpdated is called)
                   dest->link->RegisterDependent (ev, _fPartWrapper, dest->info.change);

                } // end for of link dests
             } // end if dests present

             SOMFree (tmpArray);

          } // end if links present
       } // end if INTERNALIZE

    }   // end try
    catch (...) {}

}

// -------------------------------------------------------------------------
// LinkContainer --> WriteSingleFrame
//
//      Write a single embedded frame to destination unit.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         LinkContainerWriteSingleFrame
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *embeddedFrame, // in
                ODStorageUnit   *toSU,          // in
                ODCloneKind     cloneKind
                )

{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer", "LinkContainerWriteSingleFrame");

    LinkContainer_parent_BaseContainer_WriteSingleFrame(somSelf, ev, embeddedFrame, toSU, cloneKind);

    try {

       if (cloneKind != kODCloneToLink)
          somSelf->WriteLinkSpec (ev, toSU);
    }
    catch (...) {}

}


//--------------------------------------------------------------------------
// ODPart --> AdjustMenus
//
//      Should prepare this part's menus for display.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerAdjustMenus
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerAdjustMenus");

    if (frame->GetLinkStatus(ev) != kODInLinkDestination)
    {
       LinkContainer_parent_BaseContainer_AdjustMenus (somSelf, ev, frame);
       ODMenuBar *MenuBar = somSelf->GetMenuBar (ev);
       ODBoolean bEnable =_fSession->GetClipboard(ev)->CanEmbed(ev);
       bEnable &= (somSelf->GetStorageUnit(ev)->GetDraft(ev)->GetPermissions(ev) != kODDPReadOnly);
       MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTEAS, bEnable);

       MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_LINK_MENU, kODTrue);

       ALinkedList *allSelected = somSelf->GetSelectedObjects (ev);
       SourceOfLink *isLinkSource      = GetLinkSource(ev, allSelected, _fAllLinkSources);
       DestOfLink   *isLinkDestination = GetLinkDestination(ev, allSelected, _fAllLinkDestinations);
       MenuBar->EnableMenuItem(ev, EDIT_LINK_MENU, EDIT_LINKINFO, (isLinkSource || isLinkDestination) );

       return;
    }

    ODMenuBar *MenuBar = somSelf->GetMenuBar (ev);
    ODULong numSelected = somSelf->GetSelectedObjects(ev)->Count(ev);
    ODULong numEmbedded = somSelf->GetEmbeddedObjects(ev)->Count(ev);

    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_SELECTALL,
                                         numEmbedded && (numSelected < numEmbedded));
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_DESELECTALL,
                                         numEmbedded && (numSelected == numEmbedded));
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_OPENSEL, numSelected);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_SELPROPERTIES, numSelected == 1);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_COPY, numSelected);

    MenuBar->EnableMenuItem(ev, IDMS_EDIT, CMD(Move), kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, CMD(MoveFront), kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, CMD(MoveBack), kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, CMD(Resize), kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_DELETE, kODFalse);

    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_CUT, kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_COPYLINKTO, kODFalse);

    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTE, kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTEAS, kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTELINK, kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTELINKFROM, kODFalse);

    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_INSERT, kODFalse);
    MenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_CREATE,      kODFalse);

    //enable our own menu items
    MenuBar->EnableMenuItem(ev, kODOptionsMenuID, CMD(ColorCHANGE), kODFalse);
    MenuBar->EnableMenu(ev, kODEmbedMenuID, kODFalse);
}

// -------------------------------------------------------------------------
// LinkContainer --> Initialize
//
//      Common code needed by the InitPart* methods.
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerInitialize
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODPart          *partWrapper    // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer", "LinkContainerInitialize");

    LinkContainer_parent_BaseContainer_Initialize(somSelf, ev, partWrapper);
    _fPartWrapper = partWrapper;
    _fSession = somSelf->GetStorageUnit(ev)->GetSession(ev);

    _fAllLinkSources = new ALinkedList;
    _fAllLinkDestinations = new ALinkedList;
    _floatingDest = kODNULL;

    _fLastSavedList = kODNULL;

}

//--------------------------------------------------------------------------
// ODPart --> FrameShapeChanged
//
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         LinkContainerFrameShapeChanged
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerFrameShapeChanged");

    // On OS/2 only, we have changed code so that for end-users
    // it looks as if embeds are anchored with top-left corner of parent
    // unlike bottom-left which is actually the origin for OS/2
    // We move embeds up or down when the container is resized
    // so that distance of embeds from top-left of container is same.
    // But when embeds are linked we also need to update linking info
    // when this happens.

#if defined (_PLATFORM_OS2_)
    ALinkedList *embeds = somSelf->GetEmbeddedObjects(ev);
    ContentObject *cObj = (ContentObject*) embeds->First(ev)->Content(ev);
    ODRect oldRect;
    if (cObj)
       oldRect = cObj->_get_boundingRect(ev);
#endif

    LinkContainer_parent_BaseContainer_FrameShapeChanged (somSelf, ev, frame);

#if defined (_PLATFORM_OS2_)
    if (cObj) {
       ODRect newRect = cObj->_get_boundingRect(ev);
       ODPoint offset = {newRect.left - oldRect.left, newRect.top - oldRect.top};

       if (offset.x || offset.y) {

           // Looks like embeds are moved. Updated linking info
           ALink *itr;
           for (itr = _fAllLinkDestinations->First(ev); itr->Content(ev) ; itr = itr->Next(ev)) {
              DestOfLink *dest = (DestOfLink *) itr->Content(ev);
              dest->destinationPoint.x += offset.x;
              dest->destinationPoint.y += offset.y;
           } /* endfor */

       } /* endif */

    } /* endif */
#endif

}


SOM_Scope void  SOMLINK LinkContainersomInit(LinkContainer *somSelf)
{
    /* LinkContainerData *somThis = LinkContainerGetData(somSelf); */
    LinkContainerMethodDebug("LinkContainer","LinkContainersomInit");

    LinkContainer_parent_BaseContainer_somInit(somSelf);
}

SOM_Scope void  SOMLINK LinkContainersomUninit(LinkContainer *somSelf)
{
    /* LinkContainerData *somThis = LinkContainerGetData(somSelf); */
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainersomUninit");

    ALink *itr;
    Environment *ev = somGetGlobalEnvironment();
    for(itr = _fAllLinkSources->First(ev); itr->Content(ev); itr=itr->Next(ev)) {
       SourceOfLink *source = (SourceOfLink *) itr->Content(ev);
       SOMFree (source->sourceObjects);
       delete source;
    }
    for(itr = _fAllLinkDestinations->First(ev); itr->Content(ev); itr=itr->Next(ev)) {
       DestOfLink *dest = (DestOfLink *) itr->Content(ev);
       SOMFree (dest->destObjects);
       delete dest;
    }

    delete _fAllLinkSources;
    delete _fAllLinkDestinations;

    LinkContainer_parent_BaseContainer_somUninit(somSelf);
}

//--------------------------------------------------------------------------
// LinkContainer --> HandleMenuEvent
//
//      Handle a menubar or pulldown menu selection event.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         LinkContainerHandleMenuEvent
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,         // in
                ODEventData     *event          // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerHandleMenuEvent");


    try {

#if   defined(_PLATFORM_UNIX_)
        ODMenuEventData* menu_event = (ODMenuEventData*) event;
        switch(menu_event->item)
#elif defined(_PLATFORM_WIN32_)
        switch(LOWORD(event->wParam)) // determine which menu pulldown it was
#elif defined(_PLATFORM_OS2_)
        switch(LONGFROMMP(event->mp1))
#endif
        {
            case CMD(LinkInfo):
	      return somSelf->DoLinkInfo(ev, frame);
	      break;

            default:
	      return LinkContainer_parent_BaseContainer_HandleMenuEvent (somSelf, ev, frame, event);
	}
    }

    catch (...) {}
    return kODFalse;
}


//--------------------------------------------------------------------------
// LinkContainer --> DoLinkInfo
//
//      Handle a menubar or pulldown menu selection event.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         LinkContainerDoLinkInfo
                (
                LinkContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    LinkContainerData *somThis = LinkContainerGetData(somSelf);
    LinkContainerMethodDebug("LinkContainer","LinkContainerDoLinkInfo");

    SourceOfLink *source = kODNULL;
    DestOfLink   *dest = kODNULL;
    ODLinkInfoResult result;
    ODUpdateID     id;

    //    PRINT("Entered DoLinkInfo:");
    ALinkedList *allSelected = somSelf->GetSelectedObjects (ev);

    ODFrameFacetIterator* facets = frame->CreateFacetIterator(ev);

    if (source = GetLinkSource(ev, allSelected, _fAllLinkSources)) { 
      //PRINT("Selection is a link Source.\n");
      if (source->linkSource->ShowLinkSourceInfo(ev, facets->First(ev), source->change, kODTrue, &result)) {

	switch (result.action) {
	case kODLinkInfoBreakLink:
	  // need to call somSelf->BreakAllLinks(ev, cObj);, but need to find the right content object to pass.
	  somSelf->BreakAllLinks(ev, source->sourceObjects[0]);
	  break;

	case kODLinkInfoUpdateNow:
	  id =  _fSession->UniqueUpdateID(ev);
	  source->change = id;
	  somSelf->WriteSingleLink (ev, (void*)source, id);
	  break;

	case kODLinkInfoOk:
	  if (result.autoUpdate != source->linkSource->IsAutoUpdate(ev)) {
	    source->linkSource->SetAutoUpdate(ev, result.autoUpdate);
	    if (result.autoUpdate) { 
	      // update now
	      id =  _fSession->UniqueUpdateID(ev);
	      source->change = id;
	      somSelf->WriteSingleLink (ev, (void*)source, id);
	    }
	  }
	  break;

	default:
	  break;
        }

      }
    }

    else if (dest = GetLinkDestination(ev, allSelected, _fAllLinkDestinations)) {
      //PRINT("Selection is a link Destination.\n");
      if (dest->link->ShowLinkDestinationInfo(ev, facets->First(ev),&dest->info, kODTrue, &result)) {

	switch (result.action) {
	case kODLinkInfoFindSource:
	  dest->link->ShowSourceContent(ev);
	  break;
	case kODLinkInfoBreakLink:
	  // need to call somSelf->BreakAllLinks(ev, cObj);, but need to find the right content object to pass.
	  somSelf->BreakAllLinks(ev, dest->destObjects[0]);
	  break;
	case kODLinkInfoUpdateNow:
            somSelf->LinkUpdated(ev, dest->link, dest->link->GetUpdateID(ev));
	    break;
	case kODLinkInfoOk:
	    if (result.autoUpdate != dest->info.autoUpdate) {
	      dest->info.autoUpdate = result.autoUpdate;
	      if (result.autoUpdate)
		dest->link->RegisterDependent(ev, _fPartWrapper, dest->info.change);
	      else
		dest->link->UnregisterDependent(ev, _fPartWrapper);
	    }
	default:
	  break;
	}
      }
    }
    else
      PRINT("Selection is neither link Source nor link Destination!.\n");
    return kODTrue;
}


/*****************************************************************************
 M_LinkContainer clsGetODPartHandlerName( M_T3GamePart *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope ISOString  SOMLINK M_LinkContainerclsGetODPartHandlerName
                 (M_LinkContainer *somSelf,  Environment *ev)
{
    /* M_LinkContainerData *somThis = M_LinkContainerGetData(somSelf); */
    M_LinkContainerMethodDebug("M_LinkContainer","M_LinkContainerclsGetODPartHandlerName");

    string handlerName = (string)SOMMalloc(strlen(kPartHandlerName)+1);
    strcpy(handlerName,kPartHandlerName);


    return (ISOString) handlerName;
}

/*****************************************************************************
 M_LinkContainer --> clsGetODPartHandlerDisplayName( M_T3GamePart *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope string  SOMLINK M_LinkContainerclsGetODPartHandlerDisplayName(M_LinkContainer *somSelf,
                                                                         Environment *ev)
{
    /* M_LinkContainerData *somThis = M_LinkContainerGetData(somSelf); */
    M_LinkContainerMethodDebug("M_LinkContainer","M_LinkContainerclsGetODPartHandlerDisplayName");

    string handlerName = (string)SOMMalloc(strlen(kPartHandlerDisplayName)+1);
    strcpy(handlerName,kPartHandlerDisplayName);


    return (ISOString) handlerName;
}

/*****************************************************************************
 M_LinkContainer --> clsGetODPartKinds( M_T3GamePart *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope _IDL_SEQUENCE_PartKindInfo  SOMLINK M_LinkContainerclsGetODPartKinds(M_LinkContainer *somSelf,
                                                                                Environment *ev)
{
    /* M_LinkContainerData *somThis = M_LinkContainerGetData(somSelf); */
    M_LinkContainerMethodDebug("M_LinkContainer","M_LinkContainerclsGetODPartKinds");

    _IDL_SEQUENCE_PartKindInfo partKindInfo;

    // Create structure PartKindInfo  and allocate memory for its fields
    PartKindInfo * info       =  (PartKindInfo *)SOMMalloc(sizeof(PartKindInfo));
    info->partKindName        =  (ISOString) SOMMalloc(strlen(kPartKindName) + 1);
    info->partKindDisplayName =  (string)SOMMalloc(strlen(kPartKindDisplayName)+1);
    info->filenameFilters     =  (string)SOMMalloc(strlen("")+1);
    info->filenameTypes       =  (string)SOMMalloc(strlen("")+1);
    info->categories          =  (string)SOMMalloc(strlen(kPartCategory)+1);
    info->categoryDisplayName =  (string)SOMMalloc(strlen(kPartCategory)+1);
    info->objectID            =  (string)SOMMalloc(strlen("")+1);

    // Copy the information into the structure
    strcpy(info->partKindName , kPartKindName);
    strcpy(info->partKindDisplayName, kPartKindDisplayName);
    strcpy(info->filenameFilters, "");
    strcpy(info->filenameTypes, "");
    strcpy(info->categories, kPartCategory);
    strcpy(info->categoryDisplayName, kPartCategory);
    strcpy(info->objectID, "");

    partKindInfo._maximum = 1;
    partKindInfo._length = 1;
    partKindInfo._buffer = info;



    return partKindInfo;
}

/*****************************************************************************
 M_LinkContainer --> clsGetODPartGetOLE2ClassID( M_T3GamePart *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope string  SOMLINK M_LinkContainerclsGetOLE2ClassId(M_LinkContainer *somSelf,
                                                            Environment *ev)
{
    /* M_LinkContainerData *somThis = M_LinkContainerGetData(somSelf); */
    M_LinkContainerMethodDebug("M_LinkContainer","M_LinkContainerclsGetOLE2ClassId");

    char *kID = "{51f39360-faeb-11cf-ad1b-08005ac0ff26}";

    string OLE2ClassID = (string)SOMMalloc(strlen(kID)+1);
    strcpy(OLE2ClassID,kID);

    return OLE2ClassID;
}

/*****************************************************************************
 M_LinkContainer --> clsGetODPartGetWindowsIconFileName ( M_T3GamePart *somSelf,
                                  Environment *ev )
******************************************************************************/

SOM_Scope string  SOMLINK M_LinkContainerclsGetWindowsIconFileName(M_LinkContainer *somSelf,
                                                                    Environment *ev)
{
    /* M_LinkContainerData *somThis = M_LinkContainerGetData(somSelf); */
    M_LinkContainerMethodDebug("M_LinkContainer","M_LinkContainerclsGetWindowsIconFileName");

    string windowsIcon = (string)SOMMalloc(strlen(kWindowsIcon)+1);
    strcpy(windowsIcon,kWindowsIcon);

    return windowsIcon;
}
