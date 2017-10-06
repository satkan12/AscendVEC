  #include <LiquidCrystal.h>
  
  //LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
  
bool doorOpen;
int incomingByte;
const int DoorOpen  = 10;
const int Floor0   = 22;
const int Floor1   = 23;
const int Floor2   = 24;

const int CallButton1 = 48;//push button on the floor1 and in paraller the button for floor 1 in the elevator
const int CallButton2 = 50;//push button on the floor2 and in paraller the button for floor 2 in the elevator
const int CallButton3 = 52;//push button on the floor3 and in paraller the button for floor 3 in the elevator
const int RelayUp = 51;//the relay that drives up the elevator
const int RelayDown=53;//the relay that drives down the elevator
const int buzzer = 11;//a buzzer warning movement or alarm stop
const int powerOn=13;

bool floorWait = false;
int callElevator1 = 0; // variable for reading the pushbutton status of the floors
int callElevator2 = 0; // variable for reading the pushbutton status of the floors
int callElevator3 = 0; // variable for reading the pushbutton status of the floors
int floor1sense = 0; // variable for reading the proximity status of the floors
int floor2sense = 0; // variable for reading the proximity status of the floors
int floor3sense = 0; // variable for reading the proximity status of the floors
  
  void HomeScreen(){
    lcd.begin(16, 2);
    lcd.print("Viduct Elevators");
    lcd.setCursor(0,1);
    lcd.print("Ascend v1.0");
    delay(1000);
    lcd.clear();
    delay(1000);
  //  
  //lcd.home();
  }
  
  void lcdDisplay(String showThis)
  {
    lcd.setCursor(0,0);
    lcd.print(showThis);
    delay(500);
    lcd.clear();
    delay(500);
  }
  
  int checkForCall()
  {
    //while(Serial.available() > 0){
    //incomingByte = Serial.read() - '0';
    //Serial.print("I received: ");
    //Serial.println(incomingByte);
    //Serial.end();
    //return incomingByte;
    if(!doorOpen)
    {
        if(digitalRead(CallButton1) == HIGH)
        {
          if(!doorOpen)
          {
          blinkFloorLED(999);
          lcdDisplay("Attending Floor 0");
          delay(5000);
           return 1; 
          }
        }
        if(digitalRead(CallButton2) == HIGH)
        {
          if(!doorOpen)
          {
          blinkFloorLED(999);
          lcdDisplay("Attending Floor 1");
          delay(5000);
           return 2; 
          }
        }
        
        if(digitalRead(CallButton3) == HIGH)
        {
          if(!doorOpen)
          {         
          blinkFloorLED(999);
          lcdDisplay("Attending Floor 2");
          delay(5000);
           return 3; 
          }
        }
        else
        {
          floorWait =  !doorOpen;
        }
    } 
  }
  void blinkFloorLED(int floorNo)
  {
    switch (floorNo)
    {
      case 1:
      if(floorWait)
      {
        digitalWrite(Floor0 , HIGH);
        delay(100);
        digitalWrite(Floor0 , LOW);
        delay(100);
        //floorWait =!doorOpen;
      }
        break;
      case 2:
      if(floorWait)
      {
        digitalWrite(Floor1 , HIGH);
        delay(100);
        digitalWrite(Floor1 , LOW);
        delay(100);
        //floorWait =!doorOpen;
      }
        break;
      case 3:
      if(floorWait)
      {
        digitalWrite(Floor2 , HIGH);
        delay(100);
        digitalWrite(Floor2 , LOW);
        delay(100);
        //floorWait =!doorOpen;
      }
        break;
      case 999:
        digitalWrite(Floor0 , LOW);
        digitalWrite(Floor1 , LOW);
        digitalWrite(Floor2 , LOW);
        break;
    }
  }
  bool floorCall(int floorNo)
  {
    setDoorValue();
    //int floorNo = checkForCall();
    if(!doorOpen)
    {
      lcd.clear();
      lcd.print( "DOOR CLOSE ");
      delay(3000);
      lcd.clear();
      blinkFloorLED(floorNo);
      if(floorNo > 0 && floorNo < 4)
        {
          
            lcdDisplay( "Floor #:"+ String(floorNo - 1));
            //delay(3000);
          return true;
        }
      else if(floorNo > 3)
        {
          lcdDisplay( "INVALID FLOOR!");          
          return false;
        }
      delay(2000);
    }
    else{
      lcd.clear();
      //if(floorNo == 0)
      if(doorOpen)      
      lcdDisplay( "DOOR OPEN ");
      return false;
    }
    
  //  //ADD A DELAY
  //  delay(5000);
  //  //doorOpen = !doorOpen; //set it to false = doorClose
  //  lcd.clear();
  //  lcdDisplay( "DOOR CLOSE ");
  }

  void setDoorValue()
  {
    int doorRelay = digitalRead(DoorOpen);
    delay(1);
    if( doorRelay == 1)
    doorOpen = false;
    else
    doorOpen = true;
  }
  
  void setup() {
    pinMode(DoorOpen, INPUT);
    pinMode(11,   OUTPUT);
    pinMode(Floor0,   OUTPUT);
    pinMode(Floor1,   OUTPUT);
    pinMode(Floor2,   OUTPUT);

    pinMode(CallButton1,   INPUT);
    pinMode(CallButton2,   INPUT);
    pinMode(CallButton3,   INPUT);
    
    HomeScreen();
    //Serial.begin(9600);
  }
  
  void loop() {
    //HomeScreen();
    
    // read the state of the pushbuttons value:
//            callElevator1 = digitalRead(CallButton1);
//            callElevator2 = digitalRead(CallButton2);
//            callElevator3 = digitalRead(CallButton3);

//            if(callElevator1 == HIGH)
//            {
//              delay(500);
//              while(callElevator1 == HIGH)
//              {
//                callElevator1 = digitalRead(CallButton1);
//                delay(10);
//              }
              delay(1000);
//              floorCall();
            //}
        floorWait =!doorOpen;
        digitalWrite(11, floorWait);
        floorCall(checkForCall());
    
  }


