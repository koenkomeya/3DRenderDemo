/**
 * @file glfw.cpp
 * @brief Custom window-based code for GLFW
 *
 * @date November 17, 2018 21:50
 * @author Koen Komeya 
 */

#include "k.hpp"
#ifdef TARGET_ATTR_WIND_GLFW
#include <stdexcept>
#include "client/window.hpp"
#include "client/render.hpp"

namespace kWindow{
    void initModule(){
        kGenWindow::initModule();
    }

    void winrefresh(GLFWwindow *win){
        void *p = glfwGetWindowUserPointer(win);
        if (p == nullptr) throw std::runtime_error("unexpected null userptr");
        GFrame *f = reinterpret_cast<GFrame*>(p);
        kRender::render(f, f->getGameData());
    }

    GFrame::GFrame(kGame::GameData *data) : kGenWindow::Frame(KGAME_DEF_WIDTH,
            KGAME_DEF_HEIGHT, KGAME_DEF_TITLE), gameData(data) {
        glfwSetWindowRefreshCallback(this->win, &winrefresh);
    }
}

#endif
