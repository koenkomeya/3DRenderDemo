/**
 * @file gles20rf.cpp
 * @brief OpenGL ES 2.0 Renderer fallback
 *
 * @date November 18, 2018 20:44
 * @author Koen Komeya 
 */


#include "k.hpp"
#ifdef TARGET_ATTR_RENDFB_GLES_2_0
#include <stdexcept>
#include <GLES2/gl2.h>
#include "client/window.hpp"

namespace kRender {
    void initFB(kWindow::GFrame& frame){
        throw std::runtime_error("Error: Fallback not implemented");
    }

    void renderFB(kWindow::GFrame& frame){
        throw std::runtime_error("Error: Fallback not implemented");
    }

}  // namespace kRender
#endif


