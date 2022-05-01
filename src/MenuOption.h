#pragma once
#include "DisplayableObject.h"
#include "PsyapEngine.h"

class MenuOption :
    public DisplayableObject
{
public:
	MenuOption(PsyapEngine* pEngine, int iHeightOffSet, const char * sText);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	int m_iHeightOffSet;
	const char* m_sText;
	bool m_iSelected = false;
	std::vector<MenuOption*> m_arrMenuOptions;
};
