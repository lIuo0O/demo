#include  "lora_ptp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"


#define   MSG_Q_NUM       300
#define   TX_MODE            true
#define   RX_MODE            false

bool  current_mode  = TX_MODE;

struct msg_q_t
{
    uint8_t  snr;
    int16_t  rssi;
    uint32_t tcb_len;
    void*    tcb;
};

struct lorapp_dev_t
{
    uint8_t*  prx;
    uint32_t  rx_len;

//    SemaphoreHandle_t  op_mutex;

//    xQueueHandle  msg_q;

    struct msg_q_t* msg_q_num[MSG_Q_NUM];
};

extern void SX1276ReadFifo( uint8_t *buffer, uint8_t size );
extern void SX1276SetRfTxPower( int8_t power );

static void EVENT_TxDoneCallback(void);
static void EVENT_TxTimeoutCallback(void);
static void EVENT_RxDoneCallback( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );
static void EVENT_RxTimeoutCallback(void);
static void EVENT_RxErrorCallback(void);
static void EVENT_CadDoneCallback(bool channelActivityDetected);

static void LORA_ptop_SetInTxMode(uint8_t sf, int8_t pwr);

RadioEvents_t RadioEvents =
{
    EVENT_TxDoneCallback, EVENT_TxTimeoutCallback, EVENT_RxDoneCallback, EVENT_RxTimeoutCallback, EVENT_RxErrorCallback, NULL, EVENT_CadDoneCallback
};

struct lorapp_dev_t lorapp_dev;

/**
 * @brief  SX1278_ptop_config
 * @param  sync_byte:0x12
 * @param  power:20
 * @retval None
 */
void LORA_ptop_config(uint8_t sync_byte, int8_t power)
{
    uint8_t reg_value = 0;

    SX1276IoInit();

    lorapp_dev.prx       = NULL;
    lorapp_dev.rx_len    = 0;

//    for (uint32_t i = 0; i < MSG_Q_NUM; i++)
//    {
//        lorapp_dev.msg_q_num[i] = NULL;
//    }

    SX1276Init(&RadioEvents);

    SX1276SetSleep( );
    SX1276SetModem( MODEM_LORA );

    SX1276Write( REG_OCP, 0x0B );

    printf("reg: %d \r\n", 0x0B);
    reg_value = 10;
    reg_value = SX1276Read(REG_OCP);
    printf("reg: %d \r\n", reg_value);

    SX1276Write( REG_PADAC, 0x84 );
    SX1276Write( REG_OSC, 0xFF);
    SX1276Write( REG_LNA, 0x23 );

    SX1276SetSyncWord(0x12);
    SX1276SetRfTxPower(20);
    uint32_t rand_v = SX1276Random();
    reg_value = SX1276Read(REG_LR_VERSION);
    SX1276SetStby();

    printf("LORA_Module_V%d.%d Init OK ...\r\n", reg_value, rand_v);
}



/**
 * @brief  LORA_ptop_SetInRxMode
 * @param  None, Channel:475500000 power:20
 * @retval None
 */
void LORA_ptop_SetInRxMode(uint8_t op_lock)
{

    uint8_t reg = 0 ;

    static uint8_t sf = 12;

    uint8_t   current_sf = 0;

//    current_sf = BSP_PB_GetState(BUTTON_MODE);
//
//    if(current_sf == 0)
//    {
//        current_sf = 7;
//    }
//    else
//    {
//        current_sf = 12;
//    }

    current_sf = 7;

    if(current_mode != RX_MODE || current_sf != sf)
    {
        SX1276SetStby();
        SX1276SetChannel(475500000);

        SX1276SetRxConfig(  MODEM_LORA, 0,   // modem, bandwidth([0: 125 kHz, 1: 250 kHz,2: 500 kHz, 3: Reserved]),
                            current_sf, 1,           // datarate(6: 64, 7: 128, 8: 256, 9: 512,10: 1024, 11: 2048, 12: 4096)
                            // coderate([1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]),
                            0,  8,           // bandwidthAfc, uint16_t preambleLen,
                            1023, false,        // symbTimeout(4~1023), bool fixLen,
                            128,               // payloadLen
                            true, false, 255,  // crcOn, FreqHopOn, HopPeriod,
                            false, true );  // iqInverted,  rxContinuous

        SX1276SetMaxPayloadLength(MODEM_LORA, 255);

        SX1276SetStby();

        reg = SX1276Read(0x41);

        reg &= RFLR_DIOMAPPING2_DIO4_MASK;
        reg |= RFLR_DIOMAPPING2_DIO4_01;

        SX1276Write(0x41, reg);

        SX1276SetRx(3e6);

        current_mode = RX_MODE;

        sf = current_sf;
    }


//    while(RF_RX_RUNNING != SX1276GetStatus());
}

