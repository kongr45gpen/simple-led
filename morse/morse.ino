const int morseDelay = 75;

const unsigned char letters[26][4] = {
  { 1, 3, 0, 0 },
  { 3, 1, 1, 1 },
  { 3, 1, 3, 1 },
  { 3, 1, 1, 0 },
  { 1, 0, 0, 0 },
  { 1, 1, 3, 1 },
  { 3, 3, 1, 0 },
  { 1, 1, 1, 1 },
  { 1, 1, 0, 0 },
  { 1, 3, 3, 3 },
  { 3, 1, 3, 0 },
  { 1, 3, 1, 1 },
  { 3, 3, 0, 0 },
  { 3, 1, 0, 0 },
  { 3, 3, 3, 0 },
  { 1, 3, 3, 1 },
  { 3, 3, 1, 3 },
  { 1, 3, 1, 0 },
  { 1, 1, 1, 0 },
  { 3, 0, 0, 0 },
  { 1, 1, 3, 0 },
  { 1, 1, 1, 3 },
  { 1, 3, 3, 0 },
  { 3, 1, 1, 3 },
  { 3, 1, 3, 3 },
  { 3, 3, 1, 1 }
};
  
const int led = 6;

void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);	
}

void loop() {
  if (Serial.available() > 0) {
    int inByte = Serial.read();

    // Convert to upper case
    if (inByte >= 97 && inByte <= 122) {
      inByte -= 32; 
    }

    if (inByte == 32) { // space
      delay(4 * morseDelay);
    } else if (inByte >= 65 && inByte <= 90) { // letter
      const unsigned char* morse = letters[inByte-65];

      for (int i = 0; i < 4; ++i) {
        if (morse[i] == 0) {
          break;
        } 

        digitalWrite(led, HIGH);
        delay(morse[i] * morseDelay);
        digitalWrite(led, LOW);
        delay(morseDelay);
      }
    } else if (inByte >= 48 && inByte <= 57) { // number
      char number = (inByte - 39)%10 + 1;

      for (int i = 0; i < 5; ++i) {
        const char code = ((1 + 2*(((10+(number+number/6)-i)%11)/6)));

        digitalWrite(led, HIGH);
        delay(code * morseDelay);
        digitalWrite(led, LOW);
        delay(morseDelay);
      }
    }
    
    // The space between letters is three units
    delay(2 * morseDelay);
  }
}
