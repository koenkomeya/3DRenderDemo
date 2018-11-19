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

#ifdef TARGET_ATTR_RENDFB_GLES_2_0
    bool Frame::isUsingFallback(){
        return this->usingFallback;
    }
#endif
}

#endif
