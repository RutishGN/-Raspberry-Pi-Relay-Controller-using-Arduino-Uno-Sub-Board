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