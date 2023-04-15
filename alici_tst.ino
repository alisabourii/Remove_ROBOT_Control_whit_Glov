#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h> // atoi() fonksiyonu için string kütüphanesi tanımlanıyor
#include <SPI.h>

Enrf24 nRF(9, 10, 2);  // CE , CSN/CS/SS , IRQ bacaklarının Arduino ile bağlantıları tanımlandı

const byte alici_adresi[] = { 0xDE, 0xAD, 0xBE, 0x0F, 0x01 };

int LED1=3;

void setup() 
{
  pinMode(LED1, OUTPUT); // aç kapat yapılacak LED için pin modu çıkış ayarlandı

  SPI.begin(); // SPI başlat
  SPI.setDataMode(SPI_MODE0); // SPI MODE0 seçildi, nrf24l01 MODE0 ile iletişim kurmaktadır
  SPI.setBitOrder(MSBFIRST); // bit sıralaması MSB'den LSB'ye doğru ayarlandı

  // datarate 250000/1000000/2000000, channel 0/125
  // 1000000 datarate seçildi , 124 nolu kanal seçildi
  nRF.begin(1000000,124); 

  nRF.setRXaddress(alici_adresi); // alıcı adresi ayarlandı
  
  nRF.enableRX();  // Dinlemeye başla
}

void loop()
{
  char gelen_bilgi[33]; // gelen string türünde bilgi için geçici dizi değişken
  int bilgi=0; // string değeri sayısal değere dönüştürdükten sonra aktarılacak değişken tanımlanıyor

  if (nRF.read(gelen_bilgi))  // bilgi geldiyse bunu gelen_bilgi değişkenine aktar
  {
    bilgi = atoi(gelen_bilgi);

    
    if(gelen_bilgi[0]=='A') // eğer gelen_bilgi dizinin ilk karakteri A ise
    {
      digitalWrite(LED1, 1); // LED2'yi yak
    }
    else if(gelen_bilgi[0]=='K') // eğer gelen_bilgi dizinin ilk karakteri K ise
    {
      digitalWrite(LED1, 0); // LED2'yi söndür
    }
  }
}