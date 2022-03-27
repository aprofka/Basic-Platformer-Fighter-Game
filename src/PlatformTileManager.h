#pragma once
#include "TileManager.h"

class PlatformTileManager :
    public TileManager
{
public:
    PlatformTileManager();
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
	
};

