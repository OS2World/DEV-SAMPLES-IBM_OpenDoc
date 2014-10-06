/* @(#) 1.57 com/src/samples/basecntr/bcxfer.cpp, odbasepart, od96os2, odos29714c 4/2/97 11:34:01 [4/2/97 17:20:09] */

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

/* -------------------------------------------------------------------------
  BCXFER.CPP
  This file contains routines for data transfer.
  Functions implemented include:
    Write to storage / Read from storage
    Clone
    Drag / Drop
    Copy / Paste
    ContainingPartPropertiesUpdated

  Following methods are implemented:

    A> Methods inherited from ODPart

    InitPart
    InitPartFromStorage
    Externalize
    ExternalizeKinds
    CloneInto

    WritePartInfo
    ReadPartInfo
    ClonePartInfo

    AcquireContainingPartProperties
    ContainingPartPropertiesUpdated

    Drop
    DropCompleted
    FulfillPromise

    B> Methods defined in BaseContainer
    StartDrag
    WriteKindInfo
    WriteContents
    ReadKindInfo
    ReadContents
    WriteSingleFrame
    ReadSingleFrame

*/

#define kBaseContainerOldPartKind "BaseContainerPartKind"
#define kODPropBackgroundColorOld "BaseContainer:Property:BackgroundColor"
static const ODPropertyName kPropBackgroundOld =  "BaseContainer:Value:NTColor";

// -------------------------------------------------------------------------
inline void InitPropVal (Environment *ev, ODStorageUnit *su,
                         ODPropertyName propName, ODValueType valName)
{
    if (ODSUExistsThenFocus (ev, su, propName, valName))
         su->Remove (ev);

    ODSUAddPropValue (ev, su, propName, valName);

}

ODFacet* FirstFacet (Environment *ev, ODFrame *frame)
{

    ODFrameFacetIterator *ffitr  = frame->CreateFacetIterator(ev);
    ODFacet *facet = (ODFacet *)ffitr->First(ev);
    ODDeleteObject(ffitr);
    return facet;

}

// -------------------------------------------------------------------------
// ODPart --> InitPart
//
//      Initializes this part (first time use).
//
//      -> does not call parent method
//      -> required for all parts
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerInitPart
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *storageUnit,   // in
                ODPart          *partWrapper    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerInitPart");



    try {

    BaseContainer_parent_ODPart_InitPart(somSelf,ev,storageUnit,partWrapper);


    _fPartWrapper = partWrapper;
    _fPartSU = storageUnit;
    somSelf->InitPersistentObject(ev, storageUnit);
    somSelf->Initialize(ev, partWrapper);

    } // end of try block
    catch(ODException _exception) {
        ODSetSOMException(ev, kODErrCannotInitializePart);

    } // end of catch block



}



// -------------------------------------------------------------------------
// ODPart --> InitPartFromStorage
//
//      Initializes this part from storage.
//
//      -> does not call parent method
//      -> required for all parts
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerInitPartFromStorage
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *storageUnit,   // in
                ODPart          *partWrapper    // in
                )

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerInitPartFromStorage");



    try {

    BaseContainer_parent_ODPart_InitPartFromStorage(somSelf,ev,storageUnit,partWrapper);

    // Initialize
    ODDraft *fromDraft = storageUnit->GetDraft (ev);
    _fPartWrapper = partWrapper;
    _fPartSU = storageUnit;
    somSelf->InitPersistentObjectFromStorage(ev, storageUnit);
    somSelf->Initialize(ev, partWrapper);
    _fNeedToInternalize = kODTrue;

   // Read in display frames and BGColor
   // This is done only when part comes up. So this cannot be put
   // in a generic *READ* routine

   // Read background color

    _fBackgroundColor = 0;
    if(ODSUExistsThenFocus(ev, storageUnit, kODPropBackgroundColor, kPropBackground)) {
       _fBackgroundColor = ODGetULongProp(ev, storageUnit, kODPropBackgroundColor, kPropBackground);
    } else if(ODSUExistsThenFocus(ev, storageUnit, kODPropBackgroundColorOld, kPropBackgroundOld)) {
       _fBackgroundColor = ODGetULongProp(ev, storageUnit, kODPropBackgroundColorOld, kPropBackgroundOld);
    }
#ifdef _PLATFORM_UNIX_
    int status;
    XColor color;
    color.flags = DoRed | DoGreen | DoBlue;

    ODULong col = (ODULong)_fBackgroundColor;

    color.red = ((col & 0xFF0000) >> 8) | ((col & 0xFF0000) >> 16);
    color.green =  (col & 0x00FF00) | ((col & 0x00FF00) >> 8);
    color.blue = (col & 0x0000FF) | ((col & 0x0000FF) << 8);

    status = XAllocColor(_fDisplay,
      XDefaultColormapOfScreen( _fSession->GetWindowState(ev)->GetScreen(ev)),
      &color);

    if (status == 0)   // XAllocColor failed
        _fBackgroundColor = WhitePixel(_fDisplay, DefaultScreen(_fDisplay));
    else
        _fBackgroundColor = color.pixel;

#elif defined(_PLATFORM_WIN32_)
    if(storageUnit->Exists(ev, kODPropBackgroundColor, kPropBackground, 0)) {
       ExchangeRedAndBlue(_fBackgroundColor);
    } 
#endif // _PLATFORM_WIN32_

    // Read in display frames

    if (ODSUExistsThenFocus (ev, storageUnit, kODPropDisplayFrames, kODWeakStorageUnitRef))
    {

         ODStorageUnitRef aSURef;
         ODULong offset, offsetLimit;

         offsetLimit = storageUnit->GetSize(ev);

         for (offset = 0; offset < offsetLimit; offset += sizeof(ODStorageUnitRef))
         {
              storageUnit->SetOffset(ev, offset);
              ODID id = ODGetWeakSURefProp (ev, storageUnit, kODNULL, kODNULL);

              if (id != kODNULLID) {
                   ODFrame* frame =  fromDraft->AcquireFrame(ev, id);
                   if (!_fDisplayFrames->Contains(ev, frame))
                        _fDisplayFrames->AddLast (ev, frame);
                   else
                        PRINT("Display frame add: ***** WRONG ******* \n");
                   frame->SetDroppable(ev, kODTrue);
              }
         }

    }

    // clean up
    ODSURemoveProperty(ev, storageUnit, kODPropContentFrame);
    ODSURemoveProperty(ev, storageUnit, kODPropSuggestedFrameShape);
    ODSURemoveProperty(ev, storageUnit, kBCSuggestedTransform);
    ODSURemoveProperty(ev, storageUnit, kODPropMouseDownOffset);


    } // end of try block
    catch(ODException _exception) {
        ODSetSOMException(ev, kODErrCannotInitializePart);
    } // end of catch block

}



