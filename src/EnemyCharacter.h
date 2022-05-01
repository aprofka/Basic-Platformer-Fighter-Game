#pragma once
#include "GenericCharacter.h"

class EnemyCharacter :
    public GenericCharacter
{
public:
    EnemyCharacter(PsyapEngine* pEngine) : GenericCharacter(pEngine, "resources/MainCharacter/png/red/ResizedOne.png") {
        m_iDrawWidth = 56 * 3;
        m_iDrawHeight = 56 * 3;
        m_iMovementSpeed = 15;

        m_mSpritePhases["Idle"] = 5;
        m_mSpritePhases["Running"] = 7;
        m_mSpritePhases["Jumping"] = 3;
        m_mSpritePhases["Falling"] = 3;
        m_mSpritePhases["BasicAttack"] = 5;
        m_mSpritePhases["Defence"] = 1;
    }

    void textureManager() override;
};