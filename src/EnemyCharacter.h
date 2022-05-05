#pragma once
#include "GenericCharacter.h"

class EnemyCharacter :
    public GenericCharacter
{
public:
    EnemyCharacter(PsyapEngine* pEngine, int startPos, int health) : GenericCharacter(pEngine, "resources/EnemyCharacter/slimeSheet.png", 700, startPos, health) {
        m_iDrawWidth = 32 * 3;
        m_iDrawHeight = 25 * 3;
        m_iMovementSpeed = 15;
        m_iTextureUpdateDelta = 125;
        m_iAttackDMG = 10;

        m_mSpritePhases["Idle"] = 3;
        m_mSpritePhases["Running"] = 3;
        m_mSpritePhases["BasicAttack"] = 4;
        m_mSpritePhases["Death"] = 4;

        m_iHealthBarOffSetY = -75;
        m_iHealthBarOffSetX = -10;
    }

    void textureManager() override;
    void aiControl();
};