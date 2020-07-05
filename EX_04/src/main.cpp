/***************************************************************
 *  Exemplo para passagem de parametros na criação da Task
 *  Por: Fábio Souza
***************************************************************/

/*Biblioteca do Arduino*/
#include <Arduino.h>

/*Bibliotecas FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*mapeamento de pinos*/ 
#define LED1 2
#define LED2 14

/* Variáveis para armazenamento do handle das tasks*/
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;
TaskHandle_t task3Handle = NULL;

/*protítipos das Tasks*/
void vTaskBlink(void *pvParameters);
void vTask2(void *pvParameters);

/*variáveis auxiliares*/
int valor = 500;


void setup() {
  Serial.begin(9600);
    
  xTaskCreate(vTaskBlink,"TASK1",configMINIMAL_STACK_SIZE,(void*)LED1,1,&task1Handle);
  xTaskCreate(vTask2,"TASK2",configMINIMAL_STACK_SIZE+1024,(void*)valor,2,&task2Handle);
  xTaskCreate(vTaskBlink,"TASK3",configMINIMAL_STACK_SIZE,(void*)LED2,1,&task3Handle);
}

void loop() {
  vTaskDelay(3000);
}


void vTaskBlink(void *pvParameters)
{
    int pin = (int)pvParameters;
    pinMode(pin,OUTPUT);

    while (1)
    {
      digitalWrite(pin,!digitalRead(pin));
      vTaskDelay(pdMS_TO_TICKS(200));
    }
}


void vTask2(void *pvParameters)
{
  int cont = (int)pvParameters;

  while (1)
  {
    Serial.println("Task 2: " + String(cont++));
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
