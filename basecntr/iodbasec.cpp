/* @(#) 1.127 com/src/samples/basecntr/iodbasec.cpp, odbasepart, od96os2, odos29714c 4/2/97 07:36:43 [4/2/97 17:20:01] */

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
//
//====END_GENERATED_PROLOG========================================
//

#define SOM_Module_iodbasec_Source
#define BaseContainer_Class_Source

#define VARIABLE_MACROS
#define SOM_DONT_IMPORT_CLASS_ALink
#define SOM_DONT_IMPORT_CLASS_ALinkedList
#define SOM_DONT_IMPORT_CLASS_BCIterator
#define SOM_DONT_IMPORT_CLASS_ContentObject
#define SOM_DONT_IMPORT_CLASS_ContentFrame


// definition for class name; use it for adding HELP menu
#define kBCClassName "BaseContainer"

#ifdef _PLATFORM_OS2_
/* One of the #include's below must be including <os2.h>, because by the time */
/* we try to include it, it has already been included, so we don't get into   */
/* the INCL_DEV portion, causing the structures referred to in IODPRINT.HPP   */
/* to be unknown.  If we ever need to add any other INCL_???'s, they should   */
/* go here also.  Probably all of the INCL_???'s should go here (but not the  */
/* #include <os2.h> itself, since the headers below might define additional   */
/* INCL_???'s, which would need to be done before the #include <os2.h>).      */
#define INCL_DEV
#endif

#include <AltPoint.h>
#include <BArray.h>
#include <FocusLib.h>
#include <ODMath.h>

#ifdef _PLATFORM_UNIX_
#include <odres.h>
#else
#include <ODRes.h>
#endif

#include <ODTypes.h>
#include <StorUtil.h>
#include <TempObj.h>
#include <WinUtils.h>

#ifndef  SOM_BCIterator_xh
#include <iodbcitr.xh>
#endif

#ifndef SOM_ODArbitrator_xh
#include <Arbitrat.xh>
#endif

#ifndef SOM_ODCanvas_xh
#include <Canvas.xh>
#endif

#ifndef SOM_ODClipboard_xh
#include <Clipbd.xh>
#endif

#ifndef SOM_ODDragItemIterator_xh
#include <DgItmIt.xh>
#endif

#ifndef SOM_ODDragAndDrop_xh
#include <DragDrp.xh>
#endif

#ifndef SOM_ODFacet_xh
#include <Facet.xh>
#endif

#ifndef SOM_ODFocus_xh
#include <Foci.xh>
#endif

#ifndef SOM_ODFocusSet_xh
#include <FocusSet.xh>
#endif

#ifndef SOM_ODFrame_xh
#include <Frame.xh>
#endif

#ifndef SOM_ODFrameFacetIterator_xh
#include <FrFaItr.xh>
#endif

#ifndef SOM_ODFacetIterator_xh
#include <FacetItr.xh>
#endif

#ifndef SOM_ODMenubar_xh
#include <MenuBar.xh>
#endif

#ifndef SOM_ODSession_xh
#include <ODSessn.xh>
#endif

#ifndef SOM_ODShape_xh
#include <Shape.xh>
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

#ifndef SOM_ODStorageUnitCursor_xh
#include <SUCursor.xh>
#endif

#ifndef SOM_ODTransform_xh
#include <Trnsform.xh>
#endif

#ifndef SOM_ODWindow_xh
#include <Window.xh>
#endif

#if defined(_PLATFORM_WIN32_)

#ifndef SOM_ODWin32Canvas_xh
#include <WinPCanv.xh>
#endif
#endif // defined win32


#if defined(_PLATFORM_OS2_)
#ifndef SOM_ODOS2Canvas_xh
#include <OS2PCanv.xh>
#endif
#endif // defined OS2

#ifdef _PLATFORM_UNIX_
#include <AIXPCanv.xh>
#include <AIXWCanv.xh>
#endif

#ifndef SOM_ODWindowState_xh
#include <WinStat.xh>
#endif

#if defined(_PLATFORM_UNIX_)
#   define QPRINTF printf
#   include <Xm/XmAll.h>
#   include <X11/cursorfont.h>

#elif defined(_PLATFORM_OS2_)
#   define QPRINTF qprintf

#   define INCL_DOS
#   define INCL_DEV
#   define INCL_GPI
#   define INCL_GPIPOLYGON
#   define INCL_WIN
#   define INCL_WINFRAMEMGR
#   define INCL_WINPOINTERS
#   define INCL_WINWINDOWMGR
#   define INCL_WINHELP
#   include <os2.h>

#elif defined(_PLATFORM_WIN32_)
#   include <windows.h>
#   include <winuser.h>
#   include <wingdi.h>

#endif

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
#ifndef SOM_ODPrintExtension_xh
#include <IODPrint.hpp> //must come after #include <os2.h> - requires INCL_DEV
#include <IODPrint.xh>
#endif

#ifndef SOM_ODScrollExtension_xh
#include <IODScrol.hpp>
#include <IODScrol.xh>
#endif
#endif //defined OS2 || WIN32

// This is the Base Container's subclass of the ODSettingsExtension class.
#ifndef SOM_BCSettingsExt_xh
#include <iodbcset.xh>
#endif

// Need to include this since this part creates a Settings Extension.
#include <StdExts.xh>

#ifndef _PLATFORM_AIX_
#include <ODResrc.h>
#endif

#include <iostream.h>
#include <ODRegApi.h>
#include <locale.h>
#include <wchar.h>
#include <ODDebug.h>
#include <StdTypIO.h>

#include <iodbasec.xih>

#ifdef _PLATFORM_UNIX_
String colors[]={
       "gray","orange","plum","white","turquoise",
       "red","green","yellow","aquamarine","SkyBlue",
       "cyan","brown","blue","maroon","purple"};
#endif


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
//           INLINE FUNCTIONS FOR RELEASING AND DELETING OBJECTS
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
inline ODTransform* ODCopyAndRelease( Environment *ev, ODTransform *t )
{
        ASSERT(t!=kODNULL, kODErrIllegalNullInput);
        if( t->GetRefCount(ev) == 1 )
                return t;
        TempODTransform tempT = t;              // Ensures that t gets released
        ODTransform *copy = t->Copy(ev);
        return copy;
}

inline ODShape* ODCopyAndRelease( Environment *ev, ODShape *s )
{
        ASSERT(s!=kODNULL, kODErrIllegalNullInput);
        if( s->GetRefCount(ev) == 1 )
                return s;
        TempODShape tempS = s;          // Ensures that s gets released
        ODShape *copy = s->Copy(ev);
        return copy;
}


inline void ODRelease( Environment *ev, ODRefCntObject* obj )
{
        if( obj )
                obj->Release(ev);
}

inline void ODSafeReleaseObject( ODRefCntObject *obj )
{
        if( obj ) {
        try{
                obj->Release(somGetGlobalEnvironment());
            }
        catch (...) {}
        }
}

extern ContentFrame *GetContentObjectForFrame(ODFrame *frame, ALinkedList *l);

#if defined(_PLATFORM_OS2_)
void InflateRect( ODRect *prectl, long dx, long dy )
{
 prectl->left   -= dx;
 prectl->right  += dx;
 prectl->bottom -= dy;
 prectl->top    += dy;
}
#elif (defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_))
void InflateRect( ODRect *prectl, long dx, long dy )
{
 prectl->left   -= dx;
 prectl->right  += dx;
 prectl->bottom += dy;
 prectl->top    -= dy;
}
#endif

#define ODReleaseObject(EV,OBJ)          \
     do{ ODRefCntObject *temp = (OBJ);   \
          (OBJ) = kODNULL;               \
          ODRelease((EV),temp); } while(0)


#ifdef _PLATFORM_OS2_
#include <os2plat.cpp>
#endif

#include <bcxfer.cpp>
#include <iodbcvwt.cpp>

extern ODFacet* FirstFacet (Environment *ev, ODFrame *frame);

// -------------------------------------------------------------------------
// -----                                                               -----
// -----                BaseContainer MetaClass                        -----
// -----                                                               -----
// -----              Overriding Inherited Methods                     -----
// -----                                                               -----
/* The methods are divided into 9 groups
   Group 1: Initialization code: Metaclass methods, Init/UnInit, Release,
            BuildMenu, Embed, Open, CreateWindow, ColorSelection
   Group 2: RequestEmbeddedFrame, RequestFrameShape, GetEmbeddedFrames,
            CreateEmbeddedFramesIter
   Group 3: Draw code: Draw, GetPrintResolution, AdjustBorderShape,
            SelectionBorderCode
   Group 4: Facet/Frame: FacetAdded/Removed, DisplayFrameAdded/Removed/Closed
                                             /Connected
   Group 5: Focus code: Commit/Begin/AbortRelinquishFocus, FocusAcquired/Lost
            ActivateFrame/Window
   Group 6: Linking code
   Group 7: Extensions
   Group 8: Undo/Redo
   Group 9: Notification methods: ViewTypeChaged/FrameShapeChanged/GeometryChanged
            SequenceChanged/PresChanged etc..
*/
// -------------------------------------------------------------------------

// ** Group 1
#ifdef __IBMC__
#pragma linkage (SOMInitModule, system)
#endif

SOMEXTERN void SOMLINK SOMInitModule (long majorversion, long minorversion,
                                        string className)
{
    SOM_IgnoreWarning (majorversion);
    SOM_IgnoreWarning (minorversion);
    SOM_IgnoreWarning (className);
    BaseContainerNewClass(BaseContainer_MajorVersion,BaseContainer_MinorVersion);
}

#ifdef _PLATFORM_OS2_
#pragma export (SOMInitModule)
#endif


// -------------------------------------------------------------------------
// M_BaseContainer --> clsGetODPartHandlerName
//
//      Returns the BaseContainer internal Part Handler name.
//
//      -> public method of BaseContainer MetaClass
// -------------------------------------------------------------------------

SOM_Scope       ISOString
SOMLINK         M_BaseContainerPartclsGetODPartHandlerName
                (
                M_BaseContainer *somSelf,       // in
                Environment *ev                 // in
                )

{
//  M_BaseContainerData *somThis = M_BaseContainerGetData(somSelf);
    M_BaseContainerMethodDebug("M_BaseContainer","M_BaseContainerPartclsGetODPartHandlerName");


    string handlerName = (string)SOMMalloc(strlen(kBaseContainerPartHandlerName)+1);
    strcpy(handlerName,kBaseContainerPartHandlerName);

    return (ISOString) handlerName;
}



// -------------------------------------------------------------------------
// M_BaseContainer --> clsGetODPartHandlerDisplayName
//
//      Defines and returns the BaseContainer displayable name.
//
//      -> public method of BaseContainer MetaClass
//      -> Part Handler name is hard coded in this example
// -------------------------------------------------------------------------

SOM_Scope       string
SOMLINK         M_BaseContainerPartclsGetODPartHandlerDisplayName
                (
                M_BaseContainer *somSelf,       // in
                Environment *ev                 // in
                )
{
//  M_BaseContainerData *somThis = M_BaseContainerGetData(somSelf);
    M_BaseContainerMethodDebug("M_BaseContainer","M_BaseContainerPartclsGetODPartHandlerDisplayName") ;


    string displayName = (string)SOMMalloc(strlen(kBaseContainerPartHandlerDisplayName)+1);
    strcpy(displayName,kBaseContainerPartHandlerDisplayName);

    return displayName;
}



// -------------------------------------------------------------------------
// M_BaseContainer --> clsGetODPartKinds
//
//      Queries the OpenDoc registry for PartKind info.
//
//      -> public method of BaseContainer MetaClass
// -------------------------------------------------------------------------

SOM_Scope       _IDL_SEQUENCE_PartKindInfo
SOMLINK         M_BaseContainerPartclsGetODPartKinds
                (
                M_BaseContainer *somSelf,       // in
                Environment *ev                 // in
                )
{
//  M_BaseContainerData *somThis = M_BaseContainerGetData(somSelf);
    M_BaseContainerMethodDebug("M_BaseContainer","M_BaseContainerPartclsGetODPartKinds");



    _IDL_SEQUENCE_PartKindInfo BaseContainerPartInfo;

    // Create array of PartKindInfo structures
    PartKindInfo * info = (PartKindInfo *)SOMCalloc(2, sizeof(PartKindInfo));

    // Allocate memory for the first PartKindInfo's fields
    info[0].partKindName = (ISOString) SOMMalloc(strlen(kBaseContainerPartKind) + 1);
    info[0].partKindDisplayName = (string)SOMMalloc(strlen(kBaseContainerPartKindDisplayName)+1);
    info[0].filenameFilters =  (string)SOMMalloc(strlen("")+1);
    info[0].filenameTypes =  (string)SOMMalloc(strlen("")+1);
    info[0].categories =  (string)SOMMalloc(strlen(kBaseContainerPartCategory)+1);
    info[0].categoryDisplayName =  (string)SOMMalloc(strlen("")+1);
    info[0].objectID =  (string)SOMMalloc(strlen("")+1);

    // Copy the information into the structure
    strcpy(info[0].partKindName , kBaseContainerPartKind);
    strcpy(info[0].partKindDisplayName, kBaseContainerPartKindDisplayName);
    strcpy(info[0].filenameFilters, "");
    strcpy(info[0].filenameTypes, "");
    strcpy(info[0].categories, kBaseContainerPartCategory);
    strcpy(info[0].categoryDisplayName, "");
    strcpy(info[0].objectID, "");

    // Allocate memory for the second PartKindInfo's fields
    info[1].partKindName = (ISOString) SOMMalloc(strlen(kODFrameList) + 1);
    info[1].partKindDisplayName = (string)SOMMalloc(strlen(kODFrameListUserString)+1);
    info[1].filenameFilters =  (string)SOMMalloc(strlen("")+1);
    info[1].filenameTypes =  (string)SOMMalloc(strlen("")+1);
    info[1].categories =  (string)SOMMalloc(strlen("")+1);
    info[1].categoryDisplayName =  (string)SOMMalloc(strlen("")+1);
    info[1].objectID =  (string)SOMMalloc(strlen("")+1);

    // Copy the information into the structure
    strcpy(info[1].partKindName , kODFrameList);
    strcpy(info[1].partKindDisplayName, kODFrameListUserString);
    strcpy(info[1].filenameFilters, "");
    strcpy(info[1].filenameTypes, "");
    strcpy(info[1].categories, "");
    strcpy(info[1].categoryDisplayName, "");
    strcpy(info[1].objectID, "");

    BaseContainerPartInfo._maximum = 2;
    BaseContainerPartInfo._length = 2;
    BaseContainerPartInfo._buffer = info;



    return BaseContainerPartInfo;
}



// -------------------------------------------------------------------------
// M_BaseContainer --> clsGetOLE2ClassId
//
//      Returns the OLE2 Class ID defined for this part.
//
//      -> public method of BaseContainer MetaClass
// -------------------------------------------------------------------------

SOM_Scope       string
SOMLINK         M_BaseContainerPartclsGetOLE2ClassId
                (
                M_BaseContainer *somSelf,       // in
                Environment *ev                 // in
                )
{
//  M_BaseContainerData *somThis = M_BaseContainerGetData(somSelf);
    M_BaseContainerMethodDebug("M_BaseContainer","M_BaseContainerPartclsGetOLE2ClassId");


    // OLE2 Class ID is determined by running the tool UUIDGEN.EXE
    // or GUIDGEN.EXE found in the IBM VAC++ SDK\BIN directory
    // this tool is gauranteed to generate a unique ID based on your
    // network address and the time of day (DCE Standard)


    string OLE2 = "{e2c13b60-a403-11cf-973b-0004ac77f242}";
    string OLE2ClassId = (string)SOMMalloc(strlen(OLE2)+1);
    strcpy(OLE2ClassId,OLE2);


    return OLE2ClassId;
}



