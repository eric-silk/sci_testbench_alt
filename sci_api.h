/*
 * spi.api.h
 *
 *  Created on: Apr 12, 2016
 *      Author: Eric
 */

#ifndef SCI_API_H_
#define SCI_API_H_

/********************************* COMMAND MACROS *********************************/

#define EMERGENCY 			0xFFFF // emergency stop

#define NULL_CMD 			0x0000 // NULL command

/******* GET commands ********/
// Poll the MCU for the values. Not a part of regular broadcasts
// Velocity, acceleration, jerk
#define GET_VELOCITY		0x1000 // send current velocity
#define GET_ACCEL			0x1001 // send current acceleration
#define GET_JERK			0x1002 // send current jerk

// Displacements
#define GET_U_DSIP_X		0x1003 // send current upper x displacement
#define GET_U_DISP_Y		0x1004 // send current upper y displacement
#define GET_L_DSIP_X		0x1005 // send current lower x displacement
#define GET_L_DISP_Y		0x1006 // send current lower y displacement

/******* SET commands ********/
// Velocity, acceleration, jerk
#define SET_VELOCITY 		0x2000 // Define velocity setpoint
#define SET_ACCEL 			0x2001 // Define acceleration
#define SET_JERK			0x2002 // Define max change in acceleration

// Displacements
#define SET_L_DISP_X		0x2003 // Set desired lower X displacement
#define SET_L_DISP_Y		0x2004 // Set desired lower Y displacement
#define SET_U_DISP_X		0x2005 // Set desired upper X displacement
#define SET_U_DISP_Y		0x2006 // Set desired upper Y displacement

// Broadcasting controls
#define EN_BROADCASTS		0x20A0 //enable regular broadcasts
#define DIS_BROADCASTS		0x20A1 //disable regular broadcasts

/******* Send commands ********/
// These are sent in tandem with the associated values during broadcast rather than
// in response to a "get" command.

// Velocity, acceleration, jerk
#define SEND_VELOCITY		0x3000 // broadcast Velocity
#define SEND_ACCEL			0x3001 // broadcast Acceleration
#define SEND_JERK			0x3002 // broadcast Jerk

// Displacements
#define SEND_L_DISP_X		0x3003 // broadcast lower X displacement
#define SEND_L_DISP_Y		0x3004 // broadcast lower Y displacement
#define SEND_U_DISP_X		0x3005 // broadcast upper X displacement
#define SEND_U_DISP_Y		0x3006 // broadcast upper Y displacement

/************ ERRORS ***********/
#define ERROR_SEND			0x4000 // unable to send
#define ERROR_RCV			0x4001 // unable to rcv
#define ERROR_DIS			0x4002 // unable to disable broadcasts
#define ERROR_EN			0x4003 // unable to enable broadcasts
#define ERROR_FIFO_FULL		0x4004 // FIFO FULL
#define ERROR_INVALID_CMD	0x4005 // unable to parse CMD sent


/************************************ FUNCTIONS ***********************************/

int parse_cmd(cmd, val);
int e_stop();

int send_value(cmd, val);

// Function prototypes to set values
int set_vel(Uint16 vel);
int set_accel(Uint16 accel);
int set_jerk(Uint16 jerk);

int set_l_disp_x(int disp);
int set_l_disp_y(int disp);
int set_u_disp_x(int disp);
int set_l_disp_y(int disp);

// Function prototypes to get values
int get_vel();
int get_accel();
int get_jerk();

int get_l_disp_x();
int get_l_disp_y();
int get_u_disp_x();
int get_l_disp_y();

// Function prototypes for broadcast handling
int broadcast();
int broadcast_ctrl(int enable);

// Function prototypes for error sending
int send_error(Uint16 error);

#endif /* SCI_API_H_ */
