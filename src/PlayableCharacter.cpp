#include "header.h"
#include "PlayableCharacter.h"

void PlayableCharacter::textureManager() {
	int delta = getEngine()->getRawTime() - m_iLastSpriteChangeTime;
	if (delta > 75) {
		switch (m_iSpriteTextureState)
		{
		case TextureState::IDLE:
			changeTexture(0, 0, "Idle", true);
			break;
		case TextureState::RUNNING:
			changeTexture(2, 0, "Running", true);
			break;
		case TextureState::JUMPING:
			changeTexture(3, 2, "Jumping", true);
			break;
		case TextureState::FALLING:
			changeTexture(4, 1, "Falling", true);
			break;
		case TextureState::ATTACKING:
			m_iLastAttack = 0;
			changeTexture(1, 0, "BasicAttack", false);
			break;
		case TextureState::DEFENCE:
			changeTexture(10, 1, "Defence", true);
			break;
		case TextureState::DEAD:
			changeTexture(6, 0, "Death", false);
			break;
		}
	}
}

void PlayableCharacter::virtKeyDown(int iKeyPressed) {
	if (m_iSpriteTextureState != TextureState::DEAD) {
		if (iKeyPressed == SDLK_f) {
			if (m_iCurrentScreenY == m_iGroundLevel) {
				m_iSpriteTextureState = TextureState::ATTACKING;
			}
		}
		else if (iKeyPressed == SDLK_UP) {
			if (m_iCurrentScreenY == m_iGroundLevel) {
				m_iCorrectionY = -10;
			}
		}
		else if (iKeyPressed == SDLK_RIGHT) {
			m_iCorrectionX = 10;
			m_bFlipped = false;
		}
		else if (iKeyPressed == SDLK_LEFT) {
			m_iCorrectionX = -10;
			m_bFlipped = true;
		}
		else if (iKeyPressed == SDLK_d) {
			if (m_iCurrentScreenY == m_iGroundLevel) {
				m_iCorrectionX = 0;
				m_iSpriteTextureState = TextureState::DEFENCE;
			}
		}
	}
	else {
		m_iCorrectionX = 0;
	}
}


void PlayableCharacter::virtKeyUp(int iKeyPressed) {
	if (m_iSpriteTextureState != TextureState::DEAD) {
		int iDelta = getEngine()->getRawTime() - m_iLastKeyReleaseTime;
		if (iKeyPressed == SDLK_RIGHT || iKeyPressed == SDLK_LEFT) {
			m_iCorrectionX = 0;
		}
		m_iLastKeyReleaseTime = getEngine()->getRawTime();
	}
}

