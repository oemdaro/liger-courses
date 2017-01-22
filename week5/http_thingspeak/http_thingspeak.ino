#include <DHT.h>
#include <ESP8266WiFi.h>

// replace with your channel’s thingspeak API key and your SSID and password

String apiKey = "xxxxxxx";
const char* ssid = "YourSSID";
const char* password = "WiFiPassword";
const char* server = "api.thingspeak.com";

/**
 * DTH sensor circuit
 * Sensor Pin  ->  NodeMCU Pin
 * Pin1        ->  3v3
 * Pin2        ->  D2
 * Pin3        -> (Not connect)
 * Pin4        -> GND
 */

//Define the PIN for the Sensor
#define DHTPIN 2        // GPIO2 => Pin D2 on NodeMCU Mesos board
#define DHTTYPE DHT11   // DTH11 for blue and DTH22 for white color

DHT dht(DHTPIN, DHTTYPE,11);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  
  WiFi.begin(ssid, password);
  
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
}
 
void loop() {
  //Read Sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    Serial.println("Pausing to re-read.");
    delay(1000);
    return;
  }
  
  if (client.connect(server,80)) {
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(t);
    postStr +="&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celsius Humidity: ");
    Serial.print(h);
    Serial.println(" - Sending data to Thingspeak");
  }
  client.stop();
  
  Serial.println("Waiting 20 secs");
  // thingspeak needs at least a 15 sec delay between updates
  // 20 seconds to be safe
  delay(20000);
}

