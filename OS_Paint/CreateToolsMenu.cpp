#include "stdafx.h"
#include "CreateToolsMenu.h"
#include "ToolsID.h"

HMENU CreateMainMenu()
{
	HMENU hMainMenu = CreateMenu();
	int i = 0;
	CreateMenuItem(hMainMenu, L"File", i++, 0, CreateFileMenu(), FALSE, MFT_STRING);
	CreateMenuItem(hMainMenu, L"Shape", i++, 0, CreateShapeMenu(), FALSE, MFT_STRING);
	CreateMenuItem(hMainMenu, L"Action", i++, 0, CreateActionMenu(), FALSE, MFT_STRING);
	CreateMenuItem(hMainMenu, L"Help", i++, 0, CreateHelpMenu(), FALSE, MFT_STRING);
	return hMainMenu;
}

BOOL CreateMenuItem(HMENU hMenu, LPWSTR str, UINT uIns, UINT uCom, HMENU hSubMenu, BOOL flag, UINT fType)
{
	MENUITEMINFO mii;
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mii.fType = fType;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = str;
	mii.cch = sizeof(str);
	mii.wID = uCom;
	mii.hSubMenu = hSubMenu;
	return InsertMenuItem(hMenu, uIns, flag, &mii);
}

HMENU CreateFileMenu() {
	HMENU hFileMenu = CreatePopupMenu();
	int i = 0;
	CreateMenuItem(hFileMenu, L"New", i++, ID_NEW, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hFileMenu, L"Load", i++, ID_LOAD, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hFileMenu, L"Save", i++, ID_SAVE, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hFileMenu, L"Print", i++, ID_PRINT, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hFileMenu, L"Exit", i++, ID_EXIT, NULL, FALSE, MFT_STRING);
	return hFileMenu;
}

HMENU CreateShapeMenu(){
	HMENU hShapeMenu = CreatePopupMenu();
	int i = 0;
	CreateMenuItem(hShapeMenu, L"Pen", i++, ID_PEN, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hShapeMenu, L"Line", i++, ID_LINE, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hShapeMenu, L"Polyline", i++, ID_POLYLINE, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hShapeMenu, L"Rectangle", i++, ID_RECTANGLE, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hShapeMenu, L"Ellipse", i++, ID_ELLIPSE, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hShapeMenu, L"Triangle", i++, ID_TRIANGLE, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hShapeMenu, L"Rhombus", i++, ID_RHOMBUS, NULL, FALSE, MFT_STRING);
	CreateMenuItem(hShapeMenu, L"Text", i++, ID_TEXT, NULL, FALSE, MFT_STRING);
	return hShapeMenu;
}

HMENU CreateActionMenu(){
	HMENU hActionMenu = CreatePopupMenu();
	int i = 0;
	CreateMenuItem(hActionMenu, L"New", i++, 0, NULL, FALSE, MFT_STRING);
	return hActionMenu;
}

HMENU CreateHelpMenu()
{
	HMENU hHelpMenu = CreatePopupMenu();
	int i = 0;
	CreateMenuItem(hHelpMenu, L"About", i++, ID_ABOUT, NULL, FALSE, MFT_STRING);
	return hHelpMenu;
}