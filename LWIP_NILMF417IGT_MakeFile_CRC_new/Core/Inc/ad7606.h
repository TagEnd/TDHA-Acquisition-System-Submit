#ifndef __AD7606_H__
#define __AD7606_H__

#include "main.h"
#include "gpio.h"
#include "math.h"
#include "stdio.h"
#define AD7606Addr *(volatile short *)(0x60000000)

#define DataBufLen 4096

#define testCHs 8

#define ADRANG 10.0

#define fftN 10

// #define Distance 1

// #define useFFTDis       20
// #define useFFTDis2      40

#define BasefeatLen 5

#define M_PI2 6.283185307179

// #define M_PI        3.1415936

#define HomeID 1

#define bufLen 1024
// 数据 + 头信息 + 填充 + 帧尾 + CRC结果
#define SendBufLen bufLen * 2 + 17 + 3 + 2 + 4

extern char *NowTimeCopy;

static int OperateMode = 0;

static int RankNumber = 0;

enum ad7606_interface
{
  AD7606_SERIAL,
  AD7606_PARALLEL,
};

enum ad7606_range
{
  AD7606_5V = 1,
  AD7606_10V = 2,
};

enum ad7606_osr
{
  AD7606_OSR_0,
  AD7606_OSR_2,
  AD7606_OSR_4,
  AD7606_OSR_8,
  AD7606_OSR_16,
  AD7606_OSR_32,
  AD7606_OSR_64,
  AD7606_OSR_128,
};

typedef struct ad7606
{
  /* data */
  uint32_t baseaddr;
  int16_t dataBuf[DataBufLen];
  enum ad7606_interface interface;
  enum ad7606_range range;
  enum ad7606_osr osr;
} AD7606Dev;

extern DMA_HandleTypeDef hdma_tim2_ch1;

extern __attribute__((section(".ccmram"))) uint8_t SendDataBuff[30][SendBufLen];

void ad7606ini(AD7606Dev *dev);
void get_AD7606(void);
void ana_AD7606(void);

void claculate(float *fBuf, short *sBuf, uint8_t Channel);

void NoFFTClaculat(short *vDataBuf, uint8_t Channnel);

void float2u8Arry(uint8_t *u8Arry, float *floatdata, uint8_t key);
// void TestRAM();
// // void InitBufInArray(void);
// void FFT_T(void);

// void PowerPhaseRadians_f32(uint16_t _usFFTPoints, float32_t _uiCmpValue);
#endif