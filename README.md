# SimpleParkingSensor
Simple parking sensor using basic electronic components.

# Components used: 
Arduino UNO, HCSR04 Ultrasonic Sensor, LCD with I2C module, LEDs(Red, Green and Yellow), Buzzer, Jumper wires and Single-strand wires.

# Software: 
Arduino IDE

I have included a video of the working of this parking sensor. Do check it out.

# Basic Logic: 
SAFE, LED GREEN ON (Other LEDs OFF), NO BUZZER.
WARNING, LED YELLOW ON (Other LEDs OFF), BUZZER - Beep-Beep-Beep-Beep...
STOP, LED RED ON (Other LEDs OFF), BUZZER - Beeeeeee..pppp...


# Initial Design: 
Used PingTravelTime constraints for the STOP, WARNING and SAFE conditions.

The main *issue* that came up is that void loop() itself is already running once per second because of delay(1000). If you put a while loop inside the warning condition, the Arduino can get stuck there and stop updating the distance.

The *clean approach* is non-blocking timing using millis(). That lets the Arduino continuously measure distance while independently toggling the buzzer.






