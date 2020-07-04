#include<TimerOne.h>  //library for using interrupts.
#include<string.h>
#include<ctype.h>

#define MOTOR_left 3  //speed sensor of the left weel is connected to pin 3
#define MOTOR_right 2   //speed sensor of the right wheel motor is connected to pin 2

#define step_count 20  //There are 20 steps in the encoder wheel.
#define wheel_diameter 66   //diameter of wheel mentioned in the box at the time of purchase.

//Left motor connections.
int en_left=10;
int in3=9;
int in4=8;

//Right motor connections.
int en_right=6;
int in1=5;
int in2=4;

volatile int pulse_counter_left=0;   //counting the number of pulses generated when the encoder wheel rotates.
volatile int pulse_counter_right=0;

void interrupt_service_routine_left()
{
  pulse_counter_left++;
}

void interrupt_service_routine_right()
{
  pulse_counter_right++;
}

int cm_to_steps(float cm)
{
  int steps;
  float cm_per_step=(((wheel_diameter*3.14)/10)/step_count);
  step=cm/cm_per_step;
  return step;
}

void forward(int step)
{
  pulse_counter_left=0;
  pulse_counter_right=0;

  //Left and Right Motors must move forward.
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  digitalWrite(in1, HIGH)
  digitalWrite(in2, LOW);

  //move as long as the pulse_counter values for both left and right motors is less than required steps.
  while(pulse_counter_left<steps || pulse_counter_right<steps)
  {
    if(pulse_counter_left<steps)
    {
      //the left wheel has not yet reached the desired distance.
      //move forward with maximum speed.
      analogWrite(en_left,255);
    }
    else
    //the left wheel has reached the destination. stop.
    analogWrite(en_left,0);

    if(pulse_counter_right<steps)
    {
      //the right wheel has not yet reached the desired distance.
      //move forward with maximum speed.
      analogWrite(en_right,255);
    }
    else
    //the right wheel has reached the destination. stop.
    analogWrite(en_right,0);
  }

  //stop the motors and reset both the pulse counters.
  analogWrite(en_left,0);
  analogWrite(en_right,0);
  pulse_counter_left=0;
  pulse_counter_right=0
}

void backwards(int steps)
{
  pulse_counter_left=0;
  pulse_counter_right=0;

  //Left and Right Motors must move backwards.
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);

  digitalWrite(in1, HIGH)
  digitalWrite(in2, LOW);

  //move as long as the pulse_counter values for both left and right motors is less than required steps.
  while(pulse_counter_left<steps || pulse_counter_right<steps)
  {
    if(pulse_counter_left<steps)
    {
      //the left wheel has not yet reached the desired distance.
      //move backward with maximum speed.
      analogWrite(en_left,255);
    }
    else
    //the left wheel has reached the destination. stop.
    analogWrite(en_left,0);

    if(pulse_counter_right<steps)
    {
      //the right wheel has not yet reached the desired distance.
      //move backward with maximum speed.
      analogWrite(en_right,255);
    }
    else
    //the right wheel has reached the destination. stop.
    analogWrite(en_right,0);
  }

  //stop the motors and reset both the pulse counters.
  analogWrite(en_left,0);
  analogWrite(en_right,0);
  pulse_counter_left=0;
  pulse_counter_right=0
}

void turn_left(steps)
{
  pulse_counter_left=0;
  pulse_counter_right=0;

  //Left Motor must move forward.
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);

  //right motor should move reverse.
  digitalWrite(in1, HIGH)
  digitalWrite(in2, LOW);

  //move as long as the pulse_counter values for both left and right motors is less than required steps.
  while(pulse_counter_left<steps || pulse_counter_right<steps)
  {
    if(pulse_counter_left<steps)
    {
      //the left wheel has not yet reached the desired distance.
      //move forward with maximum speed.
      analogWrite(en_left,255);
    }
    else
    //the left wheel has reached the destination. stop.
    analogWrite(en_left,0);

    if(pulse_counter_right<steps)
    {
      //the right wheel has not yet reached the desired distance.
      //move backwards with maximum speed.
      analogWrite(en_right,255);
    }
    else
    //the right wheel has reached the destination. stop.
    analogWrite(en_right,0);
  }

  //stop the motors and reset both the pulse counters.
  analogWrite(en_left,0);
  analogWrite(en_right,0);
  pulse_counter_left=0;
  pulse_counter_right=0
}

void turn_right(int steps)
{
  pulse_counter_left=0;
  pulse_counter_right=0;

  //Left Motor must move backward.
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  //Right Motor must move forward.
  digitalWrite(in2, HIGH)
  digitalWrite(in1, LOW);

  //move as long as the pulse_counter values for both left and right motors is less than required steps.
  while(pulse_counter_left<steps || pulse_counter_right<steps)
  {
    if(pulse_counter_left<steps)
    {
      //the left wheel has not yet reached the desired distance.
      //move backwards with maximum speed.
      analogWrite(en_left,255);
    }
    else
    //the left wheel has reached the destination. stop.
    analogWrite(en_left,0);

    if(pulse_counter_right<steps)
    {
      //the right wheel has not yet reached the desired distance.
      //move forward with maximum speed.
      analogWrite(en_right,255);
    }
    else
    //the right wheel has reached the destination. stop.
    analogWrite(en_right,0);
  }

  //stop the motors and reset both the pulse counters.
  analogWrite(en_left,0);
  analogWrite(en_right,0);
  pulse_counter_left=0;
  pulse_counter_right=0
}

void setup()
{
  //Attatch interrupt pins to interrupt_service_routines.
  attachInterrupt(digitalPinToInterrupt(MOTOR_left),interrupt_service_routine_left,RISING);
  attachInterrupt(digitalPinToInterrupt(MOTOR_right),interrupt_service_routine_right,RISING);

  Serial.begin(9600);
  Serial.println("Give commands with distance(cm) specified by direction. Ex(20 Forward)");
}

void loop()
{
  if(Serial.available()>0)
  {
    char s[]=Serial.read();
    Serial.println(c);
    char distance[]=s.substring(0,indexOf(''));
    char direction[]=s.substring(indexOf('')+1);
    int dist=0, j=0;
    int n=strlen(distance);
    //convert distance in character to integer
    for(int i=n-1;i>=0;i--)
    {
      if(isdigit(distance[i]))
      {
        int x=distance[i]-'0';
        dist=dist+x*pow(10,j);
        j++;
      }
    }

    int steps=cm_to_steps(dist);

    if(direction[]=="forward")
    forward(steps);
    if(direction[]=="backward" || direction[]=="reverse")
    backwards(steps);
    if(direction[]=="left")
    turn_left(steps);
    if(direction[]=="right")
    turn_right(steps);
    delay(1000);
  }
}
