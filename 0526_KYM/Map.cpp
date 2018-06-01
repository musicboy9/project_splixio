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

using namespace std;

Map::Map(float player_r, float player_g, float player_b, float zombie_r, float zombie_g, float zombie_b, int newZombieNum){
    
    for (int i=1; i<65; i++){
        for (int j=1; j<65; j++){
            playerLand[i][j] = emptyLand;
        }
    }
    for (int i=0; i<66; i++){
        playerLand[0][i] = boundary;
        playerLand[65][i] = boundary;
        playerLand[i][0] = boundary;
        playerLand[i][65] = boundary;
    }
    
    for (int j=28; j<37; j++){
        for (int k=28; k<37; k++){
            playerLand[j][k] = myLand;
        }
    }
    
    trailing = false;
    status = gaming;
    currentDir = STOP;
    
    player = new Player;
    *player = Player(32, 32, player_r, player_g, player_b);
    (*player).setLife(3);
    
    zombieNum = newZombieNum;
    zombies = new vector<Zombie>;
    srand((int)time(0));
    for (int i = 0; i < zombieNum; i++){
        int x = 0;int y = 0;
        while (playerLand[x][y] != emptyLand){
            x = (rand() % 64) + 1;
            y = (rand() % 64) + 1;
        }
        Zombie temp = Zombie(x, y, zombie_r, zombie_g, zombie_b);
        (*zombies).push_back(temp);
    }
}

Map::~Map(){
    if (player != nullptr){
        delete player;
    } if (zombies != nullptr){
        delete zombies;
    }
}

Map& Map::operator=(const Map& tempMap){
    for (int i = 0; i<66; i++){
        for (int j = 0; j<66; j++){
            totalLand[i][j] = tempMap.totalLand[i][j];
            playerLand[i][j] = tempMap.playerLand[i][j];
        }
    }
    playerTrail = tempMap.playerTrail;
    zombieNum = tempMap.zombieNum;
    trailing = tempMap.trailing;
    currentDir = tempMap.currentDir;
    status = tempMap.status;
    Player temp_player = Player(*tempMap.player);
    player = &temp_player;
    vector<Zombie> temp_zombies;
    for (auto i = (*(tempMap.zombies)).begin(); i != (*(tempMap.zombies)).end(); i++){
        temp_zombies.push_back(Zombie(*i));
    }
    zombies = &temp_zombies;
    
    return (*this);
}

Map::Map(const Map& tempMap){
    for (int i = 0; i<66; i++){
        for (int j = 0; j<66; j++){
            totalLand[i][j] = tempMap.totalLand[i][j];
            playerLand[i][j] = tempMap.playerLand[i][j];
        }
    }
    playerTrail = tempMap.playerTrail;
    zombieNum = tempMap.zombieNum;
    trailing = tempMap.trailing;
    currentDir = tempMap.currentDir;
    status = tempMap.status;
    Player temp_player = Player(*tempMap.player);
    player = &temp_player;
    vector<Zombie> temp_zombies;
    for (auto i = (*(tempMap.zombies)).begin(); i != (*(tempMap.zombies)).end(); i++){
        temp_zombies.push_back(Zombie(*i));
    }
    zombies = &temp_zombies;
}

