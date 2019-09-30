#define step_pinx 2  // Pin 9 connected to Steps pin on EasyDriver
#define dir_pinx 3   // Pin 8 connected to Direction pin
#define step_piny 4  // Pin 9 connected to Steps pin on EasyDriver
#define dir_piny 5   // Pin 8 connected to Direction pin
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
      
        digitalWrite(dir_pinx, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
        digitalWrite(step_pinx, HIGH);
        delay(step_speed);
        digitalWrite(step_pinx, LOW);
        delay(step_speed);
    }      
  }
  
    if (analogRead(X_pin) < 312) {  // If joystick is moved right
    
    if (!digitalRead(Limit02)) {}  // check if limit switch is activated
    
      else {  //  if limit switch is not activated, move motor counter clockwise
      
        digitalWrite(dir_pinx, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
        digitalWrite(step_pinx, HIGH);
        delay(step_speed);
        digitalWrite(step_pinx, LOW);
        delay(step_speed);
    }      
  }
    
  if (analogRead(Y_pin) > 712) {  //  If joystick is moved Left
    if (!digitalRead(Limit01)) {}  // check if limit switch is activated
    
      else {  //  if limit switch is not activated, move motor clockwise
      
        digitalWrite(dir_piny, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
        digitalWrite(step_piny, HIGH);
        delay(step_speed);
        digitalWrite(step_piny, LOW);
        delay(step_speed);
    }      
  }
  
    if (analogRead(Y_pin) < 312) {  // If joystick is moved right
    
    if (!digitalRead(Limit02)) {}  // check if limit switch is activated
    
      else {  //  if limit switch is not activated, move motor counter clockwise
      
        digitalWrite(dir_piny, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
        digitalWrite(step_piny, HIGH);
        delay(step_speed);
        digitalWrite(step_piny, LOW);
        delay(step_speed);
    }      
  }
}
