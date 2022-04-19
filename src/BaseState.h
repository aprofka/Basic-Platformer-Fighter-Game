#pragma once

class GenericCharacter;
class PsyapEngine;

class BaseState
{
protected:
	PsyapEngine *m_currentEngine;

public:
	BaseState();
	BaseState(PsyapEngine* newEngine);

	void setEngine(PsyapEngine *newEngine) {
		this-> m_currentEngine = newEngine;
	}

	GenericCharacter* m_oMovObject;

	virtual void GetNewMovableObject();
	virtual void stateMainLoopDoBeforeUpdate();
	virtual void stateAllBackgroundBuffer();
};

