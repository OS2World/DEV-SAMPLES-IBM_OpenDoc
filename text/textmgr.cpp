//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odtextpart
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
// @(#) 1.17 com/src/samples/text/textmgr.cpp, odtextpart, od96os2, odos29712d 2/21/97 13:41:07 [3/21/97 17:48:39]
#include "textmgr.hpp"
#include "iodtext.xh"
#include "indxcoll.hpp"

#include <string.h>
#include <ctype.h>

#ifdef _PLATFORM_WIN32_
#define _UNICODE
#include <tchar.h>
#include <wchar.h>
#endif

// TextMgr Constructor
TextMgr::TextMgr(TextPart* parent)
{
   myEv = somGetGlobalEnvironment();
   myParent = parent;
   paragraphs = new IndexedCollection();

   SetNullPosition(currentPos);

   Paragraph* newPara = new Paragraph(0);
   paragraphs->AddLast(1, (ElementType*)&newPara);
   currentParagraph = newPara;
   insertMode = 1;
   maxParagraphLength = 0;
   memset(&myFont, 0, sizeof(MYFONT));
}

TextMgr::~TextMgr()
{
   // Delete each paragraph
    for(int i = 0; i < paragraphs->Count(); i++)
    {
      Paragraph* para = (Paragraph*) paragraphs->FromIndex(i);
      delete para;
    }
    delete paragraphs;
}

void TextMgr::ToggleInsertMode()
{
   insertMode = insertMode ^ 1;
#ifdef ODDebug
   PRINT("insertMode is %d\n", insertMode);
#endif
}

int TextMgr::GetText(char** text)
{
   int   textSize = GetTextSize();
   char* textPtr;
   int   paraSize;

   // If we haven't input any text, return with a null buffer pointer.
   if (textSize == 0) {
      *text = kODNULL;
   } else {
      // Otherwise, allocate a buffer for the text
      textPtr = new char[textSize+1];  // Add one for last (ignored) endLine.
      *text = textPtr;

      // Iterate through each paragraph to read its text
      for(int i = 0; i < paragraphs->Count(); i++)
      {
         Paragraph* para = (Paragraph*) paragraphs->FromIndex(i);
         paraSize = para->GetTextSize(); // Set up to copy whole paragraph
         para->CopyText(0, paraSize-1, textPtr);

         textPtr += paraSize;       // Advance pointer past the copied text
         memcpy(textPtr++,"\n",1);  // Append endLine for each paragraph
      } /* end for */
   } /* end if */

   return textSize;
}

// void TextMgr::DrawText(HDC hdc, ODRect clipRect)
// See textplat.cpp for definition

// void TextMgr::SetFont(HDC hdc)
// See textplat.cpp for definition

// void TextMgr::SetCursor(HWND hwnd, ODPoint cursor, ODRect cliprect)
// See textplat.cpp for definition

int TextMgr::GetTextSize()
{
   // Initialize to number of paragraphs, to account for endLine characters.
   int totalChars = paragraphs->Count();

   // Add text for each paragraph.
   for (int i=0; i < paragraphs->Count(); i++)
   {
       Paragraph* para = (Paragraph*) paragraphs->FromIndex(i);
       totalChars += para->GetTextSize();
   }

   // Subtract one from the size to account for the currentParagraph.  For example,
   // if the total is only one, this means we only have our default paragraph
   // with no text, so we'll return 0.
   return totalChars-1;

} // end GetTextSize

BOOL TextMgr::HasText()
{
   if (paragraphs->Count() > 1 || maxParagraphLength > 0)
      return TRUE;
   else
      return FALSE;
}

long TextMgr::GetTotalHeight()
{
#ifdef ODDebug
   PRINT("paracount is %d, fontHeight is %d, total is %d\n",
          paragraphs->Count(), myFont.height, paragraphs->Count()*myFont.height);
#endif
   return paragraphs->Count() * myFont.height;
}

long TextMgr::GetMaximumWidth()
{
   return maxParagraphLength * myFont.width;
}

