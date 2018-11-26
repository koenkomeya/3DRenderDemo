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
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <GLES2/gl2.h>
#include "client/window.hpp"
#include "client/game.hpp"
#include "client/render.hpp"
#include "../gles.hpp"
#include "generic/common/math.hpp"

#include <cstdlib>

namespace kRender {
    const GLuint VERT_POS_ATTRIB = 0;
    const GLuint VERT_NORM_ATTRIB = 1;
    const GLuint VERT_TEX_ATTRIB = 2;

    void printGLESShaderInfoLog(GLuint shader);
    void printGLESProgramInfoLog(GLuint program);

    constexpr double sqrt2 = kMath::sqrtNR(2.0);
    constexpr double sqrt6 = kMath::sqrtNR(6.0);


    void initFB(kWindow::GFrame* frame){
        RenderData& rd = frame->renderData;

        const GLchar *vShader = lightingVS; //array not const workaround
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        //We bind the shader code to the object
        glShaderSource(vs, 1, &vShader, nullptr);
        //compile the shader
        glCompileShader(vs);
        GLint glSuccess;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &glSuccess);
        if (glSuccess == GL_FALSE){
            printGLESShaderInfoLog(vs);
            throw std::runtime_error("Failed to compile GLES2 vertex shader");
        }
        const GLchar * fShaderHP = lightingFS; //array not const workard
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        //We bind the shader code to the object
        glShaderSource(fs, 1, &fShaderHP, nullptr);
        //compile the shader
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &glSuccess);
        if (glSuccess == GL_FALSE){
            printGLESShaderInfoLog(fs);
            throw std::runtime_error(
                    "Failed to compile GLES3 fragment shader");
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
        glBindAttribLocation(program, VERT_POS_ATTRIB,  "vertPos");
        glBindAttribLocation(program, VERT_NORM_ATTRIB, "vertNorm");
        glBindAttribLocation(program, VERT_TEX_ATTRIB,  "vertTex");
        //Link and check to make sure everything went fine
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &glSuccess);
        if (glSuccess == GL_FALSE){
            printGLESProgramInfoLog(program);
            throw std::runtime_error("Failed to link GLES3 program");
        }
        rd.defProgram = program;
        //Since we only have one program, we can just call this here.
        glUseProgram(program);
        //Set Lighting
        glUniform3f(glGetUniformLocation(program,"ambient"),0.6,0.6,0.6);
        glUniform3f(rd.lightColorUni=glGetUniformLocation(program,"lightColor"),
                0.8, 0.8, 0.8);
        //Get Uniform locations for things in the shader.
        rd.texUni = glGetUniformLocation(program, "texture");
        rd.iclightvecUni = glGetUniformLocation(program, "eyeCoordLightVec");
        rd.mvvecUni = glGetUniformLocation(program, "mvVecMatrix");
        rd.mvpvertUni = glGetUniformLocation(program, "mvpVertMatrix");
        rd.alphaUni = glGetUniformLocation(program, "alpha");
        glUniform1f(rd.alphaUni, 1.0);

        //Prepare textures for triangles.
        glGenTextures(6, rd.rainbowTex);
        //Prepare colors
        const unsigned char COLORS[] = {
                0xf0, 0x00, 0x00, 0xe8,
                0xe0, 0x70, 0x00, 0xe8,
                0xf0, 0xf0, 0x00, 0xe8,
                0x00, 0xf0, 0x00, 0xe8,
                0x00, 0x00, 0xd0, 0xe8,
                0xd0, 0x00, 0xd0, 0xe8
        };
        //Set random
        std::srand(237);
        //Dynamically generate textures
        for (int i = 0; i < 6; i++){
            glActiveTexture(GL_TEXTURE0 + i); //Set texture i.
            glBindTexture(GL_TEXTURE_2D, rd.rainbowTex[i]); //Bind text
            // Make textures pixelly near and mergefar
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                        //Generate texture
            unsigned char tex[256 * 4];
            for (int p = 0; p < 256; p++){
                //tex[p] = COLORS[i] +
                //    (((std::rand() << 16) ^ std::rand()) & 0x0f0f0f00);
                tex[p * 4] = COLORS[i * 4] + (std::rand() & 0x0f);
                tex[p*4+1] = COLORS[i*4+1] + (std::rand() & 0x0f);
                tex[p*4+2] = COLORS[i*4+2] + (std::rand() & 0x0f);
                tex[p*4+3] = COLORS[i*4+3];
            }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, tex);
            GLenum err;
            if ((err = glGetError())){
                std::fprintf(stderr, "Error %d", err);
                std::fflush(stderr);
            }
        }
        //Enable vertex attribute arrays
        glEnableVertexAttribArray(VERT_POS_ATTRIB);
        glEnableVertexAttribArray(VERT_NORM_ATTRIB);
        glEnableVertexAttribArray(VERT_TEX_ATTRIB);
        //Player texture
        glGenTextures(1, &rd.playerTex);
        glActiveTexture(GL_TEXTURE6); //Set texture i.
        glBindTexture(GL_TEXTURE_2D, rd.playerTex); //Bind text
        // Make textures pixelly near and mergefar
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //Generate texture
        GLchar tex[256 * 4];
        for (int p = 0; p < 256; p++){
            tex[p * 4] = 0x20;
            tex[p*4+1] = 0x80;
            tex[p*4+2] = 0xD0;
            tex[p*4+3] = 0xC0;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA,
                GL_UNSIGNED_BYTE, tex);

        //Generate player model (triangular bipyramid)
        glGenBuffers(1, &rd.playerModelVertBuf);
        glGenBuffers(1, &rd.playerModelFaceBuf);
        glBindBuffer(GL_ARRAY_BUFFER, rd.playerModelVertBuf);
        //Packed as vx, vy, vz, nx, ny, nz, u, v
        const GLfloat tribipyrvert[] = {
                0.0,2.0,0.0,sqrt6/3,1/3.0,sqrt2/3,0.5,0.0,
                0.0,1.0,-sqrt2/2,sqrt6/3,1/3.0,sqrt2/3,0.0,1.0,
                sqrt6/4,1.0,sqrt2/4,sqrt6/3,1/3.0,sqrt2/3,1.0,1.0,

                0.0,2.0,0.0,0.0,1/3.0,2*sqrt2/3,0.5,0.0,
                sqrt6/4,1.0,sqrt2/4,0.0,1/3.0,2*sqrt2/3,0.0,1.0,
                -sqrt6/4,1.0,sqrt2/4,0.0,1/3.0,2*sqrt2/3,1.0,1.0,

                0.0,2.0,0.0,-sqrt6/3,1/3.0,sqrt2/3,0.5,0.0,
                -sqrt6/4,1.0,sqrt2/4,-sqrt6/3,1/3.0,sqrt2/3,0.0,1.0,
                0.0,1.0,-sqrt2/2,-sqrt6/3,1/3.0,sqrt2/3,1.0,1.0,

                0.0,0.0,0.0,sqrt6/3,-1/3.0,sqrt2/3,0.5,0.0,
                sqrt6/4,1.0,sqrt2/4,sqrt6/3,-1/3.0,sqrt2/3,1.0,1.0,
                0.0,1.0,-sqrt2/2,sqrt6/3,-1/3.0,sqrt2/3,0.0,1.0,

                0.0,0.0,0.0,0.0,-1/3.0,2*sqrt2/3,0.5,0.0,
                -sqrt6/4,1.0,sqrt2/4,0.0,-1/3,2*sqrt2/3,1.0,1.0,
                sqrt6/4,1.0,sqrt2/4,0.0,-1/3,2*sqrt2/3,0.0,1.0,

                0.0,0.0,0.0,-sqrt6/3,-1/3,sqrt2/3,0.5,0.0,
                0.0,1.0,-sqrt2/2,-sqrt6/3,-1/3,sqrt2/3,1.0,1.0,
                -sqrt6/4,1.0,sqrt2/4,-sqrt6/3,-1/3,sqrt2/3,0.0,1.0
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(tribipyrvert), tribipyrvert,
                GL_STATIC_DRAW);
        const GLuint tribipyrface[] = {
                0, 1, 2,
                3, 4, 5,
                6, 7, 8,
                9, 10, 11,
                12, 13, 14,
                15, 16, 17
        };
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rd.playerModelFaceBuf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tribipyrface),
                tribipyrface, GL_STATIC_DRAW);
