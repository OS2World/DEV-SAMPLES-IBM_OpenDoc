/* @(#) 1.54 com/src/samples/basecntr/bcmain.h, odbasepart, od96os2, odos29714c 3/25/97 13:46:05 [4/2/97 17:20:01] */

//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odsamples
//
//   CLASSES: none
//
//   ORIGINS: 82,27
//
//
//   (C) COPYRIGHT International Business Machines Corp. 1995,1996
//   All Rights Reserved
//   Licensed Materials - Property of IBM
//   US Government Users Restricted Rights - Use, duplication or
//   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//
//   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
//   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
//   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
//   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
//   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
//   OR PERFORMANCE OF THIS SOFTWARE.
//
//====END_GENERATED_PROLOG========================================
//


#ifndef BaseContainer_Header
#define BaseContainer_Header



// CMD_Offset is set to the MENUID_ACTIVEPART_USER as defined in CMDDEFS.XH
// This is an area reserved for USER defined menuitems.


#define CMD(X)    kODCommand##X

#define CMD_Offset                 MENUID_ACTIVEPART_USER
const   ODMenuID  kODEmbedMenuID = CMD_Offset;
#define kODCommandDash             (CMD_Offset+1)
#define kODCommandMove             (CMD_Offset+2)
#define kODCommandMoveFront        (CMD_Offset+3)
#define kODCommandMoveBack         (CMD_Offset+4)
#define kODCommandResize           (CMD_Offset+5)
#define kODCommandHelp             (CMD_Offset+6)
const   ODMenuID  kODOptionsMenuID = (CMD_Offset+60);
#define kODCommandColorCHANGE        (CMD_Offset+61)

#define kODCommandParts            (CMD_Offset+400)
#define CMD_Offset_Subclass        (CMD_Offset+500)

#define kODErrCannotInitializePart 3001

// Property names
#define kODPropBackgroundColor     "+//ISO 9070/ANSI::113722::US::CI LABS::IBM:Property:BackgroundColor"
static const ODPropertyName kPropBackground = "+//ISO 9070/ANSI::113722::US::CI LABS::IBM:Value:NTColor";
// the below definition was removed per DEFECT 22908 and added to StdDefs.idl
//#define kODPropEmbeddedFrames     "BaseContainer:Property:EmbeddedFrames"

// Frame List Value Type
const ODValueType kODFrameList = "+//ISO 9070/ANSI::113722:US::CI LABS:MacOS:Type:FrameList";

// Frame List User String
#define kODFrameListUserString "Frame List"


#define kBaseContainerPartKind                  "IBM:BaseContainer:PartKind"
#define kBaseContainerPartHandlerName           "BaseContainer"
#define kBaseContainerPartHandlerDisplayName    "IBM Base ContainerPart"
const   ODType   kBaseContainerPartKindDisplayName = "IBM BaseContainer Kind";
const   ODType   kBaseContainerPartCategory        = "Container";

static const ODPropertyName kBCSuggestedTransform = "BaseContainer:Transform";


// ----------------------------------------------------------
// NLS Message constants used in BaseContainer --> Initialize
//
//      The BCMSG_SET and BC_* messages must conform to what
//      is shown in the XPG/4 Message catalog file BCPART.MSG
// ----------------------------------------------------------

#include <locale.h>
#include <wchar.h>
#include <ODDebug.h>

#define BC_NLS_CATALOG "iodbasec.cat" // BCPART Messages are stored in IODBASEC.MSG
#include <iodbasec.h>                 // BC_* constants are defined in IODBASEC.H

#if !(defined(__IBMCPP__) || defined(_IBMR2))
typedef ODPtr nl_catd;
#endif

// PLATFORMSTRID macro. Used to determine catalog string to read for menu
// items requiring mnemonics. There will be one string and BC_ constant pair
// for each platform. Constants end with _OS2, _WIN, or _AIX to differentiate
// amongst them.
#ifdef _PLATFORM_OS2_
   #define PLATFORMSTRID(X)      X##_OS2
#elif defined(_PLATFORM_WIN32_)
   #define PLATFORMSTRID(X)      X##_WIN
