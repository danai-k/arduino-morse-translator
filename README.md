# Arduino Morse Code Translator

An interactive, physical Morse code translator built with an Arduino, an I2C LCD screen, a buzzer, an LED, and a custom input/clear button setup. Tap out dots and dashes, watch the visual feedback and read your translated message right on the screen !

Unlike standard LCD1602 screens that use the PCF8574 I2C expansion chip, Waveshare modules utilize the **AiP31068 controller**. Therefore, Standard Arduino libraries (such as `LiquidCrystal_I2C`) are incompatible with this chip. This repository provides a custom header driver (`WaveshareLCD.h`).

---

## Features

* **Real-time Feedback:** Flashes an LED and sounds a buzzer simultaneously as you tap.
* **Beginner-Friendly Timing:** Generous custom pauses (2 seconds for letters, 3 seconds for words) so you have time to look at a cheat sheet.
* **Automatic Row Wrapping:** Automatically jumps to the second row at 16 characters and clears/resets when the screen fills up.
* **Dedicated Clear Button:** A physical second button to instantly wipe the screen and reset your current word.
* **Startup Animation:** Displays a custom two-row welcome banner when powered on.

---

## Hardware Required
* **Microcontroller:** Arduino Uno, Nano, or compatible board.
* **Display:** Waveshare LCD1602 I2C Module (AiP31068 controller).
* **Input:** 2x Push Button.
* **Output:** 1x Buzzer, 1x LED.
* **Miscellaneous:** Breadboard, some Jumper Wires, and a 220Ω to 330Ω Resistor.
  
---

## Wiring Instructions



---

## Morse Code Alphabet Cheat Sheet





---

## File Structure

```text

```

---

## How to Install and Run


---
## License

This project is open-source and available under the [MIT License](LICENSE).
