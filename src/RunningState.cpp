#ifndef FILENAME_H
#define FILENAME_H

#include "header.h"
#include "RunningState.h"

#endif

RunningState::RunningState(void) : BaseState() {
	std::cout << "State Running - Created\n";
}

RunningState::~RunningState()
{
	//delete m_oMainCharObject;
	//delete m_oEnemyObject;
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
	m_oMainCharObject = new PlayableCharacter(m_currentEngine);
	m_oEnemyObject = new EnemyCharacter(m_currentEngine);

	m_currentEngine->storeObjectInArray(0, m_oMainCharObject);
	m_currentEngine->storeObjectInArray(1, m_oEnemyObject);
}



