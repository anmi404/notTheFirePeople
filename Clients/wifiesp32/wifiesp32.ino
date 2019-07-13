
#include <WiFi.h>
#include <WiFiUpd.h>

/* WiFi network name and password */
// Your wirelless router ssid and password
const char * ssid = "moto_2";
const char * pwd = "31d7dd433fc0";

// IP address to send UDP data to.
// it can be ip address of the server or
// a network broadcast address
// here is broadcast address
const char * udpAddress = ""; // your pc ip
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
  //data will be sent to server
  uint8_t buffer[50] = "hello world";
  //send hello world to server
  udp.beginPacket(udpAddress, udpPort);
  udp.write(buffer, 11);
  udp.endPacket();
  memset(buffer, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();
  //receive response from server, it will be HELLO WORLD
  if(udp.read(buffer, 50) > 0){
    Serial.print("Server to client: ");
    Serial.println((char *)buffer);
  }
  //Wait for 1 second
  delay(500);
}
