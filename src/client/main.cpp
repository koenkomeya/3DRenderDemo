/**
 *******************************************************************************
 * @file    main.cpp
 * @brief   Demo for OpenGL ES Rendering?
 *
 * This is a demo for OpenGL ES rendering! (this isn't really much right now)
 *
 * As for this file, this contains stuff relating to program initialization.
 *
 * @author  Koen Komeya <komeyakoen@gmail.com>
 * @date    November 14, 2018 10:36
 *******************************************************************************
**/
#include "k.hpp"
#ifdef TARGET_ATTR_TOOL_EM
# include <emscripten.h>
# ifndef __EMSCRIPTEN__
void usleep(int time); //<- To fix syntax highlighting errors
# endif
#endif
#include "client/window.hpp"
#include "client/render.hpp"
#include "client/game.hpp"

/**
 * Initializes
 */
void init(){
    kWindow::initModule();

}

kGame::GameData data;

void tick(){
    data.getPlayer()->tick();
    kRender::render(data.frame, &data);
}

/**
 * Entry point of the program
 */
int main_client(int argc, char **argv) {
    init();
    data.frame = new kWindow::GFrame(&data);
    kRender::init(data.frame);
#ifdef TARGET_ATTR_TOOL_EM
    emscripten_set_main_loop(&tick, 60, 1);
#else
#error "Main loop not implemented for target"
#endif
    return 0;
}

