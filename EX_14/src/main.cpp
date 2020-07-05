/*********************************************************
* Exemplo para demonstrar o uso de grupo de eventos
* Por: Fábio Souza
*********************************************************/

/*inclusão da Biblioteca Arduino*/
#include <Arduino.h>

/*inclusão das Biblioteca do FreeRTOS*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"

#define LED 2

//mapeamento de eventos
#define TASK1_FLAG (1<<0)  //1
#define TASK2_FLAG (1<<1)  //10

TaskHandle_t xTask1Handle,xTask2Handle;
TimerHandle_t xTimer;
EventGroupHandle_t xEventos;

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void callBackTimer1(TimerHandle_t pxTimer);

int tempo = 0;

void setup(){
  Serial.begin(9600);
  pinMode(LED,OUTPUT);

  xEventos = xEventGroupCreate();
  xTimer = xTimerCreate("TIMER1",pdMS_TO_TICKS(1000),pdTRUE,0,callBackTimer1);
  xTaskCreate(vTask1,"TASK1",configMINIMAL_STACK_SIZE + 1024,NULL,1,&xTask1Handle);
  xTaskCreate(vTask2,"TASK2",configMINIMAL_STACK_SIZE + 1024,NULL,1,&xTask2Handle);

  xTimerStart(xTimer,0);

}

void loop(){
  digitalWrite(LED,!digitalRead(LED));
  vTaskDelay(pdMS_TO_TICKS(500));
}


void vTask1(void *pvParameters)
{
  EventBits_t xBits;
  while (1)
  {
    xBits = xEventGroupWaitBits(xEventos,TASK1_FLAG,pdTRUE,pdTRUE,portMAX_DELAY);
    Serial.println("Task 1 saiu do estado de bloqueio: "+ String(xBits));
  }
}
void vTask2(void *pvParameters)
{
  EventBits_t xBits;
  while (1)
  {
    xBits = xEventGroupWaitBits(xEventos,TASK2_FLAG,pdTRUE,pdTRUE,portMAX_DELAY);
    Serial.println("Task 2 saiu do estado de bloqueio: " + String(xBits));
  }
}

void callBackTimer1(TimerHandle_t pxTimer)
{
    tempo++;
    if(tempo == 5){
      xEventGroupSetBits(xEventos,TASK1_FLAG);
    }
    else if(tempo == 10){
      xEventGroupSetBits(xEventos,TASK2_FLAG);
    }
    else if(tempo == 15){
      tempo = 0;
      xEventGroupSetBits(xEventos,TASK1_FLAG|TASK2_FLAG);
    }
}