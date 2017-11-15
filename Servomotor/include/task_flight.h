#ifndef ADRONE_TASK_FLIGHT_H
#define ADRONE_TASK_FLIGHT_H

#include <FreeRTOS.h>
#include <task.h>

#include "system.h"
#include "matrix.h"
#include "sensorfusion.h"


namespace adrone
{
	void flight_task(void * pvParameters)
	{		
	    asystem.flight.acce_z = 0.0;
	    asystem.flight.gyro_x = 0.0;
	    asystem.flight.gyro_y = 0.0;
	    asystem.flight.gyro_z = 0.0;

	    asystem.motor[0].pid.init(0.0035 , 0.000002, 0.05 , 0.05);
	    asystem.motor[1].pid.init(5.0    , 0.5     , 10.0 , 0.05);
	    asystem.motor[2].pid.init(5.0    , 0.5     , 10.0 , 0.05);
	    asystem.motor[3].pid.init(5.0    , 0.5     , 10.0 , 0.05);

		adrone::sensorfusion fusion;
		double l = 4.0;
		double lambda = 1.0;

		unsigned counter = 0;
		bool flag = true;
		double yaww = 0;

		while(true)
		{
			adrone::matrix angle_position = fusion.update();
        	//printf("%f  %f  %f  %f  %f  %f\n", angle_position(0,0), angle_position(1,0), angle_position(2,0), angle_position(3,0), angle_position(4,0), angle_position(5,0));

        	if (counter >= 10 && flag)
	        {
	            flag = false;
	            yaww  = angle_position(5,0);
	        }
	        else
	        {
	            ++counter;
		     }

	        double a[4], u[4], uOperacao[4] = {500.0,500.0,500.0,500.0};

	        u[0] = asystem.motor[0].pid.update(angle_position(2,0), asystem.flight.acce_z);
	        u[1] = asystem.motor[1].pid.update(asystem.flight.gyro_x, angle_position(3,0));
	        u[2] = asystem.motor[2].pid.update(asystem.flight.gyro_y, angle_position(4,0));
	        u[3] = asystem.motor[3].pid.update(asystem.flight.gyro_z, angle_position(5,0)-yaww);

	        a[0] = (u[0]/4.0 - u[2] / (2.0 * l) - u[3] / (4.0 * lambda)) + uOperacao[0];
	        a[1] = (u[0]/4.0 - u[1] / (2.0 * l) + u[3] / (4.0 * lambda)) + uOperacao[1];
	        a[2] = (u[0]/4.0 + u[2] / (2.0 * l) - u[3] / (4.0 * lambda)) + uOperacao[2];
	        a[3] = (u[0]/4.0 + u[1] / (2.0 * l) + u[3] / (4.0 * lambda)) + uOperacao[3];

			//printf("A %f %f %f %f\n", a[0], a[1], a[2], a[3]);
	        if (asystem.power) 
	        {
		        asystem.motor[0].pwm = (a[0] > 0) ? a[0] : 0; asystem.motor[0].pwm = (a[0]  < 4096) ? a[0] : 4096;
		        asystem.motor[1].pwm = (a[1] > 0) ? a[1] : 0; asystem.motor[1].pwm = (a[1]  < 4096) ? a[1] : 4096;
		        asystem.motor[2].pwm = (a[2] > 0) ? a[2] : 0; asystem.motor[2].pwm = (a[2]  < 4096) ? a[2] : 4096;
		        asystem.motor[3].pwm = (a[3] > 0) ? a[3] : 0; asystem.motor[3].pwm = (a[3]  < 4096) ? a[3] : 4096;
		    }
		    else 
		    {
		    	asystem.motor[0].pwm = 0;
		    	asystem.motor[1].pwm = 0;
		    	asystem.motor[2].pwm = 0;
		    	asystem.motor[3].pwm = 0;
		    }

	        //printf("pwm %d %d %d %d\n", asystem.motor[0].pwm, asystem.motor[1].pwm, asystem.motor[2].pwm, asystem.motor[3].pwm);
	        vTaskDelay( 50 / portTICK_PERIOD_MS );
		}

		vTaskDelete(NULL);
	}
}

#endif