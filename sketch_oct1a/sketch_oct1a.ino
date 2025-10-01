#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando o Scan de redes Wi-Fi");
}

void loop() {
  int number = WiFi.scanNetworks();
  delay(500);
  if(number == -1){
    Serial.prinln("ERRO!, fui mogado");
  }
  else{
    for(int net = 0; net < net; net++){
      Serial.printf("%d - %s | %d db\n",net,WiFi.SSID(net),WiFi.RSSI(net));
    }
    Serial.prinf("Número de redes encontradas: %d\n", number);

  }
}
