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
/* @(#) 1.4 com/src/samples/dynamicp/binit/iexternz.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:49:37 [3/21/97 17:44:44]
*******************************************************************
** Name: void Externalize
**
** Description:  Saves intrinsic content to a storage unit.
**
*******************************************************************
*/
try {

  // set up storage unit
  // add property to store part identifier
  ODSUForceFocus(ev, toSU, kODPropPart, kODISOStr);
  StorageUnitSetValue(toSU, ev, strlen(kPartTestDynamicPart)+1, (ODValue)kPartTestDynamicPart);

  // add property for part kind
  if (!toSU->Exists(ev, kODPropContents, kKindTestDynamicPart, 0)) {
    toSU->AddProperty(ev, kODPropContents)->AddValue(ev, kKindTestDynamicPart);
  } /* endif */

  // write values to storage unit

  toSU->Focus(ev, kODPropContents, kODPosUndefined, kKindTestDynamicPart, 0, kODPosUndefined);
  ODSetSLongProp(ev, toSU, kODNULL, kODNULL, _scrollTimerRate);
  ODSetSLongProp(ev, toSU, kODNULL, kODNULL, _rotateTimerRate);
  ODSetSLongProp(ev, toSU, kODNULL, kODNULL, _JumpRate);
  ODSetSLongProp(ev, toSU, kODNULL, kODNULL, _ScrollPos);
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _fFrameNegotiated);
// store color attributes.
  ODSByte colorMix = 0;
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _customBackground);
  if (_customBackground) {
    colorMix = _BackColor.redMix();   StorageUnitSetValue(toSU, ev, sizeof(colorMix), &colorMix);
    colorMix = _BackColor.greenMix(); StorageUnitSetValue(toSU, ev, sizeof(colorMix), &colorMix);
    colorMix = _BackColor.blueMix();  StorageUnitSetValue(toSU, ev, sizeof(colorMix), &colorMix);
  } /* endif */
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _customTextColor);
  if (_customTextColor) {
    colorMix = _TextColor.redMix();   StorageUnitSetValue(toSU, ev, sizeof(colorMix), &colorMix);
    colorMix = _TextColor.greenMix(); StorageUnitSetValue(toSU, ev, sizeof(colorMix), &colorMix);
    colorMix = _TextColor.blueMix();  StorageUnitSetValue(toSU, ev, sizeof(colorMix), &colorMix);
  } /* endif */
  ODSLong degrees = 0;
// store angles in degrees
  degrees = _xRotAngle * 180 / pi;
  ODSetSLongProp(ev, toSU, kODNULL, kODNULL, degrees);

  degrees = _xAngleDelta * 180 / pi;
  ODSetSLongProp(ev, toSU, kODNULL, kODNULL, degrees);
  degrees = _hShearAngle * 180 / pi;
  ODSetSLongProp(ev, toSU, kODNULL, kODNULL, degrees);
  degrees = _vShearAngle * 180 / pi;
  ODSetSLongProp(ev, toSU, kODNULL, kODNULL, degrees);
  // are we scrolling/rotating
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _scrolling);
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _xRotateActive);
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _hShearActive);
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _vShearActive);
  // which directions
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _xRotateClockwise);
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _hShearRight);
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _vShearUp);

  // save the font, if necessary
  ODSetBooleanProp(ev, toSU, kODNULL, kODNULL, _customFont);
  if (_customFont) {
    ODSetISOStrProp(ev, toSU, kODNULL, kODNULL, (char *)_Font->name());
  } /* endif */

  // add property for string representation
  if (!toSU->Exists(ev, kODPropContents, kODISOStr, 0)) {
    toSU->AddProperty(ev, kODPropContents)->AddValue(ev, kODISOStr);
  } /* endif */
  // now save the text
  ODSetISOStrProp(ev, toSU, kODPropContents, kODISOStr, (char *)_Message->text() );
} catch (...) {
  reportAnyException(ev);
} /* end try */