// -------------------------------------------------------------------------
// ODPersistentObject --> Externalize
//
//      Write this part's content, and state to storage.
//
//      Called by your part editor when part data must be stored.
//
//      -> if overridden then must call parent's Externalize method first!
//      -> write out part's persistent properties/values to storage
//         as defined in the InitPart method of this part.
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerExternalize
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerExternalize");

    try {

    BaseContainer_parent_ODPart_Externalize(somSelf,ev);

    somSelf->WriteKindInfo (ev, somSelf->GetStorageUnit (ev));
    BCCloneInfo cloneInfo;
    memset (&cloneInfo, 0, sizeof (BCCloneInfo));
    somSelf->WriteContents (ev, somSelf->GetStorageUnit (ev), &cloneInfo, EXTERNALIZE);

    } // end of try block
    catch (...) {}

}



// -------------------------------------------------------------------------
// BaseContainer --> ExternalizeKinds
//
//      Writes part's PartKind info list to storage.
//
//      Called by OpenDoc (but I don't know why or when???)
//
//      -> do not call your parent method
//      -> BaseContainer has no PartKind info to write to storage
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerExternalizeKinds
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODTypeList      *kindset        // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerExternalizeKinds");

}


// -------------------------------------------------------------------------
// ODPersistentObject --> CloneInto
//
//      Copy an object data into a storage unit.
//
//      Called by OpenDoc when your part is copied to the ClipBoard, the
//      Drag-Drop object, or link-source object.
//
//      -> if overridden then must call the parent's CloneInto method first!
//      -> used to support internal data interchange
//      -> the parent method clones kODPropCreateDate,
//                                  kODPropModDate,
//                                  kODPropModUser properties for you
//      -> you need to clone any additional properties
//      -> and write your part's data to the StorageUnit
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCloneInto
                (
                BaseContainer   *somSelf,           // in
                Environment     *ev,                // in
                ODDraftKey       key,               // in
                ODStorageUnit   *destinationSU,     // in
                ODFrame         *initiatingFrame    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCloneInto");

    try {

    BaseContainer_parent_ODPart_CloneInto(somSelf,ev,key, destinationSU, initiatingFrame);

    BCCloneInfo cloneInfo;
    memset (&cloneInfo, 0, sizeof (BCCloneInfo));

    somSelf->WriteKindInfo (ev, destinationSU);

    cloneInfo.key = key;

    somSelf->WriteContents ( ev, destinationSU, &cloneInfo, CLONE_ALL);

    } // end of try block
    catch (...) {}
}



// -------------------------------------------------------------------------
// ODPart --> ReadPartInfo
//
//      Should read the part info data for a display frame of this part
//      from the specified storage unit.
//
//      -> does not call parent method
//      -> required for all parts
// -------------------------------------------------------------------------

SOM_Scope       ODInfoType
SOMLINK         BaseContainerReadPartInfo
                (
                BaseContainer       *somSelf,       // in
                Environment         *ev,            // in
                ODFrame             *frame,         // in
                ODStorageUnitView   *storUnitView   // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerReadPartInfo");

    return kODNULL;
}



// -------------------------------------------------------------------------
// ODPart --> WritePartInfo
//
//      Should write the part info data for a display frame of this part
//      from the specified storage unit.
//
//      -> does not call parent method
//      -> required for all parts
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerWritePartInfo
                (
                BaseContainer       *somSelf,       // in
                Environment         *ev,            // in
                ODInfoType           partInfo,      // in
                ODStorageUnitView   *storUnitView   // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerWritePartInfo");


}



// -------------------------------------------------------------------------
// ODPart --> ClonePartInfo
//
//      Should clone the part info data for a display frame of this part
//      into the specified storage unit.
//
//      -> does not call parent method
//      -> required for all parts
// -------------------------------------------------------------------------
SOM_Scope void	SOMLINK BaseContainerClonePartInfo(BaseContainer *somSelf,
         Environment *ev,
         ODDraftKey key,
         ODInfoType partInfo,
         ODStorageUnitView* storageUnitView,
         ODFrame* scope)

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerClonePartInfo");

}



//--------------------------------------------------------------------------
// ODPart --> AcquireContainingPartProperties
//
//      Should write into a storage unit the container properties
//      this part associates with the specified embedded frame and
//      then return the storage unit.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODStorageUnit*
SOMLINK         BaseContainerAcquireContainingPartProperties
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerGetContainingPartProperties");


    return kODNULL;
}



//--------------------------------------------------------------------------
// ODPart --> ContainingPartPropertiesUpdated
//
//      Should notify this part that its containing part's container
//      properties have changed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerContainingPartPropertiesUpdated
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,         // in
                ODStorageUnit   *propertyUnit   // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerContainingPartPropertiesChanged");


}


