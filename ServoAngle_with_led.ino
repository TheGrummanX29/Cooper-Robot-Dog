#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// NeoPixel settings
#define PIN        2
#define PIN1       4
#define NUMPIXELS  5
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

// Servo driver settings
#define SERVO_MIN 500
#define SERVO_MAX 2500
#define FREQUENCY 50
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
uint8_t servoAngles[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  // NeoPixel initialization
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels1.begin();

  // Servo driver initialization
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  updateAllServos();

  // UART initialization
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

void loop() {
  // NeoPixel processing
  static unsigned long prevMillis = 0;
  static int i = 0;
  
  if (millis() - prevMillis >= DELAYVAL) {
    prevMillis = millis();
    
    pixels.clear();
    pixels1.clear();
    
    if (i < NUMPIXELS) {
      pixels.setPixelColor(i, pixels.Color(0, 191, 255));
      pixels1.setPixelColor(i, pixels1.Color(0, 191, 255));
      pixels.show();
      pixels1.show();
      i++;
    } else {
      i = 0;
    }
  }

  if (Serial2.available()) {
    String message = Serial2.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(message);
  }
}

// Functions for servo control
uint16_t angleToPulse(uint8_t angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX) * static_cast<float>(FREQUENCY) * 4096 / 1000000;
}

void updateAllServos() {
  for(uint8_t i = 0; i < 12; i++) {
    pwm.setPWM(i, 0, angleToPulse(servoAngles[i]));
  }
}

void setServoAngle(uint8_t servoNum, uint8_t angle) {
  if(servoNum >= 12 || angle > 180) return;
  servoAngles[servoNum] = angle;
  pwm.setPWM(servoNum, 0, angleToPulse(angle));
}

void handleServoCommand(String cmd) {
  if (cmd.startsWith("SERVO")) {
    int servoNum = cmd.substring(6, 8).toInt();
    int angle = cmd.substring(9).toInt();
    setServoAngle(servoNum, angle);
  }
}
