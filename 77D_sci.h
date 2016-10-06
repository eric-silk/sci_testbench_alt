/*
 * 77D_sci.h
 *
 *  Created on: Apr 27, 2016
 *      Author: Eric
 *
 *      Device Specific definitions for SCI communications.
 *
 */

#ifndef 77D_SCI_H_
#define 77D_SCI_H_

//Set to 1 to set baud rate to 3.125Mbps, set to 0 for 9.6kbps
#define HIGH_BAUD	0

void scia_fifo_init()
void scia_xmit_int(int a);
void scia_xmit_float(float a);
void scia_msg(char * msg);


#endif /* 77D_SCI_H_ */
