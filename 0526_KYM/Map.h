//
//  Map.h
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 26..
//  Copyright © 2018년 고영민. All rights reserved.
//

#include "Player.h"
#include "Zombie.h"
#include <vector>

#ifndef Map_h
#define Map_h

enum gameStatus {
    gameWin = 2,
    gaming = 1,
    gameOver = 0
};

class Map{
public:
    Map(float player_r, float player_g, float player_b, float zombie_r, float zombie_g, float zombie_b, int zombieNum);
    ~Map();
    Map& operator=(const Map& tempMap);
    Map(const Map& tempMap);
    void update(playerDirection newDirection);
	float percentLand(); //Calculate the percentage of my land
    landFlag getLandFlag(int x, int y);
    gameStatus getStatus();
    int getLife();
private:
    void playerReset();
    bool trailCollision(); // true if player or zombie on trail, false if not
    void trailToLand();
    void floodFillLand(bool boolLand[66][66], bool visitLand[66][66], int x, int y);
    
    landFlag totalLand[66][66];
    landFlag playerLand[66][66];
    vector<vector<int>> playerTrail;
    int zombieNum;
    bool trailing;
    Player *player;
    vector<Zombie> *zombies;
    playerDirection currentDir;
    gameStatus status;
};

#endif /* Map_h */
