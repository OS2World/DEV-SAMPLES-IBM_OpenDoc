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
/* @(#) 1.4 com/src/samples/dynamicp/bxform/calcrotf.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:50:55 [3/21/97 17:44:50]
*******************************************************************
** Name: void CalcRotationFactors
**
** Description:  Updates _xRotAngle, _hShearAngle, and vShearAngle
**               as appropriate by angleDelta radians.
**
** returns       sin and cos of rotation angle,
**               tangent of horizontal and vertical shear angles.
**
*******************************************************************
*/
{
   try {
#ifdef _PLATFORM_WIN32_
     // this is to get around an apparent bug in OpenClass libraries
     if ((fabs(_xRotAngle-degrees_90)<=minAngleDelta) ||
         (fabs(_xRotAngle-degrees_270)<=minAngleDelta) ) {
        // angle is near a singularity?
        *rotCos = cos(_xRotAngle-minAngleDelta);
        *rotSin = sin(_xRotAngle-minAngleDelta);
     } else {
        *rotCos = cos(_xRotAngle);
        *rotSin = sin(_xRotAngle);
     } /* endif */
#else
        *rotCos = cos(_xRotAngle);
        *rotSin = sin(_xRotAngle);
#endif
   } catch (...) {
     *rotSin = 0.0; *rotCos = 1.0;
   } /* end try */

   // tangent of horizontal shear angle
   try {
     if ((fabs(_hShearAngle-degrees_90)>minAngleDelta) &&
         (fabs(_hShearAngle-degrees_270)>minAngleDelta) ) {
        // if the angle is between 90 and 270 degrees, change the angle used
        // to simulate 3-D
        if ((_hShearAngle > degrees_90) &&
            (_hShearAngle < degrees_270)) {
          *hshTan = tan(two_pi - _hShearAngle);  // horizontal shear
        } else {
          *hshTan = tan(_hShearAngle);  // horizontal shear
        } /* endif */
     } else {
        // angle is near a singularity for tangent
        *hshTan = tan(_hShearAngle-minAngleDelta);  // horizontal shear
     } /* endif */
   } catch (...) {
     *hshTan = 0.0;
   } /* end try */

   // tangent of vertical shear angle
   try {
     if ((fabs(_vShearAngle-degrees_90)>minAngleDelta) &&
         (fabs(_vShearAngle-degrees_270)>minAngleDelta) ) {
        // if the angle is between 90 and 270 degrees, change the angle used
        // to simulate 3-D
        if ((fabs(_vShearAngle) > degrees_90) &&
            (fabs(_vShearAngle) < degrees_270) ) {
           *vshTan = tan(two_pi - _vShearAngle);  // vertical shear
        } else {
           *vshTan = tan(_vShearAngle);  // vertical shear
        } /* endif */
     } else {
        // angle is near a singularity for tangent
        *vshTan = tan(_vShearAngle-minAngleDelta);  // vertical shear
     } /* endif */
   } catch (...) {
     *vshTan = 0;
   } /* end try */
}
