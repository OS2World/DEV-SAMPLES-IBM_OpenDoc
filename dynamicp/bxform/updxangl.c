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
/* @(#) 1.2 com/src/samples/dynamicp/bxform/updxangl.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:52 (96/11/01 08:51:35)
*******************************************************************
** Name: ODFloat UpdateTransformAngles
**
** Description:  Updates _xRotAngle, _hShearAngle, and vShearAngle
**               as appropriate by angleDelta radians.
**
** Parameters:   angleDelta - the amount by which to update the
**                            rotation angle.
**
*******************************************************************
*/
{
   // Increment or decrement the instance variable _xRotAngle by ANGLE_DELTA
   // depending on the direction of rotation.  Reset _xRotAngle to 0 whenever
   // the rotation has reached 360 degrees.
   if (_xRotateActive) {
     if (_xRotateClockwise) {
       _xRotAngle += angleDelta;
     } else {
       _xRotAngle -= angleDelta;
     } /* endif */
     if (_xRotAngle < 0) {
       _xRotAngle += two_pi;
     } else {
       if (_xRotAngle>=two_pi) {
          _xRotAngle -= two_pi;
       } /* endif */
     } /* endif */
   } /* endif */

   // Increment or decrement the instance variable _hShearAngle by ANGLE_DELTA
   // depending on the direction of rotation.  Reset _hShearAngle to 0 whenever
   // the rotation has reached 360 degrees.
   if (_hShearActive) {
     if (_hShearRight) {
       _hShearAngle += angleDelta;
     } else {
       _hShearAngle -= angleDelta;
     } /* endif */
     if (_hShearAngle < 0) {
       _hShearAngle += two_pi;
     } else {
       if (_hShearAngle>=two_pi) {
          _hShearAngle -= two_pi;
       } /* endif */
     } /* endif */
   } /* endif */

   // Increment or decrement the instance variable _vShearAngle by ANGLE_DELTA
   // depending on the direction of rotation.  Reset _vShearAngle to 0 whenever
   // the rotation has reached 360 degrees.
   if (_vShearActive) {
     if (_vShearUp) {
       _vShearAngle += angleDelta;
     } else {
       _vShearAngle -= angleDelta;
     } /* endif */
     if (_vShearAngle < 0) {
       _vShearAngle += two_pi;
     } else {
       if (_vShearAngle>=two_pi) {
          _vShearAngle -= two_pi;
       } /* endif */
     } /* endif */
   } /* endif */
}
