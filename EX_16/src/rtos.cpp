#include "rtos.h"


/*
Task             Core  Prio     Descrição
-------------------------------------------------------------------------------
vTaskSensor        1     1     faz a leitura do sensor analógico
vTaskPrint         1     1     Imprime o valor do sensor o display
vTaskMQTT          0     2     Publica valor do Sensor em tópico MQTT
vTaskTeclado       0     3     Faz a leitura da tecla e aciona saida

*/


xTimerHandle xTimer;
QueueHandle_t xFila; 

/* Variáveis para armazenar o handle da Task */
TaskHandle_t xTaskPrintHandle;
TaskHandle_t xTaskMQTTHandle;
TaskHandle_t xTaskSensorHandle;
TaskHandle_t xTaskTecladoHandle;

void vTaskSensor(void *pvParameters );
void vTaskPrint(void *pvParameters);
void vTaskMQTT(void *pvParameters); 
void vTaskTeclado( void *pvParameters );

void callBackTimer(TimerHandle_t pxTimer );

void rtosInit(){

    xFila = xQueueCreate(1, sizeof(int));
    xTimer = xTimerCreate("TIMER",pdMS_TO_TICKS(2000),pdTRUE, 0, callBackTimer);

    xTaskCreatePinnedToCore(vTaskSensor,  "TaskADC",  configMINIMAL_STACK_SIZE + 1024,  NULL,  1,  &xTaskSensorHandle,APP_CPU_NUM);
    xTaskCreatePinnedToCore(vTaskPrint,  "TaskPrint",  configMINIMAL_STACK_SIZE + 1024,  NULL,  1,  &xTaskPrintHandle,APP_CPU_NUM);
    xTaskCreatePinnedToCore(vTaskMQTT,  "TaskMQTT",  configMINIMAL_STACK_SIZE + 2048,  NULL,  2,  &xTaskMQTTHandle,PRO_CPU_NUM);  
    xTaskCreatePinnedToCore(vTaskTeclado,  "Taskteclado",  configMINIMAL_STACK_SIZE ,  (void *)BT1,  3,  &xTaskTecladoHandle,PRO_CPU_NUM);   

    xTimerStart(xTimer,0);
}


/* impementação da TaskADC */
void vTaskSensor(void *pvParameters )
{
  (void) pvParameters;
  
  int adcValue;
  while(1)
  {
    adcValue = sensorRead();
    xQueueOverwrite(xFila, &adcValue);/* envia valor atual de count para fila*/
    vTaskDelay(pdMS_TO_TICKS(1000)); /* Aguarda 5000 ms antes de uma nova iteração*/
  }
}


/* Implemntação da vTaskDisplay  */
void vTaskPrint(void *pvParameters )
{
  (void) pvParameters;  /* Apenas para o Compilador não retornar warnings */
  int valor_recebido = 0;
  while(1)
  {
      if(xQueueReceive(xFila, &valor_recebido, portMAX_DELAY) == pdTRUE) //verifica se há valor na fila para ser lido. Espera 1 segundo
      {
        imprimeSensorDisplay(valor_recebido);
      }
  }
}


/*Implementação da Task MQTT */
void vTaskMQTT(void *pvParameters){
  (void) pvParameters;
  char mensagem[30];
  int valor_recebido = 0;

  while(1)
  {
    
      if(xQueueReceive(xFila, &valor_recebido, portMAX_DELAY) == pdTRUE) //verifica se há valor na fila para ser lido. Espera 1 segundo
      {
        mqttIsConected();
        sprintf(mensagem, "%d", valor_recebido);
        mqttSend(mensagem);       
        vTaskDelay(15000);
      }

  }

}


void vTaskTeclado( void * pvParameters )
{
  int pin = (int) pvParameters;

  uint8_t debouncingTime = 0;
  bool estadoAnterior = 0;

  pinMode(OUTPUT_1,OUTPUT);      
  initTeclado(pin);

  while(1)
  {
    if(leTeclado(pin)== PRESSIONADO){
      debouncingTime++;
      if((debouncingTime >= 10) && (estadoAnterior == SOLTO) )
      {

          debouncingTime = 0;
          digitalWrite(OUTPUT_1,!digitalRead(OUTPUT_1));
          estadoAnterior = PRESSIONADO;
      }
    }
    else{
      debouncingTime = 0;
      estadoAnterior = SOLTO;
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void callBackTimer(TimerHandle_t pxTimer ){
  digitalWrite(LED_HEART_BEAT,HIGH);
  vTaskDelay(pdMS_TO_TICKS(100));
  digitalWrite(LED_HEART_BEAT,LOW);

}