// -------------------------------------------------------------------------
// M_BaseContainer --> clsGetWindowsIconFileName
//
//      Returns the Windows Icon Filename defined for this part.
//
//      -> public method of BaseContainer MetaClass
// -------------------------------------------------------------------------

SOM_Scope       string
SOMLINK         M_BaseContainerPartclsGetWindowsIconFileName
                (
                M_BaseContainer *somSelf,       // in
                Environment *ev                 // in
                )
{
//  M_BaseContainerData *somThis = M_BaseContainerGetData(somSelf);
    M_BaseContainerMethodDebug("M_BaseContainer","M_BaseContainerPartclsGetWindowsIconFileName");



    string kWindowsIcon = "iodbasec.ico";
    string WindowsIconFileName = (string)SOMMalloc(strlen(kWindowsIcon)+1);
    strcpy(WindowsIconFileName,kWindowsIcon);


    return WindowsIconFileName;
}


// -------------------------------------------------------------------------
/*                  BaseContainer Class
*/
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
// SOMObject --> somInit
//
//      Initializes the instance variables in the SOMObject of this part.
//
//      -> somInit must NOT fail (code that might fail goes to InitPart)
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainersomInit
                (
                BaseContainer   *somSelf        // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainersomInit");



    //  (1) call parent's method before starting
    BaseContainer_parent_ODPart_somInit(somSelf);



    //  (2) initialize BaseContainer attributes
    _fSession         = kODNULL;
    _fDisplayFrames   = kODNULL;
    _fEmbeddedObjects  = kODNULL;
    _fSelectedObjects  = kODNULL;

    _fFocusSet          = kODNULL;
    _fSelectionFocus    = kODNULL;
    _fMenuFocus         = kODNULL;
    _fKeyFocus          = kODNULL;
    _fModalFocus        = kODNULL;
    _fMouseFocus        = kODNULL;
    _fMouseFocusOutside = kODNULL;
    _fFrameView         = kODNULL;
    _fLargeIconView     = kODNULL;
    _fSmallIconView     = kODNULL;
    _fThumbnailView     = kODNULL;
    _fMainPresentation  = kODNULL;
    _fPartSU            = kODNULL;

    _fDirty             = kODFalse;

    _fMenuBar           = kODNULL;
    _fEditMenu          = kODNULL;
    _fEmbedMenu         = kODNULL;
    _fColorMenu         = kODNULL;
    _fWindowID          = kODNULL;
    _fFrameViewWindow   = kODNULL;
    _fPartWrapper       = kODNULL;

    _fPartToEmbed       = kODNULL;
    _usMouseMode        = kMouseModeNull;

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    _fScrollExt = kODNULL;
    _fScrollingEnabled = kODFalse;

    _fPrintExt = kODNULL;
    _fPrintingEnabled = kODFalse;

#endif //defined OS2 || WIN32

    _fSettingsExt = kODNULL ;
}




// -------------------------------------------------------------------------
// SOMObject --> somUninit
//
//      Disposes of storage for SOMObject of this part.
//
//      -> does not call parent method (called automatically by SOM)
//      -> optional for all parts
//
//      -> somUninit must NOT fail
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainersomUninit
                (
                BaseContainer   *somSelf        // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainersomUninit");


    Environment* ev = somGetGlobalEnvironment();

    if (_fFocusSet)       delete _fFocusSet;

    if (_fDisplayFrames)  delete _fDisplayFrames;
    if (_fEmbeddedObjects) delete _fEmbeddedObjects;
    if (_fSelectedObjects) delete _fSelectedObjects;

    if (_fMouseStart)
      delete _fMouseStart;

    // call parent's method after you're finished and before you exit
    BaseContainer_parent_ODPart_somUninit(somSelf);



}

//--------------------------------------------------------------------------
// ODPart ----> Release
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerRelease
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev            // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerRelease");

    BaseContainer_parent_ODPart_Release(somSelf, ev);
    if (somSelf->GetRefCount(ev) == 0) {
       somSelf->GetStorageUnit(ev)->GetDraft(ev)->ReleasePart (ev, _fPartWrapper);
    }
}

//--------------------------------------------------------------------------
// ODPart ----> ReleaseAll
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerReleaseAll
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev            // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerReleaseAll");

    ODSafeReleaseObject((ODRefCntObject *)_fMenuBar);
    ODSafeReleaseObject((ODRefCntObject *)_fEditMenu);
    ODSafeReleaseObject((ODRefCntObject *)_fEmbedMenu);

    ODReleaseObject (ev, _fSelectShape);
    ODReleaseObject (ev, _fCornerHandleShape);
    ODReleaseObject (ev, _fEdgeHandleShape);

#ifdef _PLATFORM_OS2_

    if( _hSmallIcon ) WinDestroyPointer(_hSmallIcon);
    if( _hLargeIcon ) WinDestroyPointer(_hLargeIcon);
    if( _hThumbnail ) WinDestroyPointer(_hThumbnail);

#elif defined(_PLATFORM_UNIX_)

    if (_iconWidget) {
       XtUnmanageChild(_iconWidget);
       XtDestroyWidget(_iconWidget);
    }

    // Get the screen
    Screen *screen = _fSession->GetWindowState(ev)->GetScreen(ev);

    if( _hSmallIcon ) XmDestroyPixmap(screen, _hSmallIcon);
    if( _hLargeIcon ) XmDestroyPixmap(screen, _hLargeIcon);
    if( _hThumbnail ) XmDestroyPixmap(screen, _hThumbnail);

#endif

    // Free the resource module.
    somSelf->FreeResModule(ev);

    BaseContainer_parent_ODPart_ReleaseAll(somSelf, ev);

    //----------------------------------------------------------------------
    // The references to the extension objects in our instance data, are not
    // reference counted.  The extension will invoke our ReleaseExtension
    // method (because we are the registered BaseObject) when the reference
    // count goes to zero (meaning no OTHER references to the extension object
    // are being retained and no other user exists for the extension).
    // ReleaseExtension will delete the object and clear our instance pointer.
    // Here we address the case of perhaps removing the extension's baseObject
    // before all other references are released.  In that case we need to inform
    // the Extension that we are no longer available as the BaseObject, by
    // invoking BaseRemoved of the extension.
    //----------------------------------------------------------------------
#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    if (_fScrollExt != kODNULL) {
       _fScrollExt->BaseRemoved(ev);
    }
    if (_fPrintExt != kODNULL) {
       _fPrintExt->BaseRemoved(ev);
    }
#endif // OS/2 or Win95/NT

    if (_fSettingsExt != kODNULL) {
       _fSettingsExt->BaseRemoved(ev) ;
    }
}

// -------------------------------------------------------------------------
// BaseContainer --> Initialize
//
//      Common code needed by the InitPart* methods.
//
//      -> private method of BaseContainer
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerInitialize
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODPart          *partWrapper    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerInitialize");



    try {

        // Cache references to Session object and other global values
        _fSession    =   somSelf->GetStorageUnit(ev)
                                ->GetSession(ev);
        _fDraftReadOnly = (somSelf->GetStorageUnit(ev)->GetDraft(ev)->GetPermissions(ev) == kODDPReadOnly);
        _fNeedToInternalize = kODFalse;

#ifdef _PLATFORM_UNIX_
        _fDisplay = _fSession->GetWindowState(ev)->GetDisplay(ev);
#endif


        // Tokenize Foci
        _fSelectionFocus = _fSession->Tokenize(ev, kODSelectionFocus);
        _fMenuFocus      = _fSession->Tokenize(ev, kODMenuFocus);
        _fKeyFocus       = _fSession->Tokenize(ev, kODKeyFocus);
        _fModalFocus     = _fSession->Tokenize(ev, kODModalFocus);

        // for clipboard menuitem enable/disable in AdjustMenus method
        _fClipboardFocus = _fSession->Tokenize(ev,kODClipboardFocus);

        // for tracking mouse events for click and drag
        _fMouseFocus        = _fSession->Tokenize(ev,kODMouseFocus);
        _fMouseFocusOutside = _fSession->Tokenize(ev, kODMouseUpOutsideFocus);
        if (_fSession->GetArbitrator(ev)->IsFocusRegistered (ev, _fMouseFocusOutside) == kODFalse)
           _fSession->GetArbitrator (ev)->RegisterFocus (ev, _fMouseFocusOutside, kODNULL);

        // Create a Focus Set for this Part Handler
        _fFocusSet = _fSession->GetArbitrator(ev)
                              ->CreateFocusSet(ev);
        _fFocusSet->Add(ev, _fKeyFocus);
        _fFocusSet->Add(ev, _fMenuFocus);
        _fFocusSet->Add(ev, _fSelectionFocus);

        // Set up linked lists of Frames
        _fDisplayFrames  = new ALinkedList;
        _fEmbeddedObjects = new ALinkedList;
        _fSelectedObjects = new ALinkedList;

        //
        _fMouseStart = new ODPoint;

        // Tokenize ViewTypes and presentation strings
        _fFrameView     = _fSession->Tokenize(ev, kODViewAsFrame);
        _fSmallIconView = _fSession->Tokenize(ev, kODViewAsSmallIcon);
        _fLargeIconView = _fSession->Tokenize(ev, kODViewAsLargeIcon);
        _fThumbnailView = _fSession->Tokenize(ev, kODViewAsThumbnail);

        // Initialize value of previous viewtype variable
        _fPrevViewType = _fFrameView;

        // initialize background color (arbitrary choices)
        _fBackgroundColor = somSelf->ColorSelection(ev,_fBackgroundColor,0);



        // Create shapes for storing selection border
        // We do not have frame or facet here, so cannot use factory methods
        _fSelectShape = new ODShape();
        _fSelectShape->InitShape(ev);
        _fSelectShape->Acquire(ev);
        _fCornerHandleShape = new ODShape();
        _fCornerHandleShape->InitShape(ev);
        _fCornerHandleShape->Acquire(ev);
        _fEdgeHandleShape = new ODShape();
        _fEdgeHandleShape->InitShape(ev);
        _fEdgeHandleShape->Acquire(ev);

        _moveData = _resizeData = _lassoData = kODNULL;

         //-------//   Create MenuBar for BaseContainer Part   //------//


        _fMenuBar = somSelf->GetStorageUnit(ev)
                           ->GetSession(ev)
                           ->GetWindowState(ev)->CopyBaseMenuBar(ev);

        if (_fMenuBar)
            somSelf->InstallMenuItems (ev, _fMenuBar);

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
        somSelf->AcquireExtension(ev, kODPrintExtension) ;
#endif
    }  // end of try block
    catch (...) {}

}


// -------------------------------------------------------------------------
// BaseContainer --> InstallMenuItems
// -------------------------------------------------------------------------


SOM_Scope       void
SOMLINK         BaseContainerInstallMenuItems
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,             // in
                ODMenuBar       *menuBar
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerInstallMenuItems");

#if defined(__IBMCPP__) || defined(_IBMR2)
    nl_catd bcNLSCat;       // NLS message catalog handle
    char *bcText;           // pointer for NLS message
    setlocale(LC_MESSAGES, NULL);
    bcNLSCat = catopen("iodbasec.cat", 0);
    if (bcNLSCat == CATD_ERR)
           {
              PRINT("Could not open BaseContainer Message catalog!\n");
           }
#else
    char bcText[256];
#endif

    menuBar->Acquire(ev);

    ODPlatformMenuItem *mi = new ODPlatformMenuItem;

    // clear the memory
    memset (mi, 0, sizeof(ODPlatformMenuItem));

    // add a menu separator line to EDIT menu
    somSelf->AddSeparatorToMenu(ev, menuBar, IDMS_EDIT, CMD(Dash));

    // add MOVE selection item to EDIT menu
    mi->id=CMD(Move);
    somSelf->CreateMenuItemFromCatalog(ev,
                                       menuBar,
                                       IDMS_EDIT,
                                       mi,
                                       bcNLSCat,
                                       BCMSG_SET,
                                       PLATFORMSTRID(BC_MOVE),
                                       "Move");

    // add MOVEFRONT selection item to EDIT menu
    mi->id=CMD(MoveFront);
    somSelf->CreateMenuItemFromCatalog(ev,
                                       menuBar,
                                       IDMS_EDIT,
                                       mi,
                                       bcNLSCat,
                                       BCMSG_SET,
                                       PLATFORMSTRID(BC_MOVE2FRONT),
                                       "Move To Front");

    // add MOVEBACK selection item to EDIT menu
    mi->id=CMD(MoveBack);
    somSelf->CreateMenuItemFromCatalog(ev,
                                       menuBar,
                                       IDMS_EDIT,
                                       mi,
                                       bcNLSCat,
                                       BCMSG_SET,
                                       PLATFORMSTRID(BC_MOVE2BACK),
                                       "Move To Back");

    // add RESIZE selection item to EDIT menu
    mi->id=CMD(Resize);
    somSelf->CreateMenuItemFromCatalog(ev,
                                       menuBar,
                                       IDMS_EDIT,
                                       mi,
                                       bcNLSCat,
                                       BCMSG_SET,
                                       PLATFORMSTRID(BC_RESIZE),
                                       "Resize");


    // add EMBED menu to MenuBar line
    somSelf->CreateNewMenu(ev, menuBar, kODEmbedMenuID);
    mi->id=kODEmbedMenuID;
    somSelf->SetMenuItemTextFromCatalog(ev,
                                       menuBar,
                                       ID_BASEMENUBAR,
                                       mi,
                                       bcNLSCat,
                                       BCMSG_SET,
                                       PLATFORMSTRID(BC_EMBED),
                                       "Embed");


    somSelf->BuildEmbedMenu(ev, mi);

    //  Add color menu item
    somSelf->CreateNewMenu(ev, menuBar, kODOptionsMenuID);
    mi->id=kODOptionsMenuID;
    somSelf->SetMenuItemTextFromCatalog(ev,
                                       menuBar,
                                       ID_BASEMENUBAR,
                                       mi,
                                       bcNLSCat,
                                       BCMSG_SET,
                                       PLATFORMSTRID(BC_OPTIONS),
                                       "Options");


    // add COLOR CHANGE selection item to COLOR menu
    mi->id=kODCommandColorCHANGE;
    somSelf->CreateMenuItemFromCatalog(ev,
                                       menuBar,
                                       kODOptionsMenuID,
                                       mi,
                                       bcNLSCat,
                                       BCMSG_SET,
                                       PLATFORMSTRID(BC_COLOR_CHG),
                                       "Change Background");

   //let's add help menu items ONLY if this is base container
   // and not its subclass
   if (!strcmp (somSelf->somGetClassName(), kBCClassName))
   {

    // add a menu separator line to HELP menu
    somSelf->AddSeparatorToMenu(ev, menuBar, IDMS_HELP, CMD(Dash));

    // add a menu item Base Container Help to HELP menu
    mi->id=CMD(Help);
    somSelf->CreateMenuItemFromCatalog(ev,
                                       menuBar,
                                       IDMS_HELP,
                                       mi,
                                       bcNLSCat,
                                       BCMSG_SET,
                                       PLATFORMSTRID(BC_HELP),
                                       "Base Container Help");

   } // end if this is a subclass

    // we can now release the MenuBar
    menuBar->Release(ev);

    delete mi;                      // cleanup menuitem buffer

#if defined(__IBMCPP__) || defined(_IBMR2)
    catclose(bcNLSCat);             // close the message catalog
#endif

}



