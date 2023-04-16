#include <Enrf24.h>
#include <nRF24L01.h>
#include <SPI.h>

Enrf24 nRF(9, 10, 3);  // CE , CSN/CS/SS , IRQ bacaklarının Arduino ile bağlantıları tanımlandı

// verici adresi tanımlandı aynı adres alıcıda da tanımlanmalıdır
const byte verici_adresi[] = { 0xDE, 0xAD, 0xBE, 0x0F, 0x01 };

int ac_kapat=0; // alıcının LED'i kapatıp açmak için gerekli bir değişken tanımlandı
int BUTON=4;

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTON, INPUT_PULLUP); // buton için 3 nolu pin ayarı input yapıldı

  SPI.begin(); // SPI başlat
  SPI.setDataMode(SPI_MODE0); // SPI MODE0 seçildi, nrf24l01 MODE0 ile iletişim kurmaktadır
  SPI.setBitOrder(MSBFIRST); // bit sıralaması MSB'den LSB'ye doğru ayarlandı
  
  // datarate 250000/1000000/2000000, channel 0/125
  // 1000000 datarate seçildi , 124 nolu kanal seçildi
  nRF.begin(1000000,124);  

  nRF.setTXaddress(verici_adresi); // verici adresi ayarlandı
}

void loop() 
{

  if(digitalRead(BUTON) == 0){
    Serial.println("A");
    nRF.print("A"); 
    nRF.flush(); 
  }
  else{
     Serial.println("K");
     nRF.print("K"); 
     nRF.flush();  
  }
   delay(200); 
  
}
