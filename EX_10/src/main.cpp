/*********************************************************
* Exemplo para demonstrar o uso de semaforo binário dentro
* de uma ISR
* Por: Fábio Souza
*********************************************************/

/*inclusão da Biblioteca Arduino*/
#include <Arduino.h>

/*inclusão das Biblioteca do FreeRTOS*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#define LED 2
#define BT 12

SemaphoreHandle_t semaforo;

TaskHandle_t taskTrataBTHandle;

void vTaskTrataBT(void * pvParameters);


void ISR_CallBack(){

  BaseType_t xHighPriorityTaskWoken = pdTRUE;

  xSemaphoreGiveFromISR(semaforo,&xHighPriorityTaskWoken);

  if(xHighPriorityTaskWoken == pdTRUE)
  {
    portYIELD_FROM_ISR();
  }

}

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(BT,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BT),ISR_CallBack,FALLING);

  semaforo = xSemaphoreCreateBinary();
  xTaskCreate(vTaskTrataBT, "Task BT",configMINIMAL_STACK_SIZE + 1024,NULL,3,&taskTrataBTHandle);

  
}

void loop() {
  digitalWrite(LED,HIGH);
  vTaskDelay(pdMS_TO_TICKS(100));
  digitalWrite(LED,LOW);
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTaskTrataBT(void * pvParameters){

  int contador = 0;

  while(1){
    xSemaphoreTake(semaforo,portMAX_DELAY);
    Serial.println("x: " + String(contador++));
  }

}
