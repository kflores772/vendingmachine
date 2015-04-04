#include <Servo.h>

#define quartSenPin A0
#define loonSenPin A1
#define toonSenPin A2
#define quartServoPin 11
#define loonServoPin 12
#define toonServoPin 13

float usrAmnt = 0;

int quartThreshold = 0;
int loonThreshold = 0;
int toonThreshold = 0;
boolean jammed = false;

Servo quartServo;
Servo loonServo;
Servo toonServo;

void setup()
{
  pinMode(quartSenPin, INPUT_PULLUP);
  pinMode(loonSenPin, INPUT_PULLUP);
  pinMode(toonSenPin, INPUT_PULLUP);

  quartServo.attach(quartServoPin);
  loonServo.attach(loonServoPin);
  toonServo.attach(toonServoPin);
  
  Serial.begin(9600);
}

void loop()
{
  
}

/*
 * detectCoinInput - checks if a coin has been inputted
 */
void detectCoinInput() //make this an interrupt??
{
  int quartSense = analogRead(quartSenPin);
  int loonSense = analogRead(loonSenPin);
  int toonSense = analogRead(toonSenPin);
  
  if (quartSense <= quartThreshold) {
  
  }
}

/*
 * dispenseCoin - takes in a coin type and the amount of times to dispense it
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

/*
 * giveChange - takes a dollar amount and dispenses coins to equal that amount
 * Input:
 *   - float changeAmnt: the amount of change that to be dispensed to the customer
 */
void giveChange(float changeAmnt)
{
  int dollarAmnt = int(changeAmnt);
  int centAmnt = int((changeAmnt-float(dollarAmnt))*10); //ex. 5.25 -> 25
  int nquart = 0; // number of quarters to dispense
  int ntoon = 0;
  int i = 0;
  
  // determine amount of quarters to dispense
  if (centAmnt > 0) {
    for (i=centAmnt; i>0; i=i-25) {
      nquart++;
    }
    
    dispenseCoin("quart", nquart);
  }
  
  // determine amount of toonies and loonies to dispense
  if (dollarAmnt > 0) {
    if (dollarAmnt >= 2) {
      // keep dispensing toonies until $1 or $0 remaining
      for (i=dollarAmnt; i>1; i=i-2) {
        ntoon++;
      }
      dispenseCoin("toon", nquart);
    }
    
    if (dollarAmnt == 1) {
      dispenseCoin("loon", 1); 
    }
  }
  
  usrAmnt = 0;
}
