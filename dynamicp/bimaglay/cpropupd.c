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
/* @(#) 1.3 com/src/samples/dynamicp/bimaglay/cpropupd.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:43 (96/11/01 08:49:07)
*******************************************************************
** Name: void ContainingPartPropertiesUpdated
**
** Description:  Notification when one of the containing part's
**               properties changes.  We only care about the
**               background and foreground colors.
**
*******************************************************************
*/
#ifdef _OS2_OD_GA_
try {
  RGBColor rgb;
  if (!_customBackground) {
    if (ODSUExistsThenFocus(ev, propertyUnit, kODBackgroundColor, kODRGB2)) {
      StorageUnitGetValue(propertyUnit, ev, sizeof(rgb), &rgb);
        //_BackColor = rgb
        ODSByte colorMix = 0;
        colorMix = rgb / 0x10000;       _BackColor.setRed(colorMix);
        colorMix = rgb / 0x100 % 0x100; _BackColor.setGreen(colorMix);
        colorMix = rgb % 0x100;         _BackColor.setBlue(colorMix);
    } /* endif */
  } /* endif */

  if (!_customTextColor) {
    // text foreground color
    if (ODSUExistsThenFocus(ev, propertyUnit, kODForegroundColor, kODRGB2)) {
      StorageUnitGetValue(propertyUnit, ev, sizeof(rgb), &rgb);
        //_TopColor = rgb
        ODSByte colorMix = 0;
        colorMix = rgb / 0x10000;       _TextColor.setRed(colorMix);
        colorMix = rgb / 0x100 % 0x100; _TextColor.setGreen(colorMix);
        colorMix = rgb % 0x100;         _TextColor.setBlue(colorMix);
    } /* endif */
  } /* endif */

  if (!_customFont) {
    // text font
    if (ODSUExistsThenFocus(ev, propertyUnit, kODFont, kODFontNameSize)) {
      ODULong fontNameLength = 0;
      char *fontNameSize = NULL;
      fontNameSize = ODGetISOStrProp(ev, propertyUnit, kODNULL, kODNULL, fontNameSize, &fontNameLength);
      if (fontNameSize) {
         char *fontName = strchr(fontNameSize, '.');
         if (fontName==kODNULL) {
           fontName = fontNameSize;
         } /* endif */
         _Font->setName(fontName);
         _Message->setFont(*_Font);
         // memory was allocated by ODGetISOStrProp, so use SOMFree to free it.
         SOMFree(fontNameSize);
      } /* endif */
    } /* endif */
  } /* endif */
} catch (...) {
  reportAnyException(ev);
} /* end try */
#endif
