int pinA = 3;
int pinB = 4;
int pinC = 5;
int pinD = 6;
int pinE = 7;
int pinF = 8;
int pinG = 9;

int butonPini = 2;

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);

  pinMode(butonPini, INPUT_PULLUP);
  randomSeed(analogRead(A0)); 
  
  ekraniTemizle(); 
}

void loop() {
  if (digitalRead(butonPini) == LOW) {
    for(int i=0; i<10; i++){
      zarYazdir(random(1, 7));
      delay(50);
    }
    
    int gelenZar = random(1, 7); 
    zarYazdir(gelenZar);
    
    delay(1000); 
  }
}

void zarYazdir(int sayi) {
  ekraniTemizle();
  
  if (sayi == 1) {
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
  } 
  else if (sayi == 2) {
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinG, LOW);
  } 
  else if (sayi == 3) {
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinG, LOW);
  } 
  else if (sayi == 4) {
    digitalWrite(pinB, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
  } 
  else if (sayi == 5) {
    digitalWrite(pinA, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
  } 
  else if (sayi == 6) {
    digitalWrite(pinA, LOW);
    digitalWrite(pinC, LOW);
    digitalWrite(pinD, LOW);
    digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);
    digitalWrite(pinG, LOW);
  }
}
void ekraniTemizle() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
