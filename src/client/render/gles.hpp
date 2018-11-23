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
#include <cmath>

namespace kRender {

//Simple lighting vertex shader shamelessly taken from the
// OpenGLES 2.0 Quick Reference Card
const GLchar lightingVS[] =
        "uniform mat4 mvpVertMatrix; \n"
        "uniform mat3 mvVecMatrix; \n" //just inv of trans of topleft
        "uniform vec3 eyeCoordLightVec; \n" //remember to mvVec this
        "attribute vec3 vertPos; \n"
        "attribute vec3 vertNorm; \n"
        "attribute vec2 vertTex; \n"
        "varying float vcalcDiffuse; \n" //varying means it interpolates
        "varying vec2 vvertTex; \n"
        "void main() {\n"
        "    vec3 eyeCoordNorm = normalize(mvVecmatrix * vertNorm);\n"
        "    vcalcDiffuse = max(dot(eyeCoordLightVec, eyeCoordNorm), 0.0);\n"
        "    vvertTex = vertTex;\n"
        "    gl_Position = mvpVertmatrrix * vec4(vertPos, 1.0);\n"
        "}";

//Simple lighting fragment shader shamelessly taken from the
// OpenGLES 2.0 Quick Reference Card BUT WITH COLORED LIGHT,
// FIXED ALPHA, AND GAMMA=
const GLchar lightingFS[] =
        "#ifdef GL_FRAGMENT_PRECISION_HIGH"
        "precision highp float;"
        "#else"
        "precision mediump float;"
        "#endif"
        "uniform sampler2D texture; \n"
        "uniform vec3 ambient; \n"
        "uniform vec3 lightColor; \n"
        "uniform float alpha; \n"
        "varying float vcalcDiffuse; \n" /*varying means it interpolates*/
        "varying vec2 vvertTex; \n"
        "void main() {\n"
        "    vec4 fragTexColorG = texture2D(texture, vvertTex);\n"
        "    vec3 fragTexColorRGB;\n"
        "    if (fragTexColorG.r > 0.04045){\n"
        "        fragTexColorRGB.r = pow((fragTexColorG.r+0.055)/1.055,2.4);\n"
        "    } else {\n"
        "        fragTexColorRGB.r = fragTexColorG.r / 12.92;\n"
        "    }\n"
        "    if (fragTexColorG.g > 0.04045){\n"
        "        fragTexColorRGB.g = pow((fragTexColorG.g+0.055)/1.055,2.4);\n"
        "    } else {\n"
        "        fragTexColorRGB.g = fragTexColorG.g / 12.92;\n"
        "    }\n"
        "    if (fragTexColorG.b > 0.04045){\n"
        "        fragTexColorRGB.b = pow((fragTexColorG.b+0.055)/1.055,2.4);\n"
        "    } else {\n"
        "        fragTexColorRGB.b = fragTexColorG.b / 12.92;\n"
        "    }\n"
        "    vec3 diffuseColor = vcalcDiffuse * lightColor;\n"
        "    vec3 rawFragRGB = min(fragTexColorRGB * (diffuseColor+ambient),1);\n"
        "    if (rawTexColorG.r > 0.04045){\n"
        "        rawTexColorRGB.r = pow(1.055*rawTexColorG.r-0.055,1/2.4);\n"
        "    } else {\n"
        "        rawTexColorRGB.r = rawTexColorG.r * 12.92;\n"
        "    }\n"
        "    if (rawTexColorG.g > 0.04045){\n"
        "        rawTexColorRGB.g = pow(1.055*rawTexColorG.g-0.055,1/2.4);\n"
        "    } else {\n"
        "        rawTexColorRGB.g = rawTexColorG.g * 12.92;\n"
        "    }\n"
        "    if (rawTexColorG.b > 0.04045){\n"
        "        rawTexColorRGB.b = pow(1.055*rawTexColorG.b-0.055,1/2.4);\n"
        "    } else {\n"
        "        rawTexColorRGB.b = rawTexColorG.b * 12.92;\n"
        "    }\n"
        "    gl_FragColor = vec4(rawTexColorRGB, fragTexColorG.a * alpha);\n"
        "}";


    constexpr int GLES_LOG_LENGTH = 256;

    /**
     * @struct RenderData
     *
     * @brief Holds data related to the render context.
     * @since November 18, 2018 21:47
    **/
    struct RenderData{ //TODO move to a gles common header
        GLint defProgram;
        GLint texUni;
        GLint mvpvertUni;
        GLint mvvecUni;
        GLint iclightvecUni;
        GLint alphaUni;
        GLint lightColorUni;
        GLuint rainbowTex[6];
        GLuint playerTex;
        GLuint playerModelVertBuf;
        GLuint playerModelFaceBuf;
    };

