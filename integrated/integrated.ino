#include <Servo.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

#define redLedPin 32
#define greenLedPin 31
#define blueLedPin 26
#define photoResPin A0
#define quartSenPin 18
#define loonSenPin 19
#define toonSenPin 20
#define quartServoPin 49
#define loonServoPin 51
#define toonServoPin 53

const byte ROWS = 4; // Number of rows in keypad
const byte COLS = 2; // Number of columns in keypad
byte rowPins[ROWS] = {2,3,4,5}; // row keypad pin connections to Arduino pins
byte colPins[COLS] = {6,7}; //coloumn keypad pin connections to Arduino pins

char keys[ROWS][COLS] = {
  {'B','A'},
  {'6','3'},
  {'5','2'},
  {'4','1'}
};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //Initialize pins for LCD

float usrAmnt = 0;
float tolerance = 10;
float highTol = 1+(tolerance/100);
float lowTol = 1-(tolerance/100);

int i;

int fiveRef[] = {241, 650, 864};
int tenRef[] = {0, 0 ,0};
//int twentRef = [0, 0, 0];
int photoResSense[] = {0, 0, 0};

Servo quartServo;
Servo loonServo;
Servo toonServo;

bool isStopped = false;
bool scanned = false;

void setup()
{
  pinMode(14, OUTPUT);
  //pinMode(38, OUTPUT);
  
  digitalWrite(14, LOW);
  //digitalWrite(38, LOW);

  lcd.begin(16, 2);   // Set up the LCD's number of columns and rows: 

  // This effectively inverts the behavior of the INPUT mode, where HIGH means the sensor is off, and LOW means the sensor is on.
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  
  pinMode(photoResPin, INPUT_PULLUP);
  
  pinMode(quartSenPin, INPUT_PULLUP);
  pinMode(loonSenPin, INPUT_PULLUP);
  pinMode(toonSenPin, INPUT_PULLUP);
  
  
  attachInterrupt(5, add25Cents, RISING); //check rising
  attachInterrupt(4, add1Dollar, RISING);
  attachInterrupt(3, add2Dollar, RISING);

  quartServo.attach(quartServoPin);
  loonServo.attach(loonServoPin);
  toonServo.attach(toonServoPin);
  
  quartServo.write(10);
  loonServo.write(0);
  toonServo.write(0);
  
  Serial.begin(9600);
}

void loop()
{
  /*Serial.print("Total: $");
  Serial.print(usrAmnt);
  Serial.println(" ");
  */
    lcd.setCursor(0, 0); // Set where to print on the LCD (column, row)
  char keyPressed = keypad.getKey();
  float priceItem1 = 1.50;
  float priceItem2 = 1.25;
  float priceItem3 = 0.75;
  float priceItem4 = 2.00;
  
  if (!scanned) {
  int scan = senseBills();
    if (scan == 5) {
      usrAmnt += 5.0;
      scanned = true;
      lcd.clear();
      lcd.print("Total: $");
      lcd.print(usrAmnt); 
    }
  }
  
  Serial.println(usrAmnt);
  
  if (keyPressed == '1')
  {
    lcd.clear();
    lcd.print("Price: $");
    lcd.print(priceItem1);
  }
  else if (keyPressed == '2')
  {
    lcd.clear();
    lcd.print("Price: $");
    lcd.print(priceItem2);
  }
  else if (keyPressed == '3')
  {
    lcd.clear();
    lcd.print("Price: $");
    lcd.print(priceItem3);
  }
  else if (keyPressed == '4')
  {
    lcd.clear();
    lcd.print("Price: $");
    lcd.print(priceItem4);
  }
  else if (keyPressed == '5')
  {
    lcd.clear();
    lcd.print("Price: $1.00");
    lcd.setCursor(0,1);
    lcd.print("Random Selection");
    lcd.setCursor(0,0);
  }
  else if (keyPressed == 'A')
  {
    lcd.clear();
    lcd.print("Dispensing...");
    digitalWrite(14, HIGH);
    delay(750);
    digitalWrite(14, LOW);
    lcd.clear();
    lcd.print("Enjoy!");
    delay(2500);
    giveChange(3.50);
    lcd.clear();
  }
  else if (keyPressed == 'B')
  {
    lcd.clear();
    lcd.print("Change returned");
    delay(2500);
    lcd.clear();
  }
    
  /*if (!isStopped) {
    
  for (int i=0; i<2; i++) {
    quartServo.write(10);
    loonServo.write(0);
    toonServo.write(0); 
    delay(2000);
    quartServo.write(180);
    loonServo.write(180);
    toonServo.write(180);
    delay(2000);
  }
  quartServo.write(10);
  loonServo.write(0);
  toonServo.write(0);
  
  //giveChange(1.75);

    isStopped = true;
  }*/
}

