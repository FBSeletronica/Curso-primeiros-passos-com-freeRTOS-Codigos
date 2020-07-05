#ifndef _TECLADO_H
#define _TECLADO_H

#include <Arduino.h>

#define BT1 12

#define PRESSIONADO LOW
#define SOLTO   HIGH

void initTeclado(int pin);
bool leTeclado(unsigned char tecla);


#endif