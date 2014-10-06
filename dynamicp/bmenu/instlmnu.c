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
/* @(#) 1.10 com/src/samples/dynamicp/bmenu/instlmnu.c, oddynamicpart, od96os2, odos29712d 11/13/96 14:34:40 (3/21/97 17:44:47)
*******************************************************************
** Name: void InstallMenus
**
** Description:  Override method to Install Menus.
**               Dynamically create menu items and add to the
**               menu bar and popup menu.
**
*******************************************************************
*/
try {

  if ( !_fMenuBar ) {
    _fMenuBar = somSelf->GetMenuBar(ev);
  } /* endif */
  if (!_fPopup) {
    _fPopup = somSelf->GetPopupMenu(ev);
  } /* endif */
  if (_fMenuBar->Exists(ev, kODNULL, DYNAMICPART_MENU)) {
    // we've already been here -- don't do it again
    return;
  } /* endif */

   ODPlatformMenuItem mi;

// Root Menu Item
// DynamicPartMenuText will contain the string that will be displayed as the main menu item
   IString DynamicPartMenuText = "";
// Sub-Menu Items
// MenuRotate will contain the string that will be displayed as the first menu item
   IString MenuRotate = "";
// MenuRotateDirection will contain the string that will be displayed as the first menu item
   IString MenuRotateDirection = "";
// MenuRotateForward   will contain the string that will be displayed as the first sub-menu item
   IString MenuRotateForward   = "";
// MenuRotateBackward  will contain the string that will be displayed as the second sub-menu item
   IString MenuRotateBackward  = "";
// MenuStopRotation will contain the string that will be displayed as the second menu item
   IString MenuStopRotation = "";

// MenuHShear will contain the string that will be displayed as the first menu item
   IString MenuHShear = "";
// MenuHShearDirection will contain the string that will be displayed as the first menu item
   IString MenuHShearDirection = "";
// MenuHShearForward   will contain the string that will be displayed as the first sub-menu item
   IString MenuHShearForward   = "";
// MenuHShearBackward  will contain the string that will be displayed as the secong sub-menu item
   IString MenuHShearBackward  = "";
// MenuStopHShear will contain the string that will be displayed as the second menu item
   IString MenuStopHShear = "";

// MenuVShear will contain the string that will be displayed as the first menu item
   IString MenuVShear = "";
// MenuVShearDirection will contain the string that will be displayed as the first menu item
   IString MenuVShearDirection = "";
// MenuVShearForward   will contain the string that will be displayed as the first sub-menu item
   IString MenuVShearForward   = "";
// MenuVShearBackward  will contain the string that will be displayed as the secong sub-menu item
   IString MenuVShearBackward  = "";
// MenuStopVShear will contain the string that will be displayed as the second menu item
   IString MenuStopVShear = "";

   IString MenuReset      = "";

   // now load strings from resource DLL
   _Resources->open();
   if (_Resources->isOpen()) {
      DynamicPartMenuText = _Resources->loadString(DYNAMICPART_MENU);
      MenuRotate          = _Resources->loadString(DYNAMICPART_MENU_ROTATE);
      MenuRotateDirection = _Resources->loadString(DYNAMICPART_MENU_RDIR);
      MenuRotateForward   = _Resources->loadString(DYNAMICPART_MENU_RDIR_FORWARD);
      MenuRotateBackward  = _Resources->loadString(DYNAMICPART_MENU_RDIR_BACKWARD);
      if (_xRotateActive) {
        MenuStopRotation = _Resources->loadString(DYNAMICPART_MENU_RESUMED);
      } else {
        MenuStopRotation = _Resources->loadString(DYNAMICPART_MENU_STOPPED);
      } /* endif */

      MenuHShear          = _Resources->loadString(DYNAMICPART_MENU_HSHEAR);
      MenuHShearDirection = _Resources->loadString(DYNAMICPART_MENU_HDIR);
      MenuHShearForward   = _Resources->loadString(DYNAMICPART_MENU_HDIR_FORWARD);
      MenuHShearBackward  = _Resources->loadString(DYNAMICPART_MENU_HDIR_BACKWARD);
      if (_hShearActive) {
        MenuStopHShear   = _Resources->loadString(DYNAMICPART_MENU_RESUMED);
      } else {
        MenuStopHShear   = _Resources->loadString(DYNAMICPART_MENU_STOPPED);
      } /* endif */

      MenuVShear          = _Resources->loadString(DYNAMICPART_MENU_VSHEAR);
      MenuVShearDirection = _Resources->loadString(DYNAMICPART_MENU_VDIR);
      MenuVShearForward   = _Resources->loadString(DYNAMICPART_MENU_VDIR_FORWARD);
      MenuVShearBackward  = _Resources->loadString(DYNAMICPART_MENU_VDIR_BACKWARD);
      if (_vShearActive) {
        MenuStopVShear   = _Resources->loadString(DYNAMICPART_MENU_RESUMED);
      } else {
        MenuStopVShear   = _Resources->loadString(DYNAMICPART_MENU_STOPPED);
      } /* endif */
      MenuReset           = _Resources->loadString(DYNAMICPART_MENU_RESET);
   } /* endif */
   _Resources->close();

   ODPlatformMenu myMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);

