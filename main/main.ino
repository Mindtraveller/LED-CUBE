#include "LEDCube.h"
#include <SoftwareSerial.h>
#include "Snake.h"

SoftwareSerial BT(10, 11);
Cube cube;
Snake snake;

void setup() {
	cube.Init();
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	BT.begin(9600);	
}

void loop() {

	if (BT.available()) {
		KEYS key = KEYS(BT.read());
		snake.ChangeDirection(key);
	}
	snake.Move(cube);
	cube.ShowDataXTimes(50);
}
