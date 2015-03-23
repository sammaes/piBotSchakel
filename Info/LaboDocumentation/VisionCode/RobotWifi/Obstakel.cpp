//
//  Obstakel.cpp
//  ObstakelCirkelDetector
//
//  Created by Jeroen Provoost on 11/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#include "Obstakel.h"
//
//  Obstakel.cpp
//  ObstakelCirkelDetector
//
//  Created by Jeroen Provoost on 11/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//
//

#include "Obstakel.h"
#include <string>
using namespace std;

Obstakel::Obstakel(void){
    
}
Obstakel::~Obstakel(){
    
}

int Obstakel::getXPos(){
    return xPos;
}

int Obstakel::getYPos(){
    return yPos;
}
int Obstakel::getRadius(){
    return radius;
}
void Obstakel::setXPos(int x){
    xPos = x;
}
void Obstakel::setYPos(int y){
    yPos = y;
}
void Obstakel::setRadius(int r){
    radius = r;
}




