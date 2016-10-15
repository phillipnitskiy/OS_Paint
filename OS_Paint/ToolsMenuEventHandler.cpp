#include "stdafx.h"
#include "HelpTools.h"
#include "ToolsMenuEventHandler.h"
#include <commdlg.h>
#include "Drawing.h"

#include <fstream> 
#include <vector> 
#include <string>

static CHOOSECOLOR ccs;
static COLORREF acrCustClr[16];  
bool initialization = true;

static OPENFILENAME file;
static TCHAR name[256] = _T(""), fullpath[256] = _T("");
static HENHMETAFILE openingMetaFile;
BOOL SavePicture(LPWSTR fullPath, HWND hWnd);
void LoadPicture(LPWSTR fullPath, HWND hWnd);
//void SetRect();

void HandlingEventMenu(HINSTANCE hInst, HWND hWnd, int id, int *shape, COLORREF *color, COLORREF *fillColor, int *width)
{
	if (initialization)
	{
		ccs.lStructSize = sizeof(CHOOSECOLOR);
		ccs.hwndOwner = hWnd;
		ccs.rgbResult = *color;
		ccs.Flags = CC_RGBINIT | CC_FULLOPEN;
		ccs.lpCustColors = (LPDWORD)acrCustClr;

		file.lStructSize = sizeof(OPENFILENAME);
		file.hInstance = hInst;
		file.lpstrFilter = _T("emf\0*.emf");
		file.lpstrFile = name;
		file.nMaxFile = 256;
		file.lpstrInitialDir = _T(".\\");
		file.lpstrDefExt = _T("emf");
	}

	switch (id)
	{
	case ID_ABOUT: 
		{
			CreateAboutBox(hWnd);
		}
		break;
	case ID_SAVE:
		{
			file.lpstrTitle = _T("Открыть файл для записи");
			file.Flags = OFN_NOTESTFILECREATE; 
			if (!GetSaveFileName(&file))
				return; 

			SavePicture(file.lpstrFile, hWnd);
		}
		break;
	case ID_LOAD:
		{
			file.lpstrTitle = _T("Открыть файл для чтения"); 
			file.Flags = OFN_HIDEREADONLY;    
			if (!GetOpenFileName(&file)) 
				return;  

			LoadPicture(file.lpstrFile, hWnd);
		}
		break;
	case ID_PRINT:
		{

		}
		break;
	case ID_CANCEL:
		{
			deleteLastShape();
		}
		break;
	case ID_COLOR:
		{
			ccs.rgbResult = *color;

			if (ChooseColor(&ccs)) 
			{ 
				*color = ccs.rgbResult;
			}
		}
		break;
	case ID_FILL:
		{
			ccs.rgbResult = *fillColor;

			if (ChooseColor(&ccs))
			{
				*fillColor = ccs.rgbResult;
			}
		}
		break;
	case ID_WIDTH_1:
		{
			*width = 1;
		}
		break;
	case ID_WIDTH_2:
		{
			*width = 2;
		}
	break;
	case ID_WIDTH_3:
		{
			*width = 3;
		}
	break;
	case ID_WIDTH_4:
		{
			*width = 4;
		}
	break;
	case ID_WIDTH_5:
		{
			*width = 5;
		}
	break;
	case ID_EXIT: 
		{
			PostQuitMessage(0);
		}
		break;
	default: 
		*shape = id;
	}
}

HENHMETAFILE GetOpenningMetafile()
{
	return openingMetaFile;
}

