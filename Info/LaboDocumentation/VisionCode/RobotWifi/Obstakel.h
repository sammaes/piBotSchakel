//
//  Obstakel.h
//  ObstakelCirkelDetector
//
//  Created by Jeroen Provoost on 11/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#ifndef __ObstakelCirkelDetector__Obstakel__
#define __ObstakelCirkelDetector__Obstakel__

#include <iostream>
#include <string>

using namespace std;

class Obstakel{
    
public:
    Obstakel(void);
    ~Obstakel(void);
    
    int getXPos();
    int getYPos();
    int getRadius();
    
    void setXPos(int x);
    void setYPos(int y);
    void setRadius(int r);
    
private:
    // Cirkel 1 is de kleine cirkel, Cirkel 2 de grote
    int xPos, yPos;
    int radius;    
};

#endif /* defined(__ObstakelCirkelDetector__Obstakel__) */
