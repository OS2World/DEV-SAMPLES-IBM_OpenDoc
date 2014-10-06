// @(#) 1.5 com/src/samples/grafpart/graph_cm.cpp, odgrafpart, od96os2, odos29712d 2/7/97 17:41:33 [3/21/97 17:49:31]
/*====START_GENERATED_PROLOG======================================
*/
/*
 *   COMPONENT_NAME: odgrafpart
 *
 *   CLASSES: GrafPart
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

// ************************************************************************
//  Contains:  Class implementation for a 2D-Drawing Container Part
// ************************************************************************

// Part Developers NOTE:
//   This file contains the kernel of the implementation for a
// GrafPart class, but is extended to be used in two ways:
//   It may be included into the source with the preprocessor symbol
// "_Scriptable_GP_" not defined, (e.g., by iodgraph.cpp),
// where it will produce the GrafPart class; or
//   It may be included into the source with the preprocessor symbol
// "_Scriptable_GP_" defined, (e.g., by iodscrgp.cpp),
// where it will produce the ScriptableGraphPart class.
//
// The following macros must be defined in one of the two ways to
// generate the correct classname in the method declarations and output.
//      GP_P(x) used when <classname> is a prefix of x
//      GP_Pq(x) used when <classname> is a prefix of x in a quoted string
//      GP_C the classname
//      GP_Cq the classname in quotes
#ifndef _Scriptable_GP_
    #define GP_P(n)    GrafPart##n
    #define GP_Pq(n)  "GrafPart##n"
    #define GP_C       GrafPart
    #define GP_Cq     "GrafPart"
#else
    #define GP_P(n)    ScriptableGraphPart##n
    #define GP_Pq(n)  "ScriptableGraphPart##n"
    #define GP_C       ScriptableGraphPart
    #define GP_Cq     "ScriptableGraphPart"
#endif



#ifndef SOM_Module_GrafPart_Source
    #define SOM_Module_GrafPart_Source
#endif   // SOM_Module_GrafPart_Source

// GrafPart's includes
#ifndef _IODGCOMM_CPP_
   #include <iodgcomm.cpp>
#endif   // _IODGCOMM_CPP_

// GrafPart's defines & constants
#ifndef _IODGRAPH_HPP_
   #include <iodgraph.hpp>
#endif   // _IODGRAPH_HPP_

// support use of temporary objects (DrawContents, HandleMouse*)
#ifndef _TEMPOBJ_
    #include <TempObj.h>
#endif // _TEMPOBJ_

// support CFocus (DrawContents)
#ifndef _FOCUSLIB_
    #include <FocusLib.h>
#endif // _FOCUSLIB_

// support Storage Units (Read/WriteKindInfo)
#ifndef _STORUTIL_
    #include <StorUtil.h>
#endif // _STORUTIL_

// includes for native drawing functions
#if defined(_PLATFORM_WIN32_)
    #include <windows.h>
    #include <winuser.h>
    #include <wingdi.h>
#elif defined(_PLATFORM_OS2_)
    #include <ODos2.h>
#endif // _PLATFORM_???_


// local function support includes
#ifndef SOM_ContentGrafPartFigr_xh
    #include "iodgfigr.xh"
#endif // SOM_ContentGrafPartFigr_xh

#ifndef SOM_ContentGrafPartPoin_xh
    #include "iodgpoin.xh"
#endif // SOM_ContentGrafPartPoin_xh

#ifndef SOM_ContentGrafPartLine_xh
    #include "iodgline.xh"
#endif // SOM_ContentGrafPartLine_xh

#ifndef SOM_ContentGrafPartRect_xh
    #include "iodgrect.xh"
#endif // SOM_ContentGrafPartRect_xh

#ifndef SOM_ContentGrafPartText_xh
    #include "iodgtext.xh"
#endif // SOM_ContentGrafPartText_xh


// =========================================================================
//
//     Global helper Functions: GrafPart
//
// =========================================================================

// -------------------------------------------------------------------------
// FirstFacet
//
//     Global helper function: return the first facet associated with a frame
// -------------------------------------------------------------------------
ODFacet*    FirstFacet( Environment*    ev,
                        ODFrame*        frame)
{
    SQUAWK("> Invoked %s(Global)::FirstFacet()\n", GP_Cq);

    ODFacet*    facet;

    try
    {
        ODFrameFacetIterator *ffitr  = frame->CreateFacetIterator(ev);
        facet = (ODFacet *)ffitr->First(ev);
        ODDeleteObject(ffitr);
    }   // try

    catch(...)
    {
        SQUAWK("\t%s(Global)::FirstFacet(): CAUGHT EXCEPTION\n", GP_Cq);
    }

    SQUAWK("< Leaving %s(Global)::FirstFacet()\n", GP_Cq);
    return facet;
}   // FirstFacet()


// -------------------------------------------------------------------------
//  FluffRect
//
//     Global helper function: expand a rectangle by one pixel in each direction
// -------------------------------------------------------------------------
ODRect* FluffRect(  ODRect*  rect)
{
    SQUAWK("> Invoked %s(Global)::FluffRect()\n", GP_Cq);

    ODFixed one   = ODIntToFixed(1);

#ifdef _PLATFORM_OS2_                   // OS2 origin is LLC
    rect->top    += one;
    rect->bottom -= one;
#else                                   // everyone else's origin is ULC
    rect->top    -= one;
    rect->bottom += one;
#endif  // _PLATFORM_OS2_
    rect->left   -= one;
    rect->right  += one;

    SQUAWK("< Leaving %s(Global)::FluffRect()\n", GP_Cq);
    return rect;
}   // FluffRect()


// -------------------------------------------------------------------------
//  GetPoint
//
//     Global helper function: update a point with current cursor position
// -------------------------------------------------------------------------
void    GetPoint(   Environment*    ev,
                    ODFacet*        facet,
                    ODEventData*    event,
                    ODPoint*        point)
{
    SQUAWK("> Invoked %s(Global)::GetPoint()\n", GP_Cq);

    // Get the containing frame's windowframe transform
    TempODTransform xform = facet->AcquireWindowContentTransform(ev, kODNULL);

    try
    {
        // collect the current point (in HDraw coords)
#ifdef _PLATFORM_OS2_
        point->x = ODIntToFixed(SHORT1FROMMP(event->mp1));
        point->y = ODIntToFixed(SHORT2FROMMP(event->mp1));
#else
        point->x = ODIntToFixed(LOWORD(event->lParam));
        point->y = ODIntToFixed(HIWORD(event->lParam));
#endif  // _PLATFORM_OS2_

        // Invert the HDraw coords into containing frame coords
        xform->InvertPoint(ev, point);

    }   // try

    catch(...)
    {
        SQUAWK("\t%s(Global)::GetPoint(): CAUGHT EXCEPTION\n", GP_Cq);
    }

    SQUAWK("< Leaving %s(Global)::GetPoint()\n", GP_Cq);

}   // GetPoint()


// *************************************************************************
//
//  Class implementation:
//
// *************************************************************************


// =========================================================================
//
//     Public override methods: GrafPart
//
// =========================================================================

// -------------------------------------------------------------------------
// GrafPart --> somInit
//
//     Initialization used at registration time
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK GP_P(somInit) (GP_C *somSelf )
{
    SQUAWK("> Invoked %s::somInit()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq , GP_Pq(somInit) );

    // call parent method
    parent_somInit(somSelf) ;

    // initialize attributes
    _fMenuBar     = kODNULL;
    _fSession     = kODNULL;
    _fPartWrapper = kODNULL;

    // initalize instance data (these are repeated in Reset() )
    _fAction      = kODCommandGrafPartSelect;
    _fActionType  = kODSingleAction;
    _fCurrObj     = kODNULL;
    _fCurrObjType = kODNULL;
    _fCurrShape   = kODNULL;
    _fTempShape   = kODNULL;
    memset(&_fPt, 0, sizeof(ODPoint) );

    SQUAWK("< Leaving %s::somInit()\n", GP_Cq);
}   // somInit()


// -------------------------------------------------------------------------
// GrafPart --> somUninit
//
//     Uninitialization used at registration time
//
//     -> public override method
//     -> calls parent last, after intrinsics are deleted
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK GP_P(somUninit) (  GP_C  *somSelf )
{
    SQUAWK("> Invoked %s::somUninit()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) ( GP_Cq , GP_Pq(somUninit) );

    // delete all intrinsic content

    Environment* ev = somGetGlobalEnvironment();            // get the environment into a buffer
    ALinkedList* sList = somSelf->GetSelectedObjects(ev);   // get the list of selected objects
    ALinkedList* eList = somSelf->GetEmbeddedObjects(ev);   // get the list of embedded objects
    ALink *eIter;                                           // define an iterator on the embedded list
    ContentGrafPartFigr*    figr;                           // declare a buffer for a intrinsic object
    ODULong                 coType;                         // declare a buffer for a intrinsic type

    for(eIter = eList->First(ev);                           // for each object in the embedded list
        eIter->Content(ev);
        eIter = eIter->Next(ev) )
    {
        figr = (ContentGrafPartFigr *) eIter->Content(ev);  // treat it as intrinsic object
        coType = figr->_get_objType(ev);                    // store the specific type

        if ( ( coType >  COBJ_GRAFPART_FIGR ) &&            // if it is GP-intrinsic content
             ( coType <= COBJ_GRAFPART_LAST ) )
        {
            figr->Uninitialize(ev);                         // unsetup the figure
            delete figr;                                    // deallocate the figure
        }   // if: intrinsic content?
        else
        {
            SQUAWK("\t%s::somUninit(): unrecognized content object type: %d\n", GP_Cq, coType );
        }   // else: intrinsic content?
    }   // for: each embedded object

    // all intrinsics are gone, so call parent last
    parent_somUninit(somSelf);

    SQUAWK("< Leaving %s::somUninit()\n", GP_Cq);
    return;
}   // somUninit()


// -------------------------------------------------------------------------
// GrafPart --> Initialize
//
//     Class-specific initialization used at run time
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK GP_P(Initialize) ( GP_C    *somSelf,
                                                Environment *ev,
                                                ODPart      *partWrapper )
{
    SQUAWK("> Invoked %s::Initialize()\n", GP_Cq);

    // initialize self pointers
    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) ( GP_Cq , GP_Pq(Initialize) );

    // call parent's Initialization
    parent_Initialize(somSelf,ev,partWrapper);

    // Cache references to Session object and other global values
    _fSession = somSelf->GetStorageUnit(ev)->GetSession(ev);

    // Create MenuBar  Part
    _fMenuBar = somSelf->GetMenuBar(ev);

    SQUAWK("< Leaving %s::Initialize()\n", GP_Cq);
    return;
}   // Initialize()


// -------------------------------------------------------------------------
// GrafPart --> WriteIconToSU
//
//     Write the Icon to the storage unit for display in stationery
//
//     -> public override method
//     -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK GP_P(WriteIconToSU) ( GP_C *somSelf,
                                                        Environment*    ev,
                                                        ODStorageUnit*  toSU )
{
    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq , GP_Pq(WritePartInfo) );

    SQUAWK("> Invoked %s::WriteIconToSU()\n", GP_Cq);

    // Customized icon support for OS2.
#ifdef _PLATFORM_OS2_
    SQUAWK("\t%s::WriteIconToSU(): performing OS/2-specific icon setup\n", GP_Cq);
    HMODULE hmod;
    ULONG cbIconSize;
    PBYTE pIconData = NULL;
    CHAR Error[256] = "";

    DosLoadModule(Error, sizeof(Error), "iodgraph", &hmod);

    if ( !DosQueryResourceSize( hmod, RT_POINTER, kODIcon, &cbIconSize) &&
         !DosGetResource( hmod, RT_POINTER, kODIcon, (PPVOID)&pIconData)  )
    {
        if ( ODSUExistsThenFocus (ev, toSU, kODPropIconFamily, kODIconFamily) )
            toSU->Remove (ev);
        ODSUAddPropValue (ev, toSU, kODPropIconFamily, kODIconFamily);
        StorageUnitSetValue( toSU, ev, cbIconSize, (ODValue)pIconData );
        DosFreeResource(pIconData);
    }
    else
    {
        SQUAWK("\t%s::WriteIconToSU(): DosGetResource failed!\n", GP_Cq);
    }
#endif // _PLATFORM_OS2_

    SQUAWK("< Leaving %s::WriteIconToSU()\n", GP_Cq);
    return;
}   // WriteIconToSU()


// -------------------------------------------------------------------------
// GrafPart --> InstallMenuItems
//
//     Install additional items in pull-down menu.
//
//     -> public override method
//     -> calls parent last, if not handled locally
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK GP_P(InstallMenuItems) (   GP_C    *somSelf,
                                                        Environment *ev,
                                                        ODMenuBar   *menuBar )
{
    SQUAWK("> Invoked %s::InstallMenuItems()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(InstallMenuItems) );

    nl_catd GrafPartNLSCat;         // handle to NLS message catalog
    char*   GrafPartText;           // pointer for NLS message
    ODPlatformMenuItem* mi = new ODPlatformMenuItem;    // menuitem buffer
    memset(mi, 0, sizeof(ODPlatformMenuItem) );         // initialize menu item attributes

    // call parent method first
    parent_InstallMenuItems(somSelf,
                                                   ev,
                                                   menuBar);
    // set up catalog
#ifdef _NLS_
    setlocale(LC_MESSAGES, NULL);

    /* Open the catalog (using LC_MESSAGES, not LANG via the second argument) */
    GrafPartNLSCat = catopen(GRAFPART_NLS_CATALOG, 0);

    if (GrafPartNLSCat != CATD_ERR)
        SQUAWK("\t%s::InstallMenuItems(): Opened NLS catalog: %s with handle: %lX\n", GP_Cq, GRAFPART_NLS_CATALOG, GrafPartNLSCat);
    else
        SQUAWK("\t%s::InstallMenuItems(): Could not open NLS catalog: %s\n", GP_Cq, GRAFPART_NLS_CATALOG);
