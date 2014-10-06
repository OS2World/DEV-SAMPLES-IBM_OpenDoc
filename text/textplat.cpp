// %Z 1.13 os2/src/samples/text/textplat.cpp, odtextpart, od96os2, odos29712d 97/03/21 17:48:53 (97/01/29 15:56:11)
//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odtextpart
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
#include "iodtext.h"
#include <io.h>       // for file extensions
#include <fcntl.h>    // for file open modes
#include <sys\stat.h> // for file permissions
#include <stdio.h>
#include <stdlib.h>
#include <indxcoll.hpp>

#ifndef SOM_ODFacet_xh
#include <Facet.xh>
#endif
#ifndef SOM_ODTransform_xh
#include <Trnsform.xh>
#endif

//------------------------------------------------------------------------------
//                             ImportDlg
//
// - invokes the common Open File dialog box to import an ASCII file.
// - returns the name of the file selected.
//------------------------------------------------------------------------------
ODBoolean PlatImportDlg(HWND hwnd, char* docName)
{
    char         szFile[kODMaxFileNameSize];
    HWND         hwndDlg;  // Dialog box's hwnd
    FILEDLG      fd;       // Control Block for WinFileDlg
    char* dialogText;      // pointer for dialog title

#if defined(__IBMCPP__) || defined(_IBMR2)
    nl_catd txNLSCat;       // NLS message catalog handle
    setlocale(LC_ALL,"");

    txNLSCat=catopen(TX_NLS_CATALOG, NL_CAT_LOCALE); // Open NLS message catalog
    dialogText = catgets(txNLSCat, TP_MSG_SET, TP_MSG_IMPORT_DLG, "Import");
#else
    dialogText = "Import";
#endif

    // Initialize the FILEDLG control block to pass to the
    // File Dialog - indicate it's a File Open Dialog
    memset( &fd, 0, sizeof( fd ) );
    fd.cbSize           = sizeof( FILEDLG );
    fd.fl               = FDS_OPEN_DIALOG | FDS_HELPBUTTON | FDS_CENTER;
    fd.pszTitle = dialogText;

    // Set the initial file filter to display all files (*.*)
    strcpy(fd.szFullFile, "*.*");

    // Now we're ready to ask for the filename to import
    hwndDlg = WinFileDlg(HWND_DESKTOP, hwnd, &fd);
    WinUpdateWindow(hwnd);

    if (hwndDlg && (fd.lReturn == DID_OK))
    {
      strcpy(docName, fd.szFullFile);
#ifdef ODDebug
      PRINT ("Document Name is %s\n",docName);
#endif
      return kODTrue;
    } // endif DID_OK
    else
       return kODFalse;
}


//------------------------------------------------------------------------------
//                           ExportDlg
// - invokes the common Save As File dialog box to obtain a file
//   name to export TextPart's data.
// - returns the name of the file specified.
//------------------------------------------------------------------------------
ODBoolean PlatExportDlg(HWND hwnd, char* docName)
{

    char         szFile[kODMaxFileNameSize];
    HWND         hwndDlg;  // Dialog box's hwnd
    FILEDLG      fd;       // Control Block for WinFileDlg
    char* dialogText;      // pointer for dialog title
    ODBoolean    result = kODFalse;

#if defined(__IBMCPP__) || defined(_IBMR2)
    nl_catd txNLSCat;       // NLS message catalog handle
    setlocale(LC_ALL,"");

    txNLSCat=catopen(TX_NLS_CATALOG, NL_CAT_LOCALE); // Open NLS message catalog
    dialogText = catgets(txNLSCat, TP_MSG_SET, TP_MSG_EXPORT_DLG, "Export");
#else
    dialogText = "Export";
#endif

    // Initialize the FILEDLG control block to pass to the
    // File Dialog - indicate it's a File Save As Dialog
    memset( &fd, 0, sizeof( fd ) );
    fd.cbSize           = sizeof( FILEDLG );
    fd.fl               = FDS_SAVEAS_DIALOG | FDS_HELPBUTTON | FDS_CENTER;
    fd.pszTitle = dialogText;

    // Set the initial file filter from the message catalog.  The
    // default is to display all files (*.*).
    // Set the initial file filter to display all files (*.*)
    strcpy(fd.szFullFile, "*.*");

    // Now we're ready to ask for the filename to export
    hwndDlg = WinFileDlg(HWND_DESKTOP, hwnd, &fd);
    WinUpdateWindow(hwnd);

    if (hwndDlg && (fd.lReturn == DID_OK))
    {
      strcpy(docName, fd.szFullFile);
#ifdef ODDebug
      PRINT ("Document Name is %s\n",docName);
#endif
      return kODTrue;
    } // endif DID_OK
    else
       return kODFalse;
}

