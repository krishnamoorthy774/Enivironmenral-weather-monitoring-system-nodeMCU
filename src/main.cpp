#include <Arduino.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define REDLED D2
#define BLUELED D3
#define GREENLED D4

int minTemp = 24;
int maxTemp = 27;

const char* ssid = "INTERNET PEDDLER"; //  //Sharaavanthraj's iPhone
const char* password = "3002aditya";  //  Appu$1912
const char* mqtt_server = "broker.hivemq.com";

const char* topicTemp = "topic/environment/temperature" ;
const char* topicHumid = "topic/environment/humidity" ;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
//int value = 0;

//=============================================WIFI Setup============================================================

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  pinMode(REDLED,OUTPUT);
  pinMode(BLUELED,OUTPUT);
  pinMode(GREENLED,OUTPUT);


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//=============================================================================================================================

// void callback(char* topic, byte* payload, unsigned int length) {
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("] ");
//   for (int i = 0; i < length; i++) {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();

//   // Switch on the LED if an 1 was received as first character
//   if ((char)payload[0] == '1') {
//     digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//     // but actually the LED is on; this is because
//     // it is active low on the ESP-01)
//   } else {
//     digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//   }

// }

//===========================================================================================================================



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("DHTTestTopic", "hello world");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//=======================================================================================================================

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT11 test!"));

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  //client.setCallback(callback);

  dht.begin();

}

//====================================================================================================================

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  if (t <= minTemp){
    digitalWrite(REDLED,LOW);
    digitalWrite(BLUELED,HIGH);
    digitalWrite(GREENLED,LOW);
  }
  else if (t >= maxTemp){
    digitalWrite(REDLED,HIGH);
    digitalWrite(BLUELED,LOW);
    digitalWrite(GREENLED,LOW);
  }
  else{
    digitalWrite(REDLED,LOW);
    digitalWrite(BLUELED,LOW);
    digitalWrite(GREENLED,HIGH);
  }

  // float hif = dht.computeHeatIndex(f, h);

  // float hic = dht.computeHeatIndex(t, h, false);

  // Serial.print(F("Humidity: "));
  // Serial.print(h);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(t);
  // Serial.print(F("°C "));
  // Serial.print(f);
  // Serial.print(F("°F  Heat index: "));
  // Serial.print(hic);
  // Serial.print(F("°C "));
  // Serial.print(hif);
  // Serial.println(F("°F"));
  // Serial.println("===================================================================");
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    // ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "Temperature: %.2f°C, Humidity: %.2f%%", t, h);
    Serial.print("Publish message: ");
    Serial.println(msg);
    // Convert the float values to strings
    String temperature = String(t);
    String humidity = String(h);

    // Publish the temperature and humidity values as strings
    client.publish(topicTemp, temperature.c_str());
    client.publish(topicHumid, humidity.c_str());
  }
}
