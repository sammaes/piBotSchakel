//
//  Robot.h
//  RobotCirkelDetector
//
//  Created by Jeroen Provoost on 11/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#ifndef __RobotCirkelDetector__Robot__
#define __RobotCirkelDetector__Robot__

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Robot{
    
public:
    Robot(void);
    ~Robot(void);
    
    int getXPosCirkel1();
    int getYPosCirkel1();
    
    int getXPosCirkel2();
    int getYPosCirkel2();
    int getRadius();
    Point getPoint1();
    Point getPoint2();
    
    int getAngle();
    
    void setXPosCirkel1(int xPos);
    void setYPosCirkel1(int yPos);
    void setXPosCirkel2(int xPos);
    void setYPosCirkel2(int yPos);
    void setRadius(int r);
    void setPoint1();
    void setPoint2();
    void setAngle(int a);

private:
    // Cirkel 1 is de kleine cirkel, Cirkel 2 de grote
    int xPosCirkel1, yPosCirkel1;
    int xPosCirkel2, yPosCirkel2;
    int radius;
    Point punt1;
    Point punt2;
    int angle;
};

#endif /* defined(__RobotCirkelDetector__Robot__) */
