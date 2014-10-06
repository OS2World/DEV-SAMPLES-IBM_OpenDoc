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
/* @(#) 1.4 com/src/samples/dynamicp/bimaglay/ifacetad.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:43 (97/02/18 13:54:16)
*******************************************************************
** Name: void FacetAdded
**
** Description:  Create a graphic font when a facet is added to
**               the part and initiate frame negotiation.
**
*******************************************************************
*/
try {
   ODFrame * frame = facet->GetFrame(ev);
   ODFrameFacetIterator* facets = frame->CreateFacetIterator(ev);

   // if this is the first facet, give the part a chance to resize the frame

   facets->First(ev);
   if (!facets->Next(ev))         //Only one facet?
   {
     // set font to use this facet
     {
       ODShape *shape = kODNULL;
       HPS hps;
       CFocus f(facet, shape, &hps);          // Set up drawing environment

       IPresSpaceHandle DrawHps(hps);
       _Font->useVectorOnly(TRUE, DrawHps);
     }
     // now adjust the facet's size
     somSelf->AdjustSize(ev, frame, facet);
   } /* endif */
   delete facets;

} catch (IException &exc) {
  reportIException(exc);
} catch (...) {
  reportAnyException(ev);
} /* end try */

