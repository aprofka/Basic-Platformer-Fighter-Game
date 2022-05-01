#pragma once
#include "ImagePixelMapping.h"

/*
This is a coordiante mapping function for shifting x and y coordinates, e.g. to scroll around an image
*/
class PsyapImagePixelMapping : public ImagePixelMapping
{
public:
	PsyapImagePixelMapping()
	{
		m_dXFrameSize = 0.00;
		m_dYFrameSize = 0.00;
		m_dXPos = 0.00;
		m_dYPos = 0.00;
		m_bFlipped = false;
	}

	PsyapImagePixelMapping(double dXFrameSize, double dYFrameSize, double dXPos, double dYPos, bool bFlipped)
	{
		m_dXFrameSize = dXFrameSize;
		m_dXFrameSize = dXFrameSize;
		m_dXPos = dXPos;
		m_dYPos = dYPos;
		m_bFlipped = bFlipped;
	}

	bool mapCoordinates(double& x, double& y, const SimpleImage& image) override
	{
		if (x < 0.00) return false;
		if (y < 0.00) return false;
		if (x >= (image.getWidth() - 0.5)) return false;
		if (y >= (image.getHeight() - 0.5)) return false;

		if (m_bFlipped) {
			x = image.getWidth() - x;
			x -= m_dXFrameSize * (m_dXPos + 2);
		}
		else {
			x += m_dXFrameSize * m_dXPos;
		}
		y += m_dYFrameSize * m_dYPos;

		// Ensure it is within the size of the image
		while (x > image.getWidth())
			x -= image.getWidth();
		while (x < 0.00)
			x += image.getWidth();
		while (y > image.getHeight())
			y -= image.getHeight();
		while (y < 0.00)
			y += image.getHeight();

		if (image.getPixelColour(0, 0) == image.getPixelColour(static_cast<int>(x), static_cast<int>(y))) return false;

		return true;
	}

	void setNewTexture(double dXFrameSize, double dYFrameSize, double dXPos, double dYPos, bool bFlipped) {
		m_dXFrameSize = dXFrameSize;
		m_dYFrameSize = dYFrameSize;
		m_dXPos = dXPos;
		m_dYPos = dYPos;
		m_bFlipped = bFlipped;
	}

protected:
	double m_dXFrameSize;
	double m_dYFrameSize;
	double m_dXPos;
	double m_dYPos;
	bool m_bFlipped;
};