/*
* Author: Floris De Smedt - EAVISE/VISICS
*
* Point.cpp
*/
#include "Point.h"

		Point::Point(int x, int y):x(x), y(y)
		{
		}	
		int Point::getX(){
			return this->x;
		}
		int Point::getY(){
			return this->y;
		}

		void Point::Print(){
			cout << "(" << this->getX() << ", " << this->getY() << ") ";
		}
