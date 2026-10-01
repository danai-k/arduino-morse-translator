#include <Wire.h>
#include <string.h>
#include "WaveshareLCD.h"

#define PIN_BUTTON 2
#define PIN_CLEAR_BUTTON 3
#define PIN_BUZZER 8
#define PIN_LED 9

unsigned long pressTime = 0;
unsigned long releaseTime = 0;
int buttonState = HIGH;
int lastButtonState = HIGH;
int clearState = HIGH;       
int lastClearState = HIGH;  
String currMorse = ""; // dots (.) or dashes (-)
bool spacePrinted = true;
int charCount = 0;

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

  if (charCount == 16) { lcd_send_cmd(0xC0); } // goto 2nd row
  else if (charCount >= 32) 
  {
    lcd_send_cmd(0x01); // Screen is full, cleaning
    charCount = 0;  
  }
}

void setup() {
  Wire.begin();
  lcd_init();

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_CLEAR_BUTTON, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  lcd_send_cmd(0x01);              
  lcd_print("       MORSE CODE   ");   
  lcd_send_cmd(0xC0);              
  lcd_print("   TRANSLATOR   ");   
  delay(2000);                     
  lcd_send_cmd(0x01);             
}

void loop() {
  // Clear Button
  clearState = digitalRead(PIN_CLEAR_BUTTON);
  if (clearState == LOW && lastClearState == HIGH) 
  {
    lcd_send_cmd(0x01);  
    currMorse = "";      
    spacePrinted = true;
    charCount = 0;
  }
  lastClearState = clearState;

  buttonState = digitalRead(PIN_BUTTON); // current state of button

  // 1. button just got pressed down
  if (buttonState == LOW && lastButtonState == HIGH) 
  {
    pressTime = millis(); // store exactly when it was pressed
    digitalWrite(PIN_LED, HIGH); // led = on
    tone(PIN_BUZZER, 1000); // buzzer = on
    spacePrinted = false; // new word
  }

  // 2. button released
  if (buttonState == HIGH && lastButtonState == LOW)
  {
    releaseTime = millis();
    digitalWrite(PIN_LED, LOW);
    noTone(PIN_BUZZER);

    unsigned long duration = releaseTime - pressTime; // how long the button was held down

    if (duration < 200 ){ currMorse += "."; }
    else { currMorse += "-"; }
  }
  lastButtonState = buttonState;

  // 3. End of letter
  if (buttonState == HIGH && (millis() - releaseTime > 600)) 
  {
    if (currMorse != "")
    {
      printCharacter(translateMorse(currMorse));
      currMorse = ""; // clear
    }
  }

  // 4. end of word
  if (buttonState == HIGH && (millis() - releaseTime > 3000)) 
  {
    if (spacePrinted == false) 
    {
      printCharacter(" ");
      spacePrinted = true; 
    }
  }
}
