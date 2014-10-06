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
// @(#) 1.9 com/src/samples/text/paragrph.cpp, odtextpart, od96os2, odos29712d 2/21/97 13:40:42 [3/21/97 17:48:38]
#include "paragrph.hpp"
#include <string.h>

Paragraph::Paragraph(int org, char* chars, int numChars)
{
   if (numChars == 0) {
     textBuffer = NULL;
     textBufferSize = 0;
   } else {
     textBufferSize = numChars;
     textBuffer = new char[textBufferSize];
     memcpy(textBuffer, chars, numChars);  // Copy input text
   }
   mem_allocated = textBufferSize;
   origin = org;

}

Paragraph::Paragraph(int org)
{
   textBufferSize = 0;
   textBuffer = NULL;
   mem_allocated = 0;
   origin = org;
}

Paragraph::~Paragraph()
{
   if (textBuffer != NULL)
      delete textBuffer;
}

void Paragraph::InsertText(int insPos, char* newChars, int numNewChars)
{
   // Check for just a plain newLine- no other characters.
   if (numNewChars == 0)
      return;

   // If the paragraph has been created but not had any text input yet,
   // just copy the incoming text directly into a new buffer.
   if (textBuffer == NULL) {
      textBufferSize = numNewChars + insPos;
      textBuffer = new char [textBufferSize];

      // If we have a non-Null insert position, we need to insert spaces
      // before the first character.  This could happen if the user uses
      // the right arrow key instead of the space bar to move the cursor.
      origin = insPos;  // In case we add indentation function later...
      for (int i=0; i < insPos; i++)  // Add spaces for indentation
         textBuffer[i] = ' ';

      // now copy the input text
      strncpy(textBuffer+insPos, newChars, numNewChars);

   // Otherwise, the paragraph already had some text, so insert the
   // new text at the input column.
   } else {
      int charsBefore;
      char* oldChars = textBuffer;
      textBuffer = new char[textBufferSize + numNewChars];

      // Copy the old and inserted text into the new buffer
      if (insPos != 0) {
         charsBefore = insPos;
         strncpy(textBuffer, oldChars, charsBefore);
      } else {
         charsBefore = 0;
      } /* endif */
      strncpy(textBuffer + charsBefore, newChars, numNewChars);
      strncpy(textBuffer + charsBefore + numNewChars,
              oldChars + charsBefore,
              textBufferSize - charsBefore);

      textBufferSize += numNewChars;
      delete oldChars;
   } /* endif */
}

void Paragraph::AppendText(char* newChars, int numNewChars)
{
   // Check for just a plain newLine- no other characters.
   if (numNewChars == 0)
      return;

   // If the paragraph has been created but not had any text input yet,
   // just copy the incoming text directly into a new buffer.
   if (textBuffer == NULL) {
      textBuffer = new char [numNewChars];
      strncpy(textBuffer, newChars, numNewChars);
      textBufferSize = numNewChars;

   // Otherwise, the paragraph already had some text, so append the new text.
   } else {
      char* oldChars = textBuffer;
      textBuffer = new char[textBufferSize + numNewChars];

      // Copy the old and appended text into the new buffer
      strncpy(textBuffer, oldChars, textBufferSize);
      strncpy(textBuffer+textBufferSize, newChars, numNewChars);

      textBufferSize += numNewChars;
      delete oldChars;
   } /* end if */
}

void Paragraph::DeleteText(int from, int numChars)
{
   char* oldBuffer = textBuffer;

   if (textBuffer != NULL) {
      numChars = min(numChars, textBufferSize - from + 1);
      textBuffer = new char [textBufferSize - numChars];
      memcpy(textBuffer,oldBuffer,from);  // Copy up to "from"
      memcpy(textBuffer + from,
             oldBuffer + from + numChars, // skip the deleted chars
             textBufferSize - from - numChars);
      textBufferSize -= numChars;
      delete oldBuffer;
   }
}

void Paragraph::ReplaceText(int from, int to, char* newChars, int numNewChars)
{
   if (textBuffer == NULL) // No text to replace- just insert the new text.
      InsertText(from, newChars, numNewChars);
   else {
      int deletedChars = to - from + 1;

      // If we have a one-for-one character replacement, just copy the
      // new text over the old text.
      if (deletedChars == numNewChars)
         memcpy(textBuffer + from, newChars, numNewChars);

      // Otherwise, we are adding a different number of chars than we're
      // deleting, so we need to allocate a new buffer.
      else {
         char* oldBuffer = textBuffer;
         textBuffer = new char [textBufferSize - deletedChars + numNewChars];
         memcpy(textBuffer, oldBuffer, from);  // Copy up to "from"
         memcpy(textBuffer + from, newChars, numNewChars);  // Copy new chars
         memcpy(textBuffer + from + numNewChars,
                oldBuffer + from + deletedChars, // Skip the replaced characters
                textBufferSize - from - deletedChars);
         textBufferSize += (numNewChars - deletedChars);
         delete oldBuffer;
      }
   }
}

void Paragraph::Join(Paragraph* appendingPara)
{
   if (appendingPara != NULL) {
      this->AppendText(appendingPara->textBuffer, appendingPara->textBufferSize);
      delete appendingPara;
   }
}


Paragraph* Paragraph::Split(int from)
{
   Paragraph* newPara;

   if (textBuffer == NULL) {
      newPara = new Paragraph(0);
   } else {
      // Create a new paragraph with the text after the split.
      char* newText = textBuffer + from;
      newPara = new Paragraph(0, newText, textBufferSize - from);

      // Create a new buffer to hold the remaining text.
      char* oldBuffer = textBuffer;
      textBuffer = new char[from];
      memcpy(textBuffer, oldBuffer, from);
      textBufferSize = from;
      delete oldBuffer;
   }

   return newPara;
}

void Paragraph::CopyText(int from, int to, char* outBuffer)
{
   if (textBuffer != NULL)
      memcpy(outBuffer, textBuffer+from, to-from+1);
}

// void Paragraph::DrawText(HDC hdc, RECT frameRect, int fontWidth, int fontAsc)
// See textplat.cpp for definition

int Paragraph::GetOrigin()
{
   return origin;
}

void Paragraph::ChangeOrigin(int orgPos)
{
   origin = orgPos;
}
