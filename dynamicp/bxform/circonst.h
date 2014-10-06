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
/* @(#) 1.2 com/src/samples/dynamicp/bxform/circonst.h, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:50 (96/11/01 08:50:59)
*******************************************************************
** Name: circle constants
**
** Description:  Constant values used to calculate rotation
**               transform and convert between degrees and radians.
**
*******************************************************************
*/

// These constants are used in calculating rotation transforms
const ODFloat pi  = 3.14159265358979323846;
const ODFloat two_pi = 2 * pi;
const ODFloat degrees_90 = pi / 2.0;        // 90 degrees
const ODFloat degrees_270 = 3.0 * pi / 2.0;  // 270 degrees
const ODFloat minAngleDelta = pi / 180;       // one degree
