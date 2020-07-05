#include "sensor.h"

int buffer[100];
int i = 0;

void sensorInit(){
    
}

int sensorRead(){
    int valor  = 0;

    i++;
    if(i==10) i = 0;
    buffer[i] = analogRead(SENSOR_PIN);

    for(char x = 0;x<10;x++){
         valor +=buffer[i];
    }


    return map(valor/10,0,4095,0,100);
}

