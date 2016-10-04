#pragma once
class Shape
{
public:
	Shape();
	virtual void Paint(HDC hdc);
	virtual void EditShape(POINT);
	~Shape();
};

