
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>//Biblioteca do UDP.
//check boards manager url in Arduino/preferences: http://arduino.esp8266.com/stable/package_esp8266com_index.json

WiFiUDP udp;//Cria um objeto da classe UDP.
long x;//Variavel para ser enviada.

const char* ssid="dragino-18f0e4";
const char* password = "iotincendios";

//int ledPin = 13;

void setup() {

// pinMode(ledPin,OUTPUT);
//digitalWrite(ledPin,LOW);
   pinMode(D4, OUTPUT);//Habilita o LED onboard como saida.
   digitalWrite(D4, 1);//Desliga o LED.

   Serial.begin(115200);
   Serial.println();
   Serial.print("Wifi connecting to ");
   Serial.println(ssid);
   WiFi.begin(ssid, password);
   Serial.println();
   Serial.println("Connecting");

   //digitalWrite( ledPin , HIGH);
   //Serial.println();
   
   WiFi.mode(WIFI_STA);//Define o ESP8266 como Station.
   while( WiFi.status() != WL_CONNECTED ){
     delay(500);
     Serial.println(".");       
   }
   Serial.println("Wifi Connected Success!");
   Serial.println("NodeMCU IP Address : ");
   Serial.println(WiFi.localIP() );
}

void loop()
{
 //  connect();//Sub-rotina para conectar-se ao host.

   send();//Sub-rotina para enviar os dados ao host.

   delay(500);//Aguarda meio segundo.
}

void connect()//Sub-rotina para verificar a conexao com o host.
{
   if (WiFi.status() != WL_CONNECTED)//Caso nao esteja conectado ao host, ira se conectar.
   {
      WiFi.begin("NodeMCU", "");//Conecta à rede do host.
      delay(2000);//Espera ate que a conexao seja feita.
   }

}

void send()//Sub-rotina para enviar dados ao host.
{
   if (WiFi.status() == WL_CONNECTED)//Só ira enviar dados se estiver conectado.
   {
      x = random(0, 1000);//Gera um numero aleatorio entre 0 e 1000.
      udp.beginPacket("10.130.1.216", 5005);//Inicializa o pacote de transmissao ao IP e PORTA.
      udp.println(x);//Adiciona-se o valor ao pacote.
      udp.endPacket();//Finaliza o pacote e envia.

      digitalWrite(D4, 0);//-
      delay(5);//-
      digitalWrite(D4, 1);//Pisca o led rapidamente apos enviar.
   }
   else//Caso nao esteja com uma conexao estabelicida ao host, piscara lentamente.
   {
      digitalWrite(D4, 0);
      delay(250);
      digitalWrite(D4, 1);
   }
}
