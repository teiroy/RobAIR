/* 
  Example of Program for the MonsterMoto Shield on the ST Nucleo L152RE
  Code by : Vivien Michel
  
  Based on the Arduino sketch example coded by: Jim Lindblom,  SparkFun Electronics
 
 License: CC-SA 3.0, feel free to use this code however you'd like.
 Please improve upon it! Let me know how you've made it better.
 
 This is really simple example code to get you some basic
 functionality with the MonsterMoto Shield. The MonsterMote uses
 two VNH2SP30 high-current full-bridge motor drivers.
 */

#include "pwm.h"
#include "gpio.h"
#include "hwtimer.h"

#define LOW 0
#define HIGH 1

//DigitalOut statpin(D13, LOW); 

#define MAXSPEED 1.0f

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 0.5f

#define dirA GPIO_15
#define dirB GPIO_8



void setupShield(void)
{  
	hwtimer_init();
	gpio_init_out(dirA,GPIO_NOPULL); 
	gpio_init_out(dirB,GPIO_NOPULL); 
	if(!pwm_init(PWM_0, PWM_CENTER, 100, 1)){
	}
	if(!pwm_init(PWM_1, PWM_CENTER, 100, 1)){
		}
	pwm_set(PWM_0,1,0);
	pwm_set(PWM_1,1,0);
}

/*void checkShield()
{  
  if ((csLeftpin.read_u16() < CS_THRESHOLD) && (csRightpin.read_u16() < CS_THRESHOLD))
    statpin.write(HIGH);
  else 
      statpin.write(LOW);
}*/


void stopLeftMotor(void)
{
       pwm_set(PWM_0,1,0);
}

void stopRightMotor(void)
{
        pwm_set(PWM_1,1,0);
}

/* 
 set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND
 
BRAKEVCC 0
CW   1
CCW  2
BRAKEGND 3
 
pwm: should be a value between 0.0f and 1.0f, higher the number, the faster it'll go
 */
 
void goLeftMotor(uint8_t direct, int percent)
{
    if (direct <=4)
    {
      if (direct <=1)
        gpio_write(dirB,HIGH);
      else
        gpio_write(dirB,LOW);

       pwm_set(PWM_1,1,percent);
    }
}
 
void goRightMotor(uint8_t direct, int percent)
{
    if (direct <=4)
    {
      if (direct <=1)
        gpio_write(dirA,HIGH);
    else
        gpio_write(dirA,LOW);
        
        pwm_set(PWM_0,1,percent);
    }
}
 

void setup(void)
{  
    setupShield();
}

void loop(void)
{
  goLeftMotor(CW, MAXSPEED);
  goRightMotor(CCW, MAXSPEED);
  //checkShield();
  hwtimer_wait(HWTIMER_TICKS(1000));
  stopLeftMotor();
  stopRightMotor();
  //checkShield();
  hwtimer_wait(HWTIMER_TICKS(1000));

  goLeftMotor(CCW, MAXSPEED);
  goRightMotor(CW, MAXSPEED);
  //checkShield();
  hwtimer_wait(HWTIMER_TICKS(1000));

  stopLeftMotor();
  stopRightMotor();
  //checkShield();
  hwtimer_wait(HWTIMER_TICKS(1000));
}

int main(void) {
    LED_GREEN_TOGGLE;
    setup();
    while(1) {
        loop();
    }
}
 
