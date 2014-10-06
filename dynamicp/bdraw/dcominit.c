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
/* @(#) 1.4 com/src/samples/dynamicp/bdraw/dcominit.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:48:37 [3/21/97 17:44:34]
*******************************************************************
** Name: void CommonInit
**
** Description:  Initialize instance variables needed to draw the
**               part.
**
*******************************************************************
*/
try {
    // Setting the Background and Fill color for the Graphic Context I draw to
    IdColor TextColor1(IColor::red);
    _TextColor   = TextColor1;
    IdColor TextColor2(IColor::white);
    _BackColor = TextColor2;
   // number of pixels skipped each time interval
    _JumpRate = drawXdimension / 80;
    // start scroll position at right edge of frame
    _ScrollPos=   drawXdimension;

    string  ModulePathName = kDynamicPartFileName;
    // or, you can use the following code to gather the dll name at runtime
    //   SOMClassMgrObject->somLocateClassFile(
    //                                   SOM_IdFromString(kPartHandlerName),
    //                                   DynamicPart_MajorVersion, DynamicPart_MinorVersion);
    // load bitmap resources
    if (_ODBitmap)
      delete _ODBitmap;
#ifdef _PLATFORM_WIN32_
    // loading from a resource loses colors, so load from a file
    char bitmapname[256];
    bitmapname[0] = '\0';
    _searchenv("ioddynam.bmp", "PATH", bitmapname);
    if (bitmapname[0] == '\0') {
#endif
      IDynamicLinkLibrary x(ModulePathName);
      IBitmapHandle ibh = x.loadBitmap(ODBMP);
      _ODBitmap = new IGBitmap(ibh);
#ifdef _PLATFORM_WIN32_
    } else {
      _ODBitmap = new IGBitmap(IString(bitmapname));
    } /* endif */
#endif
    // Determine font for message strings
    long FontSize = drawYdimension/20;
    if (_Font)
       delete _Font;
    _Font = new IFont("",FontSize,FALSE,TRUE);
    _Font->setPointSize(FontSize);
    _Font->useBitmapOnly(false);
    _Font->useNonPropOnly(false);
    _Font->useVectorOnly(true);
    // load string resources
    _Message =new IGString(_Resources->loadString(DYNAMICPART_DEFAULTMESSAGE), IPoint(0,0), *_Font );
} catch (IException &exc) {
   reportIException(exc);
} /* end try */
