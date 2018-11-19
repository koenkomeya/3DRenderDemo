/**
 * @file glfw_keys.hpp
 * @brief Fix me son
 * This does stuff
 *
 * @date November 18, 2018 15:15
 * @author Koen Komeya 
 */

#ifndef GENERIC_CLIENT_WINDOW_BASE_GLFW_KEYS_HPP_
#define GENERIC_CLIENT_WINDOW_BASE_GLFW_KEYS_HPP_
#include "k.hpp"
#ifdef TARGET_ATTR_WIND_GLFW
#include <GLFW/glfw3.h>
namespace kGenWindow{
    typedef int key_t;
    //See miscscripts/fastglfwkeyconstexprgen.py for regen
    constexpr key_t KEY_UNKNOWN = GLFW_KEY_UNKNOWN;
    constexpr key_t KEY_SPACE = GLFW_KEY_SPACE;
    constexpr key_t KEY_0 = GLFW_KEY_0;
    constexpr key_t KEY_1 = GLFW_KEY_1;
    constexpr key_t KEY_2 = GLFW_KEY_2;
    constexpr key_t KEY_3 = GLFW_KEY_3;
    constexpr key_t KEY_4 = GLFW_KEY_4;
    constexpr key_t KEY_5 = GLFW_KEY_5;
    constexpr key_t KEY_6 = GLFW_KEY_6;
    constexpr key_t KEY_7 = GLFW_KEY_7;
    constexpr key_t KEY_8 = GLFW_KEY_8;
    constexpr key_t KEY_9 = GLFW_KEY_9;
    constexpr key_t KEY_A = GLFW_KEY_A;
    constexpr key_t KEY_B = GLFW_KEY_B;
    constexpr key_t KEY_C = GLFW_KEY_C;
    constexpr key_t KEY_D = GLFW_KEY_D;
    constexpr key_t KEY_E = GLFW_KEY_E;
    constexpr key_t KEY_F = GLFW_KEY_F;
    constexpr key_t KEY_G = GLFW_KEY_G;
    constexpr key_t KEY_H = GLFW_KEY_H;
    constexpr key_t KEY_I = GLFW_KEY_I;
    constexpr key_t KEY_J = GLFW_KEY_J;
    constexpr key_t KEY_K = GLFW_KEY_K;
    constexpr key_t KEY_L = GLFW_KEY_L;
    constexpr key_t KEY_M = GLFW_KEY_M;
    constexpr key_t KEY_N = GLFW_KEY_N;
    constexpr key_t KEY_O = GLFW_KEY_O;
    constexpr key_t KEY_P = GLFW_KEY_P;
    constexpr key_t KEY_Q = GLFW_KEY_Q;
    constexpr key_t KEY_R = GLFW_KEY_R;
    constexpr key_t KEY_S = GLFW_KEY_S;
    constexpr key_t KEY_T = GLFW_KEY_T;
    constexpr key_t KEY_U = GLFW_KEY_U;
    constexpr key_t KEY_V = GLFW_KEY_V;
    constexpr key_t KEY_W = GLFW_KEY_W;
    constexpr key_t KEY_X = GLFW_KEY_X;
    constexpr key_t KEY_Y = GLFW_KEY_Y;
    constexpr key_t KEY_Z = GLFW_KEY_Z;
    constexpr key_t KEY_ESCAPE = GLFW_KEY_ESCAPE;
    constexpr key_t KEY_ENTER = GLFW_KEY_ENTER;
    constexpr key_t KEY_TAB = GLFW_KEY_TAB;
    constexpr key_t KEY_BACKSPACE = GLFW_KEY_BACKSPACE;
    constexpr key_t KEY_INSERT = GLFW_KEY_INSERT;
    constexpr key_t KEY_DELETE = GLFW_KEY_DELETE;
    constexpr key_t KEY_RIGHT = GLFW_KEY_RIGHT;
    constexpr key_t KEY_LEFT = GLFW_KEY_LEFT;
    constexpr key_t KEY_DOWN = GLFW_KEY_DOWN;
    constexpr key_t KEY_UP = GLFW_KEY_UP;
    constexpr key_t KEY_PAGE_UP = GLFW_KEY_PAGE_UP;
    constexpr key_t KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN;
    constexpr key_t KEY_HOME = GLFW_KEY_HOME;
    constexpr key_t KEY_END = GLFW_KEY_END;
    constexpr key_t KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK;
    constexpr key_t KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK;
    constexpr key_t KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK;
    constexpr key_t KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN;
    constexpr key_t KEY_PAUSE = GLFW_KEY_PAUSE;
    constexpr key_t KEY_F1 = GLFW_KEY_F1;
    constexpr key_t KEY_F2 = GLFW_KEY_F2;
    constexpr key_t KEY_F3 = GLFW_KEY_F3;
    constexpr key_t KEY_F4 = GLFW_KEY_F4;
    constexpr key_t KEY_F5 = GLFW_KEY_F5;
    constexpr key_t KEY_F6 = GLFW_KEY_F6;
    constexpr key_t KEY_F7 = GLFW_KEY_F7;
    constexpr key_t KEY_F8 = GLFW_KEY_F8;
    constexpr key_t KEY_F9 = GLFW_KEY_F9;
    constexpr key_t KEY_F10 = GLFW_KEY_F10;
    constexpr key_t KEY_F11 = GLFW_KEY_F11;
    constexpr key_t KEY_F12 = GLFW_KEY_F12;
    constexpr key_t KEY_F13 = GLFW_KEY_F13;
    constexpr key_t KEY_F14 = GLFW_KEY_F14;
    constexpr key_t KEY_F15 = GLFW_KEY_F15;
    constexpr key_t KEY_F16 = GLFW_KEY_F16;
    constexpr key_t KEY_F17 = GLFW_KEY_F17;
    constexpr key_t KEY_F18 = GLFW_KEY_F18;
    constexpr key_t KEY_F19 = GLFW_KEY_F19;
    constexpr key_t KEY_F20 = GLFW_KEY_F20;
    constexpr key_t KEY_F21 = GLFW_KEY_F21;
    constexpr key_t KEY_F22 = GLFW_KEY_F22;
    constexpr key_t KEY_F23 = GLFW_KEY_F23;
    constexpr key_t KEY_F24 = GLFW_KEY_F24;
    constexpr key_t KEY_F25 = GLFW_KEY_F25;
    constexpr key_t KEY_KP_0 = GLFW_KEY_KP_0;
    constexpr key_t KEY_KP_1 = GLFW_KEY_KP_1;
    constexpr key_t KEY_KP_2 = GLFW_KEY_KP_2;
    constexpr key_t KEY_KP_3 = GLFW_KEY_KP_3;
    constexpr key_t KEY_KP_4 = GLFW_KEY_KP_4;
    constexpr key_t KEY_KP_5 = GLFW_KEY_KP_5;
    constexpr key_t KEY_KP_6 = GLFW_KEY_KP_6;
    constexpr key_t KEY_KP_7 = GLFW_KEY_KP_7;
    constexpr key_t KEY_KP_8 = GLFW_KEY_KP_8;
    constexpr key_t KEY_KP_9 = GLFW_KEY_KP_9;
    constexpr key_t KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL;
    constexpr key_t KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE;
    constexpr key_t KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY;
    constexpr key_t KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT;
    constexpr key_t KEY_KP_ADD = GLFW_KEY_KP_ADD;
    constexpr key_t KEY_KP_ENTER = GLFW_KEY_KP_ENTER;
    constexpr key_t KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL;
    constexpr key_t KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT;
    constexpr key_t KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL;
    constexpr key_t KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT;
    constexpr key_t KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER;
    constexpr key_t KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT;
    constexpr key_t KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL;
    constexpr key_t KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT;
    constexpr key_t KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER;
    constexpr key_t KEY_MENU = GLFW_KEY_MENU;
    constexpr key_t KEY_LAST = GLFW_KEY_LAST;
}
#else
#error
#endif




#endif /* GENERIC_CLIENT_WINDOW_BASE_GLFW_KEYS_HPP_ */