//--------------------------------------------------------------------------
// ODPart --> Drop
//
//      Should move or copy the dragged data into this part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODDropResult
SOMLINK         BaseContainerDrop
                (
                BaseContainer       *somSelf,   // in
                Environment         *ev,        // in
                ODDragItemIterator  *dropInfo,  // in
                ODFacet             *facet,     // in
                ODPoint             *where      // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDrop");

    ODDropResult        dropResult = kODDropFail;
    ODCloneKind         cloneKind;
    ODULong             attributes;
    ODBoolean           isMovePart;
    ODFrame*            myFrame = facet->GetFrame(ev);

    if (_fDraftReadOnly) {
       WARNMSG(WARN_INDEX(-1), "Document is read only. Drop is not accepted.");
       return dropResult;
    }
    somSelf->InvertDragHilite( ev, facet );

  try {

    // Get proper attributes


    attributes = _fSession->GetDragAndDrop(ev)->GetDragAttributes(ev);
    isMovePart = ((attributes & kODDropIsInSourceFrame) &&
                  (attributes & kODDropIsMove)) ? kODTrue : kODFalse;

    if (attributes & kODDropIsCopy)  {
        dropResult = kODDropCopy;
        cloneKind = kODCloneDropCopy;
    }
    else {
        dropResult = kODDropMove;
        cloneKind = kODCloneDropMove;
    }

    // where is in frame coordinates, change to content coordinates
    TempODTransform intXform = myFrame->AcquireInternalTransform (ev, kODNULL);
    intXform->InvertPoint (ev, where);

    // Move selection ..

    if (isMovePart) {

       ODPoint delta;
       ALink *itr;
       delta.x = where->x - _fMouseStart->x;
       delta.y = where->y - _fMouseStart->y;

       somSelf->CompleteMoveOperation (ev, myFrame, &delta);

    } // if move part

    else {

       // It is a drop from another part

       ODStorageUnit *dropSU;
       ODPoint refPoint;

       for (dropSU = dropInfo->First(ev); dropSU; dropSU = dropInfo->Next(ev)) {

#if defined(_PLATFORM_OS2_)

          // some OS/2 specific stuff for drag-drop from WPShell
          if ( !dropSU->Exists(ev, kODPropContents, (ODValueType)kODDragitem, 0))
          {
             // nothing to process... (bug)
             continue;
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
             continue;
          }
#endif

          if (ODGetPointProp (ev, dropSU, kODPropMouseDownOffset, kODPoint, &refPoint) == kODNULL)
             refPoint.x = refPoint.y = 0;
          refPoint.x = where->x - refPoint.x;
          refPoint.y = where->y - refPoint.y;

          if ((dropSU->Exists(ev, kODPropContentFrame, kODWeakStorageUnitRef, 0))
              || (somSelf->ReadKindInfo(ev, dropSU) == kODFalse)
              || (attributes & kODDropIsPasteAs))
          {
             ODFrame *embeddedFrame = somSelf->ReadSingleFrame (ev, facet,
                                         dropSU, cloneKind, &refPoint);
             if (embeddedFrame)
             {
                ContentFrame *newObject = new ContentFrame();
                newObject->_set_myFrame (ev, embeddedFrame);
                _fEmbeddedObjects->AddLast (ev, (ODPtr)newObject);
             }
          }
          else {

             BCCloneInfo cloneInfo;
             memset (&cloneInfo, 0, sizeof(BCCloneInfo));

             ODDraft *toDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
             ODDraft *fromDraft = dropSU->GetDraft(ev);
             ODDraftKey key = 0;
             key = fromDraft->BeginClone (ev, toDraft, kODNULL, cloneKind);
             cloneInfo.key = key;
             cloneInfo.refPoint = &refPoint;
             cloneInfo.myFrame = facet->GetFrame (ev);

             somSelf->ReadContents(ev, dropSU, &cloneInfo, CLONE_ALL);

             fromDraft->EndClone (ev, key);

          }
       } // end for

    } // if not move part

    somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);
    somSelf->ChangeNotification (ev, BCC_DROP, myFrame, kODNULL, kODTrue, kODNULL);

  } // end of try block
  catch (...) {}

  return dropResult;
}



//--------------------------------------------------------------------------
// ODPart --> DropCompleted
//
//      Should notify this part of a drag operation, resulting from an
//      asynchronous drag initiated from this part, is complete.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDropCompleted
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODPart          *destPart,      // in
                ODDropResult     dropResult     // in
                )

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDropCompleted");

    ALink   *itr;


        // We have returned from drag/drop, clean up the stuff
        // If drop operation was not a move OR if it was a move within myself or
        // if the draft is readonly then I am going to still HAVE this selection
        // In that case, set the Dragging and InLimbo flags
        if ((destPart == _fPartWrapper) || (dropResult != kODDropMove) || _fDraftReadOnly)
        {
           for (itr=_fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
           {
              ContentFrame *embedObj = (ContentFrame *)itr->Content(ev);
              if (embedObj->_get_objType(ev) == COBJ_FRAMECLASS)
              {
                  embedObj->_get_myFrame(ev)->SetDragging(ev, kODFalse);
                  embedObj->_get_myFrame(ev)->SetInLimbo (ev, kODFalse);
              }
           }
        }

        if ((destPart != _fPartWrapper) && (dropResult == kODDropMove)) {
           if (!_fDraftReadOnly)
               somSelf->DeleteSelection (ev, OBJECT_DRAGGED);
           else
              WARNMSG (WARN_INDEX(-1), "Cannot delete selection. Document is read-only.");
        }

        if (destPart)
           ODSafeReleaseObject (destPart);
}


//--------------------------------------------------------------------------
// ODPart --> FulfillPromise
//
//      Should fulfill a promise by providing the content data the
//      promise represents.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerFulfillPromise
                (
                BaseContainer      *somSelf,        // in
                Environment        *ev,             // in
                ODStorageUnitView  *promiseSUView   // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerFulfillPromise");


}


