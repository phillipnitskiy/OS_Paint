#pragma once
#include "Shape.h"
#include <vector>

using namespace std;

class Pen :
	public Shape
{
public:
	Pen();
	void EditShape(POINT x)override;
	void Paint(HDC hdc)override;
	void AddText(TCHAR text)override;
	~Pen();

};

