#include "header.h"
#include "MenuOption.h"

//Default constructor as it needs at least pEngine
MenuOption::MenuOption(PsyapEngine* pEngine, int iHeightOffSet, const char * sText) : DisplayableObject(pEngine) {
	m_pEngine = pEngine;
	m_iHeightOffSet = iHeightOffSet;
	m_sText = sText;
}

//Deals with what to draw on creation of the object
void MenuOption::virtDraw()
{
	getEngine()->drawForegroundString((getEngine()->getWindowWidth() / 2) - 60, (getEngine()->getWindowHeight() / 2) + m_iHeightOffSet, m_sText, 0xffffff, getEngine()->getFont("Cornerstone Regular.ttf", 60));
	if (m_iSelected) {
		getEngine()->drawForegroundString((getEngine()->getWindowWidth() / 2) - 62, (getEngine()->getWindowHeight() / 2) + m_iHeightOffSet, m_sText, 0xf57e1d, getEngine()->getFont("Cornerstone Regular.ttf", 60));
	}
}

void MenuOption::virtDoUpdate(int iCurrentTime)
{
	this->redrawDisplay();
}