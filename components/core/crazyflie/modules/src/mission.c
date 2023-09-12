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

#include "config.h"
#include "crtp.h"
#include "mission.h"
#include "version.h"
#include "pm_esplane.h"
#include "stm32_legacy.h"
#include "static_mem.h"
#include "debug_cf.h"
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
    vTaskDelay(M2T(1000));
    DEBUG_PRINT_LOCAL("Mission DOING SOMETHING ! \n");
  }
}
