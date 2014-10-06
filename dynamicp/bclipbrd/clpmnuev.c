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
/* @(#) 1.4 com/src/samples/dynamicp/bclipbrd/clpmnuev.c, oddynamicpart, od96os2, odos29712d 2/18/97 14:00:00 [3/21/97 17:48:06]
*******************************************************************
** Name: ODBoolean HandleMenuEvent
**
** Description:  Handle user requests for clipboard copy and paste.
**
*******************************************************************
*/
{
#ifdef _PLATFORM_OS2_
   ODCommandID command = LONGFROMMP(event->mp1);
#elif defined(_PLATFORM_WIN32_)
   ODCommandID command = LOWORD(event->wParam);
#endif
   switch (command) {
   case EDIT_COPY:
   {
     // copy contents to clipboard
      ODClipboard   *clipboard      = _fSession->GetClipboard(ev);
      ODArbitrator  *arbitrator     = _fSession->GetArbitrator( ev );
      ODTypeToken    clipboardFocus = _fSession->Tokenize( ev, kODClipboardFocus );
      // request the clipboard focus
      if (arbitrator->RequestFocus( ev, clipboardFocus, FocusFrame ))
      {
         clipboard->Clear( ev );
         ODStorageUnit* clipRootSU = clipboard->GetContentStorageUnit(ev);

         ODDraft* fromDraft = somSelf->GetStorageUnit(ev)->GetDraft(ev);
         ODDraft* toDraft   = clipRootSU->GetDraft(ev);

         // modify clipboard

         // Initiate the cloning operation.
         ODDraftKey key  = fromDraft->BeginClone(ev, toDraft, kODNULL, kODCloneCopy);
         // now clone self into the clipboard.  This should be done throught the draft object.
         fromDraft->Clone(ev, key, somSelf->GetID(ev), clipRootSU->GetID(ev), FocusFrame->GetID(ev));
         // commit the cloning operation.
         fromDraft->EndClone(ev, key);

         // put OpenDoc clipboard data into the system clipboard.
         clipboard->ExportClipboard( ev);

         // finished with clipboard focus.
         arbitrator->RelinquishFocus( ev, clipboardFocus, FocusFrame );
      }

      handled = kODTrue;
      }
      break;
   case EDIT_PASTE:
      {
      // paste from clipboard.
      ODClipboard*   clipboard = _fSession->GetClipboard(ev);
      ODArbitrator  *arbitrator     = _fSession->GetArbitrator( ev );
      ODTypeToken    clipboardFocus = _fSession->Tokenize( ev, kODClipboardFocus );
      if (arbitrator->RequestFocus( ev, clipboardFocus, FocusFrame )) {
         ODStorageUnit* su = clipboard->GetContentStorageUnit( ev );
         if (su->Exists(ev, kODPropContents, kKindTestDynamicPart, 0) ) {
           // Clipboard contains a DynamicPart, so internalize that part's data.
           // This code is similar to the code used in InitPartFromStorage,  but
           // contains some slight differences to account for timers, etc.
           su->Focus(ev, kODPropContents, kODPosUndefined, kKindTestDynamicPart, 0, kODPosUndefined);
           _scrollTimerRate  = ODGetSLongProp(ev, su, kODNULL, kODNULL);
           _rotateTimerRate  = ODGetSLongProp(ev, su, kODNULL, kODNULL);
           _JumpRate         = ODGetSLongProp(ev, su, kODNULL, kODNULL);
           _ScrollPos        = ODGetSLongProp(ev, su, kODNULL, kODNULL);
           _fFrameNegotiated = ODGetBooleanProp(ev, su, kODNULL, kODNULL);
         // saved color attributes.
           ODSByte colorMix = 0;
           _customBackground = ODGetBooleanProp(ev, su, kODNULL, kODNULL);
           if (_customBackground) {
             StorageUnitGetValue(su, ev, sizeof(colorMix), &colorMix); _BackColor.setRed(colorMix);
             StorageUnitGetValue(su, ev, sizeof(colorMix), &colorMix); _BackColor.setGreen(colorMix);
             StorageUnitGetValue(su, ev, sizeof(colorMix), &colorMix); _BackColor.setBlue(colorMix);
           } /* endif */
           _customTextColor  = ODGetBooleanProp(ev, su, kODNULL, kODNULL);
           if (_customTextColor) {
             StorageUnitGetValue(su, ev, sizeof(colorMix), &colorMix); _TextColor.setRed(colorMix);
             StorageUnitGetValue(su, ev, sizeof(colorMix), &colorMix); _TextColor.setGreen(colorMix);
             StorageUnitGetValue(su, ev, sizeof(colorMix), &colorMix); _TextColor.setBlue(colorMix);
           } /* endif */
         // saved angles in degrees -- must convert to radians for c trig functions.
           ODSLong degrees = 0;
           degrees = ODGetSLongProp(ev, su, kODNULL, kODNULL);
           ODFloat xRotAngle = degrees * pi / 180;
           degrees = ODGetSLongProp(ev, su, kODNULL, kODNULL);
           ODFloat xAngleDelta = degrees * pi / 180;
           degrees = ODGetSLongProp(ev, su, kODNULL, kODNULL);
           ODFloat hShearAngle = degrees * pi / 180;
           degrees = ODGetSLongProp(ev, su, kODNULL, kODNULL);
           ODFloat vShearAngle = degrees * pi / 180;

         // are we scrolling/rotating
           somSelf->_set_scrolling(ev, ODGetBooleanProp(ev, su, kODNULL, kODNULL));
           somSelf->_set_xRotateActive(ev, ODGetBooleanProp(ev, su, kODNULL, kODNULL));
           somSelf->_set_hShearActive(ev, ODGetBooleanProp(ev, su, kODNULL, kODNULL));
           somSelf->_set_vShearActive(ev, ODGetBooleanProp(ev, su, kODNULL, kODNULL));
         // which directions
           somSelf->_set_xRotateClockwise(ev, ODGetBooleanProp(ev, su, kODNULL, kODNULL));
           somSelf->_set_hShearRight(ev, ODGetBooleanProp(ev, su, kODNULL, kODNULL));
           somSelf->_set_vShearUp(ev, ODGetBooleanProp(ev, su, kODNULL, kODNULL));

         // now get the font
           _customFont = ODGetBooleanProp(ev, su, kODNULL, kODNULL);
           if (_customFont) {
             ODULong fontNameLength = 0;
             char *fontName = NULL;
             fontName = ODGetISOStrProp(ev, su, kODPropContents, kODISOStr, fontName, &fontNameLength);
             if (fontName) {
                _Font->setName(fontName);
                _Message->setFont(*_Font);
                // memory was allocated by ODGetISOStrProp, so use SOMFree to free it.
                SOMFree(fontName);
             } /* endif */
           } /* endif */

         // now get the text value
           ODULong msgLength = 0;
           char *msgText = NULL;
           msgText = ODGetISOStrProp(ev, su, kODPropContents, kODISOStr, msgText, &msgLength);
           if (msgText) {
              _Message->setText(msgText);
              // memory was allocated by ODGetISOStrProp, so use SOMFree to free it.
              SOMFree(msgText);
           } else {
             // couldn't read the text, so turn off scrolling
             _scrolling = kODFalse;
           } /* endif */
           msgText = NULL;
           somSelf->_set_xRotAngle(ev, xRotAngle);
           somSelf->_set_xAngleDelta(ev, xAngleDelta);
           somSelf->_set_hShearAngle(ev, hShearAngle);
           somSelf->_set_vShearAngle(ev, vShearAngle);
         //somSelf->RotateContent(ev, 0.0);
         //somSelf->SetInternalXform(ev, FocusFrame);
         } /* endif */

         // get a text value if one exists
         if (su->Exists(ev, kODPropContents, kODISOStr, 0) ) {
           ODULong msgLength = 0;
           char *msgText = NULL;
           msgText = ODGetISOStrProp(ev, su, kODPropContents, kODISOStr, msgText, &msgLength);
           if (msgText) {
              IString message(msgText);
              message.strip();
              // be sure message ends with a single space
              message += " ";
              _Message->setText(message);
              // memory was allocated by ODGetISOStrProp, so use SOMFree to free it.
              SOMFree(msgText);
           } /* endif */
           msgText = NULL;
         } else {
           // try for a native clipboard text format.
           ODValueType textType = _fSession->GetTranslation(ev)->
                                 GetISOTypeFromPlatformType(ev, CF_TEXT, kODPlatformDataType);
           if (su->Exists(ev, kODPropContents, textType, 0) ) {
             ODULong msgLength = 0;
             char *msgText = NULL;
             msgText = ODGetISOStrProp(ev, su, kODPropContents, textType, msgText, &msgLength);
             if (msgText) {
                 IString message(msgText);
                 message.strip();
                 // be sure message ends with a single space
                 message += " ";
                _Message->setText(message);
                // memory was allocated by ODGetISOStrProp, so use SOMFree to free it.
                SOMFree(msgText);
             } /* endif */
             msgText = NULL;
           } /* endif */
         } /* endif */
      } /* endif */
      arbitrator->RelinquishFocus( ev, clipboardFocus, FocusFrame );
      somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);
      ODUpdateID updateID = _fSession->UniqueUpdateID(ev);
      FocusFrame->ContentUpdated (ev, updateID);
      handled = kODTrue;
      }
      break;
   default:
      break;
   } /* endswitch */
}
