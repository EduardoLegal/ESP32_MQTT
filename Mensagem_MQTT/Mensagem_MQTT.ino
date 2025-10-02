#include <WiFi.h> 
#include <PubSubClient.h>
const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

const String brokerUrl = "test.mosquitto.org";
const int port = 1883;

String message = "";

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
  mqttClient.subscribe("AulaIoTSul/Chat");
  mqttClient.setCallback(callback);
  Serial.println("mqtt Connectado com sucesso!");
}

void callback(char* topico, byte* payload, unsigned long length){
  String mensagem = "";
  for(int i=0; i < length; i++){
    mensagem += (char) payload[i];
  }
  Serial.println(mensagem);
}

void conexaoWifi(){
  Serial.println("Iniciando conexão com rede Wi-Fi");
  Serial.print("Conectando");
  while(WiFi.status() != WL_CONNECTED){
    WiFi.begin(SSID,PSWD);
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nConectado");
}

void reconexaoWifi(){
  Serial.println("Iniciando reconexão com rede Wi-Fi");
  Serial.print("Reconectando");
  while(WiFi.status() != WL_CONNECTED){
    WiFi.begin(SSID,PSWD);
    Serial.print(".");
    delay(5000);
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
  if(Serial.available()){
    message = Serial.readStringUntil('\n');
    message = "Eduardo e Lipe:" + message;
    mqttClient.publish("AulaIoTSul/Chat",message.c_str());
    delay(1000);
  }
  

  mqttClient.loop();
}
