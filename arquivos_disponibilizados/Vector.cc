#include "Vector.h"
#include "Point.h"
#include <ctime>
#include <cstdlib>


Vector::Vector() {
   x = 0.0;
   y = 0.0;
}

Vector::Vector(double a, double b) : x(a), y(b) {

}

Vector::~Vector() {

}

Vector Vector::operator*(double scalar) {
   return Vector(x*scalar, y*scalar);
}

Vector Vector::operator+(Vector v) {
   return Vector(x + v.x, y + v.y);
}

void Vector::rollRandom() {
   x = rand() % 200 - 400; // range
   y = rand() % 400 - 200; // range [-200, 200]
}

void Vector::rollReallyRandom() {
   switch((rand() % 2) + 1){
      case 1:
	 x = rand() % 100 - 500;
	 y = rand() % 500;
	 break;
      case 2:
	 x = rand() % 200 - 600;
	 y = 0 - rand() % 500;
	 break;
   }
}

void Vector::rollRandomY() {
   y = rand() % 400 - 200;
}

void Vector::rollRandomX() {
   x = rand() % 200 - 400;
}

void Vector::reflectY() {
   y = -y;
}

void Vector::reflectX() {
   x = -x;
}
void Vector::Angle(Point end, Point current, double time){
   x=(end.x-current.x)/time;
   y=(end.y-current.y)/time;
}
void Vector::flip(){
   double temp=x;
   x=y;
   y=temp;
}
