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
/* @(#) 1.4 com/src/samples/dynamicp/binit/icominit.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:44 (97/02/18 13:56:30)
*******************************************************************
** Name: void CommonInit
**
** Description:  Common initialization code common to InitPart and
**               InitPartFromStorage.
**
*******************************************************************
*/
try {
    // allocate memory for non-persistant instance variables.

    _fSession = somSelf->GetStorageUnit(ev)->GetSession(ev);
    _fDraftReadOnly = (somSelf->GetStorageUnit(ev)->
                       GetDraft(ev)->GetPermissions(ev) == kODDPReadOnly);

    // _Resources is used to access resources such as strings, messages,
    // dialogs, and menus.
    if (_Resources==NULL) {
      string  ModulePathName = kDynamicPartFileName;
    // or, you can use the following code to gather the dll name at runtime
    //     SOMClassMgrObject->somLocateClassFile(
    //                                     SOM_IdFromString(kPartHandlerName),
    //                                     DynamicPart_MajorVersion, DynamicPart_MinorVersion);
      _Resources = new IDynamicLinkLibrary( ModulePathName );
    } /* endif */

} catch (...) {
    reportAnyException(ev);
} /* end try */

