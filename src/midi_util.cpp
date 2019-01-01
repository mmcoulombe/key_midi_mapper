#include "midi_util.hpp"

namespace MIDI {

  char getScaleValueFromString(const std::string &value) {
    if (value.compare("C")) {
      return 0;
    } else if (value.compare("C#")) {
      return 1;
    } else if (value.compare("D")) {
      return 2;
    } else if (value.compare("D#")) {
      return 3;
    } else if (value.compare("E")) {
      return 4;
    } else if (value.compare("F")) {
      return 5;
    } else if (value.compare("F#")) {
      return 6;
    } else if (value.compare("G")) {
      return 7;
    } else if (value.compare("G#")) {
      return 8;
    } else if (value.compare("A")) {
      return 9;
    } else if (value.compare("A#")) {
      return 10;
    } else if (value.compare("B")) {
      return 11;
    } else {
      return -1;
    }
  }

  int getOctave(int pitch) {
    return (pitch / 12) - 2;
  }

  int getNoteIndex(int pitch) {
    return pitch % 12;
  }

  std::optional<std::string> getScaleStr(short scale)
  {
    switch (scale) {
      case 0:
        return "C";
      case 1:
        return "C#";
      case 2:
        return "D";
      case 3:
        return "D#";
      case 4:
        return "E";
      case 5:
        return "F";
      case 6:
        return "F#";
      case 7:
        return "G";
      case 8:
        return "G#";
      case 9:
        return "A";
      case 10:
        return "A#";
      case 11:
        return "B";
    }
    return {};
  }
}