// Adding the Menu Item to the BaseMenuBar at the end
// DYNAMICPART_MENU is the ID of the new menu
// myMenu is a PM menu handle
// _fPartWrapper is a pointer to the Part creating the menu
   _fMenuBar->AddMenuLast(ev, DYNAMICPART_MENU, myMenu, _fPartWrapper);
   _fMenuBar->SetMenuItemText(ev, ID_BASEMENUBAR, DYNAMICPART_MENU, DynamicPartMenuText);

//---------------------------------------------

memset((PCH)&mi, 0, sizeof(ODPlatformMenuItem));

// MenuStopRotation is the string containing the text for the menu item
// ULONG has a range from 0 to 4,294,967,295
// Store the text from menu item 1 in mi.hltem

// AddMenuItemLast adds a submenu to the end of the menu bar
// DYNAMICPART_MENU = ID of the new menu
// kODNULL = Parameter to indicate a PM menu handler
// &mi = Pointer to the Part creating the menu

// DYNAMICPART_MENU = ID of the menu on which the menu item is to be placed
// Sets the text associated with the menu item DYNAMICPART_MENU+1
// MenuRotateDirection = String containing the text for menu item

   ODPlatformMenu mySubMenu;
   // Menu items for Rotate menu
   mi.id = DYNAMICPART_MENU_ROTATE;
   mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
   _fMenuBar->InsertSubmenu(ev, DYNAMICPART_MENU, mi.id, mySubMenu);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU, mi.id, (char *)MenuRotate);

   // Menu items for Horizontal Shear
   mi.id = DYNAMICPART_MENU_HSHEAR;
   mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
   _fMenuBar->InsertSubmenu(ev, DYNAMICPART_MENU, mi.id, mySubMenu);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU, mi.id, (char *)MenuHShear);

   // Menu items for Vertical Shear
   mi.id = DYNAMICPART_MENU_VSHEAR;
   mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
   _fMenuBar->InsertSubmenu(ev, DYNAMICPART_MENU, mi.id, mySubMenu);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU, mi.id, (char *)MenuVShear);

   // Menu items for Reset
   mi.id = DYNAMICPART_MENU_RESET;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU, mi.id, (char *)MenuReset);

   ///////////////////////////////////////////////////////////////////////
   // Add submenus for rotate
   mi.id = DYNAMICPART_MENU_RDIR;
   mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
   _fMenuBar->InsertSubmenu(ev, DYNAMICPART_MENU_ROTATE, mi.id, mySubMenu);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_ROTATE, mi.id, (char *)MenuRotateDirection);

   mi.id = DYNAMICPART_MENU_RDIR_FORWARD;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_RDIR, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_RDIR, mi.id, (char *)MenuRotateForward);

   mi.id = DYNAMICPART_MENU_RDIR_BACKWARD;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_RDIR, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_RDIR, mi.id, (char *)MenuRotateBackward);

   mi.id = DYNAMICPART_MENU_STOPPED;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_ROTATE, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_ROTATE, mi.id, (char *)MenuStopRotation);

   ///////////////////////////////////////////////////////////////////////
   // Add submenus for horizontal shear
   mi.id = DYNAMICPART_MENU_HDIR;
   mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
   _fMenuBar->InsertSubmenu(ev, DYNAMICPART_MENU_HSHEAR, mi.id, mySubMenu);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_HSHEAR, mi.id, (char *)MenuHShearDirection);

   mi.id = DYNAMICPART_MENU_HDIR_FORWARD;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_HDIR, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_HDIR, mi.id, (char *)MenuHShearForward);

   mi.id = DYNAMICPART_MENU_HDIR_BACKWARD;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_HDIR, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_HDIR, mi.id, (char *)MenuHShearBackward);

   mi.id = DYNAMICPART_MENU_HSTOPPED;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_HSHEAR, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_HSHEAR, mi.id, (char *)MenuStopHShear);
   ///////////////////////////////////////////////////////////////////////
   // Add submenus for vertical shear
   mi.id = DYNAMICPART_MENU_VDIR;
   mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
   _fMenuBar->InsertSubmenu(ev, DYNAMICPART_MENU_VSHEAR, mi.id, mySubMenu);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_VSHEAR, mi.id, (char *)MenuVShearDirection);

   mi.id = DYNAMICPART_MENU_VDIR_FORWARD;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_VDIR, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_VDIR, mi.id, (char *)MenuVShearForward);

   mi.id = DYNAMICPART_MENU_VDIR_BACKWARD;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_VDIR, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_VDIR, mi.id, (char *)MenuVShearBackward);

   mi.id = DYNAMICPART_MENU_VSTOPPED;
   _fMenuBar->AddMenuItemLast(ev, DYNAMICPART_MENU_VSHEAR, mi.id, &mi);
   _fMenuBar->SetMenuItemText(ev, DYNAMICPART_MENU_VSHEAR, mi.id, (char *)MenuStopVShear);

//////////////////////////////////////////////////////////////////////////
// MenuItem 2

