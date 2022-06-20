//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "clock.h"

#define F_CPU 48000000UL
#include "delay.h"

#include "adc.h"

void AppInit(void)
{
	ClocksInit();
	
	// Assign LED0 as OUTPUT
	REG_PORT_DIR0 = LED0_PIN_MASK;
	
	// Set LED0 OFF
	REG_PORT_OUTCLR0 = LED0_PIN_MASK;
	

} // AppInit()

void AppRun(void)
{
	// variable to store result of ADC conversion
	int result;
	
	// initialize the ADC
	//adc_init();
	
	while(1)
	{
		// read the ADC channel 19 (PA11)
		result =  adc_readchannel();
		//result = (result & 0xfff0) >> 4;
		// if result under threshold keep LED off
		if (result < 4000)
		{
			
	      // Set LED0 OFF
	      REG_PORT_OUTCLR0 = LED0_PIN_MASK;
		}
		
		// if result is over threshold turn LED on
		else if (result > 4000)
		{
			// Set LED0 ON
			REG_PORT_OUTSET0 = LED0_PIN_MASK;
		}
		
        // small delay
		delay_ms(100);
	}

} // Apprun()

