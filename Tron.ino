#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;
#include <Wire.h>

const byte moto[] PROGMEM = {80,44,0x0,0x0,0x7,0xFF,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xFF,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xFF,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xFF,0xF0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1F,0xFF,0xF0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7F,0xFF,0xFE,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7F,0xFF,0xFE,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xFF,0xF1,0xE0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xFF,0xF1,0xE0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xFF,0xF,0xFF,0xC0,0x0,0x0,0x0,0x0,0x0,0x7,0xFF,0xF,0xFF,0xC0,0x0,0x0,0x0,0x0,0x0,0x1F,0xFC,0x3F,0xE1,0xFC,0x0,0x0,0x0,0x0,0x0,0x1F,0xFC,0x3F,0xE1,0xFC,0x0,0x0,0x0,0x0,0x0,0x1F,0xF0,0xFF,0xFE,0x3F,0xFF,0xE0,0x0,0x0,0x0,0x1F,0xF0,0xFF,0xFE,0x3F,0xFF,0xE0,0x0,0x0,0x0,0x1F,0xF0,0xFF,0xFE,0x3F,0xFF,0xE0,0x0,0x0,0xFF,0x80,0x0,0xFC,0x7F,0x8F,0x3F,0xF8,0x0,0x0,0xFF,0x80,0x0,0xFC,0x7F,0x8F,0x3F,0xF8,0x0,0x7,0xFF,0xE0,0xF,0xF0,0x7,0x8C,0xFF,0xFF,0x0,0x7,0xFF,0xE0,0xF,0xF0,0x7,0x8C,0xFF,0xFF,0x0,0x1F,0xFF,0xF8,0x7F,0xC3,0xE7,0x83,0xFF,0xFF,0xC0,0x1F,0xFF,0xF8,0x7F,0xC3,0xE7,0x83,0xFF,0xFF,0xC0,0x7F,0xC0,0xE7,0xFC,0xF,0xE7,0x8F,0xF0,0x7,0xF0,0x7F,0xC0,0xE7,0xFC,0xF,0xE7,0x8F,0xF0,0x7,0xF0,0xFE,0x0,0x0,0x0,0xFF,0xE7,0x80,0x0,0x7,0xF0,0xFE,0x0,0x0,0x0,0xFF,0xE7,0x80,0x0,0x7,0xF0,0xFE,0x0,0x0,0x0,0xFF,0xE7,0x80,0x0,0x7,0xF0,0xF8,0x0,0x7,0x8F,0xFF,0xE7,0xFF,0xC0,0x0,0xF0,0xF8,0x0,0x7,0x9F,0xFF,0xE7,0xFF,0xC0,0x0,0xF0,0xF8,0x0,0x7,0x9F,0xFF,0xF9,0xFF,0xC0,0x0,0xF0,0xF8,0x0,0x7,0x9F,0xFF,0xF9,0xFF,0xC0,0x0,0xF0,0xF8,0x0,0x7,0x9F,0xFF,0xFE,0x3,0xC0,0x1,0xF0,0xF8,0x0,0x7,0x9F,0xFF,0xFE,0x3,0xC0,0x1,0xF0,0xFE,0x0,0x3F,0x9F,0xFF,0xFF,0xF3,0x0,0x7,0xF0,0xFE,0x0,0x3F,0x9F,0xFF,0xFF,0xF3,0x0,0x7,0xF0,0x7F,0x80,0xFF,0xFF,0xFF,0xFF,0xF0,0x30,0x7,0xF0,0x7F,0x80,0xFF,0xFF,0xFF,0xFF,0xF0,0x30,0x7,0xF0,0x7F,0x80,0xFF,0xFF,0xFF,0xFF,0xF0,0x30,0x7,0xF0,0x1F,0xFF,0xFF,0xFF,0x0,0x0,0x3,0xFF,0xFF,0xC0,0x1F,0xFF,0xFF,0xFF,0x0,0x0,0x3,0xFF,0xFF,0xC0,0x7,0xFF,0xF0,0x0,0x0,0x0,0x0,0xFF,0xFE,0x0,0x7,0xFF,0xF0,0x0,0x0,0x0,0x0,0xFF,0xFE,0x0,0x1,0xFF,0xC0,0x0,0x0,0x0,0x0,0x3F,0xF8,0x0,0x1,0xFF,0xC0,0x0,0x0,0x0,0x0,0x3F,0xF8,0x0,};

