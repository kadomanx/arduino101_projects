int ledPinler[] = {2,3,4,5,6,7,8};
int ledSayisi = 7;
int potPin = A0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ledSayisi; i++){ 
    pinMode(ledPinler[i], OUTPUT);
  }
}

void loop() {
  int hizSuresi = analogRead(potPin);
  Serial.println(hizSuresi);

  for (int i = 0; i < ledSayisi; i++) {
    digitalWrite(ledPinler[i], HIGH);
    delay(hizSuresi);
    digitalWrite(ledPinler[i], LOW);
  }

  for (int i = ledSayisi - 2; i > 0; i--){
    digitalWrite(ledPinler[i], HIGH);
    delay(hizSuresi);
    digitalWrite(ledPinler[i], LOW);
  }
}
