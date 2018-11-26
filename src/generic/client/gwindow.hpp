/**
 * @file window.hpp
 * @brief Defines generic data structures and functions relating to windowing
 *
 * This file defines generic data structures and functions relating to
 * windowing.
 *
 *
 * @date November 16, 2018 5:50
 * @author Koen Komeya <komeyakoen@gmail.com>
 */

#ifndef GENERIC_CLIENT_GWINDOW_HPP_
#define GENERIC_CLIENT_GWINDOW_HPP_

#ifdef TARGET_ATTR_WIND_GLFW
#include <GLFW/glfw3.h>
#include "generic/client/window/base/glfw_keys.hpp"
#else
#error "Window system not defined."
#endif

/**
 * @namespace kGenWindow
 * @brief Contains data structures and functions pertaining to a display.
 * @author Koen Komeya
 */
namespace kGenWindow{
    //Keys (defined in *_keys.hpp)
    /*
    typedef ? key_t;
    constexpr key_t KEY_SPACE;
    constexpr key_t KEY_0;
    constexpr key_t KEY_1;
    constexpr key_t KEY_2;
    constexpr key_t KEY_3;
    constexpr key_t KEY_4;
    constexpr key_t KEY_5;
    constexpr key_t KEY_6;
    constexpr key_t KEY_7;
    constexpr key_t KEY_8;
    constexpr key_t KEY_9;
    constexpr key_t KEY_A;
    constexpr key_t KEY_B;
    constexpr key_t KEY_C;
    constexpr key_t KEY_D;
    constexpr key_t KEY_E;
    constexpr key_t KEY_F;
    constexpr key_t KEY_G;
    constexpr key_t KEY_H;
    constexpr key_t KEY_I;
    constexpr key_t KEY_J;
    constexpr key_t KEY_K;
    constexpr key_t KEY_L;
    constexpr key_t KEY_M;
    constexpr key_t KEY_N;
    constexpr key_t KEY_O;
    constexpr key_t KEY_P;
    constexpr key_t KEY_Q;
    constexpr key_t KEY_R;
    constexpr key_t KEY_S;
    constexpr key_t KEY_T;
    constexpr key_t KEY_U;
    constexpr key_t KEY_V;
    constexpr key_t KEY_W;
    constexpr key_t KEY_X;
    constexpr key_t KEY_Y;
    constexpr key_t KEY_Z;
    constexpr key_t KEY_ESCAPE;
    constexpr key_t KEY_ENTER;
    constexpr key_t KEY_TAB;
    constexpr key_t KEY_BACKSPACE;
    constexpr key_t KEY_INSERT;
    constexpr key_t KEY_DELETE;
    constexpr key_t KEY_RIGHT;
    constexpr key_t KEY_LEFT;
    constexpr key_t KEY_DOWN;
    constexpr key_t KEY_UP;
    constexpr key_t KEY_PAGE_UP;
    constexpr key_t KEY_PAGE_DOWN;
    constexpr key_t KEY_HOME;
    constexpr key_t KEY_END;
    constexpr key_t KEY_PRkey_t_SCREEN;
    constexpr key_t KEY_PAUSE;
    constexpr key_t KEY_F1;
    constexpr key_t KEY_F2;
    constexpr key_t KEY_F3;
    constexpr key_t KEY_F4;
    constexpr key_t KEY_F5;
    constexpr key_t KEY_F6;
    constexpr key_t KEY_F7;
    constexpr key_t KEY_F8;
    constexpr key_t KEY_F9;
    constexpr key_t KEY_F10;
    constexpr key_t KEY_F11;
    constexpr key_t KEY_F12;
    constexpr key_t KEY_KP_0;
    constexpr key_t KEY_KP_1;
    constexpr key_t KEY_KP_2;
    constexpr key_t KEY_KP_3;
    constexpr key_t KEY_KP_4;
    constexpr key_t KEY_KP_5;
    constexpr key_t KEY_KP_6;
    constexpr key_t KEY_KP_7;
    constexpr key_t KEY_KP_8;
    constexpr key_t KEY_KP_9;
    constexpr key_t KEY_KP_DECIMAL;
    constexpr key_t KEY_KP_DIVIDE;
    constexpr key_t KEY_KP_MULTIPLY;
    constexpr key_t KEY_KP_SUBTRACT;
    constexpr key_t KEY_KP_ADD;
    constexpr key_t KEY_KP_ENTER;
    constexpr key_t KEY_KP_EQUAL;
    constexpr key_t KEY_LEFT_SHIFT;
    constexpr key_t KEY_LEFT_CONTROL;
    constexpr key_t KEY_LEFT_ALT;
    constexpr key_t KEY_LEFT_SUPER;
    constexpr key_t KEY_RIGHT_SHIFT;
    constexpr key_t KEY_RIGHT_CONTROL;
    constexpr key_t KEY_RIGHT_ALT;
    constexpr key_t KEY_RIGHT_SUPER;
    constexpr key_t KEY_MENU;
    */

