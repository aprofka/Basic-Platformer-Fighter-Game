#include "header.h"
#include "MainMenuState.h"
#include "HighscoreState.h"
#include "PsyapEngine.h"
#include <fstream>
#include <sstream>


HighscoreState::HighscoreState(PsyapEngine* newEngine) : BaseState() {
	this->m_currentEngine = newEngine;

	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/MainMenuState/MainMenuBackground.jpg", true);

	m_currentEngine->lockForegroundForDrawing();
	m_currentEngine->lockBackgroundForDrawing();

	//Draw imagine
	backgroundLayer.renderImage(m_currentEngine->getBackgroundSurface(), 0, 0,
		0, 0, backgroundLayer.getWidth(), backgroundLayer.getHeight());

	m_currentEngine->drawableObjectsChanged();
	m_currentEngine->destroyOldObjects(true);

	m_currentEngine->unlockForegroundForDrawing();
	m_currentEngine->unlockBackgroundForDrawing();
}

void HighscoreState::stateMainLoopDoBeforeUpdate()
{
	m_currentEngine->redrawDisplay();
}

void HighscoreState::stateAllBackgroundBuffer()
{
   m_currentEngine->BaseEngine::copyAllBackgroundBuffer();
}

void HighscoreState::stateVirtPostDraw()
{
	std::ifstream outFile;
	outFile.open("saves/highscore.txt");
	int scoreT;
	std::string nickname;
	outFile >> scoreT >> nickname;
	outFile.close();

	int iCenterW = (m_currentEngine->getWindowWidth() / 2);
	int iCenterH = (m_currentEngine->getWindowHeight() / 2);
	m_currentEngine->drawForegroundRectangle(iCenterW - 325, iCenterH - 300, iCenterW + 300, iCenterH + 300, 0xffffff);
	m_currentEngine->drawForegroundString(iCenterW - 175, iCenterH - 100, nickname.c_str(), 0x000000, m_currentEngine->getFont("resources/BebasNeue-Regular.ttf", 100));

	std::stringstream temp_str;
	temp_str << (scoreT);
	std::string str = temp_str.str();
	const char* cstrScore = str.c_str();
	m_currentEngine->drawForegroundString(iCenterW - 100, iCenterH, cstrScore, 0x000000, m_currentEngine->getFont("resources/BebasNeue-Regular.ttf", 100));
}

//Menu selection button
void HighscoreState::keyControl(int iKeyPressed) {
	if (iKeyPressed == SDLK_ESCAPE) {
		m_currentEngine->changeState(new MainMenuState(m_currentEngine));
	}
}
