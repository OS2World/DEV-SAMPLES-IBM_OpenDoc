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
/* @(#) 1.5 com/src/samples/dynamicp/bxform/xreset.c, oddynamicpart, od96os2, odos29712d 11/8/96 17:29:23 [3/21/97 17:44:53]
*******************************************************************
** Name: void Reset
**
** Description:  Reset all transformations to default value
**               and stop rotation timer.
**
*******************************************************************
*/
try {
    // this case should either stop rotation and shear and reset angles
    if (_xRotateActive || _hShearActive || _vShearActive) {
       _rotateTimer->stop();
    } /* endif */

    _xRotateClockwise   = kODTrue;
    _hShearRight    = kODTrue;
    _vShearUp       = kODTrue;
    _xRotateActive  = kODFalse;
    _hShearActive   = kODFalse;
    _vShearActive   = kODFalse;
    _xRotAngle   = 0;
    _hShearAngle = 0;
    _vShearAngle = 0;
    /////////////////////////////////////////////////////////////
    // Now reset the internal Transform
    IODLinkedList *displayFrames = somSelf->GetDisplayFrames(ev);
    IODLink *listItem;
    ODFrame *frame;

    for (listItem = displayFrames->First(ev);
         (listItem != kODNULL) && (frame = (ODFrame *)(listItem->Content(ev)));
         listItem = listItem->Next(ev))
    {
      somSelf->SetInternalXform(ev, frame);
    } /* endfor */
    // do NOT delete displayFrames;
} catch (...) {
  reportAnyException(ev);
} /* end try */
