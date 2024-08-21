// This is the starter code for the Lab 4 Task 2B.
// Designed for ECE/CSE 474.
//
// Please read through the entire file and make sure
// you understand your tasks, the structure of the code,
// and the hints you are given (although you are not
// required to follow them)
//
// The only requirement is to use the three tasks specified
// in the main function. Feel free to add/delete the code we
// provided, though it is recommended to follow the hints.
//
// Here's the documentation page for FreeRTOS.
// You may want to look at it when doing this assignment.
// https://www.freertos.org/FreeRTOS-quick-start-guide.html

#include "FreeRTOS.h"
#include "task.h"
// Include the LCD driver's header file, the PLL driver's header file,
// and your own header file here.
#include <SSD2119_Display.h>
#include <SSD2119_Touch.h>
#include <PLL_Header.h>
#include <Lab4_Inits.h>
#include <lab4.h>
#include <tm4c1294ncpdt.h>

// After skimming through the entire file,
// you might want to add some FSM states here.
enum TL_States {TL_Init, TL_Off, TL_Go, TL_Warn, TL_Stop} TL_State; // initialize states

// Hint:
//
// The following global variables are flags you may want to use
int pedestrian_status = 0;
int onoff_status = 0;


// Below are function prototypes for our RTOS task.
// You should not change the function declerations.
// However, you are allowed to add more helper functions
// as needed.

// Task function that checks the state of the virtual pedestrian button.
// Keeps track of how many seconds the pedestrian button has been pressed.
// Once the user has pressed the virtual pedestrian button for 2 seconds,
// it will set the global flag indicating the virtual pedestrian button
// has been pressed.
void Pedestrian(void *p);

// Task function that checks the state of the virtual onoff button.
// Keeps track of how many seconds the onoff button has been pressed.
// Once the user has pressed the onoff button for 2 seconds,
// it will set the global flag indicating the onoff button has been
// pressed
void StartStop(void *p);

// Task function that represents your Finite State Machine.
// Keeps track of how many seconds the virtual traffic light has been
// lighting on. It will update the state of the traffic light system
// every 5 seconds or once there's virtual button input.
void Control(void *p);

// Helper function that represents your FSM.
// You are allowed to change this function decleration.
//
// Handles the traffic light state transition.
void FSM(void);


// Do not modify this function.
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName) {
  // This function can not return, so loop forever.  Interrupts are disabled
  // on entry to this function, so no processor interrupts will interrupt
  // this loop.
  while (1) {}
}


// Initialize FreeRTOS and start the tasks.
int main(void) {
  // STEP 1
  //
  // This is the beginning of the main function,
  // Initialize your system by initialize the display and touch
  // functionalities of your SSD2119 touch display assembly. You may
  // also want to initialize (draw) your virtual buttons here.
  // Moreover, initialize the PLL to set the system clock to 60 MHz.
  
  enum frequency freq = PRESET2;  // 60 MHz
  PLL_Init(freq); // initialize the PLL
  LCD_Init();     // initialize the display
  LCD_ColorFill(Color4[15]); 
  Buttons_Init(); // initialize virtual buttons setup
  Touch_Init();
  Lights_Init();
  /*
  LCD_Init();     // initialize the display
  LCD_ColorFill(Color4[15]); 
  Buttons_Init(); // initialize virtual buttons setup
  Touch_Init();   // initialize the touch
  Lights_Init();
  */
  // STEP 2
  //
  // The code below creates three tasks.
  // Your task here is to assign priorities to the tasks.
  //
  // Think about which task(s) should be given the highest
  // priority and which should be given lower. It is possible to assign
  // the same priority to all the tasks, however.
  //
  // Priorities are in range: [0, configMAX_PRIORITIES - 1], where
  // configMAX_PRIORITIES - 1 corresponds to the highest priority and
  // 0 corresponds to the lowest priority.
  // You can find configMAX_PRIORITIES defined in the file called FreeRTOSConfig.h
  // under the freertos_demo directory.
  //
  // You should not create more tasks. However, you are allowed to add as many
  // helper functions as you want.
  // xTaskCreate(Function Name,
  //             Descriptive Task Name,
  //             Stack Depth,
  //             Task Function Parameter,
  //             Priority,
  //             Task Handle);
  xTaskCreate(StartStop, (const char *)"StartStopButton", 1024, NULL, 15, NULL); 
  xTaskCreate(Pedestrian, (const char *)"PedestrianButton", 1024, NULL, 14, NULL);
  xTaskCreate(Control, (const char *)"Control FSM", 1024, NULL, 13, NULL);
  
  // Start the scheduler. This should not return.
  // The scheduler will do the scheduling and switch between
  // different tasks for you.
  // Refer to the lecture slides and RTOS documentation
  // page for more details about task scheduling and context switching.
  //
  // One important concept for context switching and task scheduling
  // is preemption. Think about what the terminology preemptive and
  // non-preemptive mean.
  //
  // Hint: Non-preemptive scheduling will allow other tasks to be scheduled
  // after the current task has entered the "waiting state". That is, in our context,
  // the current task will keep running until it reaches vTaskDelay
  // (you'll see this in task functions).
  //
  // You can find in FreeRTOSConfig.h the setting of preemption
  // for the RTOS. Feel free to change this setting as needed.
  vTaskStartScheduler();

  // In case the scheduler returns for some reason, loop forever.
  while(1) {}
}

