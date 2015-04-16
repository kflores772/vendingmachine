int total = 0;
int initialValue = 0;
int threshold = 0;
boolean coinDetected = false; // true when a coin is detected
int jamCounter = 0; // increments when coin is detected for 3 consecutive loops
boolean jammed = false; // true when sorter is jammed

void setup()  { 
  pinMode(A0, INPUT_PULLUP); // 1$ input
  Serial.begin(9600);
  
  initialValue = analogRead(A0);
  threshold = initialValue - 10;
  Serial.println(threshold);
} 

void loop() {
  int dollarSensor = analogRead(A0);

  Serial.println(dollarSensor);
  /*
  if (!jammed) {    
    // reset total once it reaches > 10 since it will never be > 10
    if (total > 10) {
      total = 0;
    }  
  
    if (dollarSensor <= threshold) {
      total = total + 1;
      
      Serial.print("Total: $");
      Serial.print(total);
      Serial.print(".00");
      Serial.println(" ");
      
      coinDetected = true; 
      delay(300);
    }
    
    if (coinDetected) {
      jamCounter++;
      
      if (jamCounter >= 5) {
        jammed = true;
      }
    } 
    
    coinDetected = false;
  } else {
    Serial.println("Coin is jammed!");
    
    if (dollarSensor == initialValue) {
      jammed = false;
    }
  }
  */
  delay(100);
}
