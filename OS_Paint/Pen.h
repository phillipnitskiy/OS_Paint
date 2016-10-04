#pragma once
#include "Shape.h"
#include <vector>

using namespace std;

class Pen :
	public Shape
{
private:
	vector<POINT> points;
public:
	Pen();
	void EditShape(POINT x);
	void Paint(HDC hdc);
	~Pen();

};

