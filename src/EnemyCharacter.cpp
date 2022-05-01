#include "header.h"
#include "EnemyCharacter.h"

void EnemyCharacter::textureManager() {
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
			changeTexture(1, 0, "BasicAttack", false);
			break;
		case TextureState::DEFENCE:
			changeTexture(10, 1, "Defence", true);
			break;
		}
	}
}