void TextMgr::AddText(char* buffer, int bufferSize)
{
   int   j = 0;  // loop counter
   int   i = 0;  // loop counter
   int addChars = 0;  // Number of characters being added
   int lastPara = paragraphs->Count() -1; // Index of last paragraph

   // Ignore this request if there is no text to add.
   if (bufferSize == 0 || buffer == NULL)
      return;

   // To avoid incorporating unprintable eof characters at the end of the buffer,
   // decrement bufferSize down to the last carriage return.
   for (j = bufferSize -1;
        (j >= 0) && (!isprint(buffer[j])) && (buffer[j] != '\n') ;
        j--)
   {bufferSize--;}

   // Loop through the buffer characters, creating a paragraph each time an
   // endLine or carriage return is encountered.
   do {
      for (j = i;
           j < bufferSize && isprint(buffer[j]) ;
           j++ )
      {}
      addChars = j - i;

      // If we have text without an endline or carriage return, insert
      // it in front of the next paragraph.
      if (j == bufferSize) {
        currentPos.row++;
        Paragraph* nextPara = (Paragraph*) paragraphs->Next(currentPos.row);

        // If we're at the end of the paragraph list, create a new one for
        // the remaining text.
        if (nextPara == NULL) {
           nextPara = new Paragraph(0);
           paragraphs->AddLast(1, (ElementType*)&nextPara);
        }

        // Insert the text in front of the next paragraph.
        currentParagraph = nextPara;
        currentParagraph->InsertText(0, buffer+i, addChars);
        maxParagraphLength = max(maxParagraphLength, currentParagraph->GetTextSize());

        // The current column is at the end of the text that was just input
        currentPos.column = addChars;

        // This is our last time through the loop
        i = bufferSize;
      } else { // j != bufferSize
         currentParagraph->AppendText(buffer+i, addChars);
         maxParagraphLength = max(maxParagraphLength, currentParagraph->GetTextSize());

         // If we hit a new line or carriage return, start a new paragraph
         currentPos.row++;
         currentPos.column = 0;
         Paragraph* newPara = new Paragraph(0);
         paragraphs->AddBefore(currentPos.row, 1, (ElementType*)&newPara);
         currentParagraph = newPara;

         // advance to the beginning of the next paragraph - ignore extra
         // carriage returns and other unprintable characters
         for (i = j;
              (i < bufferSize) && (!isprint(buffer[i])) ;
              i++ )
            {
              if (buffer[i] == '\n') {
                 i++;
                 break;
              }
            }
      } /* endif */

   } while (i < bufferSize);  // end do loop

} // end AddText


// ProcessKeyInput handles a keyboard event.  The message parameter
// contains a key up, key down, or WM_CHAR event.  The keyEvent
// parameter contains the virtual key code or the ASCII character
// value of the input.

