#include <Adafruit_NeoPixel.h>
#include "DMXUSB.h"

#define DMXUSB_BAUDRATE 115200

#define NEOPIXEL_LED_PIN 6
#define NEOPIXEL_LED_COUNT 32

Adafruit_NeoPixel strip(NEOPIXEL_LED_COUNT, NEOPIXEL_LED_PIN, NEO_GRB + NEO_KHZ800);

void onDmxReceived(int universe, char buffer[512]) {
  if (universe == 0) {
    for (int i = 0; i < strip.numPixels(); i++) {
      // Determine DMX start channel for this pixel
      int dmxIndex = i * 3;

      // Get pixel colors (R,G,B)
      int red = buffer[dmxIndex];
      int green = buffer[dmxIndex + 1];
      int blue = buffer[dmxIndex + 2];
      uint32_t color = strip.Color(red, green, blue);

      //  Set pixel's color (in RAM)
      strip.setPixelColor(i, color);
    }

    //  Update strip to match
    strip.show();
  }
}

DMXUSB dmxUSB(
  Serial,
  DMXUSB_BAUDRATE,
  0,
  onDmxReceived
);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(50);
  Serial.begin(DMXUSB_BAUDRATE);
}

void loop() {
  dmxUSB.listen();
}