//--------------------------------------------------------------------------
// BaseContainer -->  BuildEmbedMenu
//
//      Change the color of a container part background
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerBuildEmbedMenu
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODPlatformMenuItem *mi          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerBuildEmbedMenu");

    char    *list;                       // list of registered part handlers
    char    *dlist;                      // list of part handler display name
    wchar_t *wlist;                      // list of registered part handlers
    wchar_t *delimiter=0;                // delimiter (",") between names in list
    wchar_t *end;                        // pointer to end of list
    wchar_t *cursor;                     // pointer to char in list
    wchar_t *wEmbedItem = new wchar_t[256]; // embed menu item

    unsigned long emptysize=1;           // size of 1 to get actual size
    unsigned long goodsize=0;            // actual size of the list (above)
    int i=0;                             // counter
    int rc;

    list=new char[emptysize];
    rc=ODQueryPartHandlerList(0, (char *)list, (ODULong) &goodsize);


    list=new char[goodsize];             // get list based on the size returned
    rc=ODQueryPartHandlerList(0, (char*)list, (ODULong) &goodsize);

    wlist=new wchar_t[goodsize];         // convert to wchar_t for NLS processing
    mbstowcs(wlist,list,sizeof(wchar_t)*goodsize);

    end = wlist + wcslen(wlist) + 1;     // set pointer to the end of the list

    _fEmbedTableParts=0;                 // assume zero parts in the list
    int nCommas = 0;

    if (wcslen(wlist)>0)
       nCommas++;                        // something in list, at least one part

                                       // count commas for number of editors
                                       // then allocate fEmbedTable to count
    for (cursor=wlist; (cursor < end); cursor++) if(*cursor==L',') nCommas++;
        _fEmbedTable=new char *[nCommas];

    for (cursor=wlist, i=0; (cursor < end); i++)
    {
        delimiter = wcschr(cursor, L','); // find first/next occurence
        if(delimiter==NULL) delimiter=end;

                                       // copy part handler name from list
        memcpy(wEmbedItem, cursor, sizeof(wchar_t)*(delimiter-cursor));
        *(wEmbedItem + (delimiter - cursor)) = NULL;


        if(wcslen(wEmbedItem)>0)       // skip empty fields (NULL parthandler)
        {
                                       // allocate mbs string to hold handler
            _fEmbedTable[_fEmbedTableParts] = new char[wcslen(wEmbedItem) + 1];
            wcstombs(_fEmbedTable[_fEmbedTableParts],wEmbedItem,wcslen(wEmbedItem)+1);
// -----------------  Display PartHandlerDisplayName in Embed menu -----------
            goodsize = 0;
            dlist=new char[emptysize]; // get size of name from query
            rc=ODQueryHandlerDisplayName(0, (char *)dlist, (ODULong) &goodsize);
            dlist=new char[goodsize];  // new dlist and then get display name
            rc=ODQueryHandlerDisplayName(_fEmbedTable[_fEmbedTableParts], (char *)dlist, (ODULong) &goodsize);
// -----------------  dlist is PartHandlerDisplayName ------------------------
            mi->id=CMD(Parts)+_fEmbedTableParts;
            _fMenuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
            _fMenuBar->SetMenuItemText(ev, kODEmbedMenuID, mi->id, dlist);
            _fEmbedTableParts++;
          // now go to next part handler
        } // if null parthandler received

        cursor = delimiter +1;

    } // for loop parsing comma-separated PartHandlerList

} // end of BuildEmbedMenu


//--------------------------------------------------------------------------
// BaseContainer --> Embed
//
//      Should perform the actual embed of a new embedded part ?
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ContentObject*
SOMLINK         BaseContainerEmbed
                (
                BaseContainer   *somSelf,           // in
                Environment     *ev,                // in
                ODType          part,               // in
                ODFrame         *containingFrame,   // in
                ODTransform     *newEmbedTransform  // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerEmbed");

    try {

        // have the Draft instantiate the part
        // call CreatePart with parthandler name as optional editor, this
        // keeps binding from loading only the preferred editor.
        TempODPart embeddedPart =
                       _fPartSU->GetDraft(ev)->CreatePart(ev, kODNULL, part );

        if (embeddedPart == kODNULL)
           return kODNULL;

        // create a shape for the new part using default dimensions
        ODShape* newShape = containingFrame->CreateShape(ev);
        ODRect* rect = new ODRect;
#if defined(_PLATFORM_OS2_)
        rect->left    = 0;
        rect->top     = ODIntToFixed(DEFAULT_EMBED_HEIGHT);;
        rect->right   = ODIntToFixed(DEFAULT_EMBED_WIDTH);
        rect->bottom  = 0;
#elif (defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_))
        rect->left    = 0;
        rect->top     = 0;
        rect->right   = ODIntToFixed(DEFAULT_EMBED_WIDTH);
        rect->bottom  = ODIntToFixed(DEFAULT_EMBED_HEIGHT);
#endif
//        newShape->NewShape(ev);
        newShape->SetRectangle(ev, rect);
        delete rect;

        // create the new frame using this shape
        ODFrame* newFrame = _fPartSU->GetDraft(ev)->CreateFrame(ev,
                                        kODFrameObject,     // frameType
                                        containingFrame,    // containingFrame
                                        newShape,           // frameShape
                                        (ODCanvas*)kODNULL, // biasCanvas
                                        embeddedPart,       // part
                                        _fFrameView,        // viewType
                                        _fSession->Tokenize(ev, kODPresDefault),
                                        kODFalse,           // isRoot
                                        kODFalse);          // isOverlaid

        // add new frame to the container's list of Embedded Frames
        ContentFrame *contFrame = new ContentFrame();
        contFrame->_set_myFrame(ev, newFrame);
        _fEmbeddedObjects->AddLast(ev, contFrame);

        // get the clip shape of the newly created frame
        // (the part may have changed it from the default 100x100 shape)
        TempODShape clipShape = newFrame->AcquireFrameShape(ev, kODNULL);

#if defined (_PLATFORM_OS2_)
         // make sure that the new part appears so that its top left is at hotspot
         ODRect frameRect;
         clipShape->GetBoundingBox (ev, &frameRect);
         ODPoint offset(0,0);
         offset.y = frameRect.bottom - frameRect.top;
         newEmbedTransform->MoveBy (ev, &offset);
#endif

        // create an embedded facet for the embedded frame
        ODFrameFacetIterator *facets = containingFrame->CreateFacetIterator(ev);
        for (ODFacet* containingFacet = facets->First(ev);
                               facets->IsNotComplete(ev);
                                     containingFacet = facets->Next(ev))
        {

            ODFacet* embeddedFacet = containingFacet->CreateEmbeddedFacet(ev,
                              newFrame,          // frame
                              clipShape,         // clipShape
                              newEmbedTransform, // externalTransform
                              kODNULL,           // canvas
                              kODNULL,           // biasCanvas
                              kODNULL,           // siblingFacet
                              kODFrameInFront);  // position

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
/* Move scroll bars above newly embedded part in Z-order */
            if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
               _fScrollExt->GeometryChanged(ev, containingFacet, kODFalse, kODTrue);
            } /* endif */
#endif //defined OS2 || WIN32

            embeddedFacet->Invalidate(ev, kODNULL, kODNULL);
        }
        delete facets;

        somSelf->ChangeNotification (ev, BCC_EMBED, containingFrame,
                                     (ContentObject *)contFrame, kODTrue, kODNULL);
        return (ContentObject *) contFrame;

    }  // end of try block

    catch (ODException _exception) {

       int Error = ErrorCode();
       PRINT("Clearing exception %d\n", Error);
       SetErrorCodeEv (ev, kODNoError);
    }

    return kODNULL;
}


//--------------------------------------------------------------------------
// ODPart --> Open
//
//      Should create or activate a window in which a frame of this part
//      is the root frame.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODID
SOMLINK         BaseContainerOpen
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerOpen");


    ODID windowID = 0;

    TempODWindow window = kODNULL;

    try {

    ODWindowState* winState=_fSession->GetWindowState(ev);

    if (frame) {
        if (frame->IsRoot(ev)) {
            WindowProperties props;
            BeginGetWindowProperties(ev, frame, &props);

            ODULong flCreateFlags = props.createFlags;


            ODPlatformWindow platwin = winState->CreatePlatformWindow(ev, kODFalse);

#if defined(_PLATFORM_WIN32_)
            SetWindowPos(platwin,
                         HWND_TOP,
                         props.boundsRect.left,
                         props.boundsRect.top,
                         props.boundsRect.right,
                         props.boundsRect.bottom,
                         SWP_NOACTIVATE | SWP_NOREDRAW);
#elif defined(_PLATFORM_OS2_)
         WinSetWindowPos(platwin,
                         HWND_TOP,
                         props.boundsRect.xLeft,
                         props.boundsRect.yBottom,
                         props.boundsRect.xRight,
                         props.boundsRect.yTop,
                         props.swpFlags | SWP_SIZE | SWP_MOVE);

#elif defined(_PLATFORM_UNIX_)
            Widget TopLevelShellWidget = XtWindowToWidget(winState->GetDisplay(ev), platwin);
            XtVaSetValues(TopLevelShellWidget,
                          XmNx, props.boundsRect.x,
                          XmNy, props.boundsRect.y,
                          XmNwidth, props.boundsRect.width,
                          XmNheight, props.boundsRect.height,
                          NULL);
#endif
            window = _fSession->GetWindowState(ev)
                              ->RegisterWindowForFrame( ev,
                                                        platwin,
                                                        frame,
                                                        props.isRootWindow,
                                                        props.isResizable,
                                                        props.isFloating,
                                                        kODTrue,
                                                        kODTrue,
                                                        props.sourceFrame);

            EndGetWindowProperties(ev, &props);     // release source frame

            window->Open(ev);
            window->Show(ev);
            }

        else {
// This is commented out to temporarily disable the Open As Window capability
            //window=winState->AcquireWindow(ev, _fWindowID);
            //if (window) {
            //    window->Select(ev);
            //    }
            //else {
            //    window = somSelf->MakeWindow(ev,frame);
            //   _fWindowID= window->GetID(ev);
            //    window->Open(ev);
            //    window->Show(ev);
            //    window->Select(ev);
            //    }

            } // end of frame->IsRoot
        } // end of frame

    else {
        window = somSelf->MakeWindow(ev, frame);
        _fWindowID=window->GetID(ev);
        window->Open(ev);
        window->Show(ev);
        window->Select(ev);


        }

    if (window)
       windowID= window->GetID(ev);

   }  // end of try block
   catch (...) {}


    return windowID;
}



//--------------------------------------------------------------------------
// BaseContainer --> CreateWindow
//
//      Should create or activate a window in which a frame of this part
//      is the root frame.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODWindow*
SOMLINK         BaseContainerMakeWindow
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *sourceFrame    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerMakeWindow");

    ODPlatformWindow platwin = kODNULL;

    ODWindow* window         = kODNULL;


    try {

    ODWindowState* winState=_fSession->GetWindowState(ev);

    platwin = winState->CreatePlatformWindow(ev, kODFalse);

    window = winState->RegisterWindow(ev,
                    platwin,
                    kODFrameObject,       // frameType
                    sourceFrame==kODNULL, // isRootWindow
                    kODTrue,              // isResizable
                    kODFalse,             // isFloating
                    kODTrue,              // shouldSave
                    kODTrue,              // shouldDispose
                    _fPartWrapper,        // rootPart
                    _fSession->Tokenize(ev, kODViewAsFrame), // ViewType
                    _fSession->Tokenize(ev, kODPresDefault), // presentation
                    sourceFrame           // sourceFrame
                    );

    }  // end of try block
    catch (...) {}


    return window;
}


//--------------------------------------------------------------------------
// BaseContainer --> ColorSelection
//
//      Change the color of a container part background
//--------------------------------------------------------------------------

SOM_Scope       COLORREF
SOMLINK         BaseContainerColorSelection
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                COLORREF        origColor,      // in
                long            theflag         // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerColorSelection");

#if defined(_PLATFORM_WIN32_)
    HDC hdc;
    CHOOSECOLOR colorstruct;
    COLORREF clrCustom[16];
#elif defined(_PLATFORM_OS2_)
    HPS hps;
#elif defined(_PLATFORM_UNIX_)
    static int fColorIndex = 0;
    XColor clrcell, rgbdef;
#endif
    int rc;
    COLORREF newColor;

    static int fColor = 0;
    static int fDelta = 64;

    static int fRed   = 96;
    static int fGreen = 96;
    static int fBlue  = 96;

//----------------------------------------------------------------------------
// --------- this is used during part initialization -------------------------
// --------- cycles through a range of colors, cycles embedded frame's colors-
//----------------------------------------------------------------------------
try {
if (theflag == 0)
{
    // cycle through the color spectrum
    fColor=(fColor+1)%3;
    switch (fColor)
    {
    case 0:
         fRed=(fRed+fDelta)%256;
         break;

    case 1:
         fBlue=(fBlue+fDelta)%256;
         break;

    case 2:
         fGreen=(fGreen+fDelta)%256;
         break;
    }
#if defined(_PLATFORM_UNIX_)
    // cycle through colors using above
    Screen *screen = _fSession->GetWindowState(ev)->GetScreen(ev);
    Colormap cmap = XDefaultColormapOfScreen(screen);
    clrcell.flags = DoRed | DoGreen | DoBlue;
    clrcell.red = fRed * 256;
    clrcell.green = fGreen * 256;
    clrcell.blue = fBlue * 256;
    rc = XAllocColor(_fDisplay, cmap, &clrcell);
    if (rc == 0)   // Alloc failed
       {
          PRINT("OPENDOC couldn't get a color\n");
          newColor = origColor;
       }
    else newColor = clrcell.pixel;

#elif defined(_PLATFORM_OS2_)
    newColor = fBlue + (256L   * (long) fGreen) + (65536L * (long) fRed);
#elif defined(_PLATFORM_WIN32_)
    newColor = RGB(fRed,fGreen,fBlue);
#endif
} // end of cycle thru color spectrum


//----------------------------------------------------------------------------
//---- this is used when OPTION/ChangeBackground Menu is selected ------------
//---- WIN and OS2 use dialog boxes. UNIX currently just reads array of color-
//----------------------------------------------------------------------------
else
{
#if defined(_PLATFORM_OS2_)
     CHAR  Error[256] = "";
     HMODULE hmod;
     // Array of binary values for RGB value
     SHORT NewColors[3] = {0, 0, 0};

     ODWindowState* WinStat =  _fSession->GetWindowState(ev);
     // Use TempODWindow so this object won't have to be released.
     TempODWindow Window = WinStat->AcquireFrontRootWindow(ev);
     HWND hwnd = Window->GetPlatformWindow(ev);
     DosLoadModule( Error, sizeof(Error), "iodbasec", &hmod );

     // calculate from a long in the format of 0x--RRGGBB where -- not used
     // to shorts in the form of 0-255 for each RGB
     NewColors[RED]   = (SHORT) ((origColor / 65536L) & 0x000000FF);
     NewColors[GREEN] = (SHORT) ((origColor / 256L) & 0x000000FF);
     NewColors[BLUE]  = (SHORT) (origColor & 0x000000FF);

     // call procedures for bringing up rc file and user changing colors
     rc = ColorWindow(hmod, hwnd, NewColors);

     // calculate back to a long in the format of 0x--RRGGBB where -- not used
     newColor = NewColors[BLUE] +
                    (256L   * (long) NewColors[GREEN]) +
                    (65536L * (long) NewColors[RED]);

#elif defined(_PLATFORM_WIN32_)

      ODWindowState* WinStat =  _fSession->GetWindowState(ev);
      // Use TempODWindow so this object won't have to be released.
      TempODWindow Window = WinStat->AcquireActiveWindow(ev);
      HWND hwnd = Window->GetPlatformWindow(ev);
      // set up structure to pass to color dialog routine
      memset(&colorstruct, 0, sizeof(colorstruct));
      colorstruct.lStructSize = sizeof(colorstruct);
      colorstruct.hwndOwner = hwnd;
      colorstruct.rgbResult = RGB(0, 0, 0);
      colorstruct.Flags = CC_RGBINIT;
      for (fColor=0; fColor<16; fColor++)
        clrCustom[fColor] = RGB(255, 255, 255);
      colorstruct.lpCustColors = clrCustom;
      if (ChooseColor(&colorstruct))
          newColor = colorstruct.rgbResult;
       else
          newColor = origColor;

#elif defined(_PLATFORM_UNIX_)
    // cycle through color array defined at top of file for now
    // no color selection dialog set up yet
    Screen *screen = _fSession->GetWindowState(ev)->GetScreen(ev);
    Colormap cmap = XDefaultColormapOfScreen(screen);
    fColorIndex=(fColorIndex+1)%15;
    rc=XAllocNamedColor(_fDisplay,cmap, colors[fColorIndex], &clrcell, &rgbdef);
    if (rc == 0)   // Alloc failed
       {
          PRINT("OPENDOC couldn't get %s color\n",colors[fColorIndex]);
          newColor = origColor;
       }
    else  newColor = clrcell.pixel;

#endif
} // end resource files use


return newColor;

}  // end of try block
catch (...) {
   PRINT("Exception occurred during color selection\n");
   PRINT("Please check color availability and try again\n");
   return origColor;
   }  // end catch block

} // end of ColorSelection


