/**
 * @file glfw.cpp
 * @brief Custom window-based code for GLFW
 *
 * @date November 17, 2018 21:50
 * @author Koen Komeya 
 */

#include "k.hpp"
#ifdef TARGET_ATTR_WIND_GLFW
#include "client/window.hpp"

namespace kWindow{
    void initModule(){
        kGenWindow::initModule();
    }
    GFrame::GFrame() : kGenWindow::Frame(KGAME_DEF_WIDTH, KGAME_DEF_HEIGHT,
            KGAME_DEF_TITLE){

    }
}

#endif
