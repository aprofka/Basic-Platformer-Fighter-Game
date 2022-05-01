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
	delete m_oMainCharObject;
	delete m_oEnemyObject;
}

RunningState::RunningState(PsyapEngine* newEngine) : BaseState() {
	std::cout << "State Running - Created\n";
	

	this->m_currentEngine = newEngine;

	//Load Image
	SimpleImage backgroundLayer = ImageManager::loadImage("resources/GameStage/background/Background.png", true);
	m_currentEngine->lockForegroundForDrawing();
	m_currentEngine->lockBackgroundForDrawing();
	//Draw imagine
	backgroundLayer.renderImage(m_currentEngine->getBackgroundSurface(), 0, 0,
		0, 0, backgroundLayer.getWidth(), backgroundLayer.getHeight());

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
	m_TileManager.drawAllTiles(m_currentEngine, m_currentEngine -> getBackgroundSurface());

	getNewMovableObject();
	//m_currentEngine->unlockBackgroundForDrawing();
	//m_currentEngine->unlockForegroundForDrawing();
}

void RunningState::stateAllBackgroundBuffer()
{
	m_currentEngine->BaseEngine::copyAllBackgroundBuffer();
}


void RunningState::getNewMovableObject(void){
	m_oMainCharObject = new PlayableCharacter(m_currentEngine);
	m_oEnemyObject = new EnemyCharacter(m_currentEngine);

	m_currentEngine->storeObjectInArray(0, m_oMainCharObject);
	m_currentEngine->storeObjectInArray(1, m_oEnemyObject);
}



