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

Square::Square(float x, float y, float r, float g, float b, float sz) {
    (*this).setPos(x,y);
    (*this).setColor(r,g,b);
    size = sz;
}

void Square::setColor(float r, float g, float b){
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Square::setPos(float x, float y){
    pos[0] = x;
    pos[1] = y;
}

float Square::getX() const{
    return pos[0];
}

float Square::getY() const{
    return pos[1];
}

void Square::draw() const {
    glBegin(GL_QUADS);
    glColor3f( color[0], color[1], color[2]);
    glVertex3f(pos[0] + size/ 2, pos[1] + size/ 2, 0);
    glVertex3f(pos[0] - size/ 2, pos[1] + size/ 2, 0);
    glVertex3f(pos[0] - size/ 2, pos[1] - size/ 2, 0);
    glVertex3f(pos[0] + size/ 2, pos[1] - size/ 2, 0);
    glEnd();
}
