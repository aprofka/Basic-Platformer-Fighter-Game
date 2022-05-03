#include "header.h"
#include "LoseState.h"
#include "ArtState.h"
#include "PsyapEngine.h"
#include "RunningState.h"
#include "MainMenuState.h"
#include <fstream>
#include <sstream>


LoseState::LoseState(PsyapEngine* newEngine) : BaseState() {
	std::cout << "State Lose - Created\n";
	this->m_currentEngine = newEngine;
	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/GameStage/background/Background1.png", true);

	m_currentEngine->lockForegroundForDrawing();
	m_currentEngine->lockBackgroundForDrawing();

	//Draw imagine
	backgroundLayer.renderImage(m_currentEngine->getBackgroundSurface(), 0, 0,
		0, 0, backgroundLayer.getWidth(), backgroundLayer.getHeight());

	m_currentEngine->drawableObjectsChanged();
	m_currentEngine->destroyOldObjects(true);

	std::ifstream saveFile; // indata is like cin
	saveFile.open("saves/userData.txt"); // opens the file
	saveFile >> m_bFirstTimeLoad;
	for (int i = 0; i <= 1; i++)
		getline(saveFile, m_sUsername); //Get the username that is on line one
	saveFile.close();

	//std::cout << m_sUsername << std::endl;
	
	getNewMovableObject();
	m_currentEngine->unlockBackgroundForDrawing();
	m_currentEngine->unlockForegroundForDrawing();
}

LoseState::~LoseState()
{
	std::vector<MenuOption*>().swap(m_arrMenuOptions);
}

void LoseState::getNewMovableObject(void) {
	m_arrMenuOptions.push_back(new MenuOption(m_currentEngine, -50, "Play Again"));
	m_arrMenuOptions.push_back(new MenuOption(m_currentEngine, 25, "Main Menu"));
	m_arrMenuOptions.push_back(new MenuOption(m_currentEngine, 100, "Exit"));

	m_arrMenuOptions[0]->m_iSelected = true;
	for (auto& i : m_arrMenuOptions) {
		i->m_arrMenuOptions = m_arrMenuOptions;
	}

	m_currentEngine->storeObjectInArray(0, m_arrMenuOptions[0]);
	m_currentEngine->storeObjectInArray(1, m_arrMenuOptions[1]);
	m_currentEngine->storeObjectInArray(2, m_arrMenuOptions[2]);
}

void LoseState::stateAllBackgroundBuffer()
{
	m_currentEngine->BaseEngine::copyAllBackgroundBuffer();
}

void LoseState::stateMainLoopDoBeforeUpdate()
{
	m_currentEngine->redrawDisplay();
}

void LoseState::stateVirtPostDraw()
{
	if (m_bFirstTimeLoad) {
		//m_currentEngine->lockForegroundForDrawing();
		int iCenterW = (m_currentEngine->getWindowWidth() / 2);
		int iCenterH = (m_currentEngine->getWindowHeight() / 2);
		m_currentEngine->drawForegroundRectangle(iCenterW - 350, iCenterH - 250, iCenterW + 350, iCenterH + 250, 0xffffff);
		m_currentEngine->drawForegroundString(iCenterW - 300, iCenterH - 30, "Enter your nickname here :", 0x000000, m_currentEngine->getFont("resources/BebasNeue-Regular.ttf", 25));
		m_currentEngine->drawForegroundRectangle(iCenterW - 300, iCenterH, iCenterW + 250, iCenterH + 50, 0x555555);

		if (!m_sUsername.empty()) {
			const char* temp = m_sUsername.c_str();
			m_currentEngine->drawForegroundString(iCenterW - 290, iCenterH + 10, temp, 0xffffff, m_currentEngine->getFont("resources/BebasNeue-Regular.ttf", 25));
		}
		//m_currentEngine->unlockForegroundForDrawing();
	}
	else {
		if (!m_sUsername.empty()) {
			const char* temp = m_sUsername.c_str();
			m_currentEngine->drawForegroundString(25, 25, temp, 0xffffff, m_currentEngine->getFont("resources/BebasNeue-Regular.ttf", 30));
		}
	}
}

//Menu selection button
void LoseState::keyControl(int iKeyPressed) {
	if (m_bFirstTimeLoad) {
		if (iKeyPressed > 94 && iKeyPressed < 123) {
			std::string temp = SDL_GetKeyName(iKeyPressed);
			if (SDL_GetModState() != KMOD_CAPS)
				std::transform(temp.begin(), temp.end(), temp.begin(),
					[](unsigned char temp) { return std::tolower(temp); });
			m_sUsername.append(temp);
		}
		else if (iKeyPressed == SDLK_BACKSPACE && m_sUsername.length() > 0) {
			m_sUsername.pop_back();
		}
		else if (iKeyPressed == 13 && m_sUsername.length() > 0) {
			std::ofstream file;
			file.open("saves/userData.txt");
			file << false << std::endl;
			file << m_sUsername << std::endl;
			file.close();

			m_bFirstTimeLoad = false;
		}
	}
	else if (iKeyPressed == SDLK_UP || iKeyPressed == SDLK_DOWN || iKeyPressed == 13) {
		for (size_t i = 0; i < m_arrMenuOptions.size(); i++) {
			if (m_arrMenuOptions[i]->m_iSelected) {

				if (iKeyPressed == SDLK_UP && i - 1 != -1) {
					m_arrMenuOptions[i]->m_iSelected = false;
					m_arrMenuOptions[i - 1]->m_iSelected = true;
					break;
				}
				else if (iKeyPressed == SDLK_DOWN && i + 1 != m_arrMenuOptions.size()) {
					m_arrMenuOptions[i]->m_iSelected = false;
					m_arrMenuOptions[i + 1]->m_iSelected = true;
					break;
				}
				else if (iKeyPressed == 13) { // 13 is Enter
					if (strcmp(m_arrMenuOptions[i]->m_sText, "Play Again") == 0) {
						m_currentEngine->destroyOldObjects(true);
						m_currentEngine->changeState(new RunningState(m_currentEngine));
					}
					else if (strcmp(m_arrMenuOptions[i]->m_sText, "Main Menu") == 0) {
						m_currentEngine->destroyOldObjects(true);
						m_currentEngine->changeState(new MainMenuState(m_currentEngine));
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