//
//  Package.h
//  RobotAndWifi
//
//  Created by Jeroen Provoost on 25/03/14.
//  Copyright (c) 2014 Jeroen Provoost. All rights reserved.
//

#ifndef RobotAndWifi_Package_h
#define RobotAndWifi_Package_h

typedef struct Info  {
    int robx;
    int roby;
    int robhoek;
    int doelx;
    int doely;
    int garx;
    int gary;
} Info;

typedef struct Udp_header  {
    unsigned short int udph_srcport;
    unsigned short int udph_destport;
    unsigned short int udph_len;
    unsigned short int udph_chksum;
} Udp_header;

typedef struct Udp_package  {
    int groep_a;
    Info info_a;
    int groep_b;
    Info info_b;
    int obs[8];
} Udp_package;

typedef struct Package  {
    int nr;
    Udp_package *udp_package;
}  Package;
#endif
