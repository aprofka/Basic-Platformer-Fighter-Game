#include "header.h"

#include "PsyapAutoObject.h"
#include "UtilCollisionDetection.h"

//Default constructor
PsyapAutoObject::PsyapAutoObject(PsyapEngine* pEngine) : DisplayableObject(pEngine) {
	m_iCurrentScreenX = 0; // X Starting position on the screen
	m_iCurrentScreenY = 0; // Y Starting position on the screen
	m_iDrawWidth = 96; // Width of drawing area
	m_iDrawHeight = 96; // Height of drawing area
	m_iColour = 0x00ffff; // Colour of the moving box
	m_iColourT = 0xffffff; // Colour of the moving box

	m_pMainEngine = pEngine;
}

//Deals with what to draw on creation of the object
void PsyapAutoObject::virtDraw()
{
	//getEngine()->lockForegroundForDrawing();
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth,
		m_iCurrentScreenY + m_iDrawHeight,
		m_iColour);
	getEngine()->drawForegroundTriangle(
		getXCentre() + 0 , getYCentre() - 48,
		getXCentre() - 48, getYCentre(),
		getXCentre() + 48, getYCentre(),
		m_iColourT);
	getEngine()->drawForegroundTriangle(
		getXCentre() + 0, getYCentre() + 48,
		getXCentre() - 48, getYCentre(),
		getXCentre() + 48, getYCentre(),
		m_iColourT);
	//getEngine()->unlockForegroundForDrawing();
}

void PsyapAutoObject::virtDoUpdate(int iCurrentTime)
{
	//Tile manager pointer/reference
	PsyapTileManager& pTileManager = m_pMainEngine->GetTileManager();

	//Collision detection
	DisplayableObject* pObject;
	for (int iObjectId = 0;
		(pObject = getEngine()->getDisplayableObject(iObjectId)
			) != NULL;
		iObjectId++)
	{
		if (pObject == this) // This is us, skip it
			continue;
		if (pObject == nullptr) // Object does not exist, skip it
			continue;		// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19

		if (CollisionDetection::checkRectangles(pObject->getXCentre() - 47 , pObject->getXCentre() + 47 ,
			pObject->getYCentre() - 47, pObject->getYCentre() + 47,
			this->getXCentre() - 47, this->getXCentre() + 47,
			this->getYCentre() - 47, this->getYCentre() + 47))

		{
			//Changes colour of the object on colision
			this->m_iColour = 0x00ff00;

		} else {
			//This will be ran if there is no colision with another element(cursor)
			//It determines to direction of the object when it encounters a wall
			this->m_iColour = 0x00ffff;
			if (m_iCurrentScreenX < ((getEngine()->getWindowWidth() - 4) - m_iDrawWidth) && m_iCurrentScreenY == 0) {
				m_iCurrentScreenX += 2;
			}
			else if (m_iCurrentScreenY < ((getEngine()->getWindowHeight() - 4) - m_iDrawHeight)
				&& m_iCurrentScreenX == (getEngine()->getWindowWidth() - 4) - m_iDrawWidth) {
				m_iCurrentScreenY += 2;
			}
			else if (m_iCurrentScreenX != 0 && m_iCurrentScreenY != 0) {
				m_iCurrentScreenX -= 2;
			}
			else if (m_iCurrentScreenY != 0) {
				m_iCurrentScreenY -= 2;
			}

			//Changes type(colour) of tyle and redraws
			if (m_prevX != pTileManager.getMapXForScreenX(this->getXCentre())
				|| m_prevY != pTileManager.getMapYForScreenY(this->getYCentre())) {
				pTileManager.setAndRedrawMapValueAt(pTileManager.getMapXForScreenX(this->getXCentre()),
					pTileManager.getMapYForScreenY(this->getYCentre()),
					2, getEngine(), getEngine()->getBackgroundSurface());
				m_prevX = pTileManager.getMapXForScreenX(this->getXCentre());
				m_prevY = pTileManager.getMapYForScreenY(this->getYCentre());
			}
			
		
		}
	}
}