const byte looser[] PROGMEM = {88,48,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,0xF0,0xF0,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xF0,0xE0,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0,0x70,0xE2,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0,0x70,0xE2,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8,0x70,0xE0,0x1F,0xFF,0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0x8,0x70,0xF0,0x1F,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xFF,0x0,0x70,0xEE,0x1F,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0x0,0x70,0xE0,0x1F,0xFD,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0x80,0xF0,0xE0,0x3F,0xFC,0x7F,0xFF,0x7F,0xFF,0xFE,0xFF,0xE3,0xF0,0xF0,0x7F,0xFF,0x3F,0xFF,0x7F,0xFF,0xFC,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0x9F,0xFF,0x7F,0xFF,0xFD,0xFF,0xFF,0xF0,0xF0,0x7F,0xFF,0xDF,0xFF,0x7F,0xFF,0xFB,0xFF,0xC,0x70,0xE0,0x3F,0xFF,0xE3,0xFD,0xFF,0xBF,0xF7,0xFF,0x88,0x70,0xE0,0x3F,0xFF,0xFB,0xFC,0xBF,0x37,0xEF,0xFF,0x80,0xF0,0xFC,0x3F,0xFF,0xF9,0xFE,0xBF,0x37,0xEF,0xFF,0x80,0xF0,0xF0,0x3F,0xFF,0xFE,0xFA,0x7F,0x27,0xDF,0xFF,0xC0,0xF0,0xE6,0x3F,0xFF,0xFE,0x78,0x7F,0xF,0x1F,0xFF,0xC1,0xF0,0xE0,0x3F,0xFF,0xFF,0xBC,0x2E,0xD,0xFF,0xFF,0xE1,0xF0,0xF0,0x3F,0xFF,0xFF,0xCC,0x2E,0x8,0xFF,0xFF,0xE3,0xF0,0xFF,0xFF,0xFF,0xFF,0xF4,0x6,0x11,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xDF,0xF8,0xC5,0x7,0xFF,0xFF,0xFF,0xF0,0xC2,0x71,0xFF,0xE1,0xBE,0xE9,0x8,0x70,0xFF,0xE3,0xF0,0xC0,0x1,0xFF,0xF0,0x0,0xE9,0x0,0x0,0xFF,0x80,0xF0,0xC2,0x10,0xFF,0xF8,0x3,0xFB,0xC0,0x3,0xFF,0x8C,0xF0,0xC2,0x10,0xFF,0xFE,0xC,0xFF,0xFE,0x1F,0xFF,0x80,0xF0,0xC2,0x10,0xFF,0xFF,0x87,0xFF,0xF8,0x1F,0xFF,0x87,0xF0,0xC2,0x10,0xFF,0xFF,0xE1,0x3F,0xF0,0xFF,0xFF,0x83,0xF0,0xC2,0x10,0xFF,0xFF,0xF1,0xFF,0xF1,0xFF,0xFF,0xC0,0xF0,0xC2,0x10,0xFF,0xFF,0xC0,0x3F,0xE0,0x7F,0xFF,0xE1,0xF0,0xFF,0xFF,0xFF,0xFF,0x84,0x9F,0xE0,0x3F,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xF8,0x37,0xE2,0x1F,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xF1,0xB7,0xE1,0xFF,0xFF,0xC2,0x70,0xF8,0xFF,0xFF,0xFF,0xA7,0x64,0xC2,0x7F,0xFF,0xC0,0x30,0xE0,0x3F,0xFF,0xFF,0xF5,0x40,0xE,0x3F,0xFF,0xC0,0x30,0xE3,0x3F,0xFF,0xFF,0xF7,0x0,0x7,0xFF,0xFF,0xC2,0x70,0xE0,0x3F,0xFF,0xFF,0xC6,0x1,0xC,0xFF,0xFF,0xC3,0xF0,0xE1,0xFF,0xFF,0xFF,0xCE,0x1,0xE,0xFF,0xFF,0xC3,0xF0,0xE0,0xFF,0xFF,0xFF,0x38,0x42,0xA7,0x3F,0xFF,0xC3,0xF0,0xF0,0x3F,0xFF,0xFE,0x7C,0x5B,0x87,0xCF,0xFF,0xC3,0xF0,0xF8,0x7F,0xFF,0xFD,0xF8,0xDF,0xF7,0xF3,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFC,0x8F,0xF7,0xF3,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFB,0xEF,0xFB,0xFC,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xFE,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xFF,0xFF,0xFF,0xFF,0xF0,};
const byte winner[] PROGMEM = {88,48,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFC,0x77,0x1F,0xC6,0x78,0xCF,0x87,0x8D,0xFF,0xF0,0xFF,0xFE,0x22,0x30,0xC0,0x38,0x7,0x3,0x80,0xFF,0xF0,0xFF,0xFE,0x0,0x30,0xC6,0x38,0xC6,0x33,0x80,0xFF,0xF0,0xFF,0xFF,0x0,0x30,0xC6,0x38,0xC6,0x3,0x8C,0xFF,0xF0,0xFF,0xFF,0x0,0x70,0xC6,0x38,0xC6,0x1F,0x8F,0xFF,0xF0,0xFF,0xFF,0x0,0x70,0xC6,0x38,0xC6,0xF,0x8F,0xFF,0xF0,0xFF,0xFF,0x8,0xF0,0xC6,0x38,0xC7,0x3,0x8F,0xFF,0xF0,0xFF,0xFF,0x9C,0xF0,0xC6,0x38,0xC7,0x87,0x8F,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC7,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBB,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xB5,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xD9,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC2,0xCF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x3F,0x3F,0xFF,0xF0,0xFF,0xFF,0x80,0x0,0x0,0x3F,0xF9,0xFF,0xA7,0xFF,0xF0,0xFF,0xFE,0x0,0x0,0x0,0x7F,0xF7,0xFF,0xFF,0xFF,0xF0,0xFF,0xF0,0x0,0x0,0x0,0x7F,0xF7,0xCF,0xDF,0xFF,0xF0,0xFF,0x80,0x0,0x0,0x0,0xC3,0xF9,0xDF,0xEF,0xE1,0xF0,0x0,0x0,0x0,0x0,0x1,0x9C,0xFF,0xC0,0xF7,0xCE,0x70,0x0,0x0,0x0,0x0,0x3,0x7F,0x70,0xFF,0x99,0xBF,0xB0,0x0,0x0,0x0,0x0,0x2,0x7F,0x2F,0xFF,0xEE,0x3F,0x90,0x0,0x0,0x0,0x0,0x2,0xFF,0xEF,0xFA,0x37,0x9F,0xD0,0x0,0x0,0x0,0x0,0x2,0xFE,0xF,0xDB,0x57,0x3F,0xD0,0x0,0x0,0x0,0x0,0x2,0xFD,0x90,0x2B,0x5F,0x7F,0xD0,0x0,0x0,0x0,0x0,0x2,0xFF,0xBF,0xDF,0xFB,0x7F,0xD0,0x0,0x0,0x0,0x0,0x2,0xFF,0xBF,0xFF,0xFB,0x7F,0x90,0x0,0x0,0x0,0x0,0x3,0x7F,0x7F,0xFF,0xFB,0xBF,0xB0,0xFF,0xC0,0x0,0x0,0x1,0x3C,0xFF,0xFF,0xFB,0x9E,0x70,0xFF,0xF8,0x0,0x0,0x0,0xC1,0xFF,0xFF,0xFF,0xE0,0xF0,0xFF,0xFF,0x0,0x0,0x0,0x3F,0xFF,0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,};


