#include <HardwareSerial.h>

HardwareSerial SerialPort(0);

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 3, 1); // RX=16, TX=17
  
  Serial.println("ESP32 UART demo started");
}

void loop() {
  SerialPort.println("Hello from ESP32!");
  delay(2000);
  
  if(SerialPort.available()) {
    String received = SerialPort.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(received);
  }
}