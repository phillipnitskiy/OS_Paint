#pragma once
#include <vector>

using namespace std;

class Shape
{
protected:
	vector<POINT> points;
public:
	Shape();
	virtual void Paint(HDC hdc) = 0;
	virtual void EditShape(POINT) = 0;
	virtual void AddText(TCHAR) = 0;
	~Shape();
};

