#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h> // atoi() fonksiyonu için string kütüphanesi tanımlanıyor
#include <SPI.h>

Enrf24 nRF(9,10, 2);    // CE , CSN/CS/SS , IRQ bacaklarının Arduino ile bağlantıları tanımlandı

const byte alici_adresi[] = { 0xDE, 0xAD, 0xBE, 0x0F, 0x01 };

int LED1=7;
int LED2=8;

int ENA = A0;
int MTR1A = 3;
int MTR1B = 4;
int ENB = A1;
int MTR2A = 6;
int MTR2B = 5;

void setup() 
{
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 

  SPI.begin(); // SPI başlat
  SPI.setDataMode(SPI_MODE0); // SPI MODE0 seçildi, nrf24l01 MODE0 ile iletişim kurmaktadır
  SPI.setBitOrder(MSBFIRST); // bit sıralaması MSB'den LSB'ye doğru ayarlandı
  nRF.begin(1000000,124); 
  nRF.setRXaddress(alici_adresi); // alıcı adresi ayarlandı
  nRF.enableRX();  // Dinlemeye başla

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);    
  for(int i=3; i<=6; i++)
    pinMode(1, OUTPUT);  
  }

void loop()
{
  char gelen_bilgi[33]; 
  int bilgi=0; 

  if (nRF.read(gelen_bilgi))  
  {
    bilgi = atoi(gelen_bilgi);
    
     Serial.println(gelen_bilgi[0]);   
    
    if(gelen_bilgi[0]=='F')   {
            Forward();
    } 
    else if(gelen_bilgi[0]=='B')   {
         Backward();
    } 
    else if(gelen_bilgi[0]=='M') {
        Stop();
    } 
  }
  
}

void Forward(){
  digitalWrite(LED1, 1); 
  digitalWrite(LED2, 0); 

  analogWrite(ENA,150);
  digitalWrite(MTR1A,1);
  digitalWrite(MTR1B,0);   

  analogWrite(ENB,150);
  digitalWrite(MTR2A,1);
  digitalWrite(MTR2B,0);   
}

void Backward(){
  digitalWrite(LED1, 0); 
  digitalWrite(LED2, 1); 

  analogWrite(ENA,150);
  digitalWrite(MTR1A,0);
  digitalWrite(MTR1B,1);  

  analogWrite(ENB,150);
  digitalWrite(MTR2A,0);
  digitalWrite(MTR2B,1);        
}

void Stop(){
  digitalWrite(LED1, 0); 
  digitalWrite(LED2, 0);    
  
  analogWrite(ENA,0);
  digitalWrite(MTR1A,0);
  digitalWrite(MTR1B,0); 

  analogWrite(ENB,0);
  digitalWrite(MTR2A,0);
  digitalWrite(MTR2B,0);          
}
