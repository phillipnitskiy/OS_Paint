#include "stdafx.h"
#include "Pen.h"

Pen::Pen(COLORREF color, int width)
{
	this->color = color;
	this->width = width;
}

void Pen::EditShape(POINT x)
{
	points.push_back(x);
}

void Pen::Paint(HDC hdc)
{
	HPEN hpen = CreatePen(PS_SOLID, width, color); 
	SelectObject(hdc, hpen);

	int points_size = points.size();

	for (int i = 0; i < points_size; i++) {
		if (i > 1) {
			MoveToEx(hdc, points[i - 1].x, points[i - 1].y, NULL);
			LineTo(hdc, points[i].x, points[i].y);
		}
		else
		{
			SetPixelV(hdc, points[i].x, points[i].y, color);
		}

	}

	DeleteObject(hpen);
	
}

void Pen::AddText(TCHAR text) 
{

}

Pen::~Pen()
{
}
