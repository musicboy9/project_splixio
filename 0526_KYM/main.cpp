//
//  main.cpp
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 26..
//  Copyright © 2018년 고영민. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Square.h"
#include "Map.h"
#include "OpenGL/OpenGL.h"
#include "GLUT/GLUT.h"

#define WIDTH 495      // window's width
#define HEIGHT 660     // window's height
#define SQUARE_INDEX(i, j) (64*(i)+(j))

float color_map[3] = {0.1, 0.1, 0.1};
float color_player[3] = {0.5, 0.5, 0.5};
float color_myLand[3] = {0.3, 0.3, 0.3};
float color_zombie[3] = {0.8, 0.3, 0.1};
float color_trail[3] = {0.4, 0.8, 0.4};
playerDirection currentDirection = STOP;

Map *map;
vector<Square> squares;

int cnt = 0;

void updateSquares(int i, int j){
    int tempIndex = SQUARE_INDEX(i, j);
    
    if ((*map).getStatus()==gaming){
        landFlag tempFlag = (*map).getLandFlag(i, j);
        switch (tempFlag) {
            case trailFlag:
                squares[tempIndex].setColor(color_trail[0], color_trail[1], color_trail[2]);
            case playerFlag:
                squares[tempIndex].setColor(color_player[0], color_player[1], color_player[2]);
                break;
            case myLand:
                squares[tempIndex].setColor(color_myLand[0], color_myLand[1], color_myLand[2]);
                break;
            case zombieFlag:
                squares[tempIndex].setColor(color_zombie[0], color_zombie[1], color_zombie[2]);
                break;
            default:
                squares[tempIndex].setColor(color_map[0], color_map[1], color_map[2]);
                break;
        }
    }
}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            currentDirection = UP;
            std::cout<<"1"<<std::endl;
            break;
        case GLUT_KEY_DOWN:
            currentDirection = DOWN;
            std::cout<<"2"<<std::endl;
            break;
        case GLUT_KEY_RIGHT:
            currentDirection = RIGHT;
            std::cout<<"3"<<std::endl;
            break;
        case GLUT_KEY_LEFT:
            currentDirection = LEFT;
            std::cout<<"4"<<std::endl;
            break;
        default:
            std::cout<<"0"<<std::endl;
            break;
    }
}

void windowInit(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 66, 0, 88);
}

void init(){
    for(int i=0;i<64;i++){
        for(int j=0; j<64; j++){
            Square temp_sq = Square(i+1, i+2, j+1, j+2, color_map[0], color_map[1], color_map[2]);
            squares.push_back(temp_sq);
        }
    }
    map = new Map(color_player[0], color_player[1], color_player[2], color_zombie[0], color_zombie[1], color_zombie[2], 1);
}

void renderScene(void) {
    glEnable(GL_DEPTH_TEST);
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<64;i++){
        for(int j=0; j<64; j++){
            int tempIndex = SQUARE_INDEX(i, j);
            squares[tempIndex].draw();
        }
    }
    glutSwapBuffers();
}

void idle() {
    (*map).update(currentDirection);
    
    for(int i=0;i<64;i++){
        for(int j=0;j<64; j++){
            updateSquares(i, j);
        }
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(650, 300);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Splix IO");
    windowInit();
    
    init();
    
    glutDisplayFunc(renderScene);
    glutSpecialFunc(processSpecialKeys);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
