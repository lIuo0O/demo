#include <sn8f5702.h>
#include "adc.h"

struct Adc adc;
/***************************************************************************/
void init_adc(void){
    adc.channel = BAT_CHANNEL;
    adc.idle = 1;
    set_adc_state(ADC_ON);
}

void set_adc_state(unsigned char state){
    if(state){
        if(adc.on) return;
        P1M &= P10_P12_P16_ADC_MODE;
        P1CON |= P10_P12_P16_ADC_CTRL;
        VREFH = VREF_3V;
        ADM |= ADC_EN;
        IEN2 |= ADC_IT_EN;
        adc.on = 1;
    }else{
        if(adc.on == 0) return;
        IEN2 &= ADC_IT_DIS;
        ADM &= ADC_DIS;
        P1CON &= P10_P12_P16_GPIO_CTRL;
        P1M |= P10_P12_P16_GPIO_MODE;
        adc.idle = 1;
        adc.on = 0;
    }
}
/*********************************************************************************/
void adc_start_convert(void){
    if(adc.idle == 0) return;
    adc.idle = 0;
    ADR &= ADC_CHANNEL_DIS;
    ADM &= CLEAR_ADC_CHANNEL;
    ADM |= adc.channel;
    ADR |= ADC_CHANNEL_EN;
    ADM |= START_ADC_CONVERT;
}

unsigned int get_adc_it_val(unsigned char channel){
    if(channel == BAT_CHANNEL){
        return adc.it_vol;
    }else if(channel == NTC1_CHANNEL){
        return adc.it_ntc1;
    }else if(channel == NTC2_CHANNEL){
        return adc.it_ntc2;
    }else{
        return 0x0fff;
    }
}

/*********************************************************************************/
void adc_irq(void) interrupt ISRAdc{             // adc
    if((IRCON2 & 0x01) == 0x01){
        IRCON2 &= 0xfe;
        if(adc.channel == BAT_CHANNEL){
            adc.it_vol = (ADB<<4) + (ADR & 0x0f);
            adc.channel = NTC1_CHANNEL;
        }else if(adc.channel == NTC1_CHANNEL){
            adc.it_ntc1 = (ADB<<4) + (ADR & 0x0f);
            adc.channel = NTC2_CHANNEL;
        }else if(adc.channel == NTC2_CHANNEL){
            adc.it_ntc2 = (ADB<<4) + (ADR & 0x0f);
            adc.channel = BAT_CHANNEL;
        }else{
            adc.channel = BAT_CHANNEL;
        }
        ADM &= CLEAR_ADC_ITF;
        adc.idle = 1;
    }
}

