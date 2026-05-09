const int ledPin = 2;               

struct Step {
  bool ledState;      // HIGH 或 LOW
  unsigned long duration;
};

const Step sosSteps[] = {
  // 字母 S （短闪3次）
  {HIGH, 200}, {LOW, 200},
  {HIGH, 200}, {LOW, 200},
  {HIGH, 200}, {LOW, 200},
  {LOW, 500},

  // 字母 O （长闪3次）
  {HIGH, 600}, {LOW, 200},
  {HIGH, 600}, {LOW, 200},
  {HIGH, 600}, {LOW, 200},
  {LOW, 500},

  // 字母 S （短闪3次）
  {HIGH, 200}, {LOW, 200},
  {HIGH, 200}, {LOW, 200},
  {HIGH, 200}, {LOW, 200},
  {LOW, 2000}
};

const int stepCount = sizeof(sosSteps) / sizeof(sosSteps[0]);
int currentStep = 0; 
unsigned long previousMillis = 0; 
bool stepRunning = false; 

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, sosSteps[0].ledState); 
  previousMillis = millis();
  stepRunning = true;
}

void loop() {
  unsigned long currentMillis = millis();

  if (stepRunning) {
    if (currentMillis - previousMillis >= sosSteps[currentStep].duration) {
      currentStep++;
      if (currentStep >= stepCount) {
        currentStep = 0;   
      }
      digitalWrite(ledPin, sosSteps[currentStep].ledState);
      previousMillis = currentMillis;
    }
  }
}