// Include the AccelStepper Library
#include <AccelStepper.h>
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11


// Number of steps for one full rotation
const int full_rotation = 48;
const int half_rotation = 96;


// Define step constant
#define FULLSTEP 4
float accel = 50.0;       // 75 por defecto acceleration
float maxSpeed = 500.0;   // maximum speed to attain
float cycle = 5000.0;     // 5000 por defecto, number of steps required to ramp up to full speed
int clockWise = 1;               // clockwise direction
//int counterClockWise = -1;       // counter-clockwise direction
// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper stepper(FULLSTEP, IN1, IN3, IN2, IN4);

void setup() {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
 // myStepper.setMaxSpeed(1000.0);
 // myStepper.setAcceleration(50.0);


  //izquierda(1000);
}

void loop() {

 
accelerateThenRun(cycle, accel, maxSpeed, clockWise);
apagado();
encendido();
accelerateThenRun(cycle, accel, maxSpeed, -clockWise);
}

void apagado(){
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
 delay(5000);
  
}

void encendido()
{
   delay(1000);
  digitalWrite(IN1,HIGH);
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,HIGH);

}
void accelerateThenRun(float numSteps, float acceleration, float maximumSpeed, int clockDir)
{
  stepper.moveTo(clockDir * numSteps);                                       //Set target steps and direction
  stepper.setMaxSpeed(maximumSpeed);
  stepper.setAcceleration(acceleration);
  //speed : The most recently set speed. 
  while (clockDir * stepper.speed() < maximumSpeed)         //Run up to max speed or until key is pressed
  {
    stepper.run();
    /*if (kpd.getKey() != NO_KEY) {
      break; //Press a key to stop acceleration phase
    }*/
  }  //end while

  if (stepper.speed() == clockDir * maximumSpeed)          //If stepper is at max speed then no key has been pressed yet
  {
    /* while (kpd.getKey() == NO_KEY) {
      stepper.runSpeed(); //Run at max speed unless key pressed
    }*/
    stepper.stop();

    while ( stepper.isRunning()  )//&& kpd.getKey() == NO_KEY )  //loop until motor stops or key is pressed
    {
      stepper.run();
     }
  
    
    stepper.setCurrentPosition(0);                         //Reset position/speed to zero so we get acceleration on next start
  }   //end if
}

