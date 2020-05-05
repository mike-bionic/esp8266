#include <ESP8266WiFi.h>

WiFiServer server(80);
int LED_PIN = 1;
int Led = 1;
void setup(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Ucgun_networks", "bionics123");
  server.begin();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, LOW);
}

void loop(){
  Serial.begin(115200);
  IPAddress HTTPS_ServerIP= WiFi.softAPIP();
  Serial.print("Server IP: ");
  Serial.println(HTTPS_ServerIP);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("Somebody has connected :)");
  String request = client.readStringUntil('\r');
  Serial.println(request);
  if (request.indexOf("/OFF") != -1){
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(Led,HIGH);
    }
  else if (request.indexOf("/ON") != -1){
    digitalWrite(LED_PIN, LOW);
    digitalWrite(Led, LOW);
  }

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><input type=\"button\" name=\"b1\"value=\"Led ON\" onclick=\"location.href='/on'\">";
  s += "<br><br><br>";
  s += "<input type=\"button\" name=\"b1\"value=\"Led OFF\" onclick=\"location.href='/off'\">";
  s += "</html>\n";
  client.flush();
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
}
