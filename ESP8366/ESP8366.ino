/*
 *  Simple HTTP get webclient test
 */
#include <SPI.h>
#include <Ethernet.h>
#include <ESP8266WiFi.h>
//
//const char* ssid     = "Jodog's Network";
//const char* password = "R1234567";

//const char* ssid     = "hearth-new";
//const char* password = "education";
//
const char* ssid = "ffflava";
const char* password = "packettt";
const char* host = "192.168.1.137";

char outBuf[128];
 
//String current = "666";
String current() {
 static char outstr[15];
 dtostrf(analogRead(A0),5,1,outstr);
 return outstr; 
}

void setup() {
  Serial.begin(115200);
  
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("searching for long range comms...");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(current());
  
}

int value = 0;

void loop() {
  delay(500);
  ++value;
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 5000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    Serial.println(current());
    return;
  }
  
  // We now create a URI for the request
  String url = "/data"; // page
  Serial.print("Requesting URL: ");
  Serial.println(url);

// POST /data HTTP/1.1
// User-Agent: curl/7.35.0
// Host: 192.168.1.137:5000
// Accept: */*
// Content-Length: 10
// Content-Type: application/x-www-form-urlencoded

  client.print("POST /data HTTP/1.1\r\n"  
               "User-Agent: curl/7.35.0\r\n"
               "Host: 192.168.1.137:5000\r\n"
               "Accept: */*\r\n"
               "Content-Length: 10\r\n"
               "Content-Type: application/x-www-form-urlencoded\r\n");
  client.print("pin1=54321");
  //client.print("pin1="+current()+"\r\n");
  client.print("Connection: close\r\n");            
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
