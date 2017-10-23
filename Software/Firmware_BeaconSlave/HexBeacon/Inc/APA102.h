#ifndef __APA102_H
#define __APA102_H

#include "main.h"
#include "stm32f4xx_hal.h"

#include <string.h> // memcpy
#include "limits.h" // data type info / sizes

// === APA102 Strip Configurable Parameters ===
#define APA102_STRIPLEN           		100     // Length of APA102 LED Strip
#define APA102_SPI_HANDLE         		hspi2   // SPI port connected to APA102 LED Strip
#define APA102_CURRENT_LIMIT_ENABLE     0
#define APA102_MAX_CURRENT        		100000   // Max current available for entire strip. (mA)
#define APA102_CHANNEL_CURRENT    		20      // Current consumed by each channel (color). (mA)


// === APA102 Strip Protocol Parameters ===
#define APA102_BYTES_PER_PIXEL           4
#define APA102_START_FRAME_BYTES         4
#define APA102_END_FRAME_BYTES           12
#define APA102_STRIP_UPDATE_PACKET_BYTES (APA102_START_FRAME_BYTES + (APA102_STRIPLEN * APA102_BYTES_PER_PIXEL) + APA102_END_FRAME_BYTES)
#define MAX_BLINKY                       7
uint8_t APA102_StartFrameByte                                 = {0b00000000};
uint8_t APA102_EndFrameByte                                   = {0b11111111};
uint8_t APA102_Strip[APA102_STRIP_UPDATE_PACKET_BYTES]        = {0};
uint8_t APA102_Strip_Buffer[APA102_STRIP_UPDATE_PACKET_BYTES] = {0};    // Buffer strip updates so that the strip data array can be edited during DMA output operations.
#define APA102_MAX_STRIP_LENGTH  (APA102_START_FRAME_BYTES + (UINT_MAX / APA102_BYTES_PER_PIXEL) + APA102_END_FRAME_BYTES)    // Presently, this calculation assumes the only limiting factor in play is the max value of an unisgned int.  YMMV, likely by a lot.

// APA102_stripStatus - Global status of APA102 strip.  Primarily used to indicate whether a strip update is currently underway.
typedef enum
{
  APA102_UNKNOWN,
  APA102_ERROR,
  APA102_IDLE,
  APA102_UPDATING
} APA102_stripStatus;
APA102_stripStatus APA102_stripStatus1 = APA102_UNKNOWN;

// APA102_result - Return status for APA102 related function calls.
typedef enum
{
  APA102_SUCCESS,
  APA102_FAILURE
} APA102_result;



APA102_result APA102_Update(void);
APA102_result APA102_Init(void);
APA102_result APA102_SetPixel(uint32_t, uint8_t, uint16_t, uint16_t);
APA102_result APA102_SetStrip(uint8_t, uint16_t, uint16_t);
uint8_t APA102_Intensity_To_Current(uint8_t);





#endif /* __APA102_H */
