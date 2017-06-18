#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool doorOpen = true;

void HomeScreen(){
  lcd.begin(16, 2);
  lcd.print("Viduct Elevators");
  lcd.setCursor(0,1);
  lcd.print("Ascend v1.0");
  delay(1000);
  lcd.clear();
  delay(1000);
}

void floorCall(int floorNo)
{
  lcd.clear();
  if(!doorOpen)
  {
  lcd.print("FLOOR " + floorNo);
  }
  lcd.clear();
  lcd.print( "DOOR OPEN ");
  //ADD A DELAY
  Sleep(4000);
  doorOpen = !doorOpen; //set it to false = doorClose
}

void setup() {
  //HomeScreen();
}

void loop() {
  HomeScreen();
  

}

