/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odtextpart
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
// @(#) 1.6 com/src/samples/text/textplat.h, odtextpart, od96os2, odos29712d 2/12/97 18:05:50 [3/21/97 17:48:52]
#ifndef _TEXTPLAT_H_
#define _TEXTPLAT_H_

// Define ODBoolean and ODPlatformWindow
#include <ODTypesB.xh>
#include <window.xh>

// Function Signatures
    ODBoolean PlatImportDlg(ODPlatformWindow window, char* docName);
    ODBoolean PlatExportDlg(ODPlatformWindow window, char* docName);
    ODBoolean PlatReadFile(char* docName, char* &buffer, int &bytesRead);
    ODBoolean PlatWriteFile(char* docName, char* buffer, int bufferSize);

// FocusLib is used for drawing
#include <FocusLib.h>

// define debugging message vehicle
#ifdef ODDebug
#include <ODDebug.h>
#endif // ODDebug

#if defined(_PLATFORM_OS2_)
#   include <ODos2.h>
#define HDC HPS
#define RECT Rect
#elif defined(_PLATFORM_WIN32_)
#   include <windows.h>
#   include <winuser.h>
#   include <wingdi.h>
#endif

// Get max file name size for import/export commands
#if defined(_PLATFORM_WIN32_)
typedef HANDLE    ODFileRefNum;
const   ODFileRefNum kODNoFileRefNum = INVALID_HANDLE_VALUE;
const   unsigned long   kODMaxFileNameSize = MAX_PATH;

#elif defined(_PLATFORM_OS2_)
typedef HFILE     ODFileRefNum;
const   ODFileRefNum kODNoFileRefNum = NULLHANDLE;
const   unsigned long   kODMaxFileNameSize = CCHMAXPATH;
#endif // defined(_PLATFORM_OS2_)

struct POSITION {
        int column;
        int row;
};

#define IsNullPosition(P)  (P.column == 0 && P.row == 0)
inline void SetNullPosition(POSITION &P) {P.column = 0; P.row = 0;}

#endif