//------------------------------------------------------------------------------
//                         PlatReadFile
//
// - allocates a buffer to read in the requested file.
// - reads the requested file into the specified buffer.
// - returns the buffer with the file contents.
//------------------------------------------------------------------------------
ODBoolean PlatReadFile(char* docName, char* &buffer, int& bytesRead)
{
    int hFile;
    int fileSize;

    // If no file is read in, buffer will be empty
    buffer = NULL;
    bytesRead = 0;

    // Open the file for reading.
    hFile = open(docName, O_RDONLY | O_TEXT);

    if (hFile == -1)
    {
#ifdef ODDebug
      PRINT ("File open failed for %s\n",docName);
#endif
      return kODFalse;
    }

    // Get the size of the file.
    fileSize = filelength(hFile);

    // Allocate a buffer for the file to be read into.
    buffer = (char *)SOMMalloc(fileSize);
    if (buffer == NULL)
    {
#ifdef ODDebug
      PRINT ("SOMMalloc failed!\n");
#endif
       close(hFile);
      return kODFalse;
    }

    // Read the file contents into a buffer.
    bytesRead = read(hFile, buffer, fileSize);

    if (bytesRead == 0)
    {
#ifdef ODDebug
      PRINT ("Zero bytes read.\n");
#endif
      close( hFile );
      SOMFree(buffer);
      return kODFalse;
    }

    // Close the file
      close( hFile );
#ifdef ODDebug
    PRINT ("File was successfully read.\n");
#endif
    return kODTrue;
}


//------------------------------------------------------------------------------
//                        PlatWriteFile
//
// - creates the requested file.
// - writes data from the specified buffer into the file.
// - does not deallocate the buffer.
//------------------------------------------------------------------------------
ODBoolean PlatWriteFile(char* docName, char* buffer, int bufferSize)
{
    int hFile;
    int bytesWritten = 0;

    // Open the file for writing.
    hFile = open(docName, O_CREAT | O_WRONLY | O_TEXT, S_IREAD | S_IWRITE);

    if (hFile == -1)
    {
#ifdef ODDebug
      PRINT ("File open failed for %s\n",docName);
#endif
      return kODFalse;
    }

    // Write the file contents from the buffer.
    bytesWritten = write(hFile,           // file handle
                         (void*) buffer,  // data to write
                         bufferSize);     // number bytes to write

    if (bytesWritten == 0)
    {
#ifdef ODDebug
      PRINT ("Zero bytes written.\n");
#endif
      close( hFile );
      return kODFalse;
    }

    // Close the file
    close( hFile );
#ifdef ODDebug
    PRINT ("File was successfully written.\n");
#endif
    return kODTrue;
}

//------------------------------------------------------------------------------
//                        TextMgr::DrawText
//
// - sets up the drawing environment
// - draws all text for the specified area
//------------------------------------------------------------------------------
void TextMgr::DrawText(HPS hps, ODRect clipRect)
{
   RECTL frameRect;
   int numPara = paragraphs->Count();
   int firstParI;
   int lastParI;

   // if there is no text to draw, no sense in continuing
   if (!HasText())
      return;

   frameRect.xLeft = FixedToInt(clipRect.left);
   frameRect.xRight  = FixedToInt(clipRect.right);
   frameRect.yTop  = FixedToInt(clipRect.top);
   frameRect.yBottom  = FixedToInt(clipRect.bottom);

   // Figure out which paragraphs to draw, based on the clip region
   firstParI = max(0, numPara - (frameRect.yTop / myFont.height));
   lastParI = min(numPara-1, numPara - (frameRect.yBottom / myFont.height));

   // Adjust the clip region to correspond to one line of text
   frameRect.yBottom  = frameRect.yTop - myFont.height;

   // Iterate through each paragraph to draw its text
   for (int i=firstParI; i <= lastParI; i++)
   {
       Paragraph* para = (Paragraph*) paragraphs->FromIndex(i);
       para->DrawText(hps, frameRect, myFont.width, myFont.descender);

       // Set up the clip region for the line of text below this one.
       frameRect.yTop  = frameRect.yBottom - myFont.externalLeading;
       frameRect.yBottom = frameRect.yTop - myFont.height;
   } /* endfor */
}

