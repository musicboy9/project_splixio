//
//  Zombie.hpp
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 26..
//  Copyright © 2018년 고영민. All rights reserved.
//

#ifndef Zombie_h
#define Zombie_h

#include <stdio.h>
#include "LandFlag.h"

using namespace std;

class Zombie {
public:
    Zombie();
    Zombie(int x, int y, float color_r, float color_g, float color_b);
    ~Zombie();
    Zombie(const Zombie& temp_zom);
    Zombie& operator=(const Zombie& temp_zom);
    
    int getX() const;
    int getY() const;
    float getR() const;
    float getG() const;
    float getB() const;
    void update(landFlag currentMap[66][66]) const;
    
private:
    int pos_min = 1;
    int pos_max = 64;
    int *pos;
    float *color;
};

#endif /* Zombie_h */
