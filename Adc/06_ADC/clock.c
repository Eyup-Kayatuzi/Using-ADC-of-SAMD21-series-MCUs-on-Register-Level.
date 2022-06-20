//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "clock.h"


void ClocksInit(void)
{
	
	PM->APBCMASK.reg |= PM_APBCMASK_ADC; // bunu nereye koyarsan koy. Farketmez...
	
	SYSCTRL->OSC8M.bit.PRESC = 0x00;  // divide by 1 
	SYSCTRL->OSC8M.bit.ENABLE = 1;
	
	
	GCLK->GENDIV.reg = 0x00000000; //*
	
	GCLK->GENCTRL.bit.SRC = 0x06; //* for OSC8M
	GCLK->GENCTRL.bit.DIVSEL = 0; //*
	GCLK->GENCTRL.bit.ID = 0x0; // * The Generic Clock Generator will be selected as the source of the generic clock by the ID bit group
	//GCLK->GENCTRL.bit.RUNSTDBY = 0;
	//GCLK ->GENCTRL.bit.OE = 1;
	GCLK->GENCTRL.bit.GENEN = 1; //*
	
	//////////////////////////
	
	GCLK->CLKCTRL.bit.ID = 0x1E; //* for adc peripheral 
	GCLK->CLKCTRL.bit.GEN = 0x0; //*
	GCLK->CLKCTRL.bit.CLKEN = 1; //* 
	
} 