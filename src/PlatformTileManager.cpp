#include "header.h"
#include "PlatformTileManager.h"


PlatformTileManager::PlatformTileManager() : TileManager(50, 100) {
	setMapSize(13, 5);
}

void PlatformTileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);
	int iColour = 0xffffff;

	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/GameStage/TileSet.png", true);
	if (iMapValue == 0) {
		//Draw nothing in the tile/box
	}
	else if (iMapValue == 1) {
		backgroundLayer.renderImage(pSurface, 75, 50,
			iStartPositionScreenX, iStartPositionScreenY, 100, 50);
	}else if (iMapValue == 2) {
		backgroundLayer.renderImage(pSurface, 80, 90,
			iStartPositionScreenX, iStartPositionScreenY, 100, 50);
	}else if (iMapValue == 3) {
		backgroundLayer.renderImage(pSurface, 80, 110,
			iStartPositionScreenX, iStartPositionScreenY, 100, 50);
	}

}