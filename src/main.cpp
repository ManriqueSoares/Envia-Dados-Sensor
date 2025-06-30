#include <WiFi.h>
#include <HTTPClient.h>
#include <DFRobot_AS7341.h>

// Credencias para conexão ao WiFi
const char* ssid = "";
const char* password = "";
const char* URL_SENSOR = ""; // URL para enviar os dados do sensor para a planilha de controle geral

// Espaço para adicionar os scripts

// Definindo constantes e pinos
DFRobot_AS7341 as7341;

// Configura o sistema no início	
void setup() {
  Serial.begin(9600);
  while (as7341.begin() != 0) {
    Serial.println("ERRO Conect sensor");
    delay(1000);
  }
  //    Configurando o sensor
  as7341.setAtime(29); // Tempo de integração moderado
  as7341.setAstep(200); // Passo de integração moderado
  as7341.setAGAIN(8); // Ganho moderado (X4)s
  as7341.enableLed(false); // LED desativado
  Serial.println("Iniciando sistema");
}

// Looping principal
void loop() {
  // Desliga o WiFi antes de fazer as leituras
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  
  // Realizando as leituras do sensor
  DFRobot_AS7341::sModeOneData_t data1;
  DFRobot_AS7341::sModeTwoData_t data2;

  as7341.startMeasure(as7341.eF1F4ClearNIR);
  data1 = as7341.readSpectralDataOne();
  Serial.print("F1: ");
  Serial.print(data1.ADF1);
  Serial.print(" F2: "); 
  Serial.print(data1.ADF2);
  Serial.print(" F3: ");
  Serial.print(data1.ADF3);
  Serial.print(" F4: ");
  Serial.print(data1.ADF4);

  as7341.startMeasure(as7341.eF5F8ClearNIR);
  data2 = as7341.readSpectralDataTwo();
  Serial.print(" F5: ");
  Serial.print(data2.ADF5);
  Serial.print(" F6: ");
  Serial.print(data2.ADF6);
  Serial.print(" F7: ");
  Serial.print(data2.ADF7);
  Serial.print(" F8: ");
  Serial.println(data2.ADF8);

  // Liga o WiFi apenas quando necessário
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao WiFi");
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    tentativas++;
    if (tentativas > 20) {
      Serial.println("Falha ao conectar ao WiFi");
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Conectado ao WiFi!!");
    HTTPClient http;
    String url = String(URL_SENSOR)+"?F1=" + String(data1.ADF1) + "&F2=" + String(data1.ADF2) + "&F3=" + String(data1.ADF3) + "&F4=" + String(data1.ADF4) + "&F5=" + String(data2.ADF5) + "&F6=" + String(data2.ADF6) + "&F7=" + String(data2.ADF7) + "&F8=" + String(data2.ADF8);
    delay(200);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == 200) {
      String payload = http.getString();
      Serial.println("Resposta: " + payload);
    }
    http.end();
  }

  delay(600000); // Delay de 10 minutos entre as leituras
}

