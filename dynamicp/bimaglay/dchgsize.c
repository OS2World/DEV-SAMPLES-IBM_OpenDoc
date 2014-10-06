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
/* @(#) 1.4 com/src/samples/dynamicp/bimaglay/dchgsize.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:43 (97/02/18 13:54:11)
*******************************************************************
** Name: void AdjustSize
**
** Description:  Frame negotiation -- This part preferrs to be
**               rectangular, so try to square up the frame
**               whenever a new shape is requested.  Save
**               frame shape related information in the instance
**               data for use in rendering the part.
**
*******************************************************************
*/
try {
   ODRect frameRect;
   ODCanvas* canvas = facet->GetCanvas(ev);
   ODShape* frameShape;
   /*
    *  Negotiate the display frame size with its containing part.
    */
   frameShape = frame->AcquireFrameShape(ev, canvas);

   if (frame->IsRoot(ev)) {
      // This is a root part, so use the frame shape as-is
      //frameShape = frame->AcquireFrameShape(ev, canvas);
   } else {
      // not a root part, so
      // calculate the preferred frame shape
      if (_fFrameNegotiated == kODFalse) {
          // determine our preferred initial shape
          const int InitWidth  = 200;
          const int InitHeight = 200;

          //
          //  Set up initial Dynamic Part size using PM coordinates
          //  and place in a new OpenDoc shape object.
          //

         int contentExtent;   // use this to hide differences between OS/2 and Windows origins
          #ifdef _PLATFORM_OS2_
            contentExtent = 0; // OS/2 origin is bottom left
          #elif defined(_PLATFORM_WIN32_)
            contentExtent = InitHeight; // Windows origin is (strangely) top right
          #endif
          frameRect.left   = 0;
          frameRect.top    = ODIntToFixed(InitHeight-contentExtent);
          frameRect.right  = ODIntToFixed(InitWidth);
          frameRect.bottom = ODIntToFixed(contentExtent);

          //
          //  Set frame negotiated to True.  If the part was instantiated
          //  either from its template or as a root part this flag was false.
          //
          _fFrameNegotiated = kODTrue;
      } else {
          // shape has changed, so square the frame
          //frameShape = frame->AcquireFrameShape(ev, canvas);
          frameShape->GetBoundingBox(ev, &frameRect);
          if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
          //frameShape->Release(ev);

          long cxFrame = frameRect.right - frameRect.left;
          long cyFrame = abs(frameRect.top - frameRect.bottom);
          if (cxFrame < cyFrame)
#ifdef _PLATFORM_OS2_
             frameRect.top = frameRect.bottom + cxFrame;
#elif defined(_PLATFORM_WIN32_)
             frameRect.bottom = frameRect.top + cxFrame;
#endif
          else if (cxFrame > cyFrame)
             frameRect.right = frameRect.left  + cyFrame;

      }
      // request the new frame shape //
      if (frameShape!=kODNULL) {
        ODRect orgFrameRect;
        frameShape->GetBoundingBox(ev, &orgFrameRect);
        frameShape->Release(ev);
        // but only request new shape if the old shape is not already square
        if (orgFrameRect.right-orgFrameRect.left != abs(orgFrameRect.top-orgFrameRect.bottom)) {
          ODShape *requestedShape = frame->CreateShape(ev);
          requestedShape->SetRectangle(ev, &frameRect);
            if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
          frameShape = frame->RequestFrameShape(ev, requestedShape, canvas);
            if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
        } /* endif */
      } /* endif */
   } /* endif */

   somSelf->CalcNewShape(ev, frame);
   if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}

} catch (IException &exc) {
   reportIException(exc);
} catch (...) {
   reportAnyException(ev);
} /* end try */

