/**
 * @file render.cpp
 * @brief Contains common rendering code.
 *
 * @date November 19, 2018 03:05
 * @author Koen Komeya 
 */
#include "client/game.hpp"
#include "client/render.hpp"

namespace kRender{
    void render_common (kWindow::GFrame* frame, kGame::GameData *data){
        kRender::renderLand(frame, data);
        kRender::renderPlayer(frame, data->getPlayer());
    }
}


