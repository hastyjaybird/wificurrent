/*
 *  Simple HTTP get webclient test
 */

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
 
//String current = "666";
float current() {
 return analogRead(A0); 
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
    Serial.print(".");
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


    // EDIT: The POST 'URL' to the location of your insert_mysql.php on your web-host
    client.println("POST /data HTTP/1.1");

    // EDIT: 'Host' to match your domain
    client.print("POST /data HTTP/1.0\n");
    client.print("Host: 192.168.1.137\n");
    client.print("Connection: close\n");
//    client.print("X-THINGSPEAKAPIKEY: " + APIKey + "\n");
//    client.print("Content-Type: application/x-www-form-urlencoded\n");
//    client.print("Content-Length: ");
//    client.print(current.length());
    client.print("\n\n");
//    client.print(current);    



  
//  // This will send the request to the server
//  client.print(String("POST ") + url + current + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" + 
//               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
