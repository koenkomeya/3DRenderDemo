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

//FIXME implement functions instead of delegating?

//Simple lighting vertex shader shamelessly taken from the
// OpenGLES 2.0 Quick Reference Card
const GLchar lightingVS[] =
        "uniform mat4 mvVertMatrix; \n"
        "uniform mat3 mvVecMatrix; \n" //just inv of trans of topleft
        "uniform vec3 eyeCoordLightVec; \n" //remember to mvVec this
        "attribute vec3 vertPos; \n"
        "attribute vec3 vertNorm; \n"
        "attribute vec2 vertTex; \n"
        "varying float vcalcDiffuse; \n" //varying means it interpolates
        "varying vec2 vvertTex; \n"
        "void main() {\n"
        "    vec3 eyeCoordNorm = normalize(myVecmatrix * vertNorm);\n"
        "    vcalcDiffuse = normalize(myVecmatrix * vertNorm);\n"
        "    vvertTex = vertTex;\n"
        "    gl_Position = mvVertmatrrix * vec4(vertPos, 1.0);\n"
        "}";

//Simple lighting fragment shader shamelessly taken from the
// OpenGLES 2.0 Quick Reference Card BUT WITH COLORED LIGHT,
// FIXED ALPHA, AND GAMMA
#define LIGHTING_FRAG_SHADER_COMMON \
        "uniform sampler2D texture; \n"\
        "uniform vec3 ambient; \n"\
        "uniform vec3 lightColor; \n"\
        "varying float vcalcDiffuse; \n" /*varying means it interpolates*/ \
        "varying vec2 vvertTex; \n"\
        "void main() {\n"\
        "    vec4 fragTexColorG = texture2D(texture, vvertTex);\n"\
        "    vec3 fragTexColorRGB;\n"\
        "    if (fragTexColorG.r > 0.04045){\n"\
        "        fragTexColorRGB.r = pow((fragTexColorG.r+0.055)/1.055,2.4);\n"\
        "    } else {\n"\
        "        fragTexColorRGB.r = fragTexColorG.r / 12.92;\n"\
        "    }\n"\
        "    if (fragTexColorG.g > 0.04045){\n"\
        "        fragTexColorRGB.g = pow((fragTexColorG.g+0.055)/1.055,2.4);\n"\
        "    } else {\n"\
        "        fragTexColorRGB.g = fragTexColorG.g / 12.92;\n"\
        "    }\n"\
        "    if (fragTexColorG.b > 0.04045){\n"\
        "        fragTexColorRGB.b = pow((fragTexColorG.b+0.055)/1.055,2.4);\n"\
        "    } else {\n"\
        "        fragTexColorRGB.b = fragTexColorG.b / 12.92;\n"\
        "    }\n"\
        "    vec3 diffuseColor = vcalcDiffuse * lightColor;\n" \
        "    vec3 rawFragRGB = min(fragTexColorRGB * (diffuseColor+ambient),1);\n"\
        "    if (rawTexColorG.r > 0.04045){\n"\
        "        rawTexColorRGB.r = pow(1.055*rawTexColorG.r-0.055,1/2.4);\n"\
        "    } else {\n"\
        "        rawTexColorRGB.r = rawTexColorG.r * 12.92;\n"\
        "    }\n"\
        "    if (rawTexColorG.g > 0.04045){\n"\
        "        rawTexColorRGB.g = pow(1.055*rawTexColorG.g-0.055,1/2.4);\n"\
        "    } else {\n"\
        "        rawTexColorRGB.g = rawTexColorG.g * 12.92;\n"\
        "    }\n"\
        "    if (rawTexColorG.b > 0.04045){\n"\
        "        rawTexColorRGB.b = pow(1.055*rawTexColorG.b-0.055,1/2.4);\n"\
        "    } else {\n"\
        "        rawTexColorRGB.b = rawTexColorG.b * 12.92;\n"\
        "    }\n"\
        "    gl_FragColor = vec4(rawTexColorRGB, fragTexColorG.a);\n" \
        "}"

const GLchar lightingFSHighP[] =
        "precision highp float;"
        LIGHTING_FRAG_SHADER_COMMON;


const GLchar lightingFSMedP[] =
        "precision mediump float;"
        LIGHTING_FRAG_SHADER_COMMON;

constexpr int GLES_LOG_LENGTH = 256;

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
        cerr << log;
    }
    void printGLESProgramInfoLog(GLuint program){
        GLchar log[GLES_LOG_LENGTH];
        glGetProgramInfoLog(program, GLES_LOG_LENGTH, nullptr, log);
        cerr << log;
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
        RenderData& rd = frame->renderData;

        const GLchar **vShaders = &lightingVS; //array not const workaround
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        //We bind the shader code to the object
        glShaderSource(vs, 1, vShaders, nullptr);
        //compile the shader
        glCompileShader(vs);
        GLint glSuccess;
        glGetShaderiv(vs, GL_SHADER_TYPE, &glSuccess);
        if (glSuccess == GL_FALSE){
            printGLESShaderInfoLog(vs);
            throw std::runtime_error("Failed to compile GLES3 vertex shader");
        }
        const GLchar **fShadersHP = &lightingFSHighP; //array not const workard
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        //We bind the shader code to the object
        glShaderSource(fs, 1, fShadersHP, nullptr);
        //compile the shader
        glCompileShader(fs);
        glGetShaderiv(fs, GL_SHADER_TYPE, &glSuccess);
        if (glSuccess == GL_FALSE){
            while (glGetError() != GL_NO_ERROR); //Clear errors
            const GLchar **fShadersMP = &lightingFSMedP; //array not const wkrd
            //We bind the shader code to the object
            glShaderSource(fs, 1, fShadersMP, nullptr);
            //compile the shader
            glCompileShader(fs);
            glGetShaderiv(fs, GL_SHADER_TYPE, &glSuccess);
            if (!glSuccess){
                printGLESShaderInfoLog(fs);
                throw std::runtime_error(
                        "Failed to compile GLES3 fragment shader");
            }
        }
        //Create the program
        GLuint program = glCreateProgram();
        if (program == 0){
            printGLESProgramInfoLog(program);
            throw std::runtime_error("Failed to create GLES3 program");
        }
        //Attach shaders
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        //Bind attributes to the shaders
        glBindAttribLocation(program, 0, "vertPos");
        glBindAttribLocation(program, 1, "vertNorm");
        glBindAttribLocation(program, 2, "vertTex");
        //Link and check to make sure everything went fine
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &glSuccess);
        if (glSuccess == GL_FALSE){
            printGLESProgramInfoLog(program);
            throw std::runtime_error("Failed to link GLES3 program");
        }
        //frame.renderData.defProgram = program;
        //Since we only have one program, we can just call this here.
        glUseProgram(program);

        glClearColor(0.5, 0.6, 1, 1);
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
        RenderData* renderData = frame->renderData;
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


