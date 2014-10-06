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
/* @(#) 1.3 com/src/samples/dynamicp/bscript/notfyrot.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:50:40 [3/21/97 17:48:34]
*******************************************************************
** Name: void RotateContent
**
** Description:  The internal transform has been modified, so notify
**               anyone who has asked to be informed.
**
*******************************************************************
*/
try {
   //Fire scripting event
   if(_fEventMgr)
   {
      _IDL_SEQUENCE_any in_pars;
      ODDSRESULT result;
      long sink_count;
      long sink_num;
      any  data[3];
      ODDSSinkEnum  *sinkEnum;

      data[0]._type = TypeCodeNew(tk_float);
      data[0]._value = (void *)&_xRotAngle;
      data[1]._type = TypeCodeNew(tk_float);
      data[1]._value = (void *)&_hShearAngle;
      data[2]._type = TypeCodeNew(tk_float);
      data[2]._value = (void *)&_vShearAngle;

      in_pars._length = 3;
      in_pars._maximum = 3;
      in_pars._buffer = data;

      _fEventMgr->PrepareEventFiring(ev, &sink_count, &sinkEnum);
      for(sink_num = 0; sink_num < sink_count; sink_num++) {
         _fEventMgr->FireEvent(ev, sinkEnum, "PositionChange", &in_pars,
                               &result);
      }
      _fEventMgr->StopEventFiring(ev, sinkEnum);
   }
} catch (...) {
   reportAnyException(ev);
} /* end try */
