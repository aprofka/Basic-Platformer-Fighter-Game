#include "header.h"
#include "ArtState.h"
#include "PsyapEngine.h"
#include "RunningState.h"


ArtState::ArtState(PsyapEngine* newEngine) : BaseState(), m_filterMain() {
	std::cout << "State Art Menu - Created\n";

	this->m_currentEngine = newEngine;

	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/MainMenuState/MainMenuBackground.jpg", true);
	rickRoll = ImageManager::loadImage("resources/rickRoll.jpg", true);

	m_currentEngine->lockBackgroundForDrawing();
	m_currentEngine->lockForegroundForDrawing();
	//Draw imagine
	backgroundLayer.renderImage(m_currentEngine->getBackgroundSurface(), 0, 0,
		0, 0, backgroundLayer.getWidth(), backgroundLayer.getHeight());

	m_currentEngine->drawableObjectsChanged();
	m_currentEngine->destroyOldObjects(true);

	m_iOffset = 0;

	m_currentEngine -> getForegroundSurface()->setDrawPointsFilter(&m_filterMain);

	m_currentEngine->unlockForegroundForDrawing();
	m_currentEngine->unlockBackgroundForDrawing();
}

void ArtState::stateMainLoopDoBeforeUpdate()
{
	m_iOffset = (m_iOffset + 1) % m_currentEngine->getWindowHeight();
	m_currentEngine->redrawDisplay();
}

void ArtState::stateAllBackgroundBuffer()
{
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, 0, m_currentEngine->getWindowWidth(), m_currentEngine->getWindowHeight(), 0, m_iOffset);
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, m_currentEngine->getWindowHeight() - m_iOffset, m_currentEngine->getWindowWidth(), 
		m_currentEngine->getWindowHeight(), 0, m_iOffset - m_currentEngine->getWindowHeight());

	rickRoll.renderImage(m_currentEngine->getForegroundSurface(), 0, 0,
		0, 0, rickRoll.getWidth(), rickRoll.getHeight());

}

//Menu selection button
void ArtState::keyControl(int iKeyPressed) {
	switch (iKeyPressed)
	{
	case SDLK_LEFT:
		m_filterMain.changeOffset(m_iScrollingSpeed, 0);
		m_currentEngine->redrawDisplay();
		break;
	case SDLK_RIGHT:
		m_filterMain.changeOffset(-m_iScrollingSpeed, 0);
		m_currentEngine->redrawDisplay();
		break;
	case SDLK_UP:
		m_filterMain.changeOffset(0, m_iScrollingSpeed);
		m_currentEngine->redrawDisplay();
		break;
	case SDLK_DOWN:
		m_filterMain.changeOffset(0, -m_iScrollingSpeed);
		m_currentEngine->redrawDisplay();
		break;
	}
}

// Mouse wheel zooms in or out depending on whether the y scroll was positive or negative
void ArtState::mouseWheel(int x, int y, int which, int timestamp)
{
	if (y < 0)
		m_filterMain.compress();
	else if (y > 0)
		m_filterMain.stretch();

	m_currentEngine->redrawDisplay();
}