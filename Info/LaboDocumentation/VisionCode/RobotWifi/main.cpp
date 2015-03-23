//
//  main.cpp
//  RobotCirkelDetector
//
//  Created by Jeroen Provoost on 11/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "Robot.h"
#include "FramePoints.h"
#include "Line.h"
#include "Obstakel.h"
#include "Client.h"

void loadCameraParams(Mat& cameraMatrix, Mat& distCoeffs);

bool init = true;
bool DrukPause = false;
bool zenden = false;
bool drawing_line = false;
bool blauw = false;
bool rood = false;
bool groen = false;
bool wit = false;
bool roos = false;
bool geel = false;
bool zwart = false;
Robot robot1;
Robot robot2;
Obstakel object;
Obstakel object2;
Obstakel garage1;
Obstakel garage2;

Mat frameTonen;
Mat gray;
Mat frame;

Line lijn;
Line lijn1;
Line lijn2;
Line lijn3;
Line lijn4;

Point a;
Point b;
Point c;
int ang;

vector<Mat> rgb(3);
Mat Rch,Gch,Bch;
int status= 0;

Info grpA;
Info grpB;
Udp_package udp;

void help(){
    
    cout << "knop p: ";
    cout << "Drukpause " << DrukPause << endl;
    cout << "knop z: ";
    cout << "Zenden " << zenden <<  endl;
    cout << "knop i: ";
    cout << "Init " << init <<  endl;
}

//--------------------------------------------------------------------//
//		Teken omkadering veld
//--------------------------------------------------------------------//

void draw_line( Mat* img, FramePoints beeldPunten ){
    Line line1 = beeldPunten.getLijn1();
    Line line2 = beeldPunten.getLijn2();
    Line line3 = beeldPunten.getLijn3();
    Line line4 = beeldPunten.getLijn4();
    
    Scalar color(255,0,0);
    int thickness = 1;
    int linetype = 8;
    int shift = 0;
    // Tekenen van 4 lijnen
    line(*img, Point(line1.getXPos1(),line1.getYPos1()), Point(line1.getXPos2(), line1.getYPos2()), color, thickness,linetype, shift);
    line(*img, Point(line2.getXPos1(),line2.getYPos1()), Point(line2.getXPos2(), line2.getYPos2()), color, thickness,linetype, shift);
    line(*img, Point(line3.getXPos1(),line3.getYPos1()), Point(line3.getXPos2(), line3.getYPos2()), color, thickness,linetype, shift);
    line(*img, Point(line4.getXPos1(),line4.getYPos1()), Point(line4.getXPos2(), line4.getYPos2()), color, thickness,linetype, shift);
}


//--------------------------------------------------------------------//
//		CallbackFunctie voor muisklikken
//--------------------------------------------------------------------//

