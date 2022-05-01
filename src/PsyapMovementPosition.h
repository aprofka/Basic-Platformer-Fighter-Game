#pragma once
#include "UtilMovementPosition.h"
class PsyapMovementPosition :
    public MovementPosition
{
public:
	int getEndX() {
		return m_iEndX;
	}

	int getEndY() {
		return m_iEndY;
	}

	void setEndX(int iX) {
		m_iEndX = iX;
	}
};