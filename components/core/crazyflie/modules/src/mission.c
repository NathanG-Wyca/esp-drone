/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2011-2012 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * info.c - Receive information requests and send them back to the client
 */

#include <string.h>
#include <math.h>

/*FreeRtos includes*/
#include "FreeRTOS.h"
#include "task.h"

#include "commander.h"
#include "config.h"
#include "crtp.h"
#include "mission.h"
#include "version.h"
#include "pm_esplane.h"
#include "stm32_legacy.h"
#include "static_mem.h"
#include "debug_cf.h"
#include "deck_digital.h"

#define DEBUG_MODULE "MISSION"


//Private functions
static void missionTask(void *param);
static bool isInit = false;


STATIC_MEM_TASK_ALLOC(missionTask, MISSION_TASK_STACKSIZE);

void missionInit(void)
{
  if(isInit)
    return;
  STATIC_MEM_TASK_CREATE(missionTask, missionTask, MISSION_TASK_NAME, NULL, MISSION_TASK_PRI);
  DEBUG_PRINT_LOCAL("----------------------------\n");
  DEBUG_PRINT_LOCAL("Mission Task Created\n");
  isInit = true;
}

void missionTask(void *param)
{
  while (TRUE)
  {
    bool sequence = FALSE;

    //Read Value of SW1 button
    int value_sw1 = digitalRead(0);
    if(value_sw1 == 0){
      sequence = TRUE;
    }
    
    if(sequence){

      DEBUG_PRINT_LOCAL("Sequence launched ! \n");

      vTaskDelay(M2T(2000));

      //EG1 ramp

      /*int thrust_mult = 1;
      double thrust_timestep = 0.1; // Sleep for 0.1s
      int thrust_max =(int) 0xFFFF * 0.7; // 50% of full thrust
      int thrust_min =(int) 0xFFFF * 0;
      double action_period = 3.0; // one action is 6s
      double thrust_step = (thrust_max - thrust_min) / (action_period / thrust_timestep);
      int pitch = 0;
      int roll = 0;
      int yaw = 0;

      int thrust = thrust_min;
      static setpoint_t setpoint;
      while (thrust >= thrust_min) {
        setpoint.thrust = thrust;
        setpoint.attitude.roll = roll;
        setpoint.attitude.pitch = pitch;
        setpoint.attitude.yaw = yaw;
        setpoint.timestamp = xTaskGetTickCount();
        commanderSetSetpoint(&setpoint, COMMANDER_PRIORITY_CRTP);
          
        vTaskDelay(M2T(thrust_timestep*1000)); 

        if (thrust >= thrust_max) {
            thrust_mult = -1;
            DEBUG_PRINT_LOCAL("Thruster's Decreasing ! Landing!\n");
        }
        
        thrust +=(int) thrust_step * thrust_mult;
      }*/

      // EG2 need to uncomment the block
      /*
      static setpoint_t setpoint;
      
      while (TRUE)
      {
        setpoint.mode.x = modeAbs;
        setpoint.mode.y = modeAbs;
        setpoint.mode.z = modeAbs;
        setpoint.position.x = 0.0;
        setpoint.position.y = 0.0;
        setpoint.position.z = 0.5;
        setpoint.attitude.yaw = 0.0;
        setpoint.mode.yaw = modeAbs;        
        commanderSetSetpoint(&setpoint, COMMANDER_PRIORITY_CRTP); 
        vTaskDelay(M2T(100)); 
      }*/
    }
    else{
      DEBUG_PRINT_LOCAL("Sequence not launched, button not pressed! \n");
    }
    vTaskDelay(M2T(1000));
  }
}
