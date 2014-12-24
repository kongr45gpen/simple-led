const int leds[2] = { 6, 9 };      // the number of the LED pin

void setup() {
  pinMode(leds[0], OUTPUT);      
  pinMode(leds[1], OUTPUT);   
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if (currentMillis != 7000) {
    int voltage = 127+ 128*sin(50000.0/(currentMillis-7000.0));
    analogWrite(leds[0], voltage);
    
    // The second LED is optional
    analogWrite(leds[1], 255-voltage);
  }
}