void Map::update(playerDirection newDirection){
    
    (*player).setDirection(newDirection);
    (*player).update(playerLand);
    
    for (int i = 0; i < zombieNum; i++){
        (*zombies)[i].update(playerLand);
    }
    int temp_x = (*player).getX();
    int temp_y = (*player).getY();
    //cout<<"Player Coord: "<<temp_x<<" "<<temp_y<<endl;
    bool temp = (playerLand[temp_x][temp_y]==myLand);
    
    if ((*this).trailCollision()){
        (*this).playerReset();
    }
    /*
    if (temp&&(!trailing)){
        return;
    } else */
    if (temp&&trailing){
        (*this).trailToLand();
    } else { // temp = false -> not myLand
        if (!trailing){
            trailing = true;
        }
        if (playerTrail.size() != 0){
            int last_x = playerTrail.back()[0];
            int last_y = playerTrail.back()[1];
            if (!((last_x==((*player).getX()))&&(last_y==((*player).getY())))){
                /*cout<<"qwe"<<endl;
                cout<<last_x<<" "<<last_y<<endl;
                cout<<(*player).getX()<<" "<<(*player).getY()<<endl;
                 */
                vector<int> temp_trail;
                temp_trail.push_back((*player).getX());
                temp_trail.push_back((*player).getY());
                playerTrail.push_back(temp_trail);
            }
        } else {
            vector<int> temp_trail;
            temp_trail.push_back((*player).getX());
            temp_trail.push_back((*player).getY());
            playerTrail.push_back(temp_trail);
        }
    }
    
    if((*this).percentLand()>=0.7){
        status = gameWin;
        cout<<"gameWin"<<endl;
    }
    
    //totalLand is made for main to check the landFlag
    //playerLand - boundary, myLand, emptyLand / playerTrail / player / zombie
    for (int i =1; i<65; i++) {
        for (int j =1; j<65; j++) {
            totalLand[i][j] = playerLand[i][j];
        }
    }
    for (auto i = playerTrail.begin(); i != playerTrail.end(); i++){
        vector<int> temp = *i;
        totalLand[temp[0]][temp[1]] = trailFlag;
    }
    totalLand[(*player).getX()][(*player).getY()] = playerFlag;
    for (int i=0; i<(*zombies).size(); i++){
        totalLand[(*zombies)[i].getX()][(*zombies)[i].getY()] = zombieFlag;
    }
}

float Map::percentLand(){      //Calculate the percentage of my land
	float playerLandNum = 0;
	float playerLandPercent = 0;

	for (int i = 0; i<66; i++){
		for (int j = 0; j<66; j++){
            if (playerLand[i][j] == myLand){
                ++playerLandNum;
            }
		}
	}
	playerLandPercent = playerLandNum/(64*64);
    cout<<playerLandPercent<<endl;
	return playerLandPercent;
}

landFlag Map::getLandFlag(int x, int y){
    return totalLand[x+1][y+1];
}
gameStatus Map::getStatus() {
    return status;
}
int Map::getLife(){
    return (*player).getLife();
}

void Map::playerReset(){
    /*<<"reset"<<endl;
    for (auto i = playerTrail.begin(); i != playerTrail.end(); i++){
        vector<int> temp = *i;
        cout<<temp[0]<<" "<<temp[1]<<endl;
    }
    cout<<(*player).getX()<<" "<<(*player).getY()<<endl;
    */
    (*player).setX(32);
    (*player).setY(32);
    playerTrail.clear();
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
    
    for (std::vector<int>::size_type i=0;i!=playerTrail.size();i++){
        vector<int> temp = playerTrail[i];
        int trail_x = temp[0];
        int trail_y = temp[1];
        if ((trail_x==playerPos[0])&&(trail_y==playerPos[1])){
            if (i != playerTrail.size()-1){
                return true;
            }
        }
        for (int k = 0; k < zombieNum; k++){
            if ((zombiesPos[k][0]==trail_x)&&(zombiesPos[k][1]==trail_y)){
                //cout<<"zombie"<<endl;
                return true;
            }
        }
    }
    /*
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
    }*/
    return false;
}

void Map::trailToLand(){
    bool tempLand[66][66];
    for (int i = 0; i<66; i++){
        for (int j = 0; j<66; j++){
            if (playerLand[i][j]==myLand){
                tempLand[i][j] = true;
            } else {
                tempLand[i][j] = false;
            }
        }
    }
    for (auto i = playerTrail.begin(); i != playerTrail.end(); i++){
        vector<int> temp = *i;
        tempLand[temp[0]][temp[1]] = true;
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
    playerTrail.clear();
    for (int i = 0; i<(*zombies).size(); i++){
        if(playerLand[(*zombies)[i].getX()][(*zombies)[i].getY()]==myLand){
            //delete (*zombies)[i];
            (*zombies).erase((*zombies).begin()+i);
            if (zombieNum>0){
                zombieNum -= 1;
            }
        }
    }//kill zombies inside myLand
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


