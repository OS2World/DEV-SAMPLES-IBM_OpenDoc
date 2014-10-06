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
// @(#) 1.11 com/src/samples/text/textmgr.hpp, odtextpart, od96os2, odos29712d 2/21/97 13:40:58 [3/21/97 17:48:38]
#ifndef _TEXTMGR_HPP_
#define _TEXTMGR_HPP_

#include "textplat.h"
#include "paragrph.hpp"

class TextPart;
class IndexedCollection;
struct MYFONT {
  char name[128];
  long id;
  long width;
  long height;
  long externalLeading;
  long descender;
  long ascender;
};

#define CHARACTER_KEY 1
#define VIRTUAL_KEY 2
#define ACCEL_KEY 3
#define TEXT_CHANGED 4
#define NO_CHANGE 5

class TextMgr
{
   public:
      TextMgr(TextPart*);
      ~TextMgr();
      void ToggleInsertMode();
      void DisplayCursor(ODFacet* facet, ODRect clipRect);
      void CreateCursor(HWND hwnd);
      void DeleteCursor(HWND hwnd);
      void SetCursor(HWND hwnd, ODPoint cursor, ODRect cliprect);
      void AddText(char* text, int textSize);
      BOOL ProcessKeyInput(long &message, short keyEvent);
      int GetText(char** text);
      int GetTextSize();
      BOOL HasText();
      long GetTotalHeight();
      long GetMaximumWidth();
      void DrawText(HDC hdc, ODRect clipRect);
      void SetFont(HDC hdc, int printing);
      Paragraph* GetLastParagraph();
      Paragraph* GetParagraphFrom(POSITION pos);

   private:
      TextPart*  myParent;
      Environment*  myEv;
      IndexedCollection* paragraphs;
      int insertMode;
      MYFONT myFont;
      POSITION cursorPos;
      POSITION currentPos;
      Paragraph* currentParagraph;
      int maxParagraphLength;
};
#endif
