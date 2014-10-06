// @(#) 1.3 com/src/samples/basecntr/iodbcvwt.cpp, odbasepart, od96os2, odos29712d 3/17/97 20:15:34 [3/21/97 17:51:34]

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
//
//====END_GENERATED_PROLOG========================================
//

//----------------------------------------------------------------------------- 
//  IODBCVWT.CPP
//  This file contains methods for displaying the view types of BaseContainer.
//----------------------------------------------------------------------------- 

// -------------------------------------------------------------------------
// BaseContainer --> AdjustViewTypeShapes
//
//      Adjusts the frame shape of the part according to the viewType.
//      Keeps track of the last frame shape, to restore it when changing
//      from icon to frame view.
//
//      -> This method is a private method of BaseContainer
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK BaseContainerAdjustViewTypeShapes(BaseContainer *somSelf,
                                                          Environment *ev,
                                                          ODFrame* frame)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerAdjustViewTypeShapes");

    try
    {

      // Do not change frame shape if this is a root frame
      if(frame->IsRoot(ev)) return;

      // Prevent infinite recursion of frame negotiation
      if(_fInFrameNegotiation) return;


      ODRect rect;
      ODTypeToken newViewType = frame->GetViewType(ev);
      TempODShape newShape = frame->CreateShape(ev);

      TempODShape currShape = frame->AcquireFrameShape(ev, kODNULL);
      currShape->GetBoundingBox(ev, &rect);


      if((_fPrevViewType == _fFrameView) && (_fPrevViewType == newViewType))
      {
         // This is an adjustment due to a resize or reconnect.
         // Just store the new frame shape.
         _lastFrameRect = rect;

         // Do not attempt any frame negotiation.
         return;
      }
      somSelf->SetViewTypeRect(ev, newViewType, &rect);
      newShape->SetRectangle(ev, &rect);


      // Get the facet from the frame
      ODFrameFacetIterator  *facetIter = frame->CreateFacetIterator(ev);
      ODFacet *facet = facetIter->First(ev);
      delete facetIter;

      _fInFrameNegotiation = kODTrue;

      // Change the frame shape
      TempODShape finalShape = frame->RequestFrameShape(ev, newShape, kODNULL);

      _fInFrameNegotiation = kODFalse;

      // Container has the last word on frame shape. If the returned frame
      // is not the one requested, reset the lastFrameRect.
      if(!finalShape->IsSameAs(ev, newShape) && (newViewType == _fFrameView))
      {
         finalShape->GetBoundingBox(ev, &_lastFrameRect);
      }

      _fPrevViewType = newViewType;
    }
    catch(ODException _exception)
    {
    }
}


// -------------------------------------------------------------------------
// BaseContainer --> SetViewTypeRect
//
//      Determines the size of the frame's bounding box according to the
//      viewType.
//
//      -> This method is a private method of BaseContainer
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK BaseContainerSetViewTypeRect(BaseContainer *somSelf,
                                                     Environment *ev,
                                                     ODTypeToken viewType,
                                                     ODRect* rect)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerSetViewTypeRect");

    int viewSize;

    if(viewType == _fSmallIconView) {
       viewSize = kODSmallIconSize;
    } else if(viewType == _fLargeIconView) {
       viewSize = kODLargeIconSize;
    } else if(viewType == _fThumbnailView) {
       viewSize = kODThumbnailSize;
    } else {
       *rect = _lastFrameRect;
       return;
    }

    rect->right = IntToFixed((FixedToInt(rect->left)) + viewSize);
#ifdef _PLATFORM_OS2_
    rect->bottom = IntToFixed(0);
    rect->top    = IntToFixed(viewSize);
#else
    rect->bottom = IntToFixed(viewSize);
    rect->top    = IntToFixed(0);
#endif
}


// -------------------------------------------------------------------------
// BaseContainer --> DrawFrame
//
//      Draws our contents in frame view.
//
//      -> This method is a private method of BaseContainer
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK BaseContainerDrawFrame(BaseContainer *somSelf,
                                            Environment *ev,
                                            ODFacet* facet,
                                            ODShape* invalidShape)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDrawFrame");

    // Use the focuslib code to set up transforms and clipping
    somSelf->DrawContents (ev, facet, invalidShape);
    somSelf->DrawSelectionBorder (ev, facet, invalidShape);
}