//--------------------------------------------------------------------------
// BaseContainer --> StartDrag
//
//      Should prepare the data for the drag operation
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerStartDrag
                (
                BaseContainer   *somSelf,        // in
                Environment     *ev,             // in
                ODEventData     *event,          // in
                ODFrame         *embeddedFrame,  // in
                ODFacet         *facet,          // in
                ODEventInfo     *eventInfo,
                ODCloneKind     cloneKind
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerStartDrag");

    ODDragAndDrop*      dragAndDrop = kODNULL;
    ODDropResult        dropResult = kODNULL;
    ODPoint cursorLocation;               // where was the mouse click


        cursorLocation = eventInfo->where;

    ODStorageUnit *toSU = kODNULL;
    ODPart*        destPart = kODNULL;
    ALink   *itr;

    try {

        // Get the DragAndDrop object's ContentStorageUnit

        dragAndDrop =
                somSelf->GetStorageUnit(ev)->GetSession(ev)->GetDragAndDrop(ev);
        dragAndDrop->Clear(ev);
        toSU = dragAndDrop->GetContentStorageUnit(ev);

        // Clone the data .. same as Copy

        ODULong num = _fSelectedObjects->Count(ev);
        if (!num)
           return;

        ContentFrame *cobj = (ContentFrame *) _fSelectedObjects->First(ev)->Content(ev);

        if ((num == 1) && (cobj->_get_objType(ev) == COBJ_FRAMECLASS)) {

            // special case: copy single embedded frame to DAD
            ODFrame *eFrame = cobj->_get_myFrame(ev);
            somSelf->WriteSingleFrame (ev, eFrame, toSU, cloneKind);

        }
        else {

           somSelf->WriteKindInfo (ev, toSU);
           BCCloneInfo cloneInfo;
           memset (&cloneInfo, 0, sizeof(BCCloneInfo));

           ODDraft *fromDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
           ODDraft *toDraft = toSU->GetDraft(ev);
           ODDraftKey key = 0;
           key = fromDraft->BeginClone (ev, toDraft, kODNULL, cloneKind);
           cloneInfo.key = key;

           somSelf->WriteContents (ev, toSU, &cloneInfo, CLONE_SELECTED);

           fromDraft->EndClone (ev, key);
        }

        // Now do the UI stuff needed for drag/drop
        // iterate through the selected embedded frames and compute region

        ODRect  embedBBox;
        Rect winRect;
        TempODShape tempShape = _fSelectShape->Copy(ev);
        TempODTransform xform = facet->AcquireWindowContentTransform(ev, kODNULL);
        tempShape->Transform(ev, xform); // now in window co-ord system
        tempShape->GetBoundingBox (ev, &embedBBox);

// ---------------------- the following code sets up an outline ---------------
// ----------------------   region that shows at drag time --------------------

ODType imageType;

#if defined(_PLATFORM_WIN32_)

        ODRgnHandle    dragRegion = kODNULL;
        SetRect(&winRect, FixedToInt(embedBBox.left),
                          FixedToInt(embedBBox.top),
                          FixedToInt(embedBBox.right),
                          FixedToInt(embedBBox.bottom));
        dragRegion = CreateRectRgn(winRect.left,
                                   winRect.top,
                                   winRect.right,
                                   winRect.bottom);

        imageType = kODWindowsRegionHandle;
#elif defined(_PLATFORM_UNIX_)
        XRectangle rgnBox;
        ODRgnHandle dragRegion = XCreateRegion();

        ODAIXWindowCanvas *aixwincanvas = (ODAIXWindowCanvas *)
                      (facet->GetCanvas(ev)->GetPlatformCanvas(ev, kODAIX));
        Window window = aixwincanvas->GetWindow(ev);
        GC gc = aixwincanvas->GetGC(ev);

        dragRegion = tempShape->GetRegion(ev);

        XSetRegion(_fDisplay, gc, dragRegion);

        XClipBox(dragRegion, &rgnBox);
        XDrawRectangle(_fDisplay, window, gc, rgnBox.x, rgnBox.y, rgnBox.width, rgnBox.height);

        imageType = kODAIXRegion;
#elif defined(_PLATFORM_OS2_)

        DRAGIMAGE dragRegion;         /* DRAGIMAGE structure     */

        // initialize
        POINTL pts[7];
        POINTL ptrOffset;
        pts[ 0].x = 0;   pts[0].y = 0;

        // save region (gotten by BoundingBox routine) in integer format
        winRect.xLeft = FixedToInt(embedBBox.left);
        winRect.yTop =  FixedToInt(embedBBox.top);
        winRect.xRight = FixedToInt(embedBBox.right);
        winRect.yBottom =  FixedToInt(embedBBox.bottom);

        // offset the amount of the cursor (Don't use the cursorLocation
        // variable set above because it is not an int)
        winRect.xLeft -= SHORT1FROMMP(event->mp1);
        winRect.xRight -= SHORT1FROMMP(event->mp1);
        winRect.yTop -= SHORT2FROMMP(event->mp1);
        winRect.yBottom -= SHORT2FROMMP(event->mp1);

        // specify region
        pts[ 0].x = 0;               pts[ 0].y = 0;
        pts[ 1].x = winRect.xLeft ;  pts[ 1].y = winRect.yBottom;
        pts[ 2].x = winRect.xLeft ;  pts[ 2].y = winRect.yTop;
        pts[ 3].x = winRect.xRight;  pts[ 3].y = winRect.yTop;
        pts[ 4].x = winRect.xRight;  pts[ 4].y = winRect.yBottom;
        pts[ 5].x = winRect.xLeft ;  pts[ 5].y = winRect.yBottom;
        pts[ 6].x = 0;               pts[ 6].y = 0;
        // PUT 0,0 at last location or you will get an extra line.

        // Fill in the DRAGIMAGE structure.
        dragRegion.cb = sizeof(DRAGIMAGE);
        dragRegion.cxOffset = 0;
        dragRegion.cyOffset = 0;
        dragRegion.cptl     = 7;
        dragRegion.hImage = (ULONG)(PPOINTL)pts;
        dragRegion.fl = DRG_POLYGON;
        // ... below it gets set into the ODByteArray dragImgBA

        imageType = kODOS2DragImage;
#endif
// ----------------------   end of region set up --------------------

        for (itr=_fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
        {
           ContentFrame *embedObj = (ContentFrame *)itr->Content(ev);
           if (embedObj->_get_objType(ev) == COBJ_FRAMECLASS)
           {
               embedObj->_get_myFrame(ev)->SetDragging(ev, kODTrue);
               embedObj->_get_myFrame(ev)->SetInLimbo(ev, kODTrue);
           }
        }

        xform->InvertPoint (ev, &cursorLocation); // now in my frame coord
        *_fMouseStart = cursorLocation;

        _fSelectShape->GetBoundingBox (ev, &embedBBox); // frame coord
        cursorLocation.x -= embedBBox.left;
        cursorLocation.y -= embedBBox.top;
        ODSetPointProp (ev, toSU, kODPropMouseDownOffset, kODPoint, &cursorLocation);

        ODByteArray dragImgBA = CreateByteArrayStruct(&dragRegion, sizeof(dragRegion));
        ODByteArray eventBA = CreateByteArrayStruct(&event, sizeof(ODEventData*));

        // Now that all setup is done, start dragging the frames
#if (defined(_PLATFORM_WIN32_) || defined(_PLATFORM_OS2_))
        dropResult = dragAndDrop->StartDrag(ev,
                                            facet->GetFrame(ev),
                                            imageType, &dragImgBA,
                                            &destPart, &eventBA);
#else
        dropResult = dragAndDrop->StartDrag(ev,
                                            facet->GetFrame(ev),
                                            imageType, &dragImgBA,
                                            &destPart, (ODByteArray*)event);
#endif

        DisposeByteArrayStruct(dragImgBA);
        DisposeByteArrayStruct(eventBA);

#if (defined(_PLATFORM_WIN32_) || defined(_PLATFORM_OS2_))
        somSelf->DropCompleted(ev, destPart, dropResult);
#endif


    } // end of try block
    catch(ODException _exception) {
        PRINT("Exception in Start Drag **----\n");
    } // end of catch block

}



// -------------------------------------------------------------------------
// BaseContainer --> WriteKindInfo
//
//      Writes Base Container kind into the storage unit.
//
//      -> private method of BaseContainer
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerWriteKindInfo
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *toSU           // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerWriteKindInfo");

    try {

         InitPropVal (ev, toSU, kODPropContents, kBaseContainerPartKind);

    } // end of try block
    catch (...) {}

}


