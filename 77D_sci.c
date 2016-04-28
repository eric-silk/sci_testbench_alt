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
   SciaRegs.SCIHBAUD.all = 0x0002;
   SciaRegs.SCILBAUD.all = 0x008B;
   SciaRegs.SCICCR.bit.LOOPBKENA = 0; // disable loop back
   SciaRegs.SCIFFTX.all=0xC022; //enable+rst fifo, sets TX FIFO interrupt level to 2, enables TX interrupt
   SciaRegs.SCIFFRX.all=0x0021; //set RX FIFO interrupt level to 1, enables RX interrupt
   SciaRegs.SCIFFCT.all=0x00;

   SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   SciaRegs.SCIFFTX.bit.TXFIFORESET=1;
   SciaRegs.SCIFFRX.bit.RXFIFORESET=1;

}



// Transmit a character from the SCI
void scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciaRegs.SCITXBUF.all =a;
}
// Transmit a string from the SCI
void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}
