#include "MIDIDevice.hpp"

#include <iostream>

#include "midi_util.hpp"

MIDIDevice::MIDIDevice(int id)
  : m_events()
  , m_device(NULL)
  , m_id(id)
  , m_connected(false)
{
}

MIDIDevice::~MIDIDevice()
{

}

bool MIDIDevice::open() {
  auto result = midiInOpen(&m_device, m_id, (DWORD_PTR)(void *)MIDIDevice::MidiInProc, (DWORD_PTR)(void *)this, CALLBACK_FUNCTION);
  if (result == MMSYSERR_NOERROR) {
    return true;
  }
  return false;
}

bool MIDIDevice::listen()
{
  auto result = midiInStart(m_device);
  if (result == MMSYSERR_NOERROR) {
    m_connected = true;
    return true;
  }
  m_connected = false;
  return false;
}

void MIDIDevice::close()
{
  midiInStop(m_device);
  midiInClose(m_device);
  m_device = NULL;
  m_connected = false;
}

bool MIDIDevice::isConnected() const
{
  return m_connected;
}

bool MIDIDevice::pollEvent(MIDIEvent& e)
{
  if (!m_events.empty()) {
    e = m_events.front();
    m_events.pop();
    return true;
  }

  return false;
}

void MIDIDevice::pushEvent(MIDIEvent& e)
{
  m_events.push(e);
}

void MIDIDevice::onMessageCb(UINT uMsg, DWORD dwParam1, DWORD dwParam2)
{
    switch (uMsg) {
    case MIM_OPEN:
      std::cout << "-----OPENED.-----" << std::endl;  
      break;
    case MIM_CLOSE:
      break;
    case MIM_DATA:
    {
        auto statusByte = LOBYTE(dwParam1);
        auto firstDataByte = HIBYTE(dwParam1);

        if ( (statusByte >> 4) == 8) {
          auto octave = MIDI::getOctave(firstDataByte);
          auto scale = MIDI::getNoteIndex(firstDataByte);

          MIDIEvent e;
          e.type = MIDIEvent::Type::note_off;
          e.note.octave = octave;
          e.note.scale = scale;

          pushEvent(e);
        } else if ((statusByte >> 4) == 9) {
          auto octave = MIDI::getOctave(firstDataByte);
          auto scale = MIDI::getNoteIndex(firstDataByte);

          MIDIEvent e;
          e.type = MIDIEvent::Type::note_on;
          e.note.octave = octave;
          e.note.scale = scale;

          pushEvent(e);
        }
      }
      break;
    case MIM_LONGDATA:
      std::cout << "-----LONGDATA'D.-----" << std::endl;
      break;
    case MIM_ERROR:
      std::cerr << "-----ERROR.-----" << std::endl;
      break;
    case MIM_LONGERROR:
      std::cerr << "-----LONGERROR.  EVEN WORSE.-----" << std::endl;
      break;
    }
}

void CALLBACK MIDIDevice::MidiInProc(HMIDIIN handle, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) 
{
  auto deviceInstance = reinterpret_cast<MIDIDevice*>(dwInstance);
  deviceInstance->onMessageCb(uMsg, dwParam1, dwParam2);
}