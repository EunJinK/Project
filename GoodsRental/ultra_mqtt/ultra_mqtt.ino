#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "IoT518";
const char* password = "iot123456";
const char* mqttServer = "3.83.84.45";
const int mqttPort = 1883;
const char* mqttUser = "SukJung";
const char* mqttPassword = "Kim";

int relay = 15; // 핀 15
int trig = 13;
int echo = 12;
char mqttcho[10];

int lastest = 0;
float total = 0;
float avdis = 0;
float now_dis[10];

WiFiClient espClient;
PubSubClient client(espClient); 

void setup() {
  for(int i = 0; i<10; i++)
  { 
    now_dis[i] = 0;
  }
  pinMode(relay,OUTPUT); // 릴레이 출력
  pinMode(trig, OUTPUT);  
  pinMode(echo, INPUT);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client1", mqttUser, mqttPassword ))
    {
      Serial.println("connected"); //보드A
      Serial.println("Ultra start");
    } 
    else 
    {
      Serial.print("failed with state "); Serial.println(client.state());
      delay(2000);
    }
  } // end of while
} // end of setup

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
   Serial.println("-----------------------");
}

void cm(){
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  //초음파를 발사!
  
  unsigned long duration = pulseIn(echo, HIGH);
  //초음파가 발사되면 물체까지의 시간을 측정하여
  //변수 duration에 넣어준다.
  float dis = ((float)(340 * duration)/ 10000) / 2;
  //측정된 시간을 cm단위로 바꿔준다.

   total = total - now_dis[lastest];
   now_dis[lastest] = dis;
   total = total + now_dis[lastest];
   lastest = lastest + 1;
   if(lastest >= 10)
   {
     lastest = 0;
   }
   avdis = total/10;
   Serial.print("dis : ");
   Serial.print(dis);
   Serial.println("cm");
   Serial.print("avdis : ");
   Serial.print(avdis);
   Serial.println("cm");
   delay(50);
}

void loop() {
  
  cm();
  sprintf(mqttcho,"%2.2f",avdis); //문자열 합치기 
  client.publish("esp/allultra",mqttcho); 
  if(avdis <= 10)
  {
    client.publish("esp/test",mqttcho);
    digitalWrite(relay,HIGH); 
  }
  else if(avdis > 10)
  {
    digitalWrite(relay,LOW);
  }
  else
  {
    digitalWrite(relay,LOW);
  }
  delay(500);
  client.loop();
}
