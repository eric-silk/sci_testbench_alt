/*
 * sci_api.c
 *
 *  Created on: Apr 12, 2016
 *      Author: Eric
 */

#include "sci_api.h"
#include "77D_sci.h"


void init_params( struct params *values)
{
	//values->vel = 202084.515625; // "HEY!" when viewed as ASCII, uncomment for PuTTy testing
	//default values below
	values->vel = 0;
	values->accel = 0;
	values->jerk = 0;
	values->l_disp_x = 0;
	values->l_disp_y = 0;
	values->u_disp_x = 0;
	values->u_disp_y = 0;
}

void extract_cmd(char extracted[4])
{
	int i = 0;
	for (;i<4;i++)
	{
//		extracted[i] = SciaRegs.SCIFFRX.bit.SAR & 0x0000;
	}

}

int parse_cmd(char *extracted, struct params *op_point)
{
	//return 1 for success, 0 for failure (e.g. incorrect framing, no valid cmd frame)
	switch(extracted[0])
		{
			case ICM_EMERGENCY_STOP :
				e_stop(op_point);
				break;

			case ICM_SET_VELOCITY :
				if(extracted[3] != CCM_SET_VELOCITY)
				{
					return 0;
				}
				op_point->vel = assemble(extracted);
				break;

			case ICM_SET_ACCELERATION :
				if(extracted[3] != CCM_SET_ACCELERATION)
				{
					return 0;
				}
				op_point->accel = assemble(extracted);

				break;

			case ICM_SET_JERK:
				if(extracted[3] != CCM_SET_JERK)
				{
					return 0;
				}
				op_point->jerk = assemble(extracted);
				break;

			default:
				return 0;

		}
	return 1;
}

int e_stop(struct params *set_point){
	set_point->vel = 0;
	set_point->accel = SAFE_DECEL;
	set_point->jerk = SAFE_JERK;
	return 1; //sucess
}

int send_value(char IDM, float val, char CDM)
{

	scia_xmit_char(IDM);
	scia_xmit_float(val);
	scia_xmit_char(CDM);
	return 1; //if success
}

// Functions for broadcast handling
int broadcast(int enable, struct params *values){
	//Uint16 error;
	// "burst" transmission of all relevant values
	// this may require some handshaking to prevent FIFO overflow

	//code to check broadcast enable
	if(enable){
		while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
		send_value(IDM_SEND_VELOCITY, values->vel, CDM_SEND_VELOCITY);
		while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
		send_value(IDM_SEND_ACCELERATION, values->accel, CDM_SEND_ACCELERATION);
		while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
		send_value(IDM_SEND_JERK, values->jerk, CDM_SEND_JERK);
		while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
		send_value(IDM_SEND_LOWER_DISPLACEMENT_X, values->l_disp_x, CDM_SEND_LOWER_DISPLACEMENT_X);
		while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
		send_value(IDM_SEND_LOWER_DISPLACEMENT_Y, values->l_disp_y, CDM_SEND_LOWER_DISPLACEMENT_Y);
		while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
		send_value(IDM_SEND_UPPER_DISPLACEMENT_X, values->u_disp_x, CDM_SEND_UPPER_DISPLACEMENT_X);
		while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
		send_value(IDM_SEND_UPPER_DISPLACEMENT_Y, values->u_disp_y, CDM_SEND_UPPER_DISPLACEMENT_Y);
		//code to check for error during transmission attempts
		return 1;
	}
	return 0;
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

float assemble(char data[6]) //not the most efficient way of doing it but eh
{
	int i = 0;
	union {
			float value;
			Uint16 bytes[2];
		} temp;

	temp.value = 0; //init to all 0's

	for(;i<2;i++)
	{
		temp.bytes[i] |= data[2*i] & 0xFF;
		temp.bytes[i] |= ((data[2*i+1] & 0xFF) >> 8);
	}

	return temp.value;
}
