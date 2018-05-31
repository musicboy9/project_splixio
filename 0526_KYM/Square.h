//
//  Square.h
//  0526_KYM
//
//  Created by 고영민 on 2018. 5. 31..
//  Copyright © 2018년 고영민. All rights reserved.
//

#ifndef Square_h
#define Square_h

class Square {
public:
    Square(float x, float y, float r, float g, float b, float sz);
    void setColor(float r, float g, float b);
    void setPos(float x, float y);
    float getX() const;
    float getY() const;
    void draw() const;
private:
    float size;
    float color[3];
    float pos[2];
};

#endif /* Square_h */
