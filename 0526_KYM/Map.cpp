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
            playerTrail[i][j] = false;
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
    
    trailing = false;
    status = gaming;
    
    player = new Player;
    *player = Player(32, 32, player_r, player_g, player_b);
    (*player).setLife(3);
    
    zombieNum = newZombieNum;
    zombies = new vector<Zombie>;
    srand((int)time(0));
    for (int i = 0; i < zombieNum; i++){
        int x, y = 0;
        while (playerLand[x][y] != emptyLand){
            x = (rand() % 64) + 1;
            y = (rand() % 64) + 1;
        }
        (*zombies).push_back(Zombie(x, y, zombie_r, zombie_g, zombie_b));
    }
}

void Map::update(){
    (*player).update(playerLand);
    for (int i = 0; i < zombieNum; i++){
        (*zombies)[i].update(playerLand);
    }
    
    bool temp = (playerLand[(*player).getX()][(*player).getY()]==myLand);
    
    if (temp&&(!trailing)){
        return;
    } else if (temp&&trailing){
        (*this).trailToLand();
    } else { // temp = false -> not myLand
        if (!trailing){
            trailing = true;
        }
        playerTrail[(*player).getX()][(*player).getY()] = true;
    }
    
    if ((*this).trailCollision()){
        (*this).playerReset();
    }
    if((*this).percentLand()>=0.7){
        status = gameWin;
    } //////////////main should check the status after update
}

float Map::percentLand(){      //Calculate the percentage of my land
	int playerLandNum;
	float playerLandPercent;

	for (int i = 0; i<66; i++){
		for (int j = 0; j<66; j++){
            if (playerLand[i][j] == 2){
                ++playerLandNum;
            }
		}
	}
	playerLandPercent = playerLandNum / 64 / 64;
	return playerLandPercent;
}

gameStatus Map::getStatus() {
    return status;
}

void Map::playerReset(){
    (*player).setX(32);
    (*player).setY(32);
    for (int i = 0; i<66; i++){
        for (int j = 0; j<66; j++){
            playerTrail[i][j] = false;
        }
    }
    int tempLife = (*player).getLife();
    (*player).setLife(tempLife-1);
    if ((tempLife-1)==0){
        status = gameOver;
    }
}

bool Map::trailCollision(){
    int playerPos[2];
    int zombieNum = (*zombies).size();
    int zombiesPos[zombieNum][2];
    
    playerPos[0] = (*player).getX();
    playerPos[1] = (*player).getY();
    for (int i = 0; i < zombieNum; i++){
        zombiesPos[i][0] = (*zombies)[i].getX();
        zombiesPos[i][1] = (*zombies)[i].getY();
    }
    //set player and zombie pos
    
    for (int i = 0; i<66; i++){
        for (int j = 0; j<66; j++){
            if (playerTrail[i][j] == true){
                if ((i==playerPos[0])&&(j==playerPos[1])){
                    return true;
                }
                for (int k = 0; k < zombieNum; k++){
                    if ((zombiesPos[k][0]==i)&&(zombiesPos[k][1]==j)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Map::trailToLand(){
    bool tempLand[66][66];
    for (int i = 0; i<66; i++){
        for (int j = 0; j<66; j++){
            if ((playerTrail[i][j])||(playerLand[i][j]==myLand)){
                tempLand[i][j] = true;
            } else {
                tempLand[i][j] = false;
            }
        }
    }
    bool visitLand[66][66] = {false};
    (*this).floodFillLand(tempLand, visitLand, 0, 0);
    for (int i = 0; i<66; i++){
        for (int j = 0; j<66; j++){
            if(!visitLand[i][j]){
                playerLand[i][j] = myLand;
            }
        }
    }
}

void Map::floodFillLand(bool boolLand[66][66], bool visitLand[66][66], int x, int y){
    if (visitLand[x][y] == true){
        return;
    }
    if ((x<0)||(y<0)||(x>65)||(y>65)){
        return;
    }
    if (boolLand[x][y] == true){
        return;
    }
    visitLand[x][y] = true;
    (*this).floodFillLand(boolLand, visitLand, x-1, y);
    (*this).floodFillLand(boolLand, visitLand, x-1, y-1);
    (*this).floodFillLand(boolLand, visitLand, x, y-1);
    (*this).floodFillLand(boolLand, visitLand, x+1, y-1);
    (*this).floodFillLand(boolLand, visitLand, x+1, y);
    (*this).floodFillLand(boolLand, visitLand, x+1, y+1);
    (*this).floodFillLand(boolLand, visitLand, x, y+1);
    (*this).floodFillLand(boolLand, visitLand, x-1, y+1);
}