void StartStop(void *p) {
  // Hint:
  //
  // Static variable will only be decleared once and
  // will retain its last assigned value until the entire
  // program exits
  static int curr_onoff_tick_time = 0;
  static int prev_onoff_tick_time = 0;

  // xTaskGetTickCount() will return the count of ticks
  // since the Task Scheduler started (i.e. your program starts executing).
  //
  // The tick rate (configTICK_RATE_HZ) is defined in FreeRTOSConfig.h,
  // the default rate is 1000 (1KHz), so one tick is equivalent to 1 ms
  //
  // It is similar to the timer we used before, but you'll
  // need to calculate the time elapsed by taking the difference
  // between curr_tick and prev_tick.
  curr_onoff_tick_time = xTaskGetTickCount();

  // STEP 3
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual StartStop button has been
  // pressed for 2 seconds and needs to set the global flags accordingly
  //
  // Task function should never return so is typically
  // implemented as an infinite loop
  //
  // The vTaskDelay(n) will cause the task to enter Blocked state
  // for n system clock ticks. i.e. the task is unblocked
  // after n systicks and will enter Ready State to be arranged for
  // running
  while (1) {
    curr_onoff_tick_time = xTaskGetTickCount();
    
    // Check whether the virtual button is pressed.
    //
    // If the virtual button has been pressed for 2 or more seconds,
    // set the global flag to 1 and set the prev_tick to be equal
    // to curr_tick (clear the timer). Otherwise clear the global flag.
    //
    // If the virtual button is not pressed, clear the global flag and
    // set the prev_tick to curr_tick.
    if (switch_input() == POWER) { // replace this condition checking with something else
      if (curr_onoff_tick_time - prev_onoff_tick_time >= 2000) {
        // Set the global flag
        onoff_status = 1;
        // Clear the timer
        prev_onoff_tick_time = curr_onoff_tick_time;
      }
      else {
        // Clear the global flag
        onoff_status = 0;
      }
    } else {
      // Clear the global flag
      onoff_status = 0;
      // Clear the timer
      prev_onoff_tick_time = curr_onoff_tick_time;
    }

    vTaskDelay(1000);
  }
}

void Pedestrian(void *p) {
  static int curr_ped_tick_time = 0;
  static int prev_ped_tick_time = 0;
   
  // STEP 4
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual pedestrian button has been pressed
  // for 2 seconds and update the global flag accordingly.
  //
  // (Refer to instructions in the StartStop function to implement
  // this function.)
  while (1) {
    curr_ped_tick_time = xTaskGetTickCount();
    if (switch_input() == PED) { // replace this condition checking with something else
      if (curr_ped_tick_time - prev_ped_tick_time >= 2000) {
        // Set the global flag
        pedestrian_status = 1;
        // Clear the timer
        prev_ped_tick_time = curr_ped_tick_time;
      }
      else {
        // Clear the global flag
        pedestrian_status = 0;
      }
    } else {
      // Clear the global flag
      pedestrian_status = 0;
      // Clear the timer
      prev_ped_tick_time = curr_ped_tick_time;
    }
    vTaskDelay(1000);
  }
}

