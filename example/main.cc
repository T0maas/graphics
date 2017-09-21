/*
 * main.cc
 *
 *  Created on: 21. 9. 2017
 *      Author: tom
 */
#include "graphics.h"

int main() {
	Color LightYellow(255,255,127);
	Color Blue(0,0,255);

	Canvas blank(640, 480, LightYellow);
	Triangle t1(Loc(10,10), Loc(200, 30),Loc(50, 100),Color(255,0,0));
	Circle c1(Loc(200,200), 70, Blue);
	Rectangle r1(Loc(300,80), Loc(500,200), Color(0,255,0));

	blank.AddObj(t1);
	blank.AddObj(c1);
	blank.AddObj(r1);
	blank.Save("image.ppm");
}

