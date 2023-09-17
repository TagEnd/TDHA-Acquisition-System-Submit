#include "ad7606.h"
#include "usart.h"
#include "string.h"
#include "FFT_MATH.h"
#include "rtc.h"

#include "dma.h"
#include "sdio.h"
#include "ScreenGui.h"

#include "arm_math.h"
#include "arm_const_structs.h"

#include "err.h"
#include "crc.h"

// #include "arm_t"

/*******************************************************
 *
 * Declare a struct variable in ur app_code.c as bellow
 * AD7606Dev ad7606dev;
 * and initialize it.
 *
 ********************************************************/

// short adcBuf[testCHs];                       0x08000000
__attribute__((section(".__malloc"))) short AdcCH1PingData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH2PingData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH3PingData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH4PingData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH5PingData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH6PingData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH7PingData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH8PingData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH1PongData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH2PongData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH3PongData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH4PongData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH5PongData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH6PongData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH7PongData[bufLen] = {0};
__attribute__((section(".__malloc"))) short AdcCH8PongData[bufLen] = {0};

uint8_t SendDataBuffIndex = 0;
__attribute__((section(".ccmram"))) uint8_t SendDataBuff[30][SendBufLen];

// __attribute__((section(".__malloc"))) uint16_t SendDataBuff[50][SendBufLen];

int16_t pingPongFlag = 0;
int16_t anaFlag = 0;

RTC_DateTypeDef GetData;

RTC_TimeTypeDef GetTime;

uint32_t SendCount;
uint32_t SendErrCount;

uint8_t Muin;

char *NowTimeCopy;

int count;

short temp;

HAL_StatusTypeDef DMA_status;

static void ini7606Paras(AD7606Dev *dev)
{
    dev->baseaddr = 0x60000000;
    dev->interface = AD7606_PARALLEL;
    dev->range = AD7606_10V;
    dev->osr = AD7606_OSR_64;
}

