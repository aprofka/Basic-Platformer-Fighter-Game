#include "header.h"
#include "ArtState.h"
#include "PsyapEngine.h"
#include "RunningState.h"


ArtState::ArtState(PsyapEngine* newEngine) : BaseState() {
	std::cout << "State Art Menu - Created\n";
	this->m_currentEngine = newEngine;

	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/MainMenuState/MainMenuBackground.jpg", true);

	m_currentEngine->lockBackgroundForDrawing();
	//Draw imagine
	backgroundLayer.renderImage(m_currentEngine->getBackgroundSurface(), 0, 0,
		0, 0, backgroundLayer.getWidth(), backgroundLayer.getHeight());


	m_currentEngine->drawableObjectsChanged();
	m_currentEngine->destroyOldObjects(true);

	m_iOffset = 0;

	//m_currentEngine->lockForegroundForDrawing(); //To prevent conflicts/errors of 2 objects being drawn to the foreground at the same time
	m_currentEngine->unlockBackgroundForDrawing();
}

void ArtState::stateMainLoopDoBeforeUpdate()
{
	m_iOffset += 1;
	m_currentEngine->redrawDisplay();
}

void ArtState::stateAllBackgroundBuffer()
{
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, 0, m_currentEngine->getWindowWidth(), m_currentEngine->getWindowHeight(), 0, m_iOffset);
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, m_currentEngine->getWindowHeight() - m_iOffset, m_currentEngine->getWindowWidth(), 
		m_currentEngine->getWindowHeight(), 0, m_iOffset - m_currentEngine->getWindowHeight());

}

void ArtState::getNewMovableObject(void) {
	//m_arrForegroundObjects.push_back(new DisplayableObject());

	//m_currentEngine->appendObjectToArray(m_arrMenuOptions[3]);

}

//Menu selection button
void ArtState::keyControl(int iKeyPressed) {
	//...
}