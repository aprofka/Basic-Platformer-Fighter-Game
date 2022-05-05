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

void PsyapEngine::changeState(BaseState* newState) {
	BaseState* prevState = m_state;
	if (m_state != nullptr) {
		m_state = newState;
		delete prevState;
	}
}

void PsyapEngine::virtSetupBackgroundBuffer() {
	int iScreenCenterX = (getWindowWidth() / 2);
	int iScreenCenterY = (getWindowHeight() / 2);

	fillBackground(0x000000); //Sets the colour of the background
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
	if(m_firstTime){
		drawableObjectsChanged();
		destroyOldObjects(true);
		createObjectArray(20);
		setAllObjectsVisible(true);
		m_state -> getNewMovableObject();
		m_firstTime = false;
		return 0;
	}
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

void PsyapEngine::virtMouseMoved(int iX, int iY) {
	m_state->mouseMoved(iX, iY);
}