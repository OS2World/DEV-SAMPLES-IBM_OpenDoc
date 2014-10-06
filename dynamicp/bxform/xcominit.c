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
/* @(#) 1.3 com/src/samples/dynamicp/bxform/xcominit.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:51:56 [3/21/97 17:44:53]
*******************************************************************
** Name: void CommonInit
**
** Description:  Provide default values for instance variables
**               used to rotate and shear the part.
**
*******************************************************************
*/
try {
  // initialize constants used in calculating rotation transforms
//const float pi = 3.14159265358979323846;

  // Rotations are measured in radians.  The Rotation angle delta defaults to 10 degree
  // change in the angle of rotation each time the rotate code segment is executed.
  // This change or delta is added to or subtracted from the persistent instance
  // variable _xRotAngle each time the rotate recipe code segment is executed.
  _xAngleDelta = (pi / 18);   // 10 degrees

  // direction defaults to "clockwise"
  _xRotateClockwise = kODTrue;
  _hShearRight = kODTrue;
  _vShearUp    = kODTrue;

} catch (...) {
  reportAnyException(ev);
} /* end try */
