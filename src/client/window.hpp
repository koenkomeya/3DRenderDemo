/**
 * @file window.hpp
 * @brief Fix me son
 *
 * This does stuff
 *
 * @date November 17, 2018 21:10
 * @author Koen Komeya <komeyakoen@gmail.com>
 */

#ifndef CLIENT_WINDOW_HPP_
#define CLIENT_WINDOW_HPP_

#include "generic/client/gwindow.hpp"

//definition for RenderData (since we can't circular include render.hpp)
namespace kRender{
    struct RenderData;
}

/**
 * @namespace kWindow
 * @brief Contains data structures and functions pertaining to a display.
 * @author Koen Komeya
 * @since November 17, 2018 21:42
 */
namespace kWindow{
    /**
     * @fn initModule
     * @brief Initializes this module.
     *
     * @param   param     description of param
     *
     * @since November 17, 2018 21:43
    **/
    void initModule();
    /**
     * @class GFrame
     *
     * @brief Frame that renders the game
     *
     * @since November 17, 2018 21:47
    **/
    class GFrame : kGenWindow::Frame{
    public:
        kRender::RenderData renderData;
        GFrame();
        ~GFrame();
    private:
    };
}



#endif /* CLIENT_WINDOW_HPP_ */
