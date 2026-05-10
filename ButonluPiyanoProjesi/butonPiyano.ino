int butonPinleri[] = {2, 3, 4, 5, 6};
int notalar[] = {200, 400, 600, 700, 900}; 

int buzzerPin = 8;
int butonSayisi = 5;

void setup() {
  for (int i = 0; i < butonSayisi; i++) {
    pinMode(butonPinleri[i], INPUT);
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  bool butonaBasildi = false; 

  for (int i = 0; i < butonSayisi; i++) {
    if (digitalRead(butonPinleri[i]) == HIGH) {
      tone(buzzerPin, notalar[i]);
      butonaBasildi = true;
      break; 
    }
  }

  if (butonaBasildi == false) {
    noTone(buzzerPin);
  }
}
