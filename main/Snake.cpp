#include "Snake.h"

Snake::Snake()
{
	this->head = Point(3, 3, 3);
	this->direction = Y;
	this->directionType = NORMAL;
}

void Snake::ApplyUp() {
	switch (direction) {
	case X:
	case Y:
		direction = Z;
		directionType = NORMAL;
		break;
	case Z:
		direction = X;
		directionType = NORMAL;
	}
}

void Snake::ApplyDown() {
	switch (direction) {
	case X:
	case Y:
		direction = Z;
		directionType = INVERSE;
		break;
	case Z:
		direction = X;
		directionType = INVERSE;
	}
}

void Snake::ApplyLeft() {
	switch (direction) {
	case X:
		direction = Y;
		directionType = directionType;
		break;
	case Y:
		direction = X;
		directionType = directionType == NORMAL ? INVERSE : NORMAL;
		break;
	case Z:
		direction = Y;
		directionType = NORMAL;
	}
}

void Snake::ApplyRight() {
	switch (direction) {
	case X:
		direction = Y;
		directionType = directionType == NORMAL ? INVERSE : NORMAL;
		break;
	case Y:
		direction = X;
		directionType = directionType;
		break;
	case Z:
		direction = Y;
		directionType = INVERSE;
	}
}

void Snake::ChangeDirection(KEYS key) {
	switch(key) {
	case UP:
		ApplyUp();
		break;
	case LEFT:
		ApplyLeft();
		break;
	case RIGHT:
		ApplyRight();
		break;
	case DOWN:
		ApplyDown();
		break;
	}
}

void Snake::Move(Cube &cube) {
	cube.TurnLEDOff(head);
	switch (direction) {
	case X:
		directionType == INVERSE ? head.x--: head.x++;
		break;
	case Y:
		directionType == INVERSE ? head.y-- : head.y++;
		break;
	case Z:
		directionType == INVERSE ? head.z-- : head.z++;
	}
	cube.TurnLEDOn(head);
}