/**
 *  @brief API Prototypes and Macros
 *  @file sci_api.h
 *
 *  These macros define the various codes used in the API, along with
 *  defining the expected control paramater structure.
 *
 *  @date 8 Dec 2016
 *  @author Eric Silk
 */


#include "F28x_Project.h"

#ifndef SCI_API_H_
#define SCI_API_H_

/**
 * @brief Parameter structure
 *  Contains all relevant parameters for Flywheel operation. Currently there should be
 *  two instances of this structure: operating point and set point. You should limit
 *  your code to only ever update the set point when commanded to by the GUI. The
 *  operating point should update whenever you have new information about flywheel
 *  operation.
 *
 *  The set point will assume all values except velocity are to be maximum values --
 *  velocity is assumed to be the desired velocity. If it is desired to allow for a max
 *  and a target value, this structure and all related functions will need to be updated.
 */
struct params {
	float vel;
	float accel;
	float jerk;
	float l_disp_x;
	float l_disp_y;
	float u_disp_x;
	float u_disp_y;
};

/**
 * @defgroup e_macros E-Stop Macros
 * @brief E-STOP LIMITS
 * 	Sets the safe decel/jerk values for an emergency stop. Must be determined at compile
 * 	time. More secure but less flexible this way.
 * 	\addtogroup e_macros
 * 	@{
 */
#define SAFE_DECEL 10; //dummy values, adjust later
#define SAFE_JERK  1;
/** @} */


// Function prototype to init op and setpoint param structs -- sets all elements to 0
extern void init_params( struct params *values);


/*!
 *  @defgroup cmd_macros Command Macros
 *  @brief COMMAND MACROS
 *
 *  Bulk packets will always be sent in the order of the definiton of the macros
 *  E.g. |SEND_BULK|VEL|ACCEL|JERK|L_DISP_X|L_DISP_Y|U_DISP_X|U_DISP_Y|
 *
 *  All packets must be 6 bytes in length. Where data is not needed, stuff with
 *  dummy bytes.
 *
 *  See the related API documentation for further information.
 *  \addtogroup cmd_macros
 *  @{
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
//@}

// FUNCTIONS

void extract_cmd(char extracted[4]);
int parse_cmd(char extracted[4], struct params *op_point);
int e_stop(struct params *set_point);

int send_value(char IDM, float val, char CDM);

int broadcast(int enable, struct params values);
int broadcast_ctrl(int enable);

int send_error(Uint16 error);

float assemble(char data[6]);

#endif /* SCI_API_H_ */
