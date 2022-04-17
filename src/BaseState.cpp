#ifndef FILENAME_H
#define FILENAME_H

#include "header.h"
#include "BaseState.h"
#include "PsyapEngine.h"
#include "GenericCharacter.h"

#endif

BaseState::BaseState(void) {
	m_currentEngine = nullptr;
	m_oCharacter = nullptr;
}

BaseState::BaseState(PsyapEngine* newEngine) {
	this -> m_currentEngine = newEngine;
	this -> m_oCharacter = nullptr;
}

void BaseState::GetNewCharacter()
{
}

void BaseState::stateMainLoopDoBeforeUpdate()
{
}

void BaseState::stateAllBackgroundBuffer()
{
}
