#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;
#include <Wire.h>

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
}

void goTitleScreen()
{
  gb.titleScreen(F("Tron"));
}

void initGame()
{
  gb.pickRandomSeed();
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
          }
        break;
        case gameOver :
          gb.display.clear();
          gb.display.persistence = false;
          if(p1.life == p2.life)
            gb.display.print("Egalite");
          else if(p1.life == 0)
            gb.display.print("P2 win");
          else if(p2.life == 0)
            gb.display.print("P1 win");
            
            if(gb.buttons.pressed(BTN_A))
            {
              state = gameMenu;
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
