
int B1Out = 4;
int B2Out = 5;
int A1Out = 6;
int A2Out = 7;
int APWM = 8;
int BPWM = 9;

void setup() {
  pinMode(A1Out, OUTPUT);
  pinMode(A2Out, OUTPUT);
  pinMode(B1Out, OUTPUT);
  pinMode(B2Out, OUTPUT);
  pinMode(APWM, OUTPUT);
  pinMode(BPWM, OUTPUT);
}

void loop() {
 analogWrite(APWM, 200);
 analogWrite(BPWM, 200);
 digitalWrite(A1Out, LOW);
 digitalWrite(A2Out, HIGH);
 digitalWrite(B1Out, LOW);
 digitalWrite(B2Out, HIGH);
 delay(2000);
 digitalWrite(A1Out, LOW);
 digitalWrite(A2Out, LOW);
 digitalWrite(B1Out, LOW);
 digitalWrite(B2Out, LOW);
 delay(1000);
 digitalWrite(A1Out, HIGH);
 digitalWrite(A2Out, LOW);
 digitalWrite(B1Out, HIGH);
 digitalWrite(B2Out, LOW);
 delay(2000);
 digitalWrite(A1Out, LOW);
 digitalWrite(A2Out, LOW);
 digitalWrite(B1Out, LOW);
 digitalWrite(B2Out, LOW);
 delay(1000);
}
