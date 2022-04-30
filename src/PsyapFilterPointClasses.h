#pragma once
#include "header.h"
#include "DrawingSurface.h"

// Filter to apply a scaling to the points
class PsyapFilterPointsMain : public FilterPoints
{
public:
	PsyapFilterPointsMain()
		: m_iStretch(1), m_iCompress(1), xModifier(0), yModifier(0)
	{
	}

	bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		if (m_iCompress > 1) {
			xVirtual /= m_iCompress;
			yVirtual /= m_iCompress;
			if (xVirtual + xModifier < surface->getVirtualMaxX() && yVirtual + yModifier < surface->getVirtualMaxY()
				&& xVirtual + xModifier > -1 && yVirtual + yModifier > -1) {
					surface->rawSetPixel(xVirtual + xModifier, yVirtual + yModifier, uiColour);
			}
		}
		else if (m_iStretch > 1) // Stretch it!
		{
			xVirtual *= m_iStretch;
			yVirtual *= m_iStretch;
			for (int i = 0; i < m_iStretch; i++) {
				for (int y = 0; y < m_iStretch; y++)
				{
					if (xVirtual + i + xModifier < surface->getVirtualMaxX() && yVirtual + y + yModifier< surface->getVirtualMaxY()
						&& xVirtual + i + xModifier > -1 && yVirtual + y + yModifier > -1) {
						surface->rawSetPixel(xVirtual + i + xModifier, yVirtual + y + yModifier, uiColour);
					}
				}	
			}		
		} 
		else {
			if (xVirtual + xModifier < surface->getVirtualMaxX() && yVirtual + yModifier < surface->getVirtualMaxY()
				&& xVirtual + xModifier > -1 && yVirtual + yModifier > -1) {
				surface->rawSetPixel(xVirtual + xModifier, yVirtual + yModifier, uiColour);
			}
		}
		return false;
	}

	void compress() {
		if (m_iCompress > 1) {
			--m_iCompress;
		}
		else {
			++m_iStretch;
		}
	}

	void stretch() { 
		if (m_iStretch > 1) {
			--m_iStretch;
		}
		else {
			++m_iCompress;
		}
	}

	void changeOffset(int offsetXIncrement, int offsetYIncrement)
	{
		xModifier += offsetXIncrement;
		yModifier += offsetYIncrement;
	}


private:
	int m_iStretch, m_iCompress;
	int xModifier, yModifier;
};