#endif

    // Allocate temporary menuitem buffer

    // use default attributes
    mi->afAttribute = 0;


    // add "Refresh" selection item to options menu
    mi->id = kODCommandGrafPartRefresh;
    menuBar->AddMenuItemLast(ev, kODOptionsMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_REFRESH);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_REFRESH,
#ifdef GPDebug
        "REFRESH WINDOW"
#else
        "Refresh Window"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODOptionsMenuID, kODCommandGrafPartRefresh, GrafPartText);


    // add a menu separator line to Embed menu
    mi->id = CMD(Dash);
    mi->afAttribute = MB_SEPARATOR;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, kODNULL, mi);
    mi->afAttribute = 0;                // reset attribute to normal

    // add "Point" selection item to Embed menu
    mi->id = kODCommandGrafPartAddPoin;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_POIN);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_POIN,
#ifdef GPDebug
        "POINT"
#else
        "Point"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddPoin, GrafPartText);


    // add "Line" selection item to Embed menu
    mi->id = kODCommandGrafPartAddLine;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_LINE);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_LINE,
#ifdef GPDebug
        "LINE"
#else
        "Line"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddLine, GrafPartText);


    // add "Rectangle" selection item to Embed menu
    mi->id = kODCommandGrafPartAddRect;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_RECT);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_RECT,