#define VITTESSE_SNAKE 2
enum Dir
{
  up,
  down,
  left,
  right
};
Dir allDir[4]{
up,
down,
left,
right
};

typedef struct {
  int8_t x,y,life;
  Dir dir;
}Snake;

Snake p1,p2;

enum gameMode
{
  gameMenu,
  game,
  gameOver
};
gameMode state = gameMenu;


void drwPlayer(Snake play);
void updPlayer(Snake *play);
void ia(Snake *play);
void human(Snake *play);

const char strSolo[] PROGMEM = "1 player";
const char strMaster[] PROGMEM = "Host (master)";
const char strSlave[] PROGMEM = "Join (slave)";
const char* const multiPlayerMenu[3] PROGMEM = {
  strSolo,
  strMaster,  
  strSlave
};

#define FACILE 7
#define MOYEN 15
#define DIFFICILE 25


/****************************************
MULTIPLAYER VAR
*****************************************/
#define SLAVE_PAUSED 1
#define I_AM_MASTER 2
#define GAME_DIFF 3
/*MASTER*/
#define P1_X 10
#define P1_Y 11
#define P1_ALIVE 12
#define P2_X 20 
#define P2_Y 21
#define P2_ALIVE 22
/*SLAVE*/
#define BT_UP 41
#define BT_DOWN 42
#define BT_LEFT 43
#define BT_RIGHT 44

