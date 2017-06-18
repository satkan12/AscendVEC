/*
  Elevator project with arduino pro mini 328 5v 8mhz
  
  - This is a simple elevator project using a single-phase ac motor.
  - There are 3 floors and a button is placed in every floor and are connected in paraller with 3 button inside the elevator.
  - 3 proximity switches are attached on every floor to indicate where the elevator is and to stop it.
  - A buzzer is connected to warn for movement or 
  -alarm stop inside the elevator is attached directly to the reset button.
  
  
  
  code by:Fanis Katmadas
  site:oramasolutions.com
  fanisk@oramasolutions.com
 */
 


const int floor1 = 7;//proximity switch attached on floor1
const int floor2 = 6;//proximity switch attached on floor2
const int floor3 = 5;//proximity switch attached on floor3
const int callbutton1 = 4;//push button on the floor1 and in paraller the button for floor 1 in the elevator
const int callbutton2 = 3;//push button on the floor2 and in paraller the button for floor 2 in the elevator
const int callbutton3 = 2;//push button on the floor3 and in paraller the button for floor 3 in the elevator
const int relayup = 12;//the relay that drives up the elevator
const int relaydown=10;//the relay that drives down the elevator
const int buzzer = 11;//a buzzer warning movement or alarm stop
const int poweron=13;

// variables will change:
int callelevator1 = 0;         // variable for reading the pushbutton status of the floors
int callelevator2 = 0; // variable for reading the pushbutton status of the floors
int callelevator3 = 0; // variable for reading the pushbutton status of the floors
int floor1sense = 0; // variable for reading the proximity status of the floors
int floor2sense = 0; // variable for reading the proximity status of the floors
int floor3sense = 0; // variable for reading the proximity status of the floors


// the setup routine runs once when you press reset:
void setup() 

        {                
          
          // initialize the digital pins inputs.
          pinMode(floor1, INPUT);   
          pinMode(floor2, INPUT);
          pinMode(floor3, INPUT);
          pinMode(callbutton1, INPUT);
          pinMode(callbutton2, INPUT);
          pinMode(callbutton3, INPUT);

          
          // initialize the digital pins outputs.
          pinMode(relayup, OUTPUT);
          pinMode(relaydown, OUTPUT);
          pinMode(buzzer, OUTPUT);
          
        }


// the loop routine runs over and over again forever:
void loop() 


        {
            digitalWrite(poweron, HIGH);
            // read the state of the pushbuttons value:
            callelevator1 = digitalRead(callbutton1);
            callelevator2 = digitalRead(callbutton2);
            callelevator3 = digitalRead(callbutton3);
            // read the state of the proximity value:
            floor1sense = digitalRead(floor1);
            floor2sense = digitalRead(floor2);
            floor3sense = digitalRead(floor3);

            
            
            //start by checking the 3 call buttons.
            //we read the input and if we have signal we wait for the release before starting.
            //after the release a pause of a second is added before beggining the motion of the elevator
            if (callelevator1 == HIGH)// if the floor 1 call button is pressed
           
                    {     
                      delay(200);//software debounce of the button 
                      while(callelevator1 == HIGH)
                             {
                             callelevator1 = digitalRead(callbutton1);//check the value of the button again
                             delay(10);//keep running smoothly
                             }//wait for the relese of the button to continue
                      delay(1000);
                      floor1function();//go to the floor 1 fuction of the elevator
                    } 
            
            
            else if(callelevator2 == HIGH)// if the floor 2 call button is pressed
                    
                    {
                      delay(200); //software debounce of the button 
                      while(callelevator2 == HIGH)
                          {
                          callelevator2 = digitalRead(callbutton2);//check the value of the button again
                          delay(10);//keep running smoothly
                          }//wait for the relese of the button to continue
                      delay(1000);
                      floor2function();//go to the floor 2 fuction of the elevator
                    }
          
           else if(callelevator3 == HIGH)// if the floor 1 call button is pressed
                    
                    {
                      delay(200); //software debounce of the button  
                      while(callelevator3 == HIGH)
                        {
                        callelevator3 = digitalRead(callbutton3);//check the value of the button again
                        delay(10);//keep running smoothly
                        }//wait for the relese of the button to continue
                      delay(1000);
                      floor3function();//go to the floor 3 fuction of the elevator
                    }
           
            
                      
          digitalWrite(relayup, LOW); //keep the relay for up motion inactive
          digitalWrite(relaydown, LOW); //keep the relay for down motion inactive
          digitalWrite(buzzer, LOW);//keep the buzzer quite
                      
         
           
           
          delay(10);//a few delay just to keep running smoothly
            
        }


void floor1function()
       
       
       
        {
    
                     if(floor1sense  != HIGH) // check the proximity sensor of the first floor to see if the elevator is there
                    
                              {//if the elevator isn't there call it
                                
                                while( floor1sense==LOW) //check that the proximity of the first floor is low
                                 //the motor begins and stops when the appropriate floor proximity give the signal
                                    {
                                    digitalWrite(relaydown, HIGH);//drive the elevator down
                                    digitalWrite(buzzer, HIGH);//some noise in the mic
                                    floor1sense = digitalRead(floor1);
                                    delay(10);//a few delay to keep running the routine smoothly
                                    }
                                    
                              }
       
             
        }



void floor2function()
        
        
        
        {
                           

                            
                            if(floor3sense  == HIGH) // check the proximity sensor of the third floor to see if the elevator is there
                          
                                              {//if the elevator is there call it
                                                
                                                while( floor2sense==LOW)//the motor begins and stops when the appropriate floor proximity give the signal 
                                                 
                                                    {
                                                    digitalWrite(relaydown, HIGH);//drive the elevator down
                                                    digitalWrite(buzzer, HIGH);//some noise in the mic
                                                    floor2sense = digitalRead(floor2);
                                                    delay(10);//a few delay to keep running the routine smoothly
                                                    }
                                                 
     
                                               }
                              
                              
                              
                              
                              else if(floor1sense  == HIGH) // check the proximity sensor of the first floor to see if the elevator is there
                    
                                              {//if the elevator is there call it
                                                
                                                while( floor2sense==LOW)//the motor begins and stops when the appropriate floor proximity give the signal 
                                                 
                                                    {
                                                    digitalWrite(relayup, HIGH);//drive the elevator up
                                                    digitalWrite(buzzer, HIGH);//some noise in the mic
                                                    floor2sense = digitalRead(floor2);
                                                    delay(10);//a few delay to keep running the routine smoothly
                                                    }

                                                    
                                              }
     
        }



void floor3function()
        
        
        
        {
                         
                           if(floor2sense  == HIGH || floor1sense  == HIGH) // check the proximity sensor of the first and second floor to see if the elevator is there
                                    
                                              {//if the elevator is there call it
                                                
                                                while( floor3sense==LOW) //the motor begins and stops when the appropriate floor proximity give the signal
                                                 
                                                    {
                                                    digitalWrite(relayup, HIGH);//drive the elevator up
                                                    digitalWrite(buzzer, HIGH);//some noise in the mic
                                                    floor3sense = digitalRead(floor3);
                                                    delay(10);//a few delay to keep running the routine smoothly
                                                    }

                                              }
                     
        }
        


