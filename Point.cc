#include "Point.h"
#include "Vector.h"

Point::Point() {
   x = 0.0;
   y = 0.0;
}

Point::Point(double a, double b) : x(a), y(b) {
   
}

Point::~Point() {

}

Point Point::operator+(Vector v) {
   return Point(x + v.x, y + v.y);
}

Point Point::operator+(Point p) {
   return Point(x + p.x, y + p.y);
}
bool Point::operator==(Point p){
   return this->x==p.x&&this->y==p.y;
}

double Point::distance(Point p) {
   return sqrt( pow( ( p.x - x ), 2 ) + pow( ( p.y - y ), 2 ) );
}

void Point::rollRandom() {
   x = rand() % 200 + 800;
   y = rand() % 300 + 100;
}

void Point::rollRandomX() {
   x = rand() % 200 + 600;
}

void Point::rollRandomY() {
   y = rand() % 300 + 100;
}
