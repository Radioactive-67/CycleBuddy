int ldr=A5;
int ldr_value;
int light_pin=4;
//int signal_pin = 3;
int buzzer_pin = 10;
int force_pin = A2;
int distance;
int force_value=0;
int accident =0;
int tilt_pin = 3;
int tilt_value=0;
int flex_pin = A0;
int flex_value = 0;


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


void setup()
{
  Serial.begin(9600);
  
  pinMode(light_pin, OUTPUT); //LDR
  pinMode(ldr, INPUT); //LDR
  pinMode(buzzer_pin, OUTPUT); //common
  pinMode(force_pin, INPUT); //Force
  pinMode(tilt_pin, INPUT); //Tilt
  pinMode(flex_pin, INPUT); // Flex
}

void loop()
{
  digitalWrite(buzzer_pin, LOW);
  
  //Ultrasonic sensor
  distance = 0.01723 * readUltrasonicDistance(A1, A1);
  if (distance < 40) {
    digitalWrite(10, HIGH);
    //Serial.println("Alert :");
    //Serial.println(distance);
  }
  else {
    //Serial.println("Safe :");
    //Serial.println(distance);
    digitalWrite(10, LOW);
  }
  
  //LDR sensor
  ldr_value=analogRead(ldr);
  if (ldr_value>512)
  digitalWrite(light_pin, LOW);
  else
  digitalWrite(light_pin, HIGH);
  
  
  //Force sensor
  force_value = analogRead(force_pin);
  //Serial.println(force_value);
  if(force_value > 640){
  	accident = force_value;  
  }
  if(accident > 0){
  	//digitalWrite(buzzer_pin, HIGH);
    tone(buzzer_pin,accident);
  }
  
  //Tilt sensor
  tilt_value = digitalRead(tilt_pin);
  //Serial.println(tilt_value);
  delay(3000);
  tilt_value = digitalRead(tilt_pin);
  noTone(buzzer_pin);
  if(tilt_value == 0){
    tone(buzzer_pin,2000);
    //digitalWrite(buzzer_pin, HIGH);
  }
  
  //Flex sensor
  flex_value = analogRead(flex_pin);
  //noTone(buzzer_pin);
  if(flex_value > 1000){
  	delay(2000);
    flex_value = analogRead(flex_pin);
    if(flex_value > 1000){
    	digitalWrite(buzzer_pin, HIGH);
      	delay(2000);
    }
  }
  //Serial.println(flex_value);
  //delay(500);
  
  
}


