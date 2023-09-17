#include "ref.h"


;/*    
;* @brief  In-place bit reversal function.   
;* @param[in, out] *pSrc        points to the in-place buffer of unknown 32-bit data type. 
;* @param[in]      bitRevLen    bit reversal table length
;* @param[in]      *pBitRevTab  points to bit reversal table.   
;* @return none.   
;*/
// void arm_bitreversal_32(uint32_t *pSrc, uint16_t bitRevLen, uint16_t *pBitRevTab)
// {
// 	uint32_t a,b,i,tmp;
	
// 	for(i=0; i<bitRevLen; i++) 
// 	{
// 		 a = pBitRevTab[2*i];
// 		 b = pBitRevTab[2*i + 1];

// 	//real
// 		 tmp = pSrc[a];
// 		 pSrc[a] = pSrc[b];
// 		 pSrc[b] = tmp;

// 	//complex
// 		 tmp = pSrc[a+1];
// 		 pSrc[a+1] = pSrc[b+1];
// 		 pSrc[b+1] = tmp;
// 	}
// }
void
arm_bitreversal_32 (uint32_t * pSrc, const uint16_t bitRevLen,
                    const uint16_t * pBitRevTable)
{
  uint32_t r7,r6,r5,r4,r3;
  if (bitRevLen <= 0)
    return;
  r3 = ((bitRevLen+1) >> 2);
  while (r3 > 0)
    {
      r7 = *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[3]);
      r6 = *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[2]);
      r5 = *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[1]);
      r4 = *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[0]);
      *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[3]) = r6;
      *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[2]) = r7;
      *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[1]) = r4;
      *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[0]) = r5;
      r7 = *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[3] + 4);
      r6 = *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[2] + 4);
      r5 = *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[1] + 4);
      r4 = *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[0] + 4);
      *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[3] + 4) = r6;
      *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[2] + 4) = r7;
      *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[1] + 4) = r4;
      *(uint32_t*)((uint8_t*) pSrc + pBitRevTable[0] + 4) = r5;
      pBitRevTable += 4;
      r3--;
    }
}