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

/**
 * Initializes
 */
void init(){
    kWindow::initModule();
}

/**
 * Entry point of the program
 */
int main_client(int argc, char **argv) {
    init();
    kWindow::GFrame frame;
    while (true){

    }
    return 0;
}

