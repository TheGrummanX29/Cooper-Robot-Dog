#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>

// Servo settings
#define SERVO_MIN 500   // Minimum pulse width (microseconds)
#define SERVO_MAX 2500  // Maximum pulse width (microseconds)
#define FREQUENCY 50    // PWM frequency

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

struct ServoConfig {
  uint8_t pin;
  uint8_t angle;
};

ServoConfig servos[] = {
  {0, 0},   // 1 right front
  {1, 90},  // 1 right rear
  {2, 130}, // 1 left front
  {3, 0},   // 1 left rear
  {4, 0},   // 2 right rear
  {5, 45},  // 2 left rear
  {6, 130}, // 2 left front
  {7, 30},  // 2 right front
  {8, 170}, // 3 right front
  {9, 0},   // 3 left front
  {10, 0},  // 3 left rear
  {11, 170} // 3 right rear
};



#define PIN       7 
#define PIN1      8
#define NUMPIXELS 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels



void setup() {
  delay(1000);
   tone (2, 600);
   delay(250);
   tone(2, 900);
   delay(250);
   tone (2, 600);
   delay(250);
   tone(2, 900);
   delay(250);
   tone (2, 800);
   delay(250);
   tone(2, 600);
   delay(250);
   
   noTone(2);

  pixels.begin();
  pixels1.begin();// INITIALIZE NeoPixel strip object (REQUIRED)



 pca.begin();
  pca.setPWMFreq(FREQUENCY);

  // Initialize all servos
  for (auto &srv : servos) {
    setServoAngle(srv.pin, srv.angle);
  }
}

void loop() {
  pixels.clear();
  pixels1.clear();

  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 191, 255));
    pixels1.setPixelColor(i, pixels1.Color(0, 191, 255));

    pixels.show();   
    pixels1.show();// Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}

void setServoAngle(uint8_t servo, uint8_t deg) {
  uint16_t pulse = map(deg, 0, 180, SERVO_MIN, SERVO_MAX);
  pca.writeMicroseconds(servo, pulse);
}