void ad7606ini(AD7606Dev *dev)
{
    NowTimeCopy = (char *)malloc(20 * sizeof(char));
    memset(NowTimeCopy, 0, sizeof(NowTimeCopy[0]));
    count = 0;
    SendCount = 0;
    SendErrCount = 0;
    Muin = 0;
    memset(AdcCH1PingData, 0, sizeof(AdcCH1PingData));
    memset(AdcCH2PingData, 0, sizeof(AdcCH2PingData));
    memset(AdcCH3PingData, 0, sizeof(AdcCH3PingData));
    memset(AdcCH4PingData, 0, sizeof(AdcCH4PingData));
    memset(AdcCH5PingData, 0, sizeof(AdcCH5PingData));
    memset(AdcCH6PingData, 0, sizeof(AdcCH6PingData));
    memset(AdcCH7PingData, 0, sizeof(AdcCH7PingData));
    memset(AdcCH8PingData, 0, sizeof(AdcCH8PingData));

    memset(AdcCH1PongData, 0, sizeof(AdcCH1PingData));
    memset(AdcCH2PongData, 0, sizeof(AdcCH2PongData));
    memset(AdcCH3PongData, 0, sizeof(AdcCH3PongData));
    memset(AdcCH4PongData, 0, sizeof(AdcCH4PongData));
    memset(AdcCH6PongData, 0, sizeof(AdcCH6PongData));
    memset(AdcCH7PongData, 0, sizeof(AdcCH7PongData));
    memset(AdcCH8PongData, 0, sizeof(AdcCH8PongData));

    // memset(SendVIBuffT, 0, sizeof(SendVIBuffT));

    int i;

    ini7606Paras(dev);

    /// set rang
    if (dev->range == AD7606_10V)
    {
        HAL_GPIO_WritePin(ADC_RANG_GPIO_Port, ADC_RANG_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(ADC_RANG_GPIO_Port, ADC_RANG_Pin, GPIO_PIN_RESET);
    }

    /// set osr
    // if (dev->osr == AD7606_OSR_64)
    // {
    //     HAL_GPIO_WritePin(ADC_OS0_GPIO_Port, ADC_OS0_Pin, GPIO_PIN_SET);
    //     HAL_GPIO_WritePin(ADC_OS1_GPIO_Port, ADC_OS1_Pin, GPIO_PIN_RESET);
    //     HAL_GPIO_WritePin(ADC_OS2_GPIO_Port, ADC_OS2_Pin, GPIO_PIN_SET);
    // }
    HAL_GPIO_WritePin(ADC_OS0_GPIO_Port, ADC_OS0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ADC_OS1_GPIO_Port, ADC_OS1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ADC_OS2_GPIO_Port, ADC_OS2_Pin, GPIO_PIN_RESET);

    /// clear bufs.
    for (i = 0; i < DataBufLen; i++)
    {
        dev->dataBuf[i] = 0;
    }

    HAL_GPIO_WritePin(ADC_STANDBY_GPIO_Port, ADC_STANDBY_Pin, GPIO_PIN_SET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(ADC_RST_GPIO_Port, ADC_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(ADC_RST_GPIO_Port, ADC_RST_Pin, GPIO_PIN_RESET);
}

void get_AD7606(void)
{

    static int bufPtr = 0;

    if (pingPongFlag)
    {
        AdcCH1PingData[bufPtr] = AD7606Addr;
        AdcCH2PingData[bufPtr] = AD7606Addr;
        AdcCH3PingData[bufPtr] = AD7606Addr;
        AdcCH4PingData[bufPtr] = AD7606Addr;
        AdcCH5PingData[bufPtr] = AD7606Addr;
        AdcCH6PingData[bufPtr] = AD7606Addr;
        AdcCH7PingData[bufPtr] = AD7606Addr;
        AdcCH8PingData[bufPtr++] = AD7606Addr;
        if (bufPtr == bufLen)
        {
            bufPtr = 0;
            pingPongFlag = 1 - pingPongFlag;
            anaFlag = 1;
        }
    }
    else
    {
        AdcCH1PongData[bufPtr] = AD7606Addr;
        AdcCH2PongData[bufPtr] = AD7606Addr;
        AdcCH3PongData[bufPtr] = AD7606Addr;
        AdcCH4PongData[bufPtr] = AD7606Addr;
        AdcCH5PongData[bufPtr] = AD7606Addr;
        AdcCH6PongData[bufPtr] = AD7606Addr;
        AdcCH7PongData[bufPtr] = AD7606Addr;
        AdcCH8PongData[bufPtr++] = AD7606Addr;
        if (bufPtr == bufLen)
        {
            bufPtr = 0;
            pingPongFlag = 1 - pingPongFlag;
            anaFlag = 1;
        }
    }
}

void ana_AD7606(void)
{

    if (anaFlag == 1)
    {
        // claculate(dataR, DataBuf);
        /* Get the RTC current Time */
        HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
        /* Get the RTC current Date */
        HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);

        if (Muin != GetTime.Minutes)
        {
            printf("%04d-%02d-%02d %02d:%02d:%02d---Success: %d,Err %d\r\n", 2000 + GetData.Year, GetData.Month, GetData.Date, GetTime.Hours, GetTime.Minutes, GetTime.Seconds, SendCount, SendErrCount);
            SendCount = 0;
            SendErrCount = 0;
            Muin = GetTime.Minutes;
        }
        anaFlag = 0;
        RankNumber++;
        if (pingPongFlag)
        {

            NoFFTClaculat(AdcCH1PongData, 1);
            NoFFTClaculat(AdcCH2PongData, 2);
            // NoFFTClaculat(AdcCH3PongData, 3);
            // NoFFTClaculat(AdcCH4PongData, 4);
            // NoFFTClaculat(AdcCH5PongData, 5);
            // NoFFTClaculat(AdcCH6PongData, 6);
            // NoFFTClaculat(AdcCH7PongData, 7);
            // NoFFTClaculat(AdcCH8PongData, 8);
        }
        else
        {

            NoFFTClaculat(AdcCH1PingData, 1);
            NoFFTClaculat(AdcCH2PingData, 2);
            // NoFFTClaculat(AdcCH3PingData, 3);
            // NoFFTClaculat(AdcCH4PingData, 4);
            // NoFFTClaculat(AdcCH5PingData, 5);
            // NoFFTClaculat(AdcCH6PingData, 6);
            // NoFFTClaculat(AdcCH7PingData, 7);
            // NoFFTClaculat(AdcCH8PingData, 8);
        }
    }
}

void claculate(float *fBuf, short *sBuf, uint8_t Channel)
{
    int i;
    for (i = 0; i < bufLen; i++)
    {
        // fBuf[i] = sBuf[i] / 32768.0 * ADRANG;
        // UpdateChart(fBuf[i],1);
        // fBuf[i*2] = sBuf[i*8+(Channel-1)] / 32768.0 * ADRANG;
        fBuf[i * 2] = sBuf[i] / 32768.0 * ADRANG;
        fBuf[i * 2 + 1] = 0;
        // UpdateChart(fBuf[i*2],1);
    }
}

void NoFFTClaculat(short *DataBuf, uint8_t Channel)
{
    int i;

    uint16_t CrCValueLen;
    uint16_t SendVIBuffAddIndex = 0;
    uint16_t CRCValueIndex = 0;
    uint16_t SendVIBuffIndex = 0;

    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = 255;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = 255;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = 254;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = 254;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = OperateMode;
    uint16_t TempTime = 2000 + GetData.Year;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = TempTime >> 8;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = TempTime;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = GetData.Month;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = GetData.Date;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = GetTime.Hours;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = GetTime.Minutes;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = GetTime.Seconds;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = RankNumber;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = HomeID;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = Channel;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = bufLen >> 8;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = bufLen;
    for (i = 0; i < bufLen; i++)
    {
        SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = DataBuf[i] >> 8;
        SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = DataBuf[i];
    }
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = SendDataBuffIndex;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = 0x00;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = 0x00;

    CrCValueLen = SendVIBuffAddIndex / 4;

    uint32_t CrCValue[CrCValueLen];
    for (i = 0; i < CrCValueLen; i++)
    {
        CrCValue[CRCValueIndex] = SendDataBuff[SendDataBuffIndex][SendVIBuffIndex++] << 24;
        CrCValue[CRCValueIndex] += SendDataBuff[SendDataBuffIndex][SendVIBuffIndex++] << 16;
        CrCValue[CRCValueIndex] += SendDataBuff[SendDataBuffIndex][SendVIBuffIndex++] << 8;
        CrCValue[CRCValueIndex] += SendDataBuff[SendDataBuffIndex][SendVIBuffIndex++];
        CRCValueIndex++;
    }

    uint32_t CrcRes = HAL_CRC_Calculate(&hcrc, (uint32_t *)CrCValue, CRCValueIndex);

    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = (uint8_t)(CrcRes >> 24);
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = (uint8_t)(CrcRes >> 16);
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = (uint8_t)(CrcRes >> 8);
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = (uint8_t)CrcRes;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = 254;
    SendDataBuff[SendDataBuffIndex][SendVIBuffAddIndex++] = 254;

    uint16_t len = SendBufLen;
    // SendDataBuff[SendDataBuffIndex] = SendVIBuff;
    err_t res = LWIP_Send_data(SendDataBuff[SendDataBuffIndex], len, Channel);
    if (res == ERR_OK)
    {
        SendCount++;
    }
    else
    {
        res = LWIP_Send_data(SendDataBuff[SendDataBuffIndex], len, Channel);
        if (res == ERR_OK)
        {
            SendCount++;
        }
        else
        {
            SendErrCount++;
        }

        printf("err_t: %d", res);
    }
    SendDataBuffIndex = (SendDataBuffIndex + 1) % 30;
}

void float2u8Arry(uint8_t *u8Arry, float *floatdata, uint8_t key)
{
    uint8_t farray[4];
    *(float *)farray = *floatdata;
    if (key == 1)
    {
        u8Arry[3] = farray[0];
        u8Arry[2] = farray[1];
        u8Arry[1] = farray[2];
        u8Arry[0] = farray[3];
    }
    else
    {
        u8Arry[0] = farray[0];
        u8Arry[1] = farray[1];
        u8Arry[2] = farray[2];
        u8Arry[3] = farray[3];
    }
}

// void TestRAM()
// {
//     for (uint16_t i = 0; i < 2000; i++)
//     {
//         SendDataBuff[SendDataBuffIndex][i] = i;
//         /* code */
//     }
// }