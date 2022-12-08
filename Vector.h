/**
 *  @file Vector.h
 *  @brief Definition of the Vector class
 *
 *
 *  @author Cody Barnson
 *  @bug No known bugs
 */

#ifndef _VECTOR_H
#define _VECTOR_H

/**
 * @struct Vector
 * @brief represents the change in position of x and y
 */

class Point;
struct Vector {
   double x;
   double y;

   
   Vector();
   Vector(double a, double b);
   ~Vector();

   
   /**
    *  @fn Vector operator * (double scalar);
    *  @brief takes a scalar value and multiplies x and y by it
    *  @param scalar 
    *  @return Vector
    */
   Vector operator * (double scalar);
   Vector operator + (Vector v);   
   void rollRandom();
   void rollReallyRandom();    
   
   
   // range [-200, 200]
   void rollRandomY();
   // range [-200,-1]
   void rollRandomX();   
   void reflectY();
   void reflectX();
   void flip();
   void Angle(Point p, Point p2, double time);
   
};

#endif
