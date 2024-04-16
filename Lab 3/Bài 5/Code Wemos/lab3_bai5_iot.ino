#include <ESP8266WiFi.h> // Import ESP8266 WiFi library
#include <WiFiClient.h>
#include <PubSubClient.h>// Import PubSubClient library to initialize MQTT protocol
#include <DHT.h>
#include <ArduinoJson.h>

// Variables
const char* ssid = "I got Kiev before Putin A53";
const char* password = "audamland18";
const char* mqtt_server = "192.168.212.85"; //raspi's IP address
int LedPin = D7;
float temp;
float hum;

#define DHTPIN D5
#define DHTTYPE DHT22

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);


WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 2000;        // Interval at which to publish sensor readings

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int blink_state = 0;

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
  
  String message = "";
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    message += (char)payload[i];
  }
  Serial.println(message);
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if (message == "Abnormal Detection")
  {
    blink_state = 1;
  }
  else if (message == "Normal Condition")
  {
    blink_state = 0;
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
      if (client.subscribe("cl21/2/nhom2/dht/detected",0))
      {
        Serial.println("subscribed to topic: cl21/2/nhom2/dht/detected");
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
  digitalWrite(LedPin, LOW);
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  //The loop function is responsible for processing the message queues and is required in the script 
  //and is placed inside a while loop so that it is called frequently.
  client.loop();

  unsigned long currentMillis = millis();
  // Every X number of seconds (interval = 2 seconds) 
  // it reads the sensor's values and publishes a new MQTT message
  if (currentMillis - previousMillis >= interval) {
    // Save the last time a new reading was published
    previousMillis = currentMillis;
    // New DHT sensor readings
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    //Creating a json
    char buffer[256];
    JsonDocument message;
    message["temperature"] = temp;
    message["humidity"] = hum;
    serializeJson(message, buffer); // {"temperature":temp,"humidity":hum}
    

    // Publish an MQTT message on topic cl21/2/nhom2/dht/value
    client.publish("cl21/2/nhom2/dht/value", buffer);
    Serial.print("Publishing on topic cl21/2/nhom2/dht/value. ");
    Serial.print("Message: ");
    serializeJson(message, Serial);
    Serial.println("");
  }

  if (blink_state)
  {
    digitalWrite(LedPin, HIGH);
    delay(500);
    digitalWrite(LedPin, LOW);
    delay(500);
  }
}
