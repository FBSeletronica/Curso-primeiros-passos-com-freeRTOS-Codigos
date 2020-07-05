/*********************************************************
* Exemplo 16 
* Exemplo de aplicação do FreeRTOS:

  - Faz a leitura de um sensor analógico e imprime seu valor
  no display OLED. A cada 15 segundo o valor do sensor é publicado
  em um broker MQTT via WIFI
  - Também faz a leitura de uma tecla e aciona uma saída.

* Por: Fábio Souza
*********************************************************/

#include "main.h"

void setup() {
  initSaida();    //inicia pinos de saída e comunicaçao serial
  displayInit();  //inicia display
  mqttInit();     //iniica comunicação com MQTT
  rtosInit();     //faz a iniicalização das tasks e estrutuas do RTOS
}

void loop() {
  vTaskDelete(NULL);  //deleta task loop
}


