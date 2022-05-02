#pragma once
#include "BaseEngine.h"
#include <sstream>

class PsyapCollisionDetection
{
public:

	PsyapCollisionDetection() {};

	/*
	Check for collision between two rectangles
	x1l and x1r are the first rectangle's x coordinates for left and right sides
	y1t and y1b are the first rectangle's y coordinates for top and bottom
	x2l and x2r are the second rectangle's x coordinates for left and right sides
	y2t and y2b are the second rectangle's y coordinates for top and bottom
	*/
	bool checkRectangles(int x1l, int x1r, int y1t, int y1b, int x2l, int x2r, int y2t, int y2b,BaseEngine* pEngine)
	{

		//std::cout << x2r << std::endl;
		//std::cout << x1l << std::endl;

		if(0){
			m_bCollision = false;
			if (x1r > x2l && x1l < x2l) {
				//std::cout << "Collision1" << std::endl;
				m_iLeftX = x2l;
				m_iRightX = x1r;
				yCheck(y1t, y1b, y2t, y2b);
				m_bCollision = true;
			}
			else if (x2r > x1l && x2l < x1l) {
				//std::cout << "Collision2" << std::endl;
				m_iLeftX = x1l;
				m_iRightX = x2r;
				yCheck(y1t,y1b,y2t,y2b);
				m_bCollision = true;
			}

			if (m_bCollision)
				//std::cout << m_iLeftX << std::endl;
				//std::cout << m_iRightX << std::endl;
				//std::cout << "===================" << std::endl;
				for (int iPixelX = m_iLeftX; iPixelX != m_iRightX; iPixelX++) {
					//std::cout << "Collision2" << std::endl;
					for (int iPixelY = m_iTopY; iPixelY != m_iBottomY; iPixelY++) {
						std::cout << "Collision1" << std::endl;
						std::stringstream stream;
						stream << std::hex << pEngine->rawGetForegroundPixel(iPixelX, iPixelY);
						std::string result(stream.str());
						//std::cout << result << std::endl;
						if (result.at(6) != 'f' && result.at(7) != 'f') {
							std::cout << "Collision3" << std::endl;
							//std::cout << pEngine->rawGetForegroundPixel(0, 0) << std::endl;
							//std::cout << pEngine -> rawGetForegroundPixel(iPixelX, iPixelY) << std::endl;
							//std::cout << surface->getPixel(iPixelX, iPixelY) << std::endl;
							return true;
						}
					}
				}
			return false;
		}
		else {
			return !((x1r < x2l) || (x2r < x1l) || (y1b < y2t) || (y2b < y1t));
		}
	}

	void yCheck(int y1t, int y1b, int y2t, int y2b) {
		if (y1b > y2t && y1t > y2t) {
			//std::cout << "Collision3" << std::endl;
			m_iTopY = y2t;
			m_iBottomY = y1t;
		}
		else if (y2b > y1t && y2t > y1t) {
			//std::cout << "Collision4" << std::endl;
			m_iTopY = y1t;
			m_iBottomY = y2t;
		}
	}

	bool m_bCollision = false;
	int m_iLeftX = 0;
	int m_iRightX = 1;
	int m_iTopY = 0;
	int m_iBottomY = 1;
};

