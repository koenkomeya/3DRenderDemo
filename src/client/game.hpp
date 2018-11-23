/**
 * @file game.hpp
 * @brief Contains game structures
 *
 * @date November 19, 2018 02:54
 * @author Koen Komeya 
 */

#ifndef GAME_HPP_
#define GAME_HPP_
#include "client/window.hpp"

/**
 * @namespace kGame
 * @brief Contains data structures and functions pertaining to the implemented game.
 *
 * @author Koen Komeya
 * @since November 19, 2018 02:57
 */
namespace kGame {

    class GameData;
    /**
     * @class Player
     * Represents the player
     *
     * @since November 19, 2018 03:00
    **/
    class Player {
    public:
        Player() = delete;
        Player(kGame::GameData *);
        /** Coords */
        double x = 0, y = 0, z = 0;
        double yaw = 0, pitch = 0;
        /** Step of animation */
        int animStep = 0;
        /** associated GameData */
        kGame::GameData *gameData;
        /**
         * @fn tick
         * @brief Ticks this player
         * @since November 19, 2018 03:39
        **/
        void tick();
    private:

    };
    /**
     * @class GameData
     *
     * Contains data for a game
     *
     * @since November 19, 2018 02:57
    **/
    class GameData{
    public:
        inline GameData() : player(Player(this)){}
        /**
         * Frame that the game is rendered to/contained in.
         */
        kWindow::GFrame* frame = nullptr;
        inline Player *getPlayer(){return &(this->player);}
    protected:
        /**
         * The controllable player
         */
        Player player;
    };




}  // namespace kGame

#endif /* GAME_HPP_ */
