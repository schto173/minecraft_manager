#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>
#include <ArduinoJson.h>

// WiFi settings
const char* ssid = "INSEL";
const char* password = "nootherperson";

// MQTT settings
const char* mqtt_server = "tome.lu";
const int mqtt_port = 1883;
const char* mqtt_user = "eco";
const char* mqtt_password = "marathon";
const char* mqtt_topic = "led";
const char* mqtt_client_id = "WemosD1Mini_LEDStrip_Individual_V2";

// LED settings
#define LED_PIN     D4
#define NUM_LEDS    16
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB  // Changed from RGB to GRB - common issue with WS2812B
#define BRIGHTNESS  96

CRGB leds[NUM_LEDS];
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMqttReconnectAttempt = 0;
unsigned long lastHeartbeat = 0;

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

// Test pattern to verify LED strip is working
void testLEDs() {
  // All red
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);
  
  // All green
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);
  
  // All blue
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);
  
  // Chase pattern
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(100);
    leds[i] = CRGB::Black;
  }
  
  // Clear all
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] Length: ");
  Serial.println(length);
  
  // Create a buffer for the payload
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
    Serial.print((char)payload[i]);
  }
  message[length] = '\\0';
  Serial.println();
  
  // Parse JSON array
  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, message);
  
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Check if the JSON is an array
  if (doc.is<JsonArray>()) {
    JsonArray array = doc.as<JsonArray>();
    int arraySize = array.size();
    
    Serial.print("JSON array size: ");
    Serial.println(arraySize);
    
    // Update LEDs based on the received JSON array
    int ledIndex = 0;
    for (JsonVariant v : array) {
      if (ledIndex < NUM_LEDS) {
        int r = v["r"];
        int g = v["g"];
        int b = v["b"];
        
        Serial.print("LED ");
        Serial.print(ledIndex);
        Serial.print(": R=");
        Serial.print(r);
        Serial.print(", G=");
        Serial.print(g);
        Serial.print(", B=");
        Serial.println(b);
        
        leds[ledIndex] = CRGB(r, g, b);
        ledIndex++;
      }
    }
    
    // If we received fewer LED values than we have LEDs, turn off the rest
    while (ledIndex < NUM_LEDS) {
      leds[ledIndex] = CRGB::Black;
      ledIndex++;
    }
    
    FastLED.show();
    delay(10);
    Serial.println("LEDs updated");
  } else {
    Serial.println("Received JSON is not an array");
  }
}

boolean reconnect() {
  if (client.connect(mqtt_client_id, mqtt_user, mqtt_password)) {
    Serial.println("Connected to MQTT broker");
    // Subscribe to the LED topic
    client.subscribe(mqtt_topic);
    Serial.print("Subscribed to topic: ");
    Serial.println(mqtt_topic);
    
    // Send a message to confirm subscription
    String confirmMsg = String("Device ") + mqtt_client_id + " connected and ready";
    client.publish("status", confirmMsg.c_str());
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  Serial.println("\\n\\n--- Starting LED Strip Controller ---");
  
  // Initialize the LED strip
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxRefreshRate(400);
  FastLED.setBrightness(BRIGHTNESS);
  
  // Run test pattern
  Serial.println("Running LED test pattern...");
  testLEDs();
  
  setup_wifi();
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  // Set buffer size to handle larger messages
  client.setBufferSize(2048);
  
  Serial.println("Setup complete, connecting to MQTT...");
}

void loop() {
  // Check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    setup_wifi();
  }
  
  // Check MQTT connection
  if (!client.connected()) {
    unsigned long now = millis();
    if (now - lastMqttReconnectAttempt > 5000) {
      lastMqttReconnectAttempt = now;
      Serial.print("MQTT disconnected, state: ");
      Serial.println(client.state());
      // Attempt to reconnect
      if (reconnect()) {
        lastMqttReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    client.loop();
    
    // Send heartbeat every 30 seconds
    unsigned long now = millis();
    if (now - lastHeartbeat > 30000) {
      lastHeartbeat = now;
      String heartbeatMsg = String("Heartbeat from ") + mqtt_client_id;
      client.publish("heartbeat", heartbeatMsg.c_str());
      Serial.println("Heartbeat sent");
    }
  }
}