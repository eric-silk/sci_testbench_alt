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

void scia_fifo_init()
void scia_xmit(int a);
void scia_msg(char * msg);

#endif /* 77D_SCI_H_ */
