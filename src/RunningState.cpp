#ifndef FILENAME_H
#define FILENAME_H

#include "header.h"
#include "RunningState.h"
#include "LoseState.h"
#endif
#include <fstream>

RunningState::~RunningState()
{
	delete m_arrBackgroundSurfaces[0];
	delete m_arrBackgroundSurfaces[1];
	delete m_arrBackgroundSurfaces[2];
	delete m_arrBackgroundSurfaces[3];
	delete m_arrBackgroundSurfaces[4];
	std::vector<DrawingSurface*>().swap(m_arrBackgroundSurfaces);
}

RunningState::RunningState(PsyapEngine* newEngine) : BaseState() {
	std::cout << "State Running - Created\n";

	this->m_currentEngine = newEngine;

	SimpleImage backgroundLayer0 = ImageManager::loadImage("resources/GameStage/background/Background1.png", true);
	SimpleImage backgroundLayer1 = ImageManager::loadImage("resources/GameStage/background/Background2.png", true);
	SimpleImage backgroundLayer2 = ImageManager::loadImage("resources/GameStage/background/Background3.png", true);
	SimpleImage backgroundLayer3 = ImageManager::loadImage("resources/GameStage/background/Background4.png", true);
	SimpleImage backgroundLayer4 = ImageManager::loadImage("resources/GameStage/background/Background5.png", true);

	m_currentEngine->lockForegroundForDrawing();
	m_currentEngine->lockBackgroundForDrawing();
	
	backgroundSetup(backgroundLayer0);
	backgroundSetup(backgroundLayer1);
	backgroundSetup(backgroundLayer2);
	backgroundSetup(backgroundLayer3);
	backgroundSetup(backgroundLayer4);
	m_pOriginalBackgroundSurface = m_currentEngine->getBackgroundSurface();
	m_currentEngine->setBackgroundSurface(m_arrBackgroundSurfaces[0]);

	PlatformTileManager m_TileManager;

	//Tiles initilization
	for (int x = 0; x < 13; x++)
		for (int y = 0; y < 2; y++)
			if (y == 0) {
				m_TileManager.setMapValue(x, y, 1);
			}
			else if(0 == x % 3){
				m_TileManager.setMapValue(x, y, 2);
			}
			else {
				m_TileManager.setMapValue(x, y, 3);
			}

	//Sets the starting/initial position of WHOLE tile from the top left edge
	//of the screen.
	m_TileManager.setTopLeftPositionOnScreen(0, 700);
	m_TileManager.drawAllTiles(m_currentEngine, m_arrBackgroundSurfaces[0]);
	m_TileManager.drawAllTiles(m_currentEngine, m_arrBackgroundSurfaces[1]);
	m_TileManager.drawAllTiles(m_currentEngine, m_arrBackgroundSurfaces[2]);
	m_TileManager.drawAllTiles(m_currentEngine, m_arrBackgroundSurfaces[3]);
	m_TileManager.drawAllTiles(m_currentEngine, m_arrBackgroundSurfaces[4]);

	getNewMovableObject();
	//m_currentEngine->unlockBackgroundForDrawing();
	//m_currentEngine->unlockForegroundForDrawing();
}

void RunningState::backgroundSetup(SimpleImage image) {
	//Load Image
	DrawingSurface* pSurface = new DrawingSurface(m_currentEngine);
	m_arrBackgroundSurfaces.push_back(pSurface);
	pSurface->createSurface(image.getWidth(), image.getHeight());
	pSurface->mySDLLockSurface();
	image.renderImage(pSurface, 0, 0,
		0, 0, image.getWidth(), image.getHeight());
	pSurface->mySDLUnlockSurface();
}

void RunningState::stateAllBackgroundBuffer()
{
	int delta = m_currentEngine->getModifiedTime() - m_iLastUpdateBackground;
	if (delta > 125) {
		//std::cout << "Test1" << std::endl;
		m_currentEngine->setBackgroundSurface(m_arrBackgroundSurfaces[m_iLastBackground]);
		if (m_iLastBackground == 4)
			m_iLastBackground = 0;
		else
			m_iLastBackground++;
		m_iLastUpdateBackground = m_currentEngine->getModifiedTime();
	}
	m_currentEngine->BaseEngine::copyAllBackgroundBuffer();
}


