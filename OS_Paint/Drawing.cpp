#include "stdafx.h"
#include "Drawing.h"
#include <vector>

using namespace std;

vector<Shape*> shapes;

Shape* createShape(POINT point, COLORREF color, COLORREF fillColor, int width, int id);

void addShape(POINT point, int id, COLORREF color, COLORREF fillColor, int width)
{
	Shape* shape = createShape(point, color, fillColor, width, id);
	shapes.push_back(shape);
}

Shape* createShape(POINT point, COLORREF color, COLORREF fillColor, int width, int id)
{
	switch (id)
	{
	case ID_PEN:
		{
			Pen *pen = new Pen(color, width);
			pen->EditShape(point);
			return pen;
		}
		break;
	case ID_TEXT:
		{
			Text *text = new Text(color, fillColor, width);
			text->EditShape(point);
			return text;
		}
		break;
	case ID_LINE:
		{
			Line *line = new Line(color, width);
			line->EditShape(point);
			return line;
		}
	break;
	default:
		break;
	}
}

void mouseMove(POINT point)
{
	if (shapes.empty())
		return;

	shapes.back()->EditShape(point);
}

void keyPressed(TCHAR text)
{
	if (shapes.empty())
		return;

	shapes.back()->AddText(text);
}

void printShapes(HDC hdc)
{
	if (shapes.empty())
		return;

	int shapes_size = shapes.size();

	for (int i = 0; i < shapes_size; i++) {
		shapes[i]->Paint(hdc);
	}
}

void deleteLastShape()
{
	if (!shapes.empty()) 
		shapes.pop_back();
}

void clearShapes()
{
	if (!shapes.empty())
		shapes.clear();
}
