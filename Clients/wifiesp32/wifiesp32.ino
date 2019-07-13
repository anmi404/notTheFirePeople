
#include <WiFi.h>
#include <WiFiUdp.h>
//#include <string.h>

/* WiFi network name and password */
// Your wirelless router ssid and password
const char* ssid = "dragino-18f0e4";
const char* password = "iotincendios";

// IP address to send UDP data to.
// it can be ip address of the server or
// a network broadcast address
// here is broadcast address
const char * udpAddress = "192.168.43.3"; // your pc ip
const int udpPort = 5005; //port server

//create UDP instance
WiFiUDP udp;

void setup(){
  Serial.begin(115200); // to monitor activity
 
  //Connect to the WiFi network
  WiFi.begin(ssid, pwd);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //This initializes udp and transfer buffer
  udp.begin(udpPort);
}

void loop(){
  //Temperature sensor
  Serial.print("Temperatura: ");
  // Convert raw temperature in F to Celsius degrees
  float t = 33.5;
  Serial.print(33.5);
  Serial.println(" *C");
  
  //uint8_t
  uint8_t buffer[50] = "33.5";
  //sprintf((char*) buffer, "Temperatura: %f *C", t);
  //send hello world to server
  udp.beginPacket(udpAddress, udpPort);
  udp.write(buffer, 4);//buffer
  udp.endPacket();
  //memset(buffer, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  //udp.parsePacket();
  //receive response from server, it will be HELLO WORLD
  //if(udp.read(buffer, 50) > 0){
  //  Serial.print("Server to client: ");
  //  Serial.println((char *)buffer);
  //}
  //Wait for 1 second
  delay(500);
}
