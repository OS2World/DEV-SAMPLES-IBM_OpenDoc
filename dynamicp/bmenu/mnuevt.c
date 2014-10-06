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
/* @(#) 1.5 com/src/samples/dynamicp/bmenu/mnuevt.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:48 (97/02/18 13:59:55)
*******************************************************************
** Name: ODBoolean HandleMenuEvent
**
** Description: code fragment for handling DynamicPart Menu Events.
**              Handles the WM_COMMAND (PM) message's defined for
**              this part.
**
*******************************************************************
*/
try {

    ODBoolean setChangedFlag = kODFalse;
#ifdef _PLATFORM_OS2_
    ODCommandID command = LONGFROMMP(event->mp1);
#elif defined(_PLATFORM_WIN32_)
    ODCommandID command = LOWORD(event->wParam);
#endif
#ifdef _SHOWMESSAGEBOXES_
    ODWindow *focusWindow = FocusFrame->AcquireWindow(ev);
    IWindow focusIwindow(IWindowHandle(focusWindow->GetPlatformWindow(ev)));
    IMessageBox myMessageBox(&focusIwindow);
    focusWindow->Release(ev);

    IString   msgTitle   = "";
    IString   msgString  = "";
#endif
    if ((command >= MENUID_ACTIVEPART_USER)
      &&(command <= MENUID_ACTIVEPART_LAST)) {
      // Commands from this part's menu(s)
      switch (command)
         {
         case DYNAMICPART_MENU_RDIR_FORWARD:
            if (!_xRotateClockwise) {
              _xRotateClockwise = kODTrue;
              setChangedFlag = kODTrue;
            }
            handled = kODTrue;
            break;

         case DYNAMICPART_MENU_RDIR_BACKWARD:
            if (_xRotateClockwise) {
              _xRotateClockwise = kODFalse;
              setChangedFlag = kODTrue;
            }
            handled = kODTrue;
            break;

         case DYNAMICPART_MENU_HDIR_FORWARD:
            if (!_hShearRight) {
              _hShearRight = kODTrue;
              setChangedFlag = kODTrue;
            }
            handled = kODTrue;
            break;

         case DYNAMICPART_MENU_HDIR_BACKWARD:
            if (_hShearRight) {
              _hShearRight = kODFalse;
              setChangedFlag = kODTrue;
            }
            handled = kODTrue;
            break;

         case DYNAMICPART_MENU_VDIR_FORWARD:
            if (!_vShearUp) {
              _vShearUp = kODTrue;
              setChangedFlag = kODTrue;
            }
            handled = kODTrue;
            break;

         case DYNAMICPART_MENU_VDIR_BACKWARD:
            if (_vShearUp) {
              _vShearUp = kODFalse;
              setChangedFlag = kODTrue;
            }
            handled = kODTrue;
            break;

         case DYNAMICPART_MENU_STOPPED: {
            // this case should either start or stop rotation

            int msgNumber ;
            somSelf->_set_xRotateActive(ev, !_xRotateActive);
#ifdef _SHOWMESSAGEBOXES_
            _Resources->open();
            if (_Resources->isOpen()) {
               msgTitle = _Resources->loadString(msgNumber);
               msgString = _Resources->loadMessage(msgNumber);
            } /* endif */
            _Resources->close();
            myMessageBox.setTitle(msgTitle);
            myMessageBox.show(msgString,IMessageBox::okButton | IMessageBox::warningIcon
                                      | IMessageBox::moveable | IMessageBox::applicationModal);
#endif
            setChangedFlag = kODTrue;
            handled = kODTrue;
            }
            break;

         case DYNAMICPART_MENU_HSTOPPED: {
            // this case should either start or stop horizontal shear

            int msgNumber ;
            somSelf->_set_hShearActive(ev, !_hShearActive);
#ifdef _SHOWMESSAGEBOXES_
            _Resources->open();
            if (_Resources->isOpen()) {
               msgTitle = _Resources->loadString(msgNumber);
               msgString = _Resources->loadMessage(msgNumber);
            } /* endif */
            _Resources->close();
            myMessageBox.setTitle(msgTitle);
            myMessageBox.show(msgString,IMessageBox::okButton | IMessageBox::warningIcon
                                      | IMessageBox::moveable | IMessageBox::applicationModal);
#endif
            setChangedFlag = kODTrue;
            handled = kODTrue;
            }
            break;

         case DYNAMICPART_MENU_VSTOPPED: {
            // this case should either start or stop vertical shear

            int msgNumber ;
            somSelf->_set_vShearActive(ev, !_vShearActive);
#ifdef _SHOWMESSAGEBOXES_
            _Resources->open();
            if (_Resources->isOpen()) {
               msgTitle = _Resources->loadString(msgNumber);
               msgString = _Resources->loadMessage(msgNumber);
            } /* endif */
            _Resources->close();
            myMessageBox.setTitle(msgTitle);
            myMessageBox.show(msgString,IMessageBox::okButton | IMessageBox::warningIcon
                                      | IMessageBox::moveable | IMessageBox::applicationModal);
#endif
            setChangedFlag = kODTrue;
            handled = kODTrue;
            }
            break;

         case DYNAMICPART_MENU_RESET: {
            // this case should either stop rotation and shear and reset angles
            somSelf->Reset(ev);
            setChangedFlag = kODTrue;
            handled = kODTrue;
            }
            break;

         default:
#ifdef _SHOWMESSAGEBOXES_
            _Resources->open();
            if (_Resources->isOpen()) {
               msgTitle = _Resources->loadString(DYNAMICPART_MENU_ERROR);
               msgString = _Resources->loadMessage(DYNAMICPART_MENU_ERROR);
            } /* endif */
            _Resources->close();
            myMessageBox.setTitle(msgTitle);
            myMessageBox.show(msgString,IMessageBox::okButton | IMessageBox::errorIcon
                                      | IMessageBox::moveable | IMessageBox::applicationModal);
            handled = kODTrue;
#endif
            break;
         }
         if (setChangedFlag) {
            somSelf->GetStorageUnit(ev)->GetDraft(ev)->SetChangedFromPrev(ev);
            ODUpdateID updateID = _fSession->UniqueUpdateID(ev);
            FocusFrame->ContentUpdated (ev, updateID);
         } /* endif */
    } else {
      // Commands from other menus (i.e. Edit)
    } /* endif */
} catch (...) {
    reportAnyException(ev);
} /* end try */
