 #include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <OLED32.h> 

int pulseA=12;
int pulseB=13;
int RST=2;
int MSB=digitalRead(pulseA);
int LSB=digitalRead(pulseB);
int rst=digitalRead(RST);
int lastEncoded=0;
char arr[20];
int cnt=0;
int i=0;

const char* ssid = "IoT518";
const char* password = "iot123456";
const char* mqttServer = "3.83.84.45";
const char* mqttUser = "hur";
const char* mqttPassword = "yun";
const int mqttPort = 1883;
char msg[100];

OLED display(4,5);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() 
{
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  display.begin();
  pinMode(pulseA,INPUT_PULLUP);
  pinMode(pulseB,INPUT_PULLUP);
  pinMode(RST,INPUT_PULLUP);
  display.begin();
  attachInterrupt(pulseA,handleRotary,CHANGE);
  attachInterrupt(pulseB,handleRotary,CHANGE);
  attachInterrupt(RST,valueReset,FALLING);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer,mqttPort);
  while(!client.connected()){
    Serial.println("Connecting to MQTT...");
    if(client.connect("ESP8266Client2",mqttUser,mqttPassword)){
        Serial.println("connected"); //보드B 
     }
    else{
      Serial.print("failed with state");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.subscribe("esp/test");
  client.setCallback(callback); 
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message: ");
  for(int i=0;i<length;i++)
  {
    Serial.print((char)payload[i]);
    msg[i]=(char)payload[i];
  }
}

void loop() 
{  
  client.loop();
  if(strlen(msg) > 0)
  {
    display.on();
    if(i<20)
      {
       arr[i]=cnt;
       i++;
      }
      else
       i=0;
    
       if(cnt>100){
          display.print(" ALREADY IN USE ", 3, 0);
          delay(50);
       }
       else{
          display.print("I'M READY TO USE", 3, 0);
          delay(50);
       }
      display.print("encoder : ");
      sprintf(arr, "%4d", cnt );
      display.print(arr, 0, 9);
      Serial.println(cnt);
      delay(50);
  }
  else
  {
    display.off();
  }
}

void handleRotary()
{
    int MSB=digitalRead(pulseA);
    int LSB=digitalRead(pulseB);
    int encoded = (MSB << 1) |LSB;   
    int sum  = (lastEncoded << 2) | encoded;   
    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) 
      cnt ++;    
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) 
      cnt --;     
    lastEncoded = encoded; //store this value for next time 
    if(cnt<0)
      cnt=0;
    else if(cnt>1024)
      cnt=1024;
    else 
      cnt=cnt;
}
void valueReset()
{
  cnt=0;
}
