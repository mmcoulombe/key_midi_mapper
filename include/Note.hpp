//-----------------------------------------------------------------------------
//  GNU General Public License v3.0+
//  (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
//-----------------------------------------------------------------------------

/*!
 * \file Note.hpp
 * \brief Concrete representation of a note
 * \author Maxime Millette-Coulombe
 * \version 0.1
 */

#ifndef NOTE_HPP_HEADER
#define NOTE_HPP_HEADER

#include <optional>
#include <string>

/*!
 * \struct Note
 * \brief A data structure representing a Note; scale + octave
 */
struct Note {
  /*!
   * \brief get the string note value
   *
   * Obtains the string note value of the scale and octave of that note
   *
   * \return the string note value
   */
  std::string asString() const;

  /*!
   * \brief Get a Note from a note string
   *
   * Try to parse a given string note into a Note. In order words,
   * extracting the scale and the octave from that note string if it's
   * a valid one
   *
   * \param noteStr: the string note value
   * \return an optional value of a Note
   */
  static std::optional<Note> fromString(const std::string& noteStr);

  // properties
  short octave; /*!< the note octave */
  short scale; /*!< the note scale */
};

#endif // NOTE_HPP_HEADER