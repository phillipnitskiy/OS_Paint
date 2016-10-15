#include "stdafx.h"
#include "Text.h"


Text::Text(COLORREF color, COLORREF fillColor, int width)
{
	this->color = color;
	this->fillColor = fillColor;
	this->width = width;
}

void Text::EditShape(POINT x)
{
	if (points.empty())
	{
		points.push_back(x);
	}
}

void Text::Paint(HDC hdc)
{
	SetTextColor(hdc, color);
	SetBkColor(hdc, fillColor);

	HFONT hFont = CreateFont(width * 10, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Consolas"));
	SelectObject(hdc, hFont);
	
	TextOut(hdc, points.front().x, points.front().y, data.data(), data.size());
	
	DeleteObject(hFont);
}

void Text::AddText(TCHAR text)
{
	data += (TCHAR)text;
}

Text::~Text()
{
}
