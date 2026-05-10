// Ekranla konuşabilmek için gerekli kütüphaneleri çağırıyorum. 
// I2C kullanmak kablo karmaşasını inanılmaz azaltıyor, 16 kablo yerine 4 kabloyla işi çözüyoruz.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Ekranımı tanıtıyorum. "0x27" bu modüllerin standart adresidir.
// 16, 2 ise ekranımın 16 sütun ve 2 satırdan oluştuğunu söylüyor.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Mesafe sensörümüzün (HC-SR04) pinleri.
// trigPin sesi yollayan, echoPin ise geri dönen yankıyı dinleyen kulak.
int trigPin = 8;
int echoPin = 9;

// Görsel ve işitsel uyarılar için donanımlarım.
int buzzer = 10;
int led = 11;

void setup() {
  // Pinlerin görevlerini dağıtıyorum.
  pinMode(trigPin, OUTPUT); // Ses dalgasını biz göndereceğiz (Çıktı)
  pinMode(echoPin, INPUT);  // Çarpıp geri dönen sesi dinleyeceğiz (Girdi)
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  
  // Ekranı uyandırıp arka plan ışığını açıyorum ki yazıları okuyabilelim.
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Süreyi ve ondan hesaplayacağımız mesafeyi tutacağımız değişkenler.
  // Sayılar büyük olabileceği için 'long' tercih ettim.
  long sure, mesafe;
  
  // -- SENSÖRÜ TETİKLEME KISMI --
  // Sensörün pürüzsüz çalışması için önce hattı temizliyor (LOW), 
  // sonra 10 mikrosaniyelik çok kısa bir sinyal (HIGH) gönderip kapatıyorum. 
  // Bu aslında sensöre "hadi ses dalgasını fırlat" deme şeklimiz.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Gönderdiğim sesin bir cisme çarpıp sensöre geri dönme süresini tutuyorum.
  sure = pulseIn(echoPin, HIGH);

  // -- HESAPLAMA KISMI --
  // Ufak bir fizik hesabı: Sesin gidip gelme süresini önce ikiye bölüyorum 
  // (çünkü bize sadece gidiş veya sadece dönüş mesafesi lazım).
  // Sonra havadaki ses hızının santimetre cinsinden sabitine (29.1) bölüyorum.
  mesafe = (sure / 2) / 29.1;

  // -- EKRANA YAZDIRMA KISMI --
  lcd.clear(); // Eski yazılar üst üste binmesin diye ekranı siliyorum.
  lcd.setCursor(0, 0); // İmleci en üst sol köşeye (0,0) aldım.
  lcd.print("MESAFE");
  lcd.setCursor(7, 0); // "MESAFE " kelimesinden sonrasına sayıyı yazdırıyorum.
  lcd.print(mesafe);
  
  // Burası işin biraz görsel düzen kısmı. Sayı tek haneli (8), çift haneli (45) 
  // veya üç haneli (120) olabilir. "cm" yazısı sabit kalırsa sayıyla üst üste biner 
  // veya arada boşluk kalır. Çirkin durmasın diye "cm" yazısının konumunu 
  // sayının uzunluğuna göre kaydırıyorum.
  if (mesafe < 10) {
    lcd.setCursor(9, 0); 
    lcd.print("cm");
  } 
  else if (mesafe < 100) {
    lcd.setCursor(10, 0); 
    lcd.print("cm");
  } 
  else if (mesafe < 1000) {
    lcd.setCursor(11, 0); 
    lcd.print("cm");
  }

  // -- ALARM KISMI (Park Sensörü Mantığı) --
  // Arabalardaki park sensörü nasıl çalışıyorsa tam olarak onu kurguladım.
  // Duvara ne kadar yaklaşırsak, döngü içindeki bekleme süresi (delay) o kadar azalıyor.
  // Yani LED ve Buzzer daha hızlı yanıp sönmeye başlıyor.
  
  if (mesafe <= 5) {
    // 5 cm ve altı: Çarpıyoruz! Çok acil uyarı (20 milisaniye). Neredeyse düz ötüyor.
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(20);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    delay(20);
  } 
  else if (mesafe <= 10) {
    // Biraz payımız var ama yine de hızlı uyarı.
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    delay(50);
  } 
  else if (mesafe <= 15) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(70);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    delay(70);
  } 
  else if (mesafe <= 20) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    delay(100);
  } 
  else if (mesafe <= 25) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(150);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    delay(150);
  } 
  else if (mesafe <= 30) {
    // 30 cm civarında yavaş yavaş uyarmaya başlıyor (250 milisaniye aralıklarla).
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    delay(250);
  }
  
  // Mesafe 30'dan fazlaysa hiçbir alarm koşuluna girmiyor (sessizlik).
  // Sistem başa sarmadan önce cihazı çok minik dinlendiriyorum.
  delay(10);
}
