#include "header.h"
#include "PlayableCharacter.h"


void PlayableCharacter::virtKeyDown(int iKeyPressed) {


	if (iKeyPressed == SDLK_f) {
		std::cout << "Pre-Up " << std::endl;
		if (m_iCurrentScreenY == m_iGroundLevel) {
			std::cout << "Basic Attack" << std::endl;
			m_iSpriteTextureState = TextureState::ATTACKING;
		}
	}
	else if (iKeyPressed == SDLK_UP) {
		std::cout << "Pre-Up " << std::endl;
		if (m_iCurrentScreenY == m_iGroundLevel) {
			std::cout << "Straight Up " << std::endl;
			m_iCorrectionY = -10;
		} 
	}
	else if (iKeyPressed == SDLK_RIGHT) {
			std::cout << "Right" << std::endl;
			m_iCorrectionX = 10;
			m_bFlipped = false;
	}
	else if (iKeyPressed == SDLK_LEFT) {
		std::cout << "Left " << std::endl;
		m_iCorrectionX = -10;
		m_bFlipped = true;
	}
}


void PlayableCharacter::virtKeyUp(int iKeyPressed) {
	int iDelta = getEngine()->getRawTime() - m_iLastKeyReleaseTime;
	if (iKeyPressed == SDLK_RIGHT || iKeyPressed == SDLK_LEFT) {
		std::cout << "X Reset " << std::endl;
		m_iCorrectionX = 0;
	}
	m_iLastKeyReleaseTime = getEngine()->getRawTime();
}