#ifdef GPDebug
        "RECTANGLE"
#else
        "Rectangle"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddRect, GrafPartText);


/*  add these sections to enable additional figure type support from the GP GUI
    // add "Text" selection item to Embed menu
    mi->id = kODCommandGrafPartAddText;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_TEXT);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_TEXT,
#ifdef GPDebug
        "TEXT"
#else
        "Text"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddText, GrafPartText);


    // add "Text" selection item to Embed menu
    mi->id = kODCommandGrafPartAddText;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_TEXT);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_TEXT,
#ifdef GPDebug
        "TEXT"
#else
        "Text"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddText, GrafPartText);


    // add "Elli" selection item to Embed menu
    mi->id = kODCommandGrafPartAddElli;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_ELLI);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_ELLI,
#ifdef GPDebug
        "ELLIPSE"
#else
        "Ellipse"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddElli, GrafPartText);


    // add "Circ" selection item to Embed menu
    mi->id = kODCommandGrafPartAddCirc;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_CIRC);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_CIRC,
#ifdef GPDebug
        "CIRCLE"
#else
        "Circle"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddCirc, GrafPartText);


    // add "Plin" selection item to Embed menu
    mi->id = kODCommandGrafPartAddPlin;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_PLIN);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_PLIN,
#ifdef GPDebug
        "POLYLINE
#else
        "Polyline"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddPlin, GrafPartText);


    // add "Pgon" selection item to Embed menu
    mi->id = kODCommandGrafPartAddPgon;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_PGON);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_PGON,
#ifdef GPDebug
        "POLYGON"
#else
        "Polygon"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddPgon, GrafPartText);


    // add "Free" selection item to Embed menu
    mi->id = kODCommandGrafPartAddFree;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_FREE);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_FREE,
#ifdef GPDebug
        "FREEHAND"
#else
        "Freehand"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddFree, GrafPartText);


    // add "Imag" selection item to Embed menu
    mi->id = kODCommandGrafPartAddImag;
    menuBar->AddMenuItemLast(ev, kODEmbedMenuID, mi->id, mi);
    SQUAWK("\t%s::InstallMenuItems(): getting NLS catalog: %lX, set: %d, command: %d\n", GP_Cq, GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_IMAG);
    GrafPartText = catgets(GrafPartNLSCat, GRAFPART_MSG_SET, GRAFPART_ADD_IMAG,
#ifdef GPDebug
        "IMAGE"
#else
        "Image"
#endif // GPDebug
    );
    menuBar->SetMenuItemText(ev, kODEmbedMenuID, kODCommandGrafPartAddImag, GrafPartText);


*/


    // cleanup menuitem buffer
    delete mi;

    // close the message catalog
    catclose(GrafPartNLSCat);
    SQUAWK("\t%s::InstallMenuItems(): closed NLS catalog handle: %lX\n", GP_Cq, GrafPartNLSCat);


    SQUAWK("< Leaving %s::InstallMenuItems()\n", GP_Cq);
    return;
}   // InstallMenuItems()


// -------------------------------------------------------------------------
// GrafPart --> HandleMenuEvent
//
//      Handle a menubar or pulldown menu selection event.
//
//     -> public override method
//     -> calls parent last, if event not handled locally
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(HandleMenuEvent) ( GP_C    *somSelf,
                                                        Environment *ev,
                                                        ODFrame     *frame,
                                                        ODEventData *event )
{
    SQUAWK("> Invoked %s::HandleMenuEvent()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(HandleMenuEvent) );

    ODBoolean   eventHandled = kODFalse;    // flag to track whether event was handled locally

    try
    {
        // determine which menu pulldown it was
        switch(
#if defined(_PLATFORM_WIN32_)
        LOWORD(event->wParam)
#elif defined(_PLATFORM_OS2_)
        LONGFROMMP(event->mp1)
#endif  // _PLATFORM_???_
               )    // switch condition
        {
            // User selected menu item to Refresh the screen
            case CMD(GrafPartRefresh):
                SQUAWK("\t%s::HandleMenuEvent(): calling HandleRefresh()\n", GP_Cq);
                eventHandled = somSelf->HandleRefresh(ev);
                break;

            // User selected menu item to Add a Point
            case CMD(GrafPartAddPoin):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Poin)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_POIN);
                break;

            // User selected menu item to Add a Line
            case CMD(GrafPartAddLine):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Line)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_LINE);
                break;

            // User selected menu item to Add a Rectangle
            case CMD(GrafPartAddRect):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Rect)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_RECT);
                break;

/*  add these sections to enable additional figure type support from the GP GUI
            // User selected menu item to Add Text
            case CMD(GrafPartAddText):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Text)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_TEXT);
                break;

            // User selected menu item to Add Elli
            case CMD(GrafPartAddElli):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Elli)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_TEXT);
                break;

            // User selected menu item to Add Circ
            case CMD(GrafPartAddCirc):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Circ)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_TEXT);
                break;

            // User selected menu item to Add Pgon
            case CMD(GrafPartAddPgon):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Pgon)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_TEXT);
                break;

            // User selected menu item to Add Plin
            case CMD(GrafPartAddPlin):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Plin)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_TEXT);
                break;

            // User selected menu item to Add Free
            case CMD(GrafPartAddFree):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Free)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_TEXT);
                break;

            // User selected menu item to Add Imag
            case CMD(GrafPartAddImag):
                SQUAWK("\t%s::HandleMenuEvent(): calling AddIntrinsic(Imag)\n", GP_Cq);
                eventHandled = somSelf->AddIntrinsic(ev, frame, COBJ_GRAFPART_TEXT);
                break;
*/

            default:
                SQUAWK("\t%s::HandleMenuEvent(): Unknown menu event: %d\n", GP_Cq, event);
                eventHandled = kODFalse;
                break;

        }   // switch: which menu pulldown?
    }   // try
    catch(...)
    {
        SQUAWK("\t%s::HandleMenuEvent(): CAUGHT EXCEPTION\n", GP_Cq);
    }   // catch

    // if event not handled locally, pass on to parent
    if (!eventHandled)
    {
        // pass event to parent
        SQUAWK("\t%s::HandleMenuEvent(): passing event to parent\n", GP_Cq);
        eventHandled = (parent_HandleMenuEvent(  somSelf,
                                                                        ev,
                                                                        frame,
                                                                        event ) );
        SQUAWK("< Leaving %s::HandleMenuEvent() with parent's result (%d)\n", GP_Cq, eventHandled);
        return(eventHandled);
    }
    else
    {
        SQUAWK("< Leaving %s::HandleMenuEvent() with event handled locally\n", GP_Cq);
        return(eventHandled);    // should always be true here
    }   // else
}   // HandleMenuEvent()


