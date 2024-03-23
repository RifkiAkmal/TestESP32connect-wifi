//NodeMCU-32S
//Menghidupkan Lampu

#include <WiFi.h>

const char* ssid     = "Alsabolbol";
const char* password = "sanggarazmina";

WiFiServer server(80);

int ledPin = 19;

void setup()
{
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("Rifki Akmal Alauddin");
    Serial.println("NPM 187002015");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void loop(){
 WiFiClient client = server.available();   

  if (client) { 
    Serial.println("New Client."); 
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {

          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("Rifki Akmal Alauddin<br>");
            client.print("NPM 187002015<br>");
            client.print(" <br>");
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 19 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 19 off.<br>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(ledPin, HIGH);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(ledPin, LOW);
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
