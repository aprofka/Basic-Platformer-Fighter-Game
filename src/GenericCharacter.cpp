#include "header.h"
#include "GenericCharacter.h"


//Default constructor as it needs at least pEngine
GenericCharacter::GenericCharacter(PsyapEngine* pEngine, std::string sSkinAddress) : DisplayableObject(pEngine) {
	m_pFlipperMapping = new PsyapImagePixelMapping(0.00,0.00,1.00,false);
	m_oSkinTile = ImageManager::loadImage(sSkinAddress, true);

	m_oMovement.setup(250, m_iGroundLevel, 250, m_iGroundLevel, pEngine -> getModifiedTime(), pEngine->getModifiedTime() + m_iMovementSpeed);
	m_oMovement.calculate(pEngine->getModifiedTime());
	m_iCurrentScreenX = m_oMovement.getX();
	m_iCurrentScreenY = m_oMovement.getY();
}

//Deals with what to draw on creation of the object
void GenericCharacter::virtDraw()
{
	m_oMovement.calculate(getEngine()->getModifiedTime());
	m_iCurrentScreenX = m_oMovement.getX();
	m_iCurrentScreenY = m_oMovement.getY();

	m_pFlipperMapping->setNewTexture(168.00,static_cast<double>(m_iSpriteFrameCount + m_iTextureOffSetX), static_cast<double>(m_iTextureOffSetY), m_bFlipped);
	m_oSkinTile.renderImageApplyingMapping(getEngine(), getEngine()->getForegroundSurface() , m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight, m_iDrawWidth, m_iDrawHeight, m_pFlipperMapping);

	//m_oSkinTile.renderImageWithMask(getEngine()->getForegroundSurface(), m_iTextureOffSetX, m_iTextureOffSetY,
	//	m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight, m_iDrawWidth, m_iDrawHeight);
}

void GenericCharacter::virtDoUpdate(int iCurrentTime)
{
	m_oMovement.calculate(getEngine()->getModifiedTime());
	m_iCurrentScreenX = m_oMovement.getX();
	m_iCurrentScreenY = m_oMovement.getY();

	//This will run the next animation only if the current one is done and if any are pending
	//If the pending ones would go bellow the ground level, they will be adjusted.
	if ((m_iCorrectionY != 0 || m_iCorrectionX != 0) && m_oMovement.hasMovementFinished(getEngine()->getModifiedTime())) {
		if (m_iCurrentScreenY + m_iCorrectionY > m_iGroundLevel) {
			m_iCorrectionY = m_iGroundLevel - m_iCurrentScreenY;
		}
		
		if (m_iCorrectionY < 0 && m_iCurrentScreenY == m_iGroundLevel) {
			m_iSpriteTextureState = TextureState::JUMPING;
		}
		else if (m_iCorrectionY == 0 && m_iCorrectionX != 0 && m_iSpriteTextureState != TextureState::RUNNING) {
			std::cout << "FELL RUNNING" << std::endl;
			m_iSpriteTextureState = TextureState::RUNNING;
		}
		else if (m_iCurrentScreenY < m_iGroundLevel - 200 && m_iSpriteTextureState != TextureState::FALLING) { // Jump height limit
			std::cout << "Height Limit" << std::endl;
			m_iCorrectionY = 5;
			m_iSpriteTextureState = TextureState::FALLING;
		}

		m_oMovement.setup(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iCorrectionX, m_iCurrentScreenY + m_iCorrectionY,
			getEngine()->getModifiedTime(), getEngine()->getModifiedTime() + m_iMovementSpeed);
	}
	else if (m_iCorrectionX == 0 && m_iCorrectionY == 0 
		&& m_iSpriteTextureState != TextureState::IDLE
		&& m_iSpriteTextureState != TextureState::ATTACKING
		&& m_iSpriteTextureState != TextureState::DEFENCE) { //Resets to idle animation after it lands from a jump
		std::cout << "FELL IDLE" << std::endl;
		m_iSpriteTextureState = TextureState::IDLE;
	}

	//Texture Animation
	textureManager();

	this->redrawDisplay();
}

void GenericCharacter::changeTexture(int iTextureOffSetY,int iTextureResetX ,std::string sTextureName, bool bRepeat) {
	//If a move needs to be executed once(like an attack), it will change to IDLE state.
	if (!bRepeat && m_mSpritePhases[sTextureName] == m_iSpriteFrameCount) {
		m_iSpriteTextureState = TextureState::IDLE;
		return;
	}
	
	int delta = getEngine()->getRawTime() - m_iLastSpriteChangeTime;
	if (delta < 100) {

	}
	else if (m_mSpritePhases[sTextureName] == m_iSpriteFrameCount || m_sLastMovement != sTextureName) {
		m_sLastMovement = sTextureName;
		m_iTextureOffSetX = iTextureResetX;
		m_iTextureOffSetY = iTextureOffSetY;
		m_iSpriteFrameCount = 0;
		m_iLastSpriteChangeTime = getEngine()->getRawTime();
	}
	else {
		m_iSpriteFrameCount++;
		m_iLastSpriteChangeTime = getEngine()->getRawTime();
	}
	//std::cout << m_iSpriteFrameCount << std::endl;
}
void GenericCharacter::textureManager() {
}