// ** Group 2
//--------------------------------------------------------------------------
// ODPart --> RequestEmbeddedFrame
//
//      Should create a new display frame for the specified embedded part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODFrame*
SOMLINK         BaseContainerRequestEmbeddedFrame
                (
                BaseContainer   *somSelf,           // in
                Environment     *ev,                // in
                ODFrame         *containingFrame,   // in
                ODFrame         *baseFrame,         // in
                ODShape         *frameShape,        // in
                ODPart          *embedPart,         // in
                ODTypeToken      viewType,          // in
                ODTypeToken      presentation,      // in
                ODBoolean        isOverlaid         // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerRequestEmbeddedFrame");
    ODFrame *newFrame = NULL;

    try {

        // Invert the mouse coords (placing it in the containing frame coords)
        //xform->InvertPoint(ev, _fCrossHair);

        // create new external transform to this location
        ODTransform* newEmbedTransform = containingFrame->CreateTransform(ev);
        //newEmbedTransform->SetOffset(ev, _fCrossHair);

        // create a shape for the new part (default to 100x100)
        ODShape* newShape = containingFrame->CreateShape(ev);

        ODRect* rect = new ODRect;

#if (defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_))
        rect->left    = 0;
        rect->top     = 0;
        rect->right   = ODIntToFixed(100);
        rect->bottom  = ODIntToFixed(100);
#elif defined(_PLATFORM_OS2_)
        rect->left    = 0;
        rect->top     = ODIntToFixed(100);
        rect->right   = ODIntToFixed(100);
        rect->bottom  = 0;
#endif

//        newShape->NewShape(ev);
        newShape->SetRectangle(ev, rect);

        delete rect;

        // create the new frame using this shape
        newFrame = _fPartSU->GetDraft(ev)->CreateFrame(ev,
                                        kODFrameObject,     // frameType
                                        containingFrame,    // containingFrame
                                        newShape,           // frameShape
                                        (ODCanvas*)kODNULL, // biasCanvas
                                        embedPart,         // part
                                        _fFrameView,        // viewType
                                        _fSession->Tokenize(ev, kODPresDefault),
                                        kODFalse,           // isRoot
                                        kODFalse);          // isOverlaid

        // add new frame to the container's list of Embedded Frames
        ContentFrame *contFrame = new ContentFrame();
        contFrame->_set_myFrame(ev, newFrame);
        _fEmbeddedObjects->AddLast(ev, contFrame);

        // get the clip shape of the newly created frame
        // (the part may have changed it from the default 100x100 shape)
        TempODShape clipShape = newFrame->AcquireFrameShape(ev, kODNULL);

        // create an embedded facet for the embedded frame
        ODFacet *containingFacet = FirstFacet(ev, containingFrame);
        ODFacet* embeddedFacet = containingFacet->CreateEmbeddedFacet(ev,
                              newFrame,          // frame
                              clipShape,         // clipShape
                              newEmbedTransform, // externalTransform
                              kODNULL,           // canvas
                              kODNULL,           // biasCanvas
                              kODNULL,           // siblingFacet
                              kODFrameInFront);  // position

        embeddedFacet->Invalidate(ev, newShape, kODNULL);

    }  // end of try block
    catch (...) {}


    return newFrame;
}



//--------------------------------------------------------------------------
// ODPart --> RequestFrameShape
//
//      Should negotiate a new frame shape for the specified frame
//      embedded part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODShape*
SOMLINK         BaseContainerRequestFrameShape
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *embeddedFrame, // in
                ODShape         *frameShape     // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerRequestFrameShape");

    try {

       // look for bad parameters
       if (embeddedFrame == kODNULL)
          return frameShape;

       if (frameShape == kODNULL)
       {
          // we use ODShape so that we increment the shape ref count
          ODShape *shape = embeddedFrame->AcquireFrameShape (ev, kODNULL);
          return shape;
       }

       // Store old embedded frame shape for future invalidation
       TempODShape currentShape = embeddedFrame->AcquireFrameShape (ev, kODNULL);
       TempODShape invalidShape = currentShape->Copy(ev);

       // Convert invalidShape from embedded frame coordinates to container's content coordinates.
       TempODTransform extXform = FirstFacet(ev, embeddedFrame)->AcquireExternalTransform(ev, kODNULL);
       invalidShape->Transform(ev, extXform);

       // tell the embed what the new shape is
       TempODShape tShape = frameShape->Copy (ev);
       embeddedFrame->ChangeFrameShape(ev, tShape, kODNULL);

       ODFrameFacetIterator* i = embeddedFrame->CreateFacetIterator(ev);
       ODFacet* facet = kODNULL;
       ODFacet* firstFacet;

       for (firstFacet = facet = i->First(ev); i->IsNotComplete(ev); facet = i->Next(ev))
       {
          // Update the clipshape of each embedded facet
          TempODShape newFrameShape = frameShape->Copy (ev);
          facet->ChangeGeometry(ev, newFrameShape, kODNULL, kODNULL);
       }

       delete i;

       // Acquire the shape so that it will be released by the caller
       frameShape->Acquire(ev);

       // If the frame is selected...
       if( firstFacet && (firstFacet->IsSelected(ev) == kODTrue) )
       {
          // Account for selection border of old shape
          invalidShape->Outset(ev, kODBorderWidth);

          // Recalculate selection border
          somSelf->CreateSelectionBorderShapes (ev, kODNULL);

          // Include new selection border in invalid shape
          TempODShape newSelectShape = _fSelectShape->Copy(ev);
          invalidShape->Union(ev, newSelectShape);
       }

       TempODFrame myFrame = embeddedFrame->AcquireContainingFrame (ev);
       i = myFrame->CreateFacetIterator(ev);
       ODFacet* myFacet = i->First(ev);
       delete i;

       // Transform invalidShape from content coordinates to frame coordinates
       TempODTransform intXForm = myFrame->AcquireInternalTransform(ev, kODNULL);
       invalidShape->Transform(ev, intXForm);

       // Invalidate this part's facet
       myFacet->Invalidate(ev, invalidShape, kODNULL);

       // call change notification
       somSelf->ChangeNotification (ev, BCC_EMBEDSHAPECHANGED, myFrame,
                                    GetContentObjectForFrame(embeddedFrame, _fEmbeddedObjects),
                                    kODTrue, kODNULL);

    }  // end of try block
    catch (...) {}


    return frameShape;
}

//--------------------------------------------------------------------------
// ODPart --> CreateEmbeddedFramesIterator
//
//      Should create an embedded frames iterator to give callers
//      access to all embedded frames of this part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODEmbeddedFramesIterator*
SOMLINK         BaseContainerCreateEmbeddedFramesIterator
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerCreateEmbeddedFramesIterator");


    // Create the Iterator object
    BCIterator *embeddedFramesIterator = new BCIterator;

    try {

    // we then initialize it
    embeddedFramesIterator->InitEmbeddedFramesIterator(ev,_fPartWrapper);

    }  // end of try block
    catch (...) {}

    // lastly, return it to the caller
    return embeddedFramesIterator;
}



//--------------------------------------------------------------------------
// ODPart --> RemoveEmbeddedFrame
//
//      Should remove the specified embedded frame from this part's
//      content.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerRemoveEmbeddedFrame
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *embeddedFrame  // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerRemoveEmbeddedFrame");

   ALink *itr;
   ContentFrame *theObj;
   for(itr = _fEmbeddedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev)) {
       ContentFrame *cobj = (ContentFrame *) itr->Content(ev);
       if ((cobj->_get_objType(ev) == COBJ_FRAMECLASS) && (cobj->_get_myFrame(ev) == embeddedFrame)) {
          theObj = cobj;
          break;
       }
   }
   _fEmbeddedObjects->Remove(ev, theObj);

}


//--------------------------------------------------------------------------
// BaseContainer --> GetDisplayFrames
//
//      Get the DisplayFrames list value for ODEmbeddedFramesIterator
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ALinkedList *
SOMLINK         BaseContainerGetDisplayFrames
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGetDisplayFrames");

    return _fDisplayFrames;

}


//--------------------------------------------------------------------------
// BaseContainer --> GetEmbeddedObjects
//
//      Get the EmbeddedObjects list value for ODEmbeddedFramesIterator
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ALinkedList *
SOMLINK         BaseContainerGetEmbeddedObjects
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGetEmbeddedObjects");

    return _fEmbeddedObjects;

}


//--------------------------------------------------------------------------
// BaseContainer --> GetSelectedObjects
//
//      Get the SelectedObjects list value
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ALinkedList *
SOMLINK         BaseContainerGetSelectedObjects
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGetSelectedObjects");

    return _fSelectedObjects;

}


//--------------------------------------------------------------------------
// BaseContainer --> GetMenuBar
//
//--------------------------------------------------------------------------

SOM_Scope       ODMenuBar *
SOMLINK         BaseContainerGetMenuBar
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGetMenuBar");

    return _fMenuBar;

}

//--------------------------------------------------------------------------
// BaseContainer --> GetBackgroundColor
//
//--------------------------------------------------------------------------

SOM_Scope       COLORREF
SOMLINK         BaseContainerGetBackgroundColor
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGetBackgroundColor");

    return _fBackgroundColor;

}


//--------------------------------------------------------------------------
// BaseContainer --> SetBackgroundColor
//
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerSetBackgroundColor
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                COLORREF        color           // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerSetBackgroundColor");

    _fBackgroundColor = color;

#ifdef _PLATFORM_UNIX_
// In X, an expose event will cause a redraw of any widgets.  Normally in
// Opendoc, setting an invalidate will do the same (by calling DrawContents),
// but in BaseContainer, our DrawContents only draws if it is off screen.
// Therefore, if the background color has changed, we need to reset the
// background color resource of our frames & facets.  This will avoid X
// defaulting to the desktop's background color instead of the new color.

       ALink *itr = kODNULL;
       for (itr = _fDisplayFrames->First (ev); itr->Content(ev); itr = itr->Next(ev))
         {
             // Loop through all the frame's facets and if they have
             // widgets, set the widgets' background colors.
             ODFrameFacetIterator* i = ((ODFrame *) itr->Content(ev))->CreateFacetIterator(ev);
             ODFacet* facet = kODNULL;

             for (facet = i->First(ev);
                  i->IsNotComplete(ev);
                  facet = i->Next(ev))
             {
                 // If the facet has a widget.  It won't if the facet
                 // is non-dynamic or is offscreen
                 Widget widget = facet->GetFacetWidget(ev);
                 if (widget)
                 {
                     XtVaSetValues(widget,
                                   XmNbackground, _fBackgroundColor,
                                   NULL);
                 }
             }

             delete i;
         } // end for
#endif



}


// ** Group 3
// -------------------------------------------------------------------------
// ODPart --> Draw
//
//      Should draw this part within the area that needs updating in the
//      specified facet.
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDraw
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet,         // in
                ODShape         *invalidShape   // in
                )
{
   BaseContainerData *somThis = BaseContainerGetData(somSelf);
   BaseContainerMethodDebug("BaseContainer","BaseContainerDraw");


   try {

      ODTypeToken viewType = facet->GetFrame(ev)->GetViewType(ev);

      if(viewType == _fSmallIconView)
      {
         somSelf->DrawIcon(ev, facet, invalidShape, _fSmallIconView);
      }
      else if(viewType == _fLargeIconView)
      {
         somSelf->DrawIcon(ev, facet, invalidShape, _fLargeIconView);
      }
      else if(viewType == _fThumbnailView)
      {
         somSelf->DrawThumbnail(ev, facet, invalidShape);
      }
      else
      {
         somSelf->DrawFrame(ev, facet, invalidShape);
      }

   }  // end of try block
   catch (...) {}


}


// -------------------------------------------------------------------------
// BaseContainerPart --> DrawContents
//
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerDrawContents
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet,          // in
                ODShape         *invalidShape
                )
{

    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDrawContents");

    ODFrame* displayFrame = facet->GetFrame(ev);
    ODCanvas *canvas = facet->GetCanvas(ev);
    TempODShape shape = ODCopyAndRelease(ev,
       displayFrame->AcquireFrameShape(ev, canvas));

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
/* Make sure we are drawing the portion of our content that is currently     */
/* scrolled into view (AcquireFrameShape returns shape in frame coordinates; */
/* we have to transform that into our content coordinates).                  */
    if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
       TempODTransform internalXform = displayFrame->AcquireInternalTransform(ev,
          canvas);
       shape->InverseTransform(ev, internalXform);
    } /* endif */
#endif //defined OS2 || WIN32

    ODRect rect;
    shape->GetBoundingBox(ev, &rect);
    Rect frameRect;

    // Convert to Window's rectangle
#if defined(_PLATFORM_OS2_)
      frameRect.xLeft = FixedToInt(rect.left);
      frameRect.yTop  = FixedToInt(rect.top);
      frameRect.xRight  = FixedToInt(rect.right);
      frameRect.yBottom  = FixedToInt(rect.bottom);

      HPS hdc;
      CFocus focus(facet, invalidShape, &hdc);

     // Clip the facet. This will prevent any children from drawing outside of the
     // facet. This is a problem when we have overlapping parts and native
     // controls as children of the facet
     ODRgnHandle clipRegion = facet->CopyFacetClipRegion(ev,hdc);
     WinSetClipRegion(facet->GetFacetHWND(ev), clipRegion);

      GpiCreateLogColorTable (hdc, 0L, LCOLF_RGB, 0L, 0L, 0L);
      GpiSetColor(hdc, _fBackgroundColor);
      POINTL orig = {0, 0};
      GpiMove(hdc, &orig);
      POINTL ptl = {frameRect.xRight, frameRect.yTop};
      GpiBox(hdc, DRO_FILL, &ptl, 0, 0);

