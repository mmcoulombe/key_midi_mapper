//-----------------------------------------------------------------------------
//  GNU General Public License v3.0+
//  (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
//-----------------------------------------------------------------------------

/*!
 * \file midi_util.hpp
 * \brief Utilitary methods used to extract data from MIDI messages.
 * \author Maxime Millette-Coulombe
 * \version 0.1
 */

#ifndef MIDI_UTILS_HPP_HEADER
#define MIDI_UTILS_HPP_HEADER

#include <string>
#include <optional>

/*! \namespace MIDI
 * 
 * Namespace regrouping all methods related to the MIDI protocol
 */
namespace MIDI {
  /*!
   *  \brief Get the scale number value from the scale string
   *
   *  Get the scale index (0 to 11) from the scale string representation (C, D, A, etc)
   *
   *  \param value: The scale aka note we want the index.
   */
  char getScaleValueFromString(const std::string &value);

  /*!
   *  \brief Get the octave of the note based on the pitch value
   *
   *  Get the octave of the note based on the pitch value. 
   *  Note: The pitch is a value that represent a note scale and its octave.
   *  When you receive a MIDI message for a note, you'll obtain the pitch. You
   *  will need to manualy convert it to a scale and an octave.
   *
   *  \param pitch: The pitch of the note
   */
  int getOctave(int pitch);

  /*!
   *  \brief Get the index of the note based on the pitch value
   *
   *  Get the index of the note based on the pitch value. 
   *  Note: The pitch is a value that represent a note scale and its octave.
   *  When you receive a MIDI message for a note, you'll obtain the pitch. You
   *  will need to manualy convert it to a scale and an octave.
   *
   *  \param pitch: The pitch of the note
   */
  int getNoteIndex(int pitch);

  /*!
   * \brief the the scale string representation from its index
   * 
   * From the given scale index value (0 to 11), get the string
   * note representation value.
   * 
   * \return the optinal value containing the string note if the given
   *  scale corespond to one.
   */
  std::optional<std::string> getScaleStr(short scale);
};

#endif