//------------------------------------------------------------------------------
//                        TextMgr::SetCursor
//
// - Sets the cursor to the input position
//------------------------------------------------------------------------------
void TextMgr::SetCursor(HWND hwnd, ODPoint cursor, ODRect clipRect)
{
   int inputRow = FixedToInt(clipRect.top - cursor.y) / myFont.height;

   // Ensure that the cursor does not go beyond the last row of text.
   currentPos.row = min(inputRow, paragraphs->Count()-1);

   // Set the current paragraph pointer so we can ensure the cursor does
   // not go beyond the last column of the paragraph.
   currentParagraph = (Paragraph*) paragraphs->FromIndex(currentPos.row);
   currentPos.column = min(FixedToInt(cursor.x) / myFont.width,
                           currentParagraph->GetTextSize());
}

//------------------------------------------------------------------------------
//                        TextMgr::DisplayCursor
//
// - Displays the cursor in the given window
//------------------------------------------------------------------------------
void TextMgr::DisplayCursor(ODFacet* facet, ODRect clipRect)
{
   RECTL frameRect;
   POINTL origin;
   ODPoint odOrigin;
   BOOL rc;
   int numPara = paragraphs->Count();
   int firstParI;
   int lastParI;

   frameRect.xLeft = FixedToInt(clipRect.left);
   frameRect.xRight  = FixedToInt(clipRect.right);
   frameRect.yTop  = FixedToInt(clipRect.top);
   frameRect.yBottom  = FixedToInt(clipRect.bottom);

   // Figure out which paragraphs to draw, based on the clip region
   firstParI = max(0, numPara - (frameRect.yTop / myFont.height));
   lastParI = min(numPara-1, numPara - (frameRect.yBottom / myFont.height));

   // Use the paragraph range to determine if we need to display the cursor
   if (currentPos.row >= firstParI && currentPos.row <= lastParI)
   {
      // Determine the cursor position relative to the frame
      origin.x = frameRect.xLeft + currentPos.column * myFont.width;
      origin.y = frameRect.yTop - ((currentPos.row - firstParI +1) * myFont.height);

      // Convert the cursor position to ODPoint coordinates and transform
      // again to window coordinates.
      odOrigin.x = IntToFixed(origin.x);
      odOrigin.y = IntToFixed(origin.y);
      HWND hwnd = facet->GetFacetHWND(myEv);
      TempODTransform xform = facet->AcquireWindowContentTransform(myEv, kODNULL);
      xform->TransformPoint (myEv, &odOrigin);

      // Convert the position back to integer coordinates, and set the cursor
      // position.
      origin.x = FixedToInt(odOrigin.x);
      origin.y = FixedToInt(odOrigin.y);
      rc = WinCreateCursor(hwnd,
                    origin.x,            // x coordinate of cursor
                    origin.y,            // y coordinate of cursor
                    0, 0,                // use size from cursor creation
                    CURSOR_SETPOS,       // set cursor position
                    NULL);               // clip within window hwnd
      WinShowCursor(hwnd, kODTrue);
      if (rc == kODFalse)
      {
         HAB hab;
         ERRORID errid = WinGetLastError(hab);
#ifdef ODDebug
      PRINT ("Error %x displaying cursor.\n",errid);
#endif
      } /* endif */
   } /* endif */
}

