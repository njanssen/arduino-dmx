#include <Adafruit_NeoPixel.h>
#include "DMXUSB.h"

#define DMXUSB_BAUDRATE 115200

#define JEWEL_LED_PIN 6
#define JEWEL_LED_COUNT 7

Adafruit_NeoPixel strip(JEWEL_LED_COUNT, JEWEL_LED_PIN, NEO_GRB + NEO_KHZ800);

void onDmxReceived(int universe, char buffer[512]) {
  if (universe == 0) {
    analogWrite(ARDUINO_LED_PIN, buffer[511]);

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
  SerialUSB,
  DMXUSB_BAUDRATE,
  0,
  onDmxReceived
);

void setup() {
  pinMode(ARDUINO_LED_PIN, OUTPUT);

  strip.begin();
  strip.show();
  strip.setBrightness(50);
  SerialUSB.begin(DMXUSB_BAUDRATE);
}

void loop() {
  dmxUSB.listen();
}
