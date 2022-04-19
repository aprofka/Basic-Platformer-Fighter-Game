#pragma once
#include "BaseState.h"
#include "MenuOption.h"

class MainMenuState :
    public BaseState
{
public:
    MainMenuState(PsyapEngine* newEngine);
    void stateMainLoopDoBeforeUpdate() override;
    void stateAllBackgroundBuffer() override;
    void GetNewMovableObject(void) override;
    int m_iOffset;
    std::vector<MenuOption*> m_arrMenuOptions;
};

