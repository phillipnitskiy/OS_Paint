#include "stdafx.h"
#include "Line.h"

Line::Line(COLORREF color, int width)
{
	this->color = color;
	this->width = width;
}

void Line::EditShape(POINT x)
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

void Line::Paint(HDC hdc)
{
	HPEN hpen = CreatePen(PS_SOLID, width, color);
	SelectObject(hdc, hpen);

	if (points.size() >= 2)
	{
		MoveToEx(hdc, points.front().x, points.front().y, NULL);
		LineTo(hdc, points.back().x, points.back().y);
	}	

	DeleteObject(hpen);

}

void Line::AddText(TCHAR text)
{

}

Line::~Line()
{
}
