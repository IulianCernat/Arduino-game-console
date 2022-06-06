#define cs 10
#define dc 9
#define rst 8
#define swPin 2  // digital pin connected to switch output
#define xPin A0  // analog pin connected to X output
#define yPin A1  // analog pin connected to Y output
#define buttons A2
#define buzzer 3
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_QDTech.h>  // Hardware-specific library
#include <SPI.h>

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978



Adafruit_QDTech tft = Adafruit_QDTech(cs, dc, rst);  // Invoke custom library

void initiliaze() {
  tft.setRotation(1);  //  Lanscape
  tft.fillScreen(QDTech_BLACK);
  tft.setTextWrap(true);
  tft.setTextColor(QDTech_RED);
  tft.setCursor(1, 120);
  tft.println("Score:");
  displayScore();
  tft.writeLine(0, 118, 160, 118, QDTech_BLUE);
}
void setup() {


  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);
  pinMode(buttons, INPUT_PULLUP);
  Serial.begin(9600);
  tft.init();


  pinMode(buzzer, OUTPUT);
  initiliaze();
}
int totalScore = 0;
void displayScore() {
  tft.setCursor(50, 120);
  tft.fillRect(50, 120, 50, 50, QDTech_BLACK);
  tft.setTextColor(QDTech_BLUE);
  tft.println(totalScore);
}

void playProjectileSound() {

  tone(buzzer, NOTE_G4, 35);
  delay(35);
  tone(buzzer, NOTE_G5, 35);
  delay(35);
  tone(buzzer, NOTE_G6, 35);
  delay(35);
  noTone(buzzer);
}

void joystick(int &x, int &y) {
  x = analogRead(xPin);
  y = analogRead(yPin);
}


int getButton() {
  int a = analogRead(A2);
  if (a >= 14 && a <= 16)
    return 4;
  if (a >= 20 && a <= 23)
    return 3;
  if (a >= 25 && a <= 29)
    return 2;
  if (a >= 31 && a <= 35)
    return 1;
  return 0;
}
void drawProjectile(char direction[], int &projectilePosX, int &projectilePosY) {

  tft.fillCircle(projectilePosX, projectilePosY, 1, QDTech_BLACK);
  if (!strcmp(direction, "left")) {
    //    if (projectilePosX % 10 == 0)
    //       playProjectileSound();
    projectilePosX--;
    if (projectilePosX <= 0) {
      strcpy(direction, "none");
      return;
    }
  } else if (!strcmp(direction, "right")) {
    //      if (projectilePosX % 10 == 0)
    //        playProjectileSound();
    projectilePosX++;
    if (projectilePosX >= 160) {
      strcpy(direction, "none");
      return;
    }

  } else if (!strcmp(direction, "up")) {
    //    if (projectilePosY % 10 == 0)
    //        playProjectileSound();
    projectilePosY--;
    if (projectilePosY <= 0) {
      strcpy(direction, "none");
      return;
    }

  } else if (!strcmp(direction, "down")) {
    //      if (projectilePosY % 10 == 0)
    //        playProjectileSound();
    projectilePosY++;
    if (projectilePosY >= 128) {
      strcpy(direction, "none");
      return;
    }
  }
  tft.fillCircle(projectilePosX, projectilePosY, 1, QDTech_WHITE);
}

void drawParticipant(char *direction, int &participantPosX, int &participantPosY, int playerSize[2], int color)  // direction
{
  tft.fillRect(participantPosX, participantPosY, playerSize[0], playerSize[1], QDTech_BLACK);
  if (!strcmp(direction, "left")) {
    if (participantPosX - 1)
      participantPosX--;
  } else if (!strcmp(direction, "right")) {
    if (participantPosX + playerSize[0] < 160)
      participantPosX++;

  } else if (!strcmp(direction, "up")) {
    if (participantPosY - 1 > 0)
      participantPosY--;
  } else if (!strcmp(direction, "down")) {
    if (participantPosY + playerSize[1] < 118)
      participantPosY++;
  }
  tft.fillRect(participantPosX, participantPosY, playerSize[0], playerSize[1], color);
}