#define SLAVE_DATA_BUFFER_LENGTH 8


/* fake button for slave*/
boolean bt_up,bt_down,bt_left,bt_right,bt_a,bt_b;
boolean isPaused = false;
boolean disconnected = false;
boolean isMaster = true;
boolean isOnePlayer = false;
byte difficulter;

void setup()
{
  gb.begin();
  initPrograme();
}

void initPrograme()
{
  goTitleScreen();
  state = gameMenu;
  gb.setFrameRate(15);
  difficulter = 15;
  setupMaster();
  setupSlave();
  gb.battery.show = false;
}

void goTitleScreen()
{
  gb.titleScreen(moto);
}

void initGame()
{
  gb.pickRandomSeed();
  gb.display.clear();
  gb.display.persistence = true;
  gb.display.drawFastVLine(0, 0, 48);
  gb.display.drawFastVLine(1, 0, 48);
  gb.display.drawFastVLine(82, 0, 48);
  gb.display.drawFastVLine(83, 0, 48);
  gb.display.drawFastHLine(0, 0, 84);
  gb.display.drawFastHLine(0, 1, 84);
  gb.display.drawFastHLine(0, 46, 84);
  gb.display.drawFastHLine(0, 47, 84);
  p1.x = 10;
  p1.y = 10;
  p1.dir = right;
  p1.life = 1;
  p2.x = 74;
  p2.y = 38;
  p2.dir = left;
  p2.life = 1;
  
  //for slave 
  bt_up = false;
  bt_down = false;
  bt_left = false;
  bt_right = false;
  bt_a = false;
  bt_b = false;
  
}

void loop()
{
    if(gb.update())
    {
      if(gb.buttons.pressed(BTN_C))
      {
        goTitleScreen();
      }
      
      switch(state)
      {
        case gameMenu :
        //multiplayer menu
        switch(gb.menu(multiPlayerMenu, 3)){
          case 0: //single      
            isPaused = false;
            disconnected = false;
            isMaster = false;
            isOnePlayer = true;
            initDifficulty();
            break;
          case 1: //Host      
            isPaused = false;
            disconnected = false;
            isMaster = true;
            isOnePlayer = false;
            initDifficulty();
            break;
          case 2: //Join
            isPaused = false;
            disconnected = false;
            isMaster = false;
            isOnePlayer = false;
            break;
          default:
            state = gameMenu;
            break;
         }
          initGame();
          state = game;
        break;
        case game :
          if(!isPaused)
          {
            if(isOnePlayer || isMaster) human(&p1);
            else movePlayerSlave();
            
            if(isOnePlayer){ ia(&p2); }
            updatePlayer();
          }
          
          drawPlayer();
          if(!isOnePlayer)
          {
            if(isMaster){
              updateMaster();
            }
            else {
              updateSlave();
            }
          }
          if(p1.life == 0 || p2.life == 0)
          {
            state = gameOver;
            gb.setFrameRate(20);//Normal frameRate 
          }
        break;
        case gameOver :
          gb.display.clear();
          gb.display.persistence = false;
          if(p1.life == 0 &&  (isOnePlayer || isMaster))
            gb.display.drawBitmap(0,0,looser);
          else 
            gb.display.drawBitmap(0,0,winner);
            
          if(gb.buttons.pressed(BTN_B))
          {
            state = gameMenu;
          }
          if(gb.buttons.pressed(BTN_A))
          {
            initGame();
            gb.setFrameRate(difficulter);
            state = game;
          }
            
        break;
      }
    }
}

const char strFacile[] PROGMEM = "Easy";
const char strHard[] PROGMEM = "Hard";
const char strInsane[] PROGMEM = "Insane";
const char* const difficultyMenu[3] PROGMEM = {
  strFacile,
  strHard,  
  strInsane
};

void initDifficulty()
{
     switch(gb.menu(difficultyMenu, 3)){
          case 0:     
            gb.setFrameRate(FACILE);
              difficulter = FACILE;
            break;
          case 1 :     
            gb.setFrameRate(MOYEN);  
              difficulter = MOYEN;
            break;
          case 2:     
            gb.setFrameRate(DIFFICILE); 
              difficulter = DIFFICILE;
            break;
          default:
            state = gameMenu;
            break;
         }
}
