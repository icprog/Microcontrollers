#ifndef ADRONE_TASK_PWM_H
#define ADRONE_TASK_PWM_H

#include "pwm.h"
#include "config.h"


namespace adrone
{
	void pwm_task(void * pvParameters)
	{
	    //SYSDATA *sys = (SYSDATA*)pvParameters;

	    adrone::pwm motor1, motor2, motor3, motor4;

	    motor1.init(MOTOR1);
	    motor2.init(MOTOR2);
	    motor3.init(MOTOR3);
	    motor4.init(MOTOR4);
	    

	    for(;;)
	    {
	    	//printf("Task PWM %d %d %d %d\n", sys.motor[0].pwm, sys.motor[1].pwm, sys.motor[2].pwm, sys.motor[3].pwm);

			motor1.update(asystem.motor[0].pwm);
	        motor2.update(asystem.motor[1].pwm);
	        motor3.update(asystem.motor[2].pwm);
	        motor4.update(asystem.motor[3].pwm);

	        vTaskDelay(1 / portTICK_PERIOD_MS);
	    }

	    vTaskDelete(NULL);
	}
}

#endif