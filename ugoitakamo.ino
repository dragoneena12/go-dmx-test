#include <DMXSerial.h>
#include <Adafruit_NeoPixel.h>

// Constants for demo program

const int LED_PIN = 2;
const int LED_COUNT = 60;

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// This Example receives the 3 values starting with this channel:
const int startChannel = 1;

void setup() {
  DMXSerial.init(DMXProbe);
  pixels.begin();
  Serial.begin(115200,SERIAL_8N2);
}


void loop() {
  // Calculate how long no data bucket was received
  unsigned long lastPacket = DMXSerial.noDataSince();
  pixels.clear();
  DMXSerial.receive();

  if (lastPacket < 5000) {
    for(int i=0; i<LED_COUNT; i++) {
      int var_r = DMXSerial.read(startChannel + 3 * i);
      int var_g = DMXSerial.read(startChannel + 3 * i + 1);
      int var_b = DMXSerial.read(startChannel + 3 * i + 2);
      pixels.setPixelColor(i, pixels.Color(var_r, var_g, var_b));
    }
  } else {
    for(int i=0; i<LED_COUNT; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 10));
    }
  }
  pixels.show();
}
