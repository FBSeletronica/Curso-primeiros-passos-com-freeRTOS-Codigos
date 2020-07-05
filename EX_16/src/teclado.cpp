#include "teclado.h"

void initTeclado(int pin){
    pinMode(pin,INPUT_PULLUP);
}

bool leTeclado(unsigned char tecla){

    return digitalRead(tecla);
}
