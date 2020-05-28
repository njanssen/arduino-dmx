#include "DMXUSB.h"

#define DMXUSB_BAUDRATE 115200

void onDmxReceived(int universe, char buffer[512]) {
  for (int index=0; index < 512; index++) { // for each channel, universe starts at 0
    int channel = index + 1; // channel starts at 0, so index 0 is DMX channel 1 and index 511 is DMX channel 512
    int value = buffer[index]; // DMX value 0 to 255
  }
}

DMXUSB dmxUSB(
  SerialUSB,
  DMXUSB_BAUDRATE,
  0,
  onDmxReceived
);

void setup() {
  SerialUSB.begin(DMXUSB_BAUDRATE);
}

void loop() {
  dmxUSB.listen();
}
