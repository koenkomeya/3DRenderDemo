/**
 * @file game.cpp
 * @brief Contains implementations for game.hpp
 *
 * @date November 19, 2018 03:02
 * @author Koen Komeya 
 */
#include "client/game.hpp"
#include <cmath>

namespace kGame {
    Player::Player(kGame::GameData *data) : gameData(data){};
    void Player::tick(){
        double speed = 1.5;
        kWindow::GFrame *frame = this->gameData->frame;
        bool move = false;
        if (frame->isKeyPressed(kGenWindow::KEY_W)){
            this->x -= speed / 60 * sin((long double)this->yaw);
            this->z += speed / 60 * cos((long double)this->yaw);
            move = true;
        }
        if (frame->isKeyPressed(kGenWindow::KEY_A)){
            this->x += speed / 60 * cos((long double)this->yaw);
            this->z += speed / 60 * sin((long double)this->yaw);
            move = true;
        }
        if (frame->isKeyPressed(kGenWindow::KEY_S)){
            this->x += speed / 60 * sin((long double)this->yaw);
            this->z -= speed / 60 * cos((long double)this->yaw);
            move = true;
        }
        if (frame->isKeyPressed(kGenWindow::KEY_D)){
            this->x -= speed / 60 * cos((long double)this->yaw);
            this->z -= speed / 60 * sin((long double)this->yaw);
            move = true;
        }
        if (move){
            this->animStep++;
        } else {
            this->animStep = 0;
        }
        if (!frame->isLocked()){
            frame->requestLock();
        } else {
            //Calculate offset and change yaw/pitch
        }
    }
}



