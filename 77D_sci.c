/*
 * 77D_sci.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Eric
 *
 *      Device Specific definitions for SCI communications.
 *
 */

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

void scia_fifo_init()
{

	SciaRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
									// No parity,8 char bits,
	                                // async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
								    // Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL1.bit.RXERRINTENA = 1; // Enable RX interrupts
	SciaRegs.SCICTL2.bit.TXINTENA =1; //SCITXBUF interrupt enable
	SciaRegs.SCICTL2.bit.RXBKINTENA =1; //Receiver-buffer/break interrupt enable
	SciaRegs.SCIHBAUD.all = 0x0000;
	SciaRegs.SCILBAUD.all = 0x0000;
	SciaRegs.SCICCR.bit.LOOPBKENA = 0; // disable loop back
	SciaRegs.SCIFFTX.all=0xC022; //enable+rst fifo, sets TX FIFO interrupt level to 2, enables TX interrupt
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0; //rst fifo
	SciaRegs.SCIFFRX.all=0x0021; //set RX FIFO interrupt level to 1, enables RX interrupt
	SciaRegs.SCIFFRX.bit.RXFFIL = 4;
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 1; //release from rst
	SciaRegs.SCIFFCT.all=0x00;

	SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
	SciaRegs.SCICTL2.bit.TXINTENA =0;
	SciaRegs.SCIFFTX.bit.TXFFIENA = 0x0; //disable TX FIFO interrupt (use polling)
	SciaRegs.SCIFFTX.bit.TXFIFORESET=1;
	SciaRegs.SCIFFRX.bit.RXFIFORESET=1;

	/*
	SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
								  // No parity,8 char bits,
								  // async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
								  // Disable RX ERR, SLEEP, TXWAKE

	SciaRegs.SCICTL2.bit.RXBKINTENA =1;
	SciaRegs.SCIHBAUD.all = 0x0002;
	SciaRegs.SCILBAUD.all = 0x008B;
	//SciaRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back
	SciaRegs.SCIFFTX.all=0xC022;
	SciaRegs.SCIFFRX.all=0x0022;
	SciaRegs.SCIFFCT.all=0x00;

	SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
	SciaRegs.SCICTL2.bit.TXINTENA =0;
	SciaRegs.SCIFFTX.bit.TXFFIENA = 0x0; //disable TX FIFO interrupt (use polling)
	SciaRegs.SCIFFTX.bit.TXFIFORESET=1;
	SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
	*/

	/*
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
	SciaRegs.SCICTL1.bit.SWRESET = 0x1; //pull SCI software out of reset
	SciaRegs.SCICTL1.bit.RXERRINTENA = 0x0; //disable RX error interrupts

	// Control Register 2
	SciaRegs.SCICTL2.bit.TXINTENA = 0x0; //disable tx interrupt, use polling
	SciaRegs.SCICTL2.bit.RXBKINTENA = 0x1; //enable RX interrupt

	// Baud registers
	SciaRegs.SCIHBAUD.all = 0x0000; //set tech ref manual for details
	SciaRegs.SCILBAUD.all = 0x0000;

	// FIFO control register
	SciaRegs.SCIFFCT.bit.FFTXDLY = 0x0; //set delay between data frames to 0 (of a maximum of 256)

	// FIFO Transmit Register
	SciaRegs.SCIFFTX.bit.TXFIFORESET = 0x0; //hold TX FIFO in reset
	SciaRegs.SCIFFTX.bit.TXFFIENA = 0x0; //disable TX FIFO interrupt (use polling)
	SciaRegs.SCIFFTX.bit.TXFFIL = 0x0; //set FIFO interrupt level to 0 (when empty), disabled by above line
	SciaRegs.SCIFFTX.bit.TXFIFORESET = 0x1; //remove TX FIFO from reset

	// FIFO Receive Register
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0x0; //hold RX FIFO in reset
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 0x1; //clear overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINT = 0x1; //enable RX FIFO interrupt
	SciaRegs.SCIFFRX.bit.RXFFINTCLR = 0x1; //clear RX FIFO interrupt flag
	SciaRegs.SCIFFRX.bit.RXFFIL = 0x6; //set threshold to 6 bytes -- 1 for initate transfer byte, 4 for the float value, and 1 for the confirm byte
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0x1; //release RX FIFO from reset

	// Priority Control (used for emulation/breakpoint behavior)
	SciaRegs.SCIPRI.bit.FREESOFT = 0x1; //complete current RX/TX before halting
	*/
}



// Transmit a character/int from the SCI
void scia_xmit_char(char a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    //sends upper and then lower 8 bits
    //SciaRegs.SCITXBUF.all = (a & 0xFF00);
    SciaRegs.SCITXBUF.all = a;
}
//split and transmit a float over 4 bytes
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

// Transmit a string from the SCI
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
