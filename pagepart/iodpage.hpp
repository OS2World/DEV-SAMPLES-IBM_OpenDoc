//   @(#) 1.5 com/src/samples/pagepart/iodpage.hpp, odpagepart, od96os2, odos29712d 11/8/96 18:18:48 [3/21/97 17:48:59]
//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME:     odpagepart
//
//   CLASSES: none
//
//   ORIGINS: 27
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


#ifndef PageLayout_Header
#define PageLayout_Header

/**********************************************************************************
CONSTANTS AND TYPE DEFINITIONS
**********************************************************************************/

#define kPartHandlerName                   "PageLayout"
#define kPartHandlerDisplayName            "Page Layout"
#define kPartKindName                      "PageLayout"
#define kPartKindDisplayName               "Page Layout Kind"
#define kPartCategoryName                  "Layout"
#define kPartCategoryDisplayName           "Layout"
#define kWindowsIcon                       "IODPage.ico"
#define kPagePartDefaultFont               "9.WarpSans"
// #define kPagePartMRIFileName               "IODPage.dll" //.dll extension causes it not to search LIBPATH???
#define kPagePartMRIFileName               "IODPage"

#define PAGE_WIDTH         612   /* 72 * 8.5 */
#define PAGE_HEIGHT        792   /* 72 * 11 */

#define HALF_CHAR_SIZE     4

#define GRID_SPACING       36

#define DOWN               -1
#define UP                 1

#define NONE               0
#define TOP_LEFT           1
#define TOP_CENTER         2
#define TOP_RIGHT          3
#define BOTTOM_LEFT        4
#define BOTTOM_CENTER      5
#define BOTTOM_RIGHT       6

#define INCHES             0
#define METRIC             1

#define DOTS               0
#define DASH               1
#define DASHDOT            2
#define DASHDOUBLEDOT      3
#define SOLID              4

#define INCH_LENGTH        72.0
#define CENTIMETER_LENGTH  72.0/2.54

#define EIGHTH_INCH_MARK   3
#define CENTIMETER_MARK    10
#define TICK_MARK_SIZE     14

#define RULER_UNIT_OFFSET  5

#define VERT_RULER_OFFSET  22
#define HORZ_RULER_OFFSET  22

#define LEFT_PAGE_OFFSET   40
#define RIGHT_PAGE_OFFSET  20
#define BOTTOM_PAGE_OFFSET 32
#define TOP_PAGE_OFFSET    40

#define LEFT_MARGIN        54    /* 72 * (3/4) */
#define RIGHT_MARGIN       54    /* 72 * (3/4) */
#define BOTTOM_MARGIN      54    /* 72 * (3/4) */
#define TOP_MARGIN         54    /* 72 * (3/4) */


#ifndef ODPrintExtension_Header
//jwa: Following two strings must stay here - do not move to pagemri.rc
//     (since they are displayed when we can't get at our string table)
#define ResourceErrorMsg   "Unable to load resources (pagemri.dll)!"
#define StringNotFoundMsg  "Message not found"
#endif //ODPrintExtension_Header


/**********************************************************************************
SIMPLE HELPER MACRO DEFINITIONS
**********************************************************************************/
#define PowerOf2(x)        (1 << (x))
#define kNoBias            kODNULL
#endif //PageLayout_Header

