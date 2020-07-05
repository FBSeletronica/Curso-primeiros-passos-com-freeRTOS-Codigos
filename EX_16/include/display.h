#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>

/*Bibliotecas para o display OLED*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*Definição da resolução do Display OLED */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


void displayInit();
void imprimeSensorDisplay(int valor);
#endif