//
//  Player.cpp
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 26..
//  Copyright © 2018년 고영민. All rights reserved.
//

#include <stdio.h>
#include "Player.h"

Player::Player(){
    pos = new int[2];
    pos[0] = 32;
    pos[1] = 32;
    
    color = new float[3];
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    
    direction = new playerDirection;
    *direction = STOP;
    
    life = new int;
    *life = 3;
}

Player::Player(int x, int y, float color_r, float color_g, float color_b) {
    pos = new int[2];
    pos[0] = x;
    pos[1] = y;
    
    color = new float[3];
    color[0] = color_r;
    color[1] = color_g;
    color[2] = color_b;
    
    direction = new playerDirection;
    *direction = STOP;
    
    life = new int;
    *life = 3;
}

Player::~Player(){
    if (pos != nullptr){
        delete [] pos;
    }
    if (direction != nullptr){
        delete direction;
    }
    if (color != nullptr){
        delete [] color;
    }
    if (life != nullptr){
        delete life;
    }
}

void Player::setX(int x) {
    pos[0] = x;
}
void Player::setY(int y) {
    pos[1] = y;
}
int Player:: getX() const {
    return pos[0];
}
int Player::getY() const {
    return pos[1];
}
float Player::getR() const {
    return color[0];
}
float Player::getG() const {
    return color[1];
}
float Player::getB() const {
    return color[2];
}

void Player::setDirection(playerDirection newDirection){
    if ((*direction==UP && newDirection==DOWN)||(*direction==DOWN && newDirection==UP)||(*direction==LEFT && newDirection==RIGHT)||(*direction==RIGHT && newDirection==LEFT)) {
        return;
    }
    *direction = newDirection;
}

int Player::getLife() const {
    return *life;
}

void Player::setLife(int newLife){
    *life = newLife;
}

void Player::update(landFlag currentMap[66][66]) const{
    switch(*direction){
        case STOP:
            return;
        case UP:
            if (currentMap[pos[0]][pos[1]+1]==boundary){
                return;
            }
            pos[1] += 1;
            break;
        case DOWN:
            if (currentMap[pos[0]][pos[1]-1]==boundary){
                return;
            }
            pos[1] -= 1;
            break;
        case LEFT:
            if (currentMap[pos[0]-1][pos[1]]==boundary){
                return;
            }
            pos[0] -= 1;
            break;
        case RIGHT:
            if (currentMap[pos[0]+1][pos[1]]==boundary){
                return;
            }
            pos[0] += 1;
            break;
        default:
            break;
    }
}






