#include <Servo.h> 
#include <LiquidCrystal.h>;
Servo servo;
LiquidCrystal lcd(6,7,8,9,10,11); 
//PWM output is possible on digital I/O pins 3, 5, 6, 9, 10 and 11
const int trigPin = 2, echoPin = 3; // Ultrasonic Sensor
float distance_cm = 1000000, switchDistance = 5, duration = 0; 
bool switchState; 
const int servoPin = 4; // Servo Motor
const int piezoPin = A0; // Piezo
const int potPin = A1; // Potentiometer
const int ledPin = A2; // LED
const int buttonUp = 5, buttonDown = 6, buttonEnter = ;kjmn `


void readDistance(bool switchState){
  do{
    digitalWrite(trigPin, LOW);
    delay(5); 
    digitalWrite(trigPin,HIGH);
    delay(10);
    digitalWrite(trigPin, LOW); 

    duration = pulseIn(echoPin, HIGH); //in us
    distance_cm = (duration/2) * 0.0343; 
    Serial.println(distance_cm);
  } while(abs(distance_cm) >= switchDistance);
}

void powerSwitch(bool switchState){
  digitalWrite(ledPin, switchState); 
  if(switchState == HIGH) servo.write(180); 
  else servo.write(0); 
}
// -----------------------------------------------
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  servo.attach(servoPin); 
  Serial.begin(9600);
  servo.write(0); 
  lcd.begin(16,2); 
  digitalWrite(ledPin, LOW); 
}

void loop() {
  readDistance(); 
  powerSwitch(HIGH); 
  delay(750);
  readDistance(); 
  int brightness = analogRead(potPin); 
  brightness = map(val, 1, 1024, 1, 255); 
  analogWrite(ledPin, brightness);  //these 3 lines should be in a loop as the LED is HIGH
  powerSwitch(LOW);
  delay(750);
}