#elif defined(_PLATFORM_UNIX_)
// BaseContainer really only draws it's background color in it's draw method.
// In AIX, this is really just a no-op, since X draws it's own background
// color on its widgets when an expose event occurs.  So rather than calling a
// draw method that isn't necessary we've wrapped it in a check for whether it
// is offscreen or not.  In that case, X doesn't draw automatically and this
// background draw is needed.
// - See comments in SetBackgroundColor method and FacetAdded methods

    // If the canvas is not dynamic or is offscreen.
    // We don't need to draw otherwise as the facet will have a
    // widget and the widget will take care of filling its background
 if ((!canvas->IsDynamic(ev)) || (canvas->IsOffscreen(ev)))
   {

    XRectangle rgnBox;

    // Get the AIX Window canvas information
    ODAIXWindowCanvas *aixwincanvas = (ODAIXWindowCanvas *)
                      (canvas->GetPlatformCanvas(ev, kODAIX));
    Window window = aixwincanvas->GetWindow(ev);

    // Get the canvas graphic context
    GC gc;
    CFocus focus(facet, invalidShape, &gc);

    XSetForeground(_fDisplay, gc, _fBackgroundColor);

    Region shapeRgn;

    TempODTransform xform = facet->AcquireContentTransform(ev, canvas);
    TempODShape tempShape = shape->Copy(ev);
    tempShape->Transform(ev, xform);
    shapeRgn = tempShape->GetRegion(ev);

    XSetRegion(_fDisplay, gc, shapeRgn);

    XClipBox(shapeRgn, &rgnBox);

    XFillRectangle(_fDisplay, window, gc, rgnBox.x, rgnBox.y, rgnBox.width, rgnBox.height);

   }
#elif defined(_PLATFORM_WIN32_)
       SetRect(&frameRect, FixedToInt(rect.left),
                       FixedToInt(rect.top),
                       FixedToInt(rect.right),
                       FixedToInt(rect.bottom));

      HDC hdc;
      CFocus focus(facet, invalidShape, &hdc);

       // Create a solid brush
       HBRUSH hbr = CreateSolidBrush (_fBackgroundColor);

       // Fill the rectangle with the brush
       FillRect (hdc, &frameRect, hbr);

       // Get rid of the brush
       DeleteObject (hbr);

#ifdef ODDebug
       // Set up a font for the text - ensure it doesn't get too small
       LOGFONT labelFont;
       memset(&labelFont, 0, sizeof(labelFont));
       labelFont.lfPitchAndFamily = FF_SCRIPT;
       labelFont.lfItalic = 1;
       labelFont.lfHeight = (frameRect.bottom - frameRect.top) / 12;
       if (labelFont.lfHeight < 16)
       {
           labelFont.lfHeight = 16;
       }
       labelFont.lfQuality = PROOF_QUALITY;
       lstrcpy((LPSTR)labelFont.lfFaceName, (LPSTR)"Cursive");

       // Create the font and select it
       HFONT hFont = CreateFontIndirect(&labelFont);
       HFONT hOldFont;
       hOldFont = SelectObject(hdc, hFont);

       // Write some text on the screen using a transparent background and
       // white text
       SetBkMode(hdc, TRANSPARENT);
       SetTextColor(hdc, 0x00FFFFFF);
       char *text = "Base Container part";
       /* DrawText(hdc,
                text,
                strlen(text),
                &frameRect,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE);
       */
       // Remove the temporary font
       SelectObject(hdc, hOldFont);
       DeleteObject(hFont);
#endif

#endif  // end WIN32 specific

       return kODTrue;
}


// -------------------------------------------------------------------------
// ODPart --> GetPrintResolution
//
// -------------------------------------------------------------------------

SOM_Scope       ODULong
SOMLINK         BaseContainerGetPrintResolution
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGetPrintResolution");

    return kODNULL;
}

//--------------------------------------------------------------------------
// ODPart --> AdjustBorderShape
//
//      Should adjust the shape of an embedded frame's active frame
//      border.
//
//      ->
//--------------------------------------------------------------------------
SOM_Scope       ODShape*
SOMLINK         BaseContainerAdjustBorderShape
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *embeddedFacet, // in
                ODShape         *shape          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerAdjustBorderShape");



    try {

    // we increment the ref count so that the shape doesn't go away too soon
    // fix from JRB
    if (shape)
       shape->Acquire(ev);

    }  // end of try block
    catch (...) {}

    return shape;
}


//--------------------------------------------------------------------------
// BaseContainer --> CreateSelectionBorderShapes
//
//      Creates border shapes and adds them to the instance variables
//      fSelectShape, fCornerHandleShape, fEdgeHandleShape
//      If ODFrame is passed in, then shapes are computed for that
//      particular frame and are added to the existing ones.
//      if frame == kODNULL then shapaes are computed for all the
//      frames in the list of selected frames.
//
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerCreateSelectionBorderShapes
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ContentObject   *contentObject    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCreateSelectionBorderShapes");


    try {

    ODFrame *myFrame = (ODFrame*)(_fDisplayFrames->First(ev)->Content(ev));

    if (contentObject) {

       // Create and add border
       TempODShape sShape = myFrame->CreateShape(ev);
       TempODShape cShape = myFrame->CreateShape(ev);
       TempODShape eShape = myFrame->CreateShape(ev);

       // Get the facet and transform
       ODRect rect = contentObject->_get_boundingRect (ev);

       somSelf->GetBorderShapes (ev, &rect, sShape, cShape, eShape);

       // Add these shapes to the existing ones
       _fSelectShape->Union (ev, sShape);
       _fCornerHandleShape->Union (ev, cShape);
       _fEdgeHandleShape->Union (ev, eShape);
    }

    else {

       // Need to create shapes for all the objects in selected list

       _fSelectShape->Reset (ev);
       _fCornerHandleShape->Reset (ev);
       _fEdgeHandleShape->Reset (ev);

       for(ALink *link=_fSelectedObjects->First(ev); link->Content(ev); link=link->Next(ev))
       {
            ContentObject *cObj = (ContentObject *)link->Content(ev);

            TempODShape sShape = myFrame->CreateShape(ev);
            TempODShape cShape = myFrame->CreateShape(ev);
            TempODShape eShape = myFrame->CreateShape(ev);

            // Get the rect
            ODRect rect = cObj->_get_boundingRect (ev);

            somSelf->GetBorderShapes (ev, &rect, sShape, cShape, eShape);

            // Add these shapes to the existing ones
            _fSelectShape->Union (ev, sShape);
            _fCornerHandleShape->Union (ev, cShape);
            _fEdgeHandleShape->Union (ev, eShape);
       }

    }
    } // end try block
    catch (...) {}

    return kODTrue;
}


//--------------------------------------------------------------------------
// BaseContainer --> GetBorderShapes
//
//      Creates border shapes.
//
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerGetBorderShapes
                (
                BaseContainer   *somSelf,        // in
                Environment     *ev,            // in
                ODRect          *rect,
                ODShape         *selectShape,    // in
                ODShape         *cornerShape,    // in
                ODShape         *edgeShape
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGetBorderShapes");


    try {

    ODRect bbox = *rect, bboxSave;

    ODShape *tempShape = new ODShape();
    tempShape->InitShape(ev);
    tempShape->Acquire (ev);
    tempShape->SetRectangle(ev, &bbox);

    InflateRect(&bbox, kODBorderWidth, kODBorderWidth);
    bboxSave = bbox;
    selectShape->SetRectangle(ev, &bbox);
    selectShape->Subtract(ev, tempShape);

    // -- corner region --

    cornerShape->CopyFrom(ev, selectShape);
    InflateRect(&bbox, -kODHandleLenMultiplier *kODBorderWidth, 0);
    tempShape->SetRectangle(ev, &bbox);
    cornerShape->Subtract(ev, tempShape);
    bbox = bboxSave;
    InflateRect(&bbox, 0, -kODHandleLenMultiplier *kODBorderWidth);
    tempShape->SetRectangle(ev, &bbox);
    cornerShape->Subtract(ev, tempShape);

    // -- edge region --

    ODRect arect[4];
    bbox = bboxSave;

    arect[0] = arect[1] = arect[2] = arect[3] = bbox;
    arect[0].right -= (bbox.right-bbox.left)/2;
    arect[0].top -= (bbox.top-bbox.bottom)/2;
    arect[1].left = arect[0].right+0x10000;
    arect[1].top = arect[0].top;
    arect[2].left = arect[0].right+0x10000;
    arect[2].bottom = arect[0].top+0x10000;
    arect[3].right = arect[0].right;
    arect[3].bottom = arect[0].top+0x10000;

    if ((bbox.right-bbox.left) >= (5*kODHandleLenMultiplier *kODBorderWidth))
    {
        /* top and bottom handles  */
        long hdist = (kODHandleLenMultiplier *kODBorderWidth)/2;

        arect[0].right -= hdist;
        arect[1].left += hdist;
        arect[2].left = arect[1].left;
        arect[3].right = arect[0].right;
    }

#if (defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_))
    if ((bbox.bottom-bbox.top) >= (5*kODHandleLenMultiplier *kODBorderWidth))
#elif defined(_PLATFORM_OS2_)
    if ((bbox.top-bbox.bottom) >= (5*kODHandleLenMultiplier *kODBorderWidth))
#endif
    {
        /* left and right handles */
        long vdist = (kODHandleLenMultiplier *kODBorderWidth)/2;

#if (defined(_PLATFORM_WIN32_) || defined(_PLATFORM_UNIX_))
        arect[0].top += vdist;
        arect[2].bottom -= vdist;
#elif defined(_PLATFORM_OS2_)
        arect[0].top -= vdist;
        arect[2].bottom += vdist;
#endif
        arect[1].top = arect[0].top;
        arect[3].bottom = arect[2].bottom;
    }

    edgeShape->CopyFrom(ev, selectShape);

    for (int i = 0; i < 4; i++)
    {
        tempShape->SetRectangle(ev, &arect[i]);
        edgeShape->Subtract(ev, tempShape);
    }

    ODReleaseObject (ev, tempShape);

    }  // end of try block
    catch (...) {}

    return kODTrue;

}

//--------------------------------------------------------------------------
// BaseContainer --> DrawSelectionBorder
//
//      Draw border shapes.
//
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerDrawSelectionBorder
                (
                BaseContainer   *somSelf,        // in
                Environment     *ev,             // in
                ODFacet         *facet,
                ODShape         *invalidShape
               )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDrawSelectionBorder");


    try {

    if (_fSelectedObjects->Count(ev) == 0)
       return kODTrue;

#if defined(_PLATFORM_OS2_)

    ODBoolean bPrinting = facet->GetCanvas(ev)->HasPlatformPrintJob(ev, kODPM);
    if (bPrinting)
       return kODTrue;

    HPS hDC;
    CFocus focus(facet, invalidShape, &hDC);


    HRGN shapeRgn = GpiCreateRegion(hDC, 0, NULL);
    Rect rect;
    SIZEL sizlThickness = {1,1} ;

    GpiSavePS(hDC);
    GpiSetColor(hDC, CLR_DARKGRAY);
    TempODTransform xform = facet->AcquireContentTransform(ev, kODNULL);
    TempODShape tempShape = _fSelectShape->Copy(ev);
    tempShape->Transform(ev, xform);
    shapeRgn = tempShape->GetRegion(ev);
    GpiPaintRegion(hDC, shapeRgn);

    GpiSetColor(hDC, CLR_BLACK);

  tempShape->CopyFrom(ev, _fCornerHandleShape);
  tempShape->Union (ev, _fEdgeHandleShape);
  tempShape->Transform(ev, xform);
  shapeRgn = tempShape->GetRegion(ev);
  GpiPaintRegion(hDC, shapeRgn);
  GpiSetColor(hDC, CLR_DARKGRAY);
  GpiFrameRegion(hDC, shapeRgn, &sizlThickness);


//  GpiDestroyRegion(hDC, shapeRgn);
  GpiRestorePS(hDC, -1);


#elif defined(_PLATFORM_WIN32_)

    ODBoolean bPrinting = facet->GetCanvas(ev)->HasPlatformPrintJob(ev, kODWin32);
    if (bPrinting)
       return kODTrue;

    HDC hDC;
    CFocus focus(facet, invalidShape, &hDC);

    //Select Shape

    ODRgnHandle borderRgn  = _fSelectShape->GetRegion(ev);
    HBRUSH  hairBrush = CreateSolidBrush(RGB(192, 192, 192));
    HBRUSH  hbrOld = SelectObject(hDC, hairBrush);

    FillRgn(hDC, borderRgn, hairBrush);
    SelectObject(hDC, hbrOld);
    DeleteObject(hairBrush);

    //Corner Shape

    borderRgn  = _fCornerHandleShape->GetRegion(ev);
    hairBrush = CreateSolidBrush(RGB(36, 36, 36));
    hbrOld = SelectObject(hDC, hairBrush);

    FillRgn(hDC, borderRgn, hairBrush);
    SelectObject(hDC, hbrOld);
    DeleteObject(hairBrush);

    //Edge Shape

    borderRgn  = _fEdgeHandleShape->GetRegion(ev);
    hairBrush = CreateSolidBrush(RGB(0, 0, 0));
    hbrOld = SelectObject(hDC, hairBrush);

    FillRgn(hDC, borderRgn, hairBrush);
    SelectObject(hDC, hbrOld);
    DeleteObject(hairBrush);

#elif defined(_PLATFORM_UNIX_)

    ODBoolean bPrinting = facet->GetCanvas(ev)->HasPlatformPrintJob(ev, kODAIX);
    if (bPrinting)
       return kODTrue;

    unsigned int height, width;
    int x, y;
    XRectangle rgnBox;

    // Set grey and black colors for using in border
    Screen *screen = _fSession->GetWindowState(ev)->GetScreen(ev);
    Colormap cmap = XDefaultColormapOfScreen(screen);
    XColor clrcell, rgbdef;

    XAllocNamedColor(_fDisplay, cmap, "black", &clrcell, &rgbdef);
    unsigned long black = clrcell.pixel;
    XAllocNamedColor(_fDisplay, cmap, "grey", &clrcell, &rgbdef);
    unsigned long grey = clrcell.pixel;


    // Get the AIX Window canvas information
    ODAIXWindowCanvas *aixwincanvas = (ODAIXWindowCanvas *)
                      (facet->GetCanvas(ev)->GetPlatformCanvas(ev, kODAIX));
    Widget widget = aixwincanvas->GetWidget(ev);
    Window window = aixwincanvas->GetWindow(ev);

    GC gc;
    CFocus focus(facet, invalidShape, &gc);

    Region shapeRgn;

    TempODTransform xform = facet->AcquireContentTransform(ev, kODNULL);
    TempODShape tempShape = _fSelectShape->Copy(ev);
    tempShape->Transform(ev, xform);
    shapeRgn = tempShape->GetRegion(ev);
    XSetRegion(_fDisplay, gc, shapeRgn);
    XClipBox(shapeRgn, &rgnBox);
    XSetForeground(_fDisplay, gc, grey);
    XFillRectangle(_fDisplay, window, gc, rgnBox.x, rgnBox.y, rgnBox.width, rgnBox.height);

    XSetForeground(_fDisplay, gc, black);

    tempShape->CopyFrom(ev, _fCornerHandleShape);
    tempShape->Union(ev, _fEdgeHandleShape);
    tempShape->Transform(ev, xform);
    shapeRgn = tempShape->GetRegion(ev);
    XSetRegion(_fDisplay, gc, shapeRgn);
    XClipBox(shapeRgn, &rgnBox);
    XFillRectangle(_fDisplay, window, gc, rgnBox.x, rgnBox.y, rgnBox.width, rgnBox.height);
    XSetForeground(_fDisplay, gc, grey);
    XDrawRectangle(_fDisplay, window, gc, rgnBox.x, rgnBox.y, rgnBox.width, rgnBox.height);

#endif
    }  // end of try block
    catch (...) {}

    return kODTrue;

}


