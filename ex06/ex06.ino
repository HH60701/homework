#define LED_A_PIN  16
#define LED_B_PIN  17

#define PWM_FREQ     5000  
#define PWM_RES      8    

void setup() {
  Serial.begin(115200);
  delay(1000);

  ledcAttach(LED_A_PIN, PWM_FREQ, PWM_RES);
  ledcAttach(LED_B_PIN, PWM_FREQ, PWM_RES);

  ledcWrite(LED_A_PIN, 0);
  ledcWrite(LED_B_PIN, 255);

  Serial.println("Two LEDs with inverse brightness started.");
}

void loop() {
  for (int brightness = 0; brightness <= 255; brightness++) {
    int brightnessA = brightness;
    int brightnessB = 255 - brightness; 
    ledcWrite(LED_A_PIN, brightnessA);
    ledcWrite(LED_B_PIN, brightnessB);
    delay(5); 
  }

  for (int brightness = 255; brightness >= 0; brightness--) {
    int brightnessA = brightness;
    int brightnessB = 255 - brightness;
    ledcWrite(LED_A_PIN, brightnessA);
    ledcWrite(LED_B_PIN, brightnessB);
    delay(5);
  }
}