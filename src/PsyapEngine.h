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
    void virtSetupBackgroundBuffer();
    void virtMainLoopDoBeforeUpdate() override;
    void copyAllBackgroundBuffer() override;
    int virtInitialiseObjects();
    void virtPostDraw();
   //void virtMouseMoved(int iX, int iY);
    void virtKeyDown(int iKeyCode) override;
    void virtMouseWheel(int x, int y, int which, int timestamp) override;
    BaseState* m_state;

private:
    

    //GenericCharacter* tempObj;
    PsyapDisplayableObject* m_rectObj1;
};

