#include "header.h"
#include "MainMenuState.h"
#include "ArtState.h"
#include "PsyapEngine.h"
#include "RunningState.h"


MainMenuState::MainMenuState(PsyapEngine* newEngine) : BaseState() {
	std::cout << "State Main Menu - Created\n";
	this->m_currentEngine = newEngine;

	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/MainMenuState/MainMenuBackground.jpg", true);
	//SimpleImage backgroundLayer = ImageManager::loadImage("resources/GameStage/background/Background.png", true);

	//Draw imagine
	backgroundLayer.renderImage(m_currentEngine->getBackgroundSurface(), 0, 0,
		0, 0, backgroundLayer.getWidth(), backgroundLayer.getHeight());


	m_currentEngine->drawableObjectsChanged();
	m_currentEngine->destroyOldObjects(true);

	m_iOffset = 0;

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
	//m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, 0, m_currentEngine->getWindowWidth(), m_currentEngine->getWindowHeight(), 0, m_iOffset);
	//m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, m_currentEngine->getWindowHeight() - m_iOffset, m_currentEngine->getWindowWidth(), 
	//	m_currentEngine->getWindowHeight(), 0, m_iOffset - m_currentEngine->getWindowHeight());

	//std::cout << m_iOffset << std::endl;
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, 0, m_currentEngine->getWindowWidth(), m_currentEngine->getWindowHeight(), 0, -m_iOffset);
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, 0, m_currentEngine->getWindowWidth(),
		m_currentEngine->getWindowHeight(), 0, m_currentEngine->getWindowHeight() - m_iOffset);
}

void MainMenuState::getNewMovableObject(void) {
	m_arrMenuOptions.push_back(new MenuOption(m_currentEngine, -125, "Play"));
	m_arrMenuOptions.push_back(new MenuOption(m_currentEngine, -50, "Leaderboard"));
	m_arrMenuOptions.push_back(new MenuOption(m_currentEngine, 25, "Game Art"));
	m_arrMenuOptions.push_back(new MenuOption(m_currentEngine, 100, "Exit"));

	m_arrMenuOptions[0]->m_iSelected = true;
	for (auto& i : m_arrMenuOptions) {
		i->m_arrMenuOptions = m_arrMenuOptions;
	}

	m_currentEngine->appendObjectToArray(m_arrMenuOptions[0]);
	m_currentEngine->appendObjectToArray(m_arrMenuOptions[1]);
	m_currentEngine->appendObjectToArray(m_arrMenuOptions[2]);
	m_currentEngine->appendObjectToArray(m_arrMenuOptions[3]);

}

//Menu selection button
void MainMenuState::keyControl(int iKeyPressed) {
	if (iKeyPressed == SDLK_UP || iKeyPressed == SDLK_DOWN || iKeyPressed == 13) {
		for (size_t i = 0; i < m_arrMenuOptions.size(); i++) {
			if (m_arrMenuOptions[i] -> m_iSelected) {
				
				if (iKeyPressed == SDLK_UP && i - 1 != -1) {
					m_arrMenuOptions[i] -> m_iSelected = false;
					m_arrMenuOptions[i - 1]->m_iSelected = true;
					break;
				}
				else if (iKeyPressed == SDLK_DOWN && i + 1 != m_arrMenuOptions.size()) {
					m_arrMenuOptions[i] -> m_iSelected = false;
					m_arrMenuOptions[i + 1]->m_iSelected = true;
					break;
				}
				else if (iKeyPressed == 13) { // 13 is Enter
					//std::cout << "Change State to Play " << std::endl;
					if (strcmp(m_arrMenuOptions[i]->m_sText, "Play") == 0) {
						m_currentEngine->destroyOldObjects(true);
						m_currentEngine->m_state = new RunningState(m_currentEngine);
					}
					else if (strcmp(m_arrMenuOptions[i]->m_sText, "Game Art") == 0) {
						m_currentEngine->destroyOldObjects(true);
						m_currentEngine->m_state = new ArtState(m_currentEngine);
					}
					else if (strcmp(m_arrMenuOptions[i]->m_sText, "Exit") == 0) {
						m_currentEngine->setExitWithCode(0);
					}
					break;			
				}
			}
		}
	}
	
}



