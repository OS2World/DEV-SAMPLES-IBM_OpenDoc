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
/* @(#) 1.7 com/src/samples/dynamicp/bdraw/scroll.c, oddynamicpart, od96os2, odos29712d 2/18/97 13:54:05 [3/21/97 17:44:35]
*******************************************************************
** Name: void ScrollTicker
**
** Description:  Scrolls the message across the bottom of the
**               part by JumpRate pixels.
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

   IODLinkedList *displayFrames = somSelf->GetDisplayFrames(ev);
   IODLink *listItem;
   ODFrame *frame;

   if ( _ScrollPos <= -(ODSLong)(_Font->textWidth((char *)(_Message->text())) ) )
   {
      _ScrollPos = drawXdimension;
   } else {
      _ScrollPos -= _JumpRate;
   }

   // calculate new position for dynamic message
   IPoint newMsgPos = _Message->position();
   newMsgPos.setX(_ScrollPos);

   for (listItem = displayFrames->First(ev);
        (listItem != kODNULL) && (frame = (ODFrame *)(listItem->Content(ev)));
        listItem = listItem->Next(ev))
   {
     // We only have one facet per frame, so get a pointer to it for this frame.
     ODFrameFacetIterator* facets = frame->CreateFacetIterator(ev);
     ODFacet* facet = facets->First(ev);
     delete facets;

     ODShape *shape = kODNULL;
     HPS hps;
     CFocus f(facet, shape, &hps);          // Set up drawing environment

     // Use the Integer Constuctor to create a presentation sapce handle using the hps returned from CFocus
     IPresSpaceHandle DrawHps(hps);

     // Use the IPresSpaceHandle Constructor to create my Graphic Context
     IGraphicContext DrawConText(DrawHps);

     // Setting the Background and Fill color for the Graphic Context to
     // redraw dynamic message

     ODHighlight highlight = facet->GetHighlight(ev);
     if (highlight==kODNoHighlight) {
       DrawConText.setBackgroundColor(_BackColor);
       DrawConText.setPenColor(_TextColor);
     } else {
       if (highlight==kODFullHighlight) {
         DrawConText.setBackgroundColor(_TextColor);
         DrawConText.setPenColor(_BackColor);
       } else {
         if (highlight==kODDimHighlight) {
           DrawConText.setBackgroundColor(_BackColor);
           DrawConText.setPenColor(_TextColor);
         } /* endif */
       } /* endif */
     } /* endif */
     DrawConText.setBackgroundMixMode(IGraphicBundle::backOverPaint);
     DrawConText.setMixMode(IGraphicBundle::overPaint);

     IRectangle DrawBotRect(0,                        //left
                            contentExtent,            //bottom
                            drawXdimension+1,         //right
#ifdef _PLATFORM_OS2_
                            abs(contentExtent  - (_Font->maxCharHeight()+_Font->maxDescender()))+7
#elif defined(_PLATFORM_WIN32_)
                            abs(contentExtent  -  _Font->maxCharHeight()   )
#endif
                           );
     _Message->setClippingRect(DrawBotRect);

     try {
       // draw dynamic message at new position
       _Message->moveTo(newMsgPos);
       _Message->drawOn(DrawConText);
     } catch (IException &exc) {
         reportIException(exc);
     } /* end try */
   } /* endfor */
   // do NOT delete displayFrames;

} catch (IException &exc) {
    reportIException(exc);
} catch (...) {
    reportAnyException(ev);
} /* end try */
