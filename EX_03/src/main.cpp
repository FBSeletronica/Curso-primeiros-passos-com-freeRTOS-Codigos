/***************************************************************
 *  Exemplo para parar e reiniciar uma task
 *  Esse exemplo exibe como  parar e reiniciar tasks no FreeRTOS
 *  Por: Fábio Souza
***************************************************************/

/*Biblioteca do Arduino*/
#include <Arduino.h>

/*Bibliotecas FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*mapeamento de pinos*/ 
#define LED 2

/* Variáveis para armazenamento do handle das tasks*/
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

/*protítipos das Tasks*/
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

void setup() {
  Serial.begin(9600);
    
  xTaskCreate(vTask1,"TASK1",configMINIMAL_STACK_SIZE,NULL,1,&task1Handle);
  xTaskCreate(vTask2,"TASK2",configMINIMAL_STACK_SIZE+1024,NULL,2,&task2Handle);

}

void loop() {
  vTaskDelay(3000);
}


void vTask1(void *pvParameters)
{
    pinMode(LED,OUTPUT);

    while (1)
    {
      digitalWrite(LED,!digitalRead(LED));
      vTaskDelay(pdMS_TO_TICKS(200));
    }
}


void vTask2(void *pvParameters)
{
  int cont = 0;

  while (1)
  {
    Serial.println("Task 2: " + String(cont++));

    if(cont==10){
      Serial.println("Supendendo a Task 1...");
      digitalWrite(LED,LOW);
      vTaskSuspend(task1Handle);
    }
    else if(cont==15){
      Serial.println("Reiniciando a Task 1....");
      vTaskResume(task1Handle);
      cont = 0;
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
