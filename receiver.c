
#include <SPI.h>
#include <LoRa.h>

#define NSS 10    // LoRa chip select pin
#define RESET 7  // LoRa reset pin
#define DIO0 2    // LoRa interrupt pin
#define LED_PIN 5 // LED connected to pin 7

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  LoRa.setPins(NSS, RESET, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (true);
  }
  Serial.println("LoRa Receiver Ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }
    Serial.print("Received: ");
    Serial.println(receivedMessage);

    if (receivedMessage == "ON") {
      digitalWrite(LED_PIN, HIGH);
    }
    else if (receivedMessage == "OFF") {
      digitalWrite(LED_PIN, LOW);
    }
  }
}
