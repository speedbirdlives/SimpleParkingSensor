//1.Parking Sensor
//This is the first code written for the ParkingSensor.
//It doesn't include any buzzer operations because I tried using an if-dependent while loop and it didn't work out!
//Check README.md and ParkingSensor_Final.ino for the solution.




//Initialising the libraries
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Declaring the display as 'lcd'
LiquidCrystal_I2C lcd(0x27, 20, 4);

//LED pins
int red = 8;
int green = 9;
int yellow = 10;

//Buzzer Pin
int buzz = 3;

//HCSR04
int trigPin = 11;
int echoPin = 12;
float pingTravelTime;
float distance=100;



void setup() {
  // put your setup code here, to run once:

  //Setting up the LEDs
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(yellow,OUTPUT);

  //Setting up the Buzzer
  pinMode(buzz,OUTPUT);

  //Setting up HCSR04
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  //Setting up LCD
  lcd.init();
  lcd.backlight();
  
  //SerialMonitor
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

// Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Measure echo time
  pingTravelTime = pulseIn(echoPin, HIGH);

  
  Serial.println(pingTravelTime);

  //STOP Operation
  if(pingTravelTime<300){

    lcd.clear();


    digitalWrite(red,HIGH);
    digitalWrite(green,LOW);
    digitalWrite(yellow,LOW);

    

    lcd.setCursor(0,0);
    lcd.print("STOP");
    
  }

  //WARNING Operation
  if(pingTravelTime>300 && pingTravelTime<=550){

    lcd.clear();


    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
    digitalWrite(yellow,HIGH);

    lcd.setCursor(0,0);
    lcd.print("WARNING");

  }


  //SAFE Operation
  if(pingTravelTime>550){
    lcd.clear();

    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    digitalWrite(yellow,LOW);

    lcd.setCursor(0,0);
    lcd.print("SAFE");

  }
  

  delay(1000);



}
