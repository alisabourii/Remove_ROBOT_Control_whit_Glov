#include <Enrf24.h>
#include <nRF24L01.h>
#include <SPI.h>

#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

Enrf24 nRF(9, 10, 3);  // CE , CSN/CS/SS , IRQ bacaklarının Arduino ile bağlantıları tanımlandı

// verici adresi tanımlandı aynı adres alıcıda da tanımlanmalıdır
const byte verici_adresi[] = { 0xDE, 0xAD, 0xBE, 0x0F, 0x01 };


int BUTON=4;

long timer = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTON, INPUT_PULLUP); // buton için 3 nolu pin ayarı input yapıldı

  SPI.begin(); // SPI başlat
  SPI.setDataMode(SPI_MODE0); // SPI MODE0 seçildi, nrf24l01 MODE0 ile iletişim kurmaktadır
  SPI.setBitOrder(MSBFIRST); // bit sıralaması MSB'den LSB'ye doğru ayarlandı
  nRF.begin(1000000,124);  
  nRF.setTXaddress(verici_adresi); // verici adresi ayarlandı

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true); 
}

void loop() 
{
  mpu6050.update();
  if(millis() - timer > 1000){
      int FB = mpu6050.getAngleY();
      int RL = mpu6050.getAngleX();

      Serial.println(FB);
      if(FB < -5){
        Serial.println("F");
        nRF.print("F"); 
        nRF.flush(); 
          }
      else if(FB > 20){
        Serial.println("B");
        nRF.print("B"); 
        nRF.flush(); 
          }
      else if(FB >= -5 && FB <= 20){
        Serial.println("M");
        nRF.print("M"); 
        nRF.flush(); 
          }                
    timer = millis();
  } 
}
