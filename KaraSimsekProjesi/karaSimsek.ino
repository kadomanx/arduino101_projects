// Kullanacağım 7 LED'i sırasıyla Arduino'nun bu pinlerine dizdim. 
int ledPinler[] = {2, 3, 4, 5, 6, 7, 8};

// Döngülerde işim kolaylaşsın diye toplam LED sayımı sabitledim.
int ledSayisi = 7;

// Animasyonun hızını parmağımla ayarlayabilmek için bir potansiyometre (ayarlı direnç) ekledim.
// Analog sinyal okuyacağım için A0 pinini seçtim.
int potPin = A0;

void setup() {
  // Potansiyometreden hangi değerlerin geldiğini ekranda görebilmek (ve gerekirse hata ayıklamak) 
  // için seri haberleşmeyi başlattım.
  Serial.begin(9600);
  
  // Önceki koddaki gibi, tek tek yazmak yerine temiz bir döngüyle 
  // bütün LED pinlerini elektrik vereceğim birer çıktı (OUTPUT) olarak ayarladım.
  for (int i = 0; i < ledSayisi; i++){ 
    pinMode(ledPinler[i], OUTPUT);
  }
}

void loop() {
  // İlk işim potansiyometrenin o anki konumunu okumak. 
  // Buradan 0 ile 1023 arasında bir sayı geliyor ve ben bunu animasyonun "bekleme süresi" yapıyorum.
  // Düğmeyi çevirdikçe animasyon hızlanacak veya yavaşlayacak.
  int hizSuresi = analogRead(potPin);
  
  // Potansiyometreden gelen değeri bilgisayar ekranına yazdırıyorum ki ne olup bittiğini göreyim.
  Serial.println(hizSuresi);

  // 1. AŞAMA: Işığın baştan sona doğru kayması (Soldan sağa)
  for (int i = 0; i < ledSayisi; i++) {
    // Sıradaki LED'i yak...
    digitalWrite(ledPinler[i], HIGH);
    // ...potansiyometreden okuduğum süre kadar bekle...
    delay(hizSuresi);
    // ...ve söndür. Hemen ardından döngü bir sonraki LED'e geçecek.
    digitalWrite(ledPinler[i], LOW);
  }

  // 2. AŞAMA: Işığın geri dönmesi (Sağdan sola)
  // Burası ince ayar kısmı: En son LED zaten üstteki döngüde yandığı için, geri dönüşe
  // sondan bir önceki LED'den başlıyorum (ledSayisi - 2).
  // Ayrıca en başa kadar (0'a kadar) gitmiyorum, 1'de bırakıyorum (i > 0). 
  // Çünkü 0. LED'i zaten üstteki döngü başlar başlamaz yakacak. 
  // Eğer bunları yapmasaydım, ışık kenarlara geldiğinde iki kez yanar ve köşelerde takılmış gibi çirkin bir görüntü olurdu.
  for (int i = ledSayisi - 2; i > 0; i--){
    digitalWrite(ledPinler[i], HIGH);
    delay(hizSuresi);
    digitalWrite(ledPinler[i], LOW);
  }
}