void RunningState::getNewMovableObject(void){
	std::ifstream outFile;
	outFile.open("saves/playState.txt");

	int playerStartX;
	int playersHealth;
	int playerScore;
	int enemyStartX;
	int enemyHealth;
	outFile >> playerStartX >> playersHealth >> playerScore >> enemyStartX >> enemyHealth;
	outFile.close();

	m_oMainCharObject = new PlayableCharacter(m_currentEngine, playerStartX, playersHealth ,playerScore);
	m_oEnemyObject = new EnemyCharacter(m_currentEngine, enemyStartX, enemyHealth);

	m_currentEngine->storeObjectInArray(0, m_oMainCharObject);
	m_currentEngine->storeObjectInArray(1, m_oEnemyObject);
}

void RunningState::stateVirtPostDraw() 
{
	GenericCharacter* pObject;
	pObject = dynamic_cast<GenericCharacter*>(m_currentEngine->getDisplayableObject(0));
	if (pObject->m_bDelete) {
		std::ofstream inFile;
		inFile.open("saves/playState.txt");
		inFile << 250 << std::endl
			<< 100 << std::endl
			<< 0 << std::endl
			<< 1200 << std::endl
			<< 100 << std::endl;
		inFile.close();

		std::ifstream outFile;
		outFile.open("saves/highscore.txt");
		int scoreT;
		std::string nickname;
		outFile >> scoreT >> nickname;
		outFile.close();
		if (scoreT < pObject->m_iCurrentPoints) {
			inFile.open("saves/highscore.txt");
			inFile << pObject->m_iCurrentPoints << std::endl
				<< m_currentEngine -> m_sNickname << std::endl;
			inFile.close();
		}

		m_currentEngine->setBackgroundSurface(m_pOriginalBackgroundSurface);
		m_currentEngine->changeState(new LoseState(m_currentEngine));
		return;
	}

	pObject = dynamic_cast<GenericCharacter*>(m_currentEngine->getDisplayableObject(1));
	if (pObject != nullptr && pObject->m_bDelete) {
		//m_currentEngine->changeState(new LoseState(m_currentEngine));
		m_currentEngine->drawableObjectsChanged();
		m_currentEngine->removeDisplayableObject(pObject);
		m_currentEngine->storeObjectInArray(1, nullptr);
		delete pObject;

		m_oEnemyObject = new EnemyCharacter(m_currentEngine, 1100, 100);
		m_currentEngine->storeObjectInArray(1, m_oEnemyObject);
	}


	pObject = dynamic_cast<GenericCharacter*>(m_currentEngine->getDisplayableObject(0));
	GenericCharacter* pObject2 = dynamic_cast<GenericCharacter*>(m_currentEngine->getDisplayableObject(1));
	std::ofstream inFile;
	inFile.open("saves/playState.txt");
	inFile << pObject->getCurrentX() << std::endl
		<< pObject->m_iHealth << std::endl
		<< pObject->m_iCurrentPoints << std::endl
		<< pObject2->getCurrentX() << std::endl
		<< pObject2->m_iHealth << std::endl;
	inFile.close();
	
	//Convert current score to const star char for printing
	int highScore = (dynamic_cast<GenericCharacter*>(m_currentEngine->getDisplayableObject(0)))->m_iCurrentPoints;
	std::stringstream temp_str;
	temp_str << (highScore);
	std::string str = "Score: " + temp_str.str() + "               Player Name: " + m_currentEngine->m_sNickname;
	const char* cstrScore = str.c_str();

	m_currentEngine->drawForegroundString(20, 20, cstrScore, 0xffffff, m_currentEngine->getFont("resources/BebasNeue-Regular.ttf", 30));
}			