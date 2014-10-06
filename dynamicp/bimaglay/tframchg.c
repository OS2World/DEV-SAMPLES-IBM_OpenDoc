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
/* @(#) 1.4 com/src/samples/dynamicp/bimaglay/tframchg.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:44 (97/02/18 13:54:21)
*******************************************************************
** Name: void FrameShapeChanged
**
** Description:  when the part's frame shape changes call AdjustSize
**               to perform frame shape negotiation.
**
*******************************************************************
*/
try {
    // If we have a facet, we want to adjust it to match the new
    // frame shape (or negotiate for a different frame shape).
    ODFrameFacetIterator* facets = frame->CreateFacetIterator(ev);
    ODFacet* facet = facets->First(ev);
    if (facet) {
      ODRect frameRect;
      ODShape *frameShape = frame->AcquireFrameShape(ev, kODNULL);
      frameShape->GetBoundingBox(ev, &frameRect);
      facet->ChangeActiveShape(ev, frameShape, kODNULL);
      // set used shape to the draw rectangle.
      somSelf-> AdjustSize(ev,  frame, facet);
    }
    delete facets;
    somSelf->SetInternalXform(ev, frame);

} catch (...) {
    reportAnyException(ev);
} /* end try */

