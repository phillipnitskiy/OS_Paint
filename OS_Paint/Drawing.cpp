#include "stdafx.h"
#include "Drawing.h"
#include <vector>

using namespace std;

vector<Shape*> shapes;

Shape* createShape(POINT point, int id);

void addShape(POINT point, int id)
{
	Shape* shape = createShape(point, id);
	shapes.push_back(shape);
}

Shape* createShape(POINT point, int id)
{
	switch (id)
	{
	case ID_PEN:
		{
			Pen *pen = new Pen();
			pen->EditShape(point);
			return pen;
		}
		break;
	case ID_TEXT:
		{
			Text *text = new Text();
			text->EditShape(point);
			return text;
		}
		break;
	default:
		break;
	}
}

void mouseMove(POINT point)
{
	shapes.back()->EditShape(point);
}

void keyPressed(TCHAR text)
{
	shapes.back()->AddText(text);
}

void printShapes(HDC hdc)
{
	int shapes_size = shapes.size();

	for (int i = 0; i < shapes_size; i++) {
		shapes[i]->Paint(hdc);
	}
}