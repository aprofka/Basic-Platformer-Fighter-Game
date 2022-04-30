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
    void getNewMovableObject(void);
    void keyControl(int iKeyPressed);
    void mouseWheel(int x, int y, int which, int timestamp) override;
    int m_iOffset;
    std::vector<DisplayableObject*> m_arrForegroundObjects;

    PsyapFilterPointsScaling m_filterScaling;
    PsyapFilterPointsTranslation m_filterTranslation;
    SimpleImage rickRoll;
};