void calculateProjectilePath(char *direction, int playerPosX, int playerPosY, int &projectilePosX, int &projectilePosY, int box[2]) {
  playProjectileSound();

  int projectilePadding = 3;
  if (!strcmp(direction, "left")) {

    projectilePosY = ceil((playerPosY + box[1] / 2));
    projectilePosX = playerPosX;
    if (playerPosX)
      projectilePosX -= projectilePadding;
    return;
  }

  if (!strcmp(direction, "right")) {

    projectilePosX = ceil((playerPosX + box[0]));
    projectilePosY = ceil((playerPosY + box[1] / 2));
    if (playerPosX + box[0] <= 160)
      projectilePosX += +projectilePadding;
    return;
  }
  if (!strcmp(direction, "up")) {

    projectilePosY = ceil((playerPosY - box[1] / 2));
    projectilePosX = ceil((playerPosX + box[0] / 2));
    if (playerPosY >= 0)
      projectilePosY -= projectilePadding;
    return;
  }
  if (!strcmp(direction, "down")) {
    projectilePosX = ceil((playerPosX + box[0] / 2));
    projectilePosY = ceil((playerPosY + box[1]));
    if (projectilePosY >= 0)
      projectilePosY += projectilePadding;
    return;
  }
}
int getRandom(int lower, int upper) {
  int i, num;
  for (i = 0; i < 5; i++) {
    num = (random(10000) % (upper - lower + 1)) + lower;
  }
  return num;
}
void generateRandomStartingPositions(int &enemyPosX, int &enemyPosY, int participantSize[2]) {
  int posibleXPosition[] = { 0, 160 - participantSize[0], 80 };
  int posibleYPosition[] = { 0, 118 - participantSize[1], 64 };

  enemyPosX = posibleXPosition[getRandom(0, 3)];
  enemyPosY = posibleYPosition[getRandom(0, 3)];
}

void generateNextRandomPosition(char enemyPosition[]) {
  char *directions[4] = { "left", "right", "down", "up" };
  int a = getRandom(0, 5);
  strcpy(enemyPosition, NULL);
  switch (a) {
    case 0: strcpy(enemyPosition, "left"); break;
    case 1: strcpy(enemyPosition, "right"); break;
    case 2: strcpy(enemyPosition, "up"); break;
    case 3: strcpy(enemyPosition, "down"); break;
  }
}
boolean checkPlayerEnemyCollision(char direction[], int enemyPosX, int enemyPosY, int enemySize[], int playerPosX, int playerPosY, int playerSize[]) {

  if (playerPosX + playerSize[0] == enemyPosX && playerPosY == enemyPosY && playerPosY + playerSize[1] == enemyPosY + enemySize[1])
    return true;
  if (playerPosX == enemyPosX + enemySize[0] && playerPosY == enemyPosY && playerPosY + playerSize[1] == enemyPosY + enemySize[1])
    return true;
  if (playerPosX == enemyPosX && playerPosX + playerSize[0] == enemyPosX + enemySize[0] && playerPosY == enemyPosY)
    return true;
  if (playerPosX == enemyPosX && playerPosX + playerSize[0] == enemyPosX + enemySize[0] && playerPosY + playerSize[1] == enemyPosY)
    return true;
  if (playerPosX == enemyPosX && playerPosY == enemyPosY)
    return true;


  return false;
}
boolean checkCollision(char *direction, int enemyPosX, int enemyPosY, int enemySize[2], int projectileX, int projectileY) {
  boolean result = false;
  if (!strcmp(direction, "left")) {
    if (enemyPosX + enemySize[0] + 1 == projectileX && enemyPosY + enemySize[1] + 2 >= projectileY && enemyPosY - 2 <= projectileY)
      result = true;
  }
  if (!strcmp(direction, "up")) {
    if ((enemyPosX + enemySize[0] + 1 >= projectileX && enemyPosX - 1 <= projectileX) && enemyPosY + enemySize[1] - 1 == projectileY)
      result = true;
  }

  if (!strcmp(direction, "right")) {
    if (enemyPosX - 1 == projectileX && enemyPosY + enemySize[1] + 2 >= projectileY && enemyPosY - 2 <= projectileY)
      result = true;
  }

  if (!strcmp(direction, "down")) {
    if ((enemyPosX + enemySize[0] + 1 >= projectileX && enemyPosX - 1 <= projectileX) && enemyPosY + enemySize[1] + 1 == projectileY)
      result = true;
  }

  return result;
}

