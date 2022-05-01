#pragma once
#include "GenericCharacter.h"

class EnemyCharacter :
    public GenericCharacter
{
public:
    EnemyCharacter(PsyapEngine* pEngine) : GenericCharacter(pEngine, "resources/EnemyCharacter/enemySpriteSheetNew.png", 713) {
        m_iDrawWidth = 50 * 3;
        m_iDrawHeight = 37 * 3;
        m_iMovementSpeed = 15;
        m_iTextureUpdateDelta = 125;
        m_iAttackDMG = 5;

        m_mSpritePhases["Idle"] = 3;
        m_mSpritePhases["Running"] = 5;
        m_mSpritePhases["Jumping"] = 1;
        m_mSpritePhases["Falling"] = 2;
        m_mSpritePhases["BasicAttack"] = 3;
        m_mSpritePhases["Defence"] = 4;

        m_iGroundLevel = 900;
        m_iHealthBarOffSetY = -75;
        m_iHealthBarOffSetX = -10;
    }

    void textureManager() override;
};