/**
 * @brief  LORA_ptop_SetInTxMode
 * @param  None, Channel:507500000
 * @retval None
 */
void LORA_ptop_SetInTxMode(uint8_t sf, int8_t pwr)
{
    uint8_t reg = 0 ;

    if(current_mode != TX_MODE)
    {
        SX1276SetStby();
        SX1276SetChannel(475500000);
        SX1276SetTxConfig( MODEM_LORA, pwr, 0,   //modem, power, fdev
                           0, sf,                //bandwidth, datarate,
                           1, 8,                 //coderate, preambleLen,
                           false, true, false,   //fixLen, crcOn, FreqHopOn,
                           0, false, 3e6 );      //HopPeriod, iqInverted, timeout

        SX1276SetMaxPayloadLength(MODEM_LORA, 255);

        reg = SX1276Read(0x41);

        reg &= RFLR_DIOMAPPING2_DIO4_MASK;
        reg |= RFLR_DIOMAPPING2_DIO4_00;

        SX1276Write(0x41, reg);

        current_mode = TX_MODE;

        SX1276SetStby();

    }


}

/**
 * @brief  LORA_ptop_SendMsg
 * @param  pchar
 * @param  len
 * @retval None
 */
void LORA_ptop_SendMsg(uint8_t sf, int8_t pwr, uint8_t* pchar, uint32_t len)
{
    LORA_ptop_SetInTxMode(sf, pwr);
    SX1276Send(pchar, len);

    HAL_Delay(20);

//    while(RF_IDLE != SX1276GetStatus())
//    {
//        HAL_Delay(1);
//    }
}

struct msg_q_t ptmp_msg;

void* LORA_ptop_ReceiveMsg( uint8_t **ppchar, uint16_t* len, int16_t* rssi, int8_t* snr, uint32_t block_wait)
{
//    struct msg_q_t ptmp_msg;
//    memset(&ptmp_msg, 0, sizeof(ptmp_msg));

    //if( xQueueReceive( lorapp_dev.msg_q, &ptmp_msg,  block_wait ) )
    {
        *rssi   = ptmp_msg.rssi;
        *snr    = ptmp_msg.snr;
        *ppchar = ptmp_msg.tcb;
        *len    = ptmp_msg.tcb_len;
    }

    return (void*)ptmp_msg.tcb;
}

void LORA_ptop_SetSleep(void)
{
    SX1276SetSleep( );
}

void EVENT_TxDoneCallback(void)
{
    printf("EVENT_TxDone ...\r\n");
}

void EVENT_TxTimeoutCallback(void)
{
    printf("EVENT_TxTimeout ...\r\n");
}

void EVENT_RxDoneCallback( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
//    struct msg_q_t tmp_msg;
//    uint8_t* pchar = NULL;

    if (NULL == payload)
    {
        return;
    }

    if (size)
    {
        size %= 256;

        ptmp_msg.rssi = rssi;
        ptmp_msg.snr  = snr;
        ptmp_msg.tcb_len = size;
        ptmp_msg.tcb     = (uint8_t*)malloc(size);

        memcpy(ptmp_msg.tcb, payload, ptmp_msg.tcb_len);

//        if(pdPASS != xQueueSendFromISR(lorapp_dev.msg_q, (void *)&tmp_msg, NULL))
//        {
//            free(tmp_msg.tcb);
//        }

    }
}

void EVENT_RxTimeoutCallback(void)
{
    LORA_ptop_SetInRxMode(OP_MUTEX_UNLOCK);
    printf("EVENT_RxTimeout ...\n");
}

void EVENT_RxErrorCallback(void)
{
    LORA_ptop_SetInRxMode(OP_MUTEX_UNLOCK);
    printf("EVENT_RxError ...\n");
}

void EVENT_CadDoneCallback( bool channelActivityDetected )
{
    if (true == channelActivityDetected)
    {
        printf("EVENT_CadDone channelActivityDetected ...\n");
    }
    else
    {
        printf("EVENT_CadDone ...\n");
    }
    LORA_ptop_SetInRxMode(OP_MUTEX_UNLOCK);
}