// ** Group 4
//--------------------------------------------------------------------------
// ODPart --> FacetAdded
//
//      Should notify this part that a facet has been added to one
//      of its display frames.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerFacetAdded
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerFacetAdded");

#ifdef ODDebug
    //PRINT ("Facet added %lx   %d \n", somSelf, somSelf->GetRefCount(ev));
#endif

    try {

    // Since we have not created canvas, no need to set its owner
    //facet->GetCanvas(ev)->SetOwner(ev,_fPartWrapper);

    ODFrame *myFrame = facet->GetFrame (ev);

    somSelf->UpdateContentExtent(ev, myFrame);

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    ODCanvas *canvas = facet->GetCanvas(ev);
    if (canvas && canvas->IsDynamic(ev)) { /* don't do when printing */
       if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
          _fScrollExt->FacetAdded(ev, facet);
       } /* endif */
    } /* endif */
#endif //defined OS2 || WIN32

    // internalize embedded stuff now (we had to wait for our facet).
    BCCloneInfo cloneInfo;
    memset (&cloneInfo, 0, sizeof(BCCloneInfo));
    cloneInfo.myFrame = myFrame;

    if (_fNeedToInternalize) {
        somSelf-> ReadContents (ev, somSelf->GetStorageUnit(ev), &cloneInfo, INTERNALIZE);
        _fNeedToInternalize = kODFalse;

    } else {

       ODFrame *dispFrame = facet->GetFrame(ev);
       ALink *itr;

       for (itr = _fEmbeddedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
       {
            ContentFrame *cObj = (ContentFrame *) itr->Content(ev);
            if ( (cObj->_get_objType(ev) == COBJ_FRAMECLASS) &&
                         (cObj->_get_containingFrame(ev) == dispFrame))
            {
               ODFrame *embeddedFrame = cObj->_get_myFrame(ev);
               ODFacet *embeddedFacet =  FirstFacet(ev, embeddedFrame);
               TempODTransform tform = kODNULL;
               if (embeddedFacet)
                  tform = embeddedFacet->AcquireExternalTransform(ev, kODNULL);
               else {
                  tform = cObj->_get_extTransform(ev);
                  tform->Acquire(ev); // we have defined tform as Temp
                  ODPoint offset;
                  tform->GetOffset(ev, &offset);
                  PRINT("printing offset %d %d \n", offset.x >> 16, offset.y >> 16);
               }

               ODTransform *xform = tform->Copy (ev);
               TempODShape shape = embeddedFrame->AcquireFrameShape (ev, kODNULL);
               ODShape *clip = shape->Copy(ev);
               facet->CreateEmbeddedFacet (ev, embeddedFrame, clip, xform,
                                     kODNULL, kODNULL, kODNULL, kODFrameInFront);

            } // if frame object

        } // end for

     } // end if
#ifdef _PLATFORM_UNIX_
// This is called on AIX only, because AIX is the only platform that will
// use the default background color (from the desktop) to draw it's background
// if we don't specify a color

    // If the facet has a widget, set the widget's background color
    Widget widget = facet->GetFacetWidget(ev);
    if (widget)
    {
        XtVaSetValues(widget,
                      XmNbackground, _fBackgroundColor,
                      NULL);
    }
#endif
    } // end try block

    catch (...) {}
}



//--------------------------------------------------------------------------
// ODPart --> FacetRemoved
//
//      Should notify this part that a facet has been removed from one
//      of its display frames.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerFacetRemoved
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet          // in
                )
{
   BaseContainerData *somThis = BaseContainerGetData(somSelf);
   BaseContainerMethodDebug("BaseContainer","BaseContainerFacetRemoved");

    try {

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    ODCanvas *canvas = facet->GetCanvas(ev);
    if (canvas && canvas->IsDynamic(ev)) { /* don't do when printing */
       if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
          _fScrollExt->FacetRemoved(ev, facet);
       } /* endif */
    } /* endif */
#endif //defined OS2 || WIN32

    ODFrame              *frame = facet->GetFrame(ev);
    ODFacet              *tempFacet;
    ODFrameFacetIterator *efitr = frame->CreateFacetIterator(ev);
    ALinkedList *children = new ALinkedList;

    ODFacetIterator* facets = facet->CreateFacetIterator(ev, kODChildrenOnly, kODFrontToBack);
    for (ODFacet* childFacet = facets->First(ev);
         facets->IsNotComplete(ev);
         childFacet = facets->Next(ev))
    {
      children->AddLast(ev, childFacet);
    }
    delete facets;

    for (ALink *link = children->First(ev);
         link->Content(ev);
         link = link->Next(ev))
    {
      childFacet = (ODFacet *) link->Content(ev);
      facet->RemoveFacet(ev, childFacet);
      delete childFacet;
    }

   ODDeleteObject(efitr);
   delete children;


    }  // end of try block
    catch (...) {}


}


//--------------------------------------------------------------------------
// ODPart --> DisplayFrameAdded
//
//      Should add the specified frame to this part's internal list of
//      display frames.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDisplayFrameAdded
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDisplayFrameAdded");

    try {

        ContentObject *contentObject;
        ALink *itr = kODNULL;

        // Add this frame to our list if it is not added

        if (!_fDisplayFrames->Contains(ev, frame)) {
             _fDisplayFrames->AddLast(ev, frame);    // add to list of frames
             frame->Acquire(ev);             // pin frame in memory
        }
#ifdef ODDebug
        else
              PRINT ("Frame already exists \n");
#endif

        // Determine the view type
        _fPrevViewType = frame->GetViewType(ev);


        if(_fPrevViewType == _fFrameView) {
           // Store the frame's bounding box for viewtype support
           TempODShape currShape = frame->AcquireFrameShape(ev, kODNULL);
           currShape->GetBoundingBox(ev, &_lastFrameRect);
        }

        // Allow the paste action
        frame->SetDroppable(ev,kODTrue);

        // If we are being embedded into another part, the presentation field
        // will be NULL, so we need to set it something meaningful.
        // The view field may also be null. If so, we prefer to be displayed
        // in a frame view.

        if ( frame->GetPresentation(ev) == kODNullTypeToken )
                frame->SetPresentation(ev, _fMainPresentation);

        if ( frame->GetViewType(ev) == kODNullTypeToken )
                frame->SetViewType(ev, _fFrameView);

        // Allocate the frame's part info.  new throws an exception if
        // unable to allocate

        FramePartInfo *pInfo = new FramePartInfo;
        pInfo->NeedsActivating = (frame->IsRoot(ev)) ? kODTrue : kODFalse;
        pInfo->BgndColor = _fBackgroundColor;

#if defined (_PLATFORM_OS2_)
        memset (&(pInfo->frameRect), 0, sizeof(ODRect));
        TempODShape fShape = frame->AcquireFrameShape(ev, kODNULL);
        if (fShape)
           fShape->GetBoundingBox (ev, &(pInfo->frameRect));
#endif
        frame->SetPartInfo(ev, (ODInfoType) pInfo);

        // Go through my list of embedded frames and set containing frame

        for (itr = _fEmbeddedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
        {
            contentObject = (ContentObject*) itr->Content(ev);
            if(!contentObject->_get_containingFrame(ev))
               contentObject->_set_containingFrame (ev, frame);
        }

    } // end try block
    catch (...) {}


}



//--------------------------------------------------------------------------
// ODPart --> DisplayFrameConnected
//
//      Should add the specified frame to this part's internal list of
//      display frames.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDisplayFrameConnected
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerDisplayFrameConnected");

    somSelf->DisplayFrameAdded (ev, frame);

}



//--------------------------------------------------------------------------
// ODPart --> DisplayFrameClosed
//
//      Should notify this part that one of its display frames has been
//      closed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDisplayFrameClosed
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDisplayFrameClosed");


    try {

        // Relinquish the entire focus set

        _fSession->GetArbitrator(ev)->RelinquishFocusSet(ev, _fFocusSet, frame);

        // Close all embedded frames
        ALink *itr;
        ALinkedList *tempList = new ALinkedList;
        for(itr = _fEmbeddedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev)) {
            ContentObject *cobj = (ContentObject *) itr->Content(ev);
            if (cobj->_get_containingFrame(ev) == frame) {
                 cobj->DeleteContents(ev, FRAME_CLOSED);
                 tempList->AddLast(ev, cobj);
            }
        }

        for(itr = tempList->First(ev); itr->Content(ev); itr=itr->Next(ev)) {
            _fEmbeddedObjects->Remove(ev, (ContentObject *) itr->Content(ev));
           delete (ContentObject *) itr->Content(ev);
        }

        //  Remove frame from frame lists and free it

        _fDisplayFrames->Remove(ev, frame);
        frame->Release(ev);         // unpin from memory
        delete tempList;

    } // end try block
    catch (...) {}


}



//--------------------------------------------------------------------------
// ODPart --> DisplayFrameRemoved
//
//      Should remove the specified frame from this part's internal
//      list of display frames.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDisplayFrameRemoved
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerDisplayFrameRemoved");


    try {

        // Relinquish the entire focus set

        _fSession->GetArbitrator(ev)->RelinquishFocusSet(ev, _fFocusSet, frame);

        // Remove/Release embedded frames
        ALink *itr;
        ALinkedList *tempList = new ALinkedList;
        for(itr = _fEmbeddedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev)) {
            ContentObject *cobj = (ContentObject *) itr->Content(ev);
            if (cobj->_get_containingFrame(ev) == frame) {
                 cobj->DeleteContents(ev, FRAME_REMOVED);
                 tempList->AddLast(ev, cobj);
            }
        }

        for(itr = tempList->First(ev); itr->Content(ev); itr=itr->Next(ev)) {
            _fEmbeddedObjects->Remove(ev, (ContentObject *) itr->Content(ev));
           delete (ContentObject *) itr->Content(ev);
        }

        //  Remove frame from frame lists and free it

        _fDisplayFrames->Remove(ev, frame);
        frame->Release(ev);         // unpin from memory
        delete tempList;

    } // end try block
    catch (...) {}


}



// ** Group 5
//--------------------------------------------------------------------------
// ODPart --> AbortRelinquishFocus
//
//      Should reestablish this part's ownership of the focus specified
//      in a previous call to this part's ODPart->BeginRelinquishFocus
//      method.
//
//      -> must override ODPart, must not call ODPart method
//      -> focus parameter is a string token == 32 bit kOD*Focus constant
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerAbortRelinquishFocus
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODTypeToken      focus,         // in string token of kOD*Focus
                ODFrame         *ownerFrame,    // in current focus owner
                ODFrame         *proposedFrame  // in proposed owner of focus
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerAbortRelinquishFocus");

    // Another part requested one of the foci we had, but was unable
    // to acquire all the foci it needed. So, we are being given our
    // complete set of foci back.

    somSelf->FocusAcquired(ev, focus, ownerFrame);

}



//--------------------------------------------------------------------------
// ODPart --> BeginRelinquishFocus
//
//      Should return a Boolean value that indicates whether this
//      part is willing to relinquish the requested focus and should
//      prepare to do so.
//
//      -> must override ODPart, must not call ODPart method
//      -> focus parameter is a string token == 32 bit kOD*Focus constant
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerBeginRelinquishFocus
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODTypeToken      focus,         // in string token of kOD*Focus
                ODFrame         *ownerFrame,    // in current focus owner
                ODFrame         *proposedFrame  // in requesting frame
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerBeginRelinquishFocus");


    ODBoolean rc=kODTrue;

    try {

        if ( focus == _fModalFocus ) {
            ODPart *proposedFramePart = proposedFrame->AcquirePart(ev);

            // if proposedFramePart is not this part then
            //   Another part is trying to put up a Modal dialog
            //   while we are currently displaying ours.
            //
            //   Deny the request.

            rc= (proposedFramePart==somSelf) ? kODTrue : kODFalse;

            proposedFramePart->Release(ev);
        }

    }  // end try block
    catch (...) {}

    return rc;
}



//--------------------------------------------------------------------------
// ODPart --> CommitRelinquishFocus
//
//      Should complete this part's relinquishing of the ownership
//      of the specified focus.
//
//      -> must override ODPart, must not call ODPart method
//      -> focus parameter is a string token == 32 bit kOD*Focus constant
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCommitRelinquishFocus
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODTypeToken      focus,         // in string token of kOD*Focus
                ODFrame         *ownerFrame,    // in current focus owner
                ODFrame         *proposedFrame  // in requesting frame
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerCommitRelinquishFocus");


    // We previously agreed to give up our FocusSet and
    // now we are being asked to really do so.



    try {

        somSelf->FocusLost(ev, focus, ownerFrame);

    }  // end of try block
    catch (...) {}

}



//--------------------------------------------------------------------------
// ODPart --> FocusAcquired
//
//      Should notify this part that one of its display frames has
//      acquired the specified focus.
//
//      Called by OpenDoc when containing part transfers focus to this part.
//      BaseContainer->ActivateFrame will also call this method.
//
//      Not called when this part used RequestFocus* methods to get focus.
//
//      -> must override ODPart, must not call ODPart method
//      -> focus parameter is a string token == 32 bit kOD*Focus constant
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerFocusAcquired
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODTypeToken      focus,         // in string token of kOD*Focus
                ODFrame         *ownerFrame     // in display frame that owns focus
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerFocusAcquired");


    try {


    if ( focus == _fMenuFocus ) _fMenuBar->Display(ev);

    else if ( focus == _fSelectionFocus )
    {
        ALink* itr = kODNULL;
        // Iterate over SelectedFrames and turn on selection highlight
        //for(itr = _fSelectedObjects->First(ev); itr->Content(ev); itr=itr->Next(ev))
        //  ((ContentObject *) itr->Content(ev))->SetSelectionState(kODTrue);

    } //end if

    } // end try block
    catch (...) {}



}



//--------------------------------------------------------------------------
// ODPart --> FocusLost
//
//      Should notify this part that one of its display frames has
//      lost the specified focus.
//
//      Called by OpenDoc when focus is lost to a containing part request
//      (TransferFocus) or because of some user/system event.
//
//      Not called when another part has requested focus (ie called this
//      part's BeginRelinquishFocus method (since you already know).
//
//      -> must override ODPart, must not call ODPart method
//      -> focus parameter is a string token == 32 bit kOD*Focus constant
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerFocusLost
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODTypeToken      focus,         // in string token of kOD*Focus
                ODFrame         *ownerFrame     // in frame which lost focus
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerFocusLost");



    try {

    if ( focus == _fSelectionFocus )
    {
        // Iterate over SelectedFrames and turn on selection highlight
        if (_fSelectedObjects->Count(ev) != 0)
           somSelf->DeselectAll(ev);

        // Reset the Mouse Mode if it is set. This way mouse tracking is lost once the part is deactivated.
        _usMouseMode = kMouseModeNull;
    }

    // who owns the clipboard focus
    TempODFrame clipboardOwner = _fSession->GetArbitrator(ev)->AcquireFocusOwner(ev, _fClipboardFocus);

    // we no longer need the clipboard focus
    if(ownerFrame == clipboardOwner) {
        _fSession->GetArbitrator(ev)->RelinquishFocus(ev, _fClipboardFocus, ownerFrame);
    }

    } // end try block
    catch (...) {}

}



