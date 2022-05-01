#pragma once
#include "PsyapEngine.h"
#include "BaseState.h"
#include "PlatformTileManager.h"
#include "RunningState.h"
#include "GenericCharacter.h"
#include "PlayableCharacter.h"
#include "EnemyCharacter.h"


class RunningState :
    public BaseState
{
public:
    RunningState();
    ~RunningState();
    RunningState(PsyapEngine* newEngine);
    void stateAllBackgroundBuffer() override;
    void getNewMovableObject(void) override;
    GenericCharacter* m_oMainCharObject;
    EnemyCharacter* m_oEnemyObject;
};