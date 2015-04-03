#include <Servo.h>

Servo quartServo;
Servo loonServo;
Servo toonServo;
int quartPin = 13;
int loonPin = 12;
int toonPin = 11;

void setup()
{
 quartServo.attach(quartPin);
 loonServo.attach(loonPin);
 toonServo.attach(toonPin);
}

void loop()
{
  dispenseCoin("loon", 4);
}

/*
 * dispenseCoin
 * Input: 
 *  - String coin: "quart" for quarter, "loon" for loonie, "toon" for toonie
 *  - int times: the amount of times to dispense a coin
 */

void dispenseCoin(String coin, int times)
{
  Servo coinServo;
  int i = 0;
  
  if (coin == "quart") {
    coinServo = quartServo;
  } else if (coin == "loon") {
    coinServo = loonServo;
  } else if (coin == "toon") {
    coinServo = toonServo;
  }
  
  for (i = 0; i<times; i++) {
    coinServo.write(0); 
    delay(2000);
    coinServo.write(180);
    delay(2000);
  }
}