bool checkFor5() {
  int count = 0;
  for (i=0; i<3; i++) {
    if ((photoResSense[0] <= fiveRef[0]*highTol) && (photoResSense[0] >= fiveRef[0]*lowTol)) {
      count++; 
    }
  }
  
  if (count == 3) {
    return true; 
  } else {
    return false; 
  }
}

bool checkFor10() {
  int count = 0;
  for (i=0; i<3; i++) {
    if ((photoResSense[0] <= tenRef[0]*highTol) && (photoResSense[0] >= tenRef[0]*lowTol)) {
      count++; 
    }
  }
  
  if (count == 3) {
    return true; 
  } else {
    return false; 
  }
}

int senseBills() {
    int count = 0;
  
    digitalWrite(redLedPin, HIGH);
    delay(100);
    photoResSense[0] = analogRead(photoResPin);
    delay(100);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    delay(100);
    photoResSense[1] = analogRead(photoResPin);
    delay(100);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(blueLedPin, HIGH);
    delay(100);
    photoResSense[2] = analogRead(photoResPin);
    delay(100);
    digitalWrite(blueLedPin, LOW);
    
    
    /*Serial.print("R: ");
    Serial.print(photoResSense[0]);
    Serial.print(" ");
    Serial.print("B: ");
    Serial.print(photoResSense[1]);
    Serial.print(" "); 
    Serial.print("G: ");
    Serial.print(photoResSense[2]);
    Serial.println(" "); */    
    
    if (checkFor5()) {
      Serial.println("$5 bill detected");
      return 5; 
    }
    
    return 0;
}

/*
 * add25Cents: called when a quarter has been inputted
 */
void add25Cents() 
{
  noInterrupts();
  usrAmnt = usrAmnt + 0.25;
  // print usramnt
  interrupts();
}

/*
 * add1Dollar: called when a loonie has been inputted
 */
void add1Dollar()
{
  noInterrupts();
  usrAmnt = usrAmnt + 1;
  interrupts();
}

/*
 * add2Dollar: called when a toonie has been inputted
 */
void add2Dollar()
{
  noInterrupts();
  usrAmnt = usrAmnt + 2;
  interrupts();
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
    coinServo.write(0);
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
  int centAmnt = int((changeAmnt-float(dollarAmnt))*100); //ex. 5.25 -> 25
  int nquart = 0; // number of quarters to dispense
  int ntoon = 0;
  int i = 0;
  /*
  Serial.println("change amount: ");
  Serial.print(changeAmnt);
    Serial.println("dollar amount: ");
  Serial.println(dollarAmnt);
    Serial.println("cent amount: ");
  Serial.println(centAmnt);*/
  
  // determine amount of quarters to dispense
  if (centAmnt > 0) {
    for (i=centAmnt; i>0; i=i-25) {
      nquart++;
    }
    
    dispenseCoin("quart", nquart);
  }
  
  // determine amount of toonies and loonies to dispense
  if (dollarAmnt > 0) {
      for (i=dollarAmnt; i>0; i=i-2) {
        if (i >= 2) {
          ntoon++;
        }
        if (i == 1) {
          dispenseCoin("loon", 1); 
        }
      }
      dispenseCoin("toon", ntoon);    
  }
  
  usrAmnt = 0;
}

/*
 * detectCoinInput - checks if a coin has been inputted
 *
void detectCoinInput() //make this an interrupt??
{
  int quartSense = analogRead(quartSenPin);
  int loonSense = analogRead(loonSenPin);
  int toonSense = analogRead(toonSenPin);
  
  if (quartSense <= quartThreshold) {
  
  }
}*/
