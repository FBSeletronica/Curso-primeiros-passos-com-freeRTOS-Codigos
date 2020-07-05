/*********************************************************
* Exemplo que demonstra como enviar valores para uma fila 
* a partir de uma ISR
* Por: Fábio Souza
*********************************************************/

#include <Arduino.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"

#define LED 2
#define BT 12

QueueHandle_t xFila;
TaskHandle_t xTask1Handle;

void vTask1(void *pvParameters);

void trataISR_BT(){
  static int valor;

  valor++;
  xQueueSendFromISR(xFila,&valor,NULL);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(BT,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BT),trataISR_BT,FALLING);

  xFila = xQueueCreate(255,sizeof(int));

  xTaskCreate(vTask1,"Task 1",configMINIMAL_STACK_SIZE + 1024,NULL,1,&xTask1Handle);


}

void loop() {
  digitalWrite(LED,!digitalRead(LED));
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTask1(void *pvParameters){

  int valorRecebido;

  while(1){
    xQueueReceive(xFila,&valorRecebido,portMAX_DELAY);
    Serial.println("BT Pressionado: " + String(valorRecebido));

  }
}