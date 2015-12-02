const byte DS = 10;
const byte ST_CP = 8; //latch
const byte SH_CP = 9; //CLK

const byte levels[] = {0, 1, 2, 3, 4, 5, 6, 7};
const byte levelsCount = 8;
const byte levelSize = 64;

byte data[512];

void setup() {
  pinMode(DS, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(SH_CP, OUTPUT);

  for (byte i =0; i < levelsCount; i++){
    pinMode(levels[i], OUTPUT);
  } 
  RainModeInit();
}

void Pulse(byte pin){
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

void WriteDS(byte _byte) {
    digitalWrite(DS, _byte == 1 ? HIGH : LOW);
    Pulse(SH_CP);
}

void RainModeInit() {
  for (byte i = 0; i < levelSize; i++){
    byte value = random(0, 2);  // max - 1
    data[i] = value;  //first level
    data[i + 7 * levelSize] = !value;  //last level
  }  
}

void ShowDataXTimes(byte times) {
  for(byte _ = 0; _ < times; _++){
     for (byte level = 0; level < levelsCount; level++) {
        for(int i = 0; i< levelSize; i++){
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
    byte positionToMove = random(levelSize + 1);
    byte fromLevel = data[positionToMove] == 1 ? 0 : 7;
    bool top = fromLevel == 0;
    ShowDataXTimes(5);
    while(true) {
      byte toLevel = top ? fromLevel + 1: fromLevel - 1;
      if (toLevel >= levelsCount || toLevel < 0) break;
      data[fromLevel * levelSize + positionToMove] = 0;
      data[toLevel * levelSize + positionToMove] = 1;
      ShowDataXTimes(2);
      fromLevel = toLevel;
    }
}

void Mode_0() {
  for (int i = 0; i < levelsCount * levelSize ; i++) {
      data[i] = 1;
      if (i != 0) data[i - 1] = 0;
      else data[511] = 0;
      ShowDataXTimes(25);
  }
}

void loop() {
    //Mode_0(); // for checking each LED
    Mode_1(); //need init in setup !!!
}
