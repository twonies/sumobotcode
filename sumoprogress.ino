#include <Servo.h>
const int piez = 4; //PIEZO
const int leftIrLed=12; //TRANSMITTER LEFT
const int leftIrReciever=13; //IR RECIEVER LEFT
const int rightIrLed=2; // TRANSMITTER RIGHT
const int rightIrReciever=3; //IR RECIVER RIGHT
const int ledRight=9; //LED RIGHT *DEPERCATED*
const int ledLeft=10; //LED LEFT *DEPERCATED*
const int sensorPinR = 7; //FLOOR SENSORS RIGHT
const int sensorPinL = 8; //FLOOR SENSORS LEFT
const int leftServoPin = 6; //LEFT SERVO
const int rightServoPin = 5; //RIGHT SERVO
const int button = 11; //BUTTON TO PRESS
int buttonVal;
const int tim=1; //SETS THE DELAY ON MOTORS *NEW*
Servo servoLeft; //SETS UP THE SERVOS
Servo servoRight;



void setup() {
  // put your setup code here, to run once:
  pinMode(leftIrReciever, INPUT); pinMode(leftIrLed, OUTPUT); //This sets the TRANSMITTER/RECIEVER to INPUT/OUTPUT
  pinMode(rightIrReciever, INPUT); pinMode(rightIrLed, OUTPUT); //This sets the TRANSMITTER/RECIEVER to INPUT/OUTPUT
  pinMode(ledRight, OUTPUT); pinMode(ledLeft,OUTPUT); //This is the two front LEDS
  servoLeft.attach(leftServoPin); //this sets our two motors
  servoRight.attach(rightServoPin); //motor continued to be set
  servoLeft.writeMicroseconds(1500); // sets motor to stationary
  servoRight.writeMicroseconds(1500); // sets motor to stationary
  pinMode(button,INPUT); // this sets the timer button as input
  Serial.begin(9600); //output for the serial monitor
}



void loop() {
// to start off we digital read the button
buttonVal=digitalRead(button); // reads value of button

  Serial.println(buttonVal); //*DEBUG* prints value of button *DEBUG*/

// starts the if command for the inital button presses stops for 5 seconds
   if (buttonVal==1) {
  servoLeft.writeMicroseconds(1500); //stationary motors
  servoRight.writeMicroseconds(1500); //stationary motors
  tone(piez,500,2000); //plays tune for 2000ms (2s)
  delay(3000); //delay 3000ms (3s)
} 
// this here sets the two IR detectors up to see and recieve the 38kHz freq
int irLeft=irDetect(leftIrLed, leftIrReciever, 38000);
int irRight=irDetect(rightIrLed,rightIrReciever,38000);

// THIS NEXT CODE IS FOR LED FOR THE TWO LIGHTS TO BE REMOVED

/*if(irLeft==0){
  digitalWrite(ledLeft, HIGH);
}
else{
  digitalWrite(ledLeft, LOW);
  
}
if(irRight==0){
   digitalWrite(ledRight, HIGH);
 
}
else{
  digitalWrite(ledRight,LOW);
}
*/


/*Start of attack code to remember this code checks
the RCtime function down below to read the buttom if it's on black or white
be sure to check out the function RCtime if you have any questiond */
//First IF just checks to make sure that it's on black and not white so greater then 700
if (RCtime(sensorPinR)>700 && RCtime(sensorPinL)>700){ 
// after checking if on black checks the front IR

//FORWARD ATTACK
if (irRight==0 && irLeft==0){
    servoLeft.writeMicroseconds(2000);
  servoRight.writeMicroseconds(1000);
  delay(tim);

//RIGHT TURN TO
} else if ( irRight==0 && irLeft != 0){
  servoLeft.writeMicroseconds(2000);
  servoRight.writeMicroseconds(2000);
    delay(tim);

//LEFT TURN TO
} else if ( irRight!=0 && irLeft==0){
  servoLeft.writeMicroseconds(1000);
  servoRight.writeMicroseconds(1000);
    delay(tim);

//STATIONARY
} else {
  servoLeft.writeMicroseconds(1500); //counterclock
  servoRight.writeMicroseconds(1500); //clocky
    delay(tim);
}
//IF ON WHITE BACK THE FUCK UP
} else if (RCtime(sensorPinR)<700 && RCtime(sensorPinL)<700){
  servoLeft.writeMicroseconds(1000);
  servoRight.writeMicroseconds(2000);
    delay(tim);
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
