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

#include "periph/pwm.h"
#include "periph/gpio.h"
#include <stdio.h>
#include "thread.h"

#define LOW 0
#define HIGH 1

//DigitalOut statpin(D13, LOW); 

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 0.5f

#define dirA GPIO_12
#define dirB GPIO_13

#define CHANNELS    PWM_0_CHANNELS

#define FREQU       1000U
#define STEPS       1000U
#define STEP        1
#define WAIT        15000
#define MAXSPEED STEPS
/* thread's stack */
char threadA_stack [KERNEL_CONF_STACKSIZE_MAIN];
char threadB_stack [KERNEL_CONF_STACKSIZE_MAIN];

/* thread's function */
void *threadA_func(void* arg);

int res;
int state = 0;
int step = STEP;

void setupShield(void)
{  
	gpio_init_out(dirA,GPIO_NOPULL); 
	gpio_init_out(dirB,GPIO_NOPULL);
	if(!(pwm_init(PWM_0, PWM_LEFT, FREQU, STEPS))){
		puts("PWM_0 correctement initialisee");
	}
	if(!(pwm_init(PWM_1, PWM_LEFT, FREQU, STEPS))){
		puts("PWM_1 correctement initialisee");
		}
	if(!pwm_set(PWM_0,1,0)){
		}
	if(!pwm_set(PWM_1,1,0)){
	}
	
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
      if (direct <=1){
        gpio_write(dirB,HIGH);
        }
      else{
        gpio_write(dirB,LOW);
	}

       pwm_set(PWM_1,1,percent);
    }
}
 
void goRightMotor(uint8_t direct, int percent)
{
    if (direct <=4)
    {
      if (direct <=1){
        gpio_write(dirA,HIGH);
        }
    else{
		gpio_write(dirA,LOW);
        }
        
        pwm_set(PWM_0,1,percent);
    }
}
 

void setup(void)
{  
    setupShield();
}

void loopL(void){
	int i;
	goLeftMotor(CW, MAXSPEED);
	
	for(i=0;i<WAIT;i++){printf("%d\n",i);
	}
	
	stopLeftMotor();
	
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}

	goLeftMotor(CCW, MAXSPEED);
	
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}
	
	stopLeftMotor();
	
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}

	}
void loopR(void)
{
	int i;
	goRightMotor(CCW, MAXSPEED);
	
    for(i=0;i<WAIT;i++){printf("%d\n",i);
	}
	//checkShield();
	
	stopRightMotor();
	
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}
	goRightMotor(CW, MAXSPEED);
	//checkShield();
	
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}
	stopRightMotor();
	//checkShield();
  
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}
  
	//puts("fin boucle");
}

void loop(void)
{
	int i;
	goRightMotor(CCW, MAXSPEED);
	goLeftMotor(CW, MAXSPEED);
    for(i=0;i<WAIT;i++){printf("%d\n",i);
	}
	//checkShield();
	
	stopRightMotor();
	stopLeftMotor();
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}
	
	goRightMotor(CW, MAXSPEED);
	goLeftMotor(CCW, MAXSPEED);
	
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}
	
	stopLeftMotor();
	stopRightMotor();
	//checkShield();
  
	for(i=0;i<WAIT;i++){printf("%d\n",i);
		}
  
	//puts("fin boucle");
}
/* thread A function implemetation */
void *threadA_func(void* arg)
{ 
	puts("Entree dans le thread A");
	
    while(1) {
        loop();
    }
   return NULL;
}

void *threadB_func(void* arg)
{ 
	puts("Entree dans le thread B");

    while(1) {
        loopL();
    }
   return NULL;
}

int main(void) {
	setup();
	/* create thread A */
    thread_create(threadA_stack, sizeof(threadA_stack), PRIORITY_MAIN, CREATE_STACKTEST, threadA_func, NULL, "thread A");
    //thread_create(threadB_stack, sizeof(threadB_stack), PRIORITY_MAIN, CREATE_STACKTEST, threadB_func, NULL, "thread B");
   
}
 

