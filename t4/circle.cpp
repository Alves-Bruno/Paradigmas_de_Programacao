/*
 * circle.cpp
 *
 *  Created on: 26 de abr de 2017
 *      Author: bruno
 */

#include <iostream>
#include <cmath>

using namespace std;
const double PI = 3.14159;

class Point {
private:
   double x;
   double y;
public:
   Point() {
      x = y = 0.0;
   }

   Point(double x_, double y_) {
        x = x_;
        y = y_;
     }

   void move(double dx, double dy){
	   x += dx;
	   y += dy;

   }

   double distanceTo(Point* ponto){

	   return std::sqrt(pow((ponto->x - x), 2) + pow((ponto->y - y), 2));
   }

};


class Circle {
private:
	Point p;
	double r;
public:
   Circle() {
	  p = Point(0.0,0.0);
      r = 0.0;
   }

   Circle(double x_, double y_, double r_) {
	   	p = Point(x_, y_);
        r = r_;
     }

   double area() {
      return PI * r * r;
   }

   void setRadius(double radius){
	   r=radius;
   }

   double getRadius(void){
  	   return r;
   }

   Point getPoint(void){
	   return p;
   }

   double distanceTo(Circle *c2){

	   Point p2 = c2->getPoint();
	   return p.distanceTo(&p2) - (r + c2->getRadius());
   }
};

int main() {

	Circle c1, c2;

	c1 = Circle(10, 10, 5);
	c2 = Circle(30, 10, 5);

	std::cout << "Distance c1, c2 = " << c1.distanceTo(&c2) << std::endl;

}












