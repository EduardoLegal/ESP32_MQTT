#include <WiFi.h>
const String SSID = "iPhone";
const String PSWD = "iot_sul_123"; 

void scanLocalNetworks();

void setup() {
  Serial.begin(115200);
  scanLocalNetworks();
  WiFi.begin(SSID,PSWD);
  Serial.println("Iniciando conexão com rede Wi-Fi");
  Serial.print("Conectando");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("\nConectado!");

}

void loop() {
  
}

void scanLocalNetworks(){
  Serial.println("Iniciando o Scan de redes Wi-Fi");
  int number = WiFi.scanNetworks();
    delay(500);
    if(number == -1){
      Serial.prinln("ERRO!, problema em encontrar alguma rede");
    }
    else{
      for(int net = 0; net < net; net++){
        Serial.printf("%d - %s | %d db\n",net,WiFi.SSID(net),WiFi.RSSI(net));
      }
      Serial.prinf("Número de redes encontradas: %d\n", number);

    }
}