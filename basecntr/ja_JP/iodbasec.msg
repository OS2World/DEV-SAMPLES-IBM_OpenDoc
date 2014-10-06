$ @(#) 1.11 %V% 6/20/96 15:26:56 [6/28/96 14:11:48]

$ *********************************************************************
$
$ COMPONENT_NAME:     ODSAMPLES
$
$ ORIGINS: 27
$
$
$                  Copyright IBM Corporation 1994
$
$                        All Rights Reserved
$
$  Permission to use, copy, modify, and distribute this software and its
$  documentation for any purpose and without fee is hereby granted,
$  provided that the above copyright notice appear in all copies and that
$  both that copyright notice and this permission notice appear in
$  supporting documentation, and that the name of IBM not be
$  used in advertising or publicity pertaining to distribution of the
$  software without specific, written prior permission.
$
$  IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
$  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
$  PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
$  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
$  USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
$  OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
$  OR PERFORMANCE OF THIS SOFTWARE.
$
$ ------------------------------------------------------------------------
$
$  File:      bcpart.msg
$  Contains:  Implementation of BaseContainer part handler
$  $Source:   com/src/samples/basecntr/bcpart.msg $
$  $Revision: 1.0 $
$
$ ************************************************************************

$ -------------------------------------------------------------
$ BaseContainer Part Messages in ENGLISH
$ -------------------------------------------------------------
$quote "

$set 1

$ -------------------------------------------------------------
$ Message 1: Embedded Part Pulldown Menu
$
$       Some Opendoc parts are called Container parts because
$       other parts can be embedded within them. The embedding
$       parts are selected from the "組み込み" pulldown menu.
$ -------------------------------------------------------------

1       "組み込み"


$ -------------------------------------------------------------
$ Message 2-5: MOVE and RESIZE actions in the EDIT menu
$
$       The "移動" action allows users to move selected embedded
$       parts around on the display. They select them with the
$       mouse, choose "移動" from the EDIT menu, and then move
$       mouse cursor to the new location and click once to
$       complete the move action.
$
$       The "手前に移動" action moves a partially hidden part
$       to the front of the display.
$
$       The "背後に移動" action moves the selected part behind
$       other parts on the display, so that other parts can be
$       seen more easily.
$
$       The "サイズ変更" action resizes the selected part on the display
$       as based on where the mouse is moved to and clicked.
$ -------------------------------------------------------------

2       "移動"
3       "手前に移動"
4       "背後に移動"
5       "サイズ変更"

$ -------------------------------------------------------------
$ Message 6,7: Color Pulldown Menu
$
$       On certain platforms a color menu will be available to
$       allow the active part's background color to change.
$ -------------------------------------------------------------

6       "色"
7       "壁紙の変更"

$ -------------------------------------------------------------
$ Message 10: Warning Messages for an Invalid Pulldown menu or action
$
$       The OpenDoc programmer must provide the text for a custom
$       menuitem and change the corresponding Menu event code to
$       recognize the custom menu. If this isn't done then the
$       warning text "メニュー選択の処理方法が不明です。: %d"
$       will appear.
$
$       The %d refers to the MENU_ID number that the programmer
$       assigned to this menuitem. The programmer can then use
$       this warning + MENU_ID to isolate and fix the problem
$       in the part source code.
$ -------------------------------------------------------------

10      "メニュー選択の処理方法が不明です。:   %d   !\n"

