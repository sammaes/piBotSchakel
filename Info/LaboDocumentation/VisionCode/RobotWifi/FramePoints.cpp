//
//  FramePoints.cpp
//  VeldAfbakenen
//
//  Created by Jeroen Provoost on 6/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#include "FramePoints.h"
#include <string>
using namespace std;
FramePoints::FramePoints(){
}

FramePoints::~FramePoints(){
}

void FramePoints::setLijn1(Line lijn){
    lijn1 = lijn;
}
void FramePoints::setLijn2(Line lijn){
    lijn2 = lijn;
}
void FramePoints::setLijn3(Line lijn){
    lijn3 = lijn;
}
void FramePoints::setLijn4(Line lijn){
    lijn4 = lijn;
}
Line FramePoints::getLijn1(void){
    return lijn1;
}
Line FramePoints::getLijn2(void){
    return lijn2;
}
Line FramePoints::getLijn3(void){
    return lijn3;
}
Line FramePoints::getLijn4(void){
    return lijn4;
}
void FramePoints::setMat(Mat fr){
    frame = fr;
}
Mat FramePoints::getMat(){
    return frame;
}