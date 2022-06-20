//////////////////////////////////////////////////////////////////////////
// Include and defines
//////////////////////////////////////////////////////////////////////////
#include "adc.h"

void adc_init(void)
{	
	PORT->Group[0].PINCFG[11].bit.PMUXEN = 1; // for pa11 peripheral is enabled.
	PORT->Group[0].PMUX[5].bit.PMUXO = 0x1; // for adc peripheral
	
	PORT->Group[0].PINCFG[4].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[2].bit.PMUXE = 0x1;
	
	ADC->CTRLA.bit.SWRST = 1; // FIRTLY IT HAS BEEN RESETED.	
	
	uint32_t bias = (*((uint32_t *) ADC_FUSES_BIASCAL_ADDR) & ADC_FUSES_BIASCAL_Msk) >> ADC_FUSES_BIASCAL_Pos;
	uint32_t linearity = (*((uint32_t *) ADC_FUSES_LINEARITY_0_ADDR) & ADC_FUSES_LINEARITY_0_Msk) >> ADC_FUSES_LINEARITY_0_Pos;
	linearity |= ((*((uint32_t *) ADC_FUSES_LINEARITY_1_ADDR) & ADC_FUSES_LINEARITY_1_Msk) >> ADC_FUSES_LINEARITY_1_Pos) << 5;
	/* Wait for bus synchronization. */
	while (ADC->STATUS.bit.SYNCBUSY) {};
	/* Write the calibration data. */
	ADC->CALIB.reg = ADC_CALIB_BIAS_CAL(bias) | ADC_CALIB_LINEARITY_CAL(linearity);
    
	ADC->REFCTRL.bit.REFCOMP = 1; //Reference Buffer Offset Compensation Enable
	ADC->REFCTRL.bit.REFSEL = 0x4; // ext Vrefb pa04 == 0x4; 0x0 for in1volt
	
	ADC->INPUTCTRL.bit.MUXNEG = 0x18; // ?Negative Mux Input Selection
	ADC->INPUTCTRL.bit.MUXPOS = 0X13; // for pa11, temp = 0x18, pa11 for 0x13
	
	
	ADC->CTRLB.bit.PRESCALER = 0x01; // Peripheral clock divided by 8
	ADC->CTRLB.bit.LEFTADJ = 0; // right adjust
	ADC->CTRLB.bit.RESSEL = 0x1;//Resolution can be changed by writing (0x1 == For averaging mode output) 
								//the Resolution bit group in the Control B register (CTRLB.RESSEL)							
	ADC->CTRLB.bit.DIFFMODE = 0; // The ADC is running in singled-ended mode.
	ADC->CTRLB.bit.FREERUN = 1; //The ADC is in free running mode and a new conversion will be initiated 
	                            // when a previous conversion completes.
								
	ADC->AVGCTRL.bit.SAMPLENUM = 0x8; // These bits define how many samples should be added together (for 16 samples == 0x4,)
									  // The result will be available in the Result register (RESULT).								  
	ADC->AVGCTRL.bit.ADJRES = 0x0; // (this value gained by the table Table 33-3 for 16 sampled)an additional right shift that must be specified by writing to the Adjusting 
								  // Result/Division Coefficient field in AVGCTRL (AVGCTRL.ADJRES). 0x4 for 16 samp
								
	ADC->CTRLA.bit.ENABLE = 1; // When GCLK_ADC is enabled, the ADC can be enabled by writing a one to 
							  // the Enable bit in the Control Register A (CTRLA.ENABLE).
							
		
	
}

int32_t adc_readchannel()
{


	// wait for analog conversion to complete
	while (ADC->INTFLAG.bit.RESRDY == 0) {} //This flag is cleared by writing a one to the flag or by reading the RESULT
		                                    // register. This flag is set when the conversion result is available,
	                                        
	// return the result of the ADC
	return ADC->RESULT.reg;
}