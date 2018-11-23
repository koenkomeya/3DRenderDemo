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
        glGetShaderiv(vs, GL_SHADER_TYPE, &glSuccess);
        if (glSuccess == GL_FALSE){
            printGLESShaderInfoLog(vs);
            throw std::runtime_error("Failed to compile GLES3 vertex shader");
        }
        const GLchar * fShaderHP = lightingFS; //array not const workard
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        //We bind the shader code to the object
        glShaderSource(fs, 1, &fShaderHP, nullptr);
        //compile the shader
        glCompileShader(fs);
        glGetShaderiv(fs, GL_SHADER_TYPE, &glSuccess);
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
        const std::uint32_t COLORS[] = {
                0xf00000e8,
                0xe07000e8,
                0xf0f000e8,
                0x00f000e8,
                0x0000d0e8,
                0xd000d0e8,
        };
        //Set random
        std::srand(237);
        //Dynamically generate textures
        for (int i = 0; i < 6; i++){
            glActiveTexture(GL_TEXTURE0 + i); //Set texture i.
            glBindTexture(GL_TEXTURE_BINDING_2D, rd.rainbowTex[i]); //Bind text
            //Generate texture
            std::uint32_t tex[256];
            for (int p = 0; p < 256; p++)
                tex[p] = COLORS[i] +
                    (((std::rand() << 16) ^ std::rand()) & 0x0f0f0f00);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA,
                    GL_UNSIGNED_BYTE, tex);
        }
        //Enable vertex attribute arrays
        glEnableVertexAttribArray(VERT_POS_ATTRIB);
        glEnableVertexAttribArray(VERT_NORM_ATTRIB);
        glEnableVertexAttribArray(VERT_TEX_ATTRIB);
        //Player texture
        glGenTextures(1, &rd.playerTex);
        glActiveTexture(GL_TEXTURE6); //Set texture i.
        glBindTexture(GL_TEXTURE_BINDING_2D, rd.playerTex); //Bind text
        //Generate texture
        std::uint32_t tex[256];
        for (int p = 0; p < 256; p++) tex[p] = 0x2080d0c0;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA,
                GL_UNSIGNED_BYTE, tex);

        //Generate player model (triangular bipyramid)
        glGenBuffers(1, &rd.playerModelVertBuf);
        glGenBuffers(1, &rd.playerModelFaceBuf);
        glBindBuffer(GL_ARRAY_BUFFER, rd.playerModelVertBuf);
        //Packed as vx, vy, vz, nx, ny, nz, u, v
        const GLfloat tribipyrvert[] = {
                0.0,2.0,0.0,sqrt6/3,1/3,sqrt2/3,0.5,0.0,
                0.0,1.0,-sqrt2/2,sqrt6/3,1/3,sqrt2/3,0.0,1.0,
                sqrt6/4,1.0,sqrt2/4,sqrt6/3,1/3,sqrt2/3,1.0,1.0,

                0.0,2.0,0.0,0.0,1/3,2*sqrt2/3,0.5,0.0,
                sqrt6/4,1.0,sqrt2/4,0.0,1/3,2*sqrt2/3,0.0,1.0,
                -sqrt6/4,1.0,sqrt2/4,0.0,1/3,2*sqrt2/3,1.0,1.0,

                0.0,2.0,0.0,-sqrt6/3,1/3,sqrt2/3,0.5,0.0,
                -sqrt6/4,1.0,0.0,-sqrt6/3,1/3,sqrt2/3,0.0,1.0,
                0.0,1.0,-sqrt2/2,-sqrt6/3,1/3,sqrt2/3,1.0,1.0,

                0.0,0.0,0.0,sqrt6/3,-1/3,sqrt2/3,0.5,0.0,
                sqrt6/4,1.0,sqrt2/4,sqrt6/3,-1/3,sqrt2/3,1.0,1.0,
                0.0,1.0,-sqrt2/2,sqrt6/3,-1/3,sqrt2/3,0.0,1.0,

                0.0,0.0,0.0,0.0,-1/3,2*sqrt2/3,0.5,0.0,
                -sqrt6/4,1.0,sqrt2/4,0.0,-1/3,2*sqrt2/3,1.0,1.0,
                sqrt6/4,1.0,sqrt2/4,0.0,-1/3,2*sqrt2/3,0.0,1.0,

                0.0,0.0,0.0,-sqrt6/3,-1/3,sqrt2/3,0.5,0.0,
                0.0,1.0,-sqrt2/2,-sqrt6/3,-1/3,sqrt2/3,1.0,1.0,
                -sqrt6/4,1.0,0.0,-sqrt6/3,-1/3,sqrt2/3,0.0,1.0
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
        glBindBuffer(GL_ARRAY_BUFFER, rd.playerModelFaceBuf);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tribipyrface),
                tribipyrface, GL_STATIC_DRAW);
        //Set clear color
        glClearColor(0.5, 0.6, 1, 1);
    }

    void renderFB(kWindow::GFrame* frame, kGame::GameData* data){
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
        GLfloat light[] = {0.2,-1.0,0.1};
        GLfloat mvpv[16], mvv[9], il[3];
        kRender::glesCreateMatrices(0, 0, 0, 0, p->pitch,
                0.5 /*FOV = 90*/, 16.0/9.0, 1.0, -4.0, light, mvpv, mvv, il);
        glUniformMatrix4fv(rd->mvpvertUni, 16, GL_FALSE, mvpv);
        glUniformMatrix3fv(rd->mvvecUni, 9, GL_FALSE, mvv);
        glUniform3fv(rd->iclightvecUni, 3, il);
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
    constexpr long double sqrt3_2 = kMath::sqrtNR<long double>(3.0l) / 2;
    constexpr long double sqrt3_3 = kMath::sqrtNR<long double>(3.0l) / 3;
    /** Represents the alpha values to render the polygons with. */
    unsigned char alpha[32][32];
    void renderFBLand (kWindow::GFrame* frame, kGame::GameData *data){
        kGame::Player *player = data->getPlayer();
        kGame::Player *p = data->getPlayer();
        RenderData *rd = &frame->renderData;
        //Set viewport uniforms
        GLfloat light[] = {0.2,-1.0,0.1};
        GLfloat mvpv[16], mvv[9], il[3];
        kRender::glesCreateMatrices(p->x, p->y + 2.0, p->z, p->yaw, p->pitch,
                0.5 /*FOV = 90*/, 16.0/9.0, 1.0, -4.0, light, mvpv, mvv, il);
        glUniformMatrix4fv(rd->mvpvertUni, 16, GL_FALSE, mvpv);
        glUniformMatrix3fv(rd->mvvecUni, 9, GL_FALSE, mvv);
        glUniform3fv(rd->iclightvecUni, 3, il);
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
        //Clear buffer bindings
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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
                glUniform1i(rd->texUni, (xt * (1 - (zt & 1) * 2) + 3 * zt) % 6);
                glUniform1f(rd->alphaUni, alpha[xt&31][zt&31]);
                //Plot vertices
                glVertexAttrib3f(VERT_POS_ATTRIB, xt / 2, 0, zt + (zt & 1));
                glVertexAttrib2f(VERT_TEX_ATTRIB,
                        static_cast<GLfloat>(std::rand()) /
                        static_cast<GLfloat>(RAND_MAX),
                        static_cast<GLfloat>(std::rand()) /
                        static_cast<GLfloat>(RAND_MAX));
                //Draw the triangle
            }
        }
        //Disables generic vertex attributes for vertex normals
        glEnableVertexAttribArray(VERT_NORM_ATTRIB);
    }

}  // namespace kRender
#endif


