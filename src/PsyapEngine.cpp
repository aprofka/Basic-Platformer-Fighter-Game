#include "header.h"

#include "PsyapEngine.h"
#include "GenericCharacter.h"
#include "RunningState.h"
#include "MainMenuState.h"
#include <typeinfo>


PsyapEngine::~PsyapEngine()
{
	delete m_state;
}

void PsyapEngine::virtSetupBackgroundBuffer() {
	int iScreenCenterX = (getWindowWidth() / 2);
	int iScreenCenterY = (getWindowHeight() / 2);

	fillBackground(0x000000); //Sets the colour of the background
	
	/*
	this -> lockForegroundForDrawing(); //To prevent conflicts/errors of 2 objects being drawn to the foreground at the same time
	this -> drawForegroundString(150, 150, "EXAMPLE TEXT AAAA", 0x0000FF, getFont("Cornerstone Regular.ttf", 48));
	this -> unlockForegroundForDrawing();
	*/

	//this -> m_state = new RunningState(this);
	this->m_state = new MainMenuState(this);

}

void PsyapEngine::virtMainLoopDoBeforeUpdate() {
	m_state->stateMainLoopDoBeforeUpdate();
}

void PsyapEngine::copyAllBackgroundBuffer() {
	m_state->stateAllBackgroundBuffer();
}

int PsyapEngine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(5);
	m_state -> getNewMovableObject();
	setAllObjectsVisible(true);
	return 0;
}

void PsyapEngine::virtPostDraw() {
	m_state->stateVirtPostDraw();
}

void PsyapEngine::virtKeyDown(int iKeyCode)
{
	this -> notifyObjectsAboutKeys(true);
	m_state->keyControl(iKeyCode);
}

void PsyapEngine::virtMouseWheel(int x, int y, int which, int timestamp)
{
	m_state->mouseWheel(x,y,which,timestamp);
}

void PsyapEngine::setBackgroundSurface(DrawingSurface* pSurface) {
	m_pBackgroundSurface = pSurface;
}

