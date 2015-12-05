#include <SoftwareSerial.h>

const byte DS = 12;
const byte ST_CP = 8; //latch
const byte SH_CP = 9; //CLK

const byte levels[] = {0, 1, 2, 3, 4, 5, 6, 7};
const byte levelsCount = 8;
const byte levelSize = 64;
const int timeForMode = 5;

byte data[512];

byte x = 4;
byte y = 4;
byte z = 4;

SoftwareSerial BT(10, 11);

enum DERECTION : byte {
	UP=0,
	DOWN=120,
	LEFT=248,
	RIGHT=128,
};

int currentMode = 0;

void ClearAllData() {
	for (int i = 0; i < levelsCount * levelSize; i++) {
		data[i] = 0;
	}
}

void Pulse(byte pin) {
	digitalWrite(pin, HIGH);
	digitalWrite(pin, LOW);
}

void WriteDS(byte _byte) {
	digitalWrite(DS, _byte == 1 ? HIGH : LOW);
	Pulse(SH_CP);
}

void Mode_1_Init() {
	for (byte i = 0; i < levelSize; i++) {
		byte value = random(0, 2);  // max - 1
		data[i] = value;  //first level
		data[i + 7 * levelSize] = !value;  //last level
	}
}

void ShowDataXTimes(byte times) {
	for (byte _ = 0; _ < times; _++) {
		for (byte level = 0; level < levelsCount; level++) {
			for (int i = 0; i< levelSize; i++) {
				WriteDS(data[i + level * levelSize]);
			}

			if (level == 0) digitalWrite(levels[levelsCount - 1], LOW);
			else digitalWrite(levels[level - 1], LOW);
			Pulse(ST_CP);
			digitalWrite(levels[level], HIGH);
		}
	}
}

void Mode_1() {
	byte positionToMove = random(levelSize);
	byte fromLevel = data[positionToMove] == 1 ? 0 : 7;
	bool top = fromLevel == 0;
	ShowDataXTimes(5);
	while (true) {
		byte toLevel = top ? fromLevel + 1 : fromLevel - 1;
		if (toLevel >= levelsCount || toLevel < 0) break;
		data[fromLevel * levelSize + positionToMove] = 0;
		data[toLevel * levelSize + positionToMove] = 1;
		ShowDataXTimes(2);
		fromLevel = toLevel;
	}
}

void Mode_0() {
	for (int i = 0; i < levelsCount * levelSize; i++) {
		data[i] = 1;
		if (i != 0) data[i - 1] = 0;
		else data[levelsCount * levelSize - 1] = 0;
		ShowDataXTimes(25);
	}
}

void Mode_2() {
	ClearAllData();
	for (byte cube_size = 0; cube_size < levelsCount; cube_size++) {
		for (byte level = 0; level <= cube_size; level++) {
			for (byte x = 0; x <= cube_size; x++) {
				for (byte y = 0; y <= cube_size; y++) {
					data[level * levelSize + x * levelsCount + y] =
						(y % cube_size == 0 || x % cube_size == 0)
						&& level % cube_size == 0 ||
						(y == 0 || y == cube_size) && (x == 0 || x == cube_size) ? 1 : 0;
				}
			}

		}
		ShowDataXTimes(5);
	}
	for (byte cube_size = levelsCount - 2; cube_size > 0; cube_size--) {
		ClearAllData();
		for (byte level = 0; level <= cube_size; level++) {
			for (byte x = 0; x <= cube_size; x++) {
				for (byte y = 0; y <= cube_size; y++) {
					data[level * levelSize + x * levelsCount + y] =
						(y % cube_size == 0 || x % cube_size == 0)
						&& level % cube_size == 0 ||
						(y == 0 || y == cube_size) && (x == 0 || x == cube_size) ? 1 : 0;
				}
			}
		}
		ShowDataXTimes(5);
	}
}

void setup() {
	/*pinMode(DS, OUTPUT);
	pinMode(ST_CP, OUTPUT);
	pinMode(SH_CP, OUTPUT);
	for (byte i = 0; i < levelsCount; i++) {
		pinMode(levels[i], OUTPUT);
	}
	ClearAllData();
	data[x + y * levelsCount + z * levelSize] = 1;*/
	//pinMode(12, OUTPUT);
	//pinMode(13, OUTPUT);
	//digitalWrite(12, HIGH);
	Serial.begin(9600);
	//delay(2000);
	//digitalWrite(13, HIGH);
	//digitalWrite(12, LOW);
	//delay(2000);
	
	BT.begin(38400);
	//bluetooth.begin(9600);
	
}

void loop() {
	//if (++currentMode < timeForMode * 10) {
	//	if (currentMode == 1) {
	//		ClearAllData();
	//		Mode_1_Init();
	//	}
	//	Mode_1(); //need init in setup !!!
	//}
	//else {
	//	if (currentMode == timeForMode * 11) currentMode = 0;
	//	Mode_2();
	//}

	//if (bluetooth.available() > 0) {
	//	data[bluetooth.read()] = 1;
	//	ShowDataXTimes(10);
	//}
	//Serial1.println("Hey");
	//Mode_0(); // for checking each LED  

	if (BT.available()) {
		byte key = BT.read();
		/*while (!BT.available());
		BT.read();
		while (!BT.available());
		BT.read();
		switch(key) {
		case DOWN: z--;
			break;
		case UP: z++;
			break;
		case RIGHT: x++;
			break;
		case LEFT: x--;
		}
		data[x + y * levelsCount + z * levelSize] = 1;*/
		Serial.println(key);
	}

	//ShowDataXTimes(1);

	// READ Arduino Serial Monitor and WRITE to HC-05
	//if (Serial.available()) {
	//	byte key = BT.read();
	//	BT.read();
	//	BT.read();
	//	BT.println(key);
	//}
}
