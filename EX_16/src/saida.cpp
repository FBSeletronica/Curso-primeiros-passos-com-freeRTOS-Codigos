#include "saida.h"

void initSaida(){
    Serial.begin(115200); 
    pinMode(LED_HEART_BEAT,OUTPUT);
}