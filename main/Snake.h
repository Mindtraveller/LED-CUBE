#pragma once
#include "Point.h"
#include "LEDCube.h"

enum KEYS {
	UP = 2,
	DOWN = 4,
	LEFT = 1,
	RIGHT = 3,
};

enum DIRECTIONS {
	X, Y, Z
};

enum DIRECTION_TYPE {
	NORMAL, INVERSE
};

class Snake
{
	Point head;
	DIRECTIONS direction;
	DIRECTION_TYPE directionType;

	void ApplyUp();
	void ApplyDown();
	void ApplyLeft();
	void ApplyRight();

public:
	Snake();
	void ChangeDirection(KEYS key);
	void Move(Cube &cube);
};

