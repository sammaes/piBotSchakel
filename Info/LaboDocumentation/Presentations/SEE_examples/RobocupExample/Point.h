/*
* Author: Floris De Smedt - EAVISE/VISICS
*
* Point.h
*/

#ifndef H_POINT
#define H_POINT

#include <iostream>

using namespace std;

class Point{
	public:
		Point(int x, int y);
		void Print();
		int getX();
		int getY();
	private:
		int x;
		int y;
};
#endif
