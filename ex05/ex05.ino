#define TOUCH_PIN 4
#define LED_PIN   2
#define THRESHOLD 700

const int speedDelays[3] = {20, 10, 5};

volatile bool touchFlag = false; 
volatile unsigned char speedLevel = 1; 
int brightness = 0; 
int step = 1;

void IRAM_ATTR gotTouch() {
  touchFlag = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  ledcAttach(LED_PIN, 5000, 8);
  ledcWrite(LED_PIN, 0);

  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);

  Serial.println("System ready. Touch to change speed level.");
}

void loop() {
  if (touchFlag) {
    touchFlag = false;
    int currentVal = touchRead(TOUCH_PIN);
    if (currentVal < THRESHOLD) {
      speedLevel++;
      if (speedLevel > 3) speedLevel = 1;
      Serial.print("Speed level changed to: ");
      Serial.println(speedLevel);
      delay(50);
    } else {
      Serial.println("Ignored release interrupt");
    }
  }

  brightness += step;
  if (brightness >= 255) {
    brightness = 255;
    step = -1;
  } else if (brightness <= 0) {
    brightness = 0;
    step = 1;
  }
  ledcWrite(LED_PIN, brightness);
  int delayMs = speedDelays[speedLevel - 1];
  delay(delayMs);
}