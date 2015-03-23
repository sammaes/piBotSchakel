//
//  Robot.cpp
//  RobotCirkelDetector
//
//  Created by Jeroen Provoost on 11/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//
//

#include "Robot.h"
#include <string>
using namespace std;

Robot::Robot(void){
    
}
Robot::~Robot(){
    
}

int Robot::getXPosCirkel1(){
    return xPosCirkel1;
}
int Robot::getXPosCirkel2(){
    return xPosCirkel2;
}
int Robot::getYPosCirkel1(){
    return yPosCirkel1;
}
int Robot::getYPosCirkel2(){
    return yPosCirkel2;
}
int Robot::getRadius(){
    return radius;
}
Point Robot::getPoint1(){
    return punt1;
}
Point Robot::getPoint2(){
    return punt2;
}
int Robot::getAngle(){
    return angle;
}

void Robot::setXPosCirkel1(int x){
    xPosCirkel1 = x;
    setPoint1();
}
void Robot::setXPosCirkel2(int x){
    xPosCirkel2 = x;
    setPoint2();
}
void Robot::setYPosCirkel1(int y){
    yPosCirkel1 = y;
    setPoint1();
}
void Robot::setYPosCirkel2(int y){
    yPosCirkel2 = y;
    setPoint2();
}
void Robot::setRadius(int r){
    radius = r;
}
void Robot::setPoint1(){
    punt1.x = getXPosCirkel1();
    punt1.y = getYPosCirkel1();
}
void Robot::setPoint2(){
    punt1.x = getXPosCirkel2();
    punt1.y = getYPosCirkel2();
}
void Robot::setAngle(int a){
    angle = a;
}


