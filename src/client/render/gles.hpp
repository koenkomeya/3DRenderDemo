/**
 * @file gles.hpp
 * @brief Represents implementations of data structures for GLES targets
 *
 * @date November 19, 2018 02:14
 * @author Koen Komeya 
 */

#ifndef CLIENT_RENDER_GLES_HPP_
#define CLIENT_RENDER_GLES_HPP_
#include "k.hpp"
#ifdef TARGET_ATTR_REND_GLES_3_0
#include <GLES2/gl2.h>

namespace kRender {

    /**
     * @struct RenderData
     *
     * @brief Holds data related to the render context.
     * @since November 18, 2018 21:47
    **/
    struct RenderData{ //TODO move to a gles common header
        GLint defProgram;
        GLint texUni;
        GLint mvvertUni;
        GLint mvvecUni;
        GLint iclightvecUni;
    };
}

#endif /* CLIENT_RENDER_GLES_HPP_ */
