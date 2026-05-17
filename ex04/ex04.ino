#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 700

volatile bool touchFlag = false;
bool ledState = false;
bool lastTouchState = false;

void IRAM_ATTR gotTouch() {
  touchFlag = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 300) {
    lastPrint = millis();
    Serial.print("Touch value: ");
    Serial.println(touchRead(TOUCH_PIN));
  }

  if (touchFlag) {
    touchFlag = false;
    int val = touchRead(TOUCH_PIN);
    bool currentlyTouched = (val < THRESHOLD);
    if (currentlyTouched) {
      delay(50); 
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      Serial.println("LED toggled (press)");
    } else {
      Serial.println("Ignored release interrupt");
    }
  }
  delay(10);
}