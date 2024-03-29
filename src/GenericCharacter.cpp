#include "header.h"
#include "GenericCharacter.h"

//Default constructor as it needs at least pEngine
GenericCharacter::GenericCharacter(PsyapEngine* pEngine, std::string sSkinAddress,int iFloorLevel, int startX, int health) : DisplayableObject(pEngine) {
	m_pFlipperMapping = new PsyapImagePixelMapping(0.00,0.00,0.00,1.00,false);
	m_oSkinTile = ImageManager::loadImage(sSkinAddress, true);

	m_iGroundLevel = iFloorLevel;
	m_oMovement.setup(startX, m_iGroundLevel, startX, m_iGroundLevel, pEngine -> getModifiedTime(), pEngine->getModifiedTime() + m_iMovementSpeed);
	m_oMovement.calculate(pEngine->getModifiedTime());
	m_iCurrentScreenX = m_oMovement.getX();
	m_iCurrentScreenY = m_oMovement.getY();
	m_pCurrentEngine = pEngine;
	m_iHealth = health;

	m_oColiDetection = new PsyapCollisionDetection();
}

GenericCharacter::~GenericCharacter()
{
	delete m_pFlipperMapping;
	delete m_oColiDetection;
}

//Deals with what to draw on creation of the object
void GenericCharacter::virtDraw()
{
	m_oMovement.calculate(getEngine()->getModifiedTime());
	m_iCurrentScreenX = m_oMovement.getX();
	m_iCurrentScreenY = m_oMovement.getY();

	m_pFlipperMapping->setNewTexture(m_iDrawWidth,m_iDrawHeight,static_cast<double>(m_iSpriteFrameCount + m_iTextureOffSetX), static_cast<double>(m_iTextureOffSetY), m_bFlipped);
	m_oSkinTile.renderImageApplyingMapping(getEngine(), getEngine()->getForegroundSurface() , m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight, m_iDrawWidth, m_iDrawHeight, m_pFlipperMapping);

	int iBarStartX = m_iCurrentScreenX + 25 + m_iHealthBarOffSetX;
	int iBarStartY = m_iCurrentScreenY - m_iDrawHeight + 25 + m_iHealthBarOffSetY;
	getEngine()->drawForegroundRectangle(iBarStartX, iBarStartY, iBarStartX + 100, iBarStartY + 10, 0xff0000);
	getEngine()->drawForegroundRectangle(iBarStartX, iBarStartY, iBarStartX + m_iHealth, iBarStartY + 10, 0x00ff00);
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
			m_iSpriteTextureState = TextureState::RUNNING;
		}
		else if (m_iCurrentScreenY < m_iGroundLevel - 200 && m_iSpriteTextureState != TextureState::FALLING) { // Jump height limit
			m_iCorrectionY = 5;
			m_iSpriteTextureState = TextureState::FALLING;
		}

		m_oMovement.setup(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iCorrectionX, m_iCurrentScreenY + m_iCorrectionY,
			getEngine()->getModifiedTime(), getEngine()->getModifiedTime() + m_iMovementSpeed);
	}
	else if (m_iCorrectionX == 0 && m_iCorrectionY == 0 
		&& m_iSpriteTextureState != TextureState::IDLE
		&& m_iSpriteTextureState != TextureState::ATTACKING
		&& m_iSpriteTextureState != TextureState::DEFENCE
		&& m_iSpriteTextureState != TextureState::DEAD) { //Resets to idle animation after it lands from a jump
		m_iSpriteTextureState = TextureState::IDLE;
	}
	else if (m_iHealth == 0) {
		m_iSpriteTextureState = TextureState::DEAD;
	}
	collisionDetection();

	//Texture Animation
	textureManager();

	this->redrawDisplay();
}

void GenericCharacter::changeTexture(int iTextureOffSetY,int iTextureResetX ,std::string sTextureName, bool bRepeat) {
	//If a move needs to be executed once(like an attack), it will change to IDLE state.
	if (!bRepeat && m_mSpritePhases[sTextureName] == m_iSpriteFrameCount) {
		if (m_iSpriteTextureState != TextureState::DEAD) {
			m_iSpriteTextureState = TextureState::IDLE;
		}
		else {
			m_bDelete = true;
		}
		return;
	}
	
	int delta = getEngine()->getRawTime() - m_iLastSpriteChangeTime;
	int attackDelta = getEngine()->getModifiedTime() - m_iLastAttack;

	int offSett = 0;
	if (m_bFlipped && m_iSpriteTextureState == TextureState::DEFENCE) {
		offSett = 2;
	}

	if (delta < m_iTextureUpdateDelta) {

	}
	else if (m_mSpritePhases[sTextureName] == m_iSpriteFrameCount || m_sLastMovement != sTextureName) {
		m_sLastMovement = sTextureName;
		m_iTextureOffSetX = iTextureResetX + offSett;
		m_iTextureOffSetY = iTextureOffSetY;
		m_iSpriteFrameCount = 0;
		m_iLastSpriteChangeTime = getEngine()->getRawTime();
		if (m_iSpriteTextureState == TextureState::ATTACKING && attackDelta > 1000) {
			m_bCanAttack = true;	
		}
	}
	else if(attackDelta > 1000 || m_iSpriteTextureState != TextureState::ATTACKING){
		m_iSpriteFrameCount++;
		m_iLastSpriteChangeTime = getEngine()->getRawTime();
		if (m_iSpriteTextureState == TextureState::ATTACKING) {
			m_iLastAttack = getEngine()->getModifiedTime();
		}
	}
}
void GenericCharacter::textureManager() {
}

void GenericCharacter::collisionDetection() {
	//Collision detection
	GenericCharacter* pObject;
	for (int iObjectId = 0;
		(pObject = dynamic_cast<GenericCharacter*>(getEngine()->getDisplayableObject(iObjectId))) != NULL; iObjectId++)
	{
		if (pObject == this) // This is us, skip it
			continue;
		if (pObject == nullptr) // Object does not exist, skip it
			continue;		// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19

		if (m_oColiDetection->checkRectangles(
			pObject->m_iCurrentScreenX, pObject->getDrawWidth() + pObject->m_iCurrentScreenX,
			pObject->m_iCurrentScreenY, pObject->getDrawHeight() + pObject->m_iCurrentScreenY,
			this->m_iCurrentScreenX, this->getDrawWidth() + m_iCurrentScreenX,
			this->m_iCurrentScreenY, this->getDrawHeight() + m_iCurrentScreenY, getEngine()))

		{
			if (m_iSpriteTextureState == TextureState::ATTACKING && m_bCanAttack) {
				if (pObject->m_iSpriteTextureState != TextureState::DEFENCE) {
					pObject->m_iHealth -= m_iAttackDMG;
					if (pObject->m_iHealth <= 0) {
						KillPoints b(1);
						m_kpKills = m_kpKills + b;
						m_iCurrentPoints = m_kpKills.getNum();
						pObject->m_iHealth = 0;
					}
					m_bCanAttack = false;
				}
			}

			this->redrawDisplay();
			m_bCollision = true;

		}
		else {
			m_bCollision = false;
		}
	}
}