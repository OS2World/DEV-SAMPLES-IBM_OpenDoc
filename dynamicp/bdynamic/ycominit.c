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
/* @(#) 1.3 com/src/samples/dynamicp/bdynamic/ycominit.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:49:03 [3/21/97 17:44:42]
*******************************************************************
** Name: void CommonInit
**
** Description:  Provide default values for instance variables
**               used to set timer and their rates.
**
*******************************************************************
*/
{
  _xRotateActive  = kODFalse;
  _hShearActive   = kODFalse;
  _vShearActive   = kODFalse;
  _rotateTimerRate = 2500;  // timer interval in milli-seconds

  _scrolling = kODTrue;
  _scrollTimerRate = 100;   // timer interval in milli-seconds

  if (_scrollTimer == NULL) {
    _scrollTimer = new ITimer();
  } /* endif */
  if (_rotateTimer == NULL) {
    _rotateTimer = new ITimer();
  } /* endif */

}
