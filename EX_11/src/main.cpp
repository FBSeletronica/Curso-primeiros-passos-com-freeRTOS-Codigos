/*********************************************************
* Exemplo para demonstrar o uso de semaforo contador dentro
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

SemaphoreHandle_t semaforoContador;

TaskHandle_t taskTrataBTHandle;

void vTaskTrataBT(void * pvParameters);


void ISR_CallBack(){

  BaseType_t xHighPriorityTaskWoken = pdTRUE;

  xSemaphoreGiveFromISR(semaforoContador,&xHighPriorityTaskWoken);

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

  semaforoContador = xSemaphoreCreateCounting(255,0);
  xTaskCreate(vTaskTrataBT, "Task BT",configMINIMAL_STACK_SIZE + 1024,NULL,3,&taskTrataBTHandle);

}

void loop() {
  digitalWrite(LED,HIGH);
  vTaskDelay(pdMS_TO_TICKS(100));
  digitalWrite(LED,LOW);
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTaskTrataBT(void * pvParameters){

  UBaseType_t x;

  while(1){
    xSemaphoreTake(semaforoContador,portMAX_DELAY);
    Serial.print("Tratando a ISR do BT: ");

    x = uxSemaphoreGetCount(semaforoContador);
    Serial.println(x);
    delay(1000);
  }

}
