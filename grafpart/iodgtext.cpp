// @(#) 1.4 com/src/samples/grafpart/iodgtext.cpp, odgrafpart, od96os2, odos29712d 2/17/97 14:04:31 [3/21/97 17:49:29]
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odgrafpart
 *
 *   CLASSES: ContentGrafPartText
 *
 *   ORIGINS: 27
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

// *********************************************************************
//  File:      iodgtext.cpp
//  Contains:  Class implementation for a Line Object in a 2D-Drawing Container Part
// ************************************************************************

#define ContentGrafPartText_Class_Source

#ifndef SOM_Module_GrafLine_Source
    #define SOM_Module_GrafLine_Source
#endif  // SOM_Module_GrafLine_Source

// GrafPart's includes
#ifndef _IODGCOMM_CPP_
   #include <iodgcomm.cpp>
#endif   // _IODGCOMM_CPP_

// GrafPart's constants & defines
#ifndef _GRAFPART_HPP_
   #include <iodgraph.hpp>
#endif   // _GRAFPART_HPP_

// support use of temporary objects (Initialize & Uninitialize)
#ifndef _TEMPOBJ_
    #include <TempObj.h>
#endif // _TEMPOBJ_

// support StorageUnit function
#ifndef _STORUTIL_
    #include <StorUtil.h>
#endif  // _STORUTIL_

// support math function (ContainsPoint)
#ifndef __math_h
    #include <math.h>
#endif  // __math_h

// includes for native drawing functions
#if defined(_PLATFORM_WIN32_)
    #include <windows.h>
    #include <winuser.h>
    #include <wingdi.h>
#elif defined(_PLATFORM_OS2_)
    #include <ODos2.h>
#endif // _PLATFORM_???_


// local function support includes
#ifndef SOM_GrafPart_xh
    #include "iodgraph.xh"
#endif // SOM_GrafPart_xh

#ifndef SOM_ContentGrafPartText_xih
    #include "iodgtext.xih"
#endif // SOM_ContentGrafPartText_xih


// *************************************************************************
//
//  Class implementation:
//      ContentGrafPartText : ContentGrafPartRect
//
// *************************************************************************

// =========================================================================
//
//      Public Override methods: ContentGrafPartText
//
// =========================================================================

// -------------------------------------------------------------------------
// ContentGrafPartText --> somInit
//
//     Initialization used at registration time
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartTextsomInit(ContentGrafPartText *somSelf )
{
    SQUAWK("> Invoked ContentGrafPartText::somInit()\n");

    ContentGrafPartTextData *somThis = ContentGrafPartTextGetData(somSelf);
    ContentGrafPartTextMethodDebug("ContentGrafPartText","ContentGrafPartTextsomInit");

    // call parent method
    ContentGrafPartText_parent_ContentGrafPartRect_somInit(somSelf);

    // set the objtype
    somSelf->_set_objType(somGetGlobalEnvironment(), COBJ_GRAFPART_TEXT);

    // set the initial values
    _fFontName   = NULL ;
//  somSelf->_set_fFontName(somGetGlobalEnvironment(), "Roman");
    _fText       = NULL ;
//  somSelf->_set_fText(somGetGlobalEnvironment(), "Text");
    _fFontHeight = 15 ;
    _fFontAngle  = 0 ;
    _fFontFlags  = 0 ;

    SQUAWK("< Leaving ContentGrafPartText::somInit()\n");
}   // somInit()


// -------------------------------------------------------------------------
// ContentGrafPartText --> somUninit
//
//     Uninitialization used at registration time
//
//     -> public override method
//     -> calls parent only
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartTextsomUninit(ContentGrafPartText *somSelf)
{
    SQUAWK("> Invoked ContentGrafPartText::somUninit()\n");

    ContentGrafPartTextData *somThis = ContentGrafPartTextGetData(somSelf);
    ContentGrafPartTextMethodDebug("ContentGrafPartText","ContentGrafPartTextsomUninit");

    ContentGrafPartText_parent_ContentGrafPartRect_somUninit(somSelf);

    if (_fFontName != NULL ) SOMFree(_fFontName) ;
    if (_fText     != NULL ) SOMFree(_fText) ;

    SQUAWK("< Leaving ContentGrafPartText::somUninit()\n");
}   // somUninit()



