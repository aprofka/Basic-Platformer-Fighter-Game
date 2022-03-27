#include "header.h"
#include "PsyapTileManager.h"

PsyapTileManager::PsyapTileManager() : TileManager(100, 100) {
	setMapSize(13, 8);
}

void PsyapTileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);
	int iColour = 0xffffff;

	if (getMapValue(iMapX, iMapY) == 0) {
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 5, // Right
			iStartPositionScreenY + getTileHeight() - 5, // Bottom
			iColour); // Pixel colour
	}
	else if (getMapValue(iMapX, iMapY) == 1) {
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 5, // Right
			iStartPositionScreenY + getTileHeight() - 5, // Bottom
			0xff00ff); // Pixel colour
	} else if (getMapValue(iMapX, iMapY) == 2) {
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 5, // Right
			iStartPositionScreenY + getTileHeight() - 5, // Bottom
			stoi(std::to_string(rand() % 255) + std::to_string(rand() % 255) + std::to_string(rand() % 255))); // Random colour	
	}

}