// -------------------------------------------------------------------------
// BaseContainer --> WriteContents
//
//      Writes part's content to storage.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         BaseContainerWriteContents
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *toSU,          // in
                BCCloneInfo     *cloneInfo,
                ODULong         writeKind
                )

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerWriteContents");

    try {

    // Focus on the contents property
    if(!ODSUExistsThenFocus(ev, toSU, kODPropContents, kBaseContainerPartKind)) {
       InitPropVal (ev, toSU, kODPropContents, kBaseContainerPartKind);
    }

    // Store the _lastFrameRect. This is the bounding rectangle of our frame,
    // the last time we were displayed as a frame view.
    ODSetRectProp(ev, toSU, kODNULL, kODNULL, &_lastFrameRect);

    // Store the content extent
    ODPoint extent(0,0);
    ODFrame *dispFrame = (ODFrame *)(_fDisplayFrames->First(ev)->Content(ev));
    if(dispFrame) {
       dispFrame->GetContentExtent(ev, &extent);
    }
    ODSetPointProp(ev, toSU, kODNULL, kODNULL, &extent);

    // Write out the background color
#ifdef _PLATFORM_UNIX_
    // For Unix we need to store RGB values separately
    XColor color;
    color.pixel = _fBackgroundColor;
    XQueryColor(_fDisplay,
      XDefaultColormapOfScreen( _fSession->GetWindowState(ev)->GetScreen(ev)),
      &color);
    ODULong col = ((color.red & 0xFF00) << 8) |
                  (color.green & 0xFF00) | ((color.blue & 0xFF00) >> 8);
    ODSetULongProp (ev, toSU, kODPropBackgroundColor, kPropBackground, col);

#elif defined(_PLATFORM_WIN32_)
    // On Windows, the color is defined as 0x00BBGGRR. We will store it as
    // 0x00RRGGBB so that it is in the same format in all platforms.
    COLORREF color = _fBackgroundColor;
    ExchangeRedAndBlue(color);

    ODSetULongProp (ev, toSU, kODPropBackgroundColor, kPropBackground, color);
#else
    ODSetULongProp (ev, toSU, kODPropBackgroundColor, kPropBackground, _fBackgroundColor);
#endif

    // Write part icon
    somSelf->WriteIconToSU (ev, toSU);

    // Write out display frames
    // We always store a weak reference to our display frames

    ALink* itr                   = kODNULL;
    ODFrame *displayFrame        = kODNULL;
    ODStorageUnitRef aSURef;
    ODULong offset = 0;
    ODDraft *fromDraft = somSelf->GetStorageUnit (ev) -> GetDraft (ev);

    InitPropVal (ev, toSU, kODPropDisplayFrames, kODWeakStorageUnitRef);

    for (itr = _fDisplayFrames->First(ev); itr->Content(ev); itr=itr->Next(ev))
    {
         displayFrame = (ODFrame*) itr->Content(ev);
         ODID frameID = displayFrame->GetStorageUnit (ev) ->GetID (ev);

         if (writeKind == EXTERNALIZE)
              displayFrame->Externalize(ev);
         else
              frameID = fromDraft->WeakClone(ev, cloneInfo->key, frameID, 0, 0);

         ODSetWeakSURefProp (ev, toSU, kODNULL, kODNULL, frameID);
    }

    // Write out embedded frames
    // Store strong reference to embedded frames.

    ContentObject *embeddedObject        = kODNULL;
    ALinkedList *frameList         = (writeKind == CLONE_SELECTED) ?
                                  _fSelectedObjects : _fEmbeddedObjects;

    ODPoint * tmpPt = new ODPoint;
    cloneInfo->refPoint = tmpPt;

    // Compute the embedOrigin value if CLONE_SELECTED

    if (writeKind == CLONE_SELECTED) {
         if (_fSelectShape) {
              ODRect sRect;
              _fSelectShape->GetBoundingBox (ev, &sRect);
              InflateRect (&sRect, -1 * kODBorderWidth, -1 * kODBorderWidth);
              cloneInfo->refPoint->x = sRect.left;
              cloneInfo->refPoint->y = sRect.top;

              // write out a preferred shape so that destination can use it
              toSU->AddProperty (ev, kODPropSuggestedFrameShape);
              ODFrame *aFrame = (ODFrame *)_fDisplayFrames->First(ev)->Content(ev);
              TempODShape tempShape = aFrame->CreateShape(ev);

              sRect.right -= sRect.left;
              sRect.left = 0;
#if (defined (_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_))
              sRect.bottom -= sRect.top;
              sRect.top = 0;
#elif defined (_PLATFORM_OS2_)
              sRect.top -= sRect.bottom;
              sRect.bottom = 0;
#endif
              tempShape->SetRectangle (ev, &sRect);
              tempShape->WriteShape(ev, toSU);
         }
    }
    else {
       cloneInfo->refPoint->x = cloneInfo->refPoint->y = 0;
    }

    // Write the frame list header into the kODFrameList value of our contents
    // property. The body of the frame list will be generated as the frames
    // write their own contents. If there are no embedded frames, nothing will
    // be written out.
    somSelf->WriteFrameListHeader(ev, toSU, cloneInfo, writeKind, frameList);

    InitPropVal (ev, toSU, kODPropEmbeddedFrames, kODStrongStorageUnitRef);

    ODULong num = frameList->Count(ev);
    ODSetULongProp (ev, toSU, kODNULL, kODNULL, num);

    for (itr = frameList->First(ev); itr->Content(ev); itr=itr->Next(ev))
    {
         embeddedObject = (ContentObject *) itr->Content(ev);

         // Store the object type which will be used in ReadContents to
         // determine which object to instantiate.
         ODULong objType = embeddedObject->_get_objType(ev);
         ODSetULongProp (ev, toSU, kODNULL, kODNULL, objType);

         embeddedObject->WriteContents (ev, toSU, writeKind, cloneInfo);
    }

    // Release any memory allocated for the frameListInfo
    if(cloneInfo->frameListInfo) somSelf->ReleaseFrameListInfo(ev, cloneInfo);

    } // end of try block
    catch (...) {}


}


