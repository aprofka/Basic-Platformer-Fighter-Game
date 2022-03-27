#pragma once
#include "BaseEngine.h"
#include "BaseState.h"

class PsyapDisplayableObject;

class PsyapEngine :
    public BaseEngine
{
public:
    void SetState(BaseState* state);
    void virtSetupBackgroundBuffer();
    int virtInitialiseObjects();
    void virtMouseMoved(int iX, int iY);
    void virtKeyDown(int iKeyCode);

private:
    BaseState* m_state;

    //GenericCharacter* tempObj;
    PsyapDisplayableObject* m_rectObj1;
};

