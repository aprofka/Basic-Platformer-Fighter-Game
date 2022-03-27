#pragma once
#include "DisplayableObject.h"
#include "PsyapEngine.h"

class PsyapAutoObject :
    public DisplayableObject
{
public:
    PsyapAutoObject(PsyapEngine* pEngine);
    void virtDraw();
    void virtDoUpdate(int iCurrentTime);

private:
	PsyapEngine* m_pMainEngine;
    int m_prevX = -1;
    int m_prevY = -1;
    int m_iColourT;
};

