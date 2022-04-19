#pragma once
#include "DisplayableObject.h"
#include "PsyapEngine.h"

class MenuOption :
    public DisplayableObject
{
public:
	MenuOption(PsyapEngine* pEngine, int iHeightOffSet, const char * sText);
	void virtDraw();
	//void virtDrawStringsUnderneath();
	//void setColour(int c);
	//int getColour();
	void virtDoUpdate(int iCurrentTime);

	void virtKeyDown(int iKeyPressed);

	int m_iHeightOffSet;
	const char* m_sText;
	bool m_iSelected = false;
	std::vector<MenuOption*> m_arrMenuOptions;
};
