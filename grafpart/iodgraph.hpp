// @(#) 1.26 com/src/samples/grafpart/iodgraph.hpp, odgrafpart, od96os2, odos29712d 2/7/97 17:42:03 [3/21/97 17:45:36]
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odgrafpart
 *
 *   CLASSES: none
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
//  File:      iodgraph.hpp
//  Contains:  Constant definitions for a 2D-Drawing Container Part
// ************************************************************************

#ifndef _IODGRAPH_HPP_
#define _IODGRAPH_HPP_

// get the generated message symbol map
#ifndef _H_IODGRAPH_MSG
    #include <iodgraph.h>
#endif  // _H_IODGRAPH_MSG

// ==========================================================
//
//  Locally-defined constants
//
// ==========================================================

// ----------------------------------------------------------
//
// Property constants used in GrafPart --> Initialize
//
// ----------------------------------------------------------
static const   ODType  kGrafPartPresNormal           = "GrafPart:Presentation:Normal";
static const   ODType  kGrafPartPresPalette          = "GrafPart:Presentation:Palette";
static const   ODType  kGrafPartDisplayName          = "Graphics Part";
static const   ODType  kGrafPartPartKind             = "GraphicsPart";
static const   ODType  kGrafPartPartKindDisplayName  = "Graphics Part Kind";
static const   ODType  kGrafPartfilenameFilters      = "";
static const   ODType  kGrafPartfilenameTypes        = "";
static const   ODType  kGrafPartHandlerName          = "GrafPart";
static const   ODType  kGrafPartHandlerDisplayName   = "Graphics Part Handler";
static const   ODType  kGrafPartCategory             = "OpenDoc:Category:Sample";
static const   ODType  kGrafPartCategoryDisplayName  = "Sample";
static const   ODType  kGrafPartobjectID             = "";
static const   ODType  kGrafPartOLE2ClassId          = "{9c93c670-e725-11cf-a634-08005a886bbf}";
static const   ODType  kGrafPartWindowsIconFileName  = "iodgraed.ico";


// ----------------------------------------------------------
//
//  Value constants used in GrafPart
//
// ----------------------------------------------------------
// coordinate plus/minus value for screen selection
#if   defined(_PLATFORM_WIN32_)
    static const SHORT    kODXSelectionThreshold = GetSystemMetrics(SM_CXDOUBLECLK);
    static const SHORT    kODYSelectionThreshold = GetSystemMetrics(SM_CYDOUBLECLK);
#elif defined(_PLATFORM_OS2_)
    static const SHORT    kODXSelectionThreshold = WinQuerySysValue(HWND_DESKTOP,SV_CXDBLCLK);
    static const SHORT    kODYSelectionThreshold = WinQuerySysValue(HWND_DESKTOP,SV_CYDBLCLK);
#endif  // PLATFORM SPECIFIC


// ----------------------------------------------------------
//
//  Value constants used in ContentGrafPartFigr and its subclasses (figures)
//
//      -> CMD_Offset is set to the MENUID_ACTIVEPART_USER as defined in CMDDEFS.XH
//          This is an area reserved for USER defined menuitems.
// ----------------------------------------------------------
static const ODULong  COBJ_GRAFPART_FIGR =  1; // objType constant for ContentGrafPartFigr (figure)
static const ODULong  COBJ_GRAFPART_POIN =  2; // objType constant for ContentGrafPartPoin (point)
static const ODULong  COBJ_GRAFPART_LINE =  3; // objType constant for ContentGrafPartLine (line segment)
static const ODULong  COBJ_GRAFPART_RECT =  4; // objType constant for ContentGrafPartRect (rectangle)
static const ODULong  COBJ_GRAFPART_TEXT =  5; // objType constant for ContentGrafPartText (text)
/*
static const ODULong  COBJ_GRAFPART_ELLI =  6; // objType constant for ContentGrafPartElli (ellipse)
static const ODULong  COBJ_GRAFPART_CIRC =  7; // objType constant for ContentGrafPartCirc (circle)
static const ODULong  COBJ_GRAFPART_PLIN =  8; // objType constant for ContentGrafPartPlin (polyline)
static const ODULong  COBJ_GRAFPART_PGON =  9; // objType constant for ContentGrafPartPgon (polygon)
static const ODULong  COBJ_GRAFPART_FREE = 10; // objType constant for ContentGrafPartFree (freehand)
static const ODULong  COBJ_GRAFPART_IMAG = 11; // objType constant for ContentGrafPartImag (image)
*/
// The following indicates the end of the range of GrafPart intrinsic types for comparisons.
// As new types are implemented, their objType values must be contigious, and the following
// line must be updated to contain the name of last defined objtype value.
static const ODULong  COBJ_GRAFPART_LAST = COBJ_GRAFPART_TEXT;  // the last defined objType constant


