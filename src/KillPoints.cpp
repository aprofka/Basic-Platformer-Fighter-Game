#include "KillPoints.h"

using namespace std;

KillPoints::KillPoints()
{}

KillPoints::KillPoints(int n)
{
	num = n;
}

KillPoints KillPoints::operator+(KillPoints kp) {
	KillPoints newPoints;
	newPoints.num = num + kp.num;
	return newPoints;
}