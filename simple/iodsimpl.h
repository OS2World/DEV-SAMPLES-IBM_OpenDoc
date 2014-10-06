/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odsimplepart
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
// @(#)Z 1.10 com/src/samples/simple/iodsimpl.h, odsimplepart, od96os2, odos29712d 97/03/21 17:45:33 (97/02/14 11:53:25)
//====START_GENERATED_PROLOG======================================
//
//
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

#ifndef _SIMPLPRT_
#define _SIMPLPRT_

// ----------------------------------------------------------
// NLS Message constants used in SimplePart --> InstallMenus
//
//   The SP_MSG_SET and SPMSG_* messages must conform to what
//   is shown in the XPG/4 Message catalog file IODSIMPL.MSG
// ----------------------------------------------------------

#include <locale.h>
#include <wchar.h>
#include <iodsmple.h>                   // message catalog includes.

#define SP_MSG_CATALOG  "iodsmple.cat"  // SimplePart Messages are stored in IODSIMPL.MSG

// Default messages
#define SP_DEFMSG_HELPMENU       "Simple Part help"
#define SP_DEFMSG_INFOMENU       "Simple Part information"
#define SP_DEFMSG_INFOTITLE      "Simple Part Information"
#define SP_DEFMSG_INFO   "Simple Part Version 1.0\n\
Copyright of International Business Machines Corporation 1996,1997. \
All rights reserved."

// SimplePart's Menu Item IDs
#define CMD_Offset                               MENUID_ACTIVEPART_USER
#define kSimplePartMenuSeparator                 CMD_Offset
#define kSimplePartHelpMenu                     (CMD_Offset + 1)
#define kSimplePartInfoMenu                     (CMD_Offset + 2)
#define CMD_Offset_Subclass                     (CMD_Offset+100)

// Help related constants
#define SP_HELP_FILE     "iodsimpl.hlp"  // SimplePart help file
#define SP_HELP_PANEL    100

// Constant used in drawing diagonal lines
#define DELTA 32

#ifdef _PLATFORM_UNIX_

// UNIX Definition of SimplePart's large icon
#define simpl32_width 32
#define simpl32_height 32
static char simpl32_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x07,
   0xfc, 0xff, 0xff, 0x07, 0xfc, 0xff, 0xff, 0x2f, 0xfc, 0xff, 0xff, 0x17,
   0xfc, 0xff, 0xff, 0x2f, 0xfc, 0xff, 0xff, 0x17, 0xfc, 0xff, 0xff, 0x2f,
   0xfc, 0xff, 0xff, 0x17, 0xfc, 0xff, 0xff, 0x2f, 0xfc, 0xff, 0xff, 0x17,
   0xfc, 0xff, 0xff, 0x2f, 0xfc, 0xff, 0xff, 0x17, 0xfc, 0xff, 0xff, 0x2f,
   0xfc, 0xff, 0xff, 0x17, 0xfc, 0xff, 0xff, 0x2f, 0xfc, 0xff, 0xff, 0x17,
   0xfc, 0xff, 0xff, 0x2f, 0xfc, 0xff, 0xff, 0x17, 0xfc, 0xff, 0xff, 0x2f,
   0xfc, 0xff, 0xff, 0x17, 0xfc, 0xff, 0xff, 0x2f, 0xfc, 0xff, 0xff, 0x17,
   0xfc, 0xff, 0xff, 0x2f, 0xfc, 0xff, 0xff, 0x17, 0xfc, 0xff, 0xff, 0x2f,
   0x50, 0x55, 0x55, 0x15, 0xa0, 0xaa, 0xaa, 0x2a, 0x50, 0x55, 0x55, 0x15,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// UNIX Definition of SimplePart's small icon
#define simpl16_width 16
#define simpl16_height 16
static char simpl16_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0xfc, 0x5f, 0xfc, 0x3f, 0xfc, 0x5f,
   0xfc, 0x3f, 0xfc, 0x5f, 0xfc, 0x3f, 0xfc, 0x5f, 0xfc, 0x3f, 0xfc, 0x5f,
   0xfc, 0x3f, 0x50, 0x55, 0xa8, 0x2a, 0x00, 0x00};

#endif // UNIX

#ifdef _PLATFORM_OS2_
#include <ODos2.h>
#endif

#include "ODTypes.h"       // for ODBoolean, ODRect, Rect

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
typedef int HIconView;
typedef int HThumbView;
typedef int HResModule;
#endif

typedef struct {
   ODBoolean  fIsActive;                // Does this frame have its focus set?
   ODBoolean  fNeedsActivating;         // should this be activated when its window is activated?
   ODBoolean  fIsPopupMenu;             // Is this a popup menu ?
   ODBoolean  fIsSelected;              // Is this the selected frame?
   void*      pOther;                   // reserved for subclass use
} PartInfoRec;

class ODFrame;
class ODTransform;

typedef enum {SmallIconView, LargeIconView, ThumbnailView, FrameView} ViewTypeEnum;

#endif // _SIMPLPRT_
