///////////////////////////////////// SETUP SLAVE
void setupSlave(){
  Wire.begin(2);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}
boolean slave_updated;
///////////////////////////////////// UPDATE SLAVE
void updateSlave(){
  //gb.popup(F("Read data SL"),20);
  byte timout = 0;
  isPaused = false;
  while(slave_updated == false){
    //wait for the master's interrupt
    delay(1);
    timout++;
    if(timout >= 300 /*&& !slave_updating*/){
      gb.popup(F("No master"),20);
      disconnected = true;
      isPaused = true;
      slave_updated = false;
      break;
    }
  }
  slave_updated = false;
}

///////////////////////////////////// SLAVE SEND
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
char output[SLAVE_DATA_BUFFER_LENGTH];
void requestEvent()
{  
  //gb.popup(F("send data SL"),20);
  //the slave can only answer with one "write" so you have to put all the variables in an string
  output[0] = BT_UP; //identifier
  output[1] = bt_up? '1' : '0';
  output[2] = BT_DOWN; 
  output[3] = bt_down? '1' : '0'; 
  output[4] = BT_LEFT; 
  output[5] = bt_left? '1' : '0';
  output[6] = BT_RIGHT; 
  output[7] = bt_right? '1' : '0';

  if(isPaused){
    output[0] = SLAVE_PAUSED;
    output[1] = SLAVE_PAUSED;
    output[2] = SLAVE_PAUSED;
    output[3] = SLAVE_PAUSED;
    output[4] = SLAVE_PAUSED;
    output[5] = SLAVE_PAUSED;
    output[6] = SLAVE_PAUSED;
    output[7] = SLAVE_PAUSED;
  }

  if(isMaster){
    output[0] = I_AM_MASTER;
    output[1] = I_AM_MASTER;
    output[2] = I_AM_MASTER;
    output[3] = I_AM_MASTER;
    output[4] = I_AM_MASTER;
    output[5] = I_AM_MASTER;
    output[6] = I_AM_MASTER;
    output[7] = I_AM_MASTER;
  }
  
  bt_up = false;
  bt_down = false;
  bt_left = false;
  bt_right = false;
  bt_a = false;
  bt_b = false;

  Wire.write(output);
}
/*
  Wire.write(GAME_DIFF); //identifier
  Wire.write(difficulter); //identifier
  
  
  Wire.write(P1_X); //identifier
  Wire.write(p1.x); //identifier
  Wire.write(P1_Y); //identifier
  Wire.write(p1.y); //identifier
  Wire.write(P1_ALIVE); //identifier
  Wire.write(p1.life); //identifier
    
  Wire.write(P2_X); //identifier
  Wire.write(p2.x); //identifier
  Wire.write(P2_Y); //identifier
  Wire.write(p2.y); //identifier
  Wire.write(P2_ALIVE); //identifier
  Wire.write(p2.life); //identifier

*/
///////////////////////////////////// SLAVE RECEIVE
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(Wire.available())    // slave may send less than requested
  {
    char data_in = Wire.read(); // receive byte per byte
    //byte numLevelTmp;
    switch(data_in){
    case GAME_DIFF:
      difficulter = Wire.read();
      break;
    case P1_X:
      p1.x = Wire.read();
      break;
    case P1_Y:
      p1.y = Wire.read();
      break;
    case P1_ALIVE:
      p1.life = Wire.read();
      break;
      
    case P2_X:
      p2.x = Wire.read();
      break;
    case P2_Y:
      p2.y = Wire.read();
      break;
    case P2_ALIVE:
      p2.life = Wire.read();
      break;
    
    default:
      break;
    }
  }
  //gb.popup(F("slave upd"),20);
  slave_updated = true;
  disconnected = false;
}








