#include "header.h"
#include "PlatformTile.h"


//Default constructor as it needs at least pEngine
PlatformTile::PlatformTile(PsyapEngine* pEngine) : DisplayableObject(pEngine) {
	//Load Image
	SimpleImage platform = ImageManager::loadImage("resources/GameStage/oak_woods_tileset.png", true);

	//Draw imagine
	platform.renderImage(pEngine->getBackgroundSurface(), 25, 25,
		50, 50, platform.getWidth(), platform.getHeight());
}