//
//  Player.h
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 26..
//  Copyright © 2018년 고영민. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include "LandFlag.h"

enum playerDirection {
    STOP = -1,
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

class Player {
public:
    Player();
    Player(int x, int y, float color_r, float color_g, float color_b);
    ~Player();
    
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    float getR() const;
    float getG() const;
    float getB() const;
    void setDirection(playerDirection newDirection);
    int getLife() const;
    void setLife(int newLife);
    void update(landFlag currentMap[66][66]) const;
    
private:
    int *pos;
    playerDirection *direction;
    float *color;
    int *life;
};

#endif /* Player_h */
