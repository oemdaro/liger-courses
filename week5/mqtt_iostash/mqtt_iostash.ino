#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTTYPE DHT22               // White color. If blue color DHT11
#define DHTPIN  2                   // GPIO2 => Pin D2 on NodeMCU Mesos board
#define SLEEP_DELAY_IN_SECONDS  30

unsigned long previousMillis = 0; 
const long interval = 2000; 
const char* ssid = "WiFi_Name";           // Put your WiFi name here
const char* password = "WiFi_Password";   // Put your WiFi password here
float humidity, temp_f;
const char* mqtt_server = "api.iostash.io";
// e.g. const char* mqtt_username = "5992d40a782251261701492a";
const char* mqtt_username = "X-Access-Token";
// e.g. const char* mqtt_password = "14071992";
const char* mqtt_password = "Device Secret";
// e.g. const char* mqtt_topic = "/5992d40a782251261701492a/25510c497a4415167502503f/";
const char* mqtt_topic = "/X-Access-Token/DeviceID/";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

String dataString;
char charBuf[100];
void setup() {
  // setup serial port
  Serial.begin(115200);

  // setup WiFi
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  dht.begin();
}

void setup_wifi() {
  delay(10);
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
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  //WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    setup_wifi();
  }
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266_Client", mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("MQTT connection failed, retry count: ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void getTemperature() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    humidity = dht.readHumidity();    
    temp_f = dht.readTemperature(false);
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  getTemperature();
  dataString = String("{\"temperature\":") + temp_f + String(",\"humidity\":") + humidity + String("}");
  dataString.toCharArray(charBuf, 150);
  Serial.println(charBuf);
  client.publish(mqtt_topic, charBuf );
  Serial.println( "Closing MQTT connection...");
  client.disconnect();
  Serial.println( "Closing WiFi connection...");
  WiFi.disconnect();
  Serial.println( "Sleeping for a minute");
  delay(1000);
}

