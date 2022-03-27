#pragma once
#include "TileManager.h"
class PsyapTileManager :
    public TileManager
{
public:
	PsyapTileManager();
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
};

