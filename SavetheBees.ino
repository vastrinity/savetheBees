#include <Servo.h>

//Servo variables
int pos = 0;//αρχικοποιηση θεσης του servo
Servo servo;
//PhotoSensor variables
int PhotosensorValue = 0;
int PhotosensorMin = 1023;        // minimum Photosensor value
int PhotosensorMax = 0;           // maximum Photosensor value
const int photoSensor=A1;

//TempSensor variables
int TempsensorValue = 0;
int TempsensorMin = 1023;        // minimum Tempsensor value
int TempsensorMax = 0;           // maximum Tempsensor value
const int TempSensor=A0;

const int ledPin=2;//το λαμπακι στην D2

void setup()
{
  servo.attach(6);//συνδεση servo στο D6
  servo.write(pos=0);
  pinMode(A0,INPUT);
  pinMode(A1, INPUT);
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  
  
  //callibration of Photosensor and Tempsensor στα πρωτα 2 δευτερολεπτα 
  digitalWrite(ledPin, HIGH);//αναβει λαμπακι κατα την εναρξη

  while (millis() < 2000) {
    PhotosensorValue = analogRead(photoSensor);
    TempsensorValue = analogRead(TempSensor);

   
    if (PhotosensorValue > PhotosensorMax) {
      PhotosensorMax = PhotosensorValue; // record the maximum Photosensor value
    }

   
    if (PhotosensorValue < PhotosensorMin) {
      PhotosensorMin = PhotosensorValue; // record the minimum Tempsensor value
    }
    if (TempsensorValue > TempsensorMax) {
      TempsensorMax = TempsensorValue; // record the maximum Tempsensor value
    }

   
    if (TempsensorValue < TempsensorMin) {
     TempsensorMin = TempsensorValue; // record the minimum Tempsensor value
    }
  }
  digitalWrite(ledPin, LOW);//κλεινει λαμπακι στο τελος του callibration
  
  
 }

void loop()
{
  TempsensorValue = analogRead(TempSensor); // read the value from the Tempsensor
  PhotosensorValue = analogRead(photoSensor); // read the value from the Photosensor
  PhotosensorValue = map(PhotosensorValue, PhotosensorMin, PhotosensorMax, 0, 255);// apply the calibration to the Photosensor reading
  TempsensorValue = map(TempsensorValue, TempsensorMin, TempsensorMax, 0, 255);// apply the calibration to the Tempsensor reading
  pos=servo.read();
  
  Serial.print("light=");
  Serial.println(PhotosensorValue); // print the Photosensor reading so you know its range
  Serial.print("temprature=");
  Serial.println(TempsensorValue); // print the Tempsensor reading so you know its range
  Serial.print("Door position =");
 Serial.println(pos);
  

  
  if (PhotosensorValue<120 && TempsensorValue<120 && pos!=90){
   //οταν ειναι νυχτα και χαμηλη θερμοκρασια και η πορτα ανοιχτη αναβει το λαμπακι και κλεινει η πορτα
      digitalWrite(ledPin, HIGH);
      delay(2000);
      pos=90;  
      servo.write(pos);// tell servo to go to position in variable 'pos'
      
      }
  
 if (PhotosensorValue>120 || TempsensorValue>120 ){
   //οταν δεν ειναι νυχτα και χαμηλη θερμοκρασια  κλεινει η πορτα
    
   pos=0;
   servo.write(pos);// tell servo to go to position in variable 'pos' 
  
 }
  digitalWrite(ledPin, LOW);
    
  delay(1000); // Wait for 100 millisecond(s)
  
}