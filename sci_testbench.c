/*****************************************************************************
 * @File: sci_testbench.c
 * @Author: Eric Silk (silk2390@vandals.uidaho.edu)
 * @date: December 7, 2016
 * MCU: TI Delfino TMS320F28377D
 * @brief Developed for the FlyCAM project in conjunction with the FESS team at
 * the University of Idaho.
 * Used as a testbench for serial communication with a GUI running on a
 * seperate PC. Will ultimately support an API to parse commands from the
 * serial port and adjust operating parameters of the FESS control system, as
 * well as providing consistent updates on system performance (e.g. speed,
 * acceleration, stored energy).
 *
 * Currently tested to be "mostly" working. The communication API seems to be
 * functional and should be fairly user friendly. Please refer all questions
 * to Eric Silk or Ben Bolton.
 *****************************************************************************/

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "77D_sci.h"		  // Device specific SCI functions
#include "sci_api.h"
#include <stdlib.h>

/**
 * @brief Prototype statements for functions found within this file.
 *
 *  Please attempt to modularize your code whenever possible.
 *  When possible/reasonable, move all functions to external files
 *  to improve modularity and readability.
 */
interrupt void sciaTxFifoIsr(void);
interrupt void sciaRxFifoIsr(void);
__interrupt void cpu_timer0_isr(void);
void update_op_point(struct params *op, struct params set);

/**
 * @brief Global variables.
 *
 *  Use only for flags and to pass data to and from ISR's.
 *  You're not Mech E's, don't code like them.
 */
volatile int RXRCV_flag = 0;
volatile int TXRDY_flag = 0;
volatile int broadcast_flag = 0;
volatile char frame[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


void main(void)
{
	struct params set_point;
	struct params op_point;
	int broadcast_enable = 1; //not really used, just in place in the event broadcast enable/disable was implemented.

/**
 * @MCU Initilization.
 *
 *  Boilerplate inits for the 77D. Gets the required clocks and peripherals up and running.
 *  The comments should explain most everything. Look at other examples in ControlSuite
 *  for further reference.
 */

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
	InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
	InitGpio();

// Init the pins for the SCI-A port.
// GPIO_SetupPinMux() - Sets the GPxMUX1/2 and GPyMUX1/2 register bits
// GPIO_SetupPinOptions() - Sets the direction and configuration of the GPIOS
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
	// Assign ISR's, add more if needed
	PieVectTable.SCIA_RX_INT = &sciaRxFifoIsr; //RX FIFO
	PieVectTable.SCIA_TX_INT = &sciaTxFifoIsr; //TX FIFO
	PieVectTable.TIMER0_INT = &cpu_timer0_isr; //Timer interrupt
	EDIS;   // This is needed to disable write to EALLOW protected registers

//Initialize and Configure the timers
	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 200, 1000000); // Initial configuration, tick every second
	CpuTimer0Regs.TCR.all = 0x4000; //write only instruction to set TSS bit = 0

	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	DINT;

// Step 4. Initialize the Device Peripherals:
	scia_fifo_init();  // Init SCI-A

// Step 5. User specific code, enable interrupts:

// Enable interrupts required for this example
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, INT1; corresponds to SCIA_RX
	PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT2; corresponds to SCIA_TX
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;   // Enable TINT0 in the PIE, group 1 interrupt 7
	//IER = 0x101; // Enable CPU INT
	IER |= 0x0101; //enable cpu int1 which is connected to cpu timer 0
	EINT;

// Initialize your operating point and set point structures
	init_params(&set_point);
	init_params(&op_point);

	//scia_msg("\r\nReady to accept values. \r\n");

// Step 6. IDLE loop. Just sit and loop forever (optional):
	for(;;)
	{
		if(broadcast_flag == 1)
		{

			update_op_point(&op_point, set_point);
			broadcast(broadcast_enable, op_point);
			broadcast_flag = 0;
		}
		if(RXRCV_flag == 1)
		{
			parse_cmd(frame, &set_point);
			RXRCV_flag = 0;
		}
	}

}

/**
 * @brief TX FIFO ISR.
 *  Currently unused and disabled. Add desired behavior and enable
 *  if needed.
 *
 *  Be aware that if the interrupt condition is not addressed
 *  during the ISR and the flag is cleared, it will just jump
 *  straight back into this. Consider setting a flag such as
 *  TXRDY_flag and only clearing the flag once the condition
 *  has been taken care of.
 */

interrupt void sciaTxFifoIsr(void)
{
	TXRDY_flag = 1;

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all|=PIEACK_GROUP9;      // Issue PIE ACK
}

/**
 * @brief RX FIFO ISR.
 *  Currently should check for errors (overflow or parity) and
 *  take some action (none implemented here).
 *
 *  Otherwise, pull 6 bytes of data from the FIFO. cnt is used to
 *  check number of times the interrupt occurs for debugging.
 */
interrupt void sciaRxFifoIsr(void)
{
	unsigned int i = 0;
	static unsigned int cnt = 0;


	if(SciaRegs.SCIRXBUF.bit.SCIFFFE || SciaRegs.SCIRXBUF.bit.SCIFFPE)
	{
		//error handling here
		i = 6; //to bypass frame read, put a breakpoint here as well for debugging
	}

	for(; i<6;i++)
	{
		frame[i] = SciaRegs.SCIRXBUF.bit.SAR; //read entire frame
	}
	RXRCV_flag = 1; //set flag to indicate frame ready
	cnt++;

    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=PIEACK_GROUP9;       // Issue PIE ack
}


/**
 * @brief Timer interrupt.
 *  Enables broadcast flag once every second.
 *
 *  Add other functionality as needed.
 */
__interrupt void cpu_timer0_isr(void){
	CpuTimer0.InterruptCount++;

	broadcast_flag = 1;

	// Acknowledge this interrupt to receive more interrupts from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/**
 * @brief Current testbench behavior.
 *  Increments all values by 1 until reaching 1000, then decrements to 0.
 *  No real functionality. Could be updated to set it around the setpoint.
 */

void update_op_point(struct params *op, struct params set)
{
	static Uint16 increment = 1;

	if(increment)
	{
		op->accel += 1;
		op->jerk += 1;
		op->l_disp_x += 1;
		op->l_disp_y += 1;
		op->u_disp_x += 1;
		op->u_disp_y += 1;
		op->vel += 1;
		if(op->vel>=1000)
		{
			increment = 0;
		}
	}
	else
	{
		op->accel -= 1;
		op->jerk -= 1;
		op->l_disp_x -= 1;
		op->l_disp_y -= 1;
		op->u_disp_x -= 1;
		op->u_disp_y -= 1;
		op->vel -= 1;
		if(op->vel<=0)
		{
			increment = 1;
		}
	}


}

//===========================================================================
// No more.
//===========================================================================
