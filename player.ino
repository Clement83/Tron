

void drwPlayer(Snake play)
{
  for(byte i=0;i<VITTESSE_SNAKE;i++)
  {
    for(byte j=0;j<VITTESSE_SNAKE;j++)
    {
      gb.display.drawPixel(play.x+i,play.y+j);
    }
   }
//  gb.display.fillRect(play.x,play.y,VITTESSE_SNAKE,VITTESSE_SNAKE);
}

void updPlayer(Snake *play)
{
  if(play->dir == up)
     play->y -= VITTESSE_SNAKE;
  else if(play->dir == down)
    play->y += VITTESSE_SNAKE;
  else if(play->dir == left)
    play->x -= VITTESSE_SNAKE;
  else if(play->dir == right)
    play->x += VITTESSE_SNAKE;
    
  if(gb.display.getPixel(play->x, play->y) == BLACK)
  {
      play->life = 0;
  }
}


void human(Snake *play)
{
  if(gb.buttons.pressed(BTN_UP))
  {
    play->dir = up;
  }
  else if(gb.buttons.pressed(BTN_DOWN))
  {
    play->dir = down;
  }
  else if(gb.buttons.pressed(BTN_LEFT))
  {
    play->dir = left;
  }
  else if(gb.buttons.pressed(BTN_RIGHT))
  {
    play->dir = right;
  }
}

void ia(Snake *play)
{
  boolean isOk = false;
  uint8_t forceSortie = 0;
  
  if(random(0,40) == 0)
  {
     play->dir = allDir[random(0,4)];
  }
  
  do{
    int8_t nextX = play->x;
    int8_t nextY = play->y;
    if(play->dir == up)
       nextY -= VITTESSE_SNAKE;
    else if(play->dir == down)
      nextY += VITTESSE_SNAKE;
    else if(play->dir == left)
      nextX -= VITTESSE_SNAKE;
    else if(play->dir == right)
      nextX += VITTESSE_SNAKE;
     
    
    if(gb.display.getPixel(nextX, nextY) == WHITE)
    {
        isOk = true;
    }
    else {
      play->dir = allDir[random(0,4)];
    }
  }while(!isOk && forceSortie++<10);
    
}

void movePlayerSlave()
{
   if(gb.buttons.pressed(BTN_RIGHT))
  {
    bt_right = true;
  }
  else if(gb.buttons.pressed(BTN_LEFT))
  {
    bt_left = true;
  }
  if(gb.buttons.pressed(BTN_UP))
  {
    bt_up = true;
  }
  else if(gb.buttons.pressed(BTN_DOWN))
  {
    bt_down = true;
  }
}

void updatePlayer()
{
  updPlayer(&p1);
  updPlayer(&p2);
}


void drawPlayer()
{ 
  drwPlayer(p1);
  drwPlayer(p2);
}
