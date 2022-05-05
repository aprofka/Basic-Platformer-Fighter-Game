#include "header.h"

#include "PsyapDisplayableObject.h"

//Default constructor as it needs at least pEngine
PsyapDisplayableObject::PsyapDisplayableObject(PsyapEngine* pEngine) : DisplayableObject(pEngine) {
	m_iCurrentScreenX = 100; // Starting position on the screen
	m_iCurrentScreenY = 100;
	m_iDrawWidth = 50; // Width of drawing area
	m_iDrawHeight = 50; // Height of drawing area
	m_iColour = 0x00ffff; // Colour of the cursor/box
}

//Deals with what to draw on creation of the object
void PsyapDisplayableObject::virtDraw()
{
	getEngine() -> drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth,
		m_iCurrentScreenY + m_iDrawHeight,
		m_iColour);
	virtDrawStringsUnderneath();
}

/* Draw the string that moving objects should be drawn on top of */
void PsyapDisplayableObject::virtDrawStringsUnderneath()
{
	// Convert string to constant char to use it for drawing
	std::string sX = "Current X";
	sX.append(std::to_string(m_iCurrentScreenX));
	const char* pcX = sX.c_str();
	getEngine() -> drawForegroundString(500, 500, pcX, 0x000000, NULL);
}

void PsyapDisplayableObject::setPosition(int iX, int iY)
{
	m_iCurrentScreenX = iX;
	m_iCurrentScreenY = iY;
}

void PsyapDisplayableObject::setColour(int c)
{
	m_iColour = c;
}

int PsyapDisplayableObject::getColour()
{
	return m_iColour;
}

void PsyapDisplayableObject::virtDoUpdate(int iCurrentTime)
{
	this -> redrawDisplay();
}
