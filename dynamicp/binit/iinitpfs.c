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
/* @(#) 1.4 com/src/samples/dynamicp/binit/iinitpfs.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:49:41 [3/21/97 17:44:46]
*******************************************************************
** Name: void InitPartFromStorage
**
** Description:  "Read" persistend instance data from the storage
**               unit.
**
*******************************************************************
*/
try {

    if (_fIsInitialized)
      // Already done this -- don't do it again.
      return;

    _fIsInitialized = kODTrue;

    // save self-reference for later use.
    _fPartWrapper = partWrapper;

    if(!storageUnit->Exists(ev, kODPropContents, kKindTestDynamicPart, 0))
    {
        storageUnit->AddProperty(ev, kODPropContents)->AddValue(ev, kKindTestDynamicPart);
    } else {
      storageUnit->Focus(ev, kODPropContents, kODPosUndefined, kKindTestDynamicPart, 0, kODPosUndefined);
      _scrollTimerRate  = ODGetSLongProp(ev, storageUnit, kODNULL, kODNULL);
      _rotateTimerRate  = ODGetSLongProp(ev, storageUnit, kODNULL, kODNULL);
      _JumpRate         = ODGetSLongProp(ev, storageUnit, kODNULL, kODNULL);
      _ScrollPos        = ODGetSLongProp(ev, storageUnit, kODNULL, kODNULL);
      _fFrameNegotiated = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
    // saved color attributes.
      ODSByte colorMix = 0;
      _customBackground = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
      if (_customBackground) {
        StorageUnitGetValue(storageUnit, ev, sizeof(colorMix), &colorMix); _BackColor.setRed(colorMix);
        StorageUnitGetValue(storageUnit, ev, sizeof(colorMix), &colorMix); _BackColor.setGreen(colorMix);
        StorageUnitGetValue(storageUnit, ev, sizeof(colorMix), &colorMix); _BackColor.setBlue(colorMix);
      } /* endif */
      _customTextColor  = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
      if (_customTextColor) {
        StorageUnitGetValue(storageUnit, ev, sizeof(colorMix), &colorMix); _TextColor.setRed(colorMix);
        StorageUnitGetValue(storageUnit, ev, sizeof(colorMix), &colorMix); _TextColor.setGreen(colorMix);
        StorageUnitGetValue(storageUnit, ev, sizeof(colorMix), &colorMix); _TextColor.setBlue(colorMix);
      } /* endif */
    // saved angles in degrees -- must convert to radians for c trig functions.
      ODSLong degrees = 0;
      degrees = ODGetSLongProp(ev, storageUnit, kODNULL, kODNULL);
      _xRotAngle = degrees * pi / 180;
      degrees = ODGetSLongProp(ev, storageUnit, kODNULL, kODNULL);
      _xAngleDelta = degrees * pi / 180;
      degrees = ODGetSLongProp(ev, storageUnit, kODNULL, kODNULL);
      _hShearAngle = degrees * pi / 180;
      degrees = ODGetSLongProp(ev, storageUnit, kODNULL, kODNULL);
      _vShearAngle = degrees * pi / 180;

    // are we scrolling/rotating
      _scrolling     = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
      _xRotateActive = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
      _hShearActive  = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
      _vShearActive  = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
    // which directions
      _xRotateClockwise = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
      _hShearRight      = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
      _vShearUp         = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);

    // now get the font
      _customFont = ODGetBooleanProp(ev, storageUnit, kODNULL, kODNULL);
      if (_customFont) {
        ODULong fontNameLength = 0;
        char *fontName = NULL;
        fontName = ODGetISOStrProp(ev, storageUnit, kODPropContents, kODISOStr, fontName, &fontNameLength);
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
      msgText = ODGetISOStrProp(ev, storageUnit, kODPropContents, kODISOStr, msgText, &msgLength);
      if (msgText) {
         _Message->setText(msgText);
         // memory was allocated by ODGetISOStrProp, so use SOMFree to free it.
         SOMFree(msgText);
      } else {
        // couldn't read the text, so turn off scrolling
        _scrolling = kODFalse;
      } /* endif */
      msgText = NULL;
    } /* endif */
    storageUnit->Focus(ev, kODPropContents, kODPosUndefined, kKindTestDynamicPart, 0, kODPosUndefined);
} catch (...) {
    reportAnyException(ev);
} /* end try */
// end initfs.frg
