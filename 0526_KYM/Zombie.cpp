//
//  Zombie.cpp
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 26..
//  Copyright © 2018년 고영민. All rights reserved.
//

#include "Zombie.h"
#include <stdlib.h>

Zombie::Zombie(){
    pos = new int[2];
    pos[0] = 1;
    pos[1] = 1;
    
    color = new float[3];
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
}

Zombie::Zombie(int x, int y, float color_r, float color_g, float color_b){
    pos = new int[2];
    pos[0] = x;
    pos[1] = y;
    
    color = new float[3];
    color[0] = color_r;
    color[1] = color_g;
    color[2] = color_b;
}

Zombie::~Zombie(){
    if (pos != nullptr){
        delete [] pos;
    }
    if (color != nullptr){
        delete [] color;
    }
}

int Zombie::getX() const {
    return pos[0];
}

int Zombie::getY() const {
    return pos[1];
}

float Zombie::getR() const {
    return color[0];
}

float Zombie::getG() const {
    return color[1];
}

float Zombie::getB() const {
    return color[2];
}

void Zombie::update(landFlag currentMap[66][66]) const {
    int direction[4] = {1,1,1,1}; // up, down, left, right
    if ((currentMap[pos[0]+1][pos[1]] == myLand) || (currentMap[pos[0]+1][pos[1]] == boundary)){
        direction[3] = 0; //can't go right
    }
    if ((currentMap[pos[0]-1][pos[1]] == myLand) || (currentMap[pos[0]-1][pos[1]] == boundary)){
        direction[2] = 0; //can't go left
    }
    if ((currentMap[pos[0]][pos[1]+1] == myLand) || (currentMap[pos[0]][pos[1]+1] == boundary)){
        direction[0] = 0; //can't go up
    }
    if ((currentMap[pos[0]][pos[1]-1] == myLand) || (currentMap[pos[0]][pos[1]-1] == boundary)){
        direction[1] = 0; //can't go down
    }
    
    int random_direction = -1;
    while (random_direction<0){
        int temp = rand()%4;
        if (direction[temp] != 0){
            random_direction = temp;
        }
    }
    
    switch (random_direction){
        case 0:
            pos[1] += 1;
            break;
        case 1:
            pos[1] -= 1;
            break;
        case 2:
            pos[0] -= 1;
            break;
        case 3:
            pos[0] += 1;
            break;
        default:
            break;
    }
}










