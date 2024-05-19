#include <WiFi.h>

const char* ssid = "DESKTOP-KU0A9BS 9091"; 
const char* password = "01Zb15<6"; 
WiFiServer server(80);

int latestMoistureLevel = 0;


const int moistureMin = 0; 
const int moistureMax = 4095; 

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  

  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    while (client.connected()) {
      if (client.available()) {
        client.read();
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        client.println("<!DOCTYPE html><html><head><title>Soil Moisture Monitoring</title></head><body>");
        client.print("<h1>Soil Moisture Level: ");
        client.print(mapMoistureLevel(latestMoistureLevel));
        client.println("%</h1></body></html>");
        break;
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
  
  
  latestMoistureLevel = analogRead(34);

  
  delay(10);
}


int mapMoistureLevel(int value) {
  int invertedValue = moistureMax - value;
  return map(invertedValue, moistureMin, moistureMax, 0, 100);
}
