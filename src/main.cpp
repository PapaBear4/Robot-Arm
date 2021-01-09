#include <Arduino.h>
#include <Servo.h>

//set analog potentiometer pins
#define potPinRotate 0 //left stick y
#define potPinArm1 1  //right stick y
#define potPinArm2 2  //right stick x
#define potPinClaw 3 //left stick x

//set pwm servo pins
#define servoPinRotate 3
#define servoPinArm1 5
#define servoPinArm2 6
#define servoPinClaw 9

//declare servos
Servo servoRotate;
Servo servoArm1;
Servo servoArm2;
Servo servoClaw;

//set initial pot vlaues
int potValRot = 5;
int potValArm1 = 5;
int potValArm2 = 5;
int potValClaw = 5;

//set initial angle values
int angleRotate = 90;
int angleArm1 = 45;
int angleArm2 = 45;
int angleClaw = 90;

void printValues(int val1, int val2, int val3, int val4){
  int values[]={val1, val2, val3, val4};
  char *names[]={"rot","arm1","arm2","claw"};
  for (byte i=0;i<4;i=i+1) {
    Serial.print(names[i]);
    Serial.print(":");
    Serial.print(values[i]);
    Serial.print(" ");
  }
}


void setup() {
  // put your setup code here, to run once:
  //start serial
  Serial.begin(9600);
  
  //attach servos
  servoRotate.attach(servoPinRotate);
  servoArm1.attach(servoPinArm1);
  servoArm2.attach(servoPinArm2);
  servoClaw.attach(servoPinClaw);
  
  //initialize positions 
  servoArm1.write(angleArm1);
}

void loop() {
  //read pot values, map to 0-20
  potValRot = map(analogRead(potPinRotate),0,1023,0,11);
  potValArm1 = map(analogRead(potPinArm1),0,1023,0,11);
  potValArm2 = map(analogRead(potPinArm2),0,1023,0,11);
  potValClaw = map(analogRead(potPinClaw),0,1023,0,11);

  printValues(potValRot,potValArm1, potValArm2, potValClaw);
  printValues(angleRotate,angleArm1,angleArm2,angleClaw);
  Serial.println();

//rotate base
if (potValRot > 6 && angleRotate < 180){  //stick left
  angleRotate += 3; //rotate CCW
  servoRotate.write(angleRotate);
  //delay(15);
}
if (potValRot <4  && angleRotate > 0){ //stick right
  angleRotate -= 3; //rotate CW
  servoRotate.write(angleRotate);
  delay(15);
}

//activate claw
if (potValClaw < 4 && angleClaw > 0){ //stick fwd
  angleClaw -= 4; //close
  servoClaw.write(angleClaw);
  delay(15); 
}
if (potValClaw > 6 && angleClaw < 180){ //stick away
  angleClaw += 4; //open
  servoClaw.write(angleClaw);
  delay(15);
}



}  //end void loop()


//function to control the direction and speed of motion
  //for val range of 4-6, do nothing
  //for val <4 move toward zero
  //for val >6 move toward 180
  /*Serial.print(valArm1);
  Serial.print(" ");
  Serial.println(angleArm1);*/
  /*
void servoMove(char servo, int potVal, int angle){
    if (potVal < 4 && angle>=5) {
    angle -= 1;
    servo.write(angle);
    delay(15);
  }
  if (potVal > 6 && angle<=140) {
    angle += 1;
    servo.write(angle);
    delay(15);
  }
}*/

