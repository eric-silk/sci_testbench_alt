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
   SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                  // No parity,8 char bits,
                                  // async mode, idle-line protocol
   SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                  // Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL1.bit.RXERRINTENA = 1; // Enable RX interrupts
   SciaRegs.SCICTL2.bit.TXINTENA =1; //SCITXBUF interrupt enable
   SciaRegs.SCICTL2.bit.RXBKINTENA =1; //Receiver-buffer/break interrupt enable
   /*
    * Baud rate is determined as follows:
    * BRR = (SCIHBAUD << 8) && SCILBAUD
    * Baud = LSPCLK / ((BRR+1)*8)
    * LSPCLK should be 50MHz by default (200MHz/4)
    * If BRR == 0, then Baud = LSPCLK/16 (or 3,125,000 by default)
    */

   //Preprocessor commands to set baud rate. Set Macro in 77D_sci.h
   #ifndef HIGH_BAUD
   SciaRegs.SCIHBAUD.all = 0x0002;
   SciaRegs.SCILBAUD.all = 0x008B;
   #endif /* HIGH_BAUD */

   #ifdef HIGH_BAUD
   SciaRegs.SCIHBAUD.all = 0x0000;
   SciaRegs.SCILBAUD.all = 0x0000;
   #endif /* HIGH_BAUD */
   SciaRegs.SCICCR.bit.LOOPBKENA = 0; // disable loop back
   //SciaRegs.SCIFFTX.all=0xC022; // enable+rst fifo, sets TX FIFO interrupt level to 2, enables TX interrupt
   SciaRegs.SCIFFTX.bit.SCIFFENA = 1; // enable TX FIFO
   SciaRegs.SCIFFTX.bit.TXFFIENA = 0; // don't enable interrupts (just poll)
   SciaRegs.SCIFFRX.all=0x0021; //set RX FIFO interrupt level to 1, enables RX interrupt
   SciaRegs.SCIFFCT.all=0x00;

   SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   //SciaRegs.SCIFFTX.bit.TXFIFORESET=1;
   SciaRegs.SCIFFRX.bit.RXFIFORESET=1;

}



// Transmit a character/int from the SCI
void scia_xmit_int(int a)
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
		Uint16 bytes[4];
	} temp;

	temp.b = a;

	while (SciaRegs.SCIFFTX.bit.TXFFST != 0); //block until space
	for(; i<4; i++)
	{
		SciaRegs.SCITXBUF.all = temp.bytes[i];
	}
}

// Transmit a string from the SCI
void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit_int(msg[i]);
        i++;
    }
}
