int B1Out = 4;
int B2Out = 5;
int A1Out = 6;
int A2Out = 7;
int APWM = 8;
int BPWM = 9;

void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  Serial1.print("AT+CWMODE=2\r\n");
  delay(100);
  Serial1.print("AT+CIPMUX=1\r\n");
  delay(100);
  Serial1.print("AT+CIPSERVER=1,80\r\n");
  delay(100);
  Serial1.print("AT+CWSAP=\"BigTrak\",\"ArduinoMega\",2,3\r\n");
  delay(100);
  emptySerialBuffer();
}

int leftMotorSpeed;
int rightMotorSpeed;
bool leftMotorSpeedNegative;
bool rightMotorSpeedNegative;
char previousChar;
char newestChar=' ';
int parsedNumbers[4] = {};
void loop() {
  bool validConnection = false;
  while (Serial1.available()==0) {}
  delay(50);
  while (Serial1.available() > 0) {
    previousChar = newestChar;
    newestChar = Serial1.read();
    if (previousChar=='/' and newestChar=='?') {
      validConnection = true;
      int i;
      int number;
      for (i=0; i<5; i+=1) {
        number = Serial1.parseInt();
        parsedNumbers[i]=number;
      }
      emptySerialBuffer();
    }
  }
  if (validConnection) {
    leftMotorSpeed = parsedNumbers[0];
    rightMotorSpeed = parsedNumbers[1];
    if (parsedNumbers[2]==1) {
      leftMotorSpeedNegative = true;
    } else {
      leftMotorSpeedNegative = false;
    }
    if (parsedNumbers[3]==1) {
      rightMotorSpeedNegative = true;
    } else {
      rightMotorSpeedNegative = false;
    }
    setLeftMotorSpeed(leftMotorSpeed, leftMotorSpeedNegative);
    setRightMotorSpeed(rightMotorSpeed, rightMotorSpeedNegative);
  }
  Serial1.print("AT+CIPCLOSE=0\r\n");
  delay(50);
  emptySerialBuffer();
}

void emptySerialBuffer() {
  while (Serial1.available()>0) {
    Serial1.read();
  }
}

void setLeftMotorSpeed(int motorSpeed, bool reverse) {
  if (reverse == false) {
    digitalWrite(A1Out, LOW);
    digitalWrite(A2Out, HIGH);
  } else {
    digitalWrite(A1Out, HIGH);
    digitalWrite(A2Out, LOW);
  }
  if (motorSpeed == 0) {
    digitalWrite(A1Out, LOW);
    digitalWrite(A2Out, LOW);
    analogWrite(APWM, 0);
  } else if (motorSpeed <= 200) {
    analogWrite(APWM, motorSpeed);
  }
}

void setRightMotorSpeed(int motorSpeed, bool reverse) {
  if (reverse == false) {
    digitalWrite(B1Out, LOW);
    digitalWrite(B2Out, HIGH);
  } else {
    digitalWrite(B1Out, HIGH);
    digitalWrite(B2Out, LOW);
  }
  if (motorSpeed == 0) {
    digitalWrite(B1Out, LOW);
    digitalWrite(B2Out, LOW);
    analogWrite(BPWM, 0);
  } else if (motorSpeed <= 200) {
    analogWrite(BPWM, motorSpeed);
  }
}