// MenuStopRotation is the string containing the text for the menu item
// ULONG has a range from 0 to 4,294,967,295
// Store the text from menu item 1 in mi.hltem



// AddMenuItemLast adds a submenu to the end of the menu bar
// DYNAMICPART_MENU = ID of the new menu
// kODNULL = Parameter to indicate a PM menu handler
// &mi = Pointer to the Part creating the menu


// DYNAMICPART_MENU = ID of the menu on which the menu item is to be placed
// Sets the text associated with the menu item DYNAMICPART_MENU+1
// MenuRotateDirection = String containing the text for menu item

   memset((PCH)&mi, 0, sizeof(ODPlatformMenuItem));



///////////////////////////////////////////
//  Process our popup menu items
///////////////////////////////////////////
   if (_fPopup != NULL) {

     // remove unwanted items from popup menu
     _fPopup->RemoveMenu(ev, VIEW_SHOWAS);

     // Add our new menu items.
     memset((PCH)&mi, 0, sizeof(ODPlatformMenuItem));

     // Menu items for Rotate menu
     mi.id = DYNAMICPART_MENU_ROTATE;
     mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
     _fPopup->InsertSubmenu(ev, ID_BASEPOPUP, mi.id, mySubMenu);
     _fPopup->SetMenuItemText(ev, ID_BASEPOPUP, mi.id, (char *)MenuRotate);

     // Menu items for Horizontal Shear
     mi.id = DYNAMICPART_MENU_HSHEAR;
     mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
     _fPopup->InsertSubmenu(ev, ID_BASEPOPUP, mi.id, mySubMenu);
     _fPopup->SetMenuItemText(ev, ID_BASEPOPUP, mi.id, (char *)MenuHShear);

     // Menu items for Vertical Shear
     mi.id = DYNAMICPART_MENU_VSHEAR;
     mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
     _fPopup->InsertSubmenu(ev, ID_BASEPOPUP, mi.id, mySubMenu);
     _fPopup->SetMenuItemText(ev, ID_BASEPOPUP, mi.id, (char *)MenuVShear);

     // Menu items for Reset
     mi.id = DYNAMICPART_MENU_RESET;
     _fPopup->AddMenuItemLast(ev, ID_BASEPOPUP, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, ID_BASEPOPUP, mi.id, (char *)MenuReset);

     ///////////////////////////////////////////////////////////////////////
     // Add submenus for rotate

     mi.id = DYNAMICPART_MENU_RDIR;
     mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
     _fPopup->InsertSubmenu(ev, DYNAMICPART_MENU_ROTATE, mi.id, mySubMenu);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_ROTATE, mi.id, (char *)MenuRotateDirection);

     mi.id = DYNAMICPART_MENU_RDIR_FORWARD;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_RDIR, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_RDIR, mi.id, (char *)MenuRotateForward);

     mi.id = DYNAMICPART_MENU_RDIR_BACKWARD;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_RDIR, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_RDIR, mi.id, (char *)MenuRotateBackward);

     mi.id = DYNAMICPART_MENU_STOPPED;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_ROTATE, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_ROTATE, mi.id, (char *)MenuStopRotation);

     ///////////////////////////////////////////////////////////////////////
     // Add submenus for horizontal shear
     mi.id = DYNAMICPART_MENU_HDIR;
     mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
     _fPopup->InsertSubmenu(ev, DYNAMICPART_MENU_HSHEAR, mi.id, mySubMenu);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_HSHEAR, mi.id, (char *)MenuHShearDirection);

     mi.id = DYNAMICPART_MENU_HDIR_FORWARD;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_HDIR, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_HDIR, mi.id, (char *)MenuHShearForward);

     mi.id = DYNAMICPART_MENU_HDIR_BACKWARD;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_HDIR, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_HDIR, mi.id, (char *)MenuHShearBackward);

     mi.id = DYNAMICPART_MENU_HSTOPPED;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_HSHEAR, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_HSHEAR, mi.id, (char *)MenuStopRotation);
     ///////////////////////////////////////////////////////////////////////
     // Add submenus for vertical shear
     mi.id = DYNAMICPART_MENU_VDIR;
     mySubMenu = WinCreateMenu(HWND_OBJECT, NULLHANDLE);
     _fPopup->InsertSubmenu(ev, DYNAMICPART_MENU_VSHEAR, mi.id, mySubMenu);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_VSHEAR, mi.id, (char *)MenuVShearDirection);

     mi.id = DYNAMICPART_MENU_VDIR_FORWARD;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_VDIR, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_VDIR, mi.id, (char *)MenuVShearForward);

     mi.id = DYNAMICPART_MENU_VDIR_BACKWARD;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_VDIR, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_VDIR, mi.id, (char *)MenuVShearBackward);

     mi.id = DYNAMICPART_MENU_VSTOPPED;
     _fPopup->AddMenuItemLast(ev, DYNAMICPART_MENU_VSHEAR, mi.id, &mi);
     _fPopup->SetMenuItemText(ev, DYNAMICPART_MENU_VSHEAR, mi.id, (char *)MenuStopRotation);

    } /* endif (fPopup != NULL) */
} catch (...) {
    reportAnyException(ev);
} /* end try */
