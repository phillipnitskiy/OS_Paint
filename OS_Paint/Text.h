#pragma once
#include "Shape.h"
#include <vector>
#include <xstring>

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > String;

using namespace std;

class Text :
	public Shape
{
private:
	String data;
public:
	Text(COLORREF, COLORREF, int);
	void EditShape(POINT x)override;
	void Paint(HDC hdc)override;
	void AddText(TCHAR text)override;
	~Text();
};
