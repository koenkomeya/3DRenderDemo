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
#include "k.hpp"
#include "generic/client/gwindow.hpp"

#ifdef TARGET_ATTR_REND_GLES_3_0
#include "client/render/gles.hpp"
#else
#error "kRender::RenderData structure not implemented for target"
#endif

namespace kGame{ class GameData;}

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
    class GFrame : public kGenWindow::Frame{
    public:
        kRender::RenderData renderData;
        GFrame() = delete;
        GFrame(kGame::GameData *gameData);
        inline kGame::GameData *getGameData(){ return this->gameData;}
    private:
        kGame::GameData * const gameData;
    };
}



#endif /* CLIENT_WINDOW_HPP_ */
