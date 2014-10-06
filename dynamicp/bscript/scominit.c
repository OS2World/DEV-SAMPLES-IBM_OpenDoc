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
/* @(#) 1.3 com/src/samples/dynamicp/bscript/scominit.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:50:45 [3/21/97 17:48:34]
*******************************************************************
** Name: void CommonInit
**
** Description:  Common initialization code common to InitPart and
**               InitPartFromStorage.
**
*******************************************************************
*/
try {
    // create scripting event manager
    ODGUID odguid = {0xd3662880, 0x267a, 0x11d0,
                     {0xa5, 0xc3, 0x00, 0x04, 0xac, 0x32, 0x80, 0xdc}};
    _fEvtGuid = odguid;

    Environment *ev = somGetGlobalEnvironment();
    _fEventMgr = new ODDSEventMgr(ev, _fEvtGuid);
    somSelf->AddEventMgr(ev, _fEventMgr);
} catch (...) {
   reportAnyException(somGetGlobalEnvironment());
} /* end try */
