/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: oddynamicpart
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
/* @(#) 1.10 com/src/samples/dynamicp/bdraw/draw.c, oddynamicpart, od96os2, odos29712d 2/18/97 13:53:57 [3/21/97 17:44:35]
*******************************************************************
** Name: void Draw
**
** Description:  Render the part's contents on the screen.
**               This method currently draws entire picture.  It
**               should be modified to only draw invalid pieces.
**
*******************************************************************
*/

try {
  int contentExtent;   // use this to hide differences between OS/2 and Windows origins
  #ifdef _PLATFORM_OS2_
    contentExtent = 0; // OS/2 origin is bottom left
  #elif defined(_PLATFORM_WIN32_)
    contentExtent = drawYdimension; // Windows origin is (strangely) top right
  #endif
  try {

    // Disable printing
#ifdef _PLATFORM_OS2_
   if (facet->GetCanvas(ev)->HasPlatformPrintJob(ev,kODPM))
#elif defined(_PLATFORM_WIN32_)
   if (facet->GetCanvas(ev)->HasPlatformPrintJob(ev,kODWin32))
#endif
       printf("Printing\n");//nd
//nd   return;

    /////////////////////////////////////////////////////////////
    // If displayed in a root window, blank out old position
    // If the part is a root part, we should blank out the
    // area around the current used area.
    if (facet->GetFrame(ev)->IsRoot(ev)) {

      ODShape *shape = facet->GetFrame(ev)->AcquireFrameShape(ev, kODNULL);

      ODTransform *contentXform = facet->AcquireWindowContentTransform(ev, facet->GetCanvas(ev));
      ODTransform *frameXform = facet->AcquireWindowFrameTransform(ev, facet->GetCanvas(ev));

      ODRect trect     = {0, ODIntToFixed(drawYdimension-contentExtent),
                          ODIntToFixed(drawXdimension), ODIntToFixed(contentExtent)};

      ODShape *figFrameShape = shape->Copy(ev);
      figFrameShape->Transform(ev, frameXform);
      ODShape *figFigShape = shape->NewShape(ev);
      figFigShape->SetRectangle(ev, &trect);
      if (contentXform) {
        figFigShape->Transform(ev, contentXform);
        figFrameShape->Subtract(ev, figFigShape);
#ifdef _PLATFORM_WIN32_
        figFrameShape->InverseTransform(ev, contentXform);
#endif
        contentXform->Release(ev);
      } /* endif */
      frameXform->Release(ev);
      try {
        HPS hps;
        CFocus f(facet, invalidShape, &hps);

        // overdraw current (old) position
        IPresSpaceHandle DrawHps(hps);
        IGraphicContext DrawConText(DrawHps);

        ODHighlight highlight = facet->GetHighlight(ev);
        if (highlight==kODNoHighlight) {
          DrawConText.setBackgroundColor(_BackColor);
        } else {
          if (highlight==kODFullHighlight) {
            DrawConText.setBackgroundColor(_TextColor);
          } else {
            if (highlight==kODDimHighlight) {
              DrawConText.setBackgroundColor(_BackColor);
            } /* endif */
          } /* endif */
        } /* endif */
        DrawConText.setPenColor(DrawConText.backgroundColor());
        DrawConText.setFillColor(DrawConText.backgroundColor());

        IRegionHandle drawHandle = figFrameShape->GetRegion(ev);
        IGRegion DrawRegion = drawHandle;
        DrawRegion.drawOn(DrawConText);
      } catch (IException &exc) {
         reportIException(exc);
      } catch (...) {
         reportAnyException(ev);
      } /* end try */

      shape->Release(ev);
      figFrameShape->Release(ev);
      figFigShape->Release(ev);
    } /* endif isRoot */
  } catch (IException &exc) {
     reportIException(exc);
  } catch (...) {
     reportAnyException(ev);
  }/* end try */

  // Now draw the figure
  try {

    HPS hps;
    CFocus f(facet, invalidShape, &hps);     // Set up drawing environment

    // Using the Integer Constuctor with the HPS from CFocus
    IPresSpaceHandle DrawHps(hps);

    // Using the IPresSpaceHandle Constructor to create my Graphic Context
    IGraphicContext DrawConText(DrawHps);

    long FontSize = drawYdimension / 20;
    _Font->setPointSize(FontSize);
    _Font->useBitmapOnly(false);
    _Font->useNonPropOnly(false);
    _Font->useVectorOnly(true);
    _Message->setFont(*_Font);

    // Creation of an IGRectange object representing the text box at the bottom

    IRectangle DrawBotRect(0,                        //left
                           contentExtent,            //bottom
                           drawXdimension+1,         //right
#ifdef _PLATFORM_OS2_
                           abs(contentExtent  - (_Font->maxCharHeight()+_Font->maxDescender()))+7
#elif defined(_PLATFORM_WIN32_)
                           abs(contentExtent  -  _Font->maxCharHeight()   )
#endif
                          );
    IGRectangle GDrawBotRect(DrawBotRect);

    IRectangle DrawTopRect(DrawBotRect.left(),
#ifdef _PLATFORM_OS2_
                           DrawBotRect.top(),
#else
                           DrawBotRect.bottom()+1,
#endif
                           DrawBotRect.right(),
                           drawYdimension - contentExtent);

    // draw the figure

    // Draw the bitmap
    DrawConText.setBackgroundMixMode(IGraphicBundle::backLeaveAlone);
    DrawConText.setMixMode(IGraphicBundle::overPaint);


    // Setting the Background and Fill color for the Graphic Context

    ODHighlight highlight = facet->GetHighlight(ev);
    long rasterOperation;
    if (highlight==kODNoHighlight) {
      DrawConText.setBackgroundColor(_BackColor);
      DrawConText.setPenColor(_TextColor);
      rasterOperation = IGBitmap::normal;
    } else {
      if (highlight==kODFullHighlight) {
        DrawConText.setBackgroundColor(_TextColor);
        DrawConText.setPenColor(_BackColor);
        rasterOperation = IGBitmap::invert;
      } else {
        if (highlight==kODDimHighlight) {
          DrawConText.setBackgroundColor(_BackColor);
          DrawConText.setPenColor(_TextColor);
          rasterOperation = IGBitmap::normal;
        } /* endif */
      } /* endif */
    } /* endif */
    DrawConText.setDrawOperation(IGraphicBundle::fill);

    try {
#ifdef _PLATFORM_OS2_
      if (facet->GetCanvas(ev)->HasPlatformPrintJob(ev,kODPM))
#elif defined(_PLATFORM_WIN32_)
      if (facet->GetCanvas(ev)->HasPlatformPrintJob(ev,kODWin32))
#endif
      {
        // OpenClass doesn't print bitmaps currently, so we must resort to the native APIs
#ifdef _PLATFORM_OS2_
        HBITMAP hbm = GpiLoadBitmap(hps,(IModuleHandle::Value)_Resources->handle(),
                                    ODBMP,0,0);
        if (hbm) {
          POINTL points[] = { {DrawTopRect.left(),  DrawTopRect.bottom()},
                              {DrawTopRect.right(), DrawTopRect.top()},
                              {0, 0},
                              {_ODBitmap->size().width(), _ODBitmap->size().height()}
                            };
          LONG rc =
          GpiWCBitBlt(hps, hbm,
                      4, points,
                      ROP_SRCCOPY, BBO_IGNORE);
        } /* endif */
#elif defined(_PLATFORM_WIN32_)
        BITMAP bm;
        HPS hMemDC;
        RECT rect;
        HBITMAP hbm = 0;
        string  ModulePathName = kDynamicPartFileName;
        // loading from a resource loses colors, so load from a file
        char bitmapname[256];
        bitmapname[0] = '\0';
        _searchenv("ioddynam.bmp", "PATH", bitmapname);
        if (bitmapname[0] != '\0') {
          hbm = LoadImage(NULL, bitmapname, IMAGE_BITMAP,0,0,
                          LR_LOADFROMFILE | LR_COLOR );
        } /* endif */
        if (hbm == NULL) {
          // didn't load from file
          hbm = LoadBitmap((IModuleHandle::Value)_Resources->handle(),
                           MAKEINTRESOURCE(ODBMP));
        } /* endif */
        GetObject( hbm, sizeof(BITMAP), &bm);
        hMemDC = CreateCompatibleDC( hps);
        SelectObject (hMemDC, hbm);
        SetStretchBltMode(hps, STRETCH_DELETESCANS);
        BOOL rc =
        StretchBlt(hps, 0, 0, DrawTopRect.width(), DrawTopRect.height(),
                   hMemDC, 0, 0, bm.bmWidth, bm.bmHeight,
                   SRCCOPY );
        if (!rc) {
          DWORD lastErr = GetLastError();
          printf("LastError=%x\n",lastErr);
        } else {
          printf("StretchBlt successful\n");
        } /* endif */
        DeleteDC(hMemDC);
        DeleteObject(hbm);
#endif
      } else {
        _ODBitmap->drawOn(DrawConText,
                          DrawTopRect.bottomLeft(),
                          DrawTopRect.topRight(),
                          IPoint(0, 0),
                          _ODBitmap->size(),
                          rasterOperation);
      } /* endif */
    } catch (IException &exc) {
        reportIException(exc);
    } /* end try */
    if (highlight==kODDimHighlight) {
      DrawConText.setFillPattern(IGraphicBundle::halftone);
      DrawConText.setFillColor(_BackColor);
      IGRectangle GDrawTopRect(DrawTopRect);
      GDrawTopRect.drawOn(DrawConText);
      DrawConText.setFillPattern(DrawConText.defaultFillPattern());
    } /* endif */

    DrawConText.setFillColor(DrawConText.backgroundColor());
    DrawConText.setBackgroundMixMode(IGraphicBundle::backOverPaint);
    DrawConText.setMixMode(IGraphicBundle::overPaint);
    GDrawBotRect.drawOn(DrawConText);

    _Message->setClippingRect(DrawBotRect);

    IPoint Msg1Pos(_ScrollPos,
#ifdef _PLATFORM_OS2_
                   DrawBotRect.bottom() + _Font->maxDescender() + _Font->externalLeading() +0
#elif defined(_PLATFORM_WIN32_)
                   DrawBotRect.top() - _Font->maxCharHeight()
#endif
                  );
    _Message->moveTo(Msg1Pos);
    _Message->drawOn(DrawConText);

  } catch (IException &exc) {
      reportIException(exc);
  } catch (...) {
      reportAnyException(ev);
  } /* end try */
} catch (IException &exc) {
    reportIException(exc);
} catch (...) {
    reportAnyException(ev);
} /* end try */
