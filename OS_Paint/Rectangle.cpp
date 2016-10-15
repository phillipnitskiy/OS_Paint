#include "stdafx.h"
#include "Rectangle.h"


RectangleS::RectangleS(COLORREF color, COLORREF fillColor, int width)
{
	this->color = color;
	this->fillColor = fillColor;
	this->width = width;
}

void RectangleS::EditShape(POINT x)
{
	if (points.size() <= 2)
	{
		points.push_back(x);
	}
	else
	{
		points.pop_back();
		points.push_back(x);
	}
}

void RectangleS::Paint(HDC hdc)
{
	HPEN hpen = CreatePen(PS_SOLID, width, color);
	SelectObject(hdc, hpen);

	HBRUSH hbrush = CreateSolidBrush(fillColor);
	SelectObject(hdc, hbrush);

	if (points.size() >= 2)
	{
		Rectangle(hdc, points.front().x, points.front().y, points.back().x, points.back().y);
	}

	DeleteObject(hpen);
	DeleteObject(hbrush);
}

void RectangleS::AddText(TCHAR text)
{
}

RectangleS::~RectangleS()
{
}
