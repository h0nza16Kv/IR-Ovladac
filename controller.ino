#include <IRremote.h>

const int ledPin = 2;
const int buttonPins[] = {7, 6, 5, 4, 3, 1}; 

IRsend irsend(ledPin); 
bool buttonState[] = {false, false, false, false, false, false}; 

uint16_t irSignals[6][12] = {
  {4500, 4500, 560, 560, 560, 1690, 560, 560, 560, 1690, 1200, 300},  
  {4600, 4400, 580, 1700, 540, 600, 580, 560, 580, 1650, 800, 400},  
  {4300, 4700, 600, 600, 600, 1600, 600, 600, 600, 1750, 1500, 350},  
  {4700, 4300, 590, 1690, 570, 570, 590, 570, 590, 1600, 900, 500},  
  {4400, 4600, 570, 570, 570, 570, 570, 570, 570, 1700, 1000, 450},  
  {4550, 4450, 580, 1680, 560, 1700, 580, 580, 580, 580, 1100, 320}   
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    checkButton(buttonPins[i], buttonState[i], irSignals[i], 12, i);
  }
}

void checkButton(int buttonPin, bool &buttonState, uint16_t signal[], int length, int index) {
  if (digitalRead(buttonPin) == LOW) {
    if (!buttonState) {
      buttonState = true;
      Serial.print("Odesílám IR signál pro tlačítko ");
      Serial.println(index + 1);
      
      for (int j = 0; j < 3; j++) { 
        irsend.sendRaw(signal, length, 38);
        delay(100);
      }

      Serial.println("Signál byl odeslán!");
      delay(500);
    }
  } else {
    buttonState = false;
  }
}