BOOL SavePicture(LPWSTR fullPath, HWND hWnd)
{

//	if (lstrcmp(fullPath, currentOpeningFileName) == 0)
	//{
		//throw TEXT("File is opening now");
		//return FALSE;
//	}

	HENHMETAFILE metafiele;
	int iWidthMM, iHeightMM, iWidthPels, iHeightPels;
	HDC hdcRef = GetDC(hWnd);

	iWidthMM = GetDeviceCaps(hdcRef, HORZSIZE);
	iHeightMM = GetDeviceCaps(hdcRef, VERTSIZE);
	iWidthPels = GetDeviceCaps(hdcRef, HORZRES);
	iHeightPels = GetDeviceCaps(hdcRef, VERTRES);

	RECT rect;
	RECT rect2;
	GetClientRect(hWnd, &rect);
	GetClientRect(hWnd, &rect2);
	// Convert client coordinates to .01-mm units.
	// Use iWidthMM, iWidthPels, iHeightMM, and
	// iHeightPels to determine the number of
	// .01-millimeter units per pixel in the x-
	// and y-directions.

	rect.left = (rect.left * iWidthMM * 100) / iWidthPels;
	rect.top = (rect.top * iHeightMM * 100) / iHeightPels;
	rect.right = (rect.right * iWidthMM * 100) / iWidthPels;
	rect.bottom = (rect.bottom * iHeightMM * 100) / iHeightPels;

	//fullPath[1] = "h";
	try
	{
		HDC fileDc = CreateEnhMetaFile(hdcRef, fullPath, &rect, NULL);
		if (openingMetaFile != NULL)
			PlayEnhMetaFile(fileDc, openingMetaFile, &rect2);

	//	drawingLogic->DrawingCode(fileDc);

		printShapes(fileDc);

		metafiele = CloseEnhMetaFile(fileDc);
		DeleteEnhMetaFile(metafiele);

	}
	catch (std::exception e)
	{
		throw TEXT("Error writing to file");
		return FALSE;
	}

	return TRUE;
}

void LoadPicture(LPWSTR fullPath, HWND hWnd)
{
	//drawingLogic->GetShapesList()->clear();

	clearShapes();

	if (openingMetaFile != NULL)
		DeleteEnhMetaFile(openingMetaFile);

	openingMetaFile = GetEnhMetaFile(fullPath);
	currentOpeningFileName = fullPath;

	//shapeListChanged = TRUE;
	InvalidateRect(hWnd, 0, 1);
}

//BOOL PrintPicture(LPWSTR(*getFileName)())
//{
//
//	HENHMETAFILE metafiele;
//	int iWidthMM, iHeightMM, iWidthPels, iHeightPels;
//	HDC hdcRef = GetDC(componentHandler);
//
//	iWidthMM = GetDeviceCaps(hdcRef, HORZSIZE);
//	iHeightMM = GetDeviceCaps(hdcRef, VERTSIZE);
//	iWidthPels = GetDeviceCaps(hdcRef, HORZRES);
//	iHeightPels = GetDeviceCaps(hdcRef, VERTRES);
//
//	RECT rect;
//
//	//GetClientRect(componentHandler, &rect);
//
//	Shape * shape = drawingLogic->GetLastShape();
//	Shape* rectangle = new RectangleShape();
//	if (lstrcmp(shape->GetShapeName(), rectangle->GetShapeName()) != 0)
//	{
//		delete rectangle;
//		return FALSE;
//	}
//	delete rectangle;
//
//	rect.left = (shape->points)[0]->x;
//	rect.top = (shape->points)[0]->y;
//	rect.right = (shape->points)[1]->x;
//	rect.bottom = (shape->points)[1]->y;
//
//
//	// Convert client coordinates to .01-mm units.
//	// Use iWidthMM, iWidthPels, iHeightMM, and
//	// iHeightPels to determine the number of
//	// .01-millimeter units per pixel in the x-
//	// and y-directions.
//
//	rect.left = (rect.left * iWidthMM * 100) / iWidthPels;
//	rect.top = (rect.top * iHeightMM * 100) / iHeightPels;
//	rect.right = (rect.right * iWidthMM * 100) / iWidthPels;
//	rect.bottom = (rect.bottom * iHeightMM * 100) / iHeightPels;
//
//	//fullPath[1] = "h";
//	try
//	{
//		HDC fileDc = CreateEnhMetaFile(hdcRef, getFileName(), &rect, NULL);
//		if (openingMetaFile != NULL)
//			PlayEnhMetaFile(fileDc, openingMetaFile, &DrawingPanel::rect);
//
//		drawingLogic->DeleteLastShape();
//		drawingLogic->DrawingCode(fileDc);
//
//		metafiele = CloseEnhMetaFile(fileDc);
//		DeleteEnhMetaFile(metafiele);
//
//	}
//	catch (std::exception e)
//	{
//		throw TEXT("Error writing to file");
//		return FALSE;
//	}
//
//	return TRUE;
//}
