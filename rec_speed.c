#include <SPI.h>
#include <LoRa.h>

#define NSS 10
#define RESET 9
#define DIO0 2

void setup() {
  Serial.begin(9600);
  LoRa.setPins(NSS, RESET, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed");
    while (true);
  }
  Serial.println("LoRa Receiver Ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    unsigned long startTime = micros();   // Start time when packet starts receiving
    String receivedData = "";
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }
    unsigned long endTime = micros();     // End time after full packet is received

    unsigned long duration = endTime - startTime;  // microseconds
    int bits = packetSize * 8;

    float seconds = duration / 1000000.0;  // convert to seconds
    float bps = bits / seconds;

    Serial.print("Received packet (");
    Serial.print(packetSize);
    Serial.print(" bytes) in ");
    Serial.print(duration);
    Serial.print(" us. Data rate: ");
    Serial.print(bps);
    Serial.println(" bits/second");
  }
}
