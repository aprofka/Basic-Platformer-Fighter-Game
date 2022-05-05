#pragma once
#include "BaseEngine.h"
#include "BaseState.h"

class PsyapDisplayableObject;

class PsyapEngine :
    public BaseEngine
{
public:
    //void SetState(BaseState* state);
    ~PsyapEngine();
    void changeState(BaseState* newState);
    void virtSetupBackgroundBuffer();
    void virtMainLoopDoBeforeUpdate() override;
    void copyAllBackgroundBuffer() override;
    int virtInitialiseObjects();
    void virtPostDraw();
    void virtMouseMoved(int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
    void virtMouseWheel(int x, int y, int which, int timestamp) override;
    void setBackgroundSurface(DrawingSurface* pSurface);
    BaseState* m_state;

    bool m_firstTime = true;
    std::string m_sNickname;
};

