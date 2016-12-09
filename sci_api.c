/**
 *  @brief API Function Calls.
 *  @file sci_api.c
 *
 *  These functions implement the desired reception, transmission, encoding, and
 *  decoding of packets described in the Flywheel API.
 *
 *  @date 8 Dec 2016
 *  @author Eric Silk
 */

#include "sci_api.h"
#include "77D_sci.h"

/**
 * @brief Accepts a pointer to a params struct and sets all values to 0.
 * Change as needed to set to the desired default values. 0 seemed like a safe bet.
 */


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

/**
 * @brief Not currently in use.
 *  Was meant to extract the data from a packet, see assemble() for current solution.
 */
void extract_cmd(char extracted[4])
{
	int i = 0;
	for (;i<4;i++)
	{
//		extracted[i] = SciaRegs.SCIFFRX.bit.SAR & 0x0000;
	}

}

/**
 *  @brief Parses packet and updates operating point.
 *  Pass a pointer to the current command packet and a pointer to the set point struct.
 *  Uses assemble() to extract the data and assign it to the relevant value.
 */
int parse_cmd(char *extracted, struct params *set_point)
{
	//return 1 for success, 0 for failure (e.g. incorrect framing, no valid cmd frame)
	switch(extracted[0])
		{
			case ICM_EMERGENCY_STOP :
				e_stop(set_point);
				break;

			case ICM_SET_VELOCITY :
				if(extracted[5] != CCM_SET_VELOCITY)
				{
					return 0;
				}
				set_point->vel = assemble(extracted);
				break;

			case ICM_SET_ACCELERATION :
				if(extracted[5] != CCM_SET_ACCELERATION)
				{
					return 0;
				}
				set_point->accel = assemble(extracted);

				break;

			case ICM_SET_JERK:
				if(extracted[5] != CCM_SET_JERK)
				{
					return 0;
				}
				set_point->jerk = assemble(extracted);
				break;

			default:
				return 0;

		}
	return 1;
}

/**
 * @brief Initiate an emergency stop.
 *  Upon receipt of an emergency stop, set the set point velocity to 0 and the acceleration and jerk to their maximum safe value.
 *  These safe values are defined in sci_api.h and must currently be configured at compile time.
 *
 *  The GUI expects an ACK, so it also sends the relevant code up.
 *
 *  Possible improvements would be accepting SAFE_DECEL and SAFE_JERK arguments so that the operator can set those, but
 *  this could lead to undesirable behavior during operation. Additionally, some form of error checking if needed and an
 *  appropriate return value as needed.
 */
int e_stop(struct params *set_point){
	set_point->vel = 0;
	set_point->accel = SAFE_DECEL;
	set_point->jerk = SAFE_JERK;

	send_value(ICM_EMERGENCY_STOP, 0.0, CCM_EMERGENCY_STOP); //send ACK
	return 1; //sucess
}

/**
 * @brief Sends a packet to the GUI
 *  Accepts the IDM, value, and CDM.
 *  In the event the transmission protocol changes (e.g. USB, Ethernet), this will need to be updated.
 *
 *  Possible improvements would be checking the IDM/CDM pair or only accepting one and filling in the other, and enforcing
 *  some form of error checking with an appropriate return value.
 */
int send_value(char IDM, float val, char CDM)
{

	scia_xmit_char(IDM);
	scia_xmit_float(val);
	scia_xmit_char(CDM);
	return 1; //if success
}

/**
 * @brief Broadcasts current operating point information
 *  Currently accepts and enable value that isn't in use and the operating point structure.
 *
 *  Currently very slow. It must wait until the lasat packet is fully transmitted before sending the next, and must
 *  transmit all packets before returning. Consider using the SCIA TX interrupt and developing an ISR for less time
 *  in the function and greater throughput. For instance, set the interrupt to fire anytime there are fewer than 8
 *  elements in the FIFO and stuff the next packet in before returning. Use a software FSM to track the next packet
 *  that needs transmission (preferably using an enumerated type to restrict behavior).
 *
 *  Google it if you don't know what I'm talking about.
 */
int broadcast(int enable, struct params values){
	//Uint16 error;
	// "burst" transmission of all relevant values
	// this may require some handshaking to prevent FIFO overflow

	//code to check broadcast enable
	if(enable){
		while(!SciaRegs.SCICTL2.bit.TXEMPTY);
		send_value(IDM_SEND_VELOCITY, values.vel, CDM_SEND_VELOCITY);
		while(!SciaRegs.SCICTL2.bit.TXEMPTY);
		send_value(IDM_SEND_ACCELERATION, values.accel, CDM_SEND_ACCELERATION);
		while(!SciaRegs.SCICTL2.bit.TXEMPTY);
		send_value(IDM_SEND_JERK, values.jerk, CDM_SEND_JERK);
		while(!SciaRegs.SCICTL2.bit.TXEMPTY);
		send_value(IDM_SEND_LOWER_DISPLACEMENT_X, values.l_disp_x, CDM_SEND_LOWER_DISPLACEMENT_X);
		while(!SciaRegs.SCICTL2.bit.TXEMPTY);
		send_value(IDM_SEND_LOWER_DISPLACEMENT_Y, values.l_disp_y, CDM_SEND_LOWER_DISPLACEMENT_Y);
		while(!SciaRegs.SCICTL2.bit.TXEMPTY);
		send_value(IDM_SEND_UPPER_DISPLACEMENT_X, values.u_disp_x, CDM_SEND_UPPER_DISPLACEMENT_X);
		while(!SciaRegs.SCICTL2.bit.TXEMPTY);
		send_value(IDM_SEND_UPPER_DISPLACEMENT_Y, values.u_disp_y, CDM_SEND_UPPER_DISPLACEMENT_Y);
		//code to check for error during transmission attempts
		return 1;
	}
	return 0;
}

/**
 * @brief Not currently in use.
 *  Was to enable/disable broadcasting of data.
 */
int broadcast_ctrl(int enable){
	// code to set an enable value
	return 1;
}

/**
 * @brief Not currently in use
 *  If an error code is needed, send it here. Should probably just call send_value() with the error code.
 */
int send_error(Uint16 error){
	//code to xmit an error code
	return 1;
}

/**
 * @brief Convert packet to a float
 *  Accepts the 6 element data packet and extracts the 4 data bytes
 *  Assembles those bytes into a float value through the use of a union.
 *  Probably could be improved stylistically through the use of bitfields.
 */
float assemble(char data[6])
{
	union {
			float value;
			Uint16 bytes[2]; //Consider using bitfields here instead.
		} temp;

	temp.value = 0; //init to all 0's

	// Unrolled the loop because its late and I didn't want to mess with array indices.'
	// ...and it's faster(theoretically). That's totally the reason I did it.
	// Definitely not because it was 2am and I wasn't thinking straight.
	temp.bytes[0] |= data[1] & 0xFF;
	temp.bytes[0] |= ((data[2] & 0xFF) << 8);
	temp.bytes[1] |= data[3] & 0xFF;
	temp.bytes[1] |= ((data[4] & 0xFF) << 8);


	return temp.value;
}