// -------------------------------------------------------------------------
// BaseContainer --> ReadKindInfo
//
//      Reads Base Container kind from the storage unit.
//
//      -> private method of BaseContainer
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerReadKindInfo
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *fromSU           // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerReadKindInfo");

    ODBoolean bExists = kODFalse;

    try {

    bExists = fromSU->Exists (ev, kODPropContents, kBaseContainerPartKind, 0);
    if(!bExists) {
       bExists = fromSU->Exists (ev, kODPropContents, kBaseContainerOldPartKind, 0);
    }

    } // end of try block
    catch (...) {}

    return bExists;
}


// -------------------------------------------------------------------------
// BaseContainer --> ReadContents
//
//      Read part's content from storage.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         BaseContainerReadContents
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *fromSU,          // in
                BCCloneInfo     *cloneInfo,
                ODULong         readKind
                )

{
   BaseContainerData *somThis = BaseContainerGetData(somSelf);
   BaseContainerMethodDebug("BaseContainer", "BaseContainerReadContents");

   ODBoolean foundEmbeddedFrames = kODFalse;

   try {

    // Focus on our contents property
    if(ODSUExistsThenFocus(ev, fromSU, kODPropContents, kBaseContainerPartKind)) {

       // Read the _lastFrameRect. This is the bounding rectangle of our frame,
       // the last time we were displayed as a frame view.
       ODGetRectProp(ev, fromSU, kODNULL, kODNULL, &_lastFrameRect);

       // Read the content extent
       ODPoint extent;
       if(ODGetPointProp(ev, fromSU, kODNULL, kODNULL, &extent)) {
          ODFrame *dispFrame = cloneInfo->myFrame;
          if(dispFrame) {
             dispFrame->ChangeContentExtent(ev, &extent);
          }
       }
    } else {
       ODFrame *dispFrame = cloneInfo->myFrame;
       if(dispFrame){

          // Update the content extent 
          somSelf->UpdateContentExtent(ev, dispFrame);

          // Store the frame's bounding box for viewtype support
          TempODShape currShape = dispFrame->AcquireFrameShape(ev, kODNULL);
          currShape->GetBoundingBox(ev, &_lastFrameRect);
       }
    }

    ODDraft *fromDraft = fromSU->GetDraft (ev);
    ODDraft *toDraft = somSelf->GetStorageUnit (ev) ->GetDraft (ev);

    // Read Embedded frames
    if ( ODSUExistsThenFocus (ev, fromSU, kODPropEmbeddedFrames, kODStrongStorageUnitRef))
        foundEmbeddedFrames = kODTrue;
    else if ( ODSUExistsThenFocus (ev, fromSU, kODPropEmbeddedFramesOld, kODStrongStorageUnitRef))
        foundEmbeddedFrames = kODTrue;

    if (foundEmbeddedFrames == kODTrue)
    {
         ODULong num = 0;
         num = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);

         int i = 0;
         for (i = 0; i < num; i++) {

             ODULong objType = 0;
             objType = ODGetULongProp (ev, fromSU, kODNULL, kODNULL);
             ContentObject *contObj = 0;
             somSelf->GetContentObjectFromObjType(ev, objType, &contObj);
             if (contObj) {
                 contObj->ReadContents(ev, fromSU, readKind, cloneInfo);
                 contObj->_set_linkStatus (ev, kODNotInLink);
                 _fEmbeddedObjects->AddLast(ev, contObj);

                 if (contObj->_get_objType(ev) ==  COBJ_FRAMECLASS)
                 {
                    ODFrame *embedFrame = ((ContentFrame *)contObj)->_get_myFrame(ev);
                    embedFrame->SetDragging(ev, kODFalse);
                    embedFrame->SetInLimbo (ev, kODFalse);
                 }
             }
         }

    } else if( ODSUExistsThenFocus(ev, fromSU, kODPropContents, kODFrameList) ) {


       // Read the frameList header and setup information in frameListInfo
       FrameListHeader header;
       memset(&header, 0, sizeof(header));
       somSelf->ReadFrameListHeader(ev, fromSU, cloneInfo, readKind, &header);

       // Read all frames
       int i;
       for(i = 0; i < header.numFrames; i++) {

          ContentFrame *contentFrame = new ContentFrame();
          contentFrame->ReadContents(ev, fromSU, readKind, cloneInfo);

          ODFrame *frame = contentFrame->_get_myFrame(ev);

          // Complete initialization of the content frame object.
          contentFrame->_set_linkStatus(ev, kODNotInLink);
          frame->SetDragging(ev, kODFalse);
          frame->SetInLimbo (ev, kODFalse);

          // Add frame to list of embedded objects
          _fEmbeddedObjects->AddLast(ev, contentFrame);

       }

       // Deallocate memory for frameListInfo
       somSelf->ReleaseFrameListInfo(ev, cloneInfo);

    }

   } // end of try block
   catch (...) {}

}


// -------------------------------------------------------------------------
// BaseContainer --> WriteSingleFrame
//
//      Write a single embedded frame to destination unit.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         BaseContainerWriteSingleFrame
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *embeddedFrame, // in
                ODStorageUnit   *toSU,          // in
                ODCloneKind     cloneKind
                )

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerWriteSingleFrame");

    ODDraftKey key = 0;
    ODDraft* fromDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);

    try {

         ODDraft* toDraft = toSU->GetDraft(ev);
         ODDraftKey key = 0;
         ODID toRootID = 0;
         ODID toFrameID = 0;

         key = fromDraft->BeginClone(ev, toDraft, kODNULL, cloneKind);

         // Clone the embedded part to the root storage unit
         TempODPart tempPart = embeddedFrame->AcquirePart(ev);
         toRootID = fromDraft->Clone(ev, key, tempPart->GetID(ev), toSU->GetID(ev),
                                     embeddedFrame->GetID(ev));
         // Clone the embedded frame to any storage unit;
         // must be done after cloning the part because
         // the embedded frame strongly references the part.
         toFrameID = fromDraft->Clone(ev, key, embeddedFrame->GetID(ev), 0,
                                      embeddedFrame->GetID(ev));

         if (toFrameID) {

            ODSetWeakSURefProp (ev, toSU, kODPropContentFrame, kODWeakStorageUnitRef, toFrameID);

            toSU->AddProperty (ev, kODPropSuggestedFrameShape);
            TempODShape tempShape = embeddedFrame->AcquireFrameShape(ev, kODNULL);
            tempShape->WriteShape(ev, toSU);

            ODFacet *embeddedFacet = FirstFacet (ev, embeddedFrame);
            if (embeddedFacet)
            {
               TempODTransform embedXform = embeddedFacet->AcquireExternalTransform (ev, kODNULL);
               toSU->AddProperty (ev, kBCSuggestedTransform);
               embedXform->WriteTo (ev, toSU);
            }

         }

         fromDraft->EndClone(ev, key);

    } // end of try block
    catch(ODException _exception) {
         if (key)
            fromDraft->AbortClone (ev, key);
    } // end of catch block

}


