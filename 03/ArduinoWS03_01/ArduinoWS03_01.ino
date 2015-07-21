
const int ledPin01 = 9;
char received;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin01, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) {
      received = (char)Serial.read();
      Serial.println(received);
      digitalWrite(ledPin01,HIGH);
      delay(1000);
      digitalWrite(ledPin01,LOW);
  }
}