BOOL TextMgr::ProcessKeyInput(long &message, short keyEvent)
{
   BOOL result = TRUE;
   int lastRow = paragraphs->Count() -1;
   int lastCol = currentParagraph->GetTextSize();

   //>>> First, let's look for character input.
   if (message == CHARACTER_KEY) {
      switch(keyEvent) {

         case 0x0A:   // Linefeed
            if (currentPos.row < lastRow) {
               currentPos.row++;
               currentPos.column = 0;
               // Set the current paragraph to correspond to the current row.
               currentParagraph = (Paragraph*) paragraphs->FromIndex(currentPos.row);
            }
            message = NO_CHANGE; // Communicate that no change occurred to text.
            break;

         case 0x1B:   // Escape
         case 0x09:   // Tab
            message = NO_CHANGE; // Communicate that no change occurred to text.
            result = FALSE;      // Let the parent handle these.
            break;

         case 0x08:   // Backspace
            // If we're at the beginning of the column, see if there's a previous row.
            if (currentPos.column == 0) {
               // If there is a previous row, just append text of the current paragraph to it.
               if (currentPos.row > 0) {
                  Paragraph* appendPara = (Paragraph*) paragraphs->RemoveFrom(currentPos.row);
                  currentParagraph = (Paragraph*) paragraphs->FromIndex(--currentPos.row);
                  currentPos.column = currentParagraph->GetTextSize();
                  currentParagraph->Join(appendPara);  // Join will delete the paragraph.
                  maxParagraphLength = max(maxParagraphLength, currentParagraph->GetTextSize());
                  message = TEXT_CHANGED;  // Communicate that the text was changed.
               } else {
                  message = NO_CHANGE; // Communicate that no change occurred to text.
               }
            // Otherwise, move the caret back one space and delete the character.
            } else {
               currentPos.column--;
               currentParagraph->DeleteText(currentPos.column,1);
               message = TEXT_CHANGED;  // Communicate that the text was changed.
            }
            break;

         case 0x0D:   // Carriage Return
            Paragraph* nextPara;

            if (currentPos.column == currentParagraph->GetTextSize()) {
              nextPara = new Paragraph(0); // We're past the end of the text- start a new paragraph
            } else { // Else we're in the middle of a paragraph, so split the text.
               nextPara = currentParagraph->Split(currentPos.column);
            }
            paragraphs->AddBefore(++currentPos.row, 1, (ElementType*)&nextPara);
            currentPos.column = 0;  // Go to beginning of new line
            currentParagraph = nextPara;
            message = TEXT_CHANGED;  // Communicate that the text was changed.
            break;

         default:     // Must be a displayable character.
            char newChar = keyEvent;
            // If we're at the end of the paragraph or we're in insertMode, use InsertText.
            // Otherwise, use ReplaceText.
            if (insertMode || (currentPos.column == currentParagraph->GetTextSize()))  {
              currentParagraph->InsertText(currentPos.column++, &newChar, 1);
              maxParagraphLength = max(maxParagraphLength, currentParagraph->GetTextSize());
            } else {
              currentParagraph->ReplaceText(currentPos.column, currentPos.column, &newChar, 1);
              currentPos.column++; // Can't use ++ in ReplaceText call since the incremented
                                   // currentPos.column parm could be processed first before
                                   // the unincremented?!
            }
            message = TEXT_CHANGED;  // Communicate that the text was changed.
      } /* end switch */

   //>>> If not character input, check for accelerator keys
   } else if (message == ACCEL_KEY) {
      switch(keyEvent) {
      case kODCommandDelete:         // Delete text.
         // If we're at the end of the row, see if there's a row following.
         if (currentPos.column == currentParagraph->GetTextSize()) {
            // If there is a row following, just append its text to the current paragraph.
            if (currentPos.row != paragraphs->Count() -1) {
              Paragraph* nextPara = (Paragraph*) paragraphs->RemoveFrom(currentPos.row+1);
              currentParagraph->Join(nextPara);
              message = TEXT_CHANGED;  // Communicate that the text was changed.
            } else {
              message = NO_CHANGE; // Communicate that no change occurred to text.
            }
         } else {
            currentParagraph->DeleteText(currentPos.column,1);
            message = TEXT_CHANGED;  // Communicate that the text was changed.
         }
         break;

      default:
         message = NO_CHANGE; // Communicate that no change occurred to text.
         result = FALSE;      // Let our parent handle this.
      } /* end switch */

   //>>> Virtual key must have been generated.  Look for keys that affect
   //    the cursor position.
   } else {
      switch(keyEvent) {
      case VK_UP:
         if (currentPos.row > 0) {
            currentPos.row--;
            // Set the current paragraph to correspond to the current row.
            currentParagraph = (Paragraph*) paragraphs->FromIndex(currentPos.row);
         }
         break;
      case VK_DOWN:
         if (currentPos.row < lastRow) {
            currentPos.row++;
         // Set the current paragraph to correspond to the current row.
         currentParagraph = (Paragraph*) paragraphs->FromIndex(currentPos.row);
         }
         break;
      case VK_LEFT:
         if (currentPos.column > 0)
            currentPos.column--;
         break;
      case VK_RIGHT:
         if (currentPos.column < lastCol)
            currentPos.column++;
         break;
      case VK_HOME:
         currentPos.column = 0;
         break;
      case VK_END:
         currentPos.column = lastCol;
         break;
      default:            /* all other characters */
         result = FALSE;  // Let our parent handle these
         break;
      } /* endswitch */

      message = NO_CHANGE; // Communicate that no change occurred to text.
   } /* end keydown event */

   return result;
} // end ProcessKeyInput

Paragraph* TextMgr::GetParagraphFrom(POSITION pos)
{
   return (Paragraph*) paragraphs->FromIndex(pos.row);
}

Paragraph* TextMgr::GetLastParagraph()
{
   return (Paragraph*) paragraphs->Last();
}
