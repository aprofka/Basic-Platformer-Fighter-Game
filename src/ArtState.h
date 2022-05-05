#pragma once
#include "BaseState.h"
#include "DisplayableObject.h"
#include "vector"
#include "SimpleImage.h"

#include "PsyapFilterPointClasses.h" 

class ArtState :
    public BaseState 
{
public:
    ArtState(PsyapEngine* newEngine);
    void stateMainLoopDoBeforeUpdate();
    void stateAllBackgroundBuffer();
    void keyControl(int iKeyPressed);
    void mouseWheel(int x, int y, int which, int timestamp) override;
    void mouseMoved(int iX, int iY) override;
    int m_iOffset;
    int m_iScrollingSpeed = 20;
    std::vector<DisplayableObject*> m_arrForegroundObjects;

    PsyapFilterPointsMain m_filterMain;
    SimpleImage rickRoll;
};

