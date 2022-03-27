#pragma once
#include "DisplayableObject.h"
#include "PsyapEngine.h"

class PsyapDisplayableObject :
	public DisplayableObject
{
public:
	PsyapDisplayableObject(PsyapEngine* pEngine);
	void virtDraw();
	void virtDrawStringsUnderneath();
	void setPosition(int iX, int iY);
	void setColour(int c);
	int getColour();
	void virtDoUpdate(int iCurrentTime);
};