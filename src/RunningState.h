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
    void backgroundSetup(SimpleImage image);
    void stateAllBackgroundBuffer() override;
    void getNewMovableObject(void) override;
    void stateVirtPostDraw() override;
    GenericCharacter* m_oMainCharObject;
    EnemyCharacter* m_oEnemyObject;
    std::vector<DrawingSurface*> m_arrBackgroundSurfaces;
    int m_iLastUpdateBackground = 0;
    int m_iLastBackground = 0;
};