    /**
     * @class Frame
     * @brief The display for our demo/game/whatevs.
     * Represents the display through which we will be rendering to.
     * Rudimentary implementation; only implemented functions I've needed.
     * @since November 17, 2018 15:11
     * @author Koen Komeya
     */
    class Frame{
    public:

        Frame() = delete;
        /**
         * @brief Initializes a new instance.
         * Initializes a new Frame, setting up the rendering context.
         * @param width the width in screen coordinates
         * @param height the height in screen coordinates
         * @param title the title of the window
        **/
        Frame(int width, int height, const char *title);
        virtual ~Frame();
        /**
         * Returns whether or not a key is pressed
         * @param key
         * @return true if the key is pressed, false otherwise.
         */
        bool isKeyPressed(key_t key);

        /**
         * @fn swapBuffers
         * @brief Swaps the buffers used by the render context
         * @since November 19, 2018 00:48
        **/
        void swapBuffers();

        /**
         * @fn pollEvents
         * @brief polls for windowing events if necessary.
         * @since November 19, 2018 02:31
        **/
        void pollEvents();

        /**
         * @fn requestLock
         * @brief requests pointer lock
         * @since November 19, 2018 04:06
        **/
        void requestLock();

        /**
         * @fn isLocked
         * @brief determines if pointer lock is active
         * @return whether or not pointer lock is active
         * @since November 19, 2018 04:07
        **/
        bool isLocked();

        /**
         * @fn getCursorPos
         * @brief gets the location of the cursor
         *
         * @param   x  pointer to hold x position
         * @param   y  pointer to hold y position
         *
         * @since November 19, 2018 04:34
        **/
        void getCursorPos (double &x, double &y);

        /**
         * @fn getCursorOffset
         * @brief gets the amount the cursor moved since the last call
         * Gets the amount the cursor moved since the last call assuming that
         * the cursor is locked.
         *
         * @param   x  pointer to hold x offset
         * @param   y  pointer to hold y offsest
         *
         * @since November 24, 2018 21:17
        **/
        void getCursorOffset (double &x, double &y);

#ifdef TARGET_ATTR_RENDFB_GLES_2_0
        /**
         * @fn isUsingFallback
         * @brief Whether or not the GLES 2.0 fallback should be used.
         * @return whether to use the fallback or not
         * @since November 18, 2018 20:52
        **/
        bool isUsingFallback();
#endif
    protected:
        int width, height;
#ifdef TARGET_ATTR_WIND_GLFW
        GLFWwindow *win;
#else
#error
#endif
#ifdef TARGET_ATTR_RENDFB_GLES_2_0
        bool usingFallback = false;
#endif
    private:
#ifdef TARGET_ATTR_WIND_GLFW
        bool wasLocked = false;
        /** Last x-offset of cursor */
        double c_lastX;
        /** Last y-offset of cursor */
        double c_lastY;
#endif
    };

    /**
     * @brief Initializes the windowing module.
     * Initializes this module.
     */
    void initModule();
}

#endif /* GENERIC_CLIENT_GWINDOW_HPP_ */