//--------------------------------------------------------------------------
// BaseContainer --> ActivateFrame
//
//      Should request the focus set, and notify ourselves that we
//      got it.
//
//      Called when the enduser clicks within the content area of a part
//      which causes an event to be sent to the HandleEvent method.
//
//      -> private method of BaseContainer
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerActivateFrame
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in frame to activate
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerActivateFrame");


    ODBoolean rc = kODFalse;


    try {

    // Do not activate if we already are active
    TempODFrame activeFrame = _fSession->GetArbitrator(ev)->AcquireFocusOwner(ev, _fSelectionFocus);
    if (frame == activeFrame)
    {
        // Get the frame's partinfo
        FramePartInfo *pInfo = (FramePartInfo *) frame->GetPartInfo(ev);

        // If the frame doesn't need activating due to window deactivation/reactivation
        if (!pInfo->NeedsActivating)
        {
            rc = kODTrue;
        }
    }

    // If all necessary activation is complete
    if (rc == kODTrue)
    {
        // The frame is already active and doesn't need activation because of window
        // deactivation/reactivation
    }
    // Request the set of foci necessary to become active.
    else if ( somSelf->GetStorageUnit(ev)
                ->GetSession(ev)
                ->GetArbitrator(ev)
                ->RequestFocusSet(ev, _fFocusSet, frame) )
    {
        // Notify ourself that we acquired the selection, menu,
        // and keyboard foci.
        somSelf->FocusAcquired(ev, _fSelectionFocus, frame);
        somSelf->FocusAcquired(ev, _fMenuFocus, frame);
        somSelf->FocusAcquired(ev, _fKeyFocus, frame);

        // We sucessfully acquired the foci we need to be active.
        rc=kODTrue;
    }
    else
        // We were unable to acquire the foci we need to be active.
        rc=kODFalse;

    } // end try block
    catch (...) {}

    return rc;
}



//--------------------------------------------------------------------------
// BaseContainer --> ActivatingWindow
//
//      Delayed activation of frame until WM_ACTIVATE is passed to
//      ODPart->HandleEvent method.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerActivatingWindow
                (
                BaseContainer *somSelf,
                Environment *ev,
                ODFrame* frame
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerActivatingWindow");


    try {

    // Get the frame's partinfo
    FramePartInfo *pInfo = (FramePartInfo *) frame->GetPartInfo(ev);



    // If the frame needs activating
    if (pInfo->NeedsActivating)
    {
        // Activate the frame
        somSelf->ActivateFrame(ev, frame);

        // Signify the frame no longer needs activating
        pInfo->NeedsActivating = kODFalse;
    }


    } // end try block
    catch (...) {}


}


//--------------------------------------------------------------------------
// BaseContainer --> DeactivatingWindow
//
//      Delayed activation of frame until WM_ACTIVATE is passed to
//      ODPart->HandleEvent method.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDeactivatingWindow
                (
                BaseContainer *somSelf,
                Environment *ev,
                ODFrame* frame
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDeactivatingWindow");



    try {

    // Get the frame's partinfo
    FramePartInfo *pInfo = (FramePartInfo *) frame->GetPartInfo(ev);

    // Get the frame which has the selection focus
    TempODFrame tempFrame = _fSession->GetArbitrator(ev)->
                            AcquireFocusOwner(ev, _fSelectionFocus);



    // If the frame with the selection focus is this frame
    if (frame == tempFrame)
    {
        // We will need to be activated when the window gets
        // activated again
        pInfo->NeedsActivating = kODTrue;
    }
    else
    {
        // We won't need to be activated when the window gets
        // activated again
        if(pInfo!=kODNULL) pInfo->NeedsActivating = kODFalse;
    }


    } // end try block
    catch (...) {}

}


// ** Group 6
//--------------------------------------------------------------------------
// ODPart --> CreateLink
//
//      Should create a link-source object for this part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODLinkSource*
SOMLINK         BaseContainerCreateLink
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODByteArray     *data           // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCreateLink");

   return (ODLinkSource *)kODNULL;
}



//--------------------------------------------------------------------------
// ODPart --> EmbeddedFrameUpdated
//
//      Should update any of the part's link-source objects affected
//      by a change to the specified embedded frame.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerEmbeddedFrameUpdated
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,         // in
                ODUpdateID       change         // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerEmbeddedFrameChanged");


    try {

        BaseContainer_parent_ODPart_EmbeddedFrameUpdated(somSelf,ev,frame,change);

        ContentObject *cObj = (ContentObject *) GetContentObjectForFrame (frame, _fEmbeddedObjects);
        somSelf->ChangeNotification (ev, BCC_EMBEDUPDATED, kODNULL, cObj, kODFalse, change);

    }  // end of try block
    catch (...) {}
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
SOMLINK         BaseContainerLinkStatusChanged
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerLinkStatusChanged");


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
SOMLINK         BaseContainerLinkUpdated
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODLink          *updatedLink,   // in
                ODUpdateID       id             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerLinkUpdated");


}



//--------------------------------------------------------------------------
// ODPart --> RevealLink
//
//      Should show the content at the source of a link.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerRevealLink
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODLinkSource    *linkSource     // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerRevealLink");


}


// ** Group 7
// -------------------------------------------------------------------------
// ODObject --> HasExtension
//
//      Queries whether this part supports the specified extension.
//
//      -> if overridden it must call the parent method for unsupported
//         extensions.
//      -> it must return kODTrue if extension is supported else kODFalse
//         note query answers 'is it supported?' not 'is there one attached?'
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHasExtension
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODType          extensionName   // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHasExtension");

    ODBoolean ReturnValue = kODFalse;

    if (strcmp(extensionName, kODSettingsExtension)==0) {
       ReturnValue = kODTrue;
    } /* endif */

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    else if (strcmp(extensionName, kODPrintExtension)==0) {
       ReturnValue = kODTrue;
    }

    else if (strcmp(extensionName, kODScrollExtension)==0) {
       ReturnValue = kODTrue;
    }
#endif //defined OS2 || WIN32

    else {
       try {                 // if needed invoke parent if we don't have answer
          ReturnValue = BaseContainer_parent_ODPart_HasExtension(
                              somSelf, ev, extensionName);
       }
       catch(ODException _exception) {
          SetErrorCodeEv (ev, kODNoError);
       }
    }
    return ReturnValue;
}



// -------------------------------------------------------------------------
// ODObject --> AcquireExtension
//
//      Returns a reference to the specified extension object.
//
//      -> if overridden it must call the parent method for unsupported
//         extensions.
//      -> it must return a reference if extension is supported else ???
// -------------------------------------------------------------------------

SOM_Scope       ODExtension*
SOMLINK         BaseContainerAcquireExtension
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODType           extensionName  // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerAcquireExtension");

    ODExtension* ReturnValue = kODNULL;

    //-----------------------------------------------------------
    // For each extension we support we maintain a pointer to the extension
    // object if one has been created.  If the object exists, we will simply
    // increment its reference count and return the existing object.  If no
    // existing extension object is available, we will attempt to create and
    // initialize the requested extension, save a copy of the object reference,
    // and return that reference to the caller.
    //
    // Note that the reference we retain is NOT reflected in the reference count
    // of the extension.  Initialization provides a pointer to this object
    // to the Extension object, the BaseObject.  When the reference count of
    // the extension becomes zero, the extension will call the ReleaseExtension
    // method of the BaseObject (us).  That routine will clear the local reference
    // to the extension and delete the extension object.
    //-----------------------------------------------------------

    //-----------------------------------------------------------
    // Settings Extension
    //-----------------------------------------------------------
    if (strcmp(extensionName, kODSettingsExtension)==0) {
       if (_fSettingsExt!=kODNULL) {    // for existing extension, step ref count
          _fSettingsExt->Acquire(ev);
       }
       else {
          _fSettingsExt = (BCPartSettingsExt *)somSelf->CreateSettingsExtension(ev) ; //create new if needed
       }
       ReturnValue = _fSettingsExt ;
    } /* end if settings extension */

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    //-----------------------------------------------------------
    // print extension
    //-----------------------------------------------------------
    else if (strcmp(extensionName, kODPrintExtension)==0) {

       if (_fPrintExt != kODNULL) {         // have existing extension
              _fPrintExt->Acquire(ev);      // step ref count and return reference
              ReturnValue = _fPrintExt;
       }
       else {
          _fPrintExt = (ODPrintExtension *)somSelf->CreatePrintExtension(ev);  // create ext if needed
          if (_fPrintExt) {                   //  then initialize it.
             somSelf->EnablePrinting(ev, kODTrue, kODNULL) ;
             ReturnValue = _fPrintExt ;
          }
       }
    }
    //-----------------------------------------------------------
    // Scroll Extension
    //-----------------------------------------------------------
    else if (strcmp(extensionName, kODScrollExtension)==0) {

       if (_fScrollExt != kODNULL) {        // have existing exten.
          _fScrollExt->Acquire(ev);         // step ref count and return ref
          ReturnValue = _fScrollExt;
       }

       else {
          _fScrollExt = (ODScrollExtension *)somSelf->CreateScrollExtension(ev) ;  // create new ext
          if (_fScrollExt) {                    //  then intialize it.
             PRINT("BaseContainer::AcquireExtension somself=0x%x\n",somSelf);
             somSelf->EnableScrolling(ev, kODFalse, 0, 0);
             ReturnValue = _fScrollExt;
          }
       }
    }
#endif  //OS/2 or Win95/NT

    //-----------------------------------------------------------
    // AcquireExtension throws a kODErrUnsupportedExtension if the
    // specified extension is not supported by the parent object.
    // We catch the exception and just return a null pointer.
    //-----------------------------------------------------------
    else {
       try {
          ReturnValue=BaseContainer_parent_ODPart_AcquireExtension(
          somSelf, ev, extensionName);
       }
       catch(ODException _exception) {
       }
    }

    return ReturnValue;
}



// -------------------------------------------------------------------------
// ODObject --> ReleaseExtension
//
//      -> if overridden it must call the parent method for unsupported
//         extensions.
// Note this routine is invoked from the extension class when the reference
// count of the extension object reaches zero (if the base object is not null).
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerReleaseExtension
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODExtension     *extension      // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerReleaseExtension");

//    PRINT("Entering BaseContainer::ReleaseExtension\n");

    if (extension != kODNULL) {

       if (extension == _fSettingsExt) {  // clear Settings Extension
          delete _fSettingsExt ;
          _fSettingsExt = kODNULL ;
       }

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
       else if (extension == _fPrintExt) {    // clear Print Extension
          delete _fPrintExt;
          _fPrintExt = kODNULL;
       }  /* endif */

       else if (extension == _fScrollExt) {   // clear Scroll Extension
          delete _fScrollExt;
          _fScrollExt = kODNULL;
       }  /* endif */
#endif //  OS/2 or Win95/NT

       else {                            // let parent check
          // the following code is currently removed.  It should be correct
          // but the code in ODPart::ReleaseExtension which tries to raise an
          // exception for some reason does not succeed and the exception is not
          // raised/caught.  The code in the .xh file that normally detects the
          // exception is not even involved in the call, but the ev block gets
          // set to a non-zero value hence, on return from this call the exception
          // is caught! Wrong timing.
          //try {
          //   BaseContainer_parent_ODPart_ReleaseExtension(
          //           somSelf, ev, extension);
          //}
          //catch(ODException _exception) {
          //}
       }

    } /* endif  extension not null */
}


// ** Group 8
//--------------------------------------------------------------------------
// ODPart --> RedoAction
//
//      Should redo the specified action.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerRedoAction
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODActionData    *actionState    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerRedoAction");



}


//--------------------------------------------------------------------------
// ODPart --> UndoAction
//
//      Should undo the specified action.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerUndoAction
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODActionData    *actionState    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerUndoAction");



}



//--------------------------------------------------------------------------
// ODPart --> DisposeActionState
//
//      Should dispose of the undo action data.
//
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerDisposeActionState
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODActionData    *actionState,   // in
                ODDoneState      doneState      // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDisposeActionState");

}



//--------------------------------------------------------------------------
// ODPart --> ReadActionState
//
//      Should read the undo action data from the specified storage-unit
//      view object.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODActionData
SOMLINK         BaseContainerReadActionState
                (
                BaseContainer       *somSelf,       // in
                Environment         *ev,            // in
                ODStorageUnitView   *storUnitView   // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerReadActionState");

    return CreateByteArrayStruct(kODNULL, sizeof(kODNULL));
}



//--------------------------------------------------------------------------
// ODPart --> WriteActionState
//
//      Should write the undo action data into the specified storage-unit
//      view object.
//
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerWriteActionState
                (
                BaseContainer       *somSelf,       // in
                Environment         *ev,            // in
                ODActionData        *actionState,   // in
                ODStorageUnitView   *storUnitView   // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerWriteActionState");


}


// ** Group 9
//--------------------------------------------------------------------------
// ODPart --> EmbeddedFrameSpec
//
//      Should create an object specifier for the specified embedded frame
//      in this part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerEmbeddedFrameSpec
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *embeddedFrame, // in
                ODObjectSpec    *spec           // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerEmbeddedFrameSpec");

}



//--------------------------------------------------------------------------
// ODPart --> RevealFrame
//
//      Should make the specified embedded frame visible by scrolling
//      it into view.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerRevealFrame
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *embeddedFrame, // in
                ODShape         *revealShape    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerRevealFrame");


   return kODFalse;
}



//--------------------------------------------------------------------------
// ODPart --> UsedShapeChanged
//
//      Should notify this part that the used frame of one of its
//      embedded frames has changed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerUsedShapeChanged
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *embeddedFrame  // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerUsedShapeChanged");
/*
    TempODShape newFrameShape = embeddedFrame->AcquireUsedShape (ev, kODNULL);

    if(newFrameShape)
    {
      ODFrameFacetIterator* i = embeddedFrame->CreateFacetIterator(ev);

      ODFacet* facet = kODNULL;
      for (facet = i->First(ev); i->IsNotComplete(ev); facet = i->Next(ev))
         facet->ChangeGeometry(ev, newFrameShape, kODNULL, kODNULL);
      delete i;
    }
*/
}


//--------------------------------------------------------------------------
// ODPart --> GeometryChanged
//
//      Should notify this part that the clip shape or external
//      transform (or both) of one of this part's facets has changed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerGeometryChanged
                (
                BaseContainer   *somSelf,             // in
                Environment     *ev,                  // in
                ODFacet         *facet,               // in
                ODBoolean        clipShapeChanged,    // in
                ODBoolean        extTransformChanged  // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGeometryChanged");

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    ODCanvas *canvas = facet->GetCanvas(ev);
    if (canvas && canvas->IsDynamic(ev)) { /* don't do when printing */
       if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
          _fScrollExt->GeometryChanged(ev, facet, clipShapeChanged,
             extTransformChanged);
       } /* endif */
    } /* endif */
#endif //defined OS2 || WIN32
}



//--------------------------------------------------------------------------
// ODPart --> AttachSourceFrame
//
//      Should associate a source frame with a display frame for this part.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerAttachSourceFrame
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,         // in
                ODFrame         *sourceFrame    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerAttachSourceFrame");

    if (_fDisplayFrames->Contains (ev, frame) &&
        sourceFrame &&
        _fDisplayFrames->Contains (ev, sourceFrame))
    {
#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
// Cause printouts to have parts scrolled to same position as they are onscreen
// Note we only do this for embedded parts - if you're the root part, and you
// support scrolling, and you want to support printing, you will need to take
// care of preparing the root printing frame yourself (based on your total
// content shape), rather than relying on the ODPrintExtension to take care of
// everything for you.  See the Page Layout sample part's override of the
// ODPrintExtension (in iodpgprn.cpp) for further details.
       if ((_fScrollExt!=kODNULL) && _fScrollingEnabled && !frame->IsRoot(ev)) {
          TempODTransform sourceXform = sourceFrame->AcquireInternalTransform(ev, kODNULL);
          ODTransform *newXform = sourceXform->Copy(ev);
          frame->ChangeInternalTransform(ev, newXform, kNoBias);
       } /* endif */
#endif //defined OS2 || WIN32

       ODULong count = _fEmbeddedObjects->Count(ev);
       ALink *itr = _fEmbeddedObjects->First(ev);

       for (int i = 0; i < count; i++)
       {
          ContentObject *cObj = (ContentObject *)itr->Content (ev);

          if (cObj->_get_containingFrame(ev) == sourceFrame) {
             ContentObject *newObj = cObj->CreateNewView (ev, frame);
             _fEmbeddedObjects->AddLast(ev, newObj);
          }
          itr = itr->Next(ev);

       } // end for

    }  // end if


}