void printGameOver() {


  tft.fillScreen(QDTech_BLACK);
  tft.setTextColor(QDTech_RED);
  tft.setCursor(50, 60);
  tft.println("GAME OVER !");
  tft.setCursor(50, 70);
  tft.println("Your Score: ");
  tft.setTextColor(QDTech_GREEN);
  tft.setCursor(123, 70);
  tft.print(totalScore);
}
boolean checkDirectionInQue(char direction[], char *que[10], int &currentQueIndex, int queSize) {

  boolean found = false;
  for (int index = 0; index < currentQueIndex; index++)
    if (!strcmp(que[index], direction))
      found = true;

  if (currentQueIndex == queSize) {
    for (int i = 0; i < currentQueIndex - 1; i++) {
      que[i] = que[i + 1];
    }
    currentQueIndex--;
  }
  que[currentQueIndex] = direction;
  currentQueIndex++;
  return found;
}
//left = 0, right = 1, up = 2, down = 3
void game() {
  int stickX, stickY;
  int drawDelay = 10;
  int button;

  //Player
  int playerPosX = 80;
  int playerPosY = 64;
  int playerSize[2] = { 5, 5 };
  int playerProjectilePosX = -1;
  int playerProjectilePosY = -1;
  char shootingDirection[10] = "none";
  //Enemy
  char *directionsQue[5];
  int currentQueIndex = 0;
  int queSize = 5;
  //
  int changeDecision = 40;
  char enemyDirection[10];
  int enemyPosX = 60;
  int enemyPosY = 70;
  int enemySize[2] = { 5, 5 };
  int enemyProjectilePosX = -1;
  int enemyProjectilePosY = -1;
  int distanceWalked = 0;
  char enemyShootingDirection = "none";

  //draw participants
  generateRandomStartingPositions(enemyPosX, enemyPosY, enemySize);
  generateNextRandomPosition(enemyDirection);
  drawParticipant("left", playerPosX, playerPosY, playerSize, QDTech_RED);
  drawParticipant(enemyDirection, enemyPosX, enemyPosY, enemySize, QDTech_GREEN);
  generateNextRandomPosition(enemyDirection);

  while (1) {


    delay(drawDelay);
    button = getButton();

    if (distanceWalked == changeDecision) {
      distanceWalked = 0;
      generateNextRandomPosition(enemyDirection);
    }

    distanceWalked++;
    drawParticipant(enemyDirection, enemyPosX, enemyPosY, enemySize, QDTech_GREEN);




    if (button)
      if (!strcmp(shootingDirection, "none")) {

        switch (button) {
          case 1: strcpy(shootingDirection, "left"); break;
          case 2: strcpy(shootingDirection, "up"); break;
          case 3: strcpy(shootingDirection, "right"); break;
          case 4: strcpy(shootingDirection, "down"); break;
        }
        calculateProjectilePath(shootingDirection, playerPosX, playerPosY, playerProjectilePosX, playerProjectilePosY, playerSize);
        button = 0;
      }
    if (strcmp(shootingDirection, "none")) {
      drawProjectile(shootingDirection, playerProjectilePosX, playerProjectilePosY);
      if (checkCollision(shootingDirection, enemyPosX, enemyPosY, enemySize, playerProjectilePosX, playerProjectilePosY)) {

        ++totalScore;
        displayScore();
      }

    } else {
      playerProjectilePosX = -1;
      playerProjectilePosY = -1;
    }

    joystick(stickX, stickY);
    if (stickX >= 480 && stickX <= 500 && stickY >= 510 && stickY <= 530)
      continue;

    if (stickX < 480 && stickY > 410 && stickY <= 620)
      drawParticipant("left", playerPosX, playerPosY, playerSize, QDTech_RED);
    if (stickX > 500 && stickY > 410 && stickY <= 620)
      drawParticipant("right", playerPosX, playerPosY, playerSize, QDTech_RED);

    if (stickY < 500 && stickX > 390 && stickX < 590)
      drawParticipant("down", playerPosX, playerPosY, playerSize, QDTech_RED);

    if (stickY > 540 && stickX > 390 && stickX < 590)
      drawParticipant("up", playerPosX, playerPosY, playerSize, QDTech_RED);
    if (checkPlayerEnemyCollision(enemyDirection, enemyPosX, enemyPosY, enemySize, playerPosX, playerPosY, playerSize)) {
      delay(1000);
      printGameOver();
      break;
    }
  }
}

void playIntroductionMelody() {

  tone(3, NOTE_B5, 100);
  delay(100);
  tone(3, NOTE_E6, 850);
  delay(800);
  noTone(3);

  delay(500);


  tone(3, NOTE_E6, 125);
  delay(130);
  tone(3, NOTE_G6, 125);
  delay(130);
  tone(3, NOTE_E7, 125);
  delay(130);
  tone(3, NOTE_C7, 125);
  delay(130);
  tone(3, NOTE_D7, 125);
  delay(130);
  tone(3, NOTE_G7, 125);
  delay(125);
  noTone(3);
}
void loop() {

  playIntroductionMelody();
  game();
  while (1) {
    if (!digitalRead(swPin)) {
      initiliaze();
      break;
    }
  }
}
