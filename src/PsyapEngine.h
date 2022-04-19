#pragma once
#include "BaseEngine.h"
#include "BaseState.h"

class PsyapDisplayableObject;

class PsyapEngine :
    public BaseEngine
{
public:
    //void SetState(BaseState* state);
    void virtSetupBackgroundBuffer();
    void virtMainLoopDoBeforeUpdate() override;
    void copyAllBackgroundBuffer() override;
    int virtInitialiseObjects();
    void virtMouseMoved(int iX, int iY);
    void virtKeyDown(int iKeyCode);
    BaseState* m_state;

private:
    

    //GenericCharacter* tempObj;
    PsyapDisplayableObject* m_rectObj1;
};