// -------------------------------------------------------------------------
// BaseContainer --> ReadSingleFrame
//
//      Read a single embedded frame from destination unit.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       ODFrame *
SOMLINK         BaseContainerReadSingleFrame
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *myFacet,        // in
                ODStorageUnit   *fromSU,        // in
                ODCloneKind     cloneKind,
                ODPoint         *refPoint
                )

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerReadSingleFrame");

    ODDraftKey key = 0;
    ODFrame *newFrame = 0;
    ODDraft* fromDraft = fromSU->GetDraft(ev);

    try {

         ODDraft* toDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
         ODFrame *myDisplayFrame = myFacet->GetFrame (ev);
         ODID newPartID = 0;
         ODID newFrameID = 0;
         TempODPart newPart = 0;

         // get the part
         key = fromDraft->BeginClone (ev, toDraft, myDisplayFrame, cloneKind);
         newPartID = fromDraft->Clone (ev, key, fromSU->GetID(ev), 0, 0);

         if (newPartID == kODNULL)
         {
            fromDraft->EndClone (ev, key);
            return kODNULL;
         }

         ODStorageUnitRef aSURef;
         ODID oldFrameID = 0;

         // get the frame
         if (ODSUExistsThenFocus (ev, fromSU, kODPropContentFrame, kODWeakStorageUnitRef))
         {

            oldFrameID = ODGetWeakSURefProp (ev, fromSU, kODPropContentFrame, kODWeakStorageUnitRef);
            newFrameID = fromDraft->Clone (ev, key, oldFrameID, 0, 0);
            newFrame = toDraft->AcquireFrame (ev, newFrameID);
            newFrame->SetContainingFrame (ev, myDisplayFrame);
         }
         fromDraft->EndClone (ev, key);

         // Part is acquired only AFTER the frame is read in else EXCEPTION
         newPart = toDraft->AcquirePart (ev, newPartID);

         if (!newFrame) {

            // Attempt to create a frame
            PRINT ("Try to create a frame\n");
            TempODShape newShape = myDisplayFrame->CreateShape (ev);

            if (ODSUExistsThenFocus (ev, fromSU, kODPropSuggestedFrameShape, kODNULL))
               newShape->ReadShape (ev, fromSU);
            else
            {
               ODRect r;
               r.left = 0;
               r.right = ODIntToFixed(DEFAULT_EMBED_HEIGHT);
#if defined(_PLATFORM_OS2_)
               r.top     = ODIntToFixed(DEFAULT_EMBED_HEIGHT);;
               r.bottom  = 0;
#elif (defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_))
               r.top     = 0;
               r.bottom  = ODIntToFixed(DEFAULT_EMBED_HEIGHT);
#endif
               newShape->SetRectangle (ev, &r);
            }

            newFrame = toDraft->CreateFrame(ev,
                                            kODFrameObject,     // frameType
                                            myDisplayFrame,    // containingFrame
                                            newShape,           // frameShape
                                            (ODCanvas*)kODNULL, // biasCanvas
                                            newPart,       // part
                                            _fFrameView,        // viewType
                                            _fSession->Tokenize(ev, kODPresDefault),
                                            kODFalse,           // isRoot
                                            kODFalse);          // isOverlaid
         }

         newFrame->SetDragging (ev, kODFalse);
         newFrame->SetInLimbo (ev, kODFalse);

         // create a facet for the frame
         ODTransform *embedTransform = myDisplayFrame->CreateTransform(ev);
         if (ODSUExistsThenFocus (ev, fromSU, kBCSuggestedTransform, kODNULL))
         {
            // Read in the stored transform and zero out the translation factor
            // We need to preserve rotation and scaling

            embedTransform->ReadFrom (ev, fromSU);
            ODPoint tempOffset;
            embedTransform->GetOffset (ev, &tempOffset);
            tempOffset.x = -tempOffset.x; tempOffset.y = -tempOffset.y;
            embedTransform->MoveBy (ev, &tempOffset);
         }


         if (refPoint)
         {
            embedTransform->MoveBy (ev, refPoint);
#if defined (_PLATFORM_OS2_)
            ODRect frameRect;
            TempODShape s = newFrame->AcquireFrameShape (ev, kODNULL);
            s->GetBoundingBox (ev, &frameRect);
            ODPoint offset(0,0);
            offset.y = frameRect.bottom - frameRect.top;
            embedTransform->MoveBy (ev, &offset);
#endif
         }

         TempODShape newFrameShape = newFrame->AcquireFrameShape (ev, kODNULL);
         ODShape *clipShape = newFrameShape ->Copy (ev);

         ODFacet *embedFacet = myFacet->CreateEmbeddedFacet (ev, newFrame,
                               clipShape,embedTransform, kODNULL, kODNULL,
                               kODNULL, kODFrameInFront);

         newFrame->Invalidate (ev, kODNULL, kODNULL);
         newFrame->ChangeLinkStatus (ev, kODNotInLink);

    } // end of try block
    catch(ODException _exception) {
         if (key)
            fromDraft->AbortClone (ev, key);

    } // end of catch block

    return newFrame;

}


// -------------------------------------------------------------------------
// BaseContainer --> GetContentObjectFromObjType
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         BaseContainerGetContentObjectFromObjType
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODULong         objType,
                ContentObject   **contentObject
                )

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerReadSingleFrame");

    switch (objType) {

       case COBJ_BASECLASS:
          *contentObject = new ContentObject();
          break;

       case COBJ_FRAMECLASS:
          *contentObject = (ContentObject*) new ContentFrame();
          break;

       default:
          WARNMSG(WARN_INDEX(-1), "Invalid type retrieved!!");
          break;
    }
}


