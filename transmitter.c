#include <SPI.h>
#include <LoRa.h>

#define NSS 10    // LoRa chip select pin
#define RESET 7   // LoRa reset pin
#define DIO0 2    // LoRa interrupt pin

int counter = 0;

void setup() {
  Serial.begin(9600);
  LoRa.setPins(NSS, RESET, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (true);
  }
  Serial.println("LoRa Transmitter Ready");
}

void loop() {
  String message = (counter % 2 == 0) ? "ON" : "OFF";
  Serial.print("Sending: ");
  Serial.println(message);

  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  counter++;
  delay(5000);  // send every 5 seconds
}
