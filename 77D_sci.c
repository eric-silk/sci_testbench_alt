/** Serial Communications functions.
 *  77D_sci.c
 *
 *  This file contains the functions that act as an interface between the
 *  API and the hardware, as well as the initialization of the hardware.
 *
 *  Created on: Apr 27, 2016
 *      Author: Eric
 *
 *      Device Specific definitions for SCI communications.
 *
 */

#include "F28x_Project.h"     // Device Headerfile and Examples Include File


/** Initializes the SCI and FIFO's
 *
 * Current version is the "verbose" initialization that should help alleviate the burden of reading
 * some technical documentation to get this to run.
 *
 * You should still read the relevant sections of the technical reference manual.
 *
 * No, seriously -- its important. 99% of questions can be answered in it or the errata.
 *
 * In the event that the verbose version gives you issues, comment it out and use the currently
 * commented init sequence, it is more tested and should work.
 *
 * The choice between a 3.125M and 9600 baud is set in the header file. Comment out the HIGH_BAUD
 * declaration to switch to 9600 baud, or set your own custom baud rate by setting the appropriate
 * registers as per the technical reference manual.
 */
void scia_fifo_init()
{
	// Communcations control register
	SciaRegs.SCICCR.bit.SCICHAR = 0x7; //set transmission characters to 8 (n+1)
	SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0x0; //disable multiprocessor mode
	SciaRegs.SCICCR.bit.LOOPBKENA = 0x0; //disable loopback testing mode
	SciaRegs.SCICCR.bit.PARITY = 0x0; //set parity to odd (but will be disabled later)
	SciaRegs.SCICCR.bit.PARITYENA = 0x0; //disable parity
	SciaRegs.SCICCR.bit.STOPBITS = 0x0; //set number of stop bits to 1 (n+1);

	// Control Register 1
	SciaRegs.SCICTL1.bit.RXENA = 0x1; //enable reception
	SciaRegs.SCICTL1.bit.TXENA = 0x1; //enable transmission
	SciaRegs.SCICTL1.bit.SLEEP = 0x0; //disable sleep mode
	SciaRegs.SCICTL1.bit.SWRESET = 0x0; //put SCI software into reset (active low, ctrl regs unaffected)
	SciaRegs.SCICTL1.bit.RXERRINTENA = 0x0; //disable RX error interrupts

	// Control Register 2
	SciaRegs.SCICTL2.bit.TXINTENA = 0x0; //disable tx interrupt, use polling
	SciaRegs.SCICTL2.bit.RXBKINTENA = 0x1; //enable RX interrupt

	// Baud registers
	#ifdef HIGH_BAUD
	SciaRegs.SCIHBAUD.all = 0x0000; //set tech ref manual for details
	SciaRegs.SCILBAUD.all = 0x0000;
	#else
	SciaRegs.SCIHBAUD.all = 0x0002;
	SciaRegs.SCILBAUD.all = 0x008B;
	#endif

	// FIFO control register
	SciaRegs.SCIFFCT.bit.FFTXDLY = 0x0; //set delay between data frames to 0 (of a maximum of 256)

	// FIFO Transmit Register
	SciaRegs.SCIFFTX.bit.TXFIFORESET = 0x0; //hold TX FIFO in reset
	SciaRegs.SCIFFTX.bit.TXFFIENA = 0x0; //disable TX FIFO interrupt (use polling)
	SciaRegs.SCIFFTX.bit.TXFFIL = 0x0; //set FIFO interrupt level to 0 (when empty), disabled by above line
	SciaRegs.SCIFFTX.bit.SCIFFENA = 1; //Enhancement enable
	SciaRegs.SCIFFTX.bit.TXFIFORESET = 0x1; //remove TX FIFO from reset

	// FIFO Receive Register
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0x0; //hold RX FIFO in reset
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 0x1; //clear overflow flag
	SciaRegs.SCIFFRX.bit.RXFFIENA = 0x1; //enable RX FIFO interrupt
	SciaRegs.SCIFFRX.bit.RXFFINTCLR = 0x1; //clear RX FIFO interrupt flag (requires a 1 to reset)
	SciaRegs.SCIFFRX.bit.RXFFIL = 0x6; //set threshold to 6 bytes -- 1 for initate transfer byte, 4 for the float value, and 1 for the confirm byte
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0x1; //release RX FIFO from reset

	// Priority Control (used for emulation/breakpoint behavior)
	SciaRegs.SCIPRI.bit.FREESOFT = 0x0; //breakpoint control

	//Pull SCIA out of Reset
	SciaRegs.SCICTL1.bit.SWRESET = 0x1; 	//pull SCI software out of reset

	/*
	SciaRegs.SCICCR.all =0x0007;    		// 1 stop bit,  No loopback
											// No parity,8 char bits,
											// async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;   		// enable TX, RX, internal SCICLK,
											// Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL1.bit.RXERRINTENA = 1; 	// Enable RX interrupts
	SciaRegs.SCICTL2.bit.TXINTENA =1; 		//SCITXBUF interrupt enable
	SciaRegs.SCICTL2.bit.RXBKINTENA =1; 	//Receiver-buffer/break interrupt enable
	SciaRegs.SCIHBAUD.all = 0x0002;
	SciaRegs.SCILBAUD.all = 0x008B;
	SciaRegs.SCICCR.bit.LOOPBKENA = 0; 		// disable loop back
	SciaRegs.SCIFFTX.all=0xC022; 			//enable+rst fifo, sets TX FIFO interrupt level to 2, enables TX interrupt
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0; 	//rst fifo
	SciaRegs.SCIFFRX.all=0x0021; 			//set RX FIFO interrupt level to 1, enables RX interrupt
	SciaRegs.SCIFFRX.bit.RXFFIL = 6;
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 1; 	//release from rst
	SciaRegs.SCIFFCT.all=0x00;

	SciaRegs.SCICTL1.all =0x0023;     		// Relinquish SCI from Reset
	SciaRegs.SCICTL2.bit.TXINTENA =0;
	SciaRegs.SCIFFTX.bit.TXFFIENA = 0x0; 	//disable TX FIFO interrupt (use polling)
	SciaRegs.SCIFFTX.bit.TXFIFORESET=1;
	SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
	//*/
}