// -------------------------------------------------------------------------
// ContentGrafPartText --> WriteContents
//
//      Override ContentObject::WriteContents to write local data to a StorageUnit
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartTextWriteContents(   ContentGrafPartText*    somSelf,
                                                            Environment*            ev,
                                                            ODStorageUnit*          toSU,
                                                            BCTransferKind          writeKind,
                                                            BCCloneInfo*            cloneInfo )
{
    SQUAWK("> Invoked ContentGrafPartText::WriteContents()\n");

    ContentGrafPartTextData *somThis = ContentGrafPartTextGetData(somSelf);
    ContentGrafPartTextMethodDebug("ContentGrafPartText","ContentGrafPartTextWriteContents");

    long wklong ;

    // call parent first
    ContentGrafPartText_parent_ContentGrafPartRect_WriteContents( somSelf,
                                                            ev,
                                                            toSU,
                                                            writeKind,
                                                            cloneInfo);

    // Write the local data
    StorageUnitSetValue(toSU, ev, sizeof(long), &_fFontHeight);
    StorageUnitSetValue(toSU, ev, sizeof(long), &_fFontAngle);
    StorageUnitSetValue(toSU, ev, sizeof(long), &_fFontFlags);
    wklong = strlen(_fFontName) ;
    StorageUnitSetValue(toSU, ev, sizeof(long), &wklong);
    StorageUnitSetValue(toSU, ev, wklong,        _fFontName);
    wklong = strlen(_fText) ;
    StorageUnitSetValue(toSU, ev, sizeof(long), &wklong);
    StorageUnitSetValue(toSU, ev, wklong,        _fText);

    SQUAWK("< Leaving Invoked ContentGrafPartText::WriteContents()\n");
}   // ContentGrafPartText::WriteContents()


// -------------------------------------------------------------------------
// ContentGrafPartText --> ReadContents
//
//      Override ContentObject::ReadContents to read local data from a StorageUnit
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartTextReadContents(    ContentGrafPartText*    somSelf,
                                                            Environment*            ev,
                                                            ODStorageUnit*          fromSU,
                                                            BCTransferKind          readKind,
                                                            BCCloneInfo*            cloneInfo )
{
    SQUAWK("> Invoked ContentGrafPartText::ReadContents()\n");

    ContentGrafPartTextData *somThis = ContentGrafPartTextGetData(somSelf);
    ContentGrafPartTextMethodDebug("ContentGrafPartText","ContentGrafPartTextReadContents");

    long wklong ;

    // call parent first
    ContentGrafPartText_parent_ContentGrafPartRect_ReadContents(  somSelf,
                                                            ev,
                                                            fromSU,
                                                            readKind,
                                                            cloneInfo);
    // Read the local data
    StorageUnitGetValue(fromSU, ev, sizeof(long), &_fFontHeight) ;
    StorageUnitGetValue(fromSU, ev, sizeof(long), &_fFontAngle) ;
    StorageUnitGetValue(fromSU, ev, sizeof(long), &_fFontFlags) ;

    StorageUnitGetValue(fromSU, ev, sizeof(long), &wklong     ) ;
    _fFontName = (string) SOMMalloc(wklong+1) ;
    StorageUnitGetValue(fromSU, ev, wklong,        _fFontName  ) ;

    StorageUnitGetValue(fromSU, ev, sizeof(long), &wklong     ) ;
    _fText     = (string) SOMMalloc(wklong+1) ;
    StorageUnitGetValue(fromSU, ev, wklong,       _fText      ) ;

    SQUAWK("< Leaving ContentGrafPartText::ReadContents()\n");
}   // ContentGrafPartText::ReadContents()


// -------------------------------------------------------------------------
// ContentGrafPartText --> DeleteContents
//
//      Override ContentObject::DeleteContents to wipe out local data
//
//     -> public override method
//     -> calls parent first
// -------------------------------------------------------------------------
SOM_Scope void  SOMLINK ContentGrafPartTextDeleteContents(  ContentGrafPartText *somSelf,
                                                            Environment         *ev,
                                                            ODULong             type )
{
    SQUAWK("> Invoked ContentGrafPartText::DeleteContents()\n");

    ContentGrafPartTextData *somThis = ContentGrafPartTextGetData(somSelf);
    ContentGrafPartTextMethodDebug("ContentGrafPartText","ContentGrafPartTextDeleteContents");

    // call parent first
    ContentGrafPartText_parent_ContentGrafPartRect_DeleteContents(somSelf,
                                                                  ev,
                                                                  type);

    // Wipe the local data
    if (_fFontName != NULL ) SOMFree(_fFontName) ;
    if (_fText     != NULL ) SOMFree(_fText)     ;
    _fFontHeight = 0 ;
    _fFontAngle  = 0 ;
    _fFontFlags  = 0 ;

    SQUAWK("< Leaving ContentGrafPartText::DeleteContents()\n");
}   // ContentGrafPartText::DeleteContents()


