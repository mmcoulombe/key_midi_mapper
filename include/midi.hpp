//-----------------------------------------------------------------------------
//  GNU General Public License v3.0+
//  (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
//-----------------------------------------------------------------------------

/*!
 * \file midi.hpp
 * \brief Methods to interact with the MIDI API regardless of the os
 * \author Maxime Millette-Coulombe
 * \version 0.1
 */

#ifndef MIDI_HPP_HEADER
#define MIDI_HPP_HEADER

#include <windows.h>

#include <memory>
#include <string>
#include <vector>

#include "MIDIDevice.hpp"

/*!
 * \struct MIDIDeviceInfo
 * \brief Contains meta data of a midi device
 * 
 * Data structure containing the meta data of a midi device.
 * Quite usefull, because you need to know the midi device ID
 * in order to use it.
 */
struct MIDIDeviceInfo {
  unsigned int id; /*!< the id of the midi device */
  std::string name; /*< the name of the midi device */
};

/*! \namespace MIDI
 * 
 * Namespace regrouping all methods related to the MIDI protocol
 */
namespace MIDI {
  /*!
   * /brief list all connected device
   *
   * Return a list of MIDIDeviceInfo coresponding to the meta data
   * of all connected MIDI device
   *
   * /return a list of all connected device information.
   */
  std::vector<MIDIDeviceInfo> listDevices() {
    std::vector<MIDIDeviceInfo> lstDeviceInfo;
    MIDIINCAPS mic;

    auto nbDevice = midiInGetNumDevs();
    for (unsigned int i = 0; i < nbDevice; ++i) {
      if (!midiInGetDevCaps(i, &mic, sizeof(MIDIINCAPS))) {
        char* str = mic.szPname;
        MIDIDeviceInfo deviceInfo = { i, str };
        lstDeviceInfo.push_back(deviceInfo);
      }
    }
    return lstDeviceInfo;
  }

  /*!
   * \brief Open a midi device
   * 
   * Method use to open a MIDI Device regarless of the os.
   * 
   * \param deviceId: the id of the MIDI device you want to open
   * \return a smart pointer of the opened device or a nullptr if the 
   *  opening process fail for a reason.
   */
  std::unique_ptr<MIDIDevice> open(int deviceId) {
    auto device = std::make_unique<MIDIDevice>(deviceId);
    auto mm = device->open();
    if (mm) {
      return std::move(device);
    }
    return nullptr;
  }
};

#endif //MIDI_HPP_HEADER