#include <WiFi.h> 
#include <PubSubClient.h>
const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

const String brokerUrl = "test.mosquitto.org";
const int port = 1883;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void conexaoBroker(){
  Serial.println("Conectando ao broker");
  mqttClient.setServer(brokerUrl.c_str(),port);
  String userId = "ESP-BANANINHA";
  while(!mqttClient.connected()){
    mqttClient.connect(userId.c_str());
    Serial.println(".");
    delay(2000);
  }
  Serial.println("mqtt Connectado com sucesso!");
}

void conexaoWifi(){
  Serial.println("Iniciando conexão com rede Wi-Fi");
  Serial.print("Conectando");
  while(WiFi.status() != WL_CONNECTED){
    WiFi.begin(SSID,PSWD);
    Serial.print(".");
    delay(2000);
  }
  Serial.println("\nConectado");
}

void reconexaoWifi(){
  Serial.println("Iniciando reconexão com rede Wi-Fi");
  Serial.print("Reconectando");
  while(WiFi.status() != WL_CONNECTED){
    WiFi.begin(SSID,PSWD);
    Serial.print(".");
    delay(2000);
  }
  Serial.println("\nReconectado!");
}


void setup() {
  Serial.begin(115200);
  conexaoWifi();
  conexaoBroker();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Conexão Wi-Fi perdida");
    reconexaoWifi();
  }
  if(!mqttClient.connected()){
    Serial.println("Conexão Broker perdida");
    conexaoBroker();
  }
  mqttClient.publish("AulaIoTSul/Chat","Esse e o EasterEgg da band!");
  delay(1000);

  mqttClient.loop();
}
