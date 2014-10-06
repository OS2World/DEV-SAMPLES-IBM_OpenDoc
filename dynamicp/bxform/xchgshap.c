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
/* @(#) 1.6 com/src/samples/dynamicp/bxform/xchgshap.c, oddynamicpart, od96os2, odos29712d 11/8/96 17:29:20 [3/21/97 17:44:52]
*******************************************************************
** Name: void CalcNewShape
**
** Description:  Recalculate the active shape and used shape
**               to match the new internal transform.
**
*******************************************************************
*/
try {
   // change used shape

   /* Calculate the Used shape */
   if (!frame->IsRoot(ev)) {

     // find facet and its canvas
     ODFrameFacetIterator* ffiter = frame->CreateFacetIterator(ev);
     ODFacet* facet = ffiter->First(ev);
     ODCanvas* canvas = facet->GetCanvas(ev);

     ODTransform *internalTransform = frame->AcquireInternalTransform(ev, kODNULL);
     ODTransform *shapeTransform = internalTransform->NewTransform(ev);

     ODShape *usedShape = frame->CreateShape(ev);
     if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}

     // set used shape to the draw rectangle.
     ODRect frameRect;
     ODShape *frameShape = frame->AcquireFrameShape(ev, kODNULL);
     frameShape->GetBoundingBox(ev, &frameRect);
     frameShape->Release(ev);
     usedShape->SetRectangle(ev, &frameRect);
     if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}

     // since the internal transform includes a scale down from
     // drawXdimension * drawXdimension, we must scale the shape up to
     // this size before applying the transformation.
     ODPoint scaleFactor;
     scaleFactor.x = (frameRect.right - frameRect.left) / drawXdimension;
     scaleFactor.y = abs(frameRect.top - frameRect.bottom) / drawYdimension;
     shapeTransform->ScaleDownBy(ev, &scaleFactor);

     // create a transformation to scale matrix by this amount
     shapeTransform->PostCompose(ev, internalTransform);

     // and transform it using the current internal transform.
     usedShape->Transform(ev, shapeTransform);
     if (ev->_major != NO_EXCEPTION) {somExceptionFree(ev); return;}
     shapeTransform->Release(ev);
     internalTransform->Release(ev);

     try {
       frame->ChangeUsedShape(ev, usedShape, kODNULL);
       if (ev->_major != NO_EXCEPTION) {
         somExceptionFree(ev); //?return;
         frameShape = frame->AcquireFrameShape(ev, kODNULL);
         frame->ChangeUsedShape(ev, frameShape, kODNULL);
         frameShape->Release(ev);
       } /* endif */
     } catch (...) {
         reportAnyException(ev);
     } /* end try */

//#ifdef _PLATFORM_OS2_
     // This fails in some cases under windows.
     if (canvas->IsDynamic(ev))
     {
       // make the active shape match the used shape.
       ODShape* activeShape = usedShape->Copy(ev);
       try {
         facet->ChangeActiveShape(ev, activeShape, kODNULL);
         if (ev->_major != NO_EXCEPTION)
           {somExceptionFree(ev); return;}
       } catch (...) {
           reportAnyException(ev);
       } /* end try */
       activeShape->Release(ev);
     }
//#endif
     delete ffiter;

     usedShape->Release(ev);
   } /* endif */

} catch (...) {
    reportAnyException(ev);
} /* end try */
