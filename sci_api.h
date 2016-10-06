/*
 * spi.api.h
 *
 *  Created on: Apr 12, 2016
 *      Author: Eric
 */


#include "F28x_Project.h"

#ifndef SCI_API_H_
#define SCI_API_H_

// structure to hold operating params, use for setpoints and current values
struct params {
	float vel;
	float accel;
	float jerk;
	float l_disp_x;
	float l_disp_y;
	float u_disp_x;
	float u_disp_y;
};

/*  E-STOP LIMITS
 * 	Sets the safe decel/jerk values for an emergency stop
 */
#define SAFE_DECEL 10; //dummy values, adjust later
#define SAFE_JERK  1;

// Function prototype to init op and setpoint param structs -- sets all elements to 0
extern void init_params( struct params *values);

// Bulk packets will always be sent in the order of the definiton of the macros
// E.g. |SEND_BULK|VEL|ACCEL|JERK|L_DISP_X|L_DISP_Y|U_DISP_X|U_DISP_Y|

/********************************* COMMAND MACROS *********************************/

/* NOTE!
 * Current API assumes NNN == 001
 * This current instance does NOT support multiple values being sent
 * e.g.: cmd = 0xF9 (SEND_VEL with NNN = 0b111) will not happen
 * 		 cmd = 0x59 (SEND_VEL with NNN = 0b001) can happen
 * Future users can implement this functionality if desired.
 */

#define NULL_CMD 			0x0000 // NULL command

/******* GET commands ********/
// Poll the MCU for the values. Not a part of regular broadcasts
// Velocity, acceleration, jerk
#define GET_VEL				0x01 // send current velocity
#define GET_ACCEL			0x02 // send current acceleration
#define GET_JERK			0x03 // send current jerk

// Displacements
#define GET_L_DISP			0x04 // send current upper x & y displacement
#define GET_U_DISP			0x05 // send current lower x & y displacement
#define GET_ALL				0xE6 // send all values

/******* SET commands ********/
// Velocity, acceleration, jerk
#define SET_VEL				0x59 // Define velocity setpoint
#define SET_ACCEL 			0x2A // Define acceleration
#define SET_JERK			0x2B // Define max change in acceleration
#define SET_VEL_ACCEL		0x2C
#define SET_VEL_JERK		0x2D
#define SET_ACCEL_JERK		0x2E
#define SET_BULK			0x6F // Set all values

/******* SEND commands ********/
// Velocity, acceleration, jerk
#define SEND_VEL			0x59 // Send current velocity
#define SEND_ACCEL 			0x5A // Send current acceleration
#define SEND_JERK			0x5B // Send curent change in acceleration
#define SEND_L_DISP			0x5C // Send current lower displacement
#define SEND_U_DISP			0x5D // Send current upper displacement
#define SEND_BULK			0xFE // Set all values

/************ ERRORS ***********/
#define ERROR_FIFO_FULL		0x15 // FIFO FULL
#define EMERGENCY			0x17 // Emergency condition


/************************************ FUNCTIONS ***********************************/

int extract_cmd(char *cmd, int *index, char *extracted);
int parse_cmd(char *cmd, Uint16 num_elem, struct params *set_point, struct params *op_point);
int e_stop();

int send_value(char cmd, float val1, float val2);

// Function prototypes to set values
int set_vel(float *vel);
int set_accel(float *accel);
int set_jerk(float *jerk);

// Function prototypes to get values
int get_vel(float vel);
int get_accel(float accel);
int get_jerk(float jerk);

int get_l_disp(float x_disp, float y_disp);
int get_u_disp(float x_disp, float y_disp);

// Function prototypes for broadcast handling
int broadcast();
int broadcast_ctrl(int enable);

// Function prototypes for error sending
int send_error(Uint16 error);

#endif /* SCI_API_H_ */