void CallBackFunc(int event, int x, int y, int flags, void* param){
   
    if(init){
        FramePoints *cast = (FramePoints*) param;
        //cout << "In CallBackFunc" << endl;
        Mat frame = cast->getMat();
        Line line1 = cast->getLijn1();
        Line line2 = cast->getLijn2();
        Line line3 = cast->getLijn3();
        Line line4 = cast->getLijn4();
    
        if(event == CV_EVENT_LBUTTONDOWN){
            switch (status) {
                // Lijn van de xas
                case 0:
                    line1.setXPos1(x);
                    line1.setYPos1(y);
                
                    line4.setXPos2(x);
                    line4.setYPos2(y);
                    status = 1;
                    cout << "Case0" << endl;
                    break;
                
                    // Lijn parallel met de yas
                case 1:
                    line1.setXPos2(x);
                    line1.setYPos2(y);
                
                    line2.setXPos1(x);
                    line2.setYPos1(y);
                    status = 2;
                    cout << "Case1" << endl;
                    break;
                
                    // Lijn parallel met de xas
                case 2:
                    line2.setXPos2(x);
                    line2.setYPos2(y);
                
                    line3.setXPos1(x);
                    line3.setYPos1(y);
                    status = 3;
                    cout << "Case2" << endl;
                    break;
                
                    // Lijn van de yas
                case 3:
                    line3.setXPos2(x);
                    line3.setYPos2(y);
                
                    line4.setXPos1(x);
                    line4.setYPos1(y);
                    status = 4;
                    cout << "Case3" << endl;
                    break;
                default:
                    break;
            }
            cast->setLijn1(line1);
            cast->setLijn2(line2);
            cast->setLijn3(line3);
            cast->setLijn4(line4);
            cast->setMat(frame);
        }
        else{
            if(event == CV_EVENT_RBUTTONDOWN)
            {
                Line nullijn;
                nullijn.setXPos1(0);
                nullijn.setXPos2(0);
                nullijn.setYPos1(0);
                nullijn.setYPos2(0);
                cast->setLijn1(nullijn);
                cast->setLijn2(nullijn);
                cast->setLijn3(nullijn);
                cast->setLijn4(nullijn);
                cast->setMat(frame);
                status = 0;
            }
        }
    }
    else{
        
        if(event == CV_EVENT_LBUTTONDOWN){
            garage1.setXPos(x);
            garage1.setYPos(y);
		std::cout << "Setting pos on " << x << "," << y << std::endl;
        }

        if(event == CV_EVENT_RBUTTONDOWN)
        {
            garage2.setXPos(x);
            garage2.setYPos(y);
		std::cout << "Setting pos2 on " << x << "," << y << std::endl;
        }
    }
}
//--------------------------------------------------------------------//
//		Zet juiste parameters in struct groepA
// 		-1 bij geen detectie
//--------------------------------------------------------------------//

void setInfoGrpA(Info *a, bool info){
    if(info){
        a->robx = robot1.getXPosCirkel1();
        a->roby = 480 - robot1.getYPosCirkel1();
        a->robhoek = robot1.getAngle();
        a->garx = garage1.getXPos();
        a->gary = 480 - garage1.getYPos();
        a->doelx = object.getXPos();
        a->doely = 480 - object.getYPos();
    }
    else{
        a->robx = -1;
        a->roby = -1;
        a->robhoek = -1;
        a->doelx = -1;
        a->doely = -1;
    }
//cout << "GroepA: " << a->robx << "\t"<< a->roby << "\t" << a->robhoek << "\t" << a->garx << "\t" << a->gary << "\t" << a->doelx << "\t" << a->doely << endl;
}
//--------------------------------------------------------------------//
//		Zet juiste parameters in struct groepB
// 		-1 bij geen detectie
//--------------------------------------------------------------------//
void setInfoGrpB(Info *b, bool info){
    if(info){
        b->robx = robot2.getXPosCirkel2();
        b->roby = 480 - robot2.getYPosCirkel2();
        b->robhoek = robot2.getAngle();
        b->garx = garage2.getXPos();
        b->gary = 480 - garage2.getYPos();
        b->doelx = object2.getXPos();
        b->doely = 480 - object2.getYPos();
    }
    else{
        b->robx = -1;
        b->roby = -1;
        b->robhoek = -1;
        b->doelx = -1;
        b->doely = -1;
    }
cout << "GroepB: "<< b->robx << "\t"<< b->roby << "\t" << b->robhoek << "\t" << b->garx << "\t" << b->gary << "\t" << b->doelx << "\t" << b->doely << endl;
}

 
//--------------------------------------------------------------------//
//	Bereken de hoek van de robot		
//--------------------------------------------------------------------//

double GetAngle(Point2d a, Point2d b){

    // a = kleine cirkel, b = grote cirkel
    float angle = atan2(b.y - a.y, b.x - a.x);
    angle = angle * 180/3.14;
    angle = 180 - angle;
    return angle;
}
 
