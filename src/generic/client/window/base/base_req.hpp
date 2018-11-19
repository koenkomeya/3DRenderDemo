/**
 * @file base_req.hpp
 * @brief Defines required functions for window/base to implement.
 * Should not be included by non-generic code!!
 * @date November 17, 2018 15:29
 * @author Koen Komeya <komeyakoen@gmail.com>
 */

#ifndef GENERIC_CLIENT_WINDOW_OS_BASE_REQ_HPP_
#define GENERIC_CLIENT_WINDOW_OS_BASE_REQ_HPP_
/**
 * @namespace kGenWinOSBase
 * @brief Contains hidden functions pertaining to the display
 * Contains functions pertaining to the display that should only be
 * visible to window/base and window/os.
 * @author Koen Komeya
 */
namespace kGenWinOSBase{
    /**
     * Initializes base submodule.
     * @since Nov 17 4:04 PM
     */
    void initSubmodule();

    /**
     * Tells the OS that the program is safe to close. (Required for certain "OSs" like emscripten).0
     * @since Nov 17 4:13 PM
     */
    void osSafeToClose(bool safe);
}


#endif /* GENERIC_CLIENT_WINDOW_OS_BASE_REQ_HPP_ */
