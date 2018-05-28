//
//  Map.cpp
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 26..
//  Copyright © 2018년 고영민. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Map.h"
#include <stdlib.h>
#include <time.h>

Map::Map(float player_r, float player_g, float player_b, float zombie_r, float zombie_g, float zombie_b, int newZombieNum){
    
    for (int i=0; i<66; i++){
        for (int j=0; j<66; j++){
            playerLand[i][j] = emptyLand;
        }
    }
    for (int i=0; i<66; i++){
        playerLand[0][i] = boundary;
        playerLand[65][i] = boundary;
        playerLand[i][0] = boundary;
        playerLand[i][65] = boundary;
    }
    for (int j=31; j<34; j++){
        for (int k=31; k<34; k++){
            playerLand[j][k] = myLand;
        }
    }
    
    memset(playerTrail,false,sizeof(playerTrail));
    
    player = new Player;
    *player = Player(32, 32, player_r, player_g, player_b);
    
    zombieNum = newZombieNum;
    zombies = new Zombie[zombieNum];
    srand((int)time(0));
    for (int i = 0; i < zombieNum; i++){
        int x, y = 0;
        while (playerLand[x][y] != emptyLand){
            x = (rand() % 64) + 1;
            y = (rand() % 64) + 1;
        }
        zombies[i] = Zombie(x, y, zombie_r, zombie_g, zombie_b);
    }
}
