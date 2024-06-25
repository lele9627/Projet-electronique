#define PIR A5
#define LED 13

void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  
}

void loop() {
   int pirVal = digitalRead(PIR);

   if (pirVal == HIGH) {
      digitalWrite(LED, HIGH);
      delay(600);
      Serial.println ("je t'ai vu ");
      
      
   }

   else {
      digitalWrite(LED,LOW);
      delay(600);
      Serial.println ("je te vois plus ");
      //
      
   }

}