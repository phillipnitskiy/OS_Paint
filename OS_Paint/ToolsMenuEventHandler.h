#include <windows.h>
#include "ToolsID.h"

void HandlingEventMenu(HINSTANCE, HWND, int, int *, COLORREF *, COLORREF *, int *);
HENHMETAFILE GetOpenningMetafile();
static LPWSTR currentOpeningFileName;
static HDC openingFileDc;
static ENHMETAHEADER openingMetafileHeader;

static HBITMAP openingFileBitMap;
static RECT rect;