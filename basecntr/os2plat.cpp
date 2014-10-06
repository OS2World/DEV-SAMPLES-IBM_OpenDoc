/* @(#) 1.6 os2/src/samples/basecntr/os2plat.cpp, odbasepart, od96os2, odos29712d 2/25/97 22:19:07 [3/21/97 17:42:03] */

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
//   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
//   OR PERFORMANCE OF THIS SOFTWARE.
//
//====END_GENERATED_PROLOG========================================

#define INCL_DOSMODULEMGR 
#define INCL_GPILOGCOLORTABLE 
#define INCL_WINDIALOGS 
#define INCL_WINMENUS 
#define INCL_WINSTDSLIDER 
#define INCL_WINSTDSPIN 
#define INCL_WINWINDOWMGR 
#include <ODos2.h> 
#include "iodbcres.h" 
 
extern "C" MRESULT EXPENTRY ColorProc( HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2 ); 
extern "C" MRESULT EXPENTRY fnwpColorSample( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 ); 
 
// Array of binary values for RGB value 
SHORT RGBColors[3] = {0, 0, 0}; 
 
// Array of fill color for sliders 
LONG RibbonColors[3] = {CLR_DARKRED, CLR_DARKGREEN, CLR_DARKBLUE}; 
LONG ShaftColors[3]  = {CLR_RED,     CLR_GREEN,     CLR_BLUE    }; 
 
// Composite color value 
LONG  Color = 0; 
 
const unsigned long ColorChoices = 9; 
/* 
 * Local method to display values of property in a modal window 
 * returning a non-empty string if value selected.  Return value 
 * is return value from WinDlgBox 
 */ 
 
