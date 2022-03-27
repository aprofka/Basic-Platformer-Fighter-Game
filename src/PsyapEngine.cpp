#include "header.h"

#include "PsyapEngine.h"
#include "PsyapDisplayableObject.h"
#include "GenericCharacter.h"
#include "RunningState.h"
#include "MainMenuState.h"




void PsyapEngine::SetState(BaseState* state) {
	std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
	if (this->m_state != nullptr)
		delete this->m_state;
	this->m_state = state;
	this->m_state->setEngine(this);
}


void PsyapEngine::virtSetupBackgroundBuffer() {
	int iScreenCenterX = (getWindowWidth() / 2);
	int iScreenCenterY = (getWindowHeight() / 2);

	fillBackground(0x222255); //Sets the colour of the background
	
	/*
	this -> lockForegroundForDrawing(); //To prevent conflicts/errors of 2 objects being drawn to the foreground at the same time
	this -> drawForegroundString(150, 150, "EXAMPLE TEXT AAAA", 0x0000FF, getFont("Cornerstone Regular.ttf", 48));
	this -> unlockForegroundForDrawing();
	*/

	this -> m_state = new RunningState(this);

}


int PsyapEngine::virtInitialiseObjects()
{
	// Record the fact that we are about to change the array
	// so it doesn't get used elsewhere without reloading it
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(5);
	m_rectObj1 = new PsyapDisplayableObject(this);
	m_state -> GetNewCharacter();
	storeObjectInArray(0, m_rectObj1);

	setAllObjectsVisible(true);
	return 0;
}

void PsyapEngine::virtMouseMoved(int iX, int iY) {
	m_rectObj1->setPosition(iX, iY); //Sets the object position to be the same the the mouse one
}

void PsyapEngine::virtKeyDown(int iKeyCode)
{
	this -> notifyObjectsAboutKeys(true);
}