/** Transmit a character from the SCI
 *
 *  Currently waits for the TX FIFO to be empty to ensure no clobbering occurs.
 *  Remove the while() loop if calling from an interrupt and/or to improve
 *  throughput if needed (or at least check that the FIFO isn't full).
 */
void scia_xmit_char(char a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0);
    SciaRegs.SCITXBUF.bit.TXDT = a;
}
/** Split and transmit a float over 4 bytes
 *  The FIFO's only accept 8 bit values. To send floats, they must be accessed
 *  8 bits at a time. A possible improvement would be to use bitfields.
 *
 *  Please also note that C2000 processors have a minimum data size of 2 bytes.
 *  Even char's are 16 bits. This can cause undesirable behavior if not accounted
 *  for.
 */
void scia_xmit_float(float a)
{
	int i = 0;
	union {
		float b;
		Uint16 bytes[2];
	} temp;

	temp.b = a;

	while (SciaRegs.SCIFFTX.bit.TXFFST != 0); //block until space
	for(; i<2; i++)
	{
		//Workaround for C2000 not supporting 8 bit types
		SciaRegs.SCITXBUF.all = (temp.bytes[i] & 0xFF);
		SciaRegs.SCITXBUF.all = ((temp.bytes[i] & 0xFF00) >> 8);

	}
}

/** Transmit a string from the SCI
 *
 *  Accepts the pointer to a C-string (fyi don't Google that without safe search).
 *  Transmits the entire string, expects a terminating NULL character. Currently
 *  slow and blocking, could be improved using an interrupt structure and a software
 *  FSM.
 */
void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit_char(msg[i]);
        i++;
    }
}
