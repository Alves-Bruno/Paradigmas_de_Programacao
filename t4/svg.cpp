/*
 * svg.cpp
 *
 *  Created on: 26 de abr de 2017
 *      Author: bruno
 */

#include <iostream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
const double PI = 3.14159;
ofstream SVG_file;


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

	double GetX(){

		return x;
	}

	double GetY(){

		return y;
	}

};


class Circle {
private:
	Point p;
	double r;
	const char *lineColor;
	const char *fillColor;


public:
	Circle() {
		p = Point(0.0,0.0);
		r = 0.0;
		lineColor = "black";
		fillColor = "black";

	}

	Circle(double x_, double y_, double r_) {
		p = Point(x_, y_);
		r = r_;
		lineColor = "black";
		fillColor = "black";
	}

	Circle(double x_, double y_, double r_, const char *lc, const char *fc) {
		p = Point(x_, y_);
		r = r_;
		lineColor = lc;
		fillColor = fc;
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

	const char* getLineCollor(void){
		return lineColor;
	}

	const char* getFillCollor(void){
		return fillColor;
	}

	double distanceTo(Circle *c2){

		Point p2 = c2->getPoint();
		return p.distanceTo(&p2) - (r + c2->getRadius());
	}


};

class Line {
private:
	Point p1;
	Point p2;
	int color[3];


public:

	Line(){
		p1 = Point(0.0,0.0);
		p2 = Point(0.0,0.0);
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
	}

	Line(Point p1_, Point p2_, int Red, int Green, int Blue){
		p1 = p1_;
		p2 = p2_;
		color[0] = Red;
		color[1] = Green;
		color[2] = Blue;
	}

	Line(double x1_, double y1_, double x2_, double y2_, int Red, int Green, int Blue){
		p1 = Point(x1_,y1_);
		p2 = Point(x2_,y2_);
		color[0] = Red;
		color[1] = Green;
		color[2] = Blue;
	}

	Line(double x1_, double y1_, double x2_, double y2_){
		p1 = Point(x1_,y1_);
		p2 = Point(x2_,y2_);
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
	}

	int GetRed(void){
		return color[0];
	}
	int GetGreen(void){
		return color[1];
	}
	int GetBlue(void){
		return color[2];
	}

	Point GetP1(){
		return p1;
	}

