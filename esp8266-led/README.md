# WS2812B LED Strip Controller for ESP8266

A reliable MQTT-based controller for WS2812B LED strips using a Wemos D1 Mini (ESP8266). This project allows you to control individual LEDs in a strip remotely via MQTT messages.

## Features

- Individual RGB control of up to 16 WS2812B LEDs
- MQTT-based communication for remote control
- Optimized for reliability with ESP8266 timing constraints
- Automatic reconnection to WiFi and MQTT broker
- Startup test pattern to verify hardware functionality
- Heartbeat messages to monitor device status

## Hardware Requirements

- Wemos D1 Mini or other ESP8266-based board
- WS2812B LED strip (16 LEDs)
- 5V power supply (minimum 1A recommended)
- 300-500 ohm resistor (recommended)
- 1000μF capacitor (recommended)

## Dependencies

- ESP8266WiFi
- PubSubClient
- FastLED
- ArduinoJson (v6+)

## Usage

Send JSON arrays to the configured MQTT topic to control the LEDs. Each object in the array represents one LED with RGB values:

```json
[{"r":255,"g":0,"b":0},{"r":0,"g":255,"b":0},{"r":0,"g":0,"b":255}]
```

## Installation

1. Install required libraries through Arduino Library Manager
2. Configure WiFi and MQTT settings in the code
3. Upload to your ESP8266 device
4. Connect the data pin (D4) to the LED strip's data input

## Troubleshooting

If experiencing inconsistent updates:
- Ensure adequate power supply
- Check data connections
- Add the recommended resistor and capacitor
- Keep data wires short and away from noise sources