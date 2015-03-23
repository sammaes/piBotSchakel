//
//  Line.h
//  MouseCallbackVideo
//
//  Created by Jeroen Provoost on 3/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#ifndef __MouseCallbackVideo__Line__
#define __MouseCallbackVideo__Line__
#include <iostream>
#include <string>

using namespace std;

class Line{
    
public:
    Line(void);
    ~Line(void);
    
    int getXPos1();
    int getXPos2();
    int getYPos1();
    int getYPos2();
    
    void setXPos1(int x);
    void setXPos2(int x);
    void setYPos1(int y);
    void setYPos2(int y);
private:
    int xPos1, yPos1;
    int xPos2, yPos2;
};

#endif /* defined(__MouseCallbackVideo__Line__) */