//--------------------------------------------------------------------------
// ODPart --> PresentationChanged
//
//      Should notify this part that the presentation of one of its
//      display frames has changed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerPresentationChanged
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer", "BaseContainerPresentationChanged");

}



//--------------------------------------------------------------------------
// ODPart --> ViewTypeChanged
//
//      Should notify this part that the view type  of one of its
//      display frames has changed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerViewTypeChanged
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerViewTypeChanged");

    try
    {

      if(frame->IsRoot(ev))
      {
         // When this is a root part, only support frame view.
         frame->SetViewType(ev, _fSession->Tokenize(ev,kODViewAsFrame));
      }
      else
      {
#ifdef _PLATFORM_AIX_
        ODTypeToken viewType = frame->GetViewType(ev);

        // Destroy the iconWidget if changing to a frame view.
        if(viewType == _fSession->Tokenize(ev, kODViewAsFrame)) {
           if(_iconWidget != NULL) {
              XtUnmanageChild(_iconWidget);
              XtDestroyWidget(_iconWidget);
              _iconWidget = NULL;
           }
        }
#endif

        // Set frame shape according to view type
        somSelf->AdjustViewTypeShapes(ev, frame);

        // Get the new frame shape to be invalidated.
        TempODShape newShape = frame->AcquireFrameShape(ev,kODNULL);

        // Force the display of our new view type
        frame->Invalidate(ev, newShape, kODNULL);
      }
    }
    catch(...)
    {
    }

}



//--------------------------------------------------------------------------
// ODPart --> SequenceChanged
//
//      Should notify this part that the sequencing of this part's
//      display frame within its frame group has changed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerSequenceChanged
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerSequenceChanged");

}

//--------------------------------------------------------------------------
// ODPart --> FrameShapeChanged
//
//      Should notify this part that the frame shape of one of its
//      display frames has changed.
//
//      ->
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerFrameShapeChanged
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerFrameShapeChanged");

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
       _fScrollExt->FrameShapeChanged(ev, frame);
    } /* endif */
#endif //defined OS2 || WIN32

    // Do not allow resize if displaying as icon/thumbnail.
    somSelf->AdjustViewTypeShapes(ev, frame);

    // Update the content extent
    somSelf->UpdateContentExtent(ev, frame);

#if defined (_PLATFORM_OS2_)

    FramePartInfo *pInfo = (FramePartInfo *) frame->GetPartInfo(ev);
    if (!pInfo)
       return;

    ODRect oldRect = pInfo->frameRect;
    ODRect newRect;
    TempODShape fShape = frame->AcquireFrameShape (ev, kODNULL);
    fShape->GetBoundingBox (ev, &newRect);

    if ((newRect.top - newRect.bottom == 0) || (newRect.right - newRect.left == 0))
       return;

    if (oldRect.top - oldRect.bottom == 0) {
       pInfo->frameRect = newRect;
       return;
    }

    pInfo->frameRect = newRect;

    if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
       /* We don't want to adjust the embed position to simulate a top-left based */
       /* coordinate system when scrolling is enabled - in that case, we take the */
       /* much more elegant approach of simply adjusting the internal transform,  */
       /* which scrolls our embeds, achieving the same effect without actually    */
       /* messing with the external transforms of the embeds themselves.          */
       return;
    } /* endif */

    // now let's do some coordinate computation
    ODPoint offset(0, 0);
    offset.y = newRect.top - oldRect.top;

    ALink *itr;
    for (itr = _fEmbeddedObjects->First(ev); itr->Content(ev); itr = itr->Next(ev)) {
       ContentObject *cObj = (ContentObject *) itr->Content(ev);
       cObj->MoveBy (ev, &offset);
    } /* endfor */

    if (_fSelectedObjects->Count(ev))
       somSelf->CreateSelectionBorderShapes (ev, kODNULL);

#endif
}

// -------------------------------------------------------------------------
// ODPart --> CanvasChanged
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCanvasChanged
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCanvasChanged");


}



//--------------------------------------------------------------------------
// ODPart --> CanvasUpdated
//
//--------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCanvasUpdated
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODCanvas        *canvas         // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCanvasUpdated");


}


// -------------------------------------------------------------------------
// ODPart --> HighlightChanged
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerHighlightChanged
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFacet         *facet          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHighlightChanged");


}

// -------------------------------------------------------------------------
// ODPart --> ChangeKind
//
//      Changes this part's preferred kind.
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerChangeKind
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODType           kind           // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerChangeKind");



}

// -------------------------------------------------------------------------
// BaseContainer --> SetupPrinting
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerSetupPrinting
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,         // in
                ODEventData     *event          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerSetupPrinting");

    ODBoolean paperSizeChanged = kODFalse;

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    if ((_fPrintExt!=kODNULL) && _fPrintingEnabled) {
       paperSizeChanged = _fPrintExt->PrinterSetup(ev, event->hwnd);
    } /* endif */
#endif //defined OS2 || WIN32

    return(paperSizeChanged);
}

// -------------------------------------------------------------------------
// BaseContainer --> HandlePrinting
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandlePrinting
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,         // in
                ODEventData     *event          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandlePrinting");

    ODBoolean handled = kODFalse;

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    if ((_fPrintExt!=kODNULL) && _fPrintingEnabled) {
       handled = _fPrintExt->PrintDocument(ev, frame, event);
    } /* endif */
#endif //defined OS2 || WIN32

    return(handled);
}

// -------------------------------------------------------------------------
// BaseContainer --> HandleScrollEvent
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BaseContainerHandleScrollEvent
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,         // in
                ODEventData     *event          // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerHandleScrollEvent");

    ODBoolean handled = kODFalse;

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
       handled = _fScrollExt->HandleScrollEvent(ev, frame, event);
    } /* endif */
#endif //defined OS2 || WIN32

    return(handled);
}

// -------------------------------------------------------------------------
// BaseContainer --> CreatePrintExtension
//
// This method could be overridden by a subclass if for example a different
// class is to be used for the PrintExtension (it would of course have to provide
// the interfaces of an ODPrintExtension which are used elsewhere in this
// class)
// -------------------------------------------------------------------------

SOM_Scope       ODExtension*
SOMLINK         BaseContainerCreatePrintExtension
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCreatePrintExtension");

    ODExtension *printExtension = kODNULL;

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)

    // create and intialize the ODPrintExtension object.
    printExtension = new ODPrintExtension;
    if (printExtension != kODNULL) {
       ((ODPrintExtension *)printExtension)->Initialize(ev, somSelf, kODNULL);
    }
#endif //defined OS2 || WIN32

    return printExtension;
}

// -------------------------------------------------------------------------
// BaseContainer --> CreateScrollExtension
//
// This method could be overridden by a subclass to provide a different
// implementation object for the Scroll Extension.
// -------------------------------------------------------------------------

SOM_Scope       ODExtension*
SOMLINK         BaseContainerCreateScrollExtension
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCreateScrollExtension");

    ODExtension *scrollExtension = kODNULL;

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)

    // create and initialize the ODScrollExtension Object.
    scrollExtension = new ODScrollExtension;
    if (scrollExtension != kODNULL) {
       ((ODScrollExtension *)scrollExtension)->Initialize(ev, somSelf, 0, 0);
    }
#endif //defined OS2 || WIN32

    return scrollExtension;
}

// -------------------------------------------------------------------------
// BaseContainer --> CreateSettingsExtension
//
// This method could be overridden by a subclass to provide a different
// object to support the SettingsExtension.
// -------------------------------------------------------------------------

SOM_Scope       ODExtension*
SOMLINK         BaseContainerCreateSettingsExtension
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev             // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCreateScrollExtension");

    BCPartSettingsExt *settingsExtension = kODNULL;

    // create and initialize the BCPartSettingsExt object.
    settingsExtension = new BCPartSettingsExt;
    if (settingsExtension != kODNULL) {
       settingsExtension->InitSettingsExtension(ev, somSelf) ;
    }

    return settingsExtension;
}

// -------------------------------------------------------------------------
// BaseContainer --> EnablePrinting
//
//
// -------------------------------------------------------------------------

SOM_Scope       ODExtension*
SOMLINK         BaseContainerEnablePrinting
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODBoolean        enable,        // in
                char            *QueueName      // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerEnablePrinting");

    ODExtension *printExtension = kODNULL;

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    _fPrintingEnabled = enable;
    if ((_fPrintExt != kODNULL) && enable) {
       printExtension = _fPrintExt ;
       _fPrintExt->QuerySelectedPrinter(ev, QueueName, kODFalse);
    }
#endif // OS/2 or Win95/NT

    return(printExtension);
}

// -------------------------------------------------------------------------
// BaseContainer --> EnableScrolling
//
//
// -------------------------------------------------------------------------

SOM_Scope       ODExtension*
SOMLINK         BaseContainerEnableScrolling
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODBoolean        enable,        // in
                long             totalWidth,    // in
                long             totalHeight    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerEnableScrolling");

    ODExtension *scrollExtension = kODNULL;

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)

    _fScrollingEnabled = enable;
    somSelf->SetScrollableDimensions(ev, kODNULL /* frame */,
                                     totalWidth, totalHeight);
    scrollExtension = _fScrollExt ;
#endif // OS/2 or Win95/NT

    return(scrollExtension);
}

// -------------------------------------------------------------------------
// BaseContainer --> SetScrollableDimensions
//
//
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerSetScrollableDimensions
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *frame,
                long             totalWidth,    // in
                long             totalHeight    // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerSetScrollableDimensions");

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)
    if ((_fScrollExt!=kODNULL) && _fScrollingEnabled) {
       _fScrollExt->SetScrollableDimensions(ev, frame, totalWidth, totalHeight);
    } /* endif */
#endif //defined OS2 || WIN32
}

// -------------------------------------------------------------------------
// BaseContainer --> ChangeNotification
// This is a hook for subclasses so that they can know when anything
// changes in base container.
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerChangeNotification
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODULong          reason,
                ODFrame         *frame,
                ContentObject  *content,        // in
                ODBoolean       bPropagate,     // in
                ODUpdateID      updateID
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerChangeNotification");

    if (bPropagate)
    {
       // get change
       ODFrame * myFrame = frame;
       if (!frame)
          myFrame = (ODFrame *) _fDisplayFrames->First(ev)->Content(ev);

       // get ID
       ODUpdateID change = updateID;
       if (!updateID)
          change = _fSession->UniqueUpdateID(ev);

       myFrame->ContentUpdated (ev, change);
    }
}

// -------------------------------------------------------------------------
// BaseContainer --> GetMouseMode
// -------------------------------------------------------------------------

SOM_Scope       unsigned short
SOMLINK         BaseContainerGetMouseMode
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev            // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerGetMouseMode");

    return _usMouseMode;
}

// -------------------------------------------------------------------------
// BaseContainer --> UpdateContentExtent
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerUpdateContentExtent
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODFrame         *myFrame        // in
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerUpdateContentExtent");

    try {
       TempODShape frameShape = myFrame->AcquireFrameShape(ev, kODNULL);
       ODRect frameRect;
       frameShape->GetBoundingBox(ev, &frameRect);
#ifdef _PLATFORM_OS2_
       ODPoint extent(frameRect.right, frameRect.top);
#else
       ODPoint extent(frameRect.right, frameRect.bottom);
#endif
       myFrame->ChangeContentExtent(ev, &extent);
    } /* endtry */
    catch (...) {
    } /* endcatch */

}

// -------------------------------------------------------------------------
// BaseContainer --> CreateNewMenu
// -------------------------------------------------------------------------

SOM_Scope       ODPlatformMenu
SOMLINK         BaseContainerCreateNewMenu (
                BaseContainer       *somSelf,       // in
                Environment         *ev,            // in
                ODMenuBar           *menuBar,
                ODULong             menuID)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCreateNewMenu");

    ODPlatformMenu newMenu;

#if defined(_PLATFORM_WIN32_)
    newMenu = (ODPlatformMenu)CreateMenu();
#elif defined(_PLATFORM_OS2_)
    newMenu = WinCreateMenu(HWND_OBJECT,kODNULL);
#elif defined(_PLATFORM_UNIX_)
    newMenu = menuBar->CreateX11PlatformMenu(ev, menuID);
#endif

    menuBar->AddMenuLast(ev, menuID, newMenu, _fPartWrapper);

    return newMenu;
}

// -------------------------------------------------------------------------
// BaseContainer --> CreateMenuItemFromCatalog
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerCreateMenuItemFromCatalog (
                BaseContainer       *somSelf,       // in
                Environment         *ev,            // in
                ODMenuBar           *menuBar,
                ODULong             parentMenuID,
                ODPlatformMenuItem  *menuItem,
                ODPtr               nlsCat,         // Catalog previously opened
                ODULong             msgSet,
                ODULong             msgID,
                string              defaultText)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCreateMenuItemFromCatalog");

    menuBar->AddMenuItemLast(ev, parentMenuID, menuItem->id, menuItem);

    somSelf->SetMenuItemTextFromCatalog ( ev,
                                          menuBar,
                                          parentMenuID,
                                          menuItem,
                                         (nl_catd) nlsCat,
                                          msgSet,
                                          msgID,
                                          defaultText);
}

// -------------------------------------------------------------------------
// BaseContainer --> SetMenuItemTextFromCatalog
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerSetMenuItemTextFromCatalog (
                BaseContainer       *somSelf,       // in
                Environment         *ev,            // in
                ODMenuBar           *menuBar,
                ODULong             parentMenuID,
                ODPlatformMenuItem  *menuItem,
                ODPtr               nlsCat,         // Catalog previously opened
                ODULong             msgSet,
                ODULong             msgID,
                string              defaultText)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerSetMenuItemTextFromCatalog");


#if defined(__IBMCPP__) || defined(_IBMR2)
    char *bcText;           // pointer for NLS message
    bcText=catgets((nl_catd) nlsCat, msgSet, msgID, defaultText);
#else
    char bcText[256];
    strcpy (bcText, defaultText);
#endif
    menuBar->SetMenuItemText(ev, parentMenuID, menuItem->id, bcText);

}

// -------------------------------------------------------------------------
// BaseContainer --> AddSeparatorToMenu
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BaseContainerAddSeparatorToMenu
                (
                BaseContainer   *somSelf,       // in
                Environment     *ev,            // in
                ODMenuBar       *menuBar,
                ODULong         menuID,
                ODULong         separatorID
                )
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerAddSeparatorToMenu");

    ODPlatformMenuItem *mi = new ODPlatformMenuItem;

    // clear the memory
    memset (mi, 0, sizeof(ODPlatformMenuItem));

    // add a menu separator line to the menu
    mi->id = separatorID;
#if defined(_PLATFORM_WIN32_)
    mi->afAttribute=MF_SEPARATOR;
#elif defined(_PLATFORM_OS2_)
    mi->afAttribute=CA_TITLESEPARATOR;
#endif
    menuBar->AddMenuItemLast(ev, menuID, mi->id, mi);

    delete mi;
}

