//
//  Map.h
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 26..
//  Copyright © 2018년 고영민. All rights reserved.
//

#include "Player.h"
#include "Zombie.h"

#ifndef Map_h
#define Map_h

class Map{
public:
    Map(float player_r, float player_g, float player_b, float zombie_r, float zombie_g, float zombie_b, int zombieNum);
    
private:
    landFlag playerLand[66][66];
    bool playerTrail[66][66];
    int zombieNum;
    Player *player;
    Zombie *zombies;
};

#endif /* Map_h */
