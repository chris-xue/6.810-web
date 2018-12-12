#include <Servo.h>
//#define ACTIVATED LOW
Servo myservo1;
Servo myservo2;
int pin = A0;
int force;
//int button = 2;
//int buttonState = 0;
//
//String mode = "go";
//int prevState = 1; //unactivated

String prev_mode = "idle";
String curr_mode = "idle";
unsigned long last_time = 0;
unsigned long curr_time = 0;

int LOWER = 50;
int UPPER = 270;

void setup() {
  Serial.begin(9600);
  myservo2.attach(9);
  myservo1.attach(8);
}

void loosen() {
  myservo1.write(45);
  myservo2.write(135);  
}

void tighten() {
  myservo1.write(135);
  myservo2.write(45);  
}

void pause() {
  myservo1.write(90);
  myservo2.write(90);  
}

void loop() {
  force = analogRead(pin);
  Serial.println("force " + String(force) + ", prev: " + prev_mode + " , curr: " + curr_mode);
  Serial.println(force);
  curr_time = millis();
  Serial.println(curr_time);
  Serial.println(last_time);
  
  if (curr_mode == "idle") {  
    if (force < LOWER) {
      if (curr_time - last_time > 2000 or prev_mode != "tighten" ){
        tighten();    
        prev_mode = "idle";
        curr_mode = "tighten";
      }
    }
  
    if (force > UPPER) {
       if (curr_time - last_time > 2000 or prev_mode != "loosen" ){
          loosen();   
          prev_mode = "idle";
          curr_mode = "loosen";
       }
    }

    else {
        pause();  
    }
  }

  else if (curr_mode == "tighten") {
    tighten();
    if (force > LOWER and force < UPPER) {
      prev_mode = "tighten";
      curr_mode = "idle";
      last_time = curr_time;
    }
  }

  else if (curr_mode == "loosen") {
    loosen();
    if (force > LOWER and force < UPPER) {
      prev_mode = "loosen";
      curr_mode = "idle";
      last_time = curr_time;
    }
  }
  
  delay(100);
}
