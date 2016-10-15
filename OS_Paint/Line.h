#pragma once
#include "Shape.h"
#include <vector>

using namespace std;

class Line :
	public Shape
{
public:
	Line(COLORREF, int);
	void EditShape(POINT x)override;
	void Paint(HDC hdc)override;
	void AddText(TCHAR text)override;
	~Line();
};

