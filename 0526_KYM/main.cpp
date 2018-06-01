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
#include <sstream>
#include <string>


#define WIDTH 495      // window's width
#define HEIGHT 600     // window's height
#define SQUARE_INDEX(i, j) (64*(i)+(j))

float color_map[3] = {0.1, 0.1, 0.1};
float color_player[3] = {0.5, 0.5, 0.5};
float color_myLand[3] = {0.3, 0.3, 0.3};
float color_zombie[3] = {0.8, 0.3, 0.1};
float color_trail[3] = {0.4, 0.8, 0.4};
playerDirection currentDirection = STOP;
gameStatus currentStatus;

enum level {
    hard = 2,
    normal = 1,
    easy = 0
};
level gameLevel;

bool showCredit = false;

Map *map;
vector<Square> squares;

void init(){
    for(int i=0;i<64;i++){
        for(int j=0; j<64; j++){
            Square temp_sq = Square(i+1, i+2, j+1, j+2, color_map[0], color_map[1], color_map[2]);
            squares.push_back(temp_sq);
        }
    }
    map = new Map(color_player[0], color_player[1], color_player[2], color_zombie[0], color_zombie[1], color_zombie[2], 1+5*gameLevel);
    currentStatus = gaming;
}

void updateSquares(int i, int j){
    int tempIndex = SQUARE_INDEX(i, j);
    
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

void processSpecialKeys(int key, int x, int y) {
    if (currentStatus == gaming){
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
}

void processNormalKeys(unsigned char key, int x, int y){
    if (key == 'q' || key == 113){
        exit(0);
    } else if (key == 'r' || key == 114){
        init();
    } else if (key == 'h' || key == 104){
        gameLevel = hard;
        init();
    } else if (key == 'n' || key == 110){
        gameLevel = normal;
        init();
    } else if (key == 'e' || key == 101){
        gameLevel = easy;
        init();
    } else if (key == 'c' || key == 99){
        showCredit = !showCredit;
    }
}

void draw_string(void *font, const char *str, float x, float y, float r, float g, float b){
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for(int i = 0; i<strlen(str); i++){
        glutBitmapCharacter(font, str[i]);
    }
}

void draw_text(){
    //LIFE BACKGROUND
    glBegin(GL_QUADS);
    glColor3f(0.1,0.1,0.1);
    glVertex3f(1, 66, 0);
    glVertex3f(17, 66, 0);
    glVertex3f(17, 79, 0);
    glVertex3f(1, 79, 0);
    glEnd();
    
    //LIFE
    draw_string(GLUT_BITMAP_HELVETICA_18, "LIFE", 2, 76, 1 ,0, 0);
    int currentLife = (*map).getLife();
    for (int i = 0; i<currentLife; i++){
        glBegin(GL_QUADS);
        glColor3f(1,0.1,0.1);
        glVertex3f(2+5*i, 67, 0);
        glVertex3f(6+5*i, 67, 0);
        glVertex3f(6+5*i, 73, 0);
        glVertex3f(2+5*i, 73, 0);
        glEnd();
    }
    
    //TEXT BACKGROUND
    glBegin(GL_QUADS);
    glColor3f(0.1,0.1,0.1);
    glVertex3f(18, 66, 0);
    glVertex3f(42, 66, 0);
    glVertex3f(42, 79, 0);
    glVertex3f(18, 79, 0);
    glEnd();
    
    //TEXT
    draw_string(GLUT_BITMAP_HELVETICA_12, "RESTART - press r", 19, 77, 0.2, 1, 0.2);
    draw_string(GLUT_BITMAP_HELVETICA_12, "QUIT - press q", 19, 74, 0.7, 0.2, 0.2);
    draw_string(GLUT_BITMAP_HELVETICA_12, "LEVEL - press e/n/h", 19, 71, 0.8, 0.8, 0.2);
    draw_string(GLUT_BITMAP_HELVETICA_12, "CREDIT - press c", 19, 68, 0.8, 0.8, 0.8);
    
    //PERCENTAGE BACKGROUND
    glBegin(GL_QUADS);
    glColor3f(0.1,0.1,0.1);
    glVertex3f(43, 66, 0);
    glVertex3f(65, 66, 0);
    glVertex3f(65, 79, 0);
    glVertex3f(43, 79, 0);
    glEnd();
    
    //PERCENTAGE
    int percent = (*map).percentLand()*100;
    glBegin(GL_QUADS);
    glColor3f(0.3,0.3,0.3);
    glVertex3f(44, 67, 0);
    glVertex3f(58, 67, 0);
    glVertex3f(58, 73, 0);
    glVertex3f(44, 73, 0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.5,0.5,0.5);
    glVertex3f(44.5, 67.5, 0);
    glVertex3f(44.5+13*(*map).percentLand(), 67.5, 0);
    glVertex3f(44.5+13*(*map).percentLand(), 72.5, 0);
    glVertex3f(44.5, 72.5, 0);
    glEnd();
    draw_string(GLUT_BITMAP_HELVETICA_18, "PERCENTAGE", 44, 76, 0, 0.8, 0);
    char str[2] = "";
    sprintf(str, "%d", percent);
    strcat(str,"%");
    draw_string(GLUT_BITMAP_HELVETICA_18, str, 59.5, 69, 1, 1, 1);
    
    if (showCredit){
        //CREDIT BACKGROUND
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        float color[4] = {0.4,0.4,0.4,0.7};
        glBegin(GL_QUADS);
        glColor4fv(color);
        glVertex3f(21, 26, 0);
        glVertex3f(21, 40, 0);
        glVertex3f(44, 40, 0);
        glVertex3f(44, 26, 0);
        glEnd();
        
        //CREDIT
        draw_string(GLUT_BITMAP_HELVETICA_12, "SPLIX IO - Version 1", 22, 37, 1, 1, 1);
        draw_string(GLUT_BITMAP_HELVETICA_12, "2018.6.1", 22, 34, 1, 1, 1);
        draw_string(GLUT_BITMAP_HELVETICA_12, "KOH YEONGMIN", 22, 31, 1, 1, 1);
        draw_string(GLUT_BITMAP_HELVETICA_12, "KIM DONGWUK", 22, 28, 1, 1, 1);
        
    }
    
    if ((currentStatus != gaming)&&!showCredit){
        currentDirection = STOP;
        switch (currentStatus){
            case gameWin: draw_string(GLUT_BITMAP_HELVETICA_18, "WIN!", 30, 38, 1, 0, 0); break;
            case gameOver: draw_string(GLUT_BITMAP_HELVETICA_18, "GAMEOVER", 26, 38, 1, 0, 0); break;
        }
    }
}

void windowInit(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 66, 0, 80);
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
    draw_text();
    glutSwapBuffers();
}

void idle() {
    (*map).update(currentDirection);
    
    for(int i=0;i<64;i++){
        for(int j=0;j<64; j++){
            updateSquares(i, j);
        }
    }
    currentStatus = (*map).getStatus();
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(650, 300);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Splix IO");
    windowInit();
    
    gameLevel = easy;
    init();
    
    glutDisplayFunc(renderScene);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
