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
// @(#) 1.8 com/src/samples/text/paragrph.hpp, odtextpart, od96os2, odos29712d 2/21/97 13:40:51 [3/21/97 17:48:38]
#ifndef _PARAGRAPH_HPP_
#define _PARAGRAPH_HPP_

#include "textplat.h"

class Paragraph
{
   public:
      Paragraph(int orgPos, char* chars, int numChars);
      Paragraph(int orgPos);
      ~Paragraph();
      void InsertText(int insPos, char* newChars, int numNewChars);
      void AppendText(char* newChars, int numNewChars);
      void DeleteText(int from, int numChars);
      void ReplaceText(int from, int to, char* newChars, int numNewChars);
      Paragraph* Split(int from);
      void Join(Paragraph* appendingPara);
      void CopyText(int from, int to, char* outBuffer);
      inline int GetTextSize() {return textBufferSize;}
      int GetOrigin();
      void ChangeOrigin(int origin);
      void DrawText(HDC hdc, RECT clipRect, int fontWidth, int fontDesc);

   private:
      int     origin;
      int     mem_allocated;

      char*     textBuffer;
      int       textBufferSize;

};
#endif
