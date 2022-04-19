#include "header.h"
#include "MenuOption.h"

//Default constructor as it needs at least pEngine
MenuOption::MenuOption(PsyapEngine* pEngine, int iHeightOffSet, const char * sText) : DisplayableObject(pEngine) {
	//m_iCurrentScreenX = 100; // Starting position on the screen
	//m_iCurrentScreenY = 100;
	//m_iDrawWidth = 95; // Width of drawing area
	//m_iDrawHeight = 95; // Height of drawing area
	//m_iColour = 0x00ff00; // Colour of the cursor/box
	m_pEngine = pEngine;
	m_iHeightOffSet = iHeightOffSet;
	m_sText = sText;
}

//Deals with what to draw on creation of the object
void MenuOption::virtDraw()
{
	getEngine()->drawForegroundString((getEngine()->getWindowWidth() / 2) - 60, (getEngine()->getWindowHeight() / 2) + m_iHeightOffSet, m_sText, 0x000000, getEngine()->getFont("Cornerstone Regular.ttf", 60));
	if (m_iSelected) {
		getEngine()->drawForegroundString((getEngine()->getWindowWidth() / 2) - 54, (getEngine()->getWindowHeight() / 2) + m_iHeightOffSet, m_sText, 0x55FFFF, getEngine()->getFont("Cornerstone Regular.ttf", 58));
	}
}

void MenuOption::setPosition(int iX, int iY)
{
	m_iCurrentScreenX = iX;
	m_iCurrentScreenY = iY;
}

void MenuOption::setColour(int c)
{
	m_iColour = c;
}

int MenuOption::getColour()
{
	return m_iColour;
}

void MenuOption::virtDoUpdate(int iCurrentTime)
{
	this->redrawDisplay();
}