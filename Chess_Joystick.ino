#define step_pin1 2  // Pin 9 connected to Steps pin on EasyDriver
#define dir_pin1 3   // Pin 8 connected to Direction pin
#define step_pin2 4  // Pin 9 connected to Steps pin on EasyDriver
#define dir_pin2 5   // Pin 8 connected to Direction pin
#define X_pin A0    // Pin A0 connected to joystick x axis
#define Y_pin A1    // Pin A1 connected to joystick y axis
#define Joy_switch 6  // Pin 4 connected to joystick switch
#define Limit01 7  // Pin 2 connected to Limit switch out
#define Limit02 8  // Pin 3 connected to Limit switch out

int step_speed = 10;  // Speed of Stepper motor (higher = slower)

void setup() {
   pinMode(dir_pin1, OUTPUT);
   pinMode(step_pin1, OUTPUT);
   pinMode(dir_pin2, OUTPUT);
   pinMode(step_pin2, OUTPUT);
   pinMode(Limit01, INPUT);
   pinMode(Limit02, INPUT);
   pinMode(Joy_switch, INPUT_PULLUP);
   delay(5);  // Wait for wake up
}

void loop() {
  if (!digitalRead(Joy_switch)) {  //  If Joystick switch is clicked
    delay(500);  // delay for deboucing
    switch (step_speed) {  // check current value of step_speed and change it
      case 1:
        step_speed=10;  // slow speed
        break;
      case 3:
        step_speed=1;  // fast speed
        break;
      case 10:
        step_speed=3;  // medium speed
        break;
    }
  }    
    
  if (analogRead(X_pin) > 712) {  //  If joystick is moved Left
    if (!digitalRead(Limit01)) {}  // check if limit switch is activated
    
      else {  //  if limit switch is not activated, move motor clockwise
      
        digitalWrite(dir_pin1, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
        digitalWrite(step_pin1, HIGH);
        delay(step_speed);
        digitalWrite(step_pin1, LOW);
        delay(step_speed);
    }      
  }
  
    if (analogRead(X_pin) < 312) {  // If joystick is moved right
    
    if (!digitalRead(Limit02)) {}  // check if limit switch is activated
    
      else {  //  if limit switch is not activated, move motor counter clockwise
      
        digitalWrite(dir_pin, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
        digitalWrite(step_pin, HIGH);
        delay(step_speed);
        digitalWrite(step_pin, LOW);
        delay(step_speed);
    }      
  }
    
  if (analogRead(Y_pin) > 712) {  //  If joystick is moved Left
    if (!digitalRead(Limit01)) {}  // check if limit switch is activated
    
      else {  //  if limit switch is not activated, move motor clockwise
      
        digitalWrite(dir_pin2, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
        digitalWrite(step_pin2, HIGH);
        delay(step_speed);
        digitalWrite(step_pin2, LOW);
        delay(step_speed);
    }      
  }
  
    if (analogRead(Y_pin) < 312) {  // If joystick is moved right
    
    if (!digitalRead(Limit02)) {}  // check if limit switch is activated
    
      else {  //  if limit switch is not activated, move motor counter clockwise
      
        digitalWrite(dir_pin2, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
        digitalWrite(step_pin2, HIGH);
        delay(step_speed);
        digitalWrite(step_pin2, LOW);
        delay(step_speed);
    }      
  }
}