// -------------------------------------------------------------------------
//  ContentGrafPartText --> Draw
//
//      Put the text onto the screen
//
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   ODBoolean   SOMLINK ContentGrafPartTextDraw(ContentGrafPartText*    somSelf,
                                                        Environment*            ev,
                                                        HDraw                   hDraw )
{
    SQUAWK("> Invoked ContentGrafPartText::Draw()\n");

    ContentGrafPartTextData *somThis = ContentGrafPartTextGetData(somSelf);
    ContentGrafPartTextMethodDebug("ContentGrafPartText","ContentGrafPartTextDraw");

    // set local buffers from persistant data
    ODPoint pt1, pt2;               // buffers for the points
    Rect frameRect;
    pt1 = somSelf->_get_fPt1(ev);   // get origin from parent figure
    pt2 = somSelf->_get_fPt2(ev);   // get endpoint from local instance data


#if defined (_PLATFORM_OS2_)
   // To Be Defined
//  WinSetRect( WinQueryAnchorBlock(HWND_DESKTOP),
//              &frameRect, FixedToInt(rect.left),      //left
//                          FixedToInt(rect.bottom),    //tom
//                          FixedToInt(rect.right),     //right
//                          FixedToInt(rect.top));      //bottom

#elif defined (_PLATFORM_WIN32_)

    SetRect(&frameRect, FixedToInt(min(pt1.x, pt2.x)),  //left
                        FixedToInt(min(pt1.y, pt2.y)),  //top
                        FixedToInt(max(pt1.x, pt2.x)),  //right
                        FixedToInt(max(pt1.y, pt2.y))); //bottom

    // Set up a font for the text
    LOGFONT labelFont;
    memset(&labelFont, 0, sizeof(labelFont));
    labelFont.lfPitchAndFamily = FF_ROMAN; // default proportional font
    labelFont.lfQuality = PROOF_QUALITY;   // quality wins over size

    lstrcpy((LPSTR)labelFont.lfFaceName, _fFontName);
    labelFont.lfHeight      = _fFontHeight ;
    labelFont.lfEscapement  = _fFontAngle  ;
    labelFont.lfOrientation = _fFontAngle  ;

    // Create the font and select it
    HFONT hFont = CreateFontIndirect(&labelFont);
    HFONT hOldFont;
    hOldFont = SelectObject(hDraw, hFont);

    // Write some text on the screen using a transparent background and white text
    SetBkMode(hDraw, TRANSPARENT);
    SetTextColor(hDraw, somSelf->_get_fColor(ev));

    unsigned int dtflags = 0 ;
    if (_fFontFlags & 0x01) dtflags |= DT_LEFT ;
    if (_fFontFlags & 0x02) dtflags |= DT_RIGHT ;
    if (_fFontFlags & 0x04) dtflags |= DT_CENTER ;
    if (_fFontFlags & 0x08) dtflags |= DT_TOP ;
    if (_fFontFlags & 0x10) dtflags |= DT_BOTTOM ;
    if (_fFontFlags & 0x20) dtflags |= DT_VCENTER ;
    if (_fFontFlags & 0x40) dtflags |= DT_SINGLELINE ;
    if (_fFontFlags & 0x80) dtflags |= DT_WORDBREAK ;

    if (dtflags == 0 ) dtflags = DT_LEFT | DT_WORDBREAK ;


    DrawText(hDraw,
             _fText,
             strlen(_fText),
             &frameRect,
             dtflags);

    // Remove the temporary font
    SelectObject(hDraw, hOldFont);
    DeleteObject(hFont);

#endif // _PLATFORM_???_

    SQUAWK("< Leaving ContentGrafPartText::Draw(), returning True\n");
    return(kODTrue);

}   // ContentGrafPartText::Draw()


// -------------------------------------------------------------------------
//  ContentGrafPartText --> _set_fText
//
//      Put the text onto the screen
//
//      -> overrides the SOM-defined shallow copy setter method
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   void  SOMLINK ContentGrafPartText_set_fText(ContentGrafPartText*    somSelf,
                                                        Environment*            ev,
                                                        string                  text)
{
    SQUAWK("> Invoked ContentGrafPartText::_set_fText()\n");

    ContentGrafPartTextData *somThis = ContentGrafPartTextGetData(somSelf);
    ContentGrafPartTextMethodDebug("ContentGrafPartText","ContentGrafPartText_set_fText");

    if (_fText != NULL) SOMFree(_fText) ;
    _fText = (string) SOMMalloc(strlen(text)+1) ;
    strcpy(_fText, text) ;

    SQUAWK("< Leaving ContentGrafPartText::_set_fText()\n");
}

// -------------------------------------------------------------------------
//  ContentGrafPartText --> _set_fFontName
//
//      Put the text onto the screen
//
//      -> overrides the SOM-defined shallow copy setter method
//      -> public override method
//      -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope void SOMLINK ContentGrafPartText_set_fFontName(ContentGrafPartText*    somSelf,
                                                        Environment*            ev,
                                                        string                  name)
{
    SQUAWK("> Invoked ContentGrafPartText::_set_fFontName()\n");

    ContentGrafPartTextData *somThis = ContentGrafPartTextGetData(somSelf);
    ContentGrafPartTextMethodDebug("ContentGrafPartText","ContentGrafPartText_set_fFontName");

    if (_fFontName != NULL) SOMFree(_fFontName) ;
    _fFontName = (string) SOMMalloc(strlen(name)+1) ;
    strcpy(_fFontName, name) ;

    SQUAWK("< Leaving ContentGrafPartText::_set_fFontName()\n");
}

// =========================================================================
// End of file: iodgtext.cpp
// =========================================================================
