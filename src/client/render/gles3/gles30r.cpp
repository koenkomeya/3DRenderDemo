/**
 * @file gles30r.cpp
 * @brief OpenGL ES 3.0 Renderer
 *
 * @date November 18, 2018 20:45
 * @author Koen Komeya 
 */

#include "k.hpp"
#ifdef TARGET_ATTR_REND_GLES_3_0
#include <stdexcept>
#include <iostream>
#include <GLES3/gl3.h>
#include "client/window.hpp"
#include "client/render.hpp"
#include "client/game.hpp"
#include "../gles.hpp"

//FIXME implement functions instead of delegating?


namespace kRender {
    /**
     * @struct RenderData
     *
     * @brief Holds data related to the render context.
     * @since November 18, 2018 21:47
    **/
    //struct RenderData{ //TODO move to a gles common header
        //GLint defProgram;
    //};

    void printGLESShaderInfoLog(GLuint shader){
        GLchar log[GLES_LOG_LENGTH];
        glGetShaderInfoLog(shader, GLES_LOG_LENGTH, nullptr, log);
        std::cerr << log;
        std::flush(std::cerr);
    }
    void printGLESProgramInfoLog(GLuint program){
        GLchar log[GLES_LOG_LENGTH];
        glGetProgramInfoLog(program, GLES_LOG_LENGTH, nullptr, log);
        std::cerr << log;
        std::flush(std::cerr);
    }

#ifdef TARGET_ATTR_RENDFB_GLES_2_0
    void initFB(kWindow::GFrame* frame);
#endif

    void init (kWindow::GFrame* frame){
#ifdef TARGET_ATTR_RENDFB_GLES_2_0
        //Do the fallback if we are using the fallback.
        //if (frame.isUsingFallback()){
            initFB(frame);
            return;
        //}
#endif
    }

#ifdef TARGET_ATTR_RENDFB_GLES_2_0
    void renderFB(kWindow::GFrame* frame, kGame::GameData* data);
#endif


    void render(kWindow::GFrame* frame, kGame::GameData* data){
#ifdef TARGET_ATTR_RENDFB_GLES_2_0
        //Do the fallback if we are using the fallback.
        //if (frame.isUsingFallback()){
            renderFB(frame, data);
            return;
        //}
#endif
        RenderData* renderData = &(frame->renderData);
        //Set
        //Render stuff
        kRender::render_common(frame, data);
        //Flush and display
        glFlush();
        frame->swapBuffers();
    }


    void renderFBPlayer (kWindow::GFrame* frame, kGame::Player* player);
    void renderFBLand (kWindow::GFrame* frame, kGame::GameData *data);

    void renderPlayer (kWindow::GFrame* frame, kGame::Player* player){
        renderFBPlayer(frame, player);
    }

    void renderLand (kWindow::GFrame* frame, kGame::GameData *data){
        renderFBLand(frame, data);
    }

    void renderNag (kWindow::GFrame* frame){
        //FIXME implement
    }

}  // namespace kRender
#endif