// ----------------------------------------------------------
// NLS Message constants used in GrafPart
//
//      ->  The GRAFPART_MSG_SET and GRAFPART_* messages must conform to what
//              is shown in the XPG/4 Message catalog file IODGRAPH.MSG
//      ->  The GP_MSG_* cpp symbols are defined in "iodgraph.h", which is generated
//              from the "iodgraph.msg" file in the locale subdirectories,
//              and shipped to samples/include
// ----------------------------------------------------------
static const char*  GRAFPART_NLS_CATALOG     =  "iodgraph.cat";     // messages are stored in GRAFPART.MSG

static const SHORT  GRAFPART_MSG_SET         =  GP_MSG_SET_ONE;     // message set #1

static const SHORT  GRAFPART_DASH            =  GP_MSG_DASH;        // message "--------"
static const SHORT  GRAFPART_ADD             =  GP_MSG_ADD;         // message "Add Mode"
static const SHORT  GRAFPART_SELECT          =  GP_MSG_SELECT;      // message "Select Mode"
static const SHORT  GRAFPART_EDIT            =  GP_MSG_EDIT;        // message "Edit Mode"
static const SHORT  GRAFPART_REFRESH         =  GP_MSG_REFRESH;     // message "Refresh Screen"
static const SHORT  GRAFPART_MB_WARNING      =  GP_MSG_MB_WARNING;  // warning messages "Don't know how to handle..."
static const SHORT  GRAFPART_ADD_POIN        =  GP_MSG_ADD_POIN;    // message "Point"
static const SHORT  GRAFPART_ADD_LINE        =  GP_MSG_ADD_LINE;    // message "Line"
static const SHORT  GRAFPART_ADD_RECT        =  GP_MSG_ADD_RECT;    // message "Rectangle"
static const SHORT  GRAFPART_ADD_TEXT        =  GP_MSG_ADD_TEXT;    // message "Text"
/*
static const SHORT  GRAFPART_ADD_ELLI        =  GP_MSG_ADD_ELLI;    // message "Ellipse"
static const SHORT  GRAFPART_ADD_CIRC        =  GP_MSG_ADD_CIRC;    // message "Circle"
static const SHORT  GRAFPART_ADD_PLIN        =  GP_MSG_ADD_PLIN;    // message "Polyline"
static const SHORT  GRAFPART_ADD_PGON        =  GP_MSG_ADD_PGON;    // message "Polygon"
static const SHORT  GRAFPART_ADD_FREE        =  GP_MSG_ADD_FREE;    // message "Freehand"
static const SHORT  GRAFPART_ADD_IMAG        =  GP_MSG_ADD_IMAG;    // message "Image"
*/


// ----------------------------------------------------------
//
//  Command constants used in GrafPart
//
//      -> CMD_Offset is set to the MENUID_ACTIVEPART_USER as defined in CMDDEFS.XH
//          This is an area reserved for USER defined menuitems.
// ----------------------------------------------------------
static const SHORT  kODCommandGrafPartDash    = ( CMD_Offset_Subclass + GRAFPART_DASH );
static const SHORT  kODCommandGrafPartAdd     = ( CMD_Offset_Subclass + GRAFPART_ADD );
static const SHORT  kODCommandGrafPartSelect  = ( CMD_Offset_Subclass + GRAFPART_SELECT );
static const SHORT  kODCommandGrafPartEdit    = ( CMD_Offset_Subclass + GRAFPART_EDIT );
static const SHORT  kODCommandGrafPartRefresh = ( CMD_Offset_Subclass + GRAFPART_REFRESH );
static const SHORT  kODCommandGrafPartMenuWarn= ( CMD_Offset_Subclass + GRAFPART_MB_WARNING );
static const SHORT  kODCommandGrafPartAddPoin = ( CMD_Offset_Subclass + GRAFPART_ADD_POIN );
static const SHORT  kODCommandGrafPartAddLine = ( CMD_Offset_Subclass + GRAFPART_ADD_LINE );
static const SHORT  kODCommandGrafPartAddRect = ( CMD_Offset_Subclass + GRAFPART_ADD_RECT );
static const SHORT  kODCommandGrafPartAddText = ( CMD_Offset_Subclass + GRAFPART_ADD_TEXT );
/*
static const SHORT  kODCommandGrafPartAddElli = ( CMD_Offset_Subclass + GRAFPART_ADD_ELLI );
static const SHORT  kODCommandGrafPartAddCirc = ( CMD_Offset_Subclass + GRAFPART_ADD_CIRC );
static const SHORT  kODCommandGrafPartAddPlin = ( CMD_Offset_Subclass + GRAFPART_ADD_PLIN );
static const SHORT  kODCommandGrafPartAddPgon = ( CMD_Offset_Subclass + GRAFPART_ADD_PGON );
static const SHORT  kODCommandGrafPartAddFree = ( CMD_Offset_Subclass + GRAFPART_ADD_FREE );
static const SHORT  kODCommandGrafPartAddImag = ( CMD_Offset_Subclass + GRAFPART_ADD_IMAG );
*/

#endif  // _IODGRAPH_HPP_

// end of file ************************************************************
