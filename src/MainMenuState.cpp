#include "header.h"
#include "MainMenuState.h"
#include "ArtState.h"
#include "PsyapEngine.h"
#include "RunningState.h"
#include <fstream>
#include <sstream>


MainMenuState::MainMenuState(PsyapEngine* newEngine) : BaseState() {
	std::cout << "State Main Menu - Created\n";
	this->m_currentEngine = newEngine;

	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/MainMenuState/MainMenuBackground.jpg", true);

	//Draw imagine
	backgroundLayer.renderImage(m_currentEngine->getBackgroundSurface(), 0, 0,
		0, 0, backgroundLayer.getWidth(), backgroundLayer.getHeight());


	m_currentEngine->drawableObjectsChanged();
	m_currentEngine->destroyOldObjects(true);

	m_iOffset = 0;

	
	std::ifstream indata; // indata is like cin
	indata.open("saves/userData.txt"); // opens the file
	indata >> m_bFirstTimeLoad;

	

	indata.close();
	std::cout << "End-of-file reached.." << std::endl;
	
	/*
	std::ofstream file;
	file.open("saves/userData.txt");
	file << true << std::endl;
	file.close();
	*/
	//m_currentEngine->lockForegroundForDrawing();
	//m_currentEngine->unlockForegroundForDrawing();
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

void MainMenuState::stateMainLoopDoBeforeUpdate()
{
	m_iOffset = (m_iOffset + 1) % m_currentEngine->getWindowHeight();

	

	m_currentEngine->redrawDisplay();
}


void MainMenuState::stateAllBackgroundBuffer()
{
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, 0, m_currentEngine->getWindowWidth(), m_currentEngine->getWindowHeight(), 0, -m_iOffset);
	m_currentEngine->getForegroundSurface()->copyRectangleFrom(m_currentEngine->getBackgroundSurface(), 0, 0, m_currentEngine->getWindowWidth(),
		m_currentEngine->getWindowHeight(), 0, m_currentEngine->getWindowHeight() - m_iOffset);
}

void MainMenuState::stateVirtPostDraw()
{
	if (m_bFirstTimeLoad) {
		//m_currentEngine->lockForegroundForDrawing();
		int iCenterW = (m_currentEngine->getWindowWidth() / 2);
		int iCenterH = (m_currentEngine->getWindowHeight() / 2);
		m_currentEngine->drawForegroundRectangle(iCenterW - 350, iCenterH - 250, iCenterW + 350, iCenterH + 250, 0xffffff);
		m_currentEngine->drawForegroundString(iCenterW - 300, iCenterH - 225, "Enter your nickname here :", 0x000000, NULL);
		//m_currentEngine->unlockForegroundForDrawing();
	}
}



//Menu selection button
void MainMenuState::keyControl(int iKeyPressed) {
	if (m_bFirstTimeLoad) {
		std::string temp = SDL_GetKeyName(iKeyPressed);
		if (SDL_GetModState() != KMOD_CAPS)
			std::transform(temp.begin(), temp.end(), temp.begin(),
				[](unsigned char temp) { return std::tolower(temp); });
		std::cout << temp << std::endl;
	} 
	else if (iKeyPressed == SDLK_UP || iKeyPressed == SDLK_DOWN || iKeyPressed == 13) {
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





