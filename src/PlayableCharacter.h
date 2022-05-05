#pragma once
#include "GenericCharacter.h"


class PlayableCharacter :
    public GenericCharacter
{
public:
    PlayableCharacter(PsyapEngine* pEngine, int startPos, int health, int score) : GenericCharacter(pEngine, "resources/MainCharacter/png/red/ResizedOne2.png", 700, startPos, health) {
        m_iDrawWidth = 56*3;
        m_iDrawHeight = 56*3;
        m_iMovementSpeed = 15;
        m_iTextureUpdateDelta = 100;
        m_iAttackDMG = 20;

        m_mSpritePhases["Idle"] = 5;
        m_mSpritePhases["Running"] = 7;
        m_mSpritePhases["Jumping"] = 3;
        m_mSpritePhases["Falling"] = 3;
        m_mSpritePhases["BasicAttack"] = 5;
        m_mSpritePhases["Defence"] = 1; 
        m_mSpritePhases["Death"] = 7;

        m_iCurrentPoints = score;
        m_iHealthBarOffSetY = 0;
        m_iHealthBarOffSetX = 20;
    }

    void textureManager() override;

    void virtKeyDown(int iKeyPressed) override;
    void virtKeyUp(int iKeyPressed) override;
    int m_iKeyDelta = 0;
    int m_iLastKeyPressed = 0;
};

