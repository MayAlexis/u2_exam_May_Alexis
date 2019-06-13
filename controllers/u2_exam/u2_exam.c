/*
 * File:          robot1.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>

#include <stdio.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define PI 3.141592

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();
 
  wb_keyboard_enable(TIME_STEP);
  int pressed_key;
  
  double linear;

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
   
   WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
   WbDeviceTag wheel_left = wb_robot_get_device("motor_left");
   
   WbDeviceTag dis_sensor = wb_robot_get_device("distance_sensor");
   wb_distance_sensor_enable(dis_sensor, TIME_STEP);
   double ds_value;
   
   WbDeviceTag pos_sensor = wb_robot_get_device("position_sensor1");
   WbDeviceTag pos_sensor2 = wb_robot_get_device("position_sensor2");
   wb_position_sensor_enable(pos_sensor, TIME_STEP);
   wb_position_sensor_enable(pos_sensor2, TIME_STEP);
   double ps_value;
   double ps_value2;
   
   wb_motor_set_position(wheel_right, INFINITY);
   wb_motor_set_position(wheel_left, INFINITY);

  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(TIME_STEP) != -1) {

    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
     
     ds_value = wb_distance_sensor_get_value(dis_sensor);
     printf("distance sensor value = %lf\n", ds_value);
     
     ps_value = wb_position_sensor_get_value(pos_sensor);
     printf("position sensor = %lf\n", ps_value);
     
     pressed_key = wb_keyboard_get_key();

    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_differential_wheels_set_speed(100.0,100.0);
     */
     
     if (pressed_key == WB_KEYBOARD_UP){
       wb_motor_set_velocity(wheel_right, -40);
       wb_motor_set_velocity(wheel_left, -40);
       
       linear = ((2*PI*0.075)/60)*381.6793;
       printf("linear velocity = %lf\n", linear);
       printf("right wheel RPM = %lf\n", 381.6793);
       printf("left wheel RPM = %lf\n", 381.6793);
       
     } else if (pressed_key == WB_KEYBOARD_LEFT){
         wb_motor_set_velocity(wheel_right, -52.3);
         wb_motor_set_velocity(wheel_left, 0);
         
         printf("right wheel RPM = %d\n", 500);
         printf("left wheel RPM = %d\n", 0);
         
     } else if (pressed_key == WB_KEYBOARD_RIGHT){
         wb_motor_set_velocity(wheel_right, 0);
         wb_motor_set_velocity(wheel_left, -52.3);
         
         printf("right wheel RPM = %d\n", 0);
         printf("left wheel RPM = %d\n", 500);
         
     } else if (pressed_key == WB_KEYBOARD_DOWN){
         wb_motor_set_velocity(wheel_right, 1.33);
         wb_motor_set_velocity(wheel_left, 1.33);
         
         linear = ((2*PI*0.075)/60)*12.6908;
         printf("linear velocity = %lf\n", linear);
         printf("right wheel RPM = %lf\n", 12.6908);
         printf("left wheel RPM = %lf\n", 12.6908);
         
     } else {
         wb_motor_set_velocity(wheel_right, 0);
         wb_motor_set_velocity(wheel_left, 0);
         linear = ((2*PI*0.075)/60)*0;
         printf("linear velocity = %lf\n", linear);
         printf("right wheel RPM = %d\n", 0);
         printf("left wheel RPM = %d\n", 0);
     }
       
       
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}


/* rad/s = (rad/s)/2pi = rps x 60 = rpm

   rpm = rpm/60 = rps x 2pi = rad/s */
