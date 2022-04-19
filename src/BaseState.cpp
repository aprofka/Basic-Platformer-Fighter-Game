#ifndef FILENAME_H
#define FILENAME_H

#include "header.h"
#include "BaseState.h"
#include "PsyapEngine.h"
#include "GenericCharacter.h"

#endif

BaseState::BaseState(void) {
	m_currentEngine = nullptr;
	m_oMovObject = nullptr;
}

BaseState::BaseState(PsyapEngine* newEngine) {
	this -> m_currentEngine = newEngine;
	this -> m_oMovObject = nullptr;
}

void BaseState::getNewMovableObject()
{
}

void BaseState::stateMainLoopDoBeforeUpdate()
{
}

void BaseState::stateAllBackgroundBuffer()
{
}

void BaseState::keyControl(int iKeyPressed)
{
}