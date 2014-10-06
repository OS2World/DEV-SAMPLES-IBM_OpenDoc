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
/* @(#) 1.6 com/src/samples/dynamicp/bxform/hrotate.c, oddynamicpart, od96os2, odos29712d 11/1/96 11:15:15 [3/21/97 17:44:50]
*******************************************************************
** Name: void RotateContent
**
** Description:  Modified the internal transform for all display
**               frames to affect rotation
**               and shearing within the part.
**
** Parameters:   byAngle - the (additional) angle by which to
**                         rotate the contents in all frames
**
*******************************************************************
*/
try {
  // initialize constants used in calculating rotation transforms

   ODFloat   angleDelta = byAngle;      // angle delta in degrees
#ifdef _PLATFORM_WIN32_
   // invert angle on Windows so rotate/shear go the right way.
   angleDelta *= -1;
#endif

   somSelf->UpdateTransformAngles(ev, angleDelta);

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
