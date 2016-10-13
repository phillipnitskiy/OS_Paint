#include "stdafx.h"
#include "Pen.h"

Pen::Pen()
{

}

void Pen::EditShape(POINT x)
{
	points.push_back(x);
}

void Pen::Paint(HDC hdc)
{
	int points_size = points.size();

	for (int i = 0; i < points_size; i++) {
		if (i > 1) {
			MoveToEx(hdc, points[i - 1].x, points[i - 1].y, NULL);
			LineTo(hdc, points[i].x, points[i].y);
		}
		else
		{
			SetPixelV(hdc, points[i].x, points[i].y, RGB(0,0,0));
		}

	}
	
}

void Pen::AddText(TCHAR text) 
{

}

Pen::~Pen()
{
}