#else
   #define PLATFORMSTRID(X)      X##_UNX
#endif

#ifdef _PLATFORM_OS2_
typedef HPS HDraw;
typedef HBITMAP HIconView;
typedef HBITMAP HThumbView;
typedef HMODULE HResModule;

#elif defined(_PLATFORM_WIN32_)
typedef HDC HDraw;
typedef HICON HIconView;
typedef HBITMAP HThumbView;
typedef HINSTANCE HResModule;

#elif defined(_PLATFORM_UNIX_)
typedef GC HDraw;
typedef Pixmap HIconView;
typedef Pixmap HThumbView;
typedef int HResModule;
#endif


// mouse position displayed for insertion point of dropped or pasted data

#define BC_NPOINTS 5            // # of points to make a cross hair mark

#if defined(_PLATFORM_OS2_)      // defines in platform specific terms,
typedef long COLORREF;           // those variables that are WIN specific
typedef POINTL POINT;
#endif
#if defined(_PLATFORM_UNIX_)
typedef Pixel COLORREF;
typedef XPoint POINT;
#define MAX_PIXEL 5;             // arbitrary maximum distance allowed in points
#endif                           // for mouse mvmt to still be part of a dblclk

// Data structure stored with frame to hold frame-specific values
typedef struct
{
    ODBoolean NeedsActivating;
    COLORREF  BgndColor;             // remember the frame's Bgnd color
#if defined (_PLATFORM_OS2_)
    ODRect  frameRect;
#endif
} FramePartInfo;

typedef struct
{
    POINT           hotSpot;
    unsigned short  simEvent;
    POINT           maxDistance;
    ODRect          frameRect;
    ODEventData     event;
    ODEventInfo     eventInfo;
} BC_MOUSETRACK;

typedef struct
{
    ODPoint offset;
    ODPoint extent;
    ODPoint scale;
    ODULong numFrames;
} FrameListHeader;

#define DEFAULT_EMBED_WIDTH 100  // default width of a part created from embed menu
#define DEFAULT_EMBED_HEIGHT 100  // default height of a part created from embed menu

// Mouse modes to be used for tracking edit operations
#define kMouseModeNull 0
#define kMouseModeEmbedFromMenu 1
#define kMouseModeTrackMove 2
#define kMouseModeTrackResize 3
#define kMouseModeTrackPaste 4
#define kMouseModeTrackPasteAs 5
#define kMouseModeTrackMouseMove 6
#define kMouseModeTrackMouseResize 7
#define kMouseModeTrackLassoSelect 8

// Constants for defining the selection border
#if defined(_PLATFORM_WIN32_)
#define MAKEFIXED(h, l)  ((ULONG) ( ((USHORT)(l)) | ((ULONG)((USHORT)(h))) << 16) )
#elif defined(_PLATFORM_UNIX_)
#define MAKEFIXED(h, l)  ((unsigned long) ( ((unsigned short)(l)) | ((unsigned long)((unsigned short)(h))) << 16) )
#endif


typedef enum BC_CHANGE {BCC_EMBED, BCC_PASTE, BCC_PASTEAS, BCC_RESIZE, BCC_MOVE,
                        BCC_DELETE, BCC_INTRINSIC, BCC_EMBEDUPDATED, BCC_DROP, BCC_EMBEDSHAPECHANGED};

typedef enum BC_RECTDRAWTYPE {BCR_REDRAW, BCR_ERASE};

const ODSLong kODBorderWidth = MAKEFIXED(4,0);
const ODSLong kODHandleLenMultiplier = 3;

#define kBCSingleClick 1
#define kBCMouseDrag 2

#define ODDeleteObject(OBJ) \
     if( !(OBJ) ) ; else { delete (OBJ); (OBJ)=kODNULL; }


// Convert color in 0x00RRGGBB format to 0x00BBGGRR format and vice-versa
#define ExchangeRedAndBlue(color) \
     color = ((color & 0x0000FF) << 16) | (color & 0x00FF00) | ((color & 0xFF0000) >> 16);


#endif
