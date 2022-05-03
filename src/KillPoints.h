#pragma once
#include "header.h"

class KillPoints
{
public:
	int num;
	KillPoints();
	KillPoints(int n);
	KillPoints operator+(KillPoints);
	int getNum() {return num * 100;}
};

