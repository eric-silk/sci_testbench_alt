/**
 *  @brief Serial Communications function prototypes and macros.
 *  @file 77D_sci.h
 *
 *  This file contains the prototypes used in the serial communications,
 *  as well as a configuration option that could be expanded upon.
 *
 *  @date Dec 8 2016
 *  @author Eric Silk
 *
 *      Device Specific definitions for SCI communications.
 *
 */

//#ifndef 77D_SCI_H_
//#define 77D_SCI_H_

/**
 *  @brief Select one of two baud rates
 *
 *  HIGH_BAUD, if defined, will set the baud rate to 3.125M. Otherwise it
 *  will be set to 9600. If you need to regularly update this, consider
 *  adding multiple macros to set the baud rate here, and then initialize
 *  the FIFO's accordingly.
 *
 *  Alternatively, implement an autobaud sequence -- I belive this will limit
 *  the maximum baud rate to 500k. Probably not needed.
 */
#define HIGH_BAUD

#ifndef HIGH_BAUD
	#define LOW_BAUD
#endif

void scia_fifo_init();
void scia_xmit_char(char a);
void scia_xmit_float(float a);
void scia_msg(char * msg);

//#endif /* 77D_SCI_H_ */

