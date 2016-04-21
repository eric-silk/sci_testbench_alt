/*
 * sci_api.c
 *
 *  Created on: Apr 12, 2016
 *      Author: Eric
 */
#include "spi_api.h"

int parse_cmd(cmd, val){
	int rslt = 0;
	switch(cmd){

	case EMERGENCY :
		do{
			rslt = e_stop();
		} while(rslt); //repeat until e_stop sucess
		break;

	case SET_VELOCITY:
		set_vel(val);
		break;

	case SET_ACCEL:
		set_accel(val);
		break;

	case SET_JERK:
		set_jerk(val);
		break;

	case SET_L_DISP_X:
		set_l_disp_x(val);
		break;

	case SET_L_DISP_Y:
		set_l_disp_y(val);
		break;

	case SET_U_DISP_X:
		set_u_disp_x(val);
		break;

	case SET_U_DISP_Y:
		set_u_disp_y(val);
		break;

	case GET_VELOCITY:
		get_vel(val);
		break;

	case GET_ACCEL:
		get_accel(val);
		break;

	case GET_JERK:
		get_jerk(val);
		break;

	case GET_L_DISP_X:
		get_l_disp_x(val);
		break;

	case GET_L_DISP_Y:
		get_l_disp_y(val);
		break;

	case GET_U_DISP_X:
		get_u_disp_x(val);
		break;

	case GET_U_DISP_Y:
		get_u_disp_y(val);
		break;

	case EN_BROADCASTS:
		broadcast_ctrl(1);
		break;

	case DIS_BROADCASTS:
		broadcast_ctrl(0);
		break;

	default:
		//send/display "ERROR_INVALID_CMD"
		break;

	} //end switch case
} // end parse_cmd()

int e_stop(){
	// code for emergency conditions
	return 1; //sucess
}

int send_value(cmd, val){
	//code to transmit cmd-val pair
	return 1; //if success
}

// Functions to set values
int set_vel(Uint16 vel){
	// code to set vel
	return 1; //sucess
}

int set_accel(Uint16 accel){
	// code to set accel
	return 1; //sucess
}

int set_jerk(Uint16 jerk){
	// code to set jerk
	return 1; //sucess
}

int set_l_disp_x(int disp){
	// code to set lower x displacement
	return 1; //sucess
}

int set_l_disp_y(int disp){
	// code to set lower y displacement
	return 1; //sucess
}

int set_u_disp_x(int disp){
	// code to set upper x displacement
	return 1; //sucess
}

int set_l_disp_y(int disp){
	// code to set lower y displacement
	return 1; //sucess
}

// Functions to get values
int get_vel(){
	Uint16 vel = 0;
	//code to obtain velocity
	send_value(SEND_VELOCITY, vel);
	return 1; //sucess
}

int get_accel(){
	Uint16 accel = 0;
	//code to obtain accel
	send_value(SEND_ACCEL, accel);
	return 1; //sucess
}

int get_jerk(){
	Uint16 jerk = 0;
	//code to obtain velocity
	send_value(SEND_JERK, jerk);
	return 1; //sucess
}

int get_l_disp_x(){
	Uint16 l_disp_x = 0;
	//code to obtain lower x displacement
	send_value(SEND_L_DISP_X, l_disp_x);
	return 1; //sucess
}

int get_l_disp_y(){
	Uint16 l_disp_y = 0;
	//code to obtain lower y displacement
	send_value(SEND_L_DISP_Y, l_disp_Y);
	return 1; //sucess
}

int get_u_disp_x(){
	Uint16 u_disp_x = 0;
	//code to obtain upper x displacement
	send_value(SEND_U_DISP_X, u_disp_x);
	return 1; //sucess
}

int get_l_disp_y(){
	Uint16 u_disp_y = 0;
	//code to obtain upper y displacement
	send_value(SEND_U_DISP_Y, u_disp_y);
	return 1; //sucess
}

// Functions for broadcast handling
int broadcast(){
	Uint16 enable, error;
	// "burst" transmission of all relevant values
	// this may require some handshaking to prevent FIFO overflow

	//code to check broadcast enable

	if(enable){
		get_vel();
		get_accel();
		get_jerk();
		get_l_disp_x();
		get_l_disp_y();
		get_u_disp_x();
		get_l_disp_y();
		//code to check for error during transmission attempts
		if(error){
			return 0; //failure
		}
		else{
			return 1; //broadcast success
		}
	}
	else{
		return 2; //broadcast disabled
	}
}
int broadcast_ctrl(int enable){
	// code to set an enable value
}

// Functions for error sending
int send_error(Uint16 error){
	//code to xmit an error code
}
