# Raspberry Pi Relay Controller using Arduino Uno

This project demonstrates how to control a **16-channel relay module** using a **Raspberry Pi** in combination with an **Arduino Uno sub-board** via serial communication. The Raspberry Pi sends commands over USB serial, and the Arduino switches the relays accordingly.

---

## Why use Arduino Uno?

The **Raspberry Pi uses 3.3V logic**, while many relay modules require **5V logic** to trigger reliably. To avoid using logic level shifters or risking unstable triggering, an **Arduino Uno** is used as a sub-board:

- ✅ Arduino Uno provides **5V logic output**, compatible with most relay modules.
- ✅ It offloads the real-time control of relays from the Raspberry Pi.
- ✅ Simple and effective serial communication between the Pi and Arduino.

---

## System Overview

**Architecture:**

- **Raspberry Pi** sends serial commands to **Arduino Uno**.
- **Arduino** interprets and executes `ON <relay_num>` or `OFF <relay_num>` to control relay channels.

---

## Arduino Code

Upload this code to your Arduino Uno using the Arduino IDE:

```cpp
// Pin definitions for the 16 relays
const int relayPins[16] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 16; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }
  Serial.println("Ready");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command.startsWith("ON ")) {
      int relayNum = command.substring(3).toInt() - 1;
      if (relayNum >= 0 && relayNum < 16) {
        digitalWrite(relayPins[relayNum], HIGH);
        Serial.print("Relay ");
        Serial.print(relayNum + 1);
        Serial.println(" ON");
      }
    } else if (command.startsWith("OFF ")) {
      int relayNum = command.substring(4).toInt() - 1;
      if (relayNum >= 0 && relayNum < 16) {
        digitalWrite(relayPins[relayNum], LOW);
        Serial.print("Relay ");
        Serial.print(relayNum + 1);
        Serial.println(" OFF");
      }
    }
  }
}
