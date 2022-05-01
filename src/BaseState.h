#pragma once

class GenericCharacter;
class PsyapEngine;

class BaseState
{
protected:
	PsyapEngine *m_currentEngine;

public:
	BaseState();
	virtual ~BaseState();
	BaseState(PsyapEngine* newEngine);

	void setEngine(PsyapEngine *newEngine) {
		this-> m_currentEngine = newEngine;
	}

	virtual void getNewMovableObject();
	virtual void stateMainLoopDoBeforeUpdate();
	virtual void stateAllBackgroundBuffer();
	virtual void keyControl(int iKeyPressed);
	virtual void mouseWheel(int x, int y, int which, int timestamp);
	virtual void stateVirtPostDraw();
};

