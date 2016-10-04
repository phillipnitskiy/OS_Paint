#include "stdafx.h"
#include "HelpTools.h"

void CreateAboutBox(HWND hWnd)
{
	MessageBoxW(hWnd, L"OS_Paint Philip Lipnitskiy POIT BSUIR 2016", L"About", MB_ICONINFORMATION);
}