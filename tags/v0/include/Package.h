#ifndef PACKAGE_H
#define PACKAGE_H

typedef struct Info{
		int robotx;
		int roboty;
		int robothoek;
		int blikx;
		int bliky;
		int garagex;
		int garagey;
} Info;

typedef struct Udp_header{
    unsigned short int udph_srcport;
    unsigned short int udph_destport;
    unsigned short int udph_len;
    unsigned short int udph_checksum;
} Udp_header;

typedef struct Udp_package{
    int groep_a;
    Info info_a;
    int groep_b;
    Info info_b;
	int obs[8];
} Udp_package;

typedef struct Package{
    int nr;
    Udp_package *udp_package;
} Package;

#endif // PACKAGE_H
