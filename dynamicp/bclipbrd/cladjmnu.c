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
/* @(#) 1.3 com/src/samples/dynamicp/bclipbrd/cladjmnu.c, oddynamicpart, od96os2, odos29712d 2/18/97 13:55:54 [3/21/97 17:48:06]
*******************************************************************
** Name: void AdjustMenus
**
** Description:  Set the Edit menu items relating to clipboard
**               copy, cut, and paste.
**
*******************************************************************
*/
{
    _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_COPY, kODTrue);
    _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTEAS, kODFalse);
    _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTELINK, kODFalse);

    // see if the clipboard contains anything we know how to paste //
    Boolean canPaste = kODFalse;
    ODClipboard*   clipboard = _fSession->GetClipboard(ev);
    ODArbitrator  *arbitrator     = _fSession->GetArbitrator( ev );
    ODTypeToken    clipboardFocus = _fSession->Tokenize( ev, kODClipboardFocus );
    if (arbitrator->RequestFocus( ev, clipboardFocus, frame )) {
       ODStorageUnit* su = clipboard->GetContentStorageUnit( ev );

       ODValueType textType = _fSession->GetTranslation(ev)->
                             GetISOTypeFromPlatformType(ev, CF_TEXT, kODPlatformDataType);

       if (su->Exists(ev, kODPropContents, kKindTestDynamicPart, 0)
         || su->Exists(ev, kODPropContents, kODISOStr, 0)
         || su->Exists(ev, kODPropContents, textType, 0) ) {
         canPaste = kODTrue;
       } /* endif */
    } /* endif */
    arbitrator->RelinquishFocus( ev, clipboardFocus, frame );

    // Enable Paste for writeable drafts if the clipboard contains pasteable stuff
    _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_PASTE, canPaste && !_fDraftReadOnly);
}
