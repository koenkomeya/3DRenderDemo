/**
 * @file render.hpp
 * @brief Header that specifies render-target-specific functionality.
 * @date November 18, 2018 20:37
 * @author Koen Komeya 
 */

#ifndef CLIENT_RENDER_HPP_
#define CLIENT_RENDER_HPP_
#include "k.hpp"
#include "client/window.hpp"

/**
 * @namespace kRender
 * @brief Namespace for render-target-specific functionality.
 *
 * @author Koen Komeya
 * @since November 18, 2018 20:45
 */
namespace kRender{

    struct RenderData;

    /**
     * @fn init
     * @brief Initializes the renderer
     * @param frame frame to render to
     * @since November 18, 2018 21:34
    **/
    void init (kWindow::GFrame& frame);

    /**
     * @fn render
     * @brief Handles the rendering for this program
     * @param frame frame to render to
     * @since November 18, 2018 20:46
    **/
    void render(kWindow::GFrame& frame);
}

#endif /* CLIENT_RENDER_HPP_ */
