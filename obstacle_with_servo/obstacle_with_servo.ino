#include <Servo.h>  // Includes servo library.
// defines pins numbers
const int trigPin = 7;
const int echoPin = 8;
const int servoPin=10;
#define buzzer 9
#define vibrator 6
#define moisture 5
int moisture_value;

Servo myservo;

// defines variables
long duration;
int distance;
int distance_f;
int distance_r;
int distance_l;
int maxLowDistance=40;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer,OUTPUT);
pinMode(vibrator,OUTPUT);
pinMode(moisture,INPUT);
myservo.attach(servoPin);
myservo.write(90);

Serial.begin(9600); // Starts the serial communication
}
void loop() {
  moisture_monitor();
   distance_f=ping();
   if(distance_f > maxLowDistance){
     digitalWrite (buzzer,LOW);
   }else{
       digitalWrite(buzzer,HIGH);
      get_Distance();
      if(distance_r > maxLowDistance){
        digitalWrite(buzzer,LOW);
      }else if(distance_l > maxLowDistance){
         digitalWrite(buzzer,LOW);
      }else{
         digitalWrite(buzzer,HIGH);
       
      }
    
   }
}
void displayDistance(){
     Serial.print("Right Distance : ");
     Serial.print(distance_r);
     Serial.println("");
     Serial.print("Front Distance : ");
     Serial.print(distance_f);
     Serial.println("");
     Serial.print("Left Distance : ");
     Serial.print(distance_l);
     Serial.println("");
  
}

void get_Distance(){
  myservo.write(0);
  delay(500);
  int temp_r1=ping();
  myservo.write(45);
  delay(500);
  int temp_r2=ping();
  if(temp_r1<temp_r2){
    distance_r=temp_r1;
  }else{
    distance_r=temp_r2;
  }
  myservo.write(90);
  delay(500);
  distance_f=ping();
  
  myservo.write(135);
  delay(500);
  int temp_l1=ping();
  myservo.write(180);
  delay(500);
  int temp_l2=ping();
  if(temp_l1<temp_l2){
    distance_l=temp_l1;
  }else{
    distance_l=temp_l2;
  }
  myservo.write(90);
  
}

int ping(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  return distance;
}

void moisture_monitor()
{
  moisture_value=digitalRead(moisture);
  if (moisture_value==0)
  {
    digitalWrite(vibrator,HIGH);
    Serial.println(moisture_value);
  }
  else
  {
    digitalWrite(vibrator,LOW);
  }
}

