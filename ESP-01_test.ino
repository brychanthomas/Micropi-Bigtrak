void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  delay(2000);
  Serial1.print("AT\r\n");
  delay(100);
  while (Serial1.available() > 0) {
    char recieved = Serial1.read();
    Serial.print(recieved);
  }
  Serial1.print("AT+CWMODE=1\r\n");
  delay(100);
  while (Serial1.available() > 0) {
    char recieved = Serial1.read();
    Serial.print(recieved);
  }
  Serial1.print("AT+CWLAP\r\n");

}

void loop() {
  while (Serial1.available() > 0) {
    char recieved = Serial1.read();
    Serial.print(recieved);
  }
}
