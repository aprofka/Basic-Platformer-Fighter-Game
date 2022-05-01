#ifndef FILENAME_H
#define FILENAME_H

#include "header.h"
#include "BaseState.h"
#include "PsyapEngine.h"
#include "GenericCharacter.h"

#endif

BaseState::BaseState(void) {
	m_currentEngine = nullptr;
}

BaseState::~BaseState()
{
}

BaseState::BaseState(PsyapEngine* newEngine) {
	this -> m_currentEngine = newEngine;
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

void BaseState::mouseWheel(int x, int y, int which, int timestamp)
{
}

void BaseState::stateVirtPostDraw()
{
}
