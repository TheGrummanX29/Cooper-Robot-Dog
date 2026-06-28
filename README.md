# Cooper - an evolving project to create an autonomous robotic platform
<img src="images/White_logo.png" alt="Cooper logo" width="80%">

## Robot equipment
<img src="images/General v127 WB.png" alt="Cooper(mk3)" width="80%">

  1. x12 servo motors (mg996)
  2. x2 26650 5100 mAh cells
  3. PCA9685 I2C
  4. Arduino Pro Micro (Leonardo)
  5. ESP32 CAM
  6. Addressable LED strip
  7. LiDAR (from Xiaomi robot vacuum cleaner)
  8. x2 voltage converters
  9. Breadboard for soldering

## Project development
During the first year of development, we managed to create a 3D model and write code for the servos, LED lighting, and ESP32-CAM.

### mk1
<img src="images/mk1" alt="Cooper(mk1)" width="60%">

### mk2
<img src="images/mk2.jpg" alt="Cooper(mk2)" width="60%">

<img src="images/mk2(bp)" alt="Cooper(mk2)" width="60%">

### mk3
<img src="images/General v126 (mk3).png" alt="Cooper(mk3)" width="60%">

## Code description
### **[ESP32-CAM](./src/ESP32/ESP32CAM_object_detection_with_tg_send.ino)**
A script was written for the ESP32-CAM that generates a web page (accessible by connecting the camera to the internet). On this page, a target can be selected, and the camera automatically recognizes it. The script also activates a Telegram bot, which allows for the control of certain robot functions.
