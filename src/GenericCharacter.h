#pragma once
#include "DisplayableObject.h"
#include "PsyapEngine.h"
#include <unordered_map>
#include <string>
#include "PsyapMovementPosition.h"
#include "PsyapImagePixelMapping.h"

enum class TextureState {
	INVALID = 0,
	IDLE = 1,
	RUNNING = 2,
	JUMPING = 3,
	FALLING = 4,
	ATTACKING = 5,
	DEFENCE = 6,
};

class GenericCharacter : public DisplayableObject
{
public:
	GenericCharacter(PsyapEngine* pEngine, std::string sAddress, int iFloorLevel);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);

	void changeTexture(int iTextureOffSetY, int iTextureResetX, std::string sTextureName, bool bRepeat);

	virtual void textureManager();

	int m_iTextureOffSetX = 0;
	int m_iTextureOffSetY = 0;
	bool m_bLookLeft = false;
	bool m_bRepeatLastMove = false;
	std::string m_sLastMovement = "";

	int m_iGroundLevel;
	int m_iMovementSpeed = 0;
	int m_iSpriteFrameCount = 0;
	TextureState m_iSpriteTextureState = TextureState::IDLE;
	TextureState m_iPrevSpriteTextureState = TextureState::INVALID;
	std::unordered_map<std::string, int> m_mSpritePhases;

	int m_iCorrectionX = 0; 
	int m_iCorrectionY = 0; 

	bool m_bFlipped = false;

	/** Movement position calculator - give it start and end position and times
	and it works out current position for the current time. */
	PsyapMovementPosition m_oMovement;

	// Last time the sprite texture was changed
	int m_iLastSpriteChangeTime; // *For Potencial Removal

	int m_iLastKeyReleaseTime = 0;

	PsyapImagePixelMapping* m_pFlipperMapping;

	int m_iTextureUpdateDelta = 0;
	int m_iHealth = 100;
	int m_iAttackDMG;
	int m_iHealthBarOffSetX;
	int m_iHealthBarOffSetY;

	int getPixelColour(int x, int y) { return m_oSkinTile.getPixelColour(x, y); }
private:
	SimpleImage m_oSkinTile;
};

