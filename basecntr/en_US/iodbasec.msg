$ ====START_GENERATED_PROLOG======================================
$ 
$ 
$    COMPONENT_NAME: odbasecntr
$ 
$    CLASSES: none
$ 
$    ORIGINS: 82,27
$ 
$ 
$    (C) COPYRIGHT International Business Machines Corp. 1995,1996
$    All Rights Reserved
$    Licensed Materials - Property of IBM
$    US Government Users Restricted Rights - Use, duplication or
$    disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
$    	
$    IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
$    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
$    PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
$    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
$    USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
$    OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
$    OR PERFORMANCE OF THIS SOFTWARE.
$ 
$ ====END_GENERATED_PROLOG========================================
$ 

$ @(#)Z 1.19 com/src/samples/basecntr/en_US/iodbasec.msg, odbasepart, od96os2, odos29712d 97/03/21 17:45:32 (97/02/12 19:27:00)
$
$ /********************************************************************/
$ /*  Licensed Materials - Property of IBM                            */
$ /*                                                                  */
$ /*                                                                  */
$ /* Copyright (C) International Business Machines Corp., 1996.       */
$ /*                                                                  */
$ /*  US Government Users Restricted Rights -                         */
$ /*  Use, duplication, or disclosure restricted                      */
$ /*  by GSA ADP Schedule Contract with IBM Corp.                     */
$ /*                                                                  */
$ /*          05/15/96  oof     Original File                         */
$ /********************************************************************/
$
$ This is the message file for Base Container Part on NT, Win95 and OS/2.
$


$ -------------------------------------------------------------
$ BaseContainer Part Messages in ENGLISH
$ -------------------------------------------------------------
$quote "

$set BCMSG_SET

$ -------------------------------------------------------------
$ A word to the translator on translating mnemonics:
$
$   A mnemonic is a single character, within the text of a menu 
$   choice, identified by an underscore beneath the character.
$   Typing that character while the menu is active will select
$   that choice.
$
$   Whenever we assigned a mnemonic to a menu choice, we have 
$   defined 3 strings for the choice text-- one for each 
$   platform. The OS/2 string will contain a '~' before the 
$   letter that has been chosen for the mnemonic. On Windows it 
$   will be an '&'. On UNIX we don't support mnemonics.
$
$   We suggest that, when translating strings with mnemonics
$   to a language with a different alphabet, you translate only
$   the menu text and add beside it the original mnemonic
$   in parenthesis. For example, if the original Windows string
$   is "&Edit" then the translated string would be "XXXXX(&E)",
$   where XXXXX is the translation of the "Edit" string.
$   
$   If the suggested translation approach is not followed, it
$   is imperative that the menues be tested for mnemonic 
$   collisions. Testing should ensure that no two active menu
$   choices have the same character for their mnemonics.
$ -------------------------------------------------------------


$ -------------------------------------------------------------
$ Embedded Part Pulldown Menu
$
$       Some Opendoc parts are called Container parts because
$       other parts can be embedded within them. The embedding
$       parts are selected from the "Embed" pulldown menu.
$
$ -------------------------------------------------------------

BC_EMBED_UNX     "Embed"
BC_EMBED_OS2     "E~mbed"
BC_EMBED_WIN     "E&mbed"


$ -------------------------------------------------------------
$ MOVE and RESIZE actions in the EDIT menu
$
$       The "MOVE" action allows users to move selected embedded
$       parts around on the display. They select them with the
$       mouse, choose "MOVE" from the EDIT menu, and then move
$       mouse cursor to the new location and click once to
$       complete the move action.
$
$       The "Move to Front" action moves a partially hidden part
$       to the front of the display.
$
$       The "Move to Back" action moves the selected part behind
$       other parts on the display, so that other parts can be
$       seen more easily.
$
$       The "Resize" action resizes the selected part on the display
$       as based on where the mouse is moved to and clicked.
$ -------------------------------------------------------------

BC_MOVE_UNX        "Move"
BC_MOVE_OS2        "~Move"
BC_MOVE_WIN        "&Move"

BC_MOVE2FRONT_UNX  "Move To Front"
BC_MOVE2FRONT_OS2  "Move To F~ront"
BC_MOVE2FRONT_WIN  "Move To F&ront"

BC_MOVE2BACK_UNX   "Move To Back"
BC_MOVE2BACK_OS2   "Move To ~Back"
BC_MOVE2BACK_WIN   "Move To &Back"

BC_RESIZE_UNX      "Resize"
BC_RESIZE_OS2      "Resi~ze"
BC_RESIZE_WIN      "Resi&ze"

$ -------------------------------------------------------------
$ Color Pulldown Menu
$
$       On certain platforms a color menu will be available to
$       allow the active part's background color to change.
$ -------------------------------------------------------------

BC_OPTIONS_UNX     "Options"
BC_OPTIONS_OS2     "~Options"
BC_OPTIONS_WIN     "&Options"

BC_COLOR_CHG_UNX   "Change Background"
BC_COLOR_CHG_OS2   "~Change Background"
BC_COLOR_CHG_WIN   "&Change Background"

$ -------------------------------------------------------------
$ Warning Messages for an Invalid Pulldown menu or action
$
$       The OpenDoc programmer must provide the text for a custom
$       menuitem and change the corresponding Menu event code to
$       recognize the custom menu. If this isn't done then the
$       warning text "Don't know how to handle this menu choice: %d"
$       will appear.
$
$       The %d refers to the MENU_ID number that the programmer
$       assigned to this menuitem. The programmer can then use
$       this warning + MENU_ID to isolate and fix the problem
$       in the part source code.
$ -------------------------------------------------------------

BC_MENUBAR_WARNING   "Don't know how to handle this menu choice:   %d   !\n"
BC_INVALID_DROP      "Document is read-only. Drop is not accepted."
BC_INVALID_DELETE    "Cannot delete selection. Document is read-only."

$ -------------------------------------------------------------
$ Base Container Help Menu Item
$
$ When the user selects the "Base Container Help" item of 
$ the HELP menu, information on how to use the Base Container
$ is displayed.
$ -------------------------------------------------------------

BC_HELP_UNX     "Base Container Help"
BC_HELP_OS2     "~Base Container Help"
BC_HELP_WIN     "&Base Container Help"
