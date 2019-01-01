//-----------------------------------------------------------------------------
//  GNU General Public License v3.0+
//  (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
//-----------------------------------------------------------------------------

#ifndef MIDI_DEVICE_HPP_HEADER
#define MIDI_DEVICE_HPP_HEADER

/*!
 * \file MIDIDevice.cpp
 * \brief A midi device instance connected to the computer
 * \author Maxime Millette-Coulombe
 * \version 0.1
 */

#include <windows.h>
#include <string>
#include <queue>
#include "Note.hpp"

/*!
 * \struct MIDIEvent
 * \brief Possible events in a midi messag
 */
struct MIDIEvent {
  /*!
   * \brief Enumeration of all possible MIDI Event.
   */
  enum class Type {
    note_off, /*!< when a note is pressed */
    note_on, /*!< when a note is released */
  };

  Type type; /*!< the event type */
  Note note; /*!< in the case of a note event, the given note */
};

/*!
 * \class MIDIDevice
 * \brief A midi device instance connected to the computer
 */
class MIDIDevice {
  public:
    /*!
     * \brief Constructor
     * 
     * MIDI Device constructor
     * 
     * \param id: MIDI Event id
     */
    MIDIDevice(int id);

    /*!
     * \brief Destructor
     * 
     * MIDI Device destructor
     */
    virtual ~MIDIDevice();

    /*!
     * /brief open the MIDI device
     * 
     * Try to open the MIDI using the given id during the instance
     * creation
     * 
     * /return true if the device is successfuly open. False otherwise
     */
    bool open();

    /*!
     * /brief Listen to MIDI Message
     * 
     * Try to create a connection with the MIDI device in order to listen for
     * MIDI Message.
     * 
     * /return true if the connection has been established. False otherwise
     */
    bool listen();

    /*!
     * /brief Close the MIDI Device
     * 
     * Disconnect and discard the MIDI Device. 
     */
    void close();

    /*!
     * \brief if the device is connected
     * Check if the device is conneced. The device is considered has connected
     * if the method listen has been call.
     * 
     * \return true if the device is connectedh
     */
    bool isConnected() const;

    /*!
     * \brief get a MIDI Event
     * 
     * Dequeue the first received event from the event queue.
     * 
     * \param e: the midi event reference to store the event data
     * \return true if there is still event in the event queue
     */
    bool pollEvent(MIDIEvent& e);
  
  private:
    /*!
     * \brief WIN API callback method for all MIDI events
     * 
     * Callback method used by the WIN API for the MIDI protocol.
     * This method is given to the MIDI Protocol handler when opening a device.
     * This method will receive every message sent by the MIDI device.
     * 
     * By using the user data parameter given by the win api, we can pass the current
     * midi device instance in order to redirect that method call to the member method
     * onMessageCb.
     * 
     * \param handle: the MIDI instance handle
     * \param uMsg: the MIDI message
     * \param dwInstance: user data information
     * \param dwParam: first message parameter
     * \param dwParam: second message parameter
     */
    static void CALLBACK MidiInProc(HMIDIIN handle, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

    /*!
     * \brief handle midi message
     * 
     * Member method where the CALLBACK is redirected here. This method will be used
     * to handle every MIDI received
     * 
     * \param uMsg: the MIDI message
     * \param dwParam: first message parameter
     * \param dwParam: second message parameter
     */
    void onMessageCb(UINT uMsg, DWORD dwParam1, DWORD dwParam2);

    /*!
     * \brief Add event to the message queue
     * 
     * Add a new event in the midi event message queue
     * 
     * /param e: the reference of the MIDIEvent to add in the queue
     */
    void pushEvent(MIDIEvent& e);

    std::queue<MIDIEvent> m_events; /*!< the midi message event queue */
    HMIDIIN m_device; /*!< the midi device win32 instance*/
    int m_id; /*!< the id of the MIDI device */
    bool m_connected; /*!< if the device is connected a.k.a listening for messages */
};

#endif // MIDI_DEVICE_HPP_HEADER