// -------------------------------------------------------------------------
// BaseContainer --> DrawThumbnail
//
//      Draws a static, scaled version of the current contents to the facet.
//
//      -> This method is a private method of BaseContainer
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK BaseContainerDrawThumbnail(BaseContainer *somSelf,
                                            Environment *ev,
                                            ODFacet* facet,
                                            ODShape* invalidShape)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDrawThumbnail");

    // Not yet implemented
    somSelf->DrawIcon(ev, facet, invalidShape, _fThumbnailView);
}


// -------------------------------------------------------------------------
// BaseContainer --> DrawIcon
//
//      Draws the icon corresponding to the given viewType on the facet.
//
//      -> This method is a private method of BaseContainer
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK BaseContainerDrawIcon(BaseContainer *somSelf,
                                              Environment *ev,
                                              ODFacet* facet,
                                              ODShape* invalidShape,
                                              ODTypeToken viewType)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerDrawIcon");


    HIconView *hIcon;
    short iconSize;

    if(viewType == _fSmallIconView)
    {
      hIcon = &_hSmallIcon;
      iconSize = kODSmallIconSize;
    }
    else
    {
      hIcon = &_hLargeIcon;
      iconSize = kODLargeIconSize;
    }

    HDraw hDraw;
    CFocus f(facet, invalidShape, &hDraw);     // Set up drawing environment

    // Create the icon if it does not exist.
    if(*hIcon == kODNULL) somSelf->CreateIcon(ev, facet, invalidShape, viewType);

#if defined(_PLATFORM_OS2_)||defined(_PLATFORM_WIN32_)
    ODRect iconODRect;
    Rect iconRect;
    TempODShape frameShape = facet->GetFrame(ev)->AcquireFrameShape(ev,kODNULL);
    frameShape->GetBoundingBox(ev, &iconODRect);

#endif
#ifdef _PLATFORM_OS2_
    HAB hab = WinInitialize(0);
    WinSetRect(hab,&iconRect, FixedToInt(iconODRect.left),
                              FixedToInt(iconODRect.bottom),
                              FixedToInt(iconODRect.right),
                              FixedToInt(iconODRect.top));

    ODFixed xscale, yscale;
    Get72DPIToScreenScale( _fSession, &xscale, &yscale);

    Point aPoints[4] = {{iconRect.xLeft,iconRect.yBottom},            // bottom-left of target
                        {iconRect.xRight,iconRect.yTop},              // top-right of target
                        {0,0},                                        // bottom-left of source
                        {FixedToInt(ODFixedMultiply(xscale, IntToFixed(iconSize))), // top-right of source
                         FixedToInt(ODFixedMultiply(yscale, IntToFixed(iconSize)))}};

    LONG lHits = GpiWCBitBlt(hDraw,
                             *hIcon,
                             4,
                             aPoints,
                             ROP_SRCCOPY,
                             BBO_IGNORE);

#elif defined(_PLATFORM_WIN32_)
    SetRect(&iconRect, FixedToInt(iconODRect.left),
                       FixedToInt(iconODRect.top),
                       FixedToInt(iconODRect.right),
                       FixedToInt(iconODRect.bottom));

    // Color white the background to cover places where the icon is transparent

    // Create a solid brush
    HBRUSH hbr = CreateSolidBrush (RGB(255,255,255));

    // Fill the rectangle with the brush
    FillRect (hDraw, &iconRect, hbr);

    // Get rid of the brush
    DeleteObject (hbr);

    BOOL success = DrawIconEx(hDraw,
                              iconRect.left,
                              iconRect.top,
                              *hIcon,
                              iconSize,
                              iconSize,
                              0,
                              NULL,
                              DI_NORMAL);

#elif defined(_PLATFORM_UNIX_)
                                    
    // Get the AIX Window canvas
    ODAIXWindowCanvas *aixwincanvas =
      (ODAIXWindowCanvas *)(facet->GetCanvas(ev)->GetPlatformCanvas(ev, kODAIX));

    // Get the canvas display
    Display *display = aixwincanvas->GetDisplay(ev);

    // Get the canvas widget
    Widget widget = aixwincanvas->GetWidget(ev);

    // Create the icon widget if it doesn't exist
    Arg args[3];
    if(!_iconWidget) {

       XtSetArg(args[0], XmNlabelType, XmPIXMAP);
       XtSetArg(args[1], XmNlabelPixmap, *hIcon);
       XtSetArg(args[2], XmNlabelInsensitivePixmap, *hIcon);

       // Create a label widget on which to display the pixmaps
       _iconWidget = XmCreateLabel( widget, "BCIconWidget", args, 3);

       // Display the pixmap
       XtManageChild(_iconWidget);

    } else {
       // The widget exists already. Just assign the corresponding
       // pixmap to it.
       XtSetArg(args[0], XmNlabelPixmap, *hIcon);
       XtSetArg(args[1], XmNlabelInsensitivePixmap, *hIcon);
       XtSetValues(_iconWidget, args, 2);

    }

