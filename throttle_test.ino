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
  aux_servo.write(SERVO_MIN);
  Serial.println("servos set to zero, start throttle");
  
  
//  throttle_servo.write(SERVO_MAX);
//  Serial.setTimeout(30000);
//  Serial.println("Throttle max, write 'end' when calibrated");
//  Serial.findUntil("end", "\n");
//  
//  throttle_servo.write(SERVO_MIN);
//  Serial.println("Throttle min, write 'end' when calibrated");
//  Serial.findUntil("end", "\n");
  
  throttle_servo.write(SERVO_MIN);
  yaw_servo.write(SERVO_MAX);
  
  delay(5000);
  
  yaw_servo.write(SERVO_MIDDLE);
  
  Serial.println("Start accelerating");
  for (int throttle = SERVO_MIN; throttle < SERVO_MIN + 500; throttle += 20) {
    Serial.println(throttle);
    throttle_servo.write(throttle);
    delay(1000);
  }
  
  delay(5000);
  
  Serial.println("Cool down");
  for (int throttle = SERVO_MIN + 500; throttle >= SERVO_MIN; throttle -= 20) {
    Serial.println(throttle);
    throttle_servo.write(throttle);
    delay(1000);
  }
  
  Serial.println("Minimum throttle");
  throttle_servo.write(SERVO_MIN);
  delay(5000);
  Serial.println("Disarm motors");
  yaw_servo.write(SERVO_MIN);
  
  Serial.println("Test if motors still run");
  throttle_servo.write(SERVO_MIN + 300);
  delay(2000);
  throttle_servo.write(SERVO_MIN);
}

void loop() {
  throttle_servo.write(SERVO_MIN + 300);
  delay(10000);
  
  throttle_servo.write(SERVO_MIN);
  delay(10000);
}
