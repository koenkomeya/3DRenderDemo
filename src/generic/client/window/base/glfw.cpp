/**
 * @file glfw.cpp
 * @brief Windowing implementation using GLFW
 *
 * This implements windowing using GLFW 3.
 *
 * @date November 16, 2018 5:13
 * @author Koen Komeya
 */

#include "k.hpp"
#ifdef TARGET_ATTR_WIND_GLFW
#include <cstddef>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include "generic/client//gwindow.hpp"
#include "generic/client/window/base/base_req.hpp"


namespace kGenWinOSBase{
    void initSubmodule(){
        glfwInit();
    }
}

namespace kGenWindow{

    Frame::Frame(key_t width, key_t height, const char *title){
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef TARGET_ATTR_REND_GLES_3_0
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
#error Render hint code not written
#endif
        GLFWwindow *win = glfwCreateWindow(width, height, title, nullptr,
                nullptr);
        if (win == nullptr){
#ifdef TARGET_ATTR_RENDFB_GLES_2_0
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            win = glfwCreateWindow(width, height, title, nullptr, nullptr);
            if (win == nullptr){
                throw std::runtime_error(
                        (const char*)"Window or GLES2.0 context couldn't be created.");
            }
            this->usingFallback = true;
#else
            throw std::runtime_error(
                    (const char*)"Window or GLES3.0 context couldn't be created.");
#endif
        }
        this->win = win;
        glfwSetWindowUserPointer(win, this);
        glfwMakeContextCurrent(win);
        glfwSwapInterval(1);
        glfwGetWindowSize(this->win, &this->width, &this->height);
    }

    Frame::~Frame(){
        glfwDestroyWindow(this->win);
    }


    bool Frame::isKeyPressed(key_t key){
        return glfwGetKey(this->win, key) == GLFW_PRESS;
    }


    void Frame::swapBuffers(){
        glfwSwapBuffers(this->win);
    }

    void Frame::pollEvents(){
        glfwPollEvents();
    }

    void Frame::requestLock(){
        glfwSetInputMode(this->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    bool Frame::isLocked(){
        bool lock;
        lock = glfwGetInputMode(this->win, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
        if (!lock) wasLocked = false;
        return lock;
    }

    void Frame::getCursorPos (double &x, double &y){
        glfwGetCursorPos(this->win, &x, &y);
    }

    void Frame::getCursorOffset (double &x, double &y){
        if (!wasLocked){
            if(glfwGetInputMode(this->win, GLFW_CURSOR)==GLFW_CURSOR_DISABLED){
                wasLocked = true;
                glfwGetCursorPos(this->win, &c_lastX, &c_lastY);
                x = 0;
                y = 0;
            }
        } else if (glfwGetInputMode(this->win, GLFW_CURSOR) ==
                GLFW_CURSOR_DISABLED){
            double cx, cy;
            glfwGetCursorPos(this->win, &cx, &cy);
            x = cx - c_lastX;
            y = cy - c_lastY;
            c_lastX = cx;
            c_lastY = cy;
        } else {
            wasLocked = false;
        }
    }

#ifdef TARGET_ATTR_RENDFB_GLES_2_0
    bool Frame::isUsingFallback(){
        return this->usingFallback;
    }
#endif
}

#endif
