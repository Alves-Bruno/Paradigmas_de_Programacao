/*
 * point.cpp
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


int main() {

	int TAM = 5, i;
	Point p;
	p = Point(10, 10);
	Point* pontos[5];

	pontos[0] = new Point(10,10);
	pontos[1]= new Point(15,15);
	pontos[2]= new Point(20, 20);
	pontos[3]= new Point(25, 25);
	pontos[4]= new Point(30, 30);

	for(i=0; i<TAM; i++){
		std::cout << "Distance p to pontos[" << i<< "] = " << p.distanceTo(pontos[i]) << std::endl;
	}

	for(i=0; i<TAM; i++){
		delete pontos[i];
	}
}







