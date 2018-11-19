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
#include "client/game.hpp"

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
    void init (kWindow::GFrame* frame);

    /**
     * @fn render
     * @brief Handles the rendering for this program
     * @param frame frame to render to
     * @since November 18, 2018 20:46
    **/
    void render(kWindow::GFrame* frame, kGame::GameData* data);

    /**
     * @fn render_common
     * @brief Renders all the entities; render(GFrame*) is probably what you are looking for.
     * @param frame frame to render to
     * @since November 19, 2018 03:05
    **/
    void render_common (kWindow::GFrame* frame, kGame::GameData* data);

    /**
     * @fn renderPlayer
     * @brief Renders a player
     * @param frame frame to render to
     * @param player player to draw
     * @since November 19, 2018 03:09
    **/
    void renderPlayer (kWindow::GFrame* frame, kGame::Player* player);

    /**
     * @fn renderLand
     * @brief Renders the land.
     * @param frame frame to render to
     * @param data the game state
     * @since November 19, 2018 03:10
    **/
    void renderLand (kWindow::GFrame* frame, kGame::GameData* data);

    /**
     * @fn renderNag
     * @brief Renders nag for focus.
     * @param frame frame to render to
     * @since November 19, 2018 04:15
    **/
    void renderNag (kWindow::GFrame* frame);
}

#endif /* CLIENT_RENDER_HPP_ */
