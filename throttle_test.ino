#include <Servo.h>

#define throttle_pin 10
#define yaw_pin 9
#define pitch_pin 8
#define roll_pin 7
#define aux_pin 6

#define SERVO_MIDDLE 1500
#define SERVO_MIN 1000
#define SERVO_MAX 2000
#define THROTTLE_MAX 1800
#define THROTTLE_MIN 1150
#define OFFSET_SERVO_VALUE(val) (SERVO_MIDDLE + val)

Servo throttle_servo;
Servo yaw_servo;
Servo pitch_servo;
Servo roll_servo;
Servo aux_servo;

int static_throttle = SERVO_MIN;

void setup() {

  Serial.begin(9600);
  Serial.println("Start");
  
  throttle_servo.attach(throttle_pin);
  yaw_servo.attach(yaw_pin);
  pitch_servo.attach(pitch_pin);
  roll_servo.attach(roll_pin);
  aux_servo.attach(aux_pin);
  Serial.println("Servos attached");
  
  yaw_servo.write(SERVO_MIDDLE);
  pitch_servo.write(SERVO_MIDDLE);
  roll_servo.write(SERVO_MIDDLE);
  aux_servo.write(SERVO_MAX);
  Serial.println("servos set to zero, start throttle");
  
  Serial.println("Calibrate");
  calibrate();
  arm_motors();
  
  Serial.println("Give number: ");
  int uselessnumber = Serial.parseInt();
  Serial.print("Number: ");
  Serial.println(uselessnumber);
//  throttle_servo.write(SERVO_MAX);
//  Serial.setTimeout(30000);
//  Serial.println("Throttle max, write 'end' when calibrated");
//  Serial.findUntil("end", "\n");
//  
//  throttle_servo.write(SERVO_MIN);
//  Serial.println("Throttle min, write 'end' when calibrated");
//  Serial.findUntil("end", "\n");
  
//  Serial.println("Start accelerating");
//  for (int throttle = SERVO_MIN; throttle < SERVO_MIN + 500; throttle += 20) {
//    Serial.println(throttle);
//    throttle_servo.write(throttle);
//    delay(1000);
//  }
//  
//  delay(5000);
//  
//  Serial.println("Cool down");
//  for (int throttle = SERVO_MIN + 500; throttle >= SERVO_MIN; throttle -= 20) {
//    Serial.println(throttle);
//    throttle_servo.write(throttle);
//    delay(1000);
//  }

  
}

void loop() {
  if (Serial.available() > 0) {
    int value = Serial.parseInt();
    if (value > 1000) {
      Serial.print("New throttle: ");
      Serial.println(value, DEC);
      throttle_servo.write(value);
    }
    else if (value == 1) {
      arm_motors();
    }
    else if (value == 0) {
      disarm_motors();
    }
    else if (value == 2) {
      Serial.println("Set, ROLL: 1, PITCH: 2, YAW: 3");
      while (Serial.available() <= 0) {
        delay(500);
      }
      int newvalue = Serial.parseInt();
      Serial.print("Input: ");
      Serial.println(newvalue);
      if (newvalue == 1) {
        Serial.println("ROLL MID: ");
        while (Serial.available() <= 0) {
          delay(500);
        }
        roll_servo.write(Serial.parseInt());
        delay(500);
        Serial.print("Roll value: ");
        Serial.println(roll_servo.readMicroseconds());
      }
      else if (newvalue == 2) {
        Serial.println("PITCH MID: ");
        while (Serial.available() <= 0) {
          delay(500);
        }
        pitch_servo.write(Serial.parseInt());
        delay(500);
        Serial.print("Pitch value: ");
        Serial.println(pitch_servo.readMicroseconds());
      }
      else if (newvalue == 3) {
        Serial.println("YAW MID: ");
        while (Serial.available() <= 0) {
          delay(500);
        }
        yaw_servo.write(Serial.parseInt());
        delay(500);
        Serial.print("Yaw value: ");
        Serial.println(yaw_servo.readMicroseconds());
      }
    }
//    else if (value == 2) {  // calibration acro gyro
//      disarm_motors();
//      throttle_servo.write(SERVO_MIN);
//      yaw_servo.write(SERVO_MIN);
//      pitch_servo.write(SERVO_MIN);
//      roll_servo.write(SERVO_MIDDLE);
//      delay(2000);
//    }
//    else if (value == 3) { // calibration stable acc
//      disarm_motors();
//      yaw_servo.write(SERVO_MIN);
//      throttle_servo.write(SERVO_MAX);
//      pitch_servo.write(SERVO_MIN);
//      roll_servo.write(SERVO_MIDDLE);
//    }
//    else if (value == 4) { // trim acc pitch UP
//      disarm_motors();
//      yaw_servo.write(SERVO_MIDDLE);
//      throttle_servo.write(SERVO_MAX);
//      pitch_servo.write(SERVO_MAX);
//      roll_servo.write(SERVO_MIDDLE);
//    }
//    else if (value == 5) { // trim acc pitch DOWN
//      disarm_motors();
//      yaw_servo.write(SERVO_MIDDLE);
//      throttle_servo.write(SERVO_MAX);
//      pitch_servo.write(SERVO_MIN);
//      roll_servo.write(SERVO_MIDDLE);
//    }
//    else if (value == 6) { // trim acc roll LEFT
//      disarm_motors();
//      yaw_servo.write(SERVO_MIDDLE);
//      throttle_servo.write(SERVO_MAX);
//      pitch_servo.write(SERVO_MIDDLE);
//      roll_servo.write(SERVO_MIN);
//    }
//    else if (value == 7) { // trim acc roll RIGHT
//      disarm_motors();
//      yaw_servo.write(SERVO_MIDDLE);
//      throttle_servo.write(SERVO_MAX);
//      pitch_servo.write(SERVO_MIDDLE);
//      roll_servo.write(SERVO_MAX);
//    }
  }
  delay(1000);
}

void calibrate() {
  throttle_servo.write(SERVO_MIN);
  delay(1000);
  yaw_servo.write(SERVO_MIN);
  delay(1000);
  pitch_servo.write(SERVO_MIN);
  delay(1000);
  yaw_servo.write(SERVO_MAX);
  delay(1000);
  yaw_servo.write(SERVO_MIDDLE);
  delay(1000);
  pitch_servo.write(SERVO_MIDDLE);
  Serial.println("Calibration ready");
}

void arm_motors() {
  pitch_servo.write(SERVO_MIDDLE);
  roll_servo.write(SERVO_MIDDLE);
  throttle_servo.write(SERVO_MIN);
  yaw_servo.write(SERVO_MAX);
  
  delay(3000);
  
  yaw_servo.write(SERVO_MIDDLE);
  Serial.println("Motors armed");
}

void disarm_motors() {
  Serial.println("Minimum throttle");
  throttle_servo.write(SERVO_MIN);
  Serial.println("Disarm motors");
  yaw_servo.write(SERVO_MIN);
}
