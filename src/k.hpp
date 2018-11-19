/**
 * @file k.hpp
 * @brief Includes important headers
 *
 * Includes important headers relating to all aspects of the program.
 * Should be included in most source files.
 *
 * @date Nov 16, 2018 6:00:33 AM
 * @author Koen Komeya
 */

#ifndef K_HPP_
#define K_HPP_

#include "CMakeConfig.hpp"

#define STRIFY(x) #x

#define KGAME_DEF_WIDTH 800
#define KGAME_DEF_HEIGHT 600
#define KGAME_DEF_TITLE KGAME_NAME \
    " v. " STRIFY(KGAME_VERSION_MAJOR) "." STRIFY(KGAME_VERSION_MINOR)

#endif /* K_HPP_ */
