#include "stdafx.h"
#include "HelpTools.h"
#include "ToolsMenuEventHandler.h"

void HandlingEventMenu(HWND hWnd, int id, int *shape)
{
	switch (id)
	{
	case ID_ABOUT: 
		{
			CreateAboutBox(hWnd);
		}
		break;
	case ID_COLOR:
		{

		}
		break;
	case ID_FILL:
		{

		}
		break;
	case ID_THICKNESS:
		{

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