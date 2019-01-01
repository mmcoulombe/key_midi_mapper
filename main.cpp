//-----------------------------------------------------------------------------
//  GNU General Public License v3.0+
//  (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
//-----------------------------------------------------------------------------

/*!
 * \file main.cpp
 * \brief MIDI Mapper executable entry point
 * \author Maxime Millette-Coulombe
 * \version 0.1
 */

#include <conio.h>
#include <iostream>

#include "io.hpp"
#include "Settings.hpp"
#include "midi.hpp"

int WinMain(HINSTANCE inst, HINSTANCE prevInst, LPSTR cmd, int shown) {
  // load the settings, basically the key mapping of the midi controller
  Settings setting;
  if(!setting.loadFromFile("config.toml")) {
    std::cerr << "Error loading 'config.toml'." << std::endl;
    return -1;
  }

  // check if a midi device is connected
  auto lstDeviceInfo = MIDI::listDevices();
  auto nbDevice = lstDeviceInfo.size();
  if (nbDevice < 1) {
    std::cerr << "No device found, make sure a MIDI Controller is connected." << std::endl;
    return -1;
  }
  std::cout << nbDevice << " MIDI device found !" << std::endl;
  
  for (unsigned int i = 0; i < lstDeviceInfo.size(); ++i) {
    auto deviceInfo =  lstDeviceInfo[i];
    std::cout << deviceInfo.id << " " << deviceInfo.name << std::endl;
  }
  
  
  std::cout << "Using the default one [Device ID : 0]" << std::endl;

  // try to open the default device
  auto midiDevice = MIDI::open(0);
  if (!midiDevice) {
    std::cerr << "Cannot open MIDI Device." << std::endl;
    return -1;
  }

  // start listening for inputs
  auto mm = midiDevice->listen();
  if(!mm) {
    std::cerr << "Error trying to start the device" << std::endl;
    return -1;
  }

  // loop until the device is disconnected (user input or force kill)
  MIDIEvent e;
  while (midiDevice->isConnected()) {
    while (midiDevice->pollEvent(e)) {
      std::cout << e.note.asString() << std::endl;
      switch(e.type) {
        case MIDIEvent::Type::note_on:
          if (auto keycode = setting.getMappingNote(e.note.asString())) {
            io::sendKeyInput(*keycode, true);
          }
          break;
        case MIDIEvent::Type::note_off:
          if (auto keycode = setting.getMappingNote(e.note.asString())) {
            io::sendKeyInput(*keycode, false);
          }
          break;
        default:
          break;
      }
    }
  
    if (!_kbhit()) {
      Sleep(100);
      continue;
    }
    int c = _getch();
    if (c == VK_ESCAPE) {
      midiDevice->close();
    }
  }
  std::cout << "Disconnected" << std::endl;
  midiDevice->close();

  return 0;
}