// -------------------------------------------------------------------------
// GrafPart --> HandleMouseMotionStart
//
//     Event handler: begin moving mouse with MB1 down
//
//     -> public override method
//     -> calls parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(HandleMouseMotionStart) ( GP_C    *somSelf,
                                                                Environment *ev,
                                                                ODEventData *event,
                                                                ODFrame     *frame,
                                                                ODFacet     *facet,
                                                                ODEventInfo *eventInfo )
{
    SQUAWK("> Invoked %s::HandleMouseMotionStart()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(HandleMouseMotionStart) );


    // Because mouse movement is handled with platform-specific events and not OpenDoc events,
    //   and that the dispatcher will return a null facet for a plat-spec event, we must check
    //   the incoming facet and correct it before using.
    if (facet == NULL)                          // if the facet it null
        facet = FirstFacet(ev, frame);          // assign it to the first facet for the current frame

    // flag to track if event was handled locally
    ODBoolean       eventHandled = kODFalse;

    // Get the containing frame's windowframe transform
    TempODTransform xform = facet->AcquireWindowContentTransform(ev, kODNULL);

    // _fActionType was set initially by HandleMenuEvent,
    //     or by a previous click in the GrafPartAdd sequence
    switch (_fActionType)
    {
        // Single not defined
        case kODSingleAction:
            SQUAWK("\t%s::HandleMouseMotionStart(): undefined ActionType: kODSingleAction\n", GP_Cq);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

        // Begin -> select first point
        case kODBeginAction:

            // create and cache the intrinsic object with current point
            SQUAWK("\t%s::HandleMouseMotionStart(): state: kODCommandGrafPartAdd, kODBeginAction\n", GP_Cq);
            GetPoint(ev, facet, event, &_fPt);                  // get the current point
            ( (ContentGrafPartFigr *)_fCurrObj )
                ->Initialize(ev, frame, &_fPt);                 // set up new object with origin point
            _fCurrShape = frame->CreateShape(ev);               // create temp shapes for rubberbanding
            _fTempShape = frame->CreateShape(ev);               // create temp shapes for rubberbanding

            // set local handling flags
            _fActionType = kODEndAction;    // set the action type for the next action
            eventHandled = kODTrue;         // the click was handled locally, do not pass on
            break;

        // End undefined
        case kODEndAction:
            SQUAWK("\t%s::HandleMouseMotionStart(): ActionType: kODEndAction\n", GP_Cq);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

        // unknown action type
        default:
            SQUAWK("\t%s::HandleMouseMotionStart(): kODCommandGrafPartAddLine: undefined ActionType: %d\n", GP_Cq, _fActionType);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

    }   // switch: ActionType

    // termination: if click not handled locally, pass on to parent
    if (!eventHandled)
    {
        SQUAWK("< Leaving %s::HandleMouseMotionStart(): calling parent\n", GP_Cq);
        return (parent_HandleMouseMotionStart(  somSelf,
                                                ev,
                                                event,
                                                frame,
                                                facet,
                                                eventInfo));
    }
    else
    {
        SQUAWK("< Leaving %s::HandleMouseMotionStart(): returning True\n", GP_Cq);
        return(eventHandled);           // should always be true here
    }
}   // HandleMouseMotionStart()


// -------------------------------------------------------------------------
// GrafPart --> HandleMouseMotionLBDown
//
//     Event handler: mouse movement with MB1 down
//
//     -> public override method
//     -> calls parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(HandleMouseMotionLBDown) ( GP_C        *somSelf,
                                                                Environment *ev,
                                                                ODEventData *event,
                                                                ODFrame     *frame,
                                                                ODFacet     *facet,
                                                                ODEventInfo *eventInfo )
{
    SQUAWK("> Invoked %s::HandleMouseMotionLBDown()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(HandleMouseMotionLBDown) );

    ODBoolean   eventHandled = kODFalse;        // flag to track whether event was handled locally


    // Because mouse movement is handled with platform-specific events and not OpenDoc events,
    //   and that the dispatcher will return a null facet for a plat-spec event, we must check
    //   the incoming facet and correct it before using.
    if (facet==kODNULL)                         // if the facet it null
        facet = FirstFacet(ev, frame);          // assign it to the first facet for the current frame

    // _fActionType was set initially by HandleMenuEvent,
    //     or by a previous click in the sequence
    switch (_fActionType)
    {
        // Single not defined
        case kODSingleAction:
            SQUAWK("\t%s::HandleMouseMotionLBDown(): undefined ActionType: kODSingleAction\n", GP_Cq);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

        // Begin not defined
        case kODBeginAction:
            SQUAWK("\t%s::HandleMouseMotionLBDown(): undefined ActionType: kODBeginAction\n", GP_Cq);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

        // End -> rubberband the line
        case kODEndAction:
            SQUAWK("\t%s::HandleMouseMotionLBDown(): state: kODGrafPartAddLine, kODBeginAction\n", GP_Cq);

            // update the intrinsic object
            GetPoint(ev, facet, event, &_fPt);                      // get the current point
            _fBBox = _fCurrObj->_get_boundingRect(ev);              // get boundry before update
            _fCurrShape->SetRectangle(ev, FluffRect(&_fBBox) );     // save the shape of it
            somSelf->UpdateIntrinsic(ev, frame, &_fPt);             // update the object in progress
            _fBBox = _fCurrObj->_get_boundingRect(ev);              // get boundry after update
            _fTempShape->SetRectangle(ev, FluffRect(&_fBBox) );     // save the shape of it
            _fCurrShape->Union(ev, _fTempShape);                    // add the shapes

            // set local handling flags
//          _fAction     = kODCommandGrafPartSelect;    // Action: reset to Select (default)
//          _fActionType = kODSingleAction;             // ActionType: reset to default
            eventHandled = kODTrue;                     // the MouseUp was handled locally, do not pass on

            // refresh the image of the intrinsic object
            char* refMeth;
            refMeth = getenv("GP_REFRESH");
            if ( refMeth==NULL )
                refMeth = "1";        // default refresh method is 1
            switch( atoi(refMeth) )
            {
                case 3:
                    // update the facet to make it render the line
                    SQUAWK("\t%s::HandleMouseMotionLBDown(): refresh method 3\n", GP_Cq);
                    facet->Update(ev, _fCurrShape, kODNULL);
                    break;

                case 2:
                    // invalidate the line's shape to make it render
                    SQUAWK("\t%s::HandleMouseMotionLBDown(): refresh method 2\n", GP_Cq);
                    frame->Invalidate(ev, _fCurrShape, kODNULL);
                    break;

                case 1:
                case 0:
                default:
                    // invalidate the frame to make it all render
                    SQUAWK("\t%s::HandleMouseMotionLBDown(): refresh method 1\n", GP_Cq);
                    frame->Invalidate(ev, kODNULL, kODNULL);
                    break;
            }   // switch refMeth

            // set local handling flags
            eventHandled = kODTrue;         // the click was handled locally, do not pass on
            break;

        // unknown action type
        default:
            SQUAWK("\t%s::HandleMouseMotionLBDown(): kODCommandGrafPartAdd: undefined ActionType: %d\n", GP_Cq, _fActionType);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

    }   // switch: ActionType

    // termination: if click not handled locally, pass on to parent
    if (!eventHandled)
    {
        SQUAWK("< Leaving %s::HandleMouseMotionLBDown(): calling parent\n", GP_Cq);
        return (parent_HandleMouseMotionLBDown(  somSelf,
                                                                        ev,
                                                                        event,
                                                                        frame,
                                                                        facet,
                                                                        eventInfo));
    }
    else
    {
        SQUAWK("< Leaving %s::HandleMouseMotionLBDown(): returning True\n", GP_Cq);
        return(eventHandled);           // should always be true here
    }
}   // HandleMouseMotionLBDown()


// -------------------------------------------------------------------------
// GrafPart --> HandleMouseMotionEnd
//
//     Event handler: end moving mouse and MB1 up
//
//     -> public override method
//     -> calls parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(HandleMouseMotionEnd) (    GP_C        *somSelf,
                                                                Environment *ev,
                                                                ODEventData *event,
                                                                ODFrame     *frame,
                                                                ODFacet     *facet,
                                                                ODEventInfo *eventInfo )
{
    SQUAWK("> Invoked %s::HandleMouseMotionEnd()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(HandleMouseMotionEnd) );

    ODBoolean       eventHandled = kODFalse;    // flag to track whether event was handled locally
    ContentGrafPartFigr*    figr;                           // declare a buffer for a intrinsic object

    // Because mouse movement is handled with platform-specific events and not OpenDoc events,
    //   and that the dispatcher will return a null facet for a plat-spec event, we must check
    //   the incoming facet and correct it before using.
    if (facet == NULL)                          // if the facet it null
        facet = FirstFacet(ev, frame);          // assign it to the first facet for the current frame

    // Get the containing frame's windowframe transform
    TempODTransform xform = facet->AcquireWindowContentTransform(ev, kODNULL);

    // _fActionType was set initially by HandleMenuEvent,
    //     or by a previous click in the GrafPartAddLine sequence
    switch (_fActionType)
    {
        // Single not defined
        case kODSingleAction:
            SQUAWK("\t%s::HandleMouseMotionEnd(): undefined state: kODCommandGrafPartAdd, kODSingleAction\n", GP_Cq);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

        // Begin not defined
        case kODBeginAction:
            SQUAWK("\t%s::HandleMouseMotionEnd(): undefined state: kODCommandGrafPartAdd, kODBeginAction\n", GP_Cq);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

        // End -> finalize the new intrinsic object at this point
        case kODEndAction:
            SQUAWK("\t%s::HandleMouseMotionEnd(): state: kODCommandGrafPartAdd, kODEndAction\n", GP_Cq);

            // update the intrinsic object
            GetPoint(ev, facet, event, &_fPt);          // get the current point
            somSelf->UpdateIntrinsic(ev, frame, &_fPt); // update the object in progress

            // set local handling flags
            _fAction     = kODCommandGrafPartSelect;    // Action: reset to Select (default)
            _fActionType = kODSingleAction;             // ActionType: reset to default
            eventHandled = kODTrue;                     // the MouseUp was handled locally, do not pass on

            // redraw: shape handling not needed because the whole frame will be invalidated by HandleRefresh()
            _fCurrShape->Release(ev);                               // delete temp shapes for rubberbanding
            _fTempShape->Release(ev);                               // delete temp shapes for rubberbanding
            somSelf->Reset(ev);                         // reset all editor state to defaults
            somSelf->HandleRefresh(ev);                 // refresh the whole content area
            break;

        // unknown action type
        default:
            SQUAWK("\t%s::HandleMouseMotionEnd(): kODCommandGrafPartAdd: undefined ActionType: %d\n", GP_Cq, _fActionType);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on
            break;

    }   // switch: ActionType

    // termination: if click not handled locally, pass on to parent
    if (!eventHandled)
    {
        SQUAWK("< Leaving %s::HandleMouseMotionEnd(): calling parent\n", GP_Cq);
        return (parent_HandleMouseMotionEnd( somSelf,
                                                                    ev,
                                                                    event,
                                                                    frame,
                                                                    facet,
                                                                    eventInfo));
    }
    else
    {
        SQUAWK("< Leaving %s::HandleMouseMotionEnd(): returning True\n", GP_Cq);
        return(eventHandled);           // should always be true here
    }
}   // HandleMouseMotionEnd()


// -------------------------------------------------------------------------
// GrafPart --> HandleMouseClick
//
//     Event handler: mouse click
//
//     -> public override method
//     -> calls parent last, if not handled locally
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(HandleMouseClick)  (   GP_C        *somSelf,
                                                            Environment *ev,
                                                            ODEventData *event,
                                                            ODFrame     *frame,
                                                            ODFacet     *facet,
                                                            ODEventInfo *eventInfo )
{
    SQUAWK("> Invoked %s::HandleMouseClick()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(HandleMouseClick) );

    ODBoolean   eventHandled = kODFalse;                    // flag to track whether event was handled locally
    ALinkedList *eList = somSelf->GetEmbeddedObjects(ev);   // get the list of embedded objects
    ALink       *eIter;                                     // declare an iterator on the emedded list
    ALinkedList *sList = somSelf->GetSelectedObjects(ev);   // get the list of selected objects
    ALink       *sIter;                                     // declare an iterator on the selected list
    ContentGrafPartFigr*    figr;                           // declare a buffer for a intrinsic object
    COType                  coType;                         // declare a buffer for a intrinsic type

    // Because mouse movement is handled with platform-specific events and not OpenDoc events,
    //   and that the dispatcher will return a null facet for a plat-spec event, we must check
    //   the incoming facet and correct it before using.
    if (!facet)                                 // if the facet it null
        facet = FirstFacet(ev, frame);          // assign it to the first facet for the current frame

    switch (_fAction)
    {
        // SELECTION
        case CMD(GrafPartSelect):

            // _fActionType is not used, as GrafPartSelect is a single-stage action
            SQUAWK("\t%s::HandleMouseClick():state: kODCommandGrafPartSelect\n", GP_Cq);

            GetPoint(ev, facet, event, &_fPt);                  // get the current point

            // is the cursor on a contained object?
            for(eIter = eList->First(ev);                       // for each object in the embedded list
                eIter->Content(ev) && !eventHandled;            // until something happens
                eIter = eIter->Next(ev) )
            {
                figr = (ContentGrafPartFigr *) eIter->Content(ev);  // treat it as intrinsic object
                coType = figr->_get_objType(ev);                    // store the specific type

                if ( ( coType >  COBJ_GRAFPART_FIGR ) &&        // if it is GP-intrinsic content
                     ( coType <= COBJ_GRAFPART_LAST ) )
                {
                    if (figr->ContainsPoint(ev, &_fPt) )        // then if the point is on the object
                    {                                           // then toggle the object's selection
                        if (figr->_get_selectionState(ev) )     // is it already selected?
                        {                                       // then deselect it
                            SQUAWK("\t%s::HandleMouseClick(): deselected intrinsic object\n", GP_Cq);
                            figr->_set_selectionState(ev, kODFalse);    // tell it is not selected
                            sList->Remove(ev, figr);            // delete it from the selected list
                        }   // if: already selected?
                        else                                    // else select it
                        {
                            SQUAWK("\t%s::HandleMouseClick(): selected intrinsic object\n", GP_Cq);
                            figr->_set_selectionState(ev, kODTrue);     // tell it is selected
                            sList->AddLast(ev, figr);                   // add it to the selected list
                        }   // else: already selected?

                        SQUAWK("\t%s::HandleMouseClick(): recalculating selected figure shape\n", GP_Cq);
                        somSelf->CreateSelectionBorderShapes(ev, figr); // recalculate borders
                        if (figr != _fCurrObj)
                        {
                            SQUAWK("\t%s::HandleMouseClick(): recalculating current figure shape\n", GP_Cq);
                            somSelf->CreateSelectionBorderShapes(ev, _fCurrObj);
                        }
                        eventHandled = kODTrue;                 // click handled locally
                        somSelf->Reset(ev);                     // reset all editor state to defaults
                        somSelf->HandleRefresh(ev);             // refresh the whole content area
                        break;                                  // don't keep looking

                    }   // if: contains point?
                    else                                        // else it does not contain this point
                        SQUAWK("\t%s::HandleMouseClick(): not this one...\n", GP_Cq);
                }   // if: intrinsic content?
                else                                            // else it is embedded content
                {
                    SQUAWK("\t%s::HandleMouseClick(): selected item was not intrinsic\n", GP_Cq);
                    eventHandled = kODFalse;                // click not handled locally, pass it on
                }   // else: intrinsic content?
            }   // for: each embedded object
            break;  // end of case: CMD(GrafPartSelect)

        // INTRINSIC EMBED (ADD)
        case CMD(GrafPartAdd):
            if (_fCurrObjType == COBJ_GRAFPART_POIN)
            {
                // create and cache the point object with current point
                SQUAWK("\t%s::HandleMouseClick(): state: kODCommandGrafPartAdd, kODBeginAction\n", GP_Cq);
                GetPoint(ev, facet, event, &_fPt);          // get the current point
                ( (ContentGrafPartFigr *) _fCurrObj )
                    ->Initialize(ev, frame, &_fPt);         // set up new object with origin point
                ( (ContentGrafPartFigr *) _fCurrObj )
                    ->AdjustBoundingRect(ev);               // update object's boundry

                // set local handling flags
                _fAction     = kODCommandGrafPartSelect;    // Action: reset to Select (default)
                _fActionType = kODSingleAction;             // ActionType: reset to default
                eventHandled = kODTrue;                     // the MouseUp was handled locally, do not pass on

                // redraw: shape handling not needed because the whole frame will be invalidated by HandleRefresh()
                somSelf->Reset(ev);                         // reset all editor state to defaults
                somSelf->HandleRefresh(ev);                 // refresh the whole content area
            }   // if add point
            else
                SQUAWK("\t%s::HandleMouseClick() does not handle kODCommandGrafPartAdd for ContentObjectTypes other than Point\n", GP_Cq);
            break;

        // unknown action
        default:
            SQUAWK("\t%s::HandleMouseClick(): undefined Action\n", GP_Cq);
            eventHandled = kODFalse;    // this state is undefined in our context, pass it on

    }   // switch: Action

    // termination: if click not handled locally, pass on to parent
    if (!eventHandled)
    {
        SQUAWK("< Leaving %s::HandleMouseClick(), calling parent\n", GP_Cq);
        return (parent_HandleMouseClick( somSelf,
                                                                ev,
                                                                event,
                                                                frame,
                                                                facet,
                                                                eventInfo ) );
    }   // if !eventHandled
    else
    {
        SQUAWK("< Leaving %s::HandleMouseClick(), handled locally\n", GP_Cq);
        return(eventHandled);           // should always be true here
    }   // else !eventHandled
}   // HandleMouseClick()


// -------------------------------------------------------------------------
// GrafPart --> DrawContents
//
//     DrawContents method, part of Draw method
//         with DrawSelectionBorder (which is not overridden)
//
//     -> public override method
//     -> does NOT call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(DrawContents)(   GP_C    *somSelf,
                                                        Environment *ev,
                                                        ODFacet     *facet,
                                                        ODShape     *invalidShape )
{
    SQUAWK("> Invoked %s::DrawContents()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(DrawContents) );

    try
    {
        // Get the frame for this facet
        ODFrame* displayFrame = facet->GetFrame(ev);

        // Get the frame bounding rectangle and convert to Window's rectangle
        ODRect rect;
        TempODShape shape = displayFrame->AcquireFrameShape(ev, facet->GetCanvas(ev));

        shape->GetBoundingBox(ev, &rect);
        Rect frameRect;

        // Define the drawing context
        HDraw hDraw;

        // Use the focuslib code to set up transforms and clipping
        CFocus Focus(facet, invalidShape, &hDraw);

#if defined(_PLATFORM_WIN32_)
        SetRect(&frameRect, FixedToInt(rect.left),
                            FixedToInt(rect.top),
                            FixedToInt(rect.right),
                            FixedToInt(rect.bottom));
#elif defined(_PLATFORM_OS2_)
        WinSetRect( WinQueryAnchorBlock(HWND_DESKTOP),
                    &frameRect, FixedToInt(rect.left),
                                FixedToInt(rect.bottom),
                                FixedToInt(rect.right),
                                FixedToInt(rect.top));
#endif // _PLATFORM_???_

        // fill the backgound
#if defined(_PLATFORM_WIN32_)
        SQUAWK("\t%s::DrawContents(): Filling background for WIN32\n", GP_Cq);
        // Create a solid brush
        HBRUSH hbr = CreateSolidBrush (somSelf->GetBackgroundColor(ev));

        // Fill the rectangle with the brush
        FillRect (hDraw, &frameRect, hbr);

        // Get rid of the brush
        DeleteObject (hbr);
#elif defined(_PLATFORM_OS2_)
        SQUAWK("\t%s::DrawContents(): Filling background for OS2\n", GP_Cq);
        POINTL orig = {0, 0};
        POINTL exnt = {frameRect.xRight, frameRect.yTop};
        GpiCreateLogColorTable (hDraw, 0L, LCOLF_RGB, 0L, 0L, 0L);
        GpiSetColor(hDraw, somSelf->GetBackgroundColor(ev));
        GpiMove(hDraw, &orig);
        GpiBox(hDraw, DRO_FILL, &exnt, 0, 0);
#endif // _PLATFORM_???_


        // place label on window
#if defined(_PLATFORM_WIN32_) && defined(ODDebug) && 0
        SQUAWK("\t%s::DrawContents(): Labelling background for WIN32\n", GP_Cq);

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
        hOldFont = SelectObject(hDraw, hFont);

        // Write some text on the screen using a transparent background and white text
        SetBkMode(hDraw, TRANSPARENT);
        SetTextColor(hDraw, 0x00FFFFFF);

        char *text = kGrafPartDisplayName;
        DrawText(hDraw,
                 text,
                 strlen(text),
                 &frameRect,
                 DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // Remove the temporary font
        SelectObject(hDraw, hOldFont);
        DeleteObject(hFont);
#elif defined(_PLATFORM_OS2_) && defined(ODDebug)
        SQUAWK("\t%s::DrawContents(): No defined background labelling for OS2\n", GP_Cq);
#endif // _PLATFORM_???_ & ODDebug, label on background


        // Tell my contents to draw
        ALinkedList*    eList = somSelf->GetEmbeddedObjects(ev);    // Get the list of embedded objects
        ALink*          eIter;                              // declare an iterator on the linked list
        ContentGrafPartFigr*    figr;                       // declare a buffer for a intrinsic object
        ODULong                 coType;                     // declare a buffer for a intrinsic type

        for(eIter = eList->First(ev);                       // for each Content Object in the list
            eIter->Content(ev);
            eIter = eIter->Next(ev) )
        {
            figr = (ContentGrafPartFigr *) eIter->Content(ev);  // treat it as intrinsic object
            coType = figr->_get_objType(ev);                    // store the specific type

            if ( ( coType >  COBJ_GRAFPART_FIGR ) &&            // if it is GP-intrinsic content
                 ( coType <= COBJ_GRAFPART_LAST ) )
            {
                figr->Draw(ev, hDraw);                          // explicitly send Draw message
            }   // if: GP-intrinsic?
            else
            {
                SQUAWK("\t%s::DrawContents(): unrecognized content object type: %d\n", GP_Cq, coType);
            }   // else: GP-intrinsic?
        }   // for: each embedded object
    }   // try
    catch(...)
    {
        SQUAWK("\t%s::DrawContents(): CAUGHT EXCEPTION, returning False\n", GP_Cq);
        return kODTrue;
    }

    SQUAWK("< Leaving %s::DrawContents(): returning True\n", GP_Cq);
    return kODTrue;
}  // GrafPartDrawContents()


// -------------------------------------------------------------------------
// GrafPart --> ReadKindInfo
//
//      Reads kind info from the storage unit.
//
//     -> public override method
//     -> does NOT call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(ReadKindInfo) (   GP_C        *somSelf,
                                                        Environment     *ev,
                                                        ODStorageUnit   *fromSU )
{
    SQUAWK("> Invoked %s::ReadKindInfo()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq, GP_Pq(ReadKindInfo) );

    ODBoolean bExists = kODFalse;

    try
    {
        bExists = fromSU->Exists (ev, kODPropContents, kGrafPartPartKind, 0);
        if (!bExists) {
          bExists = parent_ReadKindInfo(somSelf, ev, fromSU);
        }
    }
    catch(...)
    {
        SQUAWK("\t%s::ReadKindInfo(): CAUGHT EXCEPTION\n", GP_Cq);
    }

    SQUAWK("< Leaving %s::ReadKindInfo()\n", GP_Cq);
    return bExists;
}   // ReadKindInfo()


// -------------------------------------------------------------------------
// GrafPart --> WriteKindInfo
//
//     Writes kind into the storage unit.
//
//     -> public override method
//     -> does NOT call parent
// -------------------------------------------------------------------------

SOM_Scope   void    SOMLINK     GP_P(WriteKindInfo) (  GP_C        *somSelf,
                                                        Environment     *ev,
                                                        ODStorageUnit   *toSU )
{
    SQUAWK("> Invoked %s::WriteKindInfo()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq, GP_Pq(WriteKindInfo) );

    try
     {
        // write the part kind info attribute
        ODSUAddPropValue(ev, toSU, kODPropContents, kGrafPartPartKind);

#if defined(_PLATFORM_OS2_)
//      somSelf->StorageUnitSetValue(toSU, ev, sizeof(somSelf), somSelf);
#endif  // _PLATFORM_OS2_


        parent_WriteKindInfo(somSelf, ev, toSU);

    }
    catch(...)
    {
        SQUAWK("\t%s::WriteKindInfo(): CAUGHT EXCEPTION\n", GP_Cq);
    }

    SQUAWK("< Leaving %s::WriteKindInfo()\n", GP_Cq);
    return;
}   // WriteKindInfo()


// -------------------------------------------------------------------------
// ContentGrafPartLine --> GetContentObjectFromObjType
//
//      Override ContentObject::GetContentObjectFromObjType to create dummy
//          Line object for CloneInto
//
//     -> public override method
//     -> calls parent last, if not handled locally
// -------------------------------------------------------------------------
SOM_Scope   void    SOMLINK GP_P(GetContentObjectFromObjType) (    GP_C *somSelf,
                                                                    Environment*    ev,
                                                                    COType          objType,
                                                                    ContentObject** contentObject )
{
    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(GetContentObjectFromObjType) );

    SQUAWK("> Invoked %s::GrafPartGetContentObjectFromObjType()\n", GP_Cq);

    switch ( objType )
    {

        // is type intrinsic Point?
        case COBJ_GRAFPART_POIN:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Poin\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartPoin();
            break;

        // is type intrinsic Line?
        case COBJ_GRAFPART_LINE:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Line\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartLine();
            break;

        // is type intrinsic Rectangle?
        case COBJ_GRAFPART_RECT:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Rect\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartRect();
            break;

        // is type intrinsic Text?
        case COBJ_GRAFPART_TEXT:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Text\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartText();
            break;


/*  Handling clauses for additional figure types, uncomment as they are implemented
        // is type intrinsic Ellipse?
        case COBJ_GRAFPART_ELLI:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Elli\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartElli();
            break;

        // is type intrinsic Circle?
        case COBJ_GRAFPART_CIRC:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Circ\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartCirc();
            break;

        // is type intrinsic Polyline?
        case COBJ_GRAFPART_PLIN:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Plin\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartPlin();
            break;

        // is type intrinsic Polygon?
        case COBJ_GRAFPART_PGON:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Pgon\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartPgon();
            break;

        // is type intrinsic Freehand?
        case COBJ_GRAFPART_FREE:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Free\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartFree();
            break;

        // is type intrinsic Text?
        case COBJ_GRAFPART_TEXT:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Text\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartText();
            break;

        // is type intrinsic Image?
        case COBJ_GRAFPART_IMAG:
            SQUAWK("\t%s::GrafPartGetContentObjectFromObjType(): creating new Imag\n", GP_Cq);
            *contentObject = (ContentObject*) new ContentGrafPartImag();
            break;
*/

        // none of the above, pass on to parent
        default:
            parent_GetContentObjectFromObjType(  somSelf,
                                                                        ev,
                                                                        objType,
                                                                        contentObject);
            break;
    }   // switch: which ContentObject type?
    SQUAWK("< Leaving %s::GrafPartGetContentObjectFromObjType()\n", GP_Cq);
    return;
}   // GrafPartGetContentObjectFromObjType()


// -------------------------------------------------------------------------
// GrafPart --> MoveSelectionToFront
//
//     Wraps a call to Parent's MoveSelectionToFront().
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------

SOM_Scope   void    SOMLINK GP_P(MoveSelectionToFront) (   GP_C *somSelf,
                                                            Environment*    ev )
{
    SQUAWK("> Invoked %s::MoveSelectionToFront()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq, GP_Pq(MoveSelectionToFront) );

    try
    {
        parent_MoveSelectionToFront( somSelf, ev);   // call parent
        somSelf->HandleRefresh(ev);                                         // refresh the screen
    }
    catch(...)
    {
        SQUAWK("\t%s::MoveSelectionToFront(): CAUGHT EXCEPTION\n", GP_Cq);
    }

    SQUAWK("< Leaving %s::MoveSelectionToFront()\n", GP_Cq);
    return;
}   // MoveSelectionToFront()


// -------------------------------------------------------------------------
// GrafPart --> MoveSelectionToBack
//
//     Wraps a call to Parent's MoveSelectionToBack().
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------

SOM_Scope   void    SOMLINK GP_P(MoveSelectionToBack) (    GP_C *somSelf,
                                                            Environment*    ev )
{
    SQUAWK("> Invoked %s::MoveSelectionToBack()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq, GP_Pq(MoveSelectionToBack) );

    try
    {
        parent_MoveSelectionToBack( somSelf, ev);    // call parent
        somSelf->HandleRefresh(ev);                                         // refresh the screen
    }
    catch(...)
    {
        SQUAWK("\t%s::MoveSelectionToBack(): CAUGHT EXCEPTION\n", GP_Cq);
    }

    SQUAWK("< Leaving %s::MoveSelectionToBack()\n", GP_Cq);
    return;
}   // MoveSelectionToBack()


// -------------------------------------------------------------------------
// GrafPart --> PasteSelection
//
//     Wraps a call to Parent's PasteSelection().
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------

SOM_Scope   void    SOMLINK GP_P(PasteSelection) ( GP_C *somSelf,
                                                    Environment*    ev,
                                                    ODFacet*        facet,
                                                    ODPoint*        point )
{
    SQUAWK("> Invoked %s::PasteSelection()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq, GP_Pq(PasteSelection) );

    try
    {
        parent_PasteSelection( somSelf, ev, facet, point);   // call parent
        somSelf->HandleRefresh(ev);                                         // refresh the screen
    }
    catch(...)
    {
        SQUAWK("\t%s::PasteSelection(): CAUGHT EXCEPTION\n", GP_Cq);
    }

    SQUAWK("< Leaving %s::PasteSelection()\n", GP_Cq);
    return;
}   // PasteSelection()


// =========================================================================
//
//     Public local methods: GrafPart
//
// =========================================================================

// -------------------------------------------------------------------------
// GrafPart --> HandleRefresh
//
//      Event handler: menu selection "Refresh screen", invalidate all frames
//          associated with this instance of GrafPart
//
//     -> public local method
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(HandleRefresh) (  GP_C *somSelf,
                                                        Environment*    ev )
{
    SQUAWK("> Invoked %s::HandleRefresh()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(HandleRefresh) );

    ALinkedList* frameList = somSelf->GetDisplayFrames(ev); // get the list of display frames
    ALink*       frameIter;                                 // define an iterator on the frame list

    try
    {
        for(frameIter = frameList->First(ev);   // for each object in the frame list
            frameIter->Content(ev);
            frameIter = frameIter->Next(ev) )
        {
            // invalidate each frame to make it redraw everything
            ( (ODFrame*) (frameIter->Content(ev) ) )->Invalidate(ev, kODNULL, kODNULL);
        }   // for: each frame link
    }       // try
    catch(...)
    {
        SQUAWK("\t%s::HandleRefresh(): CAUGHT EXCEPTION, returning False\n", GP_Cq);
        return( kODTrue );
    }

    SQUAWK("< Leaving %s::HandleRefresh(): returning True\n", GP_Cq);
    return( kODTrue );
}   // HandleRefresh()


// =========================================================================
//
//     Private local methods: GrafPart
//
// =========================================================================

// -------------------------------------------------------------------------
// GrafPart --> Reset
//
//      Terminate current action and reset editor state to default
//
//      -> private local method
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(Reset) (  GP_C *somSelf,
                                                Environment*    ev )
{
    SQUAWK("> Invoked %s::Reset()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(Reset) );

    try
    {
        // check that we're not in the middle of an action
        if ( _fAction==CMD(GrafPartAdd) )
        {
            SQUAWK("\t%s::Reset(): terminating Add action for type: %d\n", GP_Cq, _fCurrObjType);
            _fCurrShape->Release(ev);                               // delete temp shapes for rubberbanding
            _fTempShape->Release(ev);                               // delete temp shapes for rubberbanding
            ( (ContentGrafPartFigr *)_fCurrObj )
                    ->Uninitialize(ev);                             // unset up object in progrss
            delete _fCurrObj;                                       // deallocate the object
        }

        // reset all local instance variables to default values
        _fAction      = kODCommandGrafPartSelect;   // Action: Select (default)
        _fActionType  = kODSingleAction;            // ActionType: single action
        _fCurrObj     = kODNULL;                    // reset current object buffer in progress
        _fCurrObjType = kODNULL;                    // reset current object type buffer in progress
        _fCurrShape   = kODNULL;                    // reset current object shape buffer
        _fTempShape   = kODNULL;                    // reset current object shape buffer
        memset(&_fPt, 0, sizeof(ODPoint) );         // zero out temp point

    }       // try
    catch(...)
    {
        SQUAWK("\t%s::Reset(): CAUGHT EXCEPTION, returning False\n", GP_Cq);
        return( kODTrue );
    }

    SQUAWK("< Leaving %s::Reset(): returning True\n", GP_Cq);
    return( kODTrue );
}   // Reset()


// -------------------------------------------------------------------------
// GrafPart --> AddIntrinsic
//
//     Create and cache a new intrinsic object
//
//     -> private local method
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(AddIntrinsic)  (   GP_C        *somSelf,
                                                        Environment *ev,
                                                        ODFrame     *frame,
                                                        COType      cotype )
{
    SQUAWK("> Invoked %s::AddIntrinsic()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(AddIntrinsic) );

    SQUAWK("\t%s::AddIntrinsic(): received  Frame: %lX\n", GP_Cq, frame);
    SQUAWK("\t%s::AddIntrinsic(): received COType: %d\n", GP_Cq, cotype);


    try
    {
        // create and cache a new intrinsic object
        _fAction      = CMD(GrafPartAdd);                       // Action: add and intrinsic object
        _fActionType  = kODBeginAction;                         // begin multipart action
        _fCurrObjType = cotype;                                 // cache the new object's COtype
        somSelf->GetContentObjectFromObjType(ev, cotype, &_fCurrObj);   // create a new object
    }   // try

    catch(...)
    {
        SQUAWK("< Leaving %s::AddIntrinsic(): CAUGHT EXCEPTION, returning False\n", GP_Cq);
        return( kODFalse );
    }   // catch

    SQUAWK("< Leaving %s::AddIntrinsic(): returning True\n", GP_Cq);
    return( kODTrue );
}   // AddIntrinsic()


// -------------------------------------------------------------------------
// GrafPart --> UpdateIntrinsic
//
//     Update a new intrinsic object in progress with a new point
//
//     -> private local method
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK GP_P(UpdateIntrinsic) (    GP_C *somSelf,
                                                            Environment*    ev,
                                                            ODFrame*        frame,
                                                            ODPoint*        point )
{
    SQUAWK("> Invoked %s::UpdateIntrinsic()\n", GP_Cq);

    GP_P(Data) *somThis = GP_P(GetData) (somSelf);
    GP_P(MethodDebug) (GP_Cq,GP_Pq(UpdateIntrinsic) );

    SQUAWK("\t%s::UpdateIntrinsic(): received Frame: %lX\n", GP_Cq, frame);
    SQUAWK("\t%s::UpdateIntrinsic(): received Point: %d,%d\n", GP_Cq, ODFixedToInt(point->x), ODFixedToInt(point->y) );

    try
    {
        // pass the point to the intrinsic object
        ( (ContentGrafPartFigr *) _fCurrObj )->Update(ev, point);       // update object with point
        ( (ContentGrafPartFigr *) _fCurrObj )->AdjustBoundingRect(ev);  // update object's boundry
    }   // try

    catch(...)
    {
        SQUAWK("< Leaving %s::UpdateIntrinsic(): CAUGHT EXCEPTION, returning False\n", GP_Cq);
        return( kODFalse );
    }   // catch

    SQUAWK("< Leaving %s::UpdateIntrinsic(): returning True\n", GP_Cq);
    return( kODTrue );
}   // UpdateIntrinsic()


// =========================================================================
// End of file: iodgraph.cpp
// =========================================================================
