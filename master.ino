///////////////////////////////////// SETUP MASTER
void setupMaster(){
  Wire.begin();
}

///////////////////////////////////// UPDATE MASTER
void updateMaster(){
  //read from slave
  masterRead();
  masterWrite();
}

///////////////////////////////////// MASTER READ
void masterRead(){
  //
  if(Wire.requestFrom(2, SLAVE_DATA_BUFFER_LENGTH)){    // request 6 bytes from slave device #2
    //gb.popup(F("Read data MA"),20);
    disconnected = false;
    isPaused = false;
    while(Wire.available()){    // slave may send less than requested
      char data_in = Wire.read(); // receive byte per byte
      switch(data_in){
      case BT_UP:
        if(Wire.read() == '1')
          p2.dir = up;
        break;
      case BT_DOWN:
        if(Wire.read() == '1')
          p2.dir = down;
      break;
      case BT_LEFT:
        if(Wire.read() == '1')
          p2.dir = left;
      break;
      case BT_RIGHT:
        if(Wire.read() == '1')
          p2.dir = right;
      break;
      case SLAVE_PAUSED:
        gb.popup(F("Slave paused"),2);
        isPaused = true;
        break;
      case I_AM_MASTER:
        gb.popup(F("1 master max"),2);
        isPaused = true;
        break;
      default:
        gb.popup(F("Wrong slave data"),2);
        //wrongSlaveData = data_in;
        //paused = true;
        break;
      }
    }
  }
  else{
    gb.popup(F("Slave disconnected"),2);
    isPaused = true;
    disconnected = true;
  }
}

/**

#define GAME_DIFF 3
#define P1_X 10
#define P1_Y 11
#define P1_ALIVE 12
#define P2_X 20 
#define P2_Y 21
#define P2_ALIVE 22

**/

///////////////////////////////////// MASTER WRITE
void masterWrite(){
  //gb.popup(F("send data MA"),20);
  Wire.beginTransmission(2); // transmit to device #2
  
  /*General*/
  Wire.write(GAME_DIFF); //identifier
  Wire.write(difficulter); //identifier
  
  /*P1*/
  Wire.write(P1_X); //identifier
  Wire.write(p1.x); //identifier
  Wire.write(P1_Y); //identifier
  Wire.write(p1.y); //identifier
  Wire.write(P1_ALIVE); //identifier
  Wire.write(p1.life); //identifier
    
  /*P2*/
  Wire.write(P2_X); //identifier
  Wire.write(p2.x); //identifier
  Wire.write(P2_Y); //identifier
  Wire.write(p2.y); //identifier
  Wire.write(P2_ALIVE); //identifier
  Wire.write(p2.life); //identifier


  Wire.endTransmission();    // stop transmitting 
}
