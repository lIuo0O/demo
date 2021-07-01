#ifndef __ADC_H
#define __ADC_H

/***************************************************************************/
/***************************************************************************/
#define          ADC_OFF                      0x00
#define          ADC_ON                       0x01

#define          ADC_LEN                      0x0c
#define          MIN_COUNT                    0x02
#define          BAT_CHANNEL                  0x02
#define          NTC1_CHANNEL                 0x00
#define          NTC2_CHANNEL                 0x06
#define          P10_P12_P16_ADC_MODE         0xba
#define          P10_P12_P16_ADC_CTRL         0x45
#define          VREF_3V                      0x01
#define          ADC_IT_EN                    0x02
#define          ADC_EN                       0x80
#define          ADC_IT_DIS                   0xfd
#define          ADC_DIS                      0x7f
#define          ADC_CHANNEL_DIS              0xbf
#define          CLEAR_ADC_CHANNEL            0xf0
#define          ADC_CHANNEL_EN               0x40
#define          START_ADC_CONVERT            0x40
#define          P10_P12_P16_GPIO_CTRL        0x00
#define          P10_P12_P16_GPIO_MODE        0x45
#define          CLEAR_ADC_ITF                0xdf


#define          NTCV_START                   0x01
#define          NTCV_STOP                    0xfe
/***************************************************************************/
struct Adc{
    unsigned int  it_vol;
    unsigned int  it_ntc1;
    unsigned int  it_ntc2;
    unsigned char channel;
    unsigned char on:1;
    unsigned char idle:1;
};
/***************************************************************************/
void init_adc(void);
void set_adc_state(unsigned char state);
void adc_start_convert(void);
unsigned int get_adc_it_val(unsigned char channel);
#endif
