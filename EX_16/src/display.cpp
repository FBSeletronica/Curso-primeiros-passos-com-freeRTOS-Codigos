#include "display.h"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void displayInit(){

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("ERRO ao iniciar o display SSD1306"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void imprimeSensorDisplay(int valor){
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("SENSOR:");
    display.println(String(valor));
    display.display(); 
}