#ifdef TARGET_ATTR_TOOL_EM
        //Emscripten converts OpenGLES to WebGL which doesn't allow for direct
        // passing of vertex data
        glGenBuffers(1, &rd.triVertBuf);
        glBindBuffer(GL_ARRAY_BUFFER, rd.triVertBuf);
        glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), nullptr,
                GL_DYNAMIC_DRAW);
#endif
        //Set viewport
        glViewport(0, 0, KGAME_DEF_WIDTH, KGAME_DEF_HEIGHT);
        //Set Depth func for sanity
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        //Use the full depth range
        glDepthRangef(-1.0,1.0);
        //Set clear color
        glClearColor(0.5, 0.6, 1, 1);
        GLenum err;
        if ((err = glGetError())){
            std::fprintf(stderr, "Error %d", err);
            std::fflush(stderr);
        }
    }

    void renderFB(kWindow::GFrame* frame, kGame::GameData* data){
        //Clear buffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Render stuff
        kRender::render_common(frame, data);
        //Make visible to screen
        glFlush();
        frame->swapBuffers();
    }

    void renderFBPlayer (kWindow::GFrame* frame, kGame::Player* player){
        RenderData* rd = &frame->renderData;
        kGame::Player *p = player;
        //Set viewport uniforms
        GLfloat light[] = {0.2,1.0,0.1}; //Light in the shader is dot prod, so rev dir.
        GLfloat mvpv[16], mvv[9], il[3];
        kRender::glesCreateMatrices(0, 1.5, 0, p->yaw, p->pitch,
                0.5 /*FOV = 90*/, 16.0/9.0, 0.001, 4.0, light, mvpv, mvv, il);
        glUniformMatrix4fv(rd->mvpvertUni, 1, GL_FALSE, mvpv);
        glUniformMatrix3fv(rd->mvvecUni, 1, GL_FALSE, mvv);
        glUniform3fv(rd->iclightvecUni, 1, il);
        glUniform1i(rd->texUni, 6);
        glUniform1f(rd->alphaUni, 1.0);
        //Set buffer bindings
        glBindBuffer(GL_ARRAY_BUFFER, rd->playerModelVertBuf);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rd->playerModelFaceBuf);
        //Set vertex attribute offsets
        constexpr GLintptr stride = 8 * sizeof(GLfloat);
        glVertexAttribPointer(VERT_POS_ATTRIB, 3, GL_FLOAT, GL_FALSE, stride,
                (GLvoid *) (0 * sizeof(GLfloat)));
        glVertexAttribPointer(VERT_NORM_ATTRIB, 3, GL_FLOAT, GL_FALSE, stride,
                (GLvoid *) (3 * sizeof(GLfloat)));
        glVertexAttribPointer(VERT_TEX_ATTRIB, 2, GL_FLOAT, GL_FALSE, stride,
                (GLvoid *) (6 * sizeof(GLfloat)));
        //Draw!
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);
    }
    constexpr double sqrt3_2 = kMath::sqrtNR<double>(3.0l) / 2;
    constexpr double sqrt3_3 = kMath::sqrtNR<double>(3.0l) / 3;
    /** Represents the alpha values to render the polygons with. */
    unsigned char alpha[32][32];
    void renderFBLand (kWindow::GFrame* frame, kGame::GameData *data){
        kGame::Player *player = data->getPlayer();
        kGame::Player *p = data->getPlayer();
        RenderData *rd = &frame->renderData;
        //Set viewport uniforms
        GLfloat light[] = {0.2,1.0,0.1};
        GLfloat mvpv[16], mvv[9], il[3];
        kRender::glesCreateMatrices(p->x, p->y + 1.5, p->z, p->yaw, p->pitch,
                0.5 /*FOV = 90*/, 16.0/9.0, 0.001, 4.0, light, mvpv, mvv, il);
        glUniformMatrix4fv(rd->mvpvertUni, 1, GL_FALSE, mvpv);
        glUniformMatrix3fv(rd->mvvecUni, 1, GL_FALSE, mvv);
        glUniform3fv(rd->iclightvecUni, 1, il);
        //we do this to adjust z to triangular grid.
        double adjZ = player->z / sqrt3_2;
        //this grid will have triangles have sides perpendicular the x axis.
        //try to check for a 6.0 x 6.0 square of triangles. Draw a radius 6
        //triangles around person. (Dynamic alpha for tex would be sick)
        int xtc = std::round(player->x * 2);
        int ztc = std::round(adjZ);
        std::srand(237);
        //All ground normals are <0,1,0>
        glDisableVertexAttribArray(VERT_NORM_ATTRIB);
        glVertexAttrib3f(VERT_NORM_ATTRIB, 0, 1, 0);
        //Clear buffer bindings.
#ifdef TARGET_ATTR_TOOL_EM
        // Emscripten converts OpenGLES to WebGL which doesn't allow for direct
        //  passing of vertex data
        glBindBuffer(GL_ARRAY_BUFFER, rd->triVertBuf);
        //   Set the attribute pointers ahead of time
        constexpr GLsizei stride = 5 * sizeof(GLfloat);
        glVertexAttribPointer(VERT_POS_ATTRIB, 3, GL_FLOAT, GL_FALSE, stride,
                0);
        glVertexAttribPointer(VERT_TEX_ATTRIB, 2, GL_FLOAT, GL_FALSE, stride,
                (GLvoid *)(3 * sizeof(GLfloat)));
#else
        glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        //Iterate over nearby triangles to render
        for (int xto = -12; xto < 13; xto++){
            for (int zto = -7; zto < 8; zto++){ //7 is approx 6/(sqrt(3)/2).
                //Determine triangle pos
                //TODO replace random seeding with a local psuedo
                int xt = xtc + xto;
                int zt = ztc + zto;
                double hyp = std::hypot(std::hypot(xt/2.0-player->x,player->y),
                        (zt + (2 - ((xt + zt) & 1)) / 3.0 - adjZ) * sqrt3_2);
                //Do dynamic alphas on triangles
                if (hyp < 6){
                    if (hyp < 4){
                        if (hyp < 3){
                            alpha[xt & 31][zt & 31] = 1;
                        } else {
                            alpha[xt & 31][zt & 31] = (char)
                                    (1/51+(alpha[xt&31][zt&31]) * 50 / 51);
                        }
                    } else {
                        if (hyp > 5){
                            alpha[xt & 31][zt & 31] = (char)
                                    ((alpha[xt&31][zt&31]) * 120 / 121);
                        }
                    }
                } else if (hyp < 7){
                    alpha[xt & 31][zt & 31] = 0;
                    continue;
                } else {
                    continue;
                }
                //Set texture and alpha of triangle
                glUniform1i(rd->texUni, ((xt /* * (1 - (zt & 1) * 2)*/ + 3 * zt)
                         % 6 + 6) % 6);
                glUniform1f(rd->alphaUni, alpha[xt&31][zt&31]);
                //Plot vertices
                int dir = (xt + zt) & 1;
                std::srand(xt);
                std::srand(std::rand()+zt);
#if not(defined(TARGET_ATTR_TOOL_EM))
                GLfloat vertices[] = {
                        (GLfloat)(xt / 2.0), 0, (GLfloat)((zt + dir) *
                                sqrt3_2), //Vertex 1
                        (GLfloat)(xt / 2.0 + 1 / 2.0 - dir), 0,
                                (GLfloat)((zt + 1 - dir) * sqrt3_2), //Vertex 2
                        (GLfloat)(xt / 2.0 - 1 / 2.0 + dir), 0,
                                (GLfloat)((zt + 1 - dir) * sqrt3_2) //Vertex 3
                };
                GLfloat textures[] = { //Randomize textures
                        static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX),
                        static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX), //Vertex 1
                        static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX),
                        static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX), //Vertex 2
                        static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX),
                        static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX), //Vertex 3
                };
                //Draw the triangle
                glVertexAttribPointer(VERT_POS_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0,
                        vertices);
                glVertexAttribPointer(VERT_TEX_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0,
                        textures);
#else
                //Emscripten converts OpenGLES to WebGL which doesn't allow for
                // direct passing of vertex data
                GLfloat vertices[] = {
                        (GLfloat)(xt / 2.0), 0, (GLfloat)((zt + dir) *
                                sqrt3_2), static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX),
                                static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX),//Vertex 1
                        (GLfloat)(xt / 2.0 + 1 / 2.0 - dir), 0,
                                (GLfloat)((zt + 1 - dir) * sqrt3_2),
                                static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX),
                                static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX), //Vertex 2
                        (GLfloat)(xt / 2.0 - 1 / 2.0 + dir), 0,
                                (GLfloat)((zt + 1 - dir) * sqrt3_2),
                                static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX),
                                static_cast<GLfloat>(std::rand()) /
                                static_cast<GLfloat>(RAND_MAX),//Vertex 3
                };
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
#endif
                glDrawArrays(GL_TRIANGLES, 0, 3);
            }
        }
        //Disables generic vertex attributes for vertex normals
        glEnableVertexAttribArray(VERT_NORM_ATTRIB);
    }

}  // namespace kRender
#endif


