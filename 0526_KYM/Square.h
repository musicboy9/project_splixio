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
    Square(float x1, float x2, float y1, float y2, float r, float g, float b);
    void setColor(float r, float g, float b);
    void setPos(float x1, float x2, float y1, float y2);
    //float getX() const;
    //float getY() const;
    void draw() const;
private:
    float color[3];
    float pos_x[2];
    float pos_y[2];
};

#endif /* Square_h */
