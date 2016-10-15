#pragma once
#include "Shape.h"
class RectangleS :
	public Shape
{
public:
	RectangleS(COLORREF, COLORREF, int);
	void EditShape(POINT x)override;
	void Paint(HDC hdc)override;
	void AddText(TCHAR text)override;
	~RectangleS();
};

