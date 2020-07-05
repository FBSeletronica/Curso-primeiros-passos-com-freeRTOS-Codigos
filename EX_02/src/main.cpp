/***************************************************************
 *  Exemplo para deletar task
 *  Esse exemplço exibe como deletar uma task
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

/*função setup*/
void setup() {
  Serial.begin(9600); //configura comunicação serial com baudrate de 9600 bps
  /*criação das tasks*/  
  xTaskCreate(vTask1,"TASK1",configMINIMAL_STACK_SIZE,NULL,1,&task1Handle);
  xTaskCreate(vTask2,"TASK2",configMINIMAL_STACK_SIZE+1024,NULL,2,&task2Handle);

}
/*função loop*/
void loop() {
  vTaskDelay(3000); //libera a CPU por 3 seg
}

/*
vTask1 
inverte LED em intervalos de 200 ms
*/
void vTask1(void *pvParameters)
{
    pinMode(LED,OUTPUT);

    while (1)
    {
      digitalWrite(LED,!digitalRead(LED));
      vTaskDelay(pdMS_TO_TICKS(200));
    }
}

/*
vTask2 
imprime valor da contagem e dela a task 1 e task 2
*/
void vTask2(void *pvParameters)
{
  int cont = 0;

  while (1)
  {
    Serial.println("Task 2: " + String(cont++));

    if(cont>=10){
      if(task1Handle != NULL){
        Serial.println("Deletando Task 1");
        vTaskDelete(task1Handle);
        digitalWrite(LED,LOW);
        task1Handle = NULL;
      }
    }
    if(cont>=15){
        Serial.println("Deletando Task 2");
        vTaskDelete(NULL);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
