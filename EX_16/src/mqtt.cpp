#include "mqtt.h"

#include <Arduino.h>

/*bibliotecas para MQTT*/
#include <WiFi.h>
#include <PubSubClient.h>

/* instacias para WIFI e client*/
WiFiClient espClient;
PubSubClient client(espClient);

void mqttReconect();

/* configuraçãoes da REDE e broker MQTT*/
const char* ssid = "xxxxxxxxxxxxxxxxxxxxxx";
const char* password =  "xxxxxxxxxxxxxxxxxxx";

/* configuraçãoes do broker MQTT*/
const char* mqttServer = "io.adafruit.com";
const int mqttPort = 1883;
const char* mqttUser = "xxxxxxxxxxxxxxxxxxx";
const char* mqttPassword = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

void mqttInit(){
   
   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando ao WiFi..");
   }
  Serial.println("Conectado na rede WiFi");

  client.setServer(mqttServer, mqttPort);


}

void mqttIsConected(){
    if(!client.connected()){
          mqttReconect();
    }
}

void mqttSend(char mensagem[]){
    //Envia a mensagem ao broker
    client.publish("fabiosouza_io/feeds/test", mensagem);
    Serial.print("Valor enviado: ");
    Serial.println(mensagem);
}

//função pra reconectar ao servido MQTT
void mqttReconect() {
  //Enquanto estiver desconectado
  while (!client.connected()) {

    if (client.connect("ESP32Client", mqttUser, mqttPassword ))
    {
      Serial.println("Conectado ao broker!");
    }
    else
    {
      Serial.print("Falha na conexao ao broker - Estado: ");
      Serial.print(client.state());
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  }
}
