/*
 *  Simple HTTP get webclient test
 */
#include <SPI.h>
#include <Ethernet.h>
#include <ESP8266WiFi.h>

//Change the following:
//***************
const char* ssid = "router name"; //name of router that both the ESP8266 and the host computer are connected to.
const char* password = "password"; //password for router. if none just leave as "";

/*on the computer that will be hosting flask open terminal and type ipconfig (windows) or ifconfig (linux).
set the host value to the ip address of the host computer on the router that they will both be connected to. 
*/
const char* host = "ip address";
String id = "01"; //ID of ESP8266 module, this will be in the output in the file that flask creates and appends to. 
//****************


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
//  WiFi.begin(ssid, password);
  WiFi.begin(ssid);
  


//print things from the ESP serial port for troubleshooting
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("searching for long range comms...");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(current());
}

int value = 0; //counter

void loop() {
  delay(1000);
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


  client.print("POST /data HTTP/1.1\r\n"  
               "User-Agent: curl/7.38.0\r\n"
               "Host: 192.168.1.137:5000\r\n" 
               "Accept: */*\r\n"
               "Content-Length: 19\r\n"
               "Content-Type: application/x-www-form-urlencoded\r\n"
               "\r\n"
               "pin1="+current()+"&"
               "name="+id+"\r\n");
               

  delay(1000);

  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
