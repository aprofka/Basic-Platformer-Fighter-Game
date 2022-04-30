#include "header.h"
#include "ArtState.h"
#include "PsyapEngine.h"
#include "RunningState.h"


ArtState::ArtState(PsyapEngine* newEngine) : BaseState(), m_filterScaling(0, 0), m_filterTranslation(0, 0, &m_filterScaling) {
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

	//m_currentEngine->lockForegroundForDrawing(); //To prevent conflicts/errors of 2 objects being drawn to the foreground at the same time

	//m_currentEngine -> getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	m_currentEngine -> getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);

	
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

	//m_currentEngine->drawForegroundString(10, 10, "Underneath the objects", 0xffffff);
	rickRoll.renderImage(m_currentEngine->getForegroundSurface(), 0, 0,
		0, 0, rickRoll.getWidth(), rickRoll.getHeight());

}

void ArtState::getNewMovableObject(void) {
	//m_arrForegroundObjects.push_back(new DisplayableObject());

	//m_currentEngine->appendObjectToArray(m_arrMenuOptions[3]);

}

//Menu selection button
void ArtState::keyControl(int iKeyPressed) {
	switch (iKeyPressed)
	{
	case SDLK_LEFT:
		m_filterTranslation.changeOffset(10, 0);
		m_currentEngine->redrawDisplay();
		break;
	case SDLK_RIGHT:
		m_filterTranslation.changeOffset(-10, 0);
		m_currentEngine->redrawDisplay();
		break;
	case SDLK_UP:
		m_filterTranslation.changeOffset(0, 10);
		m_currentEngine->redrawDisplay();
		break;
	case SDLK_DOWN:
		m_filterTranslation.changeOffset(0, -10);
		m_currentEngine->redrawDisplay();
		break;
	}
}

// Mouse wheel zooms in or out depending on whether the y scroll was positive or negative
void ArtState::mouseWheel(int x, int y, int which, int timestamp)
{
	if (y < 0)
		m_filterScaling.compress();
	else if (y > 0)
		m_filterScaling.stretch();

	m_currentEngine->redrawDisplay();
}