#endif
}


// -------------------------------------------------------------------------
// BaseContainer --> CreateIcon
//
//      Creates the icon corresponding to the given viewType. Stores the 
//      resulting icon handle in the corresponding part instance variable.
//
//      -> This method is a private method of BaseContainer
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK BaseContainerCreateIcon(BaseContainer *somSelf,
                                                Environment *ev,
                                                ODFacet* facet,
                                                ODShape* invalidShape,
                                                ODTypeToken viewType)

{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerCreateIcon");

#if defined(_PLATFORM_OS2_) || defined(_PLATFORM_WIN32_)

    somSelf->LoadIconsFromModule(ev,
                                 "iodbasec",
                                 kODIcon);
#else
                                    
    // Get the AIX Window canvas
    ODAIXWindowCanvas *aixwincanvas =
      (ODAIXWindowCanvas *)(facet->GetCanvas(ev)->GetPlatformCanvas(ev, kODAIX));

    // Get the canvas display
    Display *display = aixwincanvas->GetDisplay(ev);

    // Get the screen
    Screen *screen = _fSession->GetWindowState(ev)->GetScreen(ev);

    // Get the default colormap for the screen
    Colormap map = XDefaultColormapOfScreen(screen);

    // Create pixel values for monochrome bitmap
    XColor def, def2;
    Pixel foreground, background;
    Status stat = XAllocNamedColor(display, map, "white" , &def, &def2);
    background = def.pixel;
    stat = XAllocNamedColor(display, map, "black" , &def, &def2);
    foreground = def.pixel;


    // On AIX we may not create both icons at the same time.
    // Create the bitmaps separately because they depend
    // on the window attributes which are different
    // for each viewtype.
    if(viewType ==  _fSmallIconView)
    {
        _hSmallIcon = XmGetPixmap(screen,
                                  "iodbasec.t.pm",
                                  foreground,
                                  background);
    }
    else
    {
       _hLargeIcon = XmGetPixmap(screen,
                                 "iodbasec.m.pm",
                                 foreground,
                                 background);
    }

#endif
}


// -------------------------------------------------------------------------
// BaseContainer --> LoadIconsFromModule
//
//      Creates the small and large icons of the part by loading them from
//      the resource module.
//
//      -> This method is a private method of BaseContainer
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK BaseContainerLoadIconsFromModule(BaseContainer *somSelf,
                                                         Environment *ev,
                                                         string moduleName,
                                                         long iconID)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerLoadIconsFromModule");

#ifdef _PLATFORM_OS2_
    CHAR errBuffer[CCHMAXPATH];
    if(moduleName)
    {
      DosLoadModule(errBuffer,
                    sizeof(errBuffer),
                    moduleName,
                    &_hResModule);
    }

    HPOINTER hptr = WinLoadPointer(HWND_DESKTOP,
                                   _hResModule,
                                   iconID);

    POINTERINFO pi;
    WinQueryPointerInfo( hptr, &pi );
    _hLargeIcon = pi.hbmColor;
    _hSmallIcon = pi.hbmMiniColor;

#elif defined(_PLATFORM_WIN32_)
    if(moduleName)
    {
      _hResModule = LoadLibrary(moduleName);
    }

    _hSmallIcon = LoadImage(_hResModule,
                       MAKEINTRESOURCE(iconID),
                       IMAGE_ICON,
                       kODSmallIconSize,
                       kODSmallIconSize,
                       LR_DEFAULTCOLOR);
    _hLargeIcon = LoadImage(_hResModule,
                       MAKEINTRESOURCE(iconID),
                       IMAGE_ICON,
                       kODLargeIconSize,
                       kODLargeIconSize,
                       LR_DEFAULTCOLOR);
#endif

}


// -------------------------------------------------------------------------
// BaseContainer --> FreeResModule
//
//      Releases the resource module, if its loaded.
//
//      -> This method is a private method of BaseContainer
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK BaseContainerFreeResModule(BaseContainer *somSelf,
                                                   Environment *ev)
{
    BaseContainerData *somThis = BaseContainerGetData(somSelf);
    BaseContainerMethodDebug("BaseContainer","BaseContainerFreeResModule");

    if(_hResModule)
    {
#ifdef _PLATFORM_OS2_
      DosFreeModule(_hResModule);
#elif defined(_PLATFORM_WIN32_)
      FreeLibrary(_hResModule);
#endif
    }
}

