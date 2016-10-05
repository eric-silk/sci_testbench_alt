/*
 * sci_api.c
 *
 *  Created on: Apr 12, 2016
 *      Author: Eric
 */
#include "sci_api.h"



void init_params( struct params *values)
{
	values->vel = 0;
	values->accel = 0;
	values->jerk = 0;
	values->l_disp_x = 0;
	values->l_disp_y = 0;
	values->u_disp_x = 0;
	values->u_disp_y = 0;
}

int extract_cmd(char *cmd, int *index, char *extracted)
{
	//returns number of elements extracted
	if(cmd[*index] == EMERGENCY)
	{
		extracted[0] = EMERGENCY;
		(*index)++;
		return 1;
	}
	else
	{
		extracted[0] = cmd[*index];
		(*index)++;
		extracted[1] = cmd[*index];
		(*index)++;
		return 2;
	}

}

int parse_cmd(char cmd, Uint16 num_elem, struct params *set_point, struct params *op_point)
{
	int rslt = 0;
	int index = 0;
	char extracted[2];
	while(num_elem > 0){
		num_elem -= extract_cmd( *cmd, *index, *extracted);
		switch(extracted[0])
		{
			case EMERGENCY :
				do{
					rslt = e_stop(*set_point);
				} while(rslt); //repeat until e_stop sucess
				break;

			case SET_VEL:
				set_vel(&set_point->vel);
				break;

			case SET_ACCEL:
				set_accel(&set_point->accel);
				break;

			case SET_JERK:
				set_jerk(&set_point->jerk);
				break;

			case GET_VELOCITY:
				get_vel(op_point->vel);
				break;

			case GET_ACCEL:
				get_accel(op_point->accel);
				break;

			case GET_JERK:
				get_jerk(op_point->jerk);
				break;

			case GET_L_DISP:
				get_l_disp(op_point->l_disp_x, op_point->l_disp_y);
				break;

			case GET_U_DISP:
				get_u_disp(op_point->u_disp_x, op_point->u_disp_y);
				break;

			default:
				//send/display "ERROR_INVALID_CMD"
				break;

		} //end switch case
	} //end While
	return 1;
} // end parse_cmd()

int e_stop(struct params *set_point){
	set_point->vel = 0;
	set_point->accel = SAFE_DECEL;
	set_point->jerk = SAFE_JERK;
	return 1; //sucess
}

int send_value(char cmd, float val1, float val2){ //set val2 to NULL when xmitting one value

	return 1; //if success
}

// Functions to set values
int set_vel(float *vel){
	// code to set vel
	return 1; //sucess
}

int set_accel(float *accel){
	// code to set accel
	return 1; //sucess
}

int set_jerk(float *jerk){
	// code to set jerk
	return 1; //sucess
}

// Functions to get values
int get_vel(float vel){
	//code to obtain velocity
	send_value(SEND_VELOCITY, vel);
	return 1; //sucess
}

int get_accel(float accel){
	send_value(SEND_ACCEL, accel);
	return 1; //sucess
}

int get_jerk(float jerk){
	send_value(SEND_JERK, jerk);
	return 1; //sucess
}

int get_l_disp(float dispx, float dispy){
	send_value(SEND_L_DISP_X, l_disp_x);
	return 1; //sucess
}

int get_l_disp_y(){
	Uint16 l_disp_y = 0;
	//code to obtain lower y displacement
	send_value(SEND_L_DISP_Y, l_disp_y);
	return 1; //sucess
}

int get_u_disp_x(){
	Uint16 u_disp_x = 0;
	//code to obtain upper x displacement
	send_value(SEND_U_DISP_X, u_disp_x);
	return 1; //sucess
}

int get_u_disp_y(){
	Uint16 u_disp_y = 0;
	//code to obtain upper y displacement
	send_value(SEND_U_DISP_Y, u_disp_y);
	return 1; //sucess
}

// Functions for broadcast handling
int broadcast(int enable, struct params *values){
	Uint16 error;
	// "burst" transmission of all relevant values
	// this may require some handshaking to prevent FIFO overflow

	//code to check broadcast enable

	if(enable){

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
	return 1;
}

// Functions for error sending
int send_error(Uint16 error){
	//code to xmit an error code
	return 1;
}
