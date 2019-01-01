//-----------------------------------------------------------------------------
//  GNU General Public License v3.0+
//  (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
//-----------------------------------------------------------------------------

/*!
 * \file io.hpp
 * \brief Choose the appropriate IO implementation to use based on the platform based
 *   on the OS used.
 * \author Maxime Millette-Coulombe
 * \version 0.1
 */

#ifdef __linux__ 
    // linux code goes here
#elif _WIN32
    #include "internal/io/windows.hpp"
#else
    // mac and other goes here ?
#endif