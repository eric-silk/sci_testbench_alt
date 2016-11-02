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

// Machine Command Codes
//------------------------------------------------
#define ICM_START                       0b00000001
#define ICM_STOP                        0b00000010
#define ICM_EMERGENCY_STOP              0b00000011
#define ICM_SET_VELOCITY                0b00000100
#define ICM_SET_ACCELERATION            0b00000101
#define ICM_SET_JERK                    0b00000110

#define CCM_START                       0b10000001
#define CCM_STOP                        0b10000010
#define CCM_EMERGENCY_STOP              0b10000011
#define CCM_SET_VELOCITY                0b10000100
#define CCM_SET_ACCELERATION            0b10000101
#define CCM_SET_JERK                    0b10000110

// Controller Command Codes
//------------------------------------------------
#define ICC_ERROR                       0b00100001
#define CCC_ERROR                       0b10100001

// Machine Data Codes
//------------------------------------------------
#define IDM_SEND_VELOCITY               0b01000001
#define IDM_SEND_ACCELERATION           0b01000010
#define IDM_SEND_JERK                   0b01000011
#define IDM_SEND_LOWER_DISPLACEMENT_X   0b01000100
#define IDM_SEND_LOWER_DISPLACEMENT_Y   0b01000101
#define IDM_SEND_UPPER_DISPLACEMENT_X   0b01000110
#define IDM_SEND_UPPER_DISPLACEMENT_Y   0b01000111
#define IDM_SEND_ROTATIONAL_POSITION_X  0b01001000
#define IDM_SEND_ROTATIONAL_POSITION_y  0b01001001

#define CDM_SEND_VELOCITY               0b11000001
#define CDM_SEND_ACCELERATION           0b11000010
#define CDM_SEND_JERK                   0b11000011
#define CDM_SEND_LOWER_DISPLACEMENT_X   0b11000100
#define CDM_SEND_LOWER_DISPLACEMENT_Y   0b11000101
#define CDM_SEND_UPPER_DISPLACEMENT_X   0b11000110
#define CDM_SEND_UPPER_DISPLACEMENT_Y   0b11000111
#define CDM_SEND_ROTATIONAL_POSITION_X  0b11001000
#define CDM_SEND_ROTATIONAL_POSITION_y  0b11001001


/************************************ FUNCTIONS ***********************************/

int extract_cmd(char *cmd, int *index, char *extracted);
//int parse_cmd(char *cmd, Uint16 num_elem, struct params *set_point, struct params *op_point);
int e_stop(struct params *set_point);

int send_value(char IDM, float val, char CDM);

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
int broadcast(int enable, struct params *values);
int broadcast_ctrl(int enable);

// Function prototypes for error sending
int send_error(Uint16 error);

#endif /* SCI_API_H_ */
