const int ledPin = 2;        
bool ledState = LOW;         
unsigned long previousMillis = 0;
const unsigned long interval = 500;  

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    ledState = !ledState;            
    digitalWrite(ledPin, ledState);
    
    Serial.println(ledState ? "LED ON" : "LED OFF");
  }

}