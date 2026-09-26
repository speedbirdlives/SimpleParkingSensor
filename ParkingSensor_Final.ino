
// 1.Simple Parking Sensor (Final Version)

//Added independent buzzer operation to the project.

//including necessary libraries
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

// LED pins
int red = 8;
int green = 9;
int yellow = 10;

// Buzzer
int buzz = 3;

// HC-SR04
int trigPin = 11;
int echoPin = 12;

float pingTravelTime;
float distance;

// Buzzer timing
unsigned long previousMillis = 0;
const long beepInterval = 300;   // Time between buzzer changes

bool buzzerState = false;


void setup() {

  // LEDs
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);

  // Buzzer
  pinMode(buzz, OUTPUT);

  // HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LCD
  lcd.init();
  lcd.backlight();

  // Serial Monitor
  Serial.begin(9600);
}


void loop() {

  // -----------------------------
  // SEND ULTRASONIC PULSE
  // -----------------------------

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);


  // -----------------------------
  // MEASURE ECHO TIME
  // -----------------------------

  pingTravelTime = pulseIn(echoPin, HIGH);

  Serial.println(pingTravelTime);


  // -----------------------------
  // STOP MODE
  // -----------------------------

  if (pingTravelTime < 300) {

    lcd.clear();

    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);

    // Buzzer continuously ON
    digitalWrite(buzz, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("STOP");

    // Reset buzzer timing
    buzzerState = false;
    previousMillis = millis();
  }


  // -----------------------------
  // WARNING MODE
  // -----------------------------

  else if (pingTravelTime >= 300 && pingTravelTime <= 550) {

    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WARNING");


    // Beep-beep-beep-beep...
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= beepInterval) {

      previousMillis = currentMillis;

      // Toggle buzzer
      buzzerState = !buzzerState;

      digitalWrite(buzz, buzzerState);
    }
  }


  // -----------------------------
  // SAFE MODE
  // -----------------------------

  else {

    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SAFE");

    // Buzzer OFF
    digitalWrite(buzz, LOW);

    // Reset buzzer timing
    buzzerState = false;
    previousMillis = millis();
  }


  // Small delay for sensor stability
  delay(50);
}

