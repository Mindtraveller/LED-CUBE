#include "Snake.h"

Snake::Snake(Cube *cube)
{
	this->cube = cube;
	Init();	
}

void Snake::Init() {
	this->parts.clear();
	this->parts.push_back(Point(3, 3, 3));
	this->parts.push_back(Point(3, 2, 3));
	this->parts.push_back(Point(3, 1, 3));
	this->head = parts[0];
	this->direction = Y;
	this->directionType = NORMAL;
	GenerateGoal();
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

void Snake::MoveParts() {
	for (unsigned i = parts.size() - 1; i > 0; i--) {
		Point *part = parts[i];
		part->x = parts[i - 1]->x;
		part->y = parts[i - 1]->y;
		part->z = parts[i - 1]->z;
	}
}

void Snake::MapPartsToCube() {
	for (unsigned i = 0; i < parts.size(); i++) {
		cube->TurnLEDOn(*parts[i]);
	}
}

bool Snake::hasReachedGoal() {
	return head->x == goal.x && head->y == goal.y && head->z == goal.z;
}

void Snake::GenerateGoal() {
	do {
		byte x = random(SIZE);
		byte y = random(SIZE);
		byte z = random(SIZE);
		this->goal = Point(x, y, z);
	} while (GoalIsPart());
	cube->TurnLEDOn(this->goal);
}

void Snake::MakeStep() {
	switch (direction) {
	case X:
		directionType == INVERSE ? head->x-- : head->x++;
		break;
	case Y:
		directionType == INVERSE ? head->y-- : head->y++;
		break;
	case Z:
		directionType == INVERSE ? head->z-- : head->z++;
	}
}

bool Snake::GoalIsPart() {
	for (unsigned i = 0; i < parts.size(); i++) {
		Point *part = parts[i];
		if (part->x == goal.x && part->y == goal.y && part->z == goal.z) {
			return true;
		}
	}
	return false;
}

bool Snake::isClash() {
	for (unsigned i = 1; i < parts.size(); i++) {
		Point *part = parts[i];
		if (part->x == head->x && part->y == head->y && part->z == head->z) {
			return true;
		}
	}
	return false;
}

void Snake::ChangeDirection(KEY key) {
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

void Snake::Move() {
	Point *last = parts[parts.size() - 1];
	cube->TurnLEDOff(*last);	
	MoveParts();
	MakeStep();
	if (hasReachedGoal()) {
		Point *preLast = parts[parts.size() - 2];
		parts.push_back(Point(last->x + last->x - preLast->x,
								last->y + last->y - preLast->y,
								last->z + last->z - preLast->z));
		head = parts[0];
		GenerateGoal();
	} else if (isClash()) {
		cube->Clear();
		Init();		
	}
	MapPartsToCube();	
}

size_t Snake::GetSize() {
	return parts.size();
}