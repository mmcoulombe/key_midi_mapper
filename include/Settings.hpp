//-----------------------------------------------------------------------------
//  GNU General Public License v3.0+
//  (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
//-----------------------------------------------------------------------------

/*!
 * \file Settings.hpp
 * \brief Load and keep the information obtained from a configuration file.
 * \author Maxime Millette-Coulombe
 * \version 0.1
 */

#ifndef SETTINGS_HPP_HEADER
#define SETTINGS_HPP_HEADER

#include <optional>
#include <string>
#include <unordered_map>

// ie: C4 -> "k"
typedef std::unordered_map<std::string, unsigned char> KeyMap;

/*!
 * \class Settings
 * \brief Logical representation of a config file
 */
class Settings {
  public:
    /*!
     * \brief Constructor
     *
     * Empty constructor for the setting instance.
     *
     * To avoid dealing with exception of loading the configuration file
     * in the constructor, we did it in a separate method.
     */
    Settings();

    /*!
     * \brief Destructor
     *
     * Empty Destructor
     */
    ~Settings();

    /*!
     * \brief load a config file from a file
     * 
     * Method allowing us to read the content of a toml file
     * and extract its content in order to have our application
     * use it later on.
     * 
     * \param path: the fil path on the os. (relative or absolute)
     * \return true if the file has been parsed without any error,
     *  False otherwise
     */
    bool loadFromFile(const std::string& path);

    /*!
     * \brief Get the key string for a specific note
     * 
     * From the information obtained from the configuration file, looks
     * into the key mapping section to find if there is a key string mapped
     * for the given note string.
     * 
     * \param noteStr: the note string to check for a mapping key note
     * \return an optinal value containing the key code of the key string
     *  mapped to the given string note.
     */
    std::optional<short> getMappingNote(const std::string& noteStr);
  
  private:
    KeyMap m_map; /*!< Contains the mapping of note to key string */
};

#endif // SETTINGS_HPP_HEADER