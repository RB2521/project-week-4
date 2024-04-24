void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A0, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(true){
    digitalWrite(8, HIGH);
    delay(100);
    digitalWrite(A2, HIGH);
    delay(100);
    digitalWrite(A1, HIGH);
    delay(100);
    digitalWrite(A0, HIGH);
    delay(100);

    digitalWrite(8, LOW);
    delay(100);
    digitalWrite(A2, LOW);
    delay(100);
    digitalWrite(A1, LOW);
    delay(100);
    digitalWrite(A0, LOW);
    delay(100);
  }
}
