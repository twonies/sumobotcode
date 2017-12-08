#include <Servo.h>
const int piez = 4; //PIEZO
const int leftIrLed=12; //TRANSMITTER LEFT
const int leftIrReciever=13; //IR RECIEVER LEFT
const int rightIrLed=2; // TRANSMITTER RIGHT
const int rightIrReciever=3; //IR RECIVER RIGHT
//const int ledRight=9; //LED RIGHT *DEPERCATED*
//const int ledLeft=10; //LED LEFT *DEPERCATED*
const int sensorPinR = 7; //FLOOR SENSORS RIGHT
const int sensorPinL = 8; //FLOOR SENSORS LEFT
const int leftServoPin = 6; //LEFT SERVO
const int rightServoPin = 5; //RIGHT SERVO
const int button = 11; //BUTTON TO PRESS
int buttonVal;
const int black=200;
const int tim=1; //SETS THE DELAY ON MOTORS *NEW*
Servo servoLeft; //SETS UP THE SERVOS
Servo servoRight;



void setup() {
  // put your setup code here, to run once:
  pinMode(leftIrReciever, INPUT); pinMode(leftIrLed, OUTPUT); //This sets the TRANSMITTER/RECIEVER to INPUT/OUTPUT
  pinMode(rightIrReciever, INPUT); pinMode(rightIrLed, OUTPUT); //This sets the TRANSMITTER/RECIEVER to INPUT/OUTPUT
 // pinMode(ledRight, OUTPUT); pinMode(ledLeft,OUTPUT); //This is the two front LEDS
  servoLeft.attach(leftServoPin); //this sets our two motors
  servoRight.attach(rightServoPin); //motor continued to be set
  servoLeft.writeMicroseconds(1500); // sets motor to stationary
  servoRight.writeMicroseconds(1500); // sets motor to stationary
  pinMode(button,INPUT); // this sets the timer button as input
  Serial.begin(9600); //output for the serial monitor
}



void loop() {
int irLeft=irDetect(leftIrLed, leftIrReciever, 38000);
int irRight=irDetect(rightIrLed,rightIrReciever,38000);
// to start off we digital read the button
buttonVal=digitalRead(button); // reads value of button
Serial.println(buttonVal);
Serial.println(RCtime(sensorPinR));
Serial.println(RCtime(sensorPinL));
 // Serial.println(buttonVal); //*DEBUG* prints value of button *DEBUG*/

// starts the if command for the inital button presses stops for 5 seconds
   if (buttonVal==1) {
  servoLeft.writeMicroseconds(1500); //stationary motors
  servoRight.writeMicroseconds(1500); //stati onary motors
  tone(piez,500,5000); //plays tune for 2000ms (2s)
  //delay(4000); //delay 3000ms (3s)
} else if (buttonVal==0) {
  if ( RCtime(sensorPinR)<300 || RCtime(sensorPinL)<300){
    servoLeft.writeMicroseconds(2000);
    servoRight.writeMicroseconds(1000);
    delay(2000);
  } else if(( RCtime(sensorPinR)>300 || RCtime(sensorPinL)>300)) {
// this here sets the two IR detectors up to see and recieve the 38kHz freq

Serial.print(" Left: ");
Serial.print(irLeft);
Serial.print(" Right: ");
Serial.println(irRight);

// THIS NEXT CODE IS FOR LED FOR THE TWO LIGHTS TO BE REMOVED
//FORWARD ATTACK
if (irRight==0 && irLeft==0){
  servoLeft.writeMicroseconds(1000);
  servoRight.writeMicroseconds(2000);
 // Serial.println("1");
// delay(tim);
//RIGHT TURN TO
} else if ( irRight==0 && irLeft != 0){
  servoLeft.writeMicroseconds(2000);
  servoRight.writeMicroseconds(2000);
  //Serial.println("2");

 //   delay(tim);

//LEFT TURN TO
} else if ( irRight!=0 && irLeft==0){
  servoLeft.writeMicroseconds(1000);
  servoRight.writeMicroseconds(1000);
  //  Serial.println("3");

 //   delay(tim);

//STATIONARY
} else {
  servoLeft.writeMicroseconds(1480); //counterclock
  servoRight.writeMicroseconds(1500); //clocky
  //  Serial.println("4");

 //   delay(tim);
}
}
}
}

//THIS FUNCTION BELOW IS FOR THE IR DECTION IT WILL RECIEVE AND UNDERSTAND THE FREQ
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  //SETS THE TRANSMITTER TO OUTPUT 38kHz
   tone(irLedPin, frequency, 8);
  delay(1);
  //READS THE RECIEVER
  int ir=digitalRead(irReceiverPin);
  delay(1);
  //GIVES THE RECIEVER VALUE BACK
  return ir;
}

//This is for flow sesnsors
long RCtime(int sensPin){
  long result = 0;
  //SETS OUTPUTS
  pinMode(sensPin, OUTPUT);
  //MAKE THE OUTPUT START READING
  digitalWrite(sensPin, HIGH);
  delay(1);
 //sets input
  pinMode(sensPin, INPUT);
  digitalWrite(sensPin, LOW);
  //Then Reads
  while(digitalRead(sensPin)){
    result++;
  }
  return result;
}

