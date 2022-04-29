#pragma once
#include "header.h"
#include "DrawingSurface.h"

// Filter to apply a scaling to the points
class PsyapFilterPointsScaling : public FilterPoints
{
public:
	PsyapFilterPointsScaling(int xStretch, int xCompress, int yStretch, int yCompress)
		: xStretch(xStretch), yStretch(yStretch), xCompress(xCompress), yCompress(yCompress)
	{

		if (xStretch < 1) xStretch = 1;
		if (yStretch < 1) yStretch = 1;
		if (xCompress < 1) xCompress = 1;
		if (xCompress < 1) xCompress = 1;
		if (xStretch > 1) xCompress = 1;
		if (yStretch > 1) xCompress = 1;
	}

	PsyapFilterPointsScaling(int xFactor, int yFactor, FilterPoints* pNextFilter = nullptr)
		: xStretch(1), yStretch(1), xCompress(1), yCompress(1)
	{
	}

	bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		if (xStretch > 1) // Stretch it!
		{
			xVirtual *= xStretch;
			yVirtual *= yStretch;
			for (int i = 0; i < xStretch; i++) {
				for (int y = 0; y < yStretch; y++)
				{
					if (xVirtual + i < surface->getVirtualMaxX() && yVirtual + y < surface->getVirtualMaxY()
						&& xVirtual + i > -1 && yVirtual + y > -1) {
						surface->rawSetPixel(xVirtual + i, yVirtual + y, uiColour); // Colour this pixel now
					}
				}	
			}		
		}
		else {
			surface->rawSetPixel(xVirtual, yVirtual, uiColour); // Colour this pixel now
		}
		return false; // We already coloured the pixel anyway
	}

	void stretchX() { if (xCompress > 1) --xCompress; else ++xStretch; }
	void stretchY() { if (yCompress > 1) --yCompress; else ++yStretch; }
	void compressX() { if (xStretch > 1) --xStretch; else ++xCompress; }
	void compressY() { if (yStretch > 1) --yStretch; else ++yCompress; }

	void compress() { compressX(); compressY(); }
	void stretch() { stretchX(); stretchY(); }

private:
	int xStretch, yStretch, xCompress, yCompress;
};

class PsyapFilterPointsTranslation : public FilterPoints
{
public:
	PsyapFilterPointsTranslation(int xModifier, int yModifier, FilterPoints* pNextFilter = nullptr)
		: xModifier(xModifier), yModifier(yModifier), pNextFilter(pNextFilter)
	{
	}

	bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		if (xVirtual + xModifier < surface->getVirtualMaxX() && yVirtual + yModifier < surface->getVirtualMaxY()
			&& xVirtual + xModifier > -1 && yVirtual + yModifier > -1) {
			xVirtual += xModifier;
			yVirtual += yModifier;
		}
		else {
			return false;
		}
		return (pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour);
	}

	void changeOffset(int offsetXIncrement, int offsetYIncrement)
	{
		xModifier += offsetXIncrement;
		yModifier += offsetYIncrement;
	}

private:
	int xModifier, yModifier;
	FilterPoints* pNextFilter;
};