#define COUNT 4

const int buttonPin = 12;    // the number of the pushbutton pin
const int leds[COUNT] = { 3, 5, 9, 6 };      // the number of the LED pin

bool on = true;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  
  // set initial LED state
  for (int i = 0; i < COUNT; i++) {
    pinMode(leds[i], OUTPUT);
    analogWrite(leds[i], LOW);
  }
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        on = !on;
        
        if (!on) {
          for (int i = 0; i < COUNT; i++) {
            digitalWrite(leds[i], LOW);
          }
        }
      }
    }
  }

  // set the LED:
  if (reading == HIGH) {
    for (int i = 0; i < COUNT; i++) {
      analogWrite(leds[i], 255);
    }
  } else if (on) {
//    float speed = (200.0+1800.0*pow(sin(millis()/5000.0),2));
    float speed = 2000.0;
    for (int i = 0; i < COUNT; i++) {
      int factor = 255;
      if (i == 3) {
        factor = 64;
      }
      analogWrite(leds[i], factor*pow(sin(  millis()/speed  +i),2));
    }
  } else {
    for (int i = 0; i < COUNT; i++) {
      digitalWrite(leds[i], LOW);
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