// -------------------------------------------------------------------------
// BaseContainer--> WriteIconToSU
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerWriteIconToSU
                (
                BaseContainer       *somSelf,       // in
                Environment         *ev,            // in
                ODStorageUnit       *toSU   // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerWritePartInfo");

#ifdef _PLATFORM_OS2_
// Customized icon support for OS2.

     HMODULE hmod;
     ULONG cbIconSize;
     PBYTE pIconData = NULL;
     //APITEST rc = 0;
     CHAR Error[256] = "";

     DosLoadModule(Error, sizeof(Error), "iodbasec", &hmod);

     if ( !DosQueryResourceSize( hmod, RT_POINTER, kODIcon, &cbIconSize) &&
         !DosGetResource( hmod, RT_POINTER, kODIcon, (PPVOID)&pIconData)  )
     {
        InitPropVal (ev, toSU,kODPropIconFamily , kODIconFamily);
        StorageUnitSetValue( toSU, ev, cbIconSize, (ODValue)pIconData );
        DosFreeResource(pIconData);
     }
     else
        PRINT("DosGetResource failed!\n");

#endif // _PLATFORM_OS2_

}

// -------------------------------------------------------------------------
// BaseContainer --> WriteFrameListHeader
//
//      Writes the header of the frame list to storage.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         BaseContainerWriteFrameListHeader
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *toSU,          // in
                BCCloneInfo     *cloneInfo,
                ODULong         writeKind,
                ALinkedList     *objectList
                )

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerWriteFrameListHeader");


    ODULong     numFrames      = 0;
    TempODShape aggregateShape = kODNULL;
    ALink*      itr            = kODNULL;

    ContentFrame *embeddedObject;

    for (itr = objectList->First(ev); itr->Content(ev); itr=itr->Next(ev))
    {
       embeddedObject = (ContentFrame *) (itr->Content(ev));

       // Only account for embedded frames. Do not include intrinsic content.
       if(embeddedObject->_get_objType(ev) != COBJ_FRAMECLASS) continue;

       // Get the embedded frame shape in its containing part content coordinates.
       ODFrame     *frame     = embeddedObject->_get_myFrame(ev);
       ODFacet     *facet     = FirstFacet(ev, frame);
       TempODShape frameShape = frame->AcquireFrameShape(ev, kODNULL);
       TempODShape tempShape  = frameShape->Copy(ev);
       TempODTransform xform  = facet->AcquireExternalTransform(ev, kODNULL);
       tempShape->Transform(ev, xform);

       if(aggregateShape == kODNULL){
          aggregateShape = frame->CreateShape(ev);
       }

       // AggregateShape is the union of all frame shapes. It is different
       // from the selected shape because it does not include intrinsic
       // content.
       aggregateShape->Union(ev, tempShape);

       numFrames++;
    }

    // If there are no embedded frames, there is nothing to externalize.
    if(numFrames == 0) return;

    // AggreagateBBox is the imaginary box bounding all of the embedded frames.
    // It is defined in the containing part's content coordinates.
    ODRect aggregateBBox;
    aggregateShape->GetBoundingBox(ev, &aggregateBBox);

    // Offset is the top-left coordinate of the aggregate bounding box,
    // assuming a top-left origin coordinate system.
    ODPoint offset = aggregateBBox.TopLeft();
#ifdef _PLATFORM_OS2_
    embeddedObject->ChangePointBias(ev, &offset);
#endif

    // Extent is the width and height of the aggregate bounding box.
    ODPoint extent(aggregateBBox.Width(), aggregateBBox.Height());

    ODFrame *containingFrame = cloneInfo->myFrame;
    if(!containingFrame) {
       // When we externalize, the information in cloneInfo does not include
       // the containing frame. Use the first display frame as the containing
       // frame.
       containingFrame = (ODFrame *)_fDisplayFrames->First(ev)->Content(ev);
    }

    // The scaling factor is the scale of the internal transform of the
    // containing frame.
    ODPoint scale;
    TempODTransform intXForm = containingFrame->AcquireInternalTransform(ev, kODNULL);
    intXForm->GetScale(ev, &scale);

    // Write the values to the kODFrameList part kind.
    InitPropVal (ev, toSU, kODPropContents, kODFrameList);

    ODSetPointProp(ev, toSU, kODNULL, kODNULL, &offset);
    ODSetPointProp(ev, toSU, kODNULL, kODNULL, &extent);
    ODSetPointProp(ev, toSU, kODNULL, kODNULL, &scale);
    ODSetULongProp (ev, toSU, kODNULL, kODNULL, numFrames);

    // Allocate memory for the frameList information structure in cloneInfo.
    cloneInfo->frameListInfo = (BCFrameListInfo *)SOMMalloc(sizeof(BCFrameListInfo));

    // Create a cursor that points to the current position in the framelist
    // value.
    cloneInfo->frameListInfo->cursor = toSU->CreateCursorWithFocus(ev);

    // Store the offset in the frame list info. It is needed to calculate
    // the bounding box coordinates that will be stored for each frame.
    cloneInfo->frameListInfo->offset = offset;

}

// -------------------------------------------------------------------------
// BaseContainer --> ReadFrameListHeader
//
//      Reads frameList header from storage and sets up frameListInfo
//      structure.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         BaseContainerReadFrameListHeader
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODStorageUnit   *fromSU,          // in
                BCCloneInfo     *cloneInfo,
                ODULong         readKind,
                FrameListHeader *header
                )

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerReadFrameListHeader");

    ODGetPointProp(ev, fromSU, kODNULL, kODNULL, &(header->offset));
    ODGetPointProp(ev, fromSU, kODNULL, kODNULL, &(header->extent));
    ODGetPointProp(ev, fromSU, kODNULL, kODNULL, &(header->scale));
    header->numFrames = ODGetULongProp(ev, fromSU, kODNULL, kODNULL);

    // Allocate memory for the frameList information structure in cloneInfo.
    cloneInfo->frameListInfo = (BCFrameListInfo *)SOMMalloc(sizeof(BCFrameListInfo));
    memset (cloneInfo->frameListInfo, 0, sizeof (BCFrameListInfo));

    cloneInfo->frameListInfo->offset = header->offset;

}

// -------------------------------------------------------------------------
// BaseContainer --> ReleaseFrameListInfo
//
//      Releases the frameListInfo->cursor and the frameListInfo structure
//      of the cloneInfo structure.
//
//      -> This method is a private method of BaseContainer
//
// -------------------------------------------------------------------------
SOM_Scope       void
SOMLINK         BaseContainerReleaseFrameListInfo
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                BCCloneInfo     *cloneInfo
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerReleaseFrameListInfo");

    if(cloneInfo->frameListInfo) {

       // Delete the storage unit cursor
       if(cloneInfo->frameListInfo->cursor)
          cloneInfo->frameListInfo->cursor->somFree();

       // Deallocate memory for frameListInfo
       SOMFree(cloneInfo->frameListInfo);
       cloneInfo->frameListInfo = kODNULL;
    }
}
