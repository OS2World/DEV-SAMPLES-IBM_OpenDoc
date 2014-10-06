/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odshapepart
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
/* @(#)Z 1.9 com/src/samples/shape/iodshape.h, odshapepart, od96nt, odnt9708d 97/02/25 13:39:49 (97/02/12 16:06:38) */
#ifndef _SHAPEPRT_H_
#define _SHAPEPRT_H_



// Constants used for Part Registration
const ODType   kODKindShapePart          = "ShapePart";
const ODType   kShapePartKindDisplayName = "ShapePart Kind";
const ODType   kShapePartHandlerName     = "ShapePart";
const ODType   kShapePartHandlerDisplayName  = "Shape Part";
const ODType   kShapePartCategory        = "OpenDoc:Category:Sample";
const ODType   kShapePartIconFileName    = "IODShape.ico";

#define kShapePartDLLName "iodshape"

// Constants for menu items
#define kShapePartBGColorMenuID (MENUID_ACTIVEPART_USER + 3)       // Simple Part uses +1,+2

// Constants for NLS catalog and messages
#define SHAPE_MSG_CATALOG        "iodshape.cat"  // ShapePart Messages are stored in iodshpe.msg

//default messages
#define SHAPE_DEFMSG_COLORMENU   "Background Color..."
#define SHAPE_DEFMSG_HELPMENU    "Shape Part help"
#define SHAPE_DEFMSG_INFOMENU    "Shape Part information"
#define SHAPE_DEFMSG_INFOTITLE   "Shape Part Information"
#define SHAPE_DEFMSG_INFO        "Shape Part Version 1.0\n\
Copyright International Business Machines Corporation 1996,1997. \
All rights reserved."

// Constants for Help
#define SHAPE_HELP_FILE          "iodshape.hlp"
#define SHAPE_HELP_PANEL         100

// platform specific typedefs

#ifdef _PLATFORM_WIN32_

#define kShapePartDefaultColor  0x000000FF

#elif _PLATFORM_OS2_

typedef long COLORREF;
#define kShapePartDefaultColor  0x00FF0000

#elif _PLATFORM_UNIX_

typedef Pixel COLORREF;
#define kShapePartDefaultColor  0x000000FF

#endif

// end typedefs

// os2 color dialog constants
#ifdef _PLATFORM_OS2_

#define RED                 0
#define GREEN               1
#define BLUE                2

#define COLORMIX          "ColorMix"
#define ID_COLORS         4108
#define ID_BCICON         100
#define ID_MIX            20
#define ID_LABEL_RED      21
#define ID_LABEL_GREEN    22
#define ID_LABEL_BLUE     23
#define ID_SLIDER_BASE    24
#define ID_SLIDER_RED     (ID_SLIDER_BASE + RED)
#define ID_SLIDER_GREEN   (ID_SLIDER_BASE + GREEN)
#define ID_SLIDER_BLUE    (ID_SLIDER_BASE + BLUE)
#define ID_SPIN_BASE      28
#define ID_SPIN_RED       (ID_SPIN_BASE + RED)
#define ID_SPIN_GREEN     (ID_SPIN_BASE + GREEN)
#define ID_SPIN_BLUE      (ID_SPIN_BASE + BLUE)

#endif // os2 color dialog


// Undo-Redo strings
#define kShapePartUndoBGColor  "Undo Background Color"
#define kShapePartRedoBGColor  "Redo Background Color"

#define UNDO_BGCOLOR 1

// struct for undo/ redo

typedef struct shapepartundorec {

   unsigned long undoAction;
   COLORREF newColor;
   COLORREF oldColor;

} ShapePartUndoRec;

#endif
