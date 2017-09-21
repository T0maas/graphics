#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
using namespace std;

class Loc {
public:
	int X,Y;
	Loc(int _x,int _y);
};

class Radius{
private:
	int xdiff,ydiff;

public:
	Radius(Loc loc1,Loc loc2);
	float get();
};

class Color{
public:
	int R,G,B;
	Color(int _r, int _g, int _b);
};

class Circle{
public:
	struct Colors{int R,G,B;} CircleColor;
	int CircleRadius,posX,posY;
	Circle(Loc loc, float _Radius, Color _color);

};

class Rectangle {
public:
	int north,west,south,east;
	struct Colors{int R,G,B;} RectColor;
	Rectangle(Loc locNW, Loc locSE, Color col);
};

class Triangle {
public:
	struct ps{int x,y;}P1,P2,P3;
	struct Colors{int R,G,B;} TriColor;
	Triangle(Loc loc1, Loc loc2, Loc loc3,Color col);
};

class Canvas{
	vector<vector<int> > imageR;
	vector<vector<int> > imageG;
	vector<vector<int> > imageB;

public:
	int width,height;
	Canvas(int x, int y, Color color);
	void Save(string filename);
	void AddObj(Circle circle);
	void AddObj(Rectangle rectangle);
	void AddObj(Triangle triangle);
	float area(int x1, int y1, int x2, int y2, int x3, int y3);
	bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y);

};





#endif
