#include "header.h"
#include "MainMenuState.h"
#include "PsyapEngine.h"


MainMenuState::MainMenuState(PsyapEngine* newEngine) : BaseState() {
	std::cout << "State Main Menu - Created\n";
	this->m_currentEngine = newEngine;

	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/GameStage/background/Background.png", true);

	//Draw imagine
	backgroundLayer.renderImage(m_currentEngine->getBackgroundSurface(), 0, 0,
		0, 0, backgroundLayer.getWidth(), backgroundLayer.getHeight());


	m_currentEngine->drawableObjectsChanged();
	m_currentEngine->destroyOldObjects(true);

	//m_currentEngine->lockForegroundForDrawing(); //To prevent conflicts/errors of 2 objects being drawn to the foreground at the same time
	//m_currentEngine->unlockForegroundForDrawing();
}

void MainMenuState::stateMainLoopDoBeforeUpdate()
{
	m_iOffset = (m_iOffset + 1) % m_currentEngine->getWindowHeight();
	m_currentEngine->redrawDisplay();
}


void MainMenuState::stateAllBackgroundBuffer()
{
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, 0, m_currentEngine->getWindowWidth(), m_currentEngine->getWindowHeight(), 0, m_iOffset);
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, m_currentEngine->getWindowHeight() - m_iOffset, m_currentEngine->getWindowWidth(), m_currentEngine->getWindowHeight(), 0, m_iOffset - m_currentEngine->getWindowHeight());

	m_currentEngine->drawForegroundString(500, 500, "EXAMPLE TEXT AAAA", 0x000000, NULL);
}



