/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: oddynamicpart
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
/* @(#) 1.9 com/src/samples/dynamicp/bmenu/madjmenu.c, oddynamicpart, od96os2, odos29712d 2/18/97 13:55:50 [3/21/97 17:44:47]
*******************************************************************
** Name: void AdjustMenus
**
** Description:  override method to update menus before displaying
**               them.
**
*******************************************************************
*/
try {

    ODBoolean disable = kODFalse;
    /**********************************************************************
    *  Be careful what you do in this method.  AdjustMenus gets called
    *  everytime the user presses MB1 down on the menu control.
    *  This method is more for adjusting the current menu.  If you want
    *  to add items, surround them with a flag so they only get added once.
    *  Also, if you are the root part, but not the active part, you will
    *  also get called to adjust the current menubar for items on the
    *  Document menu (like Open as) if you support them.
    **********************************************************************/
    // Disable the VIEW standard menu item on the MenuBar
      _fMenuBar->EnableMenu(ev, VIEW_SHOWAS, disable);

   // Disable unsupported menu items on Document and Edit menus
     _fMenuBar->EnableMenuItem(ev, IDMS_DOCUMENT, DOC_SETUP, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_DOCUMENT, DOC_PRINT, kODFalse);

     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_CREATE, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_CUT, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_LINK_MENU, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_DELETE, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_SELECTALL, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_DESELECTALL, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_OPENSEL, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_SELPROPERTIES, kODFalse);
     _fMenuBar->EnableMenuItem(ev, IDMS_EDIT, EDIT_INSERT, kODFalse);

    // customize menu text to reflect current status

    IString MenuStopRotation = "";
    IString MenuStopHShear = "";
    IString MenuStopVShear = "";
    _Resources->open();
    if (_Resources->isOpen()) {
       if (_xRotateActive) {
         MenuStopRotation = _Resources->loadString(DYNAMICPART_MENU_RESUMED);
       } else {
         MenuStopRotation = _Resources->loadString(DYNAMICPART_MENU_STOPPED);
       } /* endif */
       if (_hShearActive) {
         MenuStopHShear   = _Resources->loadString(DYNAMICPART_MENU_RESUMED);
       } else {
         MenuStopHShear   = _Resources->loadString(DYNAMICPART_MENU_STOPPED);
       } /* endif */
       if (_vShearActive) {
         MenuStopVShear   = _Resources->loadString(DYNAMICPART_MENU_RESUMED);
       } else {
         MenuStopVShear   = _Resources->loadString(DYNAMICPART_MENU_STOPPED);
       } /* endif */
    } /* endif */
    _Resources->close();

    // change menu item text to reflect new state
    _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_ROTATE, DYNAMICPART_MENU_STOPPED, (char *)MenuStopRotation);
    _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_HSHEAR, DYNAMICPART_MENU_HSTOPPED, (char *)MenuStopHShear);
    _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_VSHEAR, DYNAMICPART_MENU_VSTOPPED, (char *)MenuStopVShear);
    // now update popup menu
    if (_fPopup != NULL) {
      _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_ROTATE, DYNAMICPART_MENU_STOPPED, (char *)MenuStopRotation);
      _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_HSHEAR, DYNAMICPART_MENU_HSTOPPED, (char *)MenuStopHShear);
      _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_VSHEAR, DYNAMICPART_MENU_VSTOPPED, (char *)MenuStopVShear);
    } /* endif */


    //enable the menu items that we support

    // rotation menus
    _fMenuBar->CheckMenuItem (ev,DYNAMICPART_MENU_RDIR, DYNAMICPART_MENU_RDIR_FORWARD, _xRotateClockwise);
    _fMenuBar->CheckMenuItem (ev,DYNAMICPART_MENU_RDIR, DYNAMICPART_MENU_RDIR_BACKWARD,!_xRotateClockwise);

    // horizontal shear menus
    _fMenuBar->CheckMenuItem (ev,DYNAMICPART_MENU_HDIR, DYNAMICPART_MENU_HDIR_FORWARD, _hShearRight);
    _fMenuBar->CheckMenuItem (ev,DYNAMICPART_MENU_HDIR, DYNAMICPART_MENU_HDIR_BACKWARD,!_hShearRight);

    // vertical shear menus
    _fMenuBar->CheckMenuItem (ev,DYNAMICPART_MENU_VDIR, DYNAMICPART_MENU_VDIR_FORWARD, _vShearUp);
    _fMenuBar->CheckMenuItem (ev,DYNAMICPART_MENU_VDIR, DYNAMICPART_MENU_VDIR_BACKWARD,!_vShearUp);

    // Enable the DynamicPart menu only if the draft is writeable
    _fMenuBar->EnableMenu(ev, DYNAMICPART_MENU, !_fDraftReadOnly);

    //////////////////////////////////////////////////////////////////

    if (_fPopup != NULL) {
    // Disable the VIEW standard menu items on the Popup Menu
      _fPopup->EnableMenuItem(ev, ID_BASEPOPUP, VIEW_PROPERTIES, disable);
      _fPopup->EnableMenuItem(ev, ID_BASEPOPUP, VIEW_SHOWAS, disable);

    // Enable the DynamicPart menu items only if the draft is writeable
      _fPopup->EnableMenuItem(ev, ID_BASEPOPUP, DYNAMICPART_MENU_ROTATE, !_fDraftReadOnly);
      _fPopup->EnableMenuItem(ev, ID_BASEPOPUP, DYNAMICPART_MENU_HSHEAR, !_fDraftReadOnly);
      _fPopup->EnableMenuItem(ev, ID_BASEPOPUP, DYNAMICPART_MENU_VSHEAR, !_fDraftReadOnly);
      _fPopup->EnableMenuItem(ev, ID_BASEPOPUP, DYNAMICPART_MENU_RESET, !_fDraftReadOnly);

    // rotation menus
      _fPopup->CheckMenuItem (ev,DYNAMICPART_MENU_RDIR, DYNAMICPART_MENU_RDIR_FORWARD, _xRotateClockwise);
      _fPopup->CheckMenuItem (ev,DYNAMICPART_MENU_RDIR, DYNAMICPART_MENU_RDIR_BACKWARD,!_xRotateClockwise);

      // horizontal shear menus
      _fPopup->CheckMenuItem (ev,DYNAMICPART_MENU_HDIR, DYNAMICPART_MENU_HDIR_FORWARD, _hShearRight);
      _fPopup->CheckMenuItem (ev,DYNAMICPART_MENU_HDIR, DYNAMICPART_MENU_HDIR_BACKWARD,!_hShearRight);

      // horizontal shear menus
      _fPopup->CheckMenuItem (ev,DYNAMICPART_MENU_VDIR, DYNAMICPART_MENU_VDIR_FORWARD, _vShearUp);
      _fPopup->CheckMenuItem (ev,DYNAMICPART_MENU_VDIR, DYNAMICPART_MENU_VDIR_BACKWARD,!_vShearUp);
    } /* endif */
    //////////////////////////////////////////////////////////////////

} catch (...) {
    reportAnyException(ev);
} /* end try */
