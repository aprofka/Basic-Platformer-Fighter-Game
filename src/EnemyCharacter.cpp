#include "header.h"
#include "EnemyCharacter.h"

void EnemyCharacter::textureManager() {
	int delta = getEngine()->getRawTime() - m_iLastSpriteChangeTime;
	if (delta > 75) {
		aiControl();
		switch (m_iSpriteTextureState)
		{
		case TextureState::IDLE:
			changeTexture(0, 0, "Idle", true);
			break;
		case TextureState::RUNNING:
			changeTexture(0, 4, "Running", true);
			break;
		case TextureState::ATTACKING:
			changeTexture(1, 0, "BasicAttack", true);
			break;
		case TextureState::DEAD:
			changeTexture(2, 0, "Death", false);
			break;
		}
	}
}

void EnemyCharacter::aiControl() {
	if(m_iSpriteTextureState != TextureState::DEAD){
		if (m_bCollision) {
			m_iCorrectionX = 0;
			m_iSpriteTextureState = TextureState::ATTACKING;
		}
		else if (getEngine()->getDisplayableObject(0)->getXCentre() > m_iCurrentScreenX) {
			m_iCorrectionX = +2;
			m_bFlipped = true;
		}
		else if (getEngine()->getDisplayableObject(0)->getXCentre() < m_iCurrentScreenX) {
			m_iCorrectionX = -2;
			m_bFlipped = false;
		}
		else {
			m_iCorrectionX = 0;
		}
	}
}