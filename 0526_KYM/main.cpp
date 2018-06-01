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

#define WIDTH 660        // window's width
#define HEIGHT 880        // window's height

float color_map[3] = {0.1, 0.1, 0.1};
float color_player[3] = {0.5, 0.5, 0.5};
float color_zombie[3] = {0.8, 0.3, 0.1};

Map *map;

void windowInit(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 66, 0, 88);
}

void init(){
    windowInit();
    
    vector<Square> squares;
    for(int i=0;i<64;i++){
        for(int j=0; j<64; j++){
            Square temp_sq = Square(i+1, i+2, j+1, j+2, color_map[0], color_map[1], color_map[2]);
            squares.push_back(temp_sq);
        }
    }
    map = new Map(color_player[0], color_player[1], color_player[2], color_zombie[0], color_zombie[1], color_zombie[2], 5);
}

void renderScene(void) {

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(660, 880);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Splix IO");
    windowInit();
    
    glutDisplayFunc(renderScene);
    glutMainLoop();
    return 0;
}
