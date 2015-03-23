//
//  Line.cpp
//  MouseCallbackVideo
//
//  Created by Jeroen Provoost on 3/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#include "Line.h"
#include <string>
using namespace std;

Line::Line(void){
    
}
Line::~Line(){
    
}

int Line::getXPos1(){
    return xPos1;
}
int Line::getXPos2(){
    return xPos2;
}
int Line::getYPos1(){
    return yPos1;
}
int Line::getYPos2(){
    return yPos2;
}
void Line::setXPos1(int x){
    xPos1 = x;
}
void Line::setXPos2(int x){
    xPos2 = x;
}
void Line::setYPos1(int y){
    yPos1 = y;
}
void Line::setYPos2(int y){
    yPos2 = y;
}



