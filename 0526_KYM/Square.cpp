//
//  Square.cpp
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 31..
//  Copyright © 2018년 고영민. All rights reserved.
//

#include <stdio.h>
#include "Square.h"
#include "OpenGL/OpenGL.h"
#include "GLUT/GLUT.h"

Square::Square(float x1, float x2, float y1, float y2, float r, float g, float b) {
    (*this).setPos(x1, x2, y1,y2);
    (*this).setColor(r,g,b);
}

void Square::setColor(float r, float g, float b){
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Square::setPos(float x1, float x2, float y1, float y2){
    pos_x[0] = x1;
    pos_x[1] = x2;
    pos_y[0] = y1;
    pos_y[1] = y2;
}

/*
float Square::getX() const{
    return pos[0];
}

float Square::getY() const{
    return pos[1];
}*/

void Square::draw() const {
    float x1 = pos_x[0];
    float x2 = pos_x[1];
    float y1 = pos_y[0];
    float y2 = pos_y[1];
    
    glBegin(GL_QUADS);
    glColor3f(color[0], color[1], color[2]);
    glVertex3f(x1, y1, 0);
    glVertex3f(x1, y2, 0);
    glVertex3f(x2, y2, 0);
    glVertex3f(x2, y1, 0);
    glEnd();
}
