/*********************************************************
* Exemplo Blink LED - ESP32
* Pisca o LED da placa em intervalos de 1 segundo
* Exemplo para entender o fluxo de criação de um projeto 
* no Platformio
* Por: Fábio Souza
*********************************************************/
//Inclusão de biblioteca Arduino
#include <Arduino.h>

/*mapeamento de pinos*/ 
#define LED 2

//Função setup 
void setup() {
  pinMode(LED,OUTPUT);    //configura pino do LED como saída
  Serial.begin(115200);   //configura comunicação serial com baudarate de 115200 bps
}

//Função Loop
void loop() {
  digitalWrite(LED,HIGH); //liga LED
  delay(500);             //espera 0,5 s
  digitalWrite(LED,LOW);  //desliga LED
  delay(500);             //espera 0,5 s
  Serial.println("OI");   // imprime mensagem na serial
}