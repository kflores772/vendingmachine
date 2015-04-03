/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep

 Change "loops" to the amount of coins you want to dispense

*/ 

#include <Servo.h> 
 
Servo toonieServo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 
int loops = 0; // amount of times the function will loop
boolean stop = false;
 
void setup() 
{ 
  toonieServo.attach(8);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  
  toonieServo.write(0);
  
  delay(2000);
  
  toonieServo.write(180);
  
  delay(2000);
  /*if(!stop)
  {
    for (int i = 0; i<=loops-1; i+=1)
    {
      for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(5);                       // waits 15ms for the servo to reach the position 
      } 
      for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
      {                                
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(5);                       // waits 15ms for the servo to reach the position 
      }
      if (i == loops-1)
      {
        stop = true;
      }
    }
  }*/
}