void Control(void *p) {
  static int curr_light_tick_time = 0;
  static int prev_light_tick_time = 0;

  // STEP 5
  //
  // Complete the implementation of this task function.
  // It represents your Finite State Machine.
  while (1) {
    curr_light_tick_time = xTaskGetTickCount();

    // If the one of the virtual lights been lighting up for 5 or more**
    // seconds, or if any of the virtual button flags has been set, switch
    // to the corresponding next state and reset the light tick**    
    if ((curr_light_tick_time - prev_light_tick_time >= 5000) | onoff_status | pedestrian_status) {
      FSM();
      prev_light_tick_time = curr_light_tick_time;
    }
        
    /*switch(TL_State) {  // State actions
      
      case TL_Init:  // Start
        TL_State = TL_Off;
        break;
        
      case TL_Off:  // All LEDs off
        if (onoff_status == 1) {          
          // Switch to next state
          TL_State = TL_Stop;
          FSM();
        }
        else {
          TL_State = TL_Off;
        }
        break;
    
      case TL_Go:  // Green LED on
        if (curr_light_tick_time - prev_light_tick_time >= 5000) {
          // Switch to next state
          TL_State = TL_Stop;
          // Reset the light tick
          prev_light_tick_time = curr_light_tick_time;
          FSM();
        }
        else if (onoff_status) {  // replace this condition checking with something else
          TL_State = TL_Off;
          // Reset the light tick
          prev_light_tick_time = curr_light_tick_time;
          FSM();
        }
        else if (pedestrian_status) {
          // Switch to next state
          TL_State = TL_Warn;
          // Reset the light tick
          prev_light_tick_time = curr_light_tick_time;
          FSM();
        }
        else {
          TL_State = TL_Go;  // stay
        }
        break;

      case TL_Warn:  // Yellow LED on
        if (curr_light_tick_time - prev_light_tick_time >= 5000) {
          // Switch to next state
          TL_State = TL_Stop;
          // Reset the light tick
          prev_light_tick_time = curr_light_tick_time;
          FSM();
        }
        else if (onoff_status) {  // replace this condition checking with something else
          TL_State = TL_Off;
          // Reset the light tick
          prev_light_tick_time = curr_light_tick_time;
          FSM();
        }
        else {
          TL_State = TL_Warn;  // stay
        }
        break;

      case TL_Stop:  // Red LED on
        if (curr_light_tick_time - prev_light_tick_time >= 5000) {
          // Switch to next state
          TL_State = TL_Go;
          // Reset the light tick
          prev_light_tick_time = curr_light_tick_time;
          FSM();
        }
        else if (onoff_status) {  // replace this condition checking with something else
          TL_State = TL_Off;
          // Reset the light tick
          prev_light_tick_time = curr_light_tick_time;
          FSM();
        }
        else {
          TL_State = TL_Stop;  // stay
        }
        break;
    
      default:
        TL_State = TL_Stop;
        break;    
    }
    */
    vTaskDelay(1000);
  }
}

void FSM(void) {
  // STEP 6
  //
  // Add your FSM implementation here.
  // This function will be called by the control task function.
  
  
  switch(TL_State) {  // State actions
      
      case TL_Init:  // Start
        TL_State = TL_Off;
        break;
        
      case TL_Off:  // All LEDs off
        if (onoff_status == 1) {          
          // Switch to next state
          TL_State = TL_Stop;
        }
        else {
          TL_State = TL_Off;
        }
        break;
    
      case TL_Go:  // Green LED on
        if (onoff_status) {  // replace this condition checking with something else
          TL_State = TL_Off;
        }
        else if (pedestrian_status) {
          // Switch to next state
          TL_State = TL_Warn;
        }
        else {
          TL_State = TL_Stop;  // stop
        }
        break;

      case TL_Warn:  // Yellow LED on
        if (onoff_status) {  // replace this condition checking with something else
          TL_State = TL_Off;
        }
        else {
          TL_State = TL_Stop;  // stop
        }
        break;

      case TL_Stop:  // Red LED on
        if (onoff_status) {  // replace this condition checking with something else
          TL_State = TL_Off;
        }
        else {
          TL_State = TL_Go;  // go
        }
        break;
    
      default:
        TL_State = TL_Stop;
        break;    
    }
  
  
  
  
  switch(TL_State) {  // State actions
    
    case TL_Off:  // All LEDs off
      Light_Off(RED);
      Light_Off(YELLOW);
      Light_Off(GREEN);
      break;
  
    case TL_Go:  // Green LED on
      Light_On(GREEN);
      break;

    case TL_Warn:  // Yellow LED on
      Light_On(YELLOW);
      break;

    case TL_Stop:  // Red LED on
      Light_On(RED);
      break;
  
    default:
      TL_State = TL_Stop;
      break;
  }
}