BOOL ColorWindow(HMODULE dllHandle, HWND ParentWindow, SHORT *BakColor) 
{ 


    // take initial background color to start
      RGBColors[RED]   = BakColor[RED];
      RGBColors[GREEN] = BakColor[GREEN];
      RGBColors[BLUE]  = BakColor[BLUE];

    // Register a window class to handle the user control 
    WinRegisterClass(WinQueryAnchorBlock(ParentWindow), 
                     "ColorMix", 
                     fnwpColorSample, 
                     0L, 
                     0); 
 
    // Execute color dialog passing in the current color value 
    ULONG rc = WinDlgBox(HWND_DESKTOP,
                         ParentWindow,
                         ColorProc,
                         dllHandle,
                         ID_COLORS,
                         0); 
 
    // If user terminated with the OK button 
    if (rc != DID_CANCEL) 
    {
     BakColor[RED] = RGBColors[RED];
     BakColor[GREEN] = RGBColors[GREEN];
     BakColor[BLUE] = RGBColors[BLUE]; 
     return 0;
    }
 
    // If canceled then don't change color
    return 1; 
} 
 
 
MRESULT EXPENTRY ColorProc( HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2 ) 
{ 
 // This global variable prevents us from infinitely looping setting PM control 
 // values.  The slider set the spin button and the spin button sets the 
 // slider. 
 static boolean Setting = FALSE; 
 
  // Switch on the PM message type 
  switch (msg) 
  { 
    // case Initialize dialog 
    case WM_INITDLG: 
    { 
      // We're setting values 
      Setting = TRUE; 
 
      // For all three colors 
      for (int Index = RED; 
           Index <= BLUE; 
           Index++) 
      { 
        // Set spin fields range from 0 to 255 
        WinSendDlgItemMsg(hwndDlg, 
                          ID_SPIN_RED + Index, 
                          SPBM_SETLIMITS, 
                          MPFROMLONG(255), 
                          MPFROMLONG(0)); 
 
        // Initialize slider 
        WinSendDlgItemMsg(hwndDlg, 
                          ID_SLIDER_RED + Index, 
                          SLM_SETSLIDERINFO, 
                          MPFROM2SHORT(SMA_SLIDERARMPOSITION, 
                                       SMA_INCREMENTVALUE), 
                          MPFROMSHORT(RGBColors[Index])); 
 
        // Set spin field 
        WinSendDlgItemMsg(hwndDlg, 
                          ID_SPIN_RED + Index, 
                          SPBM_SETCURRENTVALUE, 
                          MPFROMLONG((long) RGBColors[Index]), 
                          0); 
      } 
 
      // Invalidate the mix window so it will repaint 
      WinInvalidateRect(WinWindowFromID(hwndDlg, 
                                        ID_MIX), 
                        NULL, 
                        FALSE); 
 
      // No longer setting values 
      Setting = FALSE; 
 
      break; 
    } 
 
    // Case draw item for owner drawn portion of sliders 
    case WM_DRAWITEM: 
    { 
      // Get control identifier 
      SHORT ID = SHORT1FROMMP(mp1); 
 
      // Switch on the control identifier 
      switch (ID) 
      { 
        // case red, green or blue slider 
        case ID_SLIDER_RED: 
        case ID_SLIDER_GREEN: 
        case ID_SLIDER_BLUE: 
          { 
            // Get owner item structure 
            POWNERITEM POwnerItem = (POWNERITEM) PVOIDFROMMP(mp2); 
 
            // If drawing the ribbon strip 
            if (POwnerItem->idItem == SDA_RIBBONSTRIP) 
            { 
              // Get color index 
              int Index = ID - ID_SLIDER_RED; 
 
              // Fill in the ribbon strip with appropriate color 
              WinFillRect(POwnerItem->hps, 
                          &POwnerItem->rclItem, 
                          RibbonColors[Index]); 
 
              // Return TRUE so the slider won't draw its own ribbon strip 
              return (MRESULT) TRUE; 
            } 
            else 
            { 
              // If drawing the slider shaft 
              if (POwnerItem->idItem == SDA_SLIDERSHAFT) 
              { 
                // Get color index 
                int Index = ID - ID_SLIDER_RED; 
 
                // Fill in the slider shaft with appropriate color 
                WinFillRect(POwnerItem->hps, 
                            &POwnerItem->rclItem, 
                            ShaftColors[Index]); 
 
                // Return TRUE so the slider won't draw its own slider shaft 
                return (MRESULT) TRUE; 
              } 
            } 
          } 
 
          break; 
      } 
 
      break; 
    } 
 
    // case Command 
    case WM_COMMAND: 
 
      // switch on the dialog item 
      switch (SHORT1FROMMP(mp1)) 
      { 
        // case OK 
        // case Cancel 
        case DID_OK: 
        case DID_CANCEL: 
 
          // Dismiss the dialog 
          WinDismissDlg(hwndDlg, (ULONG) SHORT1FROMMP(mp1)); 
 
          break; 
 
        // default case 
        default: 
 
          // get PM's default procedure to handle the request 
          return WinDefDlgProc(hwndDlg, 
                               msg, 
                               mp1, 
                               mp2); 
 
          break; 
      } 
 
      break; 
 
    // case Control 
    case WM_CONTROL: 
    { 
      // Get control identifier 
      SHORT ID = SHORT1FROMMP(mp1); 
 
      // switch on the dialog item 
      switch (ID) 
      { 
        // case red, green or blue slider 
        case ID_SLIDER_RED: 
        case ID_SLIDER_GREEN: 
        case ID_SLIDER_BLUE: 
 
          // switch on the PM action 
          switch (SHORT2FROMMP(mp1)) 
          { 
            // case slider change 
            case SLN_CHANGE: 
            case SLN_SLIDERTRACK: 
            { 
              // If not already setting values 
              if (Setting == FALSE) 
              { 
                // Get index for red, green, blue 
                SHORT Index = ID - ID_SLIDER_RED; 
 
                // get the new color value 
                RGBColors[Index] = SHORT1FROMMR(WinSendDlgItemMsg(hwndDlg, 
                                                ID, 
                                                SLM_QUERYSLIDERINFO, 
                                                MPFROM2SHORT(SMA_SLIDERARMPOSITION, 
                                                             SMA_INCREMENTVALUE), 
                                                MPFROMLONG(0))); 
 
                // We're setting values 
                Setting = TRUE; 
 
                // Set corresponding spin button 
                WinSendDlgItemMsg(hwndDlg, 
                                  ID_SPIN_RED + Index, 
                                  SPBM_SETCURRENTVALUE, 
                                  MPFROMLONG((long) RGBColors[Index]), 
                                  0); 
 
                // We're no longer setting values 
                Setting = FALSE; 
 
                // invalidate the mix window so it will get redrawn 
                WinInvalidateRect(WinWindowFromID(hwndDlg, 
                                                  ID_MIX), 
                                  NULL, 
                                  FALSE); 
              } 
 
              break; 
            } 
 
            // default case 
            default: 
 
              // get PM's default procedure to handle the request 
              return WinDefDlgProc(hwndDlg, 
                                   msg, 
                                   mp1, 
                                   mp2); 
 
              break; 
          } 
          // endswitch - switch on the PM action 
 
          break; 
 
        // case red, green or blue spin button 
        case ID_SPIN_RED: 
        case ID_SPIN_GREEN: 
        case ID_SPIN_BLUE: 
 
          // switch on the PM action 
          switch (SHORT2FROMMP(mp1)) 
          { 
            // case value change 
            case SPBN_CHANGE: 
            { 
              // If not already setting values 
              if (Setting == FALSE) 
              { 
                // Get index for red, green, blue 
                SHORT Index = ID - ID_SPIN_RED; 
 
                // get the new color value 
                long NewValue; 
                WinSendDlgItemMsg(hwndDlg, 
                                  ID, 
                                  SPBM_QUERYVALUE, 
                                  MRFROMP(&NewValue), 
                                  MRFROM2SHORT(0, 
                                               SPBQ_ALWAYSUPDATE)); 
                RGBColors[Index] = (SHORT) NewValue; 
 
                // We're setting values 
                Setting = TRUE; 
 
                // Set slider value 
                WinSendDlgItemMsg(hwndDlg, 
                                  ID_SLIDER_RED + Index, 
                                  SLM_SETSLIDERINFO, 
                                  MPFROM2SHORT(SMA_SLIDERARMPOSITION, 
                                               SMA_INCREMENTVALUE), 
                                  MPFROMSHORT(RGBColors[Index])); 
 
                // We're no longer setting values 
                Setting = FALSE; 
 
                // invalidate the mix window so it will get redrawn 
                WinInvalidateRect(WinWindowFromID(hwndDlg, 
                                                  ID_MIX), 
                                  NULL, 
                                  FALSE); 
              } 
              else 
 
              break; 
            } 
 
            // default case 
            default: 
 
              // get PM's default procedure to handle the request 
              return WinDefDlgProc(hwndDlg, 
                                   msg, 
                                   mp1, 
                                   mp2); 
 
              break; 
          } 
          // endswitch - switch on the PM action 
 
          break; 
 
        // default case 
        default: 
 
          // get PM's default procedure to handle the request 
          return WinDefDlgProc(hwndDlg, 
                               msg, 
                               mp1, 
                               mp2); 
 
          break; 
      } 
      // endswitch - switch on the dialog item 
      break; 
    } 
 
    // default case 
    default: 
 
      // get PM's default procedure to handle the request 
      return WinDefDlgProc(hwndDlg, 
                           msg, 
                           mp1, 
                           mp2); 
 
      break; 
  } 
 
  return FALSE; 
} 
 
 
MRESULT EXPENTRY fnwpColorSample( HWND hwnd, ULONG msg, 
                                  MPARAM mp1, MPARAM mp2 ) 
{ 
  // If processing the paint message 
  if (msg == WM_PAINT) 
  { 
    HPS    hps; 
    RECTL  rcl,rcl1; 
 
    // Issue the begin paint 
    hps = WinBeginPaint(hwnd, 
                        NULL, 
                        &rcl); 
 
    // Override the rectangle returned from WinBeginPaint with the 
    // window's entire rectangle 
    WinQueryWindowRect(hwnd, &rcl); 
 
    // Compose the color value needed by GpiCreateLogColorTable 
    Color =                RGBColors[BLUE]   + 
          (256L   * (LONG) RGBColors[GREEN]) + 
          (65536L * (LONG) RGBColors[RED  ]); 
 
    // Create a color log table with one entry 
    GpiCreateLogColorTable(hps, 
                           LCOL_RESET, 
                           LCOLF_RGB, 
                           0L, 
                           1L, 
                           &Color); 
 
    // Issue four fills to outline the color in black 
    rcl1.xLeft=rcl.xLeft; 
    rcl1.xRight=rcl.xRight; 
    rcl1.yTop=rcl.yTop; 
    rcl1.yBottom=rcl.yTop - 4; 
    WinFillRect(hps, &rcl1, CLR_BLACK); 
 
    rcl1.xLeft=rcl.xLeft; 
    rcl1.xRight=rcl.xRight; 
    rcl1.yTop=rcl.yBottom + 4; 
    rcl1.yBottom=rcl.yBottom; 
    WinFillRect(hps, &rcl1, CLR_BLACK); 
 
    rcl1.xLeft=rcl.xLeft; 
    rcl1.xRight=rcl.xLeft + 4; 
    rcl1.yTop=rcl.yTop - 4; 
    rcl1.yBottom=rcl.yBottom + 4; 
    WinFillRect(hps, &rcl1, CLR_BLACK); 
 
    rcl1.xLeft=rcl.xRight - 4; 
    rcl1.xRight=rcl.xRight; 
    rcl1.yTop=rcl.yTop - 4; 
    rcl1.yBottom=rcl.yBottom + 4; 
    WinFillRect(hps, &rcl1, CLR_BLACK); 
 
    // Fill the rest of the rectangle with the current color 
    rcl.xLeft += 5; 
    rcl.yBottom += 5; 
    rcl.xRight -= 5; 
    rcl.yTop -= 5; 
    WinFillRect(hps, &rcl, Color); 
 
    // Issue the end paint 
    WinEndPaint( hps ); 
 
    // Return value is unimportant 
    return FALSE; 
  } 
  else 
  { 
    // Pass all other messages to the default window procedure 
    return WinDefWindowProc(hwnd, msg, mp1, mp2); 
  } 
} 

 
