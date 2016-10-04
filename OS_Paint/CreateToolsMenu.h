#include <windows.h>
#include "Resource.h"

HMENU CreateMainMenu();

HMENU CreateShapeMenu();
HMENU CreateActionMenu();
HMENU CreateFileMenu();
HMENU CreateHelpMenu();
BOOL CreateMenuItem(HMENU hMenu, LPWSTR str, UINT uIns, UINT uCom, HMENU hSubMenu, BOOL flag, UINT fType);