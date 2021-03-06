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
/* @(#) 1.3 com/src/samples/dynamicp/bdynamic/facetrem.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:48:55 [3/21/97 17:44:41]
*******************************************************************
** Name: void FacetRemoved
**
** Description:  This code fragment stops any window timers which may
**               currently be associated with the facet being removed.
*******************************************************************
*/
{

   // only if no more facets exist!
   // decrement the facet count instance variable
   _facetCount--;
   if (_facetCount==0) {
     if (_rotateTimer->isStarted()) {
       _rotateTimer->stop();
     } /* endif */
     if (_scrollTimer->isStarted()) {
       _scrollTimer->stop();
     } /* endif */
   } /* endif */

}
