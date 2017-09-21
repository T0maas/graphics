#include "graphics.h"
#include <fstream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int buffer;

void Canvas::Save(string filename){
	ofstream file;
	file.open(filename.c_str());

	file << "P6\n"<< width << " " << height << "\n255"  << "\n";
	file.close();

	file.open(filename.c_str(),ios::binary|ios::app);

	for (int h=0;h<height ;h++){
		for (int w=0;w<width ;w++){
			file << (char)(imageR[h][w]);
			file << (char)(imageG[h][w]);
			file << (char)(imageB[h][w]);
		}
	}

	file.close();
}

Loc::Loc(int _x, int _y){
	{
		X=_x;
		Y=_y;
	}
}

Color::Color(int _r, int _g, int _b){
	{
		R = _r;
		G = _g;
		B = _b;
	}
}

Circle::Circle(Loc loc, float _Radius, Color _color){
	{
		CircleRadius = _Radius;
		posX = loc.X;
		posY = loc.Y;
		CircleColor.R = _color.R;
		CircleColor.G = _color.G;
		CircleColor.B = _color.B;

	}

}

Canvas::Canvas(int x, int y, Color color){
	{
		height = y;
		width =x;
		imageR.resize(y);
		for (int i = 0; i < y; i++)
			imageR[i].resize(x);
		imageG.resize(y);
		for (int i = 0; i < y; i++)
			imageG[i].resize(x);
		imageB.resize(y);
		for (int i = 0; i < y; i++)
			imageB[i].resize(x);


		for (int h=0;h<y ;h++){
			for (int w=0;w<x ;w++){
				imageR[h][w] = color.R;
				imageG[h][w] = color.G;
				imageB[h][w] = color.B;
			}
		}

	}
}

Radius::Radius(Loc loc1,Loc loc2){
	xdiff = loc1.X - loc2.X;
	ydiff = loc1.Y - loc2.Y;
}

float Radius::get(){
	return (sqrt( pow(xdiff,2) + pow(ydiff,2)  ) );
}

void Canvas::AddObj(Circle circle){

	for (int h=0;h<height ;h++){
		for (int w=0;w<width ;w++){
			if (Radius(Loc(circle.posX,circle.posY),Loc(w,h)).get() <= circle.CircleRadius ){
				imageR[h][w] = circle.CircleColor.R;
				imageG[h][w] = circle.CircleColor.G;
				imageB[h][w] = circle.CircleColor.B;
			}
		}
	}
}

Rectangle::Rectangle(Loc locNW, Loc locSE, Color col){
	north=locNW.Y;
	west=locNW.X;
	south=locSE.Y;
	east=locSE.X;

	RectColor.R = col.R;
	RectColor.G = col.G;
	RectColor.B = col.B;

}

void Canvas::AddObj(Rectangle rectangle){
	for (int h=0;h<height ;h++){
		for (int w=0;w<width ;w++){
			if (h >= rectangle.north  && h <= rectangle.south && w >= rectangle.west && w <= rectangle.east  ){
				imageR[h][w] = rectangle.RectColor.R;
				imageG[h][w] = rectangle.RectColor.G;
				imageB[h][w] = rectangle.RectColor.B;
			}
		}
	}
}

Triangle::Triangle(Loc loc1, Loc loc2, Loc loc3,Color col) {
	P1.x = loc1.X;
	P1.y = loc1.Y;
	P2.x = loc2.X;
	P2.y = loc2.Y;
	P3.x = loc3.X;
	P3.y = loc3.Y;
	TriColor.R = col.R;
	TriColor.G = col.G;
	TriColor.B = col.B;
}

Line::Line(Loc loc1, Loc loc2, Color _color) {
	north = loc1.Y;
	south = loc2.Y;
	west = loc1.X;
	east = loc2.X;

	LineColor.R = _color.R;
	LineColor.G = _color.G;
	LineColor.B = _color.B;
}

void Canvas::AddObj(Triangle triangle) {
	for (int h=0;h<height ;h++){
		for (int w=0;w<width ;w++){
			if (isInside(triangle.P1.x, triangle.P1.y, triangle.P2.x, triangle.P2.y, triangle.P3.x, triangle.P3.y, w, h)){
				imageR[h][w] = triangle.TriColor.R;
				imageG[h][w] = triangle.TriColor.G;
				imageB[h][w] = triangle.TriColor.B;
			}
		}
	}
}

void Canvas::AddObj(Line line) {
	for (int h=0;h< height ;h++){
		for (int w=0;w< width ;w++){
			if (w >= line.west && w <=line.east && h >= line.north && h <= line.south ){
				if (Canvas::isOnLine(Loc(line.west,line.north),Loc(line.east,line.south),Loc(w,h)))
				{
					imageR[h][w] = line.LineColor.R;
					imageG[h][w] = line.LineColor.G;
					imageB[h][w] = line.LineColor.B;
				}
			}
		}
	}
}
float Canvas::area(int x1, int y1, int x2, int y2, int x3, int y3){
	return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

bool Canvas::isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
{
   /* Calculate area of triangle ABC */
   float A = area (x1, y1, x2, y2, x3, y3);

   /* Calculate area of triangle PBC */
   float A1 = area (x, y, x2, y2, x3, y3);

   /* Calculate area of triangle PAC */
   float A2 = area (x1, y1, x, y, x3, y3);

   /* Calculate area of triangle PAB */
   float A3 = area (x1, y1, x2, y2, x, y);

   /* Check if sum of A1, A2 and A3 is same as A */
   return (A == A1 + A2 + A3);
}

bool Canvas::isOnLine(Loc line1 ,Loc line2,Loc point)
{
	float y2 = line2.Y;
	float y1 = line1.Y;
	float x2 = line2.X;
	float x1 = line1.X;
	float x = point.X;
	float y = point.Y;

	float slope = (y2-y1)/(x2-x1);
	if (abs(slope * (x - x1) - y) < 1.1)
	    return true;
	else
	    return false;
}
