#pragma once
#include "Arduino.h"
#include "Point.h"

class Cube
{
	byte *data;
	byte DS;
	byte ST_CP; //latch
	byte SH_CP; //CLK
	byte *levels;
	byte levelsCount;
	byte levelSize;

	void Pulse(byte pin);
	void WriteDS(byte _byte);
public:
	Cube();
	void Init();
	void ClearAllData();
	void ShowDataXTimes(unsigned int times);
	void TurnLEDOn(Point &point);
	void TurnLEDOff(Point &point);
};

