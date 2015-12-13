#include "LEDCube.h"
#include <SoftwareSerial.h>
#include "Snake.h"

SoftwareSerial BT(10, 11);
Cube *cube = new Cube();
Snake *snake = new Snake(cube);

void setup() {
	cube->Init();
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	BT.begin(9600);
}

void loop() {

	if (BT.available()) {
		KEY key = KEY(BT.read());
		snake->ChangeDirection(key);
	}
	snake->Move();
	cube->ShowDataXTimes(50 - snake->GetSize());
}
