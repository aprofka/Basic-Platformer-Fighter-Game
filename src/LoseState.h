#pragma once
#include "BaseState.h"
#include "MenuOption.h"

class LoseState :
    public BaseState
{
public:
    LoseState(PsyapEngine* newEngine);
    ~LoseState() override;
    void stateAllBackgroundBuffer() override;
    void stateMainLoopDoBeforeUpdate() override;
    void getNewMovableObject(void) override;
    void keyControl(int iKeyPressed) override;
    void stateVirtPostDraw() override;
    int m_iOffset;
    std::vector<MenuOption*> m_arrMenuOptions;
    bool m_bFirstTimeLoad = false;

    std::string m_sUsername;
};

