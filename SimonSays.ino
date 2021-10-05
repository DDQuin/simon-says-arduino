
void lightLED(int pin, int pitch, int times);

const int red = 0;
const int yellow = 1;
const int green = 2;
const int blue = 3;
const int piezoPin = 3;

const int LEDPins[] = {12, 10, 8, 6};
const int buttonPins[] = {13, 5, 9, 7};
int LEDOrder[200];
int index;
int isShowing;
int playerIndex;


void setup() {
  randomSeed(analogRead(0));
  for (int i = 0; i < 4; i++) {
    pinMode(LEDPins[i],OUTPUT);
    pinMode(buttonPins[i],INPUT);
  }
  reset();

}

void loop() {
  if (isShowing == 1) {
    LEDOrder[index] = random(4);
    index++;
    for (int i = 0; i < index; i++) {
      int color = LEDOrder[i];
      lightLED(LEDPins[color], 400, 50);
    }
    isShowing = 0;
    playerIndex = 0;
    return;
  }
  for (int i = 0; i < 4; i++) {
    int curButtonState = digitalRead(buttonPins[i]);
    if (curButtonState == HIGH) {
   
      if (LEDOrder[playerIndex] == i) {
        // right color
        lightLED(LEDPins[i], 350, 50);
        playerIndex++;
        // in this case player has sucessfully completed a sequence
        if (playerIndex >= index) {
          isShowing = 1;
        }
      } else {
        //wrong color so reset
        resetLights();
        reset();
      }
      //return so in each loop we only focus on one color so multiple buttons cant be pressed
      return;
    }
  }

}

void lightLED(int pin, int pitch, int times) {
  digitalWrite(pin, HIGH);
  tone(piezoPin, pitch, times);
  delay(400);
  digitalWrite(pin, LOW);
  delay(200);
}

void resetLights() {
  tone(piezoPin, 100, 200);
  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDPins[i], HIGH);
  }
  delay(250);
  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDPins[i], LOW);
  }
  delay(250);
  tone(piezoPin, 100, 200);
  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDPins[i], HIGH);
  }
  delay(250);
  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDPins[i], LOW);
  }
  delay(500);
}
 
void reset() {
  index = 0;
  isShowing = 1;

}
