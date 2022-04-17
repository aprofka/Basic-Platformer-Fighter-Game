#pragma once
#include "BaseState.h"
class MainMenuState :
    public BaseState
{
public:
    MainMenuState(PsyapEngine* newEngine);
    void stateMainLoopDoBeforeUpdate() override;
    void stateAllBackgroundBuffer() override;
    int m_iOffset;
};

