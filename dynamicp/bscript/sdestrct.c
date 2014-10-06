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
/* @(#) 1.3 com/src/samples/dynamicp/bscript/sdestrct.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:50:49 [3/21/97 17:48:33]
*******************************************************************
** Name: void somDestruct
**
** Description:  override method to deallocate any resources
**               as part of part de-initialization.
**
*******************************************************************
*/
try {
   if (_fEventMgr) {
     Environment *ev = SOM_CreateLocalEnvironment();
     somSelf->DeleteEventMgr(ev,&_fEvtGuid) ;
     _fEventMgr = NULL ;
     SOM_DestroyLocalEnvironment(ev);
   }
} catch (...) {
   reportAnyException(somGetGlobalEnvironment());
} /* end try */
