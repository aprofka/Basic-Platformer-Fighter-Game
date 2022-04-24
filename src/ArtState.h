#pragma once
#include "BaseState.h"
#include "DisplayableObject.h"
#include "vector"

class ArtState :
    public BaseState
{
public:
    ArtState(PsyapEngine* newEngine);
    void stateMainLoopDoBeforeUpdate();
    void stateAllBackgroundBuffer();
    void getNewMovableObject(void);
    void keyControl(int iKeyPressed);
    int m_iOffset;
    std::vector<DisplayableObject*> m_arrForegroundObjects;
};

