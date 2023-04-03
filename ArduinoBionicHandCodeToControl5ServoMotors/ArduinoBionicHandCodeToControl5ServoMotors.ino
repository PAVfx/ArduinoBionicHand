
  /*
 Controlling a servo with two Push Buttons (incremental) or Two Switches (operaitonal) via Arduino
  when Right  push button is pressed, the servo start moving to the right until it reaches 180( or zero) degrees
  when Left  push button is pressed, the servo start moving to the left until it reaches 180( or zero) degrees
  when switch is set to binary value (0,1,2,3) it will perform 4 operations 
  
  ArduinoBionicHandCodeToControl5ServoMotors.ino = Two_push_buttons_5_Servo_Motors_Default_180_Deg_CW.ino
  */

#include <Servo.h> //include servo library
// Note:
//Use PWM pins for servos, PWM pins = 3, 5, 6, 9, 10, I have 5 servo motors: 4 fingers + 1 thumb, so I will need 5 PWM signals 
Servo servo1;  // initalize/create servo object to control each servo
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
int angle = 180;    // initial angle  for servo
int angleStep = 5; // when PB is pressed, this is the step it will increment by to the left/right

//Use non-PWM pins as Switch and PB pins, non-PWM pins = 2, 4, 7, 8, 12, 13
#define Switch1 2  // pin 2 is connected to left switch
#define Switch2 4  // pin 4 is connected to right switch

#define LEFT 7   // pin 7 is connected to left push button
#define RIGHT 8  // pin 8 is connected to right push button

// cw aka right string = loose
// ccw aka left string = tight

void setup() {
  Serial.begin(9600); //  setup serial baud rate
  servo1.attach(3);  // attach the servo to pwm pin 3 = pinky
  servo2.attach(5);  // attach the servo to pwm pin 5 = ring
  servo3.attach(6);  // attach the servo to pwm pin 6 = middle
  servo4.attach(9);  // attach the servo to pwm pin 9 = index
  servo5.attach(10);  // attach the servo to pwm pin 10 = thumb
  pinMode(2,INPUT_PULLUP); // sets up internal pull up resistor to 5V, so we just ahve to put the signal to GND to complete signal
  pinMode(4,INPUT_PULLUP); // INPUT_PULLUP (20k ohms resistance, this effectively inverts the behavior of the INPUT mode, where HIGH means the sensor is off, and LOW means the sensor is on)
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP); 
  Serial.println("Pav's Servo Control via Switch / Push Button ");
}

void loop() { // run continously
  while(digitalRead(LEFT) == LOW){ // when push button (pin 7) is not pressed, it is considered high, aka not true, and the while loop will not be run
  if (angle >= 0 && angle <= 180) {  //sets limits
  angle = angle + angleStep; //increment desired angle up by 5 deg as long as (while) PB is being pressed, 0 -> 180
  if(angle > 180){
     angle = 180;
    }
  else {
      servo1.write(angle); // move the servo to desired angle
      servo2.write(angle);
      servo3.write(angle);
      servo4.write(angle);
      servo5.write(angle);
      Serial.print("Moved to: ");
      Serial.print(angle);   // prints the angle
      Serial.println(" degree");      
       } // end of else loop 
    } // end of if loop 
  delay(100); // waits 100msec for the servo to get there    
  }// end of while loop for LEFT PB

  while(digitalRead(RIGHT) == LOW){ //when push button (pin 8) is not pressed, it is considered high, aka not true, and while loop will not be run
  if (angle > 0 && angle <= 180) {  //sets limits
  angle = angle - angleStep; //increment desired angle up by 5 deg as long as (while) PB is being pressed, 180 -> 0
  if(angle < 0){
     angle = 0;
    }
  else {
      servo1.write(angle); // move the servo to desired angle
      servo2.write(angle);
      servo3.write(angle);
      servo4.write(angle);
      servo5.write(angle);      
      Serial.print("Moved to: ");
      Serial.print(angle);   // prints the angle
      Serial.println(" degree");      
       } // end of else loop 
    } // end of if loop 
  delay(100); // waits 100msec for the servo to get there    
  }// end of while loop for RIGHT PB
  
  while(digitalRead(LEFT) == HIGH && digitalRead(RIGHT) == HIGH){ // When either PB is not active, use switches for control operation
  if (digitalRead(Switch1) == HIGH && digitalRead(Switch2) == HIGH){ // neither switches pressed = 00
  // if switch is pressed (it will read LOW), if nt pressed it will read high
    Serial.println("Operation 0"); //nothing pressed
    // set servo angleition (20 msec = 20,000 microsecond period)
    servo1.write(180);   // set servo1 angle to 180
    servo2.write(180);   // set servo2 angle to 180
    servo3.write(180);   // set servo3 angle to 180
    servo4.write(180);   // set servo4 angle to 180
    servo5.write(180);   // set servo5 angle to 180
    delay(1000);
    }
       
  if (digitalRead(Switch1) == HIGH && digitalRead(Switch2) == LOW){ // sw2 pressed = 01
  // if keybutton is pressed (it will read LOW)
    Serial.println("Operation 1"); // sw2 pressed
    servo1.write(0);   // set servo1 angle to 0
    servo2.write(0);   // set servo2 angle to 0
    servo3.write(0);   // set servo3 angle to 0
    servo4.write(0);   // set servo4 angle to 0
    servo5.write(0);   // set servo5 angle to 0
    delay(1000); 
    }
       
  if (digitalRead(Switch1) == LOW && digitalRead(Switch2) == HIGH){ // sw1 pressed = 10
  // if keybutton is pressed (it will read LOW)
    Serial.println("Operation 2"); // sw1 pressed
      for (angle = 0; angle <= 180; angle += 1) {   // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo1.write(angle);                      // tell servo1 to go to 0 to 180
      servo2.write(angle);                      // tell servo2 to go to 0 to 180
      servo3.write(angle);                      // tell servo3 to go to 0 to 180
      servo4.write(angle);                      // tell servo4 to go to 0 to 180
      servo5.write(angle);                      // tell servo5 to go to 0 to 180
      delay(100);                               // waits 100ms for the servo to reach the angleition
    }
  }
    
  if (digitalRead(Switch1) == LOW && digitalRead(Switch2) == LOW){ // sw1 & sw2 pressed = 11
  // if keybutton is pressed (it will read LOW)
    Serial.println("Operation 3");  // sw1 & sw2 pressed
      for (angle = 180; angle >= 0; angle -= 1) { // goes from 180 degrees to 0 degrees
      servo1.write(angle);              // tell servo1 to go from 180  to 0
      servo2.write(angle);              // tell servo2 to go to 180 to 0
      servo3.write(angle);              // tell servo3 to go to 180 to 0
      servo4.write(angle);              // tell servo4 to go to 180 to 0
      servo5.write(angle);              // tell servo5 to go to 180 to 0
      delay(100);  
    }
  }     
    delay(100); // so button is not displayed/pressed more than once
  } // end of switch while loop

} // end of continous void loop
