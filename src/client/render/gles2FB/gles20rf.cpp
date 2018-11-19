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
#include <cmath>
#include <GLES2/gl2.h>
#include "client/window.hpp"
#include "client/game.hpp"
#include "client/render.hpp"

const GLchar lightingVS[];
const GLchar lightingFSHighP[];
const GLchar lightingFSMedP[];

namespace kRender {


    void printGLESShaderInfoLog(GLuint shader);
    void printGLESProgramInfoLog(GLuint program);

    void initFB(kWindow::GFrame* frame){
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
                frame->renderData.defProgram = program;
                //Since we only have one program, we can just call this here.
                glUseProgram(program);
                glUniform3f(glGetUniformLocation(program,"ambient"),0.6,0.6,0.6);
                glUniform3f(glGetUniformLocation(program,"lightColor"),
                        0.8, 0.8, 0.8);
                frame->renderData.texUni = glGetUniformLocation(program,
                        "texture");
                frame->renderData.iclightvecUni = glGetUniformLocation(program,
                        "eyeCoordLightVec");
                frame->renderData.mvvecUni = glGetUniformLocation(program,
                        "mvVecMatrix");
                frame->renderData.mvvertUni = glGetUniformLocation(program,
                        "mvVertMatrix");
                glClearColor(0.5, 0.6, 1, 1);
    }

    void renderFB(kWindow::GFrame* frame, kGame::GameData* data){
        RenderData& renderData = frame->renderData;
        kRender::render_common(frame, data);
        kGame::Player *p = data->getPlayer();

        glFlush();
        frame->swapBuffers();
    }

    void renderFBPlayer (kWindow::GFrame* frame, kGame::Player* player){

    }
    constexpr long double sqrt3_2 = sqrt(3.0l) / 2;
    void renderFBLand (kWindow::GFrame* frame, kGame::GameData *data){

    }

}  // namespace kRender
#endif


