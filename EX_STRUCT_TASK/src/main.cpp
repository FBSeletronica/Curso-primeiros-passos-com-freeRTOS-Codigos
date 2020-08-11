/***************************************************************
 *  Exemplo para passagem de parametros na criação da Task
 *  Passando struct
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

typedef struct ablink
{
    uint16_t usTempo;
    uint8_t pino;
}led_t;

led_t led1 = {1000,LED1};  //estrutura para led1: delay 1 seg, pino LED1(2)
led_t led2 = {200,LED2};   //estrutura para led2: delay 0,2 seg, pino LED2(14)

/* Variáveis para armazenamento do handle das tasks*/
TaskHandle_t taskBlinkHandle = NULL;


/*protítipos das Tasks*/
void vTaskBlink(void *pvParameters);


void setup() {
  Serial.begin(9600);

  xTaskCreate(vTaskBlink,"TASK1",configMINIMAL_STACK_SIZE+1024,(void*)&led1,1,NULL);
  xTaskCreate(vTaskBlink,"TASK2",configMINIMAL_STACK_SIZE+1024,(void*)&led2,1,NULL);
}

void loop() {
  vTaskDelay(3000);
}


void vTaskBlink(void *pvParameters)
{

    led_t * led= (led_t *) pvParameters; //faz a leitura da struct passada

    pinMode(led->pino,OUTPUT);           //configura pino como saída

    while (1)
    {
      digitalWrite(led->pino,!digitalRead(led->pino)); //inverte estado do LED
      vTaskDelay(pdMS_TO_TICKS(led->usTempo));         //delay
    }
}
