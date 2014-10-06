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
/* @(#) 1.3 com/src/samples/dynamicp/bxform/rotactiv.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:51 (96/11/12 18:47:34)
*******************************************************************
** Name: void _set_xRotateActive
**
** Description:  Update the flag that determines whether the
**               part will rotate.
**
** Parameters:   xRotateActive - should part rotate?
**
*******************************************************************
*/
{
    if (_xRotateActive != xRotateActive) {
      _xRotateActive = xRotateActive;
      if (!_hShearActive && !_vShearActive) {
        if (_xRotateActive) {
          if (!_rotateTimer->isStarted()) {
            _rotateTimer->start(new DynamicPartRotateFn(*somSelf), _rotateTimerRate );
          } /* endif */
        } else {
          _rotateTimer->stop();
        } /* endif */
      } /* endif */

      if (_xRotateActive) {
        // Force only one type of transform to be applied
        // to work around limitation in OpenDoc Transforms.
        if (_hShearAngle != 0.0) {
          somSelf->_set_hShearAngle(ev, 0.0);
        } /* endif */
        if (_hShearActive) {
          somSelf->_set_hShearActive(ev, kODFalse);
        } /* endif */
        if (_vShearAngle!=0.0) {
          somSelf->_set_vShearAngle(ev, 0.0);
        } /* endif */
        if (_vShearActive) {
          somSelf->_set_vShearActive(ev, kODFalse);
        } /* endif */
      } /* endif */
    } /* endif */
}
