//-----------------------------------------------------------------------------
//  GNU General Public License v3.0+
//  (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
//-----------------------------------------------------------------------------

/*!
 * \file windows.hpp
 * \brief Specific win32 API keyboard IO
 * \author Maxime Millette-Coulombe
 * \version 0.1
 */

#ifndef IO_WINDOWS_HEADER
#define IO_WINDOWS_HEADER

#include "windows.h"
 
/*! \namespace io
 * 
 * Namespace regrouping all input/output methods
 */
namespace io {
  /*!
   *  \brief Send a global key down or up event to the system
   *
   *  Use win32 API to send a key down or up event of the given keycode
   *
   *  \param keycode: The keyboard key number representation
   *  \param down: Define if it's a key down or key up event. 
   */
  void sendKeyInput(int keycode, bool down) {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = keycode;
    ip.ki.dwFlags = down ? 0 : KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
  }
}

#endif // IO_WINDOWS_HEADER