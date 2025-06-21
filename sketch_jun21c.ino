const int relayPins[16] =  {
  A0, A1, A2, A3, A4, A5, 10, 11, // Relays 1-8
  9, 8, 7, 6, 5, 4, 3, 2         // Relays 9-16
};

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
      if (command.equals("OFF ALL")) {
        for (int i = 0; i < 16; i++) {
          digitalWrite(relayPins[i], LOW);
        }
        Serial.println("All relays OFF");
      } else {
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
}