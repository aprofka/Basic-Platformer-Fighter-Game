#pragma once
#include "BaseState.h"

class HighscoreState :
    public BaseState
{
public:
    HighscoreState(PsyapEngine* newEngine);
    void stateMainLoopDoBeforeUpdate() override;
    void stateAllBackgroundBuffer() override;
    void keyControl(int iKeyPressed) override;
    void stateVirtPostDraw() override;
};