	Point GetP2(){
		return p2;
	}

};

void SVG_file_open(int altura, int largura){

	SVG_file.open("circulos.svg");
	SVG_file << "<!DOCTYPE html>\n" << "<html>\n" << "<body>\n";

	SVG_file << "<svg height=\"" << altura << "\" width=\"" << largura << "\">\n";
	SVG_file << "<rect width=\"" << altura << "\" height=\"" << largura << "\" style=\"fill:rgb(255,255,255);stroke-width:3;stroke:rgb(0,0,0)\" />\n";

}

void SVG_file_close(void){

	SVG_file << "</svg>\n</body>\n</html>\n";
	SVG_file.close();
}

void SVG_draw_circle(Circle *circ){

	Point ponto = circ->getPoint();
	SVG_file << "  <circle cx=\"" << ponto.GetX() << "\" cy=\"" << ponto.GetY()
			<< "\" r=\"" << circ->getRadius()
			<<"\" stroke=\"" << circ->getLineCollor() << "\" stroke-width=\"3\" fill=\""
			<< circ->getFillCollor() << "\" />\n";

}

void SVG_draw_line(Line *line){

	Point p1 = line->GetP1();
	Point p2 = line->GetP2();

	SVG_file << "  <line x1=\"" << p1.GetX() <<"\" y1=\"" << p1.GetY() << "\" x2=\""
			<< p2.GetX() <<"\" y2=\"" << p2.GetY() << "\" style=\"stroke:rgb("
			<< line->GetRed() << ',' << line->GetGreen() << ','
			<< line->GetBlue() << ");stroke-width:2\" />\n";

}

void draw_triangle(Point p1, Point p2, Point p3){

	Circle *c1, *c2, *c3;
	c1 = new Circle(p1.GetX(), p1.GetY(), 10);
	c2 = new Circle(p2.GetX(), p2.GetY(), 10);
	c3 = new Circle(p3.GetX(), p3.GetY(), 10);

	Line *l1, *l2, *l3;

	l1 = new Line(p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
	l2 = new Line(p2.GetX(), p2.GetY(), p3.GetX(), p3.GetY());
	l3 = new Line(p3.GetX(), p3.GetY(), p1.GetX(), p1.GetY());

	SVG_draw_circle(c1);
	SVG_draw_circle(c2);
	SVG_draw_circle(c3);

	SVG_draw_line(l1);
	SVG_draw_line(l2);
	SVG_draw_line(l3);

	delete c1;
	delete c2;
	delete c3;
	delete l1;
	delete l2;
	delete l3;
}

void draw_square(Point p1, double Area){

	Circle *c1, *c2, *c3, *c4;
	double a = std::sqrt(Area);

	c1 = new Circle(p1.GetX(), p1.GetY(), 5);
	c2 = new Circle(p1.GetX(), p1.GetY() + a, 5);
	c3 = new Circle(p1.GetX() + a, p1.GetY(), 5);
	c4 = new Circle(p1.GetX() + a, p1.GetY()+ a, 5);

	Line *l1, *l2, *l3, *l4;

	l1 = new Line(p1.GetX(), p1.GetY(), p1.GetX() + a, p1.GetY());
	l2 = new Line(p1.GetX() + a, p1.GetY(), p1.GetX() + a, p1.GetY() + a);
	l3 = new Line(p1.GetX() + a, p1.GetY() + a, p1.GetX(), p1.GetY() + a);
	l4 = new Line(p1.GetX(), p1.GetY() + a, p1.GetX(), p1.GetY());

	SVG_draw_circle(c1);
	SVG_draw_circle(c2);
	SVG_draw_circle(c3);
	SVG_draw_circle(c4);

	SVG_draw_line(l1);
	SVG_draw_line(l2);
	SVG_draw_line(l3);
	SVG_draw_line(l4);

	delete c1;
	delete c2;
	delete c3;
	delete c4;
	delete l1;
	delete l2;
	delete l3;
	delete l4;
}

void draw_stickman(Point p1, double height){

	double head, legs, body;
	head = legs = 0.25 * height;
	body = 0.5 * height;

	draw_square(p1,std::pow(head, 2)); // HEAD
	Circle *eyes[2], *mouth[2];
	eyes[0] = new Circle(p1.GetX() + 0.25 * head, p1.GetY() + 0.25 * head, 10, "green", "green");
	eyes[1] = new Circle(p1.GetX() + 0.75 * head, p1.GetY() + 0.25 * head, 10, "green", "green");
	mouth[0] = new Circle(p1.GetX() + 0.25 * head, p1.GetY() + 0.75 * head, 5, "red", "red");
	mouth[1] = new Circle(p1.GetX() + 0.75 * head, p1.GetY() + 0.75 * head, 5, "red", "red");


	Circle *hands[2], *feet[2], *body_start, *body_end;
	Line *body_l, *arms_l[2], *legs_l[2], *mouth_l;

	hands[0] = new Circle(p1.GetX(), p1.GetY()+ head + 0.75 * body, 10);
	hands[1] = new Circle(p1.GetX() + head, p1.GetY()+ head + 0.75 * body, 10);

	feet[0] = new Circle(p1.GetX(), p1.GetY() + head + body + legs, 10);
	feet[1] = new Circle(p1.GetX() + head, p1.GetY() + head + body + legs, 10);

	body_start = new Circle(p1.GetX() + head/2, p1.GetY() + head, 5);
	body_end = new Circle(p1.GetX() + head/2, p1.GetY() + head + body, 5);

	SVG_draw_circle(hands[0]);
	SVG_draw_circle(hands[1]);
	SVG_draw_circle(mouth[0]);
	SVG_draw_circle(mouth[1]);
	SVG_draw_circle(feet[0]);
	SVG_draw_circle(feet[1]);
	SVG_draw_circle(body_start);
	SVG_draw_circle(body_end);

	body_l = new Line(body_start->getPoint(),body_end->getPoint(), 0, 0, 0);
	legs_l[0] = new Line(body_end->getPoint(), feet[0]->getPoint(), 0, 0, 0);
	legs_l[1] = new Line(body_end->getPoint(), feet[1]->getPoint(), 0, 0, 0);
	arms_l[0] = new Line(body_start->getPoint(), hands[0]->getPoint(), 0, 0, 0);
	arms_l[1] = new Line(body_start->getPoint(), hands[1]->getPoint(), 0, 0, 0);
	mouth_l = new Line(mouth[0]->getPoint(), mouth[1]->getPoint(), 255, 0, 0);

	SVG_draw_line(body_l);
	SVG_draw_line(legs_l[0]);
	SVG_draw_line(legs_l[1]);
	SVG_draw_line(arms_l[0]);
	SVG_draw_line(arms_l[1]);
	SVG_draw_line(mouth_l);

	SVG_draw_circle(eyes[0]);
	SVG_draw_circle(eyes[1]);

	delete eyes[0];
	delete eyes[1];
	delete hands[0];
	delete hands[1];
	delete feet[0];
	delete feet[1];
	delete body_start;
	delete body_end;
	delete body_l;
	delete legs_l[0];
	delete legs_l[1];
	delete arms_l[0];
	delete arms_l[1];
	delete mouth[0];
	delete mouth[1];
	delete mouth_l;



}


int main() {

	SVG_file_open(1000, 1000);


	Point chao[2];
	chao[0] = Point(0, 900);
	chao[1] = Point(1000, 900);

	Line *chao_l;
	chao_l = new Line(chao[0], chao[1], 0, 255, 0);
	SVG_draw_line(chao_l);


	Point p1, p2, p3;	// TELHADO (CASA)
	p1 = Point(400, 390);
	p2 = Point(655, 250);
	p3 = Point(910, 390);
	draw_triangle(p1, p2, p3);

	Point p4;	// CASA
	p4 = Point(400, 390);
	draw_square(p4, 260100);

	Point p6;	// PORTA
	p6 = Point(500,700);
	draw_square(p6, 40000);

	Point p5;	// BONECO
	p5 = Point(30, 540);
	draw_stickman(p5, 350);



	SVG_file_close();

	delete chao_l;

}
