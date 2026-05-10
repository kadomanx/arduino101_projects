// 7 segmentli ekranımızın içindeki her bir LED çubuğunu (A'dan G'ye)
// Arduino'nun bu pinlerine bağladım.
int pinA = 3;
int pinB = 4;
int pinC = 5;
int pinD = 6;
int pinE = 7;
int pinF = 8;
int pinG = 9;

// Zarı atmamızı sağlayacak butonu da 2. pine taktım.
int butonPini = 2;

void setup() {
  // Ekran pinlerinin hepsini dışarıya sinyal vereceğimiz için çıktı (OUTPUT) yaptık.
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);

  // Burası çok önemli pratik bir detay: Buton için dışarıdan fazladan bir direnç
  // bağlamakla uğraşmamak için Arduino'nun içindeki dahili direnci (INPUT_PULLUP) aktif ettim.
  // Bu yüzden butona basılmadığında sistem '1' (HIGH), basıldığında '0' (LOW) okuyacak.
  pinMode(butonPini, INPUT_PULLUP);
  
  // Arduino aslında kendi kendine tam rastgele sayı üretemez, hep aynı sırayı takip eder.
  // Gerçek bir rastgelelik katmak için boşta duran A0 pinindeki elektriksel "gürültüyü" 
  // (havadaki dalgaları vs.) çekirdek olarak (seed) verdim. Artık zarlarımız cidden rastgele gelecek.
  randomSeed(analogRead(A0)); 
  
  // Başlangıçta ekranda anlamsız çizgiler yanmasın diye ekranı sıfırlayarak işe başlıyorum.
  ekraniTemizle(); 
}

void loop() {
  // Yukarıda PULLUP kullandığım için, butona "basıldı mı?" diye sormak yerine
  // "buton LOW'a çekildi mi?" diye kontrol ediyorum.
  if (digitalRead(butonPini) == LOW) {
    
    // -- ANİMASYON KISMI --
    // Zarı atar atmaz hemen sonucu göstermek yerine, gerçekçi olsun diye 
    // ekranda 10 kere art arda çok hızlı (50 milisaniye) rastgele sayılar gösteriyorum.
    // Tıpkı zarın masada yuvarlanması gibi. (Üst sınır 7 yazılı çünkü random fonksiyonu son sayıyı dahil etmez, 1 ile 6 arası üretir.)
    for(int i=0; i<10; i++){
      zarYazdir(random(1, 7));
      delay(50);
    }
    
    // -- ASIL ZAR SONUCU --
    // Animasyon bitti, şimdi asıl atışımızın sonucunu belirliyoruz.
    int gelenZar = random(1, 7); 
    zarYazdir(gelenZar);
    
    // Zarı attıktan sonra sistem 1 saniye beklesin. 
    // Yoksa elimiz butondayken saniyede yüzlerce kez zar atıp sistemi çıldırtabiliriz.
    delay(1000); 
  }
}

// Hangi sayının hangi LED çubuklarını yakacağını ayarladığım fonksiyon.
void zarYazdir(int sayi) {
  // Eski sayının çizgileri ekranda kalmasın diye her sayı yazmadan önce tahtayı siliyorum.
  ekraniTemizle();
  
  // Ekranımız "ortak anot" olduğu için, yakmak istediğim çizgiye LOW gönderiyorum.
  // Mesela 1 yazmak için sadece sağ taraftaki B ve C çubuklarının yanması yeterli.
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

// Bütün LED'leri söndürmek için hepsine HIGH (elektrik) veriyorum. 
// Çünkü anot ekranlar elektriği kesince (LOW) yanar, elektrik verince (HIGH) söner.
void ekraniTemizle() {
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