//--------------------------------------------------------------------//
//	Onderzoek de cirkels die van houghTransform komen op kleur		
//--------------------------------------------------------------------//
void getCirkels(vector<Vec3f> circles){
    
    blauw = false;
    rood = false;
    groen = false;
    wit = false;
    roos = false;
    geel = false;
    zwart = false;
    
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle center
        circle( gray, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        circle( gray, center, radius, Scalar(0,255,255), 3, 8, 0 );
        
        ////////////////////////////////////////////////////////////////////////////////
        // Channels opsplitsen om nadien de kleur van het centerpunt te zoeken
        Mat ch1, ch2, ch3;
        // "channels" is a vector of 3 Mat arrays:
        vector<Mat> channels(3);
        // split img:
        split(frame, channels);
        // get the channels (dont forget they follow BGR order in OpenCV)
        ch1 = channels[0]; // B
        ch2 = channels[1]; // G
        ch3 = channels[2]; // R
        ////////////////////////////////////////////////////////////////////////////////
        int BlauwCenter = (int)ch1.at<uchar>(center.y,center.x);
        int GroenCenter = (int)ch2.at<uchar>(center.y,center.x);
        int RoodCenter = (int)ch3.at<uchar>(center.y,center.x);

        /// ----------------------------------------------------------------- ///
        /// ########## Blauw = Kleine bol robot 1
        if( RoodCenter < 90 && GroenCenter < 200 && BlauwCenter > 235){
            blauw = true;
            // circle center
            circle( frameTonen, center, 3, Scalar(255,0,0), -1, 8, 0 );
            // circle outline
            circle( frameTonen, center, radius, Scalar(255,0,0), 3, 8, 0 );
            robot1.setXPosCirkel1(center.x);
            robot1.setYPosCirkel1(center.y);
        }

        /// ########## Rood = Grote bol robot 1
        if( RoodCenter > 135 && GroenCenter < 100 && BlauwCenter < 100){
            rood = true;
            // circle center
            circle( frameTonen, center, 3, Scalar(0,0,255), -1, 7, 0 );
            // circle outline
            circle( frameTonen, center, radius, Scalar(0,0,255), 3, 8, 0 );
            robot1.setXPosCirkel2(center.x);
            robot1.setYPosCirkel2(center.y);
        }
        
        /// ########## geel = Kleine bol robot 2
        if( RoodCenter > 200 && GroenCenter > 200 && BlauwCenter < 160){
            geel = true;
            // circle center
            circle( frameTonen, center, 3, Scalar(255,0,0), -1, 7, 0 );
            // circle outline
            circle( frameTonen, center, radius, Scalar(255,0,0), 3, 8, 0 );
            robot2.setXPosCirkel1(center.x);
            robot2.setYPosCirkel1(center.y);
        }

        /// ########## Roos = Grote bol robot 2
        if( RoodCenter > 150 && GroenCenter < 150 && BlauwCenter > 180){
            roos = true;
            // circle center
            circle( frameTonen, center, 3, Scalar(0,255,255), -1, 7, 0 );
            // circle outline
            circle( frameTonen, center, radius, Scalar(255,255,0), 3, 8, 0 );
            robot2.setXPosCirkel2(center.x);
            robot2.setYPosCirkel2(center.y);
        }

        /// ########## Wit = Object1
        if( RoodCenter >170 && GroenCenter > 170 && BlauwCenter > 170){
            wit = true;
            // circle center
            circle( frameTonen, center, 3, Scalar(0,255,255), -1, 7, 0 );
            // circle outline
            circle( frameTonen, center, radius, Scalar(255,255,0), 3, 8, 0 );
            object.setXPos(center.x);
            object.setYPos(center.y);
            object.setRadius(radius);
            
            Point p1 = Point(object.getXPos() - 20, object.getYPos()-20);
            Point p2 = Point(object.getXPos() +20, object.getYPos()+20);
            
            putText(frameTonen, "Object1 Detected", Point(420,380), 1, 1, Scalar(0,0,0));
            rectangle(frameTonen, p1,p2,Scalar(0,0,0));
        }

        /// ########## Zwart = Object2
        if( RoodCenter < 50 && GroenCenter < 50 && BlauwCenter < 50){
            zwart = true;
            // circle center
            circle( frameTonen, center, 3, Scalar(0,255,255), -1, 7, 0 );
            // circle outline
            circle( frameTonen, center, radius, Scalar(255,255,0), 3, 8, 0 );
            object2.setXPos(center.x);
            object2.setYPos(center.y);
            object2.setRadius(radius);
            
            Point p1 = Point(object2.getXPos() - 20, object2.getYPos()-20);
            Point p2 = Point(object2.getXPos() +20, object2.getYPos()+20);
            
            putText(frameTonen, "Object2 Detected", Point(420,400), 1, 1, Scalar(255,255,255));
            rectangle(frameTonen, p1,p2,Scalar(0,255,0));
            
        }
        /// ----------------------------------------------------------------- ///
        /// Wanneer Rode en Blauwe cirkel gevonden zijn -> Robot1 gevonden 
        if(blauw == true && rood == true){
            Point p1 = Point(robot1.getXPosCirkel1() - 50, robot1.getYPosCirkel1()-50);
            Point p2 = Point(robot1.getXPosCirkel1() +50, robot1.getYPosCirkel1()+50);
            Point a = Point(robot1.getXPosCirkel1(),robot1.getYPosCirkel1());
            Point b = Point(robot1.getXPosCirkel2(),robot1.getYPosCirkel2());
            Point c = Point(robot1.getXPosCirkel1()+100,robot1.getYPosCirkel1());
            
            a = Point(robot1.getXPosCirkel1(),robot1.getYPosCirkel1());
            b = Point(robot1.getXPosCirkel2(),robot1.getYPosCirkel2());
            c = Point(robot1.getXPosCirkel1()+100,robot1.getYPosCirkel1());
            
            ang = (int)GetAngle(a, b);
            robot1.setAngle(ang);
            
            //cout << "Hoek Robot1: " << ang << " graden." << endl;
            //line(frameTonen, Point(robot1.getXPosCirkel1(),robot1.getYPosCirkel1()),Point(robot1.getXPosCirkel2(),robot1.getYPosCirkel2()), Scalar(255,255,255));
            //line(frameTonen, Point(robot1.getXPosCirkel2(),robot1.getYPosCirkel2()),Point(robot1.getXPosCirkel2()+100,robot1.getYPosCirkel2()), Scalar(255,255,255));
            
            putText(frameTonen, "Robot1 Detected", Point(420,320), 1, 1, Scalar(255,0,0));
            rectangle(frameTonen, p1,p2,Scalar(255,0,0));
        }
        // Als Groep1 al zijn info gevonden heeft -> de juiste waarden doorsturen
        if(blauw == true && rood == true && wit == true){
            setInfoGrpA(&grpA,true);
            udp.info_a = grpA;
        }
        // Anders -1 doorsturen
        else{
            setInfoGrpA(&grpA,false);
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Wanneer Rose en Gele cirkel gevonden zijn -> Robot2 gevonden 
        if(geel == true && roos == true){
            Point p1 = Point(robot2.getXPosCirkel1() - 50, robot2.getYPosCirkel1()-50);
            Point p2 = Point(robot2.getXPosCirkel1() +50, robot2.getYPosCirkel1()+50);
            
            a = Point(robot2.getXPosCirkel1(),robot2.getYPosCirkel1());
            b = Point(robot2.getXPosCirkel2(),robot2.getYPosCirkel2());
            c = Point(robot2.getXPosCirkel1()+100,robot2.getYPosCirkel1());
            
            ang = (int)GetAngle(a, b);
            robot2.setAngle(ang);
	//cout << "Pos Robot2: " << robot2.getXPosCirkel1() << 480 - robot2.getYPosCirkel1() << endl;
        //cout << "Hoek Robot2: " << ang  << " graden."<< endl;
   
            putText(frameTonen, "Robot2 Detected", Point(420,340), 1, 1, Scalar(0,255,0));
            rectangle(frameTonen, p1,p2,Scalar(0,255,0));
        }
        // Als Groep2 al zijn info gevonden heeft -> de juiste waarden doorsturen
        if(geel == true && roos == true && zwart == true){
            setInfoGrpB(&grpB, true);
        }
        // Anders -1 doorsturen
        else{
            setInfoGrpB(&grpB, false);
        }
        udp.info_a = grpA;
        udp.info_b = grpB;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
int main(int argc, const char * argv[]){
   
    VideoCapture cap;
    //cap.open("/users/jeroen/desktop/BeeldenRobot/e/frame-%010d.ppm");
    cap.open(0);
    Mat src;
    Mat cameraMatrix, distCoeffs;
    Mat frametemp;
    help();

    Size sz;
    int height;
    int width;
    FramePoints beeld;
    /* Variabelen voor Wifi */
    Client cl;
    Client clB;
    
    Vec3b colour;
    cout << "GroepA: IP= " << groepA << endl;
    cout << "GroepB: IP= " << groepB << endl;

	// Camera parameters van cameraCalibratie
    loadCameraParams(cameraMatrix,distCoeffs);

    cap >> src;
cout << "Cap to src" << endl;
    if(src.empty()){
        cout << "Images can't be loaded" << endl;
        exit(-1);
    }
    sz = src.size();
    height = sz.height;
    width = sz.width;
    
    src.copyTo(frame);
    cout << "Voor lus" << endl;


    // Lus die over de frames gaat
    for(;;)
    {
        if(!DrukPause){
            double tijd = (double)getTickCount();
            cap >> src;
	 if(src.empty()){
                exit(-1);
            }  
      	cvtColor( src, frame, CV_BayerBG2BGR );
	frametemp = frame.clone();
	undistort(frametemp, frame, cameraMatrix, distCoeffs);
	frame.copyTo(frameTonen);

        cvtColor( frame, gray, CV_BGR2GRAY );
       	beeld.setMat(frame);
	namedWindow("Aanklikscherm");

        setMouseCallback("Aanklikscherm", CallBackFunc , (void*)&beeld);
        draw_line( &frameTonen, beeld );
        
            if(!init){
                /// Reduce the noise so we avoid false circle detection
                GaussianBlur( gray, gray, Size(11, 11), 1, 1 );
        
                vector<Vec3f> circles;
        
                /// Apply the Hough Transform to find the circles
                HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, 1, 35, 30, 0, 20 );

                getCirkels(circles);
                
                // setMouseCallback("Aanklikscherm", CallBackFunc , (void*)&beeld);
                tijd = ((double)getTickCount() - tijd)/getTickFrequency();
                //ycout << "frame: " << framecount << endl;
                // cout << "Times passed in seconds: " << tijd << endl;
            }
        }
        if(zenden){
            	cl.init();
		cl.send(udp);
		cl.close_socket();
	
		clB.initB();
		clB.sendB(udp);
		clB.close_socketB();	
		cout << "Verzonden" << endl;

        }
        // Draw Garages
        circle(frameTonen, Point(garage1.getXPos(),garage1.getYPos()),5,Scalar(255,255,255));
        circle(frameTonen, Point(garage2.getXPos(),garage2.getYPos()),5,Scalar(255,255,0));

        //putText(frameTonen, to_string(garage1.getXPos()), Point(100,100), 2, 5, Scalar(255,255,255));
        //putText(frameTonen, to_string(garage1.getYPos()), Point(200,100), 2, 5, Scalar(255,255,255));
	//cout << garage1.getXPos() <<"\t" <<  garage1.getYPos() << endl;
        //imshow("gray", gray);
        imshow("Aanklikscherm", frame);
        imshow("frameTonen", frameTonen);

        char c = waitKey(30);
        
       if( c == 'p'){
           DrukPause = !DrukPause;
           cout << "Drukpause " << DrukPause << endl;
        }
       else if (c == 'z'){
           zenden = !zenden;
           cout << "Zenden " << zenden <<  endl;
       }
       else if (c == 'i'){
           init = !init;
           cout << "Init " << init <<  endl;
       }
       else if (c == 'n'){
            break;
        }
        else if( (char)c == '\x1b' ){
            exit(0);
        }
    }
    	cl.close_socket();
	clB.close_socketB();
    return 0;
}



void loadCameraParams(Mat& cameraMatrix, Mat& distCoeffs)
{
	
	FileStorage fs( "out_camera_data.xml", FileStorage::READ );
	
	fs["Camera_Matrix"] >> cameraMatrix;
	fs["Distortion_Coefficients"] >> distCoeffs;
	return;
}

