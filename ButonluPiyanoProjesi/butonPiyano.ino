İşte tam da o kafa yapısıyla, sanki kodu yazarken bir yandan da kendi kendime notlar alıyormuşum gibi eklediğim yorum satırlarıyla kurgulanmış hali:

```cpp
// Kullanacağım 5 butonu sırasıyla Arduino'nun bu pinlerine bağladım.
int butonPinleri[] = {2, 3, 4, 5, 6};

// Her butona bastığımda çıkacak ses frekanslarını (notaları) aynı sırayla eşleştirdim.
int notalar[] = {200, 400, 600, 700, 900}; 

// Sesi verecek olan hoparlörü (buzzer) 8. pine taktım.
int buzzerPin = 8;

// Aşağıdaki döngülerde tekrar tekrar 5 yazmamak için toplam buton sayımı sabitledim.
int butonSayisi = 5;

void setup() {
  // Pinlerin görev dağılımını yapıyorum. Alt alta tek tek yazmak yerine 
  // temiz bir döngüyle bütün butonları hareket bekleyen girdi (INPUT) haline getirdim.
  for (int i = 0; i < butonSayisi; i++) {
    pinMode(butonPinleri[i], INPUT);
  }
  
  // Buzzer dışarıya ses vereceği için haliyle onu da çıktı (OUTPUT) olarak ayarladım.
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Her döngünün başında durumu sıfırlıyorum. 
  // Varsayılan kabulüm şu: "Şu an hiçbir tuşa basılmıyor."
  bool butonaBasildi = false; 

  // Bütün butonları sırayla gezmeye başlıyorum.
  for (int i = 0; i < butonSayisi; i++) {
    
    // Eğer o an baktığım butondan elektrik geliyorsa (yani butona basılmışsa)...
    if (digitalRead(butonPinleri[i]) == HIGH) {
      
      // ...hemen o butonun sırasına denk gelen notayı alıp buzzer'a gönderiyorum.
      tone(buzzerPin, notalar[i]);
      
      // Sesi başlattığım an, kontrol değişkenimi "evet, butona basıldı" olarak güncelliyorum.
      butonaBasildi = true;
      
      // Aynı anda iki butona birden basılırsa sistemin kafası karışmasın. 
      // İlk basılanı çaldıktan sonra bu aramayı kesip döngüden çıkıyorum.
      break; 
    }
  }

  // Güvenlik önlemim: Bütün butonlara baktım ve hiçbirine basılmadığını gördüysem...
  if (butonaBasildi == false) {
    // ...buzzer'a susmasını söylüyorum. 
    // Bunu yapmasaydım, elimi çeksem bile son nota sonsuza kadar ötmeye devam ederdi.
    noTone(buzzerPin);
  }
}

```
