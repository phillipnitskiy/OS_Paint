#include "Shape.h"
#include "ToolsID.h"
#include "Pen.h"
#include "Text.h"
#include "Line.h"
#include "Rectangle.h"

void addShape(POINT, int, COLORREF, COLORREF, int);
void mouseMove(POINT);
void printShapes(HDC);
void keyPressed(TCHAR);
void deleteLastShape();
void clearShapes();
