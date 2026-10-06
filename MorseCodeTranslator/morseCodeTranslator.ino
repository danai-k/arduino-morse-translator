#include <Wire.h>
#include "WaveshareLCD.h"

#define PIN_BUTTON 2
#define CLEAR_BUTTON 3
#define BUZZER 8
#define LED 9

unsigned long pressTime = 0;
unsigned long releaseTime = 0;

int buttonState = HIGH;
int lastButtonState = HIGH;
int clearState = HIGH;       
int lastClearState = HIGH;  

String currMorse = ""; // dots (.) or dashes (-)
bool wordStarted = false;
int charCount = 0;

// can be changed
const unsigned long dotLimit = 200;
const unsigned long letterGap = 600;
const unsigned long wordGap = 3000;

// Morse Code Alphabet
const char* translateMorse(String morse){
  if (morse == ".-")   return "A";
  if (morse == "-...") return "B";
  if (morse == "-.-.") return "C";
  if (morse == "-..")  return "D";
  if (morse == ".")    return "E";
  if (morse == "..-.") return "F";
  if (morse == "--.")  return "G";
  if (morse == "....") return "H";
  if (morse == "..")   return "I";
  if (morse == ".---") return "J";
  if (morse == "-.-")  return "K";
  if (morse == ".-..") return "L";
  if (morse == "--")   return "M";
  if (morse == "-.")   return "N";
  if (morse == "---")  return "O";
  if (morse == ".--.") return "P";
  if (morse == "--.-") return "Q";
  if (morse == ".-.")  return "R";
  if (morse == "...")  return "S";
  if (morse == "-")    return "T";
  if (morse == "..-")  return "U";
  if (morse == "...-") return "V";
  if (morse == ".--")  return "W";
  if (morse == "-..-") return "X";
  if (morse == "-.--") return "Y";
  if (morse == "--..") return "Z";
  return "?";
}

void printCharacter(const char* text) {
  lcd_print(text);
  charCount++; 

  if (charCount == 16) 
  { 
    lcd_send_cmd(0xC0); // goto 2nd row
  } 
  else if (charCount >= 32) 
  {
    lcd_send_cmd(0x01); // Screen is full, clear
    charCount = 0;  
  }
}

void setup() {
  Wire.begin();
  lcd_init();

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(CLEAR_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  lcd_send_cmd(0x01);              
  lcd_print("       MORSE CODE   ");   
  lcd_send_cmd(0xC0);              
  lcd_print("   TRANSLATOR   ");   
  delay(2000);                     
  lcd_send_cmd(0x01);             
}

void loop() {
  // 1. CLEAR_BUTTON
  clearState = digitalRead(CLEAR_BUTTON);
  if (clearState == LOW && lastClearState == HIGH) // just pressed
  {
    lcd_send_cmd(0x01);  
    currMorse = "";      
    wordStarted = false;
    charCount = 0;
  }
  lastClearState = clearState;

  // 2. PIN_BUTTON
  int reading = digitalRead(PIN_BUTTON);
  if (reading != lastButtonState)
  {
    delay(50); // to avoid accidental double-click
    reading = digitalRead(PIN_BUTTON);
  }
  buttonState = reading;

  // 2.1. just pressed
  if (buttonState == LOW && lastButtonState == HIGH) 
  {
    pressTime = millis();
    digitalWrite(LED, HIGH); 
    tone(BUZZER, 1000); 
    wordStarted = true; // no space printed yet
  }
  
  // 2.2. just released
  if (buttonState == HIGH && lastButtonState == LOW)
  {
    releaseTime = millis();
    digitalWrite(LED, LOW);
    noTone(BUZZER);

    unsigned long duration = releaseTime - pressTime; // how long the button was held down

    if (duration < dotLimit )
    { 
      currMorse += "."; 
    }
    else 
    { 
      currMorse += "-"; 
    }
  }
  lastButtonState = buttonState;

  // 2.3. End of letter
  if (buttonState == HIGH && (millis() - releaseTime > letterGap)) 
  {
    if (currMorse != "")
    {
      printCharacter(translateMorse(currMorse));
      currMorse = ""; // clear
    }
  }

  // 2.4. end of word
  if (buttonState == HIGH && (millis() - releaseTime > wordGap)) 
  {
    if (wordStarted) 
    {
      printCharacter(" ");
      wordStarted = false; 
    }
  }
}
