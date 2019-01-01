#include "Note.hpp"

#include "midi_util.hpp"

std::string Note::asString() const {
  // kinda safe since a Note so far contains a valid scale and octave
  std::string scaleStr = MIDI::getScaleStr(scale).value_or("");
  scaleStr.append(std::to_string(octave));
  return scaleStr;
}

std::optional<Note> Note::fromString(const std::string& noteStr) {
  auto len = noteStr.size();
  int slipIndex = len == 2 ? 1 : len == 3 ? 2 : 0;
  if (slipIndex <= 0 || slipIndex > 2) {
    return {};
  }

  Note note;
  auto strScale =  noteStr.substr(0, slipIndex);
  auto strOctave = noteStr.substr(slipIndex, noteStr.size() - 1);

  auto scale = MIDI::getScaleValueFromString(strScale);
  auto octave = atoi(strOctave.c_str());

  // safety check. Do not create a note if the given values are garbish
  if (scale < 0 || scale > 11 || octave <  0 || octave > 8) {
    return {};
  }

  note.scale = scale;
  note.octave = octave;
  return note;
};