    /**
     * @fn glesCreateMatrices
     * @brief Creates the MV and eye-coord light matrices.
     * Calculates the MV and eye-coord light matrices.
     * Simply calculates the camera transformations using predetermined
     * component equations (does the cam translation, an y-axis rot, an x-axis
     * rotation, then the perspective transform using the matrix P * X * Y * T).
     * Determines eye-coord light matrix as MV^-1 * L where L is the light mat.
     * Uses an infinite projection matrix for flexibility.
     * @param cx x-coord of the camera from the rendered object's pos sys origin
     * @param cy y-coord of the camera from the rendered object's pos sys origin
     * @param cz z-coord of the camera from the rendered object's pos sys origin
     * @param cyaw yaw of the camera in radians
     * @param cpit pitch of the camera in radians
     * @param invOf2TanHalfFOV 1/(2tan(FOV/2))
     * @param cw_ch camera width divided by camera height
     * @param npdist distance to the near plane
     * @param camdist camera depth position alteration.
     * @param light light vector
     * @param mvpVert storage for the 4x4 model-view-projection matrix
     * @param mvVec storage for the 3x3 MV submatrix inv transpose ("normal")
     * @param iLight the light matrix after the mvpVec matrix is applied to it
     * @since November 22, 2018 19:59
    **/
    inline void glesCreateMatrices(double cx, double cy, double cz, double cyaw,
            double cpit, GLfloat invOf2TanHalfFOV, double cw_ch, double npdist,
            double camDist,
            GLfloat *light, GLfloat *mvpVert, GLfloat *mvVec, GLfloat *iLight){
#ifdef TARGET_ATTR_REND_GLES_3_0
        //Slightly greater than 2^-9. We use this to ensure inf depth works
        //smallest value that will give a change in value when subtracted from 2
        //Value based on mediump precision
        constexpr GLfloat epsilon = 0.00196;//required for infinite persp matrix
#else
        //Slightly greater than 2^-22. We use this to ensure inf depth works
        //smallest value that will give a change in value when subtracted from 2
        //Value based on floating point precision
        constexpr GLfloat epsilon = 2.4e-7; //required for infinite persp matrix
#endif
        const double sinyaw = std::sin(cyaw);
        const double cosyaw = std::cos(cyaw);
        const double sinpit = std::sin(cpit);
        const double cospit = std::cos(cpit);
        constexpr double onemineps = 1 - epsilon;
        //inverse of tan half horizontal fov
        const double io2thhfov = invOf2TanHalfFOV;
        //inverse of tan half vertical fov
        const double io2thvfov = invOf2TanHalfFOV / cw_ch;
        mvVec[0] = cosyaw;
        mvVec[1] = 0;
        mvVec[2] = -sinyaw;
        mvVec[3] = sinyaw * sinpit;
        mvVec[4] = cospit;
        mvVec[5] = cosyaw * sinpit;
        mvVec[6] = sinyaw * cospit;
        mvVec[7] = -sinpit;
        mvVec[8] = cosyaw * cospit;
        iLight[1] = mvVec[3]*light[0] + mvVec[4]*light[1] + mvVec[5]*light[2];
        iLight[2] = mvVec[6]*light[0] + mvVec[7]*light[1] + mvVec[8]*light[2];
        iLight[0] = cosyaw * light[0] - sinyaw * light[2];
        mvpVert[1]  = 0;
        //mvpVert[3]  = 0;
        //mvpVert[7]  = 0;
        //mvpVert[15] = 0;
        mvpVert[0]  = io2thhfov * cosyaw;
        mvpVert[2]  = -io2thhfov * sinyaw;
        mvpVert[4]  = io2thvfov * mvVec[3];
        mvpVert[5]  = io2thvfov * cospit;
        mvpVert[6]  = io2thvfov * mvVec[5];
        mvpVert[12] = -mvVec[6];
        mvpVert[13] = sinpit;
        mvpVert[14] = -mvVec[8];
        mvpVert[8]  = mvpVert[12] * onemineps;
        mvpVert[9]  = mvpVert[13] * onemineps;
        mvpVert[10] = mvpVert[14] * onemineps;
        mvpVert[3]  = mvpVert[0] * -cx - mvpVert[2] * cz;
        mvpVert[7]  = mvpVert[3] * -cx - mvpVert[4] * cy - mvpVert[5] * cz;
        mvpVert[15] = mvVec[6] * cx - sinpit * cy + mvVec[8] * cz + camDist;
        mvpVert[11] = (2 - epsilon) * npdist + mvpVert[15] * onemineps;
    }
}

#endif
#endif /* CLIENT_RENDER_GLES_HPP_ */
