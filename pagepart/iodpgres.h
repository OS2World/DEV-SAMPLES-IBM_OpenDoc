/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odpagepart
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
//   @(#) 1.5 com/src/samples/pagepart/iodpgres.h, odpagepart, od96os2, odos29712d 11/4/96 06:02:40 [3/21/97 17:49:00]

#ifndef _IODPAGE_RESOURCE_HEADER_
#define _IODPAGE_RESOURCE_HEADER_

#define UNUSED                      0

#define PAGEICON                    1

#define PagePartDefaultFont         "9.WarpSans"

#define ChoosePageDlgValue          100
#define ChoosePageSpinButton        101
#define ChoosePageEntryField        102

#define GoToPageDlgValue            150
#define InsertPageDlgValue          151
#define RemovePageDlgValue          152

#define GetTextDlgValue             200
#define GetTextEntryField           201

#define HeaderDlgValue              250
#define FooterDlgValue              251

#define PartInfoDlgValue            300

#define PageMenuString              400
#define ColorMenuString             401
#define FillPageString              402
#define SnapToGridString            403
#define ShowGridString              404
#define ShowRulersString            405
#define ShowMarginsString           406
#define RefreshString               407
#define PartInfoString              408

#define GoToPageErrorMsg            500
#define MaxPageString               501

#define GoToPageDlgTitle            600
#define InsertPageDlgTitle          601
#define RemovePageDlgTitle          602

#define HeaderDlgTitle              700
#define FooterDlgTitle              701

#if 0
#define kPartHandlerDisplayName     900
#define kPartHandlerKindDisplayName 901
#define kPartHandlerCategoryDisplayName 902
#endif

/* Beginning of Menu ID definitions */
/* MENUID_ACTIVEPART_USER == 0x6F00 */
/* We start at 0x7F00 to avoid collisions with BaseContainer */
#define PageMenuID                  0x7F00
#define ColorMenuID                 0x7F01

#define MenuInsertPage              0x7F10
#define MenuInsertPageLast          0x7F11
#define MenuRemovePage              0x7F12
#define MenuGoToPage                0x7F13
#define MenuPageNumberPosition      0x7F14
#define MenuRulerUnits              0x7F15
#define MenuMarginLineType          0x7F17
#define MenuGridLineType            0x7F18
#define MenuHeader                  0x7F19
#define MenuFooter                  0x7F1A

#define MenuPageNumberTopLeft       0x7F20
#define MenuPageNumberTopCenter     0x7F21
#define MenuPageNumberTopRight      0x7F22
#define MenuPageNumberBottomLeft    0x7F23
#define MenuPageNumberBottomCenter  0x7F24
#define MenuPageNumberBottomRight   0x7F25
#define MenuPageNumberNone          0x7F26

#define MenuRulerInches             0x7F30
#define MenuRulerCentimeters        0x7F31

#define MenuMarginDots              0x7F40
#define MenuMarginDash              0x7F41
#define MenuMarginDashDot           0x7F42
#define MenuMarginDashDoubleDot     0x7F43
#define MenuMarginSolid             0x7F44

#define MenuGridDots                0x7F50
#define MenuGridDash                0x7F51
#define MenuGridDashDot             0x7F52
#define MenuGridDashDoubleDot       0x7F53
#define MenuGridSolid               0x7F54

#define MenuShowGrid                0x7F60
#define MenuShowRulers              0x7F61
#define MenuShowMargins             0x7F62
#define MenuRefresh                 0x7F63

#define MenuPartInfo                0x7F70

#define MenuFillPage                0x7F80
#define MenuSnapToGrid              0x7F81

#define MenuBackgroundColor         0x7F90
#define MenuPageColor               0x7F92
#define MenuTextColor               0x7F91
#define MenuRulersColor             0x7F93
#define MenuMarginsColor            0x7F94
#define MenuGridColor               0x7F95

#define MenuSeparator               0x7FF0
#define MenuSeparator2              0x7FF1
#define MenuSeparator3              0x7FF2
#define MenuSeparator4              0x7FF3
#define MenuSeparator5              0x7FF4
#define MenuSeparator6              0x7FF5
/* Ending of Menu ID definitions */


#ifndef BS_NOTEBOOKBUTTON
#define BS_NOTEBOOKBUTTON           8
#endif

/* IDs of help panels */
#define PAGE_HELP                   33476
#define MARGIN_HELP                 33435
#define HEADERFOOTER_HELP           33472
#define GRID_HELP                   33464
#define RULER_HELP                  33484
#define COLOR_HELP                  33459
#define COLOR_GRID_HELP             33471

#define PRINTER_SETUP_MENU_HELP     33501
#define PRINT_MENU_HELP             33502
#define FILL_ENTIRE_PAGE_MENU_HELP  33503
#define ARRANGE_MENU_HELP           33504
#define MOVE_TO_FRONT_MENU_HELP     33505
#define MOVE_TO_BACK_MENU_HELP      33506
#define MOVE_FORWARD_MENU_HELP      33507
#define MOVE_BACKWARD_MENU_HELP     33509
#define SCALE_MENU_HELP             33510
#define ROTATE_MENU_HELP            33511
#define RESET_MENU_HELP             33512
#define SHOW_GRID_MENU_HELP         33412
#define SHOW_MARGINS_MENU_HELP      33413
#define SHOW_RULERS_MENU_HELP       33414
#define INSERT_PAGE_MENU_HELP       33416
#define INSERT_PAGE_LAST_MENU_HELP  33417
#define REMOVE_PAGE_MENU_HELP       33513
#define GOTO_PAGE_MENU_HELP         33418
#define PAGE_COLOR_MENU_HELP        33460
#define BACKGROUND_COLOR_MENU_HELP  33461
#define SNAP_TO_GRID_MENU_HELP      33432
#define PAGE_LAYOUT_INFO_MENU_HELP  33514
#define PAGE_LAYOUT_GENERAL_HELP    33516
#define AVAILABLE_PRINTERS_HELP     33517
#define BACKGROUND_MENU_HELP        1007
#define TRANSPARENT_MENU_HELP       1008
#define OPAQUE_MENU_HELP            1009
#define PAGE_MENU_HELP              1010

#endif //_IODPAGE_RESOURCE_HEADER
