/*****************************************************************************
 * File: sci_testbench.c
 * Author: Eric Silk (silk2390@vandals.uidaho.edu)
 * Revision date: April 4th, 2016
 * MCU: TI Delfino TMS320F28377D
 * Developed for the FlyCAM project in conjunction with the FESS team at
 * the University of Idaho.
 * Used as a testbench for serial communication with a GUI running on a
 * seperate PC. Will ultimately support an API to parse commands from the
 * serial port and adjust operating parameters of the FESS control system, as
 * well as providing consistent updates on system performance (e.g. speed,
 * acceleration, stored energy).
 *****************************************************************************/

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "77D_sci.h"		  // Device specific SCI functions

#define CPU_FREQ    60E6
#define LSPCLK_FREQ CPU_FREQ/4
#define SCI_FREQ    100E3
#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

// Prototype statements for functions found within this file.
interrupt void sciaTxFifoIsr(void);
interrupt void sciaRxFifoIsr(void);
__interrupt void cpu_timer0_isr(void);
void scia_fifo_init(void);
void error(void);
void scia_xmit(int a);
void scia_msg(char * msg);

// Global variables
Uint16 ReceivedChar; // Used for checking the received data

int RXRCV_flag = 0;
int TXRDY_flag = 0;

void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   InitGpio();

//  Init the pins for the SCI-A port.
//  GPIO_SetupPinMux() - Sets the GPxMUX1/2 and GPyMUX1/2 register bits
//  GPIO_SetupPinOptions() - Sets the direction and configuration of the GPIOS
// These functions are found in the F2837xD_Gpio.c file.
   GPIO_SetupPinMux(28, GPIO_MUX_CPU1, 1);
   GPIO_SetupPinOptions(28, GPIO_INPUT, GPIO_PUSHPULL);
   GPIO_SetupPinMux(29, GPIO_MUX_CPU1, 1);
   GPIO_SetupPinOptions(29, GPIO_OUTPUT, GPIO_ASYNC);

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.SCIA_RX_INT = &sciaRxFifoIsr;
   PieVectTable.SCIA_TX_INT = &sciaTxFifoIsr;
   PieVectTable.TIMER0_INT = &cpu_timer0_isr;//assign ISR's, add more if needed
   EDIS;   // This is needed to disable write to EALLOW protected registers

//Initialize and Configure the timers
	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 200, 400000); //initial configuration
	CpuTimer0Regs.TCR.all = 0x4000; //write only instruction to set TSS bit = 0

	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	DINT;

// Step 4. Initialize the Device Peripherals:
   scia_fifo_init();  // Init SCI-A

// Step 5. User specific code, enable interrupts:


   //ReceivedChar = sdataA[0];
// Enable interrupts required for this example
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, INT1; corresponds to SCIA_RX
   PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT2; corresponds to SCIA_TX
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;   // Enable TINT0 in the PIE, group 1 interrupt 7
   //IER = 0x101; // Enable CPU INT
   IER |= 0x0101; //enable cpu int1 which is connected to cpu timer 0
   EINT;

// Step 6. IDLE loop. Just sit and loop forever (optional):
   for(;;);

}

interrupt void sciaTxFifoIsr(void)
{
	if(RXRCV_flag == 1){
		scia_msg("You sent: \0");
		scia_xmit(ReceivedChar);
		scia_msg("\r\n\0");
		RXRCV_flag = 0;
	}
	else{
		TXRDY_flag = 1;
	}

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all|=PIEACK_GROUP9;      // Issue PIE ACK
}

interrupt void sciaRxFifoIsr(void)
{
	ReceivedChar = SciaRegs.SCIRXBUF.all;  // Read data
	//ReceivedChar = SciaRegs.SCIRXBUF.all;
	RXRCV_flag = 1;

    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=PIEACK_GROUP9;       // Issue PIE ack
}



__interrupt void cpu_timer0_isr(void){
	CpuTimer0.InterruptCount++;

	static Uint16 count = 0x41; //effectively "A"

	if(TXRDY_flag == 1){
		scia_xmit(count);
		scia_msg("\r\n\0");
		TXRDY_flag = 0;
		if(count >= 0x5A){
			count = 0x41;
		}
		else{
			count++;
		}
	}

	// Acknowledge this interrupt to receive more interrupts from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//===========================================================================
// No more.
//===========================================================================
