#include <ESP8266WiFi.h> // Import ESP8266 WiFi library
#include <WiFiClient.h>
#include <PubSubClient.h>// Import PubSubClient library to initialize MQTT protocol

// Update these with values suitable for your network.
const char* ssid = "I got Kiev before Putin A53";
const char* password = "audamland18";
const char* mqtt_server = "192.168.212.85"; //raspi's IP address
int LedPin = 13;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  // Connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
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

// Check for Message received on define topic for MQTT Broker
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived, from topic: [");
  Serial.print(topic);
  Serial.println("].");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1')
  {
    digitalWrite(D2, HIGH);
  }
  else
  {
    digitalWrite(D2, LOW);
  }
}

void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESPClient-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      if (client.subscribe("cl21/2/nhom2/led",0))
      {
        Serial.println("subscribed");
      }
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      // Wait 3 seconds before retrying
      delay(3000);
    }
  }
}

void setup() {
  pinMode(LedPin, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  Serial.println("Go");
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //client.subscribe("cl21/2/nhom2/led");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
}
