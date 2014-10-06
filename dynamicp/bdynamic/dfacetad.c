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
/* @(#) 1.2 com/src/samples/dynamicp/bdynamic/dfacetad.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:35 (96/11/01 08:48:51)
*******************************************************************
** Name: void FacetAdded
**
** Description: This code fragment creates any window timers which may
**              be needed for the facet being added.
**
*******************************************************************
*/
try {
  _facetCount++;
  if (_xRotateActive || _hShearActive || _vShearActive) {
    if (!_rotateTimer->isStarted()) {
      _rotateTimer->start(new DynamicPartRotateFn(*somSelf), _rotateTimerRate );
    } /* endif */
  } /* endif */

  if (_scrolling) {
    if (!_scrollTimer->isStarted()) {
      _scrollTimer->start(new DynamicPartScrollFn(*somSelf), _scrollTimerRate);
    } /* endif */
  } /* endif */
} catch (IException &exc) {
    reportIException(exc);
} /* end try */