//------------------------------------------------------------------------------
//                        TextMgr::SetFont
//
// - chooses a font for the drawing environment
// - stores the necessary font metrics
//------------------------------------------------------------------------------
void TextMgr::SetFont(HPS hps, int printing)
{
   FONTMETRICS fontM;
   FATTRS fontA;
   LONG lcid = 42;

   // Set up our font attributes.  Since we are using an Outline font
   // (as opposed to an Image font), we do not need to specify the
   // MaxBaselineExt or the AveCharWidth fields.
   memset(&fontA,0,sizeof(fontA));
   fontA.usRecordLength = sizeof(FATTRS);
   strcpy(fontA.szFacename, "Courier");
   fontA.fsFontUse = FATTR_FONTUSE_OUTLINE;

   // Let the system choose a courier font for us
   LONG match = GpiCreateLogFont(hps, (PSTR8) NULL, lcid, &fontA);
#ifdef ODDebug
   if (match == FONT_DEFAULT) {
      PRINT ("Default font used.\n");
   } else if (match == GPI_ERROR) {
      PRINT ("Error in choosing font.\n");
   } /* endif */
#endif

   // Set the drawing font, color, etc. for our hps
   GpiSetCharSet(hps, lcid);
   GpiSetTextAlignment(hps, TA_STANDARD_HORIZ, TA_BASE);
   GpiSetBackMix(hps,BM_LEAVEALONE);
   GpiSetColor(hps, CLR_BLACK);

   // If we're printing, adjust the scale of the font
   if (printing) {
       SIZEF sizfCharBox;
       sizfCharBox.cx = MAKEFIXED (12, 0);
       sizfCharBox.cy = MAKEFIXED (12, 0);
       GpiSetCharBox(hps,&sizfCharBox);  // scale the font
   } /* endif */

   // Save the font characteristics to use later when we draw
   GpiQueryFontMetrics(hps, sizeof(FONTMETRICS), &fontM);
   strcpy(myFont.name, fontM.szFacename);
   myFont.id = fontM.lMatch;
   myFont.width = fontM.lMaxCharInc;
   myFont.height = fontM.lMaxBaselineExt;
   myFont.externalLeading = fontM.lExternalLeading;
   myFont.descender = fontM.lMaxDescender;
   myFont.ascender = fontM.lMaxAscender;
}

//------------------------------------------------------------------------------
//                        TextMgr::CreateCursor
//
// - creates a system cursor for the given window
//------------------------------------------------------------------------------
void TextMgr::CreateCursor(HWND hwnd)
{
  BOOL rc = WinCreateCursor(hwnd,
                  0, 0,                          // where to display cursor - set later
                  0, myFont.height,              // use default width for cursor
                  CURSOR_SOLID | CURSOR_FLASH,   // cursor appearance
                  NULL);                         // clip within window hwnd
  WinShowCursor(hwnd, kODTrue);
  if (rc == kODFalse)
  {
     HAB hab;
     ERRORID errid = WinGetLastError(hab);
#ifdef ODDebug
     PRINT ("Error %x creating cursor.\n",errid);
#endif
  }
}

//------------------------------------------------------------------------------
//                        TextMgr::DeleteCursor
//
// - deletes the system cursor for the given window
//------------------------------------------------------------------------------
void TextMgr::DeleteCursor(HWND hwnd)
{
  // First hide the cursor so no residual is left.
  WinShowCursor(hwnd, kODFalse);
  BOOL rc = WinDestroyCursor(hwnd);

  if (rc == kODFalse)
  {
     HAB hab;
     ERRORID errid = WinGetLastError(hab);
#ifdef ODDebug
     PRINT ("Error %x deleting cursor.\n",errid);
#endif
  }
}

//------------------------------------------------------------------------------
//                        Paragraph::DrawText
//
// - draws this paragraph's text for the specified area
//------------------------------------------------------------------------------
void Paragraph::DrawText(HPS hps, RECTL frameRect, int fontWidth, int fontDesc)
{
   POINTL origin;
   origin.x = frameRect.xLeft;
   origin.y = frameRect.yBottom + fontDesc;
   int startChar = frameRect.xLeft / fontWidth;
   int numChars = textBufferSize - startChar;

   // Make sure we have characters to output.
   if (numChars >0) {
      GpiCharStringPosAt(hps,
                    &origin,
                    &frameRect,
                    CHS_CLIP,
                    numChars,
                    textBuffer + startChar,
                    NULL);
   }
}
