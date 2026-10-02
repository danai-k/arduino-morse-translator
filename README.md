# Arduino Morse Code Translator

An interactive, physical Morse code translator built with an Arduino, an I2C LCD screen, a buzzer, an LED, and a custom input/clear button setup. Tap out dots and dashes, watch the visual feedback and read your translated message right on the screen !

Unlike standard LCD1602 screens that use the PCF8574 I2C expansion chip, Waveshare modules utilize the **AiP31068 controller**. Therefore, Standard Arduino libraries (such as `LiquidCrystal_I2C`) are incompatible with this chip. This repository provides a custom header driver (`WaveshareLCD.h`).

---

## Features

* **Custom Waveshare Driver:**  Low-level I2C communication tailored for the AiP31068 controller (`0x3E` / `0x27` address).
* **Live Audio/Visual Feedback:** The LED and buzzer trigger exactly while the input button is held down.
* **Non-Blocking Timer Logic:** Built using `millis()` math rather than `delay()`, ensuring instant button responsiveness.
* **Beginner-Friendly Timing:** Generous custom pauses (2 seconds for letters, 3 seconds for words) so you have time to look at a cheat sheet.
* **Auto Word-Wrap:** Automatically drops down to the second row after 16 characters, and completely wipes the screen clean when 32 characters are reached.
* **Dedicated Clear Button:** A physical second button to instantly wipe the screen and reset your current word.

---

## Hardware Required
* **Microcontroller:** Arduino Uno, Nano, or compatible board.
* **Display:** Waveshare LCD1602 I2C Module (AiP31068 controller).
* **Input:** 2x Push Button (1 for tapping Morse, 1 for clearing the screen).
* **Output:** 1x Buzzer, 1x LED.
* **Miscellaneous:** Breadboard, some Jumper Wires, and a 220Ω to 330Ω Resistor (to protect the LED).
  
---

## Wiring Instructions

Follow these step-by-step connections to wire up your components:

### 1. Ground & Power setup
* Connect a wire from the **GND** pin on your Arduino to the **`-` (ground) rail** on your breadboard. (Allows all components to share a common ground drain).

### 2. Waveshare LCD1602 Module (I2C)
* Connect **VCC** to the Arduino **5V** pin.
* Connect **GND** to the breadboard **GND rail**.
* Connect **SDA** to Arduino pin **A4** (or dedicated SDA pin).
* Connect **SCL** to Arduino pin **A5** (or dedicated SCL pin).

### 3. Input Buttons
* **Input Button (Morse Tap):** 
  * Connect **Leg 1** to Arduino Digital Pin **2**.
  * Connect **Leg 2** to the breadboard **GND rail**.
* **Clear Screen Button:**
  * Connect **Leg 1** to Arduino Digital Pin **3**.
  * Connect **Leg 2** to the breadboard **GND rail**.

### 4. Audio / Visual Feedback
* **Buzzer:** 
  * Connect the **Positive (+ / longer leg)** to Arduino Digital Pin **8**.
  * Connect the **Negative (- / shorter leg)** to the breadboard **GND rail**.
* **LED:**
  * Connect the **Positive (+ / longer leg)** to Arduino Digital Pin **9**.
  * Connect the **Negative (- / shorter leg)** to a **Resistor (220Ω to 330Ω)**, then connect the other end of the resistor to the breadboard **GND rail**.


---

## Customizing Timing Durations

By default, this code is set up with slower wait times so beginners have time to read a Morse Code dictionary between taps. You can easily adjust these speeds in `MorseTranslator.ino`. 

| Phase                       | Standard Morse Timing | Default Project Timing  |
|  ---                        |  ---                  |  ---                    |
| **Dot (`.`) vs Dash (`-`)** | 200 ms                | **200 ms** (Unchanged)  |
| **End of Letter**           | 600 ms                | **2000 ms** (2 Seconds) |
| **End of Word (Space)**     | 1400 ms               | **3000 ms** (3 Seconds) |

---

## Morse Code Alphabet Cheat Sheet

Here is the standard International Morse Code alphabet programmed into this translator. 
* **Dot (`.`)** = Quick tap (under 200ms)
* **Dash (`-`)** = Long hold (over 200ms)

| Letter | Morse Code | &nbsp;&nbsp;&nbsp;&nbsp; | Letter | Morse Code |
| :---: | :--- | :--- | :---: | :--- |
| **A** | `.-` | | **N** | `-.` |
| **B** | `-...` | | **O** | `---` |
| **C** | `-.-.` | | **P** | `.--.` |
| **D** | `-..` | | **Q** | `--.-` |
| **E** | `.` | | **R** | `.-.` |
| **F** | `..-.` | | **S** | `...` |
| **G** | `--.` | | **T** | `-` |
| **H** | `....` | | **U** | `..-` |
| **I** | `..` | | **V** | `...-` |
| **J** | `.---` | | **W** | `.--` |
| **K** | `-.-` | | **X** | `-..-` |
| **L** | `.-..` | | **Y** | `-.--` |
| **M** | `--` | | **Z** | `--..` |

---

## File Structure

```text
arduino-waveshare-morse/
├── WaveshareLCD.h      # Custom driver header for Waveshare AiP31068 display
├── MorseTranslator.ino # Main sketch containing logic, timings, and dictionary
└── README.md           # Project documentation
```

---

## How to Install and Run

1. **Clone or Download** this repository:
   ```bash
   git clone [https://github.com/YOUR-USERNAME/arduino-waveshare-morse.git](https://github.com/YOUR-USERNAME/arduino-waveshare-morse.git)
   ```
2. Open `MorseTranslator.ino` in the **Arduino IDE**.
3. Ensure `WaveshareLCD.h` is located in the same directory as `MorseTranslator.ino` 
4. Verify the I2C address in `WaveshareLCD.h` matches your module:
   ```cpp
   #define LCD_ADDR 0x3E  // Default Waveshare address (change to 0x27 if needed)
   ```
5. Select your Board (e.g., **Arduino Uno**) under **Tools > Board**.
6. Select your COM port under **Tools > Port**.
7. Click **Upload**.

---

## License

This project is open-source and available under the [MIT License](LICENSE).
