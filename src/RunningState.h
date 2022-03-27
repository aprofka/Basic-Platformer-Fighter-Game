#pragma once
#include "PsyapEngine.h"
#include "BaseState.h"
#include "PlatformTileManager.h"
#include "RunningState.h"
#include "GenericCharacter.h"
#include "PlayableCharacter.h"


class RunningState :
    public BaseState
{
public:
    RunningState();
    RunningState(PsyapEngine* newEngine);
    